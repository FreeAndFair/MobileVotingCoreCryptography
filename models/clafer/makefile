################################################################################
# Makefile to perform various actions and tasks on the E2EVIV Clafer PLE model #
################################################################################
# Possible targets: make [help|check|skin|instances|sysml|plantuml|clean]      #
################################################################################

# Basename of the Clafer model and verious derived files.
BASENAME = e2eviv

# Clafer file for the E2EVIV PLE model.
CLAFER_FILE  = $(BASENAME).cfr

# Skinned Clafer file for more rapid analysis.
SKINNED_FILE = $(BASENAME)_skinned.cfr

# Skinned Clafer file with optimization constraints.
SKINNED_OPT_FILE = $(BASENAME)_skinned_opt.cfr

# Produced PlantUML file for the E2EVIV PLE model.
PLANTUML_FILE = $(BASENAME).plantuml

# Produced PlantUML file for the E2EVIV PLE model.
SYSML_FILE = $(BASENAME).sysml

# Subfolder where all Chocosolver instances are written to.
INSTANCES_DIR = instances

# Subfolder where optimal Chocosolver instances are written to.
OPTIMAL_DIR = optimal

# Subfolder where generated SysML instances are written to.
SYSML_DIR = sysml

# Subfolder where the PlantUML diagram is written to.
PLANTUML_DIR = plantuml

# PlantUML configuration file for diagram generation.
PLANTUML_CONFIG = $(PLANTUML_DIR)/plantuml_config.toml

# The below is essential, otherwise we may get some weird results during DSE
# due to addition of GE PPAS values overflowing from positive into negative.
# Since we measure gate count in units of 100 GE, we expect the GE values to
# exceed 1000. Using 4095 (11 bits) gives a little room upwards, assuming that
# no admissible instance will have more than 400k GE.
CLAFER_IG_OPTS = --maxint=4095

