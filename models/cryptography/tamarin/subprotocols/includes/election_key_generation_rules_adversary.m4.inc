dnl
dnl This is the m4 input file for rules that enable adversary
dnl action in the trustee setup protocol. The adversary must
dnl be able to submit messages to the trustee board (this
dnl is enabled in the trustee board ruleset), and to discover
dnl one or more trustee private keys (which can be used to
dnl submit such messages).
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
