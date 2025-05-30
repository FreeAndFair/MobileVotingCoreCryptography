/*
 * Extensions for Prime Field Elliptic Curves (PFEC)
 *
 * @note This file is included by PFEC.cry to localize
 * all E2EVIV extension to the cryptol-spec PFEC module
 * in a designated place. We may integrate the content
 * of this file upstream into the PFEC.cry which is
 * part of cryptol-specs, including imported functions
 * from Algebra::Utils.
 *
 * @author Frank Zeyda (frank.zeyda@freeandfair.us)
 * @copyright Free & Fair 2025
 * @version 0.1
 */

import Algebra::Utils(lg2floor, bv2Z, Z2bv, sqrtZ, isQuadraticResidue)

/**
 * Extracts the y-coordinate `Z P` value, if the point is not
 * the point at infinity.
 */
yCoord: Point -> Option (Z P)
yCoord p = case p of
    Infinity   -> None
    Affine _ y -> Some y

/**
 * Finds a curve point, starting from a given x coordinate.
 *
 * The point (x, y) must satisfy the (short) Weierstrass equation
 * `x^3 - 3x + b = y^2` since a is always -3 in PFEC.cry curves.
 */
findPoint : Z P -> Point
findPoint x = if isQuadraticResidue lhs then Affine x (sqrtZ lhs)
                                        else findPoint (x + 1)
  where lhs = x^^3 - 3*x + b

/**
 * Property to check that `findPoint` returns a valid curve point.
 *
 * The `findPoint` function that is verified is defined above.
 */
property findPoint_isValid (x : Z P) = isValid (findPoint x)

/**
 * Encodes a bit string into a valid curve point.
 *
 * The approach is based on one of the methods (Sect. 3, (2))
 * suggested by Neil Koblitz in Elliptic Curve Cryptosystems,
 * @see https://doi.org/10.1090/S0025-5718-1987-0866109-5
 * The type parameter `fixed` determines the bit-string length
 * and the type parameter `twiddle` the number of twiddle bits
 * to permute in order to find a valid curve point for `bv`.
 *
 * @note With a sufficiently large `twiddle`, the probability
 * that this function fails becomes negligible: 2^(-(2^twiddle)).
 *
 * @note Using `lg2floor P` instead of `lg2 P` is crucial to
 * avoid certain pathological situation where bit strings that
 * exceed P cannot be encoded.
 */
encBits : {fixed, twiddle} (fixed + twiddle == lg2floor P) => [fixed] -> Point
encBits bv =
  if bv == bv'dec then p
  else error "failed to find a suitable curve point"
  where bv'ext = bv # (zero : [twiddle])
        p = findPoint (bv2Z bv'ext)
        bv'dec = decPoint p

/**
 * Decodes a curve point (not infinity) into a bit string.
 *
 * The type parameter `fixed` determines the bit-string length
 * and the type parameter `twiddle` the number of twiddle bits
 * to discard when decoding the x coordinate into a bit string.
 *
 * @note Using `lg2floor P` instead of `lg2 P` is crucial to
 * avoid certain pathological situation where bit strings that
 * exceed P cannot be encoded.
 */
decPoint : {fixed, twiddle} (fixed + twiddle == lg2floor P) => Point -> [fixed]
decPoint p = take`{front = fixed, back = twiddle} (Z2bv x)
  where x = case xCoord p of
    Some v -> v
    None   -> error "cannot decode point at infinity"

/**
 * Property to check that `decPoint` is the inverse of `encBits`.
 *
 * @note Since numeric type `bits` can be freely chosen, it is
 * important to choose `type k = (lg2 P) - bits` large enough so
 * that the probability for failing to encode a bit string into
 * the curve becomes negligible, being estimated by 2^(-(2^k)).
 */
encBits_decPoint_inverse : {bits} (bits <= lg2floor P) => [bits] -> Bool
property encBits_decPoint_inverse (bv : [bits]) =
  decPoint (encBits bv) == bv

/*
 * Checks that `encBits_decPoint_inv` holds for boundary values.
 */
encBits_decPoint_testcases : {bits} (bits >= 2, bits <= lg2floor P) => Bool
property encBits_decPoint_testcases =
  all encBits_decPoint_inverse`{bits} [-2, -1, 0, 1, 2]
