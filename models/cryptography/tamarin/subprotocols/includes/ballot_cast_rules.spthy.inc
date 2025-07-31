/* Ballot Cast Subprotocol Rules */

/* Voter Application */

/*
  This rule is, effectively, the voter deciding to cast a ballot after their
  submission is confirmed and their tracker is received. A "parallel" rule
  exists in the ballot check subprotocol for the voter deciding to check.
 */
rule BallotCast_VA_Cast [role="VA"]:
  let pk_voter = pk(~sk_voter)
      msg_cast = Msg_VA_Cast_Ballot(~ec, pseudo, pk_voter, tracker)
      signed_msg_cast = <msg_cast, sign(msg_cast, '1', ~sk_voter)> in
    [ VA_State_CheckOrCast(~ec, ~va_id, $V, ~ballot, cryptograms, ~r, tracker),
      !VA_Eligible_Voter(~ec, ~va_id, pseudo, ~sk_voter, ~bs_unused),
      Fr(~cid) ]
  --[ VA_CastBallot_Trace(~ec, ~va_id, pseudo, ~ballot, cryptograms, ~r, tracker) ]->
    [ SecureSend(~cid, ~va_id, <~ec, 'DBB'>, signed_msg_cast),
      VA_State_BallotCastResponse(~ec, ~va_id, ~cid, pseudo, ~ballot, cryptograms, ~r, tracker) ]

/*
  This rule receives a response from the DBB saying that a ballot was
  successfully cast and the cast message was posted to the public bulletin
  board, and providing the cast tracker for verification. The BB persistent
  facts here allow us to check that the tracker actually coresponds to a
  bulletin board entry, and that that bulletin board entry contains the
  correct ballot cast information.

  Validation checks performed implicitly:
    - the bulletin board entries corresponding to the trackers we received
      actually exist (via pattern match)
    - the signed ballot cast message we submitted, and the signed ballot
      message we originally submitted, are both in the bulletin board entry
      corresponding to the tracker (via pattern match)
 */
rule BallotCast_VA_BallotCastResponse_CastConfirmation_Success [role="VA"]:
  let pk_voter = pk(~sk_voter)
      msg_cast_confirmation = Msg_DBB_Cast_Confirmation(~ec, sub_tracker, cast_tracker)
      msg_submit = Msg_VA_Submit_Ballot(~ec, pseudo, pk_voter, ballot_style, cryptograms)
      signed_msg_submit = <msg_submit, sign(msg_submit, '1', ~sk_voter)>
      msg_cast = Msg_VA_Cast_Ballot(~ec, pseudo, pk_voter, tracker)
      signed_msg_cast = <msg_cast, sign(msg_cast, '1', ~sk_voter)>
      cast_bb_entry = BBEntry_Ballot_Cast(~ec, %ts_cast, signed_msg_submit, signed_msg_cast) in
    [ VA_State_BallotCastResponse(~ec, ~va_id, ~cid, pseudo, ~ballot, cryptograms, ~r, sub_tracker),
      !VA_Eligible_Voter(~ec, ~va_id, pseudo, ~sk_voter, ballot_style),
      !BB_Root(~ec, ~bbid, r_unused, rh_unused),
      !BB_Entry(~bbid, sub_bb_entry, sub_tracker, %idx_sub),
      !BB_Entry(~bbid, cast_bb_entry, cast_tracker, %idx_cast),
      SecureReceive(~cid, <~ec, 'DBB'>, ~va_id, msg_cast_confirmation) ]
  --[ VA_CastConfirmation_Trace(~ec, ~va_id, pseudo, ~ballot, cryptograms, ~r, sub_tracker, cast_tracker) ]->
    [ !VA_Cast_Ballot(~ec, ~va_id, sub_tracker, cast_tracker),
      VA_State_VotingComplete(~ec, ~va_id, sub_tracker, cast_tracker) ]

/*
  This rule receives a response from the DBB saying that a ballot was
  cast on the public bulletin board, but the ballot in the bulletin board
  cast entry doesn't match the submitted ballot, indicating an error condition.
  If our secure channels remain secure, this should never happen.
 */
