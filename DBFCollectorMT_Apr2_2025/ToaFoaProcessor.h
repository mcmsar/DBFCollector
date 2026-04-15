#pragma once

#include <windows.h>
#include <vector>
#include <string>

// Original project headers
#include "sigproc.h"
#include "emsclock.h"
#include "emsconst.h"
#include "emsvectr.h"
#include "emsDBF.h"
//#include "TrackDBFSatellites.h"
#include "emsDBFDataMgr.h"
#include "emsDBFtypes2.h"

#include "SigProcHelper.h"

class CToaFoaProcessor {
public:
    static EMS_RESULT InitializeTOAFOA(
        EMSTIME timestamp, 
        ULONG ulSatellites, 
        EMSDBFPASSRECORDS2* pPassSchedule, 
        float* pTemp1, 
        EMSCOMPLEX* pAcTemp1, 
        EMSCOMPLEX* pAcFFTBeacon, 
        EMSDBFTOAFOARECORD* pTOAFOA
    );

    static bool SatelliteTOAFOA(
        int isat, 
        EMSDBFPASSRECORDS2* pPassSchedule, 
        float* pTemp1, 
        EMSCOMPLEX* pAcTemp3, 
        EMSDBFTOAFOARECORD* pTOAFOA
    );

    static bool IdentifyTOAFOA(
        EMSTIME tm, 
        ULONG ulSatellites, 
        EMSDBFPASSRECORDS2* pPassSchedule, 
        CEMSQueue<DBFTrackingData>& qrefDBFBeamVectors, 
        EMSCOMPLEX* acDBFBeamVectors_In, 
        int* pBeamIDs, 
        EMSCOMPLEX* pAcDBFBeamVectors, 
        EMSDBFTOAFOARECORD* pTOAFOA
    );

private:
    // Helper stubs
    static void CopyData(float* dest, float value, int count);
    static bool CheckBit(char* buffer, int bitPos);
};