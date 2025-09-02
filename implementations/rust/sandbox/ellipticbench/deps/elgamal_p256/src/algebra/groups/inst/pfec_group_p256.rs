/*! NIST P-256 Elliptic Curve defined in [FIPS-186-5]
@see https://doi.org/10.6028/NIST.FIPS.186-5

@author Frank Zeyda (frank.zeyda@freeandfair.us)
@copyright Free & Fair 2025
@version 0.1
*/
/*! Elliptic Curves over Prime Field Group

This is a wrapping of the cryptol-specs PFEC module
in order to implement the CyclicGroupI interface of
the E2EVIV algebraic framework.

@author Frank Zeyda (frank.zeyda@freeandfair.us)
@copyright Free & Fair 2025
@version 0.1
*/
#![allow(unused_variables)]
#![allow(unused_imports)]
use cry_rts::trait_methods::*;

/**
A point that satisfies the curve equation `y^2 = x^3 + ax + b`.
Sometimes this is called an "affine" representation.
[SP-800-186] Section 2.1.1.

```cryptol
enum Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point
```
*/
#[derive(Clone)]
pub enum Inimportat32point {
  Infinity(),
  Affine(cry_rts::Z, cry_rts::Z),
}

cry_rts::RefType! { Inimportat32point }

cry_rts::Global! {
  /**
  A point that satisfies the curve equation `y^2 = x^3 + ax + b`.
  Sometimes this is called an "affine" representation.
  [SP-800-186] Section 2.1.1.

  ```cryptol
  enum Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point
  ```
  */ _in__import_at__32_con__infinity_con_con: Inimportat32point = {
    Inimportat32point::Infinity()
  }
}

/**
A point that satisfies the curve equation `y^2 = x^3 + ax + b`.
Sometimes this is called an "affine" representation.
[SP-800-186] Section 2.1.1.

```cryptol
enum Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point
```
*/
pub fn _in__import_at__32_con__affine_con_con(
  anon: &cry_rts::Z,
  anon_1: &cry_rts::Z,
) -> Inimportat32point {
  Inimportat32point::Affine(anon.clone_arg(), anon_1.clone_arg())
}

cry_rts::Global! {
  /**
  Coefficient b that define the curve

  For a curve in (short) Weierstrass form, the equation is
  `y^2 = x^3 + ax + b`. Note that a is fixed to -3 by the
  EC curve implementation.
  @trace [SP-800-186] Section 2.1.1.

  ```cryptol
  b : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951
  ```
  */ b: cry_rts::Z = {
    crate::algebra::groups::inst::pfec_group_p256___where::b_inst_val::<cry_rts::Z>(num::BigUint::from_bytes_le(&[
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      1u8,
      0u8,
      0u8,
      0u8,
      255u8,
      255u8,
      255u8,
      255u8,
    ]))
  }
}

cry_rts::Global! {
  /**
  Coefficients that define the curve.
  For a curve in short-Weierstrass form, the equation is
  `y^2 = x^3 + ax + b`.
  See the `curveCoefficientsAreValid` property.
  [SP-800-186] Section 2.1.1.

  ```cryptol
  b : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951
  ```
  */ in_import_at__32_b: cry_rts::Z = { (&*b).as_arg().clone_arg() }
}

/**
 Finds a curve point, starting from a given x coordinate.

 The point (x, y) must satisfy the (short) Weierstrass equation
 `x^3 - 3x + b = y^2` since a is always -3 in PFEC.cry curves.

```cryptol
findPoint : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951 -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point
```
*/
pub fn in_import_at__32_find_point(x: &cry_rts::Z) -> Inimportat32point {
  let lhs =
    <cry_rts::Z as cry_rts::Ring>::add(
      <cry_rts::Z as cry_rts::Ring>::sub(
        cry_rts::exp::<cry_rts::Z, num::BigInt>(
          x,
          <num::BigInt>::number((), 3usize).as_arg(),
        )
          .as_arg(),
        <cry_rts::Z as cry_rts::Ring>::mul(
          <cry_rts::Z>::number(
            num::BigUint::from_bytes_le(&[
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              1u8,
              0u8,
              0u8,
              0u8,
              255u8,
              255u8,
              255u8,
              255u8,
            ]),
            3usize,
          )
            .as_arg(),
          x,
        )
          .as_arg(),
      )
        .as_arg(),
      (&*in_import_at__32_b).as_arg(),
    );
  if crate::algebra::utils::is_quadratic_residue_inst_nat(
    &num::BigUint::from_bytes_le(&[
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      1u8,
      0u8,
      0u8,
      0u8,
      255u8,
      255u8,
      255u8,
      255u8,
    ]),
    lhs.as_arg(),
  ) {
    _in__import_at__32_con__affine_con_con(
      x,
      crate::algebra::utils::sqrt_z_inst_nat(
        &num::BigUint::from_bytes_le(&[
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          1u8,
          0u8,
          0u8,
          0u8,
          255u8,
          255u8,
          255u8,
          255u8,
        ]),
        lhs.as_arg(),
      )
        .as_arg(),
    )
  } else {
    in_import_at__32_find_point(<cry_rts::Z as cry_rts::Ring>::add(
      x,
      <cry_rts::Z>::number(
        num::BigUint::from_bytes_le(&[
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          1u8,
          0u8,
          0u8,
          0u8,
          255u8,
          255u8,
          255u8,
          255u8,
        ]),
        1usize,
      )
        .as_arg(),
    )
      .as_arg())
  }
}

/**
Extract the x-coordinate `Z P` value, if the point is not the point at
infinity.

```cryptol
xCoord : Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Cryptol::Option
(Z 115792089210356248762697446949407573530086143415290314195533631308867097853951)
```
*/
pub fn in_import_at__32_x_coord(
  p: &Inimportat32point,
) -> crate::cryptol::OptionInstTy<cry_rts::Z> {
  match p.clone_arg() {
    Inimportat32point::Affine(x, __p6) => crate::cryptol::_some_con_inst_ty::<cry_rts::Z>(x
      .as_arg()),
    Inimportat32point::Infinity() => crate::cryptol::_none_con_inst_ty::<cry_rts::Z>(

    ),
  }
}

/**
 Decodes a curve point (not infinity) into a bit string.

 The type parameter `fixed` determines the bit-string length
 and the type parameter `twiddle` the number of twiddle bits
 to discard when decoding the x coordinate into a bit string.

 @note Using `lg2floor P` instead of `lg2 P` is crucial to
 avoid certain pathological situation where bit strings that
 exceed P cannot be encoded.

```cryptol
decPoint : {fixed, twiddle}
  (fixed + twiddle == 255) =>
  Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> [fixed]
```
*/
pub fn in_import_at__32_dec_point_inst_sz_sz(
  fixed: usize,
  twiddle: usize,
  p: &Inimportat32point,
) -> cry_rts::DWord {
  let x =
    match in_import_at__32_x_coord(p) {
      crate::cryptol::OptionInstTy::None() => todo!("error"),
      crate::cryptol::OptionInstTy::Some(v) => v,
    };
  crate::algebra::utils::z_2bv_inst_sz_nat(
    cry_rts::add_size(fixed, twiddle),
    &num::BigUint::from_bytes_le(&[
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      1u8,
      0u8,
      0u8,
      0u8,
      255u8,
      255u8,
      255u8,
      255u8,
    ]),
    x.as_arg(),
  )
    .as_arg()
    .take(fixed)
}

/**
 Encodes a bit string into a valid curve point.

 The approach is based on one of the methods (Sect. 3, (2))
 suggested by Neil Koblitz in Elliptic Curve Cryptosystems,
 @see https://doi.org/10.1090/S0025-5718-1987-0866109-5
 The type parameter `fixed` determines the bit-string length
 and the type parameter `twiddle` the number of twiddle bits
 to permute in order to find a valid curve point for `bv`.

 @note With a sufficiently large `twiddle`, the probability
 that this function fails becomes negligible: 2^(-(2^twiddle)).

 @note Using `lg2floor P` instead of `lg2 P` is crucial to
 avoid certain pathological situation where bit strings that
 exceed P cannot be encoded.

```cryptol
encBits : {fixed, twiddle}
  (fixed + twiddle == 255) =>
  [fixed] -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point
```
*/
pub fn in_import_at__32_enc_bits_inst_sz_sz(
  fixed: usize,
  twiddle: usize,
  bv: cry_rts::DWordRef<'_>,
) -> Inimportat32point {
  let bvqx_1_ext =
    bv.append(<cry_rts::DWord as cry_rts::Zero>::zero(twiddle).as_arg());


  let p =
    in_import_at__32_find_point(crate::algebra::utils::bv2z_inst_sz_nat(
      cry_rts::add_size(fixed, twiddle),
      &num::BigUint::from_bytes_le(&[
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        1u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ]),
      bvqx_1_ext.as_arg(),
    )
      .as_arg());
  let bvqx_1_dec =
    in_import_at__32_dec_point_inst_sz_sz(
      fixed,
      cry_rts::sub_size(255usize, fixed),
      p.as_arg(),
    );

  if <cry_rts::DWord as cry_rts::Eq>::eq(bv, bvqx_1_dec.as_arg()) { p } else {
    todo!("error")
  }
}

/**
Encoding a message as a group element

Uses Koblitz's approach (2) to encode a bit vector of
a given length `bits - k` into a valid curve point.
Note that k can be freely chosen within [1 ..< bits]
and determines the probability that the encoding of a
given bitstring fails, being approximately 2^(-(2^k)).
@see https://doi.org/10.1090/S0025-5718-1987-0866109-5

```cryptol
enc : [247] -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point
```
*/
pub fn enc(x: cry_rts::DWordRef<'_>) -> Inimportat32point {
  in_import_at__32_enc_bits_inst_sz_sz(247usize, 8usize, x)
}

/**
Convert from a projective to an affine representation.
[MATH-2008] Routine 2.2.2.

```cryptol
to_affine : {x : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 y : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 z : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951} -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point
```
*/
pub fn in_import_at__32_to_affine(
  p: &(cry_rts::Z, cry_rts::Z, cry_rts::Z),
) -> Inimportat32point {
  if <cry_rts::Z as cry_rts::Eq>::eq(
    p.2.as_arg(),
    <cry_rts::Z>::number(
      num::BigUint::from_bytes_le(&[
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        1u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ]),
      0usize,
    )
      .as_arg(),
  ) { (&*_in__import_at__32_con__infinity_con_con).as_arg().clone_arg() } else {
    let lambda = <cry_rts::Z>::recip(p.2.as_arg());
    _in__import_at__32_con__affine_con_con(
      <cry_rts::Z as cry_rts::Ring>::mul(
        cry_rts::exp::<cry_rts::Z, num::BigInt>(
          lambda.as_arg(),
          <num::BigInt>::number((), 2usize).as_arg(),
        )
          .as_arg(),
        p.0.as_arg(),
      )
        .as_arg(),
      <cry_rts::Z as cry_rts::Ring>::mul(
        cry_rts::exp::<cry_rts::Z, num::BigInt>(
          lambda.as_arg(),
          <num::BigInt>::number((), 3usize).as_arg(),
        )
          .as_arg(),
        p.1.as_arg(),
      )
        .as_arg(),
    )
  }
}

/**
```cryptol
InfinityProjective : {a, b, c} (Literal 0 c, Literal 1 b, Literal 1 a) => {x : a, y : b, z : c}
```
*/
pub fn in_import_at__32_infinity_projective_inst_ty_ty_ty<T, T1, T2>(
  t_len: T::Length,
  t_1_len: T1::Length,
  t_2_len: T2::Length,
) -> (T, T1, T2)
where
  T: cry_rts::Type,
  T1: cry_rts::Type,
  T2: cry_rts::Type,
  T: cry_rts::Literal,
  T1: cry_rts::Literal,
  T2: cry_rts::Literal,
{
  (
    <T>::number(t_len.clone(), 1usize),
    <T1>::number(t_1_len.clone(), 1usize),
    <T2>::number(t_2_len.clone(), 0usize),
  )
}

/**
Convert from an affine to a projective representation.
[MATH-2008] Routine 2.2.1.

```cryptol
to_projective : Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> {x : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 y : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 z : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951}
```
*/
pub fn in_import_at__32_to_projective(p: &Inimportat32point) -> (
  cry_rts::Z,
  cry_rts::Z,
  cry_rts::Z,
) {
  match p.clone_arg() {
    Inimportat32point::Affine(x, y) => (
      x,
      y,
      <cry_rts::Z>::number(
        num::BigUint::from_bytes_le(&[
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          1u8,
          0u8,
          0u8,
          0u8,
          255u8,
          255u8,
          255u8,
          255u8,
        ]),
        1usize,
      ),
    ),
    Inimportat32point::Infinity() => in_import_at__32_infinity_projective_inst_ty_ty_ty::<cry_rts::Z, cry_rts::Z, cry_rts::Z>(
      num::BigUint::from_bytes_le(&[
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        1u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ]),
      num::BigUint::from_bytes_le(&[
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        1u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ]),
      num::BigUint::from_bytes_le(&[
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        1u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ]),
    ),
  }
}

