/* Lemmas for election key generation protocol. */

/* Protocol Safety Lemmas */

/*
  This lemma states that the only valid trustee names are the
  <!!>TRUSTEE_COUNT<!!> that start with 'Trustee'.
 */
lemma Safety_ElectionKeyGeneration_Valid_Trustee_Names [reuse]:
  "
    All tn pk_sign pk_encrypt #i.
          TAS_Trustee_Trace(tn, pk_sign, pk_encrypt)@i
      ==>
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!            tn = 'Trustee<!!>TN<!!>'<!!>ifelse(eval(TN < TRUSTEE_COUNT), eval(1), <!
          |
!>)!>)
  "

/*
  This lemma states that each trustee name only has one associated
  identity.
 */
lemma Safety_ElectionKeyGeneration_Only_One_Identity_Per_Trustee [reuse]:
  "
    All tr sk1 sk2 pk1 pk2 #i1 #i2.
            TAS_Trustee_Trace(tr, sk1, pk1)@i1
          &
            TAS_Trustee_Trace(tr, sk2, pk2)@i2
      ==>
          sk1 = sk2 & pk1 = pk2
  "

/*
  This lemma states that all trustees and the TAS agree on the election
  setup (it is redundant with a lemma from the election setup protocol
  but is provided here for Tamarin's reuse).
 */
lemma Safety_ElectionKeyGeneration_UniqueElectionSetup [reuse]:
  "
    All tr es1 es2 es3 #i1 #i2 #j.
          TAS_ElectionSetup_Complete_Trace(es1)@i1
        &
          TAS_ElectionSetup_Complete_Trace(es2)@i2
        &
          Trustee_ElectionSetup_Trace(tr, es3)@j
      ==>
          es1 = es2 & es1 = es3 & es2 = es3
  "

/*
  This lemma states that all TAS BB messages, except the root message,
  come from one of the <!!>TRUSTEE_COUNT<!!> trustees (or are injected
  with their signature).
 */
lemma Safety_ElectionKeyGeneration_TAS_BB_Message_Sources [reuse]:
  "
    All sd sl msg sig %idx #i.
            TAS_BBEntry_Trace(sd, sl, msg, sig, %idx)@i
      ==>
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!            sd = 'Trustee<!!>TN<!!>'<!!>ifelse(eval(TN < TRUSTEE_COUNT), eval(1), <!
          |
!>)!>)
  "

/*
  This lemma states that no two TAS bulletin board messages have the
  same index.
 */
lemma Safety_ElectionKeyGeneration_TAS_BB_No_Duplicate_Indices [reuse]:
  "
    All tr1 tr2 mt1 mt2 msg1 msg2 sig1 sig2 %idx #i1 #i2.
            TAS_BBEntry_Trace(tr1, mt1, msg1, sig1, %idx)@i1
          &
            TAS_BBEntry_Trace(tr2, mt2, msg2, sig2, %idx)@i2
      ==>
          tr1 = tr2 & mt1 = mt2 & msg1 = msg2 & sig1 = sig2 & #i1 = #i2
  "

/*
  This lemma states that all BB messages on the TAS bulletin board
  have distinct event times.
 */
lemma Safety_ElectionKeyGeneration_TAS_BB_Distinct_Timestamps [reuse]:
  "
    All sd1 sd2 sl1 sl2 msg1 msg2 sig1 sig2 %idx1 %idx2 #i1 #i2.
            TAS_BBEntry_Trace(sd1, sl1, msg1, sig1, %idx1)@i1
          &
            TAS_BBEntry_Trace(sd2, sl2, msg2, sig2, %idx2)@i2
          &
            not (%idx1 = %idx2)
          &
            #i1 = #i2
      ==>
          F
  "

