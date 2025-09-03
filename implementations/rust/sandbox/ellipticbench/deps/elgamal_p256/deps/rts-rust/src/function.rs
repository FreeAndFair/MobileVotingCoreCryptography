use std::sync::Arc;
use std::{marker::PhantomData, ops::Deref};

use crate::{Ring, Zero, type_traits::*};

// Helper for generating anonymous functions that ignore their arguments in function_wrapper
macro_rules! underscore {
    ($x:ident) => {
        _
    };
}

// The follow 2 types specify the calling conventions for lambdas
pub struct O<T>(PhantomData<T>); // Indicates that argument is passed as owned
pub struct B<T>(PhantomData<T>); // Indicates that argument is passed as borrowed (i.e., via Arg)

pub trait FnArg: 'static {
    type FnArg<'a>: Clone;
}

impl<T: Type> FnArg for O<T> {
    type FnArg<'a> = T;
}

impl<T: Type> FnArg for B<T> {
    type FnArg<'a> = T::Arg<'a>;
}

macro_rules! function_wrapper {
    ($Wrap:ident ($($x:ident : $T:ident $a:lifetime),*)) => {

        /// A type-erased wrapper around a reference-counted closures
        pub struct $Wrap<$($T: FnArg,)* R>(Arc<dyn for<$($a,)*> Fn($($T::FnArg<$a>,)*) -> R + Send + Sync>);

        impl<$($T: FnArg,)* R> $Wrap<$($T,)* R> {
          pub fn to_fun(&self) -> &dyn for<$($a,)*> Fn($($T::FnArg<$a>,)*) -> R {
            &**self
          }

          pub fn to_fun_own(self) -> impl Clone + for<$($a,)*> Fn($($T::FnArg<$a>,)*) -> R {
            move |$($x,)*| self($($x,)*)
          }
        }

        impl<$($T: FnArg,)* R> Clone for $Wrap<$($T,)* R> {
          fn clone(&self) -> Self { Self(self.0.clone()) }
        }

        impl<$($T: FnArg,)* R> $Wrap<$($T,)* R> {
            pub fn new<F: 'static + for <$($a,)*> Fn($($T::FnArg<$a>,)*) -> R + Send + Sync>(f: F) -> Self {
                Self(Arc::new(f))
            }
        }

        // This enables us to call values of the wrapped function directly!
        impl<$($T: FnArg,)* R> Deref for $Wrap<$($T,)* R> {
            type Target = dyn for <$($a,)*> Fn($($T::FnArg<$a>,)*) -> R;
            fn deref(&self) -> &Self::Target {
                &*self.0
            }
        }

        impl<$($T: FnArg,)* R: Type> CloneArg for &$Wrap<$($T,)* R> {
            type Owned = $Wrap<$($T,)* R>;
            fn clone_arg(self) -> Self::Owned {
                self.clone()
            }
        }

        impl<$($T: FnArg,)* R: Type> Type for $Wrap<$($T,)* R> {
            type Arg<'a> = &'a Self;
            type Length = R::Length;
            fn as_arg(&self) -> Self::Arg<'_> {
                self
            }
        }

        impl<$($T: FnArg,)* R: Zero> Zero for $Wrap<$($T,)* R> {
            fn zero(n: Self::Length) -> Self {
                Self::new(move |$(underscore!($x),)*| {
                    Zero::zero(n.clone())
                })
            }
        }

        impl<$($T: FnArg,)* R: Ring> Ring for $Wrap<$($T,)* R> {
            fn negate(f: Self::Arg<'_>) -> Self {
                let f = f.clone_arg();
                Self::new(move |$($x,)*| Ring::negate(f($($x,)*).as_arg()))
            }

            fn mul(f: Self::Arg<'_>, g: Self::Arg<'_>) -> Self {
                let f = f.clone_arg();
                let g = g.clone_arg();
                Self::new(move |$($x,)*| Ring::mul(f($($x.clone(),)*).as_arg(), g($($x,)*).as_arg()))
            }

            fn sub(f: Self::Arg<'_>, g: Self::Arg<'_>) -> Self {
                let f = f.clone_arg();
                let g = g.clone_arg();
                Self::new(move |$($x,)*| Ring::sub(f($($x.clone(),)*).as_arg(), g($($x,)*).as_arg()))
            }

            fn add(f: Self::Arg<'_>, g: Self::Arg<'_>) -> Self {
                let f = f.clone_arg();
                let g = g.clone_arg();
                Self::new(move |$($x,)*| Ring::add(f($($x.clone(),)*).as_arg(), g($($x,)*).as_arg()))
            }

            fn from_integer(n: Self::Length, x: &num::BigInt) -> Self {
                let x = x.clone();
                Self::new(move |$(underscore!($x),)*| {
                    Ring::from_integer(n.clone(), &x)
                })
            }

            fn exp_usize(x: Self::Arg<'_>, y: usize) -> Self {
                let x = x.clone_arg();
                Self::new(move |$($x,)*| Ring::exp_usize(x($($x,)*).as_arg(), y))
            }

            fn exp_uint(x: Self::Arg<'_>, y: &num::BigUint) -> Self {
                let x = x.clone_arg();
                let y = y.clone();
                Self::new(move |$($x,)*| Ring::exp_uint(x($($x,)*).as_arg(), &y))
            }
        }
    };
}
function_wrapper!(Fn0());
function_wrapper!( Fn1(x1: T1 'a1));
function_wrapper!( Fn2(x1: T1 'a1, x2: T2 'a2));
function_wrapper!( Fn3(x1: T1 'a1, x2: T2 'a2, x3: T3 'a3));
function_wrapper!( Fn4(x1: T1 'a1, x2: T2 'a2, x3: T3 'a3, x4: T4 'a4));
function_wrapper!( Fn5(x1: T1 'a1, x2: T2 'a2, x3: T3 'a3, x4: T4 'a4, x5: T5 'a5));
function_wrapper!( Fn6(x1: T1 'a1, x2: T2 'a2, x3: T3 'a3, x4: T4 'a4, x5: T5 'a5, x6: T6 'a6));
function_wrapper!( Fn7(x1: T1 'a1, x2: T2 'a2, x3: T3 'a3, x4: T4 'a4, x5: T5 'a5, x6: T6 'a6, x7: T7 'a7));
function_wrapper!( Fn8(x1: T1 'a1, x2: T2 'a2, x3: T3 'a3, x4: T4 'a4, x5: T5 'a5, x6: T6 'a6, x7: T7 'a7, x8: T8 'a8));
function_wrapper!( Fn9(x1: T1 'a1, x2: T2 'a2, x3: T3 'a3, x4: T4 'a4, x5: T5 'a5, x6: T6 'a6, x7: T7 'a7, x8: T8 'a8, x9: T9 'a9));
function_wrapper!(Fn10(x1: T1 'a1, x2: T2 'a2, x3: T3 'a3, x4: T4 'a4, x5: T5 'a5, x6: T6 'a6, x7: T7 'a7, x8: T8 'a8, x9: T9 'a9, x10: T10 'a10));
function_wrapper!(Fn11(x1: T1 'a1, x2: T2 'a2, x3: T3 'a3, x4: T4 'a4, x5: T5 'a5, x6: T6 'a6, x7: T7 'a7, x8: T8 'a8, x9: T9 'a9, x10: T10 'a10, x11: T11 'a11));
function_wrapper!(Fn12(x1: T1 'a1, x2: T2 'a2, x3: T3 'a3, x4: T4 'a4, x5: T5 'a5, x6: T6 'a6, x7: T7 'a7, x8: T8 'a8, x9: T9 'a9, x10: T10 'a10, x11: T11 'a11, x12: T12 'a12));
function_wrapper!(Fn13(x1: T1 'a1, x2: T2 'a2, x3: T3 'a3, x4: T4 'a4, x5: T5 'a5, x6: T6 'a6, x7: T7 'a7, x8: T8 'a8, x9: T9 'a9, x10: T10 'a10, x11: T11 'a11, x12: T12 'a12, x13: T13 'a13));
function_wrapper!(Fn14(x1: T1 'a1, x2: T2 'a2, x3: T3 'a3, x4: T4 'a4, x5: T5 'a5, x6: T6 'a6, x7: T7 'a7, x8: T8 'a8, x9: T9 'a9, x10: T10 'a10, x11: T11 'a11, x12: T12 'a12, x13: T13 'a13, x14: T14 'a14));
function_wrapper!(Fn15(x1: T1 'a1, x2: T2 'a2, x3: T3 'a3, x4: T4 'a4, x5: T5 'a5, x6: T6 'a6, x7: T7 'a7, x8: T8 'a8, x9: T9 'a9, x10: T10 'a10, x11: T11 'a11, x12: T12 'a12, x13: T13 'a13, x14: T14 'a14, x15: T15 'a15));

#[macro_export]
macro_rules! PickFn {
    ($r:ty) => {
        $crate::Fn0::<$r>
    };
    ($a1:ty, $r:ty) => {
        $crate::Fn1::<$a1, $r>
    };
    ($a1:ty, $a2:ty, $r:ty) => {
        $crate::Fn2::<$a1, $a2, $r>
    };
    ($a1:ty, $a2:ty, $a3:ty, $r:ty) => {
        $crate::Fn3::<$a1, $a2, $a3, $r>
    };
    ($a1:ty, $a2:ty, $a3:ty, $a4:ty, $r:ty) => {
        $crate::Fn4::<$a1, $a2, $a3, $a4, $r>
    };
    ($a1:ty, $a2:ty, $a3:ty, $a4:ty, $a5:ty, $r:ty) => {
        $crate::Fn5::<$a1, $a2, $a3, $a4, $a5, $r>
    };
    ($a1:ty, $a2:ty, $a3:ty, $a4:ty, $a5:ty, $a6:ty, $r:ty) => {
        $crate::Fn6::<$a1, $a2, $a3, $a4, $a5, $a6, $r>
    };
    ($a1:ty, $a2:ty, $a3:ty, $a4:ty, $a5:ty, $a6:ty, $a7:ty, $r:ty) => {
        $crate::Fn7::<$a1, $a2, $a3, $a4, $a5, $a6, $a7, $r>
    };
    ($a1:ty, $a2:ty, $a3:ty, $a4:ty, $a5:ty, $a6:ty, $a7:ty, $a8:ty, $r:ty) => {
        $crate::Fn8::<$a1, $a2, $a3, $a4, $a5, $a6, $a7, $a8, $r>
    };
    ($a1:ty, $a2:ty, $a3:ty, $a4:ty, $a5:ty, $a6:ty, $a7:ty, $a8:ty, $a9:ty, $r:ty) => {
        $crate::Fn9::<$a1, $a2, $a3, $a4, $a5, $a6, $a7, $a8, $a9, $r>
    };
    ($a1:ty, $a2:ty, $a3:ty, $a4:ty, $a5:ty, $a6:ty, $a7:ty, $a8:ty, $a9:ty, $a10:ty, $r:ty) => {
        $crate::Fn10::<$a1, $a2, $a3, $a4, $a5, $a6, $a7, $a8, $a9, $a10, $r>
    };
    ($a1:ty, $a2:ty, $a3:ty, $a4:ty, $a5:ty, $a6:ty, $a7:ty, $a8:ty, $a9:ty, $a10:ty, $a11:ty, $r:ty) => {
        $crate::Fn11::<$a1, $a2, $a3, $a4, $a5, $a6, $a7, $a8, $a9, $a10, $a11, $r>
    };
    ($a1:ty, $a2:ty, $a3:ty, $a4:ty, $a5:ty, $a6:ty, $a7:ty, $a8:ty, $a9:ty, $a10:ty, $a11:ty, $a12:ty, $r:ty) => {
        $crate::Fn12::<$a1, $a2, $a3, $a4, $a5, $a6, $a7, $a8, $a9, $a10, $a11, $a12, $r>
    };
    ($a1:ty, $a2:ty, $a3:ty, $a4:ty, $a5:ty, $a6:ty, $a7:ty, $a8:ty, $a9:ty, $a10:ty, $a11:ty, $a12:ty, $a13:ty, $r:ty) => {
        $crate::Fn13::<$a1, $a2, $a3, $a4, $a5, $a6, $a7, $a8, $a9, $a10, $a11, $a12, $a13, $r>
    };
    ($a1:ty, $a2:ty, $a3:ty, $a4:ty, $a5:ty, $a6:ty, $a7:ty, $a8:ty, $a9:ty, $a10:ty, $a11:ty, $a12:ty, $a13:ty, $a14:ty, $r:ty) => {
        $crate::Fn14::<$a1, $a2, $a3, $a4, $a5, $a6, $a7, a8, $a9, $a10, $a11, $a12, $a13, $a14, $r>
    };
    ($a1:ty, $a2:ty, $a3:ty, $a4:ty, $a5:ty, $a6:ty, $a7:ty, $a8:ty, $a9:ty, $a10:ty, $a11:ty, $a12:ty, $a13:ty, $a14:ty, $a15:ty, $r:ty) => {
        $crate::Fn15::<
            $a1,
            $a2,
            $a3,
            $a4,
            $a5,
            $a6,
            $a7,
            a8,
            $a9,
            $a10,
            $a11,
            $a12,
            $a13,
            $a14,
            $a15,
            $r,
        >
    };
}

#[macro_export]
/// This macro defines the functions in a recursive group by
/// "tying the recursive knot".
macro_rules! do_rec_closure_def {
  // Last closure definition does not need to clone
  (true, $clo:path, $f:ident, [$(($x:ident,$ArgTy:ty))*], $ResTy:ty) => {
    let $f = <$crate::PickFn!($($ArgTy,)* $ResTy)>::new(
        move |$($x,)*| { ($clo.$f)(&$clo, $($x,)* ) }
      );
  };

  // Not the last closure definition: we need to clone the closure
  (false, $clo:path, $f:ident, [$(($x:ident,$ArgTy:ty))*], $ResTy:ty) => {
    let clo1 = $clo.clone();
    let $f = <$crate::PickFn!($($ArgTy,)* $ResTy)>::new(
        move |$($x,)*| { (clo1.$f)(&clo1, $($x,)* ) }
      );
  }
}

#[macro_export]
/// Declare a group of local mutually recursive functions.
/// This is the "worker" part of the macro.  For concrete syntax, see `rec`.
macro_rules! do_rec {
    ( [ $($T:ident)* ]
    , [ $( ( $last:tt
           , ($f:ident, [$($cap:stmt)*], [$(($x:ident,$ArgTy:ty))*], $ResTy:ty, $e:block)
           , [ [ $($FT:ident)* ] $([ $fs:ident $($fs_xs:ident)* ])* ]
           )
        )*
      ]
    ) => {

      #[allow(unused_variables)]
      let ( $($f),* ) =
      {
        // First we define a local type containing the definitions
        // for the recursive functions, but instead of making recursive calls
        // they call a function in an additional object of functions.
        // Note that we need this and we can't just pass the functions one
        // by one as we couldn't type them:  we need a recursive type
        // like `CryRegGrp` to make the types fit.
        struct CryRecGrp<$($T: $crate::Type),*> {
          $($f : $crate::PickFn!( $crate::B<CryRecGrp< $($FT,)*>> $(,$ArgTy)*, $ResTy ),)*
        }

        impl<$($T: $crate::Type,)*> Clone for CryRecGrp<$($T,)*> {
          fn clone(&self) -> Self { CryRecGrp { $($f: self.$f.clone(),)* } }
        }

        impl<$($T: $crate::Type,)*> $crate::Type for CryRecGrp<$($T,)*> {
          type Arg<'a> = &'a CryRecGrp<$($T,)*>;
          type Length = ();
          fn as_arg(&self) -> Self::Arg<'_> { self }
        }

        impl<'a, $($T: $crate::Type,)*> $crate::CloneArg for &'a CryRecGrp<$($T,)*> {
          type Owned = CryRecGrp<$($T,)*>;
          fn clone_arg(self) -> Self::Owned { self.clone() }
        }


        // Next we define a single value of the type,
        // containing the actual definitions.
        let clo: CryRecGrp<$($T,)*>= CryRecGrp {
          $($f: <$crate::PickFn!($crate::B<CryRecGrp<$($FT,)*>> $(,$ArgTy)*, $ResTy)>::new(
            {
            $($cap;)*  // Custom statements, typically used to capture things
                       // that should be moved in the recursive function.
            move |this $(,$x)*| {
              $(
                // This defines the recursive group members for this
                // particular member
                #[allow(unused_variables)]
                let $fs = |$($fs_xs),*| { (this.$fs)(this $(,$fs_xs)*)};
              )*
              $e
            }}
            ),)*
        };

        // Finally, we tie the knot together by making some functions
        // that pass the above recursive group as an argument to all group
        // members
        $($crate::do_rec_closure_def!($last,clo,$f,[$(($x,$ArgTy))*],$ResTy);)*
        ( $($f),* )
      };
    }
  }

// This is the "worker" part of `macro_map`, see below.
#[macro_export]
macro_rules! macro_map_worker {
  ($f:path,$globals:tt,$locals:tt, $done:tt, []) => {
    $f!($globals,$done)
  };
  ($f:path,$globals:tt,$locals:tt,[$($done:tt)*],[$x:tt]) => {
    $f!($globals,[$($done)* (true,$x,$locals)])
  };
  ($f:path,$globals:tt,$locals:tt,[$($done:tt)*],[$x:tt $($xs:tt)+]) => {
    $crate::macro_map_worker!($f,$globals,$locals,[$($done)* (false,$x,$locals)],[$($xs)*])
  }
}

/// A macro to duplicate stuff so we can iterate over them as we want to.
///
/// macro_map f globals locals xs = f globals (zip3 isLast xs (repeat ls))
///  where isLast = reverse (zipWith const (True : repeat False) xs)
#[macro_export]
macro_rules! macro_map {
    ($f:path, $globals:tt, $locals:tt, $xs:tt) => {
        $crate::macro_map_worker!($f, $globals, $locals, [], $xs)
    };
}

#[macro_export]
/// Declare a group of local mutually recursive functions.
/// This is the entry point for defining recursive lambdas.
///
/// rec {
///   capture S T;     // Type variable from the context we'll use
///   { stmts }        // Statements to put before function def
///   let f = move |x: O<TypeOfFArg>| -> TypeOfFResult {
///     ... definition of `f`, may use `f` and `g`
///   }
///   let g = move |y: O<TypeOfGArg>| -> TypeOfGResult {
///     ... definition of `g`, may use `f` and `g`
///   }
///
/// See `FnArg` above for the meaning of `O` (in this example "Owned")---
/// it specifies how arguments are passed to the lambda.
///
/// The `stmts` are added before each function definition.  Typically they are
/// used to capture some things that should be moved in each closure.
/// They should not really mention the functions defined in the recursive group.
/// }
macro_rules! rec {
  (captures $($T:ident)*;
    $({ $($cap:stmt;)* }
      let $f:ident = move |$($x:ident : $ArgTy: ty),*| -> $ResTy: ty $e:block;)*) => {
      $crate::macro_map!($crate::do_rec,
                 [$($T)*],
                 [[$($T)*] $([$f $($x)*])* ],
                 [ $(($f,[$($cap)*],[$(($x,$ArgTy))*],$ResTy,$e))* ])
    }
}

#[cfg(test)]
mod test {
    use crate::{B, Cmp, Fn1, Fn2, Integral, O, Ring, type_traits::*};
    use num::BigInt;

    // Show that we can have an array of closures that can be called using
    // our Arg calling convention
    #[test]
    fn test() {
        let one = BigInt::from(1);
        let one_ = one.clone();
        let two = BigInt::from(2);
        let three = BigInt::from(3);

        let logic: [Fn1<B<BigInt>, BigInt>; 2] = [
            Fn1::new(move |x| Integral::div(x, two.as_arg())),
            Fn1::new(move |x| {
                Ring::add(
                    <BigInt as Ring>::mul(x, three.as_arg()).as_arg(),
                    one_.as_arg(),
                )
            }),
        ];

        let mut x = BigInt::from(25);
        let mut n: u64 = 0;

        while <BigInt as Cmp>::gt(x.as_arg(), one.as_arg()) {
            let i = x.bit(0) as usize;
            x = logic[i](x.as_arg());
            n = n + 1;
        }

        assert_eq!(n, 23);
    }

    // We can easily wrap function pointers using the common calling convention
    #[test]
    fn wrap_gt() {
        let f: Fn2<B<BigInt>, B<BigInt>, bool> = Fn2::new(<BigInt as Cmp>::gt);
        assert!(f(BigInt::from(3).as_arg(), BigInt::from(2).as_arg()));
        assert!(!f(BigInt::from(2).as_arg(), BigInt::from(3).as_arg()));
    }

    #[test]
    fn test_add() {
        let f = Fn1::<O<BigInt>, BigInt>::new(|x| Ring::mul(x.as_arg(), BigInt::from(2).as_arg()));
        let g = <Fn1<O<BigInt>, BigInt> as Ring>::add(f.as_arg(), f.as_arg());
        assert_eq!(g(BigInt::from(7)), BigInt::from(28));
    }
}
