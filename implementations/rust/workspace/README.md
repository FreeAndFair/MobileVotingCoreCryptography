## Project workspace

This repository contains the Rust workspace for the project.

## Packages

The following packages are present:

- crypto

  Cryptographic building blocks necessary to implement the Mobile Voting Core Cryptography protocol.

## Building

* Note This crate requires the **nightly** Rust compiler. To install and use the nightly toolchain, run:

```bash
rustup default nightly
```

To build all packages in the workspace, navigate to the root of the repository and run:

```Bash
cargo build
```

To build a specific package, you can use:

```Bash
cargo build -p crypto
```

## Testing

To run tests for all packages:

```Bash
cargo test
```

To run tests for a specific package:

```Bash
cargo test -p crypto
```

## Linting

To run clippy for all packages:

```Bash
cargo clippy
```

To run clippy for a specific package:

```Bash
cargo clippy -p crypto
```

## Cleaning

```Bash
cargo clean
```
