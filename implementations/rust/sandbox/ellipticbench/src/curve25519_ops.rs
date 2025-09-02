/*
 * Curve25519 benchmark code
 *
 * @author David Ruescas (david@sequentech.io)\
 * @copyright Free & Fair. 2025\
 * @version 0.1
 */

use curve25519_dalek::ristretto::RistrettoPoint;
use curve25519_dalek::scalar::Scalar;
use rand::rngs::ThreadRng;

/// Generate a random scalar for Curve25519
pub fn random_scalar(rng: &mut ThreadRng) -> Scalar {
    /*let mut bytes = [0u8; 32];
    rng.fill(&mut bytes);
    Scalar::from_bytes_mod_order(bytes)*/
    Scalar::random(rng)
}

/// Generate a random point on the Curve25519 (not the generator)
pub fn random_point(rng: &mut ThreadRng) -> RistrettoPoint {
    RistrettoPoint::random(rng)
}

/// Multiply the generator point by a scalar
pub fn multiply_generator(scalar: &Scalar) -> RistrettoPoint {
    RistrettoPoint::mul_base(scalar)
}

/// Multiply a random point by a scalar
pub fn multiply_random_point(point: &RistrettoPoint, scalar: &Scalar) -> RistrettoPoint {
    point * scalar
}

/// Run a benchmark for generator point multiplication
pub fn bench_generator_multiplication(iterations: usize) -> (f64, f64, f64) {
    let mut rng = rand::thread_rng();

    // Pre-generate all scalars to ensure timing only measures the multiplication
    let scalars: Vec<Scalar> = (0..iterations).map(|_| random_scalar(&mut rng)).collect();

    // Measure individual operations and collect times
    let mut times = Vec::with_capacity(iterations);

    for scalar in &scalars {
        let start = crate::utils::now();
        let _result = multiply_generator(scalar);
        let duration = start.elapsed();
        // Convert to milliseconds
        times.push(duration.as_micros() as f64 / 1000.0);
    }

    // Calculate statistics
    let avg = times.iter().sum::<f64>() / times.len() as f64;
    let min = *times
        .iter()
        .min_by(|a, b| a.partial_cmp(b).unwrap())
        .unwrap();
    let max = *times
        .iter()
        .max_by(|a, b| a.partial_cmp(b).unwrap())
        .unwrap();

    (avg, min, max)
}

/// Run a benchmark for random point multiplication
pub fn bench_random_point_multiplication(iterations: usize) -> (f64, f64, f64) {
    let mut rng = rand::thread_rng();

    // Pre-generate all points and scalars
    let points: Vec<RistrettoPoint> = (0..iterations).map(|_| random_point(&mut rng)).collect();
    let scalars: Vec<Scalar> = (0..iterations).map(|_| random_scalar(&mut rng)).collect();

    // Measure individual operations and collect times
    let mut times = Vec::with_capacity(iterations);

    for i in 0..iterations {
        let start = crate::utils::now();
        let _result = multiply_random_point(&points[i], &scalars[i]);
        let duration = start.elapsed();
        // Convert to milliseconds
        times.push(duration.as_micros() as f64 / 1000.0);
    }

    // Calculate statistics
    let avg = times.iter().sum::<f64>() / times.len() as f64;
    let min = *times
        .iter()
        .min_by(|a, b| a.partial_cmp(b).unwrap())
        .unwrap();
    let max = *times
        .iter()
        .max_by(|a, b| a.partial_cmp(b).unwrap())
        .unwrap();

    (avg, min, max)
}
