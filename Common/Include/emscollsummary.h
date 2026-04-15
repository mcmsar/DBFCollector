/******************************************************************** 
*       Module:                 emscollsummary.h
*       Process ID:
*       S/W Platforms:
*       H/W Platforms:
*       Compiler:
*       Description:    Data Collection Summary (GeoLut)
*
*       Usage:
*       Entry Point:
*       Input Files:
*       Output Files:
*       Comments:
*
*********************************************************************
*          Copyright (c) 2002 by EMS Technologies Canada, Ltd. Ottawa ON
*                                                                               All rights reserved
*       This program is unpublished software and contains the trade secrets
*       and confidential information of EMS Technologies Canada, Ltd.  It may 
* not be reproduced in whole or in part, in any form or by any means 
* whatsoever without the express written permission of EMS Technologies 
* Canada, Ltd.
********************************************************************/

/*******************************************************************

  Revision Record

        Rev     Date                    Auth    Changes
        ===     ====                    ====    =======

        0.0     2002/12/20              fjp     start

********************************************************************/
#ifndef INC_EMSCOLLECTIONSUMMARY
#define INC_EMSCOLLECTIONSUMMARY

#include "emstypes.h"

typedef struct _tagEMSCOLLECTIONSUMMARY         // corresponds to SIT662A
{
                                                // SIT662A line 1 ----------------------------
   ULONG                   ulSatID;             // satellite to perform the manoeuvre (MF#6)
   EMSTIME                 startTime;           // start time of collection period (MF#602)
   EMSTIME                 endTime;             // end time of collection period (MF#603)
                                                // SIT662A line 2 ----------------------------
   WORD                    wDurationScheduled;  // scheduled duration of data collection (MF#604)
   WORD                    wDurationActual;     // scheduled duration of data collection (MF#629)
   WORD                    wGoodSignal;         // percentage of good signal for duration (reword this?)
   WORD                    wBeaconIDs;          // unique beacon IDs detected during collection (MF#10B)
   WORD                    wBeaconBursts;       // number of beacon bursts detected during collection (MF#636)
   WORD                    wSolutions;          // number of integrated solutions produced during collection (MF#601)
   WORD                    wAlarms;             // number of alarm messages generated during collection (MF#634)
   WORD                    wWarnings;           // number of warning messages generated during collection (MF#635)

} EMSCOLLECTIONSUMMARY, *LPEMSCOLLECTIONSUMMARY;

#endif // INC_EMSCOLLECTIONSUMMARY

