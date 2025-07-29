simplify
solve( (#i1 < #i2)  ∥ (#i2 < #i1) )
  case case_1
  solve( !VA_Eligible_Voter( ~ec, ~va_id, pseudo1, ~sk_voter,
                             ballot_style1
         ) ▶₁ #i1 )
    case BallotSubmission_Mock_Voter_Authentication
    solve( !VA_Eligible_Voter( ~ec, ~va_id.1, pseudo2, ~sk_voter.1,
                               ballot_style2
           ) ▶₁ #i2 )
      case BallotSubmission_Mock_Voter_Authentication
      solve( !BB_Root( ~ec, ~bbid, ~ec, bb_root_hash ) ▶₂ #i1 )
        case BulletinBoard_Create
        solve( !BB_Root( ~ec, ~bbid.1, ~ec, bb_root_hash ) ▶₂ #i2 )
          case BulletinBoard_Create
          solve( !BB_Entry( ~bbid,
                            <'BBEntry_Ballot_Submission', ~ec, timestamp,
                             <'VA_Submit_Ballot', ~ec, pseudonym($V.1), pk(~sk_voter), ~bs,
                              cryptograms1>,
                             sign(<'VA_Submit_Ballot', ~ec, pseudonym($V.1), pk(~sk_voter),
                                   ~bs, cryptograms1>,
                                  '1', ~sk_voter)
                            >,
                            tracker1, %idx
                 ) ▶₃ #i1 )
            case BulletinBoard_Append
            solve( !BB_Entry( ~bbid,
                              <'BBEntry_Ballot_Submission', ~ec, timestamp.1,
                               <'VA_Submit_Ballot', ~ec, pseudonym($V.3), pk(~sk_voter.1), ~bs.1,
                                cryptograms2>,
                               sign(<'VA_Submit_Ballot', ~ec, pseudonym($V.3), pk(~sk_voter.1),
                                     ~bs.1, cryptograms2>,
                                    '1', ~sk_voter.1)
                              >,
                              tracker2, %idx.1
                   ) ▶₃ #i2 )
              case BulletinBoard_Append
              solve( BB_Append_Request( ~bbid,
                                        <'BBEntry_Ballot_Submission', ~ec, timestamp.1,
                                         <'VA_Submit_Ballot', ~ec, pseudonym($V.3),
                                          pk(~sk_voter.1), ~bs.1, cryptograms2>,
                                         sign(<'VA_Submit_Ballot', ~ec, pseudonym($V.3),
                                               pk(~sk_voter.1), ~bs.1, cryptograms2>,
                                              '1', ~sk_voter.1)
                                        >,
                                        %idx.1
                     )[+] ▶₂ #vr.15 )
                case BallotSubmission_DBB_AppendSubmittedBallot_case_1
                solve( BB_Append_Request( ~bbid,
                                          <'BBEntry_Ballot_Submission', ~ec, timestamp,
                                           <'VA_Submit_Ballot', ~ec, pseudonym($V.1),
                                            pk(~sk_voter), ~bs, cryptograms1>,
                                           sign(<'VA_Submit_Ballot', ~ec, pseudonym($V.1),
                                                 pk(~sk_voter), ~bs, cryptograms1>,
                                                '1', ~sk_voter)
                                          >,
                                          %idx
                       )[+] ▶₂ #vr.13 )
                  case BallotSubmission_DBB_AppendSubmittedBallot_case_1
                  by contradiction /* from formulas */
                next
                  case BallotSubmission_DBB_AppendSubmittedBallot_case_2
                  solve( BB_Trace_Entry( ~bbid, ~ec, h(<~ec, ~bbid>), %1 ) @ #j )
                    case BulletinBoard_Create
                    solve( (¬((%1%+%1) ⊏ (%idx%+%1)))  ∥ (#vr.14 < #j.1) )
                      case case_1
                      solve( BB_Current( ~bbid, c, h(<~ec, ~bbid>), %1 )[+] ▶₁ #j.1 )
                        case BulletinBoard_Create
                        solve( BB_Current( ~bbid, c,
                                           h(<
                                              <'BBEntry_Ballot_Submission', ~ec, %ts.1,
                                               <'VA_Submit_Ballot', ~ec, pseudonym($V.2),
                                                pk(~sk_voter.1), ~bs.1,
                                                ny_encrypt_c1(x.3, pk(x.4), x.5),
                                                ny_encrypt_c2(x.3, pk(x.4), x.5),
                                                ny_encrypt_p(x.3, pk(x.4), x.5)>,
                                               sign(<'VA_Submit_Ballot', ~ec, pseudonym($V.2),
                                                     pk(~sk_voter.1), ~bs.1,
                                                     ny_encrypt_c1(x.3, pk(x.4), x.5),
                                                     ny_encrypt_c2(x.3, pk(x.4), x.5),
                                                     ny_encrypt_p(x.3, pk(x.4), x.5)>,
                                                    '1', ~sk_voter.1)
                                              >,
                                              h(<~ec, ~bbid>)>),
                                           (%1%+%1)
                               )[+] ▶₁ #vr.13 )
                          case BulletinBoard_Append
                          solve( BB_Trace_Entry( ~bbid,
                                                 <'BBEntry_Ballot_Submission', ~ec, %ts.1,
                                                  <'VA_Submit_Ballot', ~ec, pseudonym($V.2),
                                                   pk(~sk_voter.1), ~bs.1,
                                                   ny_encrypt_c1(x.3, pk(x.4), x.5),
                                                   ny_encrypt_c2(x.3, pk(x.4), x.5),
                                                   ny_encrypt_p(x.3, pk(x.4), x.5)>,
                                                  sign(<'VA_Submit_Ballot', ~ec, pseudonym($V.2),
                                                        pk(~sk_voter.1), ~bs.1,
                                                        ny_encrypt_c1(x.3, pk(x.4), x.5),
                                                        ny_encrypt_c2(x.3, pk(x.4), x.5),
                                                        ny_encrypt_p(x.3, pk(x.4), x.5)>,
                                                       '1', ~sk_voter.1)
                                                 >,
                                                 h(<
                                                    <'BBEntry_Ballot_Submission', ~ec, %ts.1,
                                                     <'VA_Submit_Ballot', ~ec, pseudonym($V.2),
                                                      pk(~sk_voter.1), ~bs.1,
                                                      ny_encrypt_c1(x.3, pk(x.4), x.5),
                                                      ny_encrypt_c2(x.3, pk(x.4), x.5),
                                                      ny_encrypt_p(x.3, pk(x.4), x.5)>,
                                                     sign(<'VA_Submit_Ballot', ~ec,
                                                           pseudonym($V.2), pk(~sk_voter.1), ~bs.1,
                                                           ny_encrypt_c1(x.3, pk(x.4), x.5),
                                                           ny_encrypt_c2(x.3, pk(x.4), x.5),
                                                           ny_encrypt_p(x.3, pk(x.4), x.5)>,
                                                          '1', ~sk_voter.1)
                                                    >,
                                                    h(<~ec, ~bbid>)>),
                                                 (%1%+%1)
                                 ) @ #j.1 )
                            case BulletinBoard_Append
                            solve( SecureReceive( ~cid, <~ec, 'DBB'>, ~va_id,
                                                  <'DBB_Ballot_Tracker', ~ec,
                                                   h(<
                                                      <'BBEntry_Ballot_Submission', ~ec, %ts,
                                                       <'VA_Submit_Ballot', ~ec, pseudonym($V.1),
                                                        pk(~sk_voter), ~bs,
                                                        ny_encrypt_c1(x, pk(x.1), x.2),
                                                        ny_encrypt_c2(x, pk(x.1), x.2),
                                                        ny_encrypt_p(x, pk(x.1), x.2)>,
                                                       sign(<'VA_Submit_Ballot', ~ec,
                                                             pseudonym($V.1), pk(~sk_voter), ~bs,
                                                             ny_encrypt_c1(x, pk(x.1), x.2),
                                                             ny_encrypt_c2(x, pk(x.1), x.2),
                                                             ny_encrypt_p(x, pk(x.1), x.2)>,
                                                            '1', ~sk_voter)
                                                      >,
                                                      h(<
                                                         <'BBEntry_Ballot_Submission', ~ec, %ts.1,
                                                          <'VA_Submit_Ballot', ~ec,
                                                           pseudonym($V.2), pk(~sk_voter.1), ~bs.1,
                                                           ny_encrypt_c1(x.3, pk(x.4), x.5),
                                                           ny_encrypt_c2(x.3, pk(x.4), x.5),
                                                           ny_encrypt_p(x.3, pk(x.4), x.5)>,
                                                          sign(<'VA_Submit_Ballot', ~ec,
                                                                pseudonym($V.2), pk(~sk_voter.1),
                                                                ~bs.1,
                                                                ny_encrypt_c1(x.3, pk(x.4), x.5),
                                                                ny_encrypt_c2(x.3, pk(x.4), x.5),
                                                                ny_encrypt_p(x.3, pk(x.4), x.5)>,
                                                               '1', ~sk_voter.1)
                                                         >,
                                                         h(<~ec, ~bbid>)>)
                                                     >)
                                                  >
                                   ) ▶₄ #i1 )
                              case SecureChannel_Receive_case_1
                              solve( SecureReceive( ~cid.1, <~ec, 'DBB'>, ~va_id.1,
                                                    <'DBB_Ballot_Tracker', ~ec,
                                                     h(<
                                                        <'BBEntry_Ballot_Submission', ~ec, %ts.1,
                                                         <'VA_Submit_Ballot', ~ec, pseudonym($V.2),
                                                          pk(~sk_voter.1), ~bs.1,
                                                          ny_encrypt_c1(x.3, pk(x.4), x.5),
                                                          ny_encrypt_c2(x.3, pk(x.4), x.5),
                                                          ny_encrypt_p(x.3, pk(x.4), x.5)>,
                                                         sign(<'VA_Submit_Ballot', ~ec,
                                                               pseudonym($V.2), pk(~sk_voter.1),
                                                               ~bs.1,
                                                               ny_encrypt_c1(x.3, pk(x.4), x.5),
                                                               ny_encrypt_c2(x.3, pk(x.4), x.5),
                                                               ny_encrypt_p(x.3, pk(x.4), x.5)>,
                                                              '1', ~sk_voter.1)
                                                        >,
                                                        h(<~ec, ~bbid>)>)
                                                    >
                                     ) ▶₄ #i2 )
                                case SecureChannel_Receive_case_1
                                solve( SecureReceive( ~cid.1, ~va_id.1, <~ec, 'DBB'>,
                                                      <
                                                       <'VA_Submit_Ballot', ~ec, pseudonym($V.2),
                                                        pk(~sk_voter.1), ~bs.1,
                                                        ny_encrypt_c1(x.3, pk(x.4), x.5),
                                                        ny_encrypt_c2(x.3, pk(x.4), x.5),
                                                        ny_encrypt_p(x.3, pk(x.4), x.5)>,
                                                       sign(<'VA_Submit_Ballot', ~ec,
                                                             pseudonym($V.2), pk(~sk_voter.1),
                                                             ~bs.1,
                                                             ny_encrypt_c1(x.3, pk(x.4), x.5),
                                                             ny_encrypt_c2(x.3, pk(x.4), x.5),
                                                             ny_encrypt_p(x.3, pk(x.4), x.5)>,
                                                            '1', ~sk_voter.1)
                                                      >
                                       ) ▶₁ #vr.15 )
                                  case SecureChannel_Receive_case_1
                                  solve( SecureReceive( ~cid, ~va_id, <~ec, 'DBB'>,
                                                        <
                                                         <'VA_Submit_Ballot', ~ec, pseudonym($V.1),
                                                          pk(~sk_voter), ~bs,
                                                          ny_encrypt_c1(x, pk(x.1), x.2),
                                                          ny_encrypt_c2(x, pk(x.1), x.2),
                                                          ny_encrypt_p(x, pk(x.1), x.2)>,
                                                         sign(<'VA_Submit_Ballot', ~ec,
                                                               pseudonym($V.1), pk(~sk_voter), ~bs,
                                                               ny_encrypt_c1(x, pk(x.1), x.2),
                                                               ny_encrypt_c2(x, pk(x.1), x.2),
                                                               ny_encrypt_p(x, pk(x.1), x.2)>,
                                                              '1', ~sk_voter)
                                                        >
                                         ) ▶₁ #vr.17 )
                                    case SecureChannel_Receive_case_1
                                    solve( VA_State_BallotSubmitResponse( ~ec, ~va_id, ~cid, $V,
                                                                          ~ballot,
                                                                          <
                                                                           ny_encrypt_c1(~ballot.1,
                                                                                         pk(~k),
                                                                                         ~r),
                                                                           ny_encrypt_c2(~ballot.1,
                                                                                         pk(~k),
                                                                                         ~r),
                                                                           ny_encrypt_p(~ballot.1,
                                                                                        pk(~k), ~r)
                                                                          >,
                                                                          ~r.1
                                           ) ▶₀ #i1 )
                                      case BallotSubmission_VA_PresentBallot
                                      solve( VA_State_BallotSubmitResponse( ~ec, ~va_id.1, ~cid.1,
                                                                            $V.2, ~ballot.2,
                                                                            <
                                                                             ny_encrypt_c1(~ballot.1,
                                                                                           pk(~k),
                                                                                           ~r.1),
                                                                             ny_encrypt_c2(~ballot.1,
                                                                                           pk(~k),
                                                                                           ~r.1),
                                                                             ny_encrypt_p(~ballot.1,
                                                                                          pk(~k),
                                                                                          ~r.1)
                                                                            >,
                                                                            ~r.2
                                             ) ▶₀ #i2 )
                                        case BallotSubmission_VA_PresentBallot
                                        solve( AuthCount( ~ec, %i ) ▶₀ #vr )
                                          case BallotSubmission_Mock_Finalize_Election_Setup
                                          solve( BallotStyleCount( ~ec, %idx_bs ) ▶₀ #vr.1 )
                                            case BallotSubmission_Mock_BallotStyle
                                            solve( VoterCount( ~ec, %idx_ev ) ▶₀ #vr.2 )
                                              case BallotSubmission_Mock_EC_And_Initial_Counters
                                              solve( AuthCount( ~ec, %i.1 ) ▶₀ #vr.3 )
                                                case BallotSubmission_Mock_Voter_Authentication
                                                solve( BallotStyleCount( ~ec, %idx_bs ) ▶₀ #vr.4 )
                                                  case BallotSubmission_Mock_BallotStyle
                                                  solve( VoterCount( ~ec, %idx_ev ) ▶₀ #vr.5 )
                                                    case BallotSubmission_Mock_EC_And_Initial_Counters
                                                    by contradiction /* from formulas */
                                                  next
                                                    case BallotSubmission_Mock_VoterRegistration_Eligible
                                                    solve( BallotStyleCount( ~ec, %idx_bs_unused
                                                           ) ▶₀ #vr.7 )
                                                      case BallotSubmission_Mock_BallotStyle
                                                      solve( VoterCount( ~ec, %idx_ev_unused
                                                             ) ▶₀ #vr.8 )
                                                        case BallotSubmission_Mock_EC_And_Initial_Counters
                                                        solve( BallotStyleCount( ~ec, %unused
                                                               ) ▶₀ #vr.10 )
                                                          case BallotSubmission_Mock_BallotStyle
                                                          solve( BallotStyleCount( ~ec, %idx_bs
                                                                 ) ▶₀ #vr.31 )
                                                            case BallotSubmission_Mock_BallotStyle
                                                            solve( VoterCount( ~ec, %idx_ev
                                                                   ) ▶₀ #vr.32 )
                                                              case BallotSubmission_Mock_EC_And_Initial_Counters
                                                              solve( VoterCount( ~ec, %i.3
                                                                     ) ▶₀ #vr.32 )
                                                                case BallotSubmission_Mock_EC_And_Initial_Counters
                                                                solve( VoterCount( ~ec, %i.5
                                                                       ) ▶₀ #vr.9 )
                                                                  case BallotSubmission_Mock_VoterRegistration_Eligible
                                                                  solve( (¬(#vr.30 < #vr.15))  ∥
                                                                         (¬(%1 ⊏ %i.1)) )
                                                                    case case_1
                                                                    solve( BallotStyleCount( ~ec,
                                                                                             %unused
                                                                           ) ▶₀ #vr.35 )
                                                                      case BallotSubmission_Mock_BallotStyle
                                                                      solve( DBB_Clock( %ts
                                                                             ) ▶₁ #vr.14 )
                                                                        case BallotSubmission_DBB_AppendSubmittedBallot_case_1
                                                                        by sorry
                                                                      next
                                                                        case BallotSubmission_DBB_AppendSubmittedBallot_case_2
                                                                        by sorry
                                                                      next
                                                                        case BallotSubmsision_Mock_DBBTimestamp
                                                                        solve( DBB_Clock( %ts
                                                                               ) ▶₁ #vr.12 )
                                                                          case BallotSubmission_DBB_AppendSubmittedBallot_case_1
                                                                          by sorry
                                                                        next
                                                                          case BallotSubmission_DBB_AppendSubmittedBallot_case_2
                                                                          by sorry
                                                                        next
                                                                          case BallotSubmsision_Mock_DBBTimestamp
                                                                          solve( BallotStyleCount( ~ec,
                                                                                                   %i.4
                                                                                 ) ▶₀ #vr.8 )
                                                                            case BallotSubmission_Mock_BallotStyle
                                                                            solve( AuthCount( ~ec,
                                                                                              %i.1
                                                                                   ) ▶₀ #vr.30 )
                                                                              case BallotSubmission_Mock_Finalize_Election_Setup
                                                                              by contradiction
                                                                                 /* cyclic */
                                                                            next
                                                                              case BallotSubmission_Mock_Voter_Authentication
                                                                              solve( VoterCount( ~ec,
                                                                                                 %i.5
                                                                                     ) ▶₀ #vr.34 )
                                                                                case BallotSubmission_Mock_EC_And_Initial_Counters
                                                                                solve( VoterCount( ~ec,
                                                                                                   %idx_ev
                                                                                       ) ▶₀ #vr.36 )
                                                                                  case BallotSubmission_Mock_EC_And_Initial_Counters
                                                                                  solve( AuthCount( ~ec,
                                                                                                    %i.1
                                                                                         ) ▶₀ #vr.34 )
                                                                                    case BallotSubmission_Mock_Finalize_Election_Setup
                                                                                    solve( BallotStyleCount( ~ec,
                                                                                                             %i.3
                                                                                           ) ▶₀ #vr.33 )
                                                                                      case BallotSubmission_Mock_BallotStyle
                                                                                      solve( BallotStyleCount( ~ec,
                                                                                                               %i.2
                                                                                             ) ▶₀ #vr.30 )
                                                                                        case BallotSubmission_Mock_BallotStyle
                                                                                        solve( BallotStyleCount( ~ec,
                                                                                                                 %i.1
                                                                                               ) ▶₀ #vr.29 )
                                                                                          case BallotSubmission_Mock_BallotStyle
                                                                                          solve( BallotStyleCount( ~ec,
                                                                                                                   %i
                                                                                                 ) ▶₀ #vr.26 )
                                                                                            case BallotSubmission_Mock_BallotStyle
                                                                                            by sorry
                                                                                          next
                                                                                            case BallotSubmission_Mock_EC_And_Initial_Counters
                                                                                            solve( BallotStyleCount( ~ec,
                                                                                                                     %i.2
                                                                                                   ) ▶₀ #vr.34 )
                                                                                              case BallotSubmission_Mock_BallotStyle
                                                                                              by sorry
                                                                                            next
                                                                                              case BallotSubmission_Mock_EC_And_Initial_Counters
                                                                                              solve( BallotStyleCount( ~ec,
                                                                                                                       %i.1
                                                                                                     ) ▶₀ #vr.33 )
                                                                                                case BallotSubmission_Mock_BallotStyle
                                                                                                simplify
                                                                                                by contradiction
                                                                                                   /*
                                                                                                   cyclic
                                                                                                   */
                                                                                              next
                                                                                                case BallotSubmission_Mock_EC_And_Initial_Counters
                                                                                                solve( BallotStyleCount( ~ec,
                                                                                                                         %i
                                                                                                       ) ▶₀ #vr.31 )
                                                                                                  case BallotSubmission_Mock_BallotStyle
                                                                                                  simplify
                                                                                                  by contradiction
                                                                                                     /*
                                                                                                     cyclic
                                                                                                     */
                                                                                                next
                                                                                                  case BallotSubmission_Mock_EC_And_Initial_Counters
                                                                                                  SOLVED // trace found
                                                                                                qed
                                                                                              qed
                                                                                            qed
                                                                                          qed
                                                                                        next
                                                                                          case BallotSubmission_Mock_EC_And_Initial_Counters
                                                                                          by sorry
                                                                                        qed
                                                                                      next
                                                                                        case BallotSubmission_Mock_EC_And_Initial_Counters
                                                                                        by sorry
                                                                                      qed
                                                                                    next
                                                                                      case BallotSubmission_Mock_EC_And_Initial_Counters
                                                                                      by sorry
                                                                                    qed
                                                                                  next
                                                                                    case BallotSubmission_Mock_Voter_Authentication
                                                                                    by sorry
                                                                                  qed
                                                                                next
                                                                                  case BallotSubmission_Mock_VoterRegistration_Eligible
                                                                                  by sorry
                                                                                qed
                                                                              next
                                                                                case BallotSubmission_Mock_VoterRegistration_Eligible
                                                                                by sorry
                                                                              qed
                                                                            qed
                                                                          next
                                                                            case BallotSubmission_Mock_EC_And_Initial_Counters
                                                                            simplify
                                                                            by contradiction
                                                                               /* cyclic */
                                                                          qed
                                                                        qed
                                                                      qed
                                                                    next
                                                                      case BallotSubmission_Mock_EC_And_Initial_Counters
                                                                      simplify
                                                                      by sorry
                                                                    qed
                                                                  next
                                                                    case case_2
                                                                    by sorry
                                                                  qed
                                                                qed
                                                              next
                                                                case BallotSubmission_Mock_VoterRegistration_Eligible
                                                                by sorry
                                                              qed
                                                            next
                                                              case BallotSubmission_Mock_VoterRegistration_Eligible
                                                              by sorry
                                                            qed
                                                          next
                                                            case BallotSubmission_Mock_EC_And_Initial_Counters
                                                            by sorry
                                                          qed
                                                        next
                                                          case BallotSubmission_Mock_EC_And_Initial_Counters
                                                          simplify
                                                          by sorry
                                                        qed
                                                      next
                                                        case BallotSubmission_Mock_VoterRegistration_Eligible
                                                        by sorry
                                                      qed
                                                    next
                                                      case BallotSubmission_Mock_EC_And_Initial_Counters
                                                      by sorry
                                                    qed
                                                  qed
                                                next
                                                  case BallotSubmission_Mock_EC_And_Initial_Counters
                                                  by sorry
                                                qed
                                              qed
                                            next
                                              case BallotSubmission_Mock_VoterRegistration_Eligible
                                              by sorry
                                            qed
                                          next
                                            case BallotSubmission_Mock_EC_And_Initial_Counters
                                            by sorry
                                          qed
                                        next
                                          case BallotSubmission_Mock_Voter_Authentication
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
                      qed
                    next
                      case case_2
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
        qed
      qed
    qed
  qed
next
  case case_2
  by sorry
qed
