use crate::traits::*;
use crate::*;

/// All types supported by the compiler should implement this.
/// Types fully own all their children, so we should not have
/// any references in them, which is enforced by the `'static` constraint.
pub trait Type : Send + Sync + Clone + 'static {

  /// The type to use when passing Self values as arugments.
  /// While in many instances the arguments are going to be [`Copy`]
  /// we intentionally do not require it here to accommodate
  /// Streams/Iterators, which are typically not [`Copy`] but are
  /// still passed by value.
  type Arg<'a> : CloneArg<Owned=Self>;

  /// Extra information to pass for types that need dynamic information
  /// to create a value.
  ///
  /// This implements [`Clone`], but not [`Copy`]. While most [`Length`]
  /// implementations will implement [`Copy`] in practice, there are some
  /// notable exceptions to this rule (e.g., `Z`, whose [`Length`] is
  /// [`num::BigUint`]).
  type Length : Clone + Send + Sync;

  /// Turn a reference to an owned value into a function argument.
  fn as_arg(&self) -> Self::Arg<'_>;
}


pub trait CloneArg : Copy {
  type Owned;

  /// Turn an argument form into an owned value, possibly by cloning.
  fn clone_arg(self) -> Self::Owned;
}

/// All finite sequence representations should support these operations.
/// Note that this trait is only here for name overloading purposes
/// and to make it clear what operations we need.  Whenever we emit code
/// it is at a specific type.
/// This trait should be defined for the "Arg" (i.e., borrowed) versions
/// of the types.
pub trait Sequence : CloneArg {
  type Item : Type;

  /// Length of this sequence
  fn seq_length(self) -> usize;

  /// Shift a sequence to the right.
  /// New elements on the left will be filled using the `Zero` trait.
  ///   * `n`   - length, if the elements are seuqneces of dynamic size or ()
  ///   * `xs`  - sequence
  ///   * `amt` - how much to shift by
  fn seq_shift_right(self, n: <Self::Item as Type>::Length, amt: usize) -> Self::Owned
    where Self::Item : Zero;

  /// Shift a sequence to the right.
  /// New elements would be copies of most significant element.
  ///   * `xs`  - sequence
  ///   * `amt` - how much to shift by
  fn seq_shift_right_signed(self, amt: usize) -> Self::Owned;

  /// Rotate the elements of a sequence to right.
  ///   * `xs`  - sequence
  ///   * `amt` - how much to rotate by
  fn seq_rotate_right(self, amt: usize) -> Self::Owned;

  /// Shift a sequence to the left.
  /// New elements on the right will be filled using the `Zero` trait.
  ///   * `n`   - length, if the elements are seuqneces of dynamic size or ()
  ///   * `xs`  - sequence
  ///   * `amt` - how much to shift by
  fn seq_shift_left(self, n: <Self::Item as Type>::Length, amt: usize) -> Self::Owned
    where Self::Item : Zero;

  /// Rotate the elements of a sequence to left.
  ///   * `xs`  - sequence
  ///   * `amt` - how much to rotate by
  fn seq_rotate_left(self, amt: usize) -> Self::Owned;

  /// Get the element at a certain index, starting at the front,
  /// using `usize` as the index.
  /// Assert: `i < seq_length()`.
  fn seq_index(self, i: usize) -> Self::Item;

  /// Get the element at a certain index, starting at the front.
  /// Assert: `i < seq_length()`.
  fn seq_index_front<I:Integral>(self, i: I::Arg<'_>) -> Self::Item {
    self.seq_index(front_index::<I>(i))
  }

  /// Get the element at a certain index, starting from the back.
  /// Assert: `i < seq_length()`.
  fn seq_index_back<I:Integral>(self, i: I::Arg<'_>) -> Self::Item {
    self.seq_index(back_index::<I>(self.seq_length(),i))
  }
}

/// Note that this trait is only here for name overloading purposes
/// and to make it clear what operations we need.  Whenever we emit code
/// it is at a specific type.
/// This trait should be defined for the owned versions of the types.
pub trait SeqOwned: Type where
  for<'a> Self::Arg<'a>: Sequence
{
  type Item: Type;

  /// Reverse the elements of a sequence.
  fn seq_reverse(self) -> Self;

  /// Update an element in the sequence, starting at the front (MSB),
  /// using `usize` as the index.
  /// Assert: `i < seq_length()`.
  fn seq_update(self, i: usize, v: Self::Item) -> Self;

  /// Update an element at a certina index, starting from the front.
  /// Assert: `i < seq_length()`.
  fn seq_update_front<I:Integral>(self, i: I::Arg<'_>, v: Self::Item) -> Self {
    self.seq_update(front_index::<I>(i), v)
  }

  /// Update an element at a certina index, starting from the back.
  /// Assert: `i < length()`.
  fn seq_update_back<I:Integral>(self, i: I::Arg<'_>, v: Self::Item) -> Self {
    let n = self.as_arg().seq_length();
    self.seq_update(back_index::<I>(n, i), v)
  }
}


/// All word representaitons should support these operations.
pub trait Word : Sequence<Item=bool> {
}


pub trait ToVec<T> : Iterator<Item=T> {
  fn to_vec(self) -> Vec<T>;
}

impl<T, I: Iterator<Item=T>> ToVec<T> for I {
  fn to_vec(self) -> Vec<T> { self.collect() }
}

pub trait ByValue : for <'a> Type<Arg<'a> = Self> {}

// All stream representaitons should support these operations.
pub trait Stream<T:Type> : ToVec<T> + Clone + 'static + Sync + Send
{
}


/// This trait is for statically sized types that have a dynamically sized
/// representation when used in polymorphic functions.
/// For example, we have instace for `u8` where `Dyn` is `DWord`.
/// The `_o` and `_b` suffixes indicate if the argument is
/// "owned" or "borrowed".
/// The result is always owned.
pub trait Static: Type {
  type Dyn: Type;
  fn dyn_o(self) -> Self::Dyn;
  fn dyn_b(x: <Self as Type>::Arg<'_>) -> Self::Dyn;
  fn stat_o(x: Self::Dyn) -> Self;
  fn stat_b(x: <Self::Dyn as Type>::Arg<'_>) -> Self;
}

/// This trait is for things that may be turned into a signed integer.
/// Note that this should work on "arg" form of the type.
/// It should always be used at known types.
pub trait ToSignedInteger {
  fn to_signed_int(self) -> num::BigInt;
}
