/*
 * Root module for the stateright protocol model
 *
 * @author David Ruescas (david@sequentech.io)\
 * @copyright Free & Fair. 2025\
 * @version 0.1
 */

#![allow(dead_code)]
pub mod decrypt;
pub mod dkg;
pub mod mix;
pub mod protocol;

use std::array;
use std::collections::BTreeSet;
use std::fmt::{Display, Formatter};
use std::hash::{DefaultHasher, Hash as HashTrait, Hasher};
use std::marker::PhantomData;

use crypto::cryptosystem::elgamal::Ciphertext as EGCiphertext;
use crypto::cryptosystem::naoryung::Ciphertext as NYCiphertext;
use crypto::utils::serialization::VSerializable;
use crypto::zkp::shuffle::ShuffleProof;
use rand::Rng;
use strum::Display;

const MAX_TRUSTEES: usize = 24;
const HASH_SIZE: usize = 8;

#[derive(Clone, Hash, PartialEq, Eq, PartialOrd, Ord, Copy)]
pub(crate) struct Hash([u8; HASH_SIZE]);
impl Hash {
    pub(crate) fn random() -> Self {
        let mut bytes = [0u8; HASH_SIZE];
        rand::thread_rng().fill(&mut bytes);
        Hash(bytes)
    }
    pub(crate) fn empty() -> Self {
        let bytes = [0u8; HASH_SIZE];
        Hash(bytes)
    }
}

impl Display for Hash {
    fn fmt(&self, f: &mut Formatter<'_>) -> Result<(), std::fmt::Error> {
        let mut hex = hex::encode(&self.0);
        hex.truncate(6);
        write!(f, "{}", hex)
    }
}
impl std::fmt::Debug for Hash {
    fn fmt(&self, f: &mut Formatter<'_>) -> Result<(), std::fmt::Error> {
        let mut hex = hex::encode(&self.0);
        hex.truncate(6);
        write!(f, "{}", hex)
    }
}

pub(crate) mod types {
    use super::AccumulatorSet;
    use super::Hash;

    pub(crate) type CfgHash = Hash;
    pub(crate) type TrusteeSharesHash = Hash;
    pub(crate) type PublicKeyHash = Hash;
    pub(crate) type CiphertextsHash = Hash;
    pub(crate) type SharesHashesAcc = AccumulatorSet<TrusteeSharesHash>;
    pub(crate) type SharesHashes = Vec<TrusteeSharesHash>;
    pub(crate) type Sender = TrusteeIndex;
    pub(crate) type TrusteeIndex = usize;
    pub(crate) type TrusteeCount = usize;
    pub(crate) type PartialDecryptionsHash = Hash;
    pub(crate) type PartialDecryptionsHashesAcc = AccumulatorSet<PartialDecryptionsHash>;
    pub(crate) type PartialDecryptionsHashes = Vec<PartialDecryptionsHash>;
    pub(crate) type PlaintextsHash = Hash;
}

#[derive(Clone, PartialEq, Eq, Hash, Debug, PartialOrd, Ord)]
pub(crate) enum Action {
    ComputeShares(CfgHash, TrusteeIndex),
    ComputePublicKey(CfgHash, SharesHashes, TrusteeIndex),
    ComputeMix(CfgHash, PublicKeyHash, CiphertextsHash, TrusteeIndex),
    SignMix(
        CfgHash,
        PublicKeyHash,
        CiphertextsHash,
        CiphertextsHash,
        TrusteeIndex,
    ),
    SignChain(
        CfgHash,
        PublicKeyHash,
        CiphertextsHash,
        CiphertextsHash,
        TrusteeIndex,
    ),
    ComputePartialDecryptions(CfgHash, PublicKeyHash, CiphertextsHash, TrusteeIndex),
    ComputePlaintexts(
        CfgHash,
        PublicKeyHash,
        CiphertextsHash,
        PartialDecryptionsHashes,
        TrusteeIndex,
    ),
    ComputeBallots(CfgHash, PublicKeyHash),
}

