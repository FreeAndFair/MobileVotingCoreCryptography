/*
 * Challenge and transport serialization.
 *
 * @author David Ruescas (david@sequentech.io)\
 * @author Frank Zeyda (frank.zeyda@freeandfair.us)\
 * @copyright Free & Fair. 2025\
 * @version 0.1
 */

//! Challenge and transport serialization.
//!
//! This module defines and implements serialization traits
//! suitable for challenge generation and data transfer. Two
//! variants of serialization are defined
//!
//! - [`fixed`][`crate::utils::serialization::fixed`]: types that can be serialized into variable length byte sequencesthat
//!
//!   A type that implements `fixed` traits requires that all its instances serialize to
//!   a sequence of bytes of equal and fixed length.
//!
//! - [`variable`][`crate::utils::serialization::variable`]: types that can be serialized into fixed length byte sequences
//!
//!   A type that implements `variable` traits does _not_ require that all its instances serialize to
//!   a sequence of bytes of equal and fixed length.
//!
//! * NOTE It is the responsibility of the implementor to ensure consistency across builds. Changes
//!   to implementations can break challenge and data transfer functionality entirely. **In particular, serialization
//!   inconsistencies can cause otherwise valid proofs to fail.**
//!
//! If the `serde` feature is enabled this module also provides an
//! adapter implementation of serde traits, based on variable length
//! serialization implementations.
//!

pub use fixed::{FDeserializable, FSer, FSerializable};
pub use variable::{LargeVector, TFTuple, VDeserializable, VSer, VSerializable};

pub mod fixed;
#[cfg(feature = "serde")]
/// Serde implementations built on `V/FSerializable` traits
#[crate::warning("Missing ristretto serialization tests and some structs.")]
pub mod serde;
pub mod variable;

#[cfg(test)]
#[cfg_attr(coverage_nightly, coverage(off))]
mod tests;
