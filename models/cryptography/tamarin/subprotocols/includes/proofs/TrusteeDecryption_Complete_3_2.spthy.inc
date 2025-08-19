simplify
solve( !TAS_ElectionSetup_Complete( election_setup ) ▶₀ #i )
  case Mock_TrusteeElectionSetup
  solve( !TAS_Ballot_Set( b ) ▶₁ #i )
    case Mock_GenerateBallotSet
    solve( !TAS_BBEntry( 'Trustee2',
                         <'Trustee_Decrypted_Ballots', ~election_setup, 'Trustee2', ~ballots>,
                         sig_decrypted_ballots2, %idx_decrypted_ballots2
           ) ▶₂ #i )
      case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_2
      solve( !TAS_BBEntry( 'Trustee3',
                           <'Trustee_Decrypted_Ballots', ~election_setup, 'Trustee3', ~ballots>,
                           sig_decrypted_ballots3, %idx_decrypted_ballots3
             ) ▶₃ #i )
        case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_2
        solve( TAS_Trustee_Trace( 'Trustee2', pk(~sk_sign_trustee2),
                                  pk(~sk_encrypt_trustee2)
               ) @ #j )
          case Mock_TrusteeElectionSetup
          solve( HonestSignatureKey( pk(~sk_sign_trustee2) ) @ #k )
            case Mock_TrusteeElectionSetup
            solve( TAS_Trustee_Trace( 'Trustee3', pk(~sk_sign_trustee3),
                                      pk(~sk_encrypt_trustee3)
                   ) @ #j.1 )
              case Mock_TrusteeElectionSetup
              solve( HonestSignatureKey( pk(~sk_sign_trustee3) ) @ #k )
                case Mock_TrusteeElectionSetup
                solve( TAS_State_ReceiveTrusteeMessage( %idx_decrypted_ballots2
                       ) ▶₀ #vr.2 )
                  case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_10
                  solve( TAS_Trustee_Trace( 'Trustee2', pk(~sk_sign_trustee2),
                                            pk(~sk_encrypt_trustee2)
                         ) @ #j.1 )
                    case Mock_TrusteeElectionSetup
                    solve( HonestSignatureKey( pk(~sk_sign_trustee2) ) @ #k )
                      case Mock_TrusteeElectionSetup
                      solve( !TAS_BBEntry( 'Trustee2',
                                           <'Trustee_Partial_Decryption', ~election_setup, 'Trustee2',
                                            ny_partial_decrypt(ny_encrypt_c1(~ballots,
                                                                             threshold_pubkey(check_value(~private_share1),
                                                                                              check_value(~private_share2),
                                                                                              check_value(~private_share3)),
                                                                             r.1),
                                                               ny_encrypt_c2(~ballots,
                                                                             threshold_pubkey(check_value(~private_share1),
                                                                                              check_value(~private_share2),
                                                                                              check_value(~private_share3)),
                                                                             r.1),
                                                               ~private_share2),
                                            ny_partial_dec_proof(ny_encrypt_c1(~ballots,
                                                                               threshold_pubkey(check_value(~private_share1),
                                                                                                check_value(~private_share2),
                                                                                                check_value(~private_share3)),
                                                                               r.1),
                                                                 ny_encrypt_c2(~ballots,
                                                                               threshold_pubkey(check_value(~private_share1),
                                                                                                check_value(~private_share2),
                                                                                                check_value(~private_share3)),
                                                                               r.1),
                                                                 ~private_share2)
                                           >,
                                           sig_pd2, %idx_pd2
                             ) ▶₁ #vr.3 )
                        case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_2
                        solve( TAS_Trustee_Trace( 'Trustee2', pk(~sk_sign_trustee2),
                                                  pk(~sk_encrypt_trustee2)
                               ) @ #j.1 )
                          case Mock_TrusteeElectionSetup
                          solve( HonestSignatureKey( pk(~sk_sign_trustee2) ) @ #k )
                            case Mock_TrusteeElectionSetup
                            solve( !TAS_BBEntry( 'Trustee3',
                                                 <'Trustee_Partial_Decryption', ~election_setup, 'Trustee3',
                                                  ny_partial_decrypt(ny_encrypt_c1(~ballots,
                                                                                   threshold_pubkey(check_value(~private_share1),
                                                                                                    check_value(~private_share2),
                                                                                                    check_value(~private_share3)),
                                                                                   r.1),
                                                                     ny_encrypt_c2(~ballots,
                                                                                   threshold_pubkey(check_value(~private_share1),
                                                                                                    check_value(~private_share2),
                                                                                                    check_value(~private_share3)),
                                                                                   r.1),
                                                                     ~private_share3),
                                                  ny_partial_dec_proof(ny_encrypt_c1(~ballots,
                                                                                     threshold_pubkey(check_value(~private_share1),
                                                                                                      check_value(~private_share2),
                                                                                                      check_value(~private_share3)),
                                                                                     r.1),
                                                                       ny_encrypt_c2(~ballots,
                                                                                     threshold_pubkey(check_value(~private_share1),
                                                                                                      check_value(~private_share2),
                                                                                                      check_value(~private_share3)),
                                                                                     r.1),
                                                                       ~private_share3)
                                                 >,
                                                 sig_pd3, %idx_pd3
                                   ) ▶₂ #vr.3 )
                              case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_2
                              solve( TAS_Trustee_Trace( 'Trustee3', pk(~sk_sign_trustee3),
                                                        pk(~sk_encrypt_trustee3)
                                     ) @ #j.1 )
                                case Mock_TrusteeElectionSetup
                                solve( HonestSignatureKey( pk(~sk_sign_trustee3) ) @ #k )
                                  case Mock_TrusteeElectionSetup
                                  solve( TAS_State_ReceiveTrusteeMessage( %idx_decrypted_ballots3
                                         ) ▶₀ #vr.6 )
                                    case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_11
                                    solve( TAS_Trustee_Trace( 'Trustee2', pk(~sk_sign_trustee2),
                                                              pk(~sk_encrypt_trustee2)
                                           ) @ #j.1 )
                                      case Mock_TrusteeElectionSetup
                                      solve( HonestSignatureKey( pk(~sk_sign_trustee2) ) @ #k )
                                        case Mock_TrusteeElectionSetup
                                        solve( !TAS_BBEntry( 'Trustee2',
                                                             <'Trustee_Partial_Decryption', ~election_setup,
                                                              'Trustee2',
                                                              ny_partial_decrypt(ny_encrypt_c1(~ballots,
                                                                                               threshold_pubkey(check_value(~private_share1),
                                                                                                                check_value(~private_share2),
                                                                                                                check_value(~private_share3)),
                                                                                               r.2),
                                                                                 ny_encrypt_c2(~ballots,
                                                                                               threshold_pubkey(check_value(~private_share1),
                                                                                                                check_value(~private_share2),
                                                                                                                check_value(~private_share3)),
                                                                                               r.2),
                                                                                 ~private_share2),
                                                              ny_partial_dec_proof(ny_encrypt_c1(~ballots,
                                                                                                 threshold_pubkey(check_value(~private_share1),
                                                                                                                  check_value(~private_share2),
                                                                                                                  check_value(~private_share3)),
                                                                                                 r.2),
                                                                                   ny_encrypt_c2(~ballots,
                                                                                                 threshold_pubkey(check_value(~private_share1),
                                                                                                                  check_value(~private_share2),
                                                                                                                  check_value(~private_share3)),
                                                                                                 r.2),
                                                                                   ~private_share2)
                                                             >,
                                                             sig_pd2, %idx_pd2
                                               ) ▶₁ #vr.7 )
                                          case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_2
                                          solve( TAS_Trustee_Trace( 'Trustee2', pk(~sk_sign_trustee2),
                                                                    pk(~sk_encrypt_trustee2)
                                                 ) @ #j.1 )
                                            case Mock_TrusteeElectionSetup
                                            solve( HonestSignatureKey( pk(~sk_sign_trustee2) ) @ #k )
                                              case Mock_TrusteeElectionSetup
                                              solve( !TAS_BBEntry( 'Trustee3',
                                                                   <'Trustee_Partial_Decryption',
                                                                    ~election_setup, 'Trustee3',
                                                                    ny_partial_decrypt(ny_encrypt_c1(~ballots,
                                                                                                     threshold_pubkey(check_value(~private_share1),
                                                                                                                      check_value(~private_share2),
                                                                                                                      check_value(~private_share3)),
                                                                                                     r.1),
                                                                                       ny_encrypt_c2(~ballots,
                                                                                                     threshold_pubkey(check_value(~private_share1),
                                                                                                                      check_value(~private_share2),
                                                                                                                      check_value(~private_share3)),
                                                                                                     r.1),
                                                                                       ~private_share3),
                                                                    ny_partial_dec_proof(ny_encrypt_c1(~ballots,
                                                                                                       threshold_pubkey(check_value(~private_share1),
                                                                                                                        check_value(~private_share2),
                                                                                                                        check_value(~private_share3)),
                                                                                                       r.1),
                                                                                         ny_encrypt_c2(~ballots,
                                                                                                       threshold_pubkey(check_value(~private_share1),
                                                                                                                        check_value(~private_share2),
                                                                                                                        check_value(~private_share3)),
                                                                                                       r.1),
                                                                                         ~private_share3)
                                                                   >,
                                                                   sig_pd3, %idx_pd3.1
                                                     ) ▶₂ #vr.7 )
                                                case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_2
                                                solve( TAS_Trustee_Trace( 'Trustee3', pk(~sk_sign_trustee3),
                                                                          pk(~sk_encrypt_trustee3)
                                                       ) @ #j.1 )
                                                  case Mock_TrusteeElectionSetup
                                                  solve( HonestSignatureKey( pk(~sk_sign_trustee3) ) @ #k )
                                                    case Mock_TrusteeElectionSetup
                                                    solve( TAS_State_ReceiveTrusteeMessage( %idx ) ▶₀ #vr.8 )
                                                      case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_10
                                                      solve( TAS_Trustee_Trace( 'Trustee3',
                                                                                pk(~sk_sign_trustee3),
                                                                                pk(~sk_encrypt_trustee3)
                                                             ) @ #j.1 )
                                                        case Mock_TrusteeElectionSetup
                                                        solve( HonestSignatureKey( pk(~sk_sign_trustee3)
                                                               ) @ #k )
                                                          case Mock_TrusteeElectionSetup
                                                          solve( !Trustee_BBEntry( 'Trustee2', 'Trustee0',
                                                                                   <'TAS_Mixed_Cryptograms',
                                                                                    ~election_setup,
                                                                                    ny_encrypt_c1(~ballots,
                                                                                                  threshold_pubkey(check_value(~private_share1),
                                                                                                                   check_value(~private_share2),
                                                                                                                   check_value(~private_share3)),
                                                                                                  r.1),
                                                                                    ny_encrypt_c2(~ballots,
                                                                                                  threshold_pubkey(check_value(~private_share1),
                                                                                                                   check_value(~private_share2),
                                                                                                                   check_value(~private_share3)),
                                                                                                  r.1)
                                                                                   >,
                                                                                   sig_mixed_cryptograms,
                                                                                   %idx_mixed_cryptograms
                                                                 ) ▶₁ #vr.9 )
                                                            case TrusteeBoard_Trustee_Update_case_5
                                                            solve( TAS_Trustee_Trace( 'Trustee0',
                                                                                      pk(~sk_sign_tas),
                                                                                      pk(~sk_encrypt_unused.1)
                                                                   ) @ #j.1 )
                                                              case Mock_TrusteeMixing
                                                              solve( HonestSignatureKey( pk(~sk_sign_tas)
                                                                     ) @ #k )
                                                                case Mock_TrusteeElectionSetup
                                                                solve( TAS_State_ReceiveTrusteeMessage( %idx_pd3
                                                                       ) ▶₀ #vr.9 )
                                                                  case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_8
                                                                  solve( TAS_Trustee_Trace( 'Trustee0',
                                                                                            pk(~sk_sign_tas),
                                                                                            pk(~sk_encrypt_unused)
                                                                         ) @ #j.2 )
                                                                    case Mock_TrusteeMixing
                                                                    solve( HonestSignatureKey( pk(~sk_sign_tas)
                                                                           ) @ #k )
                                                                      case Mock_TrusteeElectionSetup
                                                                      solve( !Trustee_BBEntry( 'Trustee3',
                                                                                               'Trustee0',
                                                                                               <
                                                                                                'TAS_Mixed_Cryptograms',
                                                                                                ~election_setup,
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
                                                                                               sig_mixed_cryptograms,
                                                                                               %idx_mixed_cryptograms.1
                                                                             ) ▶₁ #vr.10 )
                                                                        case TrusteeBoard_Trustee_Update_case_5
                                                                        solve( TAS_Trustee_Trace( 'Trustee0',
                                                                                                  pk(~sk_sign_tas),
                                                                                                  pk(~sk_encrypt_unused)
                                                                               ) @ #j.2 )
                                                                          case Mock_TrusteeMixing
                                                                          solve( HonestSignatureKey( pk(~sk_sign_tas)
                                                                                 ) @ #k )
                                                                            case Mock_TrusteeElectionSetup
                                                                            solve( Trustee_State_ReceiveBBMessage( 'Trustee2',
                                                                                                                   %idx_mixed_cryptograms
                                                                                   ) ▶₀ #vr.11 )
                                                                              case Mock_TrusteeMixing
                                                                              solve( TAS_State_ReceiveTrusteeMessage( %1
                                                                                     ) ▶₀ #vr.12 )
                                                                                case Mock_TrusteeMixing
                                                                                solve( Trustee_State_ReceiveBBMessage( 'Trustee3',
                                                                                                                       %1
                                                                                       ) ▶₀ #vr.13 )
                                                                                  case Mock_TrusteeMixing
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