use types::*;

#[derive(Clone, PartialEq, Eq, Hash, Debug, Display, Ord, PartialOrd)]
pub(crate) enum Message {
    ConfigurationValid(CfgHash, TrusteeCount, TrusteeCount, TrusteeIndex),
    Shares(CfgHash, TrusteeSharesHash, Sender),
    PublicKey(CfgHash, PublicKeyHash, Sender),
    Ballots(CfgHash, PublicKeyHash, CiphertextsHash, Vec<TrusteeIndex>),
    // cfg hash, pk hash, mix input hash, mix output hash, sender
    Mix(
        CfgHash,
        PublicKeyHash,
        CiphertextsHash,
        CiphertextsHash,
        TrusteeIndex,
    ),
    // cfg hash, pk hash, mix input hash, mix output hash, sender
    MixSignature(
        CfgHash,
        PublicKeyHash,
        CiphertextsHash,
        CiphertextsHash,
        TrusteeIndex,
    ),
    // unused
    MixCompleteSignature(
        CfgHash,
        PublicKeyHash,
        CiphertextsHash,
        CiphertextsHash,
        TrusteeIndex,
    ),
    PartialDecryptions(
        CfgHash,
        PublicKeyHash,
        CiphertextsHash,
        PartialDecryptionsHash,
        TrusteeIndex,
    ),
    Plaintexts(
        CfgHash,
        PublicKeyHash,
        CiphertextsHash,
        PlaintextsHash,
        TrusteeIndex,
    ),
}
impl Message {
    // Every message has a unique "slot". Even though checks for this should exist
    // outside our protocol logic, we can perform these checks here as well.
    fn collides(&self, other: &Message) -> bool {
        if self == other {
            return false;
        }
        if std::mem::discriminant(self) != std::mem::discriminant(other) {
            return false;
        }

        match (self, other) {
            (Message::Shares(_, _shares1, sender1), Message::Shares(_, _shares2, sender2)) => {
                sender1 == sender2
            }
            (
                Message::PublicKey(_, _shares1, sender1),
                Message::PublicKey(_, _shares2, sender2),
            ) => sender1 == sender2,
            (Message::Ballots(_, _, _, _), Message::Ballots(_, _, _, _)) => true,
            (Message::Mix(_, _, _, _, sender1), Message::Mix(_, _, _, _, sender2)) => {
                sender1 == sender2
            }
            (
                Message::MixSignature(_, _, in_ciphertexts1, out_ciphertexts1, sender1),
                Message::MixSignature(_, _, in_ciphertexts2, out_ciphertexts2, sender2),
            ) => {
                sender1 == sender2
                    && ((in_ciphertexts1 == in_ciphertexts2)
                        || (out_ciphertexts1 == out_ciphertexts2))
            }
            _ => false,
        }
    }

    fn get_cfg(&self) -> CfgHash {
        match self {
            Message::ConfigurationValid(cfg_hash, _, _, _) => *cfg_hash,
            Message::Shares(cfg_hash, _, _) => *cfg_hash,
            Message::PublicKey(cfg_hash, _, _) => *cfg_hash,

            Message::Ballots(cfg_hash, _, _, _) => *cfg_hash,
            Message::Mix(cfg_hash, _, _, _, _) => *cfg_hash,

            Message::MixSignature(cfg_hash, _, _, _, _) => *cfg_hash,
            Message::MixCompleteSignature(cfg_hash, _, _, _, _) => *cfg_hash,
            Message::PartialDecryptions(cfg_hash, _, _, _, _) => *cfg_hash,
            Message::Plaintexts(cfg_hash, _, _, _, _) => *cfg_hash,
        }
    }
}

pub(crate) mod crypto_params {
    pub(crate) type Ctx = crypto::context::RistrettoCtx;
    pub(crate) const W: usize = 2;
    pub(crate) const T: usize = 2;
    pub(crate) const P: usize = 3;
}

