# Relevant Isabelle/HOL Theories and Libraries

This markdown document includes a brief overview of relevant [Isabelle/HOL](https://isabelle.in.tum.de/) libraries and resources for specification and verification of cryptographic functions and algorithms. Both, in view of _functional correctness_ and _security properties_.

Since (extended) use of Isabelle is out of scope of the E2E-VIV Cryptography project, we keep the list fairly short, with just a few pointers that may be followed up in the future, should we decide at some instance to further go down the route of taking advantage if the Isabelle proof system and existing libraries.

## Standard Isabelle/HOL Libraries

Within the Standard Isabelle/HOL library, the following sessions appear to be most useful:
- [HOL-Algebra](https://github.com/isabelle-prover/mirror-isabelle/tree/master/src/HOL/Algebra)
- [HOL-Computational_Algebra](https://github.com/isabelle-prover/mirror-isabelle/tree/master/src/HOL/Computational_Algebra)
- [HOL-Number_Theory](https://github.com/isabelle-prover/mirror-isabelle/tree/master/src/HOL/Number_Theory)
- [HOL-Analysis](https://github.com/isabelle-prover/mirror-isabelle/tree/master/src/HOL/Analysis)
- [HOL-Complex_Analysis](https://github.com/isabelle-prover/mirror-isabelle/tree/master/src/HOL/Complex_Analysis)
- [HOL-Probability](https://github.com/isabelle-prover/mirror-isabelle/tree/master/src/HOL/Probability)

## Archive of Formal Proofs

Isabelle Archive of Formal Proofs ([AFP](https://www.isa-afp.org/)) has a couple of section that may be relevant for protocol specification and verification:
- Security: https://www.isa-afp.org/topics/computer-science/security/
- Cryptography: https://www.isa-afp.org/topics/computer-science/security/cryptography/
- Probability Theories: https://www.isa-afp.org/topics/mathematics/probability-theory/
- CryptHOL: https://www.isa-afp.org/entries/CryptHOL.html

In particular, [CryptHOL](https://www.isa-afp.org/entries/CryptHOL.html) provides a general framework to reason about security aspects of cryptographic functions, via probability distributions. The underlying strategy is based on game-hopping proofs, see the following tutorial introduction https://eprint.iacr.org/2018/941.pdf and Springer _Journal of Cryptography_ paper https://link.springer.com/article/10.1007/s00145-019-09341-z.

## CryptHOL in a Nutshell

Below is a summary of a few additional notes by [Frank Zeyda](mailto:frank.zeyda@freeandfair.us?subject=Re%3A%20Notes%20on%20CryltHOL) on CryptHOL, after reading the paper: [CryptHOL: Game-based Proofs in Higher-order Logic](https://eprint.iacr.org/2017/753.pdf)

The centerpiece of the work is a monad that captures functions with
probabilistic outcomes. More precisely, is uses a notion of discrete
**subprobability distribution** over outcomes. This concept permits
one to model probabilities of events which do not have to sum to one
(but instead, possibly less), describing abortive behavior of computations. (This notion as also used in McIver and Morgan's [Abstraction, Refinement and Proof for Probabilistic Systems](https://link.springer.com/book/10.1007/b138392), and goes back to [Feldman and Harel](https://www.sciencedirect.com/science/article/pii/0022000084900655/pdf?md5=b28f481188df3f14697578cb82c1c8e7&pid=1-s2.0-0022000084900655-main.pdf).)

Based on this monad, the authors specify games that capture security properties of protocols, such as [ciphertext indistinguishability](https://en.wikipedia.org/wiki/Ciphertext_indistinguishability) of encryption schemes and more. The reasoning is effectively about the distributions encapsulated by those monadic computations in a suitable formalization of a game involving the advisory.

They support different strategies of mechanized reasoning:
- Equational Reasoning
- Relational Reasoning
- Reasoning via the Semantics
and take advantage of Isabelle's facilities for generic theory and proof engineering, i.e., via [locales](https://isabelle.in.tum.de/doc/locales.pdf).

The library looks fairly comprehensive, but I am not sure how it compares to [EasyCrypt](https://www.easycrypt.info/) (which also supports game-based cryptographic proofs) in terms of capability and completeness.

(**@todo fzeyda**: compare both systems and possibly others if we
decide to revisit proofs of security properties via
[EasyCrypt](https://github.com/EasyCrypt/easycrypt) or
[CryptHOL](https://www.isa-afp.org/entries/CryptHOL.html) in the
future.)

(**@review kiniry**: We can directly talk with Gilles Barthe about the
strengths and weaknesses of EasyCrypt compared to other approaches, as
well as his personal experience attempting to formalize STAR-Vote.)

Here is a summary of what the authors say in various places in their paper [CryptHOL: Game-based Proofs in Higher-order Logic](https://eprint.iacr.org/2017/753.pdf):
- _In summary, guided by parametricity, we have essentially rediscovered the functional counterpart to probabilistic relational Hoare logic as implemented in EasyCrypt._
- _In comparison to EasyCrypt, the state of the art in proof automation, we achieve a similar degree of automation when reasoning about programs. The RP-RF switching lemma involves considerable reasoning about probabilities rather than programs.12 Here, the CryptHOL proof is much shorter than EasyCrypt’s because in CryptHOL we can leverage the richer Isabelle/HOL library and generic proof automation._
- _[CertiCrypt](https://github.com/EasyCrypt/certicrypt) and [EasyCrypt](https://github.com/EasyCrypt/easycrypt) support discrete subprobability distributions expressed using a probabilistic while language. CryptHOL has the same semantic domain and the language is equally expressive, thanks to the fixpoint operator._
- _For EasyCrypt, we are aware of neither a consistency proof for its underlying logic, in particular for the module system, nor of a derivation of its probabilistic relational Hoare logic._

So, at a glance I presume CryptHOL and EasyCrypt share quite a few similarities.

## Additional Notes of Joe Kiniry

FWIW, most folks who wish to formalize cryptographic protocols in an LF started life in Coq (I was partly responsible for getting [Gilles Barthe](https://www.mpi-sp.org/barthe) and others at INRIA interested in this topic) and the pain entailed in that R&D is what lead to the creation of [EasyCrypt](https://github.com/EasyCrypt/easycrypt). Also, don't forget about the utility of frameworks like Adam's [FCF](https://github.com/adampetcher/fcf) (**F**oundational **C**ryptography **F**ramework for machine-checked proofs of cryptography). There is a reason that people have earned whole PhDs by virtue of working in this area.

Here is an excellent book that lays out the foundation of this area:
[Barthe et al., *_Foundations of Probablistic
Programming_*](https://www.amazon.com/Foundations-Probabilistic-Programming-Gilles-Barthe/dp/110848851X).
I have setup a meeting to discuss the intersection between
Probablistic Programming Languages (PPLs) and pure cryptography with a
local expert at Galois in March, 2025.
