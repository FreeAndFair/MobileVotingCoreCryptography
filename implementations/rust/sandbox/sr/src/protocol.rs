/*
 * Full protocol model: from dkg to decryption
 *
 * @author David Ruescas (david@sequentech.io)\
 * @copyright Free & Fair. 2025\
 * @version 0.1
 */

mod composed_infer {
    use crate::types::*;
    use crate::{AccumulatorSet, Action, Message};

    ascent::ascent! {
        include_source!(crate::prelude);
        include_source!(crate::dkg::infer::dkg_infer);
        include_source!(crate::mix::infer::mix_infer);
        include_source!(crate::decrypt::infer::decrypt_infer);

        action(Action::ComputeBallots(*cfg_hash, *pk_hash)) <--
            public_keys_all(cfg_hash, pk_hash),
            configuration_valid(cfg_hash, _, _, self_index),
            !ballots(cfg_hash, pk_hash, _, _);
    }

    pub(crate) fn program() -> AscentProgram {
        AscentProgram::default()
    }
}

use crate::GetHash;
use crate::types::*;
use crate::{Action, Message};
use crate::{Ballots, Mix, Plaintexts};
use core::hash;
use crypto::context::Context;
use crypto::cryptosystem::elgamal::{Ciphertext as EGCiphertext, PublicKey as EGPublicKey};
use crypto::cryptosystem::naoryung::{Ciphertext as NYCiphertext, PublicKey as NYPublicKey};
use crypto::dkgd::dealer::{Dealer, DealerShares, VerifiableShare};
use crypto::dkgd::recipient::combine;
use crypto::dkgd::recipient::{DecryptionFactor, DkgCiphertext, ParticipantPosition, Recipient};
use crypto::traits::groups::CryptoGroup;
use crypto::traits::groups::GroupElement;
use crypto::zkp::shuffle::Shuffler;
use stateright::{Model, Property};
use std::array;
use std::fmt::Formatter;
use std::marker::PhantomData;

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
    pub(crate) fn get_bb() -> BulletinBoard<C, W, T, P> {
        BulletinBoard::new(crate::dkg::DUMMY_CFG)
    }
    pub(crate) fn compute_share(
        trustee: usize,
        bb: &mut BulletinBoard<C, W, T, P>,
    ) -> TrusteeSharesHash {
        // println!("compute_share: computing shares for trustee {}", trustee);
        let dealer: Dealer<C, T, P> = Dealer::generate();
        let shares = dealer.get_verifiable_shares();
        bb.add_shares(shares, trustee);

        bb.messages.get_hash()
    }
    pub(crate) fn compute_pk(trustee: usize, bb: &mut BulletinBoard<C, W, T, P>) -> PublicKeyHash {
        // println!("compute_pk: Computing pk trustee {}", trustee);
        let position = ParticipantPosition::new(trustee as u32);

        let verifiable_shares: [VerifiableShare<C, T>; P] = bb
            .shares
            .clone()
            .map(|d| d.unwrap().for_recipient(&position));

        let recipient = Recipient::from_shares(position, &verifiable_shares).unwrap();
        let pk = recipient.1;

        bb.add_pk(pk.inner, trustee);

        bb.shares.len().get_hash()
    }
    pub(crate) fn compute_ballots(
        bb: &mut BulletinBoard<C, W, T, P>,
    ) -> (CiphertextsHash, Vec<TrusteeIndex>) {
        let pk = bb.pks[0].clone().unwrap();
        // println!("compute_ballots: Computing ballots");
        let messages = vec![
            <[C::Element; W]>::random(&mut C::get_rng()),
            <[C::Element; W]>::random(&mut C::get_rng()),
            <[C::Element; W]>::random(&mut C::get_rng()),
        ];
        let ny_pk = NYPublicKey::from_elgamal(&pk, C::generator());
        let encrypted: Vec<NYCiphertext<C, W>> = messages
            .iter()
            .map(|m| ny_pk.encrypt(m, &[]).unwrap())
            .collect();

        let trustees = array::from_fn(|i| i + 1);
        bb.add_ballots(messages, encrypted, trustees);

        let hash = bb.messages.get_hash();

        (hash, trustees.to_vec())
    }

    pub(crate) fn compute_mix(
        bb: &mut BulletinBoard<C, W, T, P>,
        trustee: TrusteeIndex,
    ) -> CiphertextsHash {
        let pk = bb.pks[0].clone().unwrap();
        let ny_pk = NYPublicKey::from_elgamal(&pk, C::generator());
        let mut bs = vec![];
        if bb.mixes[0].is_none() {
            let ballots_: Result<Vec<EGCiphertext<C, W>>, crypto::Error> = bb
                .ballots
                .as_ref()
                .unwrap()
                .ciphertexts
                .iter()
                .map(|b| {
                    let ret = ny_pk.strip(b.clone(), &[])?;

                    Ok(ret)
                })
                .collect();

            bs = ballots_.unwrap();
        } else {
            for m in bb.mixes.iter() {
                if let Some(mix) = m {
                    bs = mix.mixed_ballots.clone();
                } else {
                    break;
                }
            }
        }
        assert!(bs.len() > 0);

        // println!("compute_mix: Computing mix for trustee {} with ciphertexts {}", trustee, ciphertexts);
        let generators = C::G::ind_generators(bs.len(), &[]).unwrap();
        let shuffler = Shuffler::new(generators, pk.clone());
        let (mixed, proof) = shuffler.shuffle(&bs, &[]).unwrap();
        let mix = Mix::new(mixed, proof);
        bb.add_mix(mix, trustee);

        bb.messages.get_hash()
    }

    pub(crate) fn verify_mix(bb: &mut BulletinBoard<C, W, T, P>) -> bool {
        let pk = bb.pks[0].clone().unwrap();
        let ny_pk = NYPublicKey::from_elgamal(&pk, C::generator());
        let ballots = bb.ballots.as_ref().unwrap();
        let mut input_cs = vec![];
        let mut mix: Option<Mix<C, W>> = None;

        for (i, m) in bb.mixes.iter().enumerate() {
            if let Some(m) = m {
                if i == 0 {
                    input_cs = ballots
                        .ciphertexts
                        .iter()
                        .map(|b| ny_pk.strip(b.clone(), &[]).unwrap())
                        .collect();
                } else {
                    input_cs = bb.mixes[i - 1].as_ref().unwrap().mixed_ballots.clone();
                }
                mix = Some(m.clone());
            } else {
                break;
            }
        }
        assert!(input_cs.len() > 0);
        assert!(mix.is_some());

        // println!("verify_mix: verifying mix for trustee {} with {} ballots", trustee, input_cs.len());
        let mix = mix.unwrap();
        let generators = C::G::ind_generators(input_cs.len(), &[]).unwrap();
        let shuffler = Shuffler::new(generators, pk.clone());
        let ok = shuffler
            .verify(&input_cs, &mix.mixed_ballots, &mix.proof, &[])
            .unwrap();

        ok
    }

    pub(crate) fn compute_partial_decryptions(
        bb: &mut BulletinBoard<C, W, T, P>,
        trustee: TrusteeIndex,
    ) -> PartialDecryptionsHash {
        // println!("compute_partial_decryptions: computing partial decryptions for trustee {}", trustee);
        let last_mix = bb.mixes.last().unwrap();
        let last_mix = last_mix.as_ref().unwrap();

        let position = ParticipantPosition::new(trustee as u32);

        let verifiable_shares: [VerifiableShare<C, T>; P] = bb
            .shares
            .clone()
            .map(|d| d.unwrap().for_recipient(&position));

        let recipient = Recipient::from_shares(position, &verifiable_shares).unwrap();
        let ciphertexts: Vec<DkgCiphertext<C, W, T>> = last_mix
            .mixed_ballots
            .iter()
            .map(|c| DkgCiphertext::<C, W, T>(c.clone()))
            .collect();

        let pd = recipient.0.decryption_factor(&ciphertexts, &[]).unwrap();

        bb.add_partial_decryptions(pd, trustee);

        bb.messages.get_hash()
    }

    pub(crate) fn compute_plaintexts(
        bb: &mut BulletinBoard<C, W, T, P>,
        trustee: TrusteeIndex,
    ) -> PlaintextsHash {
        // println!("compute_plaintexts: computing plaintexts for trustee {}", trustee);
        let last_mix = bb.mixes.last().unwrap();
        let last_mix = last_mix.as_ref().unwrap();
        let trustees = bb.ballots.as_ref().unwrap().participants.clone();

        let ciphertexts: Vec<DkgCiphertext<C, W, T>> = last_mix
            .mixed_ballots
            .iter()
            .map(|c| DkgCiphertext::<C, W, T>(c.clone()))
            .collect();

        let checking_values = bb.shares.clone().map(|s| s.unwrap().checking_values);
        let verification_keys: [C::Element; T] = trustees.clone().map(|i| {
            let position = ParticipantPosition::from_usize(i);
            let vk: C::Element =
                Recipient::<C, T, P>::verification_key(&position, &checking_values);
            vk
        });

        let decryptions = bb.decryptions.clone().map(|d| d.unwrap());
        let plaintexts = combine(&ciphertexts, &decryptions, &verification_keys, &[]);
        let plaintexts = Plaintexts::new(plaintexts.unwrap());

        bb.add_plaintexts(plaintexts, trustee);

        bb.messages.get_hash()
    }
}
impl<C: Context, const W: usize, const T: usize, const P: usize> Model for Harness<C, W, T, P> {
    type State = BulletinBoard<C, W, T, P>;
    type Action = Action;

