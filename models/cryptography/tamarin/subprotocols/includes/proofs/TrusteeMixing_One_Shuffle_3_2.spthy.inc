simplify
solve( !Trustee_Mix_Active( t2 ) ▶₀ #j )
  case TrusteeMixing_TAS_Init_case_3
  solve( !Trustee_Mix_Active( t1 ) ▶₁ #j )
    case TrusteeMixing_TAS_Init_case_1
    solve( !Trustee_ElectionSetup( 'Trustee2', election_setup ) ▶₃ #j )
      case Mock_TrusteeElectionSetup
      solve( !Trustee_Secret_Keys( 'Trustee2', sk_sign, sk_encrypt_unused
             ) ▶₄ #j )
        case Mock_TrusteeElectionSetup
        solve( Trustee_Shuffle_Trace( 'Trustee1', o, s, p ) @ #i )
          case TrusteeMixing_Trustee_1_Shuffle
          solve( !Trustee_ElectionSetup( 'Trustee1', election_setup ) ▶₂ #i )
            case Mock_TrusteeElectionSetup
            solve( !Trustee_Secret_Keys( 'Trustee1', sk_sign, sk_encrypt_unused
                   ) ▶₃ #i )
              case Mock_TrusteeElectionSetup
              solve( !Trustee_BBEntry( 'Trustee2', 'Trustee1',
                                       <<'Trustee_EG_Cryptograms', 'Trustee1', 'Trustee1'>, ~election_setup,
                                        shuffle_order(prev_prev_ballot_order, ballot_set, prev_r),
                                        ballot_set, shuffle_proof(prev_prev_ballot_order, ballot_set, prev_r)
                                       >,
                                       sig_shuffled_ballots, %idx_shuffled_ballots
                     ) ▶₂ #j )
                case TrusteeBoard_Trustee_Update_case_10
                solve( TAS_Trustee_Trace( 'Trustee1', pk(~sk_sign_trustee1),
                                          pk(~sk_encrypt_trustee1)
                       ) @ #j.6 )
                  case Mock_TrusteeElectionSetup
                  solve( HonestSignatureKey( pk(~sk_sign_trustee1) ) @ #k )
                    case Mock_TrusteeElectionSetup
                    solve( TAS_Trustee_Trace( 'Trustee1', pk(~sk_sign_trustee1),
                                              pk(~sk_encrypt_trustee1)
                           ) @ #j.6 )
                      case Mock_TrusteeElectionSetup
                      solve( HonestSignatureKey( pk(~sk_sign_trustee1) ) @ #k.1 )
                        case Mock_TrusteeElectionSetup
                        solve( TAS_Trustee_Trace( 'Trustee2', pk(~sk_sign_trustee2),
                                                  pk(~sk_encrypt_trustee2)
                               ) @ #j.6 )
                          case Mock_TrusteeElectionSetup
                          solve( HonestSignatureKey( pk(~sk_sign_trustee2) ) @ #k.1 )
                            case Mock_TrusteeElectionSetup
                            solve( TAS_Trustee_Trace( 'Trustee0', pk(~sk_sign_tas),
                                                      pk(~sk_encrypt_unused)
                                   ) @ #j.6 )
                              case TrusteeMixing_TAS_Init
                              solve( HonestSignatureKey( pk(~sk_sign_tas) ) @ #k.1 )
                                case Mock_TrusteeElectionSetup
                                solve( Trustee_Sent_Msg_Trace( 'Trustee1',
                                                               <
                                                                <'Trustee_EG_Cryptograms', 'Trustee0',
                                                                 'Trustee1'>,
                                                                ~election_setup, ~ballot_order,
                                                                <
                                                                 ny_encrypt_c1(~ballots,
                                                                               threshold_pubkey(check_value(~private_share1),
                                                                                                check_value(~private_share2),
                                                                                                check_value(~private_share3)),
                                                                               ~r),
                                                                 ny_encrypt_c2(~ballots,
                                                                               threshold_pubkey(check_value(~private_share1),
                                                                                                check_value(~private_share2),
                                                                                                check_value(~private_share3)),
                                                                               ~r)
                                                                >,
                                                                'no shuffle'>
                                       ) @ #j.5 )
                                  case TrusteeMixing_Check_Encryption_Proofs_Success
                                  solve( !Trustee_BBEntry( 'Trustee1', 'Trustee1',
                                                           <
                                                            <'Trustee_EG_Cryptograms', 'Trustee0', 'Trustee1'
                                                            >,
                                                            ~election_setup, ~ballot_order,
                                                            <
                                                             ny_encrypt_c1(~ballots,
                                                                           threshold_pubkey(check_value(~private_share1),
                                                                                            check_value(~private_share2),
                                                                                            check_value(~private_share3)),
                                                                           ~r),
                                                             ny_encrypt_c2(~ballots,
                                                                           threshold_pubkey(check_value(~private_share1),
                                                                                            check_value(~private_share2),
                                                                                            check_value(~private_share3)),
                                                                           ~r)
                                                            >,
                                                            'no shuffle'>,
                                                           sign(<
                                                                 <'Trustee_EG_Cryptograms', 'Trustee0',
                                                                  'Trustee1'>,
                                                                 ~election_setup, ~ballot_order,
                                                                 <
                                                                  ny_encrypt_c1(~ballots,
                                                                                threshold_pubkey(check_value(~private_share1),
                                                                                                 check_value(~private_share2),
                                                                                                 check_value(~private_share3)),
                                                                                ~r),
                                                                  ny_encrypt_c2(~ballots,
                                                                                threshold_pubkey(check_value(~private_share1),
                                                                                                 check_value(~private_share2),
                                                                                                 check_value(~private_share3)),
                                                                                ~r)
                                                                 >,
                                                                 'no shuffle'>,
                                                                '1', ~sk_sign_trustee1),
                                                           %idx_signed_shuffle1
                                         ) ▶₀ #i )
                                    case TrusteeBoard_Trustee_Update
                                    solve( TAS_Trustee_Trace( 'Trustee0', pk(~sk_sign_tas),
                                                              pk(~sk_encrypt_unused)
                                           ) @ #j.6 )
                                      case TrusteeMixing_TAS_Init
                                      solve( HonestSignatureKey( pk(~sk_sign_tas) ) @ #k.1 )
                                        case Mock_TrusteeElectionSetup
                                        solve( !Trustee_BBEntry( 'Trustee1', 'Trustee2',
                                                                 <
                                                                  <'Trustee_EG_Cryptograms', 'Trustee0',
                                                                   'Trustee2'>,
                                                                  ~election_setup, ~ballot_order,
                                                                  <
                                                                   ny_encrypt_c1(~ballots,
                                                                                 threshold_pubkey(check_value(~private_share1),
                                                                                                  check_value(~private_share2),
                                                                                                  check_value(~private_share3)),
                                                                                 ~r),
                                                                   ny_encrypt_c2(~ballots,
                                                                                 threshold_pubkey(check_value(~private_share1),
                                                                                                  check_value(~private_share2),
                                                                                                  check_value(~private_share3)),
                                                                                 ~r)
                                                                  >,
                                                                  'no shuffle'>,
                                                                 sign(<
                                                                       <'Trustee_EG_Cryptograms', 'Trustee0',
                                                                        'Trustee2'>,
                                                                       ~election_setup, ~ballot_order,
                                                                       <
                                                                        ny_encrypt_c1(~ballots,
                                                                                      threshold_pubkey(check_value(~private_share1),
                                                                                                       check_value(~private_share2),
                                                                                                       check_value(~private_share3)),
                                                                                      ~r),
                                                                        ny_encrypt_c2(~ballots,
                                                                                      threshold_pubkey(check_value(~private_share1),
                                                                                                       check_value(~private_share2),
                                                                                                       check_value(~private_share3)),
                                                                                      ~r)
                                                                       >,
                                                                       'no shuffle'>,
                                                                      '1', ~sk_sign_trustee2),
                                                                 %idx_signed_shuffle2
                                               ) ▶₁ #i )
                                          case TrusteeBoard_Trustee_Update
                                          solve( TAS_Trustee_Trace( 'Trustee0', pk(~sk_sign_tas),
                                                                    pk(~sk_encrypt_unused)
                                                 ) @ #j.6 )
                                            case TrusteeMixing_TAS_Init
                                            solve( HonestSignatureKey( pk(~sk_sign_tas) ) @ #k.1 )
                                              case Mock_TrusteeElectionSetup
                                              solve( Trustee_State_ReceiveBBMessage( 'Trustee2',
                                                                                     %idx_shuffled_ballots
                                                     ) ▶₀ #vr.3 )
                                                case TrusteeBoard_Trustee_Update_case_06
                                                solve( TAS_Trustee_Trace( 'Trustee1', pk(~sk_sign_trustee1),
                                                                          pk(~sk_encrypt_trustee1)
                                                       ) @ #j.6 )
                                                  case Mock_TrusteeElectionSetup
                                                  solve( HonestSignatureKey( pk(~sk_sign_trustee1) ) @ #k.1 )
                                                    case Mock_TrusteeElectionSetup
                                                    solve( TAS_Trustee_Trace( 'Trustee0', pk(~sk_sign_tas),
                                                                              pk(~sk_encrypt_unused)
                                                           ) @ #j.6 )
                                                      case TrusteeMixing_TAS_Init
                                                      solve( HonestSignatureKey( pk(~sk_sign_tas) ) @ #k.1 )
                                                        case Mock_TrusteeElectionSetup
                                                        solve( TAS_State_ReceiveTrusteeMessage( (
                                                                                                 %idx_signed_shuffle1%+
                                                                                                 %1)
                                                               ) ▶₀ #vr.4 )
                                                          case TrusteeBoard_TAS_ReceiveTrusteeMessage
                                                          solve( TAS_Trustee_Trace( 'Trustee1',
                                                                                    pk(~sk_sign_trustee1),
                                                                                    pk(~sk_encrypt_trustee1)
                                                                 ) @ #j.6 )
                                                            case Mock_TrusteeElectionSetup
                                                            solve( HonestSignatureKey( pk(~sk_sign_trustee1)
                                                                   ) @ #k.1 )
                                                              case Mock_TrusteeElectionSetup
                                                              solve( TAS_Trustee_Trace( 'Trustee0',
                                                                                        pk(~sk_sign_tas),
                                                                                        pk(~sk_encrypt_unused)
                                                                     ) @ #j.6 )
                                                                case TrusteeMixing_TAS_Init
                                                                solve( HonestSignatureKey( pk(~sk_sign_tas)
                                                                       ) @ #k.1 )
                                                                  case Mock_TrusteeElectionSetup
                                                                  solve( Trustee_State_ReceiveBBMessage( 'Trustee1',
                                                                                                         %idx_signed_shuffle1
                                                                         ) ▶₀ #j.1 )
                                                                    case TrusteeBoard_Trustee_Update_case_06
                                                                    solve( TAS_Trustee_Trace( 'Trustee2',
                                                                                              pk(~sk_sign_trustee2),
                                                                                              pk(~sk_encrypt_trustee2)
                                                                           ) @ #j.6 )
                                                                      case Mock_TrusteeElectionSetup
                                                                      solve( HonestSignatureKey( pk(~sk_sign_trustee2)
                                                                             ) @ #k.1 )
                                                                        case Mock_TrusteeElectionSetup
                                                                        solve( TAS_Trustee_Trace( 'Trustee0',
                                                                                                  pk(~sk_sign_tas),
                                                                                                  pk(~sk_encrypt_unused)
                                                                               ) @ #j.6 )
                                                                          case TrusteeMixing_TAS_Init
                                                                          solve( HonestSignatureKey( pk(~sk_sign_tas)
                                                                                 ) @ #k.1 )
                                                                            case Mock_TrusteeElectionSetup
                                                                            solve( Trustee_State_ReceiveBBMessage( 'Trustee1',
                                                                                                                   %idx_signed_shuffle2
                                                                                   ) ▶₀ #j.2 )
                                                                              case TrusteeBoard_Trustee_Update_case_5
                                                                              solve( TAS_Trustee_Trace( 'Trustee0',
                                                                                                        pk(~sk_sign_tas),
                                                                                                        pk(~sk_encrypt_unused)
                                                                                     ) @ #j.6 )
                                                                                case TrusteeMixing_TAS_Init
                                                                                solve( HonestSignatureKey( pk(~sk_sign_tas)
                                                                                       ) @ #k.1 )
                                                                                  case Mock_TrusteeElectionSetup
                                                                                  solve( TAS_State_ReceiveTrusteeMessage( (
                                                                                                                           %idx_initial_ballots%+
                                                                                                                           %1%+
                                                                                                                           %1
                                                                                                                          )
                                                                                         ) ▶₀ #vr.5 )
                                                                                    case TrusteeBoard_TAS_ReceiveTrusteeMessage
                                                                                    solve( TAS_Trustee_Trace( 'Trustee2',
                                                                                                              pk(~sk_sign_trustee2),
                                                                                                              pk(~sk_encrypt_trustee2)
                                                                                           ) @ #j.6 )
                                                                                      case Mock_TrusteeElectionSetup
                                                                                      solve( HonestSignatureKey( pk(~sk_sign_trustee2)
                                                                                             ) @ #k.1 )
                                                                                        case Mock_TrusteeElectionSetup
                                                                                        solve( TAS_Trustee_Trace( 'Trustee0',
                                                                                                                  pk(~sk_sign_tas),
                                                                                                                  pk(~sk_encrypt_unused)
                                                                                               ) @ #j.6 )
                                                                                          case TrusteeMixing_TAS_Init
                                                                                          solve( HonestSignatureKey( pk(~sk_sign_tas)
                                                                                                 ) @ #k.1 )
                                                                                            case Mock_TrusteeElectionSetup
                                                                                            solve( TAS_State_ReceiveTrusteeMessage( (
                                                                                                                                     %idx_initial_ballots%+
                                                                                                                                     %1
                                                                                                                                    )
                                                                                                   ) ▶₀ #vr.6 )
                                                                                              case TrusteeBoard_TAS_ReceiveTrusteeMessage
                                                                                              solve( TAS_Trustee_Trace( 'Trustee0',
                                                                                                                        pk(~sk_sign_tas),
                                                                                                                        pk(~sk_encrypt_unused)
                                                                                                     ) @ #j.6 )
                                                                                                case TrusteeMixing_TAS_Init
                                                                                                solve( HonestSignatureKey( pk(~sk_sign_tas)
                                                                                                       ) @ #k.1 )
                                                                                                  case Mock_TrusteeElectionSetup
                                                                                                  solve( !Trustee_BBEntry( 'Trustee1',
                                                                                                                           'Trustee0',
                                                                                                                           <
                                                                                                                            <
                                                                                                                             'Trustee_NY_Cryptograms',
                                                                                                                             'Trustee0',
                                                                                                                             'Trustee0'
                                                                                                                            >,
                                                                                                                            ~election_setup,
                                                                                                                            ~ballot_order,
                                                                                                                            ny_encrypt_c1(~ballots,
                                                                                                                                          threshold_pubkey(check_value(~private_share1),
                                                                                                                                                           check_value(~private_share2),
                                                                                                                                                           check_value(~private_share3)),
                                                                                                                                          ~r),
                                                                                                                            ny_encrypt_c2(~ballots,
                                                                                                                                          threshold_pubkey(check_value(~private_share1),
                                                                                                                                                           check_value(~private_share2),
                                                                                                                                                           check_value(~private_share3)),
                                                                                                                                          ~r),
                                                                                                                            ny_encrypt_p(~ballots,
                                                                                                                                         threshold_pubkey(check_value(~private_share1),
                                                                                                                                                          check_value(~private_share2),
                                                                                                                                                          check_value(~private_share3)),
                                                                                                                                         ~r)
                                                                                                                           >,
                                                                                                                           sign(<
                                                                                                                                 <
                                                                                                                                  'Trustee_NY_Cryptograms',
                                                                                                                                  'Trustee0',
                                                                                                                                  'Trustee0'
                                                                                                                                 >,
                                                                                                                                 ~election_setup,
                                                                                                                                 ~ballot_order,
                                                                                                                                 ny_encrypt_c1(~ballots,
                                                                                                                                               threshold_pubkey(check_value(~private_share1),
                                                                                                                                                                check_value(~private_share2),
                                                                                                                                                                check_value(~private_share3)),
                                                                                                                                               ~r),
                                                                                                                                 ny_encrypt_c2(~ballots,
                                                                                                                                               threshold_pubkey(check_value(~private_share1),
                                                                                                                                                                check_value(~private_share2),
                                                                                                                                                                check_value(~private_share3)),
                                                                                                                                               ~r),
                                                                                                                                 ny_encrypt_p(~ballots,
                                                                                                                                              threshold_pubkey(check_value(~private_share1),
                                                                                                                                                               check_value(~private_share2),
                                                                                                                                                               check_value(~private_share3)),
                                                                                                                                              ~r)
                                                                                                                                >,
                                                                                                                                '1',
                                                                                                                                ~sk_sign_tas),
                                                                                                                           %idx_initial_ballots
                                                                                                         ) ▶₁ #j.5 )
                                                                                                    case TrusteeBoard_Trustee_Update
                                                                                                    solve( Trustee_State_ReceiveBBMessage( 'Trustee1',
                                                                                                                                           %idx_initial_ballots
                                                                                                           ) ▶₀ #j.3 )
                                                                                                      case TrusteeMixing_TAS_Init
                                                                                                      solve( !Trustee_BBEntry( 'Trustee2',
                                                                                                                               'Trustee0',
                                                                                                                               <
                                                                                                                                <
                                                                                                                                 'Trustee_NY_Cryptograms',
                                                                                                                                 'Trustee0',
                                                                                                                                 'Trustee0'
                                                                                                                                >,
                                                                                                                                ~election_setup,
                                                                                                                                ~ballot_order,
                                                                                                                                ny_encrypt_c1(~ballots,
                                                                                                                                              threshold_pubkey(check_value(~private_share1),
                                                                                                                                                               check_value(~private_share2),
                                                                                                                                                               check_value(~private_share3)),
                                                                                                                                              ~r),
                                                                                                                                ny_encrypt_c2(~ballots,
                                                                                                                                              threshold_pubkey(check_value(~private_share1),
                                                                                                                                                               check_value(~private_share2),
                                                                                                                                                               check_value(~private_share3)),
                                                                                                                                              ~r),
                                                                                                                                ny_encrypt_p(~ballots,
                                                                                                                                             threshold_pubkey(check_value(~private_share1),
                                                                                                                                                              check_value(~private_share2),
                                                                                                                                                              check_value(~private_share3)),
                                                                                                                                             ~r)
                                                                                                                               >,
                                                                                                                               sign(<
                                                                                                                                     <
                                                                                                                                      'Trustee_NY_Cryptograms',
                                                                                                                                      'Trustee0',
                                                                                                                                      'Trustee0'
                                                                                                                                     >,
                                                                                                                                     ~election_setup,
                                                                                                                                     ~ballot_order,
                                                                                                                                     ny_encrypt_c1(~ballots,
                                                                                                                                                   threshold_pubkey(check_value(~private_share1),
                                                                                                                                                                    check_value(~private_share2),
                                                                                                                                                                    check_value(~private_share3)),
                                                                                                                                                   ~r),
                                                                                                                                     ny_encrypt_c2(~ballots,
                                                                                                                                                   threshold_pubkey(check_value(~private_share1),
                                                                                                                                                                    check_value(~private_share2),
                                                                                                                                                                    check_value(~private_share3)),
                                                                                                                                                   ~r),
                                                                                                                                     ny_encrypt_p(~ballots,
                                                                                                                                                  threshold_pubkey(check_value(~private_share1),
                                                                                                                                                                   check_value(~private_share2),
                                                                                                                                                                   check_value(~private_share3)),
                                                                                                                                                  ~r)
                                                                                                                                    >,
                                                                                                                                    '1',
                                                                                                                                    ~sk_sign_tas),
                                                                                                                               %1
                                                                                                             ) ▶₁ #vr.7 )
                                                                                                        case TrusteeBoard_Trustee_Update
                                                                                                        solve( Trustee_State_ReceiveBBMessage( 'Trustee2',
                                                                                                                                               %1
                                                                                                               ) ▶₀ #j.4 )
                                                                                                          case TrusteeMixing_TAS_Init
                                                                                                          solve( TAS_State_ReceiveTrusteeMessage( %1
                                                                                                                 ) ▶₀ #vr.8 )
                                                                                                            case TrusteeMixing_TAS_Init
                                                                                                            solve( Trustee_State_ReceiveBBMessage( 'Trustee2',
                                                                                                                                                   (
                                                                                                                                                    %1%+
                                                                                                                                                    %1%+
                                                                                                                                                    %1
                                                                                                                                                   )
                                                                                                                   ) ▶₀ #vr.9 )
                                                                                                              case TrusteeBoard_Trustee_Update
                                                                                                              solve( TAS_Trustee_Trace( 'Trustee2',
                                                                                                                                        pk(~sk_sign_trustee2),
                                                                                                                                        pk(~sk_encrypt_trustee2)
                                                                                                                     ) @ #j.7 )
                                                                                                                case Mock_TrusteeElectionSetup
                                                                                                                solve( HonestSignatureKey( pk(~sk_sign_trustee2)
                                                                                                                       ) @ #k.1 )
                                                                                                                  case Mock_TrusteeElectionSetup
                                                                                                                  solve( TAS_Trustee_Trace( 'Trustee0',
                                                                                                                                            pk(~sk_sign_tas),
                                                                                                                                            pk(~sk_encrypt_unused)
                                                                                                                         ) @ #j.7 )
                                                                                                                    case TrusteeMixing_TAS_Init
                                                                                                                    solve( HonestSignatureKey( pk(~sk_sign_tas)
                                                                                                                           ) @ #k.1 )
                                                                                                                      case Mock_TrusteeElectionSetup
                                                                                                                      solve( Trustee_Sent_Msg_Trace( 'Trustee2',
                                                                                                                                                     <
                                                                                                                                                      <
                                                                                                                                                       'Trustee_EG_Cryptograms',
                                                                                                                                                       'Trustee0',
                                                                                                                                                       'Trustee2'
                                                                                                                                                      >,
                                                                                                                                                      ~election_setup,
                                                                                                                                                      ~ballot_order,
                                                                                                                                                      <
                                                                                                                                                       ny_encrypt_c1(~ballots,
                                                                                                                                                                     threshold_pubkey(check_value(~private_share1),
                                                                                                                                                                                      check_value(~private_share2),
                                                                                                                                                                                      check_value(~private_share3)),
                                                                                                                                                                     ~r),
                                                                                                                                                       ny_encrypt_c2(~ballots,
                                                                                                                                                                     threshold_pubkey(check_value(~private_share1),
                                                                                                                                                                                      check_value(~private_share2),
                                                                                                                                                                                      check_value(~private_share3)),
                                                                                                                                                                     ~r)
                                                                                                                                                      >,
                                                                                                                                                      'no shuffle'
                                                                                                                                                     >
                                                                                                                             ) @ #j.6 )
                                                                                                                        case TrusteeMixing_Check_Encryption_Proofs_Success
                                                                                                                        solve( Trustee_State_ReceiveBBMessage( 'Trustee2',
                                                                                                                                                               (
                                                                                                                                                                %1%+
                                                                                                                                                                %1
                                                                                                                                                               )
                                                                                                                               ) ▶₀ #vr.9 )
                                                                                                                          case TrusteeBoard_Trustee_Update
                                                                                                                          solve( TAS_Trustee_Trace( 'Trustee0',
                                                                                                                                                    pk(~sk_sign_tas),
                                                                                                                                                    pk(~sk_encrypt_unused)
                                                                                                                                 ) @ #j.7 )
                                                                                                                            case TrusteeMixing_TAS_Init
                                                                                                                            solve( HonestSignatureKey( pk(~sk_sign_tas)
                                                                                                                                   ) @ #k.1 )
                                                                                                                              case Mock_TrusteeElectionSetup
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
        qed
      qed
    qed
  qed
qed
