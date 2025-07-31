simplify
solve( VA_State_PresentBallot( ~ec, ~va_id, $V, ~sk_voter ) ▶₀ #i )
  case Mock_Voter_Authentication
  solve( !ElectionPublicKey( ~ec, pk_election ) ▶₁ #i )
    case Mock_Finalize_Election_Setup
    solve( !DBB_Voter_Authorized( ~ec, auth_msg_unused, pseudonym($V.1),
                                  pk(~sk_voter.1), ~bs, %i.1
           ) ▶₂ #i )
      case Mock_Voter_Authentication
      solve( !VA_Eligible_Voter( ~ec, ~va_id, pseudonym($V.1), ~sk_voter, ~bs
             ) ▶₃ #i )
        case Mock_Voter_Authentication
        solve( DBB_State_ReceiveAuthorizeVoter( ~ec, %i.1 ) ▶₀ #j )
          case Mock_Finalize_Election_Setup
          solve( BallotStyleCount( ~ec, %idx_bs ) ▶₀ #vr )
            case Mock_BallotStyle
            solve( VoterCount( ~ec, %idx_ev ) ▶₀ #vr.1 )
              case Mock_EC_And_Initial_Counters
              solve( BallotStyleCount( ~ec, %idx_bs_unused ) ▶₀ #vr.3 )
                case Mock_BallotStyle
                solve( VoterCount( ~ec, %idx_ev_unused ) ▶₀ #vr.4 )
                  case Mock_EC_And_Initial_Counters
                  solve( BallotStyleCount( ~ec, %i.3 ) ▶₀ #vr.4 )
                    case Mock_BallotStyle
                    solve( VoterCount( ~ec, %i.4 ) ▶₀ #vr.5 )
                      case Mock_EC_And_Initial_Counters
                      solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.5 )
                        case Mock_EC_And_Initial_Counters
                        solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.7 )
                          case Mock_EC_And_Initial_Counters
                          solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.6 )
                            case Mock_EC_And_Initial_Counters
                            SOLVED // trace found
                          qed
                        qed
                      qed
                    qed
                  qed
                qed
              qed
            qed
          qed
        qed
      qed
    qed
  qed
qed
