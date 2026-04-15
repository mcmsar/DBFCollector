/*M*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1994-1998 Intel Corporation. All Rights Reserved.
//
//  PVCS:
//      $Workfile: nsp30/include/nspwlt.h $
//      $Revision: 0.3 $
//      $Modtime: 1996/10/17 21:16:22 $
//      $ModTime:    Jun 25 1998 18:10:11  $
//
//  Purpose: NSP wavelet transform.
//
//  Authors: Valery Kuryakin, Pramila Srinivasan, Boris Shamraev,
//           updated by Michael S. Kulikov for decomposition and 
//           reconstruction of signal whith arbitrary length
//
*M*/

#if !defined (_NSPWLT_H) || defined (_OWN_BLDPCS)

#define _NSPWLT_H

/* ======================================================================== */

#if !defined (_OWN_BLDPCS)

/* ------------------------------------------------------------------------ */
/*  Structure for store all information needed to decompose and reconstruct */
/*  of wavelet transform:                                                   */
/* ------------------------------------------------------------------------ */

typedef struct _NSPWtState {
   int    wtCore;
   int    wtType;
   int    wtOrtType;
   int    par1;
   int    par2;
   int    dataOrder;
   int    level;
   int    len_filt[ 4 ];
   int    ofs_filt[ 4 ];
   void  *tap_filt[ 4 ];
   void  *src_pad;
   int    len_dec;
   int   *tree;
} NSPWtState;

/*  wtCore  -  for calculation core (float, double or short) control  */
# define   NSP_WtCoreFloat       1
# define   NSP_WtCoreDouble      2
# define   NSP_WtCoreShort       4

/*  wtType  -  the type of wavelet  */
# define   NSP_Haar              1
# define   NSP_Daublet           2
# define   NSP_Symmlet           3
# define   NSP_Coiflet           4
# define   NSP_Vaidyanathan      5
# define   NSP_BSpline           6
# define   NSP_BSplineDual       7
# define   NSP_LinSpline         8
# define   NSP_QuadSpline        9
# define   NSP_WtByFilter       10

/*  wtOrtType  -  the orthogonality type of wavelet for add. control */
# define   NSP_WtOrtType         1
# define   NSP_WtBiOrtType       2
# define   NSP_WtOrtUnknown      3

/*
//  par1, par2   -  the parameters of wavelet,
//                  dependent from the type of wavelet.
//  NSP_Haar           par1 - dummy
//                     par2 - dummy
//  NSP_Daublet        par1 = 1,2,3,4,5,6,7,8,9,10.
//                     par2 - dummy
//  NSP_Symmlet        par1 = 1,2,3,4,5,6,7.
//                     par2 - dummy
//  NSP_Coiflet        par1 = 1,2,3,4,5.
//                     par2 - dummy
//  NSP_Vaidyanathan   par1 - dummy
//                     par2 - dummy
//
//  NSP_BSpline        B - spline,
//  NSP_BSplineDual               (par1, par2) must be:
//                     box -
//                         ( 1, 1 ), ( 1, 3 ), ( 1, 5 );
//                     lin. spline -
//                         ( 2, 2 ), ( 2, 4 ), ( 2, 6 ), ( 2, 8 );
//                     quad. spline -
//                         ( 3, 1 ), ( 3, 3 ), ( 3, 5 ), ( 3, 7 ), ( 3, 9 ).
//
//  NSP_LinSpline      (eq. case NSP_BSpline with par1=2, par2=2.)
//                     par1 - dummy
//                     par2 - dummy
//  NSP_QuadSpline     (eq. case NSP_BSpline with par1=3, par2=3.)
//                     par1 - dummy
//                     par2 - dummy
*/

/*  dataOrder  -  the length of data  L = pow(2,dataOrder)  */

/*  level  -  determines the number of levels of decompositions we need.  */

/*
//  Filters
//  len_filt[] - length
//  ofs_filt[] - offset
//  tap_filt[] - taps
//               [ 0 ] - low  pass analysis  filter
//               [ 1 ] - high pass analysis  filter
//               [ 2 ] - low  pass synthesis filter
//               [ 3 ] - high pass synthesis filter
//  Must be
//      2 <= len_filt[ i ] ,
//      0 <= ofs_filt[ i ] < len_filt[ i ] ,
//      i = 0, 1, 2, 3;
//      len_filt[ 0 ] = len_filt[ 3 ] ,
//      len_filt[ 1 ] = len_filt[ 2 ] .
//
//  src_pad - working array
*/

