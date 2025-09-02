/*! Mathematical Sets

@author Frank Zeyda (frank.zeyda@freeandfair.us)
@copyright Free & Fair 2025
@version 0.1
*/
#![allow(unused_variables)]
#![allow(unused_imports)]
use cry_rts::trait_methods::*;

/**
Set Membership

```cryptol
∈ : {a} a -> (a -> Bit) -> Bit
```
*/
pub fn op_2208_inst_ty<A>(
  x: A::Arg<'_>,
  s: &cry_rts::Fn1<cry_rts::O<A>, bool>,
) -> bool
where
  A: cry_rts::Type,
{
  (s)(x.clone_arg())
}
