simplify
solve( Trustee_Trace_Error( t, e ) @ #i )
  case ElectionKeyGeneration_Trustee_Abort
  by contradiction /* from formulas */
next
  case ElectionKeyVerification_Trustee_Error_Invalid_Pairwise_Share
  by sorry
next
  case TrusteeBoard_Trustee_Error
  solve( (∃ e_msg e_sig %e_idx #j.
           (Trustee_BBEntry_Trace( t, sender, z, e_msg, e_sig, %e_idx ) @ #j)
          ∧
           #j < #i)  ∥
         ((sender = t) ∧
          (∀ #j. (Trustee_Sent_Msg_Trace( t, msg ) @ #j) ⇒ ¬(#j < #i))) )
    case case_1
    by sorry
  next
    case case_2
    solve( Trustee_State_ReceiveBBMessage( sender, %idx ) ▶₀ #i )
      case ElectionKeyGeneration_TAS_Init_case_1
      solve( !TAS_BBEntry( 'Trustee1', msg, sig, %1 ) ▶₁ #i )
        case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_1
        solve( !KU( sign(msg, x, ~sk_sign_trustee1) ) @ #vk.4 )
          case TrusteeBoard_Reveal_BB_Message_case_1
          by contradiction /* from formulas */
        next
          case TrusteeBoard_Reveal_BB_Message_case_2
          by contradiction /* from formulas */
        next
          case TrusteeBoard_Reveal_BB_Message_case_3
          by contradiction /* from formulas */
        next
          case TrusteeBoard_Reveal_BB_Message_case_4
          by contradiction /* from formulas */
        next
          case TrusteeBoard_Reveal_BB_Message_case_5
          by contradiction /* from formulas */
        next
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
                next
                  case split_case_2
                  by sorry
                qed
              qed
            qed
          qed
        qed
      next
        case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_2
        by contradiction /* from formulas */
      next
        case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_3
        by contradiction /* from formulas */
      next
        case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_4
        by contradiction /* from formulas */
      next
        case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_5
        by contradiction /* from formulas */
      next
        case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_6
        by contradiction /* from formulas */
      qed
    next
      case ElectionKeyGeneration_TAS_Init_case_2
      by sorry
    next
      case ElectionKeyGeneration_TAS_Init_case_3
      by sorry
    next
      case TrusteeBoard_Trustee_Update_case_01
      by sorry
    next
      case TrusteeBoard_Trustee_Update_case_02
      by sorry
    next
      case TrusteeBoard_Trustee_Update_case_03
      by sorry
    next
      case TrusteeBoard_Trustee_Update_case_04
      by sorry
    next
      case TrusteeBoard_Trustee_Update_case_05
      by sorry
    next
      case TrusteeBoard_Trustee_Update_case_06
      by sorry
    next
      case TrusteeBoard_Trustee_Update_case_07
      by sorry
    next
      case TrusteeBoard_Trustee_Update_case_08
      by sorry
    next
      case TrusteeBoard_Trustee_Update_case_09
      by sorry
    next
      case TrusteeBoard_Trustee_Update_case_10
      by sorry
    next
      case TrusteeBoard_Trustee_Update_case_11
      by sorry
    next
      case TrusteeBoard_Trustee_Update_case_12
      by sorry
    next
      case TrusteeBoard_Trustee_Update_case_13
      by sorry
    next
      case TrusteeBoard_Trustee_Update_case_14
      by sorry
    next
      case TrusteeBoard_Trustee_Update_case_15
      by sorry
    next
      case TrusteeBoard_Trustee_Update_case_16
      by sorry
    next
      case TrusteeBoard_Trustee_Update_case_17
      by sorry
    next
      case TrusteeBoard_Trustee_Update_case_18
      by sorry
    qed
  qed
qed