rule BallotCast_VA_BallotCastResponse_CastConfirmation_BallotMismatch [role="VA"]:
  let pk_voter = pk(~sk_voter)
      msg_cast_confirmation = Msg_DBB_Cast_Confirmation(~ec, sub_tracker, cast_tracker)
      msg_submit = Msg_VA_Submit_Ballot(~ec, pseudo, pk_voter, ballot_style, cryptograms)
      signed_msg_submit = <msg_submit, sign(msg_submit, '1', ~sk_voter)>
      msg_cast = Msg_VA_Cast_Ballot(~ec, pseudo, pk_voter, tracker)
      signed_msg_cast = <msg_cast, sign(msg_cast, '1', ~sk_voter)>
      cast_bb_entry = BBEntry_Ballot_Cast(~ec, %ts_cast, bb_entry_msg, signed_msg_cast) in
    [ VA_State_BallotCastResponse(~ec, ~va_id, ~cid, pseudo, ~ballot, cryptograms, ~r, sub_tracker),
      !VA_Eligible_Voter(~ec, ~va_id, pseudo, ~sk_voter, ballot_style),
      !BB_Root(~ec, ~bbid, r_unused, rh_unused),
      !BB_Entry(~bbid, sub_bb_entry, sub_tracker, %idx_sub),
      !BB_Entry(~bbid, cast_bb_entry, cast_tracker, %idx_cast),
      SecureReceive(~cid, <~ec, 'DBB'>, ~va_id, msg_cast_confirmation) ]
  --[ VA_CastConfirmation_BallotMismatch_Trace(~ec, ~va_id, pseudo, ~ballot, cryptograms, ~r, sub_tracker, cast_tracker),
      VA_Error_Trace(~ec, ~va_id),
      /* only execute if bb entry's submitted ballot doesn't match ours */
      Neq(bb_entry_msg, signed_msg_submit) ]->
    [ VA_State_CastError(~ec, ~va_id) /* UI presents an error */ ]

/*
  This rule receives a response from the DBB saying that a ballot was
  cast on the public bulletin board, but the cast request in the bulletin
  board cast entry doesn't match the submitted one, indicating an error
  condition. If our secure channels remain secure, this should never
  happen.
 */
rule BallotCast_VA_BallotCastResponse_CastConfirmation_CastReqMismatch [role="VA"]:
  let pk_voter = pk(~sk_voter)
      msg_cast_confirmation = Msg_DBB_Cast_Confirmation(~ec, maybe_sub_tracker, cast_tracker)
      msg_submit = Msg_VA_Submit_Ballot(~ec, pseudo, pk_voter, ballot_style, cryptograms)
      signed_msg_submit = <msg_submit, sign(msg_submit, '1', ~sk_voter)>
      msg_cast = Msg_VA_Cast_Ballot(~ec, pseudo, pk_voter, sub_tracker)
      signed_msg_cast = <msg_cast, sign(msg_cast, '1', ~sk_voter)>
      cast_bb_entry = BBEntry_Ballot_Cast(~ec, %ts_cast, signed_msg_submit, bb_entry_msg) in
    [ VA_State_BallotCastResponse(~ec, ~va_id, ~cid, pseudo, ~ballot, cryptograms, ~r, sub_tracker),
      !VA_Eligible_Voter(~ec, ~va_id, pseudo, ~sk_voter, ballot_style),
      !BB_Root(~ec, ~bbid, r_unused, rh_unused),
      !BB_Entry(~bbid, sub_bb_entry, sub_tracker, %idx_sub),
      !BB_Entry(~bbid, cast_bb_entry, cast_tracker, %idx_cast),
      SecureReceive(~cid, <~ec, 'DBB'>, ~va_id, msg_cast_confirmation) ]
  --[ VA_CastConfirmation_BallotMismatch_Trace(~ec, ~va_id, pseudo, ~ballot, cryptograms, ~r, sub_tracker, cast_tracker),
      VA_Error_Trace(~ec, ~va_id),
      /* only execute if bb entry's cast request doesn't match ours */
      Neq(bb_entry_msg, signed_msg_cast) ]->
    [ VA_State_CastError(~ec, ~va_id) /* UI presents an error */ ]

