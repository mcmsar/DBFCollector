/*M*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1995 Intel Corporation. All Rights Reserved.
//
//  PVCS: 
//      $Workfile: Nspfirl.h $
//      $Revision: 2 $
//      $Date: 19/05/97 9:12 $
//      $Archive: /gres/project/nsp/firl/Nspfirl.h $
//
//  Purpose: NSP Finite Impulse Response low level filter
//
//  History:
//       04-May-97, change w-flavor interface (use float taps now)
//
*M*/

#if !defined (_NSPFIRL_H)  || defined (_OWN_BLDPCS)
# define _NSPFIRL_H

/* ------------------------------------------------------------------------*/

#if !defined (_OWN_BLDPCS)

/* --- FIR low level filter structure -------------------------------------*/

#define FirLmsTapState \
   void *taps; \
   int   len; \
   int   upFactor; \
   int   upPhase; \
   int   downFactor; \
   int   downPhase; \
   int   isMultiRate; \
   int   isFilterMode

#define FirLmsDlyState \
   void *dlyl; \
   int   len; \
   int   isFilterMode

/* --- Finite impulse response filter -------------------------------------*/

 typedef struct _NSPFirTapState {
   FirLmsTapState;
   int tapsFactor;
 } NSPFirTapState;

/* --- Delay line of FIR low level filter ---------------------------------*/

 typedef struct _NSPFirDlyState {
   FirLmsDlyState;
 } NSPFirDlyState;

#endif

/* ------------------------------------------------------------------------*/
/*        FirlInit, FirlInitMr, FirlInitDlyl                               */
/*                                                                         */
/* Low level functions for cyclic FIR filtering via a tapped delay line.   */

NSPAPI(void,nspsFirlInit,(float  *taps, int tapsLen, NSPFirTapState *tapStPtr))
NSPAPI(void,nspdFirlInit,(double *taps, int tapsLen, NSPFirTapState *tapStPtr))
NSPAPI(void,nspcFirlInit,(SCplx  *taps, int tapsLen, NSPFirTapState *tapStPtr))
NSPAPI(void,nspzFirlInit,(DCplx  *taps, int tapsLen, NSPFirTapState *tapStPtr))
/* Serg. _OLD_INTERFACE
___API(void,nspwFirlInit,(short  *taps, int tapsLen, NSPFirTapState *tapStPtr))
*/
NSPAPI(void,nspwFirlInit,(float  *taps, int tapsLen, NSPFirTapState *tapStPtr))

NSPAPI(void,nspsFirlInitMr,(float  *taps, int tapsLen, int upFactor, int upPhase,
                    int downFactor, int downPhase, NSPFirTapState *tapStPtr))
NSPAPI(void,nspdFirlInitMr,(double *taps, int tapsLen, int upFactor, int upPhase,
                    int downFactor, int downPhase, NSPFirTapState *tapStPtr))
NSPAPI(void,nspcFirlInitMr,(SCplx  *taps, int tapsLen, int upFactor, int upPhase,
                    int downFactor, int downPhase, NSPFirTapState *tapStPtr))
NSPAPI(void,nspzFirlInitMr,(DCplx  *taps, int tapsLen, int upFactor, int upPhase,
                    int downFactor, int downPhase, NSPFirTapState *tapStPtr))
/* Serg. _OLD_INTERFACE
___API(void,nspwFirlInitMr,(short*taps, int tapsLen, int upFactor, int upPhase,
                    int downFactor, int downPhase, NSPFirTapState *tapStPtr))
*/
NSPAPI(void,nspwFirlInitMr,(float*taps, int tapsLen, int upFactor, int upPhase,
                    int downFactor, int downPhase, NSPFirTapState *tapStPtr))

NSPAPI(void,nspsFirlInitDlyl,(const NSPFirTapState *tapStPtr, float *dlyl,
                                    NSPFirDlyState *dlyStPtr))
NSPAPI(void,nspcFirlInitDlyl,(const NSPFirTapState *tapStPtr, SCplx *dlyl,
                                    NSPFirDlyState *dlyStPtr))
