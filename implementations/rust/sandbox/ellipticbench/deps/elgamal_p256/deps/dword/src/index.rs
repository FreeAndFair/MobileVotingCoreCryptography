use crate::{DWord,DWordRef};

/// Specify from which side of a word are we indexing.
#[derive(Clone,Copy)]
pub enum IndexFrom {
  /// Index from the last signficatn side of the word.
  Lsb,

  /// Index from the most signficatn side of the word.
  Msb
}


/// Direction for indexing.
pub trait IndexDir: Clone {
  const DIR: IndexFrom;
}

/// Index from the last signficatn side of the word.
#[derive(Clone,Copy)]
pub struct FromLSB;

/// Index from the most signficatn side of the word.
#[derive(Clone,Copy)]
pub struct FromMSB;

impl IndexDir for FromLSB { const DIR: IndexFrom = IndexFrom::Lsb; }
impl IndexDir for FromMSB { const DIR: IndexFrom = IndexFrom::Msb; }

impl<'a> DWordRef<'a> {

  /// Extract a bit at the given index.
  pub fn index<INDEX: IndexDir>(self, index: usize) -> bool {
    assert!(index < self.bits());

    // Turn into LSB index
    let i = match INDEX::DIR {
              IndexFrom::Msb => self.bits() - index - 1,
              IndexFrom::Lsb => index
            };

    let data = self.as_slice();
    let ix   = i + self.padding();
    let w    = data[ix / DWord::LIMB_BITS];
    w & (1 << (ix % DWord::LIMB_BITS)) != 0
  }

  pub fn index_msb(self, i: usize) -> bool { self.index::<FromMSB>(i) }
  pub fn index_lsb(self, i: usize) -> bool { self.index::<FromLSB>(i) }


  pub fn leading_zeros(self) -> usize {
    if self.bits() == 0 { return 0 }

    let mut tot = 0_usize;
    let ws  = self.as_slice();
    for i in (1 .. self.limbs()).rev() {
      let w = ws[i];
      let n = w.leading_zeros() as usize;
      tot += n;
      if n < DWord::LIMB_BITS { return tot }
    }

    tot + (ws[0].leading_zeros() as usize).min(self.not_padding())
  }
}

impl DWord {
  pub fn set_bit<INDEX: IndexDir>(&mut self, index: usize, value: bool) {
    assert!(index < self.bits());
    let i = match INDEX::DIR {
              IndexFrom::Msb => self.bits() - index - 1,
              IndexFrom::Lsb => index
            };
    let ix   = i + self.padding();
    let data = self.as_slice_mut();
    let bit  = 1 << (ix % DWord::LIMB_BITS);
    if value {
      data[ix / DWord::LIMB_BITS] |= bit
    } else {
      data[ix / DWord::LIMB_BITS] &= !bit;
      self.fix_underflow()
    }
  }

  pub fn set_bit_lsb(&mut self, index: usize, value: bool) {
    self.set_bit::<FromLSB>(index,value)
  }

  pub fn set_bit_msb(&mut self, index: usize, value: bool) {
    self.set_bit::<FromMSB>(index,value)
  }

}

#[cfg(test)]
mod test {
  use crate::{DWord,FromLSB,FromMSB};
  use crate::proptest::*;

  #[test]
  fn index_lsb() {
    do_test(word_and::<usize>, |(x,i0) : (DWord,usize) | {
      if x.bits() == 0 { return Some(true) }
      let i = i0 % x.bits();
      let (xr,a) = x.sem();
      return Some(xr.index::<FromLSB>(i) == a.bit(i as u64))
    })
  }

  #[test]
  fn index_msb() {
    do_test(word_and::<usize>, |(x,i0) : (DWord,usize) | {
      if x.bits() == 0 { return Some(true) }
      let i = i0 % x.bits();
      let j = (x.bits() - 1 - i) as u64;
      let (xr,a) = x.sem();
      return Some(xr.index::<FromMSB>(i) == a.bit(j))
    })
  }

  #[test]
  fn test_leading_zeros() {
    do_test(unary, |x: DWord| {
      let r = x.as_ref();
      let n = r.leading_zeros();
      assert!(n <= x.bits());
      for i in 0 .. n { assert_eq!(r.index_msb(i),false) }
      if n < r.bits() { assert_eq!(r.index_msb(n),true) }
      return Some(true)
    })
  }

}
