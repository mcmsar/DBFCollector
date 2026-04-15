/*M*
//
//               INTEL CORPORATION PROPRIETARY INFORMATION
//  This software is supplied under the terms of a license agreement or
//  nondisclosure agreement with Intel Corporation and may not be copied
//  or disclosed except in accordance with the terms of that agreement.
//        Copyright (c) 1995 Intel Corporation. All Rights Reserved.
//
//  PVCS: 
//      $Workfile:   NSPRAND.H  $
//      $Revision:   1.0  $
//      $Date:   Dec 16 1996 18:31:30  $
//      $Archive:   X:/nsp40_arc/INCLUDE/NSPRAND.H_v  $
//
*/

#if !defined (_NSPRAND_H) || defined (_OWN_BLDPCS)
# define _NSPRAND_H

/*-------------------------------------------------------------------------*/

#if !defined (_OWN_BLDPCS)

typedef struct NSPSRandUniState {
   float        low,muler;             /* Lower value and scale multiplier */
   unsigned int seed2,carry;           /* Variables of the algorithm       */
   unsigned int seed1[3];              /* Variables of the algorithm       */
   int          quickSeed;
} NSPSRandUniState;

typedef struct NSPDRandUniState {
   double       low,muler;
   unsigned int seed2,carry;
   unsigned int seed1[3];
   int          quickSeed;
} NSPDRandUniState;

#define XBUFLEN   32

/* A new state structure of the pseudo random numbers 
   generator has two seed values (m_seed) now. Generator 
   based on multiplication uses m_seed values. Generator 
   based on subtraction uses d_seed and carry.
*/

typedef struct NSPWRandUniState {
   float        low,muler;
   int          center, pwr2;
   unsigned int m_seed[2];                       
   unsigned int d_seed[3];                       
   unsigned int carry;
   int          quickSeed;
   int          current;
   short        xbuf[XBUFLEN];
} NSPWRandUniState;

typedef struct NSPSRandUniState NSPCRandUniState;
typedef struct NSPDRandUniState NSPZRandUniState;
typedef struct NSPWRandUniState NSPVRandUniState;


typedef struct NSPSRandGausState {
   float        mean,stDev;            /* Mean and standard deviation values */
   float        extraValue;            /* Value computed early               */
   int          useExtra;              /* Flag to use extra value            */
   unsigned int seed2,carry;           /* Variables of the algorithm         */
   unsigned int seed1[3];              /* Variables of the algorithm         */
   int          quickSeed;
} NSPSRandGausState;

typedef struct NSPDRandGausState {
   double       mean,stDev;
   double       extraValue;
   int          useExtra;
   unsigned int seed2,carry;
   unsigned int seed1[3];
   int          quickSeed;
} NSPDRandGausState;

typedef struct NSPWRandGausState {
   int          useExtra;
   unsigned int seed2,carry;
   unsigned int seed1[3];
   short        mean,stDev;
   short        extraValue;
   int          quickSeed;
} NSPWRandGausState;

typedef struct NSPSRandGausState NSPCRandGausState;
typedef struct NSPDRandGausState NSPZRandGausState;
typedef struct NSPWRandGausState NSPVRandGausState;

#endif

/*-------------------------------------------------------------------------*/
/*
   Uniform distribution.
   Algorithm by G.Marsaglia and A.Zaman (Computers in Physics, vol.8,
   #1, 1994, 117) are used to build generator of uniformly distributed
   random numbers.
*/

NSPAPI(void,nspsRandUniInit,(float seed, float  low, float  high,
                             NSPSRandUniState  *statePtr))
NSPAPI(void,nspcRandUniInit,(float seed, float  low, float  high,
                             NSPCRandUniState  *statePtr))
NSPAPI(void,nspdRandUniInit,(double seed,double low, double high,
                             NSPDRandUniState  *statePtr))
NSPAPI(void,nspzRandUniInit,(double seed,double low, double high,
                             NSPZRandUniState  *statePtr))
