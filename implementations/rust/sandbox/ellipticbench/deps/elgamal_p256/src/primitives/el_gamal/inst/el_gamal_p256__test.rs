/*! Smoke test of ElGamal’s Cryptosystem in the context of
the NIST P-256 Elliptic Curve defined in [FIPS-186-5]
using the default bitstring encoding of the EC group.

@author Frank Zeyda (frank.zeyda@freeandfair.us)
@copyright Free & Fair 2025
@version 0.1
*/
#![allow(unused_variables)]
#![allow(unused_imports)]
use cry_rts::trait_methods::*;

cry_rts::Global! {
  /**
  Simple testing function encrypting and decrypting five messages.

  ```cryptol
  main : [5][247]
  ```
  */ main: Vec<cry_rts::DWord> = {
    let tv =
      vec!(
        <cry_rts::DWord>::number(247usize, 0usize), <cry_rts::DWord>::number(
          247usize,
          1usize,
        ), <cry_rts::DWord>::number(247usize, 5usize), <cry_rts::DWord>::number(
          247usize,
          11usize,
        ), <cry_rts::DWord>::number(247usize, 23usize)
      );
    let tvqx_1_enc =
      crate::cryptol::map_inst_sz_val_val::<cry_rts::DWord, crate::algebra::groups::inst::pfec_group_p256::Inimportat32point>(
        5usize,
        &<cry_rts::Fn1<cry_rts::O<cry_rts::DWord>, _>>::new(move |x| crate::algebra::encoders::inst::encoder_utils_p256::strictqx_1_encode(x
          .as_arg())),
        tv.as_arg(),
      );
    let tvqx_1_run =
      crate::cryptol::map_inst_sz_val_val::<crate::algebra::groups::inst::pfec_group_p256::Inimportat32point, crate::algebra::groups::inst::pfec_group_p256::Inimportat32point>(
        5usize,
        &<cry_rts::Fn1<cry_rts::O<crate::algebra::groups::inst::pfec_group_p256::Inimportat32point>, _>>::new(move |x| crate::primitives::el_gamal::inst::el_gamal_p256::gen_enc_dec(
          <num::BigInt>::number((), 1usize).as_arg(),
          <num::BigInt>::number((), 2usize).as_arg(),
          x.as_arg(),
        )),
        tvqx_1_enc.as_arg(),
      );
    let tvqx_1_dec =
      crate::cryptol::map_inst_sz_val_val::<crate::algebra::groups::inst::pfec_group_p256::Inimportat32point, cry_rts::DWord>(
        5usize,
        &<cry_rts::Fn1<cry_rts::O<crate::algebra::groups::inst::pfec_group_p256::Inimportat32point>, _>>::new(move |x| crate::algebra::encoders::inst::encoder_utils_p256::strictqx_1_decode(x
          .as_arg())),
        tvqx_1_run.as_arg(),
      );
    tvqx_1_dec
  }
}
