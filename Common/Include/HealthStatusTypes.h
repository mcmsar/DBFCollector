/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed May 06 07:46:35 2009
 */
/* Compiler settings for ..\Common\Include\HealthStatusTypes.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __HealthStatusTypes_h__
#define __HealthStatusTypes_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_HealthStatusTypes_0000 */
/* [local] */ 

/********************************************************************
*	Module:			HealthStatusTypes.h 
*********************************************************************
*	              Copyright (c) 2009 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
#ifndef INC_HEALTHSTATUSTYPES_IDL
#define INC_HEALTHSTATUSTYPES_IDL
typedef struct  tagEMSHealthStatus
    {
    EMSTIME timestamp;
    ULONG ulLutID;
    ULONG ulReportPeriod;
    WORD wWarningCount;
    WORD wAlarmCount;
    WORD wDetectRecordCount;
    WORD wReserved1;
    WORD wReserved2;
    ULONG ulReserved1;
    ULONG ulReserved2;
    double dReserved1;
    double dReserved2;
    EMSTIME timeReserved1;
    EMSTIME timeReserved2;
    }	EMSHEALTHSTATUS;

typedef struct  tagEMSHealthDetections
    {
    EMSTIME timestamp;
    ULONG ulLutID;
    ULONG ulFPID;
    ULONG ulSatID;
    WORD wDetectionCount;
    EMSTIME timeLastDetection;
    WORD wReserved1;
    ULONG ulReserved1;
    }	EMSHEALTHDETECTIONS;

#endif //INC_HEALTHSTATUSTYPES_IDL


extern RPC_IF_HANDLE __MIDL_itf_HealthStatusTypes_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_HealthStatusTypes_0000_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
