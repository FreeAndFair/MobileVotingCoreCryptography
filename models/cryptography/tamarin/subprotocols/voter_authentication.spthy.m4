dnl
dnl This is the m4 input file for the Voter Authentication Subprotocol.
dnl If the STANDALONE macro is defined, this file generates a standalone
dnl version of the subprotocol; otherwise, it generates a Tamarin code
dnl snippet suitable for inclusion in a Tamarin file composing multiple
dnl subprotocols.
dnl
dnl If the VOTER_AUTHENTICATION_MOCKS macro is defined (which is always the
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
  Voter Authentication Subprotocol

  This protocol implements the voter authentication process, which
  involves a third-party KYC provider such as CLEAR (or something with
  a similar API). It involves the voter application, the election
  administration server, the digital ballot box, and the authentication
  server. These communicate using a secure channel abstraction, where
  adversaries are capable of both intercepting and injecting messages
  into channels.

  @author Daniel M. Zimmerman
  @copyright Free & Fair 2025
  @version 0.1
 */

theory voter_authentication

begin

define(<!USE_UNIQUE!>)dnl
define(<!USE_PSEUDONYM!>)dnl
include(common/primitives.m4.inc)
define(<!USE_SECURE_CHANNELS!>)dnl
define(<!USE_SECURE_CHANNELS_INJECTION!>)dnl
define(<!USE_SECURE_CHANNELS_INTERCEPTION!>)dnl
include(common/channels.m4.inc)

/*
  We don't include the bulletin board, even though we establish
  a fact for it, because it isn't used in the standalone version.
 */
!>)dnl
dnl If STANDALONE is defined, all mocks are always required
ifdef(<!STANDALONE!>,<!define(VOTER_AUTHENTICATION_MOCKS)!>)dnl
dnl
ifdef(<!VOTER_AUTHENTICATION_MOCKS!>,<!
/*
  The initial counters for ballot styles and voters are %1, and
  the election configuration is just a fresh variable.
 */
rule VoterAuthentication_Mock_EC_And_Initial_Counters [role="Mock"]:
    [ Fr(~ec) ]
  --[ Unique(<'EC_And_Initial_Counters', ~ec>),
      ElectionConfiguration_Trace(~ec) ]->
    [ BallotStyleCount(~ec, %1),
      VoterCount(~ec, %1) ]

/*
  Mock ballot styles into the environment. We simply
  generate an arbitrary number of persistent facts with ballot style
  identifiers for later use.
 */
rule VoterAuthentication_Mock_BallotStyle [role="Mock"]:
    [ BallotStyleCount(~ec, %i),
      Fr(~ballot_style) ]
  --[ BallotStyle_Trace(~ec, ~ballot_style, %i) ]->
    [ !BallotStyle(~ec, ~ballot_style, %i),
      BallotStyleCount(~ec, %i %+ %1) ]

/*
  Mock a voter registration database into the environment (for a voter
  that is eligible for this election). Voter IDs are Tamarin public
  variables (because we want the adversary to be able to attempt
  masquerading as a voter), that are distinguished by persistent facts
  associating them with eligibility information.
 */
rule VoterAuthentication_Mock_VoterRegistration_Eligible [role="Mock"]:
    [ VoterCount(~ec, %i),
      !BallotStyle(~ec, ~ballot_style, %unused) ]
  --[ Unique(<'VoterRegistration', ~ec, $V>),
      EligibleVoter_Trace(~ec, $V, ~ballot_style, %i) ]->
    [ !EligibleVoter(~ec, $V, ~ballot_style, %i),
      VoterCount(~ec, %i %+ %1) ]

/*
  Stop registering voters and ballot styles, then broadcast the
  election configuration. This also tells the DBB to start authorizing
  voters with index %1 for this election. Note the requirement for
  the rule, which ensures there is at least one eligible voter, one
  ineligible voter, and one ballot style.
 */
rule VoterAuthentication_Mock_Finalize_Election_Setup [role="Mock"]:
    [ !BallotStyle(~ec, ~bs_unused, %idx_bs_unused),
      !EligibleVoter(~ec, $EV, ~ev_bs_unused, %idx_ev_unused),
      BallotStyleCount(~ec, %next_idx_bs_unused),
      VoterCount(~ec, %next_idx_v_unused) ]
  --[ Unique(<'FinalizeElectionSetup', ~ec>),
      Finalize_Election_Setup_Trace(~ec) ]->
    [ !ElectionConfiguration(~ec),
      BB_Create_Request(~ec, ~ec),
      DBB_State_ReceiveAuthorizeVoter(~ec, %1),
      Out(~ec) ]
!>)
dnl
macros:
  /*
    Message types. The ones that include an "ec_hash" will actually use
    the election configuration, not its hash, because it is public
    information and Tamarin doesn't care if we hash it or not.
   */
  Msg_EAS_Request_Authentication_Session(project_id, api_key) = <'EAS_Request_Authentication_Session', project_id, api_key>,
  Msg_AS_Authentication_Session(session_id, token) = <'AS_Authentication_Session', session_id, token>,
  Msg_Voter_Authentication(token, voter_id) = <'Voter_Authentication', token, voter_id>,
  Msg_AS_Authentication_Complete(token) = <'AS_Authentication_Complete', token>,
  Msg_EAS_Request_Authentication_Result(session_id) = <'EAS_Request_Authentication_Result', session_id>,
  Msg_AS_Authentication_Result(session_id, voter_id, status) = <'AS_Authentication_Result', session_id, voter_id, status>,
  Msg_VA_Request_Authentication(ec_hash, pk_voter) = <'VA_Request_Authentication', ec_hash, pk_voter>,
  Msg_EAS_Authentication_Session(ec_hash, pk_voter, token) = <'EAS_Authentication_Session', ec_hash, pk_voter, token>,
  Msg_VA_Authentication_Complete(ec_hash, pk_voter, token) = <'VA_Authentication_Complete', ec_hash, pk_voter, token>,
  Msg_EAS_Authentication_Result(ec_hash, result, pseudo, pk_voter, ballot_style) = <'EAS_Authentication_Result', result, ec_hash, pseudo, pk_voter, ballot_style>,
  Msg_EAS_Authorize_Voter(ec_hash, pseudo, pk_voter, ballot_style) = <'EAS_Authorize_Voter', ec_hash, pseudo, pk_voter, ballot_style>

include(subprotocols/includes/voter_authentication_rules.spthy.inc)
dnl

include(subprotocols/includes/voter_authentication_lemmas.spthy.inc)
dnl

dnl
ifdef(<!STANDALONE!>,<!
end
!>)dnl