/*
  This lemma states that there are no missing indices on the TAS
  bulletin board; it does this indirectly, by saying that for any
  pair of messages whose indices differ by more than one, there
  is a message with an index in between.

  Tamarin is unable to prove this automatically, despite it being
  obviously true by construction (there is only one rule that adds
  bulletin board messages for each bulletin board, it always
  increments the index by exactly one, and there is only ever at
  most one linear fact instance for each index for each board).
  It may be proven interactively in the future.
 */
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, <!subprotocols/includes/proofs/ElectionKeyGeneration_TAS_BB_All_Indices_<!!>TRUSTEE_COUNT<!!>.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_Safety_ElectionKeyGeneration_TAS_BB_All_Indices [use_induction]:
  "
    All sd1 sd2 sl1 sl2 msg1 msg2 sig1 sig2 %idx1 %idx2 #i1 #i2.
            TAS_BBEntry_Trace(sd1, sl1, msg1, sig1, %idx1)@i1
          &
            TAS_BBEntry_Trace(sd2, sl2, msg2, sig2, %idx2)@i2
          &
            %idx1 %+ %1 << %idx2
      ==>
          (
            Ex sd3 sl3 msg3 sig3 %idx3 #i3.
                TAS_BBEntry_Trace(sd3, sl3, msg3, sig3, %idx3)@i3
              &
                %idx1 << %idx3
              &
                %idx3 << %idx2
          )
  "
dnl Include the proof script, if one exists.
sinclude(PROOF_SCRIPT)dnl

/*
  This lemma states that all BB messages occur in chronological order on
  the global bulletin board.

  Tamarin is unable to prove this automatically, despite it being
  obviously true by construction for the same reasons as the previous
  lemma. It may be proven interactively in the future.
 */
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, <!subprotocols/includes/proofs/ElectionKeyGeneration_TAS_BB_Chronological_Order_<!!>TRUSTEE_COUNT<!!>.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_Safety_ElectionKeyGeneration_TAS_BB_Chronological_Order [use_induction]:
  "
    All sd1 sd2 sl1 sl2 msg1 msg2 sig1 sig2 %idx1 %idx2 #i1 #i2.
            TAS_BBEntry_Trace(sd1, sl1, msg1, sig1, %idx1)@i1
          &
            TAS_BBEntry_Trace(sd2, sl2, msg2, sig2, %idx2)@i2
          &
            %idx1 << %idx2
          &
            #i2 < #i1
      ==>
          F
  "
dnl Include the proof script, if one exists.
sinclude(PROOF_SCRIPT)dnl

/*
  This lemma states that every entry on the TAS bulletin board, other
  than the root message, is from a registered trustee and has a
  valid signature.
 */
lemma Safety_ElectionKeyGeneration_TAS_BB_Message_Validity [reuse]:
  "
    All tr mt msg sig %idx #i.
            TAS_BBEntry_Trace(tr, mt, msg, sig, %idx)@i
      ==>
          (Ex pk_sign pk_encrypt param sk #j #k.
              TAS_Trustee_Trace(tr, pk_sign, pk_encrypt)@j
            &
              HonestSignatureKey(pk_sign)@k
            &
              pk(sk) = pk_sign
            &
              sig = sign(msg, param, sk)
          )
  "

/*
  This lemma states that there is at most one message in each slot
  from each trustee on the TAS bulletin board, unless one was injected.
 */
