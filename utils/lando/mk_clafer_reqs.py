#! /usr/bin/env python
# Processes all E2EVIV .lando files in the current directory
# and produces a Clafer fragment that encodes all requirements
# found in those files, organized in groups (i.e., subclafers).
# The script takes no arguments, must be run in the same folder
# that contains all if the .lando requirements files, and, if
# successful, produces a 'requirements.cfr' file that contains
# the respective Clafer fragment. Note that the lando tool must
# be available/installed before this script can be run.
import sys, os, re, glob
import argparse, json

# Obtain the file name of this script.
SCRIPT_NAME = os.path.basename(__file__)

# Tab string used in the Clafer model fragment.
TAB_STR = ' ' * 4

# OS-independent newline string.
NEWLINE = os.linesep

##############
# ANSI Class #
##############

# Class providing definitions for ANSI escape sequences.
class ANSI:
  RESET   = "\033[0m"
  BOLD    = "\033[1m"
  BLACK   = "\033[0;30m"
  RED     = "\033[0;31m"
  GREEN   = "\033[0;32m"
  YELLOW  = "\033[0;33m"
  BLUE    = "\033[0;34m"
  MAGENTA = "\033[0;35m"
  CYAN    = "\033[0;36m"
  WHITE   = "\033[0;36m"

####################
# Output Functions #
####################

# Prints to stderr by default.
def eprint(*args, **kwargs):
  print(*args, file = sys.stderr, **kwargs)

# Prints a given debugging message.
def debug(msg):
  print(f"[{ANSI.CYAN}debug{ANSI.RESET}] " + msg)
  sys.stdout.flush()

# Prints a given informative message.
def info(msg):
  print(f"[{ANSI.BLUE}info{ANSI.RESET}] " + msg)
  sys.stdout.flush()

# Prints a given warning message.
def warning(msg):
  eprint(f"[{ANSI.YELLOW}warn{ANSI.RESET}] " + msg)

# Prints a given error message and aborts the script.
def error(msg):
  eprint(f"[{ANSI.RED}error{ANSI.RESET}] " + msg)
  eprint("-> Aborting script ...")
  exit(1)

####################
# Global Constants #
####################

# Lando class names for requirements elements.
REQUIREMENTS_TYPES =  [
  "com.galois.besspin.lando.ssl.ast.RawRequirements"
]

# Group prefixes for the E2EVIV requirements.
# TODO: This may need to be extended as requirements evolve.
REQS_GROUP_PREFIX = {
  'Accessibility Requirements': 'AC',
  'Assurance Requirements': 'AS',
  'Auditing Requirements': 'AUD',
  'Auditing Requirements Verification': 'AUDV',
  'Authentication Requirements': 'AUTH',
  'Certification Functional Requirements': 'CF',
  'Certification Non Functional Requirements': 'CNF',
  'Evolvability Requirements': 'E',
  'Functional Requirements': 'F',
  'Interoperability Requirements': 'I',
  'Legal Requirements': 'L',
  'Maintenance Requirements': 'M',
  'Operational Requirements': 'O',
  'Procedural Requirements': 'P',
  'Reliability Requirements': 'R',
  'Security Requirements': 'S',
  'E2EVIV Security Requirements': 'ES',
  'Privacy Requirements': 'PRI',
  'Certification and Recertification Requirements': 'CR',
  'System Operational Requirements': 'SOP',
  'Usability Requirements': 'U',
}

# Abstract Requirement clafer and Requirements header fragment.
CLAFER_HEADER = f'''
// Each requirement feature has a label, name, and description.
// Shall we include a reference for traceability to specs?
abstract Requirement
{TAB_STR}label -> string
{TAB_STR}name -> string
{TAB_STR}description -> string
{TAB_STR}// ref -> string

// Requirements are organized into groups (subclafers), reflecting
// the precise structure of the Lando Domain Engineering (DE) model.
Requirements
'''.lstrip()

##################
# Fragment Class #
##################

# Utility class to build the Clafer fragment by the script.
class Fragment:
  # Fragment string to be built.
  _CLAFER_FRAGMENT = ""

  @staticmethod
  def init(text):
    Fragment._CLAFER_FRAGMENT = text

  @staticmethod
  def append(text, tabs = 0, end = NEWLINE):
    Fragment._CLAFER_FRAGMENT += (TAB_STR * tabs) + text + end

  @staticmethod
  def write(filename):
    info(f"writing Clafer fragment to {ANSI.RED}{filename}{ANSI.RESET}")
    with open(filename, "w") as file:
      file.write(Fragment._CLAFER_FRAGMENT)

  @staticmethod
  def print():
    print(Fragment._CLAFER_FRAGMENT)

#######################
# Auxiliary Functions #
#######################

# Scans the current directory for .lando files and (re)creates the
# respective .json files using the lando tool (must be installed).
def recreate_json_files():
  for filename in sorted(glob.glob('*.lando')):
    info(f"(re)creating json file for {ANSI.BOLD}{filename}{ANSI.RESET} ... ")
    json_name = re.sub(r'\.lando$', '.json', filename)
    LANDO_CMD = f"lando convert --to json '{filename}' '{json_name}'"
    retval = os.system(LANDO_CMD)
    if retval != 0:
      error(f"failed to create json file for '{filename}'. " +
            f"Please review model wrt to syntax and type errors.")
    assert(os.path.isfile(json_name)) # the JSON file ought to exist now

# Creates the Clafer fragment for all requirements in Lando files.
# Note that we assume a .json file is present for each .lando file.
def build_clafer_fragment():
  Fragment.init(CLAFER_HEADER)
  for filename in sorted(glob.glob('*.json')):
    create_reqs_fragment(filename)

# Adds Requirement subclafers for a given Lando JSON file.
def create_reqs_fragment(filename):
  info(f"processing requirements in {ANSI.BOLD}{filename}{ANSI.RESET}")
  try:
    with open(filename) as jsonfile:
      tree = json.load(jsonfile)
  except:
    error(f"loading JSON file '{filename}'")
  body = tree['body']
  all_reqs = [e for e in body if e['type'] in REQUIREMENTS_TYPES]
  if len(all_reqs) == 0:
    # raise an error if all_reqs is empty?
    warning("no requirements found in '{filename}'")
  for reqs in all_reqs:
    reqs_name = reqs['name'].strip()
    emit_name = reqs_name.replace(' ', '')
    reqs_abbrev = reqs.get('abbrevName') # currently ignored
    reqs_prefix = REQS_GROUP_PREFIX[reqs_name]
    Fragment.append(emit_name, 1)
    count = 1
    for req in reqs['requirements']:
      req_label = f"{reqs_prefix}.{count}"
      req_id = req['id'].strip()
      req_text = req['text'].strip()
      req_text = req_text.replace('  ', ' ')
      Fragment.append(f'{reqs_prefix}{count}', 2)
      Fragment.append(f'[label = "{reqs_prefix}.{count}"]', 3)
      Fragment.append(f'[name = "{req_id}"]', 3)
      Fragment.append(f'[description = "{req_text}"]', 3)
      count += 1

#################
# Main Behavior #
#################

# Top-level behavior of the script.
def main():
  recreate_json_files()
  build_clafer_fragment()
  # Fragment.print()
  Fragment.write("requirements.cfr")

# Calls main() function of the script.
if __name__ == "__main__": main()
