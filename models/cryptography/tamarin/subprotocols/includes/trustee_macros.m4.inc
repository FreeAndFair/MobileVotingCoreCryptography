dnl
dnl This input file contains Tamarin macros for messages in the trustee
dnl protocols. It sets the number of trustees to 3 if it is not set already.
dnl It is idempotent; if included more than once, every inclusion after the
dnl first will have no effect.
dnl
dnl @author Daniel M. Zimmerman
dnl @copyright Free & Fair 2025
dnl @version 0.1
dnl
dnl We set the number of trustees to 3, if it's not set already.
ifdef(<!TRUSTEE_COUNT!>,<!!>,<!define(TRUSTEE_COUNT, <!3!>)!>)dnl
dnl The following tuple is used in messages that contain all the trustee names and public keys.
ifdef(<!TRUSTEE_ID_TUPLE_COMPONENT!>,<!!>,<!define(TRUSTEE_ID_TUPLE_COMPONENT, <!<!<'Trustee$1', id_trustee$1, pk_sign_trustee$1, pk_encrypt_trustee$1>!>!>)!>)dnl
dnl
ifdef(<!TRUSTEE_TAMARIN_MACROS!>,<!!>,<!macros:
  /*
    All message types contain a tag at the beginning, either a single constant
    (like 'Trustee_ID') or a tuple (like <'Trustee_Pairwise_Share', x>). In the
    trustee protocol, each such tag can only appear on the bulletin board _once_
    for each sending trustee; this is enforced via restrictions on the rules that
    post the messages.
   */dnl
ifdef(<!TRUSTEE_SETUP!>, <!
  Msg_Trustee_ID(name, id, pk_sign, pk_encrypt) = <'Trustee_ID', name, id, pk_sign, pk_encrypt>,
  Msg_TAS_ID(pk_sign) = <'TAS_ID', pk_sign>,
  Msg_TAS_Election_Setup(trustee_tuple, election_definition) = <'TAS_Election_Setup', trustee_tuple, election_definition>,
  Msg_Trustee_Election_Setup_Confirm(id, msg) = <'Trustee_Election_Setup_Confirm', id, msg>,
  Trustee_ID_Tuple() =
    <forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!
      TRUSTEE_ID_TUPLE_COMPONENT(TN)ifelse(eval(TN < TRUSTEE_COUNT), eval(1), <!, !>, <!!>)!>)
    >,
!>, <!!>)dnl
ifdef(<!ELECTION_KEY_GENERATION!>, <!
  Msg_Trustee_Check_Value(h_election, check_value) = <'Trustee_Check_Value', h_election, check_value>,
  Msg_Trustee_Pairwise_Share(h_election, recipient, ciphertext) = <<'Trustee_Pairwise_Share', recipient>, h_election, ciphertext>,
  Msg_Trustee_Election_Public_Key(h_election, pk_election) = <'Trustee_Election_Public_Key', h_election, pk_election>
!>, <!!>)dnl
define(TRUSTEE_TAMARIN_MACROS)
dnl!>)
dnl
