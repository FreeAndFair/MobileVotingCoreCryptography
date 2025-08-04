simplify
solve( !DBB_Submitted_Ballot( ~ec, ~va_id, ~cid, pseudo, msg
       ) ▶₀ #i )
  case Mock_Ballot_Submission
  solve( !Mock_Submitted_Ballot( ~ec, ~va_id, $V.1, ~ballot.1,
                                 cryptograms, ~r.1,
                                 <
                                  <'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter), ~bs,
                                   ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                   ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                   ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                  sign(<'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter), ~bs,
                                        ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                        ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                        ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                       '1', ~sk_voter.1)
                                 >
         ) ▶₁ #i )
    case Mock_Ballot_Submission
    solve( !BB_Root( ~ec, bbid, r_unused, rh_unused ) ▶₃ #i )
      case BulletinBoard_Create
      solve( !BB_Entry( ~bbid, e_unused, eh_unused, %idx ) ▶₄ #i )
        case BulletinBoard_Append
        by sorry
      next
        case BulletinBoard_Create
        solve( DBB_Clock( %ts ) ▶₂ #i )
          case Mock_AppendSubmittedBallot_case_1
          by sorry
        next
          case Mock_AppendSubmittedBallot_case_2
          by sorry
        next
          case Mock_DBBTimestamp
          solve( DBB_State_ReceiveAuthorizeVoter( ~ec, %i.2 ) ▶₀ #vr.1 )
            case Mock_Finalize_Election_Setup
            solve( DBB_State_ReceiveAuthorizeVoter( ~ec, %i.1 ) ▶₀ #vr.3 )
              case Mock_Finalize_Election_Setup
              solve( BallotStyleCount( ~ec, %idx_bs ) ▶₀ #vr.3 )
                case Mock_BallotStyle
                by sorry
              next
                case Mock_EC_And_Initial_Counters
                solve( VoterCount( ~ec, %idx_ev ) ▶₀ #vr.4 )
                  case Mock_EC_And_Initial_Counters
                  solve( BallotStyleCount( ~ec, %idx_bs_unused ) ▶₀ #vr.5 )
                    case Mock_BallotStyle
                    by sorry
                  next
                    case Mock_EC_And_Initial_Counters
                    solve( VoterCount( ~ec, %idx_ev_unused ) ▶₀ #vr.5 )
                      case Mock_EC_And_Initial_Counters
                      solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.5 )
                        case Mock_BallotStyle
                        solve( VoterCount( ~ec, %i.2 ) ▶₀ #vr.6 )
                          case Mock_EC_And_Initial_Counters
                          solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.9 )
                            case Mock_BallotStyle
                            by sorry
                          next
                            case Mock_EC_And_Initial_Counters
                            SOLVED // trace found
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
                  qed
                next
                  case Mock_VoterRegistration_Eligible
                  by sorry
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
        qed
      qed
    qed
  qed
qed