/*
  This rule receives a response from the DBB saying that a ballot was
  cast on the public bulletin board, but neither message in the bulletin
  board entry matches the ones we sent, indicating an error condition. If
  our secure channels remain secure, this should never happen.
 */
rule BallotCast_VA_BallotCastResponse_CastConfirmation_BothMismatch [role="VA"]:
  let pk_voter = pk(~sk_voter)
      msg_cast_confirmation = Msg_DBB_Cast_Confirmation(~ec, maybe_sub_tracker, cast_tracker)
      msg_submit = Msg_VA_Submit_Ballot(~ec, pseudo, pk_voter, ballot_style, cryptograms)
      signed_msg_submit = <msg_submit, sign(msg_submit, '1', ~sk_voter)>
      msg_cast = Msg_VA_Cast_Ballot(~ec, pseudo, pk_voter, sub_tracker)
      signed_msg_cast = <msg_cast, sign(msg_cast, '1', ~sk_voter)>
      cast_bb_entry = BBEntry_Ballot_Cast(~ec, %ts_cast, bb_entry_submit_msg, bb_entry_cast_msg) in
    [ VA_State_BallotCastResponse(~ec, ~va_id, ~cid, pseudo, ~ballot, cryptograms, ~r, sub_tracker),
      !VA_Eligible_Voter(~ec, ~va_id, pseudo, ~sk_voter, ballot_style),
      !BB_Root(~ec, ~bbid, r_unused, rh_unused),
      !BB_Entry(~bbid, sub_bb_entry, sub_tracker, %idx_sub),
      !BB_Entry(~bbid, cast_bb_entry, cast_tracker, %idx_cast),
      SecureReceive(~cid, <~ec, 'DBB'>, ~va_id, msg_cast_confirmation) ]
  --[ VA_CastConfirmation_BothMismatch_Trace(~ec, ~va_id, pseudo, ~ballot, cryptograms, ~r, sub_tracker, cast_tracker),
      VA_Error_Trace(~ec, ~va_id),
      /* only execute if neither message matches ours */
      Neq(bb_entry_submit_msg, signed_msg_submit),
      Neq(bb_entry_cast_msg, signed_msg_cast) ]->
    [ VA_State_CastError(~ec, ~va_id) /* UI presents an error */ ]

/*
  This rule receives a response from the DBB saying that a ballot was
  cast on the public bulletin board, but there is no matching bulletin
  board entry for the the received cast request tracker, indicating an
  error condition. If our secure channels remain secure, this should
  never happen.
 */
rule BallotCast_VA_BallotCastResponse_CastConfirmation_NoBBEntryForCast [role="VA"]:
  let msg_cast_confirmation = Msg_DBB_Cast_Confirmation(~ec, sub_tracker, cast_tracker) in
    [ VA_State_BallotCastResponse(~ec, ~va_id, ~cid, pseudo, ~ballot, cryptograms, ~r, sub_tracker),
      !VA_Eligible_Voter(~ec, ~va_id, pseudo, ~sk_voter, ballot_style),
      !BB_Root(~ec, ~bbid, r_unused, rh_unused),
      !BB_Entry(~bbid, sub_bb_entry, sub_tracker, %idx_sub),
      SecureReceive(~cid, <~ec, 'DBB'>, ~va_id, msg_cast_confirmation) ]
  --[ VA_CastConfirmation_NoBBEntryForCast_Trace(~ec, ~va_id, pseudo, ~ballot, cryptograms, ~r, sub_tracker, cast_tracker),
      VA_Error_Trace(~ec, ~va_id),
      /* only execute if cast bb entry doesn't exist */
      NoBBEntryWithHash(~bbid, cast_tracker) ]->
    [ VA_State_CastError(~ec, ~va_id) /* UI presents an error */ ]

/*
  This rule receives a response from the DBB saying that a ballot was
  cast on the public bulletin board, but there is no matching bulletin
  board entry for the the received submit request tracker, indicating an
  error condition. If our secure channels remain secure, this should
  never happen.
 */