    fn init_states(&self) -> Vec<Self::State> {
        let init = Self::get_bb();

        vec![init]
    }

    fn actions(&self, state: &Self::State, actions: &mut Vec<Self::Action>) {
        // println!("* actions called with state {:?}", state);
        let mut prog = composed_infer::program();

        let messages: Vec<(Message,)> = state.messages.iter().map(|m| (m.clone(),)).collect();
        prog.message = messages;
        prog.run();
        let mut actions_: Vec<Action> = prog.action.into_iter().map(|a| a.0).collect();

        if prog.error.len() != 0 {
            println!("* actions: found errors: {:?}", prog.error);
            println!("{:?}", state);
            panic!();
        }

        if actions_.len() == 0 {
            // println!("*  actions {:?} => {:?} * end state *", state.messages, actions_);
        } else {
            // println!("* current_messages {:?} => actions {:?}", state.messages.len(), actions_);
            actions_.sort();
            actions.append(&mut actions_);
        }
    }

    fn next_state(&self, last_state: &Self::State, action: Self::Action) -> Option<Self::State> {
        // println!("* next_state action {:?}", action);
        let bb = &mut last_state.clone();
        let action = vec![(action.clone(),)];
        // let action = action.clone().iter().map(|a| (a.clone(),)).collect::<Vec<(Action,)>>();
        let active: Vec<(usize,)> = (1..=P).map(|i| (i,)).collect();

        let message = ascent::ascent_run! {

            include_source!(crate::prelude);

            action(a) <-- for (a,) in action.iter();
            active(a) <-- for (a,) in active.iter();

            message(Message::Shares(*cfg_hash, Self::compute_share(*trustee, bb), *trustee)) <--
                action(compute_shares),
                if let Action::ComputeShares(cfg_hash, trustee) = compute_shares,
                active(trustee);

            message(Message::PublicKey(*cfg_hash, Self::compute_pk(*trustee, bb), *trustee)) <--
                action(compute_public_key),
                if let Action::ComputePublicKey(cfg_hash, shares, trustee) = compute_public_key,
                active(trustee);

            message(Message::Ballots(*cfg_hash, *pk_hash, ciphertexts, trustees)) <--
                action(compute_ballots),
                if let Action::ComputeBallots(cfg_hash, pk_hash) = compute_ballots,
                let (ciphertexts, trustees) = Self::compute_ballots(bb);

            message(Message::Mix(*cfg_hash, *pk_hash, *ciphertexts_hash, Self::compute_mix(bb, *trustee), *trustee)) <--
                action(compute_mix),
                if let Action::ComputeMix(cfg_hash, pk_hash, ciphertexts_hash, trustee) = compute_mix,
                active(trustee);

            message(Message::MixSignature(*cfg_hash, *pk_hash, *in_ciphertexts_hash, *out_ciphertexts_hash, *trustee)) <--
                action(sign_mix),
                if let Action::SignMix(cfg_hash, pk_hash, in_ciphertexts_hash, out_ciphertexts_hash, trustee) = sign_mix,
                active(trustee),
                if Self::verify_mix(bb) == true;

            message(Message::MixCompleteSignature(*cfg_hash, *pk_hash, *in_ciphertexts_hash, *out_ciphertexts_hash, *trustee)) <--
                action(sign_chain),
                if let Action::SignChain(cfg_hash, pk_hash, in_ciphertexts_hash, out_ciphertexts_hash, trustee) = sign_chain,
                active(trustee);

            message(Message::PartialDecryptions(*cfg_hash, *pk_hash, *ciphertexts_hash, Self::compute_partial_decryptions(bb, *trustee), *trustee)) <--
                action(compute_partial_decryptions),
                if let Action::ComputePartialDecryptions(cfg_hash, pk_hash, ciphertexts_hash, trustee) = compute_partial_decryptions,
                active(trustee);

            message(Message::Plaintexts(*cfg_hash, *pk_hash, *ciphertexts_hash, Self::compute_plaintexts(bb, *trustee), *trustee)) <--
                action(compute_plaintexts),
                if let Action::ComputePlaintexts(cfg_hash, pk_hash, ciphertexts_hash, partial_decryptions, trustee) = compute_plaintexts,
                active(trustee);

        }.message;

        let mut messages_: Vec<Message> = message.into_iter().map(|m| m.0).collect();

        let ret = if messages_.len() > 0 {
            // println!("* appending messages: {:?}", messages_);
            bb.messages.append(&mut messages_);

            Some(bb)
        } else {
            println!("* next_state: No next state *");
            None
        };

        ret.cloned()
    }

