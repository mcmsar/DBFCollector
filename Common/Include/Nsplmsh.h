/*M*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1995 Intel Corporation. All Rights Reserved.
//
//  PVCS: 
//      $Workfile:   NSPLMSH.H  $
//      $Revision:   1.0  $
//      $Date:   Dec 16 1996 18:31:28  $
//      $Archive:   X:/nsp40_arc/INCLUDE/NSPLMSH.H_v  $
//
//  Purpose: NSP  Adaptive FIR filter that uses the LMS algorithm
*M*/

#if !defined (_NSPLMSH_H)  || defined (_OWN_BLDPCS)
# define _NSPLMSH_H

# include "nsplmsl.h"

/* ------------------------------------------------------------------------*/

#if !defined (_OWN_BLDPCS)

typedef struct _NSPLmsState {
   NSPLmsTapState tapState;
   NSPLmsDlyState dlyState;
   union err {
      float sVal;
      double dVal;
      SCplx cVal;
      DCplx zVal;
   } err;
} NSPLmsState;

#endif

/* ------------------------------------------------------------------------*/

NSPAPI(void, nspsLmsInit, (NSPLmsType    lmsType,const float*  tapVals,
                           int           tapsLen,const float*  dlyVals,
                           float         step,         float   leak,
                           int           errDly, NSPLmsState*  statePtr))
NSPAPI(void, nspdLmsInit, (NSPLmsType    lmsType,const double* tapVals,
                           int           tapsLen,const double* dlyVals,
                           float         step,         float   leak,
                           int           errDly, NSPLmsState*  statePtr))
NSPAPI(void, nspcLmsInit, (NSPLmsType    lmsType,const SCplx*  tapVals,
                           int           tapsLen,const SCplx*  dlyVals,
                           float         step,         float   leak,
                           int           errDly, NSPLmsState*  statePtr))
NSPAPI(void, nspzLmsInit, (NSPLmsType    lmsType,const DCplx*  tapVals,
                           int           tapsLen,const DCplx*  dlyVals,
                           float         step,         float   leak, 
                           int           errDly, NSPLmsState*  statePtr))
NSPAPI(void, nspscLmsInit, (NSPLmsType   lmsType,const SCplx*  tapVals,
                            int          tapsLen,const float*  dlyVals,
                            float        step,         float   leak,
                            int          errDly, NSPLmsState*  statePtr))
NSPAPI(void, nspdzLmsInit, (NSPLmsType   lmsType,const DCplx*  tapVals,
                            int          tapsLen,const double* dlyVals,
                            float        step,         float   leak,
                            int          errDly, NSPLmsState*  statePtr))


NSPAPI(void, nspsLmsInitMr, (NSPLmsType lmsType,const float*       tapVals,
                             int        tapsLen,const float*       dlyVals,
                             float      step,         float        leak,
                             int        errDly,       int          downFactor,
                             int        downPhase,    NSPLmsState* statePtr))
NSPAPI(void, nspdLmsInitMr, (NSPLmsType lmsType,const double*      tapVals,
                             int        tapsLen,const double*      dlyVals,
                             float      step,         float        leak,
                             int        errDly,       int          downFactor,
                             int        downPhase,    NSPLmsState* statePtr))
NSPAPI(void, nspcLmsInitMr, (NSPLmsType lmsType,const SCplx*       tapVals,
                             int        tapsLen,const SCplx*       dlyVals,
                             float      step,         float        leak,
                             int        errDly,       int          downFactor,
                             int        downPhase,    NSPLmsState* statePtr))
NSPAPI(void, nspzLmsInitMr, (NSPLmsType lmsType,const DCplx*       tapVals,
                             int        tapsLen,const DCplx*       dlyVals,
                             float      step,         float        leak,
                             int        errDly,       int          downFactor,
                             int        downPhase,    NSPLmsState* statePtr))
NSPAPI(void, nspscLmsInitMr,(NSPLmsType lmsType,const SCplx*       tapVals,
                             int        tapsLen,const float*       dlyVals,
                             float      step,         float        leak,
                             int        errDly,       int          downFactor,
                             int        downPhase,    NSPLmsState* statePtr))
NSPAPI(void, nspdzLmsInitMr,(NSPLmsType lmsType,const DCplx*       tapVals,
                             int        tapsLen,const double*      dlyVals,
                             float      step,         float        leak,
                             int        errDly,       int          downFactor,
                             int        downPhase,    NSPLmsState* statePtr))

NSPAPI(void, nspLmsFree,(NSPLmsState* statePtr))

NSPAPI(float, nspsLms, (NSPLmsState* statePtr, float  samp, float  err))
NSPAPI(double,nspdLms, (NSPLmsState* statePtr, double samp, double err))
NSPAPI(SCplx, nspcLms, (NSPLmsState* statePtr, SCplx  samp, SCplx  err))
NSPAPI(DCplx, nspzLms, (NSPLmsState* statePtr, DCplx  samp, DCplx  err))
NSPAPI(SCplx, nspscLms,(NSPLmsState* statePtr, float  samp, SCplx  err))
NSPAPI(DCplx, nspdzLms,(NSPLmsState* statePtr, double samp, DCplx  err))

