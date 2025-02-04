################################################################################
# Makefile to conveniently run Cryptol model verification and code generation  #
# @author Frank Zeyda (frank.zeyda@freeandfair.us)                             #
# @copyright Free & Fair 2025                                                  #
# @version 0.1                                                                 #
################################################################################

# Directory to place generated Rust crates from Cryptol modules.
RUST_GEN_DIR = rust-gen

# Path to the cryptol-compiler executable.
# CRYPTOL_COMPILER ?= ../../../docker/cryptol-compiler/scripts/cryptol-compiler
CRYPTOL_COMPILER ?= cryptol-compiler

# General options passed to `cryptol-compiler`
CRYPTOL_COMPILER_OPTS = --suppress-warnings

# Print a horizontal line made of dashes
define hline
echo "--------------------------------------------------------------------------------"
endef

# Default target: help
default: help

# Display a brief help page listing possible commands/targets.
help:
	@echo "List of Possible make commands/targets:"
	@echo "make        - runs the default command (make help)"
	@echo "make all    - executes all commands (verify and rust)"
	@echo "make verify - syntax and type-checks all cryptol modules;"
	@echo "              also runs docstring commands where present,"
	@echo "              namely to carry out property verification"
	@echo "make rust   - generates Rust code for relevant modules"
	@echo "make test   - executes smoke tests for generated Rust code"
	@echo "make clean  - cleans up all dynamically generated files"
	@echo "make help   - displays this help page"

# Executes the verify and rust command in order.
all: verify rust

# Executes Cryptol verification tasks on all source files.
verify:
	$(info [info] performing syntax&type checking, and verification ...)
	cryptol --project "$(CURDIR)"