rule BallotCast_VA_BallotCastResponse_CastConfirmation_NoBBEntryForSubmit [role="VA"]:
  let msg_cast_confirmation = Msg_DBB_Cast_Confirmation(~ec, sub_tracker, cast_tracker) in
    [ VA_State_BallotCastResponse(~ec, ~va_id, ~cid, pseudo, ~ballot, cryptograms, ~r, sub_tracker),
      !VA_Eligible_Voter(~ec, ~va_id, pseudo, ~sk_voter, ballot_style),
      !BB_Root(~ec, ~bbid, r_unused, rh_unused),
      !BB_Entry(~bbid, cast_bb_entry, cast_tracker, %idx_cast),
      SecureReceive(~cid, <~ec, 'DBB'>, ~va_id, msg_cast_confirmation) ]
  --[ VA_CastConfirmation_NoBBEntryForSubmit_Trace(~ec, ~va_id, pseudo, ~ballot, cryptograms, ~r, sub_tracker, cast_tracker),
      VA_Error_Trace(~ec, ~va_id),
      /* only execute if submit bb entry doesn't exist */
      NoBBEntryWithHash(~bbid, sub_tracker) ]->
    [ VA_State_CastError(~ec, ~va_id) /* UI presents an error */ ]

/*
  This rule receives a response from the DBB saying that a ballot was
  cast on the public bulletin board, but there is no matching bulletin
  board entry for the either of the received trackers, indicating an
  error condition. If our secure channels remain secure, this should
  never happen.
 */
rule BallotCast_VA_BallotCastResponse_CastConfirmation_NoBBEntryForEither [role="VA"]:
  let msg_cast_confirmation = Msg_DBB_Cast_Confirmation(~ec, sub_tracker, cast_tracker) in
    [ VA_State_BallotCastResponse(~ec, ~va_id, ~cid, pseudo, ~ballot, cryptograms, ~r, sub_tracker),
      !VA_Eligible_Voter(~ec, ~va_id, pseudo, ~sk_voter, ballot_style),
      !BB_Root(~ec, ~bbid, r_unused, rh_unused),
      SecureReceive(~cid, <~ec, 'DBB'>, ~va_id, msg_cast_confirmation) ]
  --[ VA_CastConfirmation_NoBBEntryForSubmit_Trace(~ec, ~va_id, pseudo, ~ballot, cryptograms, ~r, sub_tracker, cast_tracker),
      VA_Error_Trace(~ec, ~va_id),
      /* only execute if neither bb entry exists */
      NoBBEntryWithHash(~bbid, sub_tracker),
      NoBBEntryWithHash(~bbid, cast_tracker) ]->
    [ VA_State_CastError(~ec, ~va_id) /* UI presents an error */ ]

/*
  This rule receives a response from the DBB saying that it was unable to
  post a cast ballot to the bulletin board for some reason. In this
  model, the only reasons this should be able to happen are if the signature
  on the ballot cast doesn't verify, if the voter public key used
  for the ballot cast is not authorized to cast a ballot because it
  was superceded by a later authentication with a different VA, or if the
  tracker in the cast request refers to a nonexistent or non-matching (e.g.,
  submitted by a different voter) message on the bulletin board.
 */
rule BallotSubmission_VA_BalloCastResponse_Error [role="VA"]:
  let msg_cast_error = Msg_DBB_Cast_Error(~ec, error) in
    [ VA_State_BallotCastResponse(~ec, ~va_id, ~cid, pseudo, ~ballot, cryptograms, ~r, sub_tracker),
      SecureReceive(~cid, <~ec, 'DBB'>, ~va_id, msg_cast_error) ]
  --[ VA_BallotTracker_Error_Trace(~ec, ~va_id, sub_tracker, error),
      VA_Error_Trace(~ec, ~va_id) ]->
    [ VA_State_CastError(~ec, ~va_id) /* UI presents an error */ ]

/* Digital Ballot Box */

