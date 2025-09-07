/*
 * Digital signatures
 *
 * @author David Ruescas (david@sequentech.io)\
 * @author Frank Zeyda (frank.zeyda@freeandfair.us)\
 * @copyright Free & Fair. 2025\
 * @version 0.1
 */

//! Digital signature utilities and [context][`crate::context::Context`] dependency.
//!
//! # Examples
//! ```
//! use crypto::context::Context;
//! use crypto::context::RistrettoCtx as RCtx;
//! use crypto::utils::signatures::{SignatureScheme, Signer, Verifier};
//!
//! let sk = RCtx::gen_signing_key();
//! let vk = sk.verifying_key();
//!
//! let message: &[u8] = b"message";
//! let signature = sk.sign(message);
//!
//! let vk = sk.verifying_key();
//! let ok = vk.verify(message, &signature);
//! assert!(ok.is_ok());
//! ```

use std::marker::PhantomData;

pub use ed25519::signature::{Error, Signer, Verifier};
use ed25519_dalek::ed25519;

use crate::utils::rng::CRng;

/**
 * A digital signature scheme.
 *
 * This trait defines the types and methods required for a digital signature
 * scheme, such as [`Ed25519`].
 */
#[crate::warning(
    "There is no explicit handling of contexts here, they must be provided by the caller as part of the message"
)]

pub trait SignatureScheme<R: CRng> {
    /// The signer type, a private key used for signing.
    type Signer: Signer<Self::Signature>;
    /// The verifier type, a public key used to verify signatures.
    type Verifier: Verifier<Self::Signature>;
    /// The signature type, a digital signature on some data.
    type Signature;

    /// Generates a new private signing key.
    ///
    /// The corresponding public verification key can be obtained with `signing_key.verifying_key()`.
    fn gen_signing_key(rng: &mut R) -> Self::Signer;
}

/**
 * Ed25519 digital signature scheme.
 *
 * This implementation uses the [`ed25519-dalek`](https://docs.rs/ed25519-dalek/latest/ed25519_dalek/) crate.
 *
 * # Examples
 * ```
 * use crypto::context::Context;
 * use crypto::context::RistrettoCtx as RCtx;
 * use crypto::utils::signatures::{SignatureScheme, Signer, Verifier};
 *
 * let sk = RCtx::gen_signing_key();
 * let vk = sk.verifying_key();
 *
 * let message: &[u8] = b"message";
 * let signature = sk.sign(message);
 *
 * let vk = sk.verifying_key();
 * let ok = vk.verify(message, &signature);
 * assert!(ok.is_ok());
 * ```
 */
pub struct Ed25519<R: CRng>(PhantomData<R>);
impl<R: CRng> SignatureScheme<R> for Ed25519<R> {
    type Signer = ed25519_dalek::SigningKey;
    type Verifier = ed25519_dalek::VerifyingKey;
    type Signature = ed25519_dalek::Signature;

    fn gen_signing_key(rng: &mut R) -> ed25519_dalek::SigningKey {
        Self::Signer::generate(rng)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use rand::RngCore;

    #[test]
    fn test_signatures_context() {
        use crate::context::Context;
        use crate::context::RistrettoCtx;

        let sk = RistrettoCtx::gen_signing_key();
        let vk = sk.verifying_key();

        let mut csprng = RistrettoCtx::get_rng();
        let message: &[u8] = &csprng.next_u64().to_be_bytes();
        let signature = sk.sign(message);
        let ok = vk.verify(message, &signature);
        assert!(ok.is_ok());

        let signature = sk.sign(&[]);
        let ok = vk.verify(&[], &signature);

        assert!(ok.is_ok());
    }
}
