/*
 * Challenge and transport serialization.
 *
 * @author David Ruescas (david@sequentech.io)\
 * @author Frank Zeyda (frank.zeyda@freeandfair.us)\
 * @copyright Free & Fair. 2025\
 * @version 0.1
 */

pub use fixed::{FDeserializable, FSer, FSerializable};
pub use variable::{LargeVector, TFTuple, VDeserializable, VSer, VSerializable};

pub mod fixed;
#[cfg(feature = "serde")]
/// Serde implementations built on `V/FSerializable` traits
#[crate::warning("Missing ristretto serialization tests and some structs.")]
pub mod serde;
pub mod variable;

#[cfg(test)]
mod tests;