/*
  This rule receives a cast request from an authorized voter
  successfully, then transitions to a state where it appends
  it to the bulletin board. Note that the fact that triggers
  appending to the bulletin board is persistent because of the
  way the bulletin board works in Tamarin.

  Validation checks performed explicitly (via restrictions):
    - the signature on the submitted cast message is valid
    - the voter's public key matches the one on the ballot
      that is to be cast
    - the voter's public key is currently authorized to vote (has
      not been superceded by another key/another authentication)
    - the voter has not previously cast a ballot, using any key

  Validation checks performed implicitly:
    - the voter's public key was at some point authorized to vote
      (via pattern match)
    - the ballot that is to be cast exists on the bulletin board
      (via pattern match)
    - the ballot that is to be cast is the most recent one on the
      bulletin board for the voter
 */
rule BallotCast_DBB_ReceiveCastBallot [role="DBB"]:
  let msg_cast = Msg_VA_Cast_Ballot(~ec, pseudo, pk_voter_cast, tracker)
      signed_msg_cast = <msg_cast, sig_cast>
      msg_submit = Msg_VA_Submit_Ballot(~ec, pseudo, pk_voter_submit, ballot_style, cryptograms)
      signed_msg_submit = <msg_submit, sig_submit>
      sub_bb_entry = BBEntry_Ballot_Submission(~ec, %ts_sub, signed_msg_submit) in
    [ !DBB_Voter_Authorized(~ec, signed_msg_auth, pseudo, pk_voter_cast, ballot_style, %auth_idx),
      !BB_Root(~ec, ~bbid, r_unused, rh_unused),
      !BB_Entry(~bbid, sub_bb_entry, tracker, %ballot_idx),
      SecureReceive(~cid, ~va_id, <~ec, 'DBB'>, signed_msg_cast) ]
  --[ DBB_ReceiveCastBallot_Trace(~ec, ~va_id, pseudo, msg_cast),
      NoPreviousCast(pseudo),
      MostRecentAuthorization(~ec, pseudo, pk_voter_cast, %auth_idx),
      MostRecentBallot(~bbid, pseudo, %ballot_idx),
      SignatureVerified(sig_cast, e1_sig(sig_cast), pk(e3_sig(sig_cast)), msg_cast,
                        pk_voter_cast, true), /* valid signature */
      /* we don't verify the signature of the submitted ballot because
         it's already on the bulletin board, but we do check that it has
         the same public key */
      Eq(pk_voter_cast, pk_voter_submit) ]->
    [ !DBB_Cast_Ballot(~ec, ~va_id, ~cid, pseudo, pk_voter_cast, tracker, signed_msg_submit, signed_msg_cast) ]

/*
  This rule handles the error csae where a submitted cast request
  fails its signature check.
 */
rule BallotCast_DBB_ReceiveCastBallot_FailedSignature [role="DBB"]:
  let msg_error = Msg_DBB_Cast_Error(~ec, 'failed signature')
      msg_cast = Msg_VA_Cast_Ballot(~ec, pseudo, pk_voter_cast, tracker)
      signed_msg_cast = <msg_cast, sig_cast> in
    [ !DBB_Voter_Authorized(~ec, signed_msg_auth, pseudo, pk_voter, ballot_style, %idx),
      SecureReceive(~cid, ~va_id, <~ec, 'DBB'>, signed_msg_cast) ]
  --[ DBB_ReceiveCastBallot_FailedSignature_Trace(~ec, ~va_id, msg_cast),
      DBB_Cast_Error_Trace(~ec, ~va_id),
      SignatureVerified(sig_cast, e1_sig(sig_cast), pk(e3_sig(sig_cast)), msg_cast,
                        pk_voter_cast, false), /* invalid signature */ ]->
    [ SecureSend(~cid, <~ec, 'DBB'>, ~va_id, msg_error) ]

/*
  This rule handles the error case where the keys on the cast and submission
  messages don't match.
 */