# Generates Rust code for all relevant Cryptol modules.
rust:
	$(info [info] generating Rust code for relevant modules ...)
	mkdir -p "$(RUST_GEN_DIR)"
	# Instance of Primitives::PRG_DDH
	$(CRYPTOL_COMPILER) --suppress-warnings -o "$(RUST_GEN_DIR)/prg_ddh" --crate=prg_ddh --entry-module=Primitives::PRG_DDH --driver Primitives/PRG_DDH_Main.cry
	@$(call hline)
	# Instances of Primitives::ElGamal::ElGamal
	$(CRYPTOL_COMPILER) $(CRYPTOL_COMPILER_OPTS) $(CRYPTOL_COMPILER_OPTS) -o "$(RUST_GEN_DIR)/elgamal_z41" --crate=elgamal_z41 --entry-module=Primitives::ElGamal::ElGamal --driver Primitives/ElGamal/Inst/ElGamal_Z41_Main.cry
	@$(call hline)
	$(CRYPTOL_COMPILER) $(CRYPTOL_COMPILER_OPTS) -o "$(RUST_GEN_DIR)/elgamal_s41" --crate=elgamal_s41 --entry-module=Primitives::ElGamal::ElGamal --driver Primitives/ElGamal/Inst/ElGamal_S41_Main.cry
	@$(call hline)
	$(CRYPTOL_COMPILER) $(CRYPTOL_COMPILER_OPTS) -o "$(RUST_GEN_DIR)/elgamal_s13" --crate=elgamal_s13 --entry-module=Primitives::ElGamal::ElGamal --driver Primitives/ElGamal/Inst/ElGamal_S13_Main.cry
	@$(call hline)
	$(CRYPTOL_COMPILER) $(CRYPTOL_COMPILER_OPTS) -o "$(RUST_GEN_DIR)/elgamal_p192" --crate=elgamal_p192 --entry-module=Primitives::ElGamal::ElGamal --driver Primitives/ElGamal/Inst/ElGamal_P192_Main.cry
	@$(call hline)
	$(CRYPTOL_COMPILER) $(CRYPTOL_COMPILER_OPTS) -o "$(RUST_GEN_DIR)/elgamal_p224" --crate=elgamal_p224 --entry-module=Primitives::ElGamal::ElGamal --driver Primitives/ElGamal/Inst/ElGamal_P224_Main.cry
	@$(call hline)
	$(CRYPTOL_COMPILER) $(CRYPTOL_COMPILER_OPTS) -o "$(RUST_GEN_DIR)/elgamal_p256" --crate=elgamal_p256 --entry-module=Primitives::ElGamal::ElGamal --driver Primitives/ElGamal/Inst/ElGamal_P256_Main.cry
	@$(call hline)
	$(CRYPTOL_COMPILER) $(CRYPTOL_COMPILER_OPTS) -o "$(RUST_GEN_DIR)/elgamal_p384" --crate=elgamal_p384 --entry-module=Primitives::ElGamal::ElGamal --driver Primitives/ElGamal/Inst/ElGamal_P384_Main.cry
	@$(call hline)
	$(CRYPTOL_COMPILER) $(CRYPTOL_COMPILER_OPTS) -o "$(RUST_GEN_DIR)/elgamal_p521" --crate=elgamal_p521 --entry-module=Primitives::ElGamal::ElGamal --driver Primitives/ElGamal/Inst/ElGamal_P521_Main.cry
	@$(call hline)
	# Instances of Primitives::ElGamal::ElGamalM (monadic version)
	$(CRYPTOL_COMPILER) $(CRYPTOL_COMPILER_OPTS) -o "$(RUST_GEN_DIR)/elgamalm_z41" --crate=elgamalm_z41 --entry-module=Primitives::ElGamal::ElGamalM --driver Primitives/ElGamal/Inst/ElGamalM_Z41_Main.cry # DOES NOT COMPILE
	@$(call hline)
	$(CRYPTOL_COMPILER) $(CRYPTOL_COMPILER_OPTS) -o "$(RUST_GEN_DIR)/elgamalm_s41" --crate=elgamalm_s41 --entry-module=Primitives::ElGamal::ElGamalM --driver Primitives/ElGamal/Inst/ElGamalM_S41_Main.cry # DOES NOT COMPILE
	@$(call hline)
	$(CRYPTOL_COMPILER) $(CRYPTOL_COMPILER_OPTS) -o "$(RUST_GEN_DIR)/elgamalm_s13" --crate=elgamalm_s13 --entry-module=Primitives::ElGamal::ElGamalM --driver Primitives/ElGamal/Inst/ElGamalM_S13_Main.cry # DOES NOT COMPILE
	@$(call hline)
	# Instances of Primitives::Pedersen::Pedersen
	$(CRYPTOL_COMPILER) $(CRYPTOL_COMPILER_OPTS) $(CRYPTOL_COMPILER_OPTS) -o "$(RUST_GEN_DIR)/pedersen_z41" --crate=pedersen_z41 --entry-module=Primitives::Pedersen::Pedersen --driver Primitives/Pedersen/Inst/Pedersen_Z41_Main.cry
	@$(call hline)
	$(CRYPTOL_COMPILER) $(CRYPTOL_COMPILER_OPTS) $(CRYPTOL_COMPILER_OPTS) -o "$(RUST_GEN_DIR)/pedersen_s41" --crate=pedersen_s41 --entry-module=Primitives::Pedersen::Pedersen --driver Primitives/Pedersen/Inst/Pedersen_S41_Main.cry
	@$(call hline)
	$(CRYPTOL_COMPILER) $(CRYPTOL_COMPILER_OPTS) $(CRYPTOL_COMPILER_OPTS) -o "$(RUST_GEN_DIR)/pedersen_s13" --crate=pedersen_s13 --entry-module=Primitives::Pedersen::Pedersen --driver Primitives/Pedersen/Inst/Pedersen_S13_Main.cry
	@$(call hline)
	$(CRYPTOL_COMPILER) $(CRYPTOL_COMPILER_OPTS) $(CRYPTOL_COMPILER_OPTS) -o "$(RUST_GEN_DIR)/pedersen_p192" --crate=pedersen_p192 --entry-module=Primitives::Pedersen::Pedersen --driver Primitives/Pedersen/Inst/Pedersen_P192_Main.cry
	@$(call hline)
	$(CRYPTOL_COMPILER) $(CRYPTOL_COMPILER_OPTS) $(CRYPTOL_COMPILER_OPTS) -o "$(RUST_GEN_DIR)/pedersen_p224" --crate=pedersen_p224 --entry-module=Primitives::Pedersen::Pedersen --driver Primitives/Pedersen/Inst/Pedersen_P224_Main.cry
	@$(call hline)
	$(CRYPTOL_COMPILER) $(CRYPTOL_COMPILER_OPTS) $(CRYPTOL_COMPILER_OPTS) -o "$(RUST_GEN_DIR)/pedersen_p256" --crate=pedersen_p256 --entry-module=Primitives::Pedersen::Pedersen --driver Primitives/Pedersen/Inst/Pedersen_P256_Main.cry
	@$(call hline)
	$(CRYPTOL_COMPILER) $(CRYPTOL_COMPILER_OPTS) $(CRYPTOL_COMPILER_OPTS) -o "$(RUST_GEN_DIR)/pedersen_p384" --crate=pedersen_p384 --entry-module=Primitives::Pedersen::Pedersen --driver Primitives/Pedersen/Inst/Pedersen_P384_Main.cry
	@$(call hline)
	$(CRYPTOL_COMPILER) $(CRYPTOL_COMPILER_OPTS) $(CRYPTOL_COMPILER_OPTS) -o "$(RUST_GEN_DIR)/pedersen_p521" --crate=pedersen_p521 --entry-module=Primitives::Pedersen::Pedersen --driver Primitives/Pedersen/Inst/Pedersen_P521_Main.cry

