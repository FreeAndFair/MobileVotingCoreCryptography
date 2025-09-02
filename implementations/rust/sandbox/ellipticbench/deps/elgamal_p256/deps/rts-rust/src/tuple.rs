use crate::traits::*;
use crate::type_traits::*;
use crate::display::*;
use crate::PrimType;
use std::fmt;

/// `tuple_update!(tup, n, val)` takes a tuple value `tup`, an index `n`, and a
/// an expression `val` and returns a new tuple consisting of the elements of
/// `tup`, but with the element at index `n` replaced with `val`.
///
/// The compiler uses this macro as part of compiling Cryptol tuple and record
/// updates to Rust.
#[macro_export]
macro_rules! tuple_update {
    ($tup: expr, $n: tt, $val: expr) => {
        { let mut new_tup = $tup;
          new_tup.$n = $val;
          new_tup
        }
    }
}

/* 0 */

// Unlike other tuples, empty tuple arguments are always passed by value (Copy)
// in all contexts. As such, we define the `Type` and `CloneArg` instances for
// empty tuples like we do other primitive types.
PrimType!(());

impl<const BASE: usize, const UPPER: bool> Base<BASE, UPPER> for () {
  fn format(&self, fmt: &mut fmt::Formatter) -> fmt::Result {
    write!(fmt, "()")
  }
}

crate::default_base!(10,());

impl Eq for () {
    fn eq(_x: Self::Arg<'_>, _y: Self::Arg<'_>) -> bool {
        true
    }
}

impl Cmp for () {
    fn lt(_x: Self::Arg<'_>, _y: Self::Arg<'_>) -> bool {
        false
    }

    fn gt(_x: Self::Arg<'_>, _y: Self::Arg<'_>) -> bool {
        false
    }

    fn le(_x: Self::Arg<'_>, _y: Self::Arg<'_>) -> bool {
        true
    }

    fn ge(_x: Self::Arg<'_>, _y: Self::Arg<'_>) -> bool {
        true
    }
}

impl SignedCmp for () {
    fn signed_lt(_x: Self::Arg<'_>, _y: Self::Arg<'_>) -> bool {
        false
    }
}

impl Zero for () {
    fn zero(_n: Self::Length) -> Self {
        ()
    }
}

impl Logic for () {
    fn complement(_x: Self::Arg<'_>) -> Self {
        ()
    }

    fn xor(_x: Self::Arg<'_>, _y: Self::Arg<'_>) -> Self {
        ()
    }

    fn and(_x: Self::Arg<'_>, _y: Self::Arg<'_>) -> Self {
        ()
    }

    fn or (_x: Self::Arg<'_>, _y: Self::Arg<'_>) -> Self {
        ()
    }
}

impl Ring for () {
    fn negate(_x: Self::Arg<'_>) -> Self {
        ()
    }

    fn mul(_x: Self::Arg<'_>, _y: Self::Arg<'_>) -> Self {
        ()
    }

    fn sub(_x: Self::Arg<'_>, _y: Self::Arg<'_>) -> Self {
        ()
    }

    fn add(_x: Self::Arg<'_>, _y: Self::Arg<'_>) -> Self {
        ()
    }

    fn from_integer(_n: Self::Length, _x: &num::BigInt) -> Self {
        ()
    }

    fn exp_usize(_x: Self::Arg<'_>, _y: usize) -> Self {
        ()
    }

    fn exp_uint(_x: Self::Arg<'_>, _y: &num::BigUint) -> Self {
        ()
    }
}

/* 1 */

// We define impls for 1-tuples both for the sake of consistent with other tuple
// types and to support Cryptol records with a single field, which are compiled
// into Rust 1-tuples.

impl<A: Type> Type for (A,) {
    type Arg<'a> = &'a (A,) where Self: 'a;
    type Length = (A::Length,);

    fn as_arg(&self) -> Self::Arg<'_> { self }
}

impl<A: Type> CloneArg for &(A,) {
    type Owned = (A,);

    fn clone_arg(self) -> Self::Owned { self.clone() }
}

impl<const BASE: usize, const UPPER: bool, A: Base<BASE, UPPER>>
    Base<BASE, UPPER> for (A,) {

    fn format(&self, fmt: &mut fmt::Formatter) -> fmt::Result {
        write!(fmt, "(")?;
        Base::<BASE,UPPER>::format(&self.0, fmt)?;
        write!(fmt, ")")
    }
}

