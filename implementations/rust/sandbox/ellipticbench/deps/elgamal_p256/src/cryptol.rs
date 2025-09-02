/*
 * Placeholder
 */

#![allow(unused_variables)]
#![allow(unused_imports)]
use cry_rts::trait_methods::*;

/**
The 'Option a' type represents an optional value. Every 'Option a' value is
either 'Some' and contains a value of type 'a', or 'None' and does not. Among
other uses, optional values are useful for modeling return values for partial
functions, i.e., functions that are not defined over their entire input
range. In these situations, 'None' can be used as a placeholder return value.

```cryptol
enum Cryptol::Option a
```
*/
#[derive(Clone)]
pub enum OptionInstTy<A> {
  None(),
  Some(A),
}

cry_rts::RefType! { OptionInstTy<A>, A }

/**
The 'Option a' type represents an optional value. Every 'Option a' value is
either 'Some' and contains a value of type 'a', or 'None' and does not. Among
other uses, optional values are useful for modeling return values for partial
functions, i.e., functions that are not defined over their entire input
range. In these situations, 'None' can be used as a placeholder return value.

```cryptol
enum Cryptol::Option a
```
*/
pub fn _none_con_inst_ty<A>() -> OptionInstTy<A>
where
  A: cry_rts::Type,
{
  OptionInstTy::None()
}

/**
The 'Option a' type represents an optional value. Every 'Option a' value is
either 'Some' and contains a value of type 'a', or 'None' and does not. Among
other uses, optional values are useful for modeling return values for partial
functions, i.e., functions that are not defined over their entire input
range. In these situations, 'None' can be used as a placeholder return value.

```cryptol
enum Cryptol::Option a
```
*/
pub fn _some_con_inst_ty<A>(anon: A::Arg<'_>) -> OptionInstTy<A>
where
  A: cry_rts::Type,
{
  OptionInstTy::Some(anon.clone_arg())
}

/**
Map a function over a sequence.

```cryptol
map : {n, a, b} (a -> b) -> [n]a -> [n]b
```
*/
pub fn map_inst_sz_val_val<A, B>(
  n: usize,
  f: &cry_rts::Fn1<cry_rts::O<A>, B>,
  xs: &[A],
) -> Vec<B>
where
  A: cry_rts::Type,
  B: cry_rts::Type,
{
  cry_rts::stream!(
    forall = [
      SI1: [ cry_rts::Stream<A> ], A: [ cry_rts::Type ], B: [ cry_rts::Type ]
    ], element = B, capture = [
      f: cry_rts::Fn1<cry_rts::O<A>, B> = f.clone(), anon: SI1 = xs
        .clone_arg()
        .into_iter()
    ], step = |this|{ let x = this.anon.next()?; (this.f)(x) }
  )
    .to_vec()
}

/**
Short-cutting logical implication.
If the first argument is False, the second argument is
not evaluated.

```cryptol
==> : Bit -> Bit -> Bit
```
*/
pub fn op_eq_eq_gt(a: bool, b: bool) -> bool {
  if a { b } else { true }
}

/**
Drop the first (left-most) element of a sequence.

```cryptol
tail : {n} [1 + n] -> [n]
Additional constraints:
  64 >= width (1 + n)
```
*/
pub fn tail_inst_sz_bit(n: usize, xs: cry_rts::DWordRef<'_>) -> cry_rts::DWord {
  xs.skip(1usize)
}

/**
Short-cutting boolean disjunction function.
If the first argument is True, the second argument
is not evaluated.

```cryptol
\/ : Bit -> Bit -> Bit
```
*/
pub fn op_bslash_fslash(x: bool, y: bool) -> bool {
  if x { true } else { y }
}

/**
Map a function over a sequence.

```cryptol
map : {n, a} (a -> Bit) -> [n]a -> [n]
```
*/
pub fn map_inst_sz_val_bit<A>(
  n: usize,
  f: &cry_rts::Fn1<cry_rts::O<A>, bool>,
  xs: &[A],
) -> cry_rts::DWord
where
  A: cry_rts::Type,
{
  cry_rts::DWord::from_stream_msb(
    n,
    cry_rts::stream!(
      forall = [
        SI1: [ cry_rts::Stream<A> ], A: [ cry_rts::Type ]
      ], element = bool, capture = [
        f: cry_rts::Fn1<cry_rts::O<A>, bool> = f.clone(), anon: SI1 = xs
          .clone_arg()
          .into_iter()
      ], step = |this|{ let x = this.anon.next()?; (this.f)(x) }
    ),
  )
}

/**
Disjunction after applying a predicate to all elements.

```cryptol
any : {n, a} (a -> Bit) -> [n]a -> Bit
```
*/
pub fn any_inst_sz_val<A>(
  n: usize,
  f: &cry_rts::Fn1<cry_rts::O<A>, bool>,
  xs: &[A],
) -> bool
where
  A: cry_rts::Type,
{
  map_inst_sz_val_bit::<A>(
    n,
    &<cry_rts::Fn1<cry_rts::O<A>, _>>::new({
      let f = f.clone();
      move |x| { let f = &f; (f)(x) }
    }),
    xs,
  )
    .into_iter_bits_msb()
    .fold(
      false,
      (&<cry_rts::Fn2<cry_rts::O<bool>, cry_rts::O<bool>, _>>::new(move |x, x_1| if x {
        true
      } else { x_1 }))
        .to_fun(),
    )
}

/**
Short-cutting boolean conjunction function.
If the first argument is False, the second argument
is not evaluated.

```cryptol
/\ : Bit -> Bit -> Bit
```
*/
pub fn op_fslash_bslash(x: bool, y: bool) -> bool {
  if x { y } else { false }
}

/**
Conjunction after applying a predicate to all elements.

```cryptol
all : {n, a} (a -> Bit) -> [n]a -> Bit
```
*/
pub fn all_inst_sz_val<A>(
  n: usize,
  f: &cry_rts::Fn1<cry_rts::O<A>, bool>,
  xs: &[A],
) -> bool
where
  A: cry_rts::Type,
{
  map_inst_sz_val_bit::<A>(
    n,
    &<cry_rts::Fn1<cry_rts::O<A>, _>>::new({
      let f = f.clone();
      move |x| { let f = &f; (f)(x) }
    }),
    xs,
  )
    .into_iter_bits_msb()
    .fold(
      true,
      (&<cry_rts::Fn2<cry_rts::O<bool>, cry_rts::O<bool>, _>>::new(move |x, x_1| if x {
        x_1
      } else { false }))
        .to_fun(),
    )
}
