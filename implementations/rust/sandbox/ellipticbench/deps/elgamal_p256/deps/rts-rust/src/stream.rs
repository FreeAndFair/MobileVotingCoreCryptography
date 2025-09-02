use crate::type_traits::*;


#[macro_export]
#[allow(bad_style)]
macro_rules! stream {
  /* This variant is for a fixed window of history accessible via mentions
   * of the stream in the list comprehension arms optionally dropped with
   * statically known sizes. */
  ( forall  = [ $( $t:ident : $($life:lifetime)* [ $($trait:path),* ] ),* ]
  , element = $elT:ty
  , history = $history:literal
  , init    = $init:expr
  , capture = [ $( $field:ident : $type:ty = $field_value:expr),* ]
  , step    = |$self:ident| $next:expr
  ) => {
    {
      #[derive(Clone)]
      #[allow(non_snake_case)]
      struct S<$($t,)*>
        where
        $( $( $t : $trait ,)* )*
        $( $( $t : $life ,)* )*
      {
        index:    usize,
        history:  [ $elT; $history ],
        $( $field: $type, )*
        $( $t: std::marker::PhantomData::<$t>, )*
      }

      impl<$($t,)*>  S<$($t,)*>
        where
        $( $( $t : $trait ,)* )*
        $( $( $t : $life ,)* )*
      {
        fn get_history(&self, i: usize) -> $elT {
          self.history[ (self.index - i - 1) % $history ].clone()
        }
      }


      impl <$($t,)*> Iterator for S<$($t,)*>
        where
        $( $( $t : $trait ,)* )*
        $( $( $t : $life ,)* )*
      {
        type Item = $elT;
        fn next(&mut self) -> Option<Self::Item> {
          if self.index < $history {
            self.index += 1;
            Some(self.history[self.index-1].clone())
          } else {
            let $self = &mut (*self);
            let result: $elT = $next;
            self.history[self.index % $history] = result.clone();
            self.index += 1;
            Some(result)
          }
        }
      }

      impl<$($t,)*> $crate::type_traits::Stream<$elT> for S<$($t,)*>
        where
        $( $( $t : $trait ,)* )*
        $( $( $t : $life ,)* )*
      { }


      S { index: 0
        , history: $init.try_into().ok().unwrap()
        , $($field: $field_value,)*
        $( $t: std::marker::PhantomData, )*
        }
    }
  };

  /* This variant omits the static history size literal and tracks
   * a dynamic amount of history that can than be indexed into. */
  ( forall   = [ $( $t:ident : $($life:lifetime)* [ $($trait:path),* ] ),* ]
  , element  = $elT:ty
  , init     = $init:expr
  , capture  = [ $( $field:ident : $type:ty = $field_value:expr),* ]
  , step     = |$self:ident| $next:expr
  ) => {
    {
      #[derive(Clone)]
      #[allow(non_snake_case)]
      struct S<$($t,)*>
        where
        $( $( $t : $trait ,)* )*
        $( $( $t : $life ,)* )*
      {
        index:    usize,
        history:  Vec<$elT>,
        $( $field: $type, )*
        $( $t: std::marker::PhantomData::<$t>, )*
      }

      impl<$($t,)*>  S<$($t,)*>
        where
        $( $( $t : $trait ,)* )*
        $( $( $t : $life ,)* )*
      {
        fn get_history(&self, i: usize) -> $elT {
          assert!(i < self.index, "recursive drop dependency on uncomputed stream value");
          self.history[ (self.index - i - 1) ].clone()
        }
      }

      impl<$($t,)*>  S<$($t,)*>
        where
        $( $( $t : $trait ,)* )*
        $( $( $t : $life ,)* )*
      {
        fn index<I: $crate::traits::Integral>(&self, i: I::Arg<'_>) -> $elT {
          let i = <I as $crate::traits::Integral>::to_usize(i);
          assert!(i < self.history.len(), "recursive index dependency on uncomputed stream value");
          self.history[i].clone()
        }
      }

      impl <$($t,)*> Iterator for S<$($t,)*>
        where
        $( $( $t : $trait ,)* )*
        $( $( $t : $life ,)* )*
      {
        type Item = $elT;
        fn next(&mut self) -> Option<Self::Item> {
          if self.index < self.history.len() {
            self.index += 1;
            Some(self.history[self.index-1].clone())
          } else {
            let $self = &mut (*self);
            let result: $elT = $next;
            self.history.push(result.clone());
            self.index += 1;
            Some(result)
          }
        }
      }

      impl<$($t,)*> $crate::type_traits::Stream<$elT> for S<$($t,)*>
        where
        $( $( $t : $trait ,)* )*
        $( $( $t : $life ,)* )*
      { }

      S { index: 0
        , history: $init.to_vec()
        , $($field: $field_value,)*
        $( $t: std::marker::PhantomData, )*
        }
    }
  };

  /* This variant is used for non-recursively defined streams. */
  ( forall  = [ $( $t:ident : $($life:lifetime)* [ $($trait:path),* ] ),* ]
  , element = $elT:ty
  , capture = [ $( $field:ident : $type:ty = $field_value:expr),* ]
  , step    = |$self:ident| $next:expr
  ) => {
    {
      #[derive(Clone)]
      #[allow(non_snake_case)]
      struct S<$($t,)*>
        where
        $( $( $t : $trait ,)* )*
        $( $( $t : $life ,)* )*
      {
          $( $field: $type, )*
          $( $t: std::marker::PhantomData::<$t>, )*
      }

      impl <$($t,)*> Iterator for S<$($t,)*>
        where
        $( $( $t : $trait ,)* )*
        $( $( $t : $life ,)* )*
      {
        type Item = $elT;
        fn next(&mut self) -> Option<Self::Item> {
          let $self = &mut (*self);
          Some($next)
        }
      }

      impl<$($t,)*> $crate::type_traits::Stream<$elT> for S<$($t,)*>
        where
        $( $( $t : $trait ,)* )*
        $( $( $t : $life ,)* )*
      { }

      S { $($field: $field_value,)*
          $( $t: std::marker::PhantomData, )*
        }
    }
  };
}