impl <A: DefaultBase> DefaultBase for (A,) {
    fn format(&self, fmt: &mut fmt::Formatter) -> fmt::Result {
        write!(fmt, "(")?;
        DefaultBase::format(&self.0, fmt)?;
        write!(fmt, ")")
    }
}

impl<A: Eq> Eq for (A,) {
    fn eq(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
        A::eq(x.0.as_arg(), y.0.as_arg())
    }
}

impl<A: Cmp> Cmp for (A,) {
    fn lt(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
        A::lt(x.0.as_arg(), y.0.as_arg())
    }

    fn gt(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
        A::gt(x.0.as_arg(), y.0.as_arg())
    }

    fn le(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
        A::le(x.0.as_arg(), y.0.as_arg())
    }

    fn ge(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
        A::ge(x.0.as_arg(), y.0.as_arg())
    }
}

impl<A: SignedCmp> SignedCmp for (A,) {
    fn signed_lt(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
        A::signed_lt(x.0.as_arg(), y.0.as_arg())
    }
}

impl<A: Zero> Zero for (A,) {
    fn zero(n: Self::Length) -> Self {
        (A::zero(n.0),)
    }
}

impl<A: Logic> Logic for (A,) {
    fn complement(x: Self::Arg<'_>) -> Self {
        (A::complement(x.0.as_arg()),)
    }

    fn xor(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
        (A::xor(x.0.as_arg(), y.0.as_arg()),)
    }

    fn and(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
        (A::and(x.0.as_arg(), y.0.as_arg()),)
    }

    fn or (x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
        (A::or(x.0.as_arg(), y.0.as_arg()),)
    }
}

impl<A: Ring> Ring for (A,) {
    fn negate(x: Self::Arg<'_>) -> Self {
        (A::negate(x.0.as_arg()),)
    }

    fn mul(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
        (A::mul(x.0.as_arg(), y.0.as_arg()),)
    }

    fn sub(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
        (A::sub(x.0.as_arg(), y.0.as_arg()),)
    }

    fn add(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
        (A::add(x.0.as_arg(), y.0.as_arg()),)
    }

    fn from_integer(n: Self::Length, x: &num::BigInt) -> Self {
        (A::from_integer(n.0, x),)
    }

    fn exp_usize(x: Self::Arg<'_>, y: usize) -> Self {
        (A::exp_usize(x.0.as_arg(), y),)
    }

    fn exp_uint(x: Self::Arg<'_>, y: &num::BigUint) -> Self {
        (A::exp_uint(x.0.as_arg(), y),)
    }
}

// Helper macros used below in tuple_type!

macro_rules! fmt_tup {
  ($f: expr, $x: expr, $fmt: expr, $($t:ident),*) => {
    {
      write!($fmt,"(")?;
      let mut is_first = true;

      #[allow(bad_style)]
      let ($($t),*) = $x;

      $(
        if is_first { is_first = false } else { write!($fmt,",")? };
        $f($t,$fmt)?;
      )*

      write!($fmt,")")
    }
  }
}

macro_rules! eq_def {
    ($x:ident $y:ident) =>
        { compile_error!("No tuple fields supplied"); };
    ($x:ident $y:ident $idx:tt $t:ident) =>
        { $t::eq($x.$idx.as_arg(), $y.$idx.as_arg()) };
    ($x:ident $y:ident $idx:tt $t:ident, $($idxs:tt $ts:ident),+) =>
        { $t::eq($x.$idx.as_arg(), $y.$idx.as_arg()) && eq_def!($x $y $($idxs $ts),*) };
}

macro_rules! ne_def {
    ($x:ident $y:ident) =>
        { compile_error!("No tuple fields supplied"); };
    ($x:ident $y:ident $idx:tt $t:ident) =>
        { $t::ne($x.$idx.as_arg(), $y.$idx.as_arg()) };
    ($x:ident $y:ident $idx:tt $t:ident, $($idxs:tt $ts:ident),+) =>
        { $t::ne($x.$idx.as_arg(), $y.$idx.as_arg()) || eq_def!($x $y $($idxs $ts),*) };
}

macro_rules! lt_def {
    ($x:ident $y:ident) =>
        { compile_error!("No tuple fields supplied"); };
    ($x:ident $y:ident $idx:tt $t:ident) =>
        { $t::lt($x.$idx.as_arg(), $y.$idx.as_arg()) };
    ($x:ident $y:ident $idx:tt $t:ident, $($idxs:tt $ts:ident),+) =>
        {
            if $t::eq($x.$idx.as_arg(), $y.$idx.as_arg()) {
                lt_def!($x $y $($idxs $ts),*)
            } else {
                $t::lt($x.$idx.as_arg(), $y.$idx.as_arg())
            }
        };
}

