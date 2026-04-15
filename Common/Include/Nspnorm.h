/*M*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1995 Intel Corporation. All Rights Reserved.
//
//  RCS:
//      $Source: $
//      $Revision: $
//      $Date: $
//
//  Purpose: 
*M*/

/*=== Definitions =========================================================*/

#if !defined (_NSPNORM_H) || defined (_OWN_BLDPCS)
# define _NSPNORM_H

#define NSP_C         0x01
#define NSP_L1        0x02
#define NSP_L2        0x04
#define NSP_RELATIVE  0x08

/*
// Functions: nsp?Norm
//  Compute the C, L1 or L2 norm of the input vectors’ difference ||a-b||
//  or of one vector ||a||.
//  Vector x[n]' norm definitions:
//  C  norm: ||x[n]|| = MAX(|x[i]|)
//  L1 norm: ||x[n]|| = SUMM(|x[i]|)
//  L2 norm: ||x[n]|| = SQRT( SUMM(x[i]*x[i]) )
//      
// Parameters:
//  srcA    - pointer to the first input vector a[n], must not be NULL.
//  srcB    - pointer to the second input vector b[n].
//  n       - the number of elements in the input vectors.
//  flag    - specifies the norm type and the relative mode.
//          Possible values:
//          NSP_C  - C  norm,
//          NSP_L1 - L1 norm,
//          NSP_L2 - L2 norm,
//          NSP_C |NSP_RELATIVE - C  norm and relative mode,
//          NSP_L1|NSP_RELATIVE - L1 norm and relative mode,
//          NSP_L2|NSP_RELATIVE - L2 norm and relative mode.
//
//  Returned value:
//          ||a-b||       if srcB != NULL && !(flag & NSP_RELATIVE)
//          ||a||         if srcB == NULL && !(flag & NSP_RELATIVE)
//          ||a-b||/||a|| if srcB != NULL && flag & NSP_RELATIVE
//          1             if srcB == NULL && flag & NSP_RELATIVE
*/

NSPAPI(float,  nspsNorm,(const float *srcA,  const float *srcB,  int n, 
                         int flag))
NSPAPI(float,  nspcNorm,(const SCplx *srcA,  const SCplx *srcB,  int n, 
                         int flag))
NSPAPI(double, nspdNorm,(const double *srcA, const double *srcB, int n, 
                         int flag))
NSPAPI(double, nspzNorm,(const DCplx  *srcA, const DCplx  *srcB, int n, 
                         int flag))
NSPAPI(float,  nspwNorm,(const short *srcA,  const short *srcB,  int n, 
                         int flag))
NSPAPI(float,  nspvNorm,(const WCplx *srcA,  const WCplx *srcB,  int n, 
                         int flag))

/*
// Functions: nspwNormExt, nspvNormExt
//  Compute the C, L1 or L2 norm of the input vectors’ difference ||a-b||
//  or of one vector ||a|| as nsp?Norm functions
//  and scales the float result to int result according to scale mode and 
//  scale factor.
//      
// Parameters:
//  srcA    pointer to the first input vector a[n], must not be NULL.
//  srcB    pointer to the second input vector b[n].
//  n       the number of elements in the input vectors.
//  flag    specifies the norm type and the relative mode.
//          Possible values:
//          NSP_C  - C  norm,
//          NSP_L1 - L1 norm,
//          NSP_L2 - L2 norm,
//          NSP_C |NSP_RELATIVE - C  norm and relative mode,
//          NSP_L1|NSP_RELATIVE - L1 norm and relative mode,
//          NSP_L2|NSP_RELATIVE - L2 norm and relative mode.
//  scaleMode    scale mode for returned value. 
//               Below VALUE is float, non-negative result of nsp?Norm.
//               scale(VALUE) will be compute according to scaleMode:
//          NSP_NO_SCALE              - scale(VALUE) = (int)(VALUE+0.5)
//          NSP_NO_SCALE|NSP_SATURATE - scale(VALUE) = VALUE+0.5 >= INT_MAX ? 
//                                                     INT_MAX :
//                                                     (int)(VALUE+0.5)
//          NSP_FIXED_SCALE              - scale(VALUE) = 
//                                         (int)(VALUE/(1<<*scaleFactor))
//          NSP_FIXED_SCALE|NSP_SATURATE - scale(VALUE) = 
//                                         (VALUE/(1<<*scaleFactor) >= INT_MAX ?
//                                         INT_MAX :
//                                         (int)(VALUE/(1<<*scaleFactor))
//          NSP_AUTO_SCALE - scale(VALUE) = (int)(VALUE/(1<<*scaleFactor)) where
//                           VALUE/(1<<*scaleFactor) < INT_MAX
//  scaleFactor  pointer to scale factor for returned value (see above)
//
//  Returned value:
//          scale(||a-b||)       if srcB != NULL && !(flag & NSP_RELATIVE)
//          scale(||a||)         if srcB == NULL && !(flag & NSP_RELATIVE)
//          scale(||a-b||/||a||) if srcB != NULL && flag & NSP_RELATIVE
//          1                    if srcB == NULL && flag & NSP_RELATIVE
*/

NSPAPI(int,  nspwNormExt,(const short *srcA,  const short *srcB,  int n, 
                          int flag, int scaleMode, int *scaleFactor)) 
NSPAPI(int,  nspvNormExt,(const WCplx *srcA,  const WCplx *srcB,  int n,
                          int flag, int scaleMode, int *scaleFactor)) 


/*
// Function: nsp?bNormalize().
//  Subtract the offset constant from the elements of the input vector a[n]
//  and divides the result by factor.
//  Output vector b[n] has the elements:
//      b[i] = ( a[i] - offset) / factor.
//
// Parameters:
//  src     pointer to the input vector a[n].
//  dst     pointer to the output vector b[n].
//  n       the number of elements in the input and output vectors.
//  offset  offset for each element a[i]
//  factor  factor for each element a[i]
*/

NSPAPI(void, nspsbNormalize,(const float *src,  float *dst,  int n,
                             float  offset, float factor))
NSPAPI(void, nspcbNormalize,(const SCplx *src,  SCplx *dst,  int n,
                             SCplx  offset, float factor))
NSPAPI(void, nspdbNormalize,(const double *src, double *dst, int n,
                             double offset, double factor))
NSPAPI(void, nspzbNormalize,(const DCplx  *src, DCplx  *dst, int n,
                             DCplx  offset, double factor))
NSPAPI(void, nspwbNormalize,(const short *src,  short *dst,  int n, 
                             short  offset, float factor))
NSPAPI(void, nspvbNormalize,(const WCplx *src,  WCplx *dst,  int n, 
                             WCplx  offset, float factor))

#endif
