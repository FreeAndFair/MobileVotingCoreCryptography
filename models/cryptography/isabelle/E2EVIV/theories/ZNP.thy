(******************************************************************************)
(* @title Isabelle/HOL Theories for E2E-VIV Cryptography                      *)
(* @description Theory "ZNP" verifying Zero Knowledge Proof Protocols         *)
(* @author Frank Zeyda                                                        *)
(* @copyright Free & Fair 2025                                                *)
(* @license TODO                                                              *)
(******************************************************************************)

section \<open>Zero Knowledge Proofs of Knowledge in Groups\<close>

theory ZNP
imports Preliminaries
begin

subsection \<open>Schnorr's Protocol Completeness Proof\<close>

text \<open>
We restate Schnorr's original protocol, but over any product group
$\Group$ and associated ring of exponents $\Rexps{\Group}$.

\begin{protocol}[Knowledge of Discrete Logarithm]
Schnorr's protocol executed over a product group $\Group$ on common
input $(\g,\y)\in\Group\times\Group$ and private input
$\x\in\Rexps{\Group}$ such that $\y=\g^{\x}$ proceeds as follows:

\begin{evsenumerate}
  \item $\PP$ chooses $\aaa\in\Rexps{\Group}$ randomly, computes
    $\AAA=\g^{\aaa}$, and hands $\AAA$ to $\PV$.

  \item $\PV$ chooses $\vv\in\BINT{\secpv}$ randomly and hands $\vv$
    to $\PP$.

  \item $\PP$ computes $\kk=\vv\x+\aaa$ and hands $\kk$ to $\PV$.

  \item $\PV$ outputs $1$ or $0$ depending on if $\y^{\vv}\AAA=\g^{\kk}$
    or not.
\end{evsenumerate}
\end{protocol}

We stress that $\g$ is not necessarily the standard generator of $\Group$.
In fact, it may not be a generator of $\Group$ at all. The distinctness
matroid $\matdist{\secpv}$ with ground set $\BINT{\secpv}$ represents the
need of finding two accepting transcripts with different challenges.
\<close>

text \<open>
  Below is a proof of completeness for Schnorr's protocol, showing that
  the equality in step (4) always holds, providing that both the prover
  and the verifier act honestly.
\<close>

(* declare [[show_types]] *)
(* declare [[show_sorts]] *)

context group
begin
lemma Schnorr_complete:
fixes g :: "'a" \<comment> \<open>element of group G\<close>
fixes y :: "'a" \<comment> \<open>element of group G\<close>
fixes x :: "nat" \<comment> \<open>element of exponent ring\<close>
fixes a :: "nat" \<comment> \<open>element of exponent ring\<close>
fixes v :: "nat" \<comment> \<open>element of exponent ring\<close>
assumes "cyclic_group G"
assumes "finite (carrier G)"
assumes "g \<in> carrier G"
assumes "y \<in> carrier G" \<comment> \<open>actually redundant\<close>
assumes "y = g [^] x"
shows "
  let A = g [^] a in
  let k = v*x + a in
    (y [^] v) \<otimes> A = g [^] k"
apply (simp add: assms)
proof -
  have "(g [^] x) [^] v \<otimes> g [^] a = g [^] (x * v) \<otimes> g [^] a"
    using assms(3) nat_pow_pow by (force)
  also have "... = g [^] (v * x) \<otimes> g [^] a"
    by (simp add: mult.commute)
  also have "... = g [^] (v * x + a)"
    using assms(3) nat_pow_mult by (force)
  finally show "(g [^] x) [^] v \<otimes> g [^] a = g [^] (v * x + a)" .
qed
end

text \<open>
  The proof is conducted within the \<^locale>\<open>group\<close> locale defined
  inside the \<^theory>\<open>HOL-Algebra.Group\<close> theory, which is part of the
  \<^session>\<open>HOL-Algebra\<close> library. It provides a notion of an algebraic
  group over a carrier set, including a predicate \<^const>\<open>cyclic_group\<close>
  that enables us to restrict the group notion to a cyclic group.
  \medskip

  The proof can be done in a completely automatic fashion. Nonetheless,
  we used the ISAR proof language for maintainability, and to serve as
  a better didactic example.
  \medskip

  Important to note here is that we use the type \<^typ>\<open>nat\<close> of natural
  numbers for the exponent ring. The proof can presumably be made more
  general, using some arbitrary type with the right sort constraint
  for the exponent ring, but this requires additional mechanization
  effort since exponentiation is currently only defined for natural
  numbers and integers in Isabelle/HOL (a failed proof attempt is
  included as a comment in the Isabelle source of theory \<open>ZNP\<close> using
  some arbitrary type \<open>'c::semiring_1\<close> for the exponent ring).
\<close>
(*
\<comment> \<open>The following proof using a generic exponent ring fails.\<close>

lemma (in group) Schnorr_complete:
fixes g :: "'a" \<comment> \<open>element of group G\<close>
fixes y :: "'a" \<comment> \<open>element of group G\<close>
fixes x :: "'c::semiring_1" \<comment> \<open>element of exponent ring\<close>
fixes a :: "'c::semiring_1" \<comment> \<open>element of exponent ring\<close>
fixes v :: "'c::semiring_1" \<comment> \<open>element of exponent ring\<close>
assumes "cyclic_group G"
assumes "finite (carrier G)"
assumes "g \<in> carrier G"
assumes "y \<in> carrier G" (* actually redundant *)
assumes "y = g [^] x"
shows "
  let A = g [^] a in
  let k = v*x + a in
    (y [^] v) \<otimes> A = g [^] k"
apply (simp add: assms)
proof -
  have "(g [^] x) [^] v \<otimes> g [^] a = g [^] (x * v) \<otimes> g [^] a"
    using assms(3) nat_pow_pow by (force)
  also have "... = g [^] (v * x) \<otimes> g [^] a"
    by (simp add: mult.commute)
  also have "... = g [^] (v * x + a)"
    using assms(3) nat_pow_mult by (force)
  finally show "(g [^] x) [^] v \<otimes> g [^] a = g [^] (v * x + a)" .
oops
*)
end

text \<open>\clearpage\<close>