ascent::ascent_source! { prelude:
    relation error(String);
    relation message(Message);
    relation active(TrusteeIndex);

    error(format!("duplicate message {:?}, {:?}", m1, m2)) <--
        message(m1),
        message(m2),
        if m1.collides(m2);

    // this message comes from the setup phase
    relation configuration_valid(CfgHash, TrusteeCount, TrusteeCount, TrusteeIndex);
    configuration_valid(cfg_hash, threshold, trustee_count, self_index) <--
        message(m),
        if let Message::ConfigurationValid(cfg_hash, threshold, trustee_count, self_index) = m;

    error(format!("message cfg does not match context {:?}", m1)) <--
        message(m1),
        configuration_valid(cfg_hash, _, _, _),
        if m1.get_cfg() != *cfg_hash;


    relation action(Action);
}

#[derive(Clone, HashTrait, PartialEq, Eq, Debug)]
pub struct AccumulatorSet<T> {
    values: [Option<T>; MAX_TRUSTEES],
    value_set: BTreeSet<T>,
}
impl<T: Ord + std::fmt::Debug + Clone> AccumulatorSet<T> {
    pub fn new(init: T) -> Self {
        AccumulatorSet {
            values: std::array::from_fn(|_| None),
            value_set: BTreeSet::new(),
        }
        .add(init, 1)
    }
    fn add(&self, rhs: T, index: TrusteeIndex) -> Self {
        let mut ret = AccumulatorSet {
            values: self.values.clone(),
            value_set: self.value_set.clone(),
        };

        if !ret.value_set.contains(&rhs) && ret.values[index] == None {
            ret.value_set.insert(rhs.clone());
            ret.values[index] = Some(rhs.clone());
        }
        /*else {
            panic!("Value {:?} duplicated {:?}", rhs, self);
        }*/

        ret
    }
    fn is_complete(&self, trustee_count: usize) -> bool {
        self.value_set.len() == trustee_count
    }

    fn extract(&self) -> Vec<T> {
        let some = self.values.iter().filter(|t| t.is_some());
        some.map(|t| t.clone().expect("impossible")).collect()
    }
}

use crypto::context::Context;
use std::hash::Hash as StdHash;

pub(crate) trait GetHash {
    fn get_hash(&self) -> Hash;
}
impl<T: StdHash> GetHash for T {
    fn get_hash(&self) -> Hash {
        let mut hasher = crate::hasher();
        self.hash(&mut hasher);
        Hash(hasher.finish().to_be_bytes())
    }
}

fn hasher() -> DefaultHasher {
    std::hash::DefaultHasher::new()
}

#[derive(Clone, PartialEq, Debug)]
pub(crate) struct Plaintexts<C: Context, const W: usize> {
    values: Vec<[C::Element; W]>,
}
impl<C: Context, const W: usize> StdHash for Plaintexts<C, W> {
    fn hash<H>(&self, h: &mut H)
    where
        H: std::hash::Hasher,
    {
        let bytes = self.values.ser();

        h.write(&bytes)
    }
}
impl<C: Context, const W: usize> Plaintexts<C, W> {
    fn new(values: Vec<[C::Element; W]>) -> Self {
        Self { values }
    }
}

#[derive(Clone, PartialEq, Debug)]
pub struct Ballots<C: Context, const W: usize, const T: usize> {
    pub ciphertexts: Vec<NYCiphertext<C, W>>,
    pub participants: [TrusteeIndex; T],
}
impl<C: Context, const W: usize, const T: usize> Ballots<C, W, T> {
    fn new(ciphertexts: Vec<NYCiphertext<C, W>>, participants: [TrusteeIndex; T]) -> Self {
        Self {
            ciphertexts,
            participants,
        }
    }
}
impl<C: Context, const W: usize, const T: usize> StdHash for Ballots<C, W, T> {
    fn hash<H>(&self, h: &mut H)
    where
        H: std::hash::Hasher,
    {
        let mut bytes = self.ciphertexts.ser();
        let participants: Vec<u8> = self
            .participants
            .iter()
            .map(|p| p.to_be_bytes())
            .flatten()
            .collect();
        bytes.extend_from_slice(&participants);

        h.write(&bytes)
    }
}

