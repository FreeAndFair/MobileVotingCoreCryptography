use std::fmt;

pub trait Base<const BASE: usize, const UPPER: bool = true> {
  fn format(&self, fmt: &mut fmt::Formatter) -> fmt::Result;
}

/// This trait specifies the default way to display a value
/// (e.g., base 16 for bitvectors, base 10 for numbers)
/// It is linked to ['std::fmt::Debug'] via the ['Display'] trait.
/// An easy way to define this trait for base types is to
/// use the ['default_base'] macro.
pub trait DefaultBase {
  fn format(&self, fmt: &mut fmt::Formatter) -> fmt::Result;
}

pub struct Displayable<'a,T: ?Sized>(pub &'a T);

/// Used to display types using the Formatting trait above.
pub trait Display {
  fn display<'a>(&'a self) -> Displayable<'a,Self>;
}

impl<T> Display for T {
  fn display<'a>(&'a self) -> Displayable<'a,T> { Displayable(self) }
}

impl<'a, T: Base<10>> fmt::Display for Displayable<'a,T> {
  fn fmt(&self, fmt: &mut fmt::Formatter) -> fmt::Result {
   Base::<10>::format(self.0, fmt)
  }
}

impl<'a, T: Base<2>> fmt::Binary for Displayable<'a,T> {
  fn fmt(&self, fmt: &mut fmt::Formatter) -> fmt::Result {
    Base::<2>::format(self.0,fmt)
  }
}

impl<'a, T: Base<8>> fmt::Octal for Displayable<'a,T> {
  fn fmt(&self, fmt: &mut fmt::Formatter) -> fmt::Result {
    Base::<8>::format(self.0,fmt)
  }
}

impl<'a, T: Base<16>> fmt::UpperHex for Displayable<'a,T> {
  fn fmt(&self, fmt: &mut fmt::Formatter) -> fmt::Result {
    Base::<16>::format(self.0,fmt)
  }
}

impl<'a, T: Base<16, false>> fmt::LowerHex for Displayable<'a,T> {
  fn fmt(&self, fmt: &mut fmt::Formatter) -> fmt::Result {
    Base::<16, false>::format(self.0,fmt)
  }
}

impl<'a, T: DefaultBase> fmt::Debug for Displayable<'a,T> {
  fn fmt(&self, fmt: &mut fmt::Formatter) -> fmt::Result {
    DefaultBase::format(self.0,fmt)
  }
}


#[macro_export]
macro_rules! default_base {
  ($n:literal, $t:ty) =>  {
    impl $crate::display::DefaultBase for $t {
      fn format(&self, fmt: &mut std::fmt::Formatter) -> std::fmt::Result {
        $crate::display::Base::<$n,false>::format(self,fmt)
      }
    }
  }
}


#[macro_export]
macro_rules! derive_display {
  ($t:ty) =>  {

    impl<const UPPER:bool> $crate::display::Base<2, UPPER> for $t {
      fn format(&self, fmt: &mut std::fmt::Formatter) -> std::fmt::Result {
        <$t as std::fmt::Binary>::fmt(self, fmt)
      }
    }

    impl <const UPPER:bool> $crate::display::Base<8, UPPER> for $t {
      fn format(&self, fmt: &mut std::fmt::Formatter) -> std::fmt::Result {
        <$t as std::fmt::Octal>::fmt(self, fmt)
      }
    }

    impl <const UPPER:bool> $crate::display::Base<10, UPPER> for $t {
      fn format(&self, fmt: &mut std::fmt::Formatter) -> std::fmt::Result {
        <$t as std::fmt::Display>::fmt(self, fmt)
      }
    }

    impl $crate::display::Base<16, true> for $t {
      fn format(&self, fmt: &mut std::fmt::Formatter) -> std::fmt::Result {
        <$t as std::fmt::UpperHex>::fmt(self, fmt)
      }
    }

    impl $crate::display::Base<16, false> for $t {
      fn format(&self, fmt: &mut std::fmt::Formatter) -> std::fmt::Result {
        <$t as std::fmt::LowerHex>::fmt(self, fmt)
      }
    }
  };
}
