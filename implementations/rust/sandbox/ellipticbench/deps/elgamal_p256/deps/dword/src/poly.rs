use crate::{DWordRef,DWord};

impl DWordRef<'_> {

  // [1 + u] -> [1 + v] -> [1 + u + v]
  pub fn pmult(self, y: DWordRef<'_>) -> DWord {
    let xw = self.bits();
    assert!(xw > 0);
    let yw = y.bits();
    assert!(yw > 0);
    let zw = xw + yw - 1;

    let y1 = DWord::zero(xw - 1).as_ref().append(y);

    let mut result = DWord::zero(zw);
    for i in (0 .. xw).rev() {
      result <<= 1;
      if self.index_lsb(i) { result ^= y1.as_ref() }
    }
    result
  }


  // [u] -> [1+v] -> [v]
  pub fn pmod(self, m: DWordRef<'_>) -> DWord {

    let u  = self.bits();            // width of 1st argument
    let v1 = m.bits();
    assert!(v1 > 0);
    let v = v1 - 1;

    let n = m.leading_zeros();
    assert!(n < v1);                 // otherise, division by 0
    let degree = v1 - n - 1;         // lsb index of most signficant bit.

    let mut result =
      if u > degree { self.sub_word_lsb(degree, 0) } else { self.clone_word() };

    if result.bits() < v {
      result = DWord::zero(v - result.bits()).as_ref().append(result.as_ref())
    }


    let m1     = m.sub_word_lsb(v, 0);
    let mut p  = m1.as_ref().clone_word();
    if degree < v { p.set_bit_lsb(degree,false) }

    for i in degree .. u {
      //println!("i = {}, result = {}, p = {}", i, result, p);
      if self.index_lsb(i) { result ^= p.as_ref() }
      let carry = if degree == 0 { false }
                  else { p.as_ref().index_lsb(degree-1) };
      p <<= 1;

      if carry {
        // print!("reducing {} ~>",p);
        p ^= m1.as_ref();
        // println!("{}",p);
      }
    }
    result
  }
}

#[cfg(test)]
mod test {
  use super::*;

  #[test]
  fn test_pmod() {
    let mut x: DWord = 12345678_u32.into();
    let mut y: DWord = 123_u8.into();
    let mut z: DWord = DWord::from_u64(7, 0x14);
    assert_eq!(x.as_ref().pmod(y.as_ref()), z);

    let mut n = num::BigUint::parse_bytes(b"1092312983128903910831",10).unwrap();
    x = DWord::from_uint(129, &n);
    n = num::BigUint::parse_bytes(b"203947283734879",10).unwrap();
    y = DWord::from_uint(76, &n);
    n = num::BigUint::parse_bytes(b"0000000076c35d397a8",16).unwrap();
    z = DWord::from_uint(75, &n);
    assert_eq!(x.as_ref().pmod(y.as_ref()), z);

    n = num::BigUint::parse_bytes(b"f000000b97d2d66615f",16).unwrap();
    y = DWord::from_uint(76, &n);
    n = num::BigUint::parse_bytes(b"03b36e346d5619205af",16).unwrap();
    z = DWord::from_uint(75, &n);
    assert_eq!(x.as_ref().pmod(y.as_ref()), z);

    x = DWord::from_u64(52, 0xFFFFFFFFFFFFF);
    y = DWord::from_u64(8, 0xDA);
    z = DWord::from_u64(7, 0x11);
    assert_eq!(x.as_ref().pmod(y.as_ref()), z);
  }

  #[test]
   fn test_pmult() {
     let mut x: DWord = 12345678_u32.into();
     let mut y: DWord = 123_u8.into();
     let mut z: DWord = DWord::from_u64(39, 0x003775c702);
     assert_eq!(x.as_ref().pmult(y.as_ref()), z);

     let mut n = num::BigUint::parse_bytes(b"1092312983128903910831",10).unwrap();
     x = DWord::from_uint(129, &n);
     n = num::BigUint::parse_bytes(b"203947283734879",10).unwrap();
     y = DWord::from_uint(76, &n);

     n = num::BigUint::parse_bytes(
        b"00000000000000000000018a75237ea0f110117fb254ed68b05",16).unwrap();
     z = DWord::from_uint(204, &n);
     assert_eq!(x.as_ref().pmult(y.as_ref()), z);
   }


}
