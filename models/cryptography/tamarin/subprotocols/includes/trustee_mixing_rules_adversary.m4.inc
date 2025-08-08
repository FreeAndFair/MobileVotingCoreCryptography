dnl
dnl This is the m4 input file for rules that enable adversary
dnl action in the trustee mixing protocol. The adversary must
dnl be able to submit messages to the trustee board (this
dnl is enabled in the trustee board ruleset), and to discover
dnl one or more trustee private keys (which can be used to
dnl submit such messages). We also allow them to discover
dnl mix randomness so as to be able to "un-mix"; this will let
dnl us prove some security properties later (along the lines
dnl of "the original sequence cannot be extracted from the mix
dnl unless all the mix randomness leaks" - that is, if at least
dnl one honest trustee doesn't leak its mix randomness the mix
dnl can't be reversed).
dnl
dnl @author Daniel M. Zimmerman
dnl @copyright Free & Fair 2025
dnl @version 0.1
dnl
/* Trustee Mixing Adversary */

/*
  This rule reveals a trustee's private keys to the adversary.
 */
rule TrusteeMixing_Reveal_Trustee_Keys:
    [ !Trustee_Secret_Keys(trustee, sk_sign, sk_encrypt) ]
  --[ Unique(<'RevealTrusteeKeys', trustee>), // to avoid cluttering the trace
      RevealTrusteeKeys(trustee) ]->
    [ Out(<trustee, sk_sign, sk_encrypt>) ]

/*
  This rule reveals a trustee's private share to the adversary.
 */
rule TrusteeMixing_Reveal_Trustee_Share:
    [ !Trustee_Private_Share(trustee, private_share) ]
  --[ Unique(<'RevealTrusteeShare', trustee>), // to avoid cluttering the trace
      RevealTrusteeShare(trustee) ]->
    [ Out(<trustee, private_share>) ]

/*
  This rule reveals a trustee's mix randomness to the adversary.
 */
rule TrusteeMixing_Reveal_Trustee_Shuffle_Randomness:
    [ !Trustee_Shuffle_Randomness(trustee, r) ]
  --[ Unique(<'RevealTrusteeShuffleRandomness', trustee>), // to avoid cluttering the trace
      RevealTrusteeShuffleRandomness(trustee) ]->
    [ Out(<trustee, r>) ]
