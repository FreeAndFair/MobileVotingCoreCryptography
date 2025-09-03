use crate::*;

fn stream_update<T: Type>(xs: impl Stream<T>, i: usize, value: T::Arg<'_>) -> impl Stream<T> {
    #[derive(Clone)]
    struct StreamUpdate<S, T>
    where
        S: Stream<T>,
        T: Type,
    {
        orig_stream: S,
        update_idx: usize,
        update_value: T,
        current_idx: usize,
    }

    impl<S, T> Iterator for StreamUpdate<S, T>
    where
        S: Stream<T>,
        T: Type,
    {
        type Item = T;
        fn next(&mut self) -> Option<Self::Item> {
            let result = if self.current_idx == self.update_idx {
                self.orig_stream.next();
                Some(self.update_value.clone())
            } else {
                self.orig_stream.next()
            };
            self.current_idx += 1;
            result
        }
    }

    impl<S, T> Stream<T> for StreamUpdate<S, T>
    where
        S: Stream<T>,
        T: Type,
    {
    }

    StreamUpdate {
        orig_stream: xs,
        update_idx: i,
        update_value: value.clone_arg(),
        current_idx: 0,
    }
}

pub fn update_stream<T, I>(xs: impl Stream<T>, i: I::Arg<'_>, value: T::Arg<'_>) -> impl Stream<T>
where
    T: Type,
    I: Integral,
{
    stream_update(xs, front_index::<I>(i), value)
}

pub fn update_stream_back<T, I>(
    len: usize,
    xs: impl Stream<T>,
    i: I::Arg<'_>,
    value: T::Arg<'_>,
) -> impl Stream<T>
where
    T: Type,
    I: Integral,
{
    stream_update(xs, back_index::<I>(len, i), value)
}
