use crate::type_traits::*;

pub trait Zero: Type {

  /// The value tha acts like 0.
  fn zero(n : Self::Length) -> Self;
}

// We reuse Rust's Eq and Ord for equality

pub trait Logic: Zero {
  fn complement(x: Self::Arg<'_>) -> Self;
  fn xor(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self;
  fn and(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self;
  fn or (x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self;
}


pub trait Ring: Zero {

  /// Negate a value
  fn negate(x: Self::Arg<'_>) -> Self;

  /// x * y
  fn mul(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self;

  /// x - y
  fn sub(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self;

  /// x + y
  fn add(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self;

  /// Convert an integer to a value of the given type.
  /// Produces a result even if the type does not fit
  /// (e.g., wrap around for bit types)
  fn from_integer(n: Self::Length, x: &num::BigInt) -> Self;

  /// Raise `x` to the `y` power, where `y` is small enough to fit into a
  /// `usize`.
  fn exp_usize(x: Self::Arg<'_>, y: usize) -> Self;

  /// Raise `x` to the `y` power, where `y` can be a large number.
  fn exp_uint(x: Self::Arg<'_>, y: &num::BigUint) -> Self;
}

/// Raise `x` to the `y` power. It is an error to raise a value to a negative
/// integer exponent.
pub fn exp<T: Ring, I: Integral>(x: T::Arg<'_>, y: I::Arg<'_>) -> T {
    match <I as Integral>::to_usize_maybe(y) {
        Some(y) => <T as Ring>::exp_usize(x, y),
        None =>
            match <I as Integral>::to_integer(y).to_biguint() {
                Some(y) => <T as Ring>::exp_uint(x, &y),
                None => panic!("exp: negative exponent"),
            }
    }
}


pub trait Integral: Ring {

  /// Convert a value to a `usize`. If the value cannot fit in a `usize`, the
  /// behavior of this function is unspecified.
  ///
  /// This is not a standard Cryptol primitive, but we use it
  /// in places where `Integral` is used for indexing into things.
  fn to_usize(x: Self::Arg<'_>) -> usize;

  /// A variant of [`to_usize`] that returns a [`Some`] value if the argument
  /// can fit in a `usize` and `None` otherwise. It is recommended that
  /// implementations of this method be marked with `#[inline(always)]` to make
  /// it more likely that the intermediate `Option` value can be optimized away.
  fn to_usize_maybe(x: Self::Arg<'_>) -> Option<usize>;

  /// Convert something to an integer.
  fn to_integer(x: Self::Arg<'_>) -> num::BigInt;

  /// Integral division
  fn div(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self;

  /// Modulo
  fn modulo(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self;
}

pub trait Field: Ring {
    /// Compute the multiplicative inverse of an element of a field.
    /// Taking the reciprocal of 0 will raise an error.
    fn recip(x: Self::Arg<'_>) -> Self;

    /// x /. y
    ///
    /// Dividing by 0 will raise an error.
    fn field_div(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self;
}


pub trait Eq: Type {
    /// x == y
    fn eq(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool;

    /// x != y
    fn ne(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
        !Self::eq(x, y)
    }
}

pub trait Cmp: Eq {
    /// x < y
    fn lt(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool;

    /// x > y
    fn gt(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool;

    /// x <= y
    fn le(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool;

    /// x >= y
    fn ge(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool;
}

pub trait SignedCmp: Cmp {
    /// x <$ y
    fn signed_lt(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool;
}


pub trait Round: Cmp + Field {
    /// Ceiling function.
    ///
    /// Given `x`, compute the smallest integer `i`
    /// such that `x <= i`.
    fn ceiling(x: Self::Arg<'_>) -> num::BigInt;

    /// Floor function.
    ///
    /// Given `x`, compute the largest integer `i`
    /// such that `i <= x`.
    fn floor(x: Self::Arg<'_>) -> num::BigInt;

    /// Truncate the value toward 0.
    ///
    /// Given `x` compute the nearest integer between
    /// `x` and 0.  For nonnegative `x`, this is floor,
    /// and for negative `x` this is ceiling.
    fn trunc(x: Self::Arg<'_>) -> num::BigInt;

    /// Round to the nearest integer, ties away from 0.
    ///
    /// Ties are broken away from 0.  For nonnegative `x`
    /// this is `floor(x + 0.5)`.  For negative `x` this
    /// is `ceiling(x - 0.5)`.
    fn round_away(x: Self::Arg<'_>) -> num::BigInt;

    /// Round to the nearest integer, ties to even.
    ///
    /// Ties are broken to the nearest even integer.
    fn round_to_even(x: Self::Arg<'_>) -> num::BigInt;
}


pub trait Literal: Type {
  fn number_usize(n: Self::Length, x: usize) -> Self;
  fn number_uint(n: Self::Length, x: &num::BigUint) -> Self;
}

pub trait LiteralNumber<T> : Literal {
  fn number(n: Self::Length, x:T) -> Self;
}

impl<T : Literal> LiteralNumber<usize> for T {
  fn number(n: Self::Length, x:usize) -> Self { Self::number_usize(n,x) }
}

impl<T : Literal> LiteralNumber<&num::BigUint> for T {
  fn number(n: Self::Length, x:&num::BigUint) -> Self { Self::number_uint(n,x) }
}

pub trait FLiteral: Type {
    /// A fractional literal corresponding to `m/n`, where `m` and `n` are both
    /// small enough to fix in a `usize`.
    fn fraction_usize(l: Self::Length, m: usize, n: usize) -> Self;

    /// A fractional literal corresponding to `m/n`, where `m` and `n` can be
    /// large numbers.
    fn fraction_uint(l: Self::Length, m: &num::BigUint, n: &num::BigUint) -> Self;
}

pub trait FLiteralNumber<T>: FLiteral {
    /// A fractional literal corresponding to `m/n`.
    fn fraction(l: Self::Length, m: T, n: T) -> Self;
}

impl<T: FLiteral> FLiteralNumber<usize> for T {
    fn fraction(l: Self::Length, m: usize, n: usize) -> Self {
        Self::fraction_usize(l, m, n)
    }
}

impl<T: FLiteral> FLiteralNumber<&num::BigUint> for T {
    fn fraction(l: Self::Length, m: &num::BigUint, n: &num::BigUint) -> Self {
        Self::fraction_uint(l, m, n)
    }
}
