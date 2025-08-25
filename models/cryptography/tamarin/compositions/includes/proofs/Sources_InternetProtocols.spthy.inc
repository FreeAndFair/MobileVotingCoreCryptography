simplify
solve( (∃ m1 m2 m3 m4 #i.
         (IN_SECURE_RECEIVE( m1, m2, m3, m4 ) @ #i)
        ∧
         ∀ #j. (SecureChannel_In( m1, m2, m3, m4 ) @ #j) ⇒ ¬(#j < #i))  ∥
       (∃ m1 m2 m3 m4 m5 m6 m7 #i.
         (IN_BALLOTCHECK_VA_CHECK( m1, m2, m3, m4, m5, m6, m7 ) @ #i)
        ∧
         ∀ #j.
          (OUT_BALLOTCHECK_VA_CHECK( m1, m2, m3, m4, m5, m6, m7 ) @ #j)
         ⇒
          ¬(#j < #i))  ∥
       (∃ m x #i.
         (IN_PSEUDO_TERM( m, x ) @ #i)
        ∧
         (∀ #j. (!KU( x ) @ #j) ⇒ ¬(#j < #i)) ∧
         (∀ #j. (OUT_PSEUDO_TERM( m ) @ #j) ⇒ ¬(#j < #i))) )
  case case_1
  solve( IN_SECURE_RECEIVE( m1, m2, m3, m4 ) @ #i )
    case BallotCheck_DBB_ForwardRandomizers
    solve( DBB_State_ForwardRandomizers( ~ec, ~va_id, ~cid_va, ~bca_id,
                                         ~cid_bca,
                                         <
                                          <'BCA_Check_Request', ~ec, tracker, pk_bca_encrypt,
                                           pk_bca_sign>,
                                          sig_bca_req>
           ) ▶₀ #i )
      case BallotCheck_DBB_ReceiveCheckRequest
      solve( SecureReceive( ~cid_va, ~va_id, <~ec, 'DBB'>,
                            <
                             <'VA_Check_Randomizers',
                              <
                               <'BCA_Check_Request', ~ec,
                                h(<
                                   <'BBEntry_Ballot_Submission', ~ec, timestamp,
                                    <'VA_Submit_Ballot', ~ec, pseudo, pk_voter, ~bs,
                                     ny_encrypt_c1(x, x.1, x.2), ny_encrypt_c2(x, x.1, x.2),
                                     ny_encrypt_p(x, x.1, x.2)>,
                                    sig>,
                                   ch>),
                                pk_bca_encrypt, pk_bca_sign>,
                               sig_bca_req>,
                              encrypted_randomizers, pk_voter.1>,
                             sig_randomizers>
             ) ▶₁ #i )
        case SecureChannel_Receive_case_1
        by contradiction /* from formulas */
      next
        case SecureChannel_Receive_case_2
        by contradiction /* from formulas */
      qed
    qed
  next
    case BallotCheck_DBB_ReceiveCheckRequest
    solve( SecureReceive( ~cid_bca, ~bca_id, <~ec, 'DBB'>,
                          <<'BCA_Check_Request', ~ec, tracker, pk_bca_encrypt, pk_bca_sign>,
                           sig_bca_req>
           ) ▶₃ #i )
      case SecureChannel_Receive_case_1
      by contradiction /* from formulas */
    next
      case SecureChannel_Receive_case_2
      by contradiction /* from formulas */
    qed
  next
    case BallotCheck_VA_RequestRandomizers
    solve( SecureReceive( ~cid, <~ec, 'DBB'>, ~va_id,
                          <'DBB_Check_Request',
                           <'BCA_Check_Request', ~ec, tracker, pk_bca_encrypt, pk_bca_sign>,
                           sig_bca_req>
           ) ▶₃ #i )
      case SecureChannel_Receive_case_1
      by contradiction /* from formulas */
    next
      case SecureChannel_Receive_case_2
      by contradiction /* from formulas */
    qed
  next
    case VoterAuthentication_AS_AuthenticationRequest
    solve( SecureReceive( ~cid, m2, 'AS',
                          <'EAS_Request_Authentication_Session', ~project_id, ~api_key>
           ) ▶₁ #i )
      case SecureChannel_Receive_case_1
      by contradiction /* from formulas */
    next
      case SecureChannel_Receive_case_2
      by contradiction /* from formulas */
    qed
  next
    case VoterAuthentication_AS_ReportAuthenticationResult
    solve( SecureReceive( ~cid, m2, 'AS',
                          <'EAS_Request_Authentication_Result', ~session_id>
           ) ▶₁ #i )
      case SecureChannel_Receive_case_1
      by contradiction /* from formulas */
    next
      case SecureChannel_Receive_case_2
      by contradiction /* from formulas */
    qed
  next
    case VoterAuthentication_AS_ReportIncompleteAuthenticationResult
    solve( SecureReceive( ~cid, m2, 'AS',
                          <'EAS_Request_Authentication_Result', ~session_id>
           ) ▶₁ #i )
      case SecureChannel_Receive_case_1
      by contradiction /* from formulas */
    next
      case SecureChannel_Receive_case_2
      by contradiction /* from formulas */
    qed
  next
    case VoterAuthentication_EAS_ReceiveAuthenticationComplete
    solve( SecureReceive( ~cid_va, ~va_id, <~ec, 'EAS'>,
                          <'VA_Authentication_Complete', ~ec, pk_voter, ~token>
           ) ▶₁ #i )
      case SecureChannel_Receive_case_1
      by contradiction /* from formulas */
    next
      case SecureChannel_Receive_case_2
      by contradiction /* from formulas */
    qed
  next
    case VoterAuthentication_EAS_RequestAuthentication
    solve( SecureReceive( ~cid_va, ~va_id, <~ec, 'EAS'>,
                          <'VA_Request_Authentication', ~ec, pk_voter>
           ) ▶₂ #i )
      case SecureChannel_Receive_case_1
      by contradiction /* from formulas */
    next
      case SecureChannel_Receive_case_2
      by contradiction /* from formulas */
    qed
  next
    case VoterAuthentication_VA_ReceiveAuthenticationResult_Eligible
    solve( SecureReceive( ~cid, <~ec, 'EAS'>, ~va_id,
                          <'EAS_Authentication_Result', 'eligible', ~ec, pseudo,
                           pk(~sk_voter), ballot_style>
           ) ▶₁ #i )
      case SecureChannel_Receive_case_1
      by contradiction /* from formulas */
    next
      case SecureChannel_Receive_case_2
      by contradiction /* from formulas */
    qed
  qed
next
  case case_2
  solve( VA_State_CheckOrCast( ~ec, ~va_id, $V, ~ballot, m5, ~r, m7
         ) ▶₀ #i )
    case BallotCheck_VA_CheckResult_OK
    by contradiction /* from formulas */
  next
    case BallotSubmission_VA_BallotSubmitResponse_BallotTracker_Success
    by contradiction /* from formulas */
  qed
next
  case case_3
  solve( !BB_Entry( ~bbid,
                    <'BBEntry_Ballot_Submission', ~ec, timestamp,
                     <'VA_Submit_Ballot', ~ec, x, pk(~sk_voter), ballot_style,
                      cryptograms>,
                     sign(<'VA_Submit_Ballot', ~ec, x, pk(~sk_voter), ballot_style,
                           cryptograms>,
                          '1', ~sk_voter)
                    >,
                    tracker, %idx
         ) ▶₃ #i )
    case BulletinBoard_Append
    solve( SecureReceive( ~cid, <~ec, 'DBB'>, ~va_id,
                          <'DBB_Ballot_Tracker', ~ec,
                           h(<
                              <'BBEntry_Ballot_Submission', ~ec, timestamp,
                               <'VA_Submit_Ballot', ~ec, x, pk(~sk_voter), ballot_style,
                                cryptograms>,
                               sign(<'VA_Submit_Ballot', ~ec, x, pk(~sk_voter), ballot_style,
                                     cryptograms>,
                                    '1', ~sk_voter)
                              >,
                              ch>)
                          >
           ) ▶₄ #i )
      case SecureChannel_Receive_case_1
      by contradiction /* from formulas */
    next
      case SecureChannel_Receive_case_2
      by contradiction /* from formulas */
    next
      case SecureChannel_Receive_case_3
      solve( BB_Append_Request( ~bbid,
                                <'BBEntry_Ballot_Submission', ~ec, timestamp,
                                 <'VA_Submit_Ballot', ~ec, x, pk(~sk_voter), ballot_style,
                                  cryptograms>,
                                 sign(<'VA_Submit_Ballot', ~ec, x, pk(~sk_voter), ballot_style,
                                       cryptograms>,
                                      '1', ~sk_voter)
                                >,
                                %idx
             )[+] ▶₂ #vr )
        case BallotSubmission_DBB_AppendSubmittedBallot_case_1
        by contradiction /* from formulas */
      next
        case BallotSubmission_DBB_AppendSubmittedBallot_case_2
        by contradiction /* from formulas */
      qed
    qed
  qed
qed
