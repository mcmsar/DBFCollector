/*M*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1996 Intel Corporation. All Rights Reserved.
//
//  PVCS: 
//      $Workfile:   NSPARITH.H  $
//      $Revision:   1.0  $
//      $ModTime:   Dec 16 1996 18:31:20  $
//
//  Purpose: NSP Scalar and Vector Arithmetics
*M*/

#if !defined (_NSPARITH_H) || defined (_OWN_BLDPCS)
# define _NSPARITH_H

/*-------------------------------------------------------------------------*/
/*   Miscellaneous Scalar Functions and Vector Functions                   */
/*        Complex Add, Sub, Mpy, Div, Conj                                 */
/*                                                                         */
/*   These functions perform addition, subtraction, multiplication,        */
/*   division, and conjugation on complex numbers a and b.                 */

NSPAPI(SCplx, nspcAdd, (const SCplx a, const SCplx b))
NSPAPI(SCplx, nspcSub, (const SCplx a, const SCplx b))
NSPAPI(SCplx, nspcMpy, (const SCplx a, const SCplx b))
NSPAPI(SCplx, nspcDiv, (const SCplx a, const SCplx b))
NSPAPI(SCplx, nspcConj,(const SCplx a))

/*---- Additional Functions -----------------------------------------------*/

NSPAPI(SCplx, nspcSet, (float  re, float im))

/*-------------------------------------------------------------------------*/
/*        Vector Initialization                                            */
/*   These functions initialize vectors of length n.                       */

NSPAPI(void, nspsbZero,(float  *dst, int n))
NSPAPI(void, nspcbZero,(SCplx  *dst, int n))

NSPAPI(void, nspsbSet, (float  val,              float *dst, int n))
NSPAPI(void, nspcbSet, (float  re,  float   im,  SCplx *dst, int n))

NSPAPI(void, nspsbCopy,(const float  *src, float  *dst, int n))
NSPAPI(void, nspcbCopy,(const SCplx  *src, SCplx  *dst, int n))

/*-------------------------------------------------------------------------*/
/*        Vector Addition and multiplication                               */
/*   These functions perform element-wise arithmetic on vectors of length n*/

/* dst[i]=dst[i]+val;                                                      */

NSPAPI(void,nspsbAdd1,(const float val,                    float *dst,int n))
NSPAPI(void,nspcbAdd1,(const SCplx val,                    SCplx *dst,int n))

/* dst[i]=dst[i]+src[i];                                                   */

NSPAPI(void,nspsbAdd2,(const float *src,                   float *dst,int n))
NSPAPI(void,nspcbAdd2,(const SCplx *src,                   SCplx *dst,int n))

/* dst[i]=srcA[i]+srcB[i];                                                 */

NSPAPI(void,nspsbAdd3,(const float *srcA,const float *srcB,float *dst,int n))
NSPAPI(void,nspcbAdd3,(const SCplx *srcA,const SCplx *srcB,SCplx *dst,int n))

/* dst[i]=dst[i]-val;                                                      */

NSPAPI(void,nspsbSub1,(const float val,                    float *dst,int n))
NSPAPI(void,nspcbSub1,(const SCplx val,                    SCplx *dst,int n))

/* dst[i]=dst[i]-val[i];                                                   */

NSPAPI(void,nspsbSub2,(const float *val,                   float *dst,int n))
NSPAPI(void,nspcbSub2,(const SCplx *val,                   SCplx *dst,int n))

/* dst[i]=src[i]-val[i];                                                   */

NSPAPI(void,nspsbSub3,(const float *src, const float *val, float *dst,int n))
NSPAPI(void,nspcbSub3,(const SCplx *src, const SCplx *val, SCplx *dst,int n))

/* dst[i]=dst[i]*val;                                                      */

NSPAPI(void,nspsbMpy1,(const float val,                    float *dst,int n))
NSPAPI(void,nspcbMpy1,(const SCplx val,                    SCplx *dst,int n))

/* dst[i]=dst[i]*src[i];                                                   */

NSPAPI(void,nspsbMpy2,(const float *src,                   float *dst,int n))
NSPAPI(void,nspcbMpy2,(const SCplx *src,                   SCplx *dst,int n))
                                                             
/* dst[i]=srcA[i]*srcB[i];                                                 */

NSPAPI(void,nspsbMpy3,(const float *srcA,const float *srcB,float *dst,int n))
NSPAPI(void,nspcbMpy3,(const SCplx *srcA,const SCplx *srcB,SCplx *dst,int n))

/*-------------------------------------------------------------------------*/
/*        Complex conjugates of scalars and vectors                        */

NSPAPI(void, nspcbConj1,      (      SCplx *vec,             int n))
NSPAPI(void, nspcbConj2,      (const SCplx *src, SCplx *dst, int n))
NSPAPI(void, nspcbConjFlip2,  (const SCplx *src, SCplx *dst, int n))
NSPAPI(void, nspcbConjExtend1,(      SCplx *vec,             int n))
NSPAPI(void, nspcbConjExtend2,(const SCplx *src, SCplx *dst, int n))