/**
Double an elliptic curve point.
[MATH-2008] Routine 2.2.6.

Requires that curve parameter `a = -3 mod P`

```cryptol
ec_double : {x : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 y : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 z : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951} -> {x : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 y : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 z : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951}
```
*/
pub fn in_import_at__32_ec_double(s: &(cry_rts::Z, cry_rts::Z, cry_rts::Z)) -> (
  cry_rts::Z,
  cry_rts::Z,
  cry_rts::Z,
) {
  let r7 =
    cry_rts::exp::<cry_rts::Z, num::BigInt>(
      s.2.as_arg(),
      <num::BigInt>::number((), 2usize).as_arg(),
    );
  let r8 = <cry_rts::Z as cry_rts::Ring>::sub(s.0.as_arg(), r7.as_arg());
  let r9 = <cry_rts::Z as cry_rts::Ring>::add(s.0.as_arg(), r7.as_arg());
  let r10 = <cry_rts::Z as cry_rts::Ring>::mul(r9.as_arg(), r8.as_arg());
  let r11 =
    crate::common::utils::mul3_inst_val::<cry_rts::Z>(
      num::BigUint::from_bytes_le(&[
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        1u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ]),
      r10.as_arg(),
    );
  let r12 = <cry_rts::Z as cry_rts::Ring>::mul(s.2.as_arg(), s.1.as_arg());
  let r13 =
    crate::common::utils::mul2_inst_val::<cry_rts::Z>(
      num::BigUint::from_bytes_le(&[
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        1u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ]),
      r12.as_arg(),
    );
  let r14 =
    cry_rts::exp::<cry_rts::Z, num::BigInt>(
      s.1.as_arg(),
      <num::BigInt>::number((), 2usize).as_arg(),
    );
  let r15 = <cry_rts::Z as cry_rts::Ring>::mul(s.0.as_arg(), r14.as_arg());
  let r16 =
    crate::common::utils::mul4_inst_val::<cry_rts::Z>(
      num::BigUint::from_bytes_le(&[
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        1u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ]),
      r15.as_arg(),
    );
  let r17 =
    cry_rts::exp::<cry_rts::Z, num::BigInt>(
      r11.as_arg(),
      <num::BigInt>::number((), 2usize).as_arg(),
    );
  let r18 =
    <cry_rts::Z as cry_rts::Ring>::sub(
      r17.as_arg(),
      crate::common::utils::mul2_inst_val::<cry_rts::Z>(
        num::BigUint::from_bytes_le(&[
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          1u8,
          0u8,
          0u8,
          0u8,
          255u8,
          255u8,
          255u8,
          255u8,
        ]),
        r16.as_arg(),
      )
        .as_arg(),
    );
  let r19 =
    cry_rts::exp::<cry_rts::Z, num::BigInt>(
      r14.as_arg(),
      <num::BigInt>::number((), 2usize).as_arg(),
    );
  let r20 =
    crate::common::utils::mul8_inst_val::<cry_rts::Z>(
      num::BigUint::from_bytes_le(&[
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        1u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ]),
      r19.as_arg(),
    );
  let r21 = <cry_rts::Z as cry_rts::Ring>::sub(r16.as_arg(), r18.as_arg());
  let r22 = <cry_rts::Z as cry_rts::Ring>::mul(r11.as_arg(), r21.as_arg());
  let r23 = <cry_rts::Z as cry_rts::Ring>::sub(r22.as_arg(), r20.as_arg());
  if <cry_rts::Z as cry_rts::Eq>::eq(
    s.2.as_arg(),
    <cry_rts::Z>::number(
      num::BigUint::from_bytes_le(&[
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        1u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ]),
      0usize,
    )
      .as_arg(),
  ) {
    in_import_at__32_infinity_projective_inst_ty_ty_ty::<cry_rts::Z, cry_rts::Z, cry_rts::Z>(
      num::BigUint::from_bytes_le(&[
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        1u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ]),
      num::BigUint::from_bytes_le(&[
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        1u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ]),
      num::BigUint::from_bytes_le(&[
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        1u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ]),
    )
  } else { (r18, r23, r13) }
}

/**
```cryptol
Zero : {a, b, c} (Literal 0 c, Literal 0 b, Literal 0 a) => {x : a, y : b, z : c}
```
*/
pub fn in_import_at__32_zero_inst_ty_ty_ty<T, T1, T2>(
  t_len: T::Length,
  t_1_len: T1::Length,
  t_2_len: T2::Length,
) -> (T, T1, T2)
where
  T: cry_rts::Type,
  T1: cry_rts::Type,
  T2: cry_rts::Type,
  T: cry_rts::Literal,
  T1: cry_rts::Literal,
  T2: cry_rts::Literal,
{
  (
    <T>::number(t_len.clone(), 0usize),
    <T1>::number(t_1_len.clone(), 0usize),
    <T2>::number(t_2_len.clone(), 0usize),
  )
}

/**
Addition of two elliptic curve points.

This will fail in the case where either of the input points are the
point at infinity or if the two input points are the same (if they
are the same, will return a default value of (0,0,0)).
[MATH-2008] Routine 2.2.7.

```cryptol
ec_add : {x : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 y : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 z : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951} -> {x : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 y : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 z : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951} -> {x : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 y : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 z : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951}
```
*/
pub fn in_import_at__32_ec_add(
  s: &(cry_rts::Z, cry_rts::Z, cry_rts::Z),
  t: &(cry_rts::Z, cry_rts::Z, cry_rts::Z),
) -> (cry_rts::Z, cry_rts::Z, cry_rts::Z) {
  let r3 = t.2.as_arg().clone_arg();
  let r4 =
    cry_rts::exp::<cry_rts::Z, num::BigInt>(
      r3.as_arg(),
      <num::BigInt>::number((), 2usize).as_arg(),
    );
  let r5 = <cry_rts::Z as cry_rts::Ring>::mul(s.0.as_arg(), r4.as_arg());
  let r6 = <cry_rts::Z as cry_rts::Ring>::mul(r3.as_arg(), r4.as_arg());
  let r7 = <cry_rts::Z as cry_rts::Ring>::mul(s.1.as_arg(), r6.as_arg());
  let __p10 =
    if <cry_rts::Z as cry_rts::Eq>::eq(
      t.2.as_arg(),
      <cry_rts::Z>::number(
        num::BigUint::from_bytes_le(&[
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          1u8,
          0u8,
          0u8,
          0u8,
          255u8,
          255u8,
          255u8,
          255u8,
        ]),
        1usize,
      )
        .as_arg(),
    ) {
      (
        s.0.as_arg().clone_arg(),
        s.1.as_arg().clone_arg(),
        s.2.as_arg().clone_arg(),
        t.0.as_arg().clone_arg(),
        t.1.as_arg().clone_arg(),
        t.2.as_arg().clone_arg(),
      )
    } else {
      (
        r5,
        r7,
        s.2.as_arg().clone_arg(),
        t.0.as_arg().clone_arg(),
        t.1.as_arg().clone_arg(),
        r3,
      )
    };
  let t1 = __p10.as_arg().0.as_arg().clone_arg();
  let t2 = __p10.as_arg().1.as_arg().clone_arg();
  let t3 = __p10.as_arg().2.as_arg().clone_arg();
  let t4 = __p10.as_arg().3.as_arg().clone_arg();
  let t5 = __p10.as_arg().4.as_arg().clone_arg();
  let t6 = __p10.as_arg().5.as_arg().clone_arg();
  let r9 =
    cry_rts::exp::<cry_rts::Z, num::BigInt>(
      t3.as_arg(),
      <num::BigInt>::number((), 2usize).as_arg(),
    );
  let r10 = <cry_rts::Z as cry_rts::Ring>::mul(t4.as_arg(), r9.as_arg());
  let r11 = <cry_rts::Z as cry_rts::Ring>::mul(t3.as_arg(), r9.as_arg());
  let r12 = <cry_rts::Z as cry_rts::Ring>::mul(t5.as_arg(), r11.as_arg());
  let r13 = <cry_rts::Z as cry_rts::Ring>::sub(t1.as_arg(), r10.as_arg());
  let r14 = <cry_rts::Z as cry_rts::Ring>::sub(t2.as_arg(), r12.as_arg());
  let r22 =
    <cry_rts::Z as cry_rts::Ring>::sub(
      crate::common::utils::mul2_inst_val::<cry_rts::Z>(
        num::BigUint::from_bytes_le(&[
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          1u8,
          0u8,
          0u8,
          0u8,
          255u8,
          255u8,
          255u8,
          255u8,
        ]),
        t1.as_arg(),
      )
        .as_arg(),
      r13.as_arg(),
    );
  let r23 =
    <cry_rts::Z as cry_rts::Ring>::sub(
      crate::common::utils::mul2_inst_val::<cry_rts::Z>(
        num::BigUint::from_bytes_le(&[
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          1u8,
          0u8,
          0u8,
          0u8,
          255u8,
          255u8,
          255u8,
          255u8,
        ]),
        t2.as_arg(),
      )
        .as_arg(),
      r14.as_arg(),
    );
  let r25 = <cry_rts::Z as cry_rts::Ring>::mul(t3.as_arg(), t6.as_arg());
  let r27 = <cry_rts::Z as cry_rts::Ring>::mul(r25.as_arg(), r13.as_arg());
  let r28 =
    cry_rts::exp::<cry_rts::Z, num::BigInt>(
      r13.as_arg(),
      <num::BigInt>::number((), 2usize).as_arg(),
    );
  let r29 = <cry_rts::Z as cry_rts::Ring>::mul(r13.as_arg(), r28.as_arg());
  let r30 = <cry_rts::Z as cry_rts::Ring>::mul(r22.as_arg(), r28.as_arg());
  let r31 =
    cry_rts::exp::<cry_rts::Z, num::BigInt>(
      r14.as_arg(),
      <num::BigInt>::number((), 2usize).as_arg(),
    );
  let r32 = <cry_rts::Z as cry_rts::Ring>::sub(r31.as_arg(), r30.as_arg());
  let r33 =
    <cry_rts::Z as cry_rts::Ring>::sub(
      r30.as_arg(),
      crate::common::utils::mul2_inst_val::<cry_rts::Z>(
        num::BigUint::from_bytes_le(&[
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          1u8,
          0u8,
          0u8,
          0u8,
          255u8,
          255u8,
          255u8,
          255u8,
        ]),
        r32.as_arg(),
      )
        .as_arg(),
    );
  let r34 = <cry_rts::Z as cry_rts::Ring>::mul(r14.as_arg(), r33.as_arg());
  let r35 = <cry_rts::Z as cry_rts::Ring>::mul(r23.as_arg(), r29.as_arg());
  let r36 = <cry_rts::Z as cry_rts::Ring>::sub(r34.as_arg(), r35.as_arg());
  let r37 =
    crate::common::utils::half_inst_nat(
      &num::BigUint::from_bytes_le(&[
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        1u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ]),
      r36.as_arg(),
    );
  if <cry_rts::Z as cry_rts::Eq>::eq(
    r13.as_arg(),
    <cry_rts::Z>::number(
      num::BigUint::from_bytes_le(&[
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        1u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ]),
      0usize,
    )
      .as_arg(),
  ) {
    if <cry_rts::Z as cry_rts::Eq>::eq(
      r14.as_arg(),
      <cry_rts::Z>::number(
        num::BigUint::from_bytes_le(&[
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          1u8,
          0u8,
          0u8,
          0u8,
          255u8,
          255u8,
          255u8,
          255u8,
        ]),
        0usize,
      )
        .as_arg(),
    ) {
      in_import_at__32_zero_inst_ty_ty_ty::<cry_rts::Z, cry_rts::Z, cry_rts::Z>(
        num::BigUint::from_bytes_le(&[
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          1u8,
          0u8,
          0u8,
          0u8,
          255u8,
          255u8,
          255u8,
          255u8,
        ]),
        num::BigUint::from_bytes_le(&[
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          1u8,
          0u8,
          0u8,
          0u8,
          255u8,
          255u8,
          255u8,
          255u8,
        ]),
        num::BigUint::from_bytes_le(&[
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          1u8,
          0u8,
          0u8,
          0u8,
          255u8,
          255u8,
          255u8,
          255u8,
        ]),
      )
    } else {
      in_import_at__32_infinity_projective_inst_ty_ty_ty::<cry_rts::Z, cry_rts::Z, cry_rts::Z>(
        num::BigUint::from_bytes_le(&[
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          1u8,
          0u8,
          0u8,
          0u8,
          255u8,
          255u8,
          255u8,
          255u8,
        ]),
        num::BigUint::from_bytes_le(&[
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          1u8,
          0u8,
          0u8,
          0u8,
          255u8,
          255u8,
          255u8,
          255u8,
        ]),
        num::BigUint::from_bytes_le(&[
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          1u8,
          0u8,
          0u8,
          0u8,
          255u8,
          255u8,
          255u8,
          255u8,
        ]),
      )
    }
  } else { (r32, r37, r27) }
}

