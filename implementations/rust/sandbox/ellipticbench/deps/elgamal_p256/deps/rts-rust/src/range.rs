use crate::traits::*;
use crate::type_traits::*;
use crate::*;
use num::Zero;

// Iterator for going up
#[derive(Clone)]
struct FromTo<const CLO: bool> {
  current: num::BigUint,
  step:    num::BigUint,
  last:    num::BigUint
}

impl<const CLO: bool> Iterator for FromTo<CLO> {
  type Item = num::BigUint;
  fn next(&mut self) -> Option<Self::Item> {
    let end = if CLO { self.current > self.last } else
                     { self.current >= self.last };
    if end { return None }
    let result = self.current.clone();
    self.current += &self.step;
    Some(result)
  }
}


/// Iterator for going up to infinity. While most Cryptol range-related
/// primitives require the upper bound to be finite, `fromToLessThan` and
/// `fromToByLess` can have an infinite upper bound, so this iterator exists to
/// support the cases when these primitives have an upper bound of `inf`.
#[derive(Clone)]
struct FromToInf {
  current: num::BigUint,
  step:    num::BigUint,
}

impl Iterator for FromToInf {
  type Item = num::BigUint;
  fn next(&mut self) -> Option<Self::Item> {
    let result = self.current.clone();
    self.current += &self.step;
    Some(result)
  }
}


// Iterator for going down
#[derive(Clone)]
struct FromDownTo<const CLO: bool> {
  current: num::BigUint,
  step:    num::BigUint,
  last:    num::BigUint
}

// We assume that both `current` and `last` start off incremented by a `step`
impl<const CLO: bool> Iterator for FromDownTo<CLO> {
  type Item = num::BigUint;
  fn next(&mut self) -> Option<Self::Item> {
    let end = if CLO { self.current < self.last }
                else { self.current <= self.last };
    if end { return None }
    self.current -= &self.step;
    Some(self.current.clone())
  }
}



// -----------------------------------------------------------------------------
// fromTo and friends (usize versions)
//
pub fn from_to_usize<T: Literal>
  (len: T::Length, from: usize, to: usize) -> impl Stream<T> {
  (from ..= to).map(move |x| <T>::number_usize(len.clone(),x))
}

pub fn from_to_less_than_usize<T: Literal>
  (len: T::Length, from: usize, to: usize) -> impl Stream<T> {
  (from .. to).map(move |x| <T>::number_usize(len.clone(),x))
}

pub fn from_to_by_usize<T: Literal>
  (len: T::Length, from: usize, to: usize, step: usize) -> impl Stream<T> {
  (from ..= to).step_by(step).map(move |x| <T>::number_usize(len.clone(),x))
}

pub fn from_to_by_less_than_usize<T: Literal>
  (len: T::Length, from: usize, to: usize, step: usize) -> impl Stream<T> {
  (from .. to).step_by(step).map(move |x| <T>::number_usize(len.clone(),x))
}

pub fn from_to_down_by_usize<T: Literal>
  (len: T::Length, from: usize, to: usize, step: usize) -> impl Stream<T> {
  // Use Iterator::rev() to go down instead of up.
  (to ..= from).rev().step_by(step).map(move |x| <T>::number_usize(len.clone(),x))
}

pub fn from_to_down_by_greater_than_usize<T: Literal>
  (len: T::Length, from: usize, to: usize, step: usize) -> impl Stream<T> {
  // Rust doesn't have a way to write a range that excludes the first element
  // (such that the reverse range would exclude the last element), so we fake it
  // by adding one to the (inclusive) first element.
  (to+1 ..= from).rev().step_by(step).map(move |x| <T>::number_usize(len.clone(),x))
}

