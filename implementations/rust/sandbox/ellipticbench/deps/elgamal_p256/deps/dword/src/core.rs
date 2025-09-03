use std::marker::PhantomData;

pub type LimbT = u64;
pub type BigLimbT = u128;

/// The data for a dynamic word.
#[derive(Copy, Clone)]
union DWordData {
    small: LimbT,
    large: *mut LimbT,
}

/// The data for a dynamic word, together with the word size in bits.
#[derive(Copy, Clone)]
struct DWordPtr {
    bits: usize,
    data: DWordData,
}

/// A fixed-size word of a dynamic size.
/// * Words are represented as a little-endian sequence of `LimbT`,
///   meaning that the less significant bits are stored at lower indexes.
/// * Sequencs that fit in a single `LimbT` are passed by value, while
///   larger ones are boxed.
/// * Words of sizes that are not multiples of `LimbT` contain 0 padding
///   in the least sigificant part of the *first limb*, meaning that they
///   are stored in the most significant part of the smallest word that
///   is of a size that is a multiple of `LimbT`.
pub struct DWord {
    data: DWordPtr,
}

unsafe impl Sync for DWord {}
unsafe impl Send for DWord {}

/// A read-only reference to a [DWord].
/// This is similar to `&DWord`, but is passed by value, thus avoiding
/// an additional indirection.
#[derive(Copy, Clone)]
pub struct DWordRef<'a> {
    scope: PhantomData<&'a [LimbT]>,
    data: DWordPtr,
}

// -----------------------------------------------------------------------------
// Limbs & is_small

/// How many limbs we need to represent the given number of bits.
pub(crate) fn limbs_for_size(bits: usize) -> usize {
    (bits + DWord::LIMB_BITS - 1) / DWord::LIMB_BITS
}

/// Returns `true` if the limbs represent a negative two's complement integer.
pub(crate) fn is_signed(buf: &[LimbT]) -> bool {
    (buf[buf.len() - 1] >> (LimbT::BITS - 1)) == 1
}

/// Is this number of bits sufficiently small to fit in the small
/// representation.
pub(crate) fn is_small_size(bits: usize) -> bool {
    bits <= DWord::LIMB_BITS
}

/// How much padding we need in the least significant word.
/// The result is < DWord::LIMB_BITS.
pub(crate) fn padding_for_size(bits: usize) -> usize {
    DWord::LIMB_BITS * limbs_for_size(bits) - bits
}

impl DWordPtr {
    /// How many limbs we need to represent the given number of bits.
    /// When creating from a vector, this is how many entries should
    /// be in the vector.
    #[inline(always)]
    fn limbs(&self) -> usize {
        limbs_for_size(self.bits)
    }

    /// Are we using the single limb representation.
    #[inline(always)]
    fn is_small(&self) -> bool {
        is_small_size(self.bits)
    }
}

// -----------------------------------------------------------------------------
// Access to underlying representation.

impl DWordPtr {
    /// Read access to the underlying representation of the word.
    /// The resulting slice is always at least 1 limb.
    #[inline(always)]
    pub fn as_slice(&self) -> &[LimbT] {
        unsafe {
            if self.is_small() {
                std::slice::from_ref(&self.data.small)
            } else {
                std::slice::from_raw_parts(self.data.large, self.limbs())
            }
        }
    }

    /// Mutable access to the underlying representation of the word.
    /// The resulting slice is always at least 1 limb.
    #[inline(always)]
    pub fn as_slice_mut(&mut self) -> &mut [LimbT] {
        unsafe {
            if self.is_small() {
                std::slice::from_mut(&mut self.data.small)
            } else {
                std::slice::from_raw_parts_mut(self.data.large, self.limbs())
            }
        }
    }
}

impl DWord {
    /// Get a read reference to the word.
    #[inline(always)]
    pub fn as_ref(&self) -> DWordRef {
        DWordRef {
            scope: PhantomData,
            data: self.data,
        }
    }

