/*
 * LibraryName project
 *
 * @author David Ruescas (david@sequentech.io)\
 * @author Frank Zeyda (frank.zeyda@freeandfair.us)\
 * @copyright Free & Fair. 2025\
 * @version 0.1
 */

#![allow(dead_code)]
// Only necessary for custom_warning_macro
#![feature(stmt_expr_attributes)]
// Only necessary for custom_warning_macro
#![feature(proc_macro_hygiene)]
#![doc = include_str!("../README.md")]
// first pass
#![deny(missing_docs)]
#![deny(rustdoc::missing_crate_level_docs)]
#![deny(rustdoc::broken_intra_doc_links)]
#![deny(clippy::missing_docs_in_private_items)]
#![deny(clippy::missing_errors_doc)]
#![deny(clippy::missing_panics_doc)]
#![deny(clippy::doc_markdown)]
#![forbid(unsafe_code)]
// 2nd pass
#![deny(clippy::unwrap_used)]
#![deny(clippy::print_stdout)]
#![deny(clippy::print_stderr)]
#![warn(clippy::pedantic)]
// 3rd pass
#![warn(clippy::arithmetic_side_effects)]
#![warn(clippy::shadow_unrelated)]
#![warn(clippy::cognitive_complexity)]
#![warn(private_interfaces)]
#![warn(private_bounds)]
#![warn(unnameable_types)]

// final pass
// #![warn(clippy::restriction)]

/// Defines implementation choices for key cryptographic functionalities.
pub mod context;
pub mod cryptosystem;
#[crate::warning(
    "Asserts are present in this module. Missing checks for threshold validity (P < T). Not optimized."
)]
pub mod dkgd;
pub mod groups;
/// Abstractions for curve arithmetic, groups, elements and scalars.
pub mod traits;
/// Utilities such as random number generation, hashing, signatures and serialization.
pub mod utils;
pub mod zkp;

pub use crate::utils::error::Error;
pub use custom_warning_macro::warning;
pub use vser_derive::VSerializable;
