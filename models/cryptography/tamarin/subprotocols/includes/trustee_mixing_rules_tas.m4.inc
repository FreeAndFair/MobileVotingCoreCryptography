dnl
dnl This is the m4 input file for the trustee administration
dnl server (TAS) in the trustee mixing protocol. Macro
dnl TRUSTEE_COUNT (defined in trustee_setup.spthy.m4)
dnl determines how many trustees there are, and macro
dnl TRUSTEE_THRESHOLD determines the trustee threshold.
dnl
dnl @author Daniel M. Zimmerman
dnl @copyright Free & Fair 2025
dnl @version 0.1
dnl
/* Trustee Administration Server */

dnl
dnl If the number of ballots to generate is not defined, define it to be
dnl the smae as the number of trustees. Not for any particular reason,
dnl just because it's a number we happen to have.
dnl
/*
  This rule generates a "set" of ballots (really, only one cryptogram,
  because in Tamarin the treatment of multiple cryptograms would be
  symmetric, and we just need to make sure it's decryptable at the end
  by the threshold number of trustees).
 */
rule TrusteeMixing_TAS_GenerateBallotSet_Valid [role="TAS"]:
  let c1 = ny_encrypt_c1(~ballots, pk_election, ~r)
      c2 = ny_encrypt_c2(~ballots, pk_election, ~r)
      p = ny_encrypt_p(~ballots, pk_election, ~r)
      cryptograms = <c1, c2, p> in
    [ !ElectionPublicKey(pk_election),
      Fr(~ballots), Fr(~r) ]
  --[ TAS_Valid_BallotSet_Trace(cryptograms, ~ballots),
      OUT_BALLOTSET_C1_TERM(c1),
      OUT_BALLOTSET_C2_TERM(c2),
      OUT_BALLOTSET_P_TERM(p),
      Unique('TrusteeMixing_BallotSet') ]->
    [ !TAS_Cryptogram_Set(cryptograms),
      /* We save the plaintext "ballots" to check threshold decryption later. */
      !TAS_Ballot_Set(~ballots) ]

/*
  This rule does exactly the same thing as the previous one, but
  generates a "set" of ballots with an invalid proof, so that the
  proof checking of the trustees can actually fail. It is mutually
  exclusive with the previous rule (via the Unique restriction).
 */
rule TrusteeMixing_TAS_GenerateBallotSet_Invalid [role="TAS"]:
  let c1 = ny_encrypt_c1(~ballots, pk_election, ~r)
      c2 = ny_encrypt_c2(~ballots, pk_election, ~r)
      cryptograms = <c1, c2, ~p> in
    [ !ElectionPublicKey(pk_election),
      Fr(~ballots), Fr(~r), Fr(~p) ]
  --[ TAS_Invalid_BallotSet_Trace(cryptograms, ~ballots),
      OUT_BALLOTSET_C1_TERM(c1),
      OUT_BALLOTSET_C2_TERM(c2),
      Unique('TrusteeMixing_BallotSet') ]->
    [ !TAS_Cryptogram_Set(cryptograms),
      /* We save the plaintext "ballots" to check threshold decryption later. */
      !TAS_Ballot_Set(~ballots) ]

/*
  This rule initializes the counter for trustee board messages,
  posts a generated ballot set on the board, and starts the
  trustee board message handling process.

  The "!Trustee_Mix_Active" facts specify which trustees are active.
  Without loss of generality, we assume that trustees 1 ..
  TRUSTEE_THRESHOLD are active and perform the mix in numerical order.
 */
rule TrusteeMixing_TAS_Init [role="TAS"]:
  let msg_initial_ballots = Msg_Trustee_NY_Cryptograms(election_setup, 'Trustee0', 'Trustee0', ~ballot_order, cryptograms) in
    [ TAS_State_BeginTrusteeMixing(),
      !TAS_ElectionSetup_Complete(election_setup),
      !TAS_Cryptogram_Set(cryptograms),
      !TAS_Secret_Signing_Key(sk_sign),
      !TAS_Public_Signing_Key(pk_sign),
      Fr(~ballot_order),
      Fr(~sk_encrypt_unused) ]
  --[ TAS_TrusteeMixing_Init_Trace(cryptograms),
      TAS_Trustee_Trace('Trustee0', pk_sign, pk(~sk_encrypt_unused)),
      Trustee_Sent_Msg_Trace('Trustee0', msg_initial_ballots),
      Unique('TrusteeMixing_TAS_Init') ]->
    [ forloop(<!TN!>, <!1!>, TRUSTEE_THRESHOLD, <!!Trustee_Mix_Active('Trustee<!!>TN<!!>')<!!>ifelse(eval(TN < TRUSTEE_THRESHOLD), eval(1), <!,
      !>, <!!>)!>),
      !Trustee_Public_Keys('Trustee0', pk_sign, pk(~sk_encrypt_unused)), /* public keys for TAS as "trustee 0" */
      Trustee_Message_Submit('Trustee0', msg_initial_ballots, sign(msg_initial_ballots, '1', sk_sign)),
forloop(<!TN!>, <!1!>, TRUSTEE_THRESHOLD, <!      Trustee_State_ReceiveBBMessage('Trustee<!!>TN<!!>', %1),
!>)dnl
      TAS_State_ReceiveTrusteeMessage(%1) ]

/*
  This rule identifies the completion of the mixing process and
  moves on to the decryption process. Note that we do not check
  the signatures or proofs on the messages because they were
  checked earlier.
 */
rule TrusteeMixing_TAS_Complete [role="TAS"]:
    [ !TAS_ElectionSetup_Complete(election_setup),
      forloop(<!TN!>, <!1!>, TRUSTEE_THRESHOLD, <!!TAS_BBEntry('Trustee<!!>TN<!!>', Msg_Trustee_EG_Cryptograms(election_setup, 'Trustee<!!>TRUSTEE_THRESHOLD<!!>', 'Trustee<!!>TN<!!>', ballot_order, ballot_set, shuffle_proof), sig_last_mix<!!>TN<!!>, %idx_last_mix<!!>TN<!!>)ifelse(eval(TN < TRUSTEE_THRESHOLD), eval(1), <!,
      !>, <!!>)!>) ]
  --[ TAS_TrusteeMixing_Complete_Trace(ballot_order, ballot_set, shuffle_proof) ]->
    [ TAS_State_BeginTrusteeDecryption() ]