/**
Checked addition of two elliptic curve points.

This method handles the cases where either of the input points are the
point at infinity or if the input points are the same.
[MATH-2008] Routine 2.2.8.

```cryptol
ec_full_add : {x : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 y : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 z : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951} -> {x : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 y : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 z : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951} -> {x : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 y : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 z : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951}
```
*/
pub fn in_import_at__32_ec_full_add(
  s: &(cry_rts::Z, cry_rts::Z, cry_rts::Z),
  t: &(cry_rts::Z, cry_rts::Z, cry_rts::Z),
) -> (cry_rts::Z, cry_rts::Z, cry_rts::Z) {
  let r = in_import_at__32_ec_add(s, t);
  if <cry_rts::Z as cry_rts::Eq>::eq(
    s.2.as_arg(),
    <cry_rts::Z>::number(
      num::BigUint::from_bytes_le(&[
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        1u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ]),
      0usize,
    )
      .as_arg(),
  ) { t.clone_arg() } else {
    if <cry_rts::Z as cry_rts::Eq>::eq(
      t.2.as_arg(),
      <cry_rts::Z>::number(
        num::BigUint::from_bytes_le(&[
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          1u8,
          0u8,
          0u8,
          0u8,
          255u8,
          255u8,
          255u8,
          255u8,
        ]),
        0usize,
      )
        .as_arg(),
    ) { s.clone_arg() } else {
      if <(cry_rts::Z, cry_rts::Z, cry_rts::Z) as cry_rts::Eq>::eq(
        r.as_arg(),
        (
          <cry_rts::Z>::number(
            num::BigUint::from_bytes_le(&[
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              1u8,
              0u8,
              0u8,
              0u8,
              255u8,
              255u8,
              255u8,
              255u8,
            ]),
            0usize,
          ),
          <cry_rts::Z>::number(
            num::BigUint::from_bytes_le(&[
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              1u8,
              0u8,
              0u8,
              0u8,
              255u8,
              255u8,
              255u8,
              255u8,
            ]),
            0usize,
          ),
          <cry_rts::Z>::number(
            num::BigUint::from_bytes_le(&[
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              1u8,
              0u8,
              0u8,
              0u8,
              255u8,
              255u8,
              255u8,
              255u8,
            ]),
            0usize,
          ),
        )
          .as_arg(),
      ) { in_import_at__32_ec_double(s) } else { r }
    }
  }
}

/**
Checked subtraction of two elliptic curve points.

This method handles the cases where either of the input points are the
point at infinity or if the input points are the same.
[MATH-2008] Routine 2.2.8.

```cryptol
ec_full_sub : {x : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 y : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 z : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951} -> {x : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 y : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 z : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951} -> {x : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 y : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 z : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951}
```
*/
pub fn in_import_at__32_ec_full_sub(
  s: &(cry_rts::Z, cry_rts::Z, cry_rts::Z),
  t: &(cry_rts::Z, cry_rts::Z, cry_rts::Z),
) -> (cry_rts::Z, cry_rts::Z, cry_rts::Z) {
  let u =
    (
      t.0.as_arg().clone_arg(),
      <cry_rts::Z as cry_rts::Ring>::negate(t.1.as_arg()),
      t.2.as_arg().clone_arg(),
    );
  let r = in_import_at__32_ec_full_add(s, u.as_arg());
  r
}

/**
Scalar multiplication on projective points
[MATH-2008] Routine 2.2.10.

The routine requires that 0 <= d < P. We enforce this constraint by
setting the type of `d` to be `Z P`, then converting it to an integer
for all actual uses.

```cryptol
ec_mult : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951 -> {x : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 y : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 z : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951} -> {x : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 y : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 z : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951}
```
*/
pub fn in_import_at__32_ec_mult(
  d: &cry_rts::Z,
  s: &(cry_rts::Z, cry_rts::Z, cry_rts::Z),
) -> (cry_rts::Z, cry_rts::Z, cry_rts::Z) {
  let sqx_1 =
    if <cry_rts::Z as cry_rts::Eq>::ne(
      s.2.as_arg(),
      <cry_rts::Z>::number(
        num::BigUint::from_bytes_le(&[
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          1u8,
          0u8,
          0u8,
          0u8,
          255u8,
          255u8,
          255u8,
          255u8,
        ]),
        1usize,
      )
        .as_arg(),
    ) {
      in_import_at__32_to_projective(in_import_at__32_to_affine(s).as_arg())
    } else { s.clone_arg() };
  let ks =
    crate::common::utils::zto_bv_inst_nat_sz(
      &num::BigUint::from_bytes_le(&[
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        1u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ]),
      258usize,
      d,
    );
  let hs =
    <cry_rts::DWord as cry_rts::Ring>::mul(
      <cry_rts::DWord>::number(258usize, 3usize).as_arg(),
      ks.as_arg(),
    );
  let rs =
    cry_rts::stream!(
      forall = [
        SI1: [ cry_rts::Stream<bool> ], SI2: [ cry_rts::Stream<bool> ]
      ], element = (
        cry_rts::Z,
        cry_rts::Z,
        cry_rts::Z,
      ), history = 1, init = vec!(
        in_import_at__32_infinity_projective_inst_ty_ty_ty::<cry_rts::Z, cry_rts::Z, cry_rts::Z>(
          num::BigUint::from_bytes_le(&[
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            1u8,
            0u8,
            0u8,
            0u8,
            255u8,
            255u8,
            255u8,
            255u8,
          ]),
          num::BigUint::from_bytes_le(&[
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            1u8,
            0u8,
            0u8,
            0u8,
            255u8,
            255u8,
            255u8,
            255u8,
          ]),
          num::BigUint::from_bytes_le(&[
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            1u8,
            0u8,
            0u8,
            0u8,
            255u8,
            255u8,
            255u8,
            255u8,
          ]),
        )
      ), capture = [
        s: (cry_rts::Z, cry_rts::Z, cry_rts::Z) = s.clone_arg(), anon: SI1 = ks
          .into_iter_bits_msb(), anon_1: SI2 = hs.into_iter_bits_msb()
      ], step = |this|{
        let ki = this.anon.next()?;
        let hi = this.anon_1.next()?;
        let ri = this.get_history(0usize);
        let double_r = in_import_at__32_ec_double(ri.as_arg());
        if <bool as cry_rts::Logic>::and(
          hi,
          <bool as cry_rts::Logic>::complement(ki),
        ) {
          in_import_at__32_ec_full_add(double_r.as_arg(), this.s.as_arg())
        } else {
          if <bool as cry_rts::Logic>::and(
            <bool as cry_rts::Logic>::complement(hi),
            ki,
          ) {
            in_import_at__32_ec_full_sub(double_r.as_arg(), this.s.as_arg())
          } else { double_r }
        }
      }
    );
  if <cry_rts::Z as cry_rts::Eq>::eq(
    d,
    <cry_rts::Z>::number(
      num::BigUint::from_bytes_le(&[
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        1u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ]),
      0usize,
    )
      .as_arg(),
  ) {
    in_import_at__32_to_projective((&*_in__import_at__32_con__infinity_con_con)
      .as_arg())
  } else {
    if <cry_rts::Z as cry_rts::Eq>::eq(
      d,
      <cry_rts::Z>::number(
        num::BigUint::from_bytes_le(&[
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          1u8,
          0u8,
          0u8,
          0u8,
          255u8,
          255u8,
          255u8,
          255u8,
        ]),
        1usize,
      )
        .as_arg(),
    ) { s.clone_arg() } else {
      if <cry_rts::Z as cry_rts::Eq>::eq(
        s.2.as_arg(),
        <cry_rts::Z>::number(
          num::BigUint::from_bytes_le(&[
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            1u8,
            0u8,
            0u8,
            0u8,
            255u8,
            255u8,
            255u8,
            255u8,
          ]),
          0usize,
        )
          .as_arg(),
      ) {
        in_import_at__32_to_projective((&*_in__import_at__32_con__infinity_con_con)
          .as_arg())
      } else {
        cry_rts::index_stream_back::<(
          cry_rts::Z,
          cry_rts::Z,
          cry_rts::Z,
        ), num::BigInt>(
          259usize,
          rs,
          <num::BigInt>::number((), 1usize).as_arg(),
        )
      }
    }
  }
}

/**
* Scalar multiplication of a curve point.

* Scalar multiplication is the process of adding `P` to itself `k` times
* for an integer `k`.
*
* [SEC1-v2] Section 2.2.1 doesn't explicitly specify an algorithm, but it
* notes that it can be computed efficiently using the addition rule and a
* variant of the double-and-add algorithm.
* In this implementation, we use a variant from [MATH-2008] (see `ec_mult`).
*
* Assumption: The `Point` passed as a parameter must be a valid EC point,
* otherwise this operation makes no sense. Use `isValid` to make sure
* the input is valid before calling this function.

```cryptol
scmul : Integer -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point
```
*/
pub fn in_import_at__32_scmul(
  k: &num::BigInt,
  p: &Inimportat32point,
) -> Inimportat32point {
  in_import_at__32_to_affine(in_import_at__32_ec_mult(
    <cry_rts::Z as cry_rts::Ring>::from_integer(
      num::BigUint::from_bytes_le(&[
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        1u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ]),
      k,
    )
      .as_arg(),
    in_import_at__32_to_projective(p).as_arg(),
  )
    .as_arg())
}

/**
Exponentiation operation (point multiplication)

```cryptol
exp : {a}
  (Integral a) =>
  Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> a -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point
```
*/
pub fn exp_inst_val<A>(
  a_len: A::Length,
  x: &Inimportat32point,
  k: A::Arg<'_>,
) -> Inimportat32point
where
  A: cry_rts::Type,
  A: cry_rts::Integral,
{
  let i = <A>::to_integer(k);
  in_import_at__32_scmul(i.as_arg(), x)
}

cry_rts::Global! {
  /**
  Coordinates of the base point `G = (Gx, Gy)`

  ```cryptol
  Gx : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951
  ```
  */ gx: cry_rts::Z = {
    crate::algebra::groups::inst::pfec_group_p256___where::gx_inst_val::<cry_rts::Z>(num::BigUint::from_bytes_le(&[
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      1u8,
      0u8,
      0u8,
      0u8,
      255u8,
      255u8,
      255u8,
      255u8,
    ]))
  }
}

cry_rts::Global! {
  /**
  Coordinates of the base point `G = (Gx, Gy)`.

  ```cryptol
  Gx : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951
  ```
  */ in_import_at__32_gx: cry_rts::Z = { (&*gx).as_arg().clone_arg() }
}

cry_rts::Global! {
  /**
  ```cryptol
  Gy : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951
  ```
  */ gy: cry_rts::Z = {
    crate::algebra::groups::inst::pfec_group_p256___where::gy_inst_val::<cry_rts::Z>(num::BigUint::from_bytes_le(&[
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      255u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      0u8,
      1u8,
      0u8,
      0u8,
      0u8,
      255u8,
      255u8,
      255u8,
      255u8,
    ]))
  }
}

cry_rts::Global! {
  /**
  ```cryptol
  Gy : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951
  ```
  */ in_import_at__32_gy: cry_rts::Z = { (&*gy).as_arg().clone_arg() }
}

cry_rts::Global! {
  /**
  Convenient `Point` representation of the base point `G`.

  ```cryptol
  G : Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point
  ```
  */ in_import_at__32_g: Inimportat32point = {
    _in__import_at__32_con__affine_con_con(
      (&*in_import_at__32_gx).as_arg(),
      (&*in_import_at__32_gy).as_arg(),
    )
  }
}

cry_rts::Global! {
  /**
  Generator element of the group (base point `G = (Gx, Gy)`)

  ```cryptol
  g : Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point
  ```
  */ g: Inimportat32point = { (&*in_import_at__32_g).as_arg().clone_arg() }
}

/**
Add two elliptic curve points together.

Assumption: The `Point`s passed as parameters must be valid EC points,
otherwise this operation makes no sense. Use `isValid` to make sure
the inputs are valid before calling this function.

```cryptol
add : Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point
```
*/
pub fn in_import_at__32_add(
  p1: &Inimportat32point,
  p2: &Inimportat32point,
) -> Inimportat32point {
  in_import_at__32_to_affine(in_import_at__32_ec_full_add(
    in_import_at__32_to_projective(p1).as_arg(),
    in_import_at__32_to_projective(p2).as_arg(),
  )
    .as_arg())
}

/**
Binary group operation (point addition)

```cryptol
gop : Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point
```
*/
pub fn gop(
  x: &Inimportat32point,
  x_1: &Inimportat32point,
) -> Inimportat32point {
  in_import_at__32_add(x, x_1)
}

/**
Subtract one curve point from another.

Assumption: The `Point`s passed as parameters must be valid EC points,
otherwise this operation makes no sense. Use `isValid` to make sure
the inputs are valid before calling this function.

```cryptol
sub : Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point
```
*/
pub fn in_import_at__32_sub(
  p1: &Inimportat32point,
  p2: &Inimportat32point,
) -> Inimportat32point {
  in_import_at__32_to_affine(in_import_at__32_ec_full_sub(
    in_import_at__32_to_projective(p1).as_arg(),
    in_import_at__32_to_projective(p2).as_arg(),
  )
    .as_arg())
}

