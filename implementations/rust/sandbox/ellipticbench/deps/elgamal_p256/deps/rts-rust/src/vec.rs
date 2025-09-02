use std::cmp;
use std::fmt;
use crate::traits::*;
use crate::type_traits::*;
use crate::display::Base;
use crate::display::DefaultBase;

#[cfg(feature = "proptest_strategies")]
use proptest::collection::*;
#[cfg(feature = "proptest_strategies")]
use proptest::prelude::*;

#[cfg(test)]
use dword::DWord;

// Convenince for making vectors from a function.
pub trait FromFn<T> {
  fn from_fn<F>(n: usize, f: F) -> Self
    where F: FnMut(usize) -> T;
}

impl<T> FromFn<T> for Vec<T>{
  fn from_fn<F>(n: usize, mut f: F) -> Self
    where F: FnMut(usize) -> T
    { let mut i = 0;
      std::iter::from_fn(|| if i < n {
                              let j = i;
                              i += 1;
                              Some (f(j))
                            } else { None }
                       ).collect()
    }
}

/* Crytpol type */
impl<T: Type> Type for Vec<T> {
  type Length = (usize, T::Length);
  type Arg<'a> = &'a [T] where T: 'a;
  fn as_arg(&self) -> Self::Arg<'_> { &self[..] }
}

impl<T: Type> CloneArg for &[T] {
  type Owned = Vec<T>;
  fn clone_arg(self) -> Self::Owned {
    let mut result = Vec::with_capacity(self.len());
    result.extend_from_slice(self);
    result
  }
}


impl<T:Static> Static for Vec<T> {
  type Dyn = Vec<T::Dyn>;
  fn dyn_o(self) -> Self::Dyn {
    self.into_iter().map(|a| T::dyn_o(a)).collect()
  }
  fn dyn_b(x: <Self as Type>::Arg<'_>) -> Self::Dyn {
    x.into_iter().map(|a| T::dyn_b(a.as_arg())).collect()
  }
  fn stat_o(x: Self::Dyn) -> Self {
    x.into_iter().map(|a| T::stat_o(a)).collect()
  }
  fn stat_b(x: <Self::Dyn as Type>::Arg<'_>) -> Self {
    x.into_iter().map(|a| T::stat_b(a.as_arg())).collect()
  }
}

impl<T:Zero> Zero for Vec<T> {
  fn zero((vec_len,elem_len): Self::Length) -> Self {
    Self::from_fn(vec_len as usize,|_| T::zero(elem_len.clone()))
  }
}

/* Sequence operations */

impl<T: Type> Sequence for &[T] {
  type Item = T;

  fn seq_length(self) -> usize { self.len() }

  fn seq_index(self, i: usize) -> T { self[i].clone() }

  fn seq_shift_right(self, n: T::Length, amt: usize) -> Self::Owned
    where T : Zero
  {
    Vec::<T>::from_fn( self.seq_length()
                 , |i| if i < amt { T::zero(n.clone()) }
                                 else { self.seq_index(i-amt) })
  }


  fn seq_shift_right_signed(self, amt: usize) -> Self::Owned {
    Vec::<T>::from_fn( self.seq_length()
                 , |i| self.seq_index(if i < amt { 0 } else { i - amt }))
  }

  fn seq_rotate_right(self, amt: usize) -> Self::Owned {
    let n = self.seq_length();
    if n == 0 { return self.clone_arg() };
    let a = amt % n;
    Vec::<T>::from_fn(n, |i| self.seq_index((n.clone() + i - a) % n))
  }


  fn seq_shift_left(self, n: T::Length, amt: usize) -> Self::Owned
    where T : Zero
  {
    let vec_len = self.seq_length();
    Vec::<T>::from_fn(vec_len, |i| {
      let j = amt + i;
      if j >= vec_len { T::zero(n.clone()) } else { self.seq_index(j) } })
  }

  fn seq_rotate_left(self, amt: usize) -> Self::Owned {
    let n = self.seq_length();
    Vec::<T>::from_fn(n, |i| self.seq_index((amt + i) % n))
  }
}

