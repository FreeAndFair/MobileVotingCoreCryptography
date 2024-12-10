#!/usr/bin/env python3
"""
Chocosolver Instance to JSON Converter

@authors: Ethan Lew <elew@galois.com> and
          Frank Zeyda <frank.zeyda@gmail.com>

Description:

This script parses the cumulative instance output of Chocosolver
(instances.txt file) and generates a corresponding instances.json
file as well as a set if separate e2eviv.<N>.json files, one
each instance.

Chocosolver is great for Clafer instance generation but it sadly
produces textual output only. The output, however, is still very
structured and can be parsed as an indentation language. As such,
we can devise a Parsing Expression Grammar (PEG) and generate a
parser that can be used to translate Chocosolver instances into a
suitable JSON format. (We use the Python Lark parsing toolkit for
that purpose.)

Prerequisites:
- Python 3 (3.12.4 or newer)
- Python Lark (1.1.9 or newer) (Install via "pip install lark".)

The script might work with older versions of the above but this
has not been tested.
"""
import sys, os, glob
import argparse, json

from lark import Lark
from lark import Transformer
from lark.exceptions import UnexpectedInput
from lark.indenter import Indenter

# Infer the name of the script.
SCRIPT_NAME = os.path.basename(sys.argv[0])

# The below can be set via the -v or --verbose CLI option.
VERBOSE_OUTPUT = False

# The below can be set via the -vv or --debug CLI option.
DEBUG_OUTPUT = False

##############
# ANSI Class #
##############

# ANSI escape sequences for fonts and colors
class ANSI:
  RESET   = "\033[0m"
  BOLD    = "\033[1m"
  BLACK   = "\033[1;30m"
  RED     = "\033[1;31m"
  GREEN   = "\033[1;32m"
  YELLOW  = "\033[1;33m"
  BLUE    = "\033[1;34m"
  MAGENTA = "\033[1;35m"
  CYAN    = "\033[1;36m"
  WHITE   = "\033[1;37m"

#####################
# Logging Functions #
#####################

# Like print() put writes to stderr by default.
def eprint(*args, **kwargs):
  print(*args, file=sys.stderr, **kwargs)

# Outputs a debugging message (written to stderr).
def debug(msg):
  if DEBUG_OUTPUT:
    eprint(f"[{ANSI.CYAN}debug{ANSI.RESET}] {msg.rstrip()}")

# Outputs an informative message (written to stdout).
def info(msg):
  if VERBOSE_OUTPUT:
    print(f"[{ANSI.BLUE}info{ANSI.RESET}] {msg.rstrip()}")

# Outputs an warning message (written to stderr).
def warning(msg):
  eprint(f"[{ANSI.YELLOW}info{ANSI.RESET}] {msg.rstrip()}")

# Outputs an error message (written to stderr).
# This function aborts the script with error code of 1.
def error(msg):
  eprint(f"[{ANSI.RED}error{ANSI.RESET}] {msg.rstrip()}")
  sys.exit(1)

################
# Lark Grammar #
################

# Lark grammar for parsing Chocosolver instances.
# Note that due to ignoring WS_INLINE tokens, the
# grammar is a bit more lenient in accepting indents
# e.g. before the Instance <N> Begin and End preambles.

INSTANCE_GRAMMAR = r"""
  start: _NL* (instance _NL*)+

  instance: instance_begin _NL* (node)+ _NL* instance_end

  ?instance_begin: "=== Instance " INT "Begin ==="
  ?instance_end:   "--- Instance " INT "End ---"

  node: clafer _NL [_INDENT (node)+ _DEDENT]

  %declare _INDENT _DEDENT

  clafer: NAME[index] [_EXTENDS NAME] [_REF TYPE _EQUALS VALUE]

  ?index: _DOLLAR INT

  VALUE: NAME | SIGNED_INT | STRING

  TYPE: "int" | "real" | "double" | "string" | NAME

  # Imported Rules
  %import common.CNAME -> NAME
  %import common.INT -> INT
  %import common.SIGNED_INT -> SIGNED_INT
  %import common.ESCAPED_STRING -> STRING
  %import common.WS_INLINE
  %ignore WS_INLINE

  # Newline+Indent and Symbols
  _NL: /\r?\n[\t ]*/
  _DOLLAR: /\$/
  _EXTENDS: ":"
  _REF: "->"
  _EQUALS: "="
"""

class NodeIndenter(Indenter):
  """Post-processing of AST for using indentation scope"""
  NL_type = '_NL'
  OPEN_PAREN_types = []
  CLOSE_PAREN_types = []
  INDENT_type = '_INDENT'
  DEDENT_type = '_DEDENT'
  tab_len = 8

