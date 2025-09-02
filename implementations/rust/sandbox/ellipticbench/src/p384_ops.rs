/*
 * p-384 benchmark code
 *
 * @author David Ruescas (david@sequentech.io)\
 * @author Frank Zeyda (frank.zeyda@freeandfair.us)\
 * @copyright Free & Fair. 2025\
 * @version 0.1
 */

use p384::elliptic_curve::Group;
use p384::{NonZeroScalar, ProjectivePoint};
use rand::rngs::ThreadRng;

pub fn random_scalar(rng: &mut ThreadRng) -> NonZeroScalar {
    NonZeroScalar::random(rng)
}

pub fn random_point(rng: &mut ThreadRng) -> ProjectivePoint {
    ProjectivePoint::random(rng)
}

pub fn multiply_generator(scalar: &NonZeroScalar) -> ProjectivePoint {
    &ProjectivePoint::generator() * scalar
}

pub fn multiply_random_point(point: &ProjectivePoint, scalar: &NonZeroScalar) -> ProjectivePoint {
    point * scalar
}

pub fn bench_generator_multiplication(iterations: usize) -> (f64, f64, f64) {
    let mut rng = rand::thread_rng();

    let scalars: Vec<NonZeroScalar> = (0..iterations).map(|_| random_scalar(&mut rng)).collect();
    let mut times = Vec::with_capacity(iterations);

    for scalar in &scalars {
        let start = crate::utils::now();
        let _result = multiply_generator(scalar);
        let duration = start.elapsed();
        times.push(duration.as_micros() as f64 / 1000.0);
    }

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

pub fn bench_random_point_multiplication(iterations: usize) -> (f64, f64, f64) {
    let mut rng = rand::thread_rng();

    let points: Vec<ProjectivePoint> = (0..iterations).map(|_| random_point(&mut rng)).collect();
    let scalars: Vec<NonZeroScalar> = (0..iterations).map(|_| random_scalar(&mut rng)).collect();
    let mut times = Vec::with_capacity(iterations);

    for i in 0..iterations {
        let start = crate::utils::now();
        let _result = multiply_random_point(&points[i], &scalars[i]);
        let duration = start.elapsed();
        times.push(duration.as_micros() as f64 / 1000.0);
    }

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
