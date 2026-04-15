/*M*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//       Copyright (c) 1994 Intel Corporation. All Rights Reserved.
//
//  PVCS: 
//      $Workfile:   NSPTRNGL.H  $
//      $Revision:   1.0  $
//      $Date:   Dec 16 1996 18:31:32  $
//      $Archive:   X:/nsp40_arc/INCLUDE/NSPTRNGL.H_v  $
//
//  Purpose: Generating of signals with triangle wave form.
//           Provides samples of a triangle of arbitrary frequency,
//           phase, magnitude, and asymmetry.
//
//           0 =< phase < 2PI,  -PI < asym < PI,
//           mag > 0, 0 =< rfrec < 0.5
//
//           asym = 0       => Triangle is symmetric (old version)
//           asym = -PI+eps => Triangle with sheer back (0<eps)
//           asym =  PI-eps => Triangle with sheer front-fore
//
//           Like (cos) tone functions the triangle has period equal 2PI
//           Triangle phase is given in radians.
//
*M*/

#if !defined (_NSPTRNGL_H) || defined (_OWN_BLDPCS)
#define _NSPTRNGL_H

/*--- Triangle structures -------------------------------------------------*/

#if !defined (_OWN_BLDPCS)

 typedef struct _NSPWTrnglState {
   float mag;
   float step;
   float step1;
   float step2;
   float st12;
   float st21;
   float shft1;
   float shft2;
   float delta1;
   float delta2;
   float last;
 } NSPWTrnglState;

 typedef struct _NSPVTrnglState {
   float mag;
   SCplx step;
   float step1;
   float step2;
   float st12;
   float st21;
   float shft1;
   float shft2;
   float delta1;
   float delta2;
   SCplx last;
 } NSPVTrnglState;

 typedef struct _NSPITrnglState {
   double mag;
   double step;
   double step1;
   double step2;
   double st12;
   double st21;
   double shft1;
   double shft2;
   double delta1;
   double delta2;
   double last;
 } NSPITrnglState;

 typedef struct _NSPJTrnglState {
   double mag;
   DCplx step;
   double step1;
   double step2;
   double st12;
   double st21;
   double shft1;
   double shft2;
   double delta1;
   double delta2;
   DCplx last;
 } NSPJTrnglState;

 typedef struct _NSPSTrnglState {
   float mag;
   float step;
   float step1;
   float step2;
   float st12;
   float st21;
   float shft1;
   float shft2;
   float delta1;
   float delta2;
   float last;
 } NSPSTrnglState;

 typedef struct _NSPCTrnglState {
   float mag;
   SCplx step;
   float step1;
   float step2;
   float st12;
   float st21;
   float shft1;
   float shft2;
   float delta1;
   float delta2;
   SCplx last;
 } NSPCTrnglState;

 typedef struct _NSPDTrnglState {
   double mag;
   double step;
   double step1;
   double step2;
   double st12;
   double st21;
   double shft1;
   double shft2;
   double delta1;
   double delta2;
   double last;
 } NSPDTrnglState;

 typedef struct _NSPZTrnglState {
   double mag;
   DCplx  step;
   double step1;
   double step2;
   double st12;
   double st21;
   double shft1;
   double shft2;
   double delta1;
   double delta2;
   DCplx  last;
 } NSPZTrnglState;

#endif

/*--- Triangle initialization ---------------------------------------------*/

NSPAPI(void,nspwTrnglInit,(float rfrq,  float  phase, short  mag,
                           float asym,  NSPWTrnglState      *stPtr))
NSPAPI(void,nspvTrnglInit,(float  rfrq, float  phase, short  mag,
                           float asym,  NSPVTrnglState      *stPtr))
NSPAPI(void,nspsTrnglInit,(float rfrq,  float  phase, float  mag,
                           float asym,  NSPSTrnglState      *stPtr))
NSPAPI(void,nspdTrnglInit,(double rfrq, double phase, double mag,
                           double asym, NSPDTrnglState      *stPtr))
NSPAPI(void,nspcTrnglInit,(float  rfrq, float  phase, float  mag,
                           float asym,  NSPCTrnglState      *stPtr))
NSPAPI(void,nspzTrnglInit,(double rfrq, double phase, double mag,
                           double asym, NSPZTrnglState      *stPtr))

/*--- Single-Sample-Generating triangle functions -------------------------*/

NSPAPI(short, nspwTrngl,(NSPWTrnglState *statePtr))
NSPAPI(WCplx, nspvTrngl,(NSPVTrnglState *statePtr))
NSPAPI(float, nspsTrngl,(NSPSTrnglState *statePtr))
NSPAPI(double,nspdTrngl,(NSPDTrnglState *statePtr))
NSPAPI(SCplx, nspcTrngl,(NSPCTrnglState *statePtr))
NSPAPI(DCplx, nspzTrngl,(NSPZTrnglState *statePtr))

/*--- Block-of-Samples-Generating triangle functions ----------------------*/

NSPAPI(void,nspwbTrngl,(NSPWTrnglState *statePtr, short  *samps, int sampsLen))
NSPAPI(void,nspvbTrngl,(NSPVTrnglState *statePtr, WCplx  *samps, int sampsLen))
NSPAPI(void,nspsbTrngl,(NSPSTrnglState *statePtr, float  *samps, int sampsLen))
NSPAPI(void,nspdbTrngl,(NSPDTrnglState *statePtr, double *samps, int sampsLen))
NSPAPI(void,nspcbTrngl,(NSPCTrnglState *statePtr, SCplx  *samps, int sampsLen))
NSPAPI(void,nspzbTrngl,(NSPZTrnglState *statePtr, DCplx  *samps, int sampsLen))

#endif                                  /* _NSPTRNGL_H                     */
