/* Safety lemmas for trustee setup protocol. */

/*
  This lemma states that each trustee only registers one set of keys.
  It's actually guaranteed by Unique(), but a sanity check nonetheless.
 */
lemma Safety_Trustee_Setup_Unique_Trustee_Identities:
  "
    All t1 id_t1 pk_sign_t1 pk_encrypt_t1 t2 id_t2 pk_sign_t2 pk_encrypt_t2 #i #j.
            Trustee_IdentityKeyGen_Trace(t1, id_t1, pk_sign_t1, pk_encrypt_t1)@i
          &
            Trustee_IdentityKeyGen_Trace(t2, id_t2, pk_sign_t2, pk_encrypt_t2)@j
          &
            t1 = t2
      ==>
            id_t1 = id_t2
          &
            pk_sign_t1 = pk_sign_t2
          &
            pk_encrypt_t1 = pk_encrypt_t2
          &
            #i = #j
  "

/*
  This lemma states that the TAS only registers one set of keys. It's
  actually guaranteed by Unique(), but a sanity check nonetheless.
 */
lemma Safety_Trustee_Setup_Unique_TAS_Identity:
  "
    All pk_sign_t1 pk_sign_t2 #i #j.
            TAS_IdentityKeyGen_Trace(pk_sign_t1)@i
          &
            TAS_IdentityKeyGen_Trace(pk_sign_t2)@j
      ==>
            pk_sign_t1 = pk_sign_t2
          &
            #i = #j
  "

/*
  This lemma states that the TAS only completes (at most) one election
  setup.
 */
lemma Safety_Trustee_Setup_Only_One_Setup_TAS:
  "
    All s1 s2 #i #j.
            TAS_ElectionSetup_Complete_Trace(s1)@i
          &
            TAS_ElectionSetup_Complete_Trace(s2)@j
      ==>
            s1 = s2
          &
            #i = #j
  "

/*
  This lemma states that each trustee only confirms (at most) one election
  setup.
 */
lemma Safety_Trustee_Setup_Only_One_Setup_Trustee:
  "
    All t s1 s2 #i #j.
            Trustee_ElectionSetup_Confirmed_Trace(t, s1)@i
          &
            Trustee_ElectionSetup_Confirmed_Trace(t, s2)@j
      ==>
            s1 = s2
          &
            #i = #j
  "

/*
  This lemma states that if the TAS has completed an election setup, then
  that setup is the only one that has been confirmed by a trustee.
 */
lemma Safety_Trustee_Setup_ElectionSetup_Agreement:
  "
    All t ts s #i #j.
            Trustee_ElectionSetup_Confirmed_Trace(t, ts)@i
          &
            TAS_ElectionSetup_Complete_Trace(s)@j
      ==>
          ts = s
  "

/* Executability lemmas for trustee setup protocol. */

/*
  This lemma states that there is at least one execution where every
  trustee registers and the election gets set up.
 */
lemma Executability_Trustee_Setup_All_Trustees_Registered:
  exists-trace
  "
    Ex ec forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!
       id_trustee<!!>TN<!!> pk_sign_trustee<!!>TN<!!> pk_encrypt_trustee<!!>TN<!!> <!#j!><!!>TN<!!>!>)
       #i.
        TAS_ElectionSetup_Complete_Trace(<'TAS_Election_Setup',  <forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!TRUSTEE_ID_TUPLE_COMPONENT(TN)ifelse(eval(TN < TRUSTEE_COUNT), eval(1), <!, !>, <!!>)!>)>, ec>)@i<!!>dnl
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!
      &
        Trustee_IdentityKeyGen_Trace('Trustee<!!>TN<!!>', id_trustee<!!>TN<!!>, pk_sign_trustee<!!>TN<!!>, pk_encrypt_trustee<!!>TN<!!>)@j<!!>TN<!!>!>)
  "

/*
  This lemma states that there is at least one execution where all
  trustees have agreed on the same election setup that the TAS has.
 */
lemma Executability_Trustee_Setup_All_Trustees_And_TAS_Agree:
  exists-trace
  "
    Ex s forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!<!#!>j<!!>TN<!!> !>)<!!>#i.
        TAS_ElectionSetup_Complete_Trace(s)@i
      &dnl
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!
        Trustee_ElectionSetup_Confirmed_Trace('Trustee<!!>TN<!!>', s)@j<!!>TN<!!>ifelse(eval(TN < TRUSTEE_COUNT), eval(1), <!
      &!>, <!!>)!>)
  "