    /// Read access to the underlying representation of the word.
    /// The resulting slice is always at least 1 limb.
    #[inline(always)]
    pub fn as_slice(&self) -> &[LimbT] {
        self.data.as_slice()
    }

    /// Get the least signficant limb of the implementation.
    #[inline(always)]
    pub fn limb0(&self) -> LimbT {
        self.as_ref().as_slice()[0]
    }

    /// Mutable access to the underlying representation of the word.
    /// The resulting slice is always at least 1 limb.
    #[inline(always)]
    pub fn as_slice_mut(&mut self) -> &mut [LimbT] {
        self.data.as_slice_mut()
    }
}

impl<'a> DWordRef<'a> {
    /// Read access to the underlying representation of the word.
    /// The resulting slice is always at least 1 limb.
    #[inline(always)]
    pub fn as_slice<'b: 'a>(&'b self) -> &'b [LimbT] {
        self.data.as_slice()
    }

    /// Get the least signficant limb of the implementation.
    #[inline(always)]
    pub fn limb0(self) -> LimbT {
        self.as_slice()[0]
    }

    /// Get the least signficant limb of the implementation,
    /// with the padding removed.
    #[inline(always)]
    pub fn limb0_norm(self) -> LimbT {
        self.as_slice()[0] >> self.padding()
    }
}

// -----------------------------------------------------------------------------
// Allocation, Cloning, Deallocation

impl DWordPtr {
    #[inline(always)]
    fn small_from_limb(bits: usize, data: LimbT) -> Self {
        assert!(is_small_size(bits));
        DWordPtr {
      bits: bits,
      data:
        // Preserve the invariant that 0-bit DWords always have `0` as their
        // `data` so that they're printed as `0x0`.
        DWordData { small: if bits > 0 { data } else { 0 } }
    }
    }

    fn large_from_limbs(bits: usize, data: Vec<LimbT>) -> Self {
        assert!(!is_small_size(bits));
        DWordPtr {
            bits: bits,
            data: DWordData {
                large: Box::<_>::into_raw(data.into_boxed_slice()).cast(),
            },
        }
    }

    fn from_limbs(bits: usize, data: Vec<LimbT>) -> Self {
        if is_small_size(bits) {
            Self::small_from_limb(bits, if bits == 0 { 0 } else { data[0] })
        } else {
            Self::large_from_limbs(bits, data)
        }
    }

    #[inline(always)]
    pub fn copy(self) -> Self {
        if is_small_size(self.bits()) {
            Self::small_from_limb(self.bits(), self.as_slice()[0])
        } else {
            Self::large_from_limbs(self.bits, Vec::from(self.as_slice()))
        }
    }

    #[inline(always)]
    fn free(self) {
        if self.is_small() {
            return;
        }
        unsafe {
            let s = std::ptr::slice_from_raw_parts_mut(self.data.large, self.limbs());
            drop(Box::<[LimbT]>::from_raw(s))
        }
    }
}

impl<'a> DWordRef<'a> {
    pub fn clone_word(self) -> DWord {
        DWord {
            data: self.data.copy(),
        }
    }
}

impl DWord {
    /// Create a 0 initialized word of the given size.
    pub fn zero(bits: usize) -> Self {
        if is_small_size(bits) {
            Self::small_from_limb(bits, 0)
        } else {
            Self::from_limbs(bits, vec![0; limbs_for_size(bits)])
        }
    }

    /// Create a [DWord] from the given limb.
    /// Assumes that `bits <= DWord::LIMB_BITS`.
    /// Does not add any padding to the limb.
    pub fn small_from_limb(bits: usize, data: LimbT) -> Self {
        DWord {
            data: DWordPtr::small_from_limb(bits, data),
        }
    }