#[derive(Clone, PartialEq, Debug)]
pub struct Mix<C: Context, const W: usize> {
    pub mixed_ballots: Vec<EGCiphertext<C, W>>,
    pub proof: ShuffleProof<C, W>,
}
impl<C: Context, const W: usize> Mix<C, W> {
    fn new(mixed_ballots: Vec<EGCiphertext<C, W>>, proof: ShuffleProof<C, W>) -> Self {
        Self {
            mixed_ballots,
            proof,
        }
    }
}
impl<C: Context, const W: usize> StdHash for Mix<C, W> {
    fn hash<H>(&self, h: &mut H)
    where
        H: std::hash::Hasher,
    {
        let mut bytes = self.mixed_ballots.ser();
        bytes.extend_from_slice(&self.proof.ser());

        h.write(&bytes)
    }
}

#[derive(Clone, Hash, PartialEq)]
pub(crate) struct HashBoard<C: Context, const W: usize, const T: usize, const P: usize> {
    pub(crate) messages: Vec<Message>,
    pub(crate) cfg_hash: CfgHash,
    pub(crate) pk_hash: PublicKeyHash,
    pub(crate) ballots_hash: CiphertextsHash,
    pub(crate) mix_hashes: [CiphertextsHash; T],
    pub(crate) mixing_trustees: [TrusteeIndex; T],
    phantom_c: PhantomData<C>,
}
impl<C: Context, const W: usize, const T: usize, const P: usize> HashBoard<C, W, T, P> {
    pub(crate) fn new(cfg_hash: CfgHash) -> Self {
        let messages: [Message; P] =
            array::from_fn(|i| Message::ConfigurationValid(cfg_hash, T, P, i + 1));
        let messages = messages.to_vec();
        let pk_hash = Hash::empty();
        let ballots_hash = Hash::empty();
        let mix_hashes = [Hash::empty(); T];
        let mixing_trustees = [0; T];

        Self {
            messages,
            cfg_hash,
            pk_hash,
            ballots_hash,
            mix_hashes,
            mixing_trustees,
            phantom_c: PhantomData,
        }
    }

    pub(crate) fn add_pk(&mut self, pk_hash: PublicKeyHash, sender: TrusteeIndex) {
        let message = Message::PublicKey(self.cfg_hash, pk_hash, sender + 1);
        self.pk_hash = pk_hash;
        self.messages.push(message);
    }

    pub(crate) fn add_ballots(
        &mut self,
        ballots_hash: CiphertextsHash,
        trustees: [TrusteeIndex; T],
    ) {
        let pk_hash = self.pk_hash;
        let message = Message::Ballots(self.cfg_hash, pk_hash, ballots_hash, trustees.to_vec());
        self.mixing_trustees = trustees;
        self.ballots_hash = ballots_hash;
        self.messages.push(message);
    }

    pub(crate) fn add_mix(
        &mut self,
        input_hash: CiphertextsHash,
        mix_hash: CiphertextsHash,
        sender: TrusteeIndex,
    ) {
        let sender = sender + 1;
        let message = Message::Mix(self.cfg_hash, self.pk_hash, input_hash, mix_hash, sender);
        self.mix_hashes[sender - 1] = mix_hash;
        self.messages.push(message);

        for i in 1..=T {
            if i != sender && self.mixing_trustees.contains(&i) {
                let message =
                    Message::MixSignature(self.cfg_hash, self.pk_hash, input_hash, mix_hash, i);
                self.messages.push(message);
            }
        }
    }
}

impl<C: Context, const W: usize, const T: usize, const P: usize> std::fmt::Debug
    for HashBoard<C, W, T, P>
{
    fn fmt(&self, f: &mut Formatter<'_>) -> Result<(), std::fmt::Error> {
        let as_strings: Vec<String> = self.messages.iter().map(|m| format!("{:?}", m)).collect();

        write!(f, "{}", as_strings.join(", "))
    }
}
