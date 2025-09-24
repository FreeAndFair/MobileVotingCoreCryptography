/*
 * CryptoGroup implementations for the P-256 group
 *
 * @author David Ruescas (david@sequentech.io)\
 * @author Frank Zeyda (frank.zeyda@freeandfair.us)\
 * @copyright Free & Fair. 2025\
 * @version 0.1
 */

use crate::groups::p256::element::P256Element;
use crate::groups::p256::scalar::P256Scalar;
use crate::traits::groups::CryptoGroup;
use crate::traits::groups::GroupElement;
use crate::traits::groups::GroupScalar;

use p256::NistP256;
use p256::ProjectivePoint;
use p256::elliptic_curve::hash2curve::{ExpandMsgXmd, GroupDigest};

use crate::utils::error::Error;
use crate::utils::hash;
use crate::utils::rng;

/// P-256 implementation of [`CryptoGroup`]
pub struct P256Group;

#[allow(clippy::arithmetic_side_effects)]
impl CryptoGroup for P256Group {
    type Element = P256Element;
    type Scalar = P256Scalar;
    type Hasher = hash::Hasher256;
    type Plaintext = [u8; 30];
    type Message = Self::Element;

    fn generator() -> Self::Element {
        P256Element::new(ProjectivePoint::GENERATOR)
    }

    fn g_exp(scalar: &Self::Scalar) -> Self::Element {
        P256Element::new(ProjectivePoint::GENERATOR * scalar.0)
    }

    #[crate::warning("Panics on empty input")]
    /// # Errors
    ///
    /// - `HashToScalarError` if `NistP256::hash_to_scalar` returns error
    fn hash_to_scalar(input_slices: &[&[u8]], ds_tags: &[&[u8]]) -> Result<Self::Scalar, Error> {
        let ret = NistP256::hash_to_scalar::<ExpandMsgXmd<Self::Hasher>>(input_slices, ds_tags);

        #[crate::warning("Fix this unwrap, modify hash_to_scalar trait to return result")]
        Ok(P256Scalar(ret?))
    }

    #[crate::warning("Panics on empty input")]
    /// # Errors
    ///
    /// - `HashToElementError` if `NistP256::hash_from_bytes` returns error
    fn hash_to_element(input_slices: &[&[u8]], ds_tags: &[&[u8]]) -> Result<Self::Element, Error> {
        let ret = NistP256::hash_from_bytes::<ExpandMsgXmd<Self::Hasher>>(input_slices, ds_tags);
        let ret: Result<ProjectivePoint, Error> =
            ret.map_err(|e| Error::HashToElementError(e.to_string()));

        #[crate::warning("Fix this unwrap, modify hash_to_element trait to return result")]
        Ok(P256Element(ret?))
    }

    fn random_element<R: rng::CRng>(rng: &mut R) -> Self::Element {
        Self::Element::random(rng)
    }

    fn random_scalar<R: rng::CRng>(rng: &mut R) -> Self::Scalar {
        Self::Scalar::random(rng)
    }

    /// # Errors
    ///
    /// todo!()
    fn encode(_p: &Self::Plaintext) -> Result<Self::Message, Error> {
        todo!()
    }

    /// # Errors
    ///
    /// todo!()
    fn decode(_p: &Self::Message) -> Result<Self::Plaintext, Error> {
        todo!()
    }

    /// # Errors
    ///
    /// - `HashToElementError` if `NistP256::hash_from_bytes` returns error
    fn ind_generators(count: usize, label: &[u8]) -> Result<Vec<Self::Element>, Error> {
        let ds_tags: &[&[u8]] = &[b"context", b"independent_generators_p256_counter"];
        let mut ret = vec![];

        #[crate::warning("The following code is not optimized. Parallelize with rayon")]
        for i in 0..count {
            let inputs = &[label, &i.to_be_bytes()];
            let point = NistP256::hash_from_bytes::<ExpandMsgXmd<Self::Hasher>>(inputs, ds_tags);
            let point = point?;
            ret.push(P256Element(point));
        }

        Ok(ret)
    }
}
