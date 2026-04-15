/*M*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1995 Intel Corporation. All Rights Reserved.
//
//  PVCS: 
//      $Workfile:   NSPTONE.H  $
//      $Revision:   1.0  $
//      $Date:   Dec 16 1996 18:31:30  $
//      $Archive:   X:/nsp40_arc/INCLUDE/NSPTONE.H_v  $
//
//  Purpose: NSP Tone Generator. Declarator
*M*/

#if !defined (_NSPTONE_H) || defined (_OWN_BLDPCS)
#define _NSPTONE_H

/*--- Tone structures -----------------------------------------------------*/

#if !defined (_OWN_BLDPCS)

typedef struct _NSPSToneState {
   double cosBase;
   double cosCurr;
   double cosPrev;
   float  mag;
   float  rfreq;
   float  phase;
   char   isInit[4];
} NSPSToneState;

typedef struct _NSPCToneState {
   double cosBase;
   DCplx  cosCurr;
   DCplx  cosPrev;
   float  mag;
   float  rfreq;
   float  phase;
   char   isInit[4];
} NSPCToneState;

typedef struct _NSPDToneState {
   double cosBase;
   double cosCurr;
   double cosPrev;
   double mag;
   double rfreq;
   double phase;
   char   isInit[4];
} NSPDToneState;

typedef struct _NSPZToneState {
   double cosBase;
   DCplx  cosCurr;
   DCplx  cosPrev;
   double mag;
   double rfreq;
   double phase;
   char   isInit[4];
} NSPZToneState;

typedef struct _NSPWToneState {
   double dummy[32];
} NSPWToneState;

typedef struct _NSPVToneState {
   double dummy[32];
} NSPVToneState;

#endif

/*--- Initialization ------------------------------------------------------*/

NSPAPI(void,nspwToneInit,(float  rfreq, float  phase, short mag,
                          NSPWToneState* statePtr))

NSPAPI(void,nspvToneInit,(float  rfreq, float  phase, short mag,
                          NSPVToneState* statePtr))

NSPAPI(void,nspsToneInit,(float  rfreq, float  phase, float mag,
                          NSPSToneState* statePtr))

NSPAPI(void,nspcToneInit,(float  rfreq, float  phase, float mag,
                          NSPCToneState* statePtr))

NSPAPI(void,nspdToneInit,(double rfreq, double phase, double mag,
                          NSPDToneState* statePtr))

NSPAPI(void,nspzToneInit,(double rfreq, double phase, double mag,
                          NSPZToneState* statePtr))

/*--- Dot product tone functions ------------------------------------------*/

NSPAPI(short, nspwTone,(NSPWToneState* statePtr))
NSPAPI(WCplx, nspvTone,(NSPVToneState* statePtr))
NSPAPI(float, nspsTone,(NSPSToneState* statePtr))
NSPAPI(SCplx, nspcTone,(NSPCToneState* statePtr))
NSPAPI(double,nspdTone,(NSPDToneState* statePtr))
NSPAPI(DCplx, nspzTone,(NSPZToneState* statePtr))

/*--- Array product tone functions ----------------------------------------*/

NSPAPI(void,nspwbTone,(NSPWToneState* statePtr, short*  samps, int sampsLen))
NSPAPI(void,nspvbTone,(NSPVToneState* statePtr, WCplx*  samps, int sampsLen))
NSPAPI(void,nspsbTone,(NSPSToneState* statePtr, float*  samps, int sampsLen))
NSPAPI(void,nspcbTone,(NSPCToneState* statePtr, SCplx*  samps, int sampsLen))
NSPAPI(void,nspdbTone,(NSPDToneState* statePtr, double* samps, int sampsLen))
NSPAPI(void,nspzbTone,(NSPZToneState* statePtr, DCplx*  samps, int sampsLen))

#endif                                  /* _NSPTONE_H                      */