lemma Safety_ElectionKeyGeneration_TAS_BB_No_Duplicate_Slots [reuse]:
  "
    All sd sl msg1 msg2 sig1 sig2 %idx1 %idx2 #i1 #i2.
            TAS_BBEntry_Trace(sd, sl, msg1, sig1, %idx1)@i1
          &
            TAS_BBEntry_Trace(sd, sl, msg2, sig2, %idx2)@i2
      ==>
            (msg1 = msg2 & sig1 = sig2 & %idx1 = %idx2 & #i1 = #i2)
          |
            (Ex #j. InjectTrusteeMsg(sd, msg1, sig1)@j)
          |
            (Ex #j. InjectTrusteeMsg(sd, msg2, sig2)@j)
  "

/*
  This lemma states that all trustee BB messages, except the root message,
  come from one of the <!!>TRUSTEE_COUNT<!!> trustees (or are injected
  with their signature).
 */
lemma Safety_ElectionKeyGeneration_Trustee_BBs_Message_Sources [reuse]:
  "
    All tr sd sl msg sig %idx #i.
            Trustee_BBEntry_Trace(tr, sd, sl, msg, sig, %idx)@i
      ==>
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!            sd = 'Trustee<!!>TN<!!>'<!!>ifelse(eval(TN < TRUSTEE_COUNT), eval(1), <!
          |
!>)!>)
  "

/*
  This lemma states that each trustee's local bulletin board
  follows the TAS bulletin board; i.e., it has exactly the same
  sequence of messages up until the trustee bulletin board ends,
  which may be before the TAS bulletin board ends depending on
  the legality of the message sequence on the TAS bulletin board
  and whether the trustee bulletin board has caught up.
 */
lemma Safety_ElectionKeyGeneration_Trustee_BBs_Follow_TAS [reuse]:
  "
    All tr sd1 sd2 sl1 sl2 msg1 msg2 sig1 sig2 %idx #i1 #i2.
            Trustee_BBEntry_Trace(tr, sd1, sl1, msg1, sig1, %idx)@i1
          &
            TAS_BBEntry_Trace(sd2, sl2, msg2, sig2, %idx)@i2
      ==>
          sd1 = sd2 & sl1 = sl2 & msg1 = msg2 & sig1 = sig2
  "

/*
  This lemma states that all the trustee local bulletin boards have
  the same message sequence, as far as they all go (it is effectively
  another way of stating that all the trustee BBs follow the TAS BB),
  but it may help Tamarin to state it separately.
 */
lemma Safety_ElectionKeyGeneration_Trustee_BBs_Match [reuse]:
  "
    All tr1 tr2 sd1 sd2 sl1 sl2 msg1 msg2 sig1 sig2 %idx #i1 #i2.
            Trustee_BBEntry_Trace(tr1, sd1, sl1, msg1, sig1, %idx)@i1
          &
            Trustee_BBEntry_Trace(tr2, sd2, sl2, msg2, sig2, %idx)@i2
      ==>
          sd1 = sd2 & sl1 = sl2 & msg1 = msg2 & sig1 = sig2
  "

/*
  This lemma states that there is at most one message in each slot
  from each trustee on each trustee's local bulletin board.
 */
lemma Safety_ElectionKeyGeneration_Trustee_BBs_No_Duplicate_Slots [reuse]:
  "
    All tr sd sl msg1 msg2 sig1 sig2 %idx1 %idx2 #i1 #i2.
            Trustee_BBEntry_Trace(tr, sd, sl, msg1, sig1, %idx1)@i1
          &
            Trustee_BBEntry_Trace(tr, sd, sl, msg2, sig2, %idx2)@i2
      ==>
          msg1 = msg2 & sig1 = sig2 & %idx1 = %idx2 & #i1 = #i2
  "

/*
  This lemma states that all BB messages on trustee bulletin boards
  have distinct event times.
 */
lemma Safety_ElectionKeyGeneration_Trustee_BBs_Distinct_Timestamps [reuse]:
  "
    All tr sd1 sd2 sl1 sl2 msg1 msg2 sig1 sig2 %idx1 %idx2 #i1 #i2.
            Trustee_BBEntry_Trace(tr, sd1, sl1, msg1, sig1, %idx1)@i1
          &
            Trustee_BBEntry_Trace(tr, sd2, sl2, msg2, sig2, %idx2)@i2
          &
            not (%idx1 = %idx2)
          &
            #i1 = #i2
      ==>
          F
  "

/*
  This lemma states that there are no missing indices on the trustee
  bulletin boards; it does this indirectly, by saying that for any
  pair of messages whose indices differ by more than one, there
  is a message with an index in between.

  Tamarin is unable to prove this automatically, despite it being
  obviously true by construction (there is only one rule that adds
  bulletin board messages for each bulletin board, it always
  increments the index by exactly one, and there is only ever at
  most one linear fact instance for each index for each board).
  It may be proven interactively in the future.
 */
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, <!subprotocols/includes/proofs/ElectionKeyGeneration_Trustee_BBs_All_Indices_<!!>TRUSTEE_COUNT<!!>.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_Safety_ElectionKeyGeneration_Trustee_BBs_All_Indices [use_induction]:
  "
    All tr sd1 sd2 sl1 sl2 msg1 msg2 sig1 sig2 %idx1 %idx2 #i1 #i2.
            Trustee_BBEntry_Trace(tr, sd1, sl1, msg1, sig1, %idx1)@i1
          &
            Trustee_BBEntry_Trace(tr, sd2, sl2, msg2, sig2, %idx2)@i2
          &
            %idx1 %+ %1 << %idx2
      ==>
          (
            Ex sd3 sl3 msg3 sig3 %idx3 #i3.
                Trustee_BBEntry_Trace(tr, sd3, sl3, msg3, sig3, %idx3)@i3
              &
                %idx1 << %idx3
              &
                %idx3 << %idx2
          )
  "
dnl Include the proof script, if one exists.
sinclude(PROOF_SCRIPT)dnl

/*
  This lemma states that all BB messages occur in chronological order on
  all trustee bulletin boards.

  Tamarin is unable to prove this automatically, despite it being
  obviously true by construction for the same reasons as the previous
  lemma. It may be proven interactively in the future.
 */
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, <!subprotocols/includes/proofs/ElectionKeyGeneration_Trustee_BBs_Chronological_Order_<!!>TRUSTEE_COUNT<!!>.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_Safety_ElectionKeyGeneration_Trustee_BBs_Chronological_Order [use_induction]:
  "
    All tr sd1 sd2 sl1 sl2 msg1 msg2 sig1 sig2 %idx1 %idx2 #i1 #i2.
            Trustee_BBEntry_Trace(tr, sd1, sl1, msg1, sig1, %idx1)@i1
          &
            Trustee_BBEntry_Trace(tr, sd2, sl2, msg2, sig2, %idx2)@i2
          &
            %idx1 << %idx2
          &
            #i2 < #i1
      ==>
          F
  "
dnl Include the proof script, if one exists.
sinclude(PROOF_SCRIPT)dnl

/*
  This lemma states that any two trustees that confirm the generated
  election public key confirm the same election public key.

  Tamarin is unable to prove this automatically. It may be proven
  interactively in the future.
 */
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, <!subprotocols/includes/proofs/ElectionKeyGeneration_IdenticalKeyConfirmation_<!!>TRUSTEE_COUNT<!!>.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_ElectionKeyGeneration_IdenticalKeyConfirmation:
  "
    All tr1 tr2 epk1 epk2 #i1 #i2.
            Trustee_CheckGeneratedElectionPublicKeys_Trace(tr1, epk1)@i1
          &
            Trustee_CheckGeneratedElectionPublicKeys_Trace(tr2, epk2)@i2
      ==>
          epk1 = epk2
  "
dnl Include the proof script, if one exists.
sinclude(PROOF_SCRIPT)dnl

/* Protocol Executability Lemmas

   Note that these are verified without reusing any lemmas that Tamarin
   cannot verify automatically or that do not have proof scripts, so
   they are all valid despite some of the safety lemmas not having been
   verified.
*/

/*
  This lemma states that it is possible to reach a state where all the
  key shares have been generated.
 */
lemma Executability_ElectionKeyGeneration_Key_Shares_Generated:
  exists-trace
  "
    Ex<!!>forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <! t<!!>TN<!!> <!#!>i<!!>TN<!!>!>).
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!        Trustee_GenerateKeyShares_Trace(t<!!>TN<!!>)@i<!!>TN<!!>
      &
!>)dnl
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!forloop(<!TN2!>, eval(TN + 1), TRUSTEE_COUNT, <!        not (t<!!>TN<!!> = t<!!>TN2<!!>)ifelse(eval(eval(TN + 1) < TRUSTEE_COUNT), eval(1), <!
      &
!>, <!!>)!>)!>, <!!>)
  "

