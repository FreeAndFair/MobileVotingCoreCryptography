dnl
dnl This is the m4 input file for the Trustee Decryption Subprotocol.
dnl If the STANDALONE macro is defined, this file generates a standalone
dnl version of the subprotocol; otherwise, it generates a Tamarin code
dnl snippet suitable for inclusion in a Tamarin file composing multiple
dnl subprotocols.
dnl
dnl If the TRUSTEE_DECRYPTION_MOCKS macro is defined (which is always the
dnl case when STANDALONE is defined), the Tamarin code snippet will include
dnl mock rules that simulate required actions of other subprotocols by
dnl establishing suitable linear/persistent/action facts.
dnl
dnl @author Daniel M. Zimmerman
dnl @copyright Free & Fair 2025
dnl @version 0.1
dnl
dnl We change the m4 quote characters to <! and !>, so that they don't
dnl interfere with Tamarin's quote characters or any comments we might
dnl want to write. The incantation below makes that change, and ensures
dnl that we don't try to change them if we've already done so (e.g.,
dnl when including this file in a composition).
dnl
ifdef(<!QUOTE_CHANGED!>,<!!>,<!changequote(`<!', `!>')!>)dnl
dnl
ifdef(<!STANDALONE!>,<!/*
  Trustee Decryption Subprotocol

  Explanation goes here.

  @author Daniel M. Zimmerman
  @copyright Free & Fair 2025
  @version 0.1
 */

theory trustee_decryption

begin

#include "../common/primitives.spthy.inc"
!>)dnl
dnl If STANDALONE is defined, all mocks are always required
ifdef(<!STANDALONE!>,<!define(TRUSTEE_DECRYPTION_MOCKS)!>)dnl
dnl
ifdef(<!TRUSTEE_DECRYPTION_MOCKS!>,<!
/*
  Mocks necessary for running the trustee decryption subprotocol without other
  subprotocols go here. There may end up being multiple such blocks controlled
  by different macro definitions, depending on what subprotocol combinations
  need to be generated and what needs to be mocked for each combination.
*/

!>)dnl
dnl
/* Rules for trustee decryption subprotocol go here. */

/*
  This rule is just to allow CI to pass until we put in real executability
  lemmas. It establishes a single fact, and that's about it.
 */
rule TrusteeDecryption_Temporary:
  [] --[ TrusteeDecryption_Executed() ]-> []

/*
  Lemmas for trustee decryption subprotocol go here.

  Executability lemmas must start with "Executability" in order to be
  automatically checked in CV.
 */

/*
  This lemma is just to allow CV to pass until we put in real
  executability lemmas.
 */
lemma Executability_TrusteeDecryption:
  exists-trace
  "
    ∃ #t. TrusteeDecryption_Executed()@t
  "
dnl
ifdef(<!STANDALONE!>,<!
end
!>)dnl
