simplify
solve( (∃ #j.
         (AS_SuccessfulAuthentication_Trace( ~session_id ) @ #j) ∧ #j < #i)  ∥
       (∃ #j.
         (AS_UnsuccessfulAuthentication_Trace( ~session_id ) @ #j) ∧ #j < #i) )
  case case_2
  solve( !AS_Authentication_Status( ~session_id, $voter_id, 'unsuccessful'
         ) ▶₀ #i )
    case VoterAuthentication_AS_UnsuccessfulAuthentication_case_1
    solve( AS_State_AwaitAuthentication( ~session_id, ~token ) ▶₀ #j )
      case VoterAuthentication_AS_AuthenticationRequest_case_1
      solve( EAS_ReceiveAuthenticationResult_Trace( ~session_id,
                                                    'unsuccessful', 'ineligible', 'ineligible'
             ) @ #j.3 )
        case VoterAuthentication_EAS_ReceiveAuthenticationResult_Unsuccessful
        solve( EAS_State_ReceiveAuthenticationResult( ~ec.1, ~cid_as, ~cid_va.1,
                                                      ~va_id.1, pk_voter, ~session_id, ~token.1
               ) ▶₀ #j.3 )
          case VoterAuthentication_EAS_ReceiveAuthenticationComplete_case_1
          solve( VA_ReceiveAuthenticationResult_Trace( ~ec, ~va_id, 'unsuccessful',
                                                       'ineligible', pk(~sk_voter), 'ineligible'
                 ) @ #k )
            case VoterAuthentication_VA_ReceiveAuthenticationResult_Unsuccessful
            solve( VA_State_ReceiveAuthenticationResult( ~ec, ~va_id, $V, ~sk_voter,
                                                         ~cid.2, ~token.1
                   ) ▶₀ #k )
              case VoterAuthentication_VA_ReceiveAuthenticationComplete
              solve( SecureReceive( ~cid_va, <~ec, 'EAS'>, ~va_id,
                                    <'EAS_Authentication_Result', 'unsuccessful', ~ec, 'ineligible',
                                     pk(~sk_voter), 'ineligible'>
                     ) ▶₁ #k )
                case SecureChannel_Receive_case_1
                solve( SecureReceive( ~cid, requesting_eas, 'AS',
                                      <'EAS_Request_Authentication_Result', ~session_id>
                       ) ▶₁ #i )
                  case SecureChannel_Receive_case_1
                  solve( SecureReceive( ~cid.1, ~v_id, 'AS',
                                        <'Voter_Authentication', ~token, $voter_id>
                         ) ▶₁ #j )
                    case SecureChannel_Receive_case_1
                    solve( SecureReceive( ~cid.2, <~ec, 'EAS'>, 'AS',
                                          <'EAS_Request_Authentication_Session', ~project_id, ~api_key>
                           ) ▶₁ #vr )
                      case SecureChannel_Receive_case_1
                      solve( SecureReceive( ~cid_va.1, ~v_id, <~ec, 'EAS'>,
                                            <'VA_Request_Authentication', ~ec, pk(~sk_voter)>
                             ) ▶₂ #vr.3 )
                        case SecureChannel_Receive_case_1
                        solve( BallotStyleCount( ~ec, %idx_bs_unused ) ▶₀ #vr.6 )
                          case Mock_BallotStyle
                          solve( VoterCount( ~ec, %idx_ev_unused ) ▶₀ #vr.7 )
                            case Mock_EC_And_Initial_Counters
                            solve( BallotStyleCount( ~ec, %i.2 ) ▶₀ #vr.8 )
                              case Mock_BallotStyle
                              solve( VoterCount( ~ec, %i.3 ) ▶₀ #vr.9 )
                                case Mock_EC_And_Initial_Counters
                                solve( BallotStyleCount( ~ec, %unused ) ▶₀ #vr.10 )
                                  case Mock_BallotStyle
                                  solve( SecureReceive( ~cid_as, 'AS', <~ec, 'EAS'>,
                                                        <'AS_Authentication_Result', ~session_id, $voter_id,
                                                         'unsuccessful'>
                                         ) ▶₁ #j.3 )
                                    case SecureChannel_Receive_case_01
                                    solve( (∃ #j.
                                             (AS_SuccessfulAuthentication_Trace( ~session_id ) @ #j)
                                            ∧
                                             #j < #vr.36)  ∥
                                           (∃ #j.
                                             (AS_UnsuccessfulAuthentication_Trace( ~session_id ) @ #j)
                                            ∧
                                             #j < #vr.36) )
                                      case case_2
                                      solve( AS_State_AwaitAuthentication( ~session_id, ~token.1 ) ▶₀ #j.6 )
                                        case VoterAuthentication_AS_AuthenticationRequest_case_1
                                        solve( SecureReceive( ~cid_va, ~v_id, <~ec, 'EAS'>,
                                                              <'VA_Authentication_Complete', ~ec,
                                                               pk(~sk_voter), ~token>
                                               ) ▶₁ #vr.11 )
                                          case SecureChannel_Receive_case_1
                                          solve( SecureReceive( ~cid_as.1, 'AS', <~ec, 'EAS'>,
                                                                <'AS_Authentication_Session', ~session_id,
                                                                 ~token>
                                                 ) ▶₁ #vr.12 )
                                            case SecureChannel_Receive_case_1
                                            solve( SecureReceive( ~cid.1, 'AS', ~v_id,
                                                                  <'AS_Authentication_Complete', ~token>
                                                   ) ▶₂ #vr.14 )
                                              case SecureChannel_Receive_case_1
                                              solve( SecureReceive( ~cid_va.1, <~ec, 'EAS'>, ~v_id,
                                                                    <'EAS_Authentication_Session', ~ec,
                                                                     pk(~sk_voter), ~token>
                                                     ) ▶₂ #vr.15 )
                                                case SecureChannel_Receive_case_1
                                                solve( SecureReceive( ~cid_as.2, 'AS', <~ec, 'EAS'>,
                                                                      <'AS_Authentication_Result',
                                                                       ~session_id.1, $voter_id,
                                                                       'unsuccessful'>
                                                       ) ▶₁ #vr.18 )
                                                  case SecureChannel_Receive_case_01
                                                  solve( (∃ #j.
                                                           (AS_SuccessfulAuthentication_Trace( ~session_id
                                                            ) @ #j)
                                                          ∧
                                                           #j < #vr.47)  ∥
                                                         (∃ #j.
                                                           (AS_UnsuccessfulAuthentication_Trace( ~session_id
                                                            ) @ #j)
                                                          ∧
                                                           #j < #vr.47) )
                                                    case case_2
                                                    solve( AS_State_AwaitAuthentication( ~session_id, ~token.1
                                                           ) ▶₀ #j.7 )
                                                      case VoterAuthentication_AS_AuthenticationRequest_case_1
                                                      solve( SecureReceive( ~cid_va, ~v_id, <~ec, 'EAS'>,
                                                                            <'VA_Authentication_Complete',
                                                                             ~ec, pk(~sk_voter), ~token>
                                                             ) ▶₁ #vr.19 )
                                                        case SecureChannel_Receive_case_1
                                                        solve( SecureReceive( ~cid_va, ~v_id, <~ec, 'EAS'>,
                                                                              <'VA_Authentication_Complete',
                                                                               ~ec, pk(~sk_voter), ~token>
                                                               ) ▶₁ #vr.20 )
                                                          case SecureChannel_Receive_case_1
                                                          solve( BallotStyleCount( ~ec, %i.1 ) ▶₀ #vr.21 )
                                                            case Mock_BallotStyle
                                                            solve( BallotStyleCount( ~ec, %i.2 ) ▶₀ #vr.23 )
                                                              case Mock_BallotStyle
                                                              solve( BallotStyleCount( ~ec, %i.3 ) ▶₀ #vr.24 )
                                                                case Mock_BallotStyle
                                                                solve( SecureReceive( ~cid, <~ec, 'EAS'>,
                                                                                      'AS',
                                                                                      <
                                                                                       'EAS_Request_Authentication_Result',
                                                                                       ~session_id>
                                                                       ) ▶₁ #vr.27 )
                                                                  case SecureChannel_Receive_case_1
                                                                  solve( SecureReceive( ~cid_as.1, 'AS',
                                                                                        <~ec, 'EAS'>,
                                                                                        <
                                                                                         'AS_Authentication_Session',
                                                                                         ~session_id.1, ~token
                                                                                        >
                                                                         ) ▶₁ #vr.33 )
                                                                    case SecureChannel_Receive_case_1
                                                                    solve( BallotStyleCount( ~ec, %i.1
                                                                           ) ▶₀ #vr.33 )
                                                                      case Mock_BallotStyle
                                                                      solve( BallotStyleCount( ~ec, %i.2
                                                                             ) ▶₀ #vr.34 )
                                                                        case Mock_BallotStyle
                                                                        solve( BallotStyleCount( ~ec, %i.3
                                                                               ) ▶₀ #vr.35 )
                                                                          case Mock_BallotStyle
                                                                          solve( BallotStyleCount( ~ec, %i.1
                                                                                 ) ▶₀ #vr.36 )
                                                                            case Mock_BallotStyle
                                                                            solve( BallotStyleCount( ~ec, %i.2
                                                                                   ) ▶₀ #vr.37 )
                                                                              case Mock_BallotStyle
                                                                              solve( BallotStyleCount( ~ec,
                                                                                                       %i.3
                                                                                     ) ▶₀ #vr.38 )
                                                                                case Mock_BallotStyle
                                                                                solve( BallotStyleCount( ~ec,
                                                                                                         %i.1
                                                                                       ) ▶₀ #vr.39 )
                                                                                  case Mock_BallotStyle
                                                                                  solve( BallotStyleCount( ~ec,
                                                                                                           %i.2
                                                                                         ) ▶₀ #vr.40 )
                                                                                    case Mock_BallotStyle
                                                                                    solve( BallotStyleCount( ~ec,
                                                                                                             %i.3
                                                                                           ) ▶₀ #vr.41 )
                                                                                      case Mock_BallotStyle
                                                                                      solve( BallotStyleCount( ~ec,
                                                                                                               %i.1
                                                                                             ) ▶₀ #vr.42 )
                                                                                        case Mock_BallotStyle
                                                                                        solve( BallotStyleCount( ~ec,
                                                                                                                 %i.2
                                                                                               ) ▶₀ #vr.43 )
                                                                                          case Mock_BallotStyle
                                                                                          solve( BallotStyleCount( ~ec,
                                                                                                                   %i.3
                                                                                                 ) ▶₀ #vr.44 )
                                                                                            case Mock_BallotStyle
                                                                                            solve( BallotStyleCount( ~ec,
                                                                                                                     %i.1
                                                                                                   ) ▶₀ #vr.45 )
                                                                                              case Mock_BallotStyle
                                                                                              solve( BallotStyleCount( ~ec,
                                                                                                                       %i.2
                                                                                                     ) ▶₀ #vr.46 )
                                                                                                case Mock_BallotStyle
                                                                                                solve( BallotStyleCount( ~ec,
                                                                                                                         %i.3
                                                                                                       ) ▶₀ #vr.47 )
                                                                                                  case Mock_BallotStyle
                                                                                                  solve( BallotStyleCount( ~ec,
                                                                                                                           %i.1
                                                                                                         ) ▶₀ #vr.48 )
                                                                                                    case Mock_BallotStyle
                                                                                                    solve( BallotStyleCount( ~ec,
                                                                                                                             %i.2
                                                                                                           ) ▶₀ #vr.49 )
                                                                                                      case Mock_BallotStyle
                                                                                                      solve( BallotStyleCount( ~ec,
                                                                                                                               %i.3
                                                                                                             ) ▶₀ #vr.50 )
                                                                                                        case Mock_BallotStyle
                                                                                                        solve( BallotStyleCount( ~ec,
                                                                                                                                 %i.1
                                                                                                               ) ▶₀ #vr.51 )
                                                                                                          case Mock_BallotStyle
                                                                                                          solve( BallotStyleCount( ~ec,
                                                                                                                                   %i.2
                                                                                                                 ) ▶₀ #vr.52 )
                                                                                                            case Mock_BallotStyle
                                                                                                            solve( BallotStyleCount( ~ec,
                                                                                                                                     %i.3
                                                                                                                   ) ▶₀ #vr.53 )
                                                                                                              case Mock_BallotStyle
                                                                                                              solve( BallotStyleCount( ~ec,
                                                                                                                                       %i.1
                                                                                                                     ) ▶₀ #vr.54 )
                                                                                                                case Mock_BallotStyle
                                                                                                                solve( BallotStyleCount( ~ec,
                                                                                                                                         %i.2
                                                                                                                       ) ▶₀ #vr.55 )
                                                                                                                  case Mock_BallotStyle
                                                                                                                  solve( BallotStyleCount( ~ec,
                                                                                                                                           %i.3
                                                                                                                         ) ▶₀ #vr.56 )
                                                                                                                    case Mock_BallotStyle
                                                                                                                    solve( BallotStyleCount( ~ec,
                                                                                                                                             %i.1
                                                                                                                           ) ▶₀ #vr.57 )
                                                                                                                      case Mock_EC_And_Initial_Counters
                                                                                                                      solve( BallotStyleCount( ~ec,
                                                                                                                                               %i.1
                                                                                                                             ) ▶₀ #vr.58 )
                                                                                                                        case Mock_BallotStyle
                                                                                                                        solve( BallotStyleCount( ~ec,
                                                                                                                                                 %i.2
                                                                                                                               ) ▶₀ #vr.59 )
                                                                                                                          case Mock_EC_And_Initial_Counters
                                                                                                                          solve( BallotStyleCount( ~ec,
                                                                                                                                                   %i.1
                                                                                                                                 ) ▶₀ #vr.49 )
                                                                                                                            case Mock_EC_And_Initial_Counters
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
