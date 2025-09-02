# LibraryName development

Core cryptography library for the Tusk mobile voting project.

## ⚠️ Requirements

This crate requires the **nightly** Rust compiler. To install and use the nightly toolchain, run:
```bash
rustup default nightly
```

## Building Documentation

**1. Generate the Documentation**

Run the following Cargo command from the root of the project:

```bash
cargo doc --no-deps --document-private-items
```

**2. Open in Your Browser**

Once the command finishes, the main documentation page will be located at:

```code
target/doc/crypto/index.html
```

Open this file in your web browser to view the docs.

You can also run this command, which will automatically build the docs and open the main page in your default browser:

```bash
cargo doc --no-deps --document-private-items --open
```

### Running Tests

To run tests, use the following command:

```bash
cargo test
```

To run only doctests:

```bash
cargo test --doc
```

### Running clippy

```bash
cargo clippy
```

### Code coverage

Install cargo-llvm-cov:

```bash
cargo install cargo-llvm-cov
```

Run the analysis:

```bash
cargo llvm-cov
```

To run and open an html report:

```bash
cargo llvm-cov
cargo llvm-cov report --html --open
```

### Supply chain analysis (cargo deny)

Install cargo deny:

```bash
cargo install cargo-deny
```

Run the analysis:

```bash
cargo deny check
```

# Automatic code formatting

```bash
cargo fmt
```

### Show custom warnings

To display custom warnings when building (test or run),
pass in ```--features=custom-warnings```:

```bash
cargo build --features=custom-warnings
```

Custom warnings are implemented in ```macros/custom_warning_macro```.

### Implementation status

Tracked by <https://github.com/FreeAndFair/TuskMobileVoting/issues/274>
