dnl
dnl This is the m4 input file for the trustee administration
dnl server (TAS) in the election key generation protocol. Macro
dnl TRUSTEE_COUNT (defined in trustee_setup.spthy.m4)
dnl determines how many trustees there are.
dnl
dnl @author Daniel M. Zimmerman
dnl @copyright Free & Fair 2025
dnl @version 0.1
dnl
/* Trustee Administration Server */

/*
  This rule initializes the counter for trustee board messages,
  starting from the state the TAS was left in at the end of election setup.
 */
rule ElectionKeyGeneration_TAS_Init [role="TAS"]:
    [ TAS_State_BeginTrusteeThresholdKeygen(),
      !TAS_Secret_Signing_Key(sk_sign) ]
  --[ TAS_ElectionKeyGeneration_Init_Trace() ]->
    [ forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!Trustee_State_ReceiveBBMessage('Trustee<!!>TN<!!>', %1),
      !>)
      TAS_State_ReceiveTrusteeMessage(%1) ]

/*
  This rule waits for messages from all the trustees indicating that
  the key generation process was completed successfully (that is, all
  confirming the same election public key) to be posted to the trustee
  board, then stops receiving trustee board messages and transitions to
  the state that awaits the beginning of the mixing protocol.

  Note that we don't actually need to verify the signatures on the election
  key confirmation messages, because we did that as part of creating the
  board entry facts for them. We could of course still include the valid
  signature restriction here, but it's not necessary.
 */
rule ElectionKeyGeneration_TAS_Complete [role="TAS"]:
    [ forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!!TAS_BBEntry('Trustee<!!>TN<!!>', Msg_Trustee_Election_Public_Key(hash_election, pk_election), sig_unused<!!>TN<!!>, %idx_unused<!!>TN<!!>)ifelse(eval(TN < TRUSTEE_COUNT), eval(1), <!,
      !>, <!!>)!>) ]
  --[ TAS_ElectionKeyGeneration_Complete_Trace() ]->
    [ TAS_State_AwaitTrusteeMixing() ]