pub fn from_then_to_usize<T: Literal>
    (len: T::Length, mut from: usize, then: usize, to: usize) -> impl Stream<T>
{
  let (mut n, delta) = if from < then {
    if from <= to {
      let d = then - from;
      let n = (to - from) / d + 1;
      (n, d)
    } else {
      (0, 0)
    }
  } else if then < from {
    if to <= from {
      let d = from - then;
      let n = (from - to) / d + 1;
      (n, d.wrapping_neg())
    } else {
      (0, 0)
    }
  } else {
    panic!("distinct from and then required")
  };

  std::iter::from_fn(move || {
    if n > 0 {
      let r = <T>::number_usize(len.clone(), from);
      n -= 1;
      from = from.wrapping_add(delta);
      Some(r)
    } else {
      None
    }
  })
}



// -----------------------------------------------------------------------------
// fromTo and friends (big num versions)

pub fn from_to_uint<T: Literal>
  (len: T::Length, from: num::BigUint, to: num::BigUint) -> impl Stream<T> {
  FromTo::<true> { current: from, step: 1u8.into(), last: to }
  .map(move |x| <T>::number_uint(len.clone(),&x))
}

pub fn from_to_less_than_uint<T: Literal>
  (len: T::Length, from: num::BigUint, to: num::BigUint) -> impl Stream<T> {
  FromTo::<false> { current: from, step: 1u8.into(), last: to }
  .map(move |x| <T>::number_uint(len.clone(),&x))
}

/// A variant of `from_to_less_than_uint` where the upper bound is infinite.
pub fn from_to_inf_uint<T: Literal>
  (len: T::Length, from: num::BigUint) -> impl Stream<T> {
  FromToInf { current: from, step: 1u8.into() }
  .map(move |x| <T>::number_uint(len.clone(), &x))
}

pub fn from_to_by_uint<T: Literal>
  (len: T::Length, from: num::BigUint, to: num::BigUint, step: num::BigUint) ->
                                                              impl Stream<T> {
  FromTo::<true> { current: from, step: step, last: to }
  .map(move |x| <T>::number_uint(len.clone(),&x))
}

pub fn from_to_by_less_than_uint<T: Literal>
  (len: T::Length, from: num::BigUint, to: num::BigUint, step: num::BigUint) ->
                                                              impl Stream<T> {
  FromTo::<false> { current: from, step: step, last: to }
  .map(move |x| <T>::number_uint(len.clone(),&x))
}

/// A variant of `from_to_by_less_than_uint` where the upper bound is infinite.
pub fn from_to_by_inf_uint<T: Literal>
  (len: T::Length, from: num::BigUint, step: num::BigUint) -> impl Stream<T> {
  FromToInf { current: from, step: step }
  .map(move |x| <T>::number_uint(len.clone(), &x))
}

pub fn from_to_down_by_uint<T: Literal>
  (len: T::Length, from: num::BigUint, to: num::BigUint, step: num::BigUint) ->
                                                              impl Stream<T> {
  let start = from + &step;
  let end   = to   + &step;
  FromDownTo::<true> { current: start, step: step, last: end }
  .map(move |x| <T>::number_uint(len.clone(),&x))
}

pub fn from_to_down_by_greater_than_uint<T: Literal>
  (len: T::Length, from: num::BigUint, to: num::BigUint, step: num::BigUint) ->
                                                              impl Stream<T> {
  let start = from + &step;
  let end   = to   + &step;
  FromDownTo::<false> { current: start, step: step, last: end }
  .map(move |x| <T>::number_uint(len.clone(),&x))
}


