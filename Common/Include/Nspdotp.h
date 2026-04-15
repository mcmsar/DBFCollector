/*M*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1995 Intel Corporation. All Rights Reserved.
//
//  PVCS: 
//      $Workfile: nspdotp.h $
//      $Revision: 1 $
//      $Date: 28/04/97 12:15 $
//      $Archive: /gres/project/nsp/dotp/nspdotp.h $
//
//  Purpose: NSP Vector Product Functions
//
//  History:
//    31-sep-98   Add prototypes
//                   nspwDotProdExt
//                   nspvDotProdExt
//                   nspwvDotProsExt
//                   nspvwDotProdExt
*M*/

#if !defined (_NSPDOTP_H) || defined (_OWN_BLDPCS)
#define _NSPDOTP_H

NSPAPI(float,  nspsDotProd, (const float  *srcA, const float  *srcB, int len))
NSPAPI(SCplx,  nspcDotProd, (const SCplx  *srcA, const SCplx  *srcB, int len))
NSPAPI(double, nspdDotProd, (const double *srcA, const double *srcB, int len))
NSPAPI(DCplx,  nspzDotProd, (const DCplx  *srcA, const DCplx  *srcB, int len))

NSPAPI(short,  nspwDotProd, (const short  *srcA, const short  *srcB, int len,
                                   int     scaleMode,  int    *scaleFactor))
NSPAPI(WCplx,  nspvDotProd, (const WCplx  *srcA, const WCplx  *srcB, int len,
                                   int     scaleMode,  int    *scaleFactor))

NSPAPI(SCplx,  nspscDotProd,(const float  *srcA, const SCplx  *srcB, int len))
NSPAPI(SCplx,  nspcsDotProd,(const SCplx  *srcA, const float  *srcB, int len))
NSPAPI(DCplx,  nspdzDotProd,(const double *srcA, const DCplx  *srcB, int len))
NSPAPI(DCplx,  nspzdDotProd,(const DCplx  *srcA, const double *srcB, int len))

NSPAPI(WCplx,  nspwvDotProd,(const short  *srcA, const WCplx  *srcB, int len,
                                   int     scaleMode,  int    *scaleFactor))
NSPAPI(WCplx,  nspvwDotProd,(const WCplx  *srcA, const short  *srcB, int len,
                                   int     scaleMode,  int    *scaleFactor))

/* Extend Dot Prod functions
*/
NSPAPI(int,   nspwDotProdExt,(const short* srcA, const short* srcB, int len,
                              int scaleMode, int* scaleFactor))
NSPAPI(ICplx, nspvDotProdExt,(const WCplx* srcA, const WCplx* srcB, int len,
                              int scaleMode, int* scaleFactor))
NSPAPI(ICplx, nspwvDotProdExt,(const short* srcA, const WCplx* srcB, int len,
                               int scaleMode, int* scaleFactor))
NSPAPI(ICplx, nspvwDotProdExt,(const WCplx* srcA, const short* srcB, int len,
                               int scaleMode, int* scaleFactor))

#endif                                          /* _NSPDOTP_H                */
