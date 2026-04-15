/*M*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1995 Intel Corporation. All Rights Reserved.
//
//  PVCS: 
//      $Workfile:   NSPGRTZL.H  $
//      $Revision:   1.0  $
//      $Date:   Dec 16 1996 18:31:26  $
//      $Archive:   X:/nsp40_arc/INCLUDE/NSPGRTZL.H_v  $
//
//  Purpose: NSP Single Frequency DFT (Goertzel)
*M*/

#if !defined (_NSPGRTZL_H)  || defined (_OWN_BLDPCS)
# define _NSPGRTZL_H

/* ------------------------------------------------------------------------*/

#if !defined (_OWN_BLDPCS)

/* Single Frequency DFT structures.                                        */

typedef struct _NSPSGoertzState {
    float freq; 
    float cosV; 
    float sinV; 
    float cpcV; 
    float prev2re;
    float prev2im;
    float prev1re;
    float prev1im;
} NSPSGoertzState;

typedef NSPSGoertzState NSPCGoertzState;

typedef struct _NSPDGoertzState {
    double freq; 
    double cosV; 
    double sinV; 
    double cpcV; 
    double prev2re;
    double prev2im;
    double prev1re;
    double prev1im;
} NSPDGoertzState;

typedef NSPDGoertzState NSPZGoertzState;

#endif

/* ------------------------------------------------------------------------*/
/*        GoertzInit                                                       */
/*                                                                         */
/* Initializes the coefficients and zeros the delay line.                  */

NSPAPI(void,nspsGoertzInit,(float  freq, NSPSGoertzState *stPtr))
NSPAPI(void,nspcGoertzInit,(float  freq, NSPCGoertzState *stPtr))
NSPAPI(void,nspdGoertzInit,(double freq, NSPDGoertzState *stPtr))
NSPAPI(void,nspzGoertzInit,(double freq, NSPZGoertzState *stPtr))

/* ------------------------------------------------------------------------*/
/*        GoertzReset                                                      */
/*                                                                         */
/* Zeros the delay line.                                                   */

NSPAPI(void,nspsGoertzReset,(NSPSGoertzState *stPtr))
NSPAPI(void,nspcGoertzReset,(NSPCGoertzState *stPtr))
NSPAPI(void,nspdGoertzReset,(NSPDGoertzState *stPtr))
NSPAPI(void,nspzGoertzReset,(NSPZGoertzState *stPtr))

/* ------------------------------------------------------------------------*/
/*        Goertz                                                           */
/*                                                                         */
/* Single Frequency DFT (Goertzel algorithm)                               */

NSPAPI(SCplx,nspsGoertz,(NSPSGoertzState *stPtr, float  sample))
NSPAPI(SCplx,nspcGoertz,(NSPCGoertzState *stPtr, SCplx  sample))
NSPAPI(DCplx,nspdGoertz,(NSPDGoertzState *stPtr, double sample))
NSPAPI(DCplx,nspzGoertz,(NSPZGoertzState *stPtr, DCplx  sample))

NSPAPI(SCplx,nspsbGoertz,(NSPSGoertzState *stPtr,const float  *inSamps,int len))
NSPAPI(SCplx,nspcbGoertz,(NSPCGoertzState *stPtr,const SCplx  *inSamps,int len))
NSPAPI(DCplx,nspdbGoertz,(NSPDGoertzState *stPtr,const double *inSamps,int len))
NSPAPI(DCplx,nspzbGoertz,(NSPZGoertzState *stPtr,const DCplx  *inSamps,int len))

#endif                                  /* _NSPGRTZL_H                      */
