dnl
dnl This is the m4 input file for the trustee administration
dnl server (TAS) in the trustee decryption protocol. Macro
dnl TRUSTEE_COUNT (defined in trustee_setup.spthy.m4)
dnl determines how many trustees there are, and macro
dnl TRUSTEE_THRESHOLD determines the trustee threshold.
dnl
dnl @author Daniel M. Zimmerman
dnl @copyright Free & Fair 2025
dnl @version 0.1
dnl
/* Trustee Administration Server */

/*
  This rule initializes the counter for trustee board messages,
  posts a (presumably shuffled) ballot set on the board, and starts
  the trustee board message handling process.

  The "!Trustee_Decrypt_Active" facts specify which trustees are active.
  Without loss of generality, we assume trustees <!!>eval(TRUSTEE_COUNT - TRUSTEE_THRESHOLD + 1)<!!> ..
  <!!>TRUSTEE_THRESHOLD<!!> are active (note that this is not the same
  set as we assume active for the mix, unless the threshold is "all the
  trustees").

  Note that we have the TAS post a message as "Trustee 0" here, containing
  the list of shuffled ballots, to start the partial decryption process.
  This could also be done by simply using the results of the last mix from
  the trustee mixing subprotocol directly; in practice, it should make no
  difference (in a composition of the protocol, this message is only posted
  after all the shuffle proofs from the mix have been verified), and in an
  actual implementation, either would be OK.
 */
rule TrusteeDecryption_TAS_Init [role="TAS"]:
  let msg_mixed_cryptograms = Msg_TAS_Mixed_Cryptograms(election_setup, cryptograms) in
    [ TAS_State_BeginTrusteeDecryption(),
      !TAS_ElectionSetup_Complete(election_setup),
      !TAS_Cryptogram_Set(cryptograms),
      !TAS_Ballot_Set(ballots),
      !TAS_Public_Signing_Key(pk_sign),
      !TAS_Secret_Signing_Key(sk_sign),
      Fr(~sk_encrypt_unused) ]
  --[ TAS_TrusteeDecryption_Init_Trace(cryptograms, ballots),
      Unique('TrusteeDecryption_TAS_Init'),
      Trustee_Sent_Msg_Trace('Trustee0', msg_mixed_cryptograms) ]->
    [ forloop(<!TN!>, eval(TRUSTEE_COUNT - TRUSTEE_THRESHOLD + 1), TRUSTEE_COUNT, <!!Trustee_Decrypt_Active('Trustee<!!>TN<!!>')<!!>ifelse(eval(TN < TRUSTEE_COUNT), eval(1), <!,
      !>, <!!>)!>),
      !Trustee_Public_Keys('Trustee0', pk_sign, pk(~sk_encrypt_unused)), /* public keys for TAS as "trustee 0" */
      Trustee_Message_Submit('Trustee0', msg_mixed_cryptograms, sign(msg_mixed_cryptograms, '1', sk_sign)) ]

/*
  This rule identifies the completion of the decryption process.
  Note that we do not check the signatures on the messages, becuase
  they were checked earlier, and that pattern matching ensures that
  all the decrypted ballot "sets" are identical and match the ballot
  "set" we started with.
 */
rule TrusteeDecryption_TAS_Complete [role="TAS"]:
    [ !TAS_ElectionSetup_Complete(election_setup),
      !TAS_Ballot_Set(ballots),
      forloop(<!TN!>, eval(TRUSTEE_COUNT - TRUSTEE_THRESHOLD + 1), TRUSTEE_COUNT, <!!TAS_BBEntry('Trustee<!!>TN<!!>', Msg_Trustee_Decrypted_Ballots(election_setup, 'Trustee<!!>TN<!!>', ballots), sig_decrypted_ballots<!!>TN<!!>, %idx_decrypted_ballots<!!>TN<!!>)ifelse(eval(TN < TRUSTEE_COUNT), eval(1), <!,
      !>, <!!>)!>) ]
  --[ TAS_TrusteeDecryption_Complete_Trace(ballots) ]->
    [ /* no further TAS action */ ]