/* -----------------------------------------------------------------------------
Repeat
----------------------------------------------------------------------------- */

impl<T: Type> Stream<T> for std::iter::Repeat<T> {}


/* -----------------------------------------------------------------------------
IntoIter
----------------------------------------------------------------------------- */

impl<T: Type> Stream<T> for std::vec::IntoIter<T> {}

/* -----------------------------------------------------------------------------
Chain
----------------------------------------------------------------------------- */
impl<T, I, J> Stream<T> for std::iter::Chain<I,J>
  where
    T: Type,
    I: Send + Sync + Clone + 'static + Iterator<Item=T>,
    J: Send + Sync + Clone + 'static + Iterator<Item=T>
    {}

/* -----------------------------------------------------------------------------
Once
----------------------------------------------------------------------------- */
impl<T> Stream<T> for std::iter::Once<T>
where
  T: Type,
  {}

/* -----------------------------------------------------------------------------
Map
----------------------------------------------------------------------------- */
impl<T, I, F> Stream<T> for std::iter::Map<I,F>
  where
  T: Type,
  I: Send + Sync + Clone + Iterator + 'static,
  F: Send + Sync + Clone + 'static + FnMut(<I as Iterator>::Item) -> T,
  {}

// -----------------------------------------------------------------------------
// Take
// -----------------------------------------------------------------------------

impl <T,I> Stream<T> for std::iter::Take<I>
  where T: Type, I: Send + Sync + Clone + 'static + Iterator<Item=T>
  {}

// -----------------------------------------------------------------------------
// Skip
// -----------------------------------------------------------------------------

impl <T,I> Stream<T> for std::iter::Skip<I>
  where T: Type, I: Send + Sync + Clone + 'static + Iterator<Item=T>
  {}

/* -----------------------------------------------------------------------------
Zip
----------------------------------------------------------------------------- */

impl<I,J> Stream<(<I as Iterator>::Item,<J as Iterator>::Item)>
  for std::iter::Zip<I,J>
  where
  <I as Iterator>::Item : Type,
  <J as Iterator>::Item : Type,
  I: Send + Sync + Clone + 'static + Iterator,
  J: Send + Sync + Clone + 'static + Iterator
  {}

/* -----------------------------------------------------------------------------
FlatMap
----------------------------------------------------------------------------- */


impl<I, U, F> Stream<<U as Iterator>::Item> for std::iter::FlatMap<I,U,F>
  where
  I: Send + Sync + Clone + Iterator + 'static,
  U: Send + Sync + Clone + Iterator + 'static,
  <U as Iterator>::Item: Type,
  F: Send + Sync + Clone + 'static + FnMut(<I as Iterator>::Item) -> U,
  {}

  impl<T, F> Stream<T> for std::iter::FromFn<F>
  where
  T: Type,
  F: Send + Sync + Clone + 'static + FnMut() -> Option<T>,
  {}

pub
fn cry_flat_map<A,B,F,I,J>(f: F, xs: I) -> impl Stream<B>
  where
  A: Type,
  B: Type,
  F: Fn(A) -> J,
  F: Send + Sync + Clone + 'static,
  I: Stream<A>,
  J: Stream<B>,
{
  xs.flat_map(move |v| { f(v) })
}

/* -----------------------------------------------------------------------------
Empty
----------------------------------------------------------------------------- */

// This impl is used for compiling primitives that return streams (see
// Note [Unimplemented primitives that return streams] in
// Cryptol.Compiler.Rust.CodeGen)
impl<T: Type> Stream<T> for std::iter::Empty<T> {}

/* -----------------------------------------------------------------------------
Scanl
----------------------------------------------------------------------------- */

pub fn cry_scanl<A, B, Bs>(f: crate::Fn2<crate::O<A>, crate::O<B>, A>, a: A, bs: Bs) -> impl Stream<A>
where
    A: Type,
    B: Type,
    Bs: Stream<B>,
{
    std::iter::once(a.clone()).chain(bs.scan(Some(a), move |st, b| {
        // Option wrapper is used so that the state variable can be temporarily empty
        *st = Some(f(st.take().unwrap(), b));
        Some(st.clone().unwrap())
    }))
}
