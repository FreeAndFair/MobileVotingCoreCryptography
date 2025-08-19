simplify
solve( !Trustee_Decrypt_Active( t ) ▶₀ #i )
  case TrusteeDecryption_TAS_Init_case_1
  solve( !Trustee_ElectionSetup( 'Trustee2', election_setup ) ▶₂ #i )
    case Mock_TrusteeElectionSetup
    solve( !ElectionPublicKey( threshold_pubkey(check_value(ps1),
                                                check_value(ps2), check_value(ps3))
           ) ▶₃ #i )
      case Mock_ElectionKeyGeneration
      solve( !Trustee_Private_Share( 'Trustee2', ps_trustee ) ▶₄ #i )
        case Mock_ElectionKeyGeneration
        solve( !Trustee_Private_Share( 'Trustee1', ~private_share1 ) ▶₅ #i )
          case Mock_ElectionKeyGeneration
          solve( !Trustee_Private_Share( 'Trustee2', ~private_share2 ) ▶₆ #i )
            case Mock_ElectionKeyGeneration
            solve( !Trustee_Private_Share( 'Trustee3', ~private_share3 ) ▶₇ #i )
              case Mock_ElectionKeyGeneration
              solve( !Trustee_Secret_Keys( 'Trustee2', sk_sign, sk_encrypt_unused
                     ) ▶₈ #i )
                case Mock_TrusteeElectionSetup
                solve( !Trustee_BBEntry( 'Trustee2', 'Trustee0',
                                         <'TAS_Mixed_Cryptograms', ~election_setup,
                                          ny_encrypt_c1(ballot,
                                                        threshold_pubkey(check_value(~private_share1),
                                                                         check_value(~private_share2),
                                                                         check_value(~private_share3)),
                                                        r),
                                          ny_encrypt_c2(ballot,
                                                        threshold_pubkey(check_value(~private_share1),
                                                                         check_value(~private_share2),
                                                                         check_value(~private_share3)),
                                                        r)
                                         >,
                                         sig_mixed_cryptograms, %idx_mixed_cryptograms
                       ) ▶₁ #i )
                  case TrusteeBoard_Trustee_Update_case_5
                  solve( TAS_Trustee_Trace( 'Trustee0', pk(~sk_sign_tas),
                                            pk(~sk_encrypt_unused.1)
                         ) @ #j )
                    case Mock_TrusteeMixing
                    solve( HonestSignatureKey( pk(~sk_sign_tas) ) @ #k )
                      case Mock_TrusteeElectionSetup
                      solve( Trustee_State_ReceiveBBMessage( 'Trustee2', %idx_mixed_cryptograms
                             ) ▶₀ #vr.3 )
                        case Mock_TrusteeMixing
                        solve( TAS_State_ReceiveTrusteeMessage( %1 ) ▶₀ #vr.4 )
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
