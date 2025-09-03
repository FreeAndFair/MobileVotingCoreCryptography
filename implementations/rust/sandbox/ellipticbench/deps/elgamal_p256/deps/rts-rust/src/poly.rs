/// Polynomial multiplication where the arguments both fit in native types.
/// Types that do not fit exactly in the representation occupy the
/// least significant part of the representation type, and the more
/// significant parts should be 0.
/// `[1 + u] -> [1 + v] -> [1 + u + v]`

#[macro_export]
macro_rules! pmult {
    ($ty: ty, $ue: expr, $ve: expr, $xe: expr, $ye: expr) => {{
        // On x86 this can be done with CLMUL;  on Arm PMUL
        let u = $ue;
        let v = $ve;
        assert!(u + v < (<$ty>::BITS as usize));
        let x = $xe as $ty;
        let y = $ye as $ty;
        let mut result = 0;
        for i in (0..1 + u).rev() {
            result <<= 1;
            if (x >> i) & 1 == 1 {
                result ^= y
            }
        }
        result
    }};
}

pub trait PMod<Rhs, Out> {
    fn pmod(self, y: Rhs, u: usize, v: usize) -> Out;
}

/// Reducing modulo a polynomial.
/// `[u] -> [1+v] -> [v]`
pub fn pmod<A, B, C>(u: usize, v: usize, x: A, y: B) -> C
where
    A: PMod<B, C>,
{
    x.pmod(y, u, v)
}

macro_rules! make_pmod {
    ($x: ty, $y: ty, $out: ty) => {
        impl PMod<$y, $out> for $x {
            fn pmod(self, m: $y, u: usize, v: usize) -> $out {
                assert!(u <= Self::BITS as usize);
                let v1 = v + 1;
                assert!(v1 <= <$y>::BITS as usize);

                let n = m.leading_zeros() as usize + v1 - <$y>::BITS as usize;
                assert!(n < v1, "division by 0");
                let degree = v - n; // lsb index of most signficant bit.

                let mut result = self as $out;
                if u > degree && v > degree {
                    result &= (1 << degree) - 1
                }

                let m1 = {
                    let tmp = m as $out;
                    if v < <$out>::BITS as usize {
                        tmp & ((1 << v) - 1)
                    } else {
                        tmp
                    }
                };

                let mut p = m1;
                if degree < v {
                    p &= !(1 << degree)
                }

                for i in degree..u {
                    // println!("i = {}, result = {}, p = {}", i, result, p);
                    if (self >> i) & 1 == 1 {
                        result ^= p
                    }
                    let carry = if degree == 0 {
                        false
                    } else {
                        p >> (degree - 1) & 1 == 1
                    };
                    p <<= 1;

                    if carry {
                        // print!("reducing {} ~>",p);
                        p ^= m1;
                        // println!("{}",p);
                    }
                }
                result
            }
        }
    };
}

make_pmod!(u64, u64, u64);
make_pmod!(u64, u128, u64);
make_pmod!(u64, u128, u128);

make_pmod!(u128, u64, u64);
make_pmod!(u128, u128, u64);
make_pmod!(u128, u128, u128);
