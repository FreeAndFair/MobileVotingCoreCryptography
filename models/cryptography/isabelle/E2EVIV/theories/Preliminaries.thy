(******************************************************************************)
(* @title Isabelle/HOL Theories for E2E-VIV Cryptography                      *)
(* @description Theory "Preliminaries" including preliminary concepts         *)
(* @author Frank Zeyda                                                        *)
(* @copyright Free & Fair 2025                                                *)
(* @license TODO                                                              *)
(******************************************************************************)

section \<open>Preliminaries\<close>

theory Preliminaries
imports Main "HOL-Algebra.Elementary_Groups"
begin

subsection \<open>Group Generator\<close>

context group
begin
\<comment> \<open>We introduce a generator via Hilbert's epsilon.\<close>
definition g :: "'a" where
"g = (SOME x. subgroup_generated G {x} = G)"
end

end

text \<open>\clearpage\<close>
