:: $env:RUSTFLAGS='--cfg curve25519_dalek_backend="fiat"'
set RUSTFLAGS=--cfg curve25519_dalek_backend="simd"
cargo run --release