macro_rules! gt_def {
    ($x:ident $y:ident) =>
        { compile_error!("No tuple fields supplied"); };
    ($x:ident $y:ident $idx:tt $t:ident) =>
        { $t::gt($x.$idx.as_arg(), $y.$idx.as_arg()) };
    ($x:ident $y:ident $idx:tt $t:ident, $($idxs:tt $ts:ident),+) =>
        {
            if $t::eq($x.$idx.as_arg(), $y.$idx.as_arg()) {
                gt_def!($x $y $($idxs $ts),*)
            } else {
                $t::gt($x.$idx.as_arg(), $y.$idx.as_arg())
            }
        };
}

macro_rules! le_def {
    ($x:ident $y:ident) =>
        { compile_error!("No tuple fields supplied"); };
    ($x:ident $y:ident $idx:tt $t:ident) =>
        { $t::le($x.$idx.as_arg(), $y.$idx.as_arg()) };
    ($x:ident $y:ident $idx:tt $t:ident, $($idxs:tt $ts:ident),+) =>
        {
            if $t::eq($x.$idx.as_arg(), $y.$idx.as_arg()) {
                le_def!($x $y $($idxs $ts),*)
            } else {
                $t::le($x.$idx.as_arg(), $y.$idx.as_arg())
            }
        };
}

macro_rules! ge_def {
    ($x:ident $y:ident) =>
        { compile_error!("No tuple fields supplied"); };
    ($x:ident $y:ident $idx:tt $t:ident) =>
        { $t::ge($x.$idx.as_arg(), $y.$idx.as_arg()) };
    ($x:ident $y:ident $idx:tt $t:ident, $($idxs:tt $ts:ident),+) =>
        {
            if $t::eq($x.$idx.as_arg(), $y.$idx.as_arg()) {
                ge_def!($x $y $($idxs $ts),*)
            } else {
                $t::ge($x.$idx.as_arg(), $y.$idx.as_arg())
            }
        };
}

macro_rules! signed_lt_def {
    ($x:ident $y:ident) =>
        { compile_error!("No tuple fields supplied"); };
    ($x:ident $y:ident $idx:tt $t:ident) =>
        { $t::signed_lt($x.$idx.as_arg(), $y.$idx.as_arg()) };
    ($x:ident $y:ident $idx:tt $t:ident, $($idxs:tt $ts:ident),+) =>
        {
            if $t::eq($x.$idx.as_arg(), $y.$idx.as_arg()) {
                lt_def!($x $y $($idxs $ts),*)
            } else {
                $t::signed_lt($x.$idx.as_arg(), $y.$idx.as_arg())
            }
        };
}

