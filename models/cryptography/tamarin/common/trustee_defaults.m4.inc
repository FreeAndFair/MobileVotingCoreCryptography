dnl
dnl This input file contains Tamarin macros for the trustee count
dnl trustee threshold, and valid subsequences of private shares
dnl that can be used for decryption.
dnl
dnl @author Daniel M. Zimmerman
dnl @copyright Free & Fair 2025
dnl @version 0.1
dnl
dnl We set the number of trustees to 3 and the threshold to 2, if
dnl they are not set already. Note that VALID_TRUSTEE_SUBSEQUENCES
dnl must be defined (in exactly this form) in order for the equational
dnl theory for threshold cryptography to be rendered properly.
dnl
dnl We could probably compute the subsequences ourselves using a lot of
dnl convoluted m4 macros, but that's a project for a later time.
dnl
ifdef(<!TRUSTEE_COUNT!>, <!!>, <!define(TRUSTEE_COUNT, <!3!>)!>)dnl
ifdef(<!TRUSTEE_THRESHOLD!>, <!!>, <!define(TRUSTEE_THRESHOLD, <!2!>)!>)dnl
ifdef(<!VALID_TRUSTEE_SUBSEQUENCES!>, <!!>,
   <!define(VALID_TRUSTEE_SUBSEQUENCES, <!((1, |, 2), (1, |, 3), (2, |, 3))!>)!>)dnl