rule BallotCast_DBB_ReceiveCastBallot_MismatchedKeys [role="DBB"]:
  let msg_error = Msg_DBB_Cast_Error(~ec, 'submission and cast keys do not match')
      msg_cast = Msg_VA_Cast_Ballot(~ec, pseudo, pk_voter_cast, tracker)
      signed_msg_cast = <msg_cast, sig_cast>
      msg_submit = Msg_VA_Submit_Ballot(~ec, pseudo, pk_voter_submit, ballot_style, cryptograms)
      signed_msg_submit = <msg_submit, sig_submit>
      sub_bb_entry = BBEntry_Ballot_Submission(~ec, %ts_sub, signed_msg_submit) in
    [ !DBB_Voter_Authorized(~ec, signed_msg_auth, pseudo, pk_voter_cast, ballot_style, %auth_idx),
      !BB_Root(~ec, ~bbid, r_unused, rh_unused),
      !BB_Entry(~bbid, sub_bb_entry, tracker, %ballot_idx),
      SecureReceive(~cid, ~va_id, <~ec, 'DBB'>, signed_msg_cast) ]
  --[ DBB_ReceiveCastBallot_MismatchedKeys_Trace(~ec, ~va_id, pseudo, msg_cast),
      NoPreviousCast(pseudo),
      MostRecentAuthorization(~ec, pseudo, pk_voter_cast, %auth_idx),
      MostRecentBallot(~bbid, pseudo, %ballot_idx),
      SignatureVerified(sig_cast, e1_sig(sig_cast), pk(e3_sig(sig_cast)), msg_cast,
                        pk_voter_cast, true), /* valid signature */
      /* the error condition is that these public keys don't match */
      Neq(pk_voter_cast, pk_voter_submit) ]->
    [ SecureSend(~cid, <~ec, 'DBB'>, ~va_id, msg_error) ]

/*
  This rule handles the error case when the public key in the cast
  request is unauthorized.
 */
rule BallotCast_DBB_ReceiveCastBallot_UnauthorizedVoter [role="DBB"]:
  let msg_error = Msg_DBB_Cast_Error(~ec, 'unauthorized voter')
      msg_cast = Msg_VA_Cast_Ballot(~ec, pseudo, pk_voter_cast, tracker)
      signed_msg_cast = <msg_cast, sig_cast> in
    [ SecureReceive(~cid, ~va_id, <~ec, 'DBB'>, signed_msg_cast) ]
  --[ DBB_ReceiveCastBallot_Unauthorized_Trace(~ec, ~va_id, msg_cast),
      DBB_Cast_Error_Trace(~ec, ~va_id),
      Unauthorized(~ec, pseudo, pk_voter_cast) ]->
    [ SecureSend(~cid, <~ec, 'DBB'>, ~va_id, msg_error) ]

/*
  This rule handles the error case when the pseudonym has previously
  cast a ballot (we simply use the existing persistent fact).
 */
rule BallotCast_DBB_ReceiveCastBallot_PreviouslyCast [role="DBB"]:
  let msg_error = Msg_DBB_Cast_Error(~ec, 'voter previously cast a ballot')
      msg_cast = Msg_VA_Cast_Ballot(~ec, pseudo, pk_voter_cast, tracker)
      signed_msg_cast = <msg_cast, sig_cast> in
    [ !DBB_Cast_Ballot(~some_ec, ~some_va_id, ~some_cid, pseudo, some_pk, some_tracker, some_msg_submit, some_msg_cast),
      SecureReceive(~cid, ~va_id, <~ec, 'DBB'>, signed_msg_cast) ]
  --[ DBB_ReceiveCastBallot_PreviouslyCast_Trace(~ec, ~va_id, msg_cast),
      DBB_Cast_Error_Trace(~ec, ~va_id) ]->
    [ SecureSend(~cid, <~ec, 'DBB'>, ~va_id, msg_error) ]

/*
  This rule handles the error case when the bulletin board entry for
  the submission that the cast request refers to does not exist.
 */
rule BallotCast_DBB_ReceiveCastBallot_NonexistentSubmission [role="DBB"]:
  let msg_error = Msg_DBB_Cast_Error(~ec, 'voter attempted to cast nonexistent ballot')
      msg_cast = Msg_VA_Cast_Ballot(~ec, pseudo, pk_voter_cast, tracker)
      signed_msg_cast = <msg_cast, sig_cast> in
    [ !BB_Root(~ec, ~bbid, r_unused, rh_unused),
      SecureReceive(~cid, ~va_id, <~ec, 'DBB'>, signed_msg_cast) ]
  --[ DBB_ReceiveCastBallot_NonexistentSubmission_Trace(~ec, ~va_id, msg_cast),
      /* need this restriction to avoid conflict with the previous rule */
      NoPreviousCast(pseudo),
      NoBBEntryWithHash(~bbid, tracker),
      DBB_Cast_Error_Trace(~ec, ~va_id) ]->
    [ SecureSend(~cid, <~ec, 'DBB'>, ~va_id, msg_error) ]

