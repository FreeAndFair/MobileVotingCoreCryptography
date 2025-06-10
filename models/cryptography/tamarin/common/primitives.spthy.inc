/*
  Tamarin built-ins, functions, equations, macros, and restrictions used
  across the models.

  @author Daniel M. Zimmerman
  @copyright Free & Fair 2025
  @version 0.1
 */

#ifdef PRIMITIVES_SPTHY_INC

/* The primitives are already included and should not be included again. */

#else
#define PRIMITIVES_SPTHY_INC

builtins:
  symmetric-encryption, asymmetric-encryption, hashing, natural-numbers, multiset

functions:
  TBD/0

equations:
  TBD() = TBD()

#ifdef USE_EUFCMA_SIGNING | INCLUDE_ALL_PRIMITIVES
/*
  We use restrictions to model signature verification with EUF-CMA security
  as described in Chapter 15 of the Tamarin book. Thus, any rule that depends
  on a signature being valid must include the following action fact:

    SignatureVerified(sig, e1_sig(sig), pk(e3_sig(sig)), ver_msg, ver_pk, true)

  where "sig" is the signature, ver_msg is the message actually being verified,
  and ver_pk is the public key it is being verified against. Note that there
  is no "verify" function; the only way to verify a signature (or model what
  happens if it does not verify) is with the Verified action fact. Note also
  that "sign" here takes 3 arguments - the message, some random value, and the
  signing key - to model possible nondeterminism in signatures for the same
  message and signing key.
 */

functions:
  sign/3, e1_sig/1 [private], e3_sig/1 [private], pk/1, true/0, false/0

equations:
  e1_sig(sign(x, y, z)) = x,
  e3_sig(sign(x, y, z)) = z

/*
  This restriction states that an honestly generated key, an honestly
  generated signature, and the correct message must verify as true.
 */
restriction SignatureCorrectness:
  "
    All sig m pk #t1 #t2.
            HonestSignatureKey(pk)@t1
          &
            SignatureVerified(sig, m, pk, m, pk, false)@t2
      ==>
          F
  "

/*
  This restriction states that if a signature verification succeeds
  against an honest public key, then the signature must have been
  honestly produced.
 */
restriction SignatureUnforgeability:
  "
    All sig sigm sigpk verm verpk #t1 #t2.
            HonestSignatureKey(verpk)@t1
          &
            SignatureVerified(sig, sigm, sigpk, verm, verpk, true)@t2
      ==>
            sigm = verm
          &
            sigpk = verpk
  "

/*
  This restriction states that the signature verification procedure
  is deterministic.
 */
restriction SignatureDeterminism:
  "
    All sig sigm sigpk verm verpk res1 res2 #t1 #t2.
            SignatureVerified(sig, sigm, sigpk, verm, verpk, res1)@t1
          &
            SignatureVerified(sig, sigm, sigpk, verm, verpk, res2)@t2
      ==>
          res1 = res2
  "

#endif
#ifdef USE_EQUALITY | INCLUDE_ALL_PRIMITIVES
/*
  Restriction that a rule can only execute if two values are equivalent.
 */
restriction Equality:
  "All x y #i. Eq(x, y)@i ==> x = y"

#endif
#ifdef USE_INEQUALITY | INCLUDE_ALL_PRIMITIVES
/*
  Restriction that a rule can only execute if two values are not equivalent.
 */
restriction Inequality:
  "All x #i. Neq(x, x)@i ==> F"

#endif
#ifdef USE_ONLYONCE | INCLUDE_ALL_PRIMITIVES
/*
  Restriction that a rule can only be executed once in the entire trace.
 */
restriction OnlyOnce:
  "All #i #j. OnlyOnce()@i & OnlyOnce()@#j ==> #i = #j"

#endif
#ifdef USE_UNIQUE | INCLUDE_ALL_PRIMITIVES
/*
  Restriction that a rule specified by a single value can only be executed
  once in the entire trace.
 */
restriction Unique:
  "All x #i #j. Unique(x)@i & Unique(x)@j ==> #i = #j"

#endif
#ifdef USE_LESSTHAN | INCLUDE_ALL_PRIMITIVES
/*
  Restriction that a rule can only be executed if one natural number is
  less than another.
 */
restriction LessThan:
  "All %x %y #i. LessThan(%x, %y)@i ==> %x << %y"

#endif
#ifdef USE_ATMOST | INCLUDE_ALL_PRIMITIVES
/*
  Restriction that a rule can only be executed if one natural number is
  at most (less than or equal to) another.
 */
restriction AtMost:
  "All %x %y #i. AtMost(%x, %y)@i ==> %x << %y | %x = %y"

#endif
#ifdef USE_NOTINMULTISET | INCLUDE_ALL_PRIMITIVES
/*
  Restriction that a multiset must not contain the specified member.
 */
restriction NotInMultiset:
  "
    All m s #i.
          NotInMultiset(m, s)@i
      ==>
          All x y. s = x + y ==> not (m = x)
  "

#endif
#ifdef USE_INMULTISET | INCLUDE_ALL_PRIMITIVES
/*
  Restriction that a multiset must contain the specified member.
 */
restriction InMultiset:
  "
    All m s #i.
          InMultiset(m, s)@i
      ==>
          Ex x y. (s = x + y) & (m = x)
  "

#endif
#endif
