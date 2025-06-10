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
  Msg_Trustee_ID(name, id, pk_sign, pk_encrypt) = <'Trustee_ID', name, id, pk_sign, pk_encrypt>,
  Msg_TAS_ID(pk_sign) = <'TAS_ID', pk_sign>,
  Msg_TAS_Election_Setup(trustee_tuple, election_definition) = <'TAS_Election_Setup', trustee_tuple, election_definition>,
  Msg_Trustee_Election_Setup_Confirm(id, msg) = <'Trustee_Election_Setup_Confirm', id, msg>,
  Trustee_ID_Tuple() =
    <forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!
      TRUSTEE_ID_TUPLE_COMPONENT(TN)ifelse(eval(TN < TRUSTEE_COUNT), eval(1), <!, !>, <!!>)!>)
    >!>)
dnl
