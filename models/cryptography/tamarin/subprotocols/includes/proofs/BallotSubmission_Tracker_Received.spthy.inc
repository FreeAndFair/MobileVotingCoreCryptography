simplify
solve( !BB_Entry( ~bbid,
                  <'BBEntry_Ballot_Submission', ~ec, timestamp,
                   <'VA_Submit_Ballot', ~ec, pseudo, pk(~sk_voter), ballot_style,
                    cryptograms>,
                   sign(<'VA_Submit_Ballot', ~ec, pseudo, pk(~sk_voter),
                         ballot_style, cryptograms>,
                        '1', ~sk_voter)
                  >,
                  tracker, %idx
       ) ▶₃ #i )
  case BulletinBoard_Append
  solve( BB_Append_Request( ~bbid,
                            <'BBEntry_Ballot_Submission', ~ec, timestamp,
                             <'VA_Submit_Ballot', ~ec, pseudo, pk(~sk_voter), ballot_style,
                              cryptograms>,
                             sign(<'VA_Submit_Ballot', ~ec, pseudo, pk(~sk_voter),
                                   ballot_style, cryptograms>,
                                  '1', ~sk_voter)
                            >,
                            %idx
         )[+] ▶₂ #vr )
    case BallotSubmission_DBB_AppendSubmittedBallot_case_1
    solve( SecureReceive( ~cid, <~ec, 'DBB'>, ~va_id,
                          <'DBB_Ballot_Tracker', ~ec,
                           h(<
                              <'BBEntry_Ballot_Submission', ~ec, %ts,
                               <'VA_Submit_Ballot', ~ec, pseudonym($V.1), pk(~sk_voter), ~bs,
                                ny_encrypt_c1(x, pk(x.1), x.2), ny_encrypt_c2(x, pk(x.1), x.2),
                                ny_encrypt_p(x, pk(x.1), x.2)>,
                               sign(<'VA_Submit_Ballot', ~ec, pseudonym($V.1), pk(~sk_voter),
                                     ~bs, ny_encrypt_c1(x, pk(x.1), x.2),
                                     ny_encrypt_c2(x, pk(x.1), x.2), ny_encrypt_p(x, pk(x.1), x.2)>,
                                    '1', ~sk_voter)
                              >,
                              h(<~ec, ~bbid>)>)
                          >
           ) ▶₄ #i )
      case SecureChannel_Receive_case_1
      solve( SecureReceive( ~cid, ~va_id, <~ec, 'DBB'>,
                            <
                             <'VA_Submit_Ballot', ~ec, pseudonym($V.1), pk(~sk_voter), ~bs,
                              ny_encrypt_c1(x, pk(x.1), x.2), ny_encrypt_c2(x, pk(x.1), x.2),
                              ny_encrypt_p(x, pk(x.1), x.2)>,
                             sign(<'VA_Submit_Ballot', ~ec, pseudonym($V.1), pk(~sk_voter),
                                   ~bs, ny_encrypt_c1(x, pk(x.1), x.2),
                                   ny_encrypt_c2(x, pk(x.1), x.2), ny_encrypt_p(x, pk(x.1), x.2)>,
                                  '1', ~sk_voter)
                            >
             ) ▶₁ #vr.9 )
        case SecureChannel_Receive_case_1
        solve( VA_State_BallotSubmitResponse( ~ec, ~va_id, ~cid, $V,
                                              ~ballot,
                                              <ny_encrypt_c1(~ballot.1, pk(~sk_election), ~r),
                                               ny_encrypt_c2(~ballot.1, pk(~sk_election), ~r),
                                               ny_encrypt_p(~ballot.1, pk(~sk_election), ~r)>,
                                              ~r.1
               ) ▶₀ #i )
          case BallotSubmission_VA_PresentBallot
          solve( DBB_Clock( %ts ) ▶₁ #vr.8 )
            case BallotSubmission_DBB_AppendSubmittedBallot_case_1
            by sorry
          next
            case BallotSubmission_DBB_AppendSubmittedBallot_case_2
            by sorry
          next
            case BallotSubmission_Initialize_DBBTimestamp
            solve( DBB_State_ReceiveAuthorizeVoter( ~ec, %idx ) ▶₀ #vr.10 )
              case Mock_Finalize_Election_Setup
              solve( !VA_Eligible_Voter( ~ec, ~va_id, pseudonym($V), ~sk_voter,
                                         ~bs
                     ) ▶₁ #i )
                case Mock_Voter_Authentication
                solve( !BB_Root( ~ec, ~bbid, ~ec, bb_root_hash ) ▶₂ #i )
                  case BulletinBoard_Create
                  solve( BB_Trace_Entry( ~bbid, ~ec, h(<~ec, ~bbid>), %1 ) @ #j )
                    case BulletinBoard_Create
                    solve( BB_Current( ~bbid, c, h(<~ec, ~bbid>), %1 )[+] ▶₁ #vr )
                      case BulletinBoard_Create
                      solve( BallotStyleCount( ~ec, %idx_bs_unused ) ▶₀ #vr.2 )
                        case Mock_BallotStyle
                        solve( VoterCount( ~ec, %idx_ev_unused ) ▶₀ #vr.3 )
                          case Mock_EC_And_Initial_Counters
                          solve( VoterCount( ~ec, %i.3 ) ▶₀ #vr.5 )
                            case Mock_EC_And_Initial_Counters
                            solve( VoterCount( ~ec, %idx_ev ) ▶₀ #vr.10 )
                              case Mock_EC_And_Initial_Counters
                              solve( BallotStyleCount( ~ec, %idx_bs ) ▶₀ #vr.5 )
                                case Mock_BallotStyle
                                by sorry /* removed */
                              next
                                case Mock_EC_And_Initial_Counters
                                solve( BallotStyleCount( ~ec, %i.2 ) ▶₀ #vr.4 )
                                  case Mock_BallotStyle
                                  solve( BallotStyleCount( ~ec, %i.2 ) ▶₀ #vr.18 )
                                    case Mock_BallotStyle
                                    by sorry
                                  next
                                    case Mock_EC_And_Initial_Counters
                                    solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.16 )
                                      case Mock_BallotStyle
                                      simplify
                                      by contradiction /* cyclic */
                                    next
                                      case Mock_EC_And_Initial_Counters
                                      SOLVED // trace found
                                    qed
                                  qed
                                next
                                  case Mock_EC_And_Initial_Counters
                                  simplify
                                  by contradiction /* cyclic */
                                qed
                              qed
                            next
                              case Mock_VoterRegistration_Eligible
                              by sorry
                            qed
                          next
                            case Mock_VoterRegistration_Eligible
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
                    qed
                  qed
                qed
              qed
            next
              case Mock_Voter_Authentication
              by sorry
            qed
          qed
        qed
      next
        case SecureChannel_Receive_case_2
        by sorry
      qed
    next
      case SecureChannel_Receive_case_2
      by sorry
    qed
  next
    case BallotSubmission_DBB_AppendSubmittedBallot_case_2
    by sorry
  qed
qed
