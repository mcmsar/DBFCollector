
/*M* 
//  
//               INTeL CORPORATION PROPRIETARY INFORMATION  
//  This software is supplied under the terms of a license agreement or  
//  nondisclosure agreement with Intel Corporation and may not be copied  
//  or disclosed except in accordance with the terms of that agreement.  
//        Copyright (c) 1996 Intel Corporation. All Rights Reserved.  
//  
//  vss & PVCS: 
//    $Workfile: nsplmsl.h $ 
//    $Created: 1994  $ 
//    $Revision: 3 $ 
//    $Modtime: 24.04.97 14:27 $ 
// 
//    Purpose: NSP Adaptive FIR filter that uses the LMS algorithm.
// 
*M*/ 

#if !defined (_NSPLMSL_H) || defined (_OWN_BLDPCS)
# define _NSPLMSL_H

#if !defined (_NSPFIRL_H)
# include "nspfirl.h"
#endif

/* ------------------------------------------------------------------------*/

#if !defined (_OWN_BLDPCS)

/* --- LMS filter (method) type -------------------------------------------*/

typedef enum _NSPLmsType {NSP_LmsNull, NSP_LmsDefault} NSPLmsType;

/* --- LMS low-level filter state structure -------------------------------*/

typedef struct _NSPLmsTapState {
   FirLmsTapState;                        /* Base filter state, see FIRL.H */
   float           leak;                  /* Leak value to range taps magn */
   float           step;                  /* Step-size to change taps magn */
   int             errDly;                /* Delay of error signal         */
   NSPLmsType      type;
} NSPLmsTapState;

/* --- LMS low-level filter delay line ------------------------------------*/

typedef struct _NSPLmsDlyState {
   FirLmsDlyState;
   int adaptB;                   /* Is used in delay length definition     */
} NSPLmsDlyState;

/* ////////////////////////////////////////////////////////////
   LMSL of "integer" type uses Fixed Point representation of taps
//////////////////////////////////////////////////////////// */

typedef int FixedPoint;

typedef struct _NSPWLmsTapState {
   FirLmsTapState;               /* Base filter state, see FIRL.H   */
   float leak;                   /* Leak value to arrange taps magn */
   union {                       /* Step size to change taps values */
      float f;
      FixedPoint i;
   } step;
   int errDly;                   /* Delay of an error signal */
   NSPLmsType type;
} NSPWLmsTapState;

typedef NSPLmsDlyState NSPWLmsDlyState;

#endif

/* ------------------------------------------------------------------------*/
/* LmslInit, LmslInitMr, LmslInitDlyl                                      */
/*                                                                         */
/* Initialize  an adaptive  FIR filter  that uses  the least  mean-square  */
/* (LMS) algorithm.                                                        */


/*--- Single-rate init ----------------------------------------------------*/

NSPAPI(void,nspsLmslInit,(NSPLmsType lmsType, float *taps, int tapsLen,
                   float step, float leak,int errDly,NSPLmsTapState *tapStPtr))

NSPAPI(void,nspdLmslInit,(NSPLmsType lmsType, double *taps, int tapsLen,
                   float step, float leak,int errDly,NSPLmsTapState *tapStPtr))

NSPAPI(void,nspcLmslInit,(NSPLmsType lmsType, SCplx *taps, int tapsLen,
                   float step, float leak,int errDly,NSPLmsTapState *tapStPtr))

NSPAPI(void,nspzLmslInit,(NSPLmsType lmsType, DCplx *taps, int tapsLen,
                   float step, float leak,int errDly,NSPLmsTapState *tapStPtr))


/*--- Multi-rate init -----------------------------------------------------*/

NSPAPI(void,nspsLmslInitMr,(NSPLmsType lmsType, float *taps, int tapsLen,
                            float step, float leak, int errDly, int downFactor,
                            int downPhase, NSPLmsTapState *tapStPtr))

NSPAPI(void,nspdLmslInitMr,(NSPLmsType lmsType, double *taps, int tapsLen,
                            float step, float leak, int errDly, int downFactor,
                            int downPhase, NSPLmsTapState *tapStPtr))

