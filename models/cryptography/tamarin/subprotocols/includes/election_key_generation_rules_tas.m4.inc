dnl
dnl This is the m4 input file for the trustee administration
dnl server (TAS) in the trustee setup protocol. Macro
dnl TRUSTEE_COUNT (defined in trustee_setup.spthy.m4)
dnl determines how many trustees there are.
dnl
dnl @author Daniel M. Zimmerman
dnl @copyright Free & Fair 2025
dnl @version 0.1
dnl
/* Trustee Administration Server */

/*
  This rule initializes the counter for trustee bulletin board messages,
  starting from the state the TAS was left in at the end of election setup.
 */
rule ElectionKeyGeneration_TAS_Init [role="TAS"]:
  let root_msg = <'Root', 'Root'> in
    [ TAS_State_BeginTrusteeThresholdKeygen(),
      !TAS_Secret_Signing_Key(sk_sign) ]
  --[ TAS_ElectionKeyGeneration_Init_Trace() ]->
    [ forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!Trustee_State_ReceiveBBMessage('Trustee<!!>TN<!!>', %1),
      !>)
      TAS_State_ReceiveTrusteeMessage(%1) ]

/*
  This rule waits for a message to be submitted by a trustee,
  checks its signature, and posts it to the trustee bulletin board.
 */
rule ElectionKeyGeneration_TAS_ReceiveTrusteeMessage [role="TAS"]:
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
  This rule waits for messages from all the trustees indicating that
  the key generation process was completed successfully (that is, all
  confirming the same election public key) to be posted to the trustee
  bulletin board, then stops receiving trustee bulletin board messages and
  transitions to the state that awaits the beginning of the mixing protocol.

  Note that we don't actually need to verify the signatures on the election
  key confirmation messages, because we did that as part of creating the
  bulletin board entry facts for them. We could of course still include the
  valid signature restriction here, but it's not necessary.
 */
rule ElectionKeyGeneration_TAS_Complete [role="TAS"]:
    [ forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!!TAS_BBEntry('Trustee<!!>TN<!!>', Msg_Trustee_Election_Public_Key(hash_election, pk_election), sig_unused<!!>TN<!!>, %idx_unused<!!>TN<!!>)ifelse(eval(TN < TRUSTEE_COUNT), eval(1), <!,
      !>, <!!>)!>) ]
  --[ TAS_ElectionKeyGeneration_Complete_Trace() ]->
    [ TAS_State_AwaitTrusteeMixing() ]