NSPAPI(void,nspdFirlInitDlyl,(const NSPFirTapState *tapStPtr, double *dlyl,
                                    NSPFirDlyState *dlyStPtr))
NSPAPI(void,nspzFirlInitDlyl,(const NSPFirTapState *tapStPtr, DCplx  *dlyl,
                                    NSPFirDlyState *dlyStPtr))
NSPAPI(void,nspwFirlInitDlyl,(const NSPFirTapState *tapStPtr, short  *dlyl,
                                    NSPFirDlyState *dlyStPtr))

/* ------------------------------------------------------------------------*/
/*        Firl, bFirl                                                      */
/*                                                                         */
/* Filter either a single sample or  block of samples through a low-level  */
/* FIR filter.                                                             */

NSPAPI(float, nspsFirl,(const NSPFirTapState *tapStPtr,
                              NSPFirDlyState *dlyStPtr, float  samp))
NSPAPI(SCplx, nspcFirl,(const NSPFirTapState *tapStPtr,
                              NSPFirDlyState *dlyStPtr, SCplx  samp))
NSPAPI(double,nspdFirl,(const NSPFirTapState *tapStPtr,
                              NSPFirDlyState *dlyStPtr, double samp))
NSPAPI(DCplx, nspzFirl,(const NSPFirTapState *tapStPtr,
                              NSPFirDlyState *dlyStPtr, DCplx  samp))
NSPAPI(short, nspwFirl,(const NSPFirTapState *tapStPtr,
                              NSPFirDlyState *dlyStPtr, short  samp,
                              int scaleMode, int *scaleFactorPtr))

NSPAPI(SCplx, nspscFirl,(const NSPFirTapState *tapStPtr,
                               NSPFirDlyState *dlyStPtr, float  samp))
NSPAPI(SCplx, nspcsFirl,(const NSPFirTapState *tapStPtr,
                               NSPFirDlyState *dlyStPtr, SCplx  samp))
NSPAPI(DCplx, nspdzFirl,(const NSPFirTapState *tapStPtr,
                               NSPFirDlyState *dlyStPtr, double samp))
NSPAPI(DCplx, nspzdFirl,(const NSPFirTapState *tapStPtr,
                               NSPFirDlyState *dlyStPtr, DCplx  samp))

NSPAPI(void,  nspsbFirl,(const NSPFirTapState *tapStPtr, NSPFirDlyState *dlyStPtr,
                         const float  *inSamps, float  *outSamps, int numIters))
NSPAPI(void,  nspcbFirl,(const NSPFirTapState *tapStPtr, NSPFirDlyState *dlyStPtr,
                         const SCplx  *inSamps, SCplx  *outSamps, int numIters))
NSPAPI(void,  nspdbFirl,(const NSPFirTapState *tapStPtr, NSPFirDlyState *dlyStPtr,
                         const double *inSamps, double *outSamps, int numIters))
NSPAPI(void,  nspzbFirl,(const NSPFirTapState *tapStPtr, NSPFirDlyState *dlyStPtr,
                         const DCplx  *inSamps, DCplx  *outSamps, int numIters))
NSPAPI(void,  nspwbFirl,(const NSPFirTapState *tapStPtr, NSPFirDlyState *dlyStPtr,
                         const short  *inSamps, short  *outSamps, int numIters,
                           int scaleMode, int *scaleFactorPtr))

NSPAPI(void,  nspscbFirl,(const NSPFirTapState *tapStPtr, NSPFirDlyState *dlyStPtr,
                          const float  *inSamps, SCplx *outSamps, int numIters))
NSPAPI(void,  nspcsbFirl,(const NSPFirTapState *tapStPtr, NSPFirDlyState *dlyStPtr,
                          const SCplx  *inSamps, SCplx *outSamps, int numIters))
NSPAPI(void,  nspdzbFirl,(const NSPFirTapState *tapStPtr, NSPFirDlyState *dlyStPtr,
                          const double *inSamps, DCplx *outSamps, int numIters))
