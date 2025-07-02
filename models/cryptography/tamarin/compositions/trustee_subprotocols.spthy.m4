dnl
dnl This is the m4 input file for the composition of the trustee
dnl subprotocols at the end of the election.
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
include(m4_utils/forloop.m4)dnl
dnl
dnl
dnl This particular composition is uncomplicated; we just include the
dnl common primitives and all the relevant subprotocol rules and lemmas.
dnl
/*
  E2E-VIV Protocol - Composition of Trustee Subprotocols

  This theory is a composition of the election-ending subprotocol
  theories for the trustees; it does not include the initial trustee
  setup that ensures that trustees agree on their public keys and the
  election configuration, or the election public key generation that
  takes place before the election.

  @author Daniel M. Zimmerman
  @copyright Free & Fair 2025
  @version 0.1
 */

theory e2eviv_trustee

begin

include(common/primitives.m4.inc)
dnl
dnl Set the number of trustees to 3.
dnl
define(TRUSTEE_COUNT, <!3!>)dnl
dnl
dnl Include the macros (both m4 and Tamarin) shared by all the trustee
dnl subprotocols; note that the path is relative to the Makefile (and thus
dnl the working directory for m4), _not_ to this file.
include(subprotocols/includes/trustee_macros.m4.inc)
dnl
dnl We also need to include the mock trustee setup.
dnl
include(subprotocols/includes/mock_trustee_setup.m4.inc)
dnl
/* Trustee Mixing */

include(subprotocols/trustee_mixing.spthy.m4)

/* Trustee Decryption */

include(subprotocols/trustee_decryption.spthy.m4)

dnl We don't need a newline here, it comes from the included file
end
