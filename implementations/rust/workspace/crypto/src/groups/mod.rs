/*
 * Curve arithmetic backends and generic product groups
 *
 * @author David Ruescas (david@sequentech.io)\
 * @author Frank Zeyda (frank.zeyda@freeandfair.us)\
 * @copyright Free & Fair. 2025\
 * @version 0.1
 */

//! Curve arithmetic backends and generic product groups
//!
//! # [`p256`]
//!
//! Group over curve P-256, backed by the [p256](https://github.com/RustCrypto/elliptic-curves/tree/master/p256) crate
//!
//! # [`ristretto255`]
//!
//! Group over the Ristretto group, backed by the [curve25519-dalek](https://github.com/dalek-cryptography/curve25519-dalek) crate
//!
//! # [`productgroup`]
//!
//! Product implementations of [`GroupElement`][`crate::traits::groups::GroupElement`] and [`GroupScalar`][`crate::traits::groups::GroupScalar`].
//! and their broadcast variants [`DistGroupOps`][`crate::traits::groups::DistGroupOps`], [`ReplGroupOps`][`crate::traits::groups::ReplGroupOps`] and
//! [`DistScalarOps`][`crate::traits::groups::DistScalarOps`], [`ReplScalarOps`][`crate::traits::groups::ReplScalarOps`].
//!
//! Product groups are represented as arrays with type `[T; N]`
//!
//! # Examples
//!
//! ```
//! use crypto::context::Context;
//! use crypto::context::RistrettoCtx as Ctx;
//! use crypto::groups::ristretto255::{RistrettoScalar, RistrettoElement};
//! use crate::crypto::traits::groups::{GroupScalar, GroupElement};
//! use crate::crypto::traits::groups::{DistGroupOps, ReplGroupOps};
//!
//! let mut rng = Ctx::get_rng();
//! // some random scalars
//! let rs = <[RistrettoScalar; 3]>::random(&mut rng);
//! // some random elements
//! let es = <[RistrettoElement; 3]>::random(&mut rng);
//!
//! // product types implement element and scalar traits,
//! // so product operations of matching shapes is transparent:
//! // compute `es_rs = es^rs = (e1^r1, e2^r2, ...)
//! let es_rs = es.exp(&rs) ;
//!
//! let g = Ctx::generator();
//! // compute `g_rs = g^(r1, r2, ...) = (g^r1, g^r2, ...)`
//! let g_rs = g.repl_exp(&rs);
//!
//! // compute `es_r = (e1, e2, ...)^r = (e1^r, e2^2, ...)`
//! let r = Ctx::random_scalar();
//! let es_r = es.dist_exp(&r);
//! ```

/// Group over curve P-256, backed by the [p256](https://github.com/RustCrypto/elliptic-curves/tree/master/p256) crate
pub mod p256;
/// Generic product groups for elements and scalars
pub mod productgroup;
/// Group over the Ristretto group, backed by the [curve25519-dalek](https://github.com/dalek-cryptography/curve25519-dalek) crate
pub mod ristretto255;

pub use p256::P256Group;
pub use ristretto255::Ristretto255Group;