/**
Inverse of a given element (point subtraction from Infinity)

```cryptol
inv : Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point
```
*/
pub fn inv(x: &Inimportat32point) -> Inimportat32point {
  in_import_at__32_sub((&*_in__import_at__32_con__infinity_con_con).as_arg(), x)
}

cry_rts::Global! {
  /**
  Coefficient that defines the curve.
  For a curve in short-Weierstrass form, the equation is
  `y^2 = x^3 + ax + b`.
  See the `curveCoefficientsAreValid` property.
  [SP-800-186] Section 2.1.1.

  Due to restrictions on the underlying elliptic curve operations, the
  a-coordinate must be -3. This is the case for all NIST-standardized
  prime order fields in short-Weierstrass form.

  ```cryptol
  a : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951
  ```
  */ in_import_at__32_a: cry_rts::Z = {
    <cry_rts::Z as cry_rts::Ring>::negate(<cry_rts::Z>::number(
      num::BigUint::from_bytes_le(&[
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        1u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ]),
      3usize,
    )
      .as_arg())
  }
}

/**
Check that a given point is on the curve -- either it is the point at
infinity or it satisfies the curve equation.
[SP-800-186] Section 2.1.1.
[SEC1-v2] Section 2.2.1.
[MATH-2008] Routine 2.2.5.

Note: by definition, the coordinates of an affine point will be correctly
formed (e.g. in the range [0, P-1]), because they are of type `Z P`.

```cryptol
isValid : Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Bit
```
*/
pub fn in_import_at__32_is_valid(point: &Inimportat32point) -> bool {
  match point.clone_arg() {
    Inimportat32point::Affine(x, y) => <cry_rts::Z as cry_rts::Eq>::eq(
      cry_rts::exp::<cry_rts::Z, num::BigInt>(
        y.as_arg(),
        <num::BigInt>::number((), 2usize).as_arg(),
      )
        .as_arg(),
      <cry_rts::Z as cry_rts::Ring>::add(
        <cry_rts::Z as cry_rts::Ring>::add(
          cry_rts::exp::<cry_rts::Z, num::BigInt>(
            x.as_arg(),
            <num::BigInt>::number((), 3usize).as_arg(),
          )
            .as_arg(),
          <cry_rts::Z as cry_rts::Ring>::mul(
            (&*in_import_at__32_a).as_arg(),
            x.as_arg(),
          )
            .as_arg(),
        )
          .as_arg(),
        (&*in_import_at__32_b).as_arg(),
      )
        .as_arg(),
    ),
    Inimportat32point::Infinity() => true,
  }
}

/**
Carrier set of the group (curve points + Infinity)

```cryptol
G : Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Bit
```
*/
pub fn g_1(x: &Inimportat32point) -> bool {
  in_import_at__32_is_valid(x)
}

/**
Decoding a group element into a message

Uses Koblitz's approach (2) to decode a valid elliptic
curve point into a bit vector of length `bits - k`.
Note that k can be freely chosen within [1 ..< bits]
and must be the same value used when encoding with enc.
@see https://doi.org/10.1090/S0025-5718-1987-0866109-5

```cryptol
dec : Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> [247]
```
*/
pub fn dec(x: &Inimportat32point) -> cry_rts::DWord {
  in_import_at__32_dec_point_inst_sz_sz(247usize, 8usize, x)
}

/**
 Property to check that `findPoint` returns a valid curve point.

 The `findPoint` function that is verified is defined above.

```cryptol
findPoint_isValid : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951 -> Bit
```
*/
pub fn in_import_at__32_find_point_is_valid(x: &cry_rts::Z) -> bool {
  in_import_at__32_is_valid(in_import_at__32_find_point(x).as_arg())
}

/**
 Property to check that `decPoint` is the inverse of `encBits`.

 @note Since numeric type `bits` can be freely chosen, it is
 important to choose `type k = (lg2 P) - bits` large enough so
 that the probability for failing to encode a bit string into
 the curve becomes negligible, being estimated by 2^(-(2^k)).

```cryptol
encBits_decPoint_inverse : {bits} (bits <= 255) => [bits] -> Bit
```
*/
pub fn in_import_at__32_enc_bits_dec_point_inverse_inst_sz(
  bits: usize,
  bv: cry_rts::DWordRef<'_>,
) -> bool {
  <cry_rts::DWord as cry_rts::Eq>::eq(
    in_import_at__32_dec_point_inst_sz_sz(
      bits,
      cry_rts::sub_size(255usize, bits),
      in_import_at__32_enc_bits_inst_sz_sz(
        bits,
        cry_rts::sub_size(255usize, bits),
        bv,
      )
        .as_arg(),
    )
      .as_arg(),
    bv,
  )
}

cry_rts::Global! {
  /**
  For curves in short-Weierstrass form, the following inequality must hold:
       4a^3 + 27b^2 != 0
  [SP-800-186] Section 2.1.1.

  ```repl
  :prove curveCoefficientsAreValid
  ```

  ```cryptol
  curveCoefficientsAreValid : Bit
  ```
  */ in_import_at__32_curve_coefficients_are_valid: bool = {
    let _27 =
      <cry_rts::Z as cry_rts::Ring>::from_integer(
        num::BigUint::from_bytes_le(&[
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          1u8,
          0u8,
          0u8,
          0u8,
          255u8,
          255u8,
          255u8,
          255u8,
        ]),
        <num::BigInt>::number((), 27usize).as_arg(),
      );
    <cry_rts::Z as cry_rts::Eq>::ne(
      <cry_rts::Z as cry_rts::Ring>::add(
        <cry_rts::Z as cry_rts::Ring>::mul(
          <cry_rts::Z>::number(
            num::BigUint::from_bytes_le(&[
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              1u8,
              0u8,
              0u8,
              0u8,
              255u8,
              255u8,
              255u8,
              255u8,
            ]),
            4usize,
          )
            .as_arg(),
          cry_rts::exp::<cry_rts::Z, num::BigInt>(
            (&*in_import_at__32_a).as_arg(),
            <num::BigInt>::number((), 3usize).as_arg(),
          )
            .as_arg(),
        )
          .as_arg(),
        <cry_rts::Z as cry_rts::Ring>::mul(
          _27.as_arg(),
          cry_rts::exp::<cry_rts::Z, num::BigInt>(
            (&*in_import_at__32_b).as_arg(),
            <num::BigInt>::number((), 2usize).as_arg(),
          )
            .as_arg(),
        )
          .as_arg(),
      )
        .as_arg(),
      <cry_rts::Z>::number(
        num::BigUint::from_bytes_le(&[
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          1u8,
          0u8,
          0u8,
          0u8,
          255u8,
          255u8,
          255u8,
          255u8,
        ]),
        0usize,
      )
        .as_arg(),
    )
  }
}

/**
Check equality of two affine points.

I don't know if this is explicitly specified anywhere because it's just
by definition.

```cryptol
affineEq : Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Bit
```
*/
pub fn in_import_at__32_affine_eq(
  p1: &Inimportat32point,
  p2: &Inimportat32point,
) -> bool {
  match p1.clone_arg() {
    Inimportat32point::Affine(x, y) => match p2.clone_arg() {
      Inimportat32point::Affine(xqx_1, yqx_1) => <bool as cry_rts::Logic>::and(
        <cry_rts::Z as cry_rts::Eq>::eq(x.as_arg(), xqx_1.as_arg()),
        <cry_rts::Z as cry_rts::Eq>::eq(y.as_arg(), yqx_1.as_arg()),
      ),
      __p2 => false,
    },
    Inimportat32point::Infinity() => match p2.clone_arg() {
      Inimportat32point::Infinity() => true,
      __p1 => false,
    },
  }
}

/**
```cryptol
~* : Integer -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point
```
*/
pub fn in_import_at__32_op_tilde_star(
  x: &num::BigInt,
  x_1: &Inimportat32point,
) -> Inimportat32point {
  in_import_at__32_scmul(x, x_1)
}

cry_rts::Global! {
  /**
  G must be of order `n`.
  ```repl
  :prove gOrderIsN
  ```

  ```cryptol
  gOrderIsN : Bit
  ```
  */ in_import_at__32_g_order_is_n: bool = {
    in_import_at__32_affine_eq(
      (&*in_import_at__32_g).as_arg(),
      in_import_at__32_op_tilde_star(
        <num::BigInt as cry_rts::Ring>::add(
          <num::BigInt>::number(
            (),
            &num::BigUint::from_bytes_le(&[
              81u8,
              37u8,
              99u8,
              252u8,
              194u8,
              202u8,
              185u8,
              243u8,
              132u8,
              158u8,
              23u8,
              167u8,
              173u8,
              250u8,
              230u8,
              188u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              0u8,
              0u8,
              0u8,
              0u8,
              255u8,
              255u8,
              255u8,
              255u8,
            ]),
          )
            .as_arg(),
          <num::BigInt>::number((), 1usize).as_arg(),
        )
          .as_arg(),
        (&*in_import_at__32_g).as_arg(),
      )
        .as_arg(),
    )
  }
}

cry_rts::Global! {
  /**
  `G` must be a valid point on the curve.
  ```repl
  :prove gIsValid
  ```

  ```cryptol
  gIsValid : Bit
  ```
  */ in_import_at__32_g_is_valid: bool = {
    in_import_at__32_is_valid((&*in_import_at__32_g).as_arg())
  }
}

/**
Compute a valid curve point from a random `k` and the base point `G`.

`k` is in the range [0, h * n), where `h * n` is the order of the
elliptic curve.
All the standardized NIST prime-order curves have (as the name suggests)
prime order and cofactor 1.

NB: If the cofactor `h` is not 1, this function will not derive points
on the curve uniformly. When the cofactor is 1, that means the group is
cyclic and can be generated by a single point. When it's not 1, the group
has a large cyclic subgroup that is generated by `G`, but it's not the
entire group.

The scalar multiplication specification specifically allows
multiplication by `k` in the range [0, P), hence the conversion.

```cryptol
validPointFromK : Z 115792089210356248762697446949407573529996955224135760342422259061068512044369 -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point
```
*/
pub fn in_import_at__32_valid_point_from_k(
  k: &cry_rts::Z,
) -> Inimportat32point {
  let _k =
    <cry_rts::Z as cry_rts::Ring>::from_integer(
      num::BigUint::from_bytes_le(&[
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        1u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ]),
      k.from_z().as_arg(),
    );
  in_import_at__32_to_affine(in_import_at__32_ec_mult(
    _k.as_arg(),
    in_import_at__32_to_projective((&*in_import_at__32_g).as_arg()).as_arg(),
  )
    .as_arg())
}

/**
Addition is a closed operation: the sum of two valid elliptic curve
points is also on the curve.
```repl
:check addIsClosed
```

```cryptol
addIsClosed : Z 115792089210356248762697446949407573529996955224135760342422259061068512044369 -> Z 115792089210356248762697446949407573529996955224135760342422259061068512044369 -> Bit
```
*/
pub fn in_import_at__32_add_is_closed(
  k1: &cry_rts::Z,
  k2: &cry_rts::Z,
) -> bool {
  let p1 = in_import_at__32_valid_point_from_k(k1);
  let p2 = in_import_at__32_valid_point_from_k(k2);
  in_import_at__32_is_valid(in_import_at__32_add(p1.as_arg(), p2.as_arg())
    .as_arg())
}

/**
Double an elliptic curve point.

Assumption: The `Point` passed as a parameter must be a valid EC point,
otherwise this operation makes no sense. Use `isValid` to make sure
the input is valid before calling this function.

```cryptol
double : Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point
```
*/
pub fn in_import_at__32_double(p: &Inimportat32point) -> Inimportat32point {
  in_import_at__32_to_affine(in_import_at__32_ec_double(in_import_at__32_to_projective(p)
    .as_arg())
    .as_arg())
}

/**
Doubling is a closed operation: the double of a valid elliptic
curve point is also on the curve.
```repl
:check doubleIsClosed
```

```cryptol
doubleIsClosed : Z 115792089210356248762697446949407573529996955224135760342422259061068512044369 -> Bit
```
*/
pub fn in_import_at__32_double_is_closed(k: &cry_rts::Z) -> bool {
  let p = in_import_at__32_valid_point_from_k(k);
  in_import_at__32_is_valid(in_import_at__32_double(p.as_arg()).as_arg())
}

/**
Subtraction is a closed operation: the difference of two valid elliptic
curve points is also on the curve.
```repl
:check subIsClosed
```

```cryptol
subIsClosed : Z 115792089210356248762697446949407573529996955224135760342422259061068512044369 -> Z 115792089210356248762697446949407573529996955224135760342422259061068512044369 -> Bit
```
*/
pub fn in_import_at__32_sub_is_closed(
  k1: &cry_rts::Z,
  k2: &cry_rts::Z,
) -> bool {
  let p1 = in_import_at__32_valid_point_from_k(k1);
  let p2 = in_import_at__32_valid_point_from_k(k2);
  in_import_at__32_is_valid(in_import_at__32_sub(p1.as_arg(), p2.as_arg())
    .as_arg())
}

