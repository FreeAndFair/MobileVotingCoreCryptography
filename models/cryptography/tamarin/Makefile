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

# Docker image information (used if DOCKER is defined in the environment)
DOCKER_IMAGE = freeandfair/cpv-e2eviv:latest
ifdef DOCKER
	TAMARIN = docker run --volume "$(PWD):/work" --workdir /work $(DOCKER_IMAGE) tamarin-prover
endif

# M4 defines (to control proof script inclusion)
ifdef INCLUDE_PROOF_SCRIPTS
	M4_DEFINES = -DINCLUDE_PROOF_SCRIPTS
else
	M4_DEFINES =
endif

ifdef M4_DEBUG
	M4_DEBUG = --debug=V
else
	M4_DEBUG =
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
	@echo "executability  - check executability lemmas of all generated models (**)"
	@echo "safety         - check safety lemmas of all generated models (**)"
	@echo "proofscript    - check all lemmas with included proof scripts (**)"
	@echo "clean          - remove all generated models and outputs"
	@echo ""
	@echo "Define the 'INCLUDE_PROOF_SCRIPTS' environment variable to include"
	@echo "proof scripts in Tamarin output, where applicable."
	@echo
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
	@m4 -E -DSTANDALONE $(M4_DEBUG) $(M4_DEFINES) $(CV_DEFINES) $< > $@

subprotocols: $(SUBPROTOCOL_DESTS)

# Variables to help make find all the composition sources.
COMPOSITION_SOURCES = $(wildcard compositions/*.m4)
COMPOSITION_SOURCES_NO_M4 = $(subst .spthy.m4,.spthy,$(COMPOSITION_SOURCES))
COMPOSITION_DESTS = $(subst compositions/,generated_composed/,$(COMPOSITION_SOURCES_NO_M4))

# Generate composed Tamarin models defined in 'compositions'.
generated_composed/%.spthy: compositions/%.spthy.m4
	$(info [info] generating model for composition $<...)
	@mkdir -p generated_composed
	@m4 -E $(M4_DEFINES) $(CV_DEFINES) $< > $@

compositions: $(COMPOSITION_DESTS)

# Execute Tamarin to check syntax of all generated models.
syntax:
	$(info [info] checking syntax of all generated models...)
	@$(foreach SPTHY, $(wildcard generated_standalone/*.spthy generated_composed/*.spthy), \
		$(TAMARIN) --parse-only $(SPTHY) > /dev/null || exit 1;)

# Execute Tamarin to check executability of all generated models. This
# reports an error either if Tamarin fails, or if any lemma is falsified.
executability:
	$(info [info] checking executability of all generated models...)
	@mkdir -p output
	$(foreach SPTHY, $(wildcard generated_standalone/*.spthy generated_composed/*.spthy), \
		$(TAMARIN) --prove="Executability*" \
		--output-dot=output/$(basename $(notdir $(SPTHY)))-executability.dot > \
		output/$(basename $(notdir $(SPTHY)))-executability.out $(SPTHY) || exit 1;)
	@grep falsified output/*.out || echo "RESULT: no lemmas falsified"
	@ ! grep -q falsified output/*.out

# Execute Tamarin to check safety lemmas for all generated models. This
# reports an error either if Tamarin fails, or if any lemma is falsified.
safety:
	$(info [info] checking safety of all generated models...)
	@mkdir -p output
	$(foreach SPTHY, $(wildcard generated_standalone/*.spthy generated_composed/*.spthy), \
		$(TAMARIN) --prove="Safety*" \
		--output-dot=output/$(basename $(notdir $(SPTHY)))-safety.dot > \
		output/$(basename $(notdir $(SPTHY)))-safety.out $(SPTHY) || exit 1;)
	@grep falsified output/*.out || echo "RESULT: no lemmas falsified"
	@ ! grep -q falsified output/*.out

# Execute Tamarin to check the proof scripts for all lemmas that have
# them in all generated models. This reports an error if Tamarin fails,
# or if any lemma is not marked "verified".
proofscript:
	$(info [info] checking proof scripts of all generated models...)
	@mkdir -p output
	$(foreach SPTHY, $(wildcard generated_standalone/*.spthy generated_composed/*.spthy), \
		$(TAMARIN) > output/$(basename $(notdir $(SPTHY)))-proofscript.out \
		$(SPTHY) || exit 1;)
	@cat output/*-proofscript.out | grep ProofScript | grep -v NoProofScript | grep -v verified | grep -v lemma > output/combined-proofscript-results.out || echo "RESULT: all proof scripts verified"
	@cat output/combined-proofscript-results.out
	@! [ -s output/combined-proofscript-results.out ]

# Cleans up all dynamically generated files, including caches.
clean:
	$(info [info] removing all generated models and output...)
	@rm -rf generated_standalone generated_composed output

# Continuous integration/verification target.
ci: clean subprotocols compositions syntax

# Always include the proof scripts for CV
# To save execution time, we do everything at once here rather than running
# the individual executability, safety, and proofscript targets; this avoids
# doing the time-consuming Tamarin precomputations multiple times.
cv: CV_DEFINES = -DINCLUDE_PROOF_SCRIPTS
cv: clean subprotocols
	$(info [info] checking proof scripts, executability, and safety of all models...)
	@mkdir -p output
	$(foreach SPTHY, $(wildcard generated_standalone/*.spthy generated_composed/*.spthy), \
		time $(TAMARIN) --prove="Safety*" --prove="Executability*" \
		--output-dot=output/$(basename $(notdir $(SPTHY))).dot > \
		output/$(basename $(notdir $(SPTHY))).out \
		$(SPTHY) || exit 1;)
	@cat output/*.out | grep ProofScript | grep -v NoProofScript | grep -v verified | grep -v lemma > output/combined-proofscript-results.out || echo "RESULT: all proof scripts verified"
	@cat output/combined-proofscript-results.out
	@grep falsified output/*.out || echo "RESULT: no lemmas falsified"
	@! [ -s output/combined-proofscript-results.out ]
	@ ! grep -q falsified output/*.out

# List of phony targets
.PHONY: default help subprotocols compositions syntax executability safety proofscript clean ci cv
