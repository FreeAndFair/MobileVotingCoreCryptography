use std::marker::PhantomData;
use crate::{DWord,DWordRef};
use crate::index::{IndexDir,IndexFrom,FromMSB,FromLSB};

impl DWord {

  /// Split the words into sub-words of the given size.
  /// Generates only full words, so if the sub size does not divide the word
  /// exactly, the left over bits at the end will be ignored.
  pub fn into_iter_words<INDEX: IndexDir>
    (self, each: usize) -> TraverseWordsOwned<INDEX> {
      TraverseWordsOwned { dir: PhantomData, vec: self, index: 0, each: each }
  }

  /// Split the words into sub-words of the given size.
  /// Generates only full words, so if the sub size does not divide the word
  /// exactly, the left over bits at the end will be ignored.
  pub fn into_iter_words_msb(self, each: usize) -> TraverseWordsOwned<FromMSB>
    { self.into_iter_words(each) }

  /// Split the words into sub-words of the given size.
  /// Generates only full words, so if the sub size does not divide the word
  /// exactly, the left over bits at the end will be ignored.
  pub fn into_iter_words_lsb(self, each: usize) -> TraverseWordsOwned<FromLSB>
    { self.into_iter_words(each) }
}


impl<'a> DWordRef<'a> {

  /// Keep only the given number of bist from the MSB side
  pub fn take(self, amt: usize) -> DWord { self.sub_word_msb(amt, 0) }


  /// Skip the given number of most significatn bits.
  pub fn skip(self, amt: usize) -> DWord {
    self.sub_word_msb(self.bits() - amt, amt)
  }

  /// Split the words into sub-words of the given size.
  /// Generates only full words, so if the sub size does not divide the word
  /// exactly, the left over bits at the end will be ignored.
  pub fn iter_words<INDEX: IndexDir>
    (self, each: usize) -> TraverseWordsBorrowed<'a,INDEX> {
      TraverseWordsBorrowed {
        dir: PhantomData, vec: self, index: 0, each: each }
  }

  /// Split the words into sub-words of the given size.
  /// Generates only full words, so if the sub size does not divide the word
  /// exactly, the left over bits at the end will be ignored.
  pub fn iter_words_msb(self, each: usize) -> TraverseWordsBorrowed<'a,FromMSB>
    { self.iter_words(each) }

  /// Split the words into sub-words of the given size.
  /// Generates only full words, so if the sub size does not divide the word
  /// exactly, the left over bits at the end will be ignored.
  pub fn iter_words_lsb(self, each: usize) -> TraverseWordsBorrowed<'a,FromLSB>
    { self.iter_words(each) }

  pub fn sub_word_msb(self, sub_bits: usize, index: usize) -> DWord {
    self.sub_word::<FromMSB>(sub_bits,index)
  }

  pub fn sub_word_lsb(self, sub_bits: usize, index: usize) -> DWord {
    self.sub_word::<FromLSB>(sub_bits,index)
  }

  /// Extract a sub-word starting at the given bit offset.
  pub fn sub_word<INDEX: IndexDir>
    (self, sub_bits: usize, index: usize) -> DWord {
    assert!(index + sub_bits <= self.bits());

    // Make into MSB index
    let i = match INDEX::DIR {
              IndexFrom::Msb => index,
              IndexFrom::Lsb => self.bits() - sub_bits - index
            };

    let ws = self.as_slice();
    let mut result = DWord::zero(sub_bits);

    // Slice 0
    if sub_bits == 0 { return result }

    let out       = result.as_slice_mut();
    let res_limbs = out.len();

    let mut cur = ws.len() - i / DWord::LIMB_BITS; // 1 bigger than read
    let off     = i % DWord::LIMB_BITS;

    if off == 0 {
      // Slice aligned
      out.copy_from_slice(&ws[(cur - res_limbs) .. cur]);

    } else {
      // Slice unaligned

      cur           -= 1;
      let mut w      = ws[cur] << off;
      let have_bits  = DWord::LIMB_BITS - off;
      for j in 1 .. res_limbs {
        cur -= 1;
        let w1 = ws[cur];
        out[res_limbs - j] = w | (w1 >> have_bits);
        w = w1 << off;
      }

      if cur > 0 {
        w = w | (ws[cur - 1] >> have_bits)
      }
      out[0] = w;
    }

    result.fix_underflow();
    result
  }


}

#[derive(Clone)]
pub struct TraverseWordsOwned <INDEX: IndexDir> {
  dir:   PhantomData<INDEX>,
  vec:   DWord,
  index: usize,
  each:  usize
}

impl<INDEX: IndexDir> Iterator for TraverseWordsOwned <INDEX> {
  type Item = DWord;
  fn next(&mut self) -> Option<Self::Item> {
    let index = self.index;
    let each  = self.each;
    if index + each > self.vec.bits() { return None }
    self.index += each;
    Some(self.vec.as_ref().sub_word::<INDEX>(each, index))
  }
}


#[derive(Clone)]
pub struct TraverseWordsBorrowed<'a, INDEX: IndexDir> {
  dir:   PhantomData<INDEX>,
  vec:   DWordRef<'a>,
  index: usize,
  each:  usize
}

impl<'a, INDEX: IndexDir> Iterator for TraverseWordsBorrowed<'a, INDEX> {
  type Item = DWord;
  fn next(&mut self) -> Option<Self::Item> {
    let index = self.index;
    let each  = self.each;
    if index + each > self.vec.bits() { return None }
    self.index += each;
    Some(self.vec.sub_word::<INDEX>(each, index))
  }
}








#[cfg(test)]
mod test {
  use crate::{DWord,FromLSB,FromMSB,IndexDir,IndexFrom};
  use crate::proptest::*;

  fn sub_word<INDEX: IndexDir>() {
    do_test(word_and2::<usize,usize>, |(x,i0,w0): (DWord,usize,usize)|{
      let i      = i0 % (x.bits() + 1);
      let have   = x.bits() - i;
      let w      = w0 % (have + 1);
      let (xr,a) = x.sem();

      let lhs    = xr.sub_word::<INDEX>(w,i);
      let amt    = match INDEX::DIR {
                    IndexFrom::Msb => x.bits() - i - w,
                    IndexFrom::Lsb => i
                  };
      Some(lhs == DWord::from_uint(w, &(a >> amt)))
    })
  }

  #[test]
  fn sub_word_lsb() { sub_word::<FromLSB>() }
  #[test]
  fn sub_word_msb() { sub_word::<FromMSB>() }

}