    fn properties(&self) -> Vec<Property<Self>> {
        let decrypt_complete = Property::<Self>::eventually("decrypt complete", |_, state| {
            let pls: Vec<&Message> = state
                .messages
                .iter()
                .filter(|m| match m {
                    Message::Plaintexts(_, _, _, _, _) => true,
                    _ => false,
                })
                .collect();

            pls.len() == T
        });
        let pks_completed = Property::<Self>::eventually("public keys completed", |_, state| {
            let pks: Vec<&Message> = state
                .messages
                .iter()
                .filter(|m| match m {
                    &Message::PublicKey(_, _, _) => true,
                    _ => false,
                })
                .collect();

            pks.len() == P
        });

        let ret = vec![pks_completed, decrypt_complete];

        ret
    }
}

#[derive(Clone)]
pub(crate) struct BulletinBoard<C: Context, const W: usize, const T: usize, const P: usize> {
    pub(crate) cfg_hash: CfgHash,

    pub(crate) messages: Vec<Message>,

    pub(crate) pks: [Option<EGPublicKey<C>>; P],
    pub(crate) shares: [Option<DealerShares<C, T, P>>; P],
    pub(crate) input_plaintexts: Plaintexts<C, W>,
    pub(crate) ballots: Option<Ballots<C, W, T>>,
    pub(crate) mixes: [Option<Mix<C, W>>; T],
    pub(crate) decryptions: [Option<Vec<DecryptionFactor<C, P, W>>>; T],
    pub(crate) plaintexts: [Option<Plaintexts<C, W>>; T],
}
impl<C: Context, const W: usize, const T: usize, const P: usize> BulletinBoard<C, W, T, P> {
    pub(crate) fn new(cfg_hash: CfgHash) -> Self {
        let pks = [const { None }; P];
        let shares = [const { None }; P];
        let mixes = [const { None }; T];
        let ballots = None;
        let decryptions = [const { None }; T];
        let plaintexts = [const { None }; T];

        let mut messages: [Message; P] =
            array::from_fn(|i| Message::ConfigurationValid(cfg_hash, T, P, i + 1));
        messages.sort();
        let messages = messages.to_vec();

        let input_plaintexts = Plaintexts::new(vec![]);

        Self {
            cfg_hash,
            pks,
            messages,
            shares,
            input_plaintexts,
            ballots,
            mixes,
            decryptions,
            plaintexts,
        }
    }

