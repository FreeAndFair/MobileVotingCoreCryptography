simplify
solve( IN_SECURE_RECEIVE( cid, S, R, m ) @ #i )
  case VoterAuthentication_AS_AuthenticationRequest
  solve( SecureReceive( ~cid, S, 'AS',
                        <'EAS_Request_Authentication_Session', ~project_id, ~api_key>
         ) ▶₁ #i )
    case SecureChannel_Receive_case_1
    by contradiction /* from formulas */
  next
    case SecureChannel_Receive_case_2
    by contradiction /* from formulas */
  qed
next
  case VoterAuthentication_AS_ReportAuthenticationResult
  solve( SecureReceive( ~cid, S, 'AS',
                        <'EAS_Request_Authentication_Result', ~session_id>
         ) ▶₁ #i )
    case SecureChannel_Receive_case_1
    by contradiction /* from formulas */
  next
    case SecureChannel_Receive_case_2
    by contradiction /* from formulas */
  qed
next
  case VoterAuthentication_AS_ReportIncompleteAuthenticationResult
  solve( SecureReceive( ~cid, S, 'AS',
                        <'EAS_Request_Authentication_Result', ~session_id>
         ) ▶₁ #i )
    case SecureChannel_Receive_case_1
    by contradiction /* from formulas */
  next
    case SecureChannel_Receive_case_2
    by contradiction /* from formulas */
  qed
next
  case VoterAuthentication_EAS_ReceiveAuthenticationComplete
  solve( SecureReceive( ~cid_va, ~va_id, <~ec, 'EAS'>,
                        <'VA_Authentication_Complete', ~ec, pk_voter, ~token>
         ) ▶₁ #i )
    case SecureChannel_Receive_case_1
    by contradiction /* from formulas */
  next
    case SecureChannel_Receive_case_2
    by contradiction /* from formulas */
  qed
next
  case VoterAuthentication_EAS_RequestAuthentication
  solve( SecureReceive( ~cid_va, ~va_id, <~ec, 'EAS'>,
                        <'VA_Request_Authentication', ~ec, pk_voter>
         ) ▶₂ #i )
    case SecureChannel_Receive_case_1
    by contradiction /* from formulas */
  next
    case SecureChannel_Receive_case_2
    by contradiction /* from formulas */
  qed
qed
