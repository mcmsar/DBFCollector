/*M*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1995 Intel Corporation. All Rights Reserved.
//
//  PVCS: 
//      $Workfile: Nspcorr.h $
//      $Revision: 1 $
//      $Date: 17/07/97 12:37 $
//      $Archive: /corr/Nspcorr.h $
//
//  Purpose: NSP Correlation
*M*/

#if !defined (_NSPCORR_H) || defined (_OWN_BLDPCS)
# define _NSPCORR_H

/* ------------------------------------------------------------------------*/

#if !defined (_OWN_BLDPCS)

typedef enum _NSPAutoCorrType 
   {NSP_Normal, NSP_Biased, NSP_UnBiased} NSPAutoCorrType;

#endif

/* ------------------------------------------------------------------------*/
/*        AutoCorrelation                                                  */
/*                                                                         */
/*
  Normal:
  ~~~~~~~
  dst[n] = S ~src[k] * src[k+n],  0 <= n < nLags
                                  0 <= k < len

  Biased:
  ~~~~~~~
  dst[n] = K* S ~src[k] * src[k+n],  0 <= n < nLags
                                     0 <= k < len
                                     K = 1/len
  UnBiased:
  ~~~~~~~~~
  dst[n] = K* S ~src[k] * src[k+n],  0 <= n < nLags
                                     0 <= k < len
                                     K = 1/(len-n)

                                             | src[k], 0<=k<len
                                   src(k) = <
                                             | 0, otherwise
*/

NSPAPI(void, nspsAutoCorr,(const float*  src, int len, float*  dst, int nLags,
                                 NSPAutoCorrType  corrType))
NSPAPI(void, nspcAutoCorr,(const SCplx*  src, int len, SCplx*  dst, int nLags,
                                 NSPAutoCorrType  corrType))
NSPAPI(void, nspdAutoCorr,(const double* src, int len, double* dst, int nLags,
                                 NSPAutoCorrType  corrType))
NSPAPI(void, nspzAutoCorr,(const DCplx*  src, int len, DCplx*  dst, int nLags,
                                 NSPAutoCorrType  corrType))
NSPAPI(void, nspwAutoCorr,(const short  *src, int len, short*  dst, int nLags,
                                 NSPAutoCorrType corrType,
                                 int scaleMode, int *scalePtr))
NSPAPI(void, nspvAutoCorr,(const WCplx  *src, int len, WCplx*  dst, int nLags,
                                 NSPAutoCorrType corrType,
                                 int scaleMode, int *scalePtr))

/* ------------------------------------------------------------------------*/
/*        CrossCorralation                                                 */
/*
  dst[n] = S ~srcA[k] * srcB[k+n+loLag],  0 <= n <= hiLag-loLag
                                          0 <= k < lenA

                                                 | srcB[k], 0<=k<lenB
                                       srcB(k) = <
                                                 | 0, otherwise
  Number of result elements is hiLag-loLag+1.
  Estimate at lag of loLag in dst[0].
  Estimate at lag of hiLag in dst[hiLag-loLag].
*/

NSPAPI(void, nspsCrossCorr, (const float*  srcA,  int lenA,
                             const float*  srcB,  int lenB, float*  dst,
                                   int     loLag, int hiLag))
NSPAPI(void, nspcCrossCorr, (const SCplx*  srcA,  int lenA,
                             const SCplx*  srcB,  int lenB, SCplx*  dst,
                                   int     loLag, int hiLag))
NSPAPI(void, nspscCrossCorr,(const float*  srcA,  int lenA,
                             const SCplx*  srcB,  int lenB, SCplx*  dst,
                                   int     loLag, int hiLag))
NSPAPI(void, nspcsCrossCorr,(const SCplx*  srcA,  int lenA,
                             const float*  srcB,  int lenB, SCplx*  dst,
                                   int     loLag, int hiLag))

NSPAPI(void,  nspdCrossCorr,(const double* srcA,  int lenA,
                             const double* srcB,  int lenB, double* dst,
                                   int     loLag, int hiLag))
NSPAPI(void,  nspzCrossCorr,(const DCplx*  srcA,  int lenA,
                             const DCplx*  srcB,  int lenB, DCplx*  dst,
                                   int     loLag, int hiLag))
NSPAPI(void, nspdzCrossCorr,(const double* srcA,  int lenA,
                             const DCplx*  srcB,  int lenB, DCplx*  dst,
                                   int     loLag, int hiLag))
NSPAPI(void, nspzdCrossCorr,(const DCplx*  srcA,  int lenA,
                             const double* srcB,  int lenB, DCplx*  dst,
                                   int     loLag, int hiLag))
NSPAPI(void, nspwCrossCorr, (const short*  srcA,  int lenA,
                             const short*  srcB,  int lenB, short*  dst,
                                   int     loLag, int hiLag,
                                   int scaleMode, int *scalePtr))
NSPAPI(void, nspvCrossCorr, (const WCplx*  srcA,  int lenA,
                             const WCplx*  srcB,  int lenB, WCplx*  dst,
                                   int     loLag, int hiLag,
                                   int scaleMode, int *scalePtr))
NSPAPI(void, nspwvCrossCorr,(const short*  srcA,  int lenA,
                             const WCplx*  srcB,  int lenB, WCplx*  dst,
                                   int     loLag, int hiLag,
                                   int scaleMode, int *scalePtr))
NSPAPI(void, nspvwCrossCorr,(const WCplx*  srcA,  int lenA,
                             const short*  srcB,  int lenB, WCplx*  dst,
                                   int     loLag, int hiLag,
                                   int scaleMode, int *scalePtr))

#endif                                  /* _NSPCORR_H                      */
