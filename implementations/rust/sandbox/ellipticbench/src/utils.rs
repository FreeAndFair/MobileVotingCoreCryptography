/*
 * Benchmark utilities
 *
 * @author David Ruescas (david@sequentech.io)\
 * @author Frank Zeyda (frank.zeyda@freeandfair.us)\
 * @copyright Free & Fair. 2025\
 * @version 0.1
 */

pub fn format_result(
    name: &str,
    p256_results: (f64, f64, f64),
    curve25519_results: (f64, f64, f64),
    secp256k1_results: (f64, f64, f64),
    p521_results: (f64, f64, f64),
    p384_results: (f64, f64, f64),
    pfec_p256_results: (f64, f64, f64),
) -> String {
    let (p256_avg, p256_min, p256_max) = p256_results;
    let (c25519_avg, c25519_min, c25519_max) = curve25519_results;
    let (secp256k1_avg, secp256k1_min, secp256k1_max) = secp256k1_results;
    let (p521_avg, p521_min, p521_max) = p521_results;
    let (p384_avg, p384_min, p384_max) = p384_results;
    let (pfec_avg, pfec_min, pfec_max) = pfec_p256_results;

    // Find the fastest average time
    let min_avg = p256_avg
        .min(c25519_avg)
        .min(secp256k1_avg)
        .min(p521_avg)
        .min(p384_avg)
        .min(pfec_avg);

    // Calculate relative performance ratios (normalized to fastest = 1.0)
    let p256_ratio = p256_avg / min_avg;
    let c25519_ratio = c25519_avg / min_avg;
    let secp256k1_ratio = secp256k1_avg / min_avg;
    let p521_ratio = p521_avg / min_avg;
    let p384_ratio = p384_avg / min_avg;
    let pfec_ratio = pfec_avg / min_avg;

    format!(
        "{:<30} |\n\
         P-256:              avg={:.3}ms, min={:.3}ms, max={:.3}ms (relative: {:.2}x) |\n\
         Curve25519:         avg={:.3}ms, min={:.3}ms, max={:.3}ms (relative: {:.2}x) |\n\
         secp256k1:          avg={:.3}ms, min={:.3}ms, max={:.3}ms (relative: {:.2}x) |\n\
         P-521:              avg={:.3}ms, min={:.3}ms, max={:.3}ms (relative: {:.2}x) |\n\
         P-384:              avg={:.3}ms, min={:.3}ms, max={:.3}ms (relative: {:.2}x) |\n\
         pfec_p256:          avg={:.3}ms, min={:.3}ms, max={:.3}ms (relative: {:.2}x)",
        name,
        p256_avg,
        p256_min,
        p256_max,
        p256_ratio,
        c25519_avg,
        c25519_min,
        c25519_max,
        c25519_ratio,
        secp256k1_avg,
        secp256k1_min,
        secp256k1_max,
        secp256k1_ratio,
        p521_avg,
        p521_min,
        p521_max,
        p521_ratio,
        p384_avg,
        p384_min,
        p384_max,
        p384_ratio,
        pfec_avg,
        pfec_min,
        pfec_max,
        pfec_ratio
    )
}

/*use cpu_time::ProcessTime;
pub fn now() -> ProcessTime {
    ProcessTime::now()
}*/

/*
Using cpu_time on windows returns timings at 15.625ms which breaks the benchmarks.
Use this on windows
*/

use std::time::Instant;
pub fn now() -> Instant {
    Instant::now()
}