/*
  This rule publishes the authorization message corresponding to a
  successfully cast ballot's public key, and the cast ballot message,
  to the bulletin board as consecutive items. It needs to be a
  separate rule (as does the one that checks to make sure they
  were published) becuase of the way the bulletin board works in
  Tamarin (we have to pick some element of the bulletin board to append
  to and if it isn't the last one, the append will fail). This rule is
  restricted to un only when the messages have not actually been
  successfully appended, and to run at most once for each board index
  to append to.

  Note that we bump the clock by 2 here, because we use one timestamp
  for each message.
 */
rule BallotCast_DBB_AppendCastBallot [role="DBB"]:
  let bb_entry_auth = BBEntry_Voter_Authorization(~ec, %ts, signed_msg_auth)
      bb_entry_cast = BBEntry_Ballot_Cast(~ec, %ts %+ %1, signed_msg_submit, signed_msg_cast) in
    [ !DBB_Cast_Ballot(~ec, ~va_id, ~cid, pseudo, pk_voter, tracker, signed_msg_submit, signed_msg_cast),
      !DBB_Voter_Authorized(~ec, signed_msg_auth, pseudo, pk_voter, ballot_style, %idx),
      DBB_Clock(%ts),
      !BB_Root(~ec, ~bbid, r_unused, rh_unused),
      !BB_Entry(~bbid, e_unused, eh_unused, %idx) ]
  --[ DBB_AppendCastBallot_Trace(~ec, ~va_id, signed_msg_auth, signed_msg_submit, signed_msg_cast, ~bbid, %idx),
      Unique(<'DBB_AppendCastBallot', signed_msg_auth, signed_msg_submit, signed_msg_cast, %idx>),
      AuthorizationNotOnB(~bbid, signed_msg_auth),
      CastNotOnBB(~bbid, signed_msg_submit, signed_msg_cast) ]->
    [ BB_Append_Request(~bbid, bb_entry_auth, %idx),
      BB_Append_Request(~bbid, bb_entry_cast, %idx %+ %1),
      DBB_Clock(%ts %+ %1 %+ %1),
      DBB_State_ConfirmCastPosting(~ec, ~va_id, ~cid, pseudo, tracker, bb_entry_auth, bb_entry_cast, %idx %+ %1) ]

/*
  This rule waits for a cast ballot (and its authorization) to be
  successfully posted to the bulletin board, then sends an appropriate
  message back to the VA.

  Note that this _must_ succeed for some index, for any successful
  ballot cast, because there is no way in Tamarin for the bulletin board
  to fail.
 */
rule BallotCast_DBB_ConfirmCastPosting [role="DBB"]:
  let msg_cast_confirmation = Msg_DBB_Cast_Confirmation(~ec, sub_tracker, cast_tracker)
      cast_idx = %auth_idx %+ %1 in
    [ DBB_State_ConfirmCastPosting(~ec, ~va_id, ~cid, pseudo, sub_tracker, bb_entry_auth, bb_entry_cast, %auth_idx),
      !BB_Root(~ec, ~bbid, r_unused, rh_unused),
      !BB_Entry(~bbid, bb_entry_auth, auth_tracker_unused, %auth_idx),
      !BB_Entry(~bbid, bb_entry_cast, cast_tracker, cast_idx) ]
  --[ DBB_ConfirmCastPosting_Trace(~ec, ~va_id, bb_entry_auth, bb_entry_cast, ~bbid, %auth_idx, cast_idx) ]->
    [ !DBB_Posted_Authorization(pseudo, bb_entry_auth, %auth_idx),
      !DBB_Posted_Cast(pseudo, bb_entry_cast, cast_idx),
      SecureSend(~cid, <~ec, 'DBB'>, ~va_id, msg_cast_confirmation) ]
