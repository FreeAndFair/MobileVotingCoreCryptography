dnl
dnl Tamarin formalization of the trustee board. This implements the
dnl board as a set of persistent facts (for the bulletin board
dnl entries),
dnl
dnl @author Daniel M. Zimmerman
dnl @copyright Free & Fair 2025
dnl @version 0.1
dnl
ifdef(<!TRUSTEEBOARD_SPTHY!>, <!!>, <!
define(<!TRUSTEEBOARD_SPTHY!>)dnl
define(<!USE_UNIQUE!>)dnl
define(<!USE_EUFCMA_SIGNING!>)dnl
include(common/primitives.m4.inc)dnl

/*
  This restriction states that if an error of some sort has occurred
  in the trace, the rule cannot execute. This models the necessity for a
  manual (outside the protocol) resolution and a restart.
 */
restriction No_Trustee_Trace_Errors:
  "
    All trustee #i.
          No_Trustee_Trace_Errors(trustee)@i
      ==>
          not (Ex err #j. Trustee_Trace_Error(trustee, err)@j & #j < #i)
  "

/*
  This rule waits for a message to be submitted by a trustee,
  checks its signature, and posts it to the trustee board.

  Note that this rule must be triggered to start off the trustee
  board; this is done by the setup for each individual subprotocol
  (or composition).
 */
rule TrusteeBoard_TAS_ReceiveTrusteeMessage [role="TAS"]:
    [ TAS_State_ReceiveTrusteeMessage(%idx),
      Trustee_Message_Submit(trustee, msg, sig),
      !Trustee_Public_Keys(trustee, pk_sign, pk_encrypt_unused) ]
  --[ Unique(<'BBEntry', %idx>),
      TAS_BBEntry_Trace(trustee, fst(msg), msg, sig, %idx),
      SignatureVerified(sig, e1_sig(sig), pk(e3_sig(sig)),
                        msg, pk_sign, true) /* valid signature */ ]->
    [ !TAS_BBEntry(trustee, msg, sig, %idx),
      TAS_State_ReceiveTrusteeMessage(%idx %+ %1) ]

/*
  This rule updates a trustee's local copy of the trustee board. It only
  fires if the next message it needs from the TAS is a legal addition to
  the trustee board.
 */
rule TrusteeBoard_Trustee_Update [role="Trustee"]:
    [ Trustee_State_ReceiveBBMessage(trustee, %idx),
      !TAS_BBEntry(sender, msg, sig, %idx) ]
  --[ Trustee_BBEntry_Trace(trustee, sender, fst(msg), msg, sig, %idx),
      Trustee_Can_Add_BBEntry(trustee, sender, fst(msg), msg, sig, %idx),
      OUT_TRUSTEE_BBENTRY(trustee, sender, msg, sig, %idx) ]->
    [ !Trustee_BBEntry(trustee, sender, msg, sig, %idx),
      Trustee_State_ReceiveBBMessage(trustee, %idx %+ %1) ]

/*
  This rule enters an error state and stops updating a trustee's local copy
  of the trustee board if an invalid message is detected on the global
  trustee board.
 */
rule TrusteeBoard_Trustee_Error [role="Trustee"]:
    [ Trustee_State_ReceiveBBMessage(trustee, %idx),
      !TAS_BBEntry(sender, msg, sig, %idx) ]
  --[ Trustee_BBError_Trace(trustee, sender, fst(msg), msg, sig, %idx),
      Trustee_Cannot_Add_BBEntry(trustee, sender, fst(msg), msg, sig, %idx),
      Trustee_Trace_Error(trustee, <'invalid trustee board message', sender, msg>) ]->
    [ !Terminal_Error(trustee) /* no further trustee execution */ ]

/*
  This restriction ensures that a new trustee board message is valid:
  it (1) does not duplicate an already used slot, and (2) does not
  claim to come from this trustee if this trustee didn't send it.
 */
restriction Trustee_Can_Add_BBEntry:
  "
    All trustee sender slot msg sig %idx #i.
          Trustee_Can_Add_BBEntry(trustee, sender, slot, msg, sig, %idx)@i
      ==>
            not (
              Ex e_msg e_sig %e_idx #j.
                  Trustee_BBEntry_Trace(trustee, sender, slot, e_msg, e_sig, %e_idx)@j
                &
                  #j < #i
            )
          &
            (
                  sender = trustee
              ==>
                  (Ex #j. Trustee_Sent_Msg_Trace(trustee, msg)@j & #j < #i)
            )
  "

/*
  This restriction is the logical negation of the previous one; it ensures
  that a new trustee board message is invalid, allowing an error condition
  to be triggered.
 */
restriction Trustee_Cannot_Add_BBEntry:
  "
    All trustee sender slot msg sig %idx #i.
          Trustee_Cannot_Add_BBEntry(trustee, sender, slot, msg, sig, %idx)@i
      ==>
            (
              Ex e_msg e_sig %e_idx #j.
                    Trustee_BBEntry_Trace(trustee, sender, slot, e_msg, e_sig, %e_idx)@j
                  &
                    #j < #i
            )
          |
            (
                sender = trustee
              &
                not (Ex #j. Trustee_Sent_Msg_Trace(trustee, msg)@j & #j < #i)
            )
  "

/*
  This rule allows the adversary to (attempt to) submit a message
  to the trustee board. In order to do this successfully, it needs to
  use a valid trustee name and signing key, which it can get from a reveal
  rule.
 */
rule TrusteeBoard_Inject_Arbitrary_Trustee_Message:
    [ In(<trustee, msg, sig>),
      !Trustee_Public_Keys(trustee, pk_sign, pk_encrypt_unused) ]
  --[ InjectTrusteeMsg(trustee, msg, sig),
      SignatureVerified(sig, e1_sig(sig), pk(e3_sig(sig)),
                        msg, pk_sign, true) /* valid signature */ ]->
    [ Trustee_Message_Submit(trustee, msg, sig) ]

/*
  This rule allows the adversary to see any trustee board message
  that has been posted.
 */
rule TrusteeBoard_Reveal_BB_Message:
    [ !TAS_BBEntry(t, m, s, %i) ]
  --[ RevealBBMsg(t, m, s, %i) ]->
    [ Out(<m, s>) /* t and %i are already known to the adversary */ ]

!>)
