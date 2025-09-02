use std::marker::PhantomData;
use crate::{DWord,DWordRef};
use crate::index::{IndexDir,FromLSB,FromMSB};

impl<'a> DWordRef<'a> {

  /// Iterate over the bits.
  pub fn iter_bits<INDEX: IndexDir>(self) -> TraverseBitsBorrowed<'a, INDEX> {
    TraverseBitsBorrowed { dir: PhantomData, vec: self, ix: 0 }
  }

  /// Iterate over the bits, starting at the most significant end.
  pub fn iter_bits_msb(self) ->
    TraverseBitsBorrowed<'a, FromMSB> { self.iter_bits() }

  /// Iterate over the bits, starting at the least significant end.
  pub fn iter_bits_lsb(self) ->
    TraverseBitsBorrowed<'a, FromLSB> { self.iter_bits() }
}

/// Traverse DWord as bits, starting from most significant.
#[derive(Clone)]
pub struct TraverseBitsBorrowed<'a, INDEX: IndexDir> {
  dir: PhantomData<INDEX>,
  vec: DWordRef<'a>,
  ix:  usize
}

impl<'a, INDEX: IndexDir> Iterator for TraverseBitsBorrowed<'a, INDEX> {
  type Item = bool;
  fn next(&mut self) -> Option<Self::Item> {
    if self.ix >= self.vec.bits() {
      None
    } else {
      let i = self.ix;
      self.ix += 1;
      Some(self.vec.index::<INDEX>(i))
    }
  }
}



// -----------------------------------------------------------------------------


impl DWord {

  /// Iterate over the bits.
  pub fn into_iter_bits<INDEX: IndexDir>(self) -> TraverseBitsOwned<INDEX> {
    TraverseBitsOwned { dir: PhantomData, vec: self, ix: 0 }
  }

  /// Iterate over the bits, starting at the most significant end.
  pub fn into_iter_bits_msb(self) -> TraverseBitsOwned<FromMSB>
    { self.into_iter_bits() }

  /// Iterate over the bits, starting at the least significant end.
  pub fn into_iter_bits_lsb(self) -> TraverseBitsOwned<FromLSB>
    { self.into_iter_bits() }
}


/// Traverse DWord as bits, starting from most significant.
#[derive(Clone)]
pub struct TraverseBitsOwned<INDEX: IndexDir> {
  dir: PhantomData<INDEX>,
  vec: DWord,
  ix:  usize
}


impl<INDEX: IndexDir> Iterator for TraverseBitsOwned<INDEX> {
  type Item = bool;
  fn next(&mut self) -> Option<Self::Item> {
    if self.ix >= self.vec.bits() {
      None
    } else {
      let i = self.ix;
      self.ix += 1;
      Some(self.vec.as_ref().index::<INDEX>(i))
    }
  }
}
