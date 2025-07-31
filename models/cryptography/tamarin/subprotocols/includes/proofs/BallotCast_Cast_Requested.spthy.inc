simplify
solve( DBB_State_ConfirmBallotPosting( ~ec, ~va_id, ~cid, pseudo,
                                       <'BBEntry_Ballot_Submission', ~ec, %ts, signed_msg_submit_ballot>, %idx
       ) ▶₀ #i )
  case Mock_AppendSubmittedBallot_case_1
  simplify
  solve( !Mock_Submitted_Ballot( ~ec, ~va_id, $V.1, ~ballot.1, cryptograms,
                                 ~r.1,
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
    solve( !VA_Eligible_Voter( ~ec, ~va_id, pseudonym($V), ~sk_voter.2, ~bs.1
           ) ▶₂ #i )
      case Mock_Voter_Authentication
      solve( !BB_Root( ~ec, bbid, r_unused, rh_unused ) ▶₃ #i )
        case BulletinBoard_Create
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
                                '1', ~sk_voter.1)
                          >,
                          tracker, (%1%+%1)
               ) ▶₄ #i )
          case BulletinBoard_Append
          solve( VA_State_CheckOrCast( ~ec, ~va_id, $V.1, ~ballot,
                                       <ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                        ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                        ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                       ~r,
                                       h(<
                                          <'BBEntry_Ballot_Submission', ~ec, %ts,
                                           <'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter), ~bs,
                                            ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                            ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                            ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                           sign(<'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter), ~bs,
                                                 ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                                 ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                                 ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                                '1', ~sk_voter.1)
                                          >,
                                          h(<~ec, ~bbid>)>)
                 ) ▶₀ #j )
            case Mock_ConfirmBallotPosting
            solve( !VA_Eligible_Voter( ~ec, ~va_id, pseudonym($V), ~sk_voter.2,
                                       ~bs_unused
                   ) ▶₁ #j )
              case Mock_Voter_Authentication
              solve( BB_Trace_Entry( ~bbid, ~ec, h(<~ec, ~bbid>), %1 ) @ #vr.2 )
                case BulletinBoard_Create
                solve( BB_Current( ~bbid, c, h(<~ec, ~bbid>), %1 )[+] ▶₁ #vr.14 )
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
                         )[+] ▶₂ #vr.14 )
                    case Mock_AppendSubmittedBallot
                    solve( DBB_Clock( %ts ) ▶₂ #vr )
                      case Mock_DBBTimestamp
                      solve( DBB_State_ReceiveAuthorizeVoter( ~ec, %i.2 ) ▶₀ #vr.3 )
                        case Mock_Finalize_Election_Setup
                        solve( DBB_State_ReceiveAuthorizeVoter( ~ec, %i.1 ) ▶₀ #vr.5 )
                          case Mock_Finalize_Election_Setup
                          solve( BallotStyleCount( ~ec, %idx_bs ) ▶₀ #vr.5 )
                            case Mock_BallotStyle
                            solve( VoterCount( ~ec, %idx_ev ) ▶₀ #vr.6 )
                              case Mock_EC_And_Initial_Counters
                              solve( BallotStyleCount( ~ec, %idx_bs_unused ) ▶₀ #vr.7 )
                                case Mock_BallotStyle
                                solve( VoterCount( ~ec, %idx_ev_unused ) ▶₀ #vr.8 )
                                  case Mock_EC_And_Initial_Counters
                                  solve( BallotStyleCount( ~ec, %i.3 ) ▶₀ #vr.8 )
                                    case Mock_BallotStyle
                                    solve( VoterCount( ~ec, %i.4 ) ▶₀ #vr.9 )
                                      case Mock_EC_And_Initial_Counters
                                      solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.11 )
                                        case Mock_BallotStyle
                                        solve( BallotStyleCount( ~ec, %i.2 ) ▶₀ #vr.13 )
                                          case Mock_BallotStyle
                                          solve( BallotStyleCount( ~ec, %i.3 ) ▶₀ #vr.14 )
                                            case Mock_BallotStyle
                                            solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.15 )
                                              case Mock_BallotStyle
                                              solve( BallotStyleCount( ~ec, %i.2 ) ▶₀ #vr.16 )
                                                case Mock_BallotStyle
                                                solve( BallotStyleCount( ~ec, %i.3 ) ▶₀ #vr.17 )
                                                  case Mock_BallotStyle
                                                  solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.18 )
                                                    case Mock_EC_And_Initial_Counters
                                                    solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.19 )
                                                      case Mock_EC_And_Initial_Counters
                                                      solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.16 )
                                                        case Mock_BallotStyle
                                                        solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.17 )
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
