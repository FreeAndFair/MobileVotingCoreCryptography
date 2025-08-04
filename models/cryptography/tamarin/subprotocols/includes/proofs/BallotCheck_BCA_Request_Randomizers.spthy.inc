simplify
solve( !BB_Entry( ~bbid,
                  <'BBEntry_Ballot_Submission', ~ec, timestamp,
                   <'VA_Submit_Ballot', ~ec, pseudo, pk_voter, ~ballot_style,
                    cryptograms>,
                   sig_msg_submit_ballot>,
                  t, %ballot_idx
       ) ▶₂ #i )
  case BulletinBoard_Append
  solve( BB_Append_Request( ~bbid,
                            <'BBEntry_Ballot_Submission', ~ec, timestamp,
                             <'VA_Submit_Ballot', ~ec, pseudo, pk_voter, ~ballot_style,
                              cryptograms>,
                             sig_msg_submit_ballot>,
                            %idx
         )[+] ▶₂ #vr )
    case Mock_AppendSubmittedBallot_case_1
    solve( BCA_State_InitiateBallotCheck( ~ec,
                                          h(<
                                             <'BBEntry_Ballot_Submission', ~ec, %ts,
                                              <'VA_Submit_Ballot', ~ec, pseudonym($V),
                                               pk(~sk_voter), ~ballot_style,
                                               ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                               ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                               ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                              sign(<'VA_Submit_Ballot', ~ec, pseudonym($V),
                                                    pk(~sk_voter), ~ballot_style,
                                                    ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                                    ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                                    ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                                   '1', ~sk_voter.1)
                                             >,
                                             h(<~ec, ~bbid>)>)
           ) ▶₀ #i )
      case BallotCheck_VA_Check_case_1
      solve( !BB_Root( ~ec, ~bbid, r_unused, rh_unused ) ▶₁ #i )
        case BulletinBoard_Create
        solve( BB_Trace_Entry( ~bbid, ~ec, h(<~ec, ~bbid>), %1 ) @ #j )
          case BulletinBoard_Create
          solve( BB_Current( ~bbid, c, h(<~ec, ~bbid>), %1 )[+] ▶₁ #vr )
            case BulletinBoard_Create
            solve( BallotStyleCount( ~ec, %idx_bs_unused ) ▶₀ #vr.2 )
              case Mock_BallotStyle
              solve( VoterCount( ~ec, %idx_ev_unused ) ▶₀ #vr.3 )
                case Mock_EC_And_Initial_Counters
                solve( BallotStyleCount( ~ec, %unused ) ▶₀ #vr.6 )
                  case Mock_BallotStyle
                  solve( BallotStyleCount( ~ec, %unused ) ▶₀ #vr.7 )
                    case Mock_BallotStyle
                    solve( VoterCount( ~ec, %i.3 ) ▶₀ #vr.5 )
                      case Mock_EC_And_Initial_Counters
                      solve( DBB_Clock( %ts ) ▶₂ #vr.6 )
                        case Mock_AppendSubmittedBallot_case_1
                        by sorry
                      next
                        case Mock_AppendSubmittedBallot_case_2
                        by sorry
                      next
                        case Mock_DBBTimestamp
                        solve( VoterCount( ~ec, %idx_ev ) ▶₀ #vr.11 )
                          case Mock_EC_And_Initial_Counters
                          solve( DBB_State_ReceiveAuthorizeVoter( ~ec, %i.5 ) ▶₀ #vr.8 )
                            case Mock_Finalize_Election_Setup
                            solve( DBB_State_ReceiveAuthorizeVoter( ~ec, %i.4 ) ▶₀ #vr.9 )
                              case Mock_Finalize_Election_Setup
                              solve( BallotStyleCount( ~ec, %i.3 ) ▶₀ #vr.13 )
                                case Mock_BallotStyle
                                by sorry
                              next
                                case Mock_EC_And_Initial_Counters
                                solve( BallotStyleCount( ~ec, %i.2 ) ▶₀ #vr.4 )
                                  case Mock_BallotStyle
                                  solve( BallotStyleCount( ~ec, %i.2 ) ▶₀ #vr.15 )
                                    case Mock_BallotStyle
                                    by sorry
                                  next
                                    case Mock_EC_And_Initial_Counters
                                    solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.10 )
                                      case Mock_BallotStyle
                                      simplify
                                      by contradiction /* cyclic */
                                    next
                                      case Mock_EC_And_Initial_Counters
                                      SOLVED // trace found
                                    qed
                                  qed
                                qed
                              qed
                            next
                              case Mock_Voter_Authentication
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
                      qed
                    next
                      case Mock_VoterRegistration_Eligible
                      by sorry
                    qed
                  next
                    case Mock_EC_And_Initial_Counters
                    simplify
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
          qed
        qed
      qed
    next
      case BallotCheck_VA_Check_case_2
      by sorry
    qed
  next
    case Mock_AppendSubmittedBallot_case_2
    by sorry
  qed
qed