#########################
# DictTransformer Class #
#########################

class DictTransformer(Transformer):
  """Transforms AST to a dict form that we can easily serialize"""
  def start(self, args):
    return args

  def instance(self, args):
    N = int(args[0])  # === Instance <N> Begin ===
    M = int(args[-1]) # --- Instance <M> End ---
    assert N == M, "inconsistent Instance <N> Begin and Instance <M> End"
    root_clafers = args[1:-1]
    return { 'instance': N, 'clafers': root_clafers, }

  def node(self, args):
    return args[0] | { 'children': args[1:] }

  def clafer(self, args):
    if args[3] == 'int' and args[4]:
      args[4].value = int(args[4].value)
    return {
      'name' : args[0].value,
      'index': int(args[1])  if args[1] else None,
      'super': args[2].value if args[2] else None,
      'type' : args[3].value if args[3] else None,
      'value': args[4].value if args[4] else None,
    }

######################
# Lark Parser Object #
######################

INSTANCE_PARSER = Lark(
  INSTANCE_GRAMMAR,
  parser = 'lalr',
  postlex = NodeIndenter(),
  transformer = DictTransformer())

########################
# Conversion Functions %
########################

# Parses chocosolver instances producing pair with a list of
# dictionaries (first element) and JSON text (second element).
def parse_instances(text, indent = 2):
  dicts = INSTANCE_PARSER.parse(text)
  json_text = json.dumps(dicts, indent = indent)
  return (dicts, json_text)

# Parses chocosolver instances producing a list of dictionaries.
def instances_to_dicts(text, indent = 2):
  return parse_instances(text, indent)[0]

# Parses chocosolver instances producing a JSON text encoding.
def instances_to_json(text, indent = 2):
  return parse_instances(text, indent)[1]

#####################
# RebuildTest Class #
#####################

# TODO: Write some explanation here of what this class is for.

class RebuildTest:
  @staticmethod
  def rebuild_clafer(clafer, indent = 0):
    print(" " * indent, end = '')
    print(clafer['name'], end = '')
    if clafer['index']: print("$" + str(clafer['index']), end = '')
    if clafer['super']: print(" : "  + clafer['super'], end = '')
    if clafer['type'] : print(" -> " + clafer['type'], end = '')
    if clafer['value']: print(" = "  + str(clafer['value']), end = '')
    print(' ') # chocosolver adds a space after each line
    for child in clafer['children']:
      RebuildTest.rebuild_clafer(child, indent + 2)

  @staticmethod
  def rebuild_instances(_list):
    for inst in _list:
      print(f"=== Instance {inst['instance']} Begin ===", end = "\n\n")
      for clafer in inst['clafers']:
        RebuildTest.rebuild_clafer(clafer)
      print()
      print(f"--- Instance {inst['instance']} End ---",   end = "\n\n")

  @staticmethod
  def run(filename):
    with open(filename, "r") as file:
      content = file.read()
    gen_json = instances_to_json(content)
    _dict = json.loads(gen_json)
    RebuildTest.rebuild_instances(_dict)

###################
# Argument Parser #
###################

ARG_PARSER = argparse.ArgumentParser(
  prog = SCRIPT_NAME,
  description = f"""Chocosolver to JSON Converter, 2024 (c) Galois Inc.

Parses an {ANSI.BOLD}instances.txt{ANSI.RESET} file created by \
chocosolver and converts
it into an {ANSI.BOLD}instances.json{ANSI.RESET} file that contains a JSON encoding of
all Clafer instance specifications. For each instance, a separate
e2eviv.<N>.json file is moreover produced.

Note that the script removes any exsting instances.json file and
all e2eviv.<N>.json files in the output directory first. If an
input file with a different name i.e. <BASENAME>.<EXT> is given,
the cumulative JSON output file will have the name <BASENAME>.json
instead of instances.json.""",
  epilog = f"Please contact {ANSI.BLUE}Ethan Lew{ANSI.RESET} (elew@galois.com) for support and/or maintenance.",
  formatter_class = argparse.RawTextHelpFormatter
)

ARG_PARSER.add_argument('output_dir', metavar = 'OUTPUT-DIR',
  help = f"""output directory for JSON files""")

ARG_PARSER.add_argument('-f', '--file', metavar = 'FILE',
  dest = 'input_file', default = 'instances.txt',
  help = f"""name of the chocosolver instances
input file (defaults to {ANSI.BOLD}instances.txt{ANSI.RESET})""")

ARG_PARSER.add_argument('-i', '--indent', metavar = 'TABSIZE', type=int,
  dest = 'indent', default = 4,
  help = f"""indentation width used in the jSON output
(defaults to 4)""")

