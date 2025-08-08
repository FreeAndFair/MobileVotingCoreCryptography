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

/*
  Shuffles and Shuffle Proofs

  These functions abstract the shuffling of ballots and the proofs
  of shuffle. They bear little to no resemblance to the actual
  reencryption mixnet we are implementing (though we may be able
  to do a model closer to that implementation in the future thanks
  to a Tamarin extension allowing associative/commutative operators,
  see https://hal.science/hal-05196126 for details), but should
  suffice for our protocol modeling purposes.

  A list of ballots is represented as a single Tamarin value for the
  ordering of the ballots, and a Tamarin multiset for the set of
  ballots. Note that the ordering is itself an abstraction and cannot
  really be used to assign an ordering to the items in the multiset,
  which are themselves encryptions of single Tamarin values (the same
  idea as used in the ballot submission/casting/checking protocols).

  The "shuffle_order" function takes a ballot order, a ballot set,
  and some randomness as parameters and generates a shuffled ballot order.

  The "shuffle_proof" function takes a ballot order, a ballot set,
  and some randomness as parameters and generates a "proof" value that
  can be verified against the shuffled ballot order and ballot set.

  The "verify_shuffle" function takes a ballot order, a ballot set, and
  a proof value and verifies that the proof value was generated using the
  same parameters as the ballot order.

  The "unshuffle_order" function takes a shuffled ballot order, a ballot
  set, and the shuffle randomness as parameters and returns the ballot order
  passed to "shuffle_order".

  The basic idea, then, is to be able to prove (though we will not likely
  do this because of time constraints) that, without the shuffle randomness
  from every trustee that participates in the shuffle, it is impossible for
  an adversary to reconstruct the original ballot order.
 */

functions: shuffle_order/3,
           shuffle_proof/3,
           verify_shuffle/3,
           unshuffle_order/3 [destructor]

equations: verify_shuffle(shuffle_order(o, s, r), s, shuffle_proof(o, s, r)) = true,
           unshuffle_order(shuffle_order(o, s, r), s, r) = o

/* Trustee Mixing Rules */

/*
  This rule checks the encryption proofs for all the ballots in the ballot set
  (since it's just one ballot here, this is straightforward), signs the ballot
  set, and posts it to the bulletin board.

  Validation checks performed explicitly (via restriction):
    - the encryption proof(s) are valid
    - no error conditions have previously occurred

  Validation checks performed implicitly:
    - the election setup information is valid (assumed from a previous
      protocol)
    - the initial list of ballots was posted correctly (pattern matching)

  Note that "b", "k", and "r" here actually pattern match the input values to
  the ballot set encryption. This is not a capability that the trustee has in
  real life, but it does help Tamarin to generate fewer variants of this rule,
  and should thus also help us eliminate partial deconstructions later on.
  Also, since this rule only executes if the proof verifies anyway, this is
  essentially a duplicative pattern match.

  Since we are pattern matching these values (even though we are not using
  them), this rule would fail the derivation check; we therefore specify
  "no_derivcheck" here.
*/
rule TrusteeMixing_Check_Encryption_Proofs_Success [role="Trustee", no_derivcheck]:
  let initial_trustee = 'Trustee0'
      c1 = ny_encrypt_c1(b, k, r)
      c2 = ny_encrypt_c2(b, k, r)
      p = ny_encrypt_p(b, k, r)
      ballot_set = <c1, c2, p>
      stripped_ballot_set = <c1, c2>
      valid_encryption = ny_check(c1, c2, p)
      msg_initial_ballots = Msg_Trustee_NY_Cryptograms(election_setup, initial_trustee, initial_trustee, initial_ballot_order, ballot_set)
      msg_checked_ballots = Msg_Trustee_EG_Cryptograms(election_setup, initial_trustee, trustee, initial_ballot_order, stripped_ballot_set, 'no shuffle') in
    [ !Trustee_Mix_Active(trustee),
      !Trustee_BBEntry(trustee, initial_trustee, msg_initial_ballots, sig_initial_ballots, %idx_initial_ballots),
      !Trustee_ElectionSetup(trustee, election_setup),
      !Trustee_Secret_Keys(trustee, sk_sign, sk_encrypt_unused) ]
  --[ Trustee_Check_Encryption_Proofs_Success_Trace(trustee, ballot_set),
      Unique(<'Trustee_Check_Encryption_Proofs', trustee>),
      Trustee_Sent_Msg_Trace(trustee, msg_checked_ballots),
      Eq(valid_encryption, true),
      No_Trustee_Trace_Errors(trustee),
      IN_TRUSTEE_BBENTRY(trustee, initial_trustee, msg_initial_ballots, sig_initial_ballots, %idx_initial_ballots),
      IN_BALLOTSET_C1_TERM(c1, b),
      IN_BALLOTSET_C2_TERM(c2, b),
      IN_BALLOTSET_P_TERM(p, b) ]->
    [ !Trustee_Check_Encryption_Proofs_Success(trustee, ballot_set),
      Trustee_Message_Submit(trustee, msg_checked_ballots, sign(msg_checked_ballots, '1', sk_sign)) ]

