#!/usr/bin/env python3
############################################################################
# Python 3 script to delete files in a directory with duplicare content.   #
# On previous occasions, we noticed that claferIG sometimes generates such #
# duplicate instances (though we are not sure if chocosolver suffers from  #
# the same issue). The script provides added assurance that no dups exist. #
############################################################################
import sys, os, glob
import argparse, hashlib, filecmp

# Infer the name of the script.
SCRIPT_NAME = os.path.basename(sys.argv[0])

# The below can be set via the -v or --verbose CLI option.
VERBOSE_OUTPUT = False

# The below can be set via the -vv or --debug CLI option.
DEBUG_OUTPUT = False

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

#####################
# Utility Functions #
#####################

# Maps SHA256 hash values to filenames.
HASHED_FILES = {}

# Returns the SHA256 hash value of the content of a given
# file and adds an entry HASHED_FILES[digest] = filename
# in case digest is not already associated with a filename.
def hashfile(filename):
  sha1 = hashlib.sha1()
  with open(filename, 'rb') as file:
    data = file.read()
    sha1.update(data)
  # The following only works with Python 3.11 or later ...
  # digest = hashlib.file_digest(file, 'sha256').hexdigest()
  digest = sha1.hexdigest()
  if digest not in HASHED_FILES.keys():
    HASHED_FILES[digest] = filename
  return digest

# Remove all duplicate *.<ext> files under the <directory> folder.
# Precondition: directory points to a valid instances directory.
def remove_dups(directory, extension):
  assert(os.path.isdir(directory))
  info(f"Removing duplicate *.{extension} files under '{directory}' ...")
  filenames = glob.glob(f"{directory}/*.{extension}")
  filenames = sorted(filenames)
  total = len(filenames)
  removed = 0
  for filename in filenames:
    digest = hashfile(filename)
    if HASHED_FILES[digest] != filename:
      # Double-check that HASHED_FILES[digest] and
      # filename have the same binary data content.
      # Unlikely this fails in practice but there
      # is a nonzero probability of it nonetheless.
      if filecmp.cmp(HASHED_FILES[digest], filename):
        debug("Deleting duplicate: " + filename)
        os.remove(filename)
        removed = removed + 1
  info(f"{removed} duplicate file(s) removed, " +
       f"{total - removed} unique files remaining.")

###################
# Argument Parser #
###################

# Displays usage information and aborts the script with error code 1.
def usage():
  print(f"{ANSI.BOLD}usage{ANSI.RESET}: ", end='')
  print(f"{SCRIPT_NAME} <folder containing the *.inst files>")
  sys.exit(1)

# Command-Line Argument Parser
ARG_PARSER = argparse.ArgumentParser(
  prog = SCRIPT_NAME,
  description = f"""Duplicate File Removal Tool, 2024 (c) Galois Inc.

Removes files with duplicate content. Only files with the
{ANSI.BOLD}given extensions{ANSI.RESET} are scanned and considered for removal.
""",
  epilog = f"Please contact {ANSI.BLUE}Ethan Lew{ANSI.RESET} (elew@galois.com) \
for support and/or maintenance.",
  formatter_class = argparse.RawTextHelpFormatter
)

ARG_PARSER.add_argument('directory', metavar = 'DIR',
  help = f"""directory from which to remove files
with duplicate content""")

ARG_PARSER.add_argument('-e', '--ext', metavar = 'FILE-EXTENSION',
  dest = 'extension',
  help = f"""file extenion of scanned files (without the dot)""")

ARG_PARSER.add_argument('-v', '--verbose', action = 'store_true',
  dest = 'verbose',
  help = f"""enable verbose (informative) messages""")

ARG_PARSER.add_argument('-vv', '--debug', action = 'store_true',
  dest = 'debug',
  help = f"""enable debugging message output""")

def arg_error(msg):
  print_usage()
  eprint(f"{SCRIPT_NAME}: error: {msg}")
  exit(1)

def parse_args():
  global DIRECTORY
  global EXTENSION
  global VERBOSE_OUTPUT
  global DEBUG_OUTPUT
  args = ARG_PARSER.parse_args()
  if args.extension is None:
    arg_error("the following argument is required: FILE-EXTENSION")
  DIRECTORY = args.directory
  EXTENSION = args.extension
  VERBOSE_OUTPUT = args.verbose
  DEBUG_OUTPUT = args.debug
  return args

def print_usage():
  ARG_PARSER.print_usage()

#################
# Main Behavior #
#################

# Scans the folder passed to the script and removes all duplicate .inst files.
def main():
  global DIRECTORY
  global EXTENSION
  parse_args()
  if os.path.exists(DIRECTORY):
    if os.path.isdir(DIRECTORY):
      if os.access(DIRECTORY, os.R_OK):
        remove_dups(DIRECTORY, EXTENSION)
      else: error(f"'{DIRECTORY}' seems not to be readable")
    else: error(f"'{DIRECTORY}' is not a directory")
  else: error(f"folder '{DIRECTORY}' does not exist")

# Entry point of the script.
if __name__ == "__main__": main()
