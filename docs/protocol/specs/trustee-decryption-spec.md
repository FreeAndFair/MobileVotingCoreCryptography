# Trustee Decryption Subprotocol

This subprotocol specifies the interactions between the trustees and the trustee administration server (TAS) that transform the (already mixed) list of ballot ciphertexts into a list of plaintexts to be tallied.

## Trustee Protocol Communication

As with the election key generation and trustee mixing protocols, the TAS performs minimal computation in this protocol. It performs three main functions: providing a "trustee board" on which the trustees can post protocol messages; validating the final round of messages posted by the trustees at the end of the subprotocol before printing them or writing them to a storage device for later printing by the election administrator; and (if necessary) posting an initial message to the trustee board containing the set of encrypted ballots that needs to be decrypted.

More information on the trustee board mechanism is avaiable in the [election key protocol specification](./election-key-gen-spec.md).

We assume that this subprotocol starts in one of two ways: (1) trustee computation picks up where the trustee mixing subprotocol left off, with the same trustee board, such that the messages from the final round of the trustee mixing subprotocol are already on the board; or (2) the TAS initializes the trustee board to contain either all, or only the last round of, the mixing subprotocol messages. In either event, the trustees start from `K` **ElGamal Cryptograms Message**s with the same `original_message_source` (the trustee that shuffled last), identical aside from signatures and signing trustee public keys. For efficiency, if the mixing and decryption subprotocols take place at different times or in different places, an implementation might choose to coalesce these `K` messages into a single message similar to the **Initial Cryptograms Message** in the trustee mixing subprotocol, but containing all the trustee public keys and signatures for the final mix. We do not describe the format of such a coalesced message here.

In this subprotocol, the trustees need to wait for messages from all participating trustees before proceeding. This implies that the trustees know the entire set of participating trustees, and that the set of participating trustees cannot change _during_ the protocol execution without causing the protocol to fail. The set of participating trustees is provided to all the participating trustees either out of band, or as part of an initial protocol message posted by the TAS.

## Phase 1: Post Partial Decryptions

In this phase, all participating trustees perform their own partial decryptions of the mixed ballot cryptograms and post their results to the trustee board. They perform the same message checks on the initial **ElGamal Cryptograms Message**s that they would perform to conclude a round of the trustee mixing subprotocol. These checks can be skipped if the same set of participating trustees executes this subprotocol immediately after the trustee mixing subprotocol, because they will have already performed it; however, if the set of participating trustees is different, they should perform the checks again.

### ElGamal (EG) Cryptograms Message

sender
: All Participating Trustees from Mixing Subprotocol, or TAS

recipient
: All Participating Trustees

board slot
: (`message_type`, `source_trustee`, `public_key`)

purpose
: Post a initial shuffled list of ElGamal cryptograms and corresponding shuffle proofs (from the mixing subprotocol).

_**structure**_

```rust
struct EGCryptogramsMessage {
  message_type : enum,
  election_hash : String,
  original_message_source : String,
  cryptograms : List<EGCryptogram>,
  shuffle_proofs: List<ShuffleProof>,
  public_key : String,
  signature : String
}
```

- `message_type`: The type of this message ("ElGamal cryptograms").
- `election_hash`: The hash of the unique election configuration item.
- `original_message_source` : The public signing key of the trustee that performed the shuffle to generate the list of cryptograms and shuffle proofs in this message; that is, the protocol actor that first sent the lists of cryptograms and shuffle proofs in this message.
- `cryptograms`: The list of shuffled cryptograms.
- `shuffle_proofs` : The shuffle proofs corresponding to the `cryptograms` list.
- `public_key` : The public key of the trustee signing this message.
- `signature`: A digital signature created with the signing key corresponding to `public_key` over the contents of this message minus the signature itself.

channel properties
: The `signature` is intended to provide authenticity and integrity over the message contents.

### ElGamal Cryptograms Message Checks

1. The `election_hash` is the hash of the election configuration item for the current election.
2. The `original_message_source` is a valid trustee for this election.
3. The `cryptograms` list contains a list of cryptograms valid for this election.
4. The `cryptograms` list is identical to the `cryptograms` list in every other `EGCryptogramMessage` with the same `original_message_source`.
5. The `shuffle_proofs` list contains valid shuffle proofs for the `cryptograms` list.
6. The `public_key` is a valid signing key for a trustee in this election.
7. The `signature` is a valid signature matching the `public_key` over the contents of this message minus the signature itself.

### Partial Decryption Message

sender
: Participating Trustee

recipient
: All Participating Trustees

board slot
: (`message_type`, `public_key`)

purpose
: Post the trustee's partial decryptions so that the other trustees can validate them.

_**structure**_

```rust
struct PartialDecryptionMessage {
  message_type : enum,
  election_hash : String,
  partial_decryptions : List<PartialDecryption>,
  public_key : String,
  signature : String
}

struct PartialDecryption {
  decrypted_component : String,
  proof : String
}
```

- `message_type`: The type of this message ("partial decryptions").
- `election_hash`: The hash of the unique election configuration item.
- `partial_decryptions` : The list of partial decryptions (and their proofs) generated by the trustee.
- `public_key` : The public key of the trustee signing this message.
- `signature`: A digital signature created with the signing key corresponding to `public_key` over the contents of this message minus the signature itself.

