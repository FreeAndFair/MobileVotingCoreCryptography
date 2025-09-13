/*
 * Utilities: hashing, rng, serialization, signatures, error handling
 *
 * @author David Ruescas (david@sequentech.io)\
 * @author Frank Zeyda (frank.zeyda@freeandfair.us)\
 * @copyright Free & Fair. 2025\
 * @version 0.1
 */

/// Error handling.
pub mod error;

/// Hashing utilities and [context][`crate::context::Context`] dependency.
pub mod hash;

/// Random number generation utilities and [context][`crate::context::Context`] dependency.
pub mod rng;

pub mod serialization;

pub mod signatures;

pub use error::Error;
