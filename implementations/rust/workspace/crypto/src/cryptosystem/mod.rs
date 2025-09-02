/*
 * Public key cryptosystems.
 *
 * @author David Ruescas (david@sequentech.io)\
 * @author Frank Zeyda (frank.zeyda@freeandfair.us)\
 * @copyright Free & Fair. 2025\
 * @version 0.1
 */

//! Public key cryptosystems.
//!
//! # [`ElGamal`][`crate::cryptosystem::elgamal`]
//!
//! The `ElGamal` cryptosystem.
//!
//! See `EVS`: Definition 11.15
//!
//! # [`Naor-Yung`][`crate::cryptosystem::naoryung`]
//!
//! The Naor-Yung cryptosystem. This is an augmentation of `ElGamal`
//! that achieves CCA security by providing two ciphertexts of the encrypted
//! plaintext and a proof of plaintext equality for them. In this implementation
//! a Naor-Yung key pair is obtained by augmenting an `ElGamal` key pair with
//! an additional public key for which the secret is never computed. This additional
//! public key is derived from publicly available information, through a hash
//! function, see [`KeyPair::generate`][`crate::cryptosystem::naoryung::KeyPair::generate`] and [`KeyPair::new`][`crate::cryptosystem::naoryung::KeyPair::new`].
//!
//! Naor-Yung ciphertexts are validated by checking their associated proofs, after
//! which they yield plain `ElGamal` ciphertexts, see [`PublicKey::strip`][`crate::cryptosystem::naoryung::PublicKey::strip`].
//!
//! See `EVS`: Definition 11.31
//!
//! # Examples
//!
//! ```
//! use crypto::cryptosystem::naoryung::KeyPair as NYKeyPair;
//! use crypto::cryptosystem::elgamal::KeyPair as EGKeyPair;
//! use crypto::cryptosystem::elgamal;
//! use crypto::context::Context;
//! use crypto::context::RistrettoCtx as RCtx;
//!
//! // Set to some relevant context value
//! let keypair_context = &[];
//!
//! // generate an `ElGamal` key pair
//! let eg_keypair: EGKeyPair<RCtx> = EGKeyPair::generate();
//! // augment it to a `Naor-Yung` key pair
//! let ny_keypair: NYKeyPair<RCtx> = NYKeyPair::augment(&eg_keypair, keypair_context).unwrap();
//! let message = [RCtx::random_element(); 2];
//! // Set to some relevant context value
//! let encryption_context = &[];
//! // computes a `Naor-Yung` ciphertext
//! let ciphertext = ny_keypair.encrypt(&message, encryption_context).unwrap();
//!
//! // stripping a `Naor-Yung` ciphertexts verifies its proof and returns an
//! // `ElGamal` ciphertext
//! let stripped: elgamal::Ciphertext<RCtx, 2> = ny_keypair.strip(ciphertext, encryption_context).unwrap();
//!
//! // decrypt using plain `ElGamal` decryption
//! let decrypted = eg_keypair.decrypt(&stripped);
//! assert_eq!(message, decrypted);
//! ```

/// `ElGamal` cryptosystem.
pub mod elgamal;
/// Naor-Yung cryptosystem.
pub mod naoryung;
