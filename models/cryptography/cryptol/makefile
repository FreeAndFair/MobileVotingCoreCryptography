################################################################################
# Makefile to conveniently run Cryptol model verification and code generation  #
# @author Frank Zeyda (frank.zeyda@freeandfair.us)                             #
# @copyright Free & Fair 2025                                                  #
# @version 0.1                                                                 #
################################################################################

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
	$(error 'rust' target not yet supported [TODO])

# Cleans up all dynamically generated files, including caches.
clean:
	$(info [info] cleaning up all dynamically generated files&caches ...)
	rm -rf .cryproject

# List of phony targets
PHONY: default help all verify rust clean