pub fn from_then_to_uint<T: Literal>
    (len: T::Length, mut from: num::BigUint, then: num::BigUint, to: num::BigUint) -> impl Stream<T>
{
  #[derive(Clone)]
  enum Delta {
    PosDelta(num::BigUint),
    NegDelta(num::BigUint),
  }

  let (mut n, delta) = if from < then {
    let d = then - &from;
    let delta = Delta::PosDelta(d.clone());

    if from <= to {
      let n = (to - &from) / &d + 1u64;
      (n, delta)
    } else {
      (num::BigUint::zero(), delta)
    }
  } else if then < from {
    let d = &from - then;
    let delta = Delta::NegDelta(d.clone());

    if to <= from {
      let n = (&from - to) / &d + 1u64;
      (n, delta)
    } else {
      (num::BigUint::zero(), delta)
    }
  } else {
    panic!("distinct from and then required")
  };

  std::iter::from_fn(move || {
    if n > num::BigUint::zero() {
      let r = <T>::number_uint(len.clone(), &from);
      n -= 1u64;
      from = match &delta {
        Delta::PosDelta(d) => &from + d,
        Delta::NegDelta(d) => &from - d,
      };
      Some(r)
    } else {
      None
    }
  })
}








// -----------------------------------------------------------------------------
// infFrom and infFromThen
// Note that these are ont Integers (signed)

#[derive(Clone)]
struct InfFromThen {
  current: num::BigInt,
  step:    num::BigInt
}

impl Iterator for InfFromThen {
  type Item = num::BigInt;
  fn next(&mut self) -> Option<num::BigInt> {
    let result = self.current.clone();
    self.current += &self.step;
    Some(result)
  }
}

pub fn inf_from_then<T:Integral>
  (len: T::Length, start: T::Arg<'_>, next: T::Arg<'_>) -> impl Stream<T> {
  let start_i = T::to_integer(start);
  let step   = T::to_integer(next) - &start_i;
  InfFromThen { current: start_i, step: step }
    .map(move |x| <T>::from_integer(len.clone(), &x))
}

pub fn inf_from<T:Integral>
  (len: T::Length, start: T::Arg<'_>) -> impl Stream<T> {

  InfFromThen {
    current: T::to_integer(start),
    step: 1u8.into()
  }.map(move |x| <T>::from_integer(len.clone(), &x))
}





// ------------------------------------------------------------------------------
// Join helpers

pub fn join_words(xs: impl Stream<DWord>) -> impl Stream<bool> {
  xs.flat_map(move |w| w.into_iter_bits_msb())
}

pub fn join_vecs<T: Type>(xs: impl Stream<Vec<T>>) -> impl Stream<T> {
  xs.flat_map(move |w| w.into_iter())
}

#[cfg(test)]
mod test {
  use num::FromPrimitive;

use super::*;

  #[test]
  fn down() {
    assert_eq!(from_to_down_by_uint::<DWord>(
      8,
      num::BigUint::from_i32(10).unwrap(),
      num::BigUint::from_i32(0).unwrap(),
      num::BigUint::from_i32(3).unwrap()
    ).to_vec(), [DWord::from_u32(8, 10), DWord::from_u32(8, 7), DWord::from_u32(8, 4), DWord::from_u32(8, 1)]);
  }

  #[test]
  fn test_from_then_to_usize(){
    assert_eq!(from_then_to_usize::<DWord>(8, 1,3,8).to_vec(), [DWord::from_u32(8, 1), DWord::from_u32(8, 3), DWord::from_u32(8, 5), DWord::from_u32(8, 7)]);
    assert_eq!(from_then_to_usize::<DWord>(8, 1,3,5).to_vec(), [DWord::from_u32(8, 1), DWord::from_u32(8, 3), DWord::from_u32(8, 5)]);
    assert_eq!(from_then_to_usize::<DWord>(8, 1,3,6).to_vec(), [DWord::from_u32(8, 1), DWord::from_u32(8, 3), DWord::from_u32(8, 5)]);
    assert_eq!(from_then_to_usize::<DWord>(8, 1,3,3).to_vec(), [DWord::from_u32(8, 1), DWord::from_u32(8, 3)]);
    assert_eq!(from_then_to_usize::<DWord>(8, 1,3,1).to_vec(), [DWord::from_u32(8, 1)]);
    assert_eq!(from_then_to_usize::<DWord>(8, 5,3,1).to_vec(), [DWord::from_u32(8, 5), DWord::from_u32(8, 3), DWord::from_u32(8, 1)]);
  }
}
