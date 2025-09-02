/*! Utility Functions for E2EVIV Cryptography

@author Frank Zeyda (frank.zeyda@freeandfair.us)
@copyright Free & Fair 2025
@version 0.1
*/
#![allow(unused_variables)]
#![allow(unused_imports)]
use cry_rts::trait_methods::*;

/**
Computes the Legendre symbol.

@pre type parameter n must be an odd prime

```cryptol
legendre : {n} (prime n, n >= 3) => Z n -> Integer
```
*/
pub fn legendre_inst_nat(n: &num::BigUint, z: &cry_rts::Z) -> num::BigInt {
  if <cry_rts::Z as cry_rts::Eq>::eq(
    z,
    <cry_rts::Z>::number(n.clone(), 0usize).as_arg(),
  ) { <num::BigInt>::number((), 0usize) } else {
    if <cry_rts::Z as cry_rts::Eq>::eq(
      cry_rts::exp::<cry_rts::Z, num::BigInt>(
        z,
        <num::BigInt>::div(
          <num::BigInt as cry_rts::Ring>::sub(
            <num::BigInt>::number((), n).as_arg(),
            <num::BigInt>::number((), 1usize).as_arg(),
          )
            .as_arg(),
          <num::BigInt>::number((), 2usize).as_arg(),
        )
          .as_arg(),
      )
        .as_arg(),
      <cry_rts::Z>::number(n.clone(), 1usize).as_arg(),
    ) { <num::BigInt>::number((), 1usize) } else {
      if <cry_rts::Z as cry_rts::Eq>::eq(
        cry_rts::exp::<cry_rts::Z, num::BigInt>(
          z,
          <num::BigInt>::div(
            <num::BigInt as cry_rts::Ring>::sub(
              <num::BigInt>::number((), n).as_arg(),
              <num::BigInt>::number((), 1usize).as_arg(),
            )
              .as_arg(),
            <num::BigInt>::number((), 2usize).as_arg(),
          )
            .as_arg(),
        )
          .as_arg(),
        <cry_rts::Z as cry_rts::Ring>::negate(<cry_rts::Z>::number(
          n.clone(),
          1usize,
        )
          .as_arg())
          .as_arg(),
      ) {
        <num::BigInt as cry_rts::Ring>::negate(<num::BigInt>::number((), 1usize)
          .as_arg())
      } else { todo!("error") }
    }
  }
}

/**
Checks if a given number is a quadratic residue in a
multiplicative modular group of prime order.

@pre type parameter n must be an odd prime
@note zero is considered a quadratic residue too

```cryptol
isQuadraticResidue : {n} (prime n, n >= 3) => Z n -> Bit
```
*/
pub fn is_quadratic_residue_inst_nat(n: &num::BigUint, z: &cry_rts::Z) -> bool {
  <num::BigInt as cry_rts::Cmp>::ge(
    legendre_inst_nat(n, z).as_arg(),
    <num::BigInt>::number((), 0usize).as_arg(),
  )
}

/**
Checks if a given number is a quartic residue in a
multiplicative modular group of prime order.

@pre type parameter n must be an odd prime
@note zero is considered a quartic residue too

```cryptol
isQuarticResidue : {n} (prime n, n >= 3) => Z n -> Bit
```
*/
pub fn is_quartic_residue_inst_nat(n: &num::BigUint, z: &cry_rts::Z) -> bool {
  <cry_rts::Z as cry_rts::Eq>::eq(
    cry_rts::exp::<cry_rts::Z, num::BigInt>(
      z,
      <num::BigInt>::div(
        <num::BigInt as cry_rts::Ring>::sub(
          <num::BigInt>::number((), n).as_arg(),
          <num::BigInt>::number((), 1usize).as_arg(),
        )
          .as_arg(),
        <num::BigInt>::number((), 4usize).as_arg(),
      )
        .as_arg(),
    )
      .as_arg(),
    <cry_rts::Z>::number(n.clone(), 1usize).as_arg(),
  )
}

