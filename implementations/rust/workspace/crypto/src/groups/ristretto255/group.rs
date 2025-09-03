/*
 * CryptoGroup implementations for the Ristretto group
 *
 * @author David Ruescas (david@sequentech.io)\
 * @author Frank Zeyda (frank.zeyda@freeandfair.us)\
 * @copyright Free & Fair. 2025\
 * @version 0.1
 */

use crate::traits::groups::CryptoGroup;
use crate::traits::groups::GroupElement;
use crate::traits::groups::GroupScalar;

use crate::groups::ristretto255::element::RistrettoElement;
use crate::groups::ristretto255::scalar::RistrettoScalar;

use crate::utils::error::Error;
use crate::utils::hash;
use crate::utils::hash::Hasher;
use crate::utils::rng;

use curve25519_dalek::ristretto::CompressedRistretto;
use curve25519_dalek::{RistrettoPoint, constants as dalek_constants};
use sha3::Digest;

use rayon::prelude::*;

/// Ristretto implementation of [`CryptoGroup`]
#[derive(Debug, Clone)]
pub struct Ristretto255Group;

impl CryptoGroup for Ristretto255Group {
    type Element = RistrettoElement;
    type Scalar = RistrettoScalar;
    type Hasher = hash::Hasher512;
    type Plaintext = [u8; 30];
    type Message = Self::Element;

    #[inline]
    fn generator() -> Self::Element {
        RistrettoElement::new(dalek_constants::RISTRETTO_BASEPOINT_POINT)
    }

    #[inline]
    fn g_exp(scalar: &Self::Scalar) -> Self::Element {
        RistrettoElement::new(RistrettoPoint::mul_base(&scalar.0))
    }

    /// # Errors
    ///
    /// Infallible
    fn hash_to_scalar(input_slices: &[&[u8]], ds_tags: &[&[u8]]) -> Result<Self::Scalar, Error> {
        let mut hasher = Self::Hasher::hasher();
        hash::update_hasher(&mut hasher, input_slices, ds_tags);

        let ret = RistrettoScalar::from_hash::<Self::Hasher>(hasher);

        Ok(ret)
    }

    /// # Errors
    ///
    /// Infallible
    fn hash_to_element(input_slices: &[&[u8]], ds_tags: &[&[u8]]) -> Result<Self::Element, Error> {
        let mut hasher = Self::Hasher::hasher();
        hash::update_hasher(&mut hasher, input_slices, ds_tags);

        let ret = RistrettoElement::from_hash::<Self::Hasher>(hasher);

        Ok(ret)
    }

    #[inline]
    fn random_element<R: rng::CRng>(rng: &mut R) -> Self::Element {
        Self::Element::random(rng)
    }

    #[inline]
    fn random_scalar<R: rng::CRng>(rng: &mut R) -> Self::Scalar {
        Self::Scalar::random(rng)
    }

    // see https://github.com/dalek-cryptography/curve25519-dalek/issues/322
    // see https://github.com/hdevalence/ristretto255-data-encoding/blob/master/src/main.rs
    /// # Errors
    ///
    /// - `EncodingError` if a point was not found for the input, with negligible probability
    fn encode(input: &Self::Plaintext) -> Result<Self::Message, Error> {
        let mut bytes = [0u8; 32];
        bytes[1..=input.len()].copy_from_slice(input);
        for j in 0..64u8 {
            bytes[31] = j;
            for i in 0..128u8 {
                // cannot overflow, 127 * 2 < u8::MAX
                #[allow(clippy::arithmetic_side_effects)]
                let byte = 2 * i;
                bytes[0] = byte;
                if let Some(point) = CompressedRistretto(bytes).decompress() {
                    return Ok(RistrettoElement(point));
                }
            }
        }
        Err(Error::EncodingError(
            "Failed to encode into ristretto point".to_string(),
        ))
    }

    fn decode(message: &Self::Message) -> Result<Self::Plaintext, Error> {
        let compressed = message.0.compress();
        // the 30 bytes of data are placed in the range 1-30
        let slice = &compressed.as_bytes()[1..31];
        let ret: Self::Plaintext = slice.try_into().expect("slice.len() == 30");

        Ok(ret)
    }

    /// # Errors
    ///
    /// Infallible
    fn ind_generators(count: usize, label: &[u8]) -> Result<Vec<Self::Element>, Error> {
        let mut hasher = Self::Hasher::hasher();
        hasher.update(label);
        hasher.update(b"independent_generators_ristretto");

        #[crate::warning("The following code is not optimized. Parallelize with rayon")]
        let ret: Vec<RistrettoElement> = (0..count)
            .into_par_iter()
            .map(|i| {
                let mut hasher = hasher.clone();
                hasher.update(i.to_be_bytes());
                let point = RistrettoPoint::from_hash(hasher);
                RistrettoElement(point)
            })
            .collect();

        Ok(ret)
    }
}
