dnl
dnl This is the m4 input file for rules that enable adversary
dnl action in the trustee setup protocol. The adversary must
dnl be able to submit messages to the bulletin board, and to
dnl discover one or more trustee private keys (which can be
dnl used to submit such messages).
dnl
dnl @author Daniel M. Zimmerman
dnl @copyright Free & Fair 2025
dnl @version 0.1
dnl
/* Election Key Generation Adversary */

/*
  This rule reveals a trustee's private keys to the adversary.
 */
rule ElectionKeyGeneration_Reveal_Trustee_Keys:
    [ !Trustee_Secret_Keys(trustee, sk_sign, sk_encrypt) ]
  --[ Unique(<'RevealTrusteeKeys', trustee>), // to avoid cluttering the trace
      RevealTrusteeKeys(trustee) ]->
    [ Out(<trustee, sk_sign, sk_encrypt>) ]

/*
  This rule reveals a trustee's private share to the adversary.
 */
rule ElectionKeyGeneration_Reveal_Trustee_Share:
    [ !Trustee_Private_Share(trustee, private_share) ]
  --[ Unique(<'RevealTrusteeShare', trustee>), // to avoid cluttering the trace
      RevealTrusteeShare(trustee) ]->
    [ Out(<trustee, private_share>) ]

/*
  This rule allows the adversary to (attempt to) submit a message
  to the trustee bulletin board. In order to do this successfully,
  it needs to use the trustee name and signing key from the
  ElectionKeyGeneration_Reveal_Trustee rule.
 */
rule ElectionKeyGeneration_Inject_Arbitrary_Trustee_Message:
    [ In(<trustee, msg, sig>),
      !Trustee_Public_Keys(trustee, pk_sign, pk_encrypt_unused) ]
  --[ InjectTrusteeMsg(trustee, msg, sig),
      SignatureVerified(sig, e1_sig(sig), pk(e3_sig(sig)),
                        msg, pk_sign, true) /* valid signature */ ]->
    [ Trustee_Message_Submit(trustee, msg, sig) ]

/*
  This rule allows the adversary to see a bulletin board message
  that has been posted.
 */
rule ElectionKeyGeneration_Reveal_BB_Message:
    [ !TAS_BBEntry(t, m, s, %i) ]
  --[ RevealBBMsg(t, m, s, %i) ]->
    [ Out(<m, s>) /* t and %i are already known to the adversary */ ]
