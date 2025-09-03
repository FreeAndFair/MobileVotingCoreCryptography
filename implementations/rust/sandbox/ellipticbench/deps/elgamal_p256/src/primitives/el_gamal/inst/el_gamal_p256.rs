/*! Instance of ElGamal’s Cryptosystem in the context of
the NIST P-256 Elliptic Curve defined in [FIPS-186-5]

@author Frank Zeyda (frank.zeyda@freeandfair.us)
@copyright Free & Fair 2025
@version 0.1
*/
/*! Generic ElGamal Cryptosystem
Section 10.4 of the EVS Draft, February 3, 2025.

@author Frank Zeyda (frank.zeyda@freeandfair.us)
@copyright Free & Fair 2025
@version 0.1
*/
#![allow(unused_variables)]
#![allow(unused_imports)]
use cry_rts::trait_methods::*;

/**
Repeated application of group operation

While exponentiation may be defined generically,
permitting instances to define it concretely
can result in more efficient implementations.
Exponentation must be closed for all integral
exponents of a valid group element. That is, for
x ∈ G and k an Integer we must have (exp x k) ∈ G.
Also, since g is a generator, (exp g k) shall
cycle through all elements of G for 0 <= k < `order.

To handle negative exponents, exp shall obey the
identity (exp x k) == (exp (inv x) -k) for x ∈ G.
Naturally, we also assume (exp x 0) == identity and
(exp x 1) == x for all x ∈ G.

@todo fzeyda: Douglas Wikström encourage exploration
of using a constraint (Field a) for the exponent type.
Or perhaps introduce another type parameter for the
exponent type. I understand that custom instantiation
of type classes is limited in Cryptol, so we may need
some more creative ways to achieve this if so.

```cryptol
exp : {a}
  (Integral a) =>
  Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> a -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point
```
*/
pub fn exp_inst_val<A>(
    a_len: A::Length,
    x: &crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
    x_1: A::Arg<'_>,
) -> crate::algebra::groups::inst::pfec_group_p256::Inimportat32point
where
    A: cry_rts::Type,
    A: cry_rts::Integral,
{
    crate::algebra::groups::inst::pfec_group_p256::exp_inst_val::<A>(a_len.clone(), x, x_1)
}

/**
```cryptol
^^ : {a}
  (Integral a) =>
  Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> a -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point
```
*/
pub fn op_hat_hat_inst_val<T>(
    t_len: T::Length,
    x: &crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
    x_1: T::Arg<'_>,
) -> crate::algebra::groups::inst::pfec_group_p256::Inimportat32point
where
    T: cry_rts::Type,
    T: cry_rts::Integral,
{
    exp_inst_val::<T>(t_len.clone(), x, x_1)
}

cry_rts::Global! {
  /**
  Generator of the group

  Cyclic groups are expected to provide a suitable
  generator element. We require g to be valid (g ∈ G).

  ```cryptol
  g : Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point
  ```
  */ g: crate::algebra::groups::inst::pfec_group_p256::Inimportat32point = {
    (&*crate::algebra::groups::inst::pfec_group_p256::g).as_arg().clone_arg()
  }
}

/**
Generates an ElGamal KeyPair from a given secret key x.

@pre x must be in the range [1 ..< order].

```cryptol
Gen : Integer -> {pk : (Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point,
  Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point),
 sk : Integer}
```
*/
pub fn r#gen(
    x: &num::BigInt,
) -> (
    (
        crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
        crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
    ),
    num::BigInt,
) {
    let y = op_hat_hat_inst_val::<num::BigInt>((), (&*g).as_arg(), x);
    (((&*g).as_arg().clone_arg(), y), x.clone_arg())
}

/**
Binary group operation

The group operation must be closed under the set G.
That is, if x ∈ G and y ∈ G then (gop x y) ∈ G.

TODO: Do we usually expect gop to be commutative?

```cryptol
gop : Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point
```
*/
pub fn gop(
    x: &crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
    x_1: &crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
) -> crate::algebra::groups::inst::pfec_group_p256::Inimportat32point {
    crate::algebra::groups::inst::pfec_group_p256::gop(x, x_1)
}

/**
```cryptol
* : Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point
```
*/
pub fn op_star(
    x: &crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
    x_1: &crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
) -> crate::algebra::groups::inst::pfec_group_p256::Inimportat32point {
    gop(x, x_1)
}