/**
Scalar multiplication is a closed operation: the result must also be on the
curve.
```repl
:check scmulIsClosed
```

```cryptol
scmulIsClosed : Integer -> Bit
```
*/
pub fn in_import_at__32_scmul_is_closed(m: &num::BigInt) -> bool {
  in_import_at__32_is_valid(in_import_at__32_op_tilde_star(
    m,
    (&*in_import_at__32_g).as_arg(),
  )
    .as_arg())
}

/**
Scalar multiplication is commutative.
```repl
:check scmul_commutes
```

```cryptol
scmul_commutes : Integer -> Integer -> Bit
```
*/
pub fn in_import_at__32_scmul_commutes(
  m: &num::BigInt,
  mqx_1: &num::BigInt,
) -> bool {
  in_import_at__32_affine_eq(
    in_import_at__32_op_tilde_star(
      m,
      in_import_at__32_op_tilde_star(mqx_1, (&*in_import_at__32_g).as_arg())
        .as_arg(),
    )
      .as_arg(),
    in_import_at__32_op_tilde_star(
      mqx_1,
      in_import_at__32_op_tilde_star(m, (&*in_import_at__32_g).as_arg())
        .as_arg(),
    )
      .as_arg(),
  )
}

/**
Optimized routine to affinify and projectify four points at once
(or do nothing, if any of the points are the point at infinity).

This optimization is designed for use in `ec_twin_mult` and should not
be used in other settings without checking that its behavior is suitable.
[MATH-2008] Section 2.2, Note 8.

```cryptol
twin_normalize : {A : {x : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
  y : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
  z : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951},
 B : {x : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
  y : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
  z : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951},
 C : {x : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
  y : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
  z : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951},
 D : {x : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
  y : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
  z : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951}} -> {A : {x : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
  y : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
  z : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951},
 B : {x : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
  y : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
  z : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951},
 C : {x : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
  y : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
  z : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951},
 D : {x : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
  y : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
  z : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951}}
```
*/
pub fn in_import_at__32_twin_normalize(
  __p11: &(
    (cry_rts::Z, cry_rts::Z, cry_rts::Z),
    (cry_rts::Z, cry_rts::Z, cry_rts::Z),
    (cry_rts::Z, cry_rts::Z, cry_rts::Z),
    (cry_rts::Z, cry_rts::Z, cry_rts::Z),
  ),
) -> (
  (cry_rts::Z, cry_rts::Z, cry_rts::Z),
  (cry_rts::Z, cry_rts::Z, cry_rts::Z),
  (cry_rts::Z, cry_rts::Z, cry_rts::Z),
  (cry_rts::Z, cry_rts::Z, cry_rts::Z),
) {
  let d = __p11.3.as_arg().clone_arg();
  let c = __p11.2.as_arg().clone_arg();
  let b_1 = __p11.1.as_arg().clone_arg();
  let a = __p11.0.as_arg().clone_arg();
  if <bool as cry_rts::Logic>::or(
    <cry_rts::Z as cry_rts::Eq>::eq(
      a.as_arg().2.as_arg(),
      <cry_rts::Z>::number(
        num::BigUint::from_bytes_le(&[
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          1u8,
          0u8,
          0u8,
          0u8,
          255u8,
          255u8,
          255u8,
          255u8,
        ]),
        0usize,
      )
        .as_arg(),
    ),
    <bool as cry_rts::Logic>::or(
      <cry_rts::Z as cry_rts::Eq>::eq(
        b_1.as_arg().2.as_arg(),
        <cry_rts::Z>::number(
          num::BigUint::from_bytes_le(&[
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            1u8,
            0u8,
            0u8,
            0u8,
            255u8,
            255u8,
            255u8,
            255u8,
          ]),
          0usize,
        )
          .as_arg(),
      ),
      <bool as cry_rts::Logic>::or(
        <cry_rts::Z as cry_rts::Eq>::eq(
          c.as_arg().2.as_arg(),
          <cry_rts::Z>::number(
            num::BigUint::from_bytes_le(&[
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              1u8,
              0u8,
              0u8,
              0u8,
              255u8,
              255u8,
              255u8,
              255u8,
            ]),
            0usize,
          )
            .as_arg(),
        ),
        <cry_rts::Z as cry_rts::Eq>::eq(
          d.as_arg().2.as_arg(),
          <cry_rts::Z>::number(
            num::BigUint::from_bytes_le(&[
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              1u8,
              0u8,
              0u8,
              0u8,
              255u8,
              255u8,
              255u8,
              255u8,
            ]),
            0usize,
          )
            .as_arg(),
        ),
      ),
    ),
  ) { (a, b_1, c, d) } else {
    let ab =
      <cry_rts::Z as cry_rts::Ring>::mul(
        a.as_arg().2.as_arg(),
        b_1.as_arg().2.as_arg(),
      );
    let cd =
      <cry_rts::Z as cry_rts::Ring>::mul(
        c.as_arg().2.as_arg(),
        d.as_arg().2.as_arg(),
      );
    let abc =
      <cry_rts::Z as cry_rts::Ring>::mul(ab.as_arg(), c.as_arg().2.as_arg());
    let abd =
      <cry_rts::Z as cry_rts::Ring>::mul(ab.as_arg(), d.as_arg().2.as_arg());
    let acd =
      <cry_rts::Z as cry_rts::Ring>::mul(a.as_arg().2.as_arg(), cd.as_arg());
    let bcd =
      <cry_rts::Z as cry_rts::Ring>::mul(b_1.as_arg().2.as_arg(), cd.as_arg());
    let abcd = <cry_rts::Z as cry_rts::Ring>::mul(ab.as_arg(), cd.as_arg());
    let e = <cry_rts::Z>::recip(abcd.as_arg());
    let a_inv = <cry_rts::Z as cry_rts::Ring>::mul(e.as_arg(), bcd.as_arg());
    let b_inv = <cry_rts::Z as cry_rts::Ring>::mul(e.as_arg(), acd.as_arg());
    let c_inv = <cry_rts::Z as cry_rts::Ring>::mul(e.as_arg(), abd.as_arg());
    let d_inv = <cry_rts::Z as cry_rts::Ring>::mul(e.as_arg(), abc.as_arg());
    let normalize_from_inv =
      <cry_rts::Fn2<cry_rts::O<(
        cry_rts::Z,
        cry_rts::Z,
        cry_rts::Z,
      )>, cry_rts::O<cry_rts::Z>, _>>::new(move |p, inv_1| in_import_at__32_to_projective(_in__import_at__32_con__affine_con_con(
        <cry_rts::Z as cry_rts::Ring>::mul(
          cry_rts::exp::<cry_rts::Z, num::BigInt>(
            inv_1.as_arg(),
            <num::BigInt>::number((), 2usize).as_arg(),
          )
            .as_arg(),
          p.as_arg().0.as_arg(),
        )
          .as_arg(),
        <cry_rts::Z as cry_rts::Ring>::mul(
          cry_rts::exp::<cry_rts::Z, num::BigInt>(
            inv_1.as_arg(),
            <num::BigInt>::number((), 3usize).as_arg(),
          )
            .as_arg(),
          p.as_arg().1.as_arg(),
        )
          .as_arg(),
      )
        .as_arg()));
    (
      (normalize_from_inv)(a, a_inv),
      (normalize_from_inv)(b_1, b_inv),
      (normalize_from_inv)(c, c_inv),
      (normalize_from_inv)(d, d_inv),
    )
  }
}

