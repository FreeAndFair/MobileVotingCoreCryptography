dnl
dnl This is the m4 input file for the trustees in the trustee mixing
dnl protocol. Macro TRUSTEE_COUNT (defined in trustee_setup.spthy.m4)
dnl determines how many trustees there are, and macro TRUSTEE_THRESHOLD
dnl determines the threshold (and participating) number.
dnl
dnl @author Daniel M. Zimmerman
dnl @copyright Free & Fair 2025
dnl @version 0.1
dnl

/* Trustees */

/* Trustee Decryption */

/*
  This rule performs a partial decryption of the ballot "set" posted
  on the trustee board and posts the partial decryption and its
  associated proof. Note that the ballot set here is a single encrypted
  value, though this modeling might be changed later to be an actual
  multiset of such encrypted values.

  Validation checks performed explicitly (via restrictions):
    - this trustee has not yet posted a partial decryption
    - no error conditions have previously occurred

  Validation checks performed implicitly:
    - the encrypted ballot was encrypted with the correct election key
      (via pattern matching)

  This rule does a lot of derivations via pattern matching, including
  some values that the trustee does not have access to (the other
  trustees' private shares); these are not used in the trustee
  computation, and are there only to allow Tamarin to resolve partial
  deconstructions, by connecting the election public key to the private
  shares. This is a reasonable simplification because in the real system,
  the trustees will all know the check values that were used to create
  the election public key, and the proofs of correct mixing and
  encryption will restrict them to only accepting valid (i.e., using the
  correct election public key) messages; effectively, pattern matching
  in this way accomplishes the same in Tamarin.

  Because these derivations also reverse out the randomness that was
  used by the voter to encrypt the ballot (in addition to the election
  public key), even though the rule does not use that, we mark it
  "no_derivcheck".
 */
rule TrusteeDecryption_Trustee_Partial_Decrypt [role="Trustee", no_derivcheck]:
  let initial_trustee = 'Trustee0'
      pk_election = threshold_pubkey(forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!check_value(ps<!!>TN<!!>)ifelse(eval(TN < TRUSTEE_COUNT), eval(1), <!, !>, <!!>)!>))
      c1 = ny_encrypt_c1(ballot, pk_election, r)
      c2 = ny_encrypt_c2(ballot, pk_election, r)
      cryptograms = <c1, c2>
      msg_mixed_cryptograms = Msg_TAS_Mixed_Cryptograms(election_setup, cryptograms)
      pd = ny_partial_decrypt(c1, c2, ps_trustee)
      pd_proof = ny_partial_dec_proof(c1, c2, ps_trustee)
      msg_pd = Msg_Trustee_Partial_Decryption(election_setup, trustee, pd, pd_proof) in
    [ !Trustee_Decrypt_Active(trustee),
      !Trustee_BBEntry(trustee, initial_trustee, msg_mixed_cryptograms, sig_mixed_cryptograms, %idx_mixed_cryptograms),
      !Trustee_ElectionSetup(trustee, election_setup),
      !ElectionPublicKey(pk_election),
      !Trustee_Private_Share(trustee, ps_trustee),
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!      !Trustee_Private_Share('Trustee<!!>TN<!!>', ps<!!>TN<!!>),
!>)dnl
      !Trustee_Secret_Keys(trustee, sk_sign, sk_encrypt_unused) ]
  --[ Trustee_Partial_Decryption_Trace(trustee, pd, pd_proof),
      Unique(<'Trustee_Partial_Decrypt', trustee>),
      Trustee_Sent_Msg_Trace(trustee, msg_pd),
      No_Trustee_Trace_Errors(trustee),
      IN_BALLOTSET_C1_TERM(c1, ballot),
      IN_BALLOTSET_C2_TERM(c2, ballot) ]->
    [ !Trustee_Partial_Decryption(trustee, pd, pd_proof),
      Trustee_Message_Submit(trustee, msg_pd, sign(msg_pd, '1', sk_sign)) ]

/*
  This rule takes all the partial decryptions that have been posted,
  combines them into decrypted plaintext ballots, and posts them to
  the trustee board.

  Validation checks performed explicitly (via restrictions):
    - all the partial decryption proofs are valid (redundantly)
    - no error conditions have previously occurred

  Validation checks performed implicitly:
    - partial decryptions have been posted by all participating
      trustees (via pattern matching)
    - all the partial decryptions are valid (via pattern matching)
    - the encrypted ballot was encrypted with the correct election key
      (via pattern matching)

  This rule does a lot of derivations via pattern matching, including
  some values that the trustee does not have access to (the other
  trustees' private shares); these are not used in the trustee
  computation, and are there only to allow Tamarin to resolve partial
  deconstructions. This is a reasonable simplification because in the
  real system, the trustees will all know the check values that were
  used to create the election public key, and the proofs of correct
  mixing, encryption, and partial decryption will restrict them to
  only accepting valid (i.e., using the correct election public key)
  messages; effectively, pattern matching in this way accomplishes
  the same in Tamarin.

  Because these derivations also reverse out the randomness that was
  used by the voter to encrypt the ballot (in addition to the election
  public key), even though the rule does not use that, we mark it
  "no_derivcheck".
 */
