use crate::traits::*;
use crate::type_traits::*;
use dword::iter_bits::*;
use dword::split::*;
use dword::*;

crate::derive_display!(DWordRef<'_>);
crate::derive_display!(DWord);
crate::default_base!(16, DWordRef<'_>);
crate::default_base!(16, DWord);

impl Type for DWord {
    type Arg<'a> = DWordRef<'a>;
    type Length = usize;
    fn as_arg(&self) -> Self::Arg<'_> {
        self.as_ref()
    }
}

impl CloneArg for DWordRef<'_> {
    type Owned = DWord;
    fn clone_arg(self) -> Self::Owned {
        self.clone_word()
    }
}

impl Zero for DWord {
    fn zero(bits: Self::Length) -> Self {
        DWord::zero(bits)
    }
}

impl Ring for DWord {
    fn negate(x: Self::Arg<'_>) -> Self {
        -x
    }
    fn mul(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
        x * y
    }
    fn sub(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
        x - y
    }
    fn add(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
        x + y
    }
    fn from_integer(bits: Self::Length, x: &num::BigInt) -> Self {
        DWord::from_int(bits, x)
    }

    fn exp_usize(x: Self::Arg<'_>, y: usize) -> Self {
        x.pow_usize(y)
    }

    fn exp_uint(x: Self::Arg<'_>, y: &num::BigUint) -> Self {
        x.pow_uint(y)
    }
}

impl Integral for DWord {
    fn to_usize(x: Self::Arg<'_>) -> usize {
        x.into()
    }
    #[inline(always)]
    fn to_usize_maybe(x: Self::Arg<'_>) -> Option<usize> {
        x.into()
    }
    fn to_integer(x: Self::Arg<'_>) -> num::BigInt {
        x.into()
    }
    fn div(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
        x / y
    }
    fn modulo(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
        x % y
    }
}

impl Literal for DWord {
    fn number_usize(n: Self::Length, x: usize) -> Self {
        Self::from_usize(n, x)
    }
    fn number_uint(n: Self::Length, x: &num::BigUint) -> Self {
        Self::from_uint(n, x)
    }
}

impl Logic for DWord {
    fn complement(x: Self::Arg<'_>) -> Self {
        !x
    }
    fn xor(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
        x ^ y
    }
    fn and(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
        x & y
    }
    fn or(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
        x | y
    }
}

impl Eq for DWord {
    fn eq(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
        x == y
    }
}

impl Cmp for DWord {
    fn lt(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
        x < y
    }
    fn gt(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
        x > y
    }
    fn le(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
        x <= y
    }
    fn ge(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
        x >= y
    }
}

impl SignedCmp for DWord {
    fn signed_lt(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
        x.to_signed_integer() < y.to_signed_integer()
    }
}

impl Sequence for DWordRef<'_> {
    type Item = bool;

    fn seq_length(self) -> usize {
        self.bits()
    }

    fn seq_shift_right(self, _: (), amt: usize) -> Self::Owned {
        self >> amt
    }

    fn seq_shift_right_signed(self, amt: usize) -> Self::Owned {
        // Note that this is not recursive, we are calling the
        // inherent method with the same name on DWordRef
        self.shift_right_signed(amt)
    }

    fn seq_shift_left(self, _: (), amt: usize) -> Self::Owned {
        self << amt
    }

    fn seq_rotate_right(self, amt: usize) -> Self::Owned {
        self.rotate_right(amt)
    }

    fn seq_rotate_left(self, amt: usize) -> Self::Owned {
        self.rotate_left(amt)
    }

    fn seq_index(self, i: usize) -> Self::Item {
        self.index_msb(i)
    }

    fn seq_index_front<I: Integral>(self, i: I::Arg<'_>) -> Self::Item {
        crate::index_word::<I>(self, i)
    }

    fn seq_index_back<I: Integral>(self, i: I::Arg<'_>) -> Self::Item {
        crate::index_word_back::<I>(self, i)
    }
}

impl SeqOwned for DWord {
    type Item = bool;

    fn seq_reverse(self) -> Self {
        self.reverse()
    }

    fn seq_update(mut self, i: usize, v: bool) -> DWord {
        self.set_bit_msb(i, v);
        self
    }
}

impl ToSignedInteger for DWordRef<'_> {
    fn to_signed_int(self) -> num::BigInt {
        self.to_signed_integer()
    }
}

impl<INDEX: Send + Sync + IndexDir + 'static> Stream<bool> for TraverseBitsOwned<INDEX> {}
impl<INDEX: Send + Sync + IndexDir + 'static> Stream<DWord> for TraverseWordsOwned<INDEX> {}