/**
Determines if a given Integral value type is even.

```cryptol
isEven : {a} (Integral a) => a -> Bit
```
*/
pub fn is_even_inst_val<A>(a_len: A::Length, x: A::Arg<'_>) -> bool
where
  A: cry_rts::Type,
  A: cry_rts::Integral,
{
  <num::BigInt as cry_rts::Eq>::eq(
    <num::BigInt>::modulo(
      <A>::to_integer(x).as_arg(),
      <num::BigInt>::number((), 2usize).as_arg(),
    )
      .as_arg(),
    <num::BigInt>::number((), 0usize).as_arg(),
  )
}

/**
Utility function for `tonelli_shanks`.

@see https://en.wikipedia.org/wiki/Tonelli%E2%80%93Shanks_algorithm

```cryptol
factorOutPow2 : Integer -> (Integer, Integer)
```
*/
pub fn factor_out_pow2(n: &num::BigInt) -> (num::BigInt, num::BigInt) {
  cry_rts::rec!{
    captures; {  } let factor_out_pow2qx_1_aux =
      move |__p4: cry_rts::O<(num::BigInt, num::BigInt)>| -> (
        num::BigInt,
        num::BigInt,
      ) {
        let s = __p4.as_arg().1.as_arg().clone_arg();
        let q = __p4.as_arg().0.as_arg().clone_arg();
        if is_even_inst_val::<num::BigInt>((), q.as_arg()) {
          (factor_out_pow2qx_1_aux)((
            <num::BigInt>::div(
              q.as_arg(),
              <num::BigInt>::number((), 2usize).as_arg(),
            ),
            <num::BigInt as cry_rts::Ring>::add(
              s.as_arg(),
              <num::BigInt>::number((), 1usize).as_arg(),
            ),
          ))
        } else { (q, s) }
      };
  }
  if <num::BigInt as cry_rts::Eq>::eq(
    n,
    <num::BigInt>::number((), 0usize).as_arg(),
  ) {
    (<num::BigInt>::number((), 0usize), <num::BigInt>::number((), 0usize))
  } else {
    (factor_out_pow2qx_1_aux)((
      n.clone_arg(),
      <num::BigInt>::number((), 0usize),
    ))
  }
}

/**
Finds a quadratic nonresidue starting the search from a given value.

@pre type parameter n must be an odd prime
@post returns a quadratic nonresidue not equal to zero

```cryptol
findQuadraticNonResidue : {n} (prime n, n >= 3) => Z n -> Z n
```
*/
pub fn find_quadratic_non_residue_inst_nat(
  n: &num::BigUint,
  z: &cry_rts::Z,
) -> cry_rts::Z {
  if <num::BigInt as cry_rts::Eq>::eq(
    legendre_inst_nat(n, z).as_arg(),
    <num::BigInt as cry_rts::Ring>::negate(<num::BigInt>::number((), 1usize)
      .as_arg())
      .as_arg(),
  ) { z.clone_arg() } else {
    find_quadratic_non_residue_inst_nat(
      n,
      <cry_rts::Z as cry_rts::Ring>::add(
        z,
        <cry_rts::Z>::number(n.clone(), 1usize).as_arg(),
      )
        .as_arg(),
    )
  }
}

/**
```cryptol
findLeasti'aux : {p} (prime p, p >= 3) => Integer -> Integer -> Z p -> Integer
```
*/
pub fn find_leastiqx_1_aux_inst_nat(
  p: &num::BigUint,
  m: &num::BigInt,
  i: &num::BigInt,
  t2i: &cry_rts::Z,
) -> num::BigInt {
  if <cry_rts::Z as cry_rts::Eq>::eq(
    t2i,
    <cry_rts::Z>::number(p.clone(), 1usize).as_arg(),
  ) { i.clone_arg() } else {
    find_leastiqx_1_aux_inst_nat(
      p,
      m,
      <num::BigInt as cry_rts::Ring>::add(
        i,
        <num::BigInt>::number((), 1usize).as_arg(),
      )
        .as_arg(),
      <cry_rts::Z as cry_rts::Ring>::mul(t2i, t2i).as_arg(),
    )
  }
}

/**
Utility function for `tonelli_shanks`.

@see https://en.wikipedia.org/wiki/Tonelli%E2%80%93Shanks_algorithm

```cryptol
findLeasti : {p} (prime p, p >= 3) => Integer -> Z p -> Integer
```
*/
pub fn find_leasti_inst_nat(
  p: &num::BigUint,
  m: &num::BigInt,
  t: &cry_rts::Z,
) -> num::BigInt {
  find_leastiqx_1_aux_inst_nat(
    p,
    m,
    <num::BigInt>::number((), 1usize).as_arg(),
    <cry_rts::Z as cry_rts::Ring>::mul(t, t).as_arg(),
  )
}

/**
Utility function for `tonelli_shanks`.

@see https://en.wikipedia.org/wiki/Tonelli%E2%80%93Shanks_algorithm

```cryptol
tonelli_shanks'loop : {p} (prime p, p >= 3) => Integer -> Z p -> Z p -> Z p -> Z p
```
*/
pub fn tonelli_shanksqx_1_loop_inst_nat(
  p: &num::BigUint,
  m: &num::BigInt,
  c: &cry_rts::Z,
  t: &cry_rts::Z,
  r: &cry_rts::Z,
) -> cry_rts::Z {
  if <cry_rts::Z as cry_rts::Eq>::eq(
    t,
    <cry_rts::Z>::number(p.clone(), 0usize).as_arg(),
  ) { <cry_rts::Z>::number(p.clone(), 0usize) } else {
    if <cry_rts::Z as cry_rts::Eq>::eq(
      t,
      <cry_rts::Z>::number(p.clone(), 1usize).as_arg(),
    ) { r.clone_arg() } else {
      let i = find_leasti_inst_nat(p, m, t);
      if <num::BigInt as cry_rts::Eq>::eq(i.as_arg(), m) {
        todo!("error")
      } else {
        let b =
          cry_rts::exp::<cry_rts::Z, num::BigInt>(
            c,
            cry_rts::exp::<num::BigInt, num::BigInt>(
              <num::BigInt>::number((), 2usize).as_arg(),
              <num::BigInt as cry_rts::Ring>::sub(
                <num::BigInt as cry_rts::Ring>::sub(m, i.as_arg()).as_arg(),
                <num::BigInt>::number((), 1usize).as_arg(),
              )
                .as_arg(),
            )
              .as_arg(),
          );
        tonelli_shanksqx_1_loop_inst_nat(
          p,
          i.as_arg(),
          <cry_rts::Z as cry_rts::Ring>::mul(b.as_arg(), b.as_arg()).as_arg(),
          <cry_rts::Z as cry_rts::Ring>::mul(
            <cry_rts::Z as cry_rts::Ring>::mul(t, b.as_arg()).as_arg(),
            b.as_arg(),
          )
            .as_arg(),
          <cry_rts::Z as cry_rts::Ring>::mul(r, b.as_arg()).as_arg(),
        )
      }
    }
  }
}

/**
Finds a square root of a given quadratic residue using the Tonelli-Shanks
algorithm.

@pre type parameter p must be an odd prime
@pre the argument n is a quadratic residue modulo p
@see https://en.wikipedia.org/wiki/Tonelli%E2%80%93Shanks_algorithm

```cryptol
tonelli_shanks : {p} (prime p, p >= 3) => Z p -> Z p
```
*/
pub fn tonelli_shanks_inst_nat(p: &num::BigUint, n: &cry_rts::Z) -> cry_rts::Z {
  let __p5 =
    factor_out_pow2(<num::BigInt as cry_rts::Ring>::sub(
      <num::BigInt>::number((), p).as_arg(),
      <num::BigInt>::number((), 1usize).as_arg(),
    )
      .as_arg());
  let q = __p5.as_arg().0.as_arg().clone_arg();
  let s = __p5.as_arg().1.as_arg().clone_arg();
  let z =
    find_quadratic_non_residue_inst_nat(
      p,
      <cry_rts::Z>::number(p.clone(), 1usize).as_arg(),
    );
  let m = s;
  let c = cry_rts::exp::<cry_rts::Z, num::BigInt>(z.as_arg(), q.as_arg());
  let t = cry_rts::exp::<cry_rts::Z, num::BigInt>(n, q.as_arg());
  let r =
    cry_rts::exp::<cry_rts::Z, num::BigInt>(
      n,
      <num::BigInt>::div(
        <num::BigInt as cry_rts::Ring>::add(
          q.as_arg(),
          <num::BigInt>::number((), 1usize).as_arg(),
        )
          .as_arg(),
        <num::BigInt>::number((), 2usize).as_arg(),
      )
        .as_arg(),
    );
  tonelli_shanksqx_1_loop_inst_nat(
    p,
    m.as_arg(),
    c.as_arg(),
    t.as_arg(),
    r.as_arg(),
  )
}

/**
Finds a square root of a given quadratic residue using a combination
of methods.

@note Attempts some shortcuts due to Lagrange that speed up the
computation before applying the Tonelli-Shanks algorithm via
`tonelli_shanks` (which is more costly).

@pre type parameter p must be an odd prime
@pre the argument n is a quadratic residue modulo p

```cryptol
sqrtZ : {p} (prime p, p >= 3) => Z p -> Z p
```
*/
pub fn sqrt_z_inst_nat(p: &num::BigUint, n: &cry_rts::Z) -> cry_rts::Z {
  if <num::BigInt as cry_rts::Eq>::eq(
    <num::BigInt>::modulo(
      <num::BigInt>::number((), p).as_arg(),
      <num::BigInt>::number((), 4usize).as_arg(),
    )
      .as_arg(),
    <num::BigInt>::number((), 3usize).as_arg(),
  ) {
    cry_rts::exp::<cry_rts::Z, num::BigInt>(
      n,
      <num::BigInt>::div(
        <num::BigInt as cry_rts::Ring>::add(
          <num::BigInt>::number((), p).as_arg(),
          <num::BigInt>::number((), 1usize).as_arg(),
        )
          .as_arg(),
        <num::BigInt>::number((), 4usize).as_arg(),
      )
        .as_arg(),
    )
  } else {
    if <num::BigInt as cry_rts::Eq>::eq(
      <num::BigInt>::modulo(
        <num::BigInt>::number((), p).as_arg(),
        <num::BigInt>::number((), 8usize).as_arg(),
      )
        .as_arg(),
      <num::BigInt>::number((), 5usize).as_arg(),
    ) {
      let r =
        cry_rts::exp::<cry_rts::Z, num::BigInt>(
          n,
          <num::BigInt>::div(
            <num::BigInt as cry_rts::Ring>::add(
              <num::BigInt>::number((), p).as_arg(),
              <num::BigInt>::number((), 3usize).as_arg(),
            )
              .as_arg(),
            <num::BigInt>::number((), 8usize).as_arg(),
          )
            .as_arg(),
        );
      if is_quartic_residue_inst_nat(p, n) { r } else {
        <cry_rts::Z as cry_rts::Ring>::mul(
          r.as_arg(),
          cry_rts::exp::<cry_rts::Z, num::BigInt>(
            <cry_rts::Z>::number(p.clone(), 2usize).as_arg(),
            <num::BigInt>::div(
              <num::BigInt as cry_rts::Ring>::sub(
                <num::BigInt>::number((), p).as_arg(),
                <num::BigInt>::number((), 1usize).as_arg(),
              )
                .as_arg(),
              <num::BigInt>::number((), 4usize).as_arg(),
            )
              .as_arg(),
          )
            .as_arg(),
        )
      }
    } else { tonelli_shanks_inst_nat(p, n) }
  }
}

/**
Conversion of a bit vector to an element of Z n.

```cryptol
bv2Z : {k, n} (n >= 1) => [k] -> Z n
```
*/
pub fn bv2z_inst_sz_nat(
  k: usize,
  n: &num::BigUint,
  bv: cry_rts::DWordRef<'_>,
) -> cry_rts::Z {
  <cry_rts::Z as cry_rts::Ring>::from_integer(
    n.clone(),
    <cry_rts::DWord>::to_integer(bv).as_arg(),
  )
}

/**
Conversion of an element of Z n to a bit vector.

```cryptol
Z2bv : {k, n} (n >= 1) => Z n -> [k]
```
*/
pub fn z_2bv_inst_sz_nat(
  k: usize,
  n: &num::BigUint,
  z: &cry_rts::Z,
) -> cry_rts::DWord {
  <cry_rts::DWord as cry_rts::Ring>::from_integer(k, z.from_z().as_arg())
}

/**
Property that `tonelli_shanks n` produces the correct result.

@pre type parameter p must be an odd prime
@post if n is a quadratic residue, returns true iff `tonelli_shanks n`
correctly calculates one of the square roots of n modulo p
@post if n is a quadratic nonresidue, vacuously returns true

```cryptol
tonelli_shanks_correct : {p} (prime p, p >= 3) => Z p -> Bit
```
*/
pub fn tonelli_shanks_correct_inst_nat(
  p: &num::BigUint,
  n: &cry_rts::Z,
) -> bool {
  let r = tonelli_shanks_inst_nat(p, n);
  if is_quadratic_residue_inst_nat(p, n) {
    <cry_rts::Z as cry_rts::Eq>::eq(
      cry_rts::exp::<cry_rts::Z, num::BigInt>(
        r.as_arg(),
        <num::BigInt>::number((), 2usize).as_arg(),
      )
        .as_arg(),
      n,
    )
  } else { true }
}

/**
Computes the Legendre symbol.

@pre type parameter n must be an odd prime

```cryptol
legendre : {n} (prime n, n >= 3) => Z n -> Integer
```
*/
pub fn legendre_inst_sz(n: usize, z: &cry_rts::Z) -> num::BigInt {
  if <cry_rts::Z as cry_rts::Eq>::eq(
    z,
    <cry_rts::Z>::number(cry_rts::size_to_int(n), 0usize).as_arg(),
  ) { <num::BigInt>::number((), 0usize) } else {
    if <cry_rts::Z as cry_rts::Eq>::eq(
      cry_rts::exp::<cry_rts::Z, num::BigInt>(
        z,
        <num::BigInt>::div(
          <num::BigInt as cry_rts::Ring>::sub(
            <num::BigInt>::number((), n).as_arg(),
            <num::BigInt>::number((), 1usize).as_arg(),
          )
            .as_arg(),
          <num::BigInt>::number((), 2usize).as_arg(),
        )
          .as_arg(),
      )
        .as_arg(),
      <cry_rts::Z>::number(cry_rts::size_to_int(n), 1usize).as_arg(),
    ) { <num::BigInt>::number((), 1usize) } else {
      if <cry_rts::Z as cry_rts::Eq>::eq(
        cry_rts::exp::<cry_rts::Z, num::BigInt>(
          z,
          <num::BigInt>::div(
            <num::BigInt as cry_rts::Ring>::sub(
              <num::BigInt>::number((), n).as_arg(),
              <num::BigInt>::number((), 1usize).as_arg(),
            )
              .as_arg(),
            <num::BigInt>::number((), 2usize).as_arg(),
          )
            .as_arg(),
        )
          .as_arg(),
        <cry_rts::Z as cry_rts::Ring>::negate(<cry_rts::Z>::number(
          cry_rts::size_to_int(n),
          1usize,
        )
          .as_arg())
          .as_arg(),
      ) {
        <num::BigInt as cry_rts::Ring>::negate(<num::BigInt>::number((), 1usize)
          .as_arg())
      } else { todo!("error") }
    }
  }
}

/**
Finds a quadratic nonresidue starting the search from a given value.

@pre type parameter n must be an odd prime
@post returns a quadratic nonresidue not equal to zero

```cryptol
findQuadraticNonResidue : {n} (prime n, n >= 3) => Z n -> Z n
```
*/
pub fn find_quadratic_non_residue_inst_sz(
  n: usize,
  z: &cry_rts::Z,
) -> cry_rts::Z {
  if <num::BigInt as cry_rts::Eq>::eq(
    legendre_inst_sz(n, z).as_arg(),
    <num::BigInt as cry_rts::Ring>::negate(<num::BigInt>::number((), 1usize)
      .as_arg())
      .as_arg(),
  ) { z.clone_arg() } else {
    find_quadratic_non_residue_inst_sz(
      n,
      <cry_rts::Z as cry_rts::Ring>::add(
        z,
        <cry_rts::Z>::number(cry_rts::size_to_int(n), 1usize).as_arg(),
      )
        .as_arg(),
    )
  }
}

/**
```cryptol
findLeasti'aux : {p} (prime p, p >= 3) => Integer -> Integer -> Z p -> Integer
```
*/
pub fn find_leastiqx_1_aux_inst_sz(
  p: usize,
  m: &num::BigInt,
  i: &num::BigInt,
  t2i: &cry_rts::Z,
) -> num::BigInt {
  if <cry_rts::Z as cry_rts::Eq>::eq(
    t2i,
    <cry_rts::Z>::number(cry_rts::size_to_int(p), 1usize).as_arg(),
  ) { i.clone_arg() } else {
    find_leastiqx_1_aux_inst_sz(
      p,
      m,
      <num::BigInt as cry_rts::Ring>::add(
        i,
        <num::BigInt>::number((), 1usize).as_arg(),
      )
        .as_arg(),
      <cry_rts::Z as cry_rts::Ring>::mul(t2i, t2i).as_arg(),
    )
  }
}

/**
Utility function for `tonelli_shanks`.

@see https://en.wikipedia.org/wiki/Tonelli%E2%80%93Shanks_algorithm

```cryptol
findLeasti : {p} (prime p, p >= 3) => Integer -> Z p -> Integer
```
*/
pub fn find_leasti_inst_sz(
  p: usize,
  m: &num::BigInt,
  t: &cry_rts::Z,
) -> num::BigInt {
  find_leastiqx_1_aux_inst_sz(
    p,
    m,
    <num::BigInt>::number((), 1usize).as_arg(),
    <cry_rts::Z as cry_rts::Ring>::mul(t, t).as_arg(),
  )
}

/**
Utility function for `tonelli_shanks`.

@see https://en.wikipedia.org/wiki/Tonelli%E2%80%93Shanks_algorithm

```cryptol
tonelli_shanks'loop : {p} (prime p, p >= 3) => Integer -> Z p -> Z p -> Z p -> Z p
```
*/
pub fn tonelli_shanksqx_1_loop_inst_sz(
  p: usize,
  m: &num::BigInt,
  c: &cry_rts::Z,
  t: &cry_rts::Z,
  r: &cry_rts::Z,
) -> cry_rts::Z {
  if <cry_rts::Z as cry_rts::Eq>::eq(
    t,
    <cry_rts::Z>::number(cry_rts::size_to_int(p), 0usize).as_arg(),
  ) { <cry_rts::Z>::number(cry_rts::size_to_int(p), 0usize) } else {
    if <cry_rts::Z as cry_rts::Eq>::eq(
      t,
      <cry_rts::Z>::number(cry_rts::size_to_int(p), 1usize).as_arg(),
    ) { r.clone_arg() } else {
      let i = find_leasti_inst_sz(p, m, t);
      if <num::BigInt as cry_rts::Eq>::eq(i.as_arg(), m) {
        todo!("error")
      } else {
        let b =
          cry_rts::exp::<cry_rts::Z, num::BigInt>(
            c,
            cry_rts::exp::<num::BigInt, num::BigInt>(
              <num::BigInt>::number((), 2usize).as_arg(),
              <num::BigInt as cry_rts::Ring>::sub(
                <num::BigInt as cry_rts::Ring>::sub(m, i.as_arg()).as_arg(),
                <num::BigInt>::number((), 1usize).as_arg(),
              )
                .as_arg(),
            )
              .as_arg(),
          );
        tonelli_shanksqx_1_loop_inst_sz(
          p,
          i.as_arg(),
          <cry_rts::Z as cry_rts::Ring>::mul(b.as_arg(), b.as_arg()).as_arg(),
          <cry_rts::Z as cry_rts::Ring>::mul(
            <cry_rts::Z as cry_rts::Ring>::mul(t, b.as_arg()).as_arg(),
            b.as_arg(),
          )
            .as_arg(),
          <cry_rts::Z as cry_rts::Ring>::mul(r, b.as_arg()).as_arg(),
        )
      }
    }
  }
}

/**
Finds a square root of a given quadratic residue using the Tonelli-Shanks
algorithm.

@pre type parameter p must be an odd prime
@pre the argument n is a quadratic residue modulo p
@see https://en.wikipedia.org/wiki/Tonelli%E2%80%93Shanks_algorithm

```cryptol
tonelli_shanks : {p} (prime p, p >= 3) => Z p -> Z p
```
*/
pub fn tonelli_shanks_inst_sz(p: usize, n: &cry_rts::Z) -> cry_rts::Z {
  let __p5 =
    factor_out_pow2(<num::BigInt as cry_rts::Ring>::sub(
      <num::BigInt>::number((), p).as_arg(),
      <num::BigInt>::number((), 1usize).as_arg(),
    )
      .as_arg());
  let q = __p5.as_arg().0.as_arg().clone_arg();
  let s = __p5.as_arg().1.as_arg().clone_arg();
  let z =
    find_quadratic_non_residue_inst_sz(
      p,
      <cry_rts::Z>::number(cry_rts::size_to_int(p), 1usize).as_arg(),
    );
  let m = s;
  let c = cry_rts::exp::<cry_rts::Z, num::BigInt>(z.as_arg(), q.as_arg());
  let t = cry_rts::exp::<cry_rts::Z, num::BigInt>(n, q.as_arg());
  let r =
    cry_rts::exp::<cry_rts::Z, num::BigInt>(
      n,
      <num::BigInt>::div(
        <num::BigInt as cry_rts::Ring>::add(
          q.as_arg(),
          <num::BigInt>::number((), 1usize).as_arg(),
        )
          .as_arg(),
        <num::BigInt>::number((), 2usize).as_arg(),
      )
        .as_arg(),
    );
  tonelli_shanksqx_1_loop_inst_sz(
    p,
    m.as_arg(),
    c.as_arg(),
    t.as_arg(),
    r.as_arg(),
  )
}

/**
Checks if a given number is a quadratic residue in a
multiplicative modular group of prime order.

@pre type parameter n must be an odd prime
@note zero is considered a quadratic residue too

```cryptol
isQuadraticResidue : {n} (prime n, n >= 3) => Z n -> Bit
```
*/
pub fn is_quadratic_residue_inst_sz(n: usize, z: &cry_rts::Z) -> bool {
  <num::BigInt as cry_rts::Cmp>::ge(
    legendre_inst_sz(n, z).as_arg(),
    <num::BigInt>::number((), 0usize).as_arg(),
  )
}

/**
Property that `tonelli_shanks n` produces the correct result.

@pre type parameter p must be an odd prime
@post if n is a quadratic residue, returns true iff `tonelli_shanks n`
correctly calculates one of the square roots of n modulo p
@post if n is a quadratic nonresidue, vacuously returns true

```cryptol
tonelli_shanks_correct : {p} (prime p, p >= 3) => Z p -> Bit
```
*/
pub fn tonelli_shanks_correct_inst_sz(p: usize, n: &cry_rts::Z) -> bool {
  let r = tonelli_shanks_inst_sz(p, n);
  if is_quadratic_residue_inst_sz(p, n) {
    <cry_rts::Z as cry_rts::Eq>::eq(
      cry_rts::exp::<cry_rts::Z, num::BigInt>(
        r.as_arg(),
        <num::BigInt>::number((), 2usize).as_arg(),
      )
        .as_arg(),
      n,
    )
  } else { true }
}

/**
Property that `sqrtZ n` produces the correct result.

@pre type parameter p must be an odd prime
@post if n is a quadratic residue, returns true iff `sqrtZ n`
correctly calculates one of the square roots of n modulo p
@post if n is a quadratic nonresidue, vacuously returns true

```cryptol
sqrtZ_correct : {p} (prime p, p >= 3) => Z p -> Bit
```
*/
pub fn sqrt_z__correct_inst_nat(p: &num::BigUint, n: &cry_rts::Z) -> bool {
  let r = sqrt_z_inst_nat(p, n);
  if is_quadratic_residue_inst_nat(p, n) {
    <cry_rts::Z as cry_rts::Eq>::eq(
      cry_rts::exp::<cry_rts::Z, num::BigInt>(
        r.as_arg(),
        <num::BigInt>::number((), 2usize).as_arg(),
      )
        .as_arg(),
      n,
    )
  } else { true }
}

/**
Checks if a given number is a quartic residue in a
multiplicative modular group of prime order.

@pre type parameter n must be an odd prime
@note zero is considered a quartic residue too

```cryptol
isQuarticResidue : {n} (prime n, n >= 3) => Z n -> Bit
```
*/
pub fn is_quartic_residue_inst_sz(n: usize, z: &cry_rts::Z) -> bool {
  <cry_rts::Z as cry_rts::Eq>::eq(
    cry_rts::exp::<cry_rts::Z, num::BigInt>(
      z,
      <num::BigInt>::div(
        <num::BigInt as cry_rts::Ring>::sub(
          <num::BigInt>::number((), n).as_arg(),
          <num::BigInt>::number((), 1usize).as_arg(),
        )
          .as_arg(),
        <num::BigInt>::number((), 4usize).as_arg(),
      )
        .as_arg(),
    )
      .as_arg(),
    <cry_rts::Z>::number(cry_rts::size_to_int(n), 1usize).as_arg(),
  )
}

/**
Finds a square root of a given quadratic residue using a combination
of methods.

@note Attempts some shortcuts due to Lagrange that speed up the
computation before applying the Tonelli-Shanks algorithm via
`tonelli_shanks` (which is more costly).

@pre type parameter p must be an odd prime
@pre the argument n is a quadratic residue modulo p

```cryptol
sqrtZ : {p} (prime p, p >= 3) => Z p -> Z p
```
*/
pub fn sqrt_z_inst_sz(p: usize, n: &cry_rts::Z) -> cry_rts::Z {
  if <num::BigInt as cry_rts::Eq>::eq(
    <num::BigInt>::modulo(
      <num::BigInt>::number((), p).as_arg(),
      <num::BigInt>::number((), 4usize).as_arg(),
    )
      .as_arg(),
    <num::BigInt>::number((), 3usize).as_arg(),
  ) {
    cry_rts::exp::<cry_rts::Z, num::BigInt>(
      n,
      <num::BigInt>::div(
        <num::BigInt as cry_rts::Ring>::add(
          <num::BigInt>::number((), p).as_arg(),
          <num::BigInt>::number((), 1usize).as_arg(),
        )
          .as_arg(),
        <num::BigInt>::number((), 4usize).as_arg(),
      )
        .as_arg(),
    )
  } else {
    if <num::BigInt as cry_rts::Eq>::eq(
      <num::BigInt>::modulo(
        <num::BigInt>::number((), p).as_arg(),
        <num::BigInt>::number((), 8usize).as_arg(),
      )
        .as_arg(),
      <num::BigInt>::number((), 5usize).as_arg(),
    ) {
      let r =
        cry_rts::exp::<cry_rts::Z, num::BigInt>(
          n,
          <num::BigInt>::div(
            <num::BigInt as cry_rts::Ring>::add(
              <num::BigInt>::number((), p).as_arg(),
              <num::BigInt>::number((), 3usize).as_arg(),
            )
              .as_arg(),
            <num::BigInt>::number((), 8usize).as_arg(),
          )
            .as_arg(),
        );
      if is_quartic_residue_inst_sz(p, n) { r } else {
        <cry_rts::Z as cry_rts::Ring>::mul(
          r.as_arg(),
          cry_rts::exp::<cry_rts::Z, num::BigInt>(
            <cry_rts::Z>::number(cry_rts::size_to_int(p), 2usize).as_arg(),
            <num::BigInt>::div(
              <num::BigInt as cry_rts::Ring>::sub(
                <num::BigInt>::number((), p).as_arg(),
                <num::BigInt>::number((), 1usize).as_arg(),
              )
                .as_arg(),
              <num::BigInt>::number((), 4usize).as_arg(),
            )
              .as_arg(),
          )
            .as_arg(),
        )
      }
    } else { tonelli_shanks_inst_sz(p, n) }
  }
}

/**
Property that `sqrtZ n` produces the correct result.

@pre type parameter p must be an odd prime
@post if n is a quadratic residue, returns true iff `sqrtZ n`
correctly calculates one of the square roots of n modulo p
@post if n is a quadratic nonresidue, vacuously returns true

```cryptol
sqrtZ_correct : {p} (prime p, p >= 3) => Z p -> Bit
```
*/
pub fn sqrt_z__correct_inst_sz(p: usize, n: &cry_rts::Z) -> bool {
  let r = sqrt_z_inst_sz(p, n);
  if is_quadratic_residue_inst_sz(p, n) {
    <cry_rts::Z as cry_rts::Eq>::eq(
      cry_rts::exp::<cry_rts::Z, num::BigInt>(
        r.as_arg(),
        <num::BigInt>::number((), 2usize).as_arg(),
      )
        .as_arg(),
      n,
    )
  } else { true }
}
