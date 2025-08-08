dnl
dnl This is the m4 input file for the trustees in the election key generation
dnl protocol. Macro TRUSTEE_COUNT (defined in trustee_setup.spthy.m4)
dnl determines how many trustees there are.
dnl
dnl @author Daniel M. Zimmerman
dnl @copyright Free & Fair 2025
dnl @version 0.1
dnl

/* Trustee Rules */

/* Key Generation */

/*
  This rule starts the key generation process. It generates and posts
  a check value and pairwise shares from a given trustee.

  Validation checks performed explicitly (via restrictions):
    - no error conditions have previously occurred

  Validation checks performed implicitly:
    - the election setup information is valid (assumed from a previous
      protocol)
 */
rule ElectionKeyGeneration_Trustee_GenerateKeyShares [role="Trustee"]:
  let forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!pws_plaintext<!!>TN<!!> = pairwise_share(~private_share, 'Trustee<!!>TN<!!>')
      pws_ciphertext<!!>TN<!!> = aenc(pws_plaintext<!!>TN<!!>, pk_encrypt<!!>TN<!!>)
      msg_pairwise_share<!!>TN<!!> = Msg_Trustee_Pairwise_Share(election_setup, 'Trustee<!!>TN<!!>', pws_ciphertext<!!>TN<!!>)<!!>ifelse(eval(TN < TRUSTEE_COUNT), eval(1), <!
      !>, <!!>)!>)
      cv = check_value(~private_share)
      msg_check_value = Msg_Trustee_Check_Value(election_setup, cv) in
    [ !Trustee_ElectionSetup(trustee, election_setup),
      !Trustee_Secret_Keys(trustee, sk_sign, sk_encrypt),
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!      !Trustee_Public_Keys('Trustee<!!>TN<!!>', pk_sign<!!>TN<!!>, pk_encrypt<!!>TN<!!>),
!>)dnl
      Fr(~private_share) ]
  --[ Trustee_GenerateKeyShares_Trace(trustee),
      Unique(<'Trustee_GenerateKeyShares', trustee>),
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!      Trustee_Sent_Msg_Trace(trustee, msg_pairwise_share<!!>TN<!!>),
!>)dnl
      Trustee_Sent_Msg_Trace(trustee, msg_check_value),
      No_Trustee_Trace_Errors(trustee) ]->
    [ !Trustee_Private_Share(trustee, ~private_share),
      !Trustee_Check_Value_Msg(trustee, msg_check_value),
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!      Trustee_Message_Submit(trustee, msg_pairwise_share<!!>TN<!!>, sign(msg_pairwise_share<!!>TN<!!>, '1', sk_sign)),
!>)dnl
      Trustee_Message_Submit(trustee, msg_check_value, sign(msg_check_value, '1', sk_sign)) ]

/*
  This rule waits until all the pairwise shares and check values have been
  posted to the trustee board, validates them, and computes the election
  public key from them, which should be the same election public key as
  every other trustee computes. It posts the election public key to the
  trustee board.

  We compute the election public key using the check values published
  by the trustees.

  Validation checks performed explicitly (via restrictions):
    - the pairwise shares are valid with respect to the check values
    - no error conditions have previously occurred

  Validation checks performed implicitly:
    - the signatures on the messages are all valid (this is implicit here,
      because it's enforced by the TAS in the Tamarin model - messages with
      bad signatures simply don't make it onto the trustee board - but would
      be explicit in an implementation)
    - there is only one pairwise share message from each trustee to trustee <!!>TN<!!>
      (check performed when making trustee copy of trustee board)
    - there is only one check value message from each trustee (check performed
      when making trustee copy of trustee board)
    - the check value and pairwise share messages we sent to ourselves are on
      the trustee board (via pattern matching)
    - all the pairwise share messages and check value messges have valid
      election setups (via pattern matching)
 */
