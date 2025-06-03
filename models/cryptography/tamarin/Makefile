#######################################################
# Makefile for Tamarin model generation and checking  #
# @author Daniel M. Zimmerman (dmz@@freeandfair.us)   #
# @copyright Free & Fair 2025                         #
# @version 0.1                                        #
#######################################################

# Tamarin command path. This is normally just `tamarin-prover`,
# but when run in CI, it is an invocation of a Docker container
# instead.
TAMARIN = tamarin-prover
DOCKER_IMAGE = freeandfair/cpv-e2eviv:latest
ifdef DOCKER
	TAMARIN = docker run --volume "$(PWD):/work" --workdir /work $(DOCKER_IMAGE) tamarin-prover
endif

# Display a brief help page listing possible commands/targets.
help:
	@echo "This Makefile supports the following targets:"
	@echo ""
	@echo "help (default) - display this help page"
	@echo "subprotocols   - generate the Tamarin models for all subprotocols"
	@echo "compositions   - generate Tamarin models for protocol compositions (*)"
	@echo "composed-all   - generate a Tamarin model composing all subprotocols"
	@echo "syntax         - check syntax of all generated models (**)"
	@echo "executability  - check executability of all generated models (**)"
	@echo "clean          - remove all generated models and outputs"
	@echo ""
	@echo "(*)  - see 'compositions/README.md' for more information about"
	@echo "       what is built by this build target"
	@echo "(**) - these build targets work only on the current set of"
	@echo "       generated models (in the 'generated' directory)"

# Display the help page as the default build target.
default: help

# Variables to help make find all the subprotocol sources.
SUBPROTOCOL_SOURCES = $(wildcard subprotocols/*.m4)
SUBPROTOCOL_SOURCES_NO_M4 = $(subst .spthy.m4,.spthy,$(SUBPROTOCOL_SOURCES))
SUBPROTOCOL_DESTS = $(subst subprotocols/,generated_standalone/,$(SUBPROTOCOL_SOURCES_NO_M4))

# Generate Tamarin models for all the subprotocols.
generated_standalone/%.spthy: subprotocols/%.spthy.m4
	$(info [info] generating standalone model for $<...)
	@mkdir -p generated_standalone
	@m4 -E -DSTANDALONE $< > $@

subprotocols: $(SUBPROTOCOL_DESTS)

# Variables to help make find all the composition sources.
COMPOSITION_SOURCES = $(wildcard compositions/*.m4)
COMPOSITION_SOURCES_NO_M4 = $(subst .spthy.m4,.spthy,$(COMPOSITION_SOURCES))
COMPOSITION_DESTS = $(subst compositions/,generated_composed/,$(COMPOSITION_SOURCES_NO_M4))

# Generate composed Tamarin models defined in 'compositions'.
generated_composed/%.spthy: compositions/%.spthy.m4
	$(info [info] generating model for composition $<...)
	@mkdir -p generated_composed
	@m4 -E $< > $@

compositions: $(COMPOSITION_DESTS)

# Execute Tamarin to check syntax of all generated models.
syntax:
	$(info [info] checking syntax of all generated models...)
	@$(foreach SPTHY, $(wildcard generated_standalone/*.spthy), \
		$(TAMARIN) --parse-only $(SPTHY) > /dev/null;)
	@$(foreach SPTHY, $(wildcard generated_composed/*.spthy), \
		$(TAMARIN) --parse-only $(SPTHY) > /dev/null;)

# Execute Tamarin to check executability of all generated models.
executability:
	$(info [info] checking executability of all generated models...)
	@mkdir -p output
	$(foreach SPTHY, $(wildcard generated_standalone/*.spthy), \
		$(TAMARIN) --prove="Executability*" --output-dot=output/$(basename $(notdir $(SPTHY)))-executability.dot $(SPTHY);)
	$(foreach SPTHY, $(wildcard generated_composed/*.spthy), \
		$(TAMARIN) --prove="Executability*" --output-dot=output/$(basename $(notdir $(SPTHY)))-executability.dot $(SPTHY);)

# Cleans up all dynamically generated files, including caches.
clean:
	$(info [info] removing all generated models and output...)
	@rm -rf generated_standalone generated_composed output

# Continuous integration/verification target.
ci: subprotocols compositions syntax

cv: subprotocols compositions executability

# List of phony targets
.PHONY: default help subprotocols compositions syntax executability clean ci cv
