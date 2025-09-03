use crate::traits::*;
use crate::type_traits::*;
use num::bigint::ToBigInt;
use num::traits::Euclid;
use std::fmt;

#[cfg(feature = "proptest_strategies")]
use crate::int::any_integer;
#[cfg(feature = "proptest_strategies")]
use proptest::prelude::*;

/// The Rust counterpart to Cryptol's `Z` type. This is "dynamically typed"
/// in the sense that the modulus is not encoded at the type level, but rather
/// at the value level (the [`modulus`] field). As such, a [`Z`] value is
/// expected to obey the following invariants:
///
/// 1. The [`remainder`] field should be a non-negative number that is less than
///    the value of [`modulus`].
///
/// 2. The [`modulus`] field should be greater than or equal to 1.
///
/// 3. A [`Z`] value of a particular [`modulus`] should only be used as an
///    argument to a binary operation if the other [`Z`] value has the same
///    [`modulus`].
#[derive(Clone)]
pub struct Z {
    pub remainder: num::BigInt,
    pub modulus: num::BigUint,
}

impl Z {
    /// Check that two [`Z`] values have the same [`modulus`]. If this is not
    /// the case, panic. This checks invariant (3) above.
    fn assert_equal_moduli(z1: &Z, z2: &Z) {
        assert!(
            z1.modulus == z2.modulus,
            "Mismatched moduli in Z operation
                 First  operand is {:?} : Z {:?}
                 Second operand is {:?} : Z {:?}",
            z1.remainder,
            z1.modulus,
            z2.remainder,
            z2.modulus
        );
    }

    /// Raise the [`Z`] value to the given power. This leverages
    /// [`num::BigUint::modpow`] to ensure that the implementation uses
    /// efficient modular exponentiation.
    fn pow(&self, exponent: &num::BigInt) -> Z {
        let modulus_int: &num::BigInt = &self.modulus.to_bigint().unwrap();
        // NB: We construct a `Z` value directly here instead of using
        // `with_rem`. We don't need to check invariant (1) above because
        // `num::BigInt::modpow`'s postconditions imply invariant (1).
        Z {
            // NB: This checks that the exponent is non-negative and panics if
            // it is negative, so we needn't check this ourselves.
            remainder: self.remainder.modpow(exponent, modulus_int),
            modulus: self.modulus.clone(),
        }
    }

    /// Construct a [`Z`] value from a remainder and a modulus.
    fn from_rem_mod(remainder: num::BigInt, modulus: num::BigUint) -> Z {
        // Check invariant (2) above
        assert!(
            modulus >= num::traits::One::one(),
            "Modulus value cannot be 0"
        );
        Z {
            // Ensure invariant (1) above
            remainder: remainder.rem_euclid(&modulus.to_bigint().unwrap()),
            modulus,
        }
    }

    /// Converts an integer modulo n to an unbounded integer in the range 0 to n-1.
    ///
    /// ```cryptol
    /// {n} (fin n, n >= 1) => Z n -> Integer
    /// ```
    pub fn from_z(&self) -> num::BigInt {
        self.remainder.clone()
    }

    /// Given a [`Z`] value, construct a new [`Z`] value with the supplied
    /// remainder value, but the same [`modulus`].
    fn with_rem(&self, remainder: num::BigInt) -> Z {
        Self::from_rem_mod(remainder, self.modulus.clone())
    }
}

impl Type for Z {
    type Length = num::BigUint;
    type Arg<'a> = &'a Self;

    fn as_arg(&self) -> Self::Arg<'_> {
        self
    }
}

impl CloneArg for &Z {
    type Owned = Z;

    fn clone_arg(self) -> Z {
        self.clone()
    }
}

impl fmt::Binary for Z {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        self.remainder.fmt(f)
    }
}

impl fmt::Octal for Z {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        self.remainder.fmt(f)
    }
}

impl fmt::LowerHex for Z {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        self.remainder.fmt(f)
    }
}

impl fmt::UpperHex for Z {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        self.remainder.fmt(f)
    }
}

impl fmt::Display for Z {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        self.remainder.fmt(f)
    }
}

impl fmt::Debug for Z {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        self.remainder.fmt(f)
    }
}

crate::derive_display!(Z);
crate::default_base!(10, Z);

impl Zero for Z {
    fn zero(n: num::BigUint) -> Self {
        Self::from_rem_mod(num::traits::Zero::zero(), n)
    }
}

impl Literal for Z {
    fn number_usize(n: num::BigUint, x: usize) -> Self {
        Self::from_rem_mod(x.to_bigint().unwrap(), n)
    }

