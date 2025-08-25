simplify
solve( (∃ #j.
         (AS_SuccessfulAuthentication_Trace( ~session_id ) @ #j) ∧ #j < #i)  ∥
       (∃ #j.
         (AS_UnsuccessfulAuthentication_Trace( ~session_id ) @ #j) ∧ #j < #i) )
  case case_1
  solve( !AS_Authentication_Status( ~session_id, $voter_id, 'successful'
         ) ▶₀ #i )
    case VoterAuthentication_AS_SuccessfulAuthentication_case_1
    solve( !EASPublicKey( ~ec, pk_eas ) ▶₁ #k2 )
      case Mock_Finalize_Election_Setup
      solve( SecureReceive( ~cid.2, <~ec, 'EAS'>, <~ec, 'DBB'>,
                            <<'EAS_Authorize_Voter', ~ec, pseudo, pk(~sk_voter), ~bs>,
                             sign(<'EAS_Authorize_Voter', ~ec, pseudo, pk(~sk_voter), ~bs>, x,
                                  ~sk_eas)
                            >
             ) ▶₂ #k2 )
        case SecureChannel_Receive_case_1
        solve( AS_State_AwaitAuthentication( ~session_id, ~token ) ▶₀ #j )
          case VoterAuthentication_AS_AuthenticationRequest_case_1
          solve( EAS_ReceiveAuthenticationResult_Trace( ~session_id, v,
                                                        pseudonym($voter_id.1), ~bs
                 ) @ #j.4 )
            case VoterAuthentication_EAS_ReceiveAuthenticationResult_Successful_Eligible
            solve( EAS_State_ReceiveAuthenticationResult( ~ec.1, ~cid_as, ~cid_va.2,
                                                          ~va_id.1, pk_voter, ~session_id, ~token.2
                   ) ▶₀ #j.4 )
              case VoterAuthentication_EAS_ReceiveAuthenticationComplete_case_1
              solve( !EASSecretKey( ~ec, ~sk_eas.1 ) ▶₁ #j.4 )
                case Mock_Finalize_Election_Setup
                solve( !EligibleVoter( ~ec, $voter_id.1, ~bs, %unused ) ▶₂ #j.4 )
                  case Mock_VoterRegistration_Eligible
                  solve( VA_ReceiveAuthenticationResult_Trace( ~ec, ~va_id, 'eligible',
                                                               pseudonym($voter_id.1), pk(~sk_voter), ~bs
                         ) @ #k1 )
                    case VoterAuthentication_VA_ReceiveAuthenticationResult_Eligible
                    solve( VA_State_ReceiveAuthenticationResult( ~ec, ~va_id, $V, ~sk_voter,
                                                                 ~cid.2, ~token.1
                           ) ▶₀ #k1 )
                      case VoterAuthentication_VA_ReceiveAuthenticationComplete
                      solve( SecureReceive( ~cid_va, <~ec, 'EAS'>, ~va_id,
                                            <'EAS_Authentication_Result', 'eligible', ~ec,
                                             pseudonym($voter_id.1), pk(~sk_voter), ~bs>
                             ) ▶₁ #k1 )
                        case SecureChannel_Receive_case_1
                        solve( SecureReceive( ~cid, requesting_eas, 'AS',
                                              <'EAS_Request_Authentication_Result', ~session_id>
                               ) ▶₁ #i )
                          case SecureChannel_Receive_case_1
                          solve( DBB_State_ReceiveAuthorizeVoter( ~ec, %idx ) ▶₀ #k2 )
                            case Mock_Finalize_Election_Setup
                            solve( SecureReceive( ~cid.1, ~v_id, 'AS',
                                                  <'Voter_Authentication', ~token, $voter_id>
                                   ) ▶₁ #j )
                              case SecureChannel_Receive_case_1
                              solve( SecureReceive( ~cid.3, <~ec, 'EAS'>, 'AS',
                                                    <'EAS_Request_Authentication_Session', ~project_id,
                                                     ~api_key>
                                     ) ▶₁ #vr )
                                case SecureChannel_Receive_case_1
                                solve( SecureReceive( ~cid_va.1, ~v_id, <~ec, 'EAS'>,
                                                      <'VA_Request_Authentication', ~ec, pk(~sk_voter)>
                                       ) ▶₂ #vr.3 )
                                  case SecureChannel_Receive_case_1
                                  solve( BallotStyleCount( ~ec, %idx_bs_unused ) ▶₀ #vr.6 )
                                    case Mock_EC_And_Initial_Counters
                                    solve( VoterCount( ~ec, %idx_ev_unused ) ▶₀ #vr.7 )
                                      case Mock_EC_And_Initial_Counters
                                      solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.8 )
                                        case Mock_EC_And_Initial_Counters
                                        solve( VoterCount( ~ec, %i.1 ) ▶₀ #vr.8 )
                                          case Mock_EC_And_Initial_Counters
                                          solve( BallotStyleCount( ~ec, %unused.1 ) ▶₀ #vr.9 )
                                            case Mock_EC_And_Initial_Counters
                                            solve( SecureReceive( ~cid_as.1, 'AS', <~ec, 'EAS'>,
                                                                  <'AS_Authentication_Result', ~session_id.1,
                                                                   $voter_id, 'successful'>
                                                   ) ▶₃ #vr.11 )
                                              case SecureChannel_Receive_case_01
                                              solve( (∃ #j.
                                                       (AS_SuccessfulAuthentication_Trace( ~session_id ) @ #j)
                                                      ∧
                                                       #j < #vr.39)  ∥
                                                     (∃ #j.
                                                       (AS_UnsuccessfulAuthentication_Trace( ~session_id
                                                        ) @ #j)
                                                      ∧
                                                       #j < #vr.39) )
                                                case case_1
                                                solve( AS_State_AwaitAuthentication( ~session_id, ~token.1
                                                       ) ▶₀ #j.6 )
                                                  case VoterAuthentication_AS_AuthenticationRequest_case_1
                                                  solve( SecureReceive( ~cid_va, ~v_id, <~ec, 'EAS'>,
                                                                        <'VA_Authentication_Complete', ~ec,
                                                                         pk(~sk_voter), ~token>
                                                         ) ▶₁ #vr.12 )
                                                    case SecureChannel_Receive_case_1
                                                    solve( VoterCount( ~ec, %unused ) ▶₀ #vr.13 )
                                                      case Mock_EC_And_Initial_Counters
                                                      solve( SecureReceive( ~cid_as.2, 'AS', <~ec, 'EAS'>,
                                                                            <'AS_Authentication_Session',
                                                                             ~session_id, ~token>
                                                             ) ▶₁ #vr.13 )
                                                        case SecureChannel_Receive_case_1
                                                        solve( SecureReceive( ~cid.1, 'AS', ~v_id,
                                                                              <'AS_Authentication_Complete',
                                                                               ~token>
                                                               ) ▶₂ #vr.15 )
                                                          case SecureChannel_Receive_case_1
                                                          solve( SecureReceive( ~cid_va.1, <~ec, 'EAS'>,
                                                                                ~v_id,
                                                                                <
                                                                                 'EAS_Authentication_Session',
                                                                                 ~ec, pk(~sk_voter), ~token>
                                                                 ) ▶₂ #vr.16 )
                                                            case SecureChannel_Receive_case_1
                                                            solve( SecureReceive( ~cid_as.1, 'AS',
                                                                                  <~ec, 'EAS'>,
                                                                                  <
                                                                                   'AS_Authentication_Result',
                                                                                   ~session_id, $EV,
                                                                                   'successful'>
                                                                   ) ▶₃ #j.4 )
                                                              case SecureChannel_Receive_case_01
                                                              solve( (∃ #j.
                                                                       (AS_SuccessfulAuthentication_Trace( ~session_id
                                                                        ) @ #j)
                                                                      ∧
                                                                       #j < #vr.48)  ∥
                                                                     (∃ #j.
                                                                       (AS_UnsuccessfulAuthentication_Trace( ~session_id
                                                                        ) @ #j)
                                                                      ∧
                                                                       #j < #vr.48) )
                                                                case case_1
                                                                solve( AS_State_AwaitAuthentication( ~session_id,
                                                                                                     ~token.1
                                                                       ) ▶₀ #j.7 )
                                                                  case VoterAuthentication_AS_AuthenticationRequest_case_1
                                                                  solve( SecureReceive( ~cid_va, ~v_id,
                                                                                        <~ec, 'EAS'>,
                                                                                        <
                                                                                         'VA_Authentication_Complete',
                                                                                         ~ec, pk(~sk_voter),
                                                                                         ~token>
                                                                         ) ▶₁ #vr.17 )
                                                                    case SecureChannel_Receive_case_1
                                                                    solve( SecureReceive( ~cid_as.2, 'AS',
                                                                                          <~ec, 'EAS'>,
                                                                                          <
                                                                                           'AS_Authentication_Result',
                                                                                           ~session_id.1,
                                                                                           $EV, 'successful'>
                                                                           ) ▶₃ #vr.18 )
                                                                      case SecureChannel_Receive_case_01
                                                                      solve( (∃ #j.
                                                                               (AS_SuccessfulAuthentication_Trace( ~session_id
                                                                                ) @ #j)
                                                                              ∧
                                                                               #j < #vr.44)  ∥
                                                                             (∃ #j.
                                                                               (AS_UnsuccessfulAuthentication_Trace( ~session_id
                                                                                ) @ #j)
                                                                              ∧
                                                                               #j < #vr.44) )
                                                                        case case_1
                                                                        solve( AS_State_AwaitAuthentication( ~session_id,
                                                                                                             ~token.1
                                                                               ) ▶₀ #j.7 )
                                                                          case VoterAuthentication_AS_AuthenticationRequest_case_1
                                                                          solve( SecureReceive( ~cid_va,
                                                                                                ~v_id,
                                                                                                <~ec, 'EAS'>,
                                                                                                <
                                                                                                 'VA_Authentication_Complete',
                                                                                                 ~ec,
                                                                                                 pk(~sk_voter),
                                                                                                 ~token>
                                                                                 ) ▶₁ #vr.19 )
                                                                            case SecureChannel_Receive_case_1
                                                                            solve( SecureReceive( ~cid_va,
                                                                                                  ~v_id,
                                                                                                  <~ec, 'EAS'
                                                                                                  >,
                                                                                                  <
                                                                                                   'VA_Authentication_Complete',
                                                                                                   ~ec,
                                                                                                   pk(~sk_voter),
                                                                                                   ~token>
                                                                                   ) ▶₁ #vr.20 )
                                                                              case SecureChannel_Receive_case_1
                                                                              solve( SecureReceive( ~cid,
                                                                                                    <~ec,
                                                                                                     'EAS'>,
                                                                                                    'AS',
                                                                                                    <
                                                                                                     'EAS_Request_Authentication_Result',
                                                                                                     ~session_id
                                                                                                    >
                                                                                     ) ▶₁ #vr.24 )
                                                                                case SecureChannel_Receive_case_1
                                                                                solve( SecureReceive( ~cid_as.1,
                                                                                                      'AS',
                                                                                                      <~ec,
                                                                                                       'EAS'>,
                                                                                                      <
                                                                                                       'AS_Authentication_Session',
                                                                                                       ~session_id.1,
                                                                                                       ~token>
                                                                                       ) ▶₁ #vr.30 )
                                                                                  case SecureChannel_Receive_case_1
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
