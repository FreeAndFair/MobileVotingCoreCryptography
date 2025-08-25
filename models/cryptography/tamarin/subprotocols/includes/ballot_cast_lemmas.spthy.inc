/* Lemmas for ballot cast protocol. */

dnl
dnl We only include the sources lemma in the standalone version, as
dnl the necessary sources lemma is different for composed versions.
dnl
ifdef(<!STANDALONE!>, <!
/* No Sources Lemma Necessary (Yet) */
!>, <!!>)
/* Protocol Safety Lemmas */

/*
  TO DO (time permitting)

  Obvious ones are:
    - no pseudonym ever gets more than one cast vote onto the bulletin board
    - no cast vote is unauthorized
 */

/* Protocol Executability Lemmas

   Note that these are verified without reusing any lemmas that Tamarin
   cannot verify automatically or that do not have proof scripts.
 */

/*
  This lemma states that it is possible for the DBB to receive a mock ballot.

  Tamarin can prove this lemma automatically, but it takes some time, so
  a proof script is available.
 */
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, ifdef(<!STANDALONE!>, <!subprotocols/includes/proofs/BallotCast_Mock_Ballot_Submission.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>), <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_Executability_BallotCast_Mock_Ballot_Submission:
  exists-trace
  "
    Ex ec va_id msg #i.
      DBB_ReceiveSubmittedBallot_Trace(ec, va_id, msg)@i
  "
dnl Include the proof script, if one exists.
sinclude(PROOF_SCRIPT)dnl

/*
  This lemma states that it is possible for the DBB to append a mock ballot.

  Tamarin can prove this lemma automatically, but it takes some time, so
  a proof script is available.
 */
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, ifdef(<!STANDALONE!>, <!subprotocols/includes/proofs/BallotCast_Mock_Ballot_Append.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>), <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_Executability_BallotCast_Mock_Ballot_Append:
  exists-trace
  "
    Ex ec va_id msg bbid %idx #i.
      DBB_AppendSubmittedBallot_Trace(ec, va_id, msg, bbid, %idx)@i
  "
dnl Include the proof script, if one exists.
sinclude(PROOF_SCRIPT)dnl

/*
  This lemma states that it is possible for the DBB to confirm a mock ballot
  was posted.

  This lemma is straightforward to prove interactively, but Tamarin has
  trouble doing it automatically, so a proof script is available.
 */
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, ifdef(<!STANDALONE!>, <!subprotocols/includes/proofs/BallotCast_Mock_Ballot_Confirm.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>), <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_Executability_BallotCast_Mock_Ballot_Confirm:
  exists-trace
  "
    Ex ec va_id msg bbid %idx #i.
      DBB_ConfirmBallotPosting_Trace(ec, va_id, msg, bbid, %idx)@i
  "
dnl Include the proof script, if one exists.
sinclude(PROOF_SCRIPT)dnl

/*
  This lemma states that it is possible for a voting application to reach
  a state where a voter has sent a valid cast request to the DBB.

  Tamarin can prove this lemma automatically, but it takes some time, so
  a proof script is available.
 */
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, ifdef(<!STANDALONE!>, <!subprotocols/includes/proofs/BallotCast_Cast_Requested.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>), <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_Executability_BallotCast_Cast_Requested:
  exists-trace
  "
    Ex ec va_id V pseudo sk_voter bs ballot cryptograms r tracker #i #j.
        VA_BallotTracker_Trace(ec, va_id, V, pseudo, sk_voter, bs, ballot, cryptograms, r, tracker)@i
      &
        VA_CastBallot_Trace(ec, va_id, pseudo, ballot, cryptograms, r, tracker)@j
  "
dnl Include the proof script, if one exists.
sinclude(PROOF_SCRIPT)dnl

/*
  This lemma states that it is possible for the DBB to receive a cast
  request.

  This lemma is straightforward to prove interactively, but Tamarin has
  trouble doing it automatically, so a proof script is available.
 */
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, ifdef(<!STANDALONE!>, <!subprotocols/includes/proofs/BallotCast_Cast_Received.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>), <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_Executability_BallotCast_Cast_Received:
  exists-trace
  "
    Ex ec va_id pseudo msg #i.
      DBB_ReceiveCastBallot_Trace(ec, va_id, pseudo, msg)@i
  "
dnl Include the proof script, if one exists.
sinclude(PROOF_SCRIPT)dnl

/*
  This lemma states that it is possible for the DBB to post a cast
  request to the bulletin board.

  This lemma is straightforward to prove interactively, but Tamarin has
  trouble doing it automatically, so a proof script is available.
 */
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, ifdef(<!STANDALONE!>, <!subprotocols/includes/proofs/BallotCast_Cast_Posted.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>), <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_Executability_BallotCast_Cast_Posted:
  exists-trace
  "
    Ex ec va_id bbe_a bbe_c bbid %idx_a %idx_c #i.
      DBB_ConfirmCastPosting_Trace(ec, va_id, bbe_a, bbe_c, bbid, %idx_a, %idx_c)@i
  "
dnl Include the proof script, if one exists.
sinclude(PROOF_SCRIPT)dnl

/*
  This lemma states that it is possible for the VA to receive a
  cast confirmation from the DBB.

  This lemma is straightforward to prove interactively, but Tamarin has
  trouble doing it automatically, so a proof script is available.
 */
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, ifdef(<!STANDALONE!>, <!subprotocols/includes/proofs/BallotCast_Cast_Confirm.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>), <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_Executability_BallotCast_Cast_Confirm:
  exists-trace
  "
    Ex ec va_id pseudo ballot cryptograms r sub_tracker cast_tracker #i.
      VA_CastConfirmation_Trace(ec, va_id, pseudo, ballot, cryptograms, r, sub_tracker, cast_tracker)@i
  "
dnl Include the proof script, if one exists.
sinclude(PROOF_SCRIPT)dnl

/*
  This lemma states that it is possible for more than one VA to receive
  a cast confirmation from the DBB, for different voters in the same election.

  This lemma is straightforward to prove interactively, but Tamarin has
  trouble doing it automatically, so a proof script is available.
 */
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, ifdef(<!STANDALONE!>, <!subprotocols/includes/proofs/BallotCast_Cast_Confirm_Multiple.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>), <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_Executability_BallotCast_Cast_Confirm_Multiple:
  exists-trace
  "
    Ex ec va_id1 va_id2 pseudo1 pseudo2 ballot1 ballot2
       cryptograms1 cryptograms2 r1 r2 sub_tracker1 sub_tracker2
       cast_tracker1 cast_tracker2 #i1 #i2.
        VA_CastConfirmation_Trace(ec, va_id1, pseudo1, ballot1, cryptograms1, r1, sub_tracker1, cast_tracker1)@i1
      &
        VA_CastConfirmation_Trace(ec, va_id2, pseudo2, ballot2, cryptograms2, r2, sub_tracker2, cast_tracker2)@i2
      &
        not (va_id1 = va_id2)
      &
        not (pseudo1 = pseudo2)
      &
        not (sub_tracker1 = sub_tracker2)
      &
        not (cast_tracker1 = cast_tracker2)
  "
dnl Include the proof script, if one exists.
sinclude(PROOF_SCRIPT)dnl
