use crate::*;

#[derive(Clone, Copy)]
pub struct StaticValue<const N: usize> {}

#[derive(Clone, Copy)]
pub struct DynamicValue(pub usize);

/// This trait is for values that might be either statically known or dynamic.
pub trait GetValue: Copy {
    /// Get the value
    fn get_value(self) -> usize;
}

/// Instance for statically known value
impl<const N: usize> GetValue for StaticValue<N> {
    #[inline(always)]
    fn get_value(self) -> usize {
        N
    }
}

/// instance for dynamic valus.
impl GetValue for DynamicValue {
    #[inline(always)]
    fn get_value(self) -> usize {
        self.0
    }
}

/// An iterator over `u64`, which "chunks" the bits into smaller chunks.
/// The `step` specified how many bits at a time we produce.
/// We produce the chunks starting with the most significant ones.
/// The output of each step is a `u64` contains the relevant chunk in
/// the least significant part of the `u64`.
#[derive(Clone)]
pub struct WordIter<Step> {
    pub todo: usize,
    pub step: Step,
    pub value: u64,
}

impl<Step: GetValue> Iterator for WordIter<Step> {
    type Item = u64;
    fn next(&mut self) -> Option<u64> {
        let step = self.step.get_value();
        if self.todo >= step {
            self.todo = self.todo - step;
            let mask = u64::MAX >> (64 - step);
            Some((self.value >> self.todo) & mask)
        } else {
            None
        }
    }
}

impl<Step: GetValue + Sync + Send + 'static> Stream<u64> for WordIter<Step> {}

pub trait StreamBits {
    /// Iterate over the bits, MSB first
    fn to_bits(self) -> impl Stream<bool>;

    /// Construct from bits, MSB first
    fn from_bits(bits: &mut impl Stream<bool>) -> Self;
}

/// Split a word into chunks
#[macro_export]
macro_rules! split_word_ss {
    (128, $ty:ty, $this:expr) => {{
        let me = $this;
        $crate::split_word_ss!(64, $ty, me >> 64).chain($crate::split_word_ss!(64, $ty, me))
    }};

    ($total:literal, $ty:ty, $this:expr) => {
        $crate::split::WordIter::<$crate::split::StaticValue<{ <$ty>::BITS as usize }>> {
            todo: $total,
            step: $crate::split::StaticValue {},
            value: $this as u64,
        }
        .map(|x| (x as $ty))
    };
}

#[macro_export]
macro_rules! split_word_sd {
    (128, $each:expr, $this:expr) => {
        $crate::split_word_sd!(64, $each, $this >> 64)
            .chain($crate::split_word_sd!(64, $each, $this))
    };

    ($total:literal, $each:expr, $this:expr) => {
        $crate::split::WordIter::<$crate::split::DynamicValue> {
            todo: $total,
            step: $crate::split::DynamicValue($each),
            value: $this as u64,
        }
        .map(|x| $crate::DWord::from_u64($each, x))
    };
}

#[macro_export]
macro_rules! split_word_ds {
    ($ty:ty, $this:expr) => {
        $this
            .into_iter_words_msb(<$ty>::BITS as usize)
            .map(|x| <$ty>::from(x.as_ref()))
    };
}

/// Split a non-bit stream into chunks.
pub fn split<T: Type>(each: usize, xs: impl Stream<T>) -> impl Stream<Vec<T>> {
    #[derive(Clone)]
    struct S<I> {
        each: usize,
        xs: I,
    }

    impl<T, I: Send + Sync + Iterator<Item = T>> Iterator for S<I> {
        type Item = Vec<T>;
        fn next(&mut self) -> Option<Self::Item> {
            let mut result = Vec::with_capacity(self.each);
            for _ in 0..self.each {
                result.push(self.xs.next()?)
            }
            Some(result)
        }
    }

    impl<T: Type, I: Send + Sync + Clone + 'static + Iterator<Item = T> + 'static> Stream<Vec<T>>
        for S<I>
    {
    }

    S { each: each, xs: xs }
}

/// Split a bit stream into dynamic words
pub fn split_bits_dynamic(each: usize, xs: impl Stream<bool>) -> impl Stream<DWord> {
    split(each, xs).map(move |v| DWord::from_stream_msb(each, v.into_iter()))
}

/// Split a bit stream into static words
pub fn split_bits_static_inf<T>(mut xs: impl Stream<bool>) -> impl Stream<T>
where
    T: Type + StreamBits,
{
    std::iter::from_fn(move || Some(<T>::from_bits(&mut xs)))
}

/// Split a bit stream into static words
pub fn split_bits_static_fin<T>(parts: usize, xs: impl Stream<bool>) -> impl Stream<T>
where
    T: Type + StreamBits,
{
    split_bits_static_inf(xs).take(parts)
}

#[cfg(test)]
pub mod test {
    use crate::split::*;

    #[test]
    fn split_test() {
        let ss1: Vec<u8> = split_word_ss!(32, u8, 0x01020304).collect();
        assert_eq!(ss1, vec!(1, 2, 3, 4));

        let ss2: Vec<u32> =
            split_word_ss!(128, u32, 0x000102030405060708090a0b0c0d0e0f_u128).collect();
        assert_eq!(ss2, vec!(0x00010203, 0x04050607, 0x08090a0b, 0x0c0d0e0f));

        let sd_a: Vec<DWord> = split_word_sd!(16, 4, 0x0123).collect();
        let sd_b = vec![
            DWord::from_u8(4, 0),
            DWord::from_u8(4, 1),
            DWord::from_u8(4, 2),
            DWord::from_u8(4, 3),
        ];
        assert_eq!(sd_a, sd_b);

        let ds: Vec<u8> = split_word_ds!(u8, DWord::from_u32(24, 0x010203)).collect();
        assert_eq!(ds, vec!(1, 2, 3));

        let es: Vec<u8> =
            split_bits_static_fin::<u8>(2, 0x01_u8.to_bits().chain(0x02_u8.to_bits())).collect();
        assert_eq!(es, vec!(1, 2));
    }
}