/**
Twin multiplication computes `[d0]S + [d1]T`.
[MATH-2008] Routine 2.2.12.

[MATH-2008] Section 2.2, Note 8 describes an optimization that can be
made by converting the input points between affine and projective
representations. That is not included here.

```cryptol
ec_twin_mult : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951 -> {x : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 y : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 z : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951} -> Z 115792089210356248762697446949407573530086143415290314195533631308867097853951 -> {x : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 y : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 z : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951} -> {x : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 y : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951,
 z : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951}
```
*/
pub fn in_import_at__32_ec_twin_mult(
  d0: &cry_rts::Z,
  s: &(cry_rts::Z, cry_rts::Z, cry_rts::Z),
  d1: &cry_rts::Z,
  t: &(cry_rts::Z, cry_rts::Z, cry_rts::Z),
) -> (cry_rts::Z, cry_rts::Z, cry_rts::Z) {
  let sp_t = in_import_at__32_ec_full_add(s, t);
  let sm_t = in_import_at__32_ec_full_sub(s, t);
  let __p7 =
    in_import_at__32_twin_normalize((s.clone_arg(), t.clone_arg(), sp_t, sm_t)
      .as_arg());
  let sqx_1 = __p7.as_arg().0.as_arg().clone_arg();
  let tqx_1 = __p7.as_arg().1.as_arg().clone_arg();
  let sp_tqx_1 = __p7.as_arg().2.as_arg().clone_arg();
  let sm_tqx_1 = __p7.as_arg().3.as_arg().clone_arg();
  let e0s =
    crate::common::utils::zto_bv_inst_nat_sz(
      &num::BigUint::from_bytes_le(&[
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        1u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ]),
      256usize,
      d0,
    );
  let e1s =
    crate::common::utils::zto_bv_inst_nat_sz(
      &num::BigUint::from_bytes_le(&[
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        1u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ]),
      256usize,
      d1,
    );
  let c =
    vec!(
      cry_rts::DWord::from_stream_msb(2usize, vec!(false, false).into_iter())
        .as_arg()
        .append(e0s
          .as_arg()
          .take(4usize)
          .as_arg()), cry_rts::DWord::from_stream_msb(
        2usize,
        vec!(false, false).into_iter(),
      )
        .as_arg()
        .append(e1s.as_arg().take(4usize).as_arg())
    );
  let f =
    <cry_rts::Fn1<cry_rts::O<cry_rts::DWord>, _>>::new(move |t_1| if <bool as cry_rts::Logic>::and(
      <cry_rts::DWord as cry_rts::Cmp>::le(
        <cry_rts::DWord>::number(5usize, 18usize).as_arg(),
        t_1.as_arg(),
      ),
      <cry_rts::DWord as cry_rts::Cmp>::lt(
        t_1.as_arg(),
        <cry_rts::DWord>::number(5usize, 22usize).as_arg(),
      ),
    ) { <cry_rts::DWord>::number(5usize, 9usize) } else {
      if <bool as cry_rts::Logic>::and(
        <cry_rts::DWord as cry_rts::Cmp>::le(
          <cry_rts::DWord>::number(5usize, 14usize).as_arg(),
          t_1.as_arg(),
        ),
        <cry_rts::DWord as cry_rts::Cmp>::lt(
          t_1.as_arg(),
          <cry_rts::DWord>::number(5usize, 18usize).as_arg(),
        ),
      ) { <cry_rts::DWord>::number(5usize, 10usize) } else {
        if <bool as cry_rts::Logic>::and(
          <cry_rts::DWord as cry_rts::Cmp>::le(
            <cry_rts::DWord>::number(5usize, 22usize).as_arg(),
            t_1.as_arg(),
          ),
          <cry_rts::DWord as cry_rts::Cmp>::lt(
            t_1.as_arg(),
            <cry_rts::DWord>::number(5usize, 24usize).as_arg(),
          ),
        ) { <cry_rts::DWord>::number(5usize, 11usize) } else {
          if <bool as cry_rts::Logic>::and(
            <cry_rts::DWord as cry_rts::Cmp>::le(
              <cry_rts::DWord>::number(5usize, 4usize).as_arg(),
              t_1.as_arg(),
            ),
            <cry_rts::DWord as cry_rts::Cmp>::lt(
              t_1.as_arg(),
              <cry_rts::DWord>::number(5usize, 12usize).as_arg(),
            ),
          ) { <cry_rts::DWord>::number(5usize, 14usize) } else {
            <cry_rts::DWord>::number(5usize, 12usize)
          }
        }
      }
    });
  let states =
    cry_rts::stream!(
      forall = [
        SI1: [ cry_rts::Stream<bool> ], SI2: [ cry_rts::Stream<bool> ]
      ], element = (
        (cry_rts::Z, cry_rts::Z, cry_rts::Z),
        Vec<cry_rts::DWord>,
      ), history = 1, init = vec!(
        (
          in_import_at__32_infinity_projective_inst_ty_ty_ty::<cry_rts::Z, cry_rts::Z, cry_rts::Z>(
            num::BigUint::from_bytes_le(&[
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              1u8,
              0u8,
              0u8,
              0u8,
              255u8,
              255u8,
              255u8,
              255u8,
            ]),
            num::BigUint::from_bytes_le(&[
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              1u8,
              0u8,
              0u8,
              0u8,
              255u8,
              255u8,
              255u8,
              255u8,
            ]),
            num::BigUint::from_bytes_le(&[
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              1u8,
              0u8,
              0u8,
              0u8,
              255u8,
              255u8,
              255u8,
              255u8,
            ]),
          ),
          c,
        )
      ), capture = [
        sqx_1: (cry_rts::Z, cry_rts::Z, cry_rts::Z) = sqx_1, tqx_1: (
          cry_rts::Z,
          cry_rts::Z,
          cry_rts::Z,
        ) = tqx_1, sp_tqx_1: (
          cry_rts::Z,
          cry_rts::Z,
          cry_rts::Z,
        ) = sp_tqx_1, sm_tqx_1: (
          cry_rts::Z,
          cry_rts::Z,
          cry_rts::Z,
        ) = sm_tqx_1, f: cry_rts::Fn1<cry_rts::O<cry_rts::DWord>, cry_rts::DWord> = f, anon: SI1 = e0s
          .into_iter_bits_msb()
          .skip(4usize)
          .chain(cry_rts::str_zero::<bool>((), 5usize)), anon_1: SI2 = e1s
          .into_iter_bits_msb()
          .skip(4usize)
          .chain(cry_rts::str_zero::<bool>((), 5usize))
      ], step = |this|{
        let __p9 = this.get_history(0usize);
        let e0k = this.anon.next()?;
        let e1k = this.anon_1.next()?;
        let rk = __p9.as_arg().0.as_arg().clone_arg();
        let __p8 = __p9.as_arg().1.as_arg().clone_arg();
        let c0 = __p8.as_arg()[0usize].as_arg().clone_arg();
        let c1 = __p8.as_arg()[1usize].as_arg().clone_arg();
        let h0 =
          if c0
            .as_arg()
            .seq_index_front::<num::BigInt>(<num::BigInt>::number((), 0usize)
              .as_arg()) {
            <cry_rts::DWord as cry_rts::Ring>::sub(
              <cry_rts::DWord>::number(5usize, 31usize).as_arg(),
              crate::cryptol::tail_inst_sz_bit(5usize, c0.as_arg()).as_arg(),
            )
          } else { crate::cryptol::tail_inst_sz_bit(5usize, c0.as_arg()) };
        let h1 =
          if c1
            .as_arg()
            .seq_index_front::<num::BigInt>(<num::BigInt>::number((), 0usize)
              .as_arg()) {
            <cry_rts::DWord as cry_rts::Ring>::sub(
              <cry_rts::DWord>::number(5usize, 31usize).as_arg(),
              crate::cryptol::tail_inst_sz_bit(5usize, c1.as_arg()).as_arg(),
            )
          } else { crate::cryptol::tail_inst_sz_bit(5usize, c1.as_arg()) };
        let u0 =
          if <cry_rts::DWord as cry_rts::Cmp>::lt(
            h0.as_arg(),
            (this.f)(h1.clone()).as_arg(),
          ) { <cry_rts::DWord>::number(2usize, 0usize) } else {
            if c0
              .as_arg()
              .seq_index_front::<num::BigInt>(<num::BigInt>::number((), 0usize)
                .as_arg()) {
              <cry_rts::DWord as cry_rts::Ring>::negate(<cry_rts::DWord>::number(
                2usize,
                1usize,
              )
                .as_arg())
            } else { <cry_rts::DWord>::number(2usize, 1usize) }
          };
        let u1 =
          if <cry_rts::DWord as cry_rts::Cmp>::lt(
            h1.as_arg(),
            (this.f)(h0).as_arg(),
          ) { <cry_rts::DWord>::number(2usize, 0usize) } else {
            if c1
              .as_arg()
              .seq_index_front::<num::BigInt>(<num::BigInt>::number((), 0usize)
                .as_arg()) {
              <cry_rts::DWord as cry_rts::Ring>::negate(<cry_rts::DWord>::number(
                2usize,
                1usize,
              )
                .as_arg())
            } else { <cry_rts::DWord>::number(2usize, 1usize) }
          };
        let c0qx_1 =
          cry_rts::DWord::from_stream_msb(
            1usize,
            vec!(
              <bool as cry_rts::Logic>::xor(
                <cry_rts::DWord as cry_rts::Eq>::ne(
                  u0.as_arg(),
                  <cry_rts::DWord>::number(2usize, 0usize).as_arg(),
                ),
                c0
                  .as_arg()
                  .seq_index_front::<num::BigInt>(<num::BigInt>::number(
                    (),
                    1usize,
                  )
                    .as_arg()),
              )
            )
              .into_iter(),
          )
            .as_arg()
            .append(c0
              .as_arg()
              .skip(2usize)
              .as_arg()
              .append(cry_rts::DWord::from_stream_msb(
                1usize,
                vec!(e0k).into_iter(),
              )
                .as_arg())
              .as_arg());
        let c1qx_1 =
          cry_rts::DWord::from_stream_msb(
            1usize,
            vec!(
              <bool as cry_rts::Logic>::xor(
                <cry_rts::DWord as cry_rts::Eq>::ne(
                  u1.as_arg(),
                  <cry_rts::DWord>::number(2usize, 0usize).as_arg(),
                ),
                c1
                  .as_arg()
                  .seq_index_front::<num::BigInt>(<num::BigInt>::number(
                    (),
                    1usize,
                  )
                    .as_arg()),
              )
            )
              .into_iter(),
          )
            .as_arg()
            .append(c1
              .as_arg()
              .skip(2usize)
              .as_arg()
              .append(cry_rts::DWord::from_stream_msb(
                1usize,
                vec!(e1k).into_iter(),
              )
                .as_arg())
              .as_arg());
        let rk_double = in_import_at__32_ec_double(rk.as_arg());
        let rkqx_1 =
          if <bool as cry_rts::Logic>::and(
            <cry_rts::DWord as cry_rts::Eq>::eq(
              u0.as_arg(),
              <cry_rts::DWord as cry_rts::Ring>::negate(<cry_rts::DWord>::number(
                2usize,
                1usize,
              )
                .as_arg())
                .as_arg(),
            ),
            <cry_rts::DWord as cry_rts::Eq>::eq(
              u1.as_arg(),
              <cry_rts::DWord as cry_rts::Ring>::negate(<cry_rts::DWord>::number(
                2usize,
                1usize,
              )
                .as_arg())
                .as_arg(),
            ),
          ) {
            in_import_at__32_ec_full_sub(
              rk_double.as_arg(),
              this.sp_tqx_1.as_arg(),
            )
          } else {
            if <bool as cry_rts::Logic>::and(
              <cry_rts::DWord as cry_rts::Eq>::eq(
                u0.as_arg(),
                <cry_rts::DWord as cry_rts::Ring>::negate(<cry_rts::DWord>::number(
                  2usize,
                  1usize,
                )
                  .as_arg())
                  .as_arg(),
              ),
              <cry_rts::DWord as cry_rts::Eq>::eq(
                u1.as_arg(),
                <cry_rts::DWord>::number(2usize, 0usize).as_arg(),
              ),
            ) {
              in_import_at__32_ec_full_sub(
                rk_double.as_arg(),
                this.sqx_1.as_arg(),
              )
            } else {
              if <bool as cry_rts::Logic>::and(
                <cry_rts::DWord as cry_rts::Eq>::eq(
                  u0.as_arg(),
                  <cry_rts::DWord as cry_rts::Ring>::negate(<cry_rts::DWord>::number(
                    2usize,
                    1usize,
                  )
                    .as_arg())
                    .as_arg(),
                ),
                <cry_rts::DWord as cry_rts::Eq>::eq(
                  u1.as_arg(),
                  <cry_rts::DWord>::number(2usize, 1usize).as_arg(),
                ),
              ) {
                in_import_at__32_ec_full_sub(
                  rk_double.as_arg(),
                  this.sm_tqx_1.as_arg(),
                )
              } else {
                if <bool as cry_rts::Logic>::and(
                  <cry_rts::DWord as cry_rts::Eq>::eq(
                    u0.as_arg(),
                    <cry_rts::DWord>::number(2usize, 0usize).as_arg(),
                  ),
                  <cry_rts::DWord as cry_rts::Eq>::eq(
                    u1.as_arg(),
                    <cry_rts::DWord as cry_rts::Ring>::negate(<cry_rts::DWord>::number(
                      2usize,
                      1usize,
                    )
                      .as_arg())
                      .as_arg(),
                  ),
                ) {
                  in_import_at__32_ec_full_sub(
                    rk_double.as_arg(),
                    this.tqx_1.as_arg(),
                  )
                } else {
                  if <bool as cry_rts::Logic>::and(
                    <cry_rts::DWord as cry_rts::Eq>::eq(
                      u0.as_arg(),
                      <cry_rts::DWord>::number(2usize, 0usize).as_arg(),
                    ),
                    <cry_rts::DWord as cry_rts::Eq>::eq(
                      u1.as_arg(),
                      <cry_rts::DWord>::number(2usize, 1usize).as_arg(),
                    ),
                  ) {
                    in_import_at__32_ec_full_add(
                      rk_double.as_arg(),
                      this.tqx_1.as_arg(),
                    )
                  } else {
                    if <bool as cry_rts::Logic>::and(
                      <cry_rts::DWord as cry_rts::Eq>::eq(
                        u0.as_arg(),
                        <cry_rts::DWord>::number(2usize, 1usize).as_arg(),
                      ),
                      <cry_rts::DWord as cry_rts::Eq>::eq(
                        u1.as_arg(),
                        <cry_rts::DWord as cry_rts::Ring>::negate(<cry_rts::DWord>::number(
                          2usize,
                          1usize,
                        )
                          .as_arg())
                          .as_arg(),
                      ),
                    ) {
                      in_import_at__32_ec_full_add(
                        rk_double.as_arg(),
                        this.sm_tqx_1.as_arg(),
                      )
                    } else {
                      if <bool as cry_rts::Logic>::and(
                        <cry_rts::DWord as cry_rts::Eq>::eq(
                          u0.as_arg(),
                          <cry_rts::DWord>::number(2usize, 1usize).as_arg(),
                        ),
                        <cry_rts::DWord as cry_rts::Eq>::eq(
                          u1.as_arg(),
                          <cry_rts::DWord>::number(2usize, 0usize).as_arg(),
                        ),
                      ) {
                        in_import_at__32_ec_full_add(
                          rk_double.as_arg(),
                          this.sqx_1.as_arg(),
                        )
                      } else {
                        if <bool as cry_rts::Logic>::and(
                          <cry_rts::DWord as cry_rts::Eq>::eq(
                            u0.as_arg(),
                            <cry_rts::DWord>::number(2usize, 1usize).as_arg(),
                          ),
                          <cry_rts::DWord as cry_rts::Eq>::eq(
                            u1.as_arg(),
                            <cry_rts::DWord>::number(2usize, 1usize).as_arg(),
                          ),
                        ) {
                          in_import_at__32_ec_full_add(
                            rk_double.as_arg(),
                            this.sp_tqx_1.as_arg(),
                          )
                        } else { rk_double }
                      }
                    }
                  }
                }
              }
            }
          };
        (rkqx_1, vec!(c0qx_1, c1qx_1))
      }
    );
  cry_rts::index_stream_back::<(
    (cry_rts::Z, cry_rts::Z, cry_rts::Z),
    Vec<cry_rts::DWord>,
  ), num::BigInt>(258usize, states, <num::BigInt>::number((), 0usize).as_arg())
    .as_arg().0
    .as_arg()
    .clone_arg()
}

/**
Checks that twin multiplication works as expected. Note that a given
point can have multiple projective representations, so we have to
check equality in the affine representation.

These tests check the general case, the case where the two points `S`
and `T` are the same, and the case where one of the points is the point
at infinity.
```repl
:check twin_mult_works
:check (\d0 d1 k -> twin_mult_works d0 k d1 k)
:check (\d0 d1 k -> twin_mult_works d0 k d1 0)
:check (\d0 d1 k -> twin_mult_works d0 0 d1 k)
```

```cryptol
twin_mult_works : Z 115792089210356248762697446949407573530086143415290314195533631308867097853951 -> Z 115792089210356248762697446949407573529996955224135760342422259061068512044369 -> Z 115792089210356248762697446949407573530086143415290314195533631308867097853951 -> Z 115792089210356248762697446949407573529996955224135760342422259061068512044369 -> Bit
```
*/
pub fn in_import_at__32_twin_mult_works(
  d0: &cry_rts::Z,
  k0: &cry_rts::Z,
  d1: &cry_rts::Z,
  k1: &cry_rts::Z,
) -> bool {
  let s =
    in_import_at__32_to_projective(in_import_at__32_valid_point_from_k(k0)
      .as_arg());
  let t =
    in_import_at__32_to_projective(in_import_at__32_valid_point_from_k(k1)
      .as_arg());
  let r__plain =
    in_import_at__32_to_affine(in_import_at__32_ec_full_add(
      in_import_at__32_ec_mult(d0, s.as_arg()).as_arg(),
      in_import_at__32_ec_mult(d1, t.as_arg()).as_arg(),
    )
      .as_arg());
  let r__twin =
    in_import_at__32_to_affine(in_import_at__32_ec_twin_mult(
      d0,
      s.as_arg(),
      d1,
      t.as_arg(),
    )
      .as_arg());
  in_import_at__32_affine_eq(r__plain.as_arg(), r__twin.as_arg())
}

