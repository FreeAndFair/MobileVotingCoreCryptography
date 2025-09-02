/*
 * Placeholder
 */

#![allow(unused_variables)]
#![allow(unused_imports)]
use cry_rts::trait_methods::*;

/**
Convert a `Z` type to a bitvector.

```cryptol
ZtoBV : {p, a} (p >= 1) => Z p -> [a]
```
*/
pub fn zto_bv_inst_nat_sz(
  p: &num::BigUint,
  a: usize,
  x: &cry_rts::Z,
) -> cry_rts::DWord {
  <cry_rts::DWord as cry_rts::Ring>::from_integer(a, x.from_z().as_arg())
}

/**
"Multiply" `x` by `2` in an additive group.

```cryptol
mul2 : {a} (Ring a) => a -> a
```
*/
pub fn mul2_inst_val<T>(t_len: T::Length, x: T::Arg<'_>) -> T
where
  T: cry_rts::Type,
  T: cry_rts::Ring,
{
  <T as cry_rts::Ring>::add(x, x)
}

/**
"Multiply" `x` by `3` in an additive group.

```cryptol
mul3 : {a} (Ring a) => a -> a
```
*/
pub fn mul3_inst_val<T>(t_len: T::Length, x: T::Arg<'_>) -> T
where
  T: cry_rts::Type,
  T: cry_rts::Ring,
{
  <T as cry_rts::Ring>::add(x, mul2_inst_val::<T>(t_len.clone(), x).as_arg())
}

/**
"Multiply" `x` by `4` in an additive group.

```cryptol
mul4 : {a} (Ring a) => a -> a
```
*/
pub fn mul4_inst_val<T>(t_len: T::Length, x: T::Arg<'_>) -> T
where
  T: cry_rts::Type,
  T: cry_rts::Ring,
{
  mul2_inst_val::<T>(
    t_len.clone(),
    mul2_inst_val::<T>(t_len.clone(), x).as_arg(),
  )
}

/**
"Multiply" `x` by `8` in an additive group.

```cryptol
mul8 : {a} (Ring a) => a -> a
```
*/
pub fn mul8_inst_val<T>(t_len: T::Length, x: T::Arg<'_>) -> T
where
  T: cry_rts::Type,
  T: cry_rts::Ring,
{
  mul2_inst_val::<T>(
    t_len.clone(),
    mul4_inst_val::<T>(t_len.clone(), x).as_arg(),
  )
}

/**
Check if an integer is even.

```cryptol
isEven : Integer -> Bit
```
*/
pub fn is_even(x: &num::BigInt) -> bool {
  <cry_rts::DWord as cry_rts::Logic>::complement(<cry_rts::DWord as cry_rts::Ring>::from_integer(
    1usize,
    x,
  )
    .as_arg())
    .as_arg()
    .seq_index_back::<num::BigInt>(<num::BigInt>::number((), 0usize).as_arg())
}

/**
Calculate "half" of a quantity in a mod `p` context.
I.e., `half x + half x == x`.

```cryptol
half : {p} (p >= 3, p - p % 2 == p - 1) => Z p -> Z p
```
*/
pub fn half_inst_nat(p: &num::BigUint, x: &cry_rts::Z) -> cry_rts::Z {
  let xint = x.from_z();
  <cry_rts::Z as cry_rts::Ring>::from_integer(
    p.clone(),
    if is_even(xint.as_arg()) {
      <num::BigInt>::div(
        xint.as_arg(),
        <num::BigInt>::number((), 2usize).as_arg(),
      )
    } else {
      <num::BigInt>::div(
        <num::BigInt as cry_rts::Ring>::add(
          xint.as_arg(),
          <num::BigInt>::number((), p).as_arg(),
        )
          .as_arg(),
        <num::BigInt>::number((), 2usize).as_arg(),
      )
    }
      .as_arg(),
  )
}

/**
Verify that `half` is correct.
```repl
:prove half_correct `{7}
```

```cryptol
half_correct : {p} (p >= 3, p - p % 2 == p - 1) => Z p -> Bit
```
*/
pub fn half_correct_inst_nat(p: &num::BigUint, x: &cry_rts::Z) -> bool {
  <cry_rts::Z as cry_rts::Eq>::eq(
    <cry_rts::Z as cry_rts::Ring>::add(
      half_inst_nat(p, x).as_arg(),
      half_inst_nat(p, x).as_arg(),
    )
      .as_arg(),
    x,
  )
}

/**
Calculate "half" of a quantity in a mod `p` context.
I.e., `half x + half x == x`.

```cryptol
half : {p} (p >= 3, p - p % 2 == p - 1) => Z p -> Z p
```
*/
pub fn half_inst_sz(p: usize, x: &cry_rts::Z) -> cry_rts::Z {
  let xint = x.from_z();
  <cry_rts::Z as cry_rts::Ring>::from_integer(
    cry_rts::size_to_int(p),
    if is_even(xint.as_arg()) {
      <num::BigInt>::div(
        xint.as_arg(),
        <num::BigInt>::number((), 2usize).as_arg(),
      )
    } else {
      <num::BigInt>::div(
        <num::BigInt as cry_rts::Ring>::add(
          xint.as_arg(),
          <num::BigInt>::number((), p).as_arg(),
        )
          .as_arg(),
        <num::BigInt>::number((), 2usize).as_arg(),
      )
    }
      .as_arg(),
  )
}

/**
Verify that `half` is correct.
```repl
:prove half_correct `{7}
```

```cryptol
half_correct : {p} (p >= 3, p - p % 2 == p - 1) => Z p -> Bit
```
*/
pub fn half_correct_inst_sz(p: usize, x: &cry_rts::Z) -> bool {
  <cry_rts::Z as cry_rts::Eq>::eq(
    <cry_rts::Z as cry_rts::Ring>::add(
      half_inst_sz(p, x).as_arg(),
      half_inst_sz(p, x).as_arg(),
    )
      .as_arg(),
    x,
  )
}