ARG_PARSER.add_argument('-t', '--test', action = 'store_true',
  dest = 'testing',
  help = f"""runs the script in {ANSI.BOLD}testing mode{ANSI.RESET};
this produces a file <FILE>.rebuilt that
can be compared to the input file <FILE>
using diff. Both have to precisely match
for the roundtrip parsing test to succeed.
""")

ARG_PARSER.add_argument('-v', '--verbose', action = 'store_true',
  dest = 'verbose',
  help = f"""enable verbose (informative) messages""")

ARG_PARSER.add_argument('-vv', '--debug', action = 'store_true',
  dest = 'debug',
  help = f"""enable debugging message output""")

# Parses and validates CLI arguments and options.
# Sets global variables accordingly in order to
# make them available to the rest of the script.
def parse_args():
  global INPUT_FILE
  global OUTPUT_DIR
  global JSON_INDENT
  global TESTING
  global VERBOSE_OUTPUT
  global DEBUG_OUTPUT
  args = ARG_PARSER.parse_args()
  # Set INPUT_FILE global
  if os.path.isfile(args.input_file):
    INPUT_FILE = args.input_file
  else:
    error(f"input file '{args.input_file}' does not exist")
  # Set OUTPUT_DIR global
  if os.path.isdir(args.output_dir):
    OUTPUT_DIR = args.output_dir
  else:
    error(f"output directory '{args.output_dir}' does not exist")
  # Set JSON_INDENT global
  if args.indent > 0:
    JSON_INDENT = args.indent
  else:
    error(f"given indentation size must be greater than zero")
  # Set TESTING global
  TESTING = args.testing
  # Set VERBOSE_OUTPUT global
  VERBOSE_OUTPUT = args.verbose or args.debug
  # Set DEBUG_OUTPUT global
  DEBUG_OUTPUT = args.debug

def print_help():
  ARG_PARSER.print_help()

def print_usage():
  ARG_PARSER.print_usage()

###################
# Highlevel Tasks #
###################

############################################################
# TODO: Ethan Lew's original script took out the lines:
# - "Compiling the Clafer model..."
# - "Instantiating..."
# - "Optimizing..."
# - "instance(s) within the scope"
# Clarify with Ethan Lew if and why this is needed.
############################################################

# Remove relevant JSON files under OUTPUT_DIR.
def remove_json_files():
  global OUTPUT_DIR
  global JSON_INDENT
  INSTANCES_TXT = os.path.join(OUTPUT_DIR, 'instances.json')
  if os.path.isfile(INSTANCES_TXT):
    debug(f"removing file '{INSTANCES_TXT}'")
    os.remove(INSTANCES_TXT)
  E2EVIV_JSON_GLOB = os.path.join(OUTPUT_DIR, 'e2eviv.*.json')
  for filename in glob.glob(E2EVIV_JSON_GLOB):
    debug(f"removing file '{filename}'")
    os.remove(filename)

# Creates relevant JSON files under OUTPUT_DIR.
def create_json_files():
  global INPUT_FILE
  global OUTPUT_DIR
  global JSON_INDENT
  assert os.path.isfile(INPUT_FILE)
  with open(INPUT_FILE, "r") as file:
    content = file.read()
  # Create instances.json file
  try: (dicts, json_text) = parse_instances(content, indent=JSON_INDENT)
  except UnexpectedInput as err:
    error(f"error parsing '{INPUT_FILE}'{os.linesep}{err}")
  BASENAME = os.path.basename(INPUT_FILE)
  # Remove remove file extension from BASENAME if present.
  (stem, ext) = os.path.splitext(BASENAME)
  BASENAME = stem
  OUTPUT_FILE = os.path.join(OUTPUT_DIR, BASENAME + '.json')
  with open(OUTPUT_FILE, "w") as file:
    debug(f"writing file '{OUTPUT_FILE}'")
    file.write(json_text)
    info(f"{OUTPUT_FILE} created")
  for inst_dict in dicts:
    inst_num = inst_dict['instance']
    json_text = json.dumps(inst_dict, indent=JSON_INDENT)
    filename = os.path.join(OUTPUT_DIR, f"e2eviv.{inst_num}.json")
    with open(filename, "w") as file:
      debug(f"writing file '{filename}'")
      file.write(json_text)
  info(f"{len(dicts)} e2eviv.<N>.json JSON files created")

#################
# Main Behavior #
#################

# Main behavior of the script.
def main():
  global INPUT_FILE, TESTING
  parse_args()
  if TESTING:
    RebuildTest.run(INPUT_FILE)
  else:
    remove_json_files()
    create_json_files()

# Entry point of the script.
if __name__ == "__main__": main()
