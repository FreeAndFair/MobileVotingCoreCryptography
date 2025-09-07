/*
 * Group over the Ristretto group (over curve25519)
 *
 * @author David Ruescas (david@sequentech.io)\
 * @author Frank Zeyda (frank.zeyda@freeandfair.us)\
 * @copyright Free & Fair. 2025\
 * @version 0.1
 */

pub use element::RistrettoElement;
pub use group::Ristretto255Group;
pub use scalar::RistrettoScalar;

/// Ristretto implementation of [`GroupElement`](crate::traits::groups::GroupElement)
pub mod element;

/// Ristretto implementation of [`CryptoGroup`](crate::traits::groups::CryptoGroup)
pub mod group;

/// Ristretto implementation of [`GroupScalar`](crate::traits::groups::GroupScalar)
pub mod scalar;

#[cfg(test)]
#[cfg_attr(coverage_nightly, coverage(off))]
mod tests;
