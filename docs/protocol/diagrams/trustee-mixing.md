# Trustee Ballot Mixing Subprotocol Sequence Diagram
```mermaid
sequenceDiagram
    participant EA as Election Admin
    participant DBB as Digital Ballot Box
    participant EA_Storage as Election Admin Storage
    participant TAS as Trustee Administration Server (Air-Gapped)
    participant T1 as Trustee 1 (uses Trustee App)
    participant T2 as Trustee 2 (uses Trustee App)
    participant Tn as Trustee n (uses Trustee App)

    %% == Phase 1: Data Transfer into Air Gap ==
    Note over EA, DBB: Election Period Ends
    activate EA
    EA->>DBB: Request Export Cast Ballots
    activate DBB
    DBB-->>EA: Cast Digital Ballot Cryptograms
    deactivate DBB
    EA->>EA_Storage: Write Cryptograms to Media
    Note right of EA_Storage: Physical Transfer into Air Gap
    deactivate EA

    box rgb(227, 243, 255) Air-Gapped Network Boundary
        participant TAS
        participant T1
        participant T2
        participant Tn
    end %% Air-Gapped Network Boundary

        activate TAS # Activated by data import
        EA_Storage->>TAS: Provide Cryptograms on Media
        TAS->>TAS: Import Cast Cryptograms List L0
        Note over TAS: Ready to start Mixnet

        %% == Phase 2: Mix Round 1 (Trustee 1) ==
        Note over TAS, T1: TAS initiates Round 1
        TAS->>T1: Initial Ballot List L0
        deactivate TAS # TAS waits for T1's result
        activate T1
        T1->>T1: Shuffle List L0
        T1->>T1: Re-encrypt ballots in shuffled list
        T1->>T1: Generate ZKP (Proof_1) of correct shuffle/re-encryption
        Note left of T1: Output: Mixed List L1, Proof_1
        T1->>TAS: Submit Mixed List & Proof (L1, Proof_1)
        deactivate T1
        activate TAS # TAS receives result and orchestrates verification

        %% == Phase 3: Verification Round 1 ==
        Note over TAS: Distributes L1 & Proof_1 for verification
        TAS-->>T2: Distribute (L1, Proof_1)
        activate T2
        TAS-->>Tn: Distribute (L1, Proof_1)
        activate Tn
        Note over TAS, Tn: Distribution to T3...T(n-1) omitted for brevity

        T2->>T2: Verify Proof_1 against L0, L1
        Note right of T2: On failure: Abort/Dispute
        T2-->>TAS: Verification Result 1 (Success)
        deactivate T2

        Tn->>Tn: Verify Proof_1 against L0, L1
        Note right of Tn: On failure: Abort/Dispute
        Tn-->>TAS: Verification Result 1 (Success)
        deactivate Tn
        Note over TAS: TAS collects all verification results for Round 1

        %% == Phase 4: Mix Round 2 (Trustee 2) ==
        Note over TAS, T2: TAS initiates Round 2 (assuming Round 1 verified)
        TAS->>T2: Mixed Ballot List L1 (Input for Round 2)
        deactivate TAS # TAS waits for T2's result
        activate T2
        T2->>T2: Shuffle List L1
        T2->>T2: Re-encrypt ballots
        T2->>T2: Generate ZKP (Proof_2)
        Note left of T2: Output: Mixed List L2, Proof_2
        T2->>TAS: Submit Mixed List & Proof (L2, Proof_2)
        deactivate T2
        activate TAS # TAS receives result and orchestrates verification

        %% == Phase 5: Verification Round 2 ==
        Note over TAS: Distributes L2 & Proof_2 for verification
        TAS-->>T1: Distribute (L2, Proof_2)
        activate T1
        TAS-->>Tn: Distribute (L2, Proof_2)
        activate Tn
        Note over TAS, Tn: Distribution to T3...T(n-1) omitted

        T1->>T1: Verify Proof_2 against L1, L2
        Note right of T1: On failure: Abort/Dispute
        T1-->>TAS: Verification Result 2 (Success)
        deactivate T1

        Tn->>Tn: Verify Proof_2 against L1, L2
        Note right of Tn: On failure: Abort/Dispute
        Tn-->>TAS: Verification Result 2 (Success)
        deactivate Tn
        Note over TAS: TAS collects all verification results for Round 2

        %% == Phase ... Subsequent Rounds ... ==
        Note over T1, Tn: Mixing and Verification steps repeat for T3...T(n-1)

        %% == Phase N: Mix Round N (Trustee n) ==
        Note over TAS, Tn: TAS initiates Round N
        TAS->>Tn: Mixed Ballot List L(n-1) (Input for Round N)
        deactivate TAS
        activate Tn
        Tn->>Tn: Shuffle List L(n-1)
        Tn->>Tn: Re-encrypt ballots
        Tn->>Tn: Generate ZKP (Proof_n)
        Note left of Tn: Output: Final Mixed List Ln, Proof_n
        Tn->>TAS: Submit Final Mixed List & Proof (Ln, Proof_n)
        deactivate Tn
        activate TAS

        %% == Phase N+1: Final Verification Round N ==
        Note over TAS: Distributes Ln & Proof_n for final verification
        TAS-->>T1: Distribute (Ln, Proof_n)
        activate T1
        TAS-->>T2: Distribute (Ln, Proof_n)
        activate T2
        Note over TAS, T2: Distribution to T3...T(n-1) omitted

        T1->>T1: Verify Proof_n against L(n-1), Ln
        Note right of T1: On failure: Abort/Dispute
        T1-->>TAS: Verification Result N (Success)
        deactivate T1

        T2->>T2: Verify Proof_n against L(n-1), Ln
        Note right of T2: On failure: Abort/Dispute
        T2-->>TAS: Verification Result N (Success)
        deactivate T2
        Note over TAS: TAS collects all verification results for Round N

        Note over TAS: Final Mixed Ballot List Ln is ready for Decryption Subprotocol. <br/> Proofs (Proof_1...Proof_n) retained as audit evidence.
        deactivate TAS # Mixing Subprotocol Complete
```
