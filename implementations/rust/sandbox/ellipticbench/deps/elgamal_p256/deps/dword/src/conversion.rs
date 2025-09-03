use crate::core::{BigLimbT, LimbT, is_signed, limbs_for_size};
use crate::{DWord, DWordRef};
use num::bigint::Sign;

impl DWord {
    /// Create a DWord of the given size, initialized by u8
    pub fn from_u8(bits: usize, value: u8) -> DWord {
        Self::from_u64(bits, value as u64)
    }

    /// Create a DWord of the given size, initialized by u16
    pub fn from_u16(bits: usize, value: u16) -> DWord {
        Self::from_u64(bits, value as u64)
    }

    /// Create a DWord of the given size, initialized by u32
    pub fn from_u32(bits: usize, value: u32) -> DWord {
        Self::from_u64(bits, value as u64)
    }

    /// Create a DWord of the given size, initialized by u64
    pub fn from_u64(bits: usize, value: u64) -> DWord {
        let mut result = DWord::zero(bits);
        if bits == 0 {
            return result;
        }

        if result.padding() > 0 {
            result.as_slice_mut()[0] = value << result.padding();
            if bits > DWord::LIMB_BITS {
                result.as_slice_mut()[1] = (value >> result.not_padding()) as LimbT;
            }
        } else {
            result.as_slice_mut()[0] = value;
        }
        result
    }

    /// Create DWord of the given size, initialized by a u128
    pub fn from_u128(bits: usize, mut value: u128) -> DWord {
        let mut result = DWord::zero(bits);
        if bits == 0 {
            return result;
        }

        let p = result.padding();
        result.as_slice_mut()[0] = (value as u64) << p;
        let mut done = result.not_padding();
        if bits == done {
            return result;
        }

        value >>= result.not_padding();
        result.as_slice_mut()[1] = value as u64;
        done += DWord::LIMB_BITS;
        if bits == done {
            return result;
        }

        result.as_slice_mut()[2] = (value >> DWord::LIMB_BITS) as u64;
        result
    }

    pub fn from_usize(bits: usize, value: usize) -> DWord {
        Self::from_u64(bits, value as u64)
    }

    /// Create a DWord of the given size, initialized with an unsigned integer
    pub fn from_uint(bits: usize, value: &num::BigUint) -> DWord {
        let limb_num = limbs_for_size(bits);
        let mut limbs = Vec::<LimbT>::with_capacity(limb_num);
        limbs.extend(
            value
                .iter_u64_digits()
                .chain(std::iter::repeat(0))
                .take(limb_num),
        );
        let mut result = DWord::from_limbs(bits, limbs);
        let pad = result.padding();
        if pad > 0 {
            result.shift_bits_left(pad);
        }
        result
    }

    /// Create a DWord of the given size, initialized with an sigend integer.
    /// The result uses 2s complement.
    pub fn from_int(bits: usize, n: &num::BigInt) -> DWord {
        let limb_num = limbs_for_size(bits);
        let mut limbs = Vec::<LimbT>::with_capacity(limb_num);

        // Use this to extend in the most significant limbs.
        let ext: u8 = match n.sign() {
            num::bigint::Sign::Minus => 255,
            _ => 0,
        };

        let mut bytes = n.to_signed_bytes_le().into_iter();
        for _ in 0..limb_num {
            let mut w: LimbT = 0;
            for z in 0..DWord::LIMB_BYTES {
                let b = match bytes.next() {
                    None => ext,
                    Some(x) => x,
                };
                w |= (b as LimbT) << (8 * z);
            }
            limbs.push(w);
        }
        let mut result = DWord::from_limbs(bits, limbs);
        let pad = result.padding();
        if pad > 0 {
            result.shift_bits_left(pad)
        }
        result
    }

    /// Create a DWord from the given stream of bits.
    /// The stream gives the bits from the most significatn end.
    pub fn from_stream_msb(bits: usize, mut n: impl Iterator<Item = bool>) -> DWord {
        let mut result = DWord::zero(bits);
        let pad = result.padding();
        for (i, x) in result.as_slice_mut().iter_mut().enumerate().rev() {
            let start = if i == 0 { pad } else { 0 };
            for shift_amt in (start..(LimbT::BITS as usize)).rev() {
                match n.next() {
                    Some(b) => {
                        if b {
                            *x |= 1 << shift_amt
                        }
                    }
                    None => return result,
                }
            }
        }
        result
    }
}

// -----------------------------------------------------------------------------
// Export