#endif                                                       /* _OWN_BLDPCS */

/* ======================================================================== */


/* Free own wavelet memory */
NSPAPI(void,nspWtFree,( NSPWtState *wtState))


/* ------------------------------------------------------------------------ */
/*                                                                          */
/*                 The initialization of the wavelet transform.             */
/*                                                                          */
/* ------------------------------------------------------------------------ */

NSPAPI(void,nspsWtInit,(int par1, int par2, int dataOrder, int level,
                        NSPWtState *wtState, int wtType))
NSPAPI(void,nspdWtInit,(int par1, int par2, int dataOrder, int level,
                        NSPWtState *wtState, int wtType))
NSPAPI(void,nspwWtInit,(int par1, int par2, int dataOrder, int level,
                        NSPWtState *wtState, int wtType))
NSPAPI(void,nspsWtInitLen,(int par1, int par2, int len, int level,
                        NSPWtState *wtState, int wtType, int *len_dec))
NSPAPI(void,nspdWtInitLen,(int par1, int par2, int len, int level,
                        NSPWtState *wtState, int wtType, int *len_dec))
NSPAPI(void,nspwWtInitLen,(int par1, int par2, int len, int level,
                        NSPWtState *wtState, int wtType, int *len_dec))


/* ------------------------------------------------------------------------ */
/*                                                                          */
/*                       Set all parameters of wavelet.                     */
/*                                                                          */
/* ------------------------------------------------------------------------ */

NSPAPI(void,nspsWtSetState,(NSPWtState *wtState, int wtType,
                            int par1, int par2, int dataOrder, int level,
                  const float **fTaps, const int *fLen, const int *fOffset))
NSPAPI(void,nspdWtSetState,(NSPWtState *wtState, int wtType,
                            int par1, int par2, int dataOrder, int level,
                  const double **fTaps, const int *fLen, const int *fOffset))
NSPAPI(void,nspwWtSetState,(NSPWtState *wtState, int wtType,
                            int par1, int par2, int dataOrder, int level,
                  const float **fTaps, const int *fLen, const int *fOffset))


/* ------------------------------------------------------------------------ */
/*                                                                          */
/*                       Get all parameters of wavelet.                     */
/*                                                                          */
/* ------------------------------------------------------------------------ */

NSPAPI(void,nspsWtGetState,(NSPWtState *wtState, int *wtType,
                            int *par1, int *par2, int *dataOrder, int *level,
                            float  **fTaps, int *fLen, int *fOffset))
NSPAPI(void,nspdWtGetState,(NSPWtState *wtState, int *wtType,
                            int *par1, int *par2, int *dataOrder, int *level,
                            double **fTaps, int *fLen, int *fOffset))
NSPAPI(void,nspwWtGetState,(NSPWtState *wtState, int *wtType,
                            int *par1, int *par2, int *dataOrder, int *level,
                            float  **fTaps, int *fLen, int *fOffset))


/* ------------------------------------------------------------------------ */
/*                                                                          */
/*                           Wavelet decomposition.                         */
/*                                                                          */
/* ------------------------------------------------------------------------ */

NSPAPI(void,nspsWtDecompose,
               (NSPWtState *wtState, const float  *src, float  *dst))
NSPAPI(void,nspdWtDecompose,
               (NSPWtState *wtState, const double *src, double *dst))
NSPAPI(void,nspwWtDecompose,
               (NSPWtState *wtState, const short  *src, short  *dst))


/* ------------------------------------------------------------------------ */
/*                                                                          */
/*                          Wavelet reconstruction.                         */
/*                                                                          */
/* ------------------------------------------------------------------------ */

NSPAPI(void,nspsWtReconstruct,
               (NSPWtState *wtState, const float  *src, float  *dst))
NSPAPI(void,nspdWtReconstruct,
               (NSPWtState *wtState, const double *src, double *dst))
NSPAPI(void,nspwWtReconstruct,
               (NSPWtState *wtState, const short  *src, short  *dst))


/* ======================================================================== */

#endif                                                         /* _NSPWLT_H */
