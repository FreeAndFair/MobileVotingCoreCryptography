/*
 * Shuffle benchmark
 *
 * @author David Ruescas (david@sequentech.io)\
 * @author Frank Zeyda (frank.zeyda@freeandfair.us)\
 * @copyright Free & Fair. 2025\
 * @version 0.1
 */

//! Shuffling benchmark
//!
//! This benchmark measures the performance of the Terelius-Wikstrom [`shuffler`][`crypto::zkp::shuffle::Shuffler`]
//! for proof computation and proof verification. The benchmark will print timings for these functions.
//!
//! This benchmark can be run with
//!
//! `cargo bench shuffle`
//!
//! You can include the P-256 benchmark with
//!
//! `cargo bench shuffle -- --include-ignored`

#![feature(test)]

extern crate test;

use std::array;
use test::Bencher;
use test::black_box;

use crypto::context::Context;
use crypto::context::P256Ctx as PCtx;
use crypto::context::RistrettoCtx as RCtx;
use crypto::cryptosystem::elgamal::Ciphertext;
use crypto::cryptosystem::elgamal::KeyPair;
use crypto::traits::groups::CryptoGroup;
use crypto::zkp::shuffle::Shuffler;

/// Benchmark for the shuffle proof generation using Ristretto
#[bench]
fn bench_shuffle_prove_ristretto(b: &mut Bencher) {
    bench_shuffle_prove::<RCtx>(b);
}

/// Benchmark for the shuffle proof verification using Ristretto
#[bench]
fn bench_shuffle_verify_ristretto(b: &mut Bencher) {
    bench_shuffle_verify::<RCtx>(b);
}

/// Benchmark for the shuffle proof verification using P-256
///
/// Not run by default. Use
///
/// `cargo bench shuffle -- --include-ignored`
///
/// to run.
#[ignore]
#[bench]
fn bench_shuffle_prove_p256(b: &mut Bencher) {
    bench_shuffle_prove::<PCtx>(b);
}

/// Benchmark for the shuffle proof verification using P-256
///
/// Not run by default. Use
///
/// `cargo bench shuffle -- --include-ignored`
///
/// to run.
#[ignore]
#[bench]
fn bench_shuffle_verify_p256(b: &mut Bencher) {
    bench_shuffle_verify::<PCtx>(b);
}

/// Generic benchmark for the shuffle proof generation (`shuffle` function).
fn bench_shuffle_prove<C: Context>(b: &mut Bencher) {
    const W: usize = 3;
    let count = 100;
    let keypair: KeyPair<C> = KeyPair::generate();
    let messages: Vec<[C::Element; W]> = (0..count)
        .map(|_| array::from_fn(|_| C::random_element()))
        .collect();
    let ciphertexts: Vec<Ciphertext<C, W>> = messages.iter().map(|m| keypair.encrypt(m)).collect();

    let generators = C::G::ind_generators(count, &vec![]).unwrap();
    let shuffler = Shuffler::<C, W>::new(generators, keypair.pkey);

    b.iter(|| {
        let (_pciphertexts, _proof) = black_box(shuffler.shuffle(&ciphertexts, &vec![]).unwrap());
    });
}

/// Generic benchmark for the shuffle proof verification (`verify` function).
fn bench_shuffle_verify<C: Context>(b: &mut Bencher) {
    const W: usize = 3;
    let count = 100;
    let keypair: KeyPair<C> = KeyPair::generate();
    let messages: Vec<[C::Element; W]> = (0..count)
        .map(|_| array::from_fn(|_| C::random_element()))
        .collect();
    let ciphertexts: Vec<Ciphertext<C, W>> = messages.iter().map(|m| keypair.encrypt(m)).collect();

    let generators = C::G::ind_generators(count, &vec![]).unwrap();
    let shuffler = Shuffler::<C, W>::new(generators, keypair.pkey);

    let (pciphertexts, proof) = shuffler.shuffle(&ciphertexts, &vec![]).unwrap();

    b.iter(|| {
        let ok = black_box(
            shuffler
                .verify(&ciphertexts, &pciphertexts, &proof, &vec![])
                .unwrap(),
        );
        assert!(ok);
    });
}
