/*
  Tamarin formalization of the public bulletin board. This implements the
  board as a hash chain of messages, which is manipulated directly using
  linear facts and writes its entries using persistent facts (while
  emitting appropriate action facts for traceability/reasoning).

  @author Daniel M. Zimmerman
  @copyright Free & Fair 2025
  @version 0.1
 */

#ifdef BULLETINBOARD_SPTHY_INC

/* The bulletin board is already included and should not be included again. */

#else
#define BULLETINBOARD_SPTHY_INC

#include "./primitives.spthy.inc"
#include "./channels.spthy.inc"

/*
  This rule creates a new bulletin board from request id `reqid`
  with id `bbid`, using message `m` as its root entry. It creates action
  facts and persistent facts for the bulletin board's root information and
  first entry, and a linear fact for the "current" entry. We use Tamarin's
  natural number theory to assign entry numbers to the entries.

  Only one bulletin board can ever be created with each `reqid` (and `bbid`,
  because `bbid` is a fresh value), and bulletin board entries, once written,
  are immutable.
 */
rule BulletinBoard_Create [role="BulletinBoard"]:
    let mh = h(<m, ~bbid>) in
    [ BB_Create_Request(reqid, m),
      Fr(~bbid) ]
  --[ Unique(<'BulletinBoard_Create', reqid>),
      BB_Trace_Root(reqid, ~bbid, m, mh),
      BB_Trace_Entry(~bbid, m, mh, %1) ]->
    [ !BB_Root(reqid, ~bbid, m, mh),
      !BB_Entry(~bbid, m, mh, %1),
      BB_Current(~bbid, m, mh, %1) ]

/*
  This rule adds a new entry to bulletin board `bbid`, using
  message `m` as the entry's contents, and referring to the current
  index `%idx`. The entry, once written, is immutable.
 */
rule BulletinBoard_Append [role="BulletinBoard"]:
    let mh = h(<m, ch>)
        new_idx = %idx %+ %1 in
    [ !BB_Root(reqid, bbid, r, rh),
      BB_Current(bbid, c, ch, %idx)[+],
      BB_Append_Request(bbid, m, %idx)[+] ]
  --[ BB_Trace_Entry(bbid, m, mh, new_idx),
      BB_NotTerminated(bbid) ]->
    [ !BB_Entry(bbid, m, mh, new_idx),
      BB_Current(bbid, m, mh, new_idx) ]

/*
  This rule "terminates" bulletin board `bbid`, such that it can
  no longer be appended to. Because entries are immutable, the
  bulletin board can no longer be changed after this rule is
  executed.
 */
rule BulletinBoard_Terminate [role="BulletinBoard"]:
    [ !BB_Root(reqid, bbid, r, rh),
      !BB_Entry(bbid, c, ch, %idx)[+],
      BB_Current(bbid, c, ch, %idx)[+],
      BB_Terminate_Request(bbid, %idx)[+] ]
  --[ BB_Trace_Last(bbid, c, ch, %idx) ]->
    [ !BB_Last(bbid, c, ch, %idx) ]

/*
  This restriction enforces in the trace that any rule that relies
  on the bulletin board not being "terminated" must execute before
  the last bulletin board entry appears in the trace. This is a bit
  of a cheat, but it is a sound one as long as `BB_Current(bbid, ...`
  appears in the precondition of any rule restricted by
  `BB_NotTerminated(bbid)`. It directly encodes the fact that the
  `BB_Current` linear fact is removed from the environment for a
  unique `bbid`, and can never be regenerated for that `bbid` (unless
  somebody composes these rules with a new rule that does so) because
  `bbid` is a fresh value` in the only rule that can establish a
  `BB_Current(bbid, ...)` fact for a `bbid` that doesn't have one.
 */
restriction BulletinBoard_NotTerminated:
  "
    All bbid #i.
          BB_NotTerminated(bbid)@i
      ==>
          not Ex m mh %idx #j. BB_Trace_Last(bbid, m, mh, %idx)@j & #j < #i
  "

