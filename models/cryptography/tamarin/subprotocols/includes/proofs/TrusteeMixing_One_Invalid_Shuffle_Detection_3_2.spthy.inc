simplify
solve( !Trustee_Mix_Active( t ) ▶₀ #i )
  case TrusteeMixing_TAS_Init_case_1
  solve( !Trustee_BBEntry( 'Trustee1', si,
                           <<'Trustee_EG_Cryptograms', sh, si>, election_setup, ballot_order,
                            ballot_set, shuffle_proof>,
                           sig_invalid_shuffle, %idx_invalid_shuffle
         ) ▶₁ #i )
    case TrusteeBoard_Trustee_Update_case_02
    solve( !Trustee_ElectionSetup( 'Trustee1', election_setup ) ▶₂ #i )
      case Mock_TrusteeElectionSetup
      solve( !Trustee_Secret_Keys( 'Trustee1', sk_sign, sk_encrypt_unused
             ) ▶₃ #i )
        case Mock_TrusteeElectionSetup
        solve( TAS_Trustee_Trace( 'Trustee2', pk(~sk_sign_trustee2),
                                  pk(~sk_encrypt_trustee2)
               ) @ #j )
          case Mock_TrusteeElectionSetup
          solve( HonestSignatureKey( pk(~sk_sign_trustee2) ) @ #k )
            case Mock_TrusteeElectionSetup
            solve( splitEqs(0) )
              case split_case_1
              solve( !KU( sign(<<'Trustee_EG_Cryptograms', sh, 'Trustee2'>,
                                ~election_setup, ballot_order, ballot_set, shuffle_proof>,
                               x, ~sk_sign_trustee2)
                     ) @ #vk.6 )
                case c_sign
                solve( !KU( ~sk_sign_trustee2 ) @ #vk.17 )
                  case TrusteeMixing_Reveal_Trustee_Keys
                  solve( !KU( ~election_setup ) @ #vk.11 )
                    case Mock_TrusteeElectionSetup
                    solve( TAS_State_ReceiveTrusteeMessage( %idx_invalid_shuffle
                           ) ▶₀ #vr.4 )
                      case TrusteeMixing_TAS_Init
                      solve( Trustee_State_ReceiveBBMessage( 'Trustee1', %1 ) ▶₀ #vr.3 )
                        case TrusteeMixing_TAS_Init
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