NSPAPI(void,nspcLmslInitMr,(NSPLmsType lmsType, SCplx *taps, int tapsLen,
                            float step, float leak, int errDly, int downFactor,
                            int downPhase, NSPLmsTapState *tapStPtr))

NSPAPI(void,nspzLmslInitMr,(NSPLmsType lmsType, DCplx *taps, int tapsLen,
                            float step, float leak, int errDly, int downFactor,
                            int downPhase, NSPLmsTapState *tapStPtr))

/*--- Delay line init -----------------------------------------------------*/

NSPAPI(void,nspsLmslInitDlyl,(NSPLmsTapState *tapStPtr, float *dlyl, int adaptB,
                              NSPLmsDlyState *dlyStPtr))

NSPAPI(void,nspdLmslInitDlyl,(NSPLmsTapState *tapStPtr, double *dlyl,int adaptB,
                              NSPLmsDlyState *dlyStPtr))

NSPAPI(void,nspcLmslInitDlyl,(NSPLmsTapState *tapStPtr, SCplx *dlyl, int adaptB,
                              NSPLmsDlyState *dlyStPtr))

NSPAPI(void,nspzLmslInitDlyl,(NSPLmsTapState *tapStPtr, DCplx *dlyl, int adaptB,
                              NSPLmsDlyState *dlyStPtr))

/* -------------------------------------------------------------------------*/
/* LmslGetStep, LmslSetStep, LmslGetLeak, LmslSetLeak                       */
/*                                                                          */
/* Utility  functions  to  get  and  set  the  leak  and step values of a   */
/* low-level LMS filter.                                                    */

NSPAPI(float,nspsLmslGetStep, (const NSPLmsTapState *statePtr))
NSPAPI(float,nspsLmslGetLeak, (const NSPLmsTapState *statePtr))

NSPAPI(void, nspsLmslSetStep, (float step, NSPLmsTapState *statePtr))
NSPAPI(void, nspsLmslSetLeak, (float leak, NSPLmsTapState *statePtr))


/* -------------------------------------------------------------------------*/
/* Lmsl, bLmsl                                                              */
/*                                                                          */
/* Filter samples through a low-level LMS filter.                           */

NSPAPI(float, nspsLmsl, (NSPLmsTapState *tapStPtr,
                         NSPLmsDlyState *dlyStPtr, float  samp, float  err))
NSPAPI(SCplx, nspcLmsl, (NSPLmsTapState *tapStPtr,
                         NSPLmsDlyState *dlyStPtr, SCplx  samp, SCplx  err))
NSPAPI(double,nspdLmsl, (NSPLmsTapState *tapStPtr,
                         NSPLmsDlyState *dlyStPtr, double samp, double err))
NSPAPI(DCplx, nspzLmsl, (NSPLmsTapState *tapStPtr,
                         NSPLmsDlyState *dlyStPtr, DCplx  samp, DCplx  err))

NSPAPI(SCplx, nspscLmsl,(NSPLmsTapState *tapStPtr,
                         NSPLmsDlyState *dlyStPtr, float  samp, SCplx  err))
NSPAPI(DCplx, nspdzLmsl,(NSPLmsTapState *tapStPtr, 
                         NSPLmsDlyState *dlyStPtr, double samp, DCplx  err))


NSPAPI(float, nspsbLmsl,(NSPLmsTapState *tapStPtr, NSPLmsDlyState *dlyStPtr,
                         const float    *inSamps,  float err))
NSPAPI(SCplx, nspcbLmsl,(NSPLmsTapState *tapStPtr, NSPLmsDlyState *dlyStPtr,
                         const SCplx    *inSamps,  SCplx err))
NSPAPI(double,nspdbLmsl,(NSPLmsTapState *tapStPtr, NSPLmsDlyState *dlyStPtr,
                         const double   *inSamps,  double err))
NSPAPI(DCplx, nspzbLmsl,(NSPLmsTapState *tapStPtr, NSPLmsDlyState *dlyStPtr,
                         const DCplx    *inSamps,  DCplx err))


