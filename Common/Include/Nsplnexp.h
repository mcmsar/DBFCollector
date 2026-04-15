/*M*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1995 Intel Corporation. All Rights Reserved.
//
//  PVCS: 
//      $Workfile:   NSPLNEXP.H  $
//      $Revision:   1.0  $
//      $Date:   Dec 16 1996 18:31:28  $
//      $Archive:   X:/nsp40_arc/INCLUDE/NSPLNEXP.H_v  $
//
//  Purpose : Compute the natural log of vector elements
//            Compute e to the power of vector elements
//
//  Contents:
//           nsp?bLn1   -
//                      Computes the natural log of each element
//                      in the array in-place
//           nsp?bLn2   -
//                      Computes the natural log of each element
//                      in the array and stores the results
//                      in the another array
//           nsp?bExp1  -
//                      Computes e to the power of each element
//                      in the array in-place
//           nsp?bExp2  -
//                      Computes e to the power of each element
//                      in the array and stores the results
//                      in the another array
//
*M*/

#if !defined (_NSPLNEXP_H) || (defined _OWN_BLDPCS)
# define _NSPLNEXP_H

NSPAPI(void, nspsbLn1, (                   float  *vec, int len))
NSPAPI(void, nspsbLn2, (const float  *src, float  *dst, int len))
NSPAPI(void, nspsbExp1,(                   float  *vec, int len))
NSPAPI(void, nspsbExp2,(const float  *src, float  *dst, int len))

NSPAPI(void, nspdbLn1, (                   double *vec, int len))
NSPAPI(void, nspdbLn2, (const double *src, double *dst, int len))
NSPAPI(void, nspdbExp1,(                   double *vec, int len))
NSPAPI(void, nspdbExp2,(const double *src, double *dst, int len))

NSPAPI(void, nspwbLn1, (                   short  *vec, int len))
NSPAPI(void, nspwbLn2, (const short  *src, short  *dst, int len))
NSPAPI(void, nspwbExp1,(                   short  *vec, int len,
                                           int scaleMode, int *scaleFactor))
NSPAPI(void, nspwbExp2,(const short  *src, short  *dst, int len,
                                           int scaleMode, int *scaleFactor))
#endif                                  /* _NSPLNEXP_H                     */
