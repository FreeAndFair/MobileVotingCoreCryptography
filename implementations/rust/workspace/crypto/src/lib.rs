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
#![cfg_attr(coverage_nightly, feature(coverage_attribute))]

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
pub mod traits;
/// Utilities such as random number generation, hashing, signatures and serialization.
pub mod utils;
pub mod zkp;

pub use custom_warning_macro::warning;
pub use vser_derive::VSerializable;