impl<T: Type> SeqOwned for Vec<T> {
  type Item = T;

  fn seq_reverse(mut self) -> Self {
    self.reverse();
    self
  }

  fn seq_update(mut self, i_idx: usize, value: T) -> Vec<T> {
    self[i_idx] = value;
    self
  }
}


impl<const BASE: usize, const UPPER: bool, T: Base<BASE, UPPER>> Base<BASE, UPPER> for Vec<T> {
  fn format(&self, fmt: &mut fmt::Formatter) -> fmt::Result {
    Base::<BASE, UPPER>::format(&self.as_slice(),fmt)
  }
}

macro_rules! fmt_vec {
  ($f: expr, $x: expr, $fmt: expr) => {
    {
      write!($fmt,"[")?;
      let mut xs = $x.into_iter();
      match xs.next() {
        Some(fst) => $f(fst,$fmt)?,
        None      => { return write!($fmt,"]") }
      }

      for i in xs {
        write!($fmt,", ")?;
        $f(i,$fmt)?;
      }
      write!($fmt, "]")
    }
  }
}

impl<const BASE: usize, const UPPER: bool, T: Base<BASE, UPPER>> Base<BASE, UPPER> for &[T] {
  fn format(&self, fmt: &mut fmt::Formatter) -> fmt::Result
  {
    fmt_vec!(Base::<BASE,UPPER>::format, self, fmt)
  }
}

impl<T: DefaultBase> DefaultBase for &[T] {
  fn format(&self, fmt: &mut fmt::Formatter) -> fmt::Result
  {
    fmt_vec!(DefaultBase::format, self, fmt)
  }
}

impl<T: DefaultBase> DefaultBase for Vec<T> {
  fn format(&self, fmt: &mut fmt::Formatter) -> fmt::Result {
    DefaultBase::format(&self.as_slice(),fmt)
  }
}


impl<T: Logic> Logic for Vec<T> {
  fn complement(x: Self::Arg<'_>) -> Self {
    x.iter().map(|a| T::complement(a.as_arg())).collect()
  }
  fn xor(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
    x.iter().zip(y.iter()).map(|(a,b)| T::xor(a.as_arg(),b.as_arg())).collect()
  }
  fn and(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
    x.iter().zip(y.iter()).map(|(a,b)| T::and(a.as_arg(),b.as_arg())).collect()
  }
  fn or (x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
    x.iter().zip(y.iter()).map(|(a,b)| T::or(a.as_arg(),b.as_arg())).collect()
  }
}


impl<T: Ring> Ring for Vec<T> {

  fn negate(x: Self::Arg<'_>) -> Self {
    x.iter().map(|a| T::negate(a.as_arg())).collect()
  }

  fn mul(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
    x.iter().zip(y.iter()).map(|(a,b)| T::mul(a.as_arg(),b.as_arg())).collect()
  }

  fn sub(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
    x.iter().zip(y.iter()).map(|(a,b)| T::sub(a.as_arg(),b.as_arg())).collect()
  }

  fn add(x: Self::Arg<'_>, y: Self::Arg<'_>) -> Self {
    x.iter().zip(y.iter()).map(|(a,b)| T::add(a.as_arg(),b.as_arg())).collect()
  }

  fn from_integer(n: Self::Length, x: &num::BigInt) -> Self {
    let r = T::from_integer(n.1, x);
    Self::from_fn(n.0, |_i| r.clone())
  }

  fn exp_usize(x: Self::Arg<'_>, y: usize) -> Self {
    x.iter().map(|a| T::exp_usize(a.as_arg(), y)).collect()
  }

  fn exp_uint(x: Self::Arg<'_>, y: &num::BigUint) -> Self {
    x.iter().map(|a| T::exp_uint(a.as_arg(), y)).collect()
  }

}

impl<T: Eq> Eq for Vec<T> {
    fn eq(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
        if x.len() != y.len() {
            return false;
        }
        x.iter().zip(y.iter()).all(|(x, y)| T::eq(x.as_arg(), y.as_arg()))
    }
}

