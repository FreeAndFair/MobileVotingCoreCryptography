/*
 * LargeVector benchmark
 *
 * @author David Ruescas (david@sequentech.io)\
 * @author Frank Zeyda (frank.zeyda@freeandfair.us)\
 * @copyright Free & Fair. 2025\
 * @version 0.1
 */

#![feature(test)]

extern crate test;
use test::Bencher;

use crypto::context::Context;
use crypto::context::RistrettoCtx as RCtx;
// use crypto::context::P256Ctx2 as PCtx;
use bincode;
use bincode::config;
use bincode::serde::encode_to_vec;
use crypto::cryptosystem::elgamal::Ciphertext;
use crypto::utils::serialization::LargeVector;
use crypto::utils::serialization::{FSerializable, VSerializable};
use curve25519_dalek::ristretto::RistrettoPoint;
use serde::{Serialize, Serializer};

impl serde::Serialize for Element {
    fn serialize<S>(&self, serializer: S) -> Result<S::Ok, S::Error>
    where
        S: Serializer,
    {
        let bytes = self.0.compress().to_bytes();
        serializer.serialize_bytes(&bytes)
    }
}

#[derive(Serialize)]
struct EG {
    gr: Element,
    mhr: Element,
}
struct Element(RistrettoPoint);

#[derive(Serialize)]
struct SerdeVector(Vec<EG>);

fn lvserde(lv: &SerdeVector) {
    let config = config::standard();
    let _bytes = encode_to_vec(&lv, config).unwrap();
}

fn lvser<Ctx: Context>(lv: &LargeVector<Ciphertext<Ctx, 1>>)
where
    Ctx::Element: FSerializable,
{
    let _bytes = lv.ser();
}

#[bench]
fn bench_large_vector(b: &mut Bencher) {
    let mut lv = LargeVector(vec![]);
    let count = 1000;

    for _ in 0..count {
        let gr = [RCtx::random_element()];
        let mhr = [RCtx::random_element()];

        let ciphertext = Ciphertext::<RCtx, 1>::new(gr, mhr);
        lv.0.push(ciphertext);
    }

    let bytes = lv.ser();
    println!("large_vector size = {} bytes", bytes.len());

    b.iter(|| lvser::<RCtx>(&lv));
}

#[bench]
fn bench_large_vector_serde_bincode(b: &mut Bencher) {
    let mut lv = SerdeVector(vec![]);
    let count = 1000;

    for _ in 0..count {
        let gr = RCtx::random_element();
        let mhr = RCtx::random_element();
        let gr = Element(gr.0);
        let mhr = Element(mhr.0);

        let ciphertext = EG { gr, mhr };
        lv.0.push(ciphertext);
    }

    let config = config::standard();
    let bytes = encode_to_vec(&lv, config).unwrap();
    println!("large_vector_serde_bincode size = {} bytes", bytes.len());

    b.iter(|| lvserde(&lv));
}