NSPAPI(SCplx, nspscbLmsl,(NSPLmsTapState *tapStPtr,NSPLmsDlyState *dlyStPtr,
                          const float    *inSamps, SCplx err))
NSPAPI(DCplx, nspdzbLmsl,(NSPLmsTapState *tapStPtr,NSPLmsDlyState *dlyStPtr,
                          const double   *inSamps, DCplx err))

/* ------------------------------------------------------------------------*/
/* LmslNa, bLmslNa                                                         */
/*                                                                         */
/* Filter a signal using a LMS filter, but without adapting the filter.    */

NSPAPI(float, nspsLmslNa,(const NSPLmsTapState *tapStPtr,
                                NSPLmsDlyState *dlyStPtr, float samp))
NSPAPI(SCplx, nspcLmslNa,(const NSPLmsTapState *tapStPtr,
                                NSPLmsDlyState *dlyStPtr, SCplx samp))
NSPAPI(double,nspdLmslNa,(const NSPLmsTapState *tapStPtr, 
                                NSPLmsDlyState *dlyStPtr, double samp))
NSPAPI(DCplx, nspzLmslNa,(const NSPLmsTapState *tapStPtr, 
                                NSPLmsDlyState *dlyStPtr, DCplx samp))

NSPAPI(SCplx,nspscLmslNa,(const NSPLmsTapState *tapStPtr,
                                NSPLmsDlyState *dlyStPtr, float samp))
NSPAPI(SCplx,nspcsLmslNa,(const NSPLmsTapState *tapStPtr,
                                NSPLmsDlyState *dlyStPtr, SCplx samp))
NSPAPI(DCplx,nspdzLmslNa,(const NSPLmsTapState *tapStPtr,
                                NSPLmsDlyState *dlyStPtr, double samp))
NSPAPI(DCplx,nspzdLmslNa,(const NSPLmsTapState *tapStPtr,
                                NSPLmsDlyState *dlyStPtr, DCplx samp))


NSPAPI(void,nspsbLmslNa,(const NSPLmsTapState *tapStPtr, NSPLmsDlyState *dlyStPtr,
                         const float *inSamps, float *outSamps, int numIters))
NSPAPI(void,nspcbLmslNa,(const NSPLmsTapState *tapStPtr, NSPLmsDlyState *dlyStPtr,
                         const SCplx *inSamps, SCplx *outSamps, int numIters))
NSPAPI(void,nspdbLmslNa,(const NSPLmsTapState *tapStPtr, NSPLmsDlyState *dlyStPtr,
                         const double *inSamps, double *outSamps, int numIters))
NSPAPI(void,nspzbLmslNa,(const NSPLmsTapState *tapStPtr, NSPLmsDlyState *dlyStPtr,
                         const DCplx *inSamps, DCplx *outSamps, int numIters))


NSPAPI(void,nspscbLmslNa,(const NSPLmsTapState *tapStPtr, NSPLmsDlyState *dlyStPtr,
                          const float *inSamps, SCplx *outSamps, int numIters))
NSPAPI(void,nspcsbLmslNa,(const NSPLmsTapState *tapStPtr, NSPLmsDlyState *dlyStPtr,
                          const SCplx *inSamps, SCplx *outSamps, int numIters))
NSPAPI(void,nspdzbLmslNa,(const NSPLmsTapState *tapStPtr, NSPLmsDlyState *dlyStPtr,
                          const double *inSamps,DCplx *outSamps, int numIters))
NSPAPI(void,nspzdbLmslNa,(const NSPLmsTapState *tapStPtr, NSPLmsDlyState *dlyStPtr,
                          const DCplx *inSamps, DCplx *outSamps, int numIters))

NSPAPI(void,nspsLmslGetTaps,(const NSPLmsTapState *tapStPtr,float  *outTaps))
NSPAPI(void,nspcLmslGetTaps,(const NSPLmsTapState *tapStPtr,SCplx  *outTaps))
NSPAPI(void,nspdLmslGetTaps,(const NSPLmsTapState *tapStPtr,double *outTaps))
NSPAPI(void,nspzLmslGetTaps,(const NSPLmsTapState *tapStPtr,DCplx  *outTaps))

