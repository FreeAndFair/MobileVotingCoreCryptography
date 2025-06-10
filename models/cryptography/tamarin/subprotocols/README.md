# Subprotocols

This directory includes the individual subprotocols. When processed for standalone use, they are entirely self-contained Tamarin theories; when processed for composition (see [the compositions README](../compositions/README.md)), certain parts of them are removed or modified.

The `make subprotocols` target of the parent directory [Makefile](../Makefile) generates standalone theories for all the subprotocols in this directory (i.e., all files ending in `.spthy.m4`).

More information about how the subprotocol files are structured with respect to `m4` macros can be found in the files themselves.

Note that this is currently an _initial_ version of the subprotocols; in particular, the trustee setup protocol included here needs to be revised to use the same model of execution for the trustee authentication server as the later models, where the trustee authentication server exists only as a way for the trustees to communicate with each other and not as a protocol actor of its own with tasks to perform.
