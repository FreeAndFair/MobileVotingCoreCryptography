use crate::traits::*;
use crate::type_traits::*;

pub fn str_zero_inf<T: Zero> (n: T::Length) -> impl Stream<T> {
  std::iter::repeat(<T as Zero>::zero(n))
}

pub fn str_zero<T: Zero> (n: T::Length, sz: usize) -> impl Stream<T> {
  str_zero_inf(n).take(sz)
}

pub fn str_negate<T: Ring> (xs: impl Stream<T>) -> impl Stream<T> {
  xs.map(|x: T| <T as Ring>::negate(x.as_arg()))
}

pub fn str_mul<T: Ring>
  (xs: impl Stream<T>, ys: impl Stream<T>) -> impl Stream<T> {
  xs.zip(ys).map(|(x,y)| <T as Ring>::mul(x.as_arg(),y.as_arg()))
}

pub fn str_sub<T: Ring>
  (xs: impl Stream<T>, ys: impl Stream<T>) -> impl Stream<T> {
  xs.zip(ys).map(|(x,y)| <T as Ring>::sub(x.as_arg(),y.as_arg()))
}

pub fn str_add<T: Ring>
  (xs: impl Stream<T>, ys: impl Stream<T>) -> impl Stream<T> {
  xs.zip(ys).map(|(x,y)| <T as Ring>::add(x.as_arg(),y.as_arg()))
}

pub fn str_from_integer_inf<T: Ring>
  (n: T::Length, x: &num::BigInt) -> impl Stream<T> {
  std::iter::repeat(<T as Ring>::from_integer(n,x))
}

pub fn str_from_integer<T: Ring>
  (n: T::Length, sz: usize, x: &num::BigInt) -> impl Stream<T> {
  std::iter::repeat(<T as Ring>::from_integer(n,x)).take(sz)
}

pub fn str_exp<T: Ring, I: Integral>
  (xs: impl Stream<T>, y: I::Arg<'_>) -> impl Stream<T> {
  let y: I = y.clone_arg();
  xs.map(move |x| exp::<T, I>(x.as_arg(),y.as_arg()))
}

pub fn str_and<T: Logic>
  (xs: impl Stream<T>, ys: impl Stream<T>) -> impl Stream<T> {
  xs.zip(ys).map(|(x,y)| <T as Logic>::and(x.as_arg(),y.as_arg()))
}

pub fn str_or<T: Logic>
  (xs: impl Stream<T>, ys: impl Stream<T>) -> impl Stream<T> {
  xs.zip(ys).map(|(x,y)| <T as Logic>::or(x.as_arg(),y.as_arg()))
}


pub fn str_xor<T: Logic>
  (xs: impl Stream<T>, ys: impl Stream<T>) -> impl Stream<T> {
  xs.zip(ys).map(|(x,y)| <T as Logic>::xor(x.as_arg(),y.as_arg()))
}

pub fn str_complement<T: Logic>
  (xs: impl Stream<T>) -> impl Stream<T> {
  xs.map(|x| <T as Logic>::complement(x.as_arg()))
}


pub fn str_eq<T: Eq>
  (xs: impl Stream<T>, ys: impl Stream<T>) -> bool {
  xs.zip(ys).all(|(x,y)| <T as Eq>::eq(x.as_arg(), y.as_arg()))
}

pub fn str_ne<T: Eq>
  (xs: impl Stream<T>, ys: impl Stream<T>) -> bool {
  xs.zip(ys).any(|(x,y)| <T as Eq>::ne(x.as_arg(), y.as_arg()))
}

pub fn str_lt<T: Cmp>
  (xs: impl Stream<T>, ys: impl Stream<T>) -> bool {
  let mut zs =
      xs.zip(ys).skip_while(|(x,y)| <T as Eq>::eq(x.as_arg(), y.as_arg()));
  match zs.next() {
    None => false,
    Some ((x,y)) => <T as Cmp>::lt(x.as_arg(), y.as_arg())
  }
}

pub fn str_gt<T: Cmp>
  (xs: impl Stream<T>, ys: impl Stream<T>) -> bool {
  let mut zs =
      xs.zip(ys).skip_while(|(x,y)| <T as Eq>::eq(x.as_arg(), y.as_arg()));
  match zs.next() {
    None => false,
    Some ((x,y)) => <T as Cmp>::gt(x.as_arg(), y.as_arg())
  }
}

pub fn str_le<T: Cmp>
  (xs: impl Stream<T>, ys: impl Stream<T>) -> bool {
  let mut zs =
      xs.zip(ys).skip_while(|(x,y)| <T as Eq>::eq(x.as_arg(), y.as_arg()));
  match zs.next() {
    None => true,
    Some ((x,y)) => <T as Cmp>::lt(x.as_arg(), y.as_arg())
  }
}

pub fn str_ge<T: Cmp>
  (xs: impl Stream<T>, ys: impl Stream<T>) -> bool {
  let mut zs =
      xs.zip(ys).skip_while(|(x,y)| <T as Eq>::eq(x.as_arg(), y.as_arg()));
  match zs.next() {
    None => true,
    Some ((x,y)) => <T as Cmp>::gt(x.as_arg(), y.as_arg())
  }
}

pub fn str_signed_lt<T: SignedCmp>
  (xs: impl Stream<T>, ys: impl Stream<T>) -> bool {
  let mut zs =
      xs.zip(ys).skip_while(|(x,y)| <T as Eq>::eq(x.as_arg(), y.as_arg()));
  match zs.next() {
    None => false,
    Some ((x,y)) => <T as SignedCmp>::signed_lt(x.as_arg(), y.as_arg())
  }
}


pub fn dyn_str<T: Static>(x: impl Stream<T>) -> impl Stream<T::Dyn> {
  x.map(|a| T::dyn_b(a.as_arg()))
}

pub fn stat_str<T: Static>(x: impl Stream<T::Dyn>) -> impl Stream<T> {
  x.map(|a| T::stat_o(a))
}