NSPAPI(void,nspsLmslSetTaps,(const float  *inTaps,NSPLmsTapState *tapStPtr))
NSPAPI(void,nspcLmslSetTaps,(const SCplx  *inTaps,NSPLmsTapState *tapStPtr))
NSPAPI(void,nspdLmslSetTaps,(const double *inTaps,NSPLmsTapState *tapStPtr))
NSPAPI(void,nspzLmslSetTaps,(const DCplx  *inTaps,NSPLmsTapState *tapStPtr))

NSPAPI(void,nspsLmslGetDlyl,(const NSPLmsTapState *tapStPtr,
                             const NSPLmsDlyState *dlyStPtr,float  *outDlyl))
NSPAPI(void,nspcLmslGetDlyl,(const NSPLmsTapState *tapStPtr,
                             const NSPLmsDlyState *dlyStPtr,SCplx  *outDlyl))
NSPAPI(void,nspdLmslGetDlyl,(const NSPLmsTapState *tapStPtr,
                             const NSPLmsDlyState *dlyStPtr,double *outDlyl))
NSPAPI(void,nspzLmslGetDlyl,(const NSPLmsTapState *tapStPtr,
                             const NSPLmsDlyState *dlyStPtr,DCplx  *outDlyl))

NSPAPI(void,nspsLmslSetDlyl,(const NSPLmsTapState *tapStPtr,const float  *inDlyl,
                                   NSPLmsDlyState *dlyStPtr))
NSPAPI(void,nspcLmslSetDlyl,(const NSPLmsTapState *tapStPtr,const SCplx  *inDlyl,
                                   NSPLmsDlyState *dlyStPtr))
NSPAPI(void,nspdLmslSetDlyl,(const NSPLmsTapState *tapStPtr,const double *inDlyl,
                                   NSPLmsDlyState *dlyStPtr))
NSPAPI(void,nspzLmslSetDlyl,(const NSPLmsTapState *tapStPtr,const DCplx  *inDlyl,
                                   NSPLmsDlyState *dlyStPtr))


/* ////////////////////////////////////////////////////////////
   The wLmsl functions for data of short type.
   31-mar-97. New interface and new functions 
      o leak is not used,
      o adaptB is not used,
      o filter taps are float in the function call,
      o step is float in the function call,
      o calculation are done with fixed point data.
//////////////////////////////////////////////////////////// */

/* Note that adaptB is not used */
NSPAPI( void, nspwLmslInitDlyl,( NSPWLmsTapState *tapStPtr, short *dlyl,
   NSPWLmsDlyState *dlyStPtr ))

NSPAPI( void, nspwLmslSetDlyl,( const NSPWLmsTapState *tapStPtr,
   const short *inDlyl, NSPWLmsDlyState *dlyStPtr ))

NSPAPI( void, nspwLmslGetDlyl,( const NSPWLmsTapState *tapStPtr,
   const NSPWLmsDlyState *dlyStPtr, short *outDlyl ))

/* Note that leak is not used and taps are float */
NSPAPI( void, nspwLmslInit,( NSPLmsType lmsType, float *taps, int tapsLen,
   float step, int errDly, NSPWLmsTapState *tapStPtr ))

NSPAPI( void, nspwLmslSetTaps,( const float *inTaps, NSPWLmsTapState *tapStPtr ))

NSPAPI( void, nspwLmslGetTaps,( const NSPWLmsTapState *tapStPtr, float *outTaps ))

NSPAPI( short, nspwLmsl,( NSPWLmsTapState *tapStPtr, NSPWLmsDlyState *dlyStPtr, 
   short samp, short err ))

/* Note that step is float */
NSPAPI( float, nspwLmslGetStep, ( const NSPWLmsTapState *statePtr ))
NSPAPI( void, nspwLmslSetStep, ( float step, NSPWLmsTapState *statePtr ))


#endif /* _NSPLMS_H */
