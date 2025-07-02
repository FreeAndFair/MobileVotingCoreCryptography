dnl
dnl This is the m4 input file for the composition of all the subprotocols
dnl that take place outside the air-gapped network (i.e., exposed to the
dnl Internet).
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
dnl common primitives and all the relevant subprotocol rules and lemmas.
dnl
/*
  E2E-VIV Protocol - Composition of Internet-Exposed Subprotocols

  This theory is a composition of all the subprotocol theories for those
  subprotocols that are executed on systems exposed to the Internet. It
  will likely at some point include additional "cross-subprotocol" lemmas
  as well, but for now is just a straightforward composition.

  @author Daniel M. Zimmerman
  @copyright Free & Fair 2025
  @version 0.1
 */

theory e2eviv_internet

begin

include(common/primitives.m4.inc)
include(common/channels.m4.inc)
include(common/bulletinboard.m4.inc)

/* Ballot Cast */

include(subprotocols/ballot_cast.spthy.m4)

/* Ballot Check */

include(subprotocols/ballot_check.spthy.m4)

/* Ballot Submission */

include(subprotocols/ballot_submission.spthy.m4)

/* Voter Authentication */

include(subprotocols/voter_authentication.spthy.m4)
dnl We don't need a newline here, it comes from the included file
end
