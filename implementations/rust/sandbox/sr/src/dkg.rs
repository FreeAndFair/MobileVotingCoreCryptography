/*
 * Protocol distributed key generation phase
 *
 * @author David Ruescas (david@sequentech.io)\
 * @copyright Free & Fair. 2025\
 * @version 0.1
 */

pub(crate) mod infer {

    ascent::ascent_source! { dkg_infer:

        relation shares(CfgHash, TrusteeSharesHash, Sender);
        shares(cfg_hash, shares, sender) <--
            message(m),
            if let Message::Shares(cfg_hash, shares, sender) = m;

        action(Action::ComputeShares(*cfg_hash, *self_index)) <--
            configuration_valid(cfg_hash, _, _, self_index),
            !shares(cfg_hash, _, self_index);

        relation public_key(CfgHash, PublicKeyHash, Sender);
        public_key(cfg_hash, pk_hash, sender) <--
            message(m),
            if let Message::PublicKey(cfg_hash, pk_hash, sender) = m;

        relation shares_acc(CfgHash, SharesHashesAcc);
        shares_acc(cfg_hash, AccumulatorSet::new(*shares)) <-- shares(cfg_hash, shares, 1);

        shares_acc(cfg_hash, shares_hashes.add(*shares, *sender)) <--
            shares_acc(cfg_hash, shares_hashes),
            shares(cfg_hash, shares, sender);

        relation shares_all(CfgHash, SharesHashesAcc);
            shares_all(cfg_hash, shares) <--
            shares_acc(cfg_hash, shares),
            configuration_valid(cfg_hash, _, trustee_count, self_index),
            if shares.is_complete(*trustee_count);

        action(Action::ComputePublicKey(*cfg_hash, shares.extract(), *self_index)) <--
            configuration_valid(cfg_hash, _, _, self_index),
            shares_all(cfg_hash, shares),
            !public_key(cfg_hash, _, self_index);

        relation public_keys_acc(CfgHash, PublicKeyHash, Sender);
        public_keys_acc(cfg_hash, pk_hash, 1) <--
            public_key(cfg_hash, pk_hash, 1);

        public_keys_acc(cfg_hash, pk_hash, sender) <--
            public_key(cfg_hash, pk_hash, sender),
            public_keys_acc(cfg_hash, pk_hash, sender - 1);

        relation public_keys_all(CfgHash, PublicKeyHash);
        public_keys_all(cfg_hash, pk_hash) <--
            public_keys_acc(cfg_hash, pk_hash, trustee_count),
            configuration_valid(cfg_hash, _, trustee_count, self_index);

        error(format!("pk mismatch {:?} != {:?} ({} {})", pk_hash1, pk_hash2, sender1, sender2)) <--
            public_key(cfg_hash, pk_hash1, sender1),
            public_key(cfg_hash, pk_hash2, sender2),
            if pk_hash1 != pk_hash2;

    }
}

mod composed_infer {
    use crate::types::*;
    use crate::{AccumulatorSet, Action, Message};

    ascent::ascent! {
        include_source!(crate::prelude);
        include_source!(crate::dkg::infer::dkg_infer);
    }

    pub(crate) fn program() -> AscentProgram {
        AscentProgram::default()
    }
}

pub(crate) mod execute {

    ascent::ascent_source! { dkg_execute:

        message(Message::Shares(*cfg_hash, share_stub(*trustee), *trustee)) <--
            action(compute_shares),
            if let Action::ComputeShares(cfg_hash, trustee) = compute_shares,
            active(trustee);

        // pass cfg_hash so all trustees compute the same value of public key
        message(Message::PublicKey(*cfg_hash, pk_stub(*cfg_hash), *trustee)) <--
            action(compute_public_key),
            if let Action::ComputePublicKey(cfg_hash, shares, trustee) = compute_public_key,
            active(trustee);
    }
}

mod composed_execute {
    use crate::{Action, Message};
    use crate::{GetHash, types::*};

    ascent::ascent! {
        include_source!(crate::prelude);
        include_source!(crate::dkg::execute::dkg_execute);
    }

    pub(crate) fn program() -> AscentProgram {
        AscentProgram::default()
    }

    pub(crate) fn share_stub(trustee: usize) -> TrusteeSharesHash {
        trustee.get_hash()
    }

    pub(crate) fn pk_stub(cfg_hash: CfgHash) -> TrusteeSharesHash {
        cfg_hash.get_hash()
    }
}

use crate::{Action, HASH_SIZE, Hash, Message};
use crate::{HashBoard, types::*};
use crypto::context::Context;
use stateright::{Model, Property};
use std::marker::PhantomData;

pub(crate) const DUMMY_CFG: Hash = Hash([0u8; HASH_SIZE]);

pub(crate) struct Harness<C: Context, const W: usize, const T: usize, const P: usize> {
    pub cfg_hash: CfgHash,
    phantom_c: PhantomData<C>,
}
impl<C: Context, const W: usize, const T: usize, const P: usize> Harness<C, W, T, P> {
    pub(crate) fn new(cfg_hash: CfgHash) -> Self {
        Self {
            cfg_hash,
            phantom_c: PhantomData,
        }
    }
    pub(crate) fn get_bb() -> HashBoard<C, W, T, P> {
        HashBoard::new(DUMMY_CFG)
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
            // println!("* actions {:?} => {:?}", state, actions_);
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
            // println!("* next_state: {:?} + {:?}", last_state, messages_);
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
        let cfg_present = Property::<Self>::always("cfg present", |_, state| {
            state.messages.iter().any(|m| match m {
                &Message::ConfigurationValid(DUMMY_CFG, _, _, _) => true,
                _ => false,
            })
        });

        let shares_completed = Property::<Self>::eventually("shares completed", |_, state| {
            let shares: Vec<&Message> = state
                .messages
                .iter()
                .filter(|m| match m {
                    &Message::Shares(DUMMY_CFG, _, _) => true,
                    _ => false,
                })
                .collect();

            shares.len() == P
        });

        let pks_completed = Property::<Self>::eventually("public keys completed", |_, state| {
            let pks: Vec<&Message> = state
                .messages
                .iter()
                .filter(|m| match m {
                    &Message::PublicKey(DUMMY_CFG, _, _) => true,
                    _ => false,
                })
                .collect();

            pks.len() == P
        });

        vec![cfg_present, shares_completed, pks_completed]
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use stateright::Checker;

    use crypto::context::RistrettoCtx;

    #[test]
    fn check_dkg() {
        let checker = Harness::<RistrettoCtx, 2, 2, 3>::new(DUMMY_CFG)
            .checker()
            .spawn_bfs()
            .join();
        checker.assert_properties();
    }

    #[ignore]
    #[test]
    fn serve_dkg() {
        let harness = Harness::<RistrettoCtx, 2, 2, 3>::new(DUMMY_CFG);

        let _ = harness.checker().serve("127.0.0.1:8080");
    }
}
