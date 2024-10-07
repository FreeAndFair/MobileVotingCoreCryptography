################################################################################
# Parses all lando models in this folder and translate them to JSON & markdown #
################################################################################
# Possible commands: make [all|clean]

# We use a wildcard to detect all lando input files.
LANDO_FILES := $(wildcard *.lando)

# Corresponding JSON file for each detected lando file
JSON_FILES := $(patsubst %.lando,%.json,$(LANDO_FILES))

# Corresponding markdown file for each detected lando file
MD_FILES := $(patsubst %.lando,%.md,$(LANDO_FILES))

# ANSI escape sequences for fancier terminal output
ANSI_RESET   := \033[0m
ANSI_BOLD    := \033[1m
ANSI_BLACK   := \033[0;30m
ANSI_RED     := \033[0;31m
ANSI_GREEN   := \033[0;32m
ANSI_YELLOW  := \033[0;33m
ANSI_BLUE    := \033[0;34m
ANSI_MAGENTA := \033[0;35m
ANSI_CYAN    := \033[0;36m
ANSI_WHITE   := \033[0;37m

# By default, generate a JSON file for each present lando file.
all: $(JSON_FILES) $(MD_FILES)

# Pattern rule to generate JSON files from lando sources.
%.json : %.lando
	@echo "Parsing $(ANSI_BOLD)$^$(ANSI_RESET) and generating $@ ..."
	lando convert $< $@ --to json

# Pattern rule to generate markdown files from lando sources.
%.md : %.lando
	@echo "Parsing $(ANSI_BOLD)$^$(ANSI_RESET) and generating $@ ..."
	lando convert $< $@ --to markdown

# Removes all dynamically generated JSON and markdown files.
clean:
	$(info Removing all dynamically generated files ...)
	rm -f $(JSON_FILES) $(MD_FILES)

.PHONY: all clean
