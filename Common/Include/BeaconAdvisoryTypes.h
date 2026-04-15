/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Jun 11 09:12:20 2009
 */
/* Compiler settings for ..\Common\Include\BeaconAdvisoryTypes.idl:
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

#ifndef __BeaconAdvisoryTypes_h__
#define __BeaconAdvisoryTypes_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_BeaconAdvisoryTypes_0000 */
/* [local] */ 

/********************************************************************
*	Module:			BeaconAdvisoryTypes.h 
*********************************************************************
*	              Copyright (c) 2009 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
#ifndef INC_BEACONADVISORYTYPES_IDL
#define INC_BEACONADVISORYTYPES_IDL
typedef 
enum _tagEMSTxMode
    {	EMSTXMODE_UNKNOWN	= 0,
	EMSTXMODE_TESTONLY	= 1,
	EMSTXMODE_COMBINED	= 2,
	EMSTXMODE_COMBINEDONLY	= 3
    }	EMSTXMODE;

#define INVALID_LATITUDE	99.9999
#define INVALID_LONGITUDE	999.9999
typedef struct  _tagEMS_BEACON_ADVISORY
    {
    EMSTIME timestamp;
    ULONG ulLUTID;
    ULONG ulSatID;
    ULONG ulPassID;
    INT64 i64BeaconID;
    BYTE cBeaconMsg[ 18 ];
    EMSTIME timeFirstDetect;
    EMSTIME timeLastDetect;
    ULONG ulTestBurstCount;
    ULONG ulTotalBurstCount;
    EMSTXMODE eTxMode;
    double dDegLatitude;
    double dDegLongitude;
    WORD wSeq;
    WORD wCount;
    ULONG ulReserved1;
    ULONG ulReserved2;
    ULONG ulReserved3;
    ULONG ulReserved4;
    double dReserved1;
    double dReserved2;
    double dReserved3;
    double dReserved4;
    EMSTIME timeReserved;
    }	EMS_BEACON_ADVISORY;

#endif //INC_BEACONADVISORYTYPES_IDL


extern RPC_IF_HANDLE __MIDL_itf_BeaconAdvisoryTypes_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_BeaconAdvisoryTypes_0000_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
