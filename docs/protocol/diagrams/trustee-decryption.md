# Election Key Generation Subprotocol Sequence Diagram

We list the Trustee Board as a separate protocol actor here, even though it is maintained by the Trustee Administration Server, to show what gets posted to the board and what information the Trustee Adminstration Server reads from the board at the end of the protocol (to add to the election configuration).

``` mermaid
sequenceDiagram
    participant T1 as Trustee 1 (uses Trustee App)
    participant T2 as Trustee 2 (uses Trustee App)
    participant Tn as Trustee n (uses Trustee App)
    participant TB as Trustee Board
    participant TAS as Trustee Administration Server
    participant BP as Ballot Printer

    %% Air-Gapped Network Box (as defined in overview)
    box rgb(227, 243, 255) Air-Gapped Network Boundary
        participant T1
        participant T2
        participant Tn
        participant TB
        participant TAS
        participant BP
    end

    %% Trustee Board is always "active"

    note over TB: Trustee Board contains sufficient messages<br/>from the mixing subprotocol for trustees<br/>to check and use the final mix

    activate TB

    %% == Phase 1: Post Partial Decryptions ==
    Note over TB, Tn: Post Partial Decryptions
    Note over TB: All messages are mirrored<br/>to trustees' local boards
    TB->>T1: ElGamal Cryptograms Lists (Final Round)
    activate T1
    TB->>T2: ElGamal Cryptograms Lists (Final Round)
    activate T2
    Note over TB: Mirroring also occurs for T3 .. Tn-1
    TB->>Tn: ElGamal Cryptograms Lists (Final Round)
    activate Tn

    T1->>T1: Check that all ElGamal Cryptograms Lists<br/>are identical
    T1->>T1: Compute partial decryptions and their proofs
    T1->>TB: Post partial decryptions and their proofs
    deactivate T1

    T2->>T2: Check that all ElGamal Cryptograms Lists<br/>are identical
    T2->>T2: Compute partial decryptions and their proofs
    T2->>TB: Post partial decryptions and their proofs
    deactivate T2

    Note over T2, Tn: Steps repeated for T3 .. Tn-1

    Tn->>Tn: Check that all ElGamal Cryptograms Lists<br/>are identical
    Tn->>Tn: Compute partial decryptions and their proofs
    Tn->>TB: Post partial decryptions and their proofs
    deactivate Tn

    %% == Phase 2: Check Partial Decryptions, Post Decryptions ==
    TB->>T1: All partial decryption/proof messages
    activate T1 # Activate T1 when it has all shares and check values
    TB->>T2: All partial decryption/proof messages
    activate T2 # Activate T2 when it has all shares and check values

    Note over TB, Tn: Mirroring also occurs for T3 .. Tn-1

    TB->>Tn: All partial decryption/proof messages
    activate Tn # Activate Tn when it has all shares and check values

    T1->>T1: Check the partial decryption proofs
    T1->>T1: Combine the partial decryptions
    T1->>TB: Post decrypted ballot plaintext list
    deactivate T1

    T2->>T2: Check the partial decryption proofs
    T2->>T2: Combine the partial decryptions
    T2->>TB: Post decrypted ballot plaintext list
    deactivate T2

    Note over T2, Tn: Steps repeated for T3 .. Tn-1

    Tn->>Tn: Check the partial decryption proofs
    Tn->>Tn: Combine the partial decryptions
    Tn->>TB: Post decrypted ballot plaintext list
    deactivate Tn

    %% == Phase 3: Print Ballots ==

    TB->>TAS: Decrypted ballot plaintext lists<br/>(from all trustees)
    deactivate TB
    activate TAS

    TAS->>TAS: Check that all trustees' decrypted ballot<br/>plaintext lists are identical, and<br/>no errors were reported
    TAS->>BP: Send ballot plaintext list to print queue
    activate BP
    BP->>BP: Print physical ballots sequentially from list
    Note over BP: Output: Set of Marked Ballots (Paper)
    BP->>TAS: Ack/Status (Batch Print Job Complete/Failed)
    deactivate TAS
    deactivate BP
```
