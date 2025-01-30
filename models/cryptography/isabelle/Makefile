################################################################################
# Makefile to build the E2EVIV Isabelle session heap and proof document (PDF)  #
################################################################################
# Possible commands are: make [help|install|session|show|clean]

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

# If no command (target) is given we display the help page.
default: help

# Display a brief help page listing possible commands/targets.
help:
	@echo "Possible $(BLUE)make$(RESET) commands are:"
	@echo "$(BOLD)make install$(RESET) - installs E2EVIV location into Isabelle ($(RED)run once$(RESET))"
	@echo "$(BOLD)make session$(RESET) - builds E2EVIV Isabelle heap and document"
	@echo "$(BOLD)make openznp$(RESET) - opens ZNP.thy theory in jedit with the HOL-Algebra heap"
	@echo "$(BOLD)make show$(RESET)    - displays the built proof document (PDF)"
	@echo "$(BOLD)make clean$(RESET)   - cleans up LaTeX files of the proof document"

# Installs E2EVIV location as an Isabelle component.
install:
	isabelle components -u "./E2EVIV"

# Builds E2EVIV Isabelle heap image and document.
session:
	isabelle build -c -D E2EVIV

# Opens the ZNP.thy theory with the HOL-Algebra heap.
openznp:
	isabelle jedit -l HOL-Algebra E2EVIV/theories/ZNP.thy

# Displays the E2EVIV proof document using evince.
show:
	open "./E2EVIV/output/document.pdf"

# Cleans E2EVIV Isabelle heap image and document.
clean:
	rm -rf "E2EVIV/output/document"

.PHONY: default help install session openznp show clean
