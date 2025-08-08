dnl
dnl This is the m4 input file for the Election Key Generation Subprotocol.
dnl If the STANDALONE macro is defined, this file generates a standalone
dnl version of the subprotocol; otherwise, it generates a Tamarin code
dnl snippet suitable for inclusion in a Tamarin file composing multiple
dnl subprotocols.
dnl
dnl If the ELECTION_KEY_GENERATION_MOCKS macro is defined (which is always
dnl the case when STANDALONE is defined), the Tamarin code snippet will
dnl include mock rules that simulate required actions of other subprotocols
dnl by establishing suitable linear/persistent/action facts.
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
ifdef(<!STANDALONE!>,<!/*
include(m4_utils/forloop.m4)dnl
  Election Key Generation Subprotocol

  This protocol implements the election key generation process, which is
  carried out by trustees in two rounds. In the first round, the trustees
  - who already know each others' names and public keys - generate their
  private key shares and the pairwise key shares they share with the other
  trustees, encrypt the latter appropriately for each recipient, and post
  them to the trustee bulletin board. In the second round, they use the
  information posted in the first round to generate the election public
  key.

  The trustee bulletin board is implemented as (1) a set of persistent
  facts for what messages the TAS has seen, (2) a set of persistent facts
  per trustee for what messages that trustee has seen, (3) a submission
  mechanism for messages that is very much like a typical Tamarin secure
  channel, and (4) a mechanism for each trustee to maintain its own local
  bulletin board that follows the TAS bulletin board, also via a mechanism
  very much like a typical Tamarin secure channel. Injection of messages is
  possible on the TAS bulletin board, as is the revelation of private keys
  and private shares to the adversary, but direct injection of messages to
  the local trustee bulletin boards is _not_ possible in this model.

  @uthor Daniel M. Zimmerman
  @copyright Free & Fair 2025
  @version 0.1
 */

theory election_key_generation

begin

dnl
dnl We define the specific restrictions we're going to use, so that we don't
dnl get warnings about restrictions referencing actions that don't exist.
dnl
define(<!USE_UNIQUE!>)dnl
define(<!USE_EUFCMA_SIGNING!>)dnl
define(<!USE_EQUALITY!>)dnl
define(<!USE_INEQUALITY!>)dnl
define(<!USE_ABSTRACTED_NAOR_YUNG!>)dnl
include(common/primitives.m4.inc)
include(common/trustee_defaults.m4.inc)

dnl
dnl Include the trustee board rules.
dnl
include(common/trustee_board.m4.inc)
!>)
dnl
dnl Include the macros (both m4 and Tamarin) shared by all the trustee
dnl subprotocols; note that the path is relative to the Makefile (and thus
dnl the working directory for m4), _not_ to this file.

define(<!ELECTION_KEY_GENERATION!>)dnl
include(subprotocols/includes/trustee_macros.m4.inc)dnl
dnl
dnl If STANDALONE is defined, all mocks are always required
ifdef(<!STANDALONE!>,<!define(ELECTION_KEY_GENERATION_MOCKS)!>)dnl
dnl
ifdef(<!ELECTION_KEY_GENERATION_MOCKS!>,<!dnl
dnl
dnl Include the mock for the trustee setup protocol, so that the trustees
dnl and their individual keys are all initialized properly and everything
dnl starts in the correct state.
dnl
dnl
include(subprotocols/includes/mock_trustee_setup.m4.inc)dnl
!>)dnl
dnl
dnl Include the rules for the TAS.
dnl

include(subprotocols/includes/election_key_generation_rules_tas.m4.inc)dnl
dnl
dnl Include the rules for the trustees.
dnl

include(subprotocols/includes/election_key_generation_rules_trustee.m4.inc)dnl
dnl
dnl Include the rules that allow an adversary (i.e., a corrupt trustee)
dnl to attempt to submit trustee messages.
dnl

include(subprotocols/includes/election_key_generation_rules_adversary.m4.inc)dnl
dnl
dnl Include the lemmas.
dnl

include(subprotocols/includes/election_key_generation_lemmas.m4.inc)dnl
ifdef(<!STANDALONE!>,<!
end
!>)dnl
