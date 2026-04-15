/*M*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1995 Intel Corporation. All Rights Reserved.
//
//  PVCS: 
//      $Workfile:   NSPVEC.H  $
//      $Revision:   1.0  $
//      $Date:   Dec 16 1996 18:31:32  $
//      $Archive:   X:/nsp40_arc/INCLUDE/NSPVEC.H_v  $
//
//  Purpose: NSP Vector Arithmetic and Algebraic Functions
*M*/

#if !defined (_NSPVEC_H) || defined (_OWN_BLDPCS)
# define _NSPVEC_H

/* ------------------------------------------------------------------------*/

#if !defined (_OWN_BLDPCS)
# define NSP_Gt 1
# define NSP_GT NSP_Gt
# define NSP_Lt 0
# define NSP_LT NSP_Lt
# define HUGE_VAL_S 3.402823466e+38F
# define HUGE_VAL_D 1.7976931348623158e+308
#endif


/* ------------------------------------------------------------------------*/

NSPAPI(void,nspsbSqr1, (      float  *vec,              int len))
NSPAPI(void,nspcbSqr1, (      SCplx  *vec,              int len))
NSPAPI(void,nspdbSqr1, (      double *vec,              int len))
NSPAPI(void,nspzbSqr1, (      DCplx  *vec,              int len))
NSPAPI(void,nspwbSqr1, (      short  *vec,              int len,
                              int     scaleMode,        int *scaleFactor ))

NSPAPI(void,nspvbSqr1, (      WCplx  *vec,              int len,
                              int     scaleMode,        int *scaleFactor ))

NSPAPI(void,nspsbSqr2, (const float  *src, float  *dst, int len))
NSPAPI(void,nspcbSqr2, (const SCplx  *src, SCplx  *dst, int len))
NSPAPI(void,nspdbSqr2, (const double *src, double *dst, int len))
NSPAPI(void,nspzbSqr2, (const DCplx  *src, DCplx  *dst, int len))
NSPAPI(void,nspwbSqr2, (const short  *src, short  *dst, int len,
                              int     scaleMode,        int *scaleFactor))
NSPAPI(void,nspvbSqr2, (const WCplx  *src, WCplx  *dst, int len,
                              int     scaleMode,        int *scaleFactor ))

NSPAPI(void,nspsbSqrt1,(      float  *vec,              int len))
NSPAPI(void,nspcbSqrt1,(      SCplx  *vec,              int len))
NSPAPI(void,nspdbSqrt1,(      double *vec,              int len))
NSPAPI(void,nspzbSqrt1,(      DCplx  *vec,              int len))
NSPAPI(void,nspwbSqrt1,(      short  *vec,              int len))
NSPAPI(void,nspvbSqrt1,(      WCplx  *vec,              int len))

NSPAPI(void,nspsbSqrt2,(const float  *src, float  *dst, int len))
NSPAPI(void,nspcbSqrt2,(const SCplx  *src, SCplx  *dst, int len))
NSPAPI(void,nspdbSqrt2,(const double *src, double *dst, int len))
NSPAPI(void,nspzbSqrt2,(const DCplx  *src, DCplx  *dst, int len))
NSPAPI(void,nspwbSqrt2,(const short  *src, short  *dst, int len))
NSPAPI(void,nspvbSqrt2,(const WCplx  *src, WCplx  *dst, int len))

NSPAPI(void,nspsbThresh1,(float  *vec, int len, float  thresh, int relOp))
NSPAPI(void,nspcbThresh1,(SCplx  *vec, int len, float  thresh, int relOp))
NSPAPI(void,nspdbThresh1,(double *vec, int len, double thresh, int relOp))
NSPAPI(void,nspzbThresh1,(DCplx  *vec, int len, double thresh, int relOp))
NSPAPI(void,nspwbThresh1,(short  *vec, int len, short  thresh, int relOp))
NSPAPI(void,nspvbThresh1,(WCplx  *vec, int len, short  thresh, int relOp))

NSPAPI(void,nspsbThresh2,(const float  *src,    float  *dst,int len,
                                float   thresh, int     relOp))
NSPAPI(void,nspcbThresh2,(const SCplx  *src,    SCplx  *dst,int len,
                                float   thresh, int     relOp))
NSPAPI(void,nspdbThresh2,(const double *src,    double *dst,int len,
                                double  thresh, int     relOp))
NSPAPI(void,nspzbThresh2,(const DCplx  *src,    DCplx  *dst,int len,
                                double  thresh, int      relOp))
NSPAPI(void,nspwbThresh2,(const short  *src,    short  *dst,int len,
                                short   thresh, int      relOp))
NSPAPI(void,nspvbThresh2,(const WCplx  *src,    WCplx  *dst,int len,
                                short   thresh, int      relOp))

NSPAPI(void,nspsbInvThresh1,(float  *vec, int len, float  thresh))
NSPAPI(void,nspcbInvThresh1,(SCplx  *vec, int len, float  thresh))
NSPAPI(void,nspdbInvThresh1,(double *vec, int len, double thresh))
NSPAPI(void,nspzbInvThresh1,(DCplx  *vec, int len, double thresh))

NSPAPI(void,nspsbInvThresh2,(const float  *src, float  *dst, int len,
                                   float   thresh))
NSPAPI(void,nspcbInvThresh2,(const SCplx  *src, SCplx  *dst, int len,
                                   float   thresh))
NSPAPI(void,nspdbInvThresh2,(const double *src, double *dst, int len,
                                   double  thresh))
NSPAPI(void,nspzbInvThresh2,(const DCplx  *src, DCplx  *dst, int len,
                                   double  thresh))

NSPAPI(void,   nspsbAbs1, (      float  *vec,              int len))
NSPAPI(void,   nspdbAbs1, (      double *vec,              int len))
NSPAPI(void,   nspwbAbs1, (      short  *vec,              int len))

NSPAPI(void,   nspsbAbs2, (const float  *src, float  *dst, int len))
NSPAPI(void,   nspdbAbs2, (const double *src, double *dst, int len))
NSPAPI(void,   nspwbAbs2, (const short  *src, short  *dst, int len))

NSPAPI(float,  nspsMax,   (const float  *vec,              int len))
NSPAPI(double, nspdMax,   (const double *vec,              int len))
NSPAPI(short,  nspwMax,   (const short  *vec,              int len))
NSPAPI(float,  nspsMin,   (const float  *vec,              int len))
NSPAPI(double, nspdMin,   (const double *vec,              int len))
NSPAPI(short,  nspwMin,   (const short  *vec,              int len))

NSPAPI(float,  nspsMaxExt, (const float  *vec, int len, int* index))
NSPAPI(double, nspdMaxExt, (const double *vec, int len, int* index))
NSPAPI(short,  nspwMaxExt, (const short  *vec, int len, int* index))
NSPAPI(float,  nspsMinExt, (const float  *vec, int len, int* index))
NSPAPI(double, nspdMinExt, (const double *vec, int len, int* index))
NSPAPI(short,  nspwMinExt, (const short  *vec, int len, int* index))


NSPAPI(float,  nspsMean,  (const float  *vec,              int len))
NSPAPI(double, nspdMean,  (const double *vec,              int len))
NSPAPI(short,  nspwMean,  (const short  *vec,              int len))


NSPAPI(float,  nspsStdDev,(const float  *vec,              int len))
NSPAPI(double, nspdStdDev,(const double *vec,              int len))
NSPAPI(short,  nspwStdDev,(const short  *vec,              int len,
                                 int     scaleMode,        int *scaleFactor))

#endif                                          /* _NSPVEC_H               */
