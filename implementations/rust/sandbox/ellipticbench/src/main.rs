/*
 * Elliptic curve benchmark
 *
 * @author David Ruescas (david@sequentech.io)\
 * @copyright Free & Fair. 2025\
 * @version 0.1
 */

mod curve25519_ops;
mod p256_ops;
mod p384_ops;
mod p521_ops;
mod pfec_p256_ops; // This is your elgamal_p256 backend
mod secp256k1_ops;
mod utils;

use utils::format_result;

fn main() {
    println!("=============================================");

    let iterations = 1000;
    println!("Running benchmarks with {} iterations each...", iterations);
    println!();

    // Benchmark generator point multiplication
    let p256_gen_results = p256_ops::bench_generator_multiplication(iterations);
    let curve25519_gen_results = curve25519_ops::bench_generator_multiplication(iterations);
    let secp256k1_gen_results = secp256k1_ops::bench_generator_multiplication(iterations);
    let p521_gen_results = p521_ops::bench_generator_multiplication(iterations);
    let p384_gen_results = p384_ops::bench_generator_multiplication(iterations);
    let elgamal_p256_gen_results = pfec_p256_ops::bench_generator_multiplication(iterations);

    // Benchmark random point multiplication
    let p256_random_results = p256_ops::bench_random_point_multiplication(iterations);
    let curve25519_random_results = curve25519_ops::bench_random_point_multiplication(iterations);
    let secp256k1_random_results = secp256k1_ops::bench_random_point_multiplication(iterations);
    let p521_random_results = p521_ops::bench_random_point_multiplication(iterations);
    let p384_random_results = p384_ops::bench_random_point_multiplication(iterations);
    let elgamal_p256_random_results = pfec_p256_ops::bench_random_point_multiplication(iterations);

    // Print results
    println!("Results:");
    println!("--------");
    println!(
        "{}",
        format_result(
            "Generator Point Multiplication",
            p256_gen_results,
            curve25519_gen_results,
            secp256k1_gen_results,
            p521_gen_results,
            p384_gen_results,
            elgamal_p256_gen_results,
        )
    );
    println!(
        "{}",
        format_result(
            "Random Point Multiplication",
            p256_random_results,
            curve25519_random_results,
            secp256k1_random_results,
            p521_random_results,
            p384_random_results,
            elgamal_p256_random_results,
        )
    );
}
