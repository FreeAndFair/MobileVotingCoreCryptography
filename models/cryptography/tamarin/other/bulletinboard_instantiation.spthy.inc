/*
  Bulletin Board Instantiation

  These rules and lemmas instantiate bulletin boards and verify
  some bulletin board executability properties.

  @author Daniel M. Zimmerman
  @copyright Free & Fair 2025
  @version 0.1
 */

/*
  This rule creates public bulletin boards.
 */
rule BulletinBoard_Test_Create [role="BulletinBoardTester"]:
    [ Fr(~reqid),
      In(m) ]
  --[ BB_Trace_Test_Create_Requested(~reqid, m) ]->
    [ BB_Create_Request(~reqid, m),
      BB_Test_Create_Requested(~reqid, m) ]

/*
  This rule waits for acknowledgement of public bulletin board creation.
 */
rule BulletinBoard_Test_Receive_Created [role="BulletinBoardTester"]:
    [ BB_Test_Create_Requested(reqid, m),
      !BB_Root(reqid, bbid, m, mh) ]
  --[ BB_Trace_Test_Create_Acknowledged(reqid, bbid) ]->
    [ BB_Test_Append(bbid) ]

/*
  This rule appends to created public bulletin boards. Note that it
  picks effectively a random element on the board to append to, so
  it will sometimes fail (and result in that trace getting "stuck"
  waiting for a message to be appended).
 */
rule BulletinBoard_Test_Append [role="BulletinBoardTester"]:
    [ In(m),
      BB_Test_Append(bbid),
      !BB_Root(reqid, bbid, r, rh),
      !BB_Entry(bbid, e, eh, %idx) ]
  --[ BB_Trace_Test_Append_Requested(bbid, m, %idx) ]->
    [ BB_Append_Request(bbid, m, %idx),
      BB_Test_Append_Requested(bbid, m, %idx) ]

/*
  This rule teminates bulletin boards.
 */
rule BulletinBoard_Test_Terminate [role="BulletinBoardTester"]:
    [ BB_Test_Append(bbid),
      !BB_Root(reqid, bbid, r, rh),
      !BB_Entry(bbid, e, eh, %idx) ]
  --[ BB_Trace_Test_Stopped(bbid) ]->
    [ BB_Terminate_Request(bbid, %idx) ]

/*
  This rule waits for a message to be posted to the bulletin board and
  then re-starts the "append or terminate" loop.
 */
rule BulletinBoard_Test_Receive_Append_Acknowledgement [role="BulletinBoardTester"]:
    [ BB_Test_Append_Requested(bbid, m, %idx),
      !BB_Root(reqid, bbid, r, rh),
      !BB_Entry(bbid, m, mh, %idx %+ %1) ]
  --[ BB_Trace_Test_Append_Acknowledged(bbid, m, %idx) ]->
    [ BB_Test_Append(bbid) ]

/*
  Executability lemmas (must start with "Executability" in order to be
  automatically checked in CV. Those with proof scripts are prefaced with
  "Script".
 */

/*
  This lemma states that it's possible to have a bulletin board with more than
  one distinct entry.
 */
lemma Executability_BB_MoreThanOneEntry:
  exists-trace
  "
     Ex reqid bbid r rh m1 m1h m2 m2h %idx1 %idx2 #i #j #k.
          BB_Trace_Root(reqid, bbid, r, rh)@i
        &
          BB_Trace_Entry(bbid, m1, m1h, %idx1)@j
        &
          BB_Trace_Entry(bbid, m2, m2h, %idx2)@k
        &
          not (#j = #k)
        &
          not (m1 = m2)
        &
          not (m1h = m2h)
        &
          not (%idx1 = %idx2)
  "

/*
  This lemma states that creation of a bulletin board is acknowledged at some point.
 */
lemma Executability_BB_Acknowledge:
  exists-trace
  "
    Ex reqid bbid #i.
      BB_Trace_Test_Create_Acknowledged(reqid, bbid)@i
  "

/*
  This lemma states that appending to a bulletin board is acknowledged at some point.
 */
lemma Executability_BB_Append:
  exists-trace
  "
    Ex bbid m %idx #i.
      BB_Trace_Test_Append_Acknowledged(bbid, m, %idx)@i
  "

/*
  This lemma states that a hash chain can in fact be created and
  appended to.
 */
lemma Executability_BB_Stopped:
  exists-trace
  "
    Ex bbid l lh %idx #i #j.
        BB_Trace_Test_Stopped(bbid)@i
      &
        BB_Trace_Last(bbid, l, lh, %idx)@j
  "

/*
  This lemma states that an execution exists where a bulletin board has at least
  two entries and their relationship to each other is correct.
 */
lemma Executability_BB_Explicit:
  exists-trace
  "
    Ex reqid bbid m0 m0h m1 #i #j.
        BB_Trace_Root(reqid, bbid, m0, m0h)@i
      &
        BB_Trace_Entry(bbid, m0, m0h, %1)@i
      &
        BB_Trace_Entry(bbid, m1, h(<m1, m0h>), %1 %+ %1)@j
  "