rule TrusteeDecryption_Trustee_Combine_Partial_Decryptions [role="Trustee", no_derivcheck]:
  let pk_election = threshold_pubkey(forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!check_value(ps<!!>TN<!!>)ifelse(eval(TN < TRUSTEE_COUNT), eval(1), <!, !>, <!!>)!>))
      c1 = ny_encrypt_c1(ballot, pk_election, r)
      c2 = ny_encrypt_c2(ballot, pk_election, r)
      forloop(<!TN!>, eval(TRUSTEE_COUNT - TRUSTEE_THRESHOLD + 1), TRUSTEE_COUNT, <!pd<!!>TN<!!> = ny_partial_decrypt(ny_encrypt_c1(ballot, pk_election, r), ny_encrypt_c2(ballot, pk_election, r), ps<!!>TN<!!>)
      pd_proof<!!>TN<!!> = ny_partial_dec_proof(c1, c2, ps<!!>TN<!!>)
      msg_pd<!!>TN<!!> = Msg_Trustee_Partial_Decryption(election_setup, 'Trustee<!!>TN<!!>', pd<!!>TN<!!>, pd_proof<!!>TN<!!>)
      pd_valid<!!>TN<!!> = ny_pd_check(pd<!!>TN<!!>, pd_proof<!!>TN<!!>)<!!>ifelse(eval(TN < TRUSTEE_COUNT), eval(1), <!
      !>, <!!>)!>)
      decrypted_ballots = ny_combine(forloop(<!TN!>, eval(TRUSTEE_COUNT - TRUSTEE_THRESHOLD + 1), TRUSTEE_COUNT, <!pd<!!>TN<!!>ifelse(eval(TN < TRUSTEE_COUNT), eval(1), <!, !>, <!!>)!>))
      msg_decrypted_ballots = Msg_Trustee_Decrypted_Ballots(election_setup, trustee, decrypted_ballots) in
    [ !Trustee_Decrypt_Active(trustee),
forloop(<!TN!>, eval(TRUSTEE_COUNT - TRUSTEE_THRESHOLD + 1), TRUSTEE_COUNT, <!      !TAS_BBEntry('Trustee<!!>TN<!!>', msg_pd<!!>TN<!!>, sig_pd<!!>TN<!!>, %idx_pd<!!>TN<!!>),
!>)dnl
      !Trustee_ElectionSetup(trustee, election_setup),
      !Trustee_Secret_Keys(trustee, sk_sign, sk_encrypt_unused),
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!      !Trustee_Private_Share('Trustee<!!>TN<!!>', ps<!!>TN<!!>),
!>)dnl
      !ElectionPublicKey(pk_election) ]
  --[ Trustee_Combine_Partial_Decryptions_Trace(trustee, decrypted_ballots),
forloop(<!TN!>, eval(TRUSTEE_COUNT - TRUSTEE_THRESHOLD + 1), TRUSTEE_COUNT, <!      Eq(pd_valid<!!>TN<!!>, true),
!>)dnl
      Unique(<'Trustee_Combine_Partial_Decryptions', trustee>),
      Trustee_Sent_Msg_Trace(trustee, msg_decrypted_ballots),
      No_Trustee_Trace_Errors(trustee),
      IN_BALLOTSET_C1_TERM(c1, ballot),
      IN_BALLOTSET_C2_TERM(c2, ballot) ]->
    [ !Trustee_Combine_Partial_Decryptions(trustee, decrypted_ballots),
      Trustee_Message_Submit(trustee, msg_decrypted_ballots, sign(msg_decrypted_ballots, '1', sk_sign)) ]

/*
  This rule causes an error condition when an invalid partial decryption
  is posted by any trustee.
 */
rule TrusteeDecryption_Trustee_Detect_Invalid_Partial_Decryption [role="Trustee"]:
  let msg_pd = Msg_Trustee_Partial_Decryption(election_setup, pd_trustee, pd, pd_proof)
      pd_proof_valid = ny_pd_check(pd, pd_proof) in
    [ !Trustee_Decrypt_Active(trustee),
      !TAS_BBEntry(pd_trustee, msg_pd, sig_pd, %idx_pd),
      !Trustee_ElectionSetup(trustee, election_setup) ]
  --[ Trustee_Detect_Invalid_Partial_Decryption_Trace(trustee, pd_trustee),
      Unique(<'Trustee_Detect_Invalid_Decryption', trustee, pd_trustee>),
      Neq(pd_proof_valid, true), /* partial decryption proof is invalid */
      No_Trustee_Trace_Errors(trustee),
      Trustee_Trace_Error(trustee, <'invalid partial decryption detected', pd_trustee>) ]->
    [ !TerminalError(trustee) /* no further trustee actions */ ]
