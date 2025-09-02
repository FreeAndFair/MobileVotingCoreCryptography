/*
 * Placeholder
 */

#![allow(unused_variables)]
#![allow(unused_imports)]
use cry_rts::trait_methods::*;

cry_rts::Global! {
  /**
  ```cryptol
  main : [5][247]
  ```
  */ main: Vec<cry_rts::DWord> = {
    (&*crate::primitives::el_gamal::inst::el_gamal_p256__test::main)
      .as_arg()
      .clone_arg()
  }
}
