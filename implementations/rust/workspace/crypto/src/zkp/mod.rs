/*
 * Zero knowledge proofs module
 *
 * @author David Ruescas (david@sequentech.io)\
 * @author Frank Zeyda (frank.zeyda@freeandfair.us)\
 * @copyright Free & Fair. 2025\
 * @version 0.1
 */

//! Zero knowledge proofs
//!
//! # [Schnorr][`crate::zkp::schnorr`]
//!
//! Proves knowledge of a discrete logarithm.
//!
//! See `EVS`: Protocol 10.1
//!
//! This proof is currently unused in the protocol.
//!
//! # [Discrete log equality][`crate::zkp::dlogeq`]
//!
//! Proves equality of discrete logarithms.
//!
//! See `EVS`: Protocol 10.3
//!
//! This proof is used to verify partial decryption correctness.
//! See [`decryption_factor`][`crate::dkgd::recipient::Recipient::decryption_factor`]
//!
//! # [Plaintext equality][`crate::zkp::pleq`]
//!
//! Proves equality of plaintexts.
//!
//! See `EVS`: Protocol 10.8
//!
//! This proof is used to construct the [`Naor-Yung`][`crate::cryptosystem::naoryung`]
//! cryptosystem and in the validation of its ciphertexts.
//!
//! # [Shuffle][`crate::zkp::shuffle`]
//!
//! Terelius-Wikstrom proof of shuffle.
//!
//! See `EVS`: Protocol 12.3
//!
//! This proof is used to verify that shuffled ciphertexts correspond to
//! their inputs, or equivalently that their set of corresponding plaintexts
//! are equal.

/// Discrete logarithm equality proofs.
pub mod dlogeq;

/// Plaintext equality proofs.
pub mod pleq;

/// Schnorr knowledge of discrete logarithm proofs.
pub mod schnorr;

#[crate::warning("Asserts are present in this module")]
/// Terelius-Wikstrom proof of shuffle.
pub mod shuffle;