#[macro_export]
macro_rules! tuple_type {
  ($($idx:tt $t:ident),*) => {

    impl<$($t: Type),*> Type for ($($t),*) {
      type Arg<'a> = &'a ($($t),*) where Self: 'a;
      type Length = ($(<$t>::Length),*);
      fn as_arg(&self) -> Self::Arg<'_> { self }
    }

    impl<$($t: Type),*> CloneArg for &($($t),*) {
      type Owned = ($($t),*);
      fn clone_arg(self) -> Self::Owned { self.clone() }
    }

    impl<const BASE: usize, const UPPER: bool, $($t),*>
      Base<BASE, UPPER> for ($($t),*)
      where $($t: Base<BASE, UPPER>),* {

      #[allow(unused)]
      fn format(&self, fmt: &mut fmt::Formatter) -> fmt::Result {
        fmt_tup!(Base::<BASE,UPPER>::format,self,fmt, $($t),*)
      }
   }

    impl <$($t),*> DefaultBase for ($($t),*)
      where $($t: DefaultBase),* {
      #[allow(unused)]
      fn format(&self, fmt: &mut fmt::Formatter) -> fmt::Result {
        fmt_tup!(DefaultBase::format,self,fmt, $($t),*)
      }
    }

    impl<$($t: Eq),*> Eq for ($($t),*) {
        fn eq(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
            eq_def!(x y $($idx $t),*)
        }

        fn ne(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
            ne_def!(x y $($idx $t),*)
        }
    }

    impl<$($t: Cmp),*> Cmp for ($($t),*) {
        fn lt(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
            lt_def!(x y $($idx $t),*)
        }

        fn gt(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
            gt_def!(x y $($idx $t),*)
        }

        fn le(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
            le_def!(x y $($idx $t),*)
        }

        fn ge(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
            ge_def!(x y $($idx $t),*)
        }
    }

    impl<$($t: SignedCmp),*> SignedCmp for ($($t),*) {
        fn signed_lt(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
            signed_lt_def!(x y $($idx $t),*)
        }
    }

    impl<$($t: Zero),*> Zero for ($($t),*) {
        fn zero(n: Self::Length) -> Self {
            ($($t::zero(n.$idx)),*)
        }
    }

    impl<$($t: Logic),*> Logic for ($($t),*) {
        fn complement(x: Self::Arg<'_>) -> Self {
            ($($t::complement(x.$idx.as_arg())),*)
        }

        fn xor(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
            ($($t::xor(x.$idx.as_arg(), y.$idx.as_arg())),*)
        }

        fn and(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
            ($($t::and(x.$idx.as_arg(), y.$idx.as_arg())),*)
        }

        fn or (x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
            ($($t::or(x.$idx.as_arg(), y.$idx.as_arg())),*)
        }
    }

    impl<$($t: Ring),*> Ring for ($($t),*) {
        fn negate(x: Self::Arg<'_>) -> Self {
            ($($t::negate(x.$idx.as_arg())),*)
        }

        fn mul(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
            ($($t::mul(x.$idx.as_arg(), y.$idx.as_arg())),*)
        }

        fn sub(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
            ($($t::sub(x.$idx.as_arg(), y.$idx.as_arg())),*)
        }

        fn add(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
            ($($t::add(x.$idx.as_arg(), y.$idx.as_arg())),*)
        }

        fn from_integer(n: Self::Length, x: &num::BigInt) -> Self {
            ($($t::from_integer(n.$idx, x)),*)
        }

        fn exp_usize(x: Self::Arg<'_>, y: usize) -> Self {
            ($($t::exp_usize(x.$idx.as_arg(), y)),*)
        }

        fn exp_uint(x: Self::Arg<'_>, y: &num::BigUint) -> Self {
            ($($t::exp_uint(x.$idx.as_arg(), y)),*)
        }
    }
  };
}

/*  2 */ tuple_type!(0 A, 1 B);
/*  3 */ tuple_type!(0 A, 1 B, 2 C);
/*  4 */ tuple_type!(0 A, 1 B, 2 C, 3 D);
/*  5 */ tuple_type!(0 A, 1 B, 2 C, 3 D, 4 E);
/*  6 */ tuple_type!(0 A, 1 B, 2 C, 3 D, 4 E, 5 F);
/*  7 */ tuple_type!(0 A, 1 B, 2 C, 3 D, 4 E, 5 F, 6 G);
/*  8 */ tuple_type!(0 A, 1 B, 2 C, 3 D, 4 E, 5 F, 6 G, 7 H);
/*  9 */ tuple_type!(0 A, 1 B, 2 C, 3 D, 4 E, 5 F, 6 G, 7 H, 8 I);
/* 10 */ tuple_type!(0 A, 1 B, 2 C, 3 D, 4 E, 5 F, 6 G, 7 H, 8 I, 9 J);
/* 11 */ tuple_type!(0 A, 1 B, 2 C, 3 D, 4 E, 5 F, 6 G, 7 H, 8 I, 9 J, 10 K);
/* 12 */ tuple_type!(0 A, 1 B, 2 C, 3 D, 4 E, 5 F, 6 G, 7 H, 8 I, 9 J, 10 K, 11 L);
/* 13 */ tuple_type!(0 A, 1 B, 2 C, 3 D, 4 E, 5 F, 6 G, 7 H, 8 I, 9 J, 10 K, 11 L, 12 M);
/* 14 */ tuple_type!(0 A, 1 B, 2 C, 3 D, 4 E, 5 F, 6 G, 7 H, 8 I, 9 J, 10 K, 11 L, 12 M, 13 N);
/* 15 */ tuple_type!(0 A, 1 B, 2 C, 3 D, 4 E, 5 F, 6 G, 7 H, 8 I, 9 J, 10 K, 11 L, 12 M, 13 N, 14 O);
/* 16 */ tuple_type!(0 A, 1 B, 2 C, 3 D, 4 E, 5 F, 6 G, 7 H, 8 I, 9 J, 10 K, 11 L, 12 M, 13 N, 14 O, 15 P);
