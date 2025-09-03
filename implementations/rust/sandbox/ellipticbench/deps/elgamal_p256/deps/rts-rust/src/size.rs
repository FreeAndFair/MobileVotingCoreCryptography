use num::Zero;
use num::pow::Pow;

pub fn size_to_int(x: usize) -> num::BigUint {
    x.into()
}

pub fn int_to_size(x: &num::BigUint) -> usize {
    if x.is_zero() {
        return 0;
    }
    let ds = x.to_u64_digits();
    assert!(ds.len() < 2);
    ds[0] as usize
}

pub fn add_size(x: usize, y: usize) -> usize {
    x + y
}
pub fn sub_size(x: usize, y: usize) -> usize {
    x - y
}
pub fn mul_size(x: usize, y: usize) -> usize {
    x * y
}
pub fn div_size(x: usize, y: usize) -> usize {
    x / y
}
pub fn mod_size(x: usize, y: usize) -> usize {
    x % y
}
pub fn exp_size(x: usize, y: usize) -> usize {
    x.pow(y as u32)
}
pub fn min_size(x: usize, y: usize) -> usize {
    x.min(y)
}
pub fn max_size(x: usize, y: usize) -> usize {
    x.max(y)
}
pub fn ceil_div_size(x: usize, y: usize) -> usize {
    x.div_ceil(y)
}
pub fn ceil_mod_size(x: usize, y: usize) -> usize {
    let n = x % y;
    if n == 0 { 0 } else { y - n }
}
pub fn width_size(x: usize) -> usize {
    usize::BITS as usize - x.leading_zeros() as usize
}

pub fn from_then_to_size(x: usize, y: usize, z: usize) -> usize {
    if x < y {
        // ascending case
        if x > z {
            0
        } else {
            let step = y - x;
            let dist = z - x;
            dist / step + 1
        }
    } else if x > y {
        // descending case
        if x < z {
            0
        } else {
            let step = x - y;
            let dist = x - z;
            dist / step + 1
        }
    } else {
        panic!("from_then_to requires distinct `from` and `then`")
    }
}

// XXX: from_then_to_size

pub fn add_size_uint(x: &num::BigUint, y: &num::BigUint) -> num::BigUint {
    x + y
}

pub fn sub_size_uint(x: &num::BigUint, y: &num::BigUint) -> num::BigUint {
    x - y
}

pub fn mul_size_uint(x: &num::BigUint, y: &num::BigUint) -> num::BigUint {
    x * y
}

pub fn div_size_uint(x: &num::BigUint, y: &num::BigUint) -> num::BigUint {
    x / y
}

pub fn mod_size_uint(x: &num::BigUint, y: &num::BigUint) -> num::BigUint {
    x % y
}

pub fn exp_size_uint(x: &num::BigUint, y: usize) -> num::BigUint {
    <&num::BigUint as Pow<usize>>::pow(x, y)
}

pub fn min_size_uint(x: &num::BigUint, y: &num::BigUint) -> num::BigUint {
    x.min(y).clone()
}

pub fn max_size_uint(x: &num::BigUint, y: &num::BigUint) -> num::BigUint {
    x.max(y).clone()
}

pub fn ceil_div_size_uint(x: &num::BigUint, y: &num::BigUint) -> num::BigUint {
    (x + y - 1u64) / y
}

pub fn ceil_mod_size_uint(x: &num::BigUint, y: &num::BigUint) -> num::BigUint {
    let n = x % y;
    if n.is_zero() { n } else { y - n }
}

pub fn width_size_uint(x: &num::BigUint) -> usize {
    let digits = x.iter_u64_digits();
    let n = digits.len();
    match digits.last() {
        None => 0,
        Some(msb) => 64 * n - msb.leading_zeros() as usize,
    }
}

pub fn from_then_to_size_uint(
    x: &num::BigUint,
    y: &num::BigUint,
    z: &num::BigUint,
) -> num::BigUint {
    if x < y {
        // ascending case
        if x > z {
            num::BigUint::zero()
        } else {
            let step = y - x;
            let dist = z - x;
            dist / step + 1u64
        }
    } else if x > y {
        // descending case
        if x < z {
            num::BigUint::zero()
        } else {
            let step = x - y;
            let dist = x - z;
            dist / step + 1u64
        }
    } else {
        panic!("from_then_to requires distinct `from` and `then`")
    }
}

#[cfg(test)]
mod test {
    use num::FromPrimitive;
    use std::usize;

    use super::*;

    #[test]
    fn test_width_size() {
        assert_eq!(width_size(0), 0);
        assert_eq!(width_size(1), 1);
        assert_eq!(width_size(2), 2);
        assert_eq!(width_size(3), 2);
        assert_eq!(width_size(4), 3);
        assert_eq!(width_size(0x10), 5);
        assert_eq!(width_size(usize::MAX), usize::BITS as usize);
    }

    #[test]
    fn test_width_size_uint() {
        assert_eq!(width_size_uint(&num::BigUint::zero()), 0);
        assert_eq!(width_size_uint(&num::BigUint::from_u128(0x100).unwrap()), 9);
        assert_eq!(
            width_size_uint(&num::BigUint::from_u128(0x0000070000000000_0000000800000000).unwrap()),
            107
        );
    }

    #[test]
    fn test_from_then_to() {
        assert_eq!(from_then_to_size(1, 2, 3), 3); // [1,2,3]
        assert_eq!(from_then_to_size(1, 2, 2), 2); // [1,2]
        assert_eq!(from_then_to_size(1, 2, 1), 1); // [1]
        assert_eq!(from_then_to_size(1, 2, 0), 0); // []
        assert_eq!(from_then_to_size(3, 2, 0), 4); // []
        assert_eq!(from_then_to_size(3, 2, 3), 1); // [3]
        assert_eq!(from_then_to_size(3, 2, 2), 2); // [3,2]
        assert_eq!(from_then_to_size(3, 2, 1), 3); // [3,2,1]
        assert_eq!(from_then_to_size(1, 5, 15), 4); // [1, 5, 9, 13]
        assert_eq!(from_then_to_size(1, 5, 13), 4); // [1, 5, 9, 13]
        assert_eq!(from_then_to_size(1, 5, 12), 3); // [1, 5, 9]
    }
}