/*
  Safety lemmas (must start with "Safety" in order to be
  automatically checked in CV).
 */

/*
  This lemma states that there cannot be two roots with the same
  reqid or bbid created at different times.
 */
lemma Safety_BB_UniqueIDs [reuse]:
 "
    All reqid1 reqid2 bbid1 bbid2 r1 r2 rh1 rh2 #i #j.
          BB_Trace_Root(reqid1, bbid1, r1, rh1)@i
        &
          BB_Trace_Root(reqid2, bbid2, r2, rh2)@j
        &
          not (#i = #j)
    ==>
        not (reqid1 = reqid2) & not (bbid1 = bbid2)
 "

/*
  This lemma states that there can only be one root entry for
  any bulletin board (identified by reqid and bbid).
 */
lemma Safety_BB_UniqueRoot [reuse]:
  "
    All reqid bbid r1 r2 rh1 rh2 #i #j.
            BB_Trace_Root(reqid, bbid, r1, rh1)@i
          &
            BB_Trace_Root(reqid, bbid, r2, rh2)@j
      ==>
          #i = #j & r1 = r2 & rh1 = rh2
  "

/*
  This lemma states that there can only be one entry on any bulletin
  board (identified by bbid) with the same idx.
 */
lemma Safety_BB_UniqueEntries [reuse]:
  "
    All bbid m1 m2 mh1 mh2 %idx #i #j.
            BB_Trace_Entry(bbid, m1, mh1, %idx)@i
          &
            BB_Trace_Entry(bbid, m2, mh2, %idx)@j
      ==>
          #i = #j & m1 = m2 & mh1 = mh2
  "

/*
  This lemma states that for every entry on a given bulletin board
  with a given idx greater than 1, there must be a matching previous
  entry. This establishes that there can be no missing entries.
 */
lemma Safety_BB_ChainLinks [reuse]:
  "
    All bbid m mh %idx #i.
          BB_Trace_Entry(bbid, m, mh, (%idx %+ %1))@i
      ==>
          (Ex p ph #j. BB_Trace_Entry(bbid, p, ph, %idx)@j & #j < #i & mh = h(<m, ph>))
  "
/*
  This lemma states that bulletin board entries are created in natural
  number order.
 */
lemma Safety_BB_CreationOrder [reuse]:
  "
    All bbid m1 m2 mh1 mh2 %idx1 %idx2 #i #j.
            BB_Trace_Entry(bbid, m1, mh1, %idx1)@i
          &
            BB_Trace_Entry(bbid, m2, mh2, %idx2)@j
          &
            %idx1 << %idx2
      ==>
          #i < #j
  "

/*
  This lemma states that entry #1 on a bulletin board must always match
  a root.
 */
lemma Safety_BB_RootEntry [reuse]:
  "
    All bbid m mh #i.
          BB_Trace_Entry(bbid, m, mh, %1)@i
      ==>
          Ex reqid. BB_Trace_Root(reqid, bbid, m, mh)@i & mh = h(<m, bbid>)
  "

/*
  This lemma states that the last entry on the bulletin board (if there is one)
  must always match an actual entry.
 */
lemma Safety_BB_Termination [reuse]:
  "
    All bbid m mh %idx #i.
          BB_Trace_Last(bbid, m, mh, %idx)@i
      ==>
          (Ex #j. BB_Trace_Entry(bbid, m, mh, %idx)@j & #j < #i)
  "

/*
  This lemma states that there can't be any bulletin board entries after
  the last one.
 */
lemma Safety_BB_LastIsLast [reuse]:
  "
    All bbid l lh %lidx m mh %midx #i #j.
            BB_Trace_Last(bbid, l, lh, %lidx)@i
          &
            BB_Trace_Entry(bbid, m, mh, %midx)@j
      ==>
          (%midx << %lidx | %midx = %lidx) & #j < #i
  "

#endif