/*
  This lemma states that it is possible to reach a state where all <!!>TRUSTEE_COUNT<!!>
  trustees have generated the same election public key.

  Tamarin seems to be unable to prove this lemma automatically. If it has
  been interactively proven for <!!>TRUSTEE_COUNT<!!> trustees, the proof script is
  included below.
 */
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, <!subprotocols/includes/proofs/ElectionKeyGeneration_Election_Public_Key_Generated_<!!>TRUSTEE_COUNT<!!>.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_Executability_Election_Public_Key_Generated:
  exists-trace
  "
    Ex epk<!!>forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <! <!#!>i<!!>TN<!!>!>).
    (
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!        Trustee_GenerateElectionPublicKey_Trace('Trustee<!!>TN<!!>', epk)@i<!!>TN<!!>ifelse(eval(TN < TRUSTEE_COUNT), eval(1), <!
      &
!>, <!!>)!>)
    )
  "
dnl Include the proof script, if one exists.
sinclude(PROOF_SCRIPT)dnl

/*
  This lemma states that it is possible to reach a state where all <!!>TRUSTEE_COUNT<!!>
  trustees have agreed that they all generated the same election public key.

  Tamarin seems to be unable to prove this lemma automatically. If it has
  been interactively proven for <!!>TRUSTEE_COUNT<!!> trustees, the proof script is
  included below.
 */
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, <!subprotocols/includes/proofs/ElectionKeyGeneration_Election_Public_Key_Agreed_Upon_<!!>TRUSTEE_COUNT<!!>.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_Executability_Election_Public_Key_Agreed_Upon:
  exists-trace
  "
    Ex epk<!!>forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <! <!#!>i<!!>TN<!!>!>).
    (
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!        Trustee_CheckGeneratedElectionPublicKeys_Trace('Trustee<!!>TN<!!>', epk)@i<!!>TN<!!>ifelse(eval(TN < TRUSTEE_COUNT), eval(1), <!
      &
!>, <!!>)!>)
    )
  "
