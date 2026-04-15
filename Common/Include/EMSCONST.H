/********************************************************************
*    Module:            emsconst.h
*    Process ID:
*    S/W Platforms:
*    H/W Platforms:
*    Compiler:
*    Description:
*
*    Usage:
*    Entry Point:
*    Input Files:
*    Output Files:
*    Comments:
*
*********************************************************************
*                  Copyright (c) 2001 by EMS Technologies, Inc.,
*                                        All rights reserved
*    This program is unpublished software and contains the trade secrets
*    and confidential information of EMS Technologies, Inc.  It may not be
* reproduced in whole or in part, in any form or by any means whatsoever
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

    Rev    Date            Auth    Changes
    ===    ====            ====    =======

    0.0    2001/03/22    rvw    start

********************************************************************/

#ifndef INC_EMSCONST
#define INC_EMSCONST

#include "emstypes.h"
#include "emstime.h"

// Mathematical constants
static const double     c_dPI                   = 3.14159265;
static const double     c_dTwoPI                = 2.0 * c_dPI;
static const double     c_dDegToRad             = c_dTwoPI / 360.0;
static const double     c_dRadToDeg             = 360.0 / c_dTwoPI;

// Physical constants
static const double     c_dSecondsPerDay        = 86400.0;       // secs
static const double     c_dMilliSecsPerSec      = 1e3;           // millisecs
static const double     c_dNanoSecsPerSec       = 1e9;           // nanosecs
static const INT64      c_iNanoSecsPerSec       = 1000000000;    // nanosecs
static const double     c_dVelocityOfLight      = 299792.5;      // km/sec
//static const double     c_dEarthKmRadius        = 6378.135;      // km
static const double     c_dEarthKmRadius        = 6378.137;      // km ( BIH )
static const double     c_dSiderealDaySeconds   = 86164.09054;   // secs
static const double     c_dSolarDaySeconds      = 86636.55536;   // secs
static const EMSRADIANS c_radEarthRotationRate  = 7.29211510e-5; // radians/second
//static const double     c_dEarthFlatteningTerm  = (1.0 / 298.26);
static const double     c_dEarthFlatteningTerm  = (1.0 / 298.2572); // BIH
static const double     c_dEarthEccentricity    = 0.00669438002;

static const double     c_dGravitationConstant  = 3.986005e5;    // km**3/sec**2
static const double     c_dJ2                   = -1082.616e-6;  // 2nd Zonal harmonic coefficient
static const double     c_dJ4                   = -1.65597e-6;   // 4th Zonal harmonic coefficient

// Signal constants
static const double     c_dCF406                = 406.025e6;     // Hz
static const double     c_dCBCCentreFreq121     = 121.5e6;       // Hz
static const double     c_dCBCCentreFreq243     = 243.0e6;       // Hz
static const double     c_dCBCCentreFreq406     = 406.05e6;      // Hz
static const double     c_dDownlinkCarrierFreq  = 1544.5e6;      // Hz

// SARP constants
static const double     c_dSarp01UsoFreq        = 4804434.0;     // USO frequency for SARP-0 and SARP-1 (Hz)
static const double     c_dSarp2UsoFreq         = 5203205.0;     // USO frequency for SARP-2 (Hz)
static const double     c_dSarp3UsoFreq         = 10000000.0;    // USO frequency for SARP-2 (Hz)
static const double     c_dSarpUsoFreqs[4]      = {              // USO frequencies for SARP (Hz)
                                                   c_dSarp01UsoFreq, // USO frequency for SARP-0 (Hz)
                                                   c_dSarp01UsoFreq, // USO frequency for SARP-1 (Hz)
                                                   c_dSarp2UsoFreq,  // USO frequency for SARP-2 (Hz)
                                                   c_dSarp3UsoFreq,  // USO frequency for SARP-3 (Hz)
                                                  };
static const double     c_dSarp0CounterMax      = 1048576.0;     // 2^20: SARP-0 counter maximum value
static const double     c_dSarp123CounterMax    = 8388608.0;     // 2^23: SARP-1, SARP-2, SARP-3 counter maximum value
static const double     c_dSarpCountersMax[4]   = {              // SARP counter maximum values
                                                   c_dSarp0CounterMax,   // SARP-0
                                                   c_dSarp123CounterMax, // SARP-1
                                                   c_dSarp123CounterMax, // SARP-2
                                                   c_dSarp123CounterMax, // SARP-3
                                                  };

static const double     c_dSarp01TickFactor     = 94208.0;       // Factor  to calculate SARP-0 and SARP-1 time per counter tick
static const double     c_dSarp2TickFactor      = 99360.0;       // Factor  to calculate SARP-2 time per counter tick
static const double     c_dSarp3TickFactor      = 200000.0;      // Factor  to calculate SARP-3 time per counter tick
static const double     c_dSarpTickFactors[4]      = {           // Factors to calculate SARP time per counter tick
                                                   c_dSarp01TickFactor, // SARP-0 
                                                   c_dSarp01TickFactor, // SARP-1 
                                                   c_dSarp2TickFactor,  // SARP-2 
                                                   c_dSarp3TickFactor,  // SARP-3 
                                                  };

static const double     c_dSarpCyclesInRollover[4] = {           // Number cycles in rollover period
                                                   c_dSarpTickFactors[0] * c_dSarpCountersMax[0], // SARP-0
                                                   c_dSarpTickFactors[1] * c_dSarpCountersMax[1], // SARP-1
                                                   c_dSarpTickFactors[2] * c_dSarpCountersMax[2], // SARP-2
                                                   c_dSarpTickFactors[3] * c_dSarpCountersMax[3], // SARP-3
                                                  };

static const double     c_dSarpOnBoardProcTime1 = 0.06;          // On-board processing time (secs)
static const double     c_dSarpOnBoardProcTime2 = 0.004;         // On-board processing time (secs)
static const double     c_dSarpOnBoardProcTime3 = 0.06;          // On-board processing time (secs)
static const double     c_dBeacToSatPropTime    = 0.21973;       // Beacon-to-satellite propagation time (secs)

static const int        c_n406BeaconMsgLength   = 18;            // 18 bytes

#endif // INC_EMSCONST
