dnl
dnl This is the m4 input file for the Trustee Setup Subprotocol.
dnl If the STANDALONE macro is defined, this file generates a standalone
dnl version of the subprotocol; otherwise, it generates a Tamarin code
dnl snippet suitable for inclusion in a Tamarin file composing multiple
dnl subprotocols.
dnl
dnl If the TRUSTEE_SETUP_MOCKS macro is defined (which is always the
dnl case when STANDALONE is defined), the Tamarin code snippet will include
dnl mock rules that simulate required actions of other subprotocols by
dnl establishing suitable linear/persistent/action facts.
dnl
dnl @author Daniel M. Zimmerman
dnl @copyright Free & Fair 2025
dnl @version 0.1
dnl
dnl We change the m4 quote characters to <! and !>, so that they don't
dnl interfere with Tamarin's quote characters or any comments we might
dnl want to write. The incantation below makes that change, and ensures
dnl that we don't try to change them if we've already done so (e.g.,
dnl when including this file in a composition).
dnl
ifdef(<!QUOTE_CHANGED!>,<!!>,<!changequote(`<!', `!>')!>)dnl
dnl
include(m4_utils/forloop.m4)dnl
dnl
ifdef(<!STANDALONE!>,<!/*
  Trustee Setup Subprotocol

  This subprotocol establishes the trustees' individual keys (and the TAS keys),
  distributes the election setup to the trustees, and achieves agreement among
  the TAS and the trustees about what the election setup is. It explicitly uses
  signed messages; later trustee subprotocols will not use signed messages,
  instead using Tamarin authenticated channels, because we will assume that
  authenticated channels between the TAS and trustees, and among trustees, and
  secure channels among trustees, exist based on the information exchanged in
  this subprotocol. In an actual implementation, all messages will be signed,
  and all messages for which confidentiality is required will be encrypted,
  regardless of whether or not they are transmitted over a TLS connection or
  in the open.

  @author Daniel M. Zimmerman
  @copyright Free & Fair 2025
  @version 0.1
 */

theory trustee_setup

begin

/*
  We define the specific restrictions we're going to use, so that we don't
  get warnings about restrictions referencing actions that don't exist.
 */
define(<!USE_EQUAL!>)dnl
define(<!USE_UNIQUE!>)dnl
define(<!USE_EUFCMA_SIGNING!>)dnl
include(common/primitives.m4.inc)
include(common/trustee_defaults.m4.inc)

!>)
dnl
dnl Include the macros (both m4 and Tamarin) shared by all the trustee
dnl subprotocols; note that the path is relative to the Makefile (and thus
dnl the working directory for m4), _not_ to this file.
define(<!TRUSTEE_SETUP!>)dnl
include(subprotocols/includes/trustee_macros.m4.inc)
dnl
dnl The trustee setup protocol is the first one to run, and thus requires
dnl no mocks to simulate the previous actions of other subprotocols.
dnl
dnl
dnl The rules for the trustees are included from a separate file (with
dnl path also relative to the Makefile).
dnl
include(subprotocols/includes/trustee_setup_rules_trustee.m4.inc)
dnl
dnl The rules for the TAS are included from a separate file (with path
dnl also relative to the Makefile).
dnl
include(subprotocols/includes/trustee_setup_rules_tas.m4.inc)
dnl
dnl The lemmas are included from another file (with path also relative
dnl to the Makefile).
dnl
include(subprotocols/includes/trustee_setup_lemmas.m4.inc)
dnl
ifdef(<!STANDALONE!>,<!
end
!>)dnl
