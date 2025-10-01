# Subprotocol Compositions

This directory includes all the subprotocol compositions that are "interesting" in the sense that we want to prove properties about them, above and beyond those of the individual subprotocols. The composition of all the subprotocols (i.e., the full protocol), [all_subprotocols.spthy.m4](./all_subprotocols.spthy.m4), provides an example of how to construct such a composition. Compositions of fewer subprotocols will likely necessitate the inclusion of mocks by defining appropriate `m4` macros before including the subprotocols. We will address this as we decide what compositions to work with.

The `make compositions` target of the parent directory [Makefile](../Makefile) builds all the compositions in this directory (i.e., all files ending in `.spthy.m4`).

## Composition List

- Bulletin Board Test - [bulletinboard_test.spthy.m4](./bulletinboard_test.spthy.m4): The composition of the bulletin board implementation and a protocol that exercises it, to "test" bulletin board properties
- Internet Subprotocols - [internet_subprotocols.spthy.m4](./internet_subprotocols.spthy.m4): The composition of all subprotocols that are exposed to the Internet
