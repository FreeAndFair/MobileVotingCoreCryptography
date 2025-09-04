###############################################
# Assurance Case Makefile, © 2025 Free & Fair #
# Daniel M. Zimmerman, May 2025               #
###############################################

# Definitions

DB_DIR :=           ../models/threat-model/db
SKELETON_DIR :=     ./advocate-project
PARSE_CMD :=        ${DB_DIR}/parse.py
GEN_SKELETON_CMD := PYTHONPATH="${PYTHONPATH}:${DB_DIR}" scripts/generate_advocate_skeleton.py
DATABASE :=         db.sqlite3
THREAT_YAML :=      ${DB_DIR}/tm.yaml

# Default target: show the help
all: help

# Display a brief help page listing possible targets.
help:
	@echo "Valid build targets are:"
	@echo "help (default)        - display this help page"
	@echo ""
	@echo "skeleton         - (re)generate the AdvoCATE assurance case skeleton"
	@echo "skeleton_implied - (re)generate the AdvoCATE assurance case skeleton,"
	@echo "                   including implied security objectives (e.g., an"
	@echo "                   attack against objective C3.1 is also treated as an"
	@echo "                   attack against properties C3, C3.1.1, C3.1.2)"
	@echo ""
	@echo "    Note that the skeleton targets overwrite any manual changes to the"
	@echo "    skeleton files, but leave other AdvoCATE project files untouched."
	@echo ""
	@echo "update           - update the non-argument parts of the assurance case"
	@echo "                   skeleton from the latest threat model"
	@echo "update_implied   - update the non-argument parts of the assurance case"
	@echo "                   skeleton from the latest threat model, including"
	@echo "                   implied security objectives"
	@echo ""
	@echo "    The update targets update all the skeleton files except the argument,"
	@echo "    but leave other AdvoCATE project files untouched."
	@echo ""
	@echo "clean            - remove the generated SQLite database"
	@echo ""

# Build the database if necessary
${DATABASE}: ${THREAT_YAML}
	@echo "building the database"
	${PARSE_CMD} ${THREAT_YAML} ${DATABASE}

# Build the AdvoCATE skeleton files
skeleton: ${DATABASE}
	@echo "generating AdvoCATE skeleton"
	mkdir -p ${SKELETON_DIR}
	${GEN_SKELETON_CMD} ${DATABASE} ${SKELETON_DIR}

# Build the AdvoCATE skeleton files with implied security objectives included
skeleton_implied: ${DATABASE}
	@echo "generating AdvoCATE skeleton with implied security objectives"
	mkdir -p ${SKELETON_DIR}
	${GEN_SKELETON_CMD} --implied ${DATABASE} ${SKELETON_DIR}

# Build the non-argument AdvoCATE skeleton files
update: ${DATABASE}
	@echo "updating static parts of AdvoCATE skeleton"
	mkdir -p ${SKELETON_DIR}
	${GEN_SKELETON_CMD} --no-argument ${DATABASE} ${SKELETON_DIR}

# Build the non-argument AdvoCATE skeleton files with implied security
# objectives included
update_implied: ${DATABASE}
	@echo "updating static parts of AdvoCATE skeleton with implied security objectives"
	mkdir -p ${SKELETON_DIR}
	${GEN_SKELETON_CMD} --no-argument --implied ${DATABASE} ${SKELETON_DIR}

ci: skeleton skeleton_implied update update_implied clean

clean:
	rm -f ${DATABASE}

PHONY: all help skeleton skeleton_implied update update_implied ci clean