/*-------------------------------------------------------------------------*/
/*   Miscellaneous Scalar Functions and Vector Functions                   */
/*        Complex Add, Sub, Mpy, Div, Conj                                 */
/*   These functions perform addition, subtraction, multiplication,        */
/*   division, and conjugation on complex numbers a and b.                 */
/*                                                                         */

NSPAPI(DCplx, nspzAdd, (const DCplx a, const DCplx b))
NSPAPI(DCplx, nspzSub, (const DCplx a, const DCplx b))
NSPAPI(DCplx, nspzMpy, (const DCplx a, const DCplx b))
NSPAPI(DCplx, nspzDiv, (const DCplx a, const DCplx b))
NSPAPI(DCplx, nspzConj,(const DCplx a))

/*---- Additional Functions -----------------------------------------------*/

NSPAPI(DCplx, nspzSet, (double re, double im))

/*-------------------------------------------------------------------------*/
/*        Vector Initialization                                            */
/*   These functions initialize vectors of length n.                       */

NSPAPI(void, nspdbZero,(double *dst, int n))
NSPAPI(void, nspzbZero,(DCplx  *dst, int n))

NSPAPI(void, nspdbSet, (double val,           double *dst, int n))
NSPAPI(void, nspzbSet, (double re, double im, DCplx  *dst, int n))

NSPAPI(void, nspdbCopy,(const double *src, double *dst, int n))
NSPAPI(void, nspzbCopy,(const DCplx  *src, DCplx  *dst, int n))

/*-------------------------------------------------------------------------*/
/*        Vector Addition and multiplication                               */
/*   These functions perform element-wise arithmetic on vectors of length n*/

/* dst[i]=dst[i]+val;                                                      */

NSPAPI(void, nspdbAdd1,(const double val,                    double *dst,int n))
NSPAPI(void, nspzbAdd1,(const DCplx  val,                    DCplx  *dst,int n))
/* dst[i]=dst[i]+src[i];                                                   */

NSPAPI(void, nspdbAdd2,(const double *src,                   double *dst,int n))
NSPAPI(void, nspzbAdd2,(const DCplx  *src,                   DCplx  *dst,int n))

/* dst[i]=srcA[i]+srcB[i];                                                 */

NSPAPI(void, nspdbAdd3,(const double *srcA,const double *srcB,double *dst,int n))
NSPAPI(void, nspzbAdd3,(const DCplx  *srcA,const DCplx  *srcB,DCplx  *dst,int n))

/* dst[i]=dst[i]-val;                                                      */

NSPAPI(void, nspdbSub1,(const double val,                    double *dst,int n))
NSPAPI(void, nspzbSub1,(const DCplx  val,                    DCplx  *dst,int n))

/* dst[i]=dst[i]-val[i];                                                   */

NSPAPI(void, nspdbSub2,(const double *val,                   double *dst,int n))
NSPAPI(void, nspzbSub2,(const DCplx  *val,                   DCplx  *dst,int n))

/* dst[i]=src[i]-val[i];                                                   */

NSPAPI(void, nspdbSub3,(const double *src, const double *val, double *dst,int n))
NSPAPI(void, nspzbSub3,(const DCplx  *src, const DCplx  *val, DCplx  *dst,int n))

/* dst[i]=dst[i]*val;                                                      */

NSPAPI(void, nspdbMpy1,(const double val,                    double *dst,int n))
NSPAPI(void, nspzbMpy1,(const DCplx  val,                    DCplx  *dst,int n))

/* dst[i]=dst[i]*src[i];                                                   */

NSPAPI(void, nspdbMpy2,(const double *src,                   double *dst,int n))
NSPAPI(void, nspzbMpy2,(const DCplx  *src,                   DCplx  *dst,int n))
                                                             
/* dst[i]=srcA[i]*srcB[i];                                                 */

NSPAPI(void, nspdbMpy3,(const double *srcA,const double *srcB,double *dst,int n))
NSPAPI(void, nspzbMpy3,(const DCplx  *srcA,const DCplx  *srcB,DCplx  *dst,int n))

/*-------------------------------------------------------------------------*/
/*                                                                         */
/*        Complex conjugates of scalars and vectors                        */
/*                                                                         */

NSPAPI(void, nspzbConj1,      (      DCplx *vec,             int n))
NSPAPI(void, nspzbConj2,      (const DCplx *src, DCplx *dst, int n))
NSPAPI(void, nspzbConjFlip2,  (const DCplx *src, DCplx *dst, int n))
NSPAPI(void, nspzbConjExtend1,(      DCplx *vec,             int n))
NSPAPI(void, nspzbConjExtend2,(const DCplx *src, DCplx *dst, int n))


/*-------------------------------------------------------------------------*/
/*   Miscellaneous Scalar Functions and Vector Functions                   */
/*        Complex Add, Sub, Mpy, Div, Conj                                 */
/*   These functions perform addition, subtraction, multiplication,        */
/*   division, and conjugation on complex numbers a and b.                 */
/*                                                                         */