NSPAPI(float, nspsbLms, (NSPLmsState* statePtr,const float*  inSamps,float  err))
NSPAPI(double,nspdbLms, (NSPLmsState* statePtr,const double* inSamps,double err))
NSPAPI(SCplx, nspcbLms, (NSPLmsState* statePtr,const SCplx*  inSamps,SCplx  err))
NSPAPI(DCplx, nspzbLms, (NSPLmsState* statePtr,const DCplx*  inSamps,DCplx  err))
NSPAPI(SCplx, nspscbLms,(NSPLmsState* statePtr,const float*  inSamps,SCplx  err))
NSPAPI(DCplx, nspdzbLms,(NSPLmsState* statePtr,const double* inSamps,DCplx  err))

NSPAPI(void, nspsLmsGetTaps,(const NSPLmsState* statePtr, float*  outTaps))
NSPAPI(void, nspdLmsGetTaps,(const NSPLmsState* statePtr, double* outTaps))
NSPAPI(void, nspcLmsGetTaps,(const NSPLmsState* statePtr, SCplx*  outTaps))
NSPAPI(void, nspzLmsGetTaps,(const NSPLmsState* statePtr, DCplx*  outTaps))

NSPAPI(void, nspsLmsSetTaps,(const float*  inTaps, NSPLmsState* statePtr))
NSPAPI(void, nspdLmsSetTaps,(const double* inTaps, NSPLmsState* statePtr))
NSPAPI(void, nspcLmsSetTaps,(const SCplx*  inTaps, NSPLmsState* statePtr))
NSPAPI(void, nspzLmsSetTaps,(const DCplx*  inTaps, NSPLmsState* statePtr))

NSPAPI(void, nspsLmsGetDlyl,(const NSPLmsState* statePtr, float*  outDlyl))
NSPAPI(void, nspdLmsGetDlyl,(const NSPLmsState* statePtr, double* outDlyl))
NSPAPI(void, nspcLmsGetDlyl,(const NSPLmsState* statePtr, SCplx*  outDlyl))
NSPAPI(void, nspzLmsGetDlyl,(const NSPLmsState* statePtr, DCplx*  outDlyl))

NSPAPI(void, nspsLmsSetDlyl,(const float*  inDlyl, NSPLmsState* statePtr))
NSPAPI(void, nspdLmsSetDlyl,(const double* inDlyl, NSPLmsState* statePtr))
NSPAPI(void, nspcLmsSetDlyl,(const SCplx*  inDlyl, NSPLmsState* statePtr))
NSPAPI(void, nspzLmsSetDlyl,(const DCplx*  inDlyl, NSPLmsState* statePtr))

NSPAPI(float,nspsLmsGetStep,(const NSPLmsState* statePtr))
NSPAPI(float,nspsLmsGetLeak,(const NSPLmsState* statePtr))

NSPAPI(void, nspsLmsSetStep,(float step, NSPLmsState* statePtr))
NSPAPI(void, nspsLmsSetLeak,(float leak, NSPLmsState* statePtr))

NSPAPI(float, nspsLmsDes, (NSPLmsState* statePtr, float  samp, float  des))
NSPAPI(double,nspdLmsDes, (NSPLmsState* statePtr, double samp, double des))
NSPAPI(SCplx, nspcLmsDes, (NSPLmsState* statePtr, SCplx  samp, SCplx  des))
NSPAPI(DCplx, nspzLmsDes, (NSPLmsState* statePtr, DCplx  samp, DCplx  des))
NSPAPI(SCplx, nspscLmsDes,(NSPLmsState* statePtr, float  samp, SCplx  des))
NSPAPI(DCplx, nspdzLmsDes,(NSPLmsState* statePtr, double samp, DCplx  des))

NSPAPI(void,nspsbLmsDes, (NSPLmsState* statePtr, const float* inSamp,
                          const float* desSamps, float* outSamps, int numIters))
NSPAPI(void,nspdbLmsDes, (NSPLmsState* statePtr, const double* inSamp,
                          const double* desSamps,double* outSamps,int numIters))
NSPAPI(void,nspcbLmsDes, (NSPLmsState* statePtr, const SCplx* inSamp,
                          const SCplx* desSamps, SCplx* outSamps, int numIters))
NSPAPI(void,nspzbLmsDes, (NSPLmsState* statePtr, const DCplx* inSamp,
                          const DCplx* desSamps, DCplx* outSamps, int numIters))
NSPAPI(void,nspscbLmsDes,(NSPLmsState* statePtr, const float* inSamp,
                          const SCplx* desSamps, SCplx* outSamps, int numIters))
NSPAPI(void,nspdzbLmsDes,(NSPLmsState* statePtr, const double* inSamp,
                          const DCplx* desSamps, DCplx* outSamps, int numIters))

NSPAPI(float, nspsLmsGetErrVal,(const NSPLmsState* statePtr))
NSPAPI(double,nspdLmsGetErrVal,(const NSPLmsState* statePtr))
NSPAPI(SCplx, nspcLmsGetErrVal,(const NSPLmsState* statePtr))
NSPAPI(DCplx, nspzLmsGetErrVal,(const NSPLmsState* statePtr))

NSPAPI(void,nspsLmsSetErrVal,(float  err, NSPLmsState* statePtr))
NSPAPI(void,nspdLmsSetErrVal,(double err, NSPLmsState* statePtr))
NSPAPI(void,nspcLmsSetErrVal,(SCplx  err, NSPLmsState* statePtr))
NSPAPI(void,nspzLmsSetErrVal,(DCplx  err, NSPLmsState* statePtr))

#endif                                  /* _NSPLMSH_H                      */
