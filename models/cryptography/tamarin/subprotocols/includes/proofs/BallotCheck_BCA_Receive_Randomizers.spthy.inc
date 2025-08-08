simplify
solve( SecureReceive( ~cid, <~ec, 'DBB'>, ~bca_id,
                      <'DBB_Check_Randomizers', ~ec,
                       <'VA_Check_Randomizers',
                        <
                         <'BCA_Check_Request', ~ec, t, pk(~sk_bca_encrypt), pk(~sk_bca_sign)
                         >,
                         sign(<'BCA_Check_Request', ~ec, t, pk(~sk_bca_encrypt),
                               pk(~sk_bca_sign)>,
                              '1', ~sk_bca_sign)
                        >,
                        <ny_encrypt_c1(x, x.1, x.2), ny_encrypt_c2(x, x.1, x.2),
                         ny_encrypt_p(x, x.1, x.2)>,
                        pk_voter>,
                       sig_randomizers>
       ) ▶₂ #i )
  case SecureChannel_Receive_case_01
  solve( BCA_State_AwaitRandomizers( ~ec,
                                     h(<
                                        <'BBEntry_Ballot_Submission', ~ec, %ts,
                                         <'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter),
                                          ~bs_unused, ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
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
                                     ~bca_id, ~cid, ~sk_bca_encrypt, ~sk_bca_sign,
                                     <'BBEntry_Ballot_Submission', ~ec, timestamp,
                                      <'VA_Submit_Ballot', ~ec, pseudo, pk(~sk_voter.1),
                                       ~ballot_style, ny_encrypt_c1(~ballot.1, pk_election, ~r),
                                       ny_encrypt_c2(~ballot.1, pk_election, ~r),
                                       ny_encrypt_p(~ballot.1, pk_election, ~r)>,
                                      sig_msg_submit_ballot>
         ) ▶₀ #i )
    case BallotCheck_BCA_InitiateBallotCheck
    solve( BB_Append_Request( ~bbid,
                              <'BBEntry_Ballot_Submission', ~ec, %ts,
                               <'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter),
                                ~ballot_style, ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                               sign(<'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter),
                                     ~ballot_style, ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                     ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                     ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                    '1', ~sk_voter)
                              >,
                              %1
           )[+] ▶₂ #vr.5 )
      case Mock_AppendSubmittedBallot
      solve( SecureReceive( ~cid_va, ~va_id, <~ec, 'DBB'>,
                            <
                             <'VA_Check_Randomizers',
                              <
                               <'BCA_Check_Request', ~ec,
                                h(<
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
                                         '1', ~sk_voter)
                                   >,
                                   h(<~ec, ~bbid>)>),
                                pk(~sk_bca_encrypt), pk(~sk_bca_sign)>,
                               sign(<'BCA_Check_Request', ~ec,
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
                                              '1', ~sk_voter)
                                        >,
                                        h(<~ec, ~bbid>)>),
                                     pk(~sk_bca_encrypt), pk(~sk_bca_sign)>,
                                    '1', ~sk_bca_sign)
                              >,
                              <ny_encrypt_c1(~r, pk(~sk_bca_encrypt), ~throwaway_r),
                               ny_encrypt_c2(~r, pk(~sk_bca_encrypt), ~throwaway_r),
                               ny_encrypt_p(~r, pk(~sk_bca_encrypt), ~throwaway_r)>,
                              pk(~sk_voter)>,
                             sign(<'VA_Check_Randomizers',
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
                                              '1', ~sk_voter)
                                        >,
                                        h(<~ec, ~bbid>)>),
                                     pk(~sk_bca_encrypt), pk(~sk_bca_sign)>,
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
                                                   '1', ~sk_voter)
                                             >,
                                             h(<~ec, ~bbid>)>),
                                          pk(~sk_bca_encrypt), pk(~sk_bca_sign)>,
                                         '1', ~sk_bca_sign)
                                   >,
                                   <ny_encrypt_c1(~r, pk(~sk_bca_encrypt), ~throwaway_r),
                                    ny_encrypt_c2(~r, pk(~sk_bca_encrypt), ~throwaway_r),
                                    ny_encrypt_p(~r, pk(~sk_bca_encrypt), ~throwaway_r)>,
                                   pk(~sk_voter)>,
                                  '1', ~sk_voter)
                            >
             ) ▶₁ #vr.2 )
        case SecureChannel_Receive_case_1
        solve( SecureReceive( ~cid, ~bca_id, <~ec, 'DBB'>,
                              <
                               <'BCA_Check_Request', ~ec,
                                h(<
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
                                         '1', ~sk_voter)
                                   >,
                                   h(<~ec, ~bbid>)>),
                                pk(~sk_bca_encrypt), pk(~sk_bca_sign)>,
                               sign(<'BCA_Check_Request', ~ec,
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
                                              '1', ~sk_voter)
                                        >,
                                        h(<~ec, ~bbid>)>),
                                     pk(~sk_bca_encrypt), pk(~sk_bca_sign)>,
                                    '1', ~sk_bca_sign)
                              >
               ) ▶₃ #vr.3 )
          case SecureChannel_Receive_case_1
          solve( SecureReceive( ~cid_va, <~ec, 'DBB'>, ~va_id,
                                <'DBB_Check_Request',
                                 <'BCA_Check_Request', ~ec,
                                  h(<
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
                                           '1', ~sk_voter)
                                     >,
                                     h(<~ec, ~bbid>)>),
                                  pk(~sk_bca_encrypt), pk(~sk_bca_sign)>,
                                 sign(<'BCA_Check_Request', ~ec,
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
                                                '1', ~sk_voter)
                                          >,
                                          h(<~ec, ~bbid>)>),
                                       pk(~sk_bca_encrypt), pk(~sk_bca_sign)>,
                                      '1', ~sk_bca_sign)
                                >
                 ) ▶₃ #vr.19 )
            case SecureChannel_Receive_case_1
            solve( SecureReceive( ~cid, ~bca_id, <~ec, 'DBB'>,
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
                                             '1', ~sk_voter)
                                       >,
                                       h(<~ec, ~bbid>)>),
                                    pk(~sk_bca_encrypt), pk(~sk_bca_sign)>,
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
                                                  '1', ~sk_voter)
                                            >,
                                            h(<~ec, ~bbid>)>),
                                         pk(~sk_bca_encrypt), pk(~sk_bca_sign)>,
                                        '1', ~sk_bca_sign)
                                  >
                   ) ▶₃ #vr.24 )
              case SecureChannel_Receive_case_1
              solve( SecureReceive( ~cid, ~bca_id, <~ec, 'DBB'>,
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
                                               '1', ~sk_voter)
                                         >,
                                         h(<~ec, ~bbid>)>),
                                      pk(~sk_bca_encrypt), pk(~sk_bca_sign)>,
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
                                                    '1', ~sk_voter)
                                              >,
                                              h(<~ec, ~bbid>)>),
                                           pk(~sk_bca_encrypt), pk(~sk_bca_sign)>,
                                          '1', ~sk_bca_sign)
                                    >
                     ) ▶₃ #vr.26 )
                case SecureChannel_Receive_case_1
                solve( SecureReceive( ~cid, ~bca_id, <~ec, 'DBB'>,
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
                                                 '1', ~sk_voter)
                                           >,
                                           h(<~ec, ~bbid>)>),
                                        pk(~sk_bca_encrypt), pk(~sk_bca_sign)>,
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
                                                       ny_encrypt_c1(~ballot, pk(~sk_election),
                                                                     ~r),
                                                       ny_encrypt_c2(~ballot, pk(~sk_election),
                                                                     ~r),
                                                       ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                                      '1', ~sk_voter)
                                                >,
                                                h(<~ec, ~bbid>)>),
                                             pk(~sk_bca_encrypt), pk(~sk_bca_sign)>,
                                            '1', ~sk_bca_sign)
                                      >
                       ) ▶₃ #vr.27 )
                  case SecureChannel_Receive_case_1
                  solve( !ElectionPublicKey( ~ec, pk(~sk_election) ) ▶₁ #i )
                    case Mock_Finalize_Election_Setup
                    solve( BB_Trace_Entry( ~bbid, ~ec, h(<~ec, ~bbid>), %1 ) @ #vr.4 )
                      case BulletinBoard_Create
                      solve( BB_Current( ~bbid, c, h(<~ec, ~bbid>), %1 )[+] ▶₁ #vr.5 )
                        case BulletinBoard_Create
                        solve( DBB_State_ReceiveAuthorizeVoter( ~ec, %i.1 ) ▶₀ #vr.8 )
                          case Mock_Finalize_Election_Setup
                          solve( BallotStyleCount( ~ec, %idx_bs_unused ) ▶₀ #vr.9 )
                            case Mock_BallotStyle
                            solve( VoterCount( ~ec, %idx_ev_unused ) ▶₀ #vr.10 )
                              case Mock_EC_And_Initial_Counters
                              solve( VoterCount( ~ec, %i.3 ) ▶₀ #vr.12 )
                                case Mock_EC_And_Initial_Counters
                                solve( VoterCount( ~ec, %idx_ev ) ▶₀ #vr.13 )
                                  case Mock_EC_And_Initial_Counters
                                  solve( DBB_Clock( %ts ) ▶₂ #vr.20 )
                                    case Mock_DBBTimestamp
                                    solve( BallotStyleCount( ~ec, %idx_bs ) ▶₀ #vr.12 )
                                      case Mock_BallotStyle
                                      solve( BallotStyleCount( ~ec, %i.3 ) ▶₀ #vr.24 )
                                        case Mock_EC_And_Initial_Counters
                                        solve( BallotStyleCount( ~ec, %i.2 ) ▶₀ #vr.11 )
                                          case Mock_BallotStyle
                                          solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.21 )
                                            case Mock_EC_And_Initial_Counters
                                            solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.23 )
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
