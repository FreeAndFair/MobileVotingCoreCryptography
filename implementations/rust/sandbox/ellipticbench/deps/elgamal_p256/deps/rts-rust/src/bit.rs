use std::fmt;

use crate::traits::*;
use crate::display::*;
use crate::PrimType;

PrimType!(bool);

impl<const BASE: usize, const UPPER: bool> Base<BASE, UPPER> for bool {
  fn format(&self, fmt: &mut fmt::Formatter) -> fmt::Result {
    write!(fmt, "{}", if *self { "True" } else { "False" })
  }
}

crate::default_base!(10,bool);

impl Zero for bool {
  fn zero(_:Self::Length) -> Self { false }
}

impl Logic for bool {
  fn complement(x: Self::Arg<'_>) -> Self { !x }
  fn xor(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self { x ^ y }
  fn and(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self { x & y }
  fn or (x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self { x | y }
}

impl Eq for bool {
    fn eq(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool { x == y }
}

impl Cmp for bool {
    fn lt(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool { x < y }
    fn gt(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool { x > y }
    fn le(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool { x <= y }
    fn ge(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool { x >= y }
}

impl Literal for bool {
  fn number_uint(_n: Self::Length, x: &num::BigUint) -> Self {
    !<num::BigUint as num::Zero>::is_zero(x)
  }
  fn number_usize(_n: Self::Length, x: usize) -> Self {
    x != 0
  }
}