    fn number_uint(n: num::BigUint, x: &num::BigUint) -> Self {
        Self::from_rem_mod(x.to_bigint().unwrap(), n)
    }
}

impl Logic for Z {
    fn complement(x: Self::Arg<'_>) -> Self {
        x.with_rem(!x.remainder.clone())
    }

    fn xor(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
        Self::assert_equal_moduli(x, y);
        x.with_rem(x.remainder.clone() ^ y.remainder.clone())
    }

    fn and(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
        Self::assert_equal_moduli(x, y);
        x.with_rem(x.remainder.clone() & y.remainder.clone())
    }

    fn or(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
        Self::assert_equal_moduli(x, y);
        x.with_rem(x.remainder.clone() | y.remainder.clone())
    }
}

impl Ring for Z {
    fn negate(x: Self::Arg<'_>) -> Self {
        x.with_rem(-x.remainder.clone())
    }

    fn mul(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
        Self::assert_equal_moduli(x, y);
        x.with_rem(x.remainder.clone() * y.remainder.clone())
    }

    fn sub(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
        Self::assert_equal_moduli(x, y);
        x.with_rem(x.remainder.clone() - y.remainder.clone())
    }

    fn add(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
        x.with_rem(x.remainder.clone() + y.remainder.clone())
    }

    fn from_integer(bits: num::BigUint, x: &num::BigInt) -> Self {
        Self::from_rem_mod(x.clone(), bits)
    }

    fn exp_usize(x: Self::Arg<'_>, y: usize) -> Self {
        // When performing exponentiation on a Z value, we choose between two
        // algorithms:
        //
        // (1) A naïve algorithm that performs the exponentiation on the Z
        //     value's remainder and then reduces it by the modulus.
        //
        // (2) A modular exponentiation algorithm that performs squaring
        //     multiplication on the remainder, reducing by the modulus at each
        //     step.
        //
        // Algorithm (2) is more space-efficient, but it has higher constant
        // factors, due in part to the need to represent the exponent as a
        // BigInt. As such, we opt for algorithm (1) for small exponents,
        // falling back to algorithm (2) if the exponent is sufficiently large.
        match u32::try_from(y) {
            // Algorithm (1)
            //
            // NB: We pick the size of a `u32` as the threshold for whether the
            // exponent is considered small or large. This is because the `pow`
            // function for Rust's primitive integer types takes a `u32` as an
            // exponent, so it is a decent measuring stick for whether algorithm
            // (1) will be more efficient than algorithm (2).
            Ok(y_u32) => x.with_rem(x.remainder.clone().pow(y_u32)),
            // Algorithm (2)
            Err(_) => {
                let y_int: &num::BigInt = &y.into();
                x.pow(y_int)
            }
        }
    }

    fn exp_uint(x: Self::Arg<'_>, y: &num::BigUint) -> Self {
        let y_int: &num::BigInt = &y.to_bigint().unwrap();
        x.pow(y_int)
    }
}

impl Field for Z {
    // TODO: Check that the modulus is prime (#49)
    fn recip(x: Self::Arg<'_>) -> Self {
        match x.remainder.modinv(&x.modulus.to_bigint().unwrap()) {
            Some(r) => x.with_rem(r),
            None => panic!("division by 0"),
        }
    }

    // TODO: Check that the modulus is prime (#49)
    fn field_div(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
        Self::assert_equal_moduli(x, y);
        Self::mul(x.as_arg(), Self::recip(y).as_arg())
    }
}

impl Eq for Z {
    fn eq(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
        Self::assert_equal_moduli(x, y);
        <num::BigInt as Eq>::eq(&x.remainder, &y.remainder)
    }
}

impl Cmp for Z {
    fn lt(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
        Self::assert_equal_moduli(x, y);
        <num::BigInt as Cmp>::lt(&x.remainder, &y.remainder)
    }

    fn gt(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
        Self::assert_equal_moduli(x, y);
        <num::BigInt as Cmp>::gt(&x.remainder, &y.remainder)
    }

    fn le(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
        Self::assert_equal_moduli(x, y);
        <num::BigInt as Cmp>::le(&x.remainder, &y.remainder)
    }

    fn ge(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
        Self::assert_equal_moduli(x, y);
        <num::BigInt as Cmp>::ge(&x.remainder, &y.remainder)
    }
}

#[cfg(feature = "proptest_strategies")]
pub fn any_z(modulus: num::BigUint) -> impl Strategy<Value = Z> {
    any_integer().prop_map(move |i| Z::from_rem_mod(i, modulus.clone()))
}
