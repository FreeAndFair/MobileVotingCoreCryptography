/*
 * Placeholder
 */

#![allow(unused_variables)]
#![allow(unused_imports)]
use cry_rts::trait_methods::*;

/**
```cryptol
b : {a}
  (Literal 41058363725152142129326129780047268409114441015993725554835256314039467401291 a) =>
  a
```
*/
pub fn b_inst_val<T>(t_len: T::Length) -> T
where
  T: cry_rts::Type,
  T: cry_rts::Literal,
{
  <T>::number(
    t_len.clone(),
    &num::BigUint::from_bytes_le(&[
      75u8,
      96u8,
      210u8,
      39u8,
      62u8,
      60u8,
      206u8,
      59u8,
      246u8,
      176u8,
      83u8,
      204u8,
      176u8,
      6u8,
      29u8,
      101u8,
      188u8,
      134u8,
      152u8,
      118u8,
      85u8,
      189u8,
      235u8,
      179u8,
      231u8,
      147u8,
      58u8,
      170u8,
      216u8,
      53u8,
      198u8,
      90u8,
    ]),
  )
}

/**
```cryptol
Gx : {a}
  (Literal 48439561293906451759052585252797914202762949526041747995844080717082404635286 a) =>
  a
```
*/
pub fn gx_inst_val<T>(t_len: T::Length) -> T
where
  T: cry_rts::Type,
  T: cry_rts::Literal,
{
  <T>::number(
    t_len.clone(),
    &num::BigUint::from_bytes_le(&[
      150u8,
      194u8,
      152u8,
      216u8,
      69u8,
      57u8,
      161u8,
      244u8,
      160u8,
      51u8,
      235u8,
      45u8,
      129u8,
      125u8,
      3u8,
      119u8,
      242u8,
      64u8,
      164u8,
      99u8,
      229u8,
      230u8,
      188u8,
      248u8,
      71u8,
      66u8,
      44u8,
      225u8,
      242u8,
      209u8,
      23u8,
      107u8,
    ]),
  )
}

/**
```cryptol
Gy : {a}
  (Literal 36134250956749795798585127919587881956611106672985015071877198253568414405109 a) =>
  a
```
*/
pub fn gy_inst_val<T>(t_len: T::Length) -> T
where
  T: cry_rts::Type,
  T: cry_rts::Literal,
{
  <T>::number(
    t_len.clone(),
    &num::BigUint::from_bytes_le(&[
      245u8,
      81u8,
      191u8,
      55u8,
      104u8,
      64u8,
      182u8,
      203u8,
      206u8,
      94u8,
      49u8,
      107u8,
      87u8,
      51u8,
      206u8,
      43u8,
      22u8,
      158u8,
      15u8,
      124u8,
      74u8,
      235u8,
      231u8,
      142u8,
      155u8,
      127u8,
      26u8,
      254u8,
      226u8,
      66u8,
      227u8,
      79u8,
    ]),
  )
}
