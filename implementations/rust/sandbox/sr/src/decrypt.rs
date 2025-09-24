/*
 * Protocol decryption phase
 *
 * @author David Ruescas (david@sequentech.io)\
 * @copyright Free & Fair. 2025\
 * @version 0.1
 */

pub(crate) mod infer {

    ascent::ascent_source! { decrypt_infer:

        relation partial_decryptions(CfgHash, PublicKeyHash, CiphertextsHash, PartialDecryptionsHash, Sender);
        partial_decryptions(cfg_hash, pk_hash, ciphertexts_hash, partial_decryptions, sender) <--
            message(m),
            if let Message::PartialDecryptions(cfg_hash, pk_hash, ciphertexts_hash, partial_decryptions, sender) = m;

        action(Action::ComputePartialDecryptions(*cfg_hash, *pk_hash, *out_ciphertexts_hash, *self_index)) <--
            configuration_valid(cfg_hash, _, _, self_index),
            ballots(cfg_hash, pk_hash, ciphertexts_hash, mixing_trustees),
            mix_complete(cfg_hash, pk_hash, ciphertexts_hash, out_ciphertexts_hash),
            mixing_position(cfg_hash, pk_hash, ciphertexts_hash, _, self_index),
            !partial_decryptions(cfg_hash, pk_hash, _, _, self_index);

        relation plaintexts(CfgHash, PublicKeyHash, CiphertextsHash, PlaintextsHash, Sender);
        plaintexts(cfg_hash, pk_hash, ciphertexts_hash, plaintexts_hash, sender) <--
            message(m),
            if let Message::Plaintexts(cfg_hash, pk_hash, ciphertexts_hash, plaintexts_hash, sender) = m;

        relation partial_decryptions_acc(CfgHash, PartialDecryptionsHashesAcc, /*Sender*/);
        partial_decryptions_acc(cfg_hash, AccumulatorSet::new(*partial_decryptions)) <--
            mixing_position(cfg_hash, pk_hash, ciphertexts_hash, 1, trustee),
            ballots(cfg_hash, pk_hash, ciphertexts_hash, mixing_trustees),
            partial_decryptions(cfg_hash, pk_hash, _, partial_decryptions, trustee);

        partial_decryptions_acc(cfg_hash, partial_decryptions_hashes.add(*partial_decryptions, *position)) <--
            partial_decryptions_acc(cfg_hash, partial_decryptions_hashes),
            mixing_position(cfg_hash, pk_hash, ciphertexts_hash, position, trustee),
            partial_decryptions(cfg_hash, pk_hash, _, partial_decryptions, trustee);

        relation partial_decryptions_all(CfgHash, PartialDecryptionsHashesAcc);
        partial_decryptions_all(cfg_hash, partial_decryptions) <--
            partial_decryptions_acc(cfg_hash, partial_decryptions),
            configuration_valid(cfg_hash, threshold, _, self_index),
            if partial_decryptions.is_complete(*threshold);

        action(Action::ComputePlaintexts(*cfg_hash, *pk_hash, *ciphertexts_hash, partial_decryptions.extract(), *self_index)) <--
            configuration_valid(cfg_hash, _, _, self_index),
            partial_decryptions_all(cfg_hash, partial_decryptions),
            ballots(cfg_hash, pk_hash, ciphertexts_hash, mixing_trustees),
            // uncomment this if we only want selected trustees to compute plaintexts
            mixing_position(cfg_hash, pk_hash, ciphertexts_hash, _, self_index),
            !plaintexts(cfg_hash, pk_hash, ciphertexts_hash, _, self_index);

        error(format!("plaintext mismatch {:?} != {:?} ({} {})", ciphertexts_hash1, ciphertexts_hash2, sender1, sender2)) <--
            plaintexts(cfg_hash, pk_hash, ciphertexts_hash1, _, sender1),
            plaintexts(cfg_hash, pk_hash, ciphertexts_hash2, _, sender2),
            if ciphertexts_hash1 != ciphertexts_hash2;

    }
}

mod composed_infer {
    use crate::types::*;
    use crate::{AccumulatorSet, Action, Message};

    ascent::ascent! {
        include_source!(crate::prelude);
        include_source!(crate::dkg::infer::dkg_infer);
        include_source!(crate::mix::infer::mix_infer);
        include_source!(crate::decrypt::infer::decrypt_infer);
    }

    pub(crate) fn program() -> AscentProgram {
        AscentProgram::default()
    }
}

pub(crate) mod execute {

    ascent::ascent_source! { decrypt_execute:

        message(Message::PartialDecryptions(*cfg_hash, *pk_hash, *ciphertexts_hash, partial_decryptions_stub(*trustee, ciphertexts_hash), *trustee)) <--
            action(compute_partial_decryptions),
            if let Action::ComputePartialDecryptions(cfg_hash, pk_hash, ciphertexts_hash, trustee) = compute_partial_decryptions,
            active(trustee);

        // we use the fixed value of 1, because honest trustees will compute the same public key
        message(Message::Plaintexts(*cfg_hash, *pk_hash, *ciphertexts_hash, plaintexts_stub(*trustee, partial_decryptions), *trustee)) <--
            action(compute_plaintexts),
            if let Action::ComputePlaintexts(cfg_hash, pk_hash, ciphertexts_hash, partial_decryptions, trustee) = compute_plaintexts,
            active(trustee);
    }
}