# Utility variables for ANSI escape sequences (colors and fonts)
BOLD    := \033[1m
RESET   := \033[0m
BLACK   := \033[1;30m
RED     := \033[1;31m
GREEN   := \033[1;32m
YELLOW  := \033[1;33m
BLUE    := \033[1;34m
MAGENTA := \033[1;35m
CYAN    := \033[1;36m
WHITE   := \033[1;37m

# Target to display a help message on how to use the makefile.
help:
	@echo "Possible $(BOLD)make$(RESET) targets are:"
	@echo "make $(RED)help$(RESET) (default) - Displays this help message"
	@echo "make $(RED)check$(RESET)          - Parses $(CLAFER_FILE) model"
	@echo "make $(RED)skin$(RESET)           - Generates skinned model files:"
	@echo "                      $(SKINNED_FILE) and $(SKINNED_OPT_FILE)"
	@echo "                      (The latter includes optimization constraints.)"
	@echo "make $(RED)instances$(RESET)      - Generates $(BOLD)cumulative$(RESET) and $(BOLD)optimal$(RESET) instances"
	@echo "                      Deposited under the $(BLUE)$(INSTANCES_DIR)$(RESET) and $(BLUE)$(OPTIMAL_DIR)$(RESET) folders."
	@echo "make $(RED)sysml$(RESET)          - Generates SysML model of instances"
	@echo "                      Respective files are written to the $(BLUE)$(SYSML_DIR)$(RESET) folder."
	@echo "make $(RED)plantuml$(RESET)       - Generates PlantUML diagram of the Clafer model"
	@echo "                      Respective files are written to the $(BLUE)$(PLANTUML_DIR)$(RESET) folder."
	@echo "make $(RED)explore$(RESET)        - Starts claferIG shell to explore instances"
	@echo "                      This uses the skinned model for reasons of complexity."
	@echo "make $(RED)all$(RESET)            - Executes all relevant targets of the CI pipeline:"
	@echo "	              make $(BOLD)check instances sysml plantuml$(RESET)"
	@echo "make $(RED)clean$(RESET)          - Removes all dynamically created files"
	@echo "Note that $(BOLD)make explore$(RESET) currently does not work due to a JDK stack overflow."

# Executes all relevant targets of the CI pipeline.
all: check skin instances plantuml sysml
	@echo "All commands executed successfully! [$(GREEN)OK$(RESET)]"

# Parses the Clafer model, performing syntactic and type checking.
check:
	$(info Syntax and type-checking the $(CLAFER_FILE) Clafer model ...)
	clafer $(CLAFER_FILE)

# Generates skinned versions of the e2eviv.cfr Clafer model file.
# This also includes a skinned file with optimization constraints enabled.
skin:
	$(info Generating cumulative models $(SKINNED_FILE) and $(SKINNED_OPT_FILE) from $(CLAFER_FILE) ...)
	./scripts/skin_e2eviv.sh
	@echo

# Uses claferIG to create cumulative instances (under 'instances').
# Note that claferIG seems to be slow and running out of stack space ...
# -> Please use the chocosolver_instances target instead which works fine!
claferIG_instances: skin
	$(info Generating cumulative instances under the '$(INSTANCES_DIR)' directory ...)
	claferIG $(CLAFER_IG_OPTS) --savedir=$(INSTANCES_DIR) --addtypes --all $(SKINNED_FILE)

# Uses claferIG to create optimal instances (under 'optimal').
# Note that claferIG seems to be slow and running out of stack space ...
# -> Please use the chocosolver_instances target instead which works fine!
claferIG_optimal: skin
	$(info Generating optimal instances under the '$(OPTIMAL_DIR)' directory ...)
	claferIG $(CLAFER_IG_OPTS) --savedir=$(OPTIMAL_DIR) --addtypes --all $(SKINNED_OPT_FILE)

# Uses chocosolver to create cumulative instances (under 'instances').
chocosolver_instances: skin
	$(info Generating cumulative instances under the '$(INSTANCES_DIR)' directory ...)
	chocosolver $(CLAFER_IG_OPTS) --file=$(SKINNED_FILE) --output $(INSTANCES_DIR)/instances.txt

# Uses chocosolver to create optimal instances (under 'optimal').
chocosolver_optimal: skin
	$(info Generating optimal instances under the '$(OPTIMAL_DIR)' directory ...)
	chocosolver $(CLAFER_IG_OPTS) --file=$(SKINNED_OPT_FILE) --output $(OPTIMAL_DIR)/instances.txt

convert_to_json:
	$(info Converting Clafer instance specifications to JSON format)
	./scripts/choco_to_json.py -v --file=$(INSTANCES_DIR)/instances.txt $(INSTANCES_DIR)-json
	./scripts/choco_to_json.py -v --file=$(OPTIMAL_DIR)/instances.txt $(OPTIMAL_DIR)-json
	@echo

# Extracts individual e2eviv.<N>.inst files from instances.txt.
extract_instances:
	$(info Extracting instances from instance.txt files ...)
	./scripts/extract_instances.py $(INSTANCES_DIR)
	./scripts/extract_instances.py $(OPTIMAL_DIR)
	@echo

# Purges duplicate .inst files from the 'instances' and 'optimal' folders.
remove_duplicates:
	$(info Removing duplicate instances due to claferIG bug (?) ...)
	./scripts/remove_duplicates.py -v -e inst $(INSTANCES_DIR)
	./scripts/remove_duplicates.py -v -e json $(INSTANCES_DIR)-json
	./scripts/remove_duplicates.py -v -e inst $(OPTIMAL_DIR)
	./scripts/remove_duplicates.py -v -e json $(OPTIMAL_DIR)-json
	@echo

# By default, we use the Chocosolver for instance generation.
instances: chocosolver_instances chocosolver_optimal extract_instances convert_to_json remove_duplicates

# Creates a SysML diagram of the complete Clafer feature model.
# TODO @elew: This does not seem to work yet. Could you please debug?
sysml:
	$(info Creating a SysML model from the Clafer feature model ...)
	chocosolver --sysml \
            $(CLAFER_IG_OPTS) \
            --file $(CLAFER_FILE) \
            --output $(SYSML_DIR)/$(SYSML_FILE) \
            --plantuml-config $(PLANTUML_CONFIG)
	@echo

# Creates a PlantUML diagram of the complete Clafer feature model.
plantuml:
	$(info Creating a PlantUML diagram from the Clafer feature model ...)
	chocosolver --plantuml \
            $(CLAFER_IG_OPTS) \
            --file $(CLAFER_FILE) \
            --output $(PLANTUML_DIR)/$(PLANTUML_FILE) \
            --plantuml-config $(PLANTUML_CONFIG)
	plantuml plantuml/$(PLANTUML_FILE)
	@echo

# Starts the claferIG shell in order to explore instances.
# Due to complexity issues, we use the skinned model here.
# TODO elew: As noted in the help message, explore currently does not work due
# to a JDK stack overflow. Could you debug this and perhaps find a workaround?
explore: skin
	$(info Instance generation for $(SKINNED_FILE) ...)
	claferIG $(CLAFER_IG_OPTS) $(SKINNED_FILE)

# Removes all dynamically created files.
clean:
	rm -f *.als *.js
	rm -f $(SKINNED_FILE) $(SKINNED_OPT_FILE)
	rm -f $(INSTANCES_DIR)/{instances.txt,e2eviv.*.inst}
	rm -f $(INSTANCES_DIR)-json/{instances.json,e2eviv.*.json}
	rm -f $(OPTIMAL_DIR)/{instances.txt,e2eviv.*.inst}
	rm -f $(OPTIMAL_DIR)-json/{instances.json,e2eviv.*.json}
	rm -f $(SYSML_DIR)/$(SYSML_FILE)
	rm -f $(PLANTUML_DIR)/$(PLANTUML_FILE) $(PLANTUML_DIR)/$(BASENAME).png

# Permissible make commands are defined as phony targets.
.PHONY: help check skin instances sysml plantuml explore all clean
