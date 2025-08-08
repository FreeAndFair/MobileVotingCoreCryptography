dnl
dnl This is the m4 input file for the Trustee Mixing Subprotocol.
dnl If the STANDALONE macro is defined, this file generates a standalone
dnl version of the subprotocol; otherwise, it generates a Tamarin code
dnl snippet suitable for inclusion in a Tamarin file composing multiple
dnl subprotocols.
dnl
dnl If the TRUSTEE_MIXING_MOCKS macro is defined (which is always the
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
ifdef(<!STANDALONE!>,<!/*
include(m4_utils/forloop.m4)dnl
  Trustee Mixing Subprotocol

  This protocol implements the mixing of ballots by the trustees
  before decryption. This is carried out by trustees in K rounds,
  where K is the number of trustees present (this is assumed to be
  at least the threshold for decryption, as the decryption subprotocol
  takes place right after this one). In each round, the trustee that
  is supposed to shuffle that round takes the previous round's output
  (or the initial list of cryptograms, for the first round), shuffles
  it, and posts it for the other trustees to verify. Once all trustees
  have verified the shuffle, the next round proceeds. At the end,
  once all trustees have verified the final shuffle, the protocol is
  complete.

  This subprotocol uses the same trustee bulletin board construction
  as the election key generation subprotocol. It implements the
  shuffling and proofs as a very simplified equational theory, and
  does not actually "shuffle" anything; the shuffle is treated more
  like an encryption, where if you know the "key" (the shuffle
  randomness), you can reverse the shuffle.

  @author Daniel M. Zimmerman
  @copyright Free & Fair 2025
  @version 0.1
 */

theory trustee_mixing

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

define(<!TRUSTEE_MIXING!>)dnl
include(subprotocols/includes/trustee_macros.m4.inc)dnl
dnl
dnl If STANDALONE is defined, all mocks are always required
ifdef(<!STANDALONE!>,<!define(TRUSTEE_MIXING_MOCKS)!>)dnl
dnl
ifdef(<!TRUSTEE_MIXING_MOCKS!>,<!
dnl
dnl
dnl Include the mock for the trustee setup protocol, so that the trustees
dnl and their individual keys are all initialized properly and everything
dnl starts in the correct state.
dnl
dnl
include(subprotocols/includes/mock_trustee_setup.m4.inc)dnl
include(subprotocols/includes/mock_election_key_generation.m4.inc)dnl
!>)dnl
dnl
dnl Include the rules for the TAS.
dnl

include(subprotocols/includes/trustee_mixing_rules_tas.m4.inc)dnl
dnl
dnl Include the rules for the trustees.
dnl

include(subprotocols/includes/trustee_mixing_rules_trustee.m4.inc)dnl
dnl
dnl Include the rules that allow an adversary (i.e., a corrupt trustee)
dnl to attempt to submit trustee messages.
dnl

include(subprotocols/includes/trustee_mixing_rules_adversary.m4.inc)dnl
dnl
dnl Include the lemmas.
dnl

include(subprotocols/includes/trustee_mixing_lemmas.m4.inc)dnl
ifdef(<!STANDALONE!>,<!
end
!>)dnl