NSPAPI(void,nspwRandUniInit,(unsigned int seed,short low,short high,
                             NSPWRandUniState *statePtr))
NSPAPI(void,nspvRandUniInit,(unsigned int seed,short low,short high,
                             NSPVRandUniState *statePtr))

NSPAPI(float, nspsRandUni,(NSPSRandUniState *statePtr))
NSPAPI(SCplx, nspcRandUni,(NSPCRandUniState *statePtr))
NSPAPI(double,nspdRandUni,(NSPDRandUniState *statePtr))
NSPAPI(DCplx, nspzRandUni,(NSPZRandUniState *statePtr))
NSPAPI(short, nspwRandUni,(NSPWRandUniState *statePtr))
NSPAPI(WCplx, nspvRandUni,(NSPVRandUniState *statePtr))

NSPAPI(void,nspsbRandUni,(NSPSRandUniState  *statePtr,
                          float  *samps, int sampsLen))
NSPAPI(void,nspcbRandUni,(NSPCRandUniState  *statePtr,
                          SCplx  *samps, int sampsLen))
NSPAPI(void,nspdbRandUni,(NSPDRandUniState  *statePtr,
                          double *samps, int sampsLen))
NSPAPI(void,nspzbRandUni,(NSPZRandUniState  *statePtr,
                          DCplx  *samps, int sampsLen))
NSPAPI(void,nspwbRandUni,(NSPWRandUniState  *statePtr,
                          short  *samps, int sampsLen))
NSPAPI(void,nspvbRandUni,(NSPVRandUniState  *statePtr,
                          WCplx  *samps, int sampsLen))

/*
   Normal distribution.
   Algorithm by G.Box and M.Muller and by G.Marsaglia (Reference:
   D.Knuth. The Art of Computer Programming. vol.2, 1969) are used
   to build generator of normally distributed random numbers.
*/


NSPAPI(void,nspsRandGausInit,(float seed,float mean,float stDev,
                              NSPSRandGausState *statePtr))
NSPAPI(void,nspcRandGausInit,(float seed,float mean,float stDev,
                              NSPCRandGausState *statePtr))
NSPAPI(void,nspdRandGausInit,(double seed,double mean,double stDev,
                              NSPDRandGausState *statePtr))
NSPAPI(void,nspzRandGausInit,(double seed,double mean,double stDev,
                              NSPZRandGausState *statePtr))
NSPAPI(void,nspwRandGausInit,(short seed,short mean,short stDev,
                              NSPWRandGausState *statePtr))
NSPAPI(void,nspvRandGausInit,(short seed,short mean,short stDev,
                              NSPVRandGausState *statePtr))

NSPAPI(float, nspsRandGaus,(NSPSRandGausState *statePtr))
NSPAPI(SCplx, nspcRandGaus,(NSPCRandGausState *statePtr))
NSPAPI(double,nspdRandGaus,(NSPDRandGausState *statePtr))
NSPAPI(DCplx, nspzRandGaus,(NSPZRandGausState *statePtr))
NSPAPI(short, nspwRandGaus,(NSPWRandGausState *statePtr))
NSPAPI(WCplx, nspvRandGaus,(NSPVRandGausState *statePtr))

NSPAPI(void,nspsbRandGaus,(NSPSRandGausState *statePtr,
                           float *samps,  int sampsLen))
NSPAPI(void,nspcbRandGaus,(NSPCRandGausState *statePtr,
                           SCplx *samps,  int sampsLen))
NSPAPI(void,nspdbRandGaus,(NSPDRandGausState *statePtr,
                           double *samps, int sampsLen))
NSPAPI(void,nspzbRandGaus,(NSPZRandGausState *statePtr,
                           DCplx *samps,  int sampsLen))
NSPAPI(void,nspwbRandGaus,(NSPWRandGausState *statePtr,
                           short *samps,  int sampsLen))
NSPAPI(void,nspvbRandGaus,(NSPVRandGausState *statePtr,
                           WCplx *samps,  int sampsLen))

#endif                                  /* _NSPRAND_H                      */
