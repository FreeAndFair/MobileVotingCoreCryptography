dnl
dnl Restrictions shared by the various ballot handling subprotocols.
dnl
dnl @author Daniel M. Zimmerman
dnl @copyright Free & Fair 2025
dnl @version 0.1
dnl
ifelse(eval(!defined_bool(<!INCLUDED_NO_PREVIOUS_CAST!>) && defined_bool(<!USE_NO_PREVIOUS_CAST!>)), eval(1), <!
define(<!INCLUDED_NO_PREVIOUS_CAST!>)dnl
/*
  This restriction states that a particular pseudonym has not previously
  cast a ballot.
 */
restriction NoPreviousCast:
  "
    All pseudo #i.
          NoPreviousCast(pseudo)@i
      ==>
          not (Ex ec va_id m #j.
            (
                DBB_ReceiveCastBallot_Trace(ec, va_id, pseudo, m)@j
              &
                #j < #i
            )
          )
  "
!>, <!!>)dnl
dnl
ifelse(eval(!defined_bool(<!INCLUDED_MOST_RECENT_BALLOT!>) && defined_bool(<!USE_MOST_RECENT_BALLOT!>)), eval(1), <!
define(<!INCLUDED_MOST_RECENT_BALLOT!>)dnl
/*
  This restriction states that the ballot at a specific index is the most
  recent one submitted for a particular pseudonym.
 */
restriction MostRecentBallot:
  "
    All bbid pseudo %idx #i.
          MostRecentBallot(bbid, pseudo, %idx)@i
      ==>
            (Ex ec %ts pk bs c sig bh #j.
                BB_Trace_Entry(bbid,
                               <'BBEntry_Ballot_Submission', ec, %ts,
                                <<'VA_Submit_Ballot', ec, pseudo, pk, bs, c>, sig>>,
                                bh, %idx)@j
              &
                #j < #i
            )
          &
            not (Ex ec %ts pk bs c sig bh %bidx #j.
              (
                BB_Trace_Entry(bbid,
                               <'BBEntry_Ballot_Submission', ec, %ts,
                                <<'VA_Submit_Ballot', ec, pseudo, pk, bs, c>, sig>>,
                                bh, %bidx)@j
                &
                  %idx << %bidx
                &
                  #j < #i
              )
            )
  "
!>, <!!>)dnl
dnl
ifelse(eval(!defined_bool(<!INCLUDED_UNAUTHORIZED!>) && defined_bool(<!USE_UNAUTHORIZED!>)), eval(1), <!
define(<!INCLUDED_UNAUTHORIZED!>)dnl
/*
  This restriction states that a specific public key is not authorized
  to vote under a particular pseudonym, either because it was never
  authorized or because its authorization has been superceded.
 */
restriction Unauthorized:
  "
    All ec pseudo pk #i.
          Unauthorized(ec, pseudo, pk)@i
      ==>
          (
              /* either no authorization for that public key and pseudonym */
              not (Ex bs %idx #j.
                (
                    DBB_Voter_Authorized_Trace(ec, pseudo, pk, bs, %idx)@j
                  &
                    #j < #i
                )
              )
            |
              /* or that public key isn't the most recent one for that pseudonym */
              (Ex bs %idx npk nbs %nidx #j #k.
                  DBB_Voter_Authorized_Trace(ec, pseudo, pk, bs, %idx)@j
                &
                  DBB_Voter_Authorized_Trace(ec, pseudo, npk, nbs, %nidx)@k
                &
                  #j < #k
                &
                  #k < #i
              )
          )
  "
!>, <!!>)dnl
dnl
ifelse(eval(!defined_bool(<!INCLUDED_MOST_RECENT_AUTHORIZATION!>) && defined_bool(<!USE_MOST_RECENT_AUTHORIZATION!>)), eval(1), <!
define(<!INCLUDED_MOST_RECENT_AUTHORIZATION!>)dnl
/*
  This restriction states that a specific public key is the most
  recently authorized one for a specific pseudonym.
 */
restriction MostRecentAuthorization:
  "
    All ec pseudo pk %idx #i.
          MostRecentAuthorization(ec, pseudo, pk, %idx)@i
      ==>
            Ex bs #j.
              (
                  DBB_Voter_Authorized_Trace(ec, pseudo, pk, bs, %idx)@j
                &
                  #j < #i
              )
          &
            not (Ex npk bs %nidx #j.
              (
                  DBB_Voter_Authorized_Trace(ec, pseudo, npk, bs, %nidx)@j
                &
                  #j < #i
                &
                  %idx << %nidx
              )
            )
  "
!>, <!!>)dnl
dnl
ifelse(eval(!defined_bool(<!INCLUDED_SUBMISSION_NOT_ON_BB!>) && defined_bool(<!USE_SUBMISSION_NOT_ON_BB!>)), eval(1), <!
define(<!INCLUDED_SUBMISSION_NOT_ON_BB!>)dnl
restriction SubmissionNotOnBB:
  "
    All bbid msg #i.
          SubmissionNotOnBB(bbid, msg)@i
      ==>
          not (
            Ex ec %ts eh %idx #j.
            (
                BB_Trace_Entry(bbid, <'BBEntry_Ballot_Submission', ec, %ts, msg>, eh, %idx)@j
              &
                #j < #i
            )
          )
  "
!>, <!!>)dnl
dnl
ifelse(eval(!defined_bool(<!INCLUDED_AUTHORIZATION_NOT_ON_BB!>) && defined_bool(<!USE_AUTHORIZATION_NOT_ON_BB!>)), eval(1), <!
define(<!INCLUDED_AUTHORIZATION_NOT_ON_BB!>)dnl
restriction AuthorizationNotOnBB:
  "
    All bbid msg #i.
          AuthorizationNotOnBB(bbid, msg)@i
      ==>
          not (
            Ex ec %ts eh %idx #j.
            (
                BB_Trace_Entry(bbid, <'BBEntry_Voter_Authorization', ec, %ts, msg>, eh, %idx)@j
              &
                #j < #i
            )
          )
  "
!>, <!!>)dnl
dnl
ifelse(eval(!defined_bool(<!INCLUDED_CAST_NOT_ON_BB!>) && defined_bool(<!USE_CAST_NOT_ON_BB!>)), eval(1), <!
define(<!INCLUDED_CAST_NOT_ON_BB!>)dnl
restriction CastNotOnBB:
  "
    All bbid msg #i.
          CastNotOnBB(bbid, msg1, msg2)@i
      ==>
          not (
            Ex ec %ts eh %idx #j.
            (
                BB_Trace_Entry(bbid, <'BBEntry_Ballot_Cast', ec, %ts, msg1, msg2>, eh, %idx)@j
              &
                #j < #i
            )
          )
  "
!>, <!!>)dnl
dnl
