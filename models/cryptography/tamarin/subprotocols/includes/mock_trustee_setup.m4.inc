dnl
dnl This is the m4 input file for the composition of all the trustee
dnl subprotocols after initial setup.
dnl
dnl @author Daniel M. Zimmerman
dnl @copyright Free & Fair 2025
dnl @version 0.1
dnl
dnl We need some macros that differ slightly from those in the trustee
dnl macros file, so that we can mock the setup process by creating a
dnl bunch of fresh values.
dnl
ifdef(<!TRUSTEE_ID_TUPLE_COMPONENT_FRESH!>,<!!>,<!define(TRUSTEE_ID_TUPLE_COMPONENT_FRESH, <!<!<'Trustee$1', ~id_trustee$1, pk(~sk_sign_trustee$1), pk(~sk_encrypt_trustee$1)>!>!>)!>)dnl
dnl
macros:
  Trustee_ID_Tuple_Fresh() =
    <forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!
      TRUSTEE_ID_TUPLE_COMPONENT_FRESH(TN)ifelse(eval(TN < TRUSTEE_COUNT), eval(1), <!, !>, <!!>)!>)
    >

/*
  The initial configuration of the trustees and the trustee
  administration server is defined by a Tamarin rule, which
  establishes all the necessary persistent facts and puts the
  trustees into the correct state.
 */
rule TrusteeElectionSetup:
  let msg_setup = Msg_TAS_Election_Setup(Trustee_ID_Tuple_Fresh(), ~election_definition) in
    [ Fr(~sk_sign_tas),dnl
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!
      Fr(~id_trustee<!!>TN<!!>),
      Fr(~sk_sign_trustee<!!>TN<!!>),
      Fr(~sk_encrypt_trustee<!!>TN<!!>),!>)
      Fr(~election_definition) ]
  --[ Unique('TrusteeElectionSetup'),
      /* TAS Initialization */
      HonestSignatureKey(pk(~sk_sign_tas)),
      TAS_IdentityKeyGen_Trace(pk(~sk_sign_tas)),dnl
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!
      /* Trustee <!!>TN<!!> */
      TAS_Trustee_Trace('Trustee<!!>TN<!!>', ~id_trustee<!!>TN<!!>, pk(~sk_sign_trustee<!!>TN<!!>), pk(~sk_encrypt_trustee<!!>TN<!!>)),
      TAS_Trustee_Confirmation_Trace('Trustee<!!>TN<!!>'),
      Trustee_Init_Trace('Trustee<!!>TN<!!>', ~id_trustee<!!>TN<!!>),
      HonestSignatureKey(pk(~sk_sign_trustee<!!>TN<!!>)),
      Trustee_IdentityKeyGen_Trace('Trustee<!!>TN<!!>', ~id_trustee<!!>TN<!!>, pk(~sk_sign_trustee<!!>TN<!!>), pk(~sk_encrypt_trustee<!!>TN<!!>)),
      Trustee_ElectionSetup_Trace('Trustee<!!>TN<!!>', msg_setup),
      Trustee_ElectionSetup_Confirmed_Trace('Trustee<!!>TN<!!>', msg_setup),!>)
      /* TAS Finalization */
      TAS_AllTrustees_Trace(Trustee_ID_Tuple_Fresh()),
      TAS_ElectionSetup_Complete_Trace(msg_setup) ]->
    [ /* Persistent Facts */
      !TAS_Secret_Signing_Key(~sk_sign_tas),
      !TAS_Public_Signing_Key(pk(~sk_sign_tas)),
      !TAS_ElectionSetup_Complete(msg_setup),dnl
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!
      /* Trustee <!!>TN<!!> */
      !Trustee('Trustee<!!>TN<!!>', ~id_trustee<!!>TN<!!>),
      !Trustee_Secret_Keys('Trustee<!!>TN<!!>', ~sk_sign_trustee<!!>TN<!!>, ~sk_encrypt_trustee<!!>TN<!!>),
      !Trustee_Public_Keys('Trustee<!!>TN<!!>', pk(~sk_sign_trustee<!!>TN<!!>), pk(~sk_encrypt_trustee<!!>TN<!!>)),
      !Trustee_ElectionSetup('Trustee<!!>TN<!!>', msg_setup),
      !Trustee_ElectionSetup_Confirmed('Trustee<!!>TN<!!>', msg_setup),!>)
      /* Linear facts (setting the next state for the TAS and each trustee) */
      TAS_State_BeginTrusteeThresholdKeygen(),dnl
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!
      Trustee_State_BeginTrusteeThresholdKeygen('Trustee<!!>TN<!!>'),!>)
      /* Ensure the adversary has all the public keys and trustee IDs */
      Out(msg_setup),
      Out(pk(~sk_sign_tas))]