// Inspired by the SlicePartialOrd impl here:
// https://github.com/rust-lang/rust/blob/023084804e5e8ea42877451c2b3030e7050281cc/library/core/src/slice/cmp.rs#L103-L121
fn cmp_vec<T, E, L>(x: &[T], y: &[T], cmp_elems: E, cmp_lens: L) -> bool
where
    T : Cmp,
    E : FnOnce(T::Arg<'_>, T::Arg<'_>) -> bool,
    L : FnOnce(&usize, &usize) -> bool,
{
    let l = cmp::min(x.len(), y.len());

    let lhs = &x[..l];
    let rhs = &y[..l];

    for i in 0..l {
        if T::eq(lhs[i].as_arg(), rhs[i].as_arg()) {
            ()
        } else {
            return cmp_elems(lhs[i].as_arg(), rhs[i].as_arg())
        }
    }

    cmp_lens(&x.len(), &y.len())
}

impl<T: Cmp> Cmp for Vec<T> {
    fn lt(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
        cmp_vec(x, y, <T as Cmp>::lt, cmp::PartialOrd::lt)
    }

    fn gt(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
        cmp_vec(x, y, <T as Cmp>::gt, cmp::PartialOrd::gt)
    }

    fn le(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
        cmp_vec(x, y, <T as Cmp>::le, cmp::PartialOrd::le)
    }

    fn ge(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
        cmp_vec(x, y, <T as Cmp>::ge, cmp::PartialOrd::ge)
    }
}

impl<T: SignedCmp> SignedCmp for Vec<T> {
    fn signed_lt(x: Self::Arg<'_>, y: Self::Arg<'_>) -> bool {
        cmp_vec(x, y, <T as SignedCmp>::signed_lt, cmp::PartialOrd::lt)
    }
}

#[cfg(feature = "proptest_strategies")]
pub fn any_vec<T: fmt::Debug>(any_elem: impl Strategy<Value = T>, size: usize) -> impl Strategy<Value = Vec<T>> {
    // We only want to generate `Vec`s of length equal to the `size` argument,
    // so generate a range containing only the value `size`.
    vec(any_elem, size..=size)
}


#[cfg(test)]
mod tests {
  use super::*;

  #[test]
  fn test_basics() {
    const LEN: usize = 8;

    fn d8(x: u8) -> DWord {
        DWord::from_u8(LEN, x)
    }

    fn d8_vec(v: Vec<u8>) -> Vec<DWord> {
        v.iter().map(|&x| d8(x)).collect()
    }

    let x = d8_vec(vec![1,2,3]);
    assert_eq!(x.seq_length(), 3);
    assert_eq!(x.seq_index(2), d8(3));

    assert_eq!(x.seq_shift_left(LEN,1), d8_vec(vec![2,3,0]));
    assert_eq!(x.seq_shift_left(LEN,0), d8_vec(vec![1,2,3]));
    assert_eq!(x.seq_shift_left(LEN,10), d8_vec(vec![0,0,0]));

    assert_eq!(x.seq_shift_right(LEN,1), d8_vec(vec![0,1,2]));
    assert_eq!(x.seq_shift_right(LEN,0), d8_vec(vec![1,2,3]));
    assert_eq!(x.seq_shift_right(LEN,10), d8_vec(vec![0,0,0]));

    assert_eq!(x.seq_shift_right_signed(1), d8_vec(vec![1,1,2]));
    assert_eq!(x.seq_shift_right_signed(0), d8_vec(vec![1,2,3]));
    assert_eq!(x.seq_shift_right_signed(10), d8_vec(vec![1,1,1]));

    assert_eq!(x.seq_rotate_left(1), d8_vec(vec![2,3,1]));
    assert_eq!(x.seq_rotate_left(0), d8_vec(vec![1,2,3]));
    assert_eq!(x.seq_rotate_left(11), d8_vec(vec![3,1,2]));

    assert_eq!(x.seq_rotate_right(1), d8_vec(vec![3,1,2]));
    assert_eq!(x.seq_rotate_right(0), d8_vec(vec![1,2,3]));
    assert_eq!(x.seq_rotate_right(11), d8_vec(vec![2,3,1]));

  }
}
