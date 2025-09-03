use crate::DWord;

impl DWord {
    pub fn reverse(self) -> DWord {
        DWord::from_stream_msb(self.bits(), self.into_iter_bits_lsb())
    }
}
