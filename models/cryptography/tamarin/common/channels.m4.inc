dnl
dnl Tamarin channel rules shared by multiple subprotocols.
dnl
dnl @author Daniel M. Zimmerman
dnl @copyright Free & Fair 2025
dnl @version 0.1
dnl
ifdef(<!defined_bool!>, <!!>, <!include(m4_utils/defined_bool.m4)!>)dnl
ifelse(eval(!defined_bool(<!INCLUDED_AUTHENTICATED_CHANNELS!>) && defined_bool(<!USE_AUTHENTICATED_CHANNELS!>)), eval(1), <!
define(<!INCLUDED_AUTHENTICATED_CHANNELS!>)dnl
/*
  An authenticated channel, where messages are guaranteed to be from
  the claimed sender but are not encrypted and can be received by
  multiple arbitrary recipients (including the adversary).

  Usage: Instead of `Out(m)` and `In(m)` facts, use
  `AuthenticatedSend(S, R, m)` and `AuthenticatedReceive(S, R, m)`,
  where `S` is the sender, `R` is the intended receiver, and `m` is
  the message.

  Note: The `!AuthenticMessage` fact should never be used outside these
  two rules.
*/

rule AuthenticatedChannel_Send:
    [ AuthenticatedSend(S, R, m) ]
  --[ AuthenticatedChannel_Out(S, R, m) ]->
    [ !AuthenticatedMessage(S, m), Out(m) ]

rule AuthenticatedChannel_Receive:
    [ !AuthenticatedMessage(S, m), In(R) ]
  --[ AuthenticatedChannel_In(S, R, m) ]->
    [ AuthenticatedReceive(S, R, m) ]
!>, <!!>)dnl
dnl
ifelse(eval(!defined_bool(<!INCLUDED_CONFIDENTIAL_CHANNELS!>) && defined_bool(<!USE_CONFIDENTIAL_CHANNELS!>)), eval(1), <!
define(<!INCLUDED_CONFIDENTIAL_CHANNELS!>)dnl
/*
  A confidential channel, where messages are guaranteed to be received
  only by the claimed recipient, but not to be sent by the claimed
  sender (the adversary can change the claimed sender, but does not get
  access to and cannot change the message contents).

  Usage: Instead of `Out(m)` and `In(m)` facts, use
  `ConfidentialSend(S, R, m)` and `ConfidentialReceive(S, R, m)`,
  where `S` is the sender, `R` is the intended receiver, and `m` is
  the message.

  Note: The `!ConfidentialMessage` fact should never be used outside these
  two rules.
*/

rule ConfidentialChannel_Send:
    [ ConfidentialSend(S, R, m) ]
  --[ ConfidentialChannel_Out(S, R, m) ]->
    [ !ConfidentialMessage(R, m) ]

rule ConfidentialChannel_Receive:
    [ !ConfidentialMessage(R, m), In(S) ]
  --[ ConfidentialChannel_In(S, R, m) ]->
    [ ConfidentialReceive(S, R, m) ]
!>, <!!>)dnl
dnl
ifelse(eval(!defined_bool(<!INCLUDED_SECURE_CHANNELS!>) && defined_bool(<!USE_SECURE_CHANNELS!>)), eval(1), <!
define(<!INCLUDED_SECURE_CHANNELS!>)dnl
/*
  A secure channel, where messages are guaranteed to be from the
  claimed sender and to only be received by the claimed recipient
  No other recipient (including the adversary) can learn the message
  contents from the channel; however, the message can be replayed
  (because the `!SecureMessage` fact is persistent).

  Usage: Instead of `Out(m)` and `In(m)` facts, use
  `SecureSend(S, R, m)` and `SecureReceive(S, R, m)`, where `S`
  is the sender, `R` is the receiver, and `m` is the message.

  Note: The `!SecureMessage` fact should never be used outside these
  two rules.
 */

rule SecureChannel_Send:
    [ SecureSend(S, R, m) ]
  --[ SecureChannel_Out(S, R, m) ]->
    [ !SecureMessage(S, R, m) ]

rule SecureChannel_Receive:
    [ !SecureMessage(S, R, m) ]
  --[ SecureChannel_In(S, R, m) ]->
    [ SecureReceive(S, R, m) ]
!>, <!!>)dnl
