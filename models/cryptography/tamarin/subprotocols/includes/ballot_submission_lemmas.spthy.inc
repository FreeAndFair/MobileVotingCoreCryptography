/* Lemmas for voter authentication protocol. */

/* No Sources Lemma Necessary (Yet) */

/* Protocol Safety Lemmas */

/* TO DO (time permitting) */

/* Protocol Executability Lemmas

   Note that these are verified without reusing any lemmas that Tamarin
   cannot verify automatically or that do not have proof scripts.
*/

/*
  This lemma states that it is possible for a voting application to reach a
  state where a voter has submitted a ballot to the DBB.
 */
lemma Executability_BallotSubmission_Ballot_Submitted:
  exists-trace
  "
      Ex ec va_id V pseudo sk_voter ballot_style ballot cryptograms r #i.
        VA_PresentBallot_Trace(ec, va_id, V, pseudo, sk_voter, ballot_style, ballot, cryptograms, r)@i
  "

/*
  This lemma states that it is possible for the DBB to receive a submitted
  ballot.

  It is easy to prove interactively, but Tamarin has trouble proving it
  automatically, so a proof script is available.
 */
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, ifdef(<!STANDALONE!>, <!subprotocols/includes/proofs/BallotSubmission_Ballot_Received.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>), <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_Executability_BallotSubmission_Ballot_Received:
  exists-trace
  "
      Ex ec va_id msg #i.
        DBB_ReceiveSubmittedBallot_Trace(ec, va_id, msg)@i
  "
dnl Include the proof script, if one exists.
sinclude(PROOF_SCRIPT)dnl

/*
  This lemma states that it is possible for the DBB to append a submitted
  ballot to the bulletin board.

  It is easy to prove interactively, but Tamarin has trouble proving it
  automatically, so a proof script is available.
 */
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, ifdef(<!STANDALONE!>, <!subprotocols/includes/proofs/BallotSubmission_Ballot_Posted.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>), <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_Executability_BallotSubmission_Ballot_Posted:
  exists-trace
  "
      Ex ec va_id msg bbid %idx #i.
        DBB_ConfirmBallotPosting_Trace(ec, va_id, msg, bbid, %idx)@i
  "
dnl Include the proof script, if one exists.
sinclude(PROOF_SCRIPT)dnl

/*
  This lemma states that it is possible for a voting application to reach a
  state where a voter has received a tracker for a submitted ballot.

  It is easy to prove interactively, but Tamarin has trouble proving it
  automatically, so a proof script is available.
 */
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, ifdef(<!STANDALONE!>, <!subprotocols/includes/proofs/BallotSubmission_Tracker_Received.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>), <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_Executability_BallotSubmission_Tracker_Received:
  exists-trace
  "
      Ex ec va_id V pseudo sk_voter ballot_style ballot cryptograms r tracker #i.
        VA_BallotTracker_Trace(ec, va_id, V, pseudo, sk_voter, ballot_style, ballot, cryptograms, r, tracker)@i
  "
dnl Include the proof script, if one exists.
sinclude(PROOF_SCRIPT)dnl

/*
  This lemma states that it is possible for more than one voting application to
  reach a state where a voter has received a tracker for a submitted ballot in
  the same election, where the voters are different.

  It is easy to prove interactively, but Tamarin has trouble proving it
  automatically, so a proof script is available.
 */
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, ifdef(<!STANDALONE!>, <!subprotocols/includes/proofs/BallotSubmission_Multiple_Trackers_Received.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>), <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_Executability_BallotSubmission_Multiple_Trackers_Received:
  exists-trace
  "
      Ex ec va_id1 va_id2 V1 V2 pseudo1 pseudo2 sk_voter1 sk_voter2
         ballot_style1 ballot_style2 ballot1 ballot2
         cryptograms1 cryptograms2 r1 r2 tracker1 tracker2 #i1 #i2.
          VA_BallotTracker_Trace(ec, va_id1, V1, pseudo1, sk_voter1, ballot_style1, ballot1, cryptograms1, r1, tracker1)@i1
        &
          VA_BallotTracker_Trace(ec, va_id2, V2, pseudo2, sk_voter2, ballot_style2, ballot2, cryptograms2, r2, tracker2)@i2
        &
          not (#i1 = #i2)
        &
          not (va_id1 = va_id2)
        &
          not (pseudo1 = pseudo2)
  "
dnl Include the proof script, if one exists.
sinclude(PROOF_SCRIPT)dnl
