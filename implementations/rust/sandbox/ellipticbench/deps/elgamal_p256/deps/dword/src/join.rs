use crate::{DWord,DWordRef};
use crate::core::{limbs_for_size,padding_for_size};

impl DWordRef<'_> {

  pub fn append(self, lower_bv: DWordRef<'_>) -> DWord {
    if self.bits() == 0 { return lower_bv.clone_word() }
    if lower_bv.bits() == 0 { return self.clone_word() }

    let upper     = self.as_slice();
    let upper_len = upper.len();
    let lower     = lower_bv.as_slice();
    let lower_len = lower.len();
    let pad_upper = self.padding();
    let pad_lower = lower_bv.padding();

    let mut result = DWord::zero(self.bits() + lower_bv.bits());
    let out_len    = result.limbs();
    let mid        = out_len - upper_len;

    let out        = result.as_slice_mut();

    // First we copy the upper word into the output.
    out[mid ..].copy_from_slice(upper);

    if pad_upper == 0 { out[0 .. lower_bv.limbs()].copy_from_slice(lower); }
    else {

      let have      = DWord::LIMB_BITS - pad_upper;
      let mut out_v = upper[0];
      for i in 0 .. lower_len {
        let w  = lower[lower_len - i - 1];
        out[mid - i] = out_v | (w >> have);
        out_v        = w << pad_upper;
      }
      if have > pad_lower { out[0] = out_v; }
    }

    result
  }
}

impl DWord {
  pub fn join(parts: usize, each: usize, xs: impl Iterator<Item = DWord>) ->
                                                                      DWord {
    let out_len = parts * each;
    let mut result = DWord::zero(out_len);

    if out_len == 0 { return result }

    let li              = result.limbs();
    let each_pad        = padding_for_size(each);
    let each_have_last  = DWord::LIMB_BITS - each_pad;
    let each_li         = limbs_for_size(each);

    let out       = result.as_slice_mut();

    if each_pad == 0 {

      // Copy full limbs
      for (i,bv) in xs.enumerate() {
        let end = li - i * each_li;
        out[ (end - each_li) .. end].copy_from_slice(bv.as_slice())
      }

    } else {

      let mut buf: u64       = 0;                  // partial word to output
      let mut have: usize    = 0;                  // meaningful bits in `buf`
      let mut out_ix: usize  = li;
      // 1 bigger than where we want write,
      // so that we don't wrap on last iteration.

      for bitvec in xs {

        let ws = bitvec.as_slice();

        if have == 0 {

          // We got aligned on a limb boundary, just copy.
          out[ (out_ix - each_li + 1) .. out_ix ].copy_from_slice(&ws[1..]);
          buf     = ws[0];
          have    = bitvec.not_padding();
          out_ix -= each_li - 1;
          // Note that we know that `have > 0`, because
          // we have already checked that `each_pad > 0`.


        } else {

          // Copy upper full words
          for j in (1 .. each_li).rev() {
            let w = ws[j];
            buf |= w >> have;
            out_ix -= 1;      // pre-decrement, as we are 1 bigger.
            out[out_ix] = buf;
            buf  = w << (DWord::LIMB_BITS - have);
          }

          // Last word is not full
          let w = ws[0];
          buf |= w >> have;
          have += each_have_last;

          if have >= DWord::LIMB_BITS {
            out_ix -= 1;
            out[out_ix] = buf;
            have -= DWord::LIMB_BITS;
            buf = w << (DWord::LIMB_BITS - have - each_pad);
          }
        }
      }

      // Do we have any leftovers
      if have > 0 { out[0] = buf; }
    }

    result
  }

}


#[cfg(test)]
mod test {
  use crate::DWord;
  use crate::proptest::*;

  #[test]
  fn append() {
    do_test2(two_words, |(x,y): (DWord,DWord)| {
      let (xr,a) = x.sem();
      let (yr,b) = y.sem();
      //let expect = (a << b.bits()) + b;
      let expect = (a << y.bits()) + b;
      assert_eq!( xr.append(yr)
                , DWord::from_uint(x.bits() + y.bits(), &expect));
      Some (true)
    })
  }

  fn join_uint(each: usize, xs: &Vec<DWord>) -> num::BigUint {
    let mut result = num::zero();
    for x in xs {
      result = (result<<each) + num::BigUint::from(x.as_ref())
    }
    result
  }

  #[test]
  fn join() {
    do_test(word_vec, |xs: Vec<DWord>| {
      let parts = xs.len();
      if parts == 0 {
        assert_eq!(DWord::join(17,0,xs.into_iter()), DWord::zero(0));
      } else {
        let each = xs[0].bits();
        let expected = join_uint(each, &xs);
        let actual = DWord::join(parts,each,xs.into_iter());
        assert_eq!(num::BigUint::from(actual.as_ref()), expected);
      }
      Some(true)
    })
  }


}
