/*
 * p256 benchmark code
 *
 * @author David Ruescas (david@sequentech.io)\
 * @copyright Free & Fair. 2025\
 * @version 0.1
 */

use p256::elliptic_curve::Group;
use p256::{NonZeroScalar, ProjectivePoint};
use rand::rngs::ThreadRng;

/// Generate a random scalar for P-256
pub fn random_scalar(rng: &mut ThreadRng) -> NonZeroScalar {
    // Use the built-in random generation for NonZeroScalar
    NonZeroScalar::random(rng)
}

/// Generate a random point on the P-256 curve (not the generator)
pub fn random_point(rng: &mut ThreadRng) -> ProjectivePoint {
    let scalar = random_scalar(rng);
    &ProjectivePoint::random(rng) * &scalar
}

/// Multiply the generator point by a scalar
pub fn multiply_generator(scalar: &NonZeroScalar) -> ProjectivePoint {
    &ProjectivePoint::generator() * scalar
}

/// Multiply a random point by a scalar
pub fn multiply_random_point(point: &ProjectivePoint, scalar: &NonZeroScalar) -> ProjectivePoint {
    point * scalar
}

/// Run a benchmark for generator point multiplication
pub fn bench_generator_multiplication(iterations: usize) -> (f64, f64, f64) {
    let mut rng = rand::thread_rng();

    // Pre-generate all scalars to ensure timing only measures the multiplication
    let scalars: Vec<NonZeroScalar> = (0..iterations).map(|_| random_scalar(&mut rng)).collect();

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
    let points: Vec<ProjectivePoint> = (0..iterations).map(|_| random_point(&mut rng)).collect();
    let scalars: Vec<NonZeroScalar> = (0..iterations).map(|_| random_scalar(&mut rng)).collect();

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
