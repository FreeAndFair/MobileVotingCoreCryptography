simplify
solve( VA_State_CheckOrCast( ~ec, ~va_id, $V, ~ballot, c, ~r, t
       ) ▶₀ #i )
  case Mock_ConfirmBallotPosting_case_1
  solve( !VA_Eligible_Voter( ~ec, ~va_id, p, ~sk_voter.2, ~bs_unused
         ) ▶₁ #i )
    case Mock_Voter_Authentication
    solve( BB_Trace_Entry( ~bbid, ~ec, h(<~ec, ~bbid>), %1 ) @ #vr.4 )
      case BulletinBoard_Create
      solve( BB_Current( ~bbid, c, h(<~ec, ~bbid>), %1 )[+] ▶₁ #vr.5 )
        case BulletinBoard_Create
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
                                        '1', ~sk_voter.1)
                                  >,
                                  %1
               )[+] ▶₂ #vr.5 )
          case Mock_AppendSubmittedBallot
          solve( DBB_Clock( %ts ) ▶₂ #vr.1 )
            case Mock_DBBTimestamp
            solve( DBB_State_ReceiveAuthorizeVoter( ~ec, %i.2 ) ▶₀ #vr.3 )
              case Mock_Finalize_Election_Setup
              solve( DBB_State_ReceiveAuthorizeVoter( ~ec, %i.1 ) ▶₀ #vr.7 )
                case Mock_Finalize_Election_Setup
                solve( BallotStyleCount( ~ec, %idx_bs ) ▶₀ #vr.7 )
                  case Mock_EC_And_Initial_Counters
                  solve( VoterCount( ~ec, %idx_ev ) ▶₀ #vr.8 )
                    case Mock_EC_And_Initial_Counters
                    solve( BallotStyleCount( ~ec, %idx_bs_unused ) ▶₀ #vr.9 )
                      case Mock_EC_And_Initial_Counters
                      solve( VoterCount( ~ec, %idx_ev_unused ) ▶₀ #vr.9 )
                        case Mock_EC_And_Initial_Counters
                        solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.9 )
                          case Mock_EC_And_Initial_Counters
                          solve( VoterCount( ~ec, %i.1 ) ▶₀ #vr.9 )
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
