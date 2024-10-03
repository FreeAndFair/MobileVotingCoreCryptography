##########################################################
# Threat Model Makefile, © 2025 Free & Fair              #
# Daniel M. Zimmerman, January 2025                      #
##########################################################
# Possible commands are: make [all|db|latex|pdf|clean

# Definitions

LATEXMK_CMD :=      latexmk --pdf
DB_DIR :=           ./db
DIAGRAMS_DIR :=			./diagrams
PARSE_CMD :=        ${DB_DIR}/parse.py
VIEW_CMD :=         ./view.py
GEN_LATEX_CMD :=    ${DB_DIR}/generate_latex_inputs.py
SERVER_CMD :=       ./server.py
PID_FILE :=         server.pid
BROWSER_CMD :=      open
SERVER_LOC :=       http://localhost:8911
DATABASE :=         ${DB_DIR}/db.sqlite3
THREAT_YAML :=      ${DB_DIR}/tm.yaml
THREAT_MODEL_DOC := threat-model

# Default target: show the help
all: help

# Display a brief help page listing possible targets.
help:
	@echo "Valid targets are:"
	@echo "make [all]    - build entire threat model including database and"
	@echo "                static document"
	@echo "make db       - build the threat model database file"
	@echo "make latex    - generate all LaTeX inputs"
	@echo "make pdf      - build the threat model PDF"
	@echo "make view     - run a smoketest of the command-line view of the model"
	@echo "make browser  - run the browser-based view of the threat model"
	@echo "make stop     - stop the running server supporting the browser-based view of the threat model"
	@echo ""
	@echo "make clean    - remove all generated database, LaTeX, and PDF files"
	@echo "make help     - display this help page"
	@echo ""
	@echo "This Makefile assumes the diagrams are up to date, as they are"
	@echo "included in the repository. To rebuild the diagrams after changes,"
	@echo "use the Makefile in ${DIAGRAMS_DIR}"
	@echo ""

# Build the database
${DATABASE}: ${THREAT_YAML}
	@echo "building the database"
	${PARSE_CMD} ${THREAT_YAML} ${DATABASE}

db: ${DATABASE}

# Build the LaTeX inputs
latex: ${DATABASE} ${GEN_LATEX_CMD}
	@echo "generating LaTeX inputs"
	${GEN_LATEX_CMD} --database ${DATABASE} --output ${DB_DIR}

# Build the PDF, including generating its dependencies
pdf: latex ${THREAT_MODEL_DOC}.tex references.bib
	@echo "generating threat model PDF"
	${LATEXMK_CMD} -halt-on-error -synctex=1 ${THREAT_MODEL_DOC}.tex

# Run a single smoketest of the command-line view of the model.
view: ${DATABASE}
	@echo "running an example view of the threat model"
	(cd ${DB_DIR}; ${VIEW_CMD} -e attack -r "Ballot tampering")

# Build the DB, run the threat model server, then open a browser window.
browser: ${DATABASE}
	@echo "running the threat model server for the browser-based viewer"
	bash -c "cd ${DB_DIR}; ${SERVER_CMD} & echo \$$! > ${PID_FILE};"
	${BROWSER_CMD} ${SERVER_LOC}

# Stop the threat model server.
stop:
	@echo "shutting down the threat model server"
	@if [ -f ${DB_DIR}/${PID_FILE} ]; then \
		kill `cat ${DB_DIR}/$(PID_FILE)` && rm -f ${DB_DIR}/$(PID_FILE); \
	else \
		echo "the server is not running (no PID file found)"; \
	fi

clean:
	rm -f ${DB_DIR}/*.tex ${DATABASE} threat_model.pdf
	${LATEXMK_CMD} -bibtex-cond1 -C ${THREAT_MODEL_DOC}.tex

PHONY: all help db latex pdf view browser stop clean