/**
Inverse of a given group element

The standard group axioms merely require the
existence of an inverse but we need to be able
to compute it, so implementations must define
the below function.

Inverse must be closed under the set G.
That is, if x ∈ G then (inv x) ∈ G.

```cryptol
inv : Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point
```
*/
pub fn inv(
    x: &crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
) -> crate::algebra::groups::inst::pfec_group_p256::Inimportat32point {
    crate::algebra::groups::inst::pfec_group_p256::inv(x)
}

/**
Decrypts a cipher text (u, v) with a secret key sk.

```cryptol
Dec : Integer -> (Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point,
 Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point) -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point
```
*/
pub fn dec(
    sk: &num::BigInt,
    __p1: &(
        crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
        crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
    ),
) -> crate::algebra::groups::inst::pfec_group_p256::Inimportat32point {
    let v = __p1.1.as_arg().clone_arg();
    let u = __p1.0.as_arg().clone_arg();
    op_star(
        op_hat_hat_inst_val::<num::BigInt>((), inv(u.as_arg()).as_arg(), sk).as_arg(),
        v.as_arg(),
    )
}

/**
Encrypts a message m with a public key pk and randomness r.

```cryptol
Enc : (Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point,
 Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point) -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Integer -> (Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point,
 Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point)
```
*/
pub fn enc(
    pk: &(
        crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
        crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
    ),
    m: &crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
    r: &num::BigInt,
) -> (
    crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
    crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
) {
    let __p0 = pk.clone_arg();
    let gqx_1 = __p0.as_arg().0.as_arg().clone_arg();
    let y = __p0.as_arg().1.as_arg().clone_arg();
    (
        op_hat_hat_inst_val::<num::BigInt>((), gqx_1.as_arg(), r),
        op_star(
            op_hat_hat_inst_val::<num::BigInt>((), y.as_arg(), r).as_arg(),
            m,
        ),
    )
}

/**
Roundtrip function that performs key generation, encryption,
and decryption of a message m : T, based on two random values
r0 and r1, where r0 is used to generate the KeyPair and r1 is
used as randomness for message encryption.

```cryptol
gen_enc_dec : Integer -> Integer -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point
```
*/
pub fn gen_enc_dec(
    r0: &num::BigInt,
    r1: &num::BigInt,
    m: &crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
) -> crate::algebra::groups::inst::pfec_group_p256::Inimportat32point {
    let kp = r#gen(r0);
    dec(
        kp.as_arg().1.as_arg(),
        enc(kp.as_arg().0.as_arg(), m, r1).as_arg(),
    )
}

/**
Carrier set of the group

Defines the values of type T that are valid group
elements.

```cryptol
G : Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Bit
```
*/
pub fn g_1(x: &crate::algebra::groups::inst::pfec_group_p256::Inimportat32point) -> bool {
    crate::algebra::groups::inst::pfec_group_p256::g_1(x)
}

/**
Equality of group elements

Since not all Cryptol types implement the Eq type
class by default, for generality, the group instance
has to define an equality test function on type T.

```cryptol
T'eq : Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Bit
```
*/
pub fn tqx_1_eq(
    x: &crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
    x_1: &crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
) -> bool {
    crate::algebra::groups::inst::pfec_group_p256::tqx_1_eq(x, x_1)
}

/**
For convenience, we overload the infix syntax for
equality, multiplication and exponentation to use
the group operations. This makes the Cryptol model
look more closely aligned with the mathematical
presentation of ElGamal, i.e., in the EVS draft.

```cryptol
≡ : Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Bit
```
*/
pub fn op_2261(
    x: &crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
    x_1: &crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
) -> bool {
    tqx_1_eq(x, x_1)
}

