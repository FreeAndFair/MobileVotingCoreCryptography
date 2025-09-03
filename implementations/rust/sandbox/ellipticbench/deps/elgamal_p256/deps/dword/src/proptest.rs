use crate::core::{LimbT, limbs_for_size};
use crate::{DWord, DWordRef};
use num::pow::Pow;
use proptest::arbitrary::*;
use proptest::collection::vec;
use proptest::prelude::*;
use proptest::strategy::*;
use proptest::test_runner::*;
use rand::random;

impl ValueTree for DWord {
    type Value = DWord;

    fn current(&self) -> DWord {
        self.clone()
    }

    fn simplify(&mut self) -> bool {
        false
    }
    fn complicate(&mut self) -> bool {
        false
    }
}

#[derive(Debug, Clone, Copy)]
pub struct DWordStrategy {
    pub bits: usize,
}

impl Strategy for DWordStrategy {
    type Tree = DWord;
    type Value = DWord;

    fn new_tree(&self, runner: &mut TestRunner) -> NewTree<Self> {
        let n = limbs_for_size(self.bits);
        let mut limbs = Vec::<LimbT>::with_capacity(n);
        let rng = runner.rng();
        for _ in 0..n {
            limbs.push(rng.next_u64())
        }
        let mut result = DWord::from_limbs(self.bits, limbs);
        result.fix_underflow();
        Ok(result)
    }
}

impl Arbitrary for DWord {
    type Parameters = usize;
    type Strategy = DWordStrategy;

    fn arbitrary_with(bits: usize) -> Self::Strategy {
        DWordStrategy { bits: bits }
    }
}

pub fn do_test<T: Arbitrary, F: Fn(usize) -> StrategyFor<T>>(s: F, p: fn(T) -> Option<bool>) {
    for bits in 0..517 {
        let mut cfg: Config = <_>::default();
        cfg.failure_persistence = None;
        let mut runner = TestRunner::new(cfg);
        let strategy = s(bits);
        runner
            .run(&strategy, |arg| match p(arg) {
                Some(result) => {
                    if result {
                        Ok(())
                    } else {
                        Err(TestCaseError::Fail("unexpected result".into()))
                    }
                }
                None => Err(TestCaseError::Reject("invalid input".into())),
            })
            .unwrap()
    }
}

pub fn do_test2<T: Arbitrary>(s: fn(usize, usize) -> StrategyFor<T>, p: fn(T) -> Option<bool>) {
    let max = 30;

    for bits1_ in 0..max {
        let bits1 = bits1_ * 2;

        for bits2_ in 0..max - bits1_ {
            let bits2 = bits2_ * 3;

            let mut cfg: Config = <_>::default();
            cfg.failure_persistence = None;
            let mut runner = TestRunner::new(cfg);
            let strategy = s(bits1, bits2);
            runner
                .run(&strategy, |arg| match p(arg) {
                    Some(result) => {
                        if result {
                            Ok(())
                        } else {
                            Err(TestCaseError::Fail("unexpected result".into()))
                        }
                    }
                    None => Err(TestCaseError::Reject("invalid input".into())),
                })
                .unwrap()
        }
    }
}

impl DWord {
    pub fn sem<'a>(&'a self) -> (DWordRef<'a>, num::BigUint) {
        let x = self.as_ref();
        (x, x.into())
    }
}

pub fn pow2(bits: usize) -> num::BigUint {
    let x: num::BigUint = 2_u64.into();
    <num::BigUint as Pow<usize>>::pow(x, bits)
}

pub fn binary(bits: usize) -> StrategyFor<(DWord, DWord)> {
    two_words(bits, bits)
}

pub fn two_words(bits1: usize, bits2: usize) -> StrategyFor<(DWord, DWord)> {
    arbitrary_with((bits1, bits2))
}

pub fn unary(bits: usize) -> StrategyFor<DWord> {
    arbitrary_with(bits)
}

pub fn word_and<T>(bits: usize) -> StrategyFor<(DWord, T)>
where
    T: Arbitrary<Parameters = ()>,
{
    arbitrary_with((bits, ()))
}

pub fn word_and2<S, T>(bits: usize) -> StrategyFor<(DWord, S, T)>
where
    S: Arbitrary<Parameters = ()>,
    T: Arbitrary<Parameters = ()>,
{
    arbitrary_with((bits, (), ()))
}

pub fn word_vec(bits: usize) -> StrategyFor<Vec<DWord>> {
    vec(arbitrary_with(bits), 0..100)
}
