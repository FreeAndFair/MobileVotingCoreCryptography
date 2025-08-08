simplify
solve( !TAS_ElectionSetup_Complete( election_setup ) ▶₀ #i )
  case Mock_TrusteeElectionSetup
  solve( !TAS_BBEntry( 'Trustee1',
                       <<'Trustee_EG_Cryptograms', 'Trustee2', 'Trustee1'>, ~election_setup, b,
                        s, p>,
                       sig_last_mix1, %idx_last_mix1
         ) ▶₁ #i )
    case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_2
    solve( !TAS_BBEntry( 'Trustee2',
                         <<'Trustee_EG_Cryptograms', 'Trustee2', 'Trustee2'>, ~election_setup,
                          shuffle_order(prev_prev_ballot_order, s, prev_r), s,
                          shuffle_proof(prev_prev_ballot_order, s, prev_r)>,
                         sig_last_mix2, %idx_last_mix2
           ) ▶₂ #i )
      case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_21
      solve( TAS_Trustee_Trace( 'Trustee1', pk(~sk_sign_trustee1),
                                pk(~sk_encrypt_trustee1)
             ) @ #j.8 )
        case Mock_TrusteeElectionSetup
        solve( HonestSignatureKey( pk(~sk_sign_trustee1) ) @ #k )
          case Mock_TrusteeElectionSetup
          solve( TAS_Trustee_Trace( 'Trustee2', pk(~sk_sign_trustee2),
                                    pk(~sk_encrypt_trustee2)
                 ) @ #j.8 )
            case Mock_TrusteeElectionSetup
            solve( HonestSignatureKey( pk(~sk_sign_trustee2) ) @ #k.1 )
              case Mock_TrusteeElectionSetup
              solve( TAS_Trustee_Trace( 'Trustee1', pk(~sk_sign_trustee1),
                                        pk(~sk_encrypt_trustee1)
                     ) @ #j.8 )
                case Mock_TrusteeElectionSetup
                solve( HonestSignatureKey( pk(~sk_sign_trustee1) ) @ #k.1 )
                  case Mock_TrusteeElectionSetup
                  solve( TAS_Trustee_Trace( 'Trustee2', pk(~sk_sign_trustee2),
                                            pk(~sk_encrypt_trustee2)
                         ) @ #j.8 )
                    case Mock_TrusteeElectionSetup
                    solve( HonestSignatureKey( pk(~sk_sign_trustee2) ) @ #k.1 )
                      case Mock_TrusteeElectionSetup
                      solve( TAS_Trustee_Trace( 'Trustee1', pk(~sk_sign_trustee1),
                                                pk(~sk_encrypt_trustee1)
                             ) @ #j.8 )
                        case Mock_TrusteeElectionSetup
                        solve( HonestSignatureKey( pk(~sk_sign_trustee1) ) @ #k.1 )
                          case Mock_TrusteeElectionSetup
                          solve( TAS_Trustee_Trace( 'Trustee2', pk(~sk_sign_trustee2),
                                                    pk(~sk_encrypt_trustee2)
                                 ) @ #j.8 )
                            case Mock_TrusteeElectionSetup
                            solve( HonestSignatureKey( pk(~sk_sign_trustee2) ) @ #k.1 )
                              case Mock_TrusteeElectionSetup
                              solve( TAS_Trustee_Trace( 'Trustee0', pk(~sk_sign_tas),
                                                        pk(~sk_encrypt_unused)
                                     ) @ #j.8 )
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
                                         ) @ #j.6 )
                                    case TrusteeMixing_Check_Encryption_Proofs_Success
                                    solve( Trustee_Sent_Msg_Trace( 'Trustee2',
                                                                   <
                                                                    <'Trustee_EG_Cryptograms', 'Trustee1',
                                                                     'Trustee2'>,
                                                                    ~election_setup,
                                                                    shuffle_order(~ballot_order,
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
                                                                                  ~r.1),
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
                                                                    shuffle_proof(~ballot_order,
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
                                                                                  ~r.1)
                                                                   >
                                           ) @ #j.7 )
                                      case TrusteeMixing_Trustee_Sign_Shuffle
                                      solve( TAS_State_ReceiveTrusteeMessage( %idx_last_mix1 ) ▶₀ #vr )
                                        case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_09
                                        solve( TAS_Trustee_Trace( 'Trustee2', pk(~sk_sign_trustee2),
                                                                  pk(~sk_encrypt_trustee2)
                                               ) @ #j.8 )
                                          case Mock_TrusteeElectionSetup
                                          solve( HonestSignatureKey( pk(~sk_sign_trustee2) ) @ #k.1 )
                                            case Mock_TrusteeElectionSetup
                                            solve( TAS_Trustee_Trace( 'Trustee1', pk(~sk_sign_trustee1),
                                                                      pk(~sk_encrypt_trustee1)
                                                   ) @ #j.8 )
                                              case Mock_TrusteeElectionSetup
                                              solve( HonestSignatureKey( pk(~sk_sign_trustee1) ) @ #k.1 )
                                                case Mock_TrusteeElectionSetup
                                                solve( TAS_Trustee_Trace( 'Trustee2', pk(~sk_sign_trustee2),
                                                                          pk(~sk_encrypt_trustee2)
                                                       ) @ #j.8 )
                                                  case Mock_TrusteeElectionSetup
                                                  solve( HonestSignatureKey( pk(~sk_sign_trustee2) ) @ #k.1 )
                                                    case Mock_TrusteeElectionSetup
                                                    solve( TAS_Trustee_Trace( 'Trustee1',
                                                                              pk(~sk_sign_trustee1),
                                                                              pk(~sk_encrypt_trustee1)
                                                           ) @ #j.8 )
                                                      case Mock_TrusteeElectionSetup
                                                      solve( HonestSignatureKey( pk(~sk_sign_trustee1)
                                                             ) @ #k.1 )
                                                        case Mock_TrusteeElectionSetup
                                                        solve( TAS_Trustee_Trace( 'Trustee2',
                                                                                  pk(~sk_sign_trustee2),
                                                                                  pk(~sk_encrypt_trustee2)
                                                               ) @ #j.8 )
                                                          case Mock_TrusteeElectionSetup
                                                          solve( HonestSignatureKey( pk(~sk_sign_trustee2)
                                                                 ) @ #k.1 )
                                                            case Mock_TrusteeElectionSetup
                                                            solve( TAS_Trustee_Trace( 'Trustee0',
                                                                                      pk(~sk_sign_tas),
                                                                                      pk(~sk_encrypt_unused)
                                                                   ) @ #j.8 )
                                                              case TrusteeMixing_TAS_Init
                                                              solve( HonestSignatureKey( pk(~sk_sign_tas)
                                                                     ) @ #k.1 )
                                                                case Mock_TrusteeElectionSetup
                                                                solve( !Trustee_BBEntry( 'Trustee1',
                                                                                         'Trustee2',
                                                                                         <
                                                                                          <
                                                                                           'Trustee_EG_Cryptograms',
                                                                                           'Trustee2',
                                                                                           'Trustee2'>,
                                                                                          ~election_setup,
                                                                                          shuffle_order(shuffle_order(~ballot_order,
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
                                                                                                                      ~r.1),
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
                                                                                                        ~r.2),
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
                                                                                          shuffle_proof(shuffle_order(~ballot_order,
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
                                                                                                                      ~r.1),
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
                                                                                                        ~r.2)
                                                                                         >,
                                                                                         sig_shuffled_ballots,
                                                                                         %idx_shuffled_ballots
                                                                       ) ▶₂ #vr.1 )
                                                                  case TrusteeBoard_Trustee_Update_case_2
                                                                  solve( TAS_Trustee_Trace( 'Trustee2',
                                                                                            pk(~sk_sign_trustee2),
                                                                                            pk(~sk_encrypt_trustee2)
                                                                         ) @ #j.8 )
                                                                    case Mock_TrusteeElectionSetup
                                                                    solve( HonestSignatureKey( pk(~sk_sign_trustee2)
                                                                           ) @ #k.1 )
                                                                      case Mock_TrusteeElectionSetup
                                                                      solve( TAS_Trustee_Trace( 'Trustee1',
                                                                                                pk(~sk_sign_trustee1),
                                                                                                pk(~sk_encrypt_trustee1)
                                                                             ) @ #j.8 )
                                                                        case Mock_TrusteeElectionSetup
                                                                        solve( HonestSignatureKey( pk(~sk_sign_trustee1)
                                                                               ) @ #k.1 )
                                                                          case Mock_TrusteeElectionSetup
                                                                          solve( TAS_Trustee_Trace( 'Trustee2',
                                                                                                    pk(~sk_sign_trustee2),
                                                                                                    pk(~sk_encrypt_trustee2)
                                                                                 ) @ #j.8 )
                                                                            case Mock_TrusteeElectionSetup
                                                                            solve( HonestSignatureKey( pk(~sk_sign_trustee2)
                                                                                   ) @ #k.1 )
                                                                              case Mock_TrusteeElectionSetup
                                                                              solve( TAS_Trustee_Trace( 'Trustee1',
                                                                                                        pk(~sk_sign_trustee1),
                                                                                                        pk(~sk_encrypt_trustee1)
                                                                                     ) @ #j.8 )
                                                                                case Mock_TrusteeElectionSetup
                                                                                solve( HonestSignatureKey( pk(~sk_sign_trustee1)
                                                                                       ) @ #k.1 )
                                                                                  case Mock_TrusteeElectionSetup
                                                                                  solve( TAS_Trustee_Trace( 'Trustee2',
                                                                                                            pk(~sk_sign_trustee2),
                                                                                                            pk(~sk_encrypt_trustee2)
                                                                                         ) @ #j.8 )
                                                                                    case Mock_TrusteeElectionSetup
                                                                                    solve( HonestSignatureKey( pk(~sk_sign_trustee2)
                                                                                           ) @ #k.1 )
                                                                                      case Mock_TrusteeElectionSetup
                                                                                      solve( TAS_Trustee_Trace( 'Trustee0',
                                                                                                                pk(~sk_sign_tas),
                                                                                                                pk(~sk_encrypt_unused)
                                                                                             ) @ #j.8 )
                                                                                        case TrusteeMixing_TAS_Init
                                                                                        solve( HonestSignatureKey( pk(~sk_sign_tas)
                                                                                               ) @ #k.1 )
                                                                                          case Mock_TrusteeElectionSetup
                                                                                          solve( TAS_State_ReceiveTrusteeMessage( %idx_last_mix2
                                                                                                 ) ▶₀ #vr.5 )
                                                                                            case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_9
                                                                                            solve( TAS_Trustee_Trace( 'Trustee2',
                                                                                                                      pk(~sk_sign_trustee2),
                                                                                                                      pk(~sk_encrypt_trustee2)
                                                                                                   ) @ #j.8 )
                                                                                              case Mock_TrusteeElectionSetup
                                                                                              solve( HonestSignatureKey( pk(~sk_sign_trustee2)
                                                                                                     ) @ #k.1 )
                                                                                                case Mock_TrusteeElectionSetup
                                                                                                solve( !Trustee_BBEntry( 'Trustee2',
                                                                                                                         'Trustee1',
                                                                                                                         <
                                                                                                                          <
                                                                                                                           'Trustee_EG_Cryptograms',
                                                                                                                           'Trustee1',
                                                                                                                           'Trustee1'
                                                                                                                          >,
                                                                                                                          ~election_setup,
                                                                                                                          shuffle_order(~ballot_order,
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
                                                                                                                                        ~r.1),
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
                                                                                                                          shuffle_proof(~ballot_order,
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
                                                                                                                                        ~r.1)
                                                                                                                         >,
                                                                                                                         sign(<
                                                                                                                               <
                                                                                                                                'Trustee_EG_Cryptograms',
                                                                                                                                'Trustee1',
                                                                                                                                'Trustee1'
                                                                                                                               >,
                                                                                                                               ~election_setup,
                                                                                                                               shuffle_order(~ballot_order,
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
                                                                                                                                             ~r.1),
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
                                                                                                                               shuffle_proof(~ballot_order,
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
                                                                                                                                             ~r.1)
                                                                                                                              >,
                                                                                                                              '1',
                                                                                                                              ~sk_sign_trustee1),
                                                                                                                         %idx_signed_shuffle1
                                                                                                       ) ▶₀ #vr.6 )
                                                                                                  case TrusteeBoard_Trustee_Update
                                                                                                  solve( TAS_Trustee_Trace( 'Trustee2',
                                                                                                                            pk(~sk_sign_trustee2),
                                                                                                                            pk(~sk_encrypt_trustee2)
                                                                                                         ) @ #j.8 )
                                                                                                    case Mock_TrusteeElectionSetup
                                                                                                    solve( HonestSignatureKey( pk(~sk_sign_trustee2)
                                                                                                           ) @ #k.1 )
                                                                                                      case Mock_TrusteeElectionSetup
                                                                                                      solve( TAS_Trustee_Trace( 'Trustee0',
                                                                                                                                pk(~sk_sign_tas),
                                                                                                                                pk(~sk_encrypt_unused)
                                                                                                             ) @ #j.8 )
                                                                                                        case TrusteeMixing_TAS_Init
                                                                                                        solve( HonestSignatureKey( pk(~sk_sign_tas)
                                                                                                               ) @ #k.1 )
                                                                                                          case Mock_TrusteeElectionSetup
                                                                                                          solve( !Trustee_BBEntry( 'Trustee2',
                                                                                                                                   'Trustee2',
                                                                                                                                   <
                                                                                                                                    <
                                                                                                                                     'Trustee_EG_Cryptograms',
                                                                                                                                     'Trustee1',
                                                                                                                                     'Trustee2'
                                                                                                                                    >,
                                                                                                                                    ~election_setup,
                                                                                                                                    shuffle_order(~ballot_order,
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
                                                                                                                                                  ~r.1),
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
                                                                                                                                    shuffle_proof(~ballot_order,
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
                                                                                                                                                  ~r.1)
                                                                                                                                   >,
                                                                                                                                   sign(<
                                                                                                                                         <
                                                                                                                                          'Trustee_EG_Cryptograms',
                                                                                                                                          'Trustee1',
                                                                                                                                          'Trustee2'
                                                                                                                                         >,
                                                                                                                                         ~election_setup,
                                                                                                                                         shuffle_order(~ballot_order,
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
                                                                                                                                                       ~r.1),
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
                                                                                                                                         shuffle_proof(~ballot_order,
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
                                                                                                                                                       ~r.1)
                                                                                                                                        >,
                                                                                                                                        '1',
                                                                                                                                        ~sk_sign_trustee2),
                                                                                                                                   %idx_signed_shuffle2
                                                                                                                 ) ▶₁ #vr.6 )
                                                                                                            case TrusteeBoard_Trustee_Update
                                                                                                            solve( Trustee_State_ReceiveBBMessage( 'Trustee2',
                                                                                                                                                   %idx_signed_shuffle1
                                                                                                                   ) ▶₀ #j )
                                                                                                              case TrusteeBoard_Trustee_Update_case_6
                                                                                                              solve( TAS_Trustee_Trace( 'Trustee1',
                                                                                                                                        pk(~sk_sign_trustee1),
                                                                                                                                        pk(~sk_encrypt_trustee1)
                                                                                                                     ) @ #j.8 )
                                                                                                                case Mock_TrusteeElectionSetup
                                                                                                                solve( HonestSignatureKey( pk(~sk_sign_trustee1)
                                                                                                                       ) @ #k.1 )
                                                                                                                  case Mock_TrusteeElectionSetup
                                                                                                                  solve( TAS_Trustee_Trace( 'Trustee0',
                                                                                                                                            pk(~sk_sign_tas),
                                                                                                                                            pk(~sk_encrypt_unused)
                                                                                                                         ) @ #j.8 )
                                                                                                                    case TrusteeMixing_TAS_Init
                                                                                                                    solve( HonestSignatureKey( pk(~sk_sign_tas)
                                                                                                                           ) @ #k.1 )
                                                                                                                      case Mock_TrusteeElectionSetup
                                                                                                                      solve( Trustee_State_ReceiveBBMessage( 'Trustee2',
                                                                                                                                                             %idx_signed_shuffle2
                                                                                                                             ) ▶₀ #j.1 )
                                                                                                                        case TrusteeBoard_Trustee_Update_case_7
                                                                                                                        solve( TAS_Trustee_Trace( 'Trustee1',
                                                                                                                                                  pk(~sk_sign_trustee1),
                                                                                                                                                  pk(~sk_encrypt_trustee1)
                                                                                                                               ) @ #j.8 )
                                                                                                                          case Mock_TrusteeElectionSetup
                                                                                                                          solve( HonestSignatureKey( pk(~sk_sign_trustee1)
                                                                                                                                 ) @ #k.1 )
                                                                                                                            case Mock_TrusteeElectionSetup
                                                                                                                            solve( TAS_Trustee_Trace( 'Trustee1',
                                                                                                                                                      pk(~sk_sign_trustee1),
                                                                                                                                                      pk(~sk_encrypt_trustee1)
                                                                                                                                   ) @ #j.8 )
                                                                                                                              case Mock_TrusteeElectionSetup
                                                                                                                              solve( HonestSignatureKey( pk(~sk_sign_trustee1)
                                                                                                                                     ) @ #k.1 )
                                                                                                                                case Mock_TrusteeElectionSetup
                                                                                                                                solve( TAS_Trustee_Trace( 'Trustee2',
                                                                                                                                                          pk(~sk_sign_trustee2),
                                                                                                                                                          pk(~sk_encrypt_trustee2)
                                                                                                                                       ) @ #j.8 )
                                                                                                                                  case Mock_TrusteeElectionSetup
                                                                                                                                  solve( HonestSignatureKey( pk(~sk_sign_trustee2)
                                                                                                                                         ) @ #k.1 )
                                                                                                                                    case Mock_TrusteeElectionSetup
                                                                                                                                    solve( TAS_Trustee_Trace( 'Trustee0',
                                                                                                                                                              pk(~sk_sign_tas),
                                                                                                                                                              pk(~sk_encrypt_unused)
                                                                                                                                           ) @ #j.8 )
                                                                                                                                      case TrusteeMixing_TAS_Init
                                                                                                                                      solve( HonestSignatureKey( pk(~sk_sign_tas)
                                                                                                                                             ) @ #k.1 )
                                                                                                                                        case Mock_TrusteeElectionSetup
                                                                                                                                        solve( TAS_State_ReceiveTrusteeMessage( (
                                                                                                                                                                                 %idx_signed_shuffle1%+
                                                                                                                                                                                 %1
                                                                                                                                                                                )
                                                                                                                                               ) ▶₀ #vr.7 )
                                                                                                                                          case TrusteeBoard_TAS_ReceiveTrusteeMessage
                                                                                                                                          solve( TAS_Trustee_Trace( 'Trustee1',
                                                                                                                                                                    pk(~sk_sign_trustee1),
                                                                                                                                                                    pk(~sk_encrypt_trustee1)
                                                                                                                                                 ) @ #j.8 )
                                                                                                                                            case Mock_TrusteeElectionSetup
                                                                                                                                            solve( HonestSignatureKey( pk(~sk_sign_trustee1)
                                                                                                                                                   ) @ #k.1 )
                                                                                                                                              case Mock_TrusteeElectionSetup
                                                                                                                                              solve( TAS_Trustee_Trace( 'Trustee0',
                                                                                                                                                                        pk(~sk_sign_tas),
                                                                                                                                                                        pk(~sk_encrypt_unused)
                                                                                                                                                     ) @ #j.8 )
                                                                                                                                                case TrusteeMixing_TAS_Init
                                                                                                                                                solve( HonestSignatureKey( pk(~sk_sign_tas)
                                                                                                                                                       ) @ #k.1 )
                                                                                                                                                  case Mock_TrusteeElectionSetup
                                                                                                                                                  solve( TAS_State_ReceiveTrusteeMessage( (
                                                                                                                                                                                           %idx_signed_shuffle1%+
                                                                                                                                                                                           %1%+
                                                                                                                                                                                           %1
                                                                                                                                                                                          )
                                                                                                                                                         ) ▶₀ #vr.8 )
                                                                                                                                                    case TrusteeBoard_TAS_ReceiveTrusteeMessage
                                                                                                                                                    solve( TAS_Trustee_Trace( 'Trustee1',
                                                                                                                                                                              pk(~sk_sign_trustee1),
                                                                                                                                                                              pk(~sk_encrypt_trustee1)
                                                                                                                                                           ) @ #j.8 )
                                                                                                                                                      case Mock_TrusteeElectionSetup
                                                                                                                                                      solve( HonestSignatureKey( pk(~sk_sign_trustee1)
                                                                                                                                                             ) @ #k.1 )
                                                                                                                                                        case Mock_TrusteeElectionSetup
                                                                                                                                                        solve( TAS_Trustee_Trace( 'Trustee1',
                                                                                                                                                                                  pk(~sk_sign_trustee1),
                                                                                                                                                                                  pk(~sk_encrypt_trustee1)
                                                                                                                                                               ) @ #j.8 )
                                                                                                                                                          case Mock_TrusteeElectionSetup
                                                                                                                                                          solve( HonestSignatureKey( pk(~sk_sign_trustee1)
                                                                                                                                                                 ) @ #k.1 )
                                                                                                                                                            case Mock_TrusteeElectionSetup
                                                                                                                                                            solve( TAS_Trustee_Trace( 'Trustee2',
                                                                                                                                                                                      pk(~sk_sign_trustee2),
                                                                                                                                                                                      pk(~sk_encrypt_trustee2)
                                                                                                                                                                   ) @ #j.8 )
                                                                                                                                                              case Mock_TrusteeElectionSetup
                                                                                                                                                              solve( HonestSignatureKey( pk(~sk_sign_trustee2)
                                                                                                                                                                     ) @ #k.1 )
                                                                                                                                                                case Mock_TrusteeElectionSetup
                                                                                                                                                                solve( TAS_Trustee_Trace( 'Trustee0',
                                                                                                                                                                                          pk(~sk_sign_tas),
                                                                                                                                                                                          pk(~sk_encrypt_unused)
                                                                                                                                                                       ) @ #j.8 )
                                                                                                                                                                  case TrusteeMixing_TAS_Init
                                                                                                                                                                  solve( HonestSignatureKey( pk(~sk_sign_tas)
                                                                                                                                                                         ) @ #k.1 )
                                                                                                                                                                    case Mock_TrusteeElectionSetup
                                                                                                                                                                    solve( !Trustee_BBEntry( 'Trustee1',
                                                                                                                                                                                             'Trustee1',
                                                                                                                                                                                             <
                                                                                                                                                                                              <
                                                                                                                                                                                               'Trustee_EG_Cryptograms',
                                                                                                                                                                                               'Trustee0',
                                                                                                                                                                                               'Trustee1'
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
                                                                                                                                                                                             >,
                                                                                                                                                                                             sign(<
                                                                                                                                                                                                   <
                                                                                                                                                                                                    'Trustee_EG_Cryptograms',
                                                                                                                                                                                                    'Trustee0',
                                                                                                                                                                                                    'Trustee1'
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
                                                                                                                                                                                                  >,
                                                                                                                                                                                                  '1',
                                                                                                                                                                                                  ~sk_sign_trustee1),
                                                                                                                                                                                             %idx_signed_shuffle1
                                                                                                                                                                           ) ▶₀ #vr.9 )
                                                                                                                                                                      case TrusteeBoard_Trustee_Update
                                                                                                                                                                      solve( TAS_Trustee_Trace( 'Trustee0',
                                                                                                                                                                                                pk(~sk_sign_tas),
                                                                                                                                                                                                pk(~sk_encrypt_unused)
                                                                                                                                                                             ) @ #j.8 )
                                                                                                                                                                        case TrusteeMixing_TAS_Init
                                                                                                                                                                        solve( HonestSignatureKey( pk(~sk_sign_tas)
                                                                                                                                                                               ) @ #k.1 )
                                                                                                                                                                          case Mock_TrusteeElectionSetup
                                                                                                                                                                          solve( !Trustee_BBEntry( 'Trustee1',
                                                                                                                                                                                                   'Trustee2',
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
                                                                                                                                                                                                   >,
                                                                                                                                                                                                   sign(<
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
                                                                                                                                                                                                        >,
                                                                                                                                                                                                        '1',
                                                                                                                                                                                                        ~sk_sign_trustee2),
                                                                                                                                                                                                   %idx_signed_shuffle2
                                                                                                                                                                                 ) ▶₁ #vr.9 )
                                                                                                                                                                            case TrusteeBoard_Trustee_Update
                                                                                                                                                                            solve( TAS_Trustee_Trace( 'Trustee0',
                                                                                                                                                                                                      pk(~sk_sign_tas),
                                                                                                                                                                                                      pk(~sk_encrypt_unused)
                                                                                                                                                                                   ) @ #j.8 )
                                                                                                                                                                              case TrusteeMixing_TAS_Init
                                                                                                                                                                              solve( HonestSignatureKey( pk(~sk_sign_tas)
                                                                                                                                                                                     ) @ #k.1 )
                                                                                                                                                                                case Mock_TrusteeElectionSetup
                                                                                                                                                                                solve( Trustee_State_ReceiveBBMessage( 'Trustee1',
                                                                                                                                                                                                                       %idx_signed_shuffle1
                                                                                                                                                                                       ) ▶₀ #j.2 )
                                                                                                                                                                                  case TrusteeBoard_Trustee_Update_case_6
                                                                                                                                                                                  solve( TAS_Trustee_Trace( 'Trustee2',
                                                                                                                                                                                                            pk(~sk_sign_trustee2),
                                                                                                                                                                                                            pk(~sk_encrypt_trustee2)
                                                                                                                                                                                         ) @ #j.8 )
                                                                                                                                                                                    case Mock_TrusteeElectionSetup
                                                                                                                                                                                    solve( HonestSignatureKey( pk(~sk_sign_trustee2)
                                                                                                                                                                                           ) @ #k.1 )
                                                                                                                                                                                      case Mock_TrusteeElectionSetup
                                                                                                                                                                                      solve( TAS_Trustee_Trace( 'Trustee0',
                                                                                                                                                                                                                pk(~sk_sign_tas),
                                                                                                                                                                                                                pk(~sk_encrypt_unused)
                                                                                                                                                                                             ) @ #j.8 )
                                                                                                                                                                                        case TrusteeMixing_TAS_Init
                                                                                                                                                                                        solve( HonestSignatureKey( pk(~sk_sign_tas)
                                                                                                                                                                                               ) @ #k.1 )
                                                                                                                                                                                          case Mock_TrusteeElectionSetup
                                                                                                                                                                                          solve( Trustee_State_ReceiveBBMessage( 'Trustee1',
                                                                                                                                                                                                                                 %idx_signed_shuffle2
                                                                                                                                                                                                 ) ▶₀ #j.3 )
                                                                                                                                                                                            case TrusteeBoard_Trustee_Update_case_5
                                                                                                                                                                                            solve( TAS_Trustee_Trace( 'Trustee0',
                                                                                                                                                                                                                      pk(~sk_sign_tas),
                                                                                                                                                                                                                      pk(~sk_encrypt_unused)
                                                                                                                                                                                                   ) @ #j.8 )
                                                                                                                                                                                              case TrusteeMixing_TAS_Init
                                                                                                                                                                                              solve( HonestSignatureKey( pk(~sk_sign_tas)
                                                                                                                                                                                                     ) @ #k.1 )
                                                                                                                                                                                                case Mock_TrusteeElectionSetup
                                                                                                                                                                                                solve( !Trustee_BBEntry( 'Trustee2',
                                                                                                                                                                                                                         'Trustee1',
                                                                                                                                                                                                                         <
                                                                                                                                                                                                                          <
                                                                                                                                                                                                                           'Trustee_EG_Cryptograms',
                                                                                                                                                                                                                           'Trustee1',
                                                                                                                                                                                                                           'Trustee1'
                                                                                                                                                                                                                          >,
                                                                                                                                                                                                                          ~election_setup,
                                                                                                                                                                                                                          shuffle_order(~ballot_order,
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
                                                                                                                                                                                                                                        ~r.1),
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
                                                                                                                                                                                                                          shuffle_proof(~ballot_order,
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
                                                                                                                                                                                                                                        ~r.1)
                                                                                                                                                                                                                         >,
                                                                                                                                                                                                                         sig_shuffled_ballots,
                                                                                                                                                                                                                         %idx_shuffled_ballots
                                                                                                                                                                                                       ) ▶₂ #j.7 )
                                                                                                                                                                                                  case TrusteeBoard_Trustee_Update
                                                                                                                                                                                                  solve( TAS_Trustee_Trace( 'Trustee1',
                                                                                                                                                                                                                            pk(~sk_sign_trustee1),
                                                                                                                                                                                                                            pk(~sk_encrypt_trustee1)
                                                                                                                                                                                                         ) @ #j.8 )
                                                                                                                                                                                                    case Mock_TrusteeElectionSetup
                                                                                                                                                                                                    solve( HonestSignatureKey( pk(~sk_sign_trustee1)
                                                                                                                                                                                                           ) @ #k.1 )
                                                                                                                                                                                                      case Mock_TrusteeElectionSetup
                                                                                                                                                                                                      solve( TAS_Trustee_Trace( 'Trustee1',
                                                                                                                                                                                                                                pk(~sk_sign_trustee1),
                                                                                                                                                                                                                                pk(~sk_encrypt_trustee1)
                                                                                                                                                                                                             ) @ #j.8 )
                                                                                                                                                                                                        case Mock_TrusteeElectionSetup
                                                                                                                                                                                                        solve( HonestSignatureKey( pk(~sk_sign_trustee1)
                                                                                                                                                                                                               ) @ #k.1 )
                                                                                                                                                                                                          case Mock_TrusteeElectionSetup
                                                                                                                                                                                                          solve( TAS_Trustee_Trace( 'Trustee2',
                                                                                                                                                                                                                                    pk(~sk_sign_trustee2),
                                                                                                                                                                                                                                    pk(~sk_encrypt_trustee2)
                                                                                                                                                                                                                 ) @ #j.8 )
                                                                                                                                                                                                            case Mock_TrusteeElectionSetup
                                                                                                                                                                                                            solve( HonestSignatureKey( pk(~sk_sign_trustee2)
                                                                                                                                                                                                                   ) @ #k.1 )
                                                                                                                                                                                                              case Mock_TrusteeElectionSetup
                                                                                                                                                                                                              solve( TAS_Trustee_Trace( 'Trustee0',
                                                                                                                                                                                                                                        pk(~sk_sign_tas),
                                                                                                                                                                                                                                        pk(~sk_encrypt_unused)
                                                                                                                                                                                                                     ) @ #j.8 )
                                                                                                                                                                                                                case TrusteeMixing_TAS_Init
                                                                                                                                                                                                                solve( HonestSignatureKey( pk(~sk_sign_tas)
                                                                                                                                                                                                                       ) @ #k.1 )
                                                                                                                                                                                                                  case Mock_TrusteeElectionSetup
                                                                                                                                                                                                                  solve( TAS_State_ReceiveTrusteeMessage( (
                                                                                                                                                                                                                                                           %idx_initial_ballots%+
                                                                                                                                                                                                                                                           %1%+
                                                                                                                                                                                                                                                           %1
                                                                                                                                                                                                                                                          )
                                                                                                                                                                                                                         ) ▶₀ #vr.10 )
                                                                                                                                                                                                                    case TrusteeBoard_TAS_ReceiveTrusteeMessage
                                                                                                                                                                                                                    solve( TAS_Trustee_Trace( 'Trustee2',
                                                                                                                                                                                                                                              pk(~sk_sign_trustee2),
                                                                                                                                                                                                                                              pk(~sk_encrypt_trustee2)
                                                                                                                                                                                                                           ) @ #j.8 )
                                                                                                                                                                                                                      case Mock_TrusteeElectionSetup
                                                                                                                                                                                                                      solve( HonestSignatureKey( pk(~sk_sign_trustee2)
                                                                                                                                                                                                                             ) @ #k.1 )
                                                                                                                                                                                                                        case Mock_TrusteeElectionSetup
                                                                                                                                                                                                                        solve( TAS_Trustee_Trace( 'Trustee0',
                                                                                                                                                                                                                                                  pk(~sk_sign_tas),
                                                                                                                                                                                                                                                  pk(~sk_encrypt_unused)
                                                                                                                                                                                                                               ) @ #j.8 )
                                                                                                                                                                                                                          case TrusteeMixing_TAS_Init
                                                                                                                                                                                                                          solve( HonestSignatureKey( pk(~sk_sign_tas)
                                                                                                                                                                                                                                 ) @ #k.1 )
                                                                                                                                                                                                                            case Mock_TrusteeElectionSetup
                                                                                                                                                                                                                            solve( TAS_State_ReceiveTrusteeMessage( (
                                                                                                                                                                                                                                                                     %idx_initial_ballots%+
                                                                                                                                                                                                                                                                     %1
                                                                                                                                                                                                                                                                    )
                                                                                                                                                                                                                                   ) ▶₀ #vr.11 )
                                                                                                                                                                                                                              case TrusteeBoard_TAS_ReceiveTrusteeMessage
                                                                                                                                                                                                                              solve( TAS_Trustee_Trace( 'Trustee0',
                                                                                                                                                                                                                                                        pk(~sk_sign_tas),
                                                                                                                                                                                                                                                        pk(~sk_encrypt_unused)
                                                                                                                                                                                                                                     ) @ #j.8 )
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
                                                                                                                                                                                                                                         ) ▶₁ #j.6 )
                                                                                                                                                                                                                                    case TrusteeBoard_Trustee_Update
                                                                                                                                                                                                                                    solve( Trustee_State_ReceiveBBMessage( 'Trustee1',
                                                                                                                                                                                                                                                                           %idx_initial_ballots
                                                                                                                                                                                                                                           ) ▶₀ #j.4 )
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
                                                                                                                                                                                                                                             ) ▶₁ #vr.12 )
                                                                                                                                                                                                                                        case TrusteeBoard_Trustee_Update
                                                                                                                                                                                                                                        solve( Trustee_State_ReceiveBBMessage( 'Trustee2',
                                                                                                                                                                                                                                                                               %1
                                                                                                                                                                                                                                               ) ▶₀ #j.5 )
                                                                                                                                                                                                                                          case TrusteeMixing_TAS_Init
                                                                                                                                                                                                                                          solve( TAS_State_ReceiveTrusteeMessage( %1
                                                                                                                                                                                                                                                 ) ▶₀ #vr.13 )
                                                                                                                                                                                                                                            case TrusteeMixing_TAS_Init
                                                                                                                                                                                                                                            solve( Trustee_State_ReceiveBBMessage( 'Trustee1',
                                                                                                                                                                                                                                                                                   (
                                                                                                                                                                                                                                                                                    %1%+
                                                                                                                                                                                                                                                                                    %1%+
                                                                                                                                                                                                                                                                                    %1%+
                                                                                                                                                                                                                                                                                    %1%+
                                                                                                                                                                                                                                                                                    %1%+
                                                                                                                                                                                                                                                                                    %1
                                                                                                                                                                                                                                                                                   )
                                                                                                                                                                                                                                                   ) ▶₀ #vr.14 )
                                                                                                                                                                                                                                              case TrusteeBoard_Trustee_Update
                                                                                                                                                                                                                                              solve( TAS_Trustee_Trace( 'Trustee2',
                                                                                                                                                                                                                                                                        pk(~sk_sign_trustee2),
                                                                                                                                                                                                                                                                        pk(~sk_encrypt_trustee2)
                                                                                                                                                                                                                                                     ) @ #j.8 )
                                                                                                                                                                                                                                                case Mock_TrusteeElectionSetup
                                                                                                                                                                                                                                                solve( HonestSignatureKey( pk(~sk_sign_trustee2)
                                                                                                                                                                                                                                                       ) @ #k.1 )
                                                                                                                                                                                                                                                  case Mock_TrusteeElectionSetup
                                                                                                                                                                                                                                                  solve( Trustee_State_ReceiveBBMessage( 'Trustee2',
                                                                                                                                                                                                                                                                                         (
                                                                                                                                                                                                                                                                                          %1%+
                                                                                                                                                                                                                                                                                          %1%+
                                                                                                                                                                                                                                                                                          %1
                                                                                                                                                                                                                                                                                         )
                                                                                                                                                                                                                                                         ) ▶₀ #vr.15 )
                                                                                                                                                                                                                                                    case TrusteeBoard_Trustee_Update
                                                                                                                                                                                                                                                    solve( TAS_Trustee_Trace( 'Trustee2',
                                                                                                                                                                                                                                                                              pk(~sk_sign_trustee2),
                                                                                                                                                                                                                                                                              pk(~sk_encrypt_trustee2)
                                                                                                                                                                                                                                                           ) @ #j.9 )
                                                                                                                                                                                                                                                      case Mock_TrusteeElectionSetup
                                                                                                                                                                                                                                                      solve( HonestSignatureKey( pk(~sk_sign_trustee2)
                                                                                                                                                                                                                                                             ) @ #k.1 )
                                                                                                                                                                                                                                                        case Mock_TrusteeElectionSetup
                                                                                                                                                                                                                                                        solve( TAS_Trustee_Trace( 'Trustee0',
                                                                                                                                                                                                                                                                                  pk(~sk_sign_tas),
                                                                                                                                                                                                                                                                                  pk(~sk_encrypt_unused)
                                                                                                                                                                                                                                                               ) @ #j.9 )
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
                                                                                                                                                                                                                                                                   ) @ #j.8 )
                                                                                                                                                                                                                                                              case TrusteeMixing_Check_Encryption_Proofs_Success
                                                                                                                                                                                                                                                              solve( Trustee_State_ReceiveBBMessage( 'Trustee1',
                                                                                                                                                                                                                                                                                                     (
                                                                                                                                                                                                                                                                                                      %1%+
                                                                                                                                                                                                                                                                                                      %1%+
                                                                                                                                                                                                                                                                                                      %1%+
                                                                                                                                                                                                                                                                                                      %1%+
                                                                                                                                                                                                                                                                                                      %1
                                                                                                                                                                                                                                                                                                     )
                                                                                                                                                                                                                                                                     ) ▶₀ #vr.15 )
                                                                                                                                                                                                                                                                case TrusteeBoard_Trustee_Update
                                                                                                                                                                                                                                                                solve( TAS_Trustee_Trace( 'Trustee1',
                                                                                                                                                                                                                                                                                          pk(~sk_sign_trustee1),
                                                                                                                                                                                                                                                                                          pk(~sk_encrypt_trustee1)
                                                                                                                                                                                                                                                                       ) @ #j.10 )
                                                                                                                                                                                                                                                                  case Mock_TrusteeElectionSetup
                                                                                                                                                                                                                                                                  solve( HonestSignatureKey( pk(~sk_sign_trustee1)
                                                                                                                                                                                                                                                                         ) @ #k.1 )
                                                                                                                                                                                                                                                                    case Mock_TrusteeElectionSetup
                                                                                                                                                                                                                                                                    solve( TAS_Trustee_Trace( 'Trustee1',
                                                                                                                                                                                                                                                                                              pk(~sk_sign_trustee1),
                                                                                                                                                                                                                                                                                              pk(~sk_encrypt_trustee1)
                                                                                                                                                                                                                                                                           ) @ #j.10 )
                                                                                                                                                                                                                                                                      case Mock_TrusteeElectionSetup
                                                                                                                                                                                                                                                                      solve( HonestSignatureKey( pk(~sk_sign_trustee1)
                                                                                                                                                                                                                                                                             ) @ #k.1 )
                                                                                                                                                                                                                                                                        case Mock_TrusteeElectionSetup
                                                                                                                                                                                                                                                                        solve( TAS_Trustee_Trace( 'Trustee2',
                                                                                                                                                                                                                                                                                                  pk(~sk_sign_trustee2),
                                                                                                                                                                                                                                                                                                  pk(~sk_encrypt_trustee2)
                                                                                                                                                                                                                                                                               ) @ #j.10 )
                                                                                                                                                                                                                                                                          case Mock_TrusteeElectionSetup
                                                                                                                                                                                                                                                                          solve( HonestSignatureKey( pk(~sk_sign_trustee2)
                                                                                                                                                                                                                                                                                 ) @ #k.1 )
                                                                                                                                                                                                                                                                            case Mock_TrusteeElectionSetup
                                                                                                                                                                                                                                                                            solve( TAS_Trustee_Trace( 'Trustee0',
                                                                                                                                                                                                                                                                                                      pk(~sk_sign_tas),
                                                                                                                                                                                                                                                                                                      pk(~sk_encrypt_unused)
                                                                                                                                                                                                                                                                                   ) @ #j.10 )
                                                                                                                                                                                                                                                                              case TrusteeMixing_TAS_Init
                                                                                                                                                                                                                                                                              solve( HonestSignatureKey( pk(~sk_sign_tas)
                                                                                                                                                                                                                                                                                     ) @ #k.1 )
                                                                                                                                                                                                                                                                                case Mock_TrusteeElectionSetup
                                                                                                                                                                                                                                                                                solve( Trustee_Sent_Msg_Trace( 'Trustee1',
                                                                                                                                                                                                                                                                                                               <
                                                                                                                                                                                                                                                                                                                <
                                                                                                                                                                                                                                                                                                                 'Trustee_EG_Cryptograms',
                                                                                                                                                                                                                                                                                                                 'Trustee1',
                                                                                                                                                                                                                                                                                                                 'Trustee1'
                                                                                                                                                                                                                                                                                                                >,
                                                                                                                                                                                                                                                                                                                ~election_setup,
                                                                                                                                                                                                                                                                                                                shuffle_order(~ballot_order,
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
                                                                                                                                                                                                                                                                                                                              ~r.1),
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
                                                                                                                                                                                                                                                                                                                shuffle_proof(~ballot_order,
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
                                                                                                                                                                                                                                                                                                                              ~r.1)
                                                                                                                                                                                                                                                                                                               >
                                                                                                                                                                                                                                                                                       ) @ #j.9 )
                                                                                                                                                                                                                                                                                  case TrusteeMixing_Trustee_1_Shuffle
                                                                                                                                                                                                                                                                                  solve( Trustee_State_ReceiveBBMessage( 'Trustee2',
                                                                                                                                                                                                                                                                                                                         (
                                                                                                                                                                                                                                                                                                                          %1%+
                                                                                                                                                                                                                                                                                                                          %1
                                                                                                                                                                                                                                                                                                                         )
                                                                                                                                                                                                                                                                                         ) ▶₀ #vr.15 )
                                                                                                                                                                                                                                                                                    case TrusteeBoard_Trustee_Update
                                                                                                                                                                                                                                                                                    solve( TAS_Trustee_Trace( 'Trustee0',
                                                                                                                                                                                                                                                                                                              pk(~sk_sign_tas),
                                                                                                                                                                                                                                                                                                              pk(~sk_encrypt_unused)
                                                                                                                                                                                                                                                                                           ) @ #j.10 )
                                                                                                                                                                                                                                                                                      case TrusteeMixing_TAS_Init
                                                                                                                                                                                                                                                                                      solve( HonestSignatureKey( pk(~sk_sign_tas)
                                                                                                                                                                                                                                                                                             ) @ #k.1 )
                                                                                                                                                                                                                                                                                        case Mock_TrusteeElectionSetup
                                                                                                                                                                                                                                                                                        solve( Trustee_State_ReceiveBBMessage( 'Trustee1',
                                                                                                                                                                                                                                                                                                                               (
                                                                                                                                                                                                                                                                                                                                %1%+
                                                                                                                                                                                                                                                                                                                                %1%+
                                                                                                                                                                                                                                                                                                                                %1%+
                                                                                                                                                                                                                                                                                                                                %1
                                                                                                                                                                                                                                                                                                                               )
                                                                                                                                                                                                                                                                                               ) ▶₀ #vr.16 )
                                                                                                                                                                                                                                                                                          case TrusteeBoard_Trustee_Update
                                                                                                                                                                                                                                                                                          solve( TAS_Trustee_Trace( 'Trustee1',
                                                                                                                                                                                                                                                                                                                    pk(~sk_sign_trustee1),
                                                                                                                                                                                                                                                                                                                    pk(~sk_encrypt_trustee1)
                                                                                                                                                                                                                                                                                                 ) @ #j.10 )
                                                                                                                                                                                                                                                                                            case Mock_TrusteeElectionSetup
                                                                                                                                                                                                                                                                                            solve( HonestSignatureKey( pk(~sk_sign_trustee1)
                                                                                                                                                                                                                                                                                                   ) @ #k.1 )
                                                                                                                                                                                                                                                                                              case Mock_TrusteeElectionSetup
                                                                                                                                                                                                                                                                                              solve( TAS_Trustee_Trace( 'Trustee0',
                                                                                                                                                                                                                                                                                                                        pk(~sk_sign_tas),
                                                                                                                                                                                                                                                                                                                        pk(~sk_encrypt_unused)
                                                                                                                                                                                                                                                                                                     ) @ #j.10 )
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
