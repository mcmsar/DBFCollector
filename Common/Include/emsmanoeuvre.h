/******************************************************************** 
*       Module:                 emsmanoeuvre.h
*       Process ID:
*       S/W Platforms:
*       H/W Platforms:
*       Compiler:
*       Description:    EMS manoeuvre types (describes MetOps manoeuvres)
*                                               
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

        0.0     2002/12/12              fjp     start

********************************************************************/
#ifndef INC_EMSMANOEUVRE
#define INC_EMSMANOEUVRE

#include "emstypes.h"

//typedef enum _tagEMSMANOEUVRETYPE
//{
//         MANOEUVRETYPE_IP = 1,      // "in-plane" manoeuvre
//         MANOEUVRETYPE_OP = 2       // "out-of-plane" manoeuvre
//#define  MANOEUVRETYPE_INVALID 3    // MUST be the next unused value 
//
//} EMSMANOEUVRETYPE;

#define  isValid_ManoeuvreType( val ) ( (val >= 1) || (val <= 2) )

//typedef enum _tagEMSMANOEUVRESTATUS
//{
//         MANOEUVRESTATUS_PL   = 1,  // planned (not yet performed)
//         MANOEUVRESTATUS_AC   = 2,  // actual (has been performed)
//         MANOEUVRESTATUS_XX   = 3   // cancelled (planned but not performed)
//#define  MANOEUVRESTATUS_INVALID 4  // MUST be the next unused value
//
//} EMSMANOEUVRESTATUS;

#define  isValid_ManoeuvreStatus( val ) ( (val >= 1) || (val <= 3) )

//typedef struct _tagEMSMANOEUVREDATA       // corresponds to SIT270A
//{
//   ULONG                   ulSatID;       // satellite to perform the manoeuvre (MF#6)
//   EMSMANOEUVRETYPE        type;          // type of manoeuvre                  (MF#660)
//   EMSTIME                 startTime;     // start time of manoeuvre            (MF#661)
//   WORD                    wDuration;     // duration of manoeuvre in seconds   (MF#662)
//   EMSMANOEUVRESTATUS      status;        // status of the manoeuvre            (MF#663)
//
//} EMSMANOEUVREDATA, *LPEMSMANOEUVREDATA;

//#if defined(__cplusplus)
//extern "C" {
//#endif
//
//const char* emsmanoeuvre_typeString( EMSMANOEUVRETYPE );
//const char* emsmanoeuvre_statusString( EMSMANOEUVRESTATUS );
//
//#if defined(__cplusplus)
//}
//#endif

#endif // INC_EMSMANOEUVRE