NSPAPI(void,  nspzdbFirl,(const NSPFirTapState *tapStPtr, NSPFirDlyState *dlyStPtr,
                          const DCplx  *inSamps, DCplx *outSamps, int numIters))

/* ------------------------------------------------------------------------*/
/*        FirlGetTaps, FirlSetTaps                                         */
/*                                                                         */
/* Utility functions to get and set the tap coefficients of low-level FIR  */
/* filters.                                                                */

NSPAPI(void,nspsFirlGetTaps,(const NSPFirTapState *tapStPtr, float  *outTaps))
NSPAPI(void,nspcFirlGetTaps,(const NSPFirTapState *tapStPtr, SCplx  *outTaps))
NSPAPI(void,nspdFirlGetTaps,(const NSPFirTapState *tapStPtr, double *outTaps))
NSPAPI(void,nspzFirlGetTaps,(const NSPFirTapState *tapStPtr, DCplx  *outTaps))
/* Serg. _OLD_INTERFACE
___API(void,nspwFirlGetTaps,(const NSPFirTapState *tapStPtr, short  *outTaps))
*/
NSPAPI(void,nspwFirlGetTaps,(const NSPFirTapState *tapStPtr, float  *outTaps))

NSPAPI(void,nspsFirlSetTaps,(const float  *inTaps, NSPFirTapState *tapStPtr))
NSPAPI(void,nspcFirlSetTaps,(const SCplx  *inTaps, NSPFirTapState *tapStPtr))
NSPAPI(void,nspdFirlSetTaps,(const double *inTaps, NSPFirTapState *tapStPtr))
NSPAPI(void,nspzFirlSetTaps,(const DCplx  *inTaps, NSPFirTapState *tapStPtr))
/* Serg. _OLD_INTERFACE
___API(void,nspwFirlSetTaps,(const short  *inTaps, NSPFirTapState *tapStPtr))
*/
NSPAPI(void,nspwFirlSetTaps,(const float  *inTaps, NSPFirTapState *tapStPtr))

/* ------------------------------------------------------------------------*/
/*        FirlGetDlyl, FirlSetDlyl                                         */
/*                                                                         */
/* Utility functions to get and set  the delay line contents of low-level  */
/* FIR filters.                                                            */

NSPAPI(void,nspsFirlGetDlyl,(const NSPFirTapState *tapStPtr,
                             const NSPFirDlyState *dlyStPtr, float  *outDlyl))
NSPAPI(void,nspcFirlGetDlyl,(const NSPFirTapState *tapStPtr,
                             const NSPFirDlyState *dlyStPtr, SCplx  *outDlyl))
NSPAPI(void,nspdFirlGetDlyl,(const NSPFirTapState *tapStPtr,
                             const NSPFirDlyState *dlyStPtr, double *outDlyl))
NSPAPI(void,nspzFirlGetDlyl,(const NSPFirTapState *tapStPtr,
                             const NSPFirDlyState *dlyStPtr, DCplx  *outDlyl))
NSPAPI(void,nspwFirlGetDlyl,(const NSPFirTapState *tapStPtr,
                             const NSPFirDlyState *dlyStPtr, short  *outDlyl))


NSPAPI(void,nspsFirlSetDlyl,(const NSPFirTapState *tapStPtr, const float  *inDlyl,
                                   NSPFirDlyState *dlyStPtr))
NSPAPI(void,nspcFirlSetDlyl,(const NSPFirTapState *tapStPtr, const SCplx  *inDlyl,
                                   NSPFirDlyState *dlyStPtr))
NSPAPI(void,nspdFirlSetDlyl,(const NSPFirTapState *tapStPtr, const double *inDlyl,
                                   NSPFirDlyState *dlyStPtr))
NSPAPI(void,nspzFirlSetDlyl,(const NSPFirTapState *tapStPtr, const DCplx  *inDlyl,
                                   NSPFirDlyState *dlyStPtr))
NSPAPI(void,nspwFirlSetDlyl,(const NSPFirTapState *tapStPtr, const short  *inDlyl,
                                   NSPFirDlyState *dlyStPtr))

#endif                                  /* _NSPFIRL_H                      */