    /// Create a [DWord] from the given limbs.
    /// The vector should contain the [correct number](Self::limbs)
    /// of limbs for the bits.
    /// Does not shift the limbs.
    pub fn from_limbs(bits: usize, data: Vec<LimbT>) -> Self {
        assert_eq!(data.len(), limbs_for_size(bits));
        DWord {
            data: DWordPtr::from_limbs(bits, data),
        }
    }
}

impl Clone for DWord {
    fn clone(&self) -> Self {
        self.as_ref().clone_word()
    }
}

impl Drop for DWord {
    fn drop(&mut self) {
        self.data.free()
    }
}

// -----------------------------------------------------------------------------

impl DWordPtr {
    /// The size of the word in bits.
    #[inline(always)]
    fn bits(&self) -> usize {
        self.bits
    }

    /// The number of 0s in the least significant position.
    #[inline(always)]
    fn padding(&self) -> usize {
        padding_for_size(self.bits())
    }

    /// The number of bits that are used in the least significant limb.
    /// This should not be used for 0-sized words.
    #[inline(always)]
    fn not_padding(&self) -> usize {
        assert!(self.bits() > 0);
        DWord::LIMB_BITS - self.padding()
    }
}

impl<'a> DWordRef<'a> {
    /// The size of the word in bits.
    #[inline(always)]
    pub fn bits(self) -> usize {
        self.data.bits()
    }

    /// Is this represented with a single limb.
    #[inline(always)]
    pub fn is_small(self) -> bool {
        self.data.is_small()
    }

    /// Returns `true` if the number is 0.
    pub fn is_zero(self) -> bool {
        for &w in self.as_slice() {
            if w != 0 {
                return false;
            }
        }
        return true;
    }

    /// The number of limbs in the representation of the word.
    /// Note that for 0 length bit vectors this returns 0,
    /// but [Self::as_slice] will still contain 1 element.
    #[inline(always)]
    pub fn limbs(self) -> usize {
        self.data.limbs()
    }

    /// The number of 0s in the least significant part of limb 0.
    #[inline(always)]
    pub fn padding(self) -> usize {
        self.data.padding()
    }

    /// The number of bits that are used in limb 0.
    /// This should not be used for 0-bit words.
    #[inline(always)]
    pub fn not_padding(self) -> usize {
        assert!(self.bits() > 0);
        self.data.not_padding()
    }
}

impl DWord {
    /// The number of bits in a libm.
    pub const LIMB_BITS: usize = LimbT::BITS as usize;
    pub const LIMB_BYTES: usize = DWord::LIMB_BITS / 8;

    /// The size of the word in bits.
    #[inline(always)]
    pub fn bits(&self) -> usize {
        self.data.bits()
    }

    /// Is this represented with a single limb.
    #[inline(always)]
    pub fn is_small(&self) -> bool {
        self.data.is_small()
    }

    /// The number of limbs in the representation of the word.
    /// Note that for 0 length bit vectors this returns 0,
    /// but [Self::as_slice] will still contain 1 element.
    #[inline(always)]
    pub fn limbs(&self) -> usize {
        self.data.limbs()
    }

    /// The number of 0s in the least significant part of limb 0.
    #[inline(always)]
    pub fn padding(&self) -> usize {
        self.data.padding()
    }

    /// The number of bits that are used in limb 0.
    #[inline(always)]
    pub fn not_padding(&self) -> usize {
        self.data.not_padding()
    }

    /// Clear up any bits in the least significant position of the full Uint.
    #[inline(always)]
    pub fn fix_underflow(&mut self) {
        let pad = self.padding();
        if pad == 0 {
            return;
        }
        let buf = self.as_slice_mut();
        buf[0] &= !((1 << pad) - 1);
    }

    /// Assign 0 to self
    pub fn assign_zero(&mut self) {
        for w in self.as_slice_mut() {
            *w = 0
        }
    }

    /// Assign all bits to max.
    pub fn assign_max(&mut self) {
        for w in self.as_slice_mut() {
            *w = LimbT::MAX
        }
        self.fix_underflow()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_padding() {
        assert_eq!(DWord::zero(0).padding(), 0);
        assert_eq!(DWord::zero(1).padding(), DWord::LIMB_BITS - 1);
        assert_eq!(DWord::zero(DWord::LIMB_BITS).padding(), 0);
    }
}
