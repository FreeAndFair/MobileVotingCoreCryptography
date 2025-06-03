dnl
dnl This is the m4 input file for the composition of all the subprotocols.
dnl
dnl @author Daniel M. Zimmerman
dnl @copyright Free & Fair 2025
dnl @version 0.1
dnl
dnl We change the m4 quote characters to <! and !>, so that they don't
dnl interfere with Tamarin's quote characters or any comments we might
dnl want to write. The incantation below makes that change, and prevents
dnl us from doing it in the included files by defining QUOTE_CHANGED.
dnl
define(`QUOTE_CHANGED')
changequote(`<!', `!>')
dnl
dnl This particular composition is uncomplicated; we just include the
dnl common primitives and all the subprotocol rules and lemmas.
dnl
/*
  Full E2E-VIV Protocol
  (Composition of All Subprotocols)

  This theory is a composition of all the subprotocol theories. It will
  likely at some point include additional "cross-subprotocol" lemmas as
  well, but for now is just a straightforward composition.

  @author Daniel M. Zimmerman
  @copyright Free & Fair 2025
  @version 0.1
 */

theory e2eviv

begin

#include "../common/primitives.spthy.inc"


/* Ballot Cast */

include(subprotocols/ballot_cast.spthy.m4)

/* Ballot Check */

include(subprotocols/ballot_check.spthy.m4)

/* Ballot Submission */

include(subprotocols/ballot_submission.spthy.m4)

/* Election Key Generation */

include(subprotocols/election_key_generation.spthy.m4)

/* Trustee Decryption */

include(subprotocols/trustee_decryption.spthy.m4)

/* Trustee Mixing */

include(subprotocols/trustee_mixing.spthy.m4)

/* Voter Authentication */

include(subprotocols/voter_authentication.spthy.m4)
dnl We don't need a newline here, it comes from the included file
end