# Suppress Rust warnings during compilation of the test target.
export RUSTFLAGS = -A warnings

# Smoke-test Rust code for all relevant Cryptol modules.
test: # rust
	cd $(RUST_GEN_DIR)/prg_ddh && cargo build && cargo run
	@$(call hline)
	cd $(RUST_GEN_DIR)/elgamal_z41 && cargo build && cargo run
	@$(call hline)
	cd $(RUST_GEN_DIR)/elgamal_s41 && cargo build && cargo run
	@$(call hline)
	cd $(RUST_GEN_DIR)/elgamal_s13 && cargo build && cargo run
	@$(call hline)
	cd $(RUST_GEN_DIR)/elgamal_p192 && cargo build && cargo run
	@$(call hline)
	cd $(RUST_GEN_DIR)/elgamal_p224 && cargo build && cargo run
	@$(call hline)
	cd $(RUST_GEN_DIR)/elgamal_p256 && cargo build && cargo run
	@$(call hline)
	cd $(RUST_GEN_DIR)/elgamal_p384 && cargo build && cargo run
	@$(call hline)
	cd $(RUST_GEN_DIR)/elgamal_p521 && cargo build && cargo run
	@$(call hline)
	# cd $(RUST_GEN_DIR)/elgamalm_z41 && cargo build && cargo run
	@$(call hline)
	# cd $(RUST_GEN_DIR)/elgamalm_s41 && cargo build && cargo run
	@$(call hline)
	# cd $(RUST_GEN_DIR)/elgamalm_s13 && cargo build && cargo run
	@$(call hline)
	cd $(RUST_GEN_DIR)/pedersen_z41 && cargo build && cargo run
	@$(call hline)
	cd $(RUST_GEN_DIR)/pedersen_s41 && cargo build && cargo run
	@$(call hline)
	cd $(RUST_GEN_DIR)/pedersen_s13 && cargo build && cargo run
	@$(call hline)
	cd $(RUST_GEN_DIR)/pedersen_p192 && cargo build && cargo run
	@$(call hline)
	cd $(RUST_GEN_DIR)/pedersen_p224 && cargo build && cargo run
	@$(call hline)
	cd $(RUST_GEN_DIR)/pedersen_p256 && cargo build && cargo run
	@$(call hline)
	cd $(RUST_GEN_DIR)/pedersen_p384 && cargo build && cargo run
	@$(call hline)
	cd $(RUST_GEN_DIR)/pedersen_p521 && cargo build && cargo run

# Cleans up all dynamically generated files, including caches.
clean:
	$(info [info] cleaning up all dynamically generated files&caches ...)
	rm -rf "$(RUST_GEN_DIR)"

# List of phony targets
PHONY: default help all verify rust test clean
