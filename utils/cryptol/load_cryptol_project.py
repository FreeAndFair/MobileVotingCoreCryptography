#! /usr/bin/env python

# This script uses Cryptol's Python API to load (and typecheck) a
# Cryptol project's modules, without checking their docstrings. Based
# on "run-docstrings.py" from the Cryptol GitHub repository,
# <https://github.com/galoisinc/cryptol>.
#
# Usage: load_cryptol_project.py <project file or directory>
#
# Daniel M. Zimmerman, June 2025
# Copyright (C) 2025 Free & Fair

import os
import sys
from cryptol.connection import connect

cry = connect(url="http://localhost:8080/", reset_server=True, verify=False)

if len(sys.argv) != 2:
  print("Usage: load_cryptol_project.py <project file or directory>\n")
  exit(1)

project_file = os.path.abspath(sys.argv[1])
print("Loading project " + os.path.relpath(project_file) + "...")

project_dir = project_file
if not os.path.isdir(project_dir):
    project_dir = os.path.dirname(project_dir)

# Load the Cryptol project.
proj = cry.load_project(project_file, "refresh").result()

# Check whether any of the project files have errors.
error = False
if len(proj["scan_status"]) == 0:
  print("no files loaded, reporting error")
  error = True
else:
  for obj in proj["scan_status"]:
      if not "file" in obj:
          continue

      file = obj["file"]

      # File does not contain errors
      if "scanned" in obj:
          print(file + " - no errors")
      # We failed to load the file because of some parse errors
      elif "invalid_module" in obj:
          print(file + " - error:", obj["invalid_module"]["error"])
          error = True
      elif "invalid_dep" in obj:
          print(file + " - depends on a module with an error")
          error = True

# If anything had an error, exit with an error code.
if error:
    exit(1)