dnl Include the proof script, if one exists.
sinclude(PROOF_SCRIPT)dnl

/*
  This lemma states that it is possible to reach a state where at
  least one trustee has detected an error.
 */
lemma Executability_ElectionKeyGeneration_Trustee_Error:
  exists-trace
  "
    Ex t e #i. Trustee_Trace_Error(t, e)@i
  "

/*
  This lemma states that it is possible to reach a state where at least
  one trustee has detected an error that was not because it aborted.

  Tamarin seems to be unable to prove this lemma automatically. If it has
  been interactively proven for <!!>TRUSTEE_COUNT<!!> trustees, the proof script is
  included below.
 */
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, <!subprotocols/includes/proofs/ElectionKeyGeneration_Trustee_Nontrivial_Error_<!!>TRUSTEE_COUNT<!!>.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_Executability_ElectionKeyGeneration_Trustee_Nontrivial_Error:
  exists-trace
  "
    Ex t e #i.
        Trustee_Trace_Error(t, e)@i
      &
        not (Ex #j. CorruptTrustee(t)@j)
  "
dnl Include the proof script, if one exists.
sinclude(PROOF_SCRIPT)dnl

/*
  This lemma states that it is possible to reach a state where all
  <!!>TRUSTEE_COUNT<!!> trustees have detected an error.
 */
lemma Executability_ElectionKeyGeneration_All_Trustees_Error:
  exists-trace
  "
    Ex<!!>forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <! e<!!>TN<!!> <!#!>i<!!>TN<!!>!>).
    (dnl
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!
        Trustee_Trace_Error('Trustee<!!>TN<!!>', e<!!>TN<!!>)@i<!!>TN<!!>ifelse(eval(TN < TRUSTEE_COUNT), eval(1), <!
      &!>, <!!>)!>)
    )
  "

/*
  This lemma states that it is possible to reach a state where all
  <!!>TRUSTEE_COUNT<!!> trustees have detected an error and none of them
  aborted.

  Tamarin seems to be unable to prove this lemma automatically. If it has
  been interactively proven for <!!>TRUSTEE_COUNT<!!> trustees, the proof script is
  included below.
 */
define(<!PROOF_SCRIPT!>, ifdef(<!INCLUDE_PROOF_SCRIPTS!>, <!subprotocols/includes/proofs/ElectionKeyGeneration_All_Trustees_Nontrivial_Error_<!!>TRUSTEE_COUNT<!!>.spthy.inc!>, <!/tmp/NOPROOFSCRIPT!>))dnl
syscmd(cat PROOF_SCRIPT > /dev/null 2>&1)dnl
lemma ifelse(sysval, <!0!>, <!ProofScript!>, <!NoProofScript!>)_Executability_ElectionKeyGeneration_All_Trustees_Nontrivial_Error:
  exists-trace
  "
    Ex<!!>forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <! e<!!>TN<!!> <!#!>i<!!>TN<!!>!>).
    (dnl
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!
        Trustee_Trace_Error('Trustee<!!>TN<!!>', e<!!>TN<!!>)@i<!!>TN<!!>
      &
        not (Ex <!#!>j. CorruptTrustee('Trustee<!!>TN<!!>')@j)<!!>ifelse(eval(TN < TRUSTEE_COUNT), eval(1), <!
      &!>, <!!>)!>)
    )
  "
dnl Include the proof script, if one exists.
sinclude(PROOF_SCRIPT)dnl
