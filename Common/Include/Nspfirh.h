/*M*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1995 Intel Corporation. All Rights Reserved.
//
//  PVCS: 
//      $Workfile: Nspfirh.h $
//      $Revision: 1 $
//      $Date: 21/04/97 16:32 $
//      $Archive: /gres/project/nsp/firh/Nspfirh.h $
//
//  Purpose: NSP Finite Impulse Response high-level filter.
//
*M*/

#if !defined (_NSPFIRH_H) || defined (_OWN_BLDPCS)
#define _NSPFIRH_H

/* ------------------------------------------------------------------------*/

#if !defined (_OWN_BLDPCS)

/*=== FIR high-level ======================================================*/

typedef struct {
   int num;             /* section number                  */
   int len;             /* section taps length in use      */
   int xId;             /* section input data index        */
   int tId;             /* section taps index              */
} firSect;

typedef struct _NSPFirState {
   int   upFactor;      /* up                               */
   int   upPhase;       /*  parameters                      */
   int   downFactor;    /* down                             */
   int   downPhase;     /*  parameters                      */
   int   isMultiRate;   /* multi-rate mode flag             */
   void* isInit;        /* init flag                        */

   int   tapsLen;       /* number of filter taps            */
   int   tapsBlk;
   void* taps;          /* taps pointer in use              */

   int   dlylLen;       /* delay line length                */
   int   inpLen;        /* input buffer length              */
   int   useInp;        /* input buffer length used         */
   void* dlyl;          /* extended dilter delay line       */
   void* dlylLimit;     /* delay line buffer end pointer    */ 
   void* useDlyl;       /* delay line pointer in use        */ 

   firSect* sect;       /* FIR sections                     */

   int   tapsFactor;    /* taps scale factor                */
   int   utapsLen;      /* number of filter taps (user def) */
} NSPFirState;

#endif

/*-------------------------------------------------------------------------*/
/* nsp?FirInit(), nsp?FirInitMr()                                          */
/* nspFirFree()                                                            */
/*                                                                         */
/* Initialize a finite impulse response high-level (FIRH) filter           */

NSPAPI(void,nspsFirInit, (const float *tapVals, int          tapsLen,
                          const float *dlyVals, NSPFirState *statePtr))
NSPAPI(void,nspcFirInit, (const SCplx *tapVals, int          tapsLen,
                          const SCplx *dlyVals, NSPFirState *statePtr))
NSPAPI(void,nspscFirInit,(const SCplx *tapVals, int          tapsLen,
                          const float *dlyVals, NSPFirState *statePtr))
NSPAPI(void,nspcsFirInit,(const float *tapVals, int          tapsLen,
                          const SCplx *dlyVals, NSPFirState *statePtr))

NSPAPI(void,nspdFirInit, (const double *tapVals, int          tapsLen,
                          const double *dlyVals, NSPFirState *statePtr))
NSPAPI(void,nspzFirInit, (const DCplx  *tapVals, int          tapsLen,
                          const DCplx  *dlyVals, NSPFirState *statePtr))
NSPAPI(void,nspdzFirInit,(const DCplx  *tapVals, int          tapsLen,
                          const double *dlyVals, NSPFirState *statePtr))
NSPAPI(void,nspzdFirInit,(const double *tapVals, int          tapsLen,
                          const DCplx  *dlyVals, NSPFirState *statePtr))

NSPAPI(void,nspwFirInit, (const float* tapVals,  int          tapsLen,
                          const short* dlyVals,  NSPFirState *statePtr))

NSPAPI(void,nspsFirInitMr, (const float *tapVals,   int tapsLen,
                            const float *dlyVals,   int upFactor, int upPhase,
                                  int    downFactor,int downPhase,
                            NSPFirState *statePtr))
NSPAPI(void,nspcFirInitMr, (const SCplx *tapVals,   int tapsLen,
                            const SCplx *dlyVals,   int upFactor, int upPhase,
                                  int    downFactor,int downPhase,
                            NSPFirState *statePtr))
NSPAPI(void,nspscFirInitMr,(const SCplx *tapVals,   int tapsLen,
                            const float *dlyVals,   int upFactor, int upPhase,
                                  int    downFactor,int downPhase,
                            NSPFirState *statePtr))
NSPAPI(void,nspcsFirInitMr,(const float *tapVals,   int tapsLen,
                            const SCplx *dlyVals,   int upFactor, int upPhase,
                                  int    downFactor,int downPhase,
                            NSPFirState *statePtr))

NSPAPI(void,nspdFirInitMr, (const double *tapVals,   int tapsLen,
                            const double *dlyVals,   int upFactor, int upPhase,
                                  int     downFactor,int downPhase,
                            NSPFirState  *statePtr))
NSPAPI(void,nspzFirInitMr, (const DCplx  *tapVals,   int tapsLen,
                            const DCplx  *dlyVals,   int upFactor, int upPhase,
                                  int     downFactor,int downPhase,
                            NSPFirState  *statePtr))
NSPAPI(void,nspdzFirInitMr,(const DCplx  *tapVals,   int tapsLen,
                            const double *dlyVals,   int upFactor, int upPhase,
                                  int     downFactor,int downPhase,
                            NSPFirState  *statePtr))
NSPAPI(void,nspzdFirInitMr,(const double *tapVals,   int tapsLen,
                            const DCplx  *dlyVals,   int upFactor, int upPhase,
                                  int     downFactor,int downPhase,
                            NSPFirState *statePtr))