/*
  This rule causes an error condition when an invalid ballot is posted in
  the initial set.
*/
rule TrusteeMixing_Check_Encryption_Proofs_Failure [role="Trustee"]:
  let initial_trustee = 'Trustee0'
      ballot_set = <c1, c2, p>
      valid_encryption = ny_check(c1, c2, p)
      msg_initial_ballots = Msg_Trustee_NY_Cryptograms(election_setup, initial_trustee, initial_trustee, initial_ballot_order, ballot_set) in
    [ !Trustee_Mix_Active(trustee),
      !Trustee_BBEntry(trustee, initial_trustee, msg_initial_ballots, sig_initial_ballots, %idx_initial_ballots),
      !Trustee_ElectionSetup(trustee, election_setup) ]
  --[ Trustee_Check_Encryption_Proofs_Failure_Trace(trustee, ballot_set),
      Unique(<'Trustee_Check_Encryption_Proofs', trustee>),
      Neq(valid_encryption, true),
      No_Trustee_Trace_Errors(trustee),
      Trustee_Trace_Error(trustee, <'invalid ballot encryption detected', ballot_set>) ]->
    [ !TerminalError(trustee) /* no further trustee actions */ ]

forloop(<!SN!>, <!1!>, TRUSTEE_THRESHOLD, <!
/*
  This rule performs the shuffle for trustee <!!>SN<!!>. It waits until trustee <!!>eval(SN - 1)<!!>
  posts its shuffle and it has been signed by all participating trustees (it
  is signed by trustee <!!>eval(SN - 1)<!!> when it is posted), then shuffles the ballots
  and posts them to the board.
  ifelse(eval(SN == 1), eval(1), <!
  Note that this rule is actually using the  "shuffle" from trustee 0,
  which is really just all the trustees signing the initial ballot set after
  checking the proofs.
  !>)dnl

  Validation checks performed explicitly (via restrictions):
    - no error conditions have previously occurred

  Validation checks performed implicitly:
    - the shuffle proof is correct (checked in a previous step, when we signed
      the message in the first place)
    - all message signatures are valid (only messages with valid signatures can
      be posted to the board)
    - all trustees have signed the previous set of shuffled ballots, and they
      all signed the same set (pattern matching)
 */
rule TrusteeMixing_Trustee_<!!>SN<!!>_Shuffle [role="Trustee"]:
  let trustee = 'Trustee<!!>SN<!!>'
      prev_trustee = 'Trustee<!!>eval(SN - 1)<!!>'
      forloop(<!TN!>, <!1!>, TRUSTEE_THRESHOLD, <!msg_signed_shuffle<!!>TN<!!> = Msg_Trustee_EG_Cryptograms(election_setup, prev_trustee, 'Trustee<!!>TN<!!>', prev_ballot_order, ballot_set, prev_shuffle_proof)<!!>ifelse(eval(TN < TRUSTEE_THRESHOLD), eval(1), <!
      !>, <!!>)!>)
      my_shuffle_order = shuffle_order(prev_ballot_order, ballot_set, ~r)
      my_shuffle_proof = shuffle_proof(prev_ballot_order, ballot_set, ~r)
      msg_shuffled_ballots = Msg_Trustee_EG_Cryptograms(election_setup, trustee, trustee, my_shuffle_order, ballot_set, my_shuffle_proof) in
    [ forloop(<!TN!>, <!1!>, TRUSTEE_THRESHOLD, <!!Trustee_BBEntry(trustee, 'Trustee<!!>TN<!!>', msg_signed_shuffle<!!>TN<!!>, sig_signed_shuffle<!!>TN<!!>, %idx_signed_shuffle<!!>TN<!!>)<!!>ifelse(eval(TN < TRUSTEE_THRESHOLD), eval(1), <!,
      !>, <!!>)!>),
      !Trustee_ElectionSetup(trustee, election_setup),
      !Trustee_Secret_Keys(trustee, sk_sign, sk_encrypt_unused),
      Fr(~r) ]
  --[ Trustee_Shuffle_Trace(trustee, my_shuffle_order, ballot_set, my_shuffle_proof),
      Unique(<'Trustee_Shuffle', trustee>),
      Unique(<'Trustee_Sign_Shuffle', trustee, trustee>),
      Trustee_Sent_Msg_Trace(trustee, msg_shuffled_ballots),
      No_Trustee_Trace_Errors(trustee),
      forloop(<!TN!>, <!1!>, TRUSTEE_THRESHOLD, <!IN_TRUSTEE_BBENTRY(trustee, 'Trustee<!!>TN<!!>', msg_signed_shuffle<!!>TN<!!>, sig_signed_shuffle<!!>TN<!!>, %idx_signed_shuffle<!!>TN<!!>)<!!>ifelse(eval(TN < TRUSTEE_THRESHOLD), eval(1), <!,
      !>, <!!>)!>),
      OUT_SHUFFLE_PROOF_TERM(my_shuffle_proof),
      OUT_SHUFFLE_ORDER_TERM(my_shuffle_order) ]->
    [ !Trustee_Shuffle(trustee, my_shuffle_order, ballot_set, my_shuffle_proof),
      !Trustee_Shuffle_Randomness(trustee, ~r),
      Trustee_Message_Submit(trustee, msg_shuffled_ballots, sign(msg_shuffled_ballots, '1', sk_sign)) ]
!>)dnl

