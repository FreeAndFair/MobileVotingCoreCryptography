# Election Key Generation Subprotocol Sequence Diagram

``` mermaid
sequenceDiagram
    participant T1 as Trustee 1 (uses Trustee App)
    participant T2 as Trustee 2 (uses Trustee App)
    participant Tn as Trustee n (uses Trustee App)
    participant TAS as Trustee Administration Server

    %% Air-Gapped Network Box (as defined in overview)
    box rgb(227, 243, 255) Air-Gapped Network Boundary
        participant T1
        participant T2
        participant Tn
        participant TAS
    end

    Note over T1, Tn: Assumes pre-agreed ElGamal parameters (p, g). <br/> Trustees interact via their dedicated Trustee Applications (on offline devices).

    %% == Phase 1: Share Generation and Commitment ==
    activate T1
    T1->>T1: Generate private share x1
    T1->>T1: Calculate public share y1 = g^x1 mod p
    T1->>T1: Generate ZKP P1 for x1 (Proof of knowledge)
    T1->>TAS: Submit Public Share & Proof (y1, P1)
    deactivate T1
    activate TAS # Activate TAS to receive/collect shares

    activate T2
    T2->>T2: Generate private share x2
    T2->>T2: Calculate public share y2 = g^x2 mod p
    T2->>T2: Generate ZKP P2 for x2
    T2->>TAS: Submit Public Share & Proof (y2, P2)
    deactivate T2
    %% TAS remains active collecting shares

    Note over T2, Tn: Steps repeated for T3...Tn-1 (Generation & Submission)

    activate Tn
    Tn->>Tn: Generate private share xn
    Tn->>Tn: Calculate public share yn = g^xn mod p
    Tn->>Tn: Generate ZKP Pn for xn
    Tn->>TAS: Submit Public Share & Proof (yn, Pn)
    deactivate Tn
    %% TAS has now collected all shares

    %% == Phase 2: Share Distribution ==
    Note over TAS: Distributes all collected shares/proofs [(y1,P1)...(yn,Pn)] to all Trustees
    TAS-->>T1: Distribute All Shares & Proofs
    activate T1 # Activate T1 upon receiving broadcast
    TAS-->>T2: Distribute All Shares & Proofs
    activate T2 # Activate T2 upon receiving broadcast

    Note over TAS, Tn: Broadcast continues for T3...Tn-1

    TAS-->>Tn: Distribute All Shares & Proofs
    activate Tn # Activate Tn upon receiving broadcast
    deactivate TAS # TAS finishes distribution phase

    %% == Phase 3: Verification, Key Computation & Storage ==
    %% T1 processes
    T1->>T1: Verify all proofs P1...Pn
    Note right of T1: On failure: Abort/Handle Exception
    T1->>T1: Calculate Joint Election Public Key y = y1 * y2 * ... * yn mod p
    T1->>T1: Securely store private share x1 on Trustee Storage (e.g., encrypted USB)
    %% T1 remains active to confirm key

    %% T2 processes
    T2->>T2: Verify all proofs P1...Pn
    Note right of T2: On failure: Abort/Handle Exception
    T2->>T2: Calculate Joint Election Public Key y = y1 * y2 * ... * yn mod p
    T2->>T2: Securely store private share x2 on Trustee Storage
    %% T2 remains active to confirm key

    Note over T2, Tn: Verification, Key Computation & Local Storage repeated for T3...Tn-1

    %% Tn processes
    Tn->>Tn: Verify all proofs P1...Pn
    Note right of Tn: On failure: Abort/Handle Exception
    Tn->>Tn: Calculate Joint Election Public Key y = y1 * y2 * ... * yn mod p
    Tn->>Tn: Securely store private share xn on Trustee Storage
    %% Tn remains active to confirm key

    %% == Phase 4: Final Key Confirmation (within Air-Gap) ==
    activate TAS # Activate TAS to receive final key confirmations
    T1->>TAS: Confirm Computed Public Key (y)
    deactivate T1 # T1 processing complete for DKG

    T2->>TAS: Confirm Computed Public Key (y)
    deactivate T2 # T2 processing complete for DKG

    Note over T2, Tn: Final key confirmation repeated for T3...Tn-1

    Tn->>TAS: Confirm Computed Public Key (y)
    deactivate Tn # Tn processing complete for DKG

    Note over T1, Tn: All trustees confirmed computation of the same Election Public Key 'y'. <br/> Each Trustee 'Ti' has stored their private share 'xi' locally on secure Trustee Storage.
    Note right of TAS: TAS now holds the final Election Public Key 'y', ready for secure export from the air-gap (via Election Admin using physical media).
    deactivate TAS # TAS processing complete for DKG subprotocol
```
