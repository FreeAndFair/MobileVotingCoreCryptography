use crate::DWordRef;

impl DWordRef<'_> {
    /// Iterate over the limbs, starting with the least signficant one.
    pub fn iter_limbs_lsb<'b>(&'b self) -> std::slice::Iter<'b, u64> {
        self.as_slice().iter()
    }

    /// Iterate over the limbs, starting with the most signficant one.
    pub fn iter_limbs_msb<'b>(&'b self) -> std::iter::Rev<std::slice::Iter<'b, u64>> {
        self.as_slice().iter().rev()
    }
}
