simplify
solve( !BB_Entry( ~bbid,
                  <'BBEntry_Ballot_Cast', %ts_cast,
                   <
                    <'VA_Submit_Ballot', ~ec, pseudo1, pk(~sk_voter), ballot_style,
                     cryptograms1>,
                    sign(<'VA_Submit_Ballot', ~ec, pseudo1, pk(~sk_voter),
                          ballot_style, cryptograms1>,
                         '1', ~sk_voter)
                   >,
                   <'VA_Cast_Ballot', ~ec, pseudo1, pk(~sk_voter), tracker>,
                   sign(<'VA_Cast_Ballot', ~ec, pseudo1, pk(~sk_voter), tracker>, '1',
                        ~sk_voter)
                  >,
                  cast_tracker1, %idx_cast
       ) ▶₄ #i1 )
  case BulletinBoard_Append
  solve( !BB_Entry( ~bbid.1,
                    <'BBEntry_Ballot_Cast', %ts_cast.1,
                     <
                      <'VA_Submit_Ballot', ~ec, pseudo2, pk(~sk_voter.1),
                       ballot_style.1, cryptograms2>,
                      sign(<'VA_Submit_Ballot', ~ec, pseudo2, pk(~sk_voter.1),
                            ballot_style.1, cryptograms2>,
                           '1', ~sk_voter.1)
                     >,
                     <'VA_Cast_Ballot', ~ec, pseudo2, pk(~sk_voter.1), tracker.1>,
                     sign(<'VA_Cast_Ballot', ~ec, pseudo2, pk(~sk_voter.1), tracker.1>,
                          '1', ~sk_voter.1)
                    >,
                    cast_tracker2, %idx_cast
         ) ▶₄ #i2 )
    case BulletinBoard_Append
    solve( !BB_Root( ~ec, ~bbid, r_unused, rh_unused ) ▶₂ #i1 )
      case BulletinBoard_Create
      solve( !BB_Entry( ~bbid, sub_bb_entry, sub_tracker1, %idx_sub
             ) ▶₃ #i1 )
        case BulletinBoard_Append
        solve( !BB_Root( ~ec, ~bbid.1, r_unused, rh_unused ) ▶₂ #i2 )
          case BulletinBoard_Create
          solve( !BB_Entry( ~bbid, sub_bb_entry.1, sub_tracker2, %idx_sub
                 ) ▶₃ #i2 )
            case BulletinBoard_Append
            solve( VA_State_BallotCastResponse( ~ec, ~va_id, ~cid, pseudo1,
                                                ~ballot, cryptograms1, ~r, h(<sub_bb_entry, ch>)
                   ) ▶₀ #i1 )
              case BallotCast_VA_Cast_case_1
              simplify
              solve( !VA_Eligible_Voter( ~ec, ~va_id, pseudonym($V), ~sk_voter.2,
                                         ballot_style
                     ) ▶₁ #i1 )
                case Mock_Voter_Authentication
                solve( VA_State_BallotCastResponse( ~ec, ~va_id.1, ~cid.1, pseudo2,
                                                    ~ballot.1, cryptograms2, ~r.1,
                                                    h(<sub_bb_entry, ch.1>)
                       ) ▶₀ #i2 )
                  case BallotCast_VA_Cast_case_1
                  by sorry
                next
                  case BallotCast_VA_Cast_case_2
                  simplify
                  solve( !VA_Eligible_Voter( ~ec, ~va_id.1, pseudonym($V.1),
                                             ~sk_voter.4, ballot_style
                         ) ▶₁ #i2 )
                    case Mock_Voter_Authentication
                    solve( SecureReceive( ~cid, <~ec, 'DBB'>, ~va_id,
                                          <'DBB_Cast_Confirmation', ~ec,
                                           h(<
                                              <'BBEntry_Ballot_Submission', ~ec, %ts,
                                               <'VA_Submit_Ballot', ~ec, pseudonym($V),
                                                pk(~sk_voter), ~bs_unused,
                                                ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                                ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                                ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                               sign(<'VA_Submit_Ballot', ~ec, pseudonym($V),
                                                     pk(~sk_voter), ~bs_unused,
                                                     ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                                     ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                                     ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                                    '1', ~sk_voter.1)
                                              >,
                                              h(<~ec, ~bbid>)>),
                                           h(<
                                              <'BBEntry_Ballot_Cast', %ts_cast,
                                               <
                                                <'VA_Submit_Ballot', ~ec, pseudonym($V),
                                                 pk(~sk_voter.1), ~bs_unused,
                                                 ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                                 ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                                 ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                                sign(<'VA_Submit_Ballot', ~ec, pseudonym($V),
                                                      pk(~sk_voter.1), ~bs_unused,
                                                      ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                                      ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                                      ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                                     '1', ~sk_voter.1)
                                               >,
                                               <'VA_Cast_Ballot', ~ec, pseudonym($V),
                                                pk(~sk_voter.1), tracker>,
                                               sign(<'VA_Cast_Ballot', ~ec, pseudonym($V),
                                                     pk(~sk_voter.1), tracker>,
                                                    '1', ~sk_voter.1)
                                              >,
                                              ch>)
                                          >
                           ) ▶₅ #i1 )
                      case SecureChannel_Receive_case_1
                      simplify
                      solve( SecureReceive( ~cid.1, <~ec, 'DBB'>, ~va_id.1,
                                            <'DBB_Cast_Confirmation', ~ec,
                                             h(<
                                                <'BBEntry_Ballot_Submission', ~ec, %ts.2,
                                                 <'VA_Submit_Ballot', ~ec, pseudonym($V.1),
                                                  pk(~sk_voter.1), ~bs_unused.1,
                                                  ny_encrypt_c1(~ballot.1, pk(~sk_election), ~r.1),
                                                  ny_encrypt_c2(~ballot.1, pk(~sk_election), ~r.1),
                                                  ny_encrypt_p(~ballot.1, pk(~sk_election), ~r.1)>,
                                                 sign(<'VA_Submit_Ballot', ~ec, pseudonym($V.1),
                                                       pk(~sk_voter.1), ~bs_unused.1,
                                                       ny_encrypt_c1(~ballot.1, pk(~sk_election),
                                                                     ~r.1),
                                                       ny_encrypt_c2(~ballot.1, pk(~sk_election),
                                                                     ~r.1),
                                                       ny_encrypt_p(~ballot.1, pk(~sk_election),
                                                                    ~r.1)
                                                      >,
                                                      '1', ~sk_voter.2)
                                                >,
                                                h(<p, ch.1>)>),
                                             h(<
                                                <'BBEntry_Ballot_Cast', %ts_cast,
                                                 <
                                                  <'VA_Submit_Ballot', ~ec, pseudonym($V.1),
                                                   pk(~sk_voter.2), ~bs_unused.1,
                                                   ny_encrypt_c1(~ballot.1, pk(~sk_election),
                                                                 ~r.1),
                                                   ny_encrypt_c2(~ballot.1, pk(~sk_election),
                                                                 ~r.1),
                                                   ny_encrypt_p(~ballot.1, pk(~sk_election), ~r.1)
                                                  >,
                                                  sign(<'VA_Submit_Ballot', ~ec, pseudonym($V.1),
                                                        pk(~sk_voter.2), ~bs_unused.1,
                                                        ny_encrypt_c1(~ballot.1, pk(~sk_election),
                                                                      ~r.1),
                                                        ny_encrypt_c2(~ballot.1, pk(~sk_election),
                                                                      ~r.1),
                                                        ny_encrypt_p(~ballot.1, pk(~sk_election),
                                                                     ~r.1)
                                                       >,
                                                       '1', ~sk_voter.2)
                                                 >,
                                                 <'VA_Cast_Ballot', ~ec, pseudonym($V.1),
                                                  pk(~sk_voter.2), tracker>,
                                                 sign(<'VA_Cast_Ballot', ~ec, pseudonym($V.1),
                                                       pk(~sk_voter.2), tracker>,
                                                      '1', ~sk_voter.2)
                                                >,
                                                ch.2>)
                                            >
                             ) ▶₅ #i2 )
                        case SecureChannel_Receive_case_1
                        solve( BB_Trace_Entry( ~bbid,
                                               <'BBEntry_Voter_Authorization', ~ec, %ts.1,
                                                <'EAS_Authorize_Voter', ~ec, pseudonym($V),
                                                 pk(~sk_voter), ~bs_unused>,
                                                sign(<'EAS_Authorize_Voter', ~ec, pseudonym($V),
                                                      pk(~sk_voter), ~bs_unused>,
                                                     '1', ~sk_eas)
                                               >,
                                               h(<
                                                  <'BBEntry_Voter_Authorization', ~ec, %ts.1,
                                                   <'EAS_Authorize_Voter', ~ec, pseudonym($V),
                                                    pk(~sk_voter), ~bs_unused>,
                                                   sign(<'EAS_Authorize_Voter', ~ec, pseudonym($V),
                                                         pk(~sk_voter), ~bs_unused>,
                                                        '1', ~sk_eas)
                                                  >,
                                                  h(<e_unused, ch>)>),
                                               (%idx%+%1%+%1)
                               ) @ #j.1 )
                          case BulletinBoard_Append
                          solve( BB_Trace_Entry( ~bbid,
                                                 <'BBEntry_Voter_Authorization', ~ec, %ts.3,
                                                  <'EAS_Authorize_Voter', ~ec, pseudonym($V.1),
                                                   pk(~sk_voter.1), ~bs_unused.1>,
                                                  sign(<'EAS_Authorize_Voter', ~ec,
                                                        pseudonym($V.1), pk(~sk_voter.1),
                                                        ~bs_unused.1>,
                                                       '1', ~sk_eas)
                                                 >,
                                                 h(<
                                                    <'BBEntry_Voter_Authorization', ~ec, %ts.3,
                                                     <'EAS_Authorize_Voter', ~ec, pseudonym($V.1),
                                                      pk(~sk_voter.1), ~bs_unused.1>,
                                                     sign(<'EAS_Authorize_Voter', ~ec,
                                                           pseudonym($V.1), pk(~sk_voter.1),
                                                           ~bs_unused.1>,
                                                          '1', ~sk_eas)
                                                    >,
                                                    h(<e_unused.1, ch.2>)>),
                                                 (%idx.2%+%1%+%1)
                                 ) @ #j.2 )
                            case BulletinBoard_Append
                            solve( BB_Trace_Entry( ~bbid,
                                                   <'BBEntry_Ballot_Submission', ~ec, %ts,
                                                    <'VA_Submit_Ballot', ~ec, pseudonym($V),
                                                     pk(~sk_voter), ~bs_unused,
                                                     ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                                     ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                                     ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                                    sign(<'VA_Submit_Ballot', ~ec, pseudonym($V),
                                                          pk(~sk_voter), ~bs_unused,
                                                          ny_encrypt_c1(~ballot, pk(~sk_election),
                                                                        ~r),
                                                          ny_encrypt_c2(~ballot, pk(~sk_election),
                                                                        ~r),
                                                          ny_encrypt_p(~ballot, pk(~sk_election),
                                                                       ~r)
                                                         >,
                                                         '1', ~sk_voter)
                                                   >,
                                                   h(<
                                                      <'BBEntry_Ballot_Submission', ~ec, %ts,
                                                       <'VA_Submit_Ballot', ~ec, pseudonym($V),
                                                        pk(~sk_voter), ~bs_unused,
                                                        ny_encrypt_c1(~ballot, pk(~sk_election),
                                                                      ~r),
                                                        ny_encrypt_c2(~ballot, pk(~sk_election),
                                                                      ~r),
                                                        ny_encrypt_p(~ballot, pk(~sk_election), ~r)
                                                       >,
                                                       sign(<'VA_Submit_Ballot', ~ec,
                                                             pseudonym($V), pk(~sk_voter),
                                                             ~bs_unused,
                                                             ny_encrypt_c1(~ballot,
                                                                           pk(~sk_election), ~r),
                                                             ny_encrypt_c2(~ballot,
                                                                           pk(~sk_election), ~r),
                                                             ny_encrypt_p(~ballot, pk(~sk_election),
                                                                          ~r)
                                                            >,
                                                            '1', ~sk_voter)
                                                      >,
                                                      h(<~ec, ~bbid>)>),
                                                   (%1%+%1)
                                   ) @ #vr.10 )
                              case BulletinBoard_Append
                              solve( BB_Trace_Entry( ~bbid,
                                                     <'BBEntry_Ballot_Submission', ~ec, %ts.2,
                                                      <'VA_Submit_Ballot', ~ec, pseudonym($V.1),
                                                       pk(~sk_voter.1), ~bs_unused.1,
                                                       ny_encrypt_c1(~ballot.1, pk(~sk_election),
                                                                     ~r.1),
                                                       ny_encrypt_c2(~ballot.1, pk(~sk_election),
                                                                     ~r.1),
                                                       ny_encrypt_p(~ballot.1, pk(~sk_election),
                                                                    ~r.1)
                                                      >,
                                                      sign(<'VA_Submit_Ballot', ~ec,
                                                            pseudonym($V.1), pk(~sk_voter.1),
                                                            ~bs_unused.1,
                                                            ny_encrypt_c1(~ballot.1,
                                                                          pk(~sk_election), ~r.1),
                                                            ny_encrypt_c2(~ballot.1,
                                                                          pk(~sk_election), ~r.1),
                                                            ny_encrypt_p(~ballot.1,
                                                                         pk(~sk_election), ~r.1)
                                                           >,
                                                           '1', ~sk_voter.1)
                                                     >,
                                                     h(<
                                                        <'BBEntry_Ballot_Submission', ~ec, %ts.2,
                                                         <'VA_Submit_Ballot', ~ec, pseudonym($V.1),
                                                          pk(~sk_voter.1), ~bs_unused.1,
                                                          ny_encrypt_c1(~ballot.1, pk(~sk_election),
                                                                        ~r.1),
                                                          ny_encrypt_c2(~ballot.1, pk(~sk_election),
                                                                        ~r.1),
                                                          ny_encrypt_p(~ballot.1, pk(~sk_election),
                                                                       ~r.1)
                                                         >,
                                                         sign(<'VA_Submit_Ballot', ~ec,
                                                               pseudonym($V.1), pk(~sk_voter.1),
                                                               ~bs_unused.1,
                                                               ny_encrypt_c1(~ballot.1,
                                                                             pk(~sk_election),
                                                                             ~r.1),
                                                               ny_encrypt_c2(~ballot.1,
                                                                             pk(~sk_election),
                                                                             ~r.1),
                                                               ny_encrypt_p(~ballot.1,
                                                                            pk(~sk_election), ~r.1)
                                                              >,
                                                              '1', ~sk_voter.1)
                                                        >,
                                                        h(<p, ch.1>)>),
                                                     (%idx.1%+%1%+%1)
                                     ) @ #vr.11 )
                                case BulletinBoard_Append
                                solve( BB_Current( ~bbid, c.1,
                                                   h(<
                                                      <'BBEntry_Voter_Authorization', ~ec, %ts.1,
                                                       <'EAS_Authorize_Voter', ~ec, pseudonym($V),
                                                        pk(~sk_voter), ~bs_unused>,
                                                       sign(<'EAS_Authorize_Voter', ~ec,
                                                             pseudonym($V), pk(~sk_voter),
                                                             ~bs_unused>,
                                                            '1', ~sk_eas)
                                                      >,
                                                      h(<e_unused, ch>)>),
                                                   (%idx%+%1%+%1)
                                       )[+] ▶₁ #vr )
                                  case BulletinBoard_Append
                                  solve( BB_Append_Request( ~bbid,
                                                            <'BBEntry_Ballot_Cast', (%ts.1%+%1),
                                                             <
                                                              <'VA_Submit_Ballot', ~ec,
                                                               pseudonym($V), pk(~sk_voter),
                                                               ~bs_unused,
                                                               ny_encrypt_c1(~ballot,
                                                                             pk(~sk_election), ~r),
                                                               ny_encrypt_c2(~ballot,
                                                                             pk(~sk_election), ~r),
                                                               ny_encrypt_p(~ballot,
                                                                            pk(~sk_election), ~r)
                                                              >,
                                                              sign(<'VA_Submit_Ballot', ~ec,
                                                                    pseudonym($V), pk(~sk_voter),
                                                                    ~bs_unused,
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
                                                             <'VA_Cast_Ballot', ~ec, pseudonym($V),
                                                              pk(~sk_voter),
                                                              h(<
                                                                 <'BBEntry_Ballot_Submission', ~ec,
                                                                  %ts,
                                                                  <'VA_Submit_Ballot', ~ec,
                                                                   pseudonym($V), pk(~sk_voter),
                                                                   ~bs_unused,
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
                                                                  sign(<'VA_Submit_Ballot', ~ec,
                                                                        pseudonym($V),
                                                                        pk(~sk_voter), ~bs_unused,
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
                                                                 h(<~ec, ~bbid>)>)
                                                             >,
                                                             sign(<'VA_Cast_Ballot', ~ec,
                                                                   pseudonym($V), pk(~sk_voter),
                                                                   h(<
                                                                      <'BBEntry_Ballot_Submission',
                                                                       ~ec, %ts,
                                                                       <'VA_Submit_Ballot', ~ec,
                                                                        pseudonym($V),
                                                                        pk(~sk_voter), ~bs_unused,
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
                                                                       sign(<'VA_Submit_Ballot',
                                                                             ~ec, pseudonym($V),
                                                                             pk(~sk_voter),
                                                                             ~bs_unused,
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
                                                                      h(<~ec, ~bbid>)>)
                                                                  >,
                                                                  '1', ~sk_voter)
                                                            >,
                                                            (%idx%+%1%+%1)
                                         )[+] ▶₂ #vr )
                                    case BallotCast_DBB_AppendCastBallot
                                    solve( BB_Current( ~bbid, c.3,
                                                       h(<
                                                          <'BBEntry_Voter_Authorization', ~ec,
                                                           %ts.3,
                                                           <'EAS_Authorize_Voter', ~ec,
                                                            pseudonym($V.1), pk(~sk_voter.1),
                                                            ~bs_unused.1>,
                                                           sign(<'EAS_Authorize_Voter', ~ec,
                                                                 pseudonym($V.1), pk(~sk_voter.1),
                                                                 ~bs_unused.1>,
                                                                '1', ~sk_eas)
                                                          >,
                                                          h(<e_unused.1, ch.2>)>),
                                                       (%idx.2%+%1%+%1)
                                           )[+] ▶₁ #vr.9 )
                                      case BulletinBoard_Append
                                      solve( BB_Append_Request( ~bbid,
                                                                <'BBEntry_Ballot_Cast',
                                                                 (%ts.3%+%1),
                                                                 <
                                                                  <'VA_Submit_Ballot', ~ec,
                                                                   pseudonym($V.1),
                                                                   pk(~sk_voter.1), ~bs_unused.1,
                                                                   ny_encrypt_c1(~ballot.1,
                                                                                 pk(~sk_election),
                                                                                 ~r.1),
                                                                   ny_encrypt_c2(~ballot.1,
                                                                                 pk(~sk_election),
                                                                                 ~r.1),
                                                                   ny_encrypt_p(~ballot.1,
                                                                                pk(~sk_election),
                                                                                ~r.1)
                                                                  >,
                                                                  sign(<'VA_Submit_Ballot', ~ec,
                                                                        pseudonym($V.1),
                                                                        pk(~sk_voter.1),
                                                                        ~bs_unused.1,
                                                                        ny_encrypt_c1(~ballot.1,
                                                                                      pk(~sk_election),
                                                                                      ~r.1),
                                                                        ny_encrypt_c2(~ballot.1,
                                                                                      pk(~sk_election),
                                                                                      ~r.1),
                                                                        ny_encrypt_p(~ballot.1,
                                                                                     pk(~sk_election),
                                                                                     ~r.1)
                                                                       >,
                                                                       '1', ~sk_voter.1)
                                                                 >,
                                                                 <'VA_Cast_Ballot', ~ec,
                                                                  pseudonym($V.1), pk(~sk_voter.1),
                                                                  h(<
                                                                     <'BBEntry_Ballot_Submission',
                                                                      ~ec, %ts.2,
                                                                      <'VA_Submit_Ballot', ~ec,
                                                                       pseudonym($V.1),
                                                                       pk(~sk_voter.1),
                                                                       ~bs_unused.1,
                                                                       ny_encrypt_c1(~ballot.1,
                                                                                     pk(~sk_election),
                                                                                     ~r.1),
                                                                       ny_encrypt_c2(~ballot.1,
                                                                                     pk(~sk_election),
                                                                                     ~r.1),
                                                                       ny_encrypt_p(~ballot.1,
                                                                                    pk(~sk_election),
                                                                                    ~r.1)
                                                                      >,
                                                                      sign(<'VA_Submit_Ballot',
                                                                            ~ec, pseudonym($V.1),
                                                                            pk(~sk_voter.1),
                                                                            ~bs_unused.1,
                                                                            ny_encrypt_c1(~ballot.1,
                                                                                          pk(~sk_election),
                                                                                          ~r.1),
                                                                            ny_encrypt_c2(~ballot.1,
                                                                                          pk(~sk_election),
                                                                                          ~r.1),
                                                                            ny_encrypt_p(~ballot.1,
                                                                                         pk(~sk_election),
                                                                                         ~r.1)
                                                                           >,
                                                                           '1', ~sk_voter.1)
                                                                     >,
                                                                     h(<p, ch.1>)>)
                                                                 >,
                                                                 sign(<'VA_Cast_Ballot', ~ec,
                                                                       pseudonym($V.1),
                                                                       pk(~sk_voter.1),
                                                                       h(<
                                                                          <
                                                                           'BBEntry_Ballot_Submission',
                                                                           ~ec, %ts.2,
                                                                           <'VA_Submit_Ballot',
                                                                            ~ec, pseudonym($V.1),
                                                                            pk(~sk_voter.1),
                                                                            ~bs_unused.1,
                                                                            ny_encrypt_c1(~ballot.1,
                                                                                          pk(~sk_election),
                                                                                          ~r.1),
                                                                            ny_encrypt_c2(~ballot.1,
                                                                                          pk(~sk_election),
                                                                                          ~r.1),
                                                                            ny_encrypt_p(~ballot.1,
                                                                                         pk(~sk_election),
                                                                                         ~r.1)
                                                                           >,
                                                                           sign(<
                                                                                 'VA_Submit_Ballot',
                                                                                 ~ec,
                                                                                 pseudonym($V.1),
                                                                                 pk(~sk_voter.1),
                                                                                 ~bs_unused.1,
                                                                                 ny_encrypt_c1(~ballot.1,
                                                                                               pk(~sk_election),
                                                                                               ~r.1),
                                                                                 ny_encrypt_c2(~ballot.1,
                                                                                               pk(~sk_election),
                                                                                               ~r.1),
                                                                                 ny_encrypt_p(~ballot.1,
                                                                                              pk(~sk_election),
                                                                                              ~r.1)
                                                                                >,
                                                                                '1', ~sk_voter.1)
                                                                          >,
                                                                          h(<p, ch.1>)>)
                                                                      >,
                                                                      '1', ~sk_voter.1)
                                                                >,
                                                                (%idx.2%+%1%+%1)
                                             )[+] ▶₂ #vr.9 )
                                        case BallotCast_DBB_AppendCastBallot
                                        simplify
                                        solve( BB_Append_Request( ~bbid,
                                                                  <'BBEntry_Ballot_Submission',
                                                                   ~ec, %ts,
                                                                   <'VA_Submit_Ballot', ~ec,
                                                                    pseudonym($V), pk(~sk_voter),
                                                                    ~bs_unused,
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
                                                                   sign(<'VA_Submit_Ballot', ~ec,
                                                                         pseudonym($V),
                                                                         pk(~sk_voter), ~bs_unused,
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
                                                                  %1
                                               )[+] ▶₂ #vr.10 )
                                          case Mock_AppendSubmittedBallot
                                          solve( BB_Append_Request( ~bbid,
                                                                    <'BBEntry_Ballot_Submission',
                                                                     ~ec, %ts.2,
                                                                     <'VA_Submit_Ballot', ~ec,
                                                                      pseudonym($V.1),
                                                                      pk(~sk_voter.1),
                                                                      ~bs_unused.1,
                                                                      ny_encrypt_c1(~ballot.1,
                                                                                    pk(~sk_election),
                                                                                    ~r.1),
                                                                      ny_encrypt_c2(~ballot.1,
                                                                                    pk(~sk_election),
                                                                                    ~r.1),
                                                                      ny_encrypt_p(~ballot.1,
                                                                                   pk(~sk_election),
                                                                                   ~r.1)
                                                                     >,
                                                                     sign(<'VA_Submit_Ballot', ~ec,
                                                                           pseudonym($V.1),
                                                                           pk(~sk_voter.1),
                                                                           ~bs_unused.1,
                                                                           ny_encrypt_c1(~ballot.1,
                                                                                         pk(~sk_election),
                                                                                         ~r.1),
                                                                           ny_encrypt_c2(~ballot.1,
                                                                                         pk(~sk_election),
                                                                                         ~r.1),
                                                                           ny_encrypt_p(~ballot.1,
                                                                                        pk(~sk_election),
                                                                                        ~r.1)
                                                                          >,
                                                                          '1', ~sk_voter.1)
                                                                    >,
                                                                    (%idx.1%+%1)
                                                 )[+] ▶₂ #vr.11 )
                                            case Mock_AppendSubmittedBallot
                                            solve( BB_Append_Request( ~bbid,
                                                                      <
                                                                       'BBEntry_Voter_Authorization',
                                                                       ~ec, %ts.1,
                                                                       <'EAS_Authorize_Voter', ~ec,
                                                                        pseudonym($V),
                                                                        pk(~sk_voter), ~bs_unused>,
                                                                       sign(<'EAS_Authorize_Voter',
                                                                             ~ec, pseudonym($V),
                                                                             pk(~sk_voter),
                                                                             ~bs_unused>,
                                                                            '1', ~sk_eas)
                                                                      >,
                                                                      (%idx%+%1)
                                                   )[+] ▶₂ #j.1 )
                                              case BallotCast_DBB_AppendCastBallot
                                              simplify
                                              solve( BB_Trace_Entry( ~bbid,
                                                                     <'BBEntry_Ballot_Submission',
                                                                      ~ec, %ts_sub,
                                                                      <'VA_Submit_Ballot', ~ec,
                                                                       pseudonym($V),
                                                                       pk(~sk_voter), ~bs_unused,
                                                                       cryptograms>,
                                                                      sig_submit>,
                                                                     h(<
                                                                        <
                                                                         'BBEntry_Ballot_Submission',
                                                                         ~ec, %ts_sub,
                                                                         <'VA_Submit_Ballot', ~ec,
                                                                          pseudonym($V),
                                                                          pk(~sk_voter),
                                                                          ~bs_unused, cryptograms>,
                                                                         sig_submit>,
                                                                        ch.3>),
                                                                     (%idx.3%+%1)
                                                     ) @ #vr.40 )
                                                case BulletinBoard_Append
                                                solve( BB_Append_Request( ~bbid,
                                                                          <
                                                                           'BBEntry_Voter_Authorization',
                                                                           ~ec, %ts.3,
                                                                           <'EAS_Authorize_Voter',
                                                                            ~ec, pseudonym($V.1),
                                                                            pk(~sk_voter.1),
                                                                            ~bs_unused.1>,
                                                                           sign(<
                                                                                 'EAS_Authorize_Voter',
                                                                                 ~ec,
                                                                                 pseudonym($V.1),
                                                                                 pk(~sk_voter.1),
                                                                                 ~bs_unused.1>,
                                                                                '1', ~sk_eas)
                                                                          >,
                                                                          (%idx.2%+%1)
                                                       )[+] ▶₂ #j.2 )
                                                  case BallotCast_DBB_AppendCastBallot
                                                  simplify
                                                  solve( BB_Trace_Entry( ~bbid,
                                                                         <
                                                                          'BBEntry_Ballot_Submission',
                                                                          ~ec, %ts_sub.1,
                                                                          <'VA_Submit_Ballot', ~ec,
                                                                           pseudonym($V.1),
                                                                           pk(~sk_voter.1),
                                                                           ~bs_unused.1,
                                                                           cryptograms.1>,
                                                                          sig_submit.1>,
                                                                         h(<
                                                                            <
                                                                             'BBEntry_Ballot_Submission',
                                                                             ~ec, %ts_sub.1,
                                                                             <'VA_Submit_Ballot',
                                                                              ~ec, pseudonym($V.1),
                                                                              pk(~sk_voter.1),
                                                                              ~bs_unused.1,
                                                                              cryptograms.1>,
                                                                             sig_submit.1>,
                                                                            ch.4>),
                                                                         (%idx.4%+%1)
                                                         ) @ #vr.43 )
                                                    case BulletinBoard_Append
                                                    solve( BB_Append_Request( ~bbid,
                                                                              <
                                                                               'BBEntry_Ballot_Submission',
                                                                               ~ec, %ts_sub,
                                                                               <'VA_Submit_Ballot',
                                                                                ~ec, pseudonym($V),
                                                                                pk(~sk_voter),
                                                                                ~bs_unused,
                                                                                cryptograms>,
                                                                               sig_submit>,
                                                                              %idx.3
                                                           )[+] ▶₂ #vr.40 )
                                                      case Mock_AppendSubmittedBallot_case_1
                                                      simplify
                                                      solve( BB_Append_Request( ~bbid,
                                                                                <
                                                                                 'BBEntry_Ballot_Submission',
                                                                                 ~ec, %ts_sub,
                                                                                 <
                                                                                  'VA_Submit_Ballot',
                                                                                  ~ec,
                                                                                  pseudonym($V.1),
                                                                                  pk(~sk_voter.1),
                                                                                  ~bs_unused.1,
                                                                                  cryptograms>,
                                                                                 sig_submit>,
                                                                                %idx.3
                                                             )[+] ▶₂ #vr.42 )
                                                        case Mock_AppendSubmittedBallot
                                                        simplify
                                                        solve( SecureReceive( ~cid, ~va_id,
                                                                              <~ec, 'DBB'>,
                                                                              <
                                                                               <'VA_Cast_Ballot',
                                                                                ~ec, pseudonym($V),
                                                                                pk(~sk_voter),
                                                                                h(<
                                                                                   <
                                                                                    'BBEntry_Ballot_Submission',
                                                                                    ~ec, %ts,
                                                                                    <
                                                                                     'VA_Submit_Ballot',
                                                                                     ~ec,
                                                                                     pseudonym($V),
                                                                                     pk(~sk_voter),
                                                                                     ~bs_unused,
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
                                                                                    sign(<
                                                                                          'VA_Submit_Ballot',
                                                                                          ~ec,
                                                                                          pseudonym($V),
                                                                                          pk(~sk_voter),
                                                                                          ~bs_unused,
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
                                                                                         '1',
                                                                                         ~sk_voter)
                                                                                   >,
                                                                                   h(<~ec, ~bbid>)>)
                                                                               >,
                                                                               sign(<
                                                                                     'VA_Cast_Ballot',
                                                                                     ~ec,
                                                                                     pseudonym($V),
                                                                                     pk(~sk_voter),
                                                                                     h(<
                                                                                        <
                                                                                         'BBEntry_Ballot_Submission',
                                                                                         ~ec, %ts,
                                                                                         <
                                                                                          'VA_Submit_Ballot',
                                                                                          ~ec,
                                                                                          pseudonym($V),
                                                                                          pk(~sk_voter),
                                                                                          ~bs_unused,
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
                                                                                         sign(<
                                                                                               'VA_Submit_Ballot',
                                                                                               ~ec,
                                                                                               pseudonym($V),
                                                                                               pk(~sk_voter),
                                                                                               ~bs_unused,
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
                                                                                              '1',
                                                                                              ~sk_voter)
                                                                                        >,
                                                                                        h(<~ec,
                                                                                           ~bbid>)
                                                                                       >)
                                                                                    >,
                                                                                    '1', ~sk_voter)
                                                                              >
                                                               ) ▶₃ #vr.30 )
                                                          case SecureChannel_Receive_case_1
                                                          solve( SecureReceive( ~cid.1, ~va_id.1,
                                                                                <~ec, 'DBB'>,
                                                                                <
                                                                                 <'VA_Cast_Ballot',
                                                                                  ~ec,
                                                                                  pseudonym($V.1),
                                                                                  pk(~sk_voter.1),
                                                                                  h(<
                                                                                     <
                                                                                      'BBEntry_Ballot_Submission',
                                                                                      ~ec, %ts.2,
                                                                                      <
                                                                                       'VA_Submit_Ballot',
                                                                                       ~ec,
                                                                                       pseudonym($V.1),
                                                                                       pk(~sk_voter.1),
                                                                                       ~bs_unused.1,
                                                                                       ny_encrypt_c1(~ballot.1,
                                                                                                     pk(~sk_election),
                                                                                                     ~r.1),
                                                                                       ny_encrypt_c2(~ballot.1,
                                                                                                     pk(~sk_election),
                                                                                                     ~r.1),
                                                                                       ny_encrypt_p(~ballot.1,
                                                                                                    pk(~sk_election),
                                                                                                    ~r.1)
                                                                                      >,
                                                                                      sign(<
                                                                                            'VA_Submit_Ballot',
                                                                                            ~ec,
                                                                                            pseudonym($V.1),
                                                                                            pk(~sk_voter.1),
                                                                                            ~bs_unused.1,
                                                                                            ny_encrypt_c1(~ballot.1,
                                                                                                          pk(~sk_election),
                                                                                                          ~r.1),
                                                                                            ny_encrypt_c2(~ballot.1,
                                                                                                          pk(~sk_election),
                                                                                                          ~r.1),
                                                                                            ny_encrypt_p(~ballot.1,
                                                                                                         pk(~sk_election),
                                                                                                         ~r.1)
                                                                                           >,
                                                                                           '1',
                                                                                           ~sk_voter.1)
                                                                                     >,
                                                                                     h(<p, ch.1>)>)
                                                                                 >,
                                                                                 sign(<
                                                                                       'VA_Cast_Ballot',
                                                                                       ~ec,
                                                                                       pseudonym($V.1),
                                                                                       pk(~sk_voter.1),
                                                                                       h(<
                                                                                          <
                                                                                           'BBEntry_Ballot_Submission',
                                                                                           ~ec,
                                                                                           %ts.2,
                                                                                           <
                                                                                            'VA_Submit_Ballot',
                                                                                            ~ec,
                                                                                            pseudonym($V.1),
                                                                                            pk(~sk_voter.1),
                                                                                            ~bs_unused.1,
                                                                                            ny_encrypt_c1(~ballot.1,
                                                                                                          pk(~sk_election),
                                                                                                          ~r.1),
                                                                                            ny_encrypt_c2(~ballot.1,
                                                                                                          pk(~sk_election),
                                                                                                          ~r.1),
                                                                                            ny_encrypt_p(~ballot.1,
                                                                                                         pk(~sk_election),
                                                                                                         ~r.1)
                                                                                           >,
                                                                                           sign(<
                                                                                                 'VA_Submit_Ballot',
                                                                                                 ~ec,
                                                                                                 pseudonym($V.1),
                                                                                                 pk(~sk_voter.1),
                                                                                                 ~bs_unused.1,
                                                                                                 ny_encrypt_c1(~ballot.1,
                                                                                                               pk(~sk_election),
                                                                                                               ~r.1),
                                                                                                 ny_encrypt_c2(~ballot.1,
                                                                                                               pk(~sk_election),
                                                                                                               ~r.1),
                                                                                                 ny_encrypt_p(~ballot.1,
                                                                                                              pk(~sk_election),
                                                                                                              ~r.1)
                                                                                                >,
                                                                                                '1',
                                                                                                ~sk_voter.1)
                                                                                          >,
                                                                                          h(<p, ch.1
                                                                                            >)
                                                                                         >)
                                                                                      >,
                                                                                      '1',
                                                                                      ~sk_voter.1)
                                                                                >
                                                                 ) ▶₃ #vr.36 )
                                                            case SecureChannel_Receive_case_1
                                                            simplify
                                                            solve( SecureReceive( ~cid.5, ~va_id.3,
                                                                                  <~ec, 'DBB'>,
                                                                                  <
                                                                                   <
                                                                                    'VA_Cast_Ballot',
                                                                                    ~ec,
                                                                                    pseudonym($V),
                                                                                    pk(~sk_voter),
                                                                                    h(<
                                                                                       <
                                                                                        'BBEntry_Ballot_Submission',
                                                                                        ~ec, %ts,
                                                                                        <
                                                                                         'VA_Submit_Ballot',
                                                                                         ~ec,
                                                                                         pseudonym($V),
                                                                                         pk(~sk_voter),
                                                                                         ~bs_unused,
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
                                                                                        sign(<
                                                                                              'VA_Submit_Ballot',
                                                                                              ~ec,
                                                                                              pseudonym($V),
                                                                                              pk(~sk_voter),
                                                                                              ~bs_unused,
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
                                                                                             '1',
                                                                                             ~sk_voter)
                                                                                       >,
                                                                                       h(<~ec, ~bbid
                                                                                         >)
                                                                                      >)
                                                                                   >,
                                                                                   sign(<
                                                                                         'VA_Cast_Ballot',
                                                                                         ~ec,
                                                                                         pseudonym($V),
                                                                                         pk(~sk_voter),
                                                                                         h(<
                                                                                            <
                                                                                             'BBEntry_Ballot_Submission',
                                                                                             ~ec,
                                                                                             %ts,
                                                                                             <
                                                                                              'VA_Submit_Ballot',
                                                                                              ~ec,
                                                                                              pseudonym($V),
                                                                                              pk(~sk_voter),
                                                                                              ~bs_unused,
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
                                                                                             sign(<
                                                                                                   'VA_Submit_Ballot',
                                                                                                   ~ec,
                                                                                                   pseudonym($V),
                                                                                                   pk(~sk_voter),
                                                                                                   ~bs_unused,
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
                                                                                                  '1',
                                                                                                  ~sk_voter)
                                                                                            >,
                                                                                            h(<~ec,
                                                                                               ~bbid
                                                                                              >)
                                                                                           >)
                                                                                        >,
                                                                                        x,
                                                                                        ~sk_voter)
                                                                                  >
                                                                   ) ▶₃ #vr.39 )
                                                              case SecureChannel_Receive_case_1
                                                              solve( SecureReceive( ~cid.5,
                                                                                    ~va_id.3,
                                                                                    <~ec, 'DBB'>,
                                                                                    <
                                                                                     <
                                                                                      'VA_Cast_Ballot',
                                                                                      ~ec,
                                                                                      pseudonym($V.1),
                                                                                      pk(~sk_voter.1),
                                                                                      h(<
                                                                                         <
                                                                                          'BBEntry_Ballot_Submission',
                                                                                          ~ec,
                                                                                          %ts_sub,
                                                                                          <
                                                                                           'VA_Submit_Ballot',
                                                                                           ~ec,
                                                                                           pseudonym($V.1),
                                                                                           pk(~sk_voter.1),
                                                                                           ~bs_unused.1,
                                                                                           ny_encrypt_c1(~ballot.2,
                                                                                                         pk(~sk_election),
                                                                                                         ~r.2),
                                                                                           ny_encrypt_c2(~ballot.2,
                                                                                                         pk(~sk_election),
                                                                                                         ~r.2),
                                                                                           ny_encrypt_p(~ballot.2,
                                                                                                        pk(~sk_election),
                                                                                                        ~r.2)
                                                                                          >,
                                                                                          sign(<
                                                                                                'VA_Submit_Ballot',
                                                                                                ~ec,
                                                                                                pseudonym($V.1),
                                                                                                pk(~sk_voter.1),
                                                                                                ~bs_unused.1,
                                                                                                ny_encrypt_c1(~ballot.2,
                                                                                                              pk(~sk_election),
                                                                                                              ~r.2),
                                                                                                ny_encrypt_c2(~ballot.2,
                                                                                                              pk(~sk_election),
                                                                                                              ~r.2),
                                                                                                ny_encrypt_p(~ballot.2,
                                                                                                             pk(~sk_election),
                                                                                                             ~r.2)
                                                                                               >,
                                                                                               '1',
                                                                                               ~sk_voter.2)
                                                                                         >,
                                                                                         h(<p.1,
                                                                                            ch.3>)
                                                                                        >)
                                                                                     >,
                                                                                     sign(<
                                                                                           'VA_Cast_Ballot',
                                                                                           ~ec,
                                                                                           pseudonym($V.1),
                                                                                           pk(~sk_voter.1),
                                                                                           h(<
                                                                                              <
                                                                                               'BBEntry_Ballot_Submission',
                                                                                               ~ec,
                                                                                               %ts_sub,
                                                                                               <
                                                                                                'VA_Submit_Ballot',
                                                                                                ~ec,
                                                                                                pseudonym($V.1),
                                                                                                pk(~sk_voter.1),
                                                                                                ~bs_unused.1,
                                                                                                ny_encrypt_c1(~ballot.2,
                                                                                                              pk(~sk_election),
                                                                                                              ~r.2),
                                                                                                ny_encrypt_c2(~ballot.2,
                                                                                                              pk(~sk_election),
                                                                                                              ~r.2),
                                                                                                ny_encrypt_p(~ballot.2,
                                                                                                             pk(~sk_election),
                                                                                                             ~r.2)
                                                                                               >,
                                                                                               sign(<
                                                                                                     'VA_Submit_Ballot',
                                                                                                     ~ec,
                                                                                                     pseudonym($V.1),
                                                                                                     pk(~sk_voter.1),
                                                                                                     ~bs_unused.1,
                                                                                                     ny_encrypt_c1(~ballot.2,
                                                                                                                   pk(~sk_election),
                                                                                                                   ~r.2),
                                                                                                     ny_encrypt_c2(~ballot.2,
                                                                                                                   pk(~sk_election),
                                                                                                                   ~r.2),
                                                                                                     ny_encrypt_p(~ballot.2,
                                                                                                                  pk(~sk_election),
                                                                                                                  ~r.2)
                                                                                                    >,
                                                                                                    '1',
                                                                                                    ~sk_voter.2)
                                                                                              >,
                                                                                              h(<
                                                                                                 p.1,
                                                                                                 ch.3
                                                                                                >)
                                                                                             >)
                                                                                          >,
                                                                                          x,
                                                                                          ~sk_voter.1)
                                                                                    >
                                                                     ) ▶₃ #vr.39 )
                                                                case SecureChannel_Receive_case_1
                                                                simplify
                                                                solve( DBB_Clock( %ts_sub
                                                                       ) ▶₂ #vr.41 )
                                                                  case BallotCast_DBB_AppendCastBallot_case_1
                                                                  by sorry
                                                                next
                                                                  case BallotCast_DBB_AppendCastBallot_case_2
                                                                  by sorry
                                                                next
                                                                  case Mock_AppendSubmittedBallot_case_1
                                                                  simplify
                                                                  by sorry
                                                                next
                                                                  case Mock_AppendSubmittedBallot_case_2
                                                                  simplify
                                                                  by sorry
                                                                next
                                                                  case Mock_DBBTimestamp
                                                                  solve( %idx.3 ⊏ (%idx.2%+%1%+%1%+
                                                                                   %1%+%1) )
                                                                    case SubtermSplit1_case_01
                                                                    simplify
                                                                    solve( %idx.1 ⊏ (%1%+%1%+%1%+%1
                                                                                    ) )
                                                                      case SubtermSplit1_case_1
                                                                      simplify
                                                                      solve( BB_Current( ~bbid, c.3,
                                                                                         h(<
                                                                                            <
                                                                                             'BBEntry_Ballot_Submission',
                                                                                             ~ec,
                                                                                             %ts,
                                                                                             <
                                                                                              'VA_Submit_Ballot',
                                                                                              ~ec,
                                                                                              pseudonym($V),
                                                                                              pk(~sk_voter),
                                                                                              ~bs_unused,
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
                                                                                             sign(<
                                                                                                   'VA_Submit_Ballot',
                                                                                                   ~ec,
                                                                                                   pseudonym($V),
                                                                                                   pk(~sk_voter),
                                                                                                   ~bs_unused,
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
                                                                                                  '1',
                                                                                                  ~sk_voter)
                                                                                            >,
                                                                                            h(<~ec,
                                                                                               ~bbid
                                                                                              >)
                                                                                           >),
                                                                                         (%1%+%1)
                                                                             )[+] ▶₁ #vr.10 )
                                                                        case BulletinBoard_Append
                                                                        solve( BB_Current( ~bbid, c,
                                                                                           h(<~ec,
                                                                                              ~bbid
                                                                                             >),
                                                                                           %1
                                                                               )[+] ▶₁ #j )
                                                                          case BulletinBoard_Create
                                                                          solve( DBB_Clock( %ts
                                                                                 ) ▶₂ #vr.14 )
                                                                            case BallotCast_DBB_AppendCastBallot_case_1
                                                                            by sorry
                                                                          next
                                                                            case BallotCast_DBB_AppendCastBallot_case_2
                                                                            by sorry
                                                                          next
                                                                            case Mock_AppendSubmittedBallot_case_1
                                                                            simplify
                                                                            by sorry
                                                                          next
                                                                            case Mock_AppendSubmittedBallot_case_2
                                                                            simplify
                                                                            by sorry
                                                                          next
                                                                            case Mock_DBBTimestamp
                                                                            solve( BB_Trace_Entry( ~bbid,
                                                                                                   ~ec,
                                                                                                   h(<
                                                                                                      ~ec,
                                                                                                      ~bbid
                                                                                                     >),
                                                                                                   %1
                                                                                   ) @ #vr.1 )
                                                                              case BulletinBoard_Create
                                                                              solve( BallotStyleCount( ~ec,
                                                                                                       %unused
                                                                                     ) ▶₀ #vr.7 )
                                                                                case Mock_BallotStyle
                                                                                by sorry
                                                                              next
                                                                                case Mock_EC_And_Initial_Counters
                                                                                solve( BallotStyleCount( ~ec,
                                                                                                         %idx_bs_unused
                                                                                       ) ▶₀ #vr.3 )
                                                                                  case Mock_BallotStyle
                                                                                  solve( VoterCount( ~ec,
                                                                                                     %idx_ev_unused
                                                                                         ) ▶₀ #vr.4 )
                                                                                    case Mock_EC_And_Initial_Counters
                                                                                    solve( BallotStyleCount( ~ec,
                                                                                                             %unused
                                                                                           ) ▶₀ #vr.8 )
                                                                                      case Mock_BallotStyle
                                                                                      simplify
                                                                                      solve( DBB_Clock( %ts
                                                                                             ) ▶₂ #vr.28 )
                                                                                        case BallotCast_DBB_AppendCastBallot_case_1
                                                                                        by sorry
                                                                                      next
                                                                                        case BallotCast_DBB_AppendCastBallot_case_2
                                                                                        by sorry
                                                                                      next
                                                                                        case Mock_AppendSubmittedBallot_case_1
                                                                                        simplify
                                                                                        by sorry
                                                                                      next
                                                                                        case Mock_AppendSubmittedBallot_case_2
                                                                                        simplify
                                                                                        by sorry
                                                                                      next
                                                                                        case Mock_DBBTimestamp
                                                                                        solve( DBB_Clock( %ts
                                                                                               ) ▶₂ #vr.34 )
                                                                                          case BallotCast_DBB_AppendCastBallot_case_1
                                                                                          by sorry
                                                                                        next
                                                                                          case BallotCast_DBB_AppendCastBallot_case_2
                                                                                          by sorry
                                                                                        next
                                                                                          case Mock_AppendSubmittedBallot_case_1
                                                                                          simplify
                                                                                          by sorry
                                                                                        next
                                                                                          case Mock_AppendSubmittedBallot_case_2
                                                                                          simplify
                                                                                          by sorry
                                                                                        next
                                                                                          case Mock_DBBTimestamp
                                                                                          solve( BallotStyleCount( ~ec,
                                                                                                                   %idx_bs
                                                                                                 ) ▶₀ #vr.16 )
                                                                                            case Mock_BallotStyle
                                                                                            by sorry
                                                                                          next
                                                                                            case Mock_EC_And_Initial_Counters
                                                                                            solve( BallotStyleCount( ~ec,
                                                                                                                     %idx_bs
                                                                                                   ) ▶₀ #vr.22 )
                                                                                              case Mock_BallotStyle
                                                                                              by sorry
                                                                                            next
                                                                                              case Mock_EC_And_Initial_Counters
                                                                                              solve( VoterCount( ~ec,
                                                                                                                 %idx_ev
                                                                                                     ) ▶₀ #vr.16 )
                                                                                                case Mock_EC_And_Initial_Counters
                                                                                                by sorry
                                                                                              next
                                                                                                case Mock_VoterRegistration_Eligible
                                                                                                solve( DBB_State_ReceiveAuthorizeVoter( ~ec,
                                                                                                                                        (
                                                                                                                                         %idx%+
                                                                                                                                         %1
                                                                                                                                        )
                                                                                                       ) ▶₀ #vr.13 )
                                                                                                  case Mock_Voter_Authentication
                                                                                                  solve( DBB_State_ReceiveAuthorizeVoter( ~ec,
                                                                                                                                          %idx
                                                                                                         ) ▶₀ #vr.48 )
                                                                                                    case Mock_Voter_Authentication
                                                                                                    simplify
                                                                                                    solve( DBB_State_ReceiveAuthorizeVoter( ~ec,
                                                                                                                                            (
                                                                                                                                             %idx%+
                                                                                                                                             %1
                                                                                                                                            )
                                                                                                           ) ▶₀ #vr.19 )
                                                                                                      case Mock_Voter_Authentication
                                                                                                      solve( (¬((
                                                                                                                 %i%+
                                                                                                                 %1%+
                                                                                                                 %1%+
                                                                                                                 %1
                                                                                                                ) ⊏
                                                                                                                (
                                                                                                                 %idx%+
                                                                                                                 %1%+
                                                                                                                 %1
                                                                                                                )))  ∥
                                                                                                             (#j.1 < #j.2) )
                                                                                                        case case_1
                                                                                                        solve( (¬((
                                                                                                                   %i%+
                                                                                                                   %1%+
                                                                                                                   %1%+
                                                                                                                   %1
                                                                                                                  ) ⊏
                                                                                                                  (
                                                                                                                   %idx%+
                                                                                                                   %1%+
                                                                                                                   %1%+
                                                                                                                   %1
                                                                                                                  )))  ∥
                                                                                                               (#j.1 < #vr.9) )
                                                                                                          case case_1
                                                                                                          solve( (¬((
                                                                                                                     %idx%+
                                                                                                                     %1%+
                                                                                                                     %1
                                                                                                                    ) ⊏
                                                                                                                    (
                                                                                                                     %i%+
                                                                                                                     %1%+
                                                                                                                     %1%+
                                                                                                                     %1
                                                                                                                    )))  ∥
                                                                                                                 (#j.2 < #j.1) )
                                                                                                            case case_1
                                                                                                            simplify
                                                                                                            by contradiction
                                                                                                               /*
                                                                                                               cyclic
                                                                                                               */
                                                                                                          next
                                                                                                            case case_2
                                                                                                            solve( %idx ⊏ (
                                                                                                                           %i%+
                                                                                                                           %1
                                                                                                                          ) )
                                                                                                              case SubtermSplit1_case_1
                                                                                                              simplify
                                                                                                              solve( (¬((
                                                                                                                         %idx%+
                                                                                                                         %1%+
                                                                                                                         %1
                                                                                                                        ) ⊏
                                                                                                                        (
                                                                                                                         %idx%+
                                                                                                                         %x%+
                                                                                                                         %1
                                                                                                                        )))  ∥
                                                                                                                     (#j.2 < #j.3) )
                                                                                                                case case_1
                                                                                                                solve( BB_Trace_Entry( ~bbid,
                                                                                                                                       <
                                                                                                                                        'BBEntry_Ballot_Cast',
                                                                                                                                        (
                                                                                                                                         %1%+
                                                                                                                                         %1
                                                                                                                                        ),
                                                                                                                                        <
                                                                                                                                         <
                                                                                                                                          'VA_Submit_Ballot',
                                                                                                                                          ~ec,
                                                                                                                                          pseudonym($V.1),
                                                                                                                                          pk(~sk_voter.1),
                                                                                                                                          ~bs_unused,
                                                                                                                                          ny_encrypt_c1(~ballot.1,
                                                                                                                                                        pk(~sk_election),
                                                                                                                                                        ~r.1),
                                                                                                                                          ny_encrypt_c2(~ballot.1,
                                                                                                                                                        pk(~sk_election),
                                                                                                                                                        ~r.1),
                                                                                                                                          ny_encrypt_p(~ballot.1,
                                                                                                                                                       pk(~sk_election),
                                                                                                                                                       ~r.1)
                                                                                                                                         >,
                                                                                                                                         sign(<
                                                                                                                                               'VA_Submit_Ballot',
                                                                                                                                               ~ec,
                                                                                                                                               pseudonym($V.1),
                                                                                                                                               pk(~sk_voter.1),
                                                                                                                                               ~bs_unused,
                                                                                                                                               ny_encrypt_c1(~ballot.1,
                                                                                                                                                             pk(~sk_election),
                                                                                                                                                             ~r.1),
                                                                                                                                               ny_encrypt_c2(~ballot.1,
                                                                                                                                                             pk(~sk_election),
                                                                                                                                                             ~r.1),
                                                                                                                                               ny_encrypt_p(~ballot.1,
                                                                                                                                                            pk(~sk_election),
                                                                                                                                                            ~r.1)
                                                                                                                                              >,
                                                                                                                                              '1',
                                                                                                                                              ~sk_voter.1)
                                                                                                                                        >,
                                                                                                                                        <
                                                                                                                                         'VA_Cast_Ballot',
                                                                                                                                         ~ec,
                                                                                                                                         pseudonym($V.1),
                                                                                                                                         pk(~sk_voter.1),
                                                                                                                                         h(<
                                                                                                                                            <
                                                                                                                                             'BBEntry_Ballot_Submission',
                                                                                                                                             ~ec,
                                                                                                                                             %1,
                                                                                                                                             <
                                                                                                                                              'VA_Submit_Ballot',
                                                                                                                                              ~ec,
                                                                                                                                              pseudonym($V.1),
                                                                                                                                              pk(~sk_voter.1),
                                                                                                                                              ~bs_unused,
                                                                                                                                              ny_encrypt_c1(~ballot.1,
                                                                                                                                                            pk(~sk_election),
                                                                                                                                                            ~r.1),
                                                                                                                                              ny_encrypt_c2(~ballot.1,
                                                                                                                                                            pk(~sk_election),
                                                                                                                                                            ~r.1),
                                                                                                                                              ny_encrypt_p(~ballot.1,
                                                                                                                                                           pk(~sk_election),
                                                                                                                                                           ~r.1)
                                                                                                                                             >,
                                                                                                                                             sign(<
                                                                                                                                                   'VA_Submit_Ballot',
                                                                                                                                                   ~ec,
                                                                                                                                                   pseudonym($V.1),
                                                                                                                                                   pk(~sk_voter.1),
                                                                                                                                                   ~bs_unused,
                                                                                                                                                   ny_encrypt_c1(~ballot.1,
                                                                                                                                                                 pk(~sk_election),
                                                                                                                                                                 ~r.1),
                                                                                                                                                   ny_encrypt_c2(~ballot.1,
                                                                                                                                                                 pk(~sk_election),
                                                                                                                                                                 ~r.1),
                                                                                                                                                   ny_encrypt_p(~ballot.1,
                                                                                                                                                                pk(~sk_election),
                                                                                                                                                                ~r.1)
                                                                                                                                                  >,
                                                                                                                                                  '1',
                                                                                                                                                  ~sk_voter.1)
                                                                                                                                            >,
                                                                                                                                            h(<
                                                                                                                                               <
                                                                                                                                                'BBEntry_Ballot_Submission',
                                                                                                                                                ~ec,
                                                                                                                                                %1,
                                                                                                                                                <
                                                                                                                                                 'VA_Submit_Ballot',
                                                                                                                                                 ~ec,
                                                                                                                                                 pseudonym($V),
                                                                                                                                                 pk(~sk_voter),
                                                                                                                                                 ~bs_unused,
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
                                                                                                                                                sign(<
                                                                                                                                                      'VA_Submit_Ballot',
                                                                                                                                                      ~ec,
                                                                                                                                                      pseudonym($V),
                                                                                                                                                      pk(~sk_voter),
                                                                                                                                                      ~bs_unused,
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
                                                                                                                                                     '1',
                                                                                                                                                     ~sk_voter)
                                                                                                                                               >,
                                                                                                                                               h(<
                                                                                                                                                  ~ec,
                                                                                                                                                  ~bbid
                                                                                                                                                 >)
                                                                                                                                              >)
                                                                                                                                           >)
                                                                                                                                        >,
                                                                                                                                        sign(<
                                                                                                                                              'VA_Cast_Ballot',
                                                                                                                                              ~ec,
                                                                                                                                              pseudonym($V.1),
                                                                                                                                              pk(~sk_voter.1),
                                                                                                                                              h(<
                                                                                                                                                 <
                                                                                                                                                  'BBEntry_Ballot_Submission',
                                                                                                                                                  ~ec,
                                                                                                                                                  %1,
                                                                                                                                                  <
                                                                                                                                                   'VA_Submit_Ballot',
                                                                                                                                                   ~ec,
                                                                                                                                                   pseudonym($V.1),
                                                                                                                                                   pk(~sk_voter.1),
                                                                                                                                                   ~bs_unused,
                                                                                                                                                   ny_encrypt_c1(~ballot.1,
                                                                                                                                                                 pk(~sk_election),
                                                                                                                                                                 ~r.1),
                                                                                                                                                   ny_encrypt_c2(~ballot.1,
                                                                                                                                                                 pk(~sk_election),
                                                                                                                                                                 ~r.1),
                                                                                                                                                   ny_encrypt_p(~ballot.1,
                                                                                                                                                                pk(~sk_election),
                                                                                                                                                                ~r.1)
                                                                                                                                                  >,
                                                                                                                                                  sign(<
                                                                                                                                                        'VA_Submit_Ballot',
                                                                                                                                                        ~ec,
                                                                                                                                                        pseudonym($V.1),
                                                                                                                                                        pk(~sk_voter.1),
                                                                                                                                                        ~bs_unused,
                                                                                                                                                        ny_encrypt_c1(~ballot.1,
                                                                                                                                                                      pk(~sk_election),
                                                                                                                                                                      ~r.1),
                                                                                                                                                        ny_encrypt_c2(~ballot.1,
                                                                                                                                                                      pk(~sk_election),
                                                                                                                                                                      ~r.1),
                                                                                                                                                        ny_encrypt_p(~ballot.1,
                                                                                                                                                                     pk(~sk_election),
                                                                                                                                                                     ~r.1)
                                                                                                                                                       >,
                                                                                                                                                       '1',
                                                                                                                                                       ~sk_voter.1)
                                                                                                                                                 >,
                                                                                                                                                 h(<
                                                                                                                                                    <
                                                                                                                                                     'BBEntry_Ballot_Submission',
                                                                                                                                                     ~ec,
                                                                                                                                                     %1,
                                                                                                                                                     <
                                                                                                                                                      'VA_Submit_Ballot',
                                                                                                                                                      ~ec,
                                                                                                                                                      pseudonym($V),
                                                                                                                                                      pk(~sk_voter),
                                                                                                                                                      ~bs_unused,
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
                                                                                                                                                     sign(<
                                                                                                                                                           'VA_Submit_Ballot',
                                                                                                                                                           ~ec,
                                                                                                                                                           pseudonym($V),
                                                                                                                                                           pk(~sk_voter),
                                                                                                                                                           ~bs_unused,
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
                                                                                                                                                          '1',
                                                                                                                                                          ~sk_voter)
                                                                                                                                                    >,
                                                                                                                                                    h(<
                                                                                                                                                       ~ec,
                                                                                                                                                       ~bbid
                                                                                                                                                      >)
                                                                                                                                                   >)
                                                                                                                                                >)
                                                                                                                                             >,
                                                                                                                                             '1',
                                                                                                                                             ~sk_voter.1)
                                                                                                                                       >,
                                                                                                                                       h(<
                                                                                                                                          <
                                                                                                                                           'BBEntry_Ballot_Cast',
                                                                                                                                           (
                                                                                                                                            %1%+
                                                                                                                                            %1
                                                                                                                                           ),
                                                                                                                                           <
                                                                                                                                            <
                                                                                                                                             'VA_Submit_Ballot',
                                                                                                                                             ~ec,
                                                                                                                                             pseudonym($V.1),
                                                                                                                                             pk(~sk_voter.1),
                                                                                                                                             ~bs_unused,
                                                                                                                                             ny_encrypt_c1(~ballot.1,
                                                                                                                                                           pk(~sk_election),
                                                                                                                                                           ~r.1),
                                                                                                                                             ny_encrypt_c2(~ballot.1,
                                                                                                                                                           pk(~sk_election),
                                                                                                                                                           ~r.1),
                                                                                                                                             ny_encrypt_p(~ballot.1,
                                                                                                                                                          pk(~sk_election),
                                                                                                                                                          ~r.1)
                                                                                                                                            >,
                                                                                                                                            sign(<
                                                                                                                                                  'VA_Submit_Ballot',
                                                                                                                                                  ~ec,
                                                                                                                                                  pseudonym($V.1),
                                                                                                                                                  pk(~sk_voter.1),
                                                                                                                                                  ~bs_unused,
                                                                                                                                                  ny_encrypt_c1(~ballot.1,
                                                                                                                                                                pk(~sk_election),
                                                                                                                                                                ~r.1),
                                                                                                                                                  ny_encrypt_c2(~ballot.1,
                                                                                                                                                                pk(~sk_election),
                                                                                                                                                                ~r.1),
                                                                                                                                                  ny_encrypt_p(~ballot.1,
                                                                                                                                                               pk(~sk_election),
                                                                                                                                                               ~r.1)
                                                                                                                                                 >,
                                                                                                                                                 '1',
                                                                                                                                                 ~sk_voter.1)
                                                                                                                                           >,
                                                                                                                                           <
                                                                                                                                            'VA_Cast_Ballot',
                                                                                                                                            ~ec,
                                                                                                                                            pseudonym($V.1),
                                                                                                                                            pk(~sk_voter.1),
                                                                                                                                            h(<
                                                                                                                                               <
                                                                                                                                                'BBEntry_Ballot_Submission',
                                                                                                                                                ~ec,
                                                                                                                                                %1,
                                                                                                                                                <
                                                                                                                                                 'VA_Submit_Ballot',
                                                                                                                                                 ~ec,
                                                                                                                                                 pseudonym($V.1),
                                                                                                                                                 pk(~sk_voter.1),
                                                                                                                                                 ~bs_unused,
                                                                                                                                                 ny_encrypt_c1(~ballot.1,
                                                                                                                                                               pk(~sk_election),
                                                                                                                                                               ~r.1),
                                                                                                                                                 ny_encrypt_c2(~ballot.1,
                                                                                                                                                               pk(~sk_election),
                                                                                                                                                               ~r.1),
                                                                                                                                                 ny_encrypt_p(~ballot.1,
                                                                                                                                                              pk(~sk_election),
                                                                                                                                                              ~r.1)
                                                                                                                                                >,
                                                                                                                                                sign(<
                                                                                                                                                      'VA_Submit_Ballot',
                                                                                                                                                      ~ec,
                                                                                                                                                      pseudonym($V.1),
                                                                                                                                                      pk(~sk_voter.1),
                                                                                                                                                      ~bs_unused,
                                                                                                                                                      ny_encrypt_c1(~ballot.1,
                                                                                                                                                                    pk(~sk_election),
                                                                                                                                                                    ~r.1),
                                                                                                                                                      ny_encrypt_c2(~ballot.1,
                                                                                                                                                                    pk(~sk_election),
                                                                                                                                                                    ~r.1),
                                                                                                                                                      ny_encrypt_p(~ballot.1,
                                                                                                                                                                   pk(~sk_election),
                                                                                                                                                                   ~r.1)
                                                                                                                                                     >,
                                                                                                                                                     '1',
                                                                                                                                                     ~sk_voter.1)
                                                                                                                                               >,
                                                                                                                                               h(<
                                                                                                                                                  <
                                                                                                                                                   'BBEntry_Ballot_Submission',
                                                                                                                                                   ~ec,
                                                                                                                                                   %1,
                                                                                                                                                   <
                                                                                                                                                    'VA_Submit_Ballot',
                                                                                                                                                    ~ec,
                                                                                                                                                    pseudonym($V),
                                                                                                                                                    pk(~sk_voter),
                                                                                                                                                    ~bs_unused,
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
                                                                                                                                                   sign(<
                                                                                                                                                         'VA_Submit_Ballot',
                                                                                                                                                         ~ec,
                                                                                                                                                         pseudonym($V),
                                                                                                                                                         pk(~sk_voter),
                                                                                                                                                         ~bs_unused,
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
                                                                                                                                                        '1',
                                                                                                                                                        ~sk_voter)
                                                                                                                                                  >,
                                                                                                                                                  h(<
                                                                                                                                                     ~ec,
                                                                                                                                                     ~bbid
                                                                                                                                                    >)
                                                                                                                                                 >)
                                                                                                                                              >)
                                                                                                                                           >,
                                                                                                                                           sign(<
                                                                                                                                                 'VA_Cast_Ballot',
                                                                                                                                                 ~ec,
                                                                                                                                                 pseudonym($V.1),
                                                                                                                                                 pk(~sk_voter.1),
                                                                                                                                                 h(<
                                                                                                                                                    <
                                                                                                                                                     'BBEntry_Ballot_Submission',
                                                                                                                                                     ~ec,
                                                                                                                                                     %1,
                                                                                                                                                     <
                                                                                                                                                      'VA_Submit_Ballot',
                                                                                                                                                      ~ec,
                                                                                                                                                      pseudonym($V.1),
                                                                                                                                                      pk(~sk_voter.1),
                                                                                                                                                      ~bs_unused,
                                                                                                                                                      ny_encrypt_c1(~ballot.1,
                                                                                                                                                                    pk(~sk_election),
                                                                                                                                                                    ~r.1),
                                                                                                                                                      ny_encrypt_c2(~ballot.1,
                                                                                                                                                                    pk(~sk_election),
                                                                                                                                                                    ~r.1),
                                                                                                                                                      ny_encrypt_p(~ballot.1,
                                                                                                                                                                   pk(~sk_election),
                                                                                                                                                                   ~r.1)
                                                                                                                                                     >,
                                                                                                                                                     sign(<
                                                                                                                                                           'VA_Submit_Ballot',
                                                                                                                                                           ~ec,
                                                                                                                                                           pseudonym($V.1),
                                                                                                                                                           pk(~sk_voter.1),
                                                                                                                                                           ~bs_unused,
                                                                                                                                                           ny_encrypt_c1(~ballot.1,
                                                                                                                                                                         pk(~sk_election),
                                                                                                                                                                         ~r.1),
                                                                                                                                                           ny_encrypt_c2(~ballot.1,
                                                                                                                                                                         pk(~sk_election),
                                                                                                                                                                         ~r.1),
                                                                                                                                                           ny_encrypt_p(~ballot.1,
                                                                                                                                                                        pk(~sk_election),
                                                                                                                                                                        ~r.1)
                                                                                                                                                          >,
                                                                                                                                                          '1',
                                                                                                                                                          ~sk_voter.1)
                                                                                                                                                    >,
                                                                                                                                                    h(<
                                                                                                                                                       <
                                                                                                                                                        'BBEntry_Ballot_Submission',
                                                                                                                                                        ~ec,
                                                                                                                                                        %1,
                                                                                                                                                        <
                                                                                                                                                         'VA_Submit_Ballot',
                                                                                                                                                         ~ec,
                                                                                                                                                         pseudonym($V),
                                                                                                                                                         pk(~sk_voter),
                                                                                                                                                         ~bs_unused,
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
                                                                                                                                                        sign(<
                                                                                                                                                              'VA_Submit_Ballot',
                                                                                                                                                              ~ec,
                                                                                                                                                              pseudonym($V),
                                                                                                                                                              pk(~sk_voter),
                                                                                                                                                              ~bs_unused,
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
                                                                                                                                                             '1',
                                                                                                                                                             ~sk_voter)
                                                                                                                                                       >,
                                                                                                                                                       h(<
                                                                                                                                                          ~ec,
                                                                                                                                                          ~bbid
                                                                                                                                                         >)
                                                                                                                                                      >)
                                                                                                                                                   >)
                                                                                                                                                >,
                                                                                                                                                '1',
                                                                                                                                                ~sk_voter.1)
                                                                                                                                          >,
                                                                                                                                          h(<
                                                                                                                                             <
                                                                                                                                              'BBEntry_Voter_Authorization',
                                                                                                                                              ~ec,
                                                                                                                                              %1,
                                                                                                                                              <
                                                                                                                                               'EAS_Authorize_Voter',
                                                                                                                                               ~ec,
                                                                                                                                               pseudonym($V.1),
                                                                                                                                               pk(~sk_voter.1),
                                                                                                                                               ~bs_unused
                                                                                                                                              >,
                                                                                                                                              sign(<
                                                                                                                                                    'EAS_Authorize_Voter',
                                                                                                                                                    ~ec,
                                                                                                                                                    pseudonym($V.1),
                                                                                                                                                    pk(~sk_voter.1),
                                                                                                                                                    ~bs_unused
                                                                                                                                                   >,
                                                                                                                                                   '1',
                                                                                                                                                   ~sk_eas)
                                                                                                                                             >,
                                                                                                                                             h(<
                                                                                                                                                e_unused,
                                                                                                                                                ch
                                                                                                                                               >)
                                                                                                                                            >)
                                                                                                                                         >),
                                                                                                                                       (
                                                                                                                                        %idx%+
                                                                                                                                        %1%+
                                                                                                                                        %1%+
                                                                                                                                        %1
                                                                                                                                       )
                                                                                                                       ) @ #vr.9 )
                                                                                                                  case BulletinBoard_Append
                                                                                                                  solve( BB_Current( ~bbid,
                                                                                                                                     c,
                                                                                                                                     h(<
                                                                                                                                        <
                                                                                                                                         'BBEntry_Ballot_Cast',
                                                                                                                                         (
                                                                                                                                          %1%+
                                                                                                                                          %1
                                                                                                                                         ),
                                                                                                                                         <
                                                                                                                                          <
                                                                                                                                           'VA_Submit_Ballot',
                                                                                                                                           ~ec,
                                                                                                                                           pseudonym($V.1),
                                                                                                                                           pk(~sk_voter.1),
                                                                                                                                           ~bs_unused,
                                                                                                                                           ny_encrypt_c1(~ballot.1,
                                                                                                                                                         pk(~sk_election),
                                                                                                                                                         ~r.1),
                                                                                                                                           ny_encrypt_c2(~ballot.1,
                                                                                                                                                         pk(~sk_election),
                                                                                                                                                         ~r.1),
                                                                                                                                           ny_encrypt_p(~ballot.1,
                                                                                                                                                        pk(~sk_election),
                                                                                                                                                        ~r.1)
                                                                                                                                          >,
                                                                                                                                          sign(<
                                                                                                                                                'VA_Submit_Ballot',
                                                                                                                                                ~ec,
                                                                                                                                                pseudonym($V.1),
                                                                                                                                                pk(~sk_voter.1),
                                                                                                                                                ~bs_unused,
                                                                                                                                                ny_encrypt_c1(~ballot.1,
                                                                                                                                                              pk(~sk_election),
                                                                                                                                                              ~r.1),
                                                                                                                                                ny_encrypt_c2(~ballot.1,
                                                                                                                                                              pk(~sk_election),
                                                                                                                                                              ~r.1),
                                                                                                                                                ny_encrypt_p(~ballot.1,
                                                                                                                                                             pk(~sk_election),
                                                                                                                                                             ~r.1)
                                                                                                                                               >,
                                                                                                                                               '1',
                                                                                                                                               ~sk_voter.1)
                                                                                                                                         >,
                                                                                                                                         <
                                                                                                                                          'VA_Cast_Ballot',
                                                                                                                                          ~ec,
                                                                                                                                          pseudonym($V.1),
                                                                                                                                          pk(~sk_voter.1),
                                                                                                                                          h(<
                                                                                                                                             <
                                                                                                                                              'BBEntry_Ballot_Submission',
                                                                                                                                              ~ec,
                                                                                                                                              %1,
                                                                                                                                              <
                                                                                                                                               'VA_Submit_Ballot',
                                                                                                                                               ~ec,
                                                                                                                                               pseudonym($V.1),
                                                                                                                                               pk(~sk_voter.1),
                                                                                                                                               ~bs_unused,
                                                                                                                                               ny_encrypt_c1(~ballot.1,
                                                                                                                                                             pk(~sk_election),
                                                                                                                                                             ~r.1),
                                                                                                                                               ny_encrypt_c2(~ballot.1,
                                                                                                                                                             pk(~sk_election),
                                                                                                                                                             ~r.1),
                                                                                                                                               ny_encrypt_p(~ballot.1,
                                                                                                                                                            pk(~sk_election),
                                                                                                                                                            ~r.1)
                                                                                                                                              >,
                                                                                                                                              sign(<
                                                                                                                                                    'VA_Submit_Ballot',
                                                                                                                                                    ~ec,
                                                                                                                                                    pseudonym($V.1),
                                                                                                                                                    pk(~sk_voter.1),
                                                                                                                                                    ~bs_unused,
                                                                                                                                                    ny_encrypt_c1(~ballot.1,
                                                                                                                                                                  pk(~sk_election),
                                                                                                                                                                  ~r.1),
                                                                                                                                                    ny_encrypt_c2(~ballot.1,
                                                                                                                                                                  pk(~sk_election),
                                                                                                                                                                  ~r.1),
                                                                                                                                                    ny_encrypt_p(~ballot.1,
                                                                                                                                                                 pk(~sk_election),
                                                                                                                                                                 ~r.1)
                                                                                                                                                   >,
                                                                                                                                                   '1',
                                                                                                                                                   ~sk_voter.1)
                                                                                                                                             >,
                                                                                                                                             h(<
                                                                                                                                                <
                                                                                                                                                 'BBEntry_Ballot_Submission',
                                                                                                                                                 ~ec,
                                                                                                                                                 %1,
                                                                                                                                                 <
                                                                                                                                                  'VA_Submit_Ballot',
                                                                                                                                                  ~ec,
                                                                                                                                                  pseudonym($V),
                                                                                                                                                  pk(~sk_voter),
                                                                                                                                                  ~bs_unused,
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
                                                                                                                                                 sign(<
                                                                                                                                                       'VA_Submit_Ballot',
                                                                                                                                                       ~ec,
                                                                                                                                                       pseudonym($V),
                                                                                                                                                       pk(~sk_voter),
                                                                                                                                                       ~bs_unused,
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
                                                                                                                                                      '1',
                                                                                                                                                      ~sk_voter)
                                                                                                                                                >,
                                                                                                                                                h(<
                                                                                                                                                   ~ec,
                                                                                                                                                   ~bbid
                                                                                                                                                  >)
                                                                                                                                               >)
                                                                                                                                            >)
                                                                                                                                         >,
                                                                                                                                         sign(<
                                                                                                                                               'VA_Cast_Ballot',
                                                                                                                                               ~ec,
                                                                                                                                               pseudonym($V.1),
                                                                                                                                               pk(~sk_voter.1),
                                                                                                                                               h(<
                                                                                                                                                  <
                                                                                                                                                   'BBEntry_Ballot_Submission',
                                                                                                                                                   ~ec,
                                                                                                                                                   %1,
                                                                                                                                                   <
                                                                                                                                                    'VA_Submit_Ballot',
                                                                                                                                                    ~ec,
                                                                                                                                                    pseudonym($V.1),
                                                                                                                                                    pk(~sk_voter.1),
                                                                                                                                                    ~bs_unused,
                                                                                                                                                    ny_encrypt_c1(~ballot.1,
                                                                                                                                                                  pk(~sk_election),
                                                                                                                                                                  ~r.1),
                                                                                                                                                    ny_encrypt_c2(~ballot.1,
                                                                                                                                                                  pk(~sk_election),
                                                                                                                                                                  ~r.1),
                                                                                                                                                    ny_encrypt_p(~ballot.1,
                                                                                                                                                                 pk(~sk_election),
                                                                                                                                                                 ~r.1)
                                                                                                                                                   >,
                                                                                                                                                   sign(<
                                                                                                                                                         'VA_Submit_Ballot',
                                                                                                                                                         ~ec,
                                                                                                                                                         pseudonym($V.1),
                                                                                                                                                         pk(~sk_voter.1),
                                                                                                                                                         ~bs_unused,
                                                                                                                                                         ny_encrypt_c1(~ballot.1,
                                                                                                                                                                       pk(~sk_election),
                                                                                                                                                                       ~r.1),
                                                                                                                                                         ny_encrypt_c2(~ballot.1,
                                                                                                                                                                       pk(~sk_election),
                                                                                                                                                                       ~r.1),
                                                                                                                                                         ny_encrypt_p(~ballot.1,
                                                                                                                                                                      pk(~sk_election),
                                                                                                                                                                      ~r.1)
                                                                                                                                                        >,
                                                                                                                                                        '1',
                                                                                                                                                        ~sk_voter.1)
                                                                                                                                                  >,
                                                                                                                                                  h(<
                                                                                                                                                     <
                                                                                                                                                      'BBEntry_Ballot_Submission',
                                                                                                                                                      ~ec,
                                                                                                                                                      %1,
                                                                                                                                                      <
                                                                                                                                                       'VA_Submit_Ballot',
                                                                                                                                                       ~ec,
                                                                                                                                                       pseudonym($V),
                                                                                                                                                       pk(~sk_voter),
                                                                                                                                                       ~bs_unused,
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
                                                                                                                                                      sign(<
                                                                                                                                                            'VA_Submit_Ballot',
                                                                                                                                                            ~ec,
                                                                                                                                                            pseudonym($V),
                                                                                                                                                            pk(~sk_voter),
                                                                                                                                                            ~bs_unused,
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
                                                                                                                                                           '1',
                                                                                                                                                           ~sk_voter)
                                                                                                                                                     >,
                                                                                                                                                     h(<
                                                                                                                                                        ~ec,
                                                                                                                                                        ~bbid
                                                                                                                                                       >)
                                                                                                                                                    >)
                                                                                                                                                 >)
                                                                                                                                              >,
                                                                                                                                              '1',
                                                                                                                                              ~sk_voter.1)
                                                                                                                                        >,
                                                                                                                                        h(<
                                                                                                                                           <
                                                                                                                                            'BBEntry_Voter_Authorization',
                                                                                                                                            ~ec,
                                                                                                                                            %1,
                                                                                                                                            <
                                                                                                                                             'EAS_Authorize_Voter',
                                                                                                                                             ~ec,
                                                                                                                                             pseudonym($V.1),
                                                                                                                                             pk(~sk_voter.1),
                                                                                                                                             ~bs_unused
                                                                                                                                            >,
                                                                                                                                            sign(<
                                                                                                                                                  'EAS_Authorize_Voter',
                                                                                                                                                  ~ec,
                                                                                                                                                  pseudonym($V.1),
                                                                                                                                                  pk(~sk_voter.1),
                                                                                                                                                  ~bs_unused
                                                                                                                                                 >,
                                                                                                                                                 '1',
                                                                                                                                                 ~sk_eas)
                                                                                                                                           >,
                                                                                                                                           h(<
                                                                                                                                              e_unused,
                                                                                                                                              ch
                                                                                                                                             >)
                                                                                                                                          >)
                                                                                                                                       >),
                                                                                                                                     (
                                                                                                                                      %idx%+
                                                                                                                                      %1%+
                                                                                                                                      %1%+
                                                                                                                                      %1
                                                                                                                                     )
                                                                                                                         )[+] ▶₁ #j.1 )
                                                                                                                    case BulletinBoard_Append
                                                                                                                    solve( (¬((
                                                                                                                               %idx%+
                                                                                                                               %1
                                                                                                                              ) ⊏
                                                                                                                              (
                                                                                                                               %1%+
                                                                                                                               %1%+
                                                                                                                               %1
                                                                                                                              )))  ∥
                                                                                                                           (#j.3 < #vr.10) )
                                                                                                                      case case_1
                                                                                                                      solve( (¬((
                                                                                                                                 %1%+
                                                                                                                                 %1%+
                                                                                                                                 %1
                                                                                                                                ) ⊏
                                                                                                                                (
                                                                                                                                 %idx%+
                                                                                                                                 %1
                                                                                                                                )))  ∥
                                                                                                                             (#vr.10 < #j.3) )
                                                                                                                        case case_1
                                                                                                                        solve( BB_Current( ~bbid,
                                                                                                                                           c,
                                                                                                                                           h(<
                                                                                                                                              <
                                                                                                                                               'BBEntry_Ballot_Submission',
                                                                                                                                               ~ec,
                                                                                                                                               %1,
                                                                                                                                               <
                                                                                                                                                'VA_Submit_Ballot',
                                                                                                                                                ~ec,
                                                                                                                                                pseudonym($V.1),
                                                                                                                                                pk(~sk_voter.1),
                                                                                                                                                ~bs_unused,
                                                                                                                                                ny_encrypt_c1(~ballot.1,
                                                                                                                                                              pk(~sk_election),
                                                                                                                                                              ~r.1),
                                                                                                                                                ny_encrypt_c2(~ballot.1,
                                                                                                                                                              pk(~sk_election),
                                                                                                                                                              ~r.1),
                                                                                                                                                ny_encrypt_p(~ballot.1,
                                                                                                                                                             pk(~sk_election),
                                                                                                                                                             ~r.1)
                                                                                                                                               >,
                                                                                                                                               sign(<
                                                                                                                                                     'VA_Submit_Ballot',
                                                                                                                                                     ~ec,
                                                                                                                                                     pseudonym($V.1),
                                                                                                                                                     pk(~sk_voter.1),
                                                                                                                                                     ~bs_unused,
                                                                                                                                                     ny_encrypt_c1(~ballot.1,
                                                                                                                                                                   pk(~sk_election),
                                                                                                                                                                   ~r.1),
                                                                                                                                                     ny_encrypt_c2(~ballot.1,
                                                                                                                                                                   pk(~sk_election),
                                                                                                                                                                   ~r.1),
                                                                                                                                                     ny_encrypt_p(~ballot.1,
                                                                                                                                                                  pk(~sk_election),
                                                                                                                                                                  ~r.1)
                                                                                                                                                    >,
                                                                                                                                                    '1',
                                                                                                                                                    ~sk_voter.1)
                                                                                                                                              >,
                                                                                                                                              h(<
                                                                                                                                                 <
                                                                                                                                                  'BBEntry_Ballot_Submission',
                                                                                                                                                  ~ec,
                                                                                                                                                  %1,
                                                                                                                                                  <
                                                                                                                                                   'VA_Submit_Ballot',
                                                                                                                                                   ~ec,
                                                                                                                                                   pseudonym($V),
                                                                                                                                                   pk(~sk_voter),
                                                                                                                                                   ~bs_unused,
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
                                                                                                                                                  sign(<
                                                                                                                                                        'VA_Submit_Ballot',
                                                                                                                                                        ~ec,
                                                                                                                                                        pseudonym($V),
                                                                                                                                                        pk(~sk_voter),
                                                                                                                                                        ~bs_unused,
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
                                                                                                                                                       '1',
                                                                                                                                                       ~sk_voter)
                                                                                                                                                 >,
                                                                                                                                                 h(<
                                                                                                                                                    ~ec,
                                                                                                                                                    ~bbid
                                                                                                                                                   >)
                                                                                                                                                >)
                                                                                                                                             >),
                                                                                                                                           (
                                                                                                                                            %1%+
                                                                                                                                            %1%+
                                                                                                                                            %1
                                                                                                                                           )
                                                                                                                               )[+] ▶₁ #j.2 )
                                                                                                                          case BulletinBoard_Append
                                                                                                                          solve( DBB_State_ReceiveAuthorizeVoter( ~ec,
                                                                                                                                                                  (
                                                                                                                                                                   %1%+
                                                                                                                                                                   %1
                                                                                                                                                                  )
                                                                                                                                 ) ▶₀ #vr.48 )
                                                                                                                            case Mock_Voter_Authentication
                                                                                                                            solve( DBB_State_ReceiveAuthorizeVoter( ~ec,
                                                                                                                                                                    %1
                                                                                                                                   ) ▶₀ #vr.51 )
                                                                                                                              case Mock_Finalize_Election_Setup
                                                                                                                              solve( VoterCount( ~ec,
                                                                                                                                                 %idx_ev
                                                                                                                                     ) ▶₀ #vr.21 )
                                                                                                                                case Mock_EC_And_Initial_Counters
                                                                                                                                solve( BallotStyleCount( ~ec,
                                                                                                                                                         %unused
                                                                                                                                       ) ▶₀ #vr.43 )
                                                                                                                                  case Mock_BallotStyle
                                                                                                                                  simplify
                                                                                                                                  by sorry
                                                                                                                                next
                                                                                                                                  case Mock_EC_And_Initial_Counters
                                                                                                                                  solve( BallotStyleCount( ~ec,
                                                                                                                                                           %idx_bs
                                                                                                                                         ) ▶₀ #vr.44 )
                                                                                                                                    case Mock_BallotStyle
                                                                                                                                    by sorry
                                                                                                                                  next
                                                                                                                                    case Mock_EC_And_Initial_Counters
                                                                                                                                    solve( BallotStyleCount( ~ec,
                                                                                                                                                             %idx_bs
                                                                                                                                           ) ▶₀ #vr.46 )
                                                                                                                                      case Mock_BallotStyle
                                                                                                                                      by sorry
                                                                                                                                    next
                                                                                                                                      case Mock_EC_And_Initial_Counters
                                                                                                                                      solve( BallotStyleCount( ~ec,
                                                                                                                                                               %idx_bs
                                                                                                                                             ) ▶₀ #vr.48 )
                                                                                                                                        case Mock_BallotStyle
                                                                                                                                        by sorry
                                                                                                                                      next
                                                                                                                                        case Mock_EC_And_Initial_Counters
                                                                                                                                        solve( VoterCount( ~ec,
                                                                                                                                                           %i.2
                                                                                                                                               ) ▶₀ #vr.6 )
                                                                                                                                          case Mock_VoterRegistration_Eligible
                                                                                                                                          solve( VoterCount( ~ec,
                                                                                                                                                             %idx_ev
                                                                                                                                                 ) ▶₀ #vr.44 )
                                                                                                                                            case Mock_EC_And_Initial_Counters
                                                                                                                                            by contradiction
                                                                                                                                               /*
                                                                                                                                               from formulas
                                                                                                                                               */
                                                                                                                                          next
                                                                                                                                            case Mock_VoterRegistration_Eligible
                                                                                                                                            solve( VoterCount( ~ec,
                                                                                                                                                               %idx_ev
                                                                                                                                                   ) ▶₀ #vr.46 )
                                                                                                                                              case Mock_EC_And_Initial_Counters
                                                                                                                                              solve( BallotStyleCount( ~ec,
                                                                                                                                                                       %unused
                                                                                                                                                     ) ▶₀ #vr.49 )
                                                                                                                                                case Mock_BallotStyle
                                                                                                                                                simplify
                                                                                                                                                by sorry
                                                                                                                                              next
                                                                                                                                                case Mock_EC_And_Initial_Counters
                                                                                                                                                solve( VoterCount( ~ec,
                                                                                                                                                                   %idx_ev
                                                                                                                                                       ) ▶₀ #vr.47 )
                                                                                                                                                  case Mock_EC_And_Initial_Counters
                                                                                                                                                  solve( VoterCount( ~ec,
                                                                                                                                                                     %i.4
                                                                                                                                                         ) ▶₀ #vr.42 )
                                                                                                                                                    case Mock_EC_And_Initial_Counters
                                                                                                                                                    simplify
                                                                                                                                                    solve( VoterCount( ~ec,
                                                                                                                                                                       %i.4
                                                                                                                                                           ) ▶₀ #vr.47 )
                                                                                                                                                      case Mock_EC_And_Initial_Counters
                                                                                                                                                      solve( BallotStyleCount( ~ec,
                                                                                                                                                                               %i.3
                                                                                                                                                             ) ▶₀ #vr.39 )
                                                                                                                                                        case Mock_BallotStyle
                                                                                                                                                        solve( VoterCount( ~ec,
                                                                                                                                                                           %i.2
                                                                                                                                                               ) ▶₀ #vr.45 )
                                                                                                                                                          case Mock_VoterRegistration_Eligible
                                                                                                                                                          solve( VoterCount( ~ec,
                                                                                                                                                                             %i.2
                                                                                                                                                                 ) ▶₀ #vr.47 )
                                                                                                                                                            case Mock_EC_And_Initial_Counters
                                                                                                                                                            solve( BallotStyleCount( ~ec,
                                                                                                                                                                                     %i.1
                                                                                                                                                                   ) ▶₀ #vr.5 )
                                                                                                                                                              case Mock_BallotStyle
                                                                                                                                                              solve( BallotStyleCount( ~ec,
                                                                                                                                                                                       %i.2
                                                                                                                                                                     ) ▶₀ #vr.45 )
                                                                                                                                                                case Mock_BallotStyle
                                                                                                                                                                by sorry
                                                                                                                                                              next
                                                                                                                                                                case Mock_EC_And_Initial_Counters
                                                                                                                                                                solve( BallotStyleCount( ~ec,
                                                                                                                                                                                         %i.1
                                                                                                                                                                       ) ▶₀ #vr.45 )
                                                                                                                                                                  case Mock_BallotStyle
                                                                                                                                                                  solve( BallotStyleCount( ~ec,
                                                                                                                                                                                           %i.1
                                                                                                                                                                         ) ▶₀ #vr.46 )
                                                                                                                                                                    case Mock_BallotStyle
                                                                                                                                                                    by sorry
                                                                                                                                                                  next
                                                                                                                                                                    case Mock_EC_And_Initial_Counters
                                                                                                                                                                    solve( BallotStyleCount( ~ec,
                                                                                                                                                                                             %i
                                                                                                                                                                           ) ▶₀ #vr.37 )
                                                                                                                                                                      case Mock_BallotStyle
                                                                                                                                                                      by sorry
                                                                                                                                                                    next
                                                                                                                                                                      case Mock_EC_And_Initial_Counters
                                                                                                                                                                      SOLVED // trace found
                                                                                                                                                                    qed
                                                                                                                                                                  qed
                                                                                                                                                                qed
                                                                                                                                                              qed
                                                                                                                                                            next
                                                                                                                                                              case Mock_EC_And_Initial_Counters
                                                                                                                                                              simplify
                                                                                                                                                              by contradiction
                                                                                                                                                                 /*
                                                                                                                                                                 cyclic
                                                                                                                                                                 */
                                                                                                                                                            qed
                                                                                                                                                          next
                                                                                                                                                            case Mock_VoterRegistration_Eligible
                                                                                                                                                            by sorry
                                                                                                                                                          qed
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
                                                                                                                                                    case Mock_VoterRegistration_Eligible
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
                                                                                                                                        qed
                                                                                                                                      qed
                                                                                                                                    qed
                                                                                                                                  qed
                                                                                                                                qed
                                                                                                                              next
                                                                                                                                case Mock_VoterRegistration_Eligible
                                                                                                                                by sorry
                                                                                                                              qed
                                                                                                                            qed
                                                                                                                          qed
                                                                                                                        qed
                                                                                                                      next
                                                                                                                        case case_2
                                                                                                                        by sorry
                                                                                                                      qed
                                                                                                                    next
                                                                                                                      case case_2
                                                                                                                      by sorry
                                                                                                                    qed
                                                                                                                  qed
                                                                                                                qed
                                                                                                              next
                                                                                                                case case_2
                                                                                                                by sorry
                                                                                                              qed
                                                                                                            next
                                                                                                              case SubtermSplit1_case_2
                                                                                                              simplify
                                                                                                              by sorry
                                                                                                            qed
                                                                                                          qed
                                                                                                        next
                                                                                                          case case_2
                                                                                                          by sorry
                                                                                                        qed
                                                                                                      next
                                                                                                        case case_2
                                                                                                        by sorry
                                                                                                      qed
                                                                                                    qed
                                                                                                  qed
                                                                                                qed
                                                                                              qed
                                                                                            qed
                                                                                          qed
                                                                                        qed
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
                                                                          qed
                                                                        qed
                                                                      qed
                                                                    next
                                                                      case SubtermSplit1_case_2
                                                                      simplify
                                                                      by contradiction /* cyclic */
                                                                    next
                                                                      case SubtermSplit1_case_3
                                                                      simplify
                                                                      by contradiction /* cyclic */
                                                                    qed
                                                                  next
                                                                    case SubtermSplit1_case_02
                                                                    simplify
                                                                    by contradiction /* cyclic */
                                                                  next
                                                                    case SubtermSplit1_case_03
                                                                    simplify
                                                                    by contradiction /* cyclic */
                                                                  next
                                                                    case SubtermSplit1_case_04
                                                                    simplify
                                                                    by sorry
                                                                  next
                                                                    case SubtermSplit1_case_05
                                                                    simplify
                                                                    by sorry
                                                                  next
                                                                    case SubtermSplit1_case_06
                                                                    simplify
                                                                    by sorry
                                                                  next
                                                                    case SubtermSplit1_case_07
                                                                    simplify
                                                                    by sorry
                                                                  next
                                                                    case SubtermSplit1_case_08
                                                                    simplify
                                                                    by sorry
                                                                  next
                                                                    case SubtermSplit1_case_09
                                                                    simplify
                                                                    by sorry
                                                                  next
                                                                    case SubtermSplit1_case_10
                                                                    simplify
                                                                    by sorry
                                                                  next
                                                                    case SubtermSplit1_case_11
                                                                    simplify
                                                                    by sorry
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
                                                    next
                                                      case Mock_AppendSubmittedBallot_case_2
                                                      simplify
                                                      by contradiction /* cyclic */
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
              case BallotCast_VA_Cast_case_2
              by sorry
            qed
          next
            case BulletinBoard_Create
            by sorry
          qed
        qed
      next
        case BulletinBoard_Create
        by sorry
      qed
    qed
  qed
qed
