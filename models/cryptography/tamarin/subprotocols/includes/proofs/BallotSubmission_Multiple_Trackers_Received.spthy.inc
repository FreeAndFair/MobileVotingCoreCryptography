simplify
solve( (#i1 < #i2)  ∥ (#i2 < #i1) )
  case case_1
  solve( !BB_Root( ~ec, ~bbid, ~ec, bb_root_hash ) ▶₂ #i1 )
    case BulletinBoard_Create
    solve( !BB_Entry( ~bbid,
                      <'BBEntry_Ballot_Submission', ~ec, timestamp,
                       <'VA_Submit_Ballot', ~ec, pseudo1, pk(~sk_voter), ballot_style1,
                        cryptograms1>,
                       sign(<'VA_Submit_Ballot', ~ec, pseudo1, pk(~sk_voter),
                             ballot_style1, cryptograms1>,
                            '1', ~sk_voter)
                      >,
                      tracker1, %idx
           ) ▶₃ #i1 )
      case BulletinBoard_Append
      solve( BB_Append_Request( ~bbid,
                                <'BBEntry_Ballot_Submission', ~ec, timestamp,
                                 <'VA_Submit_Ballot', ~ec, pseudo1, pk(~sk_voter), ballot_style1,
                                  cryptograms1>,
                                 sign(<'VA_Submit_Ballot', ~ec, pseudo1, pk(~sk_voter),
                                       ballot_style1, cryptograms1>,
                                      '1', ~sk_voter)
                                >,
                                %idx
             )[+] ▶₂ #vr.8 )
        case BallotSubmission_DBB_AppendSubmittedBallot_case_1
        solve( !BB_Entry( ~bbid.1,
                          <'BBEntry_Ballot_Submission', ~ec, timestamp,
                           <'VA_Submit_Ballot', ~ec, pseudo2, pk(~sk_voter.1), ballot_style2,
                            cryptograms2>,
                           sign(<'VA_Submit_Ballot', ~ec, pseudo2, pk(~sk_voter.1),
                                 ballot_style2, cryptograms2>,
                                '1', ~sk_voter.1)
                          >,
                          tracker2, %idx
               ) ▶₃ #i2 )
          case BulletinBoard_Append
          solve( BB_Append_Request( ~bbid.1,
                                    <'BBEntry_Ballot_Submission', ~ec, timestamp,
                                     <'VA_Submit_Ballot', ~ec, pseudo2, pk(~sk_voter.1),
                                      ballot_style2, cryptograms2>,
                                     sign(<'VA_Submit_Ballot', ~ec, pseudo2, pk(~sk_voter.1),
                                           ballot_style2, cryptograms2>,
                                          '1', ~sk_voter.1)
                                    >,
                                    %idx
                 )[+] ▶₂ #vr.13 )
            case BallotSubmission_DBB_AppendSubmittedBallot_case_1
            by contradiction /* from formulas */
          next
            case BallotSubmission_DBB_AppendSubmittedBallot_case_2
            solve( SecureReceive( ~cid, <~ec, 'DBB'>, ~va_id,
                                  <'DBB_Ballot_Tracker', ~ec,
                                   h(<
                                      <'BBEntry_Ballot_Submission', ~ec, %ts,
                                       <'VA_Submit_Ballot', ~ec, pseudonym($V.1), pk(~sk_voter),
                                        ~bs, ny_encrypt_c1(x, pk(x.1), x.2),
                                        ny_encrypt_c2(x, pk(x.1), x.2),
                                        ny_encrypt_p(x, pk(x.1), x.2)>,
                                       sign(<'VA_Submit_Ballot', ~ec, pseudonym($V.1),
                                             pk(~sk_voter), ~bs, ny_encrypt_c1(x, pk(x.1), x.2),
                                             ny_encrypt_c2(x, pk(x.1), x.2),
                                             ny_encrypt_p(x, pk(x.1), x.2)>,
                                            '1', ~sk_voter)
                                      >,
                                      h(<~ec, ~bbid>)>)
                                  >
                   ) ▶₄ #i1 )
              case SecureChannel_Receive_case_1
              solve( SecureReceive( ~cid.1, <~ec, 'DBB'>, ~va_id.1,
                                    <'DBB_Ballot_Tracker', ~ec,
                                     h(<
                                        <'BBEntry_Ballot_Submission', ~ec, %ts.1,
                                         <'VA_Submit_Ballot', ~ec, pseudonym($V.3),
                                          pk(~sk_voter.1), ~bs.1, ny_encrypt_c1(x.3, pk(x.4), x.5),
                                          ny_encrypt_c2(x.3, pk(x.4), x.5),
                                          ny_encrypt_p(x.3, pk(x.4), x.5)>,
                                         sign(<'VA_Submit_Ballot', ~ec, pseudonym($V.3),
                                               pk(~sk_voter.1), ~bs.1,
                                               ny_encrypt_c1(x.3, pk(x.4), x.5),
                                               ny_encrypt_c2(x.3, pk(x.4), x.5),
                                               ny_encrypt_p(x.3, pk(x.4), x.5)>,
                                              '1', ~sk_voter.1)
                                        >,
                                        h(<p, ch>)>)
                                    >
                     ) ▶₄ #i2 )
                case SecureChannel_Receive_case_1
                solve( SecureReceive( ~cid.1, ~va_id.1, <~ec, 'DBB'>,
                                      <
                                       <'VA_Submit_Ballot', ~ec, pseudonym($V.3), pk(~sk_voter.1),
                                        ~bs.1, ny_encrypt_c1(x.3, pk(x.4), x.5),
                                        ny_encrypt_c2(x.3, pk(x.4), x.5),
                                        ny_encrypt_p(x.3, pk(x.4), x.5)>,
                                       sign(<'VA_Submit_Ballot', ~ec, pseudonym($V.3),
                                             pk(~sk_voter.1), ~bs.1,
                                             ny_encrypt_c1(x.3, pk(x.4), x.5),
                                             ny_encrypt_c2(x.3, pk(x.4), x.5),
                                             ny_encrypt_p(x.3, pk(x.4), x.5)>,
                                            '1', ~sk_voter.1)
                                      >
                       ) ▶₁ #vr.15 )
                  case SecureChannel_Receive_case_1
                  solve( SecureReceive( ~cid, ~va_id, <~ec, 'DBB'>,
                                        <
                                         <'VA_Submit_Ballot', ~ec, pseudonym($V.1), pk(~sk_voter),
                                          ~bs, ny_encrypt_c1(x, pk(x.1), x.2),
                                          ny_encrypt_c2(x, pk(x.1), x.2),
                                          ny_encrypt_p(x, pk(x.1), x.2)>,
                                         sign(<'VA_Submit_Ballot', ~ec, pseudonym($V.1),
                                               pk(~sk_voter), ~bs, ny_encrypt_c1(x, pk(x.1), x.2),
                                               ny_encrypt_c2(x, pk(x.1), x.2),
                                               ny_encrypt_p(x, pk(x.1), x.2)>,
                                              '1', ~sk_voter)
                                        >
                         ) ▶₁ #vr.9 )
                    case SecureChannel_Receive_case_1
                    solve( VA_State_BallotSubmitResponse( ~ec, ~va_id, ~cid, $V,
                                                          ~ballot,
                                                          <
                                                           ny_encrypt_c1(~ballot.1,
                                                                         pk(~sk_election), ~r),
                                                           ny_encrypt_c2(~ballot.1,
                                                                         pk(~sk_election), ~r),
                                                           ny_encrypt_p(~ballot.1, pk(~sk_election),
                                                                        ~r)
                                                          >,
                                                          ~r.1
                           ) ▶₀ #i1 )
                      case BallotSubmission_VA_PresentBallot
                      solve( VA_State_BallotSubmitResponse( ~ec, ~va_id.1, ~cid.1, $V.1,
                                                            ~ballot.1,
                                                            <
                                                             ny_encrypt_c1(~ballot.2,
                                                                           pk(~sk_election), ~r.1),
                                                             ny_encrypt_c2(~ballot.2,
                                                                           pk(~sk_election), ~r.1),
                                                             ny_encrypt_p(~ballot.2,
                                                                          pk(~sk_election), ~r.1)
                                                            >,
                                                            ~r.2
                             ) ▶₀ #i2 )
                        case BallotSubmission_VA_PresentBallot
                        solve( (¬(%1 ⊏ %idx))  ∥ (#j < #j.2) )
                          case case_1
                          solve( !BB_Root( ~ec, ~bbid, ~ec, bb_root_hash ) ▶₂ #i2 )
                            case BulletinBoard_Create
                            solve( BB_Trace_Entry( ~bbid, ~ec, h(<~ec, ~bbid>), %1 ) @ #j )
                              case BulletinBoard_Create
                              solve( BB_Current( ~bbid, c.1,
                                                 h(<
                                                    <'BBEntry_Ballot_Submission', ~ec, %ts,
                                                     <'VA_Submit_Ballot', ~ec, pseudonym($V),
                                                      pk(~sk_voter), ~bs,
                                                      ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                                      ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                                      ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                                     sign(<'VA_Submit_Ballot', ~ec, pseudonym($V),
                                                           pk(~sk_voter), ~bs,
                                                           ny_encrypt_c1(~ballot, pk(~sk_election),
                                                                         ~r),
                                                           ny_encrypt_c2(~ballot, pk(~sk_election),
                                                                         ~r),
                                                           ny_encrypt_p(~ballot, pk(~sk_election),
                                                                        ~r)
                                                          >,
                                                          '1', ~sk_voter)
                                                    >,
                                                    h(<~ec, ~bbid>)>),
                                                 (%1%+%1)
                                     )[+] ▶₁ #vr.12 )
                                case BulletinBoard_Append
                                solve( BB_Current( ~bbid, c, h(<~ec, ~bbid>), %1 )[+] ▶₁ #j.1 )
                                  case BulletinBoard_Create
                                  solve( BB_Trace_Entry( ~bbid,
                                                         <'BBEntry_Ballot_Submission', ~ec, %ts,
                                                          <'VA_Submit_Ballot', ~ec, pseudonym($V),
                                                           pk(~sk_voter), ~bs,
                                                           ny_encrypt_c1(~ballot, pk(~sk_election),
                                                                         ~r),
                                                           ny_encrypt_c2(~ballot, pk(~sk_election),
                                                                         ~r),
                                                           ny_encrypt_p(~ballot, pk(~sk_election),
                                                                        ~r)
                                                          >,
                                                          sign(<'VA_Submit_Ballot', ~ec,
                                                                pseudonym($V), pk(~sk_voter), ~bs,
                                                                ny_encrypt_c1(~ballot,
                                                                              pk(~sk_election),
                                                                              ~r),
                                                                ny_encrypt_c2(~ballot,
                                                                              pk(~sk_election),
                                                                              ~r),
                                                                ny_encrypt_p(~ballot,
                                                                             pk(~sk_election), ~r)
                                                               >,
                                                               '1', ~sk_voter)
                                                         >,
                                                         h(<
                                                            <'BBEntry_Ballot_Submission', ~ec, %ts,
                                                             <'VA_Submit_Ballot', ~ec,
                                                              pseudonym($V), pk(~sk_voter), ~bs,
                                                              ny_encrypt_c1(~ballot,
                                                                            pk(~sk_election), ~r),
                                                              ny_encrypt_c2(~ballot,
                                                                            pk(~sk_election), ~r),
                                                              ny_encrypt_p(~ballot,
                                                                           pk(~sk_election), ~r)
                                                             >,
                                                             sign(<'VA_Submit_Ballot', ~ec,
                                                                   pseudonym($V), pk(~sk_voter),
                                                                   ~bs,
                                                                   ny_encrypt_c1(~ballot,
                                                                                 pk(~sk_election),
                                                                                 ~r),
                                                                   ny_encrypt_c2(~ballot,
                                                                                 pk(~sk_election),
                                                                                 ~r),
                                                                   ny_encrypt_p(~ballot,
                                                                                pk(~sk_election),
                                                                                ~r)
                                                                  >,
                                                                  '1', ~sk_voter)
                                                            >,
                                                            h(<~ec, ~bbid>)>),
                                                         (%1%+%1)
                                         ) @ #j.1 )
                                    case BulletinBoard_Append
                                    solve( DBB_State_ReceiveAuthorizeVoter( ~ec, %idx.1
                                           ) ▶₀ #vr.15 )
                                      case Mock_Finalize_Election_Setup
                                      solve( !VA_Eligible_Voter( ~ec, ~va_id, pseudonym($V),
                                                                 ~sk_voter, ~bs
                                             ) ▶₁ #i1 )
                                        case Mock_Voter_Authentication
                                        solve( !VA_Eligible_Voter( ~ec, ~va_id.1, pseudonym($V.1),
                                                                   ~sk_voter.1, ~bs.1
                                               ) ▶₁ #i2 )
                                          case Mock_Voter_Authentication
                                          solve( BallotStyleCount( ~ec, %idx_bs_unused ) ▶₀ #vr.1 )
                                            case Mock_BallotStyle
                                            solve( VoterCount( ~ec, %idx_ev_unused ) ▶₀ #vr.2 )
                                              case Mock_EC_And_Initial_Counters
                                              solve( BallotStyleCount( ~ec, %unused ) ▶₀ #vr.5 )
                                                case Mock_BallotStyle
                                                solve( BallotStyleCount( ~ec, %unused ) ▶₀ #vr.6 )
                                                  case Mock_BallotStyle
                                                  solve( DBB_State_ReceiveAuthorizeVoter( ~ec, %idx
                                                         ) ▶₀ #vr.9 )
                                                    case Mock_Voter_Authentication
                                                    solve( DBB_State_ReceiveAuthorizeVoter( ~ec,
                                                                                            %i.5
                                                           ) ▶₀ #vr.34 )
                                                      case Mock_Finalize_Election_Setup
                                                      solve( VoterCount( ~ec, %idx_ev.1
                                                             ) ▶₀ #vr.17 )
                                                        case Mock_EC_And_Initial_Counters
                                                        solve( VoterCount( ~ec, %idx_ev
                                                               ) ▶₀ #vr.11 )
                                                          case Mock_EC_And_Initial_Counters
                                                          by contradiction /* from formulas */
                                                        next
                                                          case Mock_VoterRegistration_Eligible
                                                          solve( BallotStyleCount( ~ec, %idx_bs
                                                                 ) ▶₀ #vr.10 )
                                                            case Mock_BallotStyle
                                                            solve( BallotStyleCount( ~ec, %unused
                                                                   ) ▶₀ #vr.33 )
                                                              case Mock_BallotStyle
                                                              solve( VoterCount( ~ec, %i.6
                                                                     ) ▶₀ #vr.32 )
                                                                case Mock_EC_And_Initial_Counters
                                                                solve( DBB_Clock( %ts.1
                                                                       ) ▶₁ #vr.13 )
                                                                  case BallotSubmission_DBB_AppendSubmittedBallot_case_1
                                                                  by sorry
                                                                next
                                                                  case BallotSubmission_DBB_AppendSubmittedBallot_case_2
                                                                  by sorry
                                                                next
                                                                  case BallotSubmission_Initialize_DBBTimestamp
                                                                  solve( DBB_Clock( %ts ) ▶₁ #vr.7 )
                                                                    case BallotSubmission_DBB_AppendSubmittedBallot_case_1
                                                                    by sorry
                                                                  next
                                                                    case BallotSubmission_DBB_AppendSubmittedBallot_case_2
                                                                    by sorry
                                                                  next
                                                                    case BallotSubmission_Initialize_DBBTimestamp
                                                                    solve( VoterCount( ~ec, %i.2
                                                                           ) ▶₀ #vr.4 )
                                                                      case Mock_VoterRegistration_Eligible
                                                                      solve( VoterCount( ~ec, %i.2
                                                                             ) ▶₀ #vr.35 )
                                                                        case Mock_EC_And_Initial_Counters
                                                                        solve( BallotStyleCount( ~ec,
                                                                                                 %i.3
                                                                               ) ▶₀ #vr.29 )
                                                                          case Mock_BallotStyle
                                                                          solve( BallotStyleCount( ~ec,
                                                                                                   %i.2
                                                                                 ) ▶₀ #vr.28 )
                                                                            case Mock_BallotStyle
                                                                            solve( BallotStyleCount( ~ec,
                                                                                                     %i.1
                                                                                   ) ▶₀ #vr.3 )
                                                                              case Mock_BallotStyle
                                                                              solve( BallotStyleCount( ~ec,
                                                                                                       %i
                                                                                     ) ▶₀ #vr.26 )
                                                                                case Mock_BallotStyle
                                                                                by sorry
                                                                              next
                                                                                case Mock_EC_And_Initial_Counters
                                                                                solve( BallotStyleCount( ~ec,
                                                                                                         %i.2
                                                                                       ) ▶₀ #vr.32 )
                                                                                  case Mock_BallotStyle
                                                                                  by sorry
                                                                                next
                                                                                  case Mock_EC_And_Initial_Counters
                                                                                  solve( BallotStyleCount( ~ec,
                                                                                                           %i.1
                                                                                         ) ▶₀ #vr.31 )
                                                                                    case Mock_BallotStyle
                                                                                    by sorry
                                                                                  next
                                                                                    case Mock_EC_And_Initial_Counters
                                                                                    solve( BallotStyleCount( ~ec,
                                                                                                             %i
                                                                                           ) ▶₀ #vr.29 )
                                                                                      case Mock_BallotStyle
                                                                                      solve( BallotStyleCount( ~ec,
                                                                                                               %i
                                                                                             ) ▶₀ #vr.30 )
                                                                                        case Mock_BallotStyle
                                                                                        by sorry
                                                                                      next
                                                                                        case Mock_EC_And_Initial_Counters
                                                                                        SOLVED // trace found
                                                                                      qed
                                                                                    qed
                                                                                  qed
                                                                                qed
                                                                              qed
                                                                            next
                                                                              case Mock_EC_And_Initial_Counters
                                                                              simplify
                                                                              by contradiction
                                                                                 /* cyclic */
                                                                            qed
                                                                          next
                                                                            case Mock_EC_And_Initial_Counters
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
                                                        qed
                                                      next
                                                        case Mock_VoterRegistration_Eligible
                                                        by sorry
                                                      qed
                                                    next
                                                      case Mock_Voter_Authentication
                                                      by sorry
                                                    qed
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
                                    next
                                      case Mock_Voter_Authentication
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
                      qed
                    qed
                  next
                    case SecureChannel_Receive_case_2
                    by sorry
                  qed
                next
                  case SecureChannel_Receive_case_2
                  by sorry
                qed
              next
                case SecureChannel_Receive_case_2
                by sorry
              qed
            next
              case SecureChannel_Receive_case_2
              by sorry
            qed
          qed
        qed
      next
        case BallotSubmission_DBB_AppendSubmittedBallot_case_2
        by sorry
      qed
    qed
  qed
next
  case case_2
  by sorry
qed