    pub(crate) fn add_shares(&mut self, shares: DealerShares<C, T, P>, sender: TrusteeIndex) {
        self.shares[sender - 1] = Some(shares);
    }

    pub(crate) fn add_pk(&mut self, pk: EGPublicKey<C>, sender: TrusteeIndex) {
        self.pks[sender - 1] = Some(pk);
    }

    pub(crate) fn add_ballots(
        &mut self,
        plaintexts: Vec<[C::Element; W]>,
        ballots: Vec<NYCiphertext<C, W>>,
        trustees: [TrusteeIndex; T],
    ) {
        self.input_plaintexts = Plaintexts::new(plaintexts);
        self.ballots = Some(Ballots::new(ballots, trustees));
    }

    pub(crate) fn add_mix(&mut self, mix: Mix<C, W>, sender: TrusteeIndex) {
        let ballots = self.ballots.as_ref().unwrap();
        let position = ballots
            .participants
            .iter()
            .position(|&t| t == sender)
            .unwrap();
        self.mixes[position] = Some(mix);
    }

    pub(crate) fn add_partial_decryptions(
        &mut self,
        dfactors: Vec<DecryptionFactor<C, P, W>>,
        sender: TrusteeIndex,
    ) {
        let ballots = self.ballots.as_ref().unwrap();
        let position = ballots
            .participants
            .iter()
            .position(|&t| t == sender)
            .unwrap();
        self.decryptions[position] = Some(dfactors);
    }