channel properties
: The `signature` is intended to provide authenticity and integrity over the message contents.

### Partial Decryption Message Checks

1. The `election_hash` is the hash of the election configuration item for the current election.
2. The `partial_decryptions` list contains a well formed partial decryption for each ciphertext in the list of cryptograms being decrypted, and each partial decryption proof verifies correctly.
3. The `public_key` is a valid signing key for a trustee participating in this subprotocol.
4. The `signature` is a valid signature matching the public signing key of the Trustee Administration Server.

## Phase 2: Partial Decryption Verification and Combination

In this phase, each trustee waits for all participating trustees to post partial decryption messages, and performs the `PartialDecryptionsMessage` checks on all of them. If all these checks succeed, the trustee combines the partial decryptions and posts them to the trustee board.

At the end of a successful phase 2, there are `K` messages with identical content (aside from signing trustee key and signature) on the trustee board containing the decrypted list of cryptograms. When this occurs, and the messages pass all the checks listed below, the decryption subprotocol is complete. If the messages do not pass the checks, or do not have identical content, the decryption subprotocol fails. This validation of the decrypted ballots does not result in any protocol messages, as the success or failure of the protocol is self-evident from whether the lists of decrypted ballots in the `DecryptedBallotMessage`s are identical; it does, however, allow trustees to report that failure if the TAS does not detect it.

### Decrypted Ballots Message

sender
: Participating Trustee

recipient
: All Participating Trustees

board slot
: (`message_type`, `public_key`)

purpose
: Post the trustee's partial decryptions so that the other trustees can validate them.

```rust
struct DecryptedBallotsMessage {
  message_type : enum,
  election_hash : String,
  decrypted_ballots : List<Ballot>,
  public_key : String,
  signature : String
}
```

- `message_type`: The type of this message ("decrypted ballots").
- `election_hash`: The hash of the unique election configuration item.
- `decrypted_ballots` : The list of decrypted ballots generated by the trustee.
- `public_key` : The public key of the trustee signing this message.
- `signature`: A digital signature created with the signing key corresponding to `public_key` over the contents of this message minus the signature itself.

channel properties
: The `signature` is intended to provide authenticity and integrity over the message contents.

### Decrypted Ballots Message Checks

1. The `election_hash` is the hash of the election configuration item for the current election.
2. The `decrypted_ballots` list contains a plaintext ballot corresponding to the initial list of ballot cryptograms (from the initial `ElGamalCryptogramsMessage`), and each plaintext ballot has the same ballot style as its corresponding cryptogram.
3. The `decrypted_ballots` list is identical to the `decrypted_ballots` list in every other `DecryptedBallotsMessage`.
4. The `public_key` is a valid signing key for a trustee participating in this subprotocol.
5. The `signature` is a valid signature matching the `public_key` over the contents of this message minus the signature itself.

## Protocol Diagrams

Note that, in these diagrams, a trustee "awaits" a message by waiting until the specified message appears on its local copy of the trustee board. Any "await" state can cause the protocol to fail if the message does not arrive within some reasonable amount of time, but these timeouts are not explicitly listed in the state diagram.

## Trustee Process Diagram

```mermaid
    stateDiagram-v2
      await_init : Await **El-Gamal Cryptograms Message**
      check_init : Check Message Contents and Shuffle Proofs
      post_partial_decryptions : Generate Partial Decryptions and Post **Partial Decryption Message**
      await_partial_decryptions: Await all **Partial Decryption Message**s
      check_partial_decryptions: Check the Partial Decryptions
      combine_partial_decryptions: Combine the Partial Decryptions and Post **Decrypted Ballots Message**
      await_decrypted_ballots : Await all **Decrypted Ballots Message**s
      check_decrypted_ballots : Check the Decrypted Ballots

      complete : **Success** - Ballot Cryptograms Decrypted
      error : **Failure** - Protocol Aborted with Error Message

      [*] --> await_init

      await_init --> check_init
      check_init --> error : Invalid Shuffled Cryptograms Message
      check_init --> post_partial_decryptions
      post_partial_decryptions --> await_partial_decryptions
      await_partial_decryptions --> check_partial_decryptions
      check_partial_decryptions --> error : Invalid Partial Decryptions
      check_partial_decryptions --> combine_partial_decryptions : Valid Partial Decryptions
      combine_partial_decryptions --> await_decrypted_ballots
      await_decrypted_ballots --> check_decrypted_ballots
      check_decrypted_ballots --> error : Invalid Decrypted Ballots
      check_decrypted_ballots --> complete : Valid Decrypted Ballots

      complete --> [*]
      error --> [*]
```

## Trustee Administration Server Process Diagram

```mermaid
    stateDiagram-v2
      post_init : Post Initial **ElGamal Cryptograms Message** (if necessary)
      await_decryption : Await Final Round **Decrypted Ballots Message**s
      check_messages: Check Message Contents

      complete : **Success** - Ballot Cryptograms Decrypted
      error : **Failure** Protocol Aborted with Error Message

      [*] --> post_init
      post_init --> await_decryption
      await_decryption --> check_messages
      check_messages --> complete : Messages Valid
      check_messages --> error : Messages Invalid

      complete --> [*]
      error --> [*]
```
