/* Lemmas for ballot check protocol. */

/* Sources */

/*
  This lemma says that incoming secure channel messages have
  to come from the secure channel rule. It is odd that this
  is necessary as that rule is the only source for the
  relevant fact.

  Tamarin cannot prove this lemma automatically, so a proof
  script is available.
 */
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, ifdef(<!STANDALONE!>, <!subprotocols/includes/proofs/Sources_BallotCheck.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>), <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_BallotCheck_Sources [sources]:
  "
      (
        All m1 m2 m3 m4 #i.
              IN_SECURE_RECEIVE(m1, m2, m3, m4)@i
          ==>
              Ex #j.
              (
                  SecureChannel_In(m1, m2, m3, m4)@j
                &
                  #j < #i
              )
      )
  "
dnl Include the proof script, if one exists.
sinclude(PROOF_SCRIPT)dnl

/* Protocol Safety Lemmas */

/*
  TO DO (time permitting)
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
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, ifdef(<!STANDALONE!>, <!subprotocols/includes/proofs/BallotCheck_Mock_Ballot_Submission.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>), <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_Executability_BallotCheck_Mock_Ballot_Submission:
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
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, ifdef(<!STANDALONE!>, <!subprotocols/includes/proofs/BallotCheck_Mock_Ballot_Append.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>), <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_Executability_BallotCheck_Mock_Ballot_Append:
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
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, ifdef(<!STANDALONE!>, <!subprotocols/includes/proofs/BallotCheck_Mock_Ballot_Confirm.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>), <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_Executability_BallotCheck_Mock_Ballot_Confirm:
  exists-trace
  "
    Ex ec va_id msg bbid %idx #i.
      DBB_ConfirmBallotPosting_Trace(ec, va_id, msg, bbid, %idx)@i
  "
dnl Include the proof script, if one exists.
sinclude(PROOF_SCRIPT)dnl

/*
  This lemma states that it is possible for the VA to initiate a
  ballot check.

  This lemma is straightforward to prove interactively, but Tamarin has
  trouble doing it automatically, so a proof script is available.
 */
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, ifdef(<!STANDALONE!>, <!subprotocols/includes/proofs/BallotCheck_VA_Initiate_Check.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>), <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_Executability_BallotCheck_VA_Initiate_Check:
  exists-trace
  "
    Ex ec va_id p b c r t #i.
      VA_CheckBallot_Trace(ec, va_id, p, b, c, r, t)@i
  "
dnl Include the proof script, if one exists.
sinclude(PROOF_SCRIPT)dnl

/*
  This lemma states that it is possible for the BCA to request the randomizers
  from the DBB.

  This lemma is straightforward to prove interactively, but Tamarin has
  trouble doing it automatically, so a proof script is available.
 */
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, ifdef(<!STANDALONE!>, <!subprotocols/includes/proofs/BallotCheck_BCA_Request_Randomizers.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>), <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_Executability_BallotCheck_BCA_Request_Randomizers:
  exists-trace
  "
    Ex ec bca_id t #i.
      BCA_InitiateBallotCheck_Trace(ec, bca_id, t)@i
  "
dnl Include the proof script, if one exists.
sinclude(PROOF_SCRIPT)dnl

/*
  This lemma states that it is possible for the DBB to receive the randomizer
  request from the BCA and forward it to the VA.

  This lemma is straightforward to prove interactively, but Tamarin has
  trouble doing it automatically, so a proof script is available.
 */
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, ifdef(<!STANDALONE!>, <!subprotocols/includes/proofs/BallotCheck_DBB_Request_Randomizers.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>), <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_Executability_BallotCheck_DBB_Request_Randomizers:
  exists-trace
  "
    Ex ec va_id bca_id m #i.
      DBB_ReceiveCheckRequest_Trace(ec, va_id, bca_id, m)@i
  "
dnl Include the proof script, if one exists.
sinclude(PROOF_SCRIPT)dnl

/*
  This lemma states that it is possible for the VA to receive the randomizer
  request from the DBB and respond to it.

  This lemma is straightforward to prove interactively, but Tamarin has
  trouble doing it automatically, so a proof script is available.
 */
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, ifdef(<!STANDALONE!>, <!subprotocols/includes/proofs/BallotCheck_VA_Send_Randomizers.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>), <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_Executability_BallotCheck_VA_Send_Randomizers:
  exists-trace
  "
    Ex ec va_id p b c r t pk #i.
      VA_RequestRandomizers_Trace(ec, va_id, p, b, c, r, t, pk)@i
  "
dnl Include the proof script, if one exists.
sinclude(PROOF_SCRIPT)dnl

/*
  This lemma states that it is possible for the DBB to receive the randomizers
  from the VA and forward them.

  This lemma is straightforward to prove interactively, but Tamarin has
  trouble doing it automatically, so a proof script is available.
 */
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, ifdef(<!STANDALONE!>, <!subprotocols/includes/proofs/BallotCheck_DBB_Forward_Randomizers.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>), <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_Executability_BallotCheck_DBB_Forward_Randomizers:
  exists-trace
  "
    Ex ec va_id bca_id m #i.
      DBB_ForwardRandomizers_Trace(ec, va_id, bca_id, m)@i
  "
dnl Include the proof script, if one exists.
sinclude(PROOF_SCRIPT)dnl

/*
  This lemma states that it is possible for the BCA to receive the randomizers
  and decrypt the ballot with them.

  This lemma is straightforward to prove interactively, but Tamarin has
  trouble doing it automatically, so a proof script is available.
 */
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, ifdef(<!STANDALONE!>, <!subprotocols/includes/proofs/BallotCheck_BCA_Receive_Randomizers.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>), <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_Executability_BallotCheck_BCA_Receive_Randomizers:
  exists-trace
  "
    Ex ec bca_id t r #i.
      BCA_ReceiveRandomizers_Trace(ec, bca_id, t, r)@i
  "
dnl Include the proof script, if one exists.
sinclude(PROOF_SCRIPT)dnl

/*
  This lemma states that it is possible for the VA to "OK" a ballot check.

  This lemma is straightforward to prove interactively, but Tamarin has
  trouble doing it automatically, so a proof script is available.
 */
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, ifdef(<!STANDALONE!>, <!subprotocols/includes/proofs/BallotCheck_VA_Result_OK.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>), <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_Executability_BallotCheck_VA_Result_OK:
  exists-trace
  "
    Ex ec va_id p b c r t pk #i.
      VA_CheckResult_OK_Trace(ec, va_id, p, b, c, r, t, pk)@i
  "
dnl Include the proof script, if one exists.
sinclude(PROOF_SCRIPT)dnl

/*
  This lemma states that it is possible for the VA to "Not OK" a ballot check.

  This lemma is straightforward to prove interactively, but Tamarin has
  trouble doing it automatically, so a proof script is available.
 */
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, ifdef(<!STANDALONE!>, <!subprotocols/includes/proofs/BallotCheck_VA_Result_Not_OK.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>), <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_Executability_BallotCheck_VA_Result_Not_OK:
  exists-trace
  "
    Ex ec va_id p b c r t pk #i.
      VA_CheckResult_NotOK_Trace(ec, va_id, p, b, c, r, t, pk)@i
  "
dnl Include the proof script, if one exists.
sinclude(PROOF_SCRIPT)dnl