    pub(crate) fn add_plaintexts(&mut self, plaintexts: Plaintexts<C, W>, sender: TrusteeIndex) {
        let ballots = self.ballots.as_ref().unwrap();
        let position = ballots
            .participants
            .iter()
            .position(|&t| t == sender)
            .unwrap();
        self.plaintexts[position] = Some(plaintexts);
    }
}

impl<C: Context, const W: usize, const T: usize, const P: usize> std::fmt::Debug
    for BulletinBoard<C, W, T, P>
{
    fn fmt(&self, f: &mut Formatter<'_>) -> Result<(), std::fmt::Error> {
        let as_strings: Vec<String> = self.messages.iter().map(|m| format!("{:?}", m)).collect();

        write!(f, "{}", as_strings.join(", "))
    }
}
impl<C: Context, const W: usize, const T: usize, const P: usize> std::hash::Hash
    for BulletinBoard<C, W, T, P>
{
    fn hash<H: hash::Hasher>(&self, state: &mut H) {
        self.messages.hash(state);
        /*let mut s = self.messages.clone();
        s.sort();
        s.hash(state);*/
    }
}
impl<C: Context, const W: usize, const T: usize, const P: usize> PartialEq
    for BulletinBoard<C, W, T, P>
{
    fn eq(&self, other: &Self) -> bool {
        self.messages == other.messages
        /* let mut s = self.messages.clone();
        s.sort();
        let mut other = other.messages.clone();
        other.sort();
        s == other*/
    }
}
impl<C: Context, const W: usize, const T: usize, const P: usize> Eq for BulletinBoard<C, W, T, P> {}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::crypto_params::*;
    use stateright::Checker;

    #[test]
    fn check_protocol() {
        let harness = Harness::<Ctx, W, T, P>::new();
        let checker = harness.checker().spawn_bfs().join();
        checker.assert_properties();
    }

    #[ignore]
    #[test]
    fn serve_protocol() {
        let harness = Harness::<Ctx, W, T, P>::new();

        let _ = harness.checker().serve("127.0.0.1:8080");
    }
}
