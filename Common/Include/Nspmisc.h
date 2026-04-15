/*M*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1995 Intel Corporation. All Rights Reserved.
//
//  RCS:
//      $Source:   nspmisc.h $
//      $Revision: 1.0 $
//      $Date:     1997/10/22 09:00:00 $
//
//  Purpose: NSP Miscellaneous Signal Processing Functions
*M*/

#if !defined (_NSPMISC_H) || defined (_OWN_BLDPCS)

#define _NSPMISC_H

/* ======================================================================== */

/* ------------------------------------------------------------------------ */
/*                                                                          */
/*       BitRev, CalcBitRevTbl, GetBitRevTbl, FreeBitRevTbls                */
/*                                                                          */
/* Obtain bit-reversed numbers, indices, and indexing tables.               */
/*                                                                          */
/* ------------------------------------------------------------------------ */

NSPAPI(int,         nspBitRev        ,(int a,   int order))
NSPAPI(const int *, nspGetBitRevTbl  ,(         int order))
NSPAPI(void,        nspCalcBitRevTbl ,(int *tbl,int order))
NSPAPI(void,        nspFreeBitRevTbls,(void))

/* ------------------------------------------------------------------------ */
/*                                                                          */
/*                      bBitRev1, bBitRev2                                  */
/*                                                                          */
/* Permute a vector into binary bit-reversed order.                         */
/*                                                                          */
/* ------------------------------------------------------------------------ */

NSPAPI(void, nspwbBitRev1,(short  *vec, int order))
NSPAPI(void, nspvbBitRev1,(WCplx  *vec, int order))
NSPAPI(void, nspsbBitRev1,(float  *vec, int order))
NSPAPI(void, nspcbBitRev1,(SCplx  *vec, int order))
NSPAPI(void, nspdbBitRev1,(double *vec, int order))
NSPAPI(void, nspzbBitRev1,(DCplx  *vec, int order))

NSPAPI(void, nspwbBitRev2,(const short  *src, short  *dst, int order))
NSPAPI(void, nspvbBitRev2,(const WCplx  *src, WCplx  *dst, int order))
NSPAPI(void, nspsbBitRev2,(const float  *src, float  *dst, int order))
NSPAPI(void, nspcbBitRev2,(const SCplx  *src, SCplx  *dst, int order))
NSPAPI(void, nspdbBitRev2,(const double *src, double *dst, int order))
NSPAPI(void, nspzbBitRev2,(const DCplx  *src, DCplx  *dst, int order))

/* ------------------------------------------------------------------------ */
/*                                                                          */
/*                   GetFftTwdTbl, GetDftTwdTbl, FreeTwdTbls                */
/*                                                                          */
/* Compute and store twiddle factors for FFT and DFT computations.          */
/*                                                                          */
/* ------------------------------------------------------------------------ */

NSPAPI(void, nspvCalcDftTwdTbl,(WCplx *tbl, int length))
NSPAPI(void, nspvCalcFftTwdTbl,(WCplx *tbl, int order))
NSPAPI(void, nspcCalcDftTwdTbl,(SCplx *tbl, int length))
NSPAPI(void, nspcCalcFftTwdTbl,(SCplx *tbl, int order))
NSPAPI(void, nspzCalcDftTwdTbl,(DCplx *tbl, int length))
NSPAPI(void, nspzCalcFftTwdTbl,(DCplx *tbl, int order))

NSPAPI(const WCplx *, nspvGetDftTwdTbl,(int length))
NSPAPI(const WCplx *, nspvGetFftTwdTbl,(int order))
NSPAPI(const SCplx *, nspcGetDftTwdTbl,(int length))
NSPAPI(const SCplx *, nspcGetFftTwdTbl,(int order))
NSPAPI(const DCplx *, nspzGetDftTwdTbl,(int length))
NSPAPI(const DCplx *, nspzGetFftTwdTbl,(int order))

NSPAPI(void, nspvFreeTwdTbls,(void))
NSPAPI(void, nspcFreeTwdTbls,(void))
NSPAPI(void, nspzFreeTwdTbls,(void))

/* ======================================================================== */

#endif                                                        /* _NSPMISC_H */
