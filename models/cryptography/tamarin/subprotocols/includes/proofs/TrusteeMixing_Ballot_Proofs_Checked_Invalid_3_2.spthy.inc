simplify
solve( !Trustee_Mix_Active( t ) ▶₀ #i )
  case TrusteeMixing_TAS_Init_case_4
  solve( !Trustee_BBEntry( 'Trustee2', 'Trustee0',
                           <<'Trustee_NY_Cryptograms', 'Trustee0', 'Trustee0'>,
                            election_setup, initial_ballot_order, c1, c2, p>,
                           sig_initial_ballots, %idx_initial_ballots
         ) ▶₁ #i )
    case TrusteeBoard_Trustee_Update_case_2
    solve( TAS_State_ReceiveTrusteeMessage( %idx_initial_ballots
           ) ▶₀ #vr.5 )
      case TrusteeMixing_TAS_Init
      solve( Trustee_State_ReceiveBBMessage( 'Trustee2', %1 ) ▶₀ #vr.4 )
        case TrusteeMixing_TAS_Init
        solve( !Trustee_ElectionSetup( 'Trustee2', ~election_setup
               ) ▶₂ #i )
          case Mock_TrusteeElectionSetup
          solve( TAS_Trustee_Trace( 'Trustee0', pk(~sk_sign_tas),
                                    pk(~sk_encrypt_unused)
                 ) @ #j )
            case TrusteeMixing_TAS_Init
            solve( HonestSignatureKey( pk(~sk_sign_tas) ) @ #k )
              case Mock_TrusteeElectionSetup
              SOLVED // trace found
            qed
          qed
        qed
      qed
    qed
  qed
qed
