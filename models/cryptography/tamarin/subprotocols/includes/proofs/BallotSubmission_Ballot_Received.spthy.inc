simplify
solve( SecureReceive( ~cid, ~va_id, <~ec, 'DBB'>,
                      <
                       <'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter),
                        ballot_style, ny_encrypt_c1(x, x.1, x.2),
                        ny_encrypt_c2(x, x.1, x.2), ny_encrypt_p(x, x.1, x.2)>,
                       sign(<'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter),
                             ballot_style, ny_encrypt_c1(x, x.1, x.2),
                             ny_encrypt_c2(x, x.1, x.2), ny_encrypt_p(x, x.1, x.2)>,
                            x.3, ~sk_voter)
                      >
       ) ▶₁ #i )
  case SecureChannel_Receive_case_1
  solve( !DBB_Voter_Authorized( ~ec, signed_msg_auth, pseudonym($V),
                                pk(~sk_voter), ~bs, %idx
         ) ▶₀ #i )
    case Mock_Voter_Authentication
    solve( DBB_State_ReceiveAuthorizeVoter( ~ec, %idx ) ▶₀ #j )
      case Mock_Finalize_Election_Setup
      solve( BallotStyleCount( ~ec, %idx_bs ) ▶₀ #vr.4 )
        case Mock_BallotStyle
        solve( VoterCount( ~ec, %idx_ev ) ▶₀ #vr.5 )
          case Mock_EC_And_Initial_Counters
          solve( BallotStyleCount( ~ec, %idx_bs_unused ) ▶₀ #vr.6 )
            case Mock_BallotStyle
            solve( VoterCount( ~ec, %idx_ev_unused ) ▶₀ #vr.7 )
              case Mock_EC_And_Initial_Counters
              solve( BallotStyleCount( ~ec, %unused ) ▶₀ #vr.9 )
                case Mock_BallotStyle
                solve( VoterCount( ~ec, %i.4 ) ▶₀ #vr.8 )
                  case Mock_EC_And_Initial_Counters
                  solve( BallotStyleCount( ~ec, %i.3 ) ▶₀ #vr.7 )
                    case Mock_BallotStyle
                    solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.8 )
                      case Mock_BallotStyle
                      by sorry
                    next
                      case Mock_EC_And_Initial_Counters
                      solve( BallotStyleCount( ~ec, %i.2 ) ▶₀ #vr.11 )
                        case Mock_BallotStyle
                        by sorry
                      next
                        case Mock_EC_And_Initial_Counters
                        solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.9 )
                          case Mock_BallotStyle
                          simplify
                          by contradiction /* cyclic */
                        next
                          case Mock_EC_And_Initial_Counters
                          SOLVED // trace found
                        qed
                      qed
                    qed
                  next
                    case Mock_EC_And_Initial_Counters
                    simplify
                    by contradiction /* cyclic */
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
next
  case SecureChannel_Receive_case_2
  by sorry
qed
