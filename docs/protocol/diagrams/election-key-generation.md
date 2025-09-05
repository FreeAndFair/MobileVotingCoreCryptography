# Election Key Generation Subprotocol Sequence Diagram

We list the Trustee Board as a separate protocol actor here, even though it is maintained by the Trustee Administration Server, to show what gets posted to the board and what information the Trustee Adminstration Server reads from the board at the end of the protocol (to add to the election configuration).

``` mermaid
sequenceDiagram
    participant T1 as Trustee 1 (uses Trustee App)
    participant T2 as Trustee 2 (uses Trustee App)
    participant Tn as Trustee n (uses Trustee App)
    participant TB as Trustee Board
    participant TAS as Trustee Administration Server

    %% Air-Gapped Network Box (as defined in overview)
    box rgb(227, 243, 255) Air-Gapped Network Boundary
        participant T1
        participant T2
        participant Tn
        participant TB
        participant TAS
    end

    %% Trustee Board is always "active"
    activate TB

    %% == Phase 1: Private and Pairwise Share Generation ==
    activate T1
    T1->>T1: Generate private share x1
    T1->>T1: Calculate public check values cv1_1 .. cv1_n
    T1->>T1: Calculate pairwise shares ps1_1 .. ps1_n
    T1->>TB: Post pairwise shares and public check values
    deactivate T1

    activate T2
    T2->>T2: Generate private share x2
    T2->>T2: Calculate public check values cv2_1 .. cv2_n
    T2->>T2: Calculate pairwise shares ps2_1 .. ps2_n
    T2->>TB: Post pairwise shares and public check values
    deactivate T2

    Note over T2, Tn: Steps repeated for T3 .. Tn-1

    activate Tn
    Tn->>Tn: Generate private share xn
    Tn->>Tn: Calculate public check values cvn_1 .. cvn_n
    Tn->>Tn: Calculate pairwise shares psn_1 .. psn_n
    Tn->>TB: Post pairwise shares and public check values
    deactivate Tn

    %% == Phase 2: Election Public Key Generation ==
    Note over TB: All shares and check values are mirrored to the trustees' local boards
    TB->>T1: All shares and check values
    activate T1 # Activate T1 when it has all shares and check values
    TB->>T2: All shares and check values
    activate T2 # Activate T2 when it has all shares and check values

    Note over TB, Tn: Mirroring also occurs for T3 .. Tn-1

    TB->>Tn: All shares and check values
    activate Tn # Activate Tn when it has all shares and check values

    %% T1 processes
    T1->>T1: Verify check values cv*_1 against pairwise shares ps*_1
    Note right of T2: On failure: abort protocol
    T1->>T1: Calculate election public key from check values
    T1->>T1: Securely store private share x1, all public check values,<br/>and all pairwise shares ps*_1 on Trustee Storage<br/>(e.g., encrypted USB)
    T1->>TB: Post calculated election public key
    %% T1 awaits posting of all generated election public keys

    %% T2 processes
    T2->>T2: Verify check values cv*_2 against pairwise shares ps*_2
    Note right of T2: On failure: abort protocol
    T2->>T2: Calculate election public key from check values
    T2->>T2: Securely store private share x2, all public check values,<br/>and all pairwise shares ps*_2 on Trustee Storage<br/>(e.g., encrypted USB)
    T2->>TB: Post calculated election public key
    %% T2 awaits posting of all generated election public keys

    Note over T2, Tn: Steps repeated for T3 .. Tn-1

    %% Tn processes
    Tn->>Tn: Verify check values cv*_n against pairwise shares ps*_n
    Note right of Tn: On failure: abort protocol
    Tn->>Tn: Calculate election public key from check values
    Tn->>Tn: Securely store private share xn, all public check values,<br/>and all pairwise shares ps*_n on Trustee Storage<br/>(e.g., encrypted USB)
    Tn->>TB: Post calculated election public key
    %% Tn awaits posting of all generated election public keys

    %% == Phase 4: Final Key Confirmation (within Air-Gap) ==

    Note over TB: All calculated public keys are mirrored to the trustees' local boards
    TB-->>T1: All calculated public keys
    activate T1 # Activate T1 when it has all calculated public keys
    TB-->>T2: All calculated public keys
    activate T2 # Activate T2 when it has all calculated public keys

    Note over TB, Tn: Mirroring also occurs for T3 .. Tn-1

    activate TAS # Activate TAS to receive final key confirmations
    TB-->>TAS: All calculated public keys

    TB-->>Tn: All calculated public keys
    activate Tn # Activate Tn when it has all calculated public keys

    T1->>T1: Check that all calculated public keys are identical
    Note right of T1: On failure: abort protocol

    T2->>T2: Check that all calculated public keys are identical
    Note right of T2: On failure: abort protocol

    Tn->>Tn: Check that all calculated public keys are identical
    Note right of Tn: On failure: abort protocol

    TAS->>TAS: Check that all calculated public keys are identical
    Note right of TAS: On failure: abort protocol

    deactivate T1 # T1 processing complete for DKG

    deactivate T2 # T2 processing complete for DKG

    deactivate Tn # Tn processing complete for DKG

    deactivate TB
    deactivate TAS

    Note over T1, Tn: All trustees computed the same election public key y.<br/>Each Trustee Ti has stored their private share xi, their pairwise shares ps*_i, and all public check values locally on secure Trustee Storage

    Note over TAS: TAS now holds the computed election public key y,<br/>ready for secure export from the air-gap<br/>(via Election Administrator Storage)
```