/*
  This rule signs a shuffle performed by another trustee that hasn't yet
  been signed by this trustee, and posts the signed shuffle to the board.

  Validation checks performed explicitly (via restrictions):
    - this shuffle has not yet been signed by this trustee
    - no error conditions have previously occurred

  Validation checks performed implicitly:
    - all message signatures are valid (only messages with valid signatures can
      be posted to the board)
    - the shuffle proof is valid (pattern matching on prev_ballot_order and
      prev_shuffle_proof), though there is still a (redundant) restriction for
      this as well

  Note that "prev_ballot_order" and "prev_shuffle_proof" here actually pattern
  match the input values to the shuffle. This is not a capability that the
  trustee has in real life, but it does help Tamarin to generate fewer variants
  of this rule, and should thus also help us eliminate partial deconstructions
  later on.

  Since we are pattern matching these values (even though we are not using
  them), this rule would fail the derivation check; we therefore specify
  "no_derivcheck" here.
 */
rule TrusteeMixing_Trustee_Sign_Shuffle [role="Trustee", no_derivcheck]:
  let prev_ballot_order = shuffle_order(prev_prev_ballot_order, ballot_set, prev_r)
      prev_shuffle_proof = shuffle_proof(prev_prev_ballot_order, ballot_set, prev_r)
      msg_shuffled_ballots = Msg_Trustee_EG_Cryptograms(election_setup, shuffle_trustee, shuffle_trustee, prev_ballot_order, ballot_set, prev_shuffle_proof)
      shuffle_proof_valid = verify_shuffle(prev_ballot_order, ballot_set, prev_shuffle_proof)
      msg_signed_shuffled_ballots = Msg_Trustee_EG_Cryptograms(election_setup, shuffle_trustee, trustee, prev_ballot_order, ballot_set, prev_shuffle_proof) in
    [ !Trustee_Mix_Active(trustee),
      !Trustee_Mix_Active(shuffle_trustee),
      !Trustee_BBEntry(trustee, shuffle_trustee, msg_shuffled_ballots, sig_shuffled_ballots, %idx_shuffled_ballots),
      !Trustee_ElectionSetup(trustee, election_setup),
      !Trustee_Secret_Keys(trustee, sk_sign, sk_encrypt_unused) ]
  --[ Trustee_Sign_Shuffle_Trace(trustee, shuffle_trustee),
      Unique(<'Trustee_Sign_Shuffle', trustee, shuffle_trustee>),
      Neq(trustee, shuffle_trustee),
      Eq(shuffle_proof_valid, true), /* shuffle proof is valid */
      Trustee_Sent_Msg_Trace(trustee, msg_signed_shuffled_ballots),
      No_Trustee_Trace_Errors(trustee),
      IN_SHUFFLE_ORDER_TERM(prev_ballot_order, prev_prev_ballot_order),
      IN_SHUFFLE_ORDER_TERM(prev_ballot_order, ballot_set),
      IN_SHUFFLE_PROOF_TERM(prev_shuffle_proof, prev_prev_ballot_order),
      IN_SHUFFLE_PROOF_TERM(prev_shuffle_proof, ballot_set) ]->
    [ !Trustee_Sign_Shuffle(trustee, shuffle_trustee),
      Trustee_Message_Submit(trustee, msg_signed_shuffled_ballots, sign(msg_signed_shuffled_ballots, '1', sk_sign)) ]

/*
  This rule causes an error condition when an invalid shuffle is posted by
  any trustee.

  Note that shuffle_trustee and signing_trustee can be different here; we can
  detect an invalid shuffle proof posted by anyone, not just the original
  shuffle trustee.
 */
rule TrusteeMixing_Trustee_Detect_Invalid_Shuffle [role="Trustee"]:
  let msg_invalid_shuffle = Msg_Trustee_EG_Cryptograms(election_setup, shuffle_trustee, signing_trustee, ballot_order, ballot_set, shuffle_proof)
      shuffle_proof_valid = verify_shuffle(ballot_order, ballot_set, shuffle_proof) in
    [ !Trustee_Mix_Active(trustee),
      !Trustee_BBEntry(trustee, signing_trustee, msg_invalid_shuffle, sig_invalid_shuffle, %idx_invalid_shuffle),
      !Trustee_ElectionSetup(trustee, election_setup),
      !Trustee_Secret_Keys(trustee, sk_sign, sk_encrypt_unused) ]
  --[ Trustee_Detect_Invalid_Shuffle_Trace(trustee, shuffle_trustee, signing_trustee),
      Unique(<'Trustee_Detect_Invalid_Shuffle', trustee, shuffle_trustee, signing_trustee>),
      Neq(shuffle_proof_valid, true), /* shuffle proof is invalid */
      No_Trustee_Trace_Errors(trustee),
      Trustee_Trace_Error(trustee, <'invalid shuffle detected', shuffle_trustee>) ]->
    [ !TerminalError(trustee) /* no further trustee actions */ ]
