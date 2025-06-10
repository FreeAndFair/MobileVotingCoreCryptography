dnl
dnl This is the m4 input file that includes rules for trustees in the
dnl trustee setup protocol. Some of them are broken out per-trustee for
dnl convenience (to avoid needing to use Tamarin's multisets for modeling
dnl more than necessary).
dnl
dnl @author Daniel M. Zimmerman
dnl @copyright Free & Fair 2025
dnl @version 0.1
dnl
dnl
/* Trustee */

/*
  Some trustee rules are individualized for specific trustee
  numbers, while others are shared among all the trustees; this is
  done for modeling convenience (mainly, to avoid having to use tricks
  with multisets and such to model specific trustees' actions).
 */
dnl
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!
/*
  This is the initial rule for trustee <!!>TN<!!>; it generates an action
  fact with a public name and transitions to the state that triggers key
  generation.
 */
rule TrusteeSetup_Trustee<!!>TN<!!>_Init:
  let name='Trustee<!!>TN<!!>' in
    [ Fr(~id) ]
  --[ Unique(<'Trustee<!!>TN<!!>_Init'>),
      Trustee_Init_Trace(name, ~id) ]->
    [ !Trustee(name, ~id),
      Trustee_State_IdentityKeyGen(name, ~id) ]
!>)
/*
  This rule (shared across all trustees) initializes the secret keys for a
  trustee, sends out its identity and public keys (and therefore registers
  them with the TAS), and transitions to the state that waits for the other
  trustee public keys.
 */
rule TrusteeSetup_Trustee_IdentityKeyGen [role="Trustee"]:
  let t_id = Msg_Trustee_ID(name, id, pk(~sk_sign), pk(~sk_encrypt)) in
    [ Trustee_State_IdentityKeyGen(name, id),
      Fr(~sk_sign),
      Fr(~sk_encrypt) ]
  --[ HonestSignatureKey(pk(~sk_sign)),
      Trustee_IdentityKeyGen_Trace(name, id, pk(~sk_sign), pk(~sk_encrypt)) ]->
    [ !Trustee_Secret_Keys(name, ~sk_sign, ~sk_encrypt),
      !Trustee_Public_Keys(name, pk(~sk_sign), pk(~sk_encrypt)),
      Out(<t_id, sign(t_id, '1', ~sk_sign)>),
      Trustee_State_ReceiveElectionSetup(name) ]
dnl
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!
/*
  This rule receives the trustee and election configuration information from
  the TAS as trustee <!!>TN<!!>, verifies the signature, verifies that trustee <!!>TN<!!>
  is in the setup and that its public keys match what it sent out, and then
  approves the election setup by signing it and sending it back to the TAS.

  Note that this rule assumes that the TAS signing key is available in the
  environment and therefore known before any message from the TAS is received;
  this reflects out-of-band manual verification of the TAS signing key. Note
  also that pattern matching of pk_sign_trustee<!!>TN<!!> and pk_encrypt_trustee<!!>TN<!!>
  ensures that trustee <!!>TN<!!> appears in the election setup message with
  the name and public keys it expects.
 */
rule TrusteeSetup_Trustee<!!>TN<!!>_ReceiveElectionSetup [role="Trustee"]:
  let name='Trustee<!!>TN<!!>'
      msg_setup = Msg_TAS_Election_Setup(Trustee_ID_Tuple(), election_definition)
      msg_confirm = Msg_Trustee_Election_Setup_Confirm(name, msg_setup) in
    [ Trustee_State_ReceiveElectionSetup(name),
      !Trustee_Secret_Keys(name, sk_sign, sk_encrypt_unused),
      !Trustee_Public_Keys(name, pk_sign_trustee<!!>TN<!!>, pk_encrypt_trustee<!!>TN<!!>),
      !TAS_Public_Signing_Key(pk_sign_tas),
      In(<msg_setup, sig>) ]
  --[ SignatureVerified(sig, e1_sig(sig), pk(e3_sig(sig)), msg_setup,
                        pk_sign_tas, true), /* valid signature */
      Trustee_ElectionSetup_Trace(name, msg_setup) ]->
    [ Out(<msg_confirm, sign(msg_confirm, '1', sk_sign)>),
      !Trustee_ElectionSetup(name, msg_setup),
      Trustee_State_ConfirmAllTrusteesSetup(name) ]
!>)
/*
  This rule (shared across all trustees) waits for all trustees to have
  confirmed the identical election setup, then transitions to the state where
  the trustee will start generating threshold keys with the next trustee. It
  determines this by looking at persistent state facts for the other trustees,
  which is a proxy for getting up-to-date information about the trustee
  bulletin board structure maintained by the TAS.
 */
rule TrusteeSetup_Trustee_ConfirmAllTrusteesSetup [role="Trustee"]:
  let msg_setup = Msg_TAS_Election_Setup(Trustee_ID_Tuple(), election_definition) in
    [ Trustee_State_ConfirmAllTrusteesSetup(name),
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!      !Trustee_ElectionSetup('Trustee<!!>TN<!!>', msg_setup)ifelse(eval(TN < TRUSTEE_COUNT), eval(1), <!,
!>, <!!>)!>) ]
  --[ Trustee_ElectionSetup_Confirmed_Trace(name, msg_setup) ]->
    [ !Trustee_ElectionSetup_Confirmed(name, msg_setup),
      Trustee_State_BeginTrusteeThresholdKeyGen(name) ]
