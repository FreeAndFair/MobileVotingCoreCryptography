dnl
dnl This is the m4 input file for mocking ballot submission.
dnl
dnl @author Daniel M. Zimmerman
dnl @copyright Free & Fair 2025
dnl @version 0.1
dnl

/*
  Message definitions from ballot submission protocol.
 */
macros:
  Msg_VA_Submit_Ballot(ec_hash, pseudonym, pk_voter, ballot_style, cryptograms) = <'VA_Submit_Ballot', ec_hash, pseudonym, pk_voter, ballot_style, cryptograms>,
  Msg_DBB_Ballot_Tracker(ec_hash, tracker) = <'DBB_Ballot_Tracker', ec_hash, tracker>,
  BBEntry_Ballot_Submission(ec_hash, timestamp, ballot_msg) = <'BBEntry_Ballot_Submission', ec_hash, timestamp, ballot_msg>

/*
  Mock a ballot submission (step 1). This creates the persistent and
  linear facts that correspond to a ballot submission by the VA, and
  attempts to have the DBB accept that ballot and put it on the bulletin
  board.

  Note that this is triggered by the linear VA_State_PresentBallot fact;
  it can thus be re-triggered if that fact is re-established (e.g., if
  the voter decides to submit a new ballot), though this should not
  occur in this protocol in isolation.
 */
rule Mock_Ballot_Submission [role="Mock"]:
  let cryptograms = <ny_encrypt_c1(~ballot, pk_election, ~r), ny_encrypt_c2(~ballot, pk_election, ~r), ny_encrypt_p(~ballot, pk_election, ~r)>
      msg_submit_ballot = Msg_VA_Submit_Ballot(~ec, pseudo, pk_voter, ~bs, cryptograms)
      signed_msg_submit_ballot = <msg_submit_ballot, sign(msg_submit_ballot, '1', ~sk_voter)> in
    [ VA_State_PresentBallot(~ec, ~va_id, $V, ~sk_voter),
      !ElectionPublicKey(~ec, pk_election),
      !DBB_Voter_Authorized(~ec, auth_msg_unused, pseudo, pk_voter, ~bs, %i),
      !VA_Eligible_Voter(~ec, ~va_id, pseudo, ~sk_voter, ~bs),
      Fr(~ballot),
      Fr(~r),
      Fr(~cid) /* unused here but used in submission protocol */ ]
  --[ DBB_ReceiveSubmittedBallot_Trace(~ec, ~va_id, msg_submit_ballot),
      MostRecentAuthorization(~ec, pseudo, pk_voter, %i) ]->
    [ !DBB_Submitted_Ballot(~ec, ~va_id, ~cid, pseudo, signed_msg_submit_ballot),
      !Mock_Submitted_Ballot(~ec, ~va_id, $V, ~ballot, cryptograms, ~r, signed_msg_submit_ballot) ]

/*
  Mock a ballot submission (step 2). This publishes the ballot to the
  bulletin board, and needs to be its own rule because of how the
  bulletin board works in Tamarin (we have to pick some element of
  the bulletin board to append to and if it isn't the last one, the
  append fails). This rule is restricted to run only when the ballot
  has not been successfully appended to the bulletin board, and to
  run at most once for each board index.
 */
rule Mock_AppendSubmittedBallot [role="Mock"]:
  let bb_entry = BBEntry_Ballot_Submission(~ec, %ts, signed_msg_submit_ballot) in
    [ !DBB_Submitted_Ballot(~ec, ~va_id, ~cid, pseudo, signed_msg_submit_ballot),
      !Mock_Submitted_Ballot(~ec, ~va_id, $V, ~ballot, cryptograms, ~r, signed_msg_submit_ballot),
      DBB_Clock(%ts),
      !BB_Root(~ec, bbid, r_unused, rh_unused),
      !BB_Entry(bbid, e_unused, eh_unused, %idx) ]
  --[ DBB_AppendSubmittedBallot_Trace(~ec, ~va_id, signed_msg_submit_ballot, bbid, %idx),
      Unique(<'Mock_AppendSubmittedBallot', signed_msg_submit_ballot, %idx>),
      SubmissionNotOnBB(bbid, signed_msg_submit_ballot) ]->
    [ BB_Append_Request(bbid, bb_entry, %idx),
      DBB_Clock(%ts %+ %1),
      DBB_State_ConfirmBallotPosting(~ec, ~va_id, ~cid, pseudo, bb_entry, %idx %+ %1) ]

/*
  Mock a ballot submission (step 3). This checks that the ballot has been
  published and establishes the persistent and linear facts that simulate
  such publication having been confirmed to the VA, putting the VA into the
  "cast or check" state.
 */
rule Mock_ConfirmBallotPosting [role="Mock"]:
  let bb_entry = BBEntry_Ballot_Submission(~ec, %ts, signed_msg_submit_ballot) in
    [ DBB_State_ConfirmBallotPosting(~ec, ~va_id, ~cid, pseudo, bb_entry, %idx),
      !Mock_Submitted_Ballot(~ec, ~va_id, $V, ~ballot, cryptograms, ~r, signed_msg_submit_ballot),
      !VA_Eligible_Voter(~ec, ~va_id, pseudo, ~sk_voter, ~bs),
      !BB_Root(~ec, bbid, r_unused, rh_unused),
      !BB_Entry(bbid, bb_entry, tracker, %idx) ]
  --[ DBB_ConfirmBallotPosting_Trace(~ec, ~va_id, bb_entry, bbid, %idx),
      VA_BallotTracker_Trace(~ec, ~va_id, pseudo, ~sk_voter, ~bs, ~ballot, cryptograms, ~r, tracker) ]->
    [ !DBB_Posted_Ballot(pseudo, bb_entry, %idx),
      !VA_Submitted_Ballot(~ec, ~va_id, ~ballot, cryptograms, ~r, tracker),
      VA_State_CheckOrCast(~ec, ~va_id, $V, ~ballot, cryptograms, ~r, tracker) ]

/*
  This rule initializes the "clock" (really, just a monotonic counter
  used in posting messages to the bulletin board) for the DBB.
 */
rule Mock_DBBTimestamp [role="Mock"]:
    []
  --[]->
    [ DBB_Clock(%1) ]
