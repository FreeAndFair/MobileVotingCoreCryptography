dnl
dnl This is the m4 input file for mocking voter authentication.
dnl
dnl @author Daniel M. Zimmerman
dnl @copyright Free & Fair 2025
dnl @version 0.1
dnl

macros:
  /* The EAS voter authorization message. */
  Msg_EAS_Authorize_Voter(ec_hash, pseudo, pk_voter, ballot_style) = <'EAS_Authorize_Voter', ec_hash, pseudo, pk_voter, ballot_style>,

/*
  Mock a voter authentication. This creates the persistent and
  linear facts that authorize a voter with a particular public
  key to vote a ballot of a particular ballot style and prompt
  the VA to have the voter fill in their ballot.

  Note that this can happen continuously, mocking the fact that
  the voter authentication protocol runs concurrently (for other
  voters) with theballot submission protocol. Note also that this
  can (rightly) result in a particular VA session having its
  votes rejected because the voter public key it was using was
  superceded by a subsequent authentication.
 */
rule Mock_Voter_Authentication [role="Mock"]:
  let pk_voter = pk(~sk_voter)
      pseudo = pseudonym($V)
      msg_auth = Msg_EAS_Authorize_Voter(~ec, pseudo, pk_voter, ~bs)
      signed_msg_auth = <msg_auth, sign(msg_auth, '1', ~sk_eas)> in
    [ DBB_State_ReceiveAuthorizeVoter(~ec, %i),
      !BallotStyle(~ec, ~bs, %idx_bs),
      !EligibleVoter(~ec, $V, ~bs, %idx_ev),
      !EASSecretKey(~ec, ~sk_eas),
      Fr(~sk_voter),
      Fr(~va_id) ]
  --[ Unique(<'VoterAuth', %i>),
      HonestSignatureKey(pk_voter),
      Voter_Authentication_Trace(~ec, ~va_id, $V, ~sk_voter, %i),
      DBB_Voter_Authorized_Trace(~ec, pseudo, pk_voter, ~bs, %i) ]->
    [ !DBB_Voter_Authorized(~ec, signed_msg_auth, pseudo, pk_voter, ~bs, %i),
      !VA_Eligible_Voter(~ec, ~va_id, pseudo, ~sk_voter, ~bs),
      VA_State_PresentBallot(~ec, ~va_id, $V, ~sk_voter),
      DBB_State_ReceiveAuthorizeVoter(~ec, %i %+ %1) ]

/*
  This rule has BB_Terminate_Request on its right-hand side, so
  that we don't get a well-formedness warning when we don't use it.
  Note that we are requesting to terminate a bulletin board that
  doesn't actually exist, so this has no real effect on anything.
 */
rule Mock_BBTerminate [role="Mock"]:
    []
  --[ Unique('BallotSubmission_Mock_BB_Terminate') ]->
    [ BB_Terminate_Request('fake_bbid', %1) ]
