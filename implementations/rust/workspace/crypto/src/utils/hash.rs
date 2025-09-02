/*
 * Hashing utilities
 *
 * @author David Ruescas (david@sequentech.io)\
 * @author Frank Zeyda (frank.zeyda@freeandfair.us)\
 * @copyright Free & Fair. 2025\
 * @version 0.1
 */

use sha3::digest::FixedOutput;
use sha3::{Digest, Sha3_256, Sha3_512};

/**
 * Hashing cryptographic [group][`crate::traits::groups::CryptoGroup`] dependency.
 *
 * Allows retrieving a hasher instance in some [Context][`crate::context::Context`].
 */
pub trait Hasher: Digest + FixedOutput {
    /// Returns a hasher instance.
    fn hasher() -> Self;
}

/**
 * Implements the hashing group dependency with `Sha3_512`.
 */
impl Hasher for Sha3_512 {
    fn hasher() -> Self {
        Sha3_512::new()
    }
}

/**
 * Implements the hashing group dependency with `Sha3_256`.
 */
impl Hasher for Sha3_256 {
    fn hasher() -> Self {
        Sha3_256::new()
    }
}

/// Hashing to 512 bits provided by sha3
pub type Hasher512 = Sha3_512;
/// Hashing to 256 bits provided by sha3
pub type Hasher256 = Sha3_256;

/// Updates the hasher with the given data slices and their corresponding tags.
///
/// This function is used to derive challenges via random oracles.
pub fn update_hasher(hasher: &mut impl Digest, data_slices: &[&[u8]], ds_tags: &[&[u8]]) {
    for (i, slice) in data_slices.iter().enumerate() {
        hasher.update(slice);
        if ds_tags.len() > i {
            hasher.update(ds_tags[i]);
        }
    }
}
