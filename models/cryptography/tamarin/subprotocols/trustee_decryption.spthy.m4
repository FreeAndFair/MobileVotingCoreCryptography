dnl
dnl This is the m4 input file for the Trustee Decryption Subprotocol.
dnl If the STANDALONE macro is defined, this file generates a standalone
dnl version of the subprotocol; otherwise, it generates a Tamarin code
dnl snippet suitable for inclusion in a Tamarin file composing multiple
dnl subprotocols.
dnl
dnl If the TRUSTEE_DECRYPTION_MOCKS macro is defined (which is always the
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
  Trustee Decryption Subprotocol

  This protocol implements the decryption of ballots by the trustees.
  This is carried out by trustees in two rounds, where each trustee
  first performs its partial decryption of the mixed ballots and then
  combines the partial decryptions to generate a full decryption.

  This subprotocol uses the same trustee bulletin board and other
  trustee setup as the trustee mixing subprotocol, with an additional
  mock for the trustee mixing.

  @author Daniel M. Zimmerman
  @copyright Free & Fair 2025
  @version 0.1
 */

theory trustee_decryption

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

define(<!TRUSTEE_DECRYPTION!>)dnl
include(subprotocols/includes/trustee_macros.m4.inc)dnl
dnl
dnl If STANDALONE is defined, all mocks are always required
ifdef(<!STANDALONE!>,<!define(TRUSTEE_DECRYPTION_MOCKS)!>)dnl
dnl
ifdef(<!TRUSTEE_DECRYPTION_MOCKS!>,<!
dnl
dnl
dnl Include the mock for the trustee setup and election key generation
dnl protocols, so that the trustees and their individual keys are all
dnl initialized properly, as well as the trustee mixing subprotocol.
dnl
include(subprotocols/includes/mock_trustee_setup.m4.inc)dnl
include(subprotocols/includes/mock_election_key_generation.m4.inc)dnl
dnl
dnl Mock the trustee mixing process
dnl
/*
  This rule generates a "set" of ballots (really, only one cryptogram,
  because in Tamarin the treatment of multiple cryptograms would be
  symmetric, and we just need to make sure it's decryptable at the end
  by the threshold number of trustees).
 */
rule Mock_GenerateBallotSet [role="Mock"]:
  let c1 = ny_encrypt_c1(~ballots, pk_election, ~r)
      c2 = ny_encrypt_c2(~ballots, pk_election, ~r)
      cryptograms = <c1, c2> in
    [ !ElectionPublicKey(pk_election),
      Fr(~ballots), Fr(~r) ]
  --[ TAS_BallotSet_Trace(cryptograms, ~ballots),
      Unique('TrusteeMixing_BallotSet'),
      OUT_BALLOTSET_C1_TERM(c1),
      OUT_BALLOTSET_C2_TERM(c2),
      OUT_PARTIAL_C1_TERM(c1),
      OUT_PARTIAL_C2_TERM(c2) ]->
    [ !TAS_Cryptogram_Set(cryptograms),
      /* We save the plaintext "ballots" to check threshold decryption later. */
      !TAS_Ballot_Set(~ballots) ]

/*
  This rule establishes all the environment facts for trustee mixing,
  so that the decryption protocol can run as though it were being
  run directly after the mixing protocol.
 */
rule Mock_TrusteeMixing [role="Mock"]:
    [ TAS_State_BeginTrusteeMixing(),
      !TAS_ElectionSetup_Complete(election_setup),
      !TAS_Cryptogram_Set(cryptograms),
      !TAS_Secret_Signing_Key(sk_sign),
      !TAS_Public_Signing_Key(pk_sign),
      Fr(~sk_encrypt_unused),
      Fr(~ballot_order),
      Fr(~shuffle_proofs) ]
  --[ TAS_TrusteeMixing_Init_Trace(cryptograms),
      TAS_Trustee_Trace('Trustee0', pk_sign, pk(~sk_encrypt_unused)),
      Unique('Mock_TrusteeMixing'),
      /* The decryption protocol doesn't care about our shuffle order or shuffle proofs. */
      TAS_TrusteeMixing_Complete_Trace('order ignored', cryptograms, 'shuffle proofs ignored') ]->
    [ !Trustee_Public_Keys('Trustee0', pk_sign, pk(~sk_encrypt_unused)), /* public keys for TAS as "trustee 0" */
      TAS_TrusteeMixing_Complete(~ballot_order, cryptograms, ~shuffle_proofs),
      TAS_State_ReceiveTrusteeMessage(%1),
forloop(<!TN!>, eval(TRUSTEE_COUNT - TRUSTEE_THRESHOLD + 1), TRUSTEE_COUNT, <!      Trustee_State_ReceiveBBMessage('Trustee<!!>TN<!!>', %1),
!>)dnl
      TAS_State_BeginTrusteeDecryption() ]
!>)dnl
dnl
dnl Include the rules for the TAS.
dnl

include(subprotocols/includes/trustee_decryption_rules_tas.m4.inc)dnl
dnl
dnl Include the rules for the trustees.
dnl

include(subprotocols/includes/trustee_decryption_rules_trustee.m4.inc)dnl
dnl
dnl Include the rules that allow an adversary (i.e., a corrupt trustee)
dnl to attempt to submit trustee messages.
dnl

include(subprotocols/includes/trustee_decryption_rules_adversary.m4.inc)dnl
dnl
dnl Include the lemmas.
dnl

include(subprotocols/includes/trustee_decryption_lemmas.m4.inc)dnl
ifdef(<!STANDALONE!>,<!
end
!>)dnl