NSPAPI(void,nspwFirInitMr,(const float* tapVals, int tapsLen,
                           const short* dlyVals, int upFactor, int upPhase,
                           int    downFactor, int downPhase,
                           NSPFirState *statePtr))

NSPAPI(void,nspFirFree,(NSPFirState *statePtr))


/*-------------------------------------------------------------------------*/
/* nsp?Fir(), nsp?bFir()                                                   */
/*                                                                         */
/* Dot and block product FIRH filtering                                    */

NSPAPI(float,nspsFir, (NSPFirState *statePtr,float samp))
NSPAPI(SCplx,nspcFir, (NSPFirState *statePtr,SCplx samp))
NSPAPI(SCplx,nspscFir,(NSPFirState *statePtr,float samp))
NSPAPI(SCplx,nspcsFir,(NSPFirState *statePtr,SCplx samp))

NSPAPI(double,nspdFir,(NSPFirState *statePtr,double samp))
NSPAPI(DCplx,nspzFir, (NSPFirState *statePtr,DCplx  samp))
NSPAPI(DCplx,nspdzFir,(NSPFirState *statePtr,double samp))
NSPAPI(DCplx,nspzdFir,(NSPFirState *statePtr,DCplx  samp))

NSPAPI(short,nspwFir, (NSPFirState *statePtr,short samp,
                       int sMode, int* sFctPtr))

NSPAPI(void,nspsbFir, (NSPFirState *statePtr,const float *inSamps,
                       float       *outSamps,      int    numIters))
NSPAPI(void,nspcbFir, (NSPFirState *statePtr,const SCplx *inSamps,
                       SCplx       *outSamps,      int    numIters))
NSPAPI(void,nspscbFir,(NSPFirState *statePtr,const float *inSamps,
                       SCplx       *outSamps,      int    numIters))
NSPAPI(void,nspcsbFir,(NSPFirState *statePtr,const SCplx *inSamps,
                       SCplx       *outSamps,      int    numIters))

NSPAPI(void,nspdbFir, (NSPFirState *statePtr,const double *inSamps,
                       double      *outSamps,      int     numIters))
NSPAPI(void,nspzbFir, (NSPFirState *statePtr,const DCplx  *inSamps,
                       DCplx       *outSamps,      int     numIters))
NSPAPI(void,nspdzbFir,(NSPFirState *statePtr,const double *inSamps,
                       DCplx       *outSamps,      int     numIters))
NSPAPI(void,nspzdbFir,(NSPFirState *statePtr,const DCplx  *inSamps,
                       DCplx       *outSamps,      int     numIters))

NSPAPI(void,nspwbFir, (NSPFirState *statePtr,const short  *inSamps,
                       short       *outSamps,      int     numIters,
                       int sMode, int* sFctPtr))


/*-------------------------------------------------------------------------*/
/* nsp?FirGetTaps(), nsp?FirSetTaps()                                      */
/*                                                                         */
/* Utility functions to get and set the FIR taps coefficients              */

NSPAPI(void,nspsFirGetTaps,(const NSPFirState *statePtr,float  *outTaps))
NSPAPI(void,nspcFirGetTaps,(const NSPFirState *statePtr,SCplx  *outTaps))
NSPAPI(void,nspdFirGetTaps,(const NSPFirState *statePtr,double *outTaps))
NSPAPI(void,nspzFirGetTaps,(const NSPFirState *statePtr,DCplx  *outTaps))

NSPAPI(void,nspwFirGetTaps,(const NSPFirState *statePtr,float* outTaps))

NSPAPI(void,nspsFirSetTaps,(const float  *inTaps,NSPFirState *statePtr))
NSPAPI(void,nspcFirSetTaps,(const SCplx  *inTaps,NSPFirState *statePtr))
NSPAPI(void,nspdFirSetTaps,(const double *inTaps,NSPFirState *statePtr))
NSPAPI(void,nspzFirSetTaps,(const DCplx  *inTaps,NSPFirState *statePtr))

NSPAPI(void,nspwFirSetTaps,(const float* inTaps,NSPFirState *statePtr))


/*-------------------------------------------------------------------------*/
/* nsp?FirGetDlyl(), nsp?FirSetDlyl()                                      */
/*                                                                         */
/* Utility functions to get and set the FIR delay line contents            */

NSPAPI(void,nspsFirGetDlyl,(const NSPFirState *statePtr,float  *outDlyl))
NSPAPI(void,nspcFirGetDlyl,(const NSPFirState *statePtr,SCplx  *outDlyl))
NSPAPI(void,nspdFirGetDlyl,(const NSPFirState *statePtr,double *outDlyl))
NSPAPI(void,nspzFirGetDlyl,(const NSPFirState *statePtr,DCplx  *outDlyl))

NSPAPI(void,nspwFirGetDlyl,(const NSPFirState *statePtr,short* outDlyl))

NSPAPI(void,nspsFirSetDlyl,(const float  *inDlyl,NSPFirState *statePtr))
NSPAPI(void,nspcFirSetDlyl,(const SCplx  *inDlyl,NSPFirState *statePtr))
NSPAPI(void,nspdFirSetDlyl,(const double *inDlyl,NSPFirState *statePtr))
NSPAPI(void,nspzFirSetDlyl,(const DCplx  *inDlyl,NSPFirState *statePtr))

NSPAPI(void,nspwFirSetDlyl,(const short* inDlyl,NSPFirState *statePtr))


#endif                                  /* _NSPFIRH_H                      */

