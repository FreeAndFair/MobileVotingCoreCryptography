simplify
solve( !BB_Root( ~ec, bbid, r_unused, rh_unused ) ▶₁ #i )
  case BulletinBoard_Create
  solve( BallotStyleCount( ~ec, %idx_bs_unused ) ▶₀ #vr.2 )
    case Mock_BallotStyle
    solve( VoterCount( ~ec, %idx_ev_unused ) ▶₀ #vr.3 )
      case Mock_EC_And_Initial_Counters
      solve( DBB_State_ConfirmBallotPosting( ~ec, ~va_id, ~cid, pseudo,
                                             msg, %idx
             ) ▶₀ #i )
        case BallotSubmission_DBB_AppendSubmittedBallot_case_1
        solve( SecureReceive( ~cid, ~va_id, <~ec, 'DBB'>,
                              <
                               <'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter), ~bs,
                                ny_encrypt_c1(x, x.1, x.2), ny_encrypt_c2(x, x.1, x.2),
                                ny_encrypt_p(x, x.1, x.2)>,
                               sign(<'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter), ~bs,
                                     ny_encrypt_c1(x, x.1, x.2), ny_encrypt_c2(x, x.1, x.2),
                                     ny_encrypt_p(x, x.1, x.2)>,
                                    x.3, ~sk_voter)
                              >
               ) ▶₁ #vr.11 )
          case SecureChannel_Receive_case_1
          solve( !BB_Entry( ~bbid,
                            <'BBEntry_Ballot_Submission', ~ec, %ts,
                             <'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter), ~bs,
                              ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                              ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                              ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                             sign(<'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter), ~bs,
                                   ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                   ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                   ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                  '1', ~sk_voter)
                            >,
                            tracker, (%1%+%1)
                 ) ▶₂ #i )
            case BulletinBoard_Append
            solve( BB_Append_Request( ~bbid,
                                      <'BBEntry_Ballot_Submission', ~ec, %ts,
                                       <'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter), ~bs,
                                        ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                        ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                        ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                       sign(<'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter),
                                             ~bs, ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                             ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                             ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                            '1', ~sk_voter)
                                      >,
                                      %1
                   )[+] ▶₂ #vr.18 )
              case BallotSubmission_DBB_AppendSubmittedBallot
              solve( BB_Trace_Entry( ~bbid, ~ec, h(<~ec, ~bbid>), %1 ) @ #vr )
                case BulletinBoard_Create
                solve( BB_Current( ~bbid, c, h(<~ec, ~bbid>), %1 )[+] ▶₁ #vr.18 )
                  case BulletinBoard_Create
                  solve( DBB_State_ReceiveAuthorizeVoter( ~ec, %idx ) ▶₀ #vr.12 )
                    case Mock_Finalize_Election_Setup
                    solve( BallotStyleCount( ~ec, %idx_bs ) ▶₀ #vr.13 )
                      case Mock_BallotStyle
                      solve( VoterCount( ~ec, %idx_ev ) ▶₀ #vr.14 )
                        case Mock_EC_And_Initial_Counters
                        solve( BallotStyleCount( ~ec, %unused ) ▶₀ #vr.7 )
                          case Mock_BallotStyle
                          solve( VoterCount( ~ec, %i.3 ) ▶₀ #vr.5 )
                            case Mock_EC_And_Initial_Counters
                            solve( BallotStyleCount( ~ec, %i.3 ) ▶₀ #vr.15 )
                              case Mock_BallotStyle
                              by sorry
                            next
                              case Mock_EC_And_Initial_Counters
                              solve( BallotStyleCount( ~ec, %i.2 ) ▶₀ #vr.4 )
                                case Mock_BallotStyle
                                solve( BallotStyleCount( ~ec, %i.2 ) ▶₀ #vr.16 )
                                  case Mock_BallotStyle
                                  by sorry
                                next
                                  case Mock_EC_And_Initial_Counters
                                  solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.5 )
                                    case Mock_BallotStyle
                                    simplify
                                    by contradiction /* cyclic */
                                  next
                                    case Mock_EC_And_Initial_Counters
                                    solve( DBB_Clock( %ts ) ▶₁ #vr.6 )
                                      case BallotSubmission_DBB_AppendSubmittedBallot_case_1
                                      solve( DBB_Clock( %ts ) ▶₁ #vr.13 )
                                        case BallotSubmission_DBB_AppendSubmittedBallot_case_1
                                        by sorry
                                      next
                                        case BallotSubmission_DBB_AppendSubmittedBallot_case_2
                                        by sorry
                                      next
                                        case BallotSubmission_Initialize_DBBTimestamp
                                        solve( (#vr = #vr.15)  ∥
                                               ((¬(~ec = ~ec.1)) ∧ (¬(~bbid = ~bbid.1))) )
                                          case case_1
                                          solve( SecureReceive( ~cid.1, ~va_id.2, <~ec, 'DBB'>,
                                                                <
                                                                 <'VA_Submit_Ballot', ~ec,
                                                                  pseudonym($V), pk(~sk_voter.1),
                                                                  ~bs, ny_encrypt_c1(x, x.1, x.2),
                                                                  ny_encrypt_c2(x, x.1, x.2),
                                                                  ny_encrypt_p(x, x.1, x.2)>,
                                                                 sign(<'VA_Submit_Ballot', ~ec,
                                                                       pseudonym($V),
                                                                       pk(~sk_voter.1), ~bs,
                                                                       ny_encrypt_c1(x, x.1, x.2),
                                                                       ny_encrypt_c2(x, x.1, x.2),
                                                                       ny_encrypt_p(x, x.1, x.2)>,
                                                                      x.3, ~sk_voter.1)
                                                                >
                                                 ) ▶₁ #vr.14 )
                                            case SecureChannel_Receive_case_1
                                            solve( DBB_State_ReceiveAuthorizeVoter( ~ec, %idx
                                                   ) ▶₀ #vr.15 )
                                              case Mock_Voter_Authentication
                                              solve( BallotStyleCount( ~ec, %idx_bs ) ▶₀ #vr.16 )
                                                case Mock_BallotStyle
                                                solve( VoterCount( ~ec, %idx_ev ) ▶₀ #vr.17 )
                                                  case Mock_EC_And_Initial_Counters
                                                  solve( DBB_State_ReceiveAuthorizeVoter( ~ec, %i.1
                                                         ) ▶₀ #vr.20 )
                                                    case Mock_Finalize_Election_Setup
                                                    SOLVED // trace found
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
                                            qed
                                          next
                                            case SecureChannel_Receive_case_2
                                            by sorry
                                          qed
                                        next
                                          case case_2
                                          by sorry
                                        qed
                                      qed
                                    next
                                      case BallotSubmission_DBB_AppendSubmittedBallot_case_2
                                      by sorry
                                    next
                                      case BallotSubmission_Initialize_DBBTimestamp
                                      SOLVED // trace found
                                    qed
                                  qed
                                qed
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
        next
          case SecureChannel_Receive_case_2
          by sorry
        qed
      next
        case BallotSubmission_DBB_AppendSubmittedBallot_case_2
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
