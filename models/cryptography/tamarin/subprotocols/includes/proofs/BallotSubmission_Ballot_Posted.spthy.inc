simplify
solve( !BB_Root( ~ec, bbid, r_unused, rh_unused ) ▶₁ #i )
  case BulletinBoard_Create
  solve( !BB_Entry( ~bbid, msg, tracker, %idx ) ▶₂ #i )
    case BulletinBoard_Append
    solve( (¬(%1 ⊏ %idx))  ∥ (#vr < #j) )
      case case_1
      solve( BB_Trace_Entry( ~bbid, ~ec, h(<~ec, ~bbid>), %1 ) @ #j )
        case BulletinBoard_Create
        solve( BB_Current( ~bbid, c, h(<~ec, ~bbid>), %1 )[+] ▶₁ #vr.7 )
          case BulletinBoard_Create
          solve( BB_Append_Request( ~bbid, msg, %1 )[+] ▶₂ #vr.7 )
            case BallotSubmission_DBB_AppendSubmittedBallot
            solve( DBB_Clock( %ts ) ▶₁ #vr.8 )
              case BallotSubmission_DBB_AppendSubmittedBallot_case_1
              by sorry
            next
              case BallotSubmission_DBB_AppendSubmittedBallot_case_2
              by sorry
            next
              case BallotSubmsision_Mock_DBBTimestamp
              solve( DBB_State_ConfirmBallotPosting( ~ec, ~va_id, ~cid, pseudo,
                                                     <'BBEntry_Ballot_Submission', ~ec, %1,
                                                      <'VA_Submit_Ballot', ~ec, pseudonym($V),
                                                       pk(~sk_voter), ~bs,
                                                       ny_encrypt_c1(x, pk(x.1), x.2),
                                                       ny_encrypt_c2(x, pk(x.1), x.2),
                                                       ny_encrypt_p(x, pk(x.1), x.2)>,
                                                      sign(<'VA_Submit_Ballot', ~ec, pseudonym($V),
                                                            pk(~sk_voter), ~bs,
                                                            ny_encrypt_c1(x, pk(x.1), x.2),
                                                            ny_encrypt_c2(x, pk(x.1), x.2),
                                                            ny_encrypt_p(x, pk(x.1), x.2)>,
                                                           x.3, ~sk_voter)
                                                     >,
                                                     (%1%+%1)
                     ) ▶₀ #i )
                case BallotSubmission_DBB_AppendSubmittedBallot
                solve( SecureReceive( ~cid, ~va_id, <~ec, 'DBB'>,
                                      <
                                       <'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter), ~bs,
                                        ny_encrypt_c1(x, pk(x.1), x.2),
                                        ny_encrypt_c2(x, pk(x.1), x.2),
                                        ny_encrypt_p(x, pk(x.1), x.2)>,
                                       sign(<'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter),
                                             ~bs, ny_encrypt_c1(x, pk(x.1), x.2),
                                             ny_encrypt_c2(x, pk(x.1), x.2),
                                             ny_encrypt_p(x, pk(x.1), x.2)>,
                                            x.3, ~sk_voter)
                                      >
                       ) ▶₁ #vr.9 )
                  case SecureChannel_Receive_case_1
                  solve( BallotStyleCount( ~ec, %idx_bs_unused ) ▶₀ #vr.1 )
                    case BallotSubmission_Mock_BallotStyle
                    solve( VoterCount( ~ec, %idx_ev_unused ) ▶₀ #vr.2 )
                      case BallotSubmission_Mock_EC_And_Initial_Counters
                      solve( BallotStyleCount( ~ec, %unused ) ▶₀ #vr.5 )
                        case BallotSubmission_Mock_BallotStyle
                        solve( BallotStyleCount( ~ec, %unused ) ▶₀ #vr.6 )
                          case BallotSubmission_Mock_BallotStyle
                          solve( BallotStyleCount( ~ec, %idx_bs ) ▶₀ #vr.11 )
                            case BallotSubmission_Mock_BallotStyle
                            solve( VoterCount( ~ec, %idx_ev ) ▶₀ #vr.12 )
                              case BallotSubmission_Mock_EC_And_Initial_Counters
                              solve( AuthCount( ~ec, %idx ) ▶₀ #vr.10 )
                                case BallotSubmission_Mock_Finalize_Election_Setup
                                solve( VoterCount( ~ec, %i.3 ) ▶₀ #vr.4 )
                                  case BallotSubmission_Mock_EC_And_Initial_Counters
                                  solve( BallotStyleCount( ~ec, %i.3 ) ▶₀ #vr.15 )
                                    case BallotSubmission_Mock_BallotStyle
                                    solve( BallotStyleCount( ~ec, %i.2 ) ▶₀ #vr.3 )
                                      case BallotSubmission_Mock_BallotStyle
                                      solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.13 )
                                        case BallotSubmission_Mock_BallotStyle
                                        by sorry
                                      next
                                        case BallotSubmission_Mock_EC_And_Initial_Counters
                                        solve( BallotStyleCount( ~ec, %i.2 ) ▶₀ #vr.16 )
                                          case BallotSubmission_Mock_BallotStyle
                                          by sorry
                                        next
                                          case BallotSubmission_Mock_EC_And_Initial_Counters
                                          solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.15 )
                                            case BallotSubmission_Mock_BallotStyle
                                            solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.16 )
                                              case BallotSubmission_Mock_BallotStyle
                                              by sorry
                                            next
                                              case BallotSubmission_Mock_EC_And_Initial_Counters
                                              SOLVED // trace found
                                            qed
                                          qed
                                        qed
                                      qed
                                    next
                                      case BallotSubmission_Mock_EC_And_Initial_Counters
                                      simplify
                                      by contradiction /* cyclic */
                                    qed
                                  next
                                    case BallotSubmission_Mock_EC_And_Initial_Counters
                                    by sorry
                                  qed
                                next
                                  case BallotSubmission_Mock_VoterRegistration_Eligible
                                  by sorry
                                qed
                              next
                                case BallotSubmission_Mock_Voter_Authentication
                                by sorry
                              qed
                            next
                              case BallotSubmission_Mock_VoterRegistration_Eligible
                              by sorry
                            qed
                          next
                            case BallotSubmission_Mock_EC_And_Initial_Counters
                            by sorry
                          qed
                        next
                          case BallotSubmission_Mock_EC_And_Initial_Counters
                          simplify
                          by sorry
                        qed
                      next
                        case BallotSubmission_Mock_EC_And_Initial_Counters
                        by sorry
                      qed
                    next
                      case BallotSubmission_Mock_VoterRegistration_Eligible
                      by sorry
                    qed
                  next
                    case BallotSubmission_Mock_EC_And_Initial_Counters
                    by sorry
                  qed
                next
                  case SecureChannel_Receive_case_2
                  by sorry
                qed
              qed
            qed
          qed
        qed
      qed
    next
      case case_2
      by sorry
    qed
  next
    case BulletinBoard_Create
    by sorry
  qed
qed
