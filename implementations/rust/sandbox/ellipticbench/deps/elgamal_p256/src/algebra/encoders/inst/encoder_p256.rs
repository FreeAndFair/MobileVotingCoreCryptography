/*! Generic bitstring encoding of message in the
NIST P-256 Elliptic Curve defined in [FIPS-186-5]

@author Frank Zeyda (frank.zeyda@freeandfair.us)
@copyright Free & Fair 2025
@version 0.1
*/
/*! Encoder that use a group's default encoding method

Where it makes sense, every implementation of the
[Cyclic]GroupI module interface defines a default
method for encoding a bitstring into a group element.
This module exposes that method as an implementation
of the EncoderI interface.

@implements Algebra::EncoderI
@author Frank Zeyda (frank.zeyda@freeandfair.us)
@copyright Free & Fair 2025
@version 0.1
*/
#![allow(unused_variables)]
#![allow(unused_imports)]
use cry_rts::trait_methods::*;

/**
Encoding a message as a group element

This function defines a default encoding of a
bitstring of predefined length `bits` into a
group element if there is an obvious canonical
way to do so.

```cryptol
enc : [247] -> Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point
```
*/
pub fn enc(
    x: cry_rts::DWordRef<'_>,
) -> crate::algebra::groups::inst::pfec_group_p256::Inimportat32point {
    crate::algebra::groups::inst::pfec_group_p256::enc(x)
}

/**
Encodes a message into a group element.

@todo Perhaps consider that the CyclicGroup::enc may
be parameterized in terms of an option type, so that
failure is propagated here from CyclicGroupI to EncoderI.

```cryptol
Encode : [247] -> Cryptol::Option
(Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point)
```
*/
pub fn encode(
    m: cry_rts::DWordRef<'_>,
) -> crate::cryptol::OptionInstTy<crate::algebra::groups::inst::pfec_group_p256::Inimportat32point>
{
    crate::cryptol::_some_con_inst_ty::<
        crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
    >(enc(m).as_arg())
}

/**
Carrier set of the group

Defines the values of type T that are valid group
elements.

```cryptol
G : Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Bit
```
*/
pub fn g(x: &crate::algebra::groups::inst::pfec_group_p256::Inimportat32point) -> bool {
    crate::algebra::groups::inst::pfec_group_p256::g_1(x)
}

/**
Decoding a group element into a message

If the given group element e is in the
range of the `enc` function, its unique
bitvector representation shall be returned.
Otherwise, the result may be any value and
is considered to be undefined.

```cryptol
dec : Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> [247]
```
*/
pub fn dec(x: &crate::algebra::groups::inst::pfec_group_p256::Inimportat32point) -> cry_rts::DWord {
    crate::algebra::groups::inst::pfec_group_p256::dec(x)
}

/**
Decodes a group element into a message.

```cryptol
Decode : Algebra::Groups::Inst::PFECGroupP256::import_at__32::Point -> Cryptol::Option
[247]
```
*/
pub fn decode(
    c: &crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
) -> crate::cryptol::OptionInstTy<cry_rts::DWord> {
    if crate::algebra::set::op_2208_inst_ty::<
        crate::algebra::groups::inst::pfec_group_p256::Inimportat32point,
    >(
        c,
        &<cry_rts::Fn1<
            cry_rts::O<crate::algebra::groups::inst::pfec_group_p256::Inimportat32point>,
            _,
        >>::new(move |x| g(x.as_arg())),
    ) {
        crate::cryptol::_some_con_inst_ty::<cry_rts::DWord>(dec(c).as_arg())
    } else {
        crate::cryptol::_none_con_inst_ty::<cry_rts::DWord>()
    }
}
