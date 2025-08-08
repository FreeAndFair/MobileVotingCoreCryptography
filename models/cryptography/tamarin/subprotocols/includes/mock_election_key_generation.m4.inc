dnl
dnl This is the m4 input file for mocking election key generation.
dnl
dnl @author Daniel M. Zimmerman
dnl @copyright Free & Fair 2025
dnl @version 0.1
dnl
dnl We need some macros that differ slightly from those in the trustee
dnl macros file, so that we can mock the setup process by creating a
dnl bunch of fresh values.
dnl

define(<!USE_ABSTRACTED_NAOR_YUNG!>)dnl
include(common/primitives.m4.inc)

/*
  The trustee shares and trustee keys, which would have been created
  during the key generation process, need to be defined here. We use the
  linear fact "TAS_State_BeginTrusteeThresholdKeyGen()" as a trigger.
  We do not mock the bulletin board entries for the key generation process,
  as they don't particularly matter. We also do not mock the persistent
  facts used by trustees to check messages in the key generation protocol.
 */
rule Mock_ElectionKeyGeneration [role="Mock"]:
  let pk_election = threshold_pubkey(forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!check_value(~private_share<!!>TN<!!>)<!!>ifelse(eval(TN < TRUSTEE_COUNT), eval(1), <!, !>, <!!>)!>)) in
    [ TAS_State_BeginTrusteeThresholdKeygen(),dnl
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!
      Fr(~private_share<!!>TN<!!>),!>) ]
  --[ Unique('Mock_ElectionKeyGeneration'),dnl
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!
      /* Trustee <!!>TN<!!> */
      Trustee_GenerateElectionPublicKey_Trace('Trustee<!!>TN<!!>', pk_election),
      Trustee_CheckGeneratedElectionPublicKeys_Trace('Trustee<!!>TN<!!>', pk_election),!>) ]->
    [ /* Persistent Facts */
      !ElectionPublicKey(pk_election),dnl
forloop(<!TN!>, <!1!>, TRUSTEE_COUNT, <!
      /* Trustee <!!>TN<!!> */
      !Trustee_Private_Share('Trustee<!!>TN<!!>', ~private_share<!!>TN<!!>),
      !Trustee_ElectionPublicKey('Trustee<!!>TN<!!>', pk_election),
      !Trustee_ElectionPublicKey_Agreement('Trustee<!!>TN<!!>', pk_election),!>)
      /*
        Linear facts (triggering the TAS to initialize the trustee board and
        gather the ballots for mixing/decryption)
       */
      TAS_State_BeginTrusteeMixing(),
      /* Ensure the adversary has the election public key */
      Out(pk_election) ]
