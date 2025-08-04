simplify
solve( SecureReceive( ~cid_bca, ~bca_id, <~ec, 'DBB'>,
                      <<'BCA_Check_Request', ~ec, tracker, pk_bca_encrypt, pk_bca_sign>,
                       sig_bca_req>
       ) ▶₃ #i )
  case SecureChannel_Receive_case_1
  solve( !BB_Entry( ~bbid,
                    <'BBEntry_Ballot_Submission', ~ec, timestamp,
                     signed_msg_submit_ballot>,
                    h(<
                       <'BBEntry_Ballot_Submission', ~ec, %ts,
                        <'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter),
                         ~ballot_style, ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                         ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                         ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                        sign(<'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter),
                              ~ballot_style, ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                              ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                              ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                             '1', ~sk_voter.1)
                       >,
                       h(<~ec, ~bbid.1>)>),
                    %ballot_idx
         ) ▶₁ #i )
    case BulletinBoard_Append
    solve( BB_Append_Request( ~bbid.1,
                              <'BBEntry_Ballot_Submission', ~ec, %ts,
                               <'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter),
                                ~ballot_style, ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                               sign(<'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter),
                                     ~ballot_style, ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                     ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                     ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                    '1', ~sk_voter.1)
                              >,
                              %1
           )[+] ▶₂ #vr.5 )
      case Mock_AppendSubmittedBallot
      solve( BB_Append_Request( ~bbid,
                                <'BBEntry_Ballot_Submission', ~ec, %ts,
                                 <'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter),
                                  ~ballot_style, ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                  ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                  ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                 sign(<'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter),
                                       ~ballot_style, ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                       ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                       ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                      '1', ~sk_voter.1)
                                >,
                                %idx
             )[+] ▶₂ #vr.20 )
        case Mock_AppendSubmittedBallot
        solve( !DBB_Submitted_Ballot( ~ec, ~va_id, ~cid_va, pseudo,
                                      <
                                       <'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter),
                                        ~ballot_style,
                                        ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                        ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                        ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                       sign(<'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter),
                                             ~ballot_style,
                                             ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                             ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                             ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                            '1', ~sk_voter.1)
                                      >
               ) ▶₂ #i )
          case Mock_Ballot_Submission
          solve( !BB_Root( ~ec, ~bbid, r_unused, rh_unused ) ▶₀ #i )
            case BulletinBoard_Create
            solve( BB_Trace_Entry( ~bbid, ~ec, h(<~ec, ~bbid>), %1 ) @ #j )
              case BulletinBoard_Create
              solve( BB_Current( ~bbid, c, h(<~ec, ~bbid>), %1 )[+] ▶₁ #vr.4 )
                case BulletinBoard_Create
                solve( DBB_State_ReceiveAuthorizeVoter( ~ec, %i.1 ) ▶₀ #vr.6 )
                  case Mock_Finalize_Election_Setup
                  solve( BallotStyleCount( ~ec, %idx_bs ) ▶₀ #vr.10 )
                    case Mock_BallotStyle
                    solve( VoterCount( ~ec, %idx_ev ) ▶₀ #vr.11 )
                      case Mock_EC_And_Initial_Counters
                      solve( BallotStyleCount( ~ec, %idx_bs_unused ) ▶₀ #vr.12 )
                        case Mock_BallotStyle
                        solve( VoterCount( ~ec, %idx_ev_unused ) ▶₀ #vr.13 )
                          case Mock_EC_And_Initial_Counters
                          solve( DBB_State_ReceiveAuthorizeVoter( ~ec, %i.5 ) ▶₀ #vr.15 )
                            case Mock_Finalize_Election_Setup
                            solve( VoterCount( ~ec, %i.4 ) ▶₀ #vr.14 )
                              case Mock_EC_And_Initial_Counters
                              solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.14 )
                                case Mock_BallotStyle
                                solve( BallotStyleCount( ~ec, %i.3 ) ▶₀ #vr.13 )
                                  case Mock_BallotStyle
                                  solve( BallotStyleCount( ~ec, %i.2 ) ▶₀ #vr.16 )
                                    case Mock_BallotStyle
                                    by sorry
                                  next
                                    case Mock_EC_And_Initial_Counters
                                    solve( BallotStyleCount( ~ec, %i.2 ) ▶₀ #vr.18 )
                                      case Mock_BallotStyle
                                      solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.17 )
                                        case Mock_BallotStyle
                                        by sorry
                                      next
                                        case Mock_EC_And_Initial_Counters
                                        solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.17 )
                                          case Mock_BallotStyle
                                          by sorry
                                        next
                                          case Mock_EC_And_Initial_Counters
                                          solve( DBB_Clock( %ts ) ▶₂ #vr.8 )
                                            case Mock_AppendSubmittedBallot_case_1
                                            by sorry
                                          next
                                            case Mock_AppendSubmittedBallot_case_2
                                            by sorry
                                          next
                                            case Mock_DBBTimestamp
                                            SOLVED // trace found
                                          qed
                                        qed
                                      qed
                                    next
                                      case Mock_EC_And_Initial_Counters
                                      simplify
                                      by contradiction
                                    qed
                                  qed
                                next
                                  case Mock_EC_And_Initial_Counters
                                  simplify
                                  by contradiction
                                qed
                              next
                                case Mock_EC_And_Initial_Counters
                                by sorry
                              qed
                            next
                              case Mock_VoterRegistration_Eligible
                              by sorry
                            qed
                          next
                            case Mock_Voter_Authentication
                            by sorry
                          qed
                        next
                          case Mock_VoterRegistration_Eligible
                          by sorry
                        qed
                      next
                        case Mock_EC_And_Initial_Counters
                        by sorry
                      qed
                    next
                      case Mock_VoterRegistration_Eligible
                      by sorry
                    qed
                  next
                    case Mock_EC_And_Initial_Counters
                    by sorry
                  qed
                next
                  case Mock_Voter_Authentication
                  by sorry
                qed
              qed
            qed
          qed
        qed
      qed
    qed
  qed
next
  case SecureChannel_Receive_case_2
  by sorry
next
  case SecureChannel_Receive_case_3
  by sorry
next
  case SecureChannel_Receive_case_4
  by sorry
qed
