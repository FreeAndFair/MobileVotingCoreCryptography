# Subprotocols

This directory includes the individual subprotocols. When processed for standalone use, they are entirely self-contained Tamarin theories; when processed for composition (see [the compositions README](../compositions/README.md)), certain parts of them are removed.

The `make subprotocols` target of the parent directory [Makefile](../Makefile) generates standalone theories for all the subprotocols in this directory (i.e., all files ending in `.spthy.m4`).

More information about how the subprotocol files are structured with respect to `m4` macros can be found in the files themselves.