/**
Determines if a given KeyPair is valid.

```cryptol
is_valid_KeyPair : {pk : (Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point,
  Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point),
 sk : Integer} -> Bit
```
*/
pub fn is_valid_key_pair(
    kp: &(
        (
            crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
            crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
        ),
        num::BigInt,
    ),
) -> bool {
    let pk = kp.0.as_arg().clone_arg();
    let sk = kp.1.as_arg().clone_arg();
    if crate::algebra::set::op_2208_inst_ty::<
        crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
    >(
        pk.as_arg().0.as_arg(),
        &<cry_rts::Fn1<
            cry_rts::O<crate::algebra::groups::inst::pfec_group_p256::Inimportat32point>,
            _,
        >>::new(move |x| g_1(x.as_arg())),
    ) {
        if crate::algebra::set::op_2208_inst_ty::<
            crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
        >(
            pk.as_arg().1.as_arg(),
            &<cry_rts::Fn1<
                cry_rts::O<crate::algebra::groups::inst::pfec_group_p256::Inimportat32point>,
                _,
            >>::new(move |x| g_1(x.as_arg())),
        ) {
            if op_2261(
                pk.as_arg().1.as_arg(),
                op_hat_hat_inst_val::<num::BigInt>((), pk.as_arg().0.as_arg(), sk.as_arg())
                    .as_arg(),
            ) {
                if <num::BigInt as cry_rts::Cmp>::gt(
                    sk.as_arg(),
                    <num::BigInt>::number((), 0usize).as_arg(),
                ) {
                    <num::BigInt as cry_rts::Cmp>::lt(
                        sk.as_arg(),
                        <num::BigInt>::number(
                            (),
                            &num::BigUint::from_bytes_le(&[
                                81u8, 37u8, 99u8, 252u8, 194u8, 202u8, 185u8, 243u8, 132u8, 158u8,
                                23u8, 167u8, 173u8, 250u8, 230u8, 188u8, 255u8, 255u8, 255u8,
                                255u8, 255u8, 255u8, 255u8, 255u8, 0u8, 0u8, 0u8, 0u8, 255u8,
                                255u8, 255u8, 255u8,
                            ]),
                        )
                        .as_arg(),
                    )
                } else {
                    false
                }
            } else {
                false
            }
        } else {
            false
        }
    } else {
        false
    }
}

/**
Key generation produces a valid key pair.

Key (Gen)eration uses the give random integer r0.
@note We assume r0 is in the range [1 ..< order].

```cryptol
gen_valid_keypair : Integer -> Bit
```
*/
pub fn gen_valid_keypair(r0: &num::BigInt) -> bool {
    if if <num::BigInt as cry_rts::Cmp>::gt(r0, <num::BigInt>::number((), 0usize).as_arg()) {
        <num::BigInt as cry_rts::Cmp>::lt(
            r0,
            <num::BigInt>::number(
                (),
                &num::BigUint::from_bytes_le(&[
                    81u8, 37u8, 99u8, 252u8, 194u8, 202u8, 185u8, 243u8, 132u8, 158u8, 23u8, 167u8,
                    173u8, 250u8, 230u8, 188u8, 255u8, 255u8, 255u8, 255u8, 255u8, 255u8, 255u8,
                    255u8, 0u8, 0u8, 0u8, 0u8, 255u8, 255u8, 255u8, 255u8,
                ]),
            )
            .as_arg(),
        )
    } else {
        false
    } {
        is_valid_key_pair(r#gen(r0).as_arg())
    } else {
        true
    }
}

/**
Decryption followed by encryption returns the same message.

In other words, function Dec is the inverse of function Enc.
Key (Gen)eration and (Enc)ryption use random integers r0 and r1.

@note For some groups such as ℤ/nℤ or Schnorr with r = 2, the
guard m ∈ G is actually not required for correctness of ElGamal.
However, for expected security properties to hold, all encoded
messages values must be from the subgroup G.

```cryptol
gen_enc_dec_inverse : Integer -> Integer -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Bit
```
*/
pub fn gen_enc_dec_inverse(
    r0: &num::BigInt,
    r1: &num::BigInt,
    m: &crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
) -> bool {
    if crate::algebra::set::op_2208_inst_ty::<
        crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
    >(
        m,
        &<cry_rts::Fn1<
            cry_rts::O<crate::algebra::groups::inst::pfec_group_p256::Inimportat32point>,
            _,
        >>::new(move |x| g_1(x.as_arg())),
    ) {
        op_2261(gen_enc_dec(r0, r1, m).as_arg(), m)
    } else {
        true
    }
}

#[cfg(test)]
mod proptests {
    use super::*;

    use proptest::prelude::*;

    proptest! {
      #[ test ]fn prop_gen_valid_keypair(r0 in cry_rts::any_integer()) {
        prop_assert!(gen_valid_keypair(r0.as_arg()))
      }
    }
}