pub(crate) mod execute_functions {
    use crate::Hash;
    use crate::types::*;

    pub(crate) fn partial_decryptions_stub(
        trustee: usize,
        input: &CiphertextsHash,
    ) -> CiphertextsHash {
        // println!("* execute: partial decryptions stub for input {}, trustee {}", input, _trustee);
        Hash(input.0.clone().map(|i| (i % 240) + trustee as u8))
    }

    pub(crate) fn plaintexts_stub(
        _trustee: usize,
        input: &PartialDecryptionsHashes,
    ) -> PlaintextsHash {
        // println!("* execute: computing plaintexts for trustee {}", trustee);
        Hash(input[0].0.clone().map(|i| (i % 254) + 1))
    }
}

mod composed_execute {
    use crate::decrypt::execute_functions::*;
    use crate::types::*;
    use crate::{Action, Message};

    ascent::ascent! {
        include_source!(crate::prelude);
        // include_source!(crate::dkg::execute::dkg_execute);
        // include_source!(crate::mix::execute::mix_execute);
        include_source!(crate::decrypt::execute::decrypt_execute);
    }

    pub(crate) fn program() -> AscentProgram {
        AscentProgram::default()
    }
}

use std::marker::PhantomData;

use crate::Hash;
use crate::HashBoard;
use crate::{Action, Message};
use crypto::context::Context;
use stateright::{Model, Property};

// stateright test harness
struct Harness<C: Context, const W: usize, const T: usize, const P: usize> {
    phantom_c: PhantomData<C>,
}
impl<C: Context, const W: usize, const T: usize, const P: usize> Harness<C, W, T, P> {
    pub(crate) fn new() -> Self {
        Self {
            phantom_c: PhantomData,
        }
    }
    pub(crate) fn get_bb() -> HashBoard<C, W, T, P> {
        let mut ret = crate::mix::Harness::get_bb();

        for i in 0..T {
            let hash = if i == 0 {
                ret.ballots_hash
            } else {
                ret.mix_hashes[i - 1]
            };
            let mix_hash = Hash::random();
            ret.add_mix(hash, mix_hash, i);
        }

        ret
    }
}
impl<C: Context, const W: usize, const T: usize, const P: usize> Model for Harness<C, W, T, P> {
    type State = HashBoard<C, W, T, P>;
    type Action = Action;

    fn init_states(&self) -> Vec<Self::State> {
        let init = Self::get_bb();

        vec![init]
    }

    fn actions(&self, state: &Self::State, actions: &mut Vec<Self::Action>) {
        let mut prog = composed_infer::program();

        let messages: Vec<(Message,)> = state.messages.iter().map(|m| (m.clone(),)).collect();
        prog.message = messages;
        prog.run();
        let mut actions_: Vec<Action> = prog.action.into_iter().map(|a| a.0).collect();

        if prog.error.len() != 0 {
            println!("* actions: found errors: {:?}", prog.error);
            return;
        }

        if actions_.len() == 0 {
            // println!("** End state **");
        } else {
            // println!("* actions {:?} => {:?}", state.0, actions_);
            // println!("* current_messages {:?} => actions {:?}", state.messages.len(), actions_);
            actions.append(&mut actions_);
        }
    }

    fn next_state(&self, last_state: &Self::State, action: Self::Action) -> Option<Self::State> {
        let mut prog = composed_execute::program();

        // println!("* next_state action {:?}", action);
        prog.action = vec![(action.clone(),)];
        let active: Vec<(usize,)> = (1..=P).map(|i| (i,)).collect();
        prog.active = active;
        prog.run();
        let mut messages_: Vec<Message> = prog.message.into_iter().map(|m| m.0).collect();

        let ret = if messages_.len() > 0 {
            // println!("* {}..{:?} + {:?} => {:?}", last_state.messages.len(), last_state.messages.last().unwrap(), action, messages_);
            // println!(" {:?} => next state messages: {}", action, messages_.len());
            let mut ret = last_state.clone();
            ret.messages.append(&mut messages_);

            Some(ret)
        } else {
            // println!("* next_state: No next state *");
            None
        };
        ret
    }

    fn properties(&self) -> Vec<Property<Self>> {
        let decrypt_complete = Property::<Self>::eventually("decrypt complete", |_, state| {
            state.messages.iter().any(|m| match m {
                Message::Plaintexts(crate::dkg::DUMMY_CFG, _, _, _, _) => true,
                _ => false,
            })
        });

        vec![decrypt_complete]
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crypto::context::RistrettoCtx;
    use stateright::Checker;

    #[test]
    fn check_decrypt() {
        let harness = Harness::<RistrettoCtx, 2, 2, 3>::new();
        let checker = harness.checker().spawn_bfs().join();
        checker.assert_properties();
    }

    #[ignore]
    #[test]
    fn serve_decrypt() {
        let harness = Harness::<RistrettoCtx, 2, 2, 3>::new();

        let _ = harness.checker().serve("127.0.0.1:8080");
    }
}