// This also adds constructor instances for the primitives
macro_rules! to_uprim {
    ($t:ty) => {
        impl From<DWordRef<'_>> for $t {
            fn from(x: DWordRef<'_>) -> Self {
                if x.bits() == 0 {
                    return 0;
                }
                const N: usize = <$t>::BITS as usize;
                let have = x.not_padding();
                let ws = x.as_slice();
                let mut w = ws[0] >> x.padding();
                if x.bits() >= N && have < N {
                    w |= ws[1] << have;
                }
                w as $t
            }
        }

        impl From<DWordRef<'_>> for Option<$t> {
            fn from(x: DWordRef<'_>) -> Self {
                let max = DWord::from_u64(x.bits(), <$t>::MAX as u64);
                if x <= max.as_ref() {
                    Some(x.into())
                } else {
                    None
                }
            }
        }

        impl From<$t> for DWord {
            fn from(x: $t) -> Self {
                DWord::from_u64(<$t>::BITS as usize, x as u64)
            }
        }
    };
}

to_uprim!(u8);
to_uprim!(u16);
to_uprim!(u32);
to_uprim!(u64);
to_uprim!(usize);

impl From<DWordRef<'_>> for u128 {
    fn from(x: DWordRef<'_>) -> Self {
        let w = x.bits();
        if w <= 64 {
            return <u64>::from(x) as u128;
        }
        let ws = x.as_slice();
        let p = x.padding();
        let np = x.not_padding();
        let res = ((ws[1] as u128) << np) | (ws[0] >> p) as u128;

        let consumed = DWord::LIMB_BITS + np;
        let need = 128 - consumed;
        let have = w - consumed;
        if need > 0 && have > 0 {
            ((ws[2] as u128) << consumed) | res
        } else {
            res
        }
    }
}

impl From<DWordRef<'_>> for Option<u128> {
    fn from(x: DWordRef<'_>) -> Self {
        if x <= DWord::from(u128::MAX).as_ref() {
            Some(x.into())
        } else {
            None
        }
    }
}

impl From<u128> for DWord {
    fn from(x: u128) -> Self {
        let xs = vec![x as u64, (x >> 64) as u64];
        DWord::from_limbs(128, xs)
    }
}

impl DWordRef<'_> {
    /// Convert to a vector of digits in base 2^32.
    /// Least significant digit first.
    /// Convenient for conversion to bignum (either a `num::BigUint` or a
    /// non-negative `num::BigInt`).
    pub fn as_vec_u32(self) -> Vec<u32> {
        let mut result = Vec::<u32>::with_capacity(self.limbs() * 2);
        if self.bits() == 0 {
            return result;
        }

        let ws = self.as_slice();
        let pad = self.padding();

        // we assume that DWord::LIMB_BITS >= 32
        let mut w = (ws[0] >> pad) as BigLimbT;
        let mut have = self.not_padding();

        while have >= 32 {
            result.push(w as u32);
            w = w >> 32;
            have -= 32;
        }

        for v in &ws[1..] {
            w = ((*v as BigLimbT) << have) | w;
            have += DWord::LIMB_BITS;
            while have >= 32 {
                result.push(w as u32);
                w = w >> 32;
                have -= 32;
            }
        }
        if have > 0 {
            result.push(w as u32);
        }
        result
    }

    /// Convert to a signed `num::BigInt`.
    pub fn to_signed_integer(self) -> num::BigInt {
        let (sign, digits) = if is_signed(self.as_slice()) {
            // If we have a signed DWord, then convert it to a two's complement
            // representation (by inverting the bits and adding one) before
            // computing its digits.
            let twos_comp: DWord = (!self).as_ref() + DWord::from_u64(self.bits(), 1).as_ref();
            (Sign::Minus, twos_comp.as_ref().as_vec_u32())
        } else {
            // If we have an unsigned DWord, then compute its digits directly.
            let s = if self.is_zero() {
                Sign::NoSign
            } else {
                Sign::Plus
            };
            (s, self.as_vec_u32())
        };
        num::BigInt::new(sign, digits)
    }
}

// To num::BigUint
impl From<DWordRef<'_>> for num::BigUint {
    fn from(x: DWordRef<'_>) -> Self {
        Self::new(x.as_vec_u32())
    }
}

// To num::BigInt. This assumes that the supplied DWordRef represents an
// unsigned integer, so the resulting BigInt will be non-negative.
impl From<DWordRef<'_>> for num::BigInt {
    fn from(x: DWordRef<'_>) -> Self {
        <_>::from(num::BigUint::from(x))
    }
}
