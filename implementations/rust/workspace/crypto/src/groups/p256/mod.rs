/*
 * Group over curve P-256
 *
 * @author David Ruescas (david@sequentech.io)\
 * @author Frank Zeyda (frank.zeyda@freeandfair.us)\
 * @copyright Free & Fair. 2025\
 * @version 0.1
 */

pub use element::P256Element;
pub use group::P256Group;
pub use scalar::P256Scalar;

/// P-256 implementation of [`GroupElement`](crate::traits::groups::GroupElement)
pub mod element;

/// P-256 implementation of [`CryptoGroup`](crate::traits::groups::CryptoGroup)
pub mod group;

/// P-256 implementation of [`GroupScalar`](crate::traits::groups::GroupScalar)
pub mod scalar;

#[cfg(test)]
#[cfg_attr(coverage_nightly, coverage(off))]
mod tests;
