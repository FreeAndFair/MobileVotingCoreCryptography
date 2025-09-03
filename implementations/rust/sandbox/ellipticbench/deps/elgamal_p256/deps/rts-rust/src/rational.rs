use crate::RefType;
use crate::display::Base;
use crate::traits::*;
use core::cmp::Ordering;
use num::Integer;
use num::Signed;
use num::bigint::ToBigInt;
use num::pow::Pow;
use std::fmt;

#[cfg(feature = "proptest_strategies")]
use crate::int::any_integer;
#[cfg(feature = "proptest_strategies")]
use proptest::prelude::*;

RefType!(num::BigRational);

impl Zero for num::BigRational {
    fn zero(_: ()) -> Self {
        <Self as num::Zero>::zero()
    }
}

impl Literal for num::BigRational {
    fn number_usize(_: (), x: usize) -> Self {
        Self::from(num::BigInt::from(x))
    }

    fn number_uint(_: (), x: &num::BigUint) -> Self {
        Self::from(x.to_bigint().unwrap())
    }
}

impl FLiteral for num::BigRational {
    fn fraction_usize(_: (), m: usize, n: usize) -> Self {
        num::BigRational::new(num::BigInt::from(m), num::BigInt::from(n))
    }

    fn fraction_uint(_: (), m: &num::BigUint, n: &num::BigUint) -> Self {
        num::BigRational::new(m.to_bigint().unwrap(), n.to_bigint().unwrap())
    }
}

impl Ring for num::BigRational {
    fn negate(x: &Self) -> Self {
        -x
    }
    fn add(x: &Self, y: &Self) -> Self {
        x + y
    }
    fn mul(x: &Self, y: &Self) -> Self {
        x * y
    }
    fn sub(x: &Self, y: &Self) -> Self {
        x - y
    }

    fn exp_usize(x: &Self, y: usize) -> Self {
        <Self as Pow<usize>>::pow(x.clone(), y)
    }

    fn exp_uint(x: &Self, y: &num::BigUint) -> Self {
        <Self as Pow<&num::BigUint>>::pow(x.clone(), y)
    }

    fn from_integer(_: Self::Length, x: &num::BigInt) -> Self {
        Self::from(x.clone())
    }
}

impl Field for num::BigRational {
    fn recip(x: Self::Arg<'_>) -> Self {
        x.recip()
    }

    fn field_div(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
        x / y
    }
}

impl Eq for num::BigRational {
    fn eq(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
        x == y
    }
}

impl Cmp for num::BigRational {
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

impl Round for num::BigRational {
    fn ceiling(x: Self::Arg<'_>) -> num::BigInt {
        x.ceil().numer().clone()
    }

    fn floor(x: Self::Arg<'_>) -> num::BigInt {
        x.floor().numer().clone()
    }

    fn trunc(x: Self::Arg<'_>) -> num::BigInt {
        x.trunc().numer().clone()
    }

    fn round_away(x: Self::Arg<'_>) -> num::BigInt {
        x.round().numer().clone()
    }

    fn round_to_even(r: Self::Arg<'_>) -> num::BigInt {
        let n: num::BigInt = r.trunc().numer().clone();
        let f: num::BigRational = r.fract();

        let one: num::BigInt = 1u64.into();
        let point_five: num::BigRational = Self::from_float(0.5).unwrap();

        let x: num::BigInt = if r.clone() < Self::from_integer(0u64.into()) {
            -one
        } else {
            one
        };

        match f.abs().cmp(&point_five) {
            Ordering::Less => n,
            Ordering::Equal => {
                if n.is_even() {
                    n
                } else {
                    n + x
                }
            }
            Ordering::Greater => n + x,
        }
    }
}

crate::default_base!(10, num::BigRational);

// BigRational already has impls for Binary et al., but these impls format
// BigRationals as `1/2`. The Cryptol REPL, on the other hand, formats them as
// `(ratio 1 2)`. To achieve formatting closer to what the Cryptol REPL uses, we
// define Base impls that avoid calling BigRational's impls for Binary et al.

impl<const UPPER: bool> Base<2, UPPER> for num::BigRational {
    fn format(&self, fmt: &mut fmt::Formatter) -> fmt::Result {
        write!(fmt, "(ratio {:b} {:b})", self.numer(), self.denom())
    }
}

impl<const UPPER: bool> Base<8, UPPER> for num::BigRational {
    fn format(&self, fmt: &mut fmt::Formatter) -> fmt::Result {
        write!(fmt, "(ratio {:o} {:o})", self.numer(), self.denom())
    }
}

impl<const UPPER: bool> Base<10, UPPER> for num::BigRational {
    fn format(&self, fmt: &mut fmt::Formatter) -> fmt::Result {
        write!(fmt, "(ratio {} {})", self.numer(), self.denom())
    }
}

impl Base<16, true> for num::BigRational {
    fn format(&self, fmt: &mut fmt::Formatter) -> fmt::Result {
        write!(fmt, "(ratio {:X} {:X})", self.numer(), self.denom())
    }
}

impl Base<16, false> for num::BigRational {
    fn format(&self, fmt: &mut fmt::Formatter) -> fmt::Result {
        write!(fmt, "(ratio {:x} {:x})", self.numer(), self.denom())
    }
}

/// Compute the ratio of two integers as a rational.
/// This function will panic if `denom` is 0.
pub fn ratio(numer: &num::BigInt, denom: &num::BigInt) -> num::BigRational {
    num::BigRational::new(numer.clone(), denom.clone())
}

#[cfg(feature = "proptest_strategies")]
pub fn any_rational() -> impl Strategy<Value = num::BigRational> {
    any_integer().prop_flat_map(|numer| {
        any_integer()
            .prop_filter("The denominator must be non-zero", |denom| {
                *denom != num::zero::<num::BigInt>()
            })
            .prop_map(move |denom| num::BigRational::new(numer.clone(), denom))
    })
}
