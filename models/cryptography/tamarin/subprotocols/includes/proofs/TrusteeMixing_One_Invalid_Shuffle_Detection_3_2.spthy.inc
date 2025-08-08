simplify
solve( !Trustee_Mix_Active( t ) ▶₀ #i )
  case TrusteeMixing_TAS_Init_case_1
  solve( !Trustee_BBEntry( 'Trustee1', si,
                           <<'Trustee_EG_Cryptograms', sh, si>, election_setup, ballot_order,
                            ballot_set, shuffle_proof>,
                           sig_invalid_shuffle, %idx_invalid_shuffle
         ) ▶₁ #i )
    case TrusteeBoard_Trustee_Update_case_01
    by sorry /* removed */
  next
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
                case TrusteeBoard_Reveal_BB_Message_case_01
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_02
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_03
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_04
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_05
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_06
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_07
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_08
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_09
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_10
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_11
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_12
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_13
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_14
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_15
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_16
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_17
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_18
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_19
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_20
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_21
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_22
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_23
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_24
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_25
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_26
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_27
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_28
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_29
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_30
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_31
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_32
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_33
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_34
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_35
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_36
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_37
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_38
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_39
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_40
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_41
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_42
                by sorry
              next
                case TrusteeBoard_Reveal_BB_Message_case_43
                by sorry
              next
                case c_sign
                solve( !KU( ~sk_sign_trustee2 ) @ #vk.17 )
                  case TrusteeBoard_Reveal_BB_Message_case_01
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_02
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_03
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_04
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_05
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_06
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_07
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_08
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_09
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_10
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_11
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_12
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_13
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_14
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_15
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_16
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_17
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_18
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_19
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_20
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_21
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_22
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_23
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_24
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_25
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_26
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_27
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_28
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_29
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_30
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_31
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_32
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_33
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_34
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_35
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_36
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_37
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_38
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_39
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_40
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_41
                  by sorry
                next
                  case TrusteeBoard_Reveal_BB_Message_case_42
                  by sorry
                next
                  case TrusteeMixing_Reveal_Trustee_Keys
                  solve( !KU( ~election_setup ) @ #vk.11 )
                    case Mock_TrusteeElectionSetup
                    solve( TAS_State_ReceiveTrusteeMessage( %idx_invalid_shuffle
                           ) ▶₀ #vr.4 )
                      case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_01
                      by sorry /* removed */
                    next
                      case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_02
                      by sorry
                    next
                      case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_03
                      by sorry
                    next
                      case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_04
                      by sorry
                    next
                      case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_05
                      by sorry
                    next
                      case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_06
                      by sorry
                    next
                      case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_07
                      by sorry
                    next
                      case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_08
                      by sorry
                    next
                      case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_09
                      by sorry
                    next
                      case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_10
                      by sorry
                    next
                      case TrusteeBoard_TAS_ReceiveTrusteeMessage_case_11
                      by sorry
                    next
                      case TrusteeMixing_TAS_Init
                      solve( Trustee_State_ReceiveBBMessage( 'Trustee1', %1 ) ▶₀ #vr.3 )
                        case TrusteeMixing_TAS_Init
                        SOLVED // trace found
                      qed
                    qed
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_01
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_02
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_03
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_04
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_05
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_06
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_07
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_08
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_09
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_10
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_11
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_12
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_13
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_14
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_15
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_16
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_17
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_18
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_19
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_20
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_21
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_22
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_23
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_24
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_25
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_26
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_27
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_28
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_29
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_30
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_31
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_32
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_33
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_34
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_35
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_36
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_37
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_38
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_39
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_40
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_41
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_42
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_43
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_44
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_45
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_46
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_47
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_48
                    by sorry
                  next
                    case TrusteeBoard_Reveal_BB_Message_case_49
                    by sorry
                  qed
                qed
              qed
            next
              case split_case_2
              by contradiction /* from formulas */
            qed
          qed
        qed
      qed
    qed
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
    by contradiction /* from formulas */
  next
    case TrusteeBoard_Trustee_Update_case_08
    by contradiction /* from formulas */
  next
    case TrusteeBoard_Trustee_Update_case_09
    by contradiction /* from formulas */
  next
    case TrusteeBoard_Trustee_Update_case_10
    by contradiction /* from formulas */
  qed
next
  case TrusteeMixing_TAS_Init_case_2
  by sorry
next
  case TrusteeMixing_TAS_Init_case_3
  by sorry
next
  case TrusteeMixing_TAS_Init_case_4
  by sorry
qed
