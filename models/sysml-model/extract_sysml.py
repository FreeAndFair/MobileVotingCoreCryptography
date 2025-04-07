#!/usr/bin/env python

# This script extracts the SysML code from a SysML Jupyter notebook.
#
# Usage: extract_sysml notebook_file output_file
#
# Daniel M. Zimmerman, January 2025
# Copyright (C) 2025 Free & Fair

import argparse
from nbformat import read, NO_CONVERT

def extract(nb_filename, dest_filename):
  notebook = {}
  with open(nb_filename) as nb_file:
    try:
      notebook = read(nb_file, NO_CONVERT)
    except:
      print(f'could not read or parse file {filename}, aborting')
      exit(1)

  cells = notebook.cells
  code_cells = [c for c in cells if c.cell_type == 'code']

  with open(dest_filename, 'w') as dest_file:
    for cell in code_cells:
        if not cell.source.startswith('%'):
          # we don't write cells that start with "%", those are magic commands
          # and not valid SysML
          dest_file.write(cell.source)
          if not cell.source.endswith('\n'):
            # no newline at end of source block, we'll add one
            dest_file.write('\n')
          # add a newline between cells
          dest_file.write('\n')

def main():
  parser = argparse.ArgumentParser(description='Extract SysML code from a SysML Jupyter notebook.')
  parser.add_argument('notebook_file', type=str, help='Path to the notebook file')
  parser.add_argument('output_file', type=str, help='Path to the output file')
  args = parser.parse_args()

  extract(args.notebook_file, args.output_file)

if __name__ == "__main__":
    main()
