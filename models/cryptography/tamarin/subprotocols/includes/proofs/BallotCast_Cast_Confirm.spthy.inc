simplify
solve( !BB_Entry( ~bbid, sub_bb_entry, sub_tracker, %idx_sub
       ) ▶₃ #i )
  case BulletinBoard_Append
  solve( !BB_Entry( ~bbid,
                    <'BBEntry_Ballot_Cast', %ts_cast,
                     <
                      <'VA_Submit_Ballot', ~ec, pseudo, pk(~sk_voter), ballot_style,
                       cryptograms>,
                      sign(<'VA_Submit_Ballot', ~ec, pseudo, pk(~sk_voter),
                            ballot_style, cryptograms>,
                           '1', ~sk_voter)
                     >,
                     <'VA_Cast_Ballot', ~ec, pseudo, pk(~sk_voter), tracker>,
                     sign(<'VA_Cast_Ballot', ~ec, pseudo, pk(~sk_voter), tracker>, '1',
                          ~sk_voter)
                    >,
                    cast_tracker, %idx_cast
         ) ▶₄ #i )
    case BulletinBoard_Append
    solve( SecureReceive( ~cid, <~ec, 'DBB'>, ~va_id,
                          <'DBB_Cast_Confirmation', ~ec, h(<sub_bb_entry, ch>),
                           h(<
                              <'BBEntry_Ballot_Cast', %ts_cast,
                               <
                                <'VA_Submit_Ballot', ~ec, pseudo, pk(~sk_voter), ballot_style,
                                 cryptograms>,
                                sign(<'VA_Submit_Ballot', ~ec, pseudo, pk(~sk_voter),
                                      ballot_style, cryptograms>,
                                     '1', ~sk_voter)
                               >,
                               <'VA_Cast_Ballot', ~ec, pseudo, pk(~sk_voter), tracker>,
                               sign(<'VA_Cast_Ballot', ~ec, pseudo, pk(~sk_voter), tracker>, '1',
                                    ~sk_voter)
                              >,
                              ch.1>)
                          >
           ) ▶₅ #i )
      case SecureChannel_Receive_case_1
      by sorry
    next
      case SecureChannel_Receive_case_2
      solve( (¬(%1 ⊏ %idx))  ∥ (#vr.1 < #j) )
        case case_1
        solve( (¬((%1%+%1) ⊏ (%idx%+%1)))  ∥ (#vr < #vr.8) )
          case case_2
          solve( (¬(%1 ⊏ %idx))  ∥ (#j < #j.1) )
            case case_2
            solve( (¬(%idx ⊏ (%1%+%1)))  ∥ (#j.1 < #vr) )
              case case_1
              solve( (¬((%1%+%1) ⊏ %idx))  ∥ (#vr < #j.1) )
                case case_2
                solve( (¬((%idx.1%+%1%+%1) ⊏ (%idx.2%+%1)))  ∥ (#vr.14 < #vr.20) )
                  case case_1
                  solve( (¬((%idx.1%+%1) ⊏ (%idx.2%+%1)))  ∥ (#vr.18 < #vr.20) )
                    case case_1
                    solve( (¬((%idx.2%+%1) ⊏ (%idx.1%+%1)))  ∥ (#vr.20 < #vr.18) )
                      case case_1
                      solve( (#j = #vr.13)  ∥ ((¬(~ec.1 = ~ec)) ∧ (¬(~bbid = ~bbid.1))) )
                        case case_1
                        solve( VA_State_BallotCastResponse( ~ec, ~va_id, ~cid,
                                                            pseudonym($V), ~ballot, cryptograms, ~r,
                                                            h(<
                                                               <'BBEntry_Ballot_Submission', ~ec,
                                                                %ts_sub,
                                                                <'VA_Submit_Ballot', ~ec,
                                                                 pseudonym($V), pk(~sk_voter), ~bs,
                                                                 cryptograms>,
                                                                sign(<'VA_Submit_Ballot', ~ec,
                                                                      pseudonym($V), pk(~sk_voter),
                                                                      ~bs, cryptograms>,
                                                                     '1', ~sk_voter)
                                                               >,
                                                               h(<~ec, ~bbid>)>)
                               ) ▶₀ #i )
                          case BallotCast_VA_Cast
                          solve( !VA_Eligible_Voter( ~ec, ~va_id, pseudonym($V), ~sk_voter,
                                                     ~bs
                                 ) ▶₁ #i )
                            case Mock_Voter_Authentication
                            solve( !BB_Root( ~ec, ~bbid, r_unused, rh_unused ) ▶₂ #i )
                              case BulletinBoard_Create
                              solve( BB_Trace_Entry( ~bbid, ~ec, h(<~ec, ~bbid>), %1 ) @ #j )
                                case BulletinBoard_Create
                                solve( BB_Trace_Entry( ~bbid,
                                                       <'BBEntry_Voter_Authorization', ~ec, %ts,
                                                        <'EAS_Authorize_Voter', ~ec, pseudonym($V),
                                                         pk(~sk_voter), ~bs>,
                                                        sign(<'EAS_Authorize_Voter', ~ec,
                                                              pseudonym($V), pk(~sk_voter), ~bs>,
                                                             '1', ~sk_eas)
                                                       >,
                                                       h(<
                                                          <'BBEntry_Voter_Authorization', ~ec, %ts,
                                                           <'EAS_Authorize_Voter', ~ec,
                                                            pseudonym($V), pk(~sk_voter), ~bs>,
                                                           sign(<'EAS_Authorize_Voter', ~ec,
                                                                 pseudonym($V), pk(~sk_voter), ~bs>,
                                                                '1', ~sk_eas)
                                                          >,
                                                          h(<
                                                             <'BBEntry_Ballot_Submission', ~ec,
                                                              %ts_sub,
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
                                                             h(<~ec, ~bbid>)>)
                                                         >),
                                                       (%1%+%1%+%1)
                                       ) @ #j.1 )
                                  case BulletinBoard_Append
                                  solve( BB_Trace_Entry( ~bbid,
                                                         <'BBEntry_Ballot_Submission', ~ec,
                                                          %ts_sub,
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
                                                            <'BBEntry_Ballot_Submission', ~ec,
                                                             %ts_sub,
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
                                         ) @ #vr )
                                    case BulletinBoard_Append
                                    solve( BB_Current( ~bbid, c, h(<~ec, ~bbid>), %1 )[+] ▶₁ #vr )
                                      case BulletinBoard_Create
                                      solve( BB_Append_Request( ~bbid,
                                                                <'BBEntry_Ballot_Submission', ~ec,
                                                                 %ts_sub,
                                                                 <'VA_Submit_Ballot', ~ec,
                                                                  pseudonym($V), pk(~sk_voter),
                                                                  ~bs,
                                                                  ny_encrypt_c1(~ballot,
                                                                                pk(~sk_election),
                                                                                ~r),
                                                                  ny_encrypt_c2(~ballot,
                                                                                pk(~sk_election),
                                                                                ~r),
                                                                  ny_encrypt_p(~ballot,
                                                                               pk(~sk_election), ~r)
                                                                 >,
                                                                 sign(<'VA_Submit_Ballot', ~ec,
                                                                       pseudonym($V),
                                                                       pk(~sk_voter), ~bs,
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
                                             )[+] ▶₂ #vr )
                                        case Mock_AppendSubmittedBallot
                                        solve( BB_Current( ~bbid, c.1,
                                                           h(<
                                                              <'BBEntry_Voter_Authorization', ~ec,
                                                               %ts,
                                                               <'EAS_Authorize_Voter', ~ec,
                                                                pseudonym($V), pk(~sk_voter), ~bs>,
                                                               sign(<'EAS_Authorize_Voter', ~ec,
                                                                     pseudonym($V), pk(~sk_voter),
                                                                     ~bs>,
                                                                    '1', ~sk_eas)
                                                              >,
                                                              h(<
                                                                 <'BBEntry_Ballot_Submission', ~ec,
                                                                  %ts_sub,
                                                                  <'VA_Submit_Ballot', ~ec,
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
                                                                  sign(<'VA_Submit_Ballot', ~ec,
                                                                        pseudonym($V),
                                                                        pk(~sk_voter), ~bs,
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
                                                             >),
                                                           (%1%+%1%+%1)
                                               )[+] ▶₁ #vr.8 )
                                          case BulletinBoard_Append
                                          solve( BB_Append_Request( ~bbid,
                                                                    <'BBEntry_Ballot_Cast',
                                                                     (%ts%+%1),
                                                                     <
                                                                      <'VA_Submit_Ballot', ~ec,
                                                                       pseudonym($V),
                                                                       pk(~sk_voter), ~bs,
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
                                                                            pk(~sk_voter), ~bs,
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
                                                                     <'VA_Cast_Ballot', ~ec,
                                                                      pseudonym($V), pk(~sk_voter),
                                                                      h(<
                                                                         <
                                                                          'BBEntry_Ballot_Submission',
                                                                          ~ec, %ts_sub,
                                                                          <'VA_Submit_Ballot', ~ec,
                                                                           pseudonym($V),
                                                                           pk(~sk_voter), ~bs,
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
                                                                                pk(~sk_voter), ~bs,
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
                                                                           pseudonym($V),
                                                                           pk(~sk_voter),
                                                                           h(<
                                                                              <
                                                                               'BBEntry_Ballot_Submission',
                                                                               ~ec, %ts_sub,
                                                                               <'VA_Submit_Ballot',
                                                                                ~ec, pseudonym($V),
                                                                                pk(~sk_voter), ~bs,
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
                                                                              h(<~ec, ~bbid>)>)
                                                                          >,
                                                                          '1', ~sk_voter)
                                                                    >,
                                                                    (%1%+%1%+%1)
                                                 )[+] ▶₂ #vr.8 )
                                            case BallotCast_DBB_AppendCastBallot
                                            solve( BB_Current( ~bbid, c,
                                                               h(<
                                                                  <'BBEntry_Ballot_Submission',
                                                                   ~ec, %ts_sub,
                                                                   <'VA_Submit_Ballot', ~ec,
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
                                                                   sign(<'VA_Submit_Ballot', ~ec,
                                                                         pseudonym($V),
                                                                         pk(~sk_voter), ~bs,
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
                                                   )[+] ▶₁ #j.1 )
                                              case BulletinBoard_Append
                                              solve( BB_Append_Request( ~bbid,
                                                                        <
                                                                         'BBEntry_Voter_Authorization',
                                                                         ~ec, %ts,
                                                                         <'EAS_Authorize_Voter',
                                                                          ~ec, pseudonym($V),
                                                                          pk(~sk_voter), ~bs>,
                                                                         sign(<
                                                                               'EAS_Authorize_Voter',
                                                                               ~ec, pseudonym($V),
                                                                               pk(~sk_voter), ~bs>,
                                                                              '1', ~sk_eas)
                                                                        >,
                                                                        (%1%+%1)
                                                     )[+] ▶₂ #j.1 )
                                                case BallotCast_DBB_AppendCastBallot
                                                simplify
                                                solve( BB_Trace_Entry( ~bbid,
                                                                       <
                                                                        'BBEntry_Ballot_Submission',
                                                                        ~ec, %ts_sub.1,
                                                                        <'VA_Submit_Ballot', ~ec,
                                                                         pseudonym($V),
                                                                         pk(~sk_voter), ~bs,
                                                                         cryptograms>,
                                                                        sig_submit>,
                                                                       h(<
                                                                          <
                                                                           'BBEntry_Ballot_Submission',
                                                                           ~ec, %ts_sub.1,
                                                                           <'VA_Submit_Ballot',
                                                                            ~ec, pseudonym($V),
                                                                            pk(~sk_voter), ~bs,
                                                                            cryptograms>,
                                                                           sig_submit>,
                                                                          ch>),
                                                                       (%idx%+%1)
                                                       ) @ #vr.23 )
                                                  case BulletinBoard_Append
                                                  solve( BB_Append_Request( ~bbid,
                                                                            <
                                                                             'BBEntry_Ballot_Submission',
                                                                             ~ec, %ts_sub.1,
                                                                             <'VA_Submit_Ballot',
                                                                              ~ec, pseudonym($V),
                                                                              pk(~sk_voter), ~bs,
                                                                              cryptograms>,
                                                                             sig_submit>,
                                                                            %idx
                                                         )[+] ▶₂ #vr.23 )
                                                    case Mock_AppendSubmittedBallot
                                                    solve( SecureReceive( ~cid, ~va_id,
                                                                          <~ec, 'DBB'>,
                                                                          <
                                                                           <'VA_Cast_Ballot', ~ec,
                                                                            pseudonym($V),
                                                                            pk(~sk_voter),
                                                                            h(<
                                                                               <
                                                                                'BBEntry_Ballot_Submission',
                                                                                ~ec, %ts_sub,
                                                                                <
                                                                                 'VA_Submit_Ballot',
                                                                                 ~ec,
                                                                                 pseudonym($V),
                                                                                 pk(~sk_voter),
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
                                                                                sign(<
                                                                                      'VA_Submit_Ballot',
                                                                                      ~ec,
                                                                                      pseudonym($V),
                                                                                      pk(~sk_voter),
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
                                                                               h(<~ec, ~bbid>)>)
                                                                           >,
                                                                           sign(<'VA_Cast_Ballot',
                                                                                 ~ec,
                                                                                 pseudonym($V),
                                                                                 pk(~sk_voter),
                                                                                 h(<
                                                                                    <
                                                                                     'BBEntry_Ballot_Submission',
                                                                                     ~ec, %ts_sub,
                                                                                     <
                                                                                      'VA_Submit_Ballot',
                                                                                      ~ec,
                                                                                      pseudonym($V),
                                                                                      pk(~sk_voter),
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
                                                                                     sign(<
                                                                                           'VA_Submit_Ballot',
                                                                                           ~ec,
                                                                                           pseudonym($V),
                                                                                           pk(~sk_voter),
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
                                                                                          '1',
                                                                                          ~sk_voter)
                                                                                    >,
                                                                                    h(<~ec, ~bbid>)
                                                                                   >)
                                                                                >,
                                                                                '1', ~sk_voter)
                                                                          >
                                                           ) ▶₃ #vr.13 )
                                                      case SecureChannel_Receive_case_1
                                                      solve( SecureReceive( ~cid.2, ~va_id.1,
                                                                            <~ec, 'DBB'>,
                                                                            <
                                                                             <'VA_Cast_Ballot',
                                                                              ~ec, pseudonym($V),
                                                                              pk(~sk_voter),
                                                                              h(<
                                                                                 <
                                                                                  'BBEntry_Ballot_Submission',
                                                                                  ~ec, %ts_sub,
                                                                                  <
                                                                                   'VA_Submit_Ballot',
                                                                                   ~ec,
                                                                                   pseudonym($V),
                                                                                   pk(~sk_voter),
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
                                                                                  sign(<
                                                                                        'VA_Submit_Ballot',
                                                                                        ~ec,
                                                                                        pseudonym($V),
                                                                                        pk(~sk_voter),
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
                                                                                       ~ec,
                                                                                       %ts_sub,
                                                                                       <
                                                                                        'VA_Submit_Ballot',
                                                                                        ~ec,
                                                                                        pseudonym($V),
                                                                                        pk(~sk_voter),
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
                                                                                       sign(<
                                                                                             'VA_Submit_Ballot',
                                                                                             ~ec,
                                                                                             pseudonym($V),
                                                                                             pk(~sk_voter),
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
                                                                                            '1',
                                                                                            ~sk_voter)
                                                                                      >,
                                                                                      h(<~ec, ~bbid
                                                                                        >)
                                                                                     >)
                                                                                  >,
                                                                                  x, ~sk_voter)
                                                                            >
                                                             ) ▶₃ #vr.22 )
                                                        case SecureChannel_Receive_case_1
                                                        solve( BallotStyleCount( ~ec, %idx_bs_unused
                                                               ) ▶₀ #vr.2 )
                                                          case Mock_BallotStyle
                                                          solve( VoterCount( ~ec, %idx_ev_unused
                                                                 ) ▶₀ #vr.3 )
                                                            case Mock_EC_And_Initial_Counters
                                                            solve( BallotStyleCount( ~ec, %unused
                                                                   ) ▶₀ #vr.6 )
                                                              case Mock_BallotStyle
                                                              solve( BallotStyleCount( ~ec, %unused
                                                                     ) ▶₀ #vr.7 )
                                                                case Mock_BallotStyle
                                                                solve( DBB_State_ReceiveAuthorizeVoter( ~ec,
                                                                                                        (
                                                                                                         %1%+
                                                                                                         %1
                                                                                                        )
                                                                       ) ▶₀ #vr.14 )
                                                                  case Mock_Voter_Authentication
                                                                  solve( BallotStyleCount( ~ec,
                                                                                           %idx_bs
                                                                         ) ▶₀ #vr.15 )
                                                                    case Mock_BallotStyle
                                                                    solve( VoterCount( ~ec, %idx_ev
                                                                           ) ▶₀ #vr.16 )
                                                                      case Mock_EC_And_Initial_Counters
                                                                      solve( DBB_Clock( %ts_sub
                                                                             ) ▶₂ #vr.17 )
                                                                        case BallotCast_DBB_AppendCastBallot
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
                                                                        solve( DBB_State_ReceiveAuthorizeVoter( ~ec,
                                                                                                                %1
                                                                               ) ▶₀ #vr.25 )
                                                                          case Mock_Finalize_Election_Setup
                                                                          solve( VoterCount( ~ec,
                                                                                             %i.3
                                                                                 ) ▶₀ #vr.5 )
                                                                            case Mock_EC_And_Initial_Counters
                                                                            solve( VoterCount( ~ec,
                                                                                               %idx_ev
                                                                                   ) ▶₀ #vr.24 )
                                                                              case Mock_EC_And_Initial_Counters
                                                                              solve( BallotStyleCount( ~ec,
                                                                                                       %i.3
                                                                                     ) ▶₀ #vr.21 )
                                                                                case Mock_BallotStyle
                                                                                solve( BallotStyleCount( ~ec,
                                                                                                         %i.2
                                                                                       ) ▶₀ #vr.4 )
                                                                                  case Mock_BallotStyle
                                                                                  solve( BallotStyleCount( ~ec,
                                                                                                           %i.1
                                                                                         ) ▶₀ #vr.19 )
                                                                                    case Mock_BallotStyle
                                                                                    by sorry
                                                                                  next
                                                                                    case Mock_EC_And_Initial_Counters
                                                                                    solve( BallotStyleCount( ~ec,
                                                                                                             %i.2
                                                                                           ) ▶₀ #vr.24 )
                                                                                      case Mock_BallotStyle
                                                                                      by sorry
                                                                                    next
                                                                                      case Mock_EC_And_Initial_Counters
                                                                                      solve( DBB_Clock( %ts
                                                                                             ) ▶₂ #vr.10 )
                                                                                        case BallotCast_DBB_AppendCastBallot
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
                                                                                                                 %i.1
                                                                                               ) ▶₀ #vr.23 )
                                                                                          case Mock_BallotStyle
                                                                                          solve( BallotStyleCount( ~ec,
                                                                                                                   %i.1
                                                                                                 ) ▶₀ #vr.25 )
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
                                                                              case Mock_VoterRegistration_Eligible
                                                                              by sorry
                                                                            qed
                                                                          next
                                                                            case Mock_VoterRegistration_Eligible
                                                                            by sorry
                                                                          qed
                                                                        qed
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
                        case case_2
                        by sorry
                      qed
                    next
                      case case_2
                      by sorry
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
      case SecureChannel_Receive_case_3
      by sorry
    qed
  qed
next
  case BulletinBoard_Create
  by sorry
qed
