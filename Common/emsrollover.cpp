
/***************************************************************************
 * Procedure: EMSCalculateTSarpRolloverDiff                                *
 * Purpose: This procedure rolls back a given SARP rollover time, given    *
 *          its frequency, to another rollover time, then calculates their *
 *          time difference.                                               *
 *                                                                         *
 * Input    dSarpCyclesInRollover                                          *
 *          fromTSarp    - from Sarp rollover time              (NanoSecs) *
 *          dFromSarpFC  - from Sarp frequency                  (Hz)       *
 *          toTSarp      - to   Sarp rollover time              (NanoSecs) *
 *          dToSarpFC    - to   Sarp frequency                  (Hz)       *
 * Output:  *pdTSarpDiff - time difference between fromTSarp    (Secs)     *
 *                         rolled back, and toTSarp                        *
 *          *pnCycles    - number cycles between rollover times            *
 *                                                                         *
 ***************************************************************************/

#include <windows.h>

#include "emstime.h"
#include "emsconst.h"
#include "emserror.h"
#include "emsrollover.h"

EMS_RESULT EMSCalculateTSarpRolloverDiff( double  dSarpCyclesInRollover, 
                         EMSTIME fromTSarp,       double dFromSarpFC,
                         EMSTIME toTSarp,         double dToSarpFC,
                         double  *pdTSarpDiff,    int    *pnRollovers )
{
    double   dFromRolloverPeriod, dToRolloverPeriod, dFromRollovers;
    EMSTIME  rolledOverTSarp;

    dToRolloverPeriod   = dSarpCyclesInRollover/dToSarpFC;
    dFromRolloverPeriod = dSarpCyclesInRollover/dFromSarpFC;
    dFromRollovers      = ((toTSarp.intTime - fromTSarp.intTime)/
                          c_dNanoSecsPerSec)/dFromRolloverPeriod;
    *pnRollovers        = (dFromRollovers < 0.0) ? 
                          (int)(dFromRollovers - 0.5) :
                          (int)(dFromRollovers + 0.5);
    if( *pnRollovers )      
    {
        rolledOverTSarp.intTime = fromTSarp.intTime + (INT64)(*pnRollovers*
                                     dFromRolloverPeriod*c_dNanoSecsPerSec);
        *pdTSarpDiff = ((rolledOverTSarp.intTime - toTSarp.intTime)/c_dNanoSecsPerSec);
    }
    else
    {
        *pnRollovers  = 1;
        *pdTSarpDiff  = (( fromTSarp.intTime  -  toTSarp.intTime)/c_dNanoSecsPerSec) - 
                         (dFromRolloverPeriod - dToRolloverPeriod);
    }

    return( EMS_OK );
}

