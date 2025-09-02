use crate::{DWordRef,DWord};
use std::fmt;


impl fmt::Binary for DWordRef<'_> {
  fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {

    let mut s = String::new();
    if self.bits() == 0 {
      s.push('0'); // special case so that we see something.
    } else {
      for b in self.iter_bits_msb() {
        s.push(if b { '1' } else { '0' })
      }
    }
    f.pad_integral(true, "0b", &s)
  }
}


impl fmt::Octal for DWordRef<'_> {
  fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {

    let mut s = String::new();
    let extra = self.bits() % 3;
    let table = ['0','1','2','3','4','5','6','7'];
    let mut emit = |x| s.push(table[ x as usize ]);

    match extra {
      1 => emit(u8::from(self.sub_word_msb(1,0).as_ref())),
      2 => emit(u8::from(self.sub_word_msb(2,0).as_ref())),
      _ => ()
    }

    for i in 0 .. self.bits() / 3 {
      emit(u8::from(self.sub_word_msb(3, extra + 3 * i).as_ref()))
    }

    f.pad_integral(true, "0o", &s)
  }
}


impl DWordRef<'_> {
  fn fmt_hex(&self, f: &mut fmt::Formatter, table: [char; 16]) -> fmt::Result {

    let mut s = String::new();
    if self.bits() == 0 { s.push('0') }

    let extra = self.bits() % 4;
    let mut emit = |x| s.push(table[ x as usize ]);

    match extra {
      1 => emit(u8::from(self.sub_word_msb(1,0).as_ref())),
      2 => emit(u8::from(self.sub_word_msb(2,0).as_ref())),
      3 => emit(u8::from(self.sub_word_msb(3,0).as_ref())),
      _ => ()
    }

    for i in 0 .. self.bits() / 4 {
      emit(u8::from(self.sub_word_msb(4, extra + 4 * i).as_ref()))
    }

    f.pad_integral(true, "0x", &s)

  }
}


impl fmt::UpperHex for DWordRef<'_> {
  fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
    self.fmt_hex(f, ['0','1','2','3','4','5','6','7','8','9'
                    ,'A','B','C','D','E','F'])
  }
}

impl fmt::LowerHex for DWordRef<'_> {
  fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
    self.fmt_hex(f, ['0','1','2','3','4','5','6','7','8','9'
                    ,'a','b','c','d','e','f'])
  }
}

impl fmt::Display for DWordRef<'_> {
  fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
    num::BigUint::from(*self).fmt(f)
  }
}

impl fmt::Debug for DWordRef<'_> {
  fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
    write!(f, "[{}|{:#x}]", self.bits(), self)
  }
}



impl fmt::Binary for DWord {
  fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result { self.as_ref().fmt(f) }
}

impl fmt::Octal for DWord {
  fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result { self.as_ref().fmt(f) }
}

impl fmt::LowerHex for DWord {
  fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result { self.as_ref().fmt(f) }
}

impl fmt::UpperHex for DWord {
  fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result { self.as_ref().fmt(f) }
}

impl fmt::Display for DWord {
  fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result { self.as_ref().fmt(f) }
}

impl fmt::Debug for DWord {
  fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result { self.as_ref().fmt(f) }
}
