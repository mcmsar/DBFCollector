/*M*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1995 Intel Corporation. All Rights Reserved.
//
//  PVCS: 
//      $Workfile:   NSPWIN.H  $
//      $Revision:   1.0  $
//      $Date:   Dec 16 1996 18:31:32  $
//      $Archive:   X:/nsp40_arc/INCLUDE/NSPWIN.H_v  $
//
//  Purpose: NSP Windowing Functions. Declaration
*M*/

#if !defined (_NSPWIN_H)  || defined (_OWN_BLDPCS)
#define _NSPWIN_H

/* ------------------------------------------------------------------------*/
/*                                                                         */
/*   Win                                                                   */
/*                                                                         */
/* Multiply a vector by a windowing function.                              */
/*                                                                         */

NSPAPI(void,nspsWinBartlett, (float  *vec, int N))
NSPAPI(void,nspcWinBartlett, (SCplx  *vec, int N))
NSPAPI(void,nspdWinBartlett, (double *vec, int N))
NSPAPI(void,nspzWinBartlett, (DCplx  *vec, int N))
NSPAPI(void,nspwWinBartlett, (short  *vec, int N))
NSPAPI(void,nspvWinBartlett, (WCplx  *vec, int N))

NSPAPI(void,nspsWinHann, (float  *vec, int N))
NSPAPI(void,nspcWinHann, (SCplx  *vec, int N))
NSPAPI(void,nspdWinHann, (double *vec, int N))
NSPAPI(void,nspzWinHann, (DCplx  *vec, int N))
NSPAPI(void,nspwWinHann, (short  *vec, int N))
NSPAPI(void,nspvWinHann, (WCplx  *vec, int N))

NSPAPI(void,nspsWinHamming, (float  *vec, int N))
NSPAPI(void,nspcWinHamming, (SCplx  *vec, int N))
NSPAPI(void,nspdWinHamming, (double *vec, int N))
NSPAPI(void,nspzWinHamming, (DCplx  *vec, int N))
NSPAPI(void,nspwWinHamming, (short  *vec, int N))
NSPAPI(void,nspvWinHamming, (WCplx  *vec, int N))

NSPAPI(void,nspsWinBlackman, (float  *vec, int N, float  alpha))
NSPAPI(void,nspcWinBlackman, (SCplx  *vec, int N, float  alpha))
NSPAPI(void,nspdWinBlackman, (double *vec, int N, double alpha))
NSPAPI(void,nspzWinBlackman, (DCplx  *vec, int N, double alpha))
NSPAPI(void,nspwWinBlackman, (short  *vec, int N, float  alpha))
NSPAPI(void,nspvWinBlackman, (WCplx  *vec, int N, float  alpha))

NSPAPI(void,nspsWinBlackmanStd, (float  *vec, int N))
NSPAPI(void,nspcWinBlackmanStd, (SCplx  *vec, int N))
NSPAPI(void,nspdWinBlackmanStd, (double *vec, int N))
NSPAPI(void,nspzWinBlackmanStd, (DCplx  *vec, int N))
NSPAPI(void,nspwWinBlackmanStd, (short  *vec, int N))
NSPAPI(void,nspvWinBlackmanStd, (WCplx  *vec, int N))

NSPAPI(void,nspsWinBlackmanOpt, (float  *vec, int N))
NSPAPI(void,nspcWinBlackmanOpt, (SCplx  *vec, int N))
NSPAPI(void,nspdWinBlackmanOpt, (double *vec, int N))
NSPAPI(void,nspzWinBlackmanOpt, (DCplx  *vec, int N))
NSPAPI(void,nspwWinBlackmanOpt, (short  *vec, int N))
NSPAPI(void,nspvWinBlackmanOpt, (WCplx  *vec, int N))

NSPAPI(void,nspsWinKaiser, (float  *vec, int N, float  beta))
NSPAPI(void,nspcWinKaiser, (SCplx  *vec, int N, float  beta))
NSPAPI(void,nspdWinKaiser, (double *vec, int N, double beta))
NSPAPI(void,nspzWinKaiser, (DCplx  *vec, int N, double beta))
NSPAPI(void,nspwWinKaiser, (short  *vec, int N, float  beta))
NSPAPI(void,nspvWinKaiser, (WCplx  *vec, int N, float  beta))

#endif                                  /* _NSPWIN_H                       */