/**
Calculate x / y in a field.
```repl
:prove 2 %/ 2 == (1 : Z 3)
```

```cryptol
%/ : {a} (Field a) => a -> a -> a
```
*/
pub fn in_import_at__32_op_percent_fslash_inst_val<A>(
  a_len: A::Length,
  x: A::Arg<'_>,
  y: A::Arg<'_>,
) -> A
where
  A: cry_rts::Type,
  A: cry_rts::Field,
{
  <A as cry_rts::Ring>::mul(x, <A>::recip(y).as_arg())
}

/**
Addition of two elliptic curve points on a prime-field curve with
coefficient 'a'. Note 'b' is unused.
[SP-800-186] Appendix A.1.1.
[SEC1-v2] Section 2.2.1.

This uses the less-efficient affine representation.

```cryptol
affine_add : Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point
```
*/
pub fn in_import_at__32_affine_add(
  point1: &Inimportat32point,
  point2: &Inimportat32point,
) -> Inimportat32point {
  match point1.clone_arg() {
    Inimportat32point::Affine(x1, y1) => match point2.clone_arg() {
      Inimportat32point::Affine(x2, y2) => {
        let lambda =
          if <cry_rts::Z as cry_rts::Eq>::eq(x1.as_arg(), x2.as_arg()) {
            in_import_at__32_op_percent_fslash_inst_val::<cry_rts::Z>(
              num::BigUint::from_bytes_le(&[
                255u8,
                255u8,
                255u8,
                255u8,
                255u8,
                255u8,
                255u8,
                255u8,
                255u8,
                255u8,
                255u8,
                255u8,
                0u8,
                0u8,
                0u8,
                0u8,
                0u8,
                0u8,
                0u8,
                0u8,
                0u8,
                0u8,
                0u8,
                0u8,
                1u8,
                0u8,
                0u8,
                0u8,
                255u8,
                255u8,
                255u8,
                255u8,
              ]),
              <cry_rts::Z as cry_rts::Ring>::add(
                <cry_rts::Z as cry_rts::Ring>::mul(
                  <cry_rts::Z>::number(
                    num::BigUint::from_bytes_le(&[
                      255u8,
                      255u8,
                      255u8,
                      255u8,
                      255u8,
                      255u8,
                      255u8,
                      255u8,
                      255u8,
                      255u8,
                      255u8,
                      255u8,
                      0u8,
                      0u8,
                      0u8,
                      0u8,
                      0u8,
                      0u8,
                      0u8,
                      0u8,
                      0u8,
                      0u8,
                      0u8,
                      0u8,
                      1u8,
                      0u8,
                      0u8,
                      0u8,
                      255u8,
                      255u8,
                      255u8,
                      255u8,
                    ]),
                    3usize,
                  )
                    .as_arg(),
                  cry_rts::exp::<cry_rts::Z, num::BigInt>(
                    x1.as_arg(),
                    <num::BigInt>::number((), 2usize).as_arg(),
                  )
                    .as_arg(),
                )
                  .as_arg(),
                (&*in_import_at__32_a).as_arg(),
              )
                .as_arg(),
              <cry_rts::Z as cry_rts::Ring>::mul(
                <cry_rts::Z>::number(
                  num::BigUint::from_bytes_le(&[
                    255u8,
                    255u8,
                    255u8,
                    255u8,
                    255u8,
                    255u8,
                    255u8,
                    255u8,
                    255u8,
                    255u8,
                    255u8,
                    255u8,
                    0u8,
                    0u8,
                    0u8,
                    0u8,
                    0u8,
                    0u8,
                    0u8,
                    0u8,
                    0u8,
                    0u8,
                    0u8,
                    0u8,
                    1u8,
                    0u8,
                    0u8,
                    0u8,
                    255u8,
                    255u8,
                    255u8,
                    255u8,
                  ]),
                  2usize,
                )
                  .as_arg(),
                y1.as_arg(),
              )
                .as_arg(),
            )
          } else {
            in_import_at__32_op_percent_fslash_inst_val::<cry_rts::Z>(
              num::BigUint::from_bytes_le(&[
                255u8,
                255u8,
                255u8,
                255u8,
                255u8,
                255u8,
                255u8,
                255u8,
                255u8,
                255u8,
                255u8,
                255u8,
                0u8,
                0u8,
                0u8,
                0u8,
                0u8,
                0u8,
                0u8,
                0u8,
                0u8,
                0u8,
                0u8,
                0u8,
                1u8,
                0u8,
                0u8,
                0u8,
                255u8,
                255u8,
                255u8,
                255u8,
              ]),
              <cry_rts::Z as cry_rts::Ring>::sub(y2.as_arg(), y1.as_arg())
                .as_arg(),
              <cry_rts::Z as cry_rts::Ring>::sub(x2.as_arg(), x1.as_arg())
                .as_arg(),
            )
          };
        let x =
          <cry_rts::Z as cry_rts::Ring>::sub(
            <cry_rts::Z as cry_rts::Ring>::sub(
              cry_rts::exp::<cry_rts::Z, num::BigInt>(
                lambda.as_arg(),
                <num::BigInt>::number((), 2usize).as_arg(),
              )
                .as_arg(),
              x1.as_arg(),
            )
              .as_arg(),
            x2.as_arg(),
          );
        let y =
          <cry_rts::Z as cry_rts::Ring>::sub(
            <cry_rts::Z as cry_rts::Ring>::mul(
              lambda.as_arg(),
              <cry_rts::Z as cry_rts::Ring>::sub(x1.as_arg(), x.as_arg())
                .as_arg(),
            )
              .as_arg(),
            y1.as_arg(),
          );
        if <bool as cry_rts::Logic>::and(
          <cry_rts::Z as cry_rts::Eq>::eq(x1.as_arg(), x2.as_arg()),
          <cry_rts::Z as cry_rts::Eq>::eq(
            y1.as_arg(),
            <cry_rts::Z as cry_rts::Ring>::negate(y2.as_arg()).as_arg(),
          ),
        ) {
          (&*_in__import_at__32_con__infinity_con_con).as_arg().clone_arg()
        } else {
          _in__import_at__32_con__affine_con_con(x.as_arg(), y.as_arg())
        }
      },
      Inimportat32point::Infinity() => point1.clone_arg(),
    },
    Inimportat32point::Infinity() => point2.clone_arg(),
  }
}

/**
Proof that both addition properties work correctly for the point at infinity.

```repl
:check addsBehaveCorrectlyAtInfinity
```

```cryptol
addsBehaveCorrectlyAtInfinity : Z 115792089210356248762697446949407573529996955224135760342422259061068512044369 -> Bit
```
*/
pub fn in_import_at__32_adds_behave_correctly_at_infinity(
  k: &cry_rts::Z,
) -> bool {
  let point = in_import_at__32_valid_point_from_k(k);
  let oo =
    in_import_at__32_affine_eq(
      (&*_in__import_at__32_con__infinity_con_con).as_arg(),
      in_import_at__32_affine_add(
        (&*_in__import_at__32_con__infinity_con_con).as_arg(),
        (&*_in__import_at__32_con__infinity_con_con).as_arg(),
      )
        .as_arg(),
    );
  let ok =
    in_import_at__32_affine_eq(
      point.as_arg(),
      in_import_at__32_affine_add(
        (&*_in__import_at__32_con__infinity_con_con).as_arg(),
        point.as_arg(),
      )
        .as_arg(),
    );
  let ko =
    in_import_at__32_affine_eq(
      point.as_arg(),
      in_import_at__32_affine_add(
        point.as_arg(),
        (&*_in__import_at__32_con__infinity_con_con).as_arg(),
      )
        .as_arg(),
    );
  let pointqx_1 = in_import_at__32_to_projective(point.as_arg());
  let ooqx_1 =
    <(cry_rts::Z, cry_rts::Z, cry_rts::Z) as cry_rts::Eq>::eq(
      in_import_at__32_infinity_projective_inst_ty_ty_ty::<cry_rts::Z, cry_rts::Z, cry_rts::Z>(
        num::BigUint::from_bytes_le(&[
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          1u8,
          0u8,
          0u8,
          0u8,
          255u8,
          255u8,
          255u8,
          255u8,
        ]),
        num::BigUint::from_bytes_le(&[
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          1u8,
          0u8,
          0u8,
          0u8,
          255u8,
          255u8,
          255u8,
          255u8,
        ]),
        num::BigUint::from_bytes_le(&[
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          255u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          0u8,
          1u8,
          0u8,
          0u8,
          0u8,
          255u8,
          255u8,
          255u8,
          255u8,
        ]),
      )
        .as_arg(),
      in_import_at__32_ec_full_add(
        in_import_at__32_infinity_projective_inst_ty_ty_ty::<cry_rts::Z, cry_rts::Z, cry_rts::Z>(
          num::BigUint::from_bytes_le(&[
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            1u8,
            0u8,
            0u8,
            0u8,
            255u8,
            255u8,
            255u8,
            255u8,
          ]),
          num::BigUint::from_bytes_le(&[
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            1u8,
            0u8,
            0u8,
            0u8,
            255u8,
            255u8,
            255u8,
            255u8,
          ]),
          num::BigUint::from_bytes_le(&[
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            1u8,
            0u8,
            0u8,
            0u8,
            255u8,
            255u8,
            255u8,
            255u8,
          ]),
        )
          .as_arg(),
        in_import_at__32_infinity_projective_inst_ty_ty_ty::<cry_rts::Z, cry_rts::Z, cry_rts::Z>(
          num::BigUint::from_bytes_le(&[
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            1u8,
            0u8,
            0u8,
            0u8,
            255u8,
            255u8,
            255u8,
            255u8,
          ]),
          num::BigUint::from_bytes_le(&[
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            1u8,
            0u8,
            0u8,
            0u8,
            255u8,
            255u8,
            255u8,
            255u8,
          ]),
          num::BigUint::from_bytes_le(&[
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            1u8,
            0u8,
            0u8,
            0u8,
            255u8,
            255u8,
            255u8,
            255u8,
          ]),
        )
          .as_arg(),
      )
        .as_arg(),
    );
  let okqx_1 =
    <(cry_rts::Z, cry_rts::Z, cry_rts::Z) as cry_rts::Eq>::eq(
      pointqx_1.as_arg(),
      in_import_at__32_ec_full_add(
        in_import_at__32_infinity_projective_inst_ty_ty_ty::<cry_rts::Z, cry_rts::Z, cry_rts::Z>(
          num::BigUint::from_bytes_le(&[
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            1u8,
            0u8,
            0u8,
            0u8,
            255u8,
            255u8,
            255u8,
            255u8,
          ]),
          num::BigUint::from_bytes_le(&[
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            1u8,
            0u8,
            0u8,
            0u8,
            255u8,
            255u8,
            255u8,
            255u8,
          ]),
          num::BigUint::from_bytes_le(&[
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            1u8,
            0u8,
            0u8,
            0u8,
            255u8,
            255u8,
            255u8,
            255u8,
          ]),
        )
          .as_arg(),
        pointqx_1.as_arg(),
      )
        .as_arg(),
    );
  let koqx_1 =
    <(cry_rts::Z, cry_rts::Z, cry_rts::Z) as cry_rts::Eq>::eq(
      pointqx_1.as_arg(),
      in_import_at__32_ec_full_add(
        pointqx_1.as_arg(),
        in_import_at__32_infinity_projective_inst_ty_ty_ty::<cry_rts::Z, cry_rts::Z, cry_rts::Z>(
          num::BigUint::from_bytes_le(&[
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            1u8,
            0u8,
            0u8,
            0u8,
            255u8,
            255u8,
            255u8,
            255u8,
          ]),
          num::BigUint::from_bytes_le(&[
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            1u8,
            0u8,
            0u8,
            0u8,
            255u8,
            255u8,
            255u8,
            255u8,
          ]),
          num::BigUint::from_bytes_le(&[
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            0u8,
            1u8,
            0u8,
            0u8,
            0u8,
            255u8,
            255u8,
            255u8,
            255u8,
          ]),
        )
          .as_arg(),
      )
        .as_arg(),
    );
  <bool as cry_rts::Logic>::and(
    oo,
    <bool as cry_rts::Logic>::and(
      ok,
      <bool as cry_rts::Logic>::and(
        ko,
        <bool as cry_rts::Logic>::and(
          ooqx_1,
          <bool as cry_rts::Logic>::and(okqx_1, koqx_1),
        ),
      ),
    ),
  )
}

/**
Proof that the affine and projective versions of addition are equivalent.
This doesn't test the point at infinity.

```repl
:check addsAreEquivalent
```

```cryptol
addsAreEquivalent : Z 115792089210356248762697446949407573529996955224135760342422259061068512044369 -> Z 115792089210356248762697446949407573529996955224135760342422259061068512044369 -> Bit
```
*/
pub fn in_import_at__32_adds_are_equivalent(
  k1: &cry_rts::Z,
  k2: &cry_rts::Z,
) -> bool {
  let p1 = in_import_at__32_valid_point_from_k(k1);
  let p2 = in_import_at__32_valid_point_from_k(k2);
  let full_sum =
    in_import_at__32_ec_full_add(
      in_import_at__32_to_projective(p1.as_arg()).as_arg(),
      in_import_at__32_to_projective(p2.as_arg()).as_arg(),
    );
  in_import_at__32_affine_eq(
    in_import_at__32_affine_add(p1.as_arg(), p2.as_arg()).as_arg(),
    in_import_at__32_to_affine(full_sum.as_arg()).as_arg(),
  )
}

