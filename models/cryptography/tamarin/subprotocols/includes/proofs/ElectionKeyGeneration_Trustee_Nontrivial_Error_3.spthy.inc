simplify
solve( Trustee_Trace_Error( t, e ) @ #i )
  case TrusteeBoard_Trustee_Error
  solve( (∃ e_msg e_sig %e_idx #j.
           (Trustee_BBEntry_Trace( t, sender, z, e_msg, e_sig, %e_idx ) @ #j)
          ∧
           #j < #i)  ∥
         ((sender = t) ∧
          (∀ #j. (Trustee_Sent_Msg_Trace( t, msg ) @ #j) ⇒ ¬(#j < #i))) )
    case case_2
    solve( Trustee_State_ReceiveBBMessage( sender, %idx ) ▶₀ #i )
      case ElectionKeyGeneration_TAS_Init_case_1
      solve( !TAS_BBEntry( 'Trustee1', msg, sig, %1 ) ▶₁ #i )
        case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_1
        solve( !KU( sign(msg, x, ~sk_sign_trustee1) ) @ #vk.4 )
          case c_sign
          solve( TAS_State_ReceiveTrusteeMessage( %1 ) ▶₀ #vr.2 )
            case ElectionKeyGeneration_TAS_Init
            solve( HonestSignatureKey( pk(~sk_sign_trustee1) ) @ #k )
              case Mock_TrusteeElectionSetup
              solve( TAS_Trustee_Trace( 'Trustee1', pk(~sk_sign_trustee1),
                                        pk(~sk_encrypt_trustee1)
                     ) @ #j )
                case Mock_TrusteeElectionSetup
                solve( splitEqs(0) )
                  case split_case_1
                  solve( !KU( ~sk_sign_trustee1 ) @ #vk.6 )
                    case ElectionKeyGeneration_Reveal_Trustee_Keys
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
