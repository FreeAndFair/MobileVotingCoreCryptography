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
  This is the initial rule for the TAS. It generates an action fact
  with a public name and transitions to the state that triggers key
  generation and sharing.
 */
rule TrusteeSetup_TAS_Init [role="TAS"]:
    [ ]
  --[ Unique(<'TAS_Init'>) ]->
    [ TAS_State_IdentityKeyGen() ]

/*
  This rule initializes the secret keys for the TAS, sends out its
  public keys, and transitions to the state that waits for trustee
  registrations (this is actually done with one fact for each
  trustee identity).
 */
rule TrusteeSetup_TAS_IdentityKeyGen [role="TAS"]:
  let name = 'TAS'
      tas_id = Msg_TAS_ID(pk(~sk_sign)) in
    [ TAS_State_IdentityKeyGen(),
      Fr(~sk_sign) ]
  --[ HonestSignatureKey(pk(~sk_sign)),
      TAS_IdentityKeyGen_Trace(pk(~sk_sign)) ]->
    [ !TAS_Secret_Signing_Key(~sk_sign),
      !TAS_Public_Signing_Key(pk(~sk_sign)),
      Out(<tas_id, sign(tas_id, '1', ~sk_sign)>),
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!      TAS_State_RegisterTrustee('Trustee<!!>TN<!!>')ifelse(eval(TN < TRUSTEE_COUNT), eval(1), <!,
!>, <!!>)!>) ]

/*
  This rule waits for a single trustee to register, and establishes
  appropriate facts in the environment and the trace.
 */
rule TrusteeSetup_TAS_RegisterTrustee [role="TAS"]:
  let msg_trustee = Msg_Trustee_ID(name, id, pk_sign, pk_encrypt) in
    [ TAS_State_RegisterTrustee(name),
      In(<msg_trustee, sig_trustee>) ]
  --[ TAS_Trustee_Trace(name, id, pk_sign, pk_encrypt),
      SignatureVerified(sig_trustee, e1_sig(sig_trustee), pk(e3_sig(sig_trustee)),
                        msg_trustee, pk_sign, true), /* valid signature */ ]->
    [ !TAS_Trustee(name, id, pk_sign, pk_encrypt),
      TAS_State_RegisterTrusteeComplete(name) ]

/*
  This rule waits for all trustee registrations to be complete. Since we
  know the number of trustees, and their names, a priori, we just wait for
  all of them to have registered (with the previous rule). Once we've
  registered them all, we construct the trustee public keys message and
  broadcast it with the election configuration, then transition to the
  state that waits for trustees to approve that broadcast.
 */
rule TrusteeSetup_TAS_BroadcastElectionSetup [role="TAS"]:
  let msg_setup = Msg_TAS_Election_Setup(Trustee_ID_Tuple(), ~election_definition) in
    [ forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!TAS_State_RegisterTrusteeComplete('Trustee<!!>TN<!!>'),
      !TAS_Trustee('Trustee<!!>TN<!!>', id_trustee<!!>TN<!!>, pk_sign_trustee<!!>TN<!!>, pk_encrypt_trustee<!!>TN<!!>),
      !>)dnl
!TAS_Secret_Signing_Key(sk_sign),
      Fr(~election_definition) ]
  --[ TAS_AllTrustees_Trace(Trustee_ID_Tuple()) ]->
    [ !TAS_AllTrustees(Trustee_ID_Tuple()),
      !TAS_ElectionSetup(msg_setup),
      Out(<msg_setup, sign(msg_setup, '1', sk_sign)>),
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!      TAS_State_ReceiveTrusteeConfirmation('Trustee<!!>TN<!!>')ifelse(eval(TN < TRUSTEE_COUNT), eval(1), <!,
!>, <!!>)!>) ]

/*
  This rule waits for a single trustee to confirm the election setup, and
  establishes appropriate facts in the environment and the trace.
 */
rule TrusteeSetup_TAS_ReceiveTrusteeConfirmation [role="TAS"]:
  let msg_setup = Msg_TAS_Election_Setup(Trustee_ID_Tuple(), election_definition)
      msg_trustee_confirm = Msg_Trustee_Election_Setup_Confirm(trustee, msg_setup) in
    [ TAS_State_ReceiveTrusteeConfirmation(name),
      !TAS_Trustee(name, id, pk_sign, pk_encrypt_unused),
      !TAS_ElectionSetup(msg_setup),
      In(<msg_trustee_confirm, sig_trustee>) ]
  --[ TAS_Trustee_Confirmation_Trace(name),
      SignatureVerified(sig_trustee, e1_sig(sig_trustee), pk(e3_sig(sig_trustee)),
                        msg_trustee_confirm, pk_sign, true), /* valid signature */ ]->
    [ TAS_State_TrusteeConfirmed(name) ]

/*
  This rule waits for all trustees to have confirmed (similarly to
  waiting for registrations), then declares the election setup complete,
  establishes appropriate facts in the environment and the trace, and
  transitions the TAS to the state where it's waiting for the trustees
  to complete their threshold key generation process with each other.
 */
rule TrusteeSetup_TAS_CompleteElectionSetup [role="TAS"]:
    [ forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!TAS_State_TrusteeConfirmed('Trustee<!!>TN<!!>')ifelse(eval(TN < TRUSTEE_COUNT), eval(1), <!,
      !>, <!!>)!>),
      !TAS_ElectionSetup(msg_setup) ]
  --[ TAS_ElectionSetup_Complete_Trace(msg_setup) ]->
    [ !TAS_ElectionSetup_Complete(msg_setup),
      TAS_State_AwaitTrusteeKeygenCompletion() ]
