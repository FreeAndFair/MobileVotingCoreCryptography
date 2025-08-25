simplify
solve( !BB_Root( ~ec, ~bbid, r_unused, rh_unused ) ▶₁ #i )
  case BulletinBoard_Create
  solve( !BB_Entry( ~bbid, bbe_a, auth_tracker_unused, %idx_a
         ) ▶₂ #i )
    case BulletinBoard_Append
    solve( !BB_Entry( ~bbid, bbe_c, cast_tracker, (%idx%+%1%+%1)
           ) ▶₃ #i )
      case BulletinBoard_Append
      solve( DBB_State_ConfirmCastPosting( ~ec, ~va_id, ~cid, pseudo,
                                           sub_tracker, bbe_a, bbe_c, (%idx%+%1)
             ) ▶₀ #i )
        case BallotCast_DBB_AppendCastBallot_case_1
        solve( (¬(%1 ⊏ %idx))  ∥ (#j < #j.1) )
          case case_2
          solve( (¬((%1%+%1) ⊏ (%idx%+%1)))  ∥ (#vr.7 < #vr.12) )
            case case_2
            solve( (¬((%1%+%1) ⊏ %idx))  ∥ (#vr.7 < #j.1) )
              case case_1
              solve( (¬((%idx%+%1) ⊏ (%1%+%1%+%1)))  ∥ (#vr.12 < #vr.8) )
                case case_2
                solve( (¬(%idx ⊏ (%1%+%1)))  ∥ (#j.1 < #vr.7) )
                  case case_2
                  solve( BB_Trace_Entry( ~bbid, ~ec, h(<~ec, ~bbid>), %1 ) @ #j )
                    case BulletinBoard_Create
                    solve( BB_Trace_Entry( ~bbid,
                                           <'BBEntry_Voter_Authorization', ~ec, %ts,
                                            <'EAS_Authorize_Voter', ~ec, pseudonym($V),
                                             pk(~sk_voter), ~bs>,
                                            sign(<'EAS_Authorize_Voter', ~ec, pseudonym($V),
                                                  pk(~sk_voter), ~bs>,
                                                 '1', ~sk_eas)
                                           >,
                                           h(<
                                              <'BBEntry_Voter_Authorization', ~ec, %ts,
                                               <'EAS_Authorize_Voter', ~ec, pseudonym($V),
                                                pk(~sk_voter), ~bs>,
                                               sign(<'EAS_Authorize_Voter', ~ec, pseudonym($V),
                                                     pk(~sk_voter), ~bs>,
                                                    '1', ~sk_eas)
                                              >,
                                              h(<~ec, ~bbid>)>),
                                           (%1%+%1)
                           ) @ #vr.7 )
                      case BulletinBoard_Append
                      solve( BB_Trace_Entry( ~bbid,
                                             <'BBEntry_Ballot_Submission', ~ec, %ts_sub,
                                              <'VA_Submit_Ballot', ~ec, pseudonym($V),
                                               pk(~sk_voter), ~bs, cryptograms>,
                                              sig_submit>,
                                             h(<
                                                <'BBEntry_Ballot_Submission', ~ec, %ts_sub,
                                                 <'VA_Submit_Ballot', ~ec, pseudonym($V),
                                                  pk(~sk_voter), ~bs, cryptograms>,
                                                 sig_submit>,
                                                ch>),
                                             (%idx%+%1)
                             ) @ #vr.12 )
                        case BulletinBoard_Append
                        by solve( BB_Trace_Entry( ~bbid, p, ch, %idx ) @ #j.1 )
                      qed
                    qed
                  qed
                qed
              qed
            next
              case case_2
              solve( (¬(%idx ⊏ (%1%+%1%+%1)))  ∥ (#j.1 < #vr.8) )
                case case_1
                solve( (¬((%1%+%1%+%1) ⊏ %idx))  ∥ (#vr.8 < #j.1) )
                  case case_2
                  solve( BB_Trace_Entry( ~bbid, ~ec, h(<~ec, ~bbid>), %1 ) @ #j )
                    case BulletinBoard_Create
                    solve( BB_Trace_Entry( ~bbid,
                                           <'BBEntry_Voter_Authorization', ~ec, %ts,
                                            <'EAS_Authorize_Voter', ~ec, pseudonym($V),
                                             pk(~sk_voter), ~bs>,
                                            sign(<'EAS_Authorize_Voter', ~ec, pseudonym($V),
                                                  pk(~sk_voter), ~bs>,
                                                 '1', ~sk_eas)
                                           >,
                                           h(<
                                              <'BBEntry_Voter_Authorization', ~ec, %ts,
                                               <'EAS_Authorize_Voter', ~ec, pseudonym($V),
                                                pk(~sk_voter), ~bs>,
                                               sign(<'EAS_Authorize_Voter', ~ec, pseudonym($V),
                                                     pk(~sk_voter), ~bs>,
                                                    '1', ~sk_eas)
                                              >,
                                              h(<~ec, ~bbid>)>),
                                           (%1%+%1)
                           ) @ #vr.7 )
                      case BulletinBoard_Append
                      solve( BB_Trace_Entry( ~bbid,
                                             <'BBEntry_Ballot_Submission', ~ec, %ts_sub,
                                              <'VA_Submit_Ballot', ~ec, pseudonym($V),
                                               pk(~sk_voter), ~bs, cryptograms>,
                                              sig_submit>,
                                             h(<
                                                <'BBEntry_Ballot_Submission', ~ec, %ts_sub,
                                                 <'VA_Submit_Ballot', ~ec, pseudonym($V),
                                                  pk(~sk_voter), ~bs, cryptograms>,
                                                 sig_submit>,
                                                ch>),
                                             (%idx%+%1)
                             ) @ #vr.12 )
                        case BulletinBoard_Append
                        solve( BB_Trace_Entry( ~bbid, p, ch, %idx ) @ #j.1 )
                          case BulletinBoard_Append
                          by solve( BB_Append_Request( ~bbid,
                                                       <'BBEntry_Voter_Authorization', ~ec, %ts,
                                                        <'EAS_Authorize_Voter', ~ec, pseudonym($V),
                                                         pk(~sk_voter), ~bs>,
                                                        sign(<'EAS_Authorize_Voter', ~ec,
                                                              pseudonym($V), pk(~sk_voter), ~bs>,
                                                             '1', ~sk_eas)
                                                       >,
                                                       %1
                                    )[+] ▶₂ #vr.7 )
                        qed
                      qed
                    qed
                  qed
                qed
              next
                case case_2
                solve( BB_Trace_Entry( ~bbid,
                                       <'BBEntry_Voter_Authorization', ~ec, %ts,
                                        <'EAS_Authorize_Voter', ~ec, pseudonym($V), pk(~sk_voter),
                                         ~bs>,
                                        sign(<'EAS_Authorize_Voter', ~ec, pseudonym($V),
                                              pk(~sk_voter), ~bs>,
                                             '1', ~sk_eas)
                                       >,
                                       h(<
                                          <'BBEntry_Voter_Authorization', ~ec, %ts,
                                           <'EAS_Authorize_Voter', ~ec, pseudonym($V),
                                            pk(~sk_voter), ~bs>,
                                           sign(<'EAS_Authorize_Voter', ~ec, pseudonym($V),
                                                 pk(~sk_voter), ~bs>,
                                                '1', ~sk_eas)
                                          >,
                                          h(<~ec, ~bbid>)>),
                                       (%1%+%1)
                       ) @ #vr.7 )
                  case BulletinBoard_Append
                  solve( BB_Trace_Entry( ~bbid,
                                         <'BBEntry_Ballot_Submission', ~ec, %ts_sub,
                                          <'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter),
                                           ~bs, cryptograms>,
                                          sig_submit>,
                                         h(<
                                            <'BBEntry_Ballot_Submission', ~ec, %ts_sub,
                                             <'VA_Submit_Ballot', ~ec, pseudonym($V),
                                              pk(~sk_voter), ~bs, cryptograms>,
                                             sig_submit>,
                                            ch>),
                                         (%idx%+%1)
                         ) @ #vr.12 )
                    case BulletinBoard_Append
                    by solve( BB_Append_Request( ~bbid,
                                                 <'BBEntry_Voter_Authorization', ~ec, %ts,
                                                  <'EAS_Authorize_Voter', ~ec, pseudonym($V),
                                                   pk(~sk_voter), ~bs>,
                                                  sign(<'EAS_Authorize_Voter', ~ec, pseudonym($V),
                                                        pk(~sk_voter), ~bs>,
                                                       '1', ~sk_eas)
                                                 >,
                                                 %1
                              )[+] ▶₂ #vr.7 )
                  qed
                qed
              qed
            qed
          qed
        qed
      next
        case BallotCast_DBB_AppendCastBallot_case_2
        solve( BB_Trace_Entry( ~bbid,
                               <'BBEntry_Voter_Authorization', ~ec, %ts,
                                <'EAS_Authorize_Voter', ~ec, pseudonym($V), pk(~sk_voter), ~bs>,
                                sign(<'EAS_Authorize_Voter', ~ec, pseudonym($V), pk(~sk_voter), ~bs
                                     >,
                                     '1', ~sk_eas)
                               >,
                               h(<
                                  <'BBEntry_Voter_Authorization', ~ec, %ts,
                                   <'EAS_Authorize_Voter', ~ec, pseudonym($V), pk(~sk_voter), ~bs>,
                                   sign(<'EAS_Authorize_Voter', ~ec, pseudonym($V), pk(~sk_voter),
                                         ~bs>,
                                        '1', ~sk_eas)
                                  >,
                                  h(<p, ch.1>)>),
                               (%idx%+%1%+%1)
               ) @ #vr.8 )
          case BulletinBoard_Append
          solve( BB_Trace_Entry( ~bbid,
                                 <'BBEntry_Ballot_Submission', ~ec, %ts_sub,
                                  <'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter), ~bs,
                                   cryptograms>,
                                  sig_submit>,
                                 h(<
                                    <'BBEntry_Ballot_Submission', ~ec, %ts_sub,
                                     <'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter), ~bs,
                                      cryptograms>,
                                     sig_submit>,
                                    ch>),
                                 (%idx.1%+%1)
                 ) @ #vr.13 )
            case BulletinBoard_Append
            solve( BB_Append_Request( ~bbid,
                                      <'BBEntry_Voter_Authorization', ~ec, %ts,
                                       <'EAS_Authorize_Voter', ~ec, pseudonym($V), pk(~sk_voter),
                                        ~bs>,
                                       sign(<'EAS_Authorize_Voter', ~ec, pseudonym($V),
                                             pk(~sk_voter), ~bs>,
                                            '1', ~sk_eas)
                                      >,
                                      (%idx%+%1)
                   )[+] ▶₂ #vr.8 )
              case BallotCast_DBB_AppendCastBallot
              simplify
              solve( BB_Append_Request( ~bbid,
                                        <'BBEntry_Ballot_Submission', ~ec, %ts_sub.1,
                                         <'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter),
                                          ~bs, cryptograms.1>,
                                         sig_submit.1>,
                                        %idx.2
                     )[+] ▶₂ #vr.18 )
                case Mock_AppendSubmittedBallot_case_1
                simplify
                solve( SecureReceive( ~cid.2, ~va_id.3, <~ec, 'DBB'>,
                                      <
                                       <'VA_Cast_Ballot', ~ec, pseudonym($V), pk(~sk_voter),
                                        h(<
                                           <'BBEntry_Ballot_Submission', ~ec, %ts_sub.1,
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
                                       sign(<'VA_Cast_Ballot', ~ec, pseudonym($V), pk(~sk_voter),
                                             h(<
                                                <'BBEntry_Ballot_Submission', ~ec, %ts_sub.1,
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
                                                       ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                                      '1', ~sk_voter.1)
                                                >,
                                                h(<~ec, ~bbid>)>)
                                            >,
                                            x.1, ~sk_voter)
                                      >
                       ) ▶₃ #vr.17 )
                  case SecureChannel_Receive_case_1
                  solve( SecureReceive( ~cid, ~va_id, <~ec, 'DBB'>,
                                        <
                                         <'VA_Cast_Ballot', ~ec, pseudonym($V), pk(~sk_voter),
                                          h(<
                                             <'BBEntry_Ballot_Submission', ~ec, %ts_sub,
                                              <'VA_Submit_Ballot', ~ec, pseudonym($V),
                                               pk(~sk_voter), ~bs, cryptograms>,
                                              sig_submit>,
                                             ch>)
                                         >,
                                         sign(<'VA_Cast_Ballot', ~ec, pseudonym($V), pk(~sk_voter),
                                               h(<
                                                  <'BBEntry_Ballot_Submission', ~ec, %ts_sub,
                                                   <'VA_Submit_Ballot', ~ec, pseudonym($V),
                                                    pk(~sk_voter), ~bs, cryptograms>,
                                                   sig_submit>,
                                                  ch>)
                                              >,
                                              x, ~sk_voter)
                                        >
                         ) ▶₃ #vr.11 )
                    case SecureChannel_Receive_case_1
                    solve( (¬((%1%+%1) ⊏ (%idx%+%1)))  ∥ (#vr.13 < #j) )
                      case case_1
                      solve( BB_Current( ~bbid, c.1,
                                         h(<
                                            <'BBEntry_Ballot_Submission', ~ec, %ts_sub,
                                             <'VA_Submit_Ballot', ~ec, pseudonym($V),
                                              pk(~sk_voter), ~bs,
                                              ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                              ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                              ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                             sign(<'VA_Submit_Ballot', ~ec, pseudonym($V),
                                                   pk(~sk_voter), ~bs,
                                                   ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                                   ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                                   ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                                  '1', ~sk_voter)
                                            >,
                                            h(<~ec, ~bbid>)>),
                                         (%1%+%1)
                             )[+] ▶₁ #vr.8 )
                        case BulletinBoard_Append
                        solve( BB_Trace_Entry( ~bbid, ~ec, h(<~ec, ~bbid>), %1 ) @ #vr )
                          case BulletinBoard_Create
                          solve( BB_Current( ~bbid, c, h(<~ec, ~bbid>), %1 )[+] ▶₁ #j )
                            case BulletinBoard_Create
                            solve( BallotStyleCount( ~ec, %idx_bs_unused ) ▶₀ #vr.2 )
                              case Mock_BallotStyle
                              solve( VoterCount( ~ec, %idx_ev_unused ) ▶₀ #vr.3 )
                                case Mock_EC_And_Initial_Counters
                                solve( BallotStyleCount( ~ec, %unused ) ▶₀ #vr.6 )
                                  case Mock_BallotStyle
                                  solve( DBB_Clock( %ts ) ▶₂ #vr.10 )
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
                                    solve( DBB_State_ReceiveAuthorizeVoter( ~ec, (%1%+%1)
                                           ) ▶₀ #vr.12 )
                                      case Mock_Voter_Authentication
                                      solve( DBB_State_ReceiveAuthorizeVoter( ~ec, %1 ) ▶₀ #vr.25 )
                                        case Mock_Finalize_Election_Setup
                                        solve( BallotStyleCount( ~ec, %idx_bs ) ▶₀ #vr.13 )
                                          case Mock_BallotStyle
                                          solve( VoterCount( ~ec, %idx_ev ) ▶₀ #vr.14 )
                                            case Mock_EC_And_Initial_Counters
                                            solve( BallotStyleCount( ~ec, %idx_bs ) ▶₀ #vr.24 )
                                              case Mock_BallotStyle
                                              solve( VoterCount( ~ec, %idx_ev ) ▶₀ #vr.25 )
                                                case Mock_EC_And_Initial_Counters
                                                solve( BallotStyleCount( ~ec, %i.4 ) ▶₀ #vr.21 )
                                                  case Mock_BallotStyle
                                                  by sorry
                                                next
                                                  case Mock_EC_And_Initial_Counters
                                                  solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.19 )
                                                    case Mock_BallotStyle
                                                    by sorry
                                                  next
                                                    case Mock_EC_And_Initial_Counters
                                                    solve( BallotStyleCount( ~ec, %unused
                                                           ) ▶₀ #vr.6 )
                                                      case Mock_BallotStyle
                                                      by sorry
                                                    next
                                                      case Mock_EC_And_Initial_Counters
                                                      simplify
                                                      solve( BallotStyleCount( ~ec, %i.1
                                                             ) ▶₀ #vr.4 )
                                                        case Mock_BallotStyle
                                                        solve( VoterCount( ~ec, %i.2 ) ▶₀ #vr.5 )
                                                          case Mock_VoterRegistration_Eligible
                                                          solve( BallotStyleCount( ~ec, %unused
                                                                 ) ▶₀ #vr.23 )
                                                            case Mock_BallotStyle
                                                            by sorry
                                                          next
                                                            case Mock_EC_And_Initial_Counters
                                                            simplify
                                                            solve( DBB_Clock( %ts_sub ) ▶₂ #vr.12 )
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
                                                              solve( BB_Current( ~bbid, c,
                                                                                 h(<
                                                                                    <
                                                                                     'BBEntry_Voter_Authorization',
                                                                                     ~ec, %1,
                                                                                     <
                                                                                      'EAS_Authorize_Voter',
                                                                                      ~ec,
                                                                                      pseudonym($EV),
                                                                                      pk(~sk_voter),
                                                                                      ~bs>,
                                                                                     sign(<
                                                                                           'EAS_Authorize_Voter',
                                                                                           ~ec,
                                                                                           pseudonym($EV),
                                                                                           pk(~sk_voter),
                                                                                           ~bs>,
                                                                                          '1',
                                                                                          ~sk_eas)
                                                                                    >,
                                                                                    h(<
                                                                                       <
                                                                                        'BBEntry_Ballot_Submission',
                                                                                        ~ec, %1,
                                                                                        <
                                                                                         'VA_Submit_Ballot',
                                                                                         ~ec,
                                                                                         pseudonym($EV),
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
                                                                                              pseudonym($EV),
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
                                                                                   >),
                                                                                 (%1%+%1%+%1)
                                                                     )[+] ▶₁ #vr.8 )
                                                                case BulletinBoard_Append
                                                                solve( BB_Append_Request( ~bbid,
                                                                                          <
                                                                                           'BBEntry_Ballot_Cast',
                                                                                           (%1%+%1
                                                                                           ),
                                                                                           <
                                                                                            <
                                                                                             'VA_Submit_Ballot',
                                                                                             ~ec,
                                                                                             pseudonym($EV),
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
                                                                                                  pseudonym($EV),
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
                                                                                           <
                                                                                            'VA_Cast_Ballot',
                                                                                            ~ec,
                                                                                            pseudonym($EV),
                                                                                            pk(~sk_voter),
                                                                                            h(<
                                                                                               <
                                                                                                'BBEntry_Ballot_Submission',
                                                                                                ~ec,
                                                                                                %1,
                                                                                                <
                                                                                                 'VA_Submit_Ballot',
                                                                                                 ~ec,
                                                                                                 pseudonym($EV),
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
                                                                                                      pseudonym($EV),
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
                                                                                               h(<
                                                                                                  ~ec,
                                                                                                  ~bbid
                                                                                                 >)
                                                                                              >)
                                                                                           >,
                                                                                           sign(<
                                                                                                 'VA_Cast_Ballot',
                                                                                                 ~ec,
                                                                                                 pseudonym($EV),
                                                                                                 pk(~sk_voter),
                                                                                                 h(<
                                                                                                    <
                                                                                                     'BBEntry_Ballot_Submission',
                                                                                                     ~ec,
                                                                                                     %1,
                                                                                                     <
                                                                                                      'VA_Submit_Ballot',
                                                                                                      ~ec,
                                                                                                      pseudonym($EV),
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
                                                                                                           pseudonym($EV),
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
                                                                                                    h(<
                                                                                                       ~ec,
                                                                                                       ~bbid
                                                                                                      >)
                                                                                                   >)
                                                                                                >,
                                                                                                '1',
                                                                                                ~sk_voter)
                                                                                          >,
                                                                                          (%1%+%1%+
                                                                                           %1)
                                                                       )[+] ▶₂ #vr.8 )
                                                                  case BallotCast_DBB_AppendCastBallot
                                                                  solve( VoterCount( ~ec, %i.2
                                                                         ) ▶₀ #vr.22 )
                                                                    case Mock_VoterRegistration_Eligible
                                                                    solve( BallotStyleCount( ~ec,
                                                                                             %unused
                                                                           ) ▶₀ #vr.25 )
                                                                      case Mock_BallotStyle
                                                                      by sorry
                                                                    next
                                                                      case Mock_EC_And_Initial_Counters
                                                                      simplify
                                                                      solve( BallotStyleCount( ~ec,
                                                                                               %i.1
                                                                             ) ▶₀ #vr.21 )
                                                                        case Mock_BallotStyle
                                                                        by sorry
                                                                      next
                                                                        case Mock_EC_And_Initial_Counters
                                                                        solve( VoterCount( ~ec, %i.1
                                                                               ) ▶₀ #vr.22 )
                                                                          case Mock_VoterRegistration_Eligible
                                                                          solve( VoterCount( ~ec,
                                                                                             %i.1
                                                                                 ) ▶₀ #vr.23 )
                                                                            case Mock_EC_And_Initial_Counters
                                                                            SOLVED // trace found
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
                    next
                      case case_2
                      by sorry
                    qed
                  next
                    case SecureChannel_Receive_case_2
                    by contradiction /* cyclic */
                  next
                    case SecureChannel_Receive_case_3
                    by sorry
                  qed
                next
                  case SecureChannel_Receive_case_2
                  by sorry
                qed
              next
                case Mock_AppendSubmittedBallot_case_2
                simplify
                by sorry
              qed
            qed
          qed
        qed
      qed
    qed
  next
    case BulletinBoard_Create
    by sorry
  qed
qed
