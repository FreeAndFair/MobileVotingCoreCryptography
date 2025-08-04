simplify
solve( IN_SECURE_RECEIVE( m1, m2, m3, m4 ) @ #i )
  case BallotCheck_DBB_ForwardRandomizers
  solve( SecureReceive( ~cid_va, ~va_id, <~ec, 'DBB'>,
                        <
                         <'VA_Check_Randomizers',
                          <<'BCA_Check_Request', ~ec, tracker, pk_bca_encrypt, pk_bca_sign>,
                           sig_bca_req>,
                          encrypted_randomizers, pk_voter>,
                         sig_randomizers>
         ) ▶₁ #i )
    case SecureChannel_Receive_case_1
    by contradiction
  next
    case SecureChannel_Receive_case_2
    by contradiction
  next
    case SecureChannel_Receive_case_3
    by contradiction
  next
    case SecureChannel_Receive_case_4
    by contradiction /* from formulas */
  qed
next
  case BallotCheck_DBB_ReceiveCheckRequest
  solve( SecureReceive( ~cid_bca, ~bca_id, <~ec, 'DBB'>,
                        <<'BCA_Check_Request', ~ec, tracker, pk_bca_encrypt, pk_bca_sign>,
                         sig_bca_req>
         ) ▶₃ #i )
    case SecureChannel_Receive_case_1
    by contradiction
  next
    case SecureChannel_Receive_case_2
    by contradiction
  next
    case SecureChannel_Receive_case_3
    by contradiction
  next
    case SecureChannel_Receive_case_4
    by contradiction /* from formulas */
  qed
next
  case BallotCheck_VA_RequestRandomizers
  solve( SecureReceive( ~cid, <~ec, 'DBB'>, ~va_id,
                        <'DBB_Check_Request',
                         <'BCA_Check_Request', ~ec, tracker, pk_bca_encrypt, pk_bca_sign>,
                         sig_bca_req>
         ) ▶₃ #i )
    case SecureChannel_Receive_case_1
    by contradiction
  next
    case SecureChannel_Receive_case_2
    by contradiction
  qed
qed
