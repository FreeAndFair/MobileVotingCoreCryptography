simplify
solve( !DBB_Voter_Authorized( ~ec, signed_msg_auth, pseudonym($V),
                              pk(~sk_voter), ballot_style, %auth_idx
       ) ▶₀ #i )
  case Mock_Voter_Authentication
  solve( !BB_Root( ~ec, ~bbid, r_unused, rh_unused ) ▶₁ #i )
    case BulletinBoard_Create
    solve( (¬(%1 ⊏ %ballot_idx))  ∥ (#vr.9 < #j.1) )
      case case_2
      solve( !BB_Entry( ~bbid,
                        <'BBEntry_Ballot_Submission', ~ec, %ts_sub,
                         <'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter), ~bs, cryptograms
                         >,
                         sig_submit>,
                        tracker, %ballot_idx
             ) ▶₂ #i )
        case BulletinBoard_Append
        solve( (¬(%1 ⊏ %idx))  ∥ (#vr.9 < #j.2) )
          case case_1
          solve( BB_Trace_Entry( ~bbid,
                                 <'BBEntry_Ballot_Submission', ~ec, %ts,
                                  <'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter), ~bs, c>, sig>,
                                 h(<
                                    <'BBEntry_Ballot_Submission', ~ec, %ts,
                                     <'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter), ~bs, c>, sig>,
                                    h(<~ec, ~bbid>)>),
                                 (%1%+%1)
                 ) @ #j.1 )
            case BulletinBoard_Append
            solve( BB_Trace_Entry( ~bbid, ~ec, h(<~ec, ~bbid>), %1 ) @ #j.2 )
              case BulletinBoard_Create
              solve( BB_Current( ~bbid, c.1, h(<~ec, ~bbid>), %1 )[+] ▶₁ #j.1 )
                case BulletinBoard_Create
                solve( BB_Append_Request( ~bbid,
                                          <'BBEntry_Ballot_Submission', ~ec, %ts,
                                           <'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter), ~bs, c>,
                                           sig>,
                                          %1
                       )[+] ▶₂ #j.1 )
                  case Mock_AppendSubmittedBallot
                  simplify
                  solve( SecureReceive( ~cid, ~va_id, <~ec, 'DBB'>,
                                        <
                                         <'VA_Cast_Ballot', ~ec, pseudonym($V), pk(~sk_voter),
                                          h(<
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
                                             h(<~ec, ~bbid>)>)
                                         >,
                                         sign(<'VA_Cast_Ballot', ~ec, pseudonym($V), pk(~sk_voter),
                                               h(<
                                                  <'BBEntry_Ballot_Submission', ~ec, %ts,
                                                   <'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter),
                                                    ~bs, ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                                    ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                                    ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                                   sign(<'VA_Submit_Ballot', ~ec, pseudonym($V),
                                                         pk(~sk_voter), ~bs,
                                                         ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                                         ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                                         ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                                        '1', ~sk_voter.1)
                                                  >,
                                                  h(<~ec, ~bbid>)>)
                                              >,
                                              x, ~sk_voter)
                                        >
                         ) ▶₃ #i )
                    case SecureChannel_Receive_case_1
                    solve( DBB_State_ReceiveAuthorizeVoter( ~ec, %auth_idx ) ▶₀ #j )
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
                                  solve( DBB_Clock( %ts ) ▶₂ #vr.5 )
                                    case Mock_DBBTimestamp
                                    solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.11 )
                                      case Mock_BallotStyle
                                      solve( BallotStyleCount( ~ec, %i.2 ) ▶₀ #vr.13 )
                                        case Mock_BallotStyle
                                        solve( BallotStyleCount( ~ec, %i.3 ) ▶₀ #vr.14 )
                                          case Mock_BallotStyle
                                          solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.16 )
                                            case Mock_BallotStyle
                                            solve( BallotStyleCount( ~ec, %i.2 ) ▶₀ #vr.17 )
                                              case Mock_BallotStyle
                                              solve( BallotStyleCount( ~ec, %i.3 ) ▶₀ #vr.18 )
                                                case Mock_BallotStyle
                                                solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.19 )
                                                  case Mock_BallotStyle
                                                  solve( BallotStyleCount( ~ec, %i.2 ) ▶₀ #vr.20 )
                                                    case Mock_EC_And_Initial_Counters
                                                    solve( BallotStyleCount( ~ec, %i.2 ) ▶₀ #vr.21 )
                                                      case Mock_BallotStyle
                                                      solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.22 )
                                                        case Mock_EC_And_Initial_Counters
                                                        solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.19 )
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
qed
