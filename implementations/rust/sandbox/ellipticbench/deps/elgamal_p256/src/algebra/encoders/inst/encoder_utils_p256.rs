/*! Utilities for bitstring encoding of message in the
NIST P-256 Elliptic Curve defined in [FIPS-186-5].

@author Frank Zeyda (frank.zeyda@freeandfair.us)
@copyright Free & Fair 2025
@version 0.1
*/
/*! Message Encoding Utility Functions

@design For verification purposes, we decided to return
Option types as the result of the `Encode` and `Decode`
functions defined in the Algebra::EncoderI interface.
For usability, this is not optimal since it forces us
to unpack those option values in several places and deal
with the None case when we assume such ought be avoided
by design. Hence, this module defines so-called "strict"
versions of those functions with stronger preconditions,
which raise errors if passed arguments for which the
original functions would return None.

@author Frank Zeyda (frank.zeyda@freeandfair.us)
@copyright Free & Fair 2025
@version 0.1
*/
#![allow(unused_variables)]
#![allow(unused_imports)]
use cry_rts::trait_methods::*;

/**
Encodes a message into a group element.

This function shall return None iff the message is not
encodable, i.e., m ∉ encodable. Moreover, every `Some y`
returned must refer to a valid group element (y ∈ G).

```cryptol
Encode : [247] -> Cryptol::Option
(Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point)
```
*/
pub fn encode(
    x: cry_rts::DWordRef<'_>,
) -> crate::cryptol::OptionInstTy<crate::algebra::groups::inst::pfec_group_p256::Inimportat32point>
{
    crate::algebra::encoders::inst::encoder_p256::encode(x)
}

/**
Encodes a message into a group element. (strict version)

This function raises an error iff the message is not
encodable, i.e., m ∉ encodable. An advantage compared
to `Encode` is that the result is not wrapped into an
`Option T` type.

```cryptol
Strict'Encode : [247] -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point
```
*/
pub fn strictqx_1_encode(
    x: cry_rts::DWordRef<'_>,
) -> crate::algebra::groups::inst::pfec_group_p256::Inimportat32point {
    match encode(x) {
        crate::cryptol::OptionInstTy::None() => todo!("error"),
        crate::cryptol::OptionInstTy::Some(y) => y,
    }
}

/**
Decodes a group element into a message.

This function shall return None iff the group element
does not result from applying Encode to an encodable
message. Note that membership to the group (y ∈ G) is
not sufficient to guarantee the function returns `Some x`.

```cryptol
Decode : Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Cryptol::Option
[247]
```
*/
pub fn decode(
    x: &crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
) -> crate::cryptol::OptionInstTy<cry_rts::DWord> {
    crate::algebra::encoders::inst::encoder_p256::decode(x)
}

/**
Decodes a group element into a message. (strict version)

This function shall return None iff the group element
does not result from applying Encode to an encodable
message.

```cryptol
Strict'Decode : Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> [247]
```
*/
pub fn strictqx_1_decode(
    y: &crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
) -> cry_rts::DWord {
    match decode(y) {
        crate::cryptol::OptionInstTy::None() => todo!("error"),
        crate::cryptol::OptionInstTy::Some(x) => x,
    }
}
