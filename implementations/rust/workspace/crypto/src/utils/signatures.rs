/*
 * Digital signatures
 *
 * @author David Ruescas (david@sequentech.io)\
 * @author Frank Zeyda (frank.zeyda@freeandfair.us)\
 * @copyright Free & Fair. 2025\
 * @version 0.1
 */

use std::marker::PhantomData;

use ed25519::signature::{Signer, Verifier};
use ed25519_dalek::ed25519;

use crate::utils::error::Error;
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
    type Signer;
    /// The verifier type, a public key used to verify signatures.
    type Verifier;
    /// The signature type, a digital signature on some data.
    type Signature;

    /// Generates a new private signing key.
    ///
    /// The corresponding public verification key can be obtained with `signing_key.verifying_key()`.
    fn generate(rng: &mut R) -> Self::Signer;
    /// Signs a message with the given signer.
    ///
    /// # Parameters
    ///
    /// - `message`: The message to sign. (SIG CONTEXT)
    /// - `sk`: The private signing key used to sign the message.
    fn sign(message: &[u8], sk: &Self::Signer) -> Self::Signature;
    /// Verifies a signature on a message with the given verifier.
    ///
    /// # Parameters
    ///
    /// - `message`: The message which was signed. (SIG CONTEXT)
    /// - `signature`: The signature to verify.
    /// - `vk`: The public verification key used to verify the signature.
    ///
    /// # Errors
    ///
    /// - `SignatureError` if the signature is invalid.
    fn verify(
        message: &[u8],
        signature: &Self::Signature,
        vk: &Self::Verifier,
    ) -> Result<(), Error>;
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
 * use crypto::utils::signatures::SignatureScheme;
 *
 * type Sig = <RCtx as crypto::context::Context>::SignatureScheme;
 *
 * let mut csprng = RCtx::get_rng();
 * let sk = Sig::generate(&mut csprng);
 *
 * let message: &[u8] = b"message";
 * let signature = Sig::sign(message, &sk);
 *
 * let vk = sk.verifying_key();
 * let ok = Sig::verify(message, &signature, &vk);
 *
 * assert!(ok.is_ok());
 * ```
 */
pub struct Ed25519<R: CRng>(PhantomData<R>);
impl<R: CRng> SignatureScheme<R> for Ed25519<R> {
    type Signer = ed25519_dalek::SigningKey;
    type Verifier = ed25519_dalek::VerifyingKey;
    type Signature = ed25519_dalek::Signature;

    fn generate(rng: &mut R) -> ed25519_dalek::SigningKey {
        Self::Signer::generate(rng)
    }
    fn sign(msg: &[u8], sk: &ed25519_dalek::SigningKey) -> ed25519_dalek::Signature {
        sk.sign(msg)
    }
    fn verify(
        msg: &[u8],
        signature: &ed25519_dalek::Signature,
        vk: &ed25519_dalek::VerifyingKey,
    ) -> Result<(), Error> {
        vk.verify(msg, signature)?;

        Ok(())
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use rand::rngs::OsRng;

    #[test]
    fn test_signatures_dalek() {
        type Sig = Ed25519<OsRng>;

        let mut csprng = OsRng;
        let sk = Sig::generate(&mut csprng);

        let message: &[u8] = b"message";
        let signature = <Sig as SignatureScheme<OsRng>>::sign(message, &sk);

        let vk = sk.verifying_key();
        let ok = <Sig as SignatureScheme<OsRng>>::verify(message, &signature, &vk);

        assert!(ok.is_ok());
    }

    #[test]
    fn test_signatures_context() {
        use crate::context::Context;

        let mut csprng = OsRng;
        type Sig = <crate::context::RistrettoCtx as Context>::SignatureScheme;
        let sk = Sig::generate(&mut csprng);

        let message: &[u8] = b"message";
        let signature = Sig::sign(message, &sk);

        let vk = sk.verifying_key();
        let ok = Sig::verify(message, &signature, &vk);

        assert!(ok.is_ok());
    }
}
