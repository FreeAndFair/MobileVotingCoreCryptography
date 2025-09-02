pub mod type_traits;
pub mod traits;
pub mod display;

pub mod cry_dword;
pub mod vec;
pub mod stream;
pub mod stream_traits;
pub mod tuple;
pub mod function;

pub mod bit;
pub mod native;
pub mod int;
pub mod range;
pub mod rational;
pub mod transpose;
pub mod split;
pub mod index;
pub mod size;
pub mod update;
pub mod z;
pub mod poly;

pub use type_traits::*;
pub use traits::*;
pub use display::*;
pub use dword::DWord;
pub use dword::DWordRef;
pub use stream::*;
pub use stream_traits::*;
pub use vec::*;
pub use range::*;
pub use transpose::*;
pub use function::*;
pub use split::*;
pub use index::*;
pub use rational::*;
pub use size::*;
pub use update::*;
pub use z::*;
pub use poly::*;

// Needed only for custom proptest strategies
#[cfg(feature = "proptest_strategies")]
pub use int::*;

pub mod trait_methods {
  pub use crate::display::Display as _;
  pub use crate::display::Base as _;
  pub use crate::display::DefaultBase as _;

  pub use crate::type_traits::Type as _;
  pub use crate::type_traits::CloneArg as _;
  pub use crate::type_traits::Sequence as _;
  pub use crate::type_traits::SeqOwned as _;
  pub use crate::type_traits::ToSignedInteger as _;
  pub use crate::type_traits::Word as _;
  pub use crate::type_traits::ToVec as _;
  pub use crate::type_traits::Stream as _;
  pub use crate::type_traits::ByValue as _;

  pub use crate::traits::Zero as _;
  pub use crate::traits::Literal as _;
  pub use crate::traits::LiteralNumber as _;
  pub use crate::traits::FLiteral as _;
  pub use crate::traits::FLiteralNumber as _;
  pub use crate::traits::Integral as _;
  pub use crate::traits::Ring as _;
  pub use crate::traits::Field as _;
  pub use crate::traits::Logic as _;
  pub use crate::traits::Eq as _;
  pub use crate::traits::Cmp as _;
  pub use crate::traits::SignedCmp as _;
  pub use crate::traits::Round as _;

  pub use crate::split::StreamBits as _;

  pub use crate::poly::PMod as _;
  /* XXX: Add other traits */
}


#[macro_export]
/// Generate the `Type` instance for a type that is passed by value (Copy),
/// and has no interesting lenght.
macro_rules! PrimType {

  ($ty:ty) => {

    impl $crate::type_traits::Type for $ty {
      type Length  = ();
      type Arg<'a> = Self;
      fn as_arg(&self) -> Self::Arg<'_> { self.clone() }
    }

    impl $crate::type_traits::CloneArg for $ty {
      type Owned = $ty;
      fn clone_arg(self) -> Self::Owned { self }
    }
  };
}



#[macro_export]
/// Generate the `Type` instance for a type that is passed by reference,
/// and has no interesting length.
macro_rules! RefType {

  // There are two cases: one where there is a monomorphic type $ty, and another
  // where there is a polymorphic type $ty plus type parameters $p. It is likely
  // that we could combine these cases with enough clever Rust macro magic, but
  // for now, it's straightforward enough to just duplicate the (relatively
  // small) amount of code needed for both cases.

  ($ty:ty) => {

    impl $crate::type_traits::Type for $ty {
      type Length = ();
      type Arg<'a> = &'a Self;
      fn as_arg(&self) -> Self::Arg<'_> { self }
    }

    impl $crate::type_traits::CloneArg for &'_ $ty {
      type Owned = $ty;
      fn clone_arg(self) -> Self::Owned { self.clone() }
    }
  };

  ($ty:ty , $($p:ident),+) => {

    impl<$($p: $crate::type_traits::Type),+> $crate::type_traits::Type for $ty {
      type Length = ();
      type Arg<'a> = &'a Self;
      fn as_arg(&self) -> Self::Arg<'_> { self }
    }

    impl<$($p: $crate::type_traits::Type),+> $crate::type_traits::CloneArg for &'_ $ty {
      type Owned = $ty;
      fn clone_arg(self) -> Self::Owned { self.clone() }
    }
  };
}

#[macro_export]
macro_rules! Global {
    ($(#[$meta:meta])* $v:ident : $t:ty = $x:expr) => {
      #[allow(non_upper_case_globals)]
      $(#[$meta])*
      pub static $v: std::sync::LazyLock<$t> = std::sync::LazyLock::new(|| $x);
    };
}
