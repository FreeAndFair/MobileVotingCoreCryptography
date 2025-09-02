use crate::traits::*;
use crate::RefType;
use num::pow::Pow;
use num::Integer;

#[cfg(feature = "proptest_strategies")]
use num_bigint::Sign;
#[cfg(feature = "proptest_strategies")]
use proptest::prelude::*;

RefType!(num::BigInt);

impl Zero for num::BigInt {
  fn zero(_ : ()) -> Self { <Self as num::Zero>::zero() }
}

impl Literal for num::BigInt {
  fn number_usize(_: (), x: usize)       -> Self { Self::from(x) }
  fn number_uint(_: (), x: &num::BigUint) -> Self {
    Self::from(x.clone())
  }
}

impl Integral for num::BigInt {

  fn to_usize(x: &Self) -> usize {
    assert!(x.sign() != num::bigint::Sign::Minus);
    let mut it = x.iter_u64_digits();
    let mut res: u64 = 0;
    match it.next() {
      None => return res as usize,
      Some(x) => res = x
    };
    if let Some(_) = it.next() { assert!(false) }
    res as usize
  }

  #[inline(always)]
  fn to_usize_maybe(x: &Self) -> Option<usize> {
    let max = usize::MAX.into();
    if x <= &max { Some(Self::to_usize(x)) } else { None }
  }

  fn to_integer(x: &Self)       -> num::BigInt { x.clone() }

  // Note that Rust's `/` and `%` truncate toward zero,
  // and Cryptol truncates toward -inf, which is why
  // we use `div_floor` and `mod_floor` instead.
  fn div   (x: &Self, y: &Self) -> Self        { x.div_floor(y) }
  fn modulo(x: &Self, y: &Self) -> Self        { x.mod_floor(y) }
}

impl Ring for num::BigInt {
  fn negate      (x: &Self)           -> Self { -x }
  fn add         (x: &Self, y: &Self) -> Self { x + y }
  fn mul         (x: &Self, y: &Self) -> Self { x * y }
  fn sub         (x: &Self, y: &Self) -> Self { x - y }
  fn exp_usize   (x: &Self, y: usize) -> Self {
    <Self as Pow<usize>>::pow(x.clone(), y)
  }
  fn exp_uint    (x: &Self, y: &num::BigUint) -> Self {
    <Self as Pow<&num::BigUint>>::pow(x.clone(), y)
  }
  fn from_integer(_: Self::Length, x: &num::BigInt)    -> Self { x.clone() }
}

impl Eq for num::BigInt {
    fn eq(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool { x == y }
}

impl Cmp for num::BigInt {
    fn lt(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool { x < y }
    fn gt(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool { x > y }
    fn le(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool { x <= y }
    fn ge(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool { x >= y }
}

crate::derive_display!(num::BigUint);
crate::derive_display!(num::BigInt);
crate::default_base!(10,num::BigUint);
crate::default_base!(10,num::BigInt);

#[cfg(feature = "proptest_strategies")]
pub fn any_integer() -> impl Strategy<Value = num::BigInt> {
    any::<bool>().prop_flat_map(|positive| {
        let sign = if positive { Sign::Plus } else { Sign::Minus };
        any::<Vec<u32>>().prop_map(move |vec|
            num::BigInt::new(sign, vec))
    })
}
