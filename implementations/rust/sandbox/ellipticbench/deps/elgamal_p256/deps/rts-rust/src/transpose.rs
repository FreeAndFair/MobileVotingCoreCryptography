use crate::*;

/// `[x][y]a -> [y][x]a`
///
/// It is the responsibility of the caller to ensure that the length of `v` is
/// `x` and that the length of each `DWord` in `v` is `y`.
pub fn transpose_word(x: usize, y: usize, v: &[DWord]) -> Vec<DWord> {
    let mut result = Vec::with_capacity(y);
    for i in 0..y {
        struct S<'a> {
            // The original sequence of `DWord`s.
            v: &'a [DWord],
            // The bit to use in each `DWord` in `v`. Because we are computing the
            // transpose, this will stay the same on each iteration of `next`.
            i: usize,
            // The index of the `DWord` to use in `v`. Because we are computing the
            // transpose, this will be incremented on each iteration of `next.
            //
            // Invariant: `j` is always within the range `[0, x)`.
            j: usize,
        }
        impl<'a> Iterator for S<'a> {
            type Item = bool;
            fn next(&mut self) -> Option<bool> {
                let bit = self.v[self.j].as_ref().index_msb(self.i);
                self.j += 1;
                Some(bit)
            }
        }
        result.push(DWord::from_stream_msb(x, S { v: v, i: i, j: 0 }))
    }
    result
}

/// `[x][y]a -> [y][x]a`
///
/// It is the responsibility of the caller to ensure that the length of `v` is
/// `x` and that the length of each `Vec` in `v` is `y`.
pub fn transpose_vec<T: Type>(x: usize, y: usize, v: &[Vec<T>]) -> Vec<Vec<T>> {
    let mut result = Vec::with_capacity(y);
    for i in 0..y {
        let mut element = Vec::with_capacity(x);
        for j in 0..x {
            element.push(v[j][i].clone())
        }
        result.push(element)
    }
    result
}