NSPAPI(WCplx, nspvAdd, (const WCplx  a, const WCplx  b,
                              int    scaleMode, int   *scaleFactor))
NSPAPI(WCplx, nspvSub, (const WCplx  a, const WCplx  b,
                              int    scaleMode, int   *scaleFactor))
NSPAPI(WCplx, nspvMpy, (const WCplx  a, const WCplx  b,
                              int    scaleMode, int   *scaleFactor))
NSPAPI(WCplx, nspvDiv, (const WCplx  a, const WCplx  b))
NSPAPI(WCplx, nspvConj,(const WCplx  a))

/*---- Additional Functions -----------------------------------------------*/

NSPAPI(WCplx, nspvSet, (short re, short im))

/*-------------------------------------------------------------------------*/
/*        Vector Initialization                                            */
/*   These functions initialize vectors of length n.                       */

NSPAPI(void, nspwbZero,(short *dst, int n))
NSPAPI(void, nspvbZero,(WCplx *dst, int n))

NSPAPI(void, nspwbSet, (short val,          short *dst, int n))
NSPAPI(void, nspvbSet, (short re, short im, WCplx *dst, int n))

NSPAPI(void, nspwbCopy,(const short *src, short *dst, int n))
NSPAPI(void, nspvbCopy,(const WCplx *src, WCplx *dst, int n))

/*-------------------------------------------------------------------------*/
/*        Vector Addition and multiplication                               */
/*   These functions perform element-wise arithmetic on vectors of length n*/

NSPAPI(void, nspwbAdd1,(const short  val,                   short *dst,int n,
                              int    scaleMode, int   *scaleFactor))
NSPAPI(void, nspvbAdd1,(const WCplx  val,                   WCplx *dst,int n,
                              int    scaleMode, int   *scaleFactor))

NSPAPI(void, nspwbAdd2,(const short *src,                   short *dst,int n,
                              int    scaleMode, int   *scaleFactor))
NSPAPI(void, nspvbAdd2,(const WCplx *src,                   WCplx *dst,int n,
                              int    scaleMode, int   *scaleFactor))

NSPAPI(void, nspwbAdd3,(const short *srcA,const short *srcB,short *dst,int n,
                              int    scaleMode, int   *scaleFactor))
NSPAPI(void, nspvbAdd3,(const WCplx *srcA,const WCplx *srcB,WCplx *dst,int n,
                              int    scaleMode, int   *scaleFactor))

NSPAPI(void, nspwbSub1,(const short  val,                   short *dst,int n,
                              int    scaleMode, int   *scaleFactor))
NSPAPI(void, nspvbSub1,(const WCplx  val,                   WCplx *dst,int n,
                              int    scaleMode, int   *scaleFactor))

NSPAPI(void, nspwbSub2,(const short *val,                   short *dst,int n,
                              int    scaleMode, int   *scaleFactor))
NSPAPI(void, nspvbSub2,(const WCplx *val,                   WCplx *dst,int n,
                              int    scaleMode, int   *scaleFactor))

NSPAPI(void, nspwbSub3,(const short *src, const short *val, short *dst,int n,
                              int    scaleMode, int   *scaleFactor))
NSPAPI(void, nspvbSub3,(const WCplx *src, const WCplx *val, WCplx *dst,int n,
                              int    scaleMode, int   *scaleFactor))

NSPAPI(void, nspwbMpy1,(const short  val,                   short *dst,int n,
                              int    scaleMode, int   *scaleFactor))
NSPAPI(void, nspvbMpy1,(const WCplx  val,                   WCplx *dst,int n,
                              int    scaleMode, int   *scaleFactor))

NSPAPI(void, nspwbMpy2,(const short *src,                   short *dst,int n,
                              int    scaleMode, int   *scaleFactor))
NSPAPI(void, nspvbMpy2,(const WCplx *src,                   WCplx *dst,int n,
                              int    scaleMode, int   *scaleFactor))

NSPAPI(void, nspwbMpy3,(const short *srcA,const short *srcB,short *dst,int n,
                              int    scaleMode, int   *scaleFactor))
NSPAPI(void, nspvbMpy3,(const WCplx *srcA,const WCplx *srcB,WCplx *dst,int n,
                              int    scaleMode, int   *scaleFactor))

/*-------------------------------------------------------------------------*/
/*        Complex conjugates of vectors                                    */

NSPAPI(void, nspvbConj1,      (      WCplx *vec,             int n))
NSPAPI(void, nspvbConj2,      (const WCplx *src, WCplx *dst, int n))
NSPAPI(void, nspvbConjFlip2,  (const WCplx *src, WCplx *dst, int n))
NSPAPI(void, nspvbConjExtend1,(      WCplx *vec,             int n))
NSPAPI(void, nspvbConjExtend2,(const WCplx *src, WCplx *dst, int n))


#endif                                  /* _NSPARITH_H                     */
