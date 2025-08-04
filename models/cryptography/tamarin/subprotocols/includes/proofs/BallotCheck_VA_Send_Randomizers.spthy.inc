simplify
solve( SecureReceive( ~cid, <~ec, 'DBB'>, ~va_id,
                      <'DBB_Check_Request',
                       <'BCA_Check_Request', ~ec, t, pk, pk_bca_sign>, sig_bca_req>
       ) ▶₃ #i )
  case SecureChannel_Receive_case_1
  solve( VA_State_RequestRandomizers( ~ec, ~va_id, $V, p, ~ballot, c,
                                      ~r,
                                      h(<
                                         <'BBEntry_Ballot_Submission', ~ec, %ts,
                                          <'VA_Submit_Ballot', ~ec, pseudonym($V.1), pk(~sk_voter),
                                           ~ballot_style,
                                           ny_encrypt_c1(~ballot.1, pk(~sk_election), ~r.1),
                                           ny_encrypt_c2(~ballot.1, pk(~sk_election), ~r.1),
                                           ny_encrypt_p(~ballot.1, pk(~sk_election), ~r.1)>,
                                          sign(<'VA_Submit_Ballot', ~ec, pseudonym($V.1),
                                                pk(~sk_voter), ~ballot_style,
                                                ny_encrypt_c1(~ballot.1, pk(~sk_election), ~r.1),
                                                ny_encrypt_c2(~ballot.1, pk(~sk_election), ~r.1),
                                                ny_encrypt_p(~ballot.1, pk(~sk_election), ~r.1)>,
                                               '1', ~sk_voter.1)
                                         >,
                                         h(<~ec, ~bbid>)>)
         ) ▶₀ #i )
    case BallotCheck_VA_Check_case_1
    solve( !VA_Eligible_Voter( ~ec, ~va_id, pseudonym($V), ~sk_voter.2,
                               ~ballot_style.1
           ) ▶₁ #i )
      case Mock_Voter_Authentication
      solve( BB_Trace_Entry( ~bbid, ~ec, h(<~ec, ~bbid>), %1 ) @ #vr.3 )
        case BulletinBoard_Create
        solve( BB_Current( ~bbid, c, h(<~ec, ~bbid>), %1 )[+] ▶₁ #vr.4 )
          case BulletinBoard_Create
          solve( BB_Append_Request( ~bbid,
                                    <'BBEntry_Ballot_Submission', ~ec, %ts,
                                     <'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter),
                                      ~ballot_style, ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                      ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                      ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                     sign(<'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter),
                                           ~ballot_style,
                                           ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                           ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                           ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                          '1', ~sk_voter.1)
                                    >,
                                    %1
                 )[+] ▶₂ #vr.4 )
            case Mock_AppendSubmittedBallot
            solve( SecureReceive( ~cid_bca, ~bca_id, <~ec, 'DBB'>,
                                  <
                                   <'BCA_Check_Request', ~ec,
                                    h(<
                                       <'BBEntry_Ballot_Submission', ~ec, %ts,
                                        <'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter),
                                         ~ballot_style,
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
                                       h(<~ec, ~bbid>)>),
                                    pk(~sk_bca_encrypt), pk(~z)>,
                                   sign(<'BCA_Check_Request', ~ec,
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
                                            h(<~ec, ~bbid>)>),
                                         pk(~sk_bca_encrypt), pk(~z)>,
                                        '1', ~z)
                                  >
                   ) ▶₃ #vr.2 )
              case SecureChannel_Receive_case_1
              solve( DBB_State_ReceiveAuthorizeVoter( ~ec, %i.4 ) ▶₀ #vr.7 )
                case Mock_Finalize_Election_Setup
                solve( DBB_State_ReceiveAuthorizeVoter( ~ec, %i.1 ) ▶₀ #vr.8 )
                  case Mock_Finalize_Election_Setup
                  solve( BallotStyleCount( ~ec, %idx_bs_unused ) ▶₀ #vr.8 )
                    case Mock_BallotStyle
                    solve( VoterCount( ~ec, %idx_ev_unused ) ▶₀ #vr.9 )
                      case Mock_EC_And_Initial_Counters
                      solve( BallotStyleCount( ~ec, %idx_bs ) ▶₀ #vr.12 )
                        case Mock_BallotStyle
                        solve( VoterCount( ~ec, %i.3 ) ▶₀ #vr.11 )
                          case Mock_EC_And_Initial_Counters
                          solve( VoterCount( ~ec, %idx_ev ) ▶₀ #vr.12 )
                            case Mock_EC_And_Initial_Counters
                            solve( DBB_Clock( %ts ) ▶₂ #vr.16 )
                              case Mock_AppendSubmittedBallot_case_1
                              by sorry
                            next
                              case Mock_AppendSubmittedBallot_case_2
                              by sorry
                            next
                              case Mock_DBBTimestamp
                              solve( BallotStyleCount( ~ec, %i.3 ) ▶₀ #vr.19 )
                                case Mock_BallotStyle
                                by sorry
                              next
                                case Mock_EC_And_Initial_Counters
                                solve( BallotStyleCount( ~ec, %i.2 ) ▶₀ #vr.10 )
                                  case Mock_BallotStyle
                                  solve( BallotStyleCount( ~ec, %i.2 ) ▶₀ #vr.21 )
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
                                qed
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
              next
                case Mock_Voter_Authentication
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
  next
    case BallotCheck_VA_Check_case_2
    by sorry
  qed
next
  case SecureChannel_Receive_case_2
  by sorry
next
  case SecureChannel_Receive_case_3
  by sorry
next
  case SecureChannel_Receive_case_4
  by sorry
next
  case SecureChannel_Receive_case_5
  by sorry
qed
