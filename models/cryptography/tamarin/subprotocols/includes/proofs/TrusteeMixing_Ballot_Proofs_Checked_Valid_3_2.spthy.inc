simplify
solve( !Trustee_BBEntry( t, 'Trustee0',
                         <<'Trustee_NY_Cryptograms', 'Trustee0', 'Trustee0'>,
                          election_setup, initial_ballot_order, ny_encrypt_c1(b, k, r),
                          ny_encrypt_c2(b, k, r), ny_encrypt_p(b, k, r)>,
                         sig_initial_ballots, %idx_initial_ballots
       ) ▶₁ #i )
  case TrusteeBoard_Trustee_Update_case_3
  solve( (¬('Trustee0' = t))  ∥
         (∃ #j.
           (Trustee_Sent_Msg_Trace( t,
                                    <<'Trustee_NY_Cryptograms', 'Trustee0', 'Trustee0'>,
                                     ~election_setup, ~ballot_order,
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
                                    >
            ) @ #j)
          ∧
           #j < #vr) )
    case case_1
    solve( !Trustee_Mix_Active( t ) ▶₀ #i )
      case TrusteeMixing_TAS_Init_case_1
      solve( !Trustee_ElectionSetup( 'Trustee1', ~election_setup
             ) ▶₂ #i )
        case Mock_TrusteeElectionSetup
        solve( !Trustee_Secret_Keys( 'Trustee1', sk_sign, sk_encrypt_unused
               ) ▶₃ #i )
          case Mock_TrusteeElectionSetup
          solve( TAS_Trustee_Trace( 'Trustee0', pk(~sk_sign_tas),
                                    pk(~sk_encrypt_unused)
                 ) @ #j )
            case TrusteeMixing_TAS_Init
            solve( HonestSignatureKey( pk(~sk_sign_tas) ) @ #k )
              case Mock_TrusteeElectionSetup
              solve( Trustee_State_ReceiveBBMessage( 'Trustee1',
                                                     %idx_initial_ballots
                     ) ▶₀ #vr )
                case TrusteeMixing_TAS_Init
                solve( TAS_State_ReceiveTrusteeMessage( %1 ) ▶₀ #vr.1 )
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
