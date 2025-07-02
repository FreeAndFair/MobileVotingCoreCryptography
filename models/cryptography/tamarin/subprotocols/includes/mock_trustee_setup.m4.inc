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
/*
  The initial configuration of the trustees and the trustee
  administration server is defined by a Tamarin rule, which
  establishes all the necessary persistent facts and puts the
  trustees into the correct state. Note that we abstract away
  the election setup into a single fresh variable, because all
  the information in it about trustee keys, etc., is already
  known to the trustees via other facts.
 */
rule TrusteeElectionSetup:
    [ Fr(~sk_sign_tas),dnl
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!
      Fr(~sk_sign_trustee<!!>TN<!!>),
      Fr(~sk_encrypt_trustee<!!>TN<!!>),!>)
      Fr(~election_setup) ]
  --[ Unique('TrusteeElectionSetup'),
      /* TAS Initialization */
      HonestSignatureKey(pk(~sk_sign_tas)),
      TAS_IdentityKeyGen_Trace(pk(~sk_sign_tas)),dnl
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!
      /* Trustee <!!>TN<!!> */
      TAS_Trustee_Trace('Trustee<!!>TN<!!>', pk(~sk_sign_trustee<!!>TN<!!>), pk(~sk_encrypt_trustee<!!>TN<!!>)),
      HonestSignatureKey(pk(~sk_sign_trustee<!!>TN<!!>)),
      Trustee_ElectionSetup_Trace('Trustee<!!>TN<!!>', ~election_setup),!>)
      /* TAS Finalization */
      TAS_ElectionSetup_Complete_Trace(~election_setup) ]->
    [ /* Persistent Facts */
      !TAS_Secret_Signing_Key(~sk_sign_tas),
      !TAS_Public_Signing_Key(pk(~sk_sign_tas)),
      !TAS_ElectionSetup_Complete(~election_setup),dnl
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!
      /* Trustee <!!>TN<!!> */
      !Trustee('Trustee<!!>TN<!!>'),
      !Trustee_Secret_Keys('Trustee<!!>TN<!!>', ~sk_sign_trustee<!!>TN<!!>, ~sk_encrypt_trustee<!!>TN<!!>),
      !Trustee_Public_Keys('Trustee<!!>TN<!!>', pk(~sk_sign_trustee<!!>TN<!!>), pk(~sk_encrypt_trustee<!!>TN<!!>)),
      !Trustee_ElectionSetup('Trustee<!!>TN<!!>', ~election_setup),!>)
      /* Linear facts (triggering the TAS to initialize the bulletin board) */
      TAS_State_BeginTrusteeThresholdKeygen(),
      /* Ensure the adversary has all the public keys and trustee IDs */
      Out(~election_setup),dnl
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!
      Out(pk(~sk_sign_trustee<!!>TN<!!>)),
      Out(pk(~sk_encrypt_trustee<!!>TN<!!>)),!>)
      Out(pk(~sk_sign_tas))]
