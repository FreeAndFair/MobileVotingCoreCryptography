use num::ToPrimitive;

use crate::type_traits::*;
use crate::traits::*;
use crate::split::*;
use dword::DWord;

macro_rules! stream_bits {
  (128, $this:expr) => {
    (($this >> 64) as u64).to_bits().chain(
     ($this        as u64).to_bits())
  };
  ($n:expr, $this:expr) => {
    WordIter::<StaticValue<1>> {
      todo: $n, step: StaticValue{}, value: $this as u64
    }.map(|x| x == 1)
  }
}

#[macro_export]
macro_rules! cat {
  ($amt: expr, $x:expr, $y:expr) => { ($x.wrapping_shl($amt)) | $y };
}

#[macro_export]
macro_rules! join {
  ($ty: ty, $n:expr, $xs:expr) => {
    $xs.fold(0 as $ty, |b,x| $crate::cat!($n, b, <$ty>::from((&x).as_arg())))
  }
}


// How many digits to use to represent things.
fn fmt_width(fmt: &std::fmt::Formatter, n: usize) -> usize {
  if let Some(w) = fmt.width() {
    if w > n { return w; }
  }
  n
}

macro_rules! NativeType {
  ($ty:ty, $sign_ty:ty, $from_uint:ident, $w:tt) => {
    $crate::PrimType!($ty);
    crate::default_base!(16,$ty);

    impl<const UPPER:bool> crate::display::Base<2, UPPER> for $ty {
      fn format(&self, fmt: &mut std::fmt::Formatter) -> std::fmt::Result {
        let width = fmt_width(fmt,<$ty>::BITS as usize + 2);
        write!(fmt,"{:#0width$b}",self)
      }
    }
    impl<const UPPER:bool> crate::display::Base<8, UPPER> for $ty {
      fn format(&self, fmt: &mut std::fmt::Formatter) -> std::fmt::Result {
        let w = (Self::BITS as usize + 2) / 3;  // 3 bits per digit
        let width = fmt_width(fmt,w);
        write!(fmt,"{:#0width$o}",self)
      }
    }
    impl<const UPPER:bool> crate::display::Base<10, UPPER> for $ty {
      fn format(&self, fmt: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(fmt,"{}",self)
      }
    }
    impl crate::display::Base<16, false> for $ty {
      fn format(&self, fmt: &mut std::fmt::Formatter) -> std::fmt::Result {
        let width = fmt_width(fmt,Self::BITS as usize /4 + 2);
        write!(fmt,"{:#0width$x}",self)
      }
    }
    impl crate::display::Base<16, true> for $ty {
      fn format(&self, fmt: &mut std::fmt::Formatter) -> std::fmt::Result {
        let width = fmt_width(fmt,Self::BITS as usize /4 + 2);
        write!(fmt,"{:#0width$X}",self)
      }
    }

    impl Static for $ty {
      type Dyn = DWord;
      fn dyn_o(self) -> Self::Dyn { self.into() }

      fn dyn_b(x: <Self as Type>::Arg<'_>) -> Self::Dyn { x.into() }

      fn stat_o(x: Self::Dyn) -> Self {
        assert!(x.bits() == Self::BITS as usize, "DWord to {} mismatch", stringify!($ty));
        Self::from(x.as_ref())
      }
      fn stat_b(x: <Self::Dyn as Type>::Arg<'_>) -> Self {
        assert!(x.bits() == Self::BITS as usize, "DWord to {} mismatch", stringify!($ty));
        Self::from(x)
      }
    }

    impl StreamBits for $ty {
      fn to_bits(self) -> impl Stream<bool> { stream_bits!($w,self) }
      fn from_bits(bits: &mut impl Stream<bool>) -> Self {
         bits.take(Self::BITS as usize).fold(0,|x,b|
           if b { (x << 1) | 1 } else { x << 1 }
         )
      }
    }

    impl ToSignedInteger for $ty {
      fn to_signed_int(self) -> num::BigInt {
        num::BigInt::from(self as $sign_ty)
      }
    }

    impl Zero for $ty {
      fn zero(_:Self::Length) -> Self { 0 }
    }

    impl Logic for $ty {
      fn complement(x: Self::Arg<'_>) -> Self { !x }
      fn xor(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self { x ^ y }
      fn and(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self { x & y }
      fn or (x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self { x | y }
    }

    impl Eq for $ty {
      fn eq(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool { x == y }
    }

    impl Cmp for $ty {
      fn lt(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool { x < y }
      fn gt(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool { x > y }
      fn le(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool { x <= y }
      fn ge(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool { x >= y }
    }

    impl SignedCmp for $ty {
      fn signed_lt(x: $ty, y: $ty) -> bool { (x as $sign_ty) < (y as $sign_ty) }
    }

    impl Literal for $ty {
      fn number_uint(_n: Self::Length, x: &num::BigUint) -> Self {
         match x.$from_uint() {
            Some(a) => a,
            None => {
              assert!(false, "Literal {} does not fit in `{}`", x, stringify!($ty));
              Self::MAX
          }
         }
      }
      fn number_usize(_n: Self::Length, x: usize) -> Self {
        if Self::BITS < usize::BITS {
          assert!(x <= Self::MAX as usize,
                      "Literal {} does not fit in `{}`", x, stringify!($ty))
        }
        x as Self
      }
    }


    impl Ring for $ty {
      fn negate(x: Self::Arg<'_>) -> Self { x.wrapping_neg() }
      fn mul(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self { x.wrapping_mul(y) }
      fn sub(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self { x.wrapping_sub(y) }
      fn add(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self { x.wrapping_add(y) }

      fn from_integer(_n: Self::Length, x: &num::BigInt) -> Self {
        let w = Self::BITS as usize;
        let mut it = x.iter_u32_digits();
        let res: $ty = if w <= 32 {
          it.next().unwrap_or(0) as Self
        } else {
          it.take(w/32).rev().fold(0,|x,d| x.wrapping_shl(32) | (d as Self))
        };
        match x.sign() {
          num::bigint::Sign::Minus => res.wrapping_neg(),
          _ => res
        }
      }

      fn exp_usize(x: Self::Arg<'_>, y: usize) -> Self {
          let mut p = y;
          let mut res = x.wrapping_pow(p as u32);
          p = p >> 32;
          if p == 0 { return res }
          let mut base = x;
          loop {
            base = base.wrapping_pow(1<<16).wrapping_pow(1<<16);
            res = res.wrapping_mul(base.wrapping_pow(p as u32));
            p = p >> 32;
            if p == 0 { return res }
          }
      }

      fn exp_uint(x: Self::Arg<'_>, y: &num::BigUint) -> Self {
        let mut base = x;
        y.iter_u32_digits().fold(1,|res,d| {
          let r1 = res * base.wrapping_pow(d);
            base = base.wrapping_pow(1<<16).wrapping_pow(1<<16);
            r1
        })
      }

    }

    impl Integral for $ty {
      fn to_usize(x: $ty) -> usize { x as usize }
      fn to_usize_maybe(x: $ty) -> Option<usize> {
        if Self::BITS <= usize::BITS {
          Some(x as usize)
        } else {
          if x <= usize::MAX as Self { Some (x as usize) } else { None }
        }
      }
      fn to_integer(x: $ty) -> num::BigInt { x.into() }
      fn div(x: $ty, y: $ty) -> $ty { x / y }
      fn modulo(x: $ty, y: $ty) -> Self { x % y }
    }

    impl Sequence for $ty {
      type Item = bool;

      fn seq_length(self) -> usize { Self::BITS as usize }

      fn seq_shift_right(self, _:(), amt: usize) -> $ty {
          if amt >= Self::BITS as usize { 0 } else { self >> amt }
      }

      fn seq_shift_right_signed(self, amt: usize) -> $ty {
        let i = self as $sign_ty;
        if amt >= Self::BITS as usize {
          if i >= 0 { 0 } else { Self::MAX }
        } else {
          (i >> amt) as Self
        }
      }

      fn seq_rotate_right(self, amt: usize) -> $ty {
        let w = Self::BITS as usize;
        let n = amt & (w - 1);
        let res = self >> n;
        res | (self << (w - n))
      }

      fn seq_shift_left(self, _: (), amt: usize) -> $ty {
        if amt >= Self::BITS as usize { 0 } else { self << amt }
      }

      fn seq_rotate_left(self, amt: usize) -> $ty {
        let w = Self::BITS as usize;
        let n = amt & (w - 1);
        let res = self << n;
        res | (self >> (w - n))
      }

      fn seq_index(self, i: usize) -> bool {
        let w = Self::BITS as usize;
        assert!(i < w, "Index out of bounds");
        ((self >> (w - 1 - i)) & 1) == 1
      }
    }

    impl SeqOwned for $ty {
      type Item = bool;

      fn seq_reverse(self) -> Self {
        self.reverse_bits()
      }

      fn seq_update(self, j: usize, v: bool) -> Self {
        let w = Self::BITS as usize;
        assert!(j < w, "seq_udpate: Index {} is too large for `{}`", j, stringify!($ty));
        if v { self | (1 << (w - j - 1)) } else { self & !(1 << (w - j - 1)) }
      }
    }

  }
}

NativeType!( u8,    i8,  to_u8,    8);
NativeType!(u16,   i16,  to_u16,  16);
NativeType!(u32,   i32,  to_u32,  32);
NativeType!(u64,   i64,  to_u64,  64);
NativeType!(u128, i128, to_u128, 128);




#[cfg(test)]
pub mod test {

use rand::prelude::*;
use crate::native::*;

pub fn wrapping_pow_u64_ref(mut base: u8, mut exp: usize) -> u8 {
    let mut result: u8 = 1;

    while exp > 0 {
        if exp & 1 == 1 {
            result = result.wrapping_mul(base);
        }
        exp >>= 1;
        base = base.wrapping_mul(base);
    }

    result
}

#[test]
fn pow_ok() {
  let mut rng = rand::thread_rng();
  for _i in 0 .. 1000000 {
      // Get random inputs with random bit widths, so we test small inputs like 0/1 instead of
      // only large ones.
      let base = rng.gen::<u8>() >> rng.gen_range(0 .. 8);
      let exp = rng.gen::<usize>() >> rng.gen_range(0 .. 64);
      assert_eq!(u8::exp_usize(base,exp), wrapping_pow_u64_ref(base, exp),
          "base = {base}, exp = {exp}");
  }
}

}
