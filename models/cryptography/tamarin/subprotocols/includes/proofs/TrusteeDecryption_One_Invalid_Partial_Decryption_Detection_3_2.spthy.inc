simplify
solve( !Trustee_Decrypt_Active( t ) ▶₀ #i )
  case TrusteeDecryption_TAS_Init_case_1
  solve( !TAS_BBEntry( pd_t,
                       <'Trustee_Partial_Decryption', election_setup, pd_t, pd, pd_proof>,
                       sig_pd, %idx_pd
         ) ▶₁ #i )
    case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_1
    solve( !Trustee_ElectionSetup( 'Trustee2', election_setup ) ▶₂ #i )
      case Mock_TrusteeElectionSetup
      solve( TAS_Trustee_Trace( 'Trustee1', pk(~sk_sign_trustee1),
                                pk(~sk_encrypt_trustee1)
             ) @ #j )
        case Mock_TrusteeElectionSetup
        solve( HonestSignatureKey( pk(~sk_sign_trustee1) ) @ #k )
          case Mock_TrusteeElectionSetup
          solve( splitEqs(0) )
            case split_case_1
            solve( !KU( sign(<'Trustee_Partial_Decryption', ~election_setup,
                              'Trustee1', pd, pd_proof>,
                             x, ~sk_sign_trustee1)
                   ) @ #vk.6 )
              case c_sign
              solve( !KU( ~sk_sign_trustee1 ) @ #vk.13 )
                case TrusteeDecryption_Reveal_Trustee_Keys
                solve( TAS_State_ReceiveTrusteeMessage( %idx_pd ) ▶₀ #vr.4 )
                  case Mock_TrusteeMixing
                  solve( !KU( ~election_setup ) @ #vk.9 )
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
