simplify
solve( SecureReceive( ~cid_va, ~va_id, <~ec, 'DBB'>,
                      <
                       <'VA_Check_Randomizers',
                        <<'BCA_Check_Request', ~ec, tracker, pk_bca_encrypt, pk_bca_sign>,
                         sig_bca_req>,
                        encrypted_randomizers, pk_voter>,
                       sig_randomizers>
       ) ▶₁ #i )
  case SecureChannel_Receive_case_01
  solve( DBB_State_ForwardRandomizers( ~ec, ~va_id, ~cid_va, ~bca_id,
                                       ~cid_bca,
                                       <
                                        <'BCA_Check_Request', ~ec,
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
                                                  '1', ~z)
                                            >,
                                            h(<~ec, ~bbid>)>),
                                         pk(~sk_bca_encrypt), pk(~z.1)>,
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
                                                        ny_encrypt_p(~ballot, pk(~sk_election), ~r)
                                                       >,
                                                       '1', ~z)
                                                 >,
                                                 h(<~ec, ~bbid>)>),
                                              pk(~sk_bca_encrypt), pk(~z.1)>,
                                             '1', ~z.1)
                                       >
         ) ▶₀ #i )
    case BallotCheck_DBB_ReceiveCheckRequest_case_1
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
                                      ~ballot_style, ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                      ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                      ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                     '1', ~z)
                               >,
                               h(<~ec, ~bbid>)>),
                            pk(~sk_bca_encrypt), pk(~z.1)>,
                           sign(<'BCA_Check_Request', ~ec,
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
                                          '1', ~z)
                                    >,
                                    h(<~ec, ~bbid>)>),
                                 pk(~sk_bca_encrypt), pk(~z.1)>,
                                '1', ~z.1)
                          >
           ) ▶₃ #vr.2 )
      case SecureChannel_Receive_case_1
      solve( SecureReceive( ~cid_bca, ~bca_id, <~ec, 'DBB'>,
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
                                       '1', ~z)
                                 >,
                                 h(<~ec, ~bbid>)>),
                              pk(~sk_bca_encrypt), pk(~z.1)>,
                             sign(<'BCA_Check_Request', ~ec,
                                   h(<
                                      <'BBEntry_Ballot_Submission', ~ec, %ts,
                                       <'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter),
                                        ~ballot_style,
                                        ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                        ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                        ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                       sign(<'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter),
                                             ~ballot_style,
                                             ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                             ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                             ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                            '1', ~z)
                                      >,
                                      h(<~ec, ~bbid>)>),
                                   pk(~sk_bca_encrypt), pk(~z.1)>,
                                  '1', ~z.1)
                            >
             ) ▶₃ #vr.21 )
        case SecureChannel_Receive_case_1
        solve( SecureReceive( ~cid_bca, ~bca_id, <~ec, 'DBB'>,
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
                                         '1', ~z)
                                   >,
                                   h(<~ec, ~bbid>)>),
                                pk(~sk_bca_encrypt), pk(~z.1)>,
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
                                              '1', ~z)
                                        >,
                                        h(<~ec, ~bbid>)>),
                                     pk(~sk_bca_encrypt), pk(~z.1)>,
                                    '1', ~z.1)
                              >
               ) ▶₃ #vr.24 )
          case SecureChannel_Receive_case_1
          solve( SecureReceive( ~cid_bca, ~bca_id, <~ec, 'DBB'>,
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
                                           '1', ~z)
                                     >,
                                     h(<~ec, ~bbid>)>),
                                  pk(~sk_bca_encrypt), pk(~z.1)>,
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
                                                '1', ~z)
                                          >,
                                          h(<~ec, ~bbid>)>),
                                       pk(~sk_bca_encrypt), pk(~z.1)>,
                                      '1', ~z.1)
                                >
                 ) ▶₃ #vr.26 )
            case SecureChannel_Receive_case_1
            solve( BB_Append_Request( ~bbid,
                                      <'BBEntry_Ballot_Submission', ~ec, %ts,
                                       <'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter),
                                        ~ballot_style,
                                        ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                        ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                        ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                       sign(<'VA_Submit_Ballot', ~ec, pseudonym($V), pk(~sk_voter),
                                             ~ballot_style,
                                             ny_encrypt_c1(~ballot, pk(~sk_election), ~r),
                                             ny_encrypt_c2(~ballot, pk(~sk_election), ~r),
                                             ny_encrypt_p(~ballot, pk(~sk_election), ~r)>,
                                            '1', ~z)
                                      >,
                                      %1
                   )[+] ▶₂ #vr.12 )
              case Mock_AppendSubmittedBallot
              solve( BB_Trace_Entry( ~bbid, ~ec, h(<~ec, ~bbid>), %1 ) @ #vr.11 )
                case BulletinBoard_Create
                solve( BB_Current( ~bbid, c, h(<~ec, ~bbid>), %1 )[+] ▶₁ #vr.12 )
                  case BulletinBoard_Create
                  solve( DBB_State_ReceiveAuthorizeVoter( ~ec, %i.1 ) ▶₀ #vr.4 )
                    case Mock_Finalize_Election_Setup
                    solve( BallotStyleCount( ~ec, %idx_bs ) ▶₀ #vr.6 )
                      case Mock_BallotStyle
                      solve( VoterCount( ~ec, %idx_ev ) ▶₀ #vr.7 )
                        case Mock_EC_And_Initial_Counters
                        solve( BallotStyleCount( ~ec, %idx_bs_unused ) ▶₀ #vr.13 )
                          case Mock_BallotStyle
                          solve( VoterCount( ~ec, %idx_ev_unused ) ▶₀ #vr.14 )
                            case Mock_EC_And_Initial_Counters
                            solve( DBB_State_ReceiveAuthorizeVoter( ~ec, %i.5 ) ▶₀ #vr.16 )
                              case Mock_Finalize_Election_Setup
                              solve( VoterCount( ~ec, %i.4 ) ▶₀ #vr.15 )
                                case Mock_EC_And_Initial_Counters
                                solve( DBB_Clock( %ts ) ▶₂ #vr.9 )
                                  case Mock_AppendSubmittedBallot_case_1
                                  by sorry
                                next
                                  case Mock_AppendSubmittedBallot_case_2
                                  by sorry
                                next
                                  case Mock_DBBTimestamp
                                  solve( BallotStyleCount( ~ec, %i.3 ) ▶₀ #vr.14 )
                                    case Mock_BallotStyle
                                    solve( BallotStyleCount( ~ec, %i.2 ) ▶₀ #vr.21 )
                                      case Mock_BallotStyle
                                      by sorry
                                    next
                                      case Mock_EC_And_Initial_Counters
                                      solve( BallotStyleCount( ~ec, %i.2 ) ▶₀ #vr.23 )
                                        case Mock_BallotStyle
                                        by sorry
                                      next
                                        case Mock_EC_And_Initial_Counters
                                        solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.18 )
                                          case Mock_BallotStyle
                                          simplify
                                          by contradiction /* cyclic */
                                        next
                                          case Mock_EC_And_Initial_Counters
                                          SOLVED // trace found
                                        qed
                                      qed
                                    qed
                                  next
                                    case Mock_EC_And_Initial_Counters
                                    simplify
                                    by contradiction /* cyclic */
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
    next
      case SecureChannel_Receive_case_3
      by sorry
    qed
  next
    case BallotCheck_DBB_ReceiveCheckRequest_case_2
    by sorry
  qed
next
  case SecureChannel_Receive_case_02
  by sorry
next
  case SecureChannel_Receive_case_03
  by sorry
next
  case SecureChannel_Receive_case_04
  by sorry
next
  case SecureChannel_Receive_case_05
  by sorry
next
  case SecureChannel_Receive_case_06
  by sorry
next
  case SecureChannel_Receive_case_07
  by sorry
next
  case SecureChannel_Receive_case_08
  by sorry
next
  case SecureChannel_Receive_case_09
  by sorry
next
  case SecureChannel_Receive_case_10
  by sorry
next
  case SecureChannel_Receive_case_11
  by sorry
next
  case SecureChannel_Receive_case_12
  by sorry
next
  case SecureChannel_Receive_case_13
  by sorry
next
  case SecureChannel_Receive_case_14
  by sorry
qed