rule ElectionKeyGeneration_Trustee_GenerateElectionPublicKey [role="Trustee"]:
  let forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!msg_pairwise_share_in<!!>TN<!!> = Msg_Trustee_Pairwise_Share(election_setup, trustee, pws_ciphertext<!!>TN<!!>)
      pws_plaintext<!!>TN<!!> = adec(pws_ciphertext<!!>TN<!!>, sk_encrypt)
      msg_check_value<!!>TN<!!> = Msg_Trustee_Check_Value(election_setup, cv<!!>TN<!!>)<!!>ifelse(eval(TN < TRUSTEE_COUNT), eval(1), <!
      !>, <!!>)!>)
      epk = threshold_pubkey(forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!cv<!!>TN<!!>ifelse(eval(TN < TRUSTEE_COUNT), eval(1), <!, !>, <!!>)!>))
      msg_epk = Msg_Trustee_Election_Public_Key(election_setup, epk) in
    [ forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!!Trustee_BBEntry(trustee, 'Trustee<!!>TN<!!>', msg_pairwise_share_in<!!>TN<!!>, sig_pairwise_share_in<!!>TN<!!>, %idx_pairwise_share_in<!!>TN<!!>),
      !Trustee_BBEntry(trustee, 'Trustee<!!>TN<!!>', msg_check_value<!!>TN<!!>, sig_check_value<!!>TN<!!>, %idx_check_value<!!>TN<!!>)<!!>ifelse(eval(TN < TRUSTEE_COUNT), eval(1), <!,
      !>, <!!>)!>),
      !Trustee_ElectionSetup(trustee, election_setup),
      !Trustee_Secret_Keys(trustee, sk_sign, sk_encrypt) ]
  --[ Trustee_GenerateElectionPublicKey_Trace(trustee, epk),
      Unique(<'Trustee_GenerateElectionPublicKey', trustee>),
      forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!Eq(valid_share(cv<!!>TN<!!>, pws_plaintext<!!>TN<!!>), true), /* share is valid */<!!>ifelse(eval(TN < TRUSTEE_COUNT), eval(1), <!
      !>, <!!>)!>)
      Trustee_Sent_Msg_Trace(trustee, msg_epk),
      No_Trustee_Trace_Errors(trustee) ]->
    [ !Trustee_ElectionPublicKey(trustee, epk),
      !Trustee_ElectionPublicKey_Msg(trustee, msg_epk),
      Trustee_Message_Submit(trustee, msg_epk, sign(msg_epk, '1', sk_sign)) ]

/*
  This rule waits until all the trustees have posted their computed public
  keys to the trustee board and, assuming they are all identical and
  match the one this trustee generated, establishes an action fact and a
  persistent fact about the trustees having all agreed upon the public key.

  Validation checks performed explicitly (via restrictions):
    - no error conditions have previously occurred

  Validation checks performed implicitly:
    - all the posted election public keys match and are identical to the one
      this trustee posted (via pattern matching)
 */
rule ElectionKeyGeneration_Trustee_CheckGeneratedElectionPublicKeys [role="Trustee"]:
  let msg_epk = Msg_Trustee_Election_Public_Key(election_setup, epk) in
    [ forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!!Trustee_BBEntry(trustee, 'Trustee<!!>TN<!!>', msg_epk, sig_epk<!!>TN<!!>, %idx_epk<!!>TN<!!>),
      !>)dnl
      !Trustee_ElectionSetup(trustee, election_setup),
      !Trustee_ElectionPublicKey_Msg(trustee, msg_epk) ]
  --[ Trustee_CheckGeneratedElectionPublicKeys_Trace(trustee, epk),
      Unique(<'Trustee_CheckGeneratedElectionPublicKeys', trustee>),
      No_Trustee_Trace_Errors(trustee) ]->
    [ !Trustee_ElectionPublicKey_Agreement(trustee, epk) ]

/*
  Trustee Corruption DoS

  A corrupt trustee can stop its work at any time and attempt to hold up the
  protocol. Other types of corruption (submitting bad messages, etc.) are
  covered by the adversary rules (i.e., if a trustee's private signing/
  encryption keys and/or private key shares are revealed to the adversary, it
  can craft corrupt messages).
 */
rule ElectionKeyGeneration_Trustee_Abort:
    [ !Trustee(trustee) ]
  --[ CorruptTrustee(trustee),
      No_Trustee_Trace_Errors(trustee),
      Trustee_Trace_Error(trustee, <'corruption'>) ]->
    [ !TerminalError(trustee) /* no further trustee actions */ ]

/*
  Error States

  These rules enter error states if various errors are detected with respect
  to the trustee board and the messages a trustee has previously
  sent/received.

  Note that most error states (duplicate message slots, messages ostensibly
  received from a trustee that the trustee did not send) are caught during
  local BB updates above, and there is no possibility of bad signatures on
  trustee boards because they never make it onto the global trustee board.
 */

/*
  If a trustee detects an invalid share on the trustee board, that's
  an error.
 */
rule ElectionKeyVerification_Trustee_Error_Invalid_Pairwise_Share [role="Trustee"]:
  let msg_pairwise_share = Msg_Trustee_Pairwise_Share(election_setup, trustee, pws_ciphertext)
      pws_plaintext = adec(pws_ciphertext, sk_encrypt)
      msg_check_value = Msg_Trustee_Check_Value(election_setup, cv) in
    [ !Trustee(trustee),
      !Trustee_Secret_Keys(trustee, sk_sign, sk_encrypt),
      !Trustee_BBEntry(trustee, sender, msg_pairwise_share, sig_pairwise_share_in, %idx_pairwise_share_in),
      !Trustee_BBEntry(trustee, sender, msg_check_value, sig_check_value, %idx_check_value) ]
  --[ Neq(valid_share(cv, pws_plaintext), true), /* share is invalid */
      No_Trustee_Trace_Errors(trustee),
      Trustee_Trace_Error(trustee, <'invalid pairwise share detected', sender>) ]->
    [ !Terminal_Error(trustee) /* no further trustee execution */ ]
