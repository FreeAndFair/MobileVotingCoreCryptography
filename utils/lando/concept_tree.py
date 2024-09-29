#!/usr/bin/env python

# When called with the path to a Lando JSON file as a command
# line parameter, this script generates an ANSI-colored textual 
# tree representation of the concepts in the Lando specification. 
# 
# It may be further extended in the future to show different 
# relationships or otherwise elucidate more of the Lando model's 
# structure.

import sys, os, re
import argparse, json

# Obtain the file name of this script.
SCRIPT_NAME = os.path.basename(__file__)

# Class providing definitions for ANSI escape sequences
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

# Lando class names for concept structure elements.
STRUCTURE_TYPES =  [
  "com.galois.besspin.lando.ssl.ast.RawSystem",
  "com.galois.besspin.lando.ssl.ast.RawSubsystem",
  "com.galois.besspin.lando.ssl.ast.RawComponent"
]

# Lando class names for requiurements elements.
REQUIREMENTS_TYPES =  [
  "com.galois.besspin.lando.ssl.ast.RawRequirements"
]

# Prints to stderr by default
def eprint(*args, **kwargs):
  print(*args, file = sys.stderr, **kwargs)

# Read lando JSON file.
def read_lando(filename):
  try:
    with open(filename) as json_file:
     content = json.load(json_file)
    return content
  except:
    eprint('Error reading JSON file, aborting.')
    exit(1)

# Render concept structure tree.
def walk_concepts(tree, prefix = ""):
  if 'body' in tree:
    body = tree['body']
    elements = [e for e in body if e['type'] in STRUCTURE_TYPES]
    count = 1
    for element in elements:
      last = count == len(elements)
      type = element['type']
      name = element['name']
      abbrevName = element.get('abbrevName') # may be None
      print(prefix, end = '')
      print("└── " if last else "├── ", end = '')
      if abbrevName != None:
        print(f"{name} ({ANSI.BOLD}{abbrevName}{ANSI.RESET})")
      else:
        print(f"{name} ({ANSI.RED}{abbrevName}{ANSI.RESET})")
      walk_concepts(element, prefix + ("    " if last else "│   "))
      count += 1

# Determines if subtree contains requirements as leaf nodes.
def contains_requirements(tree):
  if tree['type'] in REQUIREMENTS_TYPES:
    return True
  elif 'body' in tree:
    body = tree['body']
    for element in body:
      if contains_requirements(element):
        return True
    return False
  else: return False

# Render requirements structure tree.
def walk_requirements(tree, prefix = ""):
  if 'body' in tree:
    body = tree['body']
    # elements = [e for e in body if e['type'] in REQUIREMENTS_TYPES]
    elements = [e for e in body if contains_requirements(e)]
    count = 1
    for element in elements:
      last = count == len(elements)
      type = element['type']
      name = element['name']
      if type.endswith("RawSystem"):
        name = name + f" ({ANSI.GREEN}system{ANSI.RESET})"
      if type.endswith("RawSubsystem"):
        name = name + f" ({ANSI.GREEN}subsystem{ANSI.RESET})"
      print(prefix, end = '')
      print("└── " if last else "├── ", end = '')
      print(f"{name}")
      walk_requirements(element, prefix + ("    " if last else "│   "))
      count += 1
  if 'requirements' in tree:
    requirements = tree['requirements']
    count = 1
    for requirement in requirements:
      last = count == len(requirements)
      id = requirement['id']
      print(prefix, end = '')
      print("└── " if last else "├── ", end = '')
      print(f"{id}")
      count += 1

# Print usage information for this script.
def usage():
  eprint(f"usage: {SCRIPT_NAME} LANDO-JSON-FILE")

# Main function: read JSON file and render tree.
def main():
  # Check number of arguments.
  if len(sys.argv) != 2:
    usage()
    exit(1)

  # Load JSON file for Lando spec.
  tree = read_lando(sys.argv[1])

  # Render system/concept structure tree.
  print(f"{ANSI.BLUE}Concept Structure{ANSI.RESET}")
  walk_concepts(tree)

  # Render requirements structure tree.
  print(f"{ANSI.BLUE}Requirements{ANSI.RESET}")
  walk_requirements(tree)

# Calls main() function of the script.
if __name__ == "__main__":
  main()