/**
This checks that the normalization function doesn't break on normalized
points. The actual, more interesting check would be to generate random
projective points (in non-normal representation, e.g. where the z coord
is not 1) on the curve and run those through `twin_normalize` but there
is not an obvious efficient way to sample such points.

```repl
:set tests=25
:check normalizeWorksOnNormalPoints
:prove normalizeWorksOnNormalPoints 0 0 0 0
```

```cryptol
normalizeWorksOnNormalPoints : Z 115792089210356248762697446949407573529996955224135760342422259061068512044369 -> Z 115792089210356248762697446949407573529996955224135760342422259061068512044369 -> Z 115792089210356248762697446949407573529996955224135760342422259061068512044369 -> Z 115792089210356248762697446949407573529996955224135760342422259061068512044369 -> Bit
```
*/
pub fn in_import_at__32_normalize_works_on_normal_points(
  k1: &cry_rts::Z,
  k2: &cry_rts::Z,
  k3: &cry_rts::Z,
  k4: &cry_rts::Z,
) -> bool {
  let p1 =
    in_import_at__32_to_projective(in_import_at__32_valid_point_from_k(k1)
      .as_arg());
  let p2 =
    in_import_at__32_to_projective(in_import_at__32_valid_point_from_k(k2)
      .as_arg());
  let p3 =
    in_import_at__32_to_projective(in_import_at__32_valid_point_from_k(k3)
      .as_arg());
  let p4 =
    in_import_at__32_to_projective(in_import_at__32_valid_point_from_k(k4)
      .as_arg());
  let input = (p1.clone(), p2.clone(), p3.clone(), p4.clone());
  let out = in_import_at__32_twin_normalize(input.as_arg());
  let any_are_infinity =
    crate::cryptol::any_inst_sz_val::<cry_rts::Z>(
      4usize,
      &<cry_rts::Fn1<cry_rts::O<cry_rts::Z>, _>>::new(move |k| <cry_rts::Z as cry_rts::Eq>::eq(
        k.as_arg(),
        <cry_rts::Z>::number(
          num::BigUint::from_bytes_le(&[
            81u8,
            37u8,
            99u8,
            252u8,
            194u8,
            202u8,
            185u8,
            243u8,
            132u8,
            158u8,
            23u8,
            167u8,
            173u8,
            250u8,
            230u8,
            188u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            255u8,
            0u8,
            0u8,
            0u8,
            0u8,
            255u8,
            255u8,
            255u8,
            255u8,
          ]),
          0usize,
        )
          .as_arg(),
      )),
      vec!(k1.clone_arg(), k2.clone_arg(), k3.clone_arg(), k4.clone_arg())
        .as_arg(),
    );
  let all_are_normal =
    <bool as cry_rts::Logic>::or(
      any_are_infinity,
      crate::cryptol::all_inst_sz_val::<(cry_rts::Z, cry_rts::Z, cry_rts::Z)>(
        4usize,
        &<cry_rts::Fn1<cry_rts::O<(
          cry_rts::Z,
          cry_rts::Z,
          cry_rts::Z,
        )>, _>>::new(move |p| <cry_rts::Z as cry_rts::Eq>::eq(
          p.as_arg().2.as_arg(),
          <cry_rts::Z>::number(
            num::BigUint::from_bytes_le(&[
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              255u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              0u8,
              1u8,
              0u8,
              0u8,
              0u8,
              255u8,
              255u8,
              255u8,
              255u8,
            ]),
            1usize,
          )
            .as_arg(),
        )),
        vec!(
          out.as_arg().0.as_arg().clone_arg(), out
            .as_arg().1
            .as_arg()
            .clone_arg(), out.as_arg().2.as_arg().clone_arg(), out
            .as_arg().3
            .as_arg()
            .clone_arg()
        )
          .as_arg(),
      ),
    );
  let all_match =
    <bool as cry_rts::Logic>::and(
      <(cry_rts::Z, cry_rts::Z, cry_rts::Z) as cry_rts::Eq>::eq(
        out.as_arg().0.as_arg(),
        p1.as_arg(),
      ),
      <bool as cry_rts::Logic>::and(
        <(cry_rts::Z, cry_rts::Z, cry_rts::Z) as cry_rts::Eq>::eq(
          out.as_arg().1.as_arg(),
          p2.as_arg(),
        ),
        <bool as cry_rts::Logic>::and(
          <(cry_rts::Z, cry_rts::Z, cry_rts::Z) as cry_rts::Eq>::eq(
            out.as_arg().2.as_arg(),
            p3.as_arg(),
          ),
          <(cry_rts::Z, cry_rts::Z, cry_rts::Z) as cry_rts::Eq>::eq(
            out.as_arg().3.as_arg(),
            p4.as_arg(),
          ),
        ),
      ),
    );
  <bool as cry_rts::Logic>::and(all_are_normal, all_match)
}

/**
Equality of group elements

```cryptol
T'eq : Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Bit
```
*/
pub fn tqx_1_eq(x: &Inimportat32point, x_1: &Inimportat32point) -> bool {
  in_import_at__32_affine_eq(x, x_1)
}

#[cfg(test)]
mod proptests {
  use super::*;

  use proptest::prelude::*;

  proptest! {
    #[ test ]fn prop_in_import_at__32_find_point_is_valid(
      x in cry_rts::any_z(num::BigUint::from_bytes_le(&[
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        1u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ]))
    ) { prop_assert!(in_import_at__32_find_point_is_valid(x.as_arg())) }
  }

  #[test]
  pub fn prop_in_import_at__32_curve_coefficients_are_valid() -> () {
    assert!(*in_import_at__32_curve_coefficients_are_valid)
  }

  #[test]
  pub fn prop_in_import_at__32_g_order_is_n() -> () {
    assert!(*in_import_at__32_g_order_is_n)
  }

  #[test]
  pub fn prop_in_import_at__32_g_is_valid() -> () {
    assert!(*in_import_at__32_g_is_valid)
  }

  proptest! {
    #[ test ]fn prop_in_import_at__32_add_is_closed(
      k1 in cry_rts::any_z(num::BigUint::from_bytes_le(&[
        81u8,
        37u8,
        99u8,
        252u8,
        194u8,
        202u8,
        185u8,
        243u8,
        132u8,
        158u8,
        23u8,
        167u8,
        173u8,
        250u8,
        230u8,
        188u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ])), k2 in cry_rts::any_z(num::BigUint::from_bytes_le(&[
        81u8,
        37u8,
        99u8,
        252u8,
        194u8,
        202u8,
        185u8,
        243u8,
        132u8,
        158u8,
        23u8,
        167u8,
        173u8,
        250u8,
        230u8,
        188u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ]))
    ) { prop_assert!(in_import_at__32_add_is_closed(k1.as_arg(), k2.as_arg())) }
  }

  proptest! {
    #[ test ]fn prop_in_import_at__32_double_is_closed(
      k in cry_rts::any_z(num::BigUint::from_bytes_le(&[
        81u8,
        37u8,
        99u8,
        252u8,
        194u8,
        202u8,
        185u8,
        243u8,
        132u8,
        158u8,
        23u8,
        167u8,
        173u8,
        250u8,
        230u8,
        188u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ]))
    ) { prop_assert!(in_import_at__32_double_is_closed(k.as_arg())) }
  }

  proptest! {
    #[ test ]fn prop_in_import_at__32_sub_is_closed(
      k1 in cry_rts::any_z(num::BigUint::from_bytes_le(&[
        81u8,
        37u8,
        99u8,
        252u8,
        194u8,
        202u8,
        185u8,
        243u8,
        132u8,
        158u8,
        23u8,
        167u8,
        173u8,
        250u8,
        230u8,
        188u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ])), k2 in cry_rts::any_z(num::BigUint::from_bytes_le(&[
        81u8,
        37u8,
        99u8,
        252u8,
        194u8,
        202u8,
        185u8,
        243u8,
        132u8,
        158u8,
        23u8,
        167u8,
        173u8,
        250u8,
        230u8,
        188u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ]))
    ) { prop_assert!(in_import_at__32_sub_is_closed(k1.as_arg(), k2.as_arg())) }
  }

  proptest! {
    #[ test ]fn prop_in_import_at__32_scmul_is_closed(
      m in cry_rts::any_integer()
    ) { prop_assert!(in_import_at__32_scmul_is_closed(m.as_arg())) }
  }

  proptest! {
    #[ test ]fn prop_in_import_at__32_scmul_commutes(
      m in cry_rts::any_integer(), mqx_1 in cry_rts::any_integer()
    ) {
      prop_assert!(in_import_at__32_scmul_commutes(m.as_arg(), mqx_1.as_arg()))
    }
  }

  proptest! {
    #[ test ]fn prop_in_import_at__32_twin_mult_works(
      d0 in cry_rts::any_z(num::BigUint::from_bytes_le(&[
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        1u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ])), k0 in cry_rts::any_z(num::BigUint::from_bytes_le(&[
        81u8,
        37u8,
        99u8,
        252u8,
        194u8,
        202u8,
        185u8,
        243u8,
        132u8,
        158u8,
        23u8,
        167u8,
        173u8,
        250u8,
        230u8,
        188u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ])), d1 in cry_rts::any_z(num::BigUint::from_bytes_le(&[
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        0u8,
        1u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ])), k1 in cry_rts::any_z(num::BigUint::from_bytes_le(&[
        81u8,
        37u8,
        99u8,
        252u8,
        194u8,
        202u8,
        185u8,
        243u8,
        132u8,
        158u8,
        23u8,
        167u8,
        173u8,
        250u8,
        230u8,
        188u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ]))
    ) {
      prop_assert!(
        in_import_at__32_twin_mult_works(
          d0.as_arg(),
          k0.as_arg(),
          d1.as_arg(),
          k1.as_arg(),
        )
      )
    }
  }

  proptest! {
    #[ test ]fn prop_in_import_at__32_adds_behave_correctly_at_infinity(
      k in cry_rts::any_z(num::BigUint::from_bytes_le(&[
        81u8,
        37u8,
        99u8,
        252u8,
        194u8,
        202u8,
        185u8,
        243u8,
        132u8,
        158u8,
        23u8,
        167u8,
        173u8,
        250u8,
        230u8,
        188u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ]))
    ) {
      prop_assert!(
        in_import_at__32_adds_behave_correctly_at_infinity(k.as_arg())
      )
    }
  }

  proptest! {
    #[ test ]fn prop_in_import_at__32_adds_are_equivalent(
      k1 in cry_rts::any_z(num::BigUint::from_bytes_le(&[
        81u8,
        37u8,
        99u8,
        252u8,
        194u8,
        202u8,
        185u8,
        243u8,
        132u8,
        158u8,
        23u8,
        167u8,
        173u8,
        250u8,
        230u8,
        188u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ])), k2 in cry_rts::any_z(num::BigUint::from_bytes_le(&[
        81u8,
        37u8,
        99u8,
        252u8,
        194u8,
        202u8,
        185u8,
        243u8,
        132u8,
        158u8,
        23u8,
        167u8,
        173u8,
        250u8,
        230u8,
        188u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ]))
    ) {
      prop_assert!(
        in_import_at__32_adds_are_equivalent(k1.as_arg(), k2.as_arg())
      )
    }
  }

  proptest! {
    #[ test ]fn prop_in_import_at__32_normalize_works_on_normal_points(
      k1 in cry_rts::any_z(num::BigUint::from_bytes_le(&[
        81u8,
        37u8,
        99u8,
        252u8,
        194u8,
        202u8,
        185u8,
        243u8,
        132u8,
        158u8,
        23u8,
        167u8,
        173u8,
        250u8,
        230u8,
        188u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ])), k2 in cry_rts::any_z(num::BigUint::from_bytes_le(&[
        81u8,
        37u8,
        99u8,
        252u8,
        194u8,
        202u8,
        185u8,
        243u8,
        132u8,
        158u8,
        23u8,
        167u8,
        173u8,
        250u8,
        230u8,
        188u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ])), k3 in cry_rts::any_z(num::BigUint::from_bytes_le(&[
        81u8,
        37u8,
        99u8,
        252u8,
        194u8,
        202u8,
        185u8,
        243u8,
        132u8,
        158u8,
        23u8,
        167u8,
        173u8,
        250u8,
        230u8,
        188u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ])), k4 in cry_rts::any_z(num::BigUint::from_bytes_le(&[
        81u8,
        37u8,
        99u8,
        252u8,
        194u8,
        202u8,
        185u8,
        243u8,
        132u8,
        158u8,
        23u8,
        167u8,
        173u8,
        250u8,
        230u8,
        188u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        255u8,
        0u8,
        0u8,
        0u8,
        0u8,
        255u8,
        255u8,
        255u8,
        255u8,
      ]))
    ) {
      prop_assert!(
        in_import_at__32_normalize_works_on_normal_points(
          k1.as_arg(),
          k2.as_arg(),
          k3.as_arg(),
          k4.as_arg(),
        )
      )
    }
  }
}
