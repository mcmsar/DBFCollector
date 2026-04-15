/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Jan 31 15:34:43 2003
 */
/* Compiler settings for emstle.idl:
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

#ifndef __emstle_h__
#define __emstle_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_emstle_0000 */
/* [local] */ 

/********************************************************************
*	Module:			emstle.h 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	data structure used to describe Satellite TLE records
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2001 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	01/03/22		rvw	start

********************************************************************/
#ifndef INC_EMSTLE
#define INC_EMSTLE
 
#define EMS_TLE_MORE_SAT_FLAG ( 0x80000000 )


extern RPC_IF_HANDLE __MIDL_itf_emstle_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_emstle_0000_v0_0_s_ifspec;

#ifndef __IEMSTLEdata_INTERFACE_DEFINED__
#define __IEMSTLEdata_INTERFACE_DEFINED__

/* interface IEMSTLEdata */
/* [auto_handle][unique][helpstring][uuid] */ 


#pragma pack(1)
typedef struct  _tagEMSTLERECORD
    {
    EMSTIME time;
    ULONG ulLutID;
    ULONG ulSatID;
    int nOrbitNumber;
    EMSTIME timeEpoch;
    double fXndt2o;
    double fXndd6o;
    double fBStar;
    double fInclination;
    double fRightAscNode;
    double fEccentricity;
    double fArgPerigee;
    double fMeanAnomaly;
    double fMeanMotion;
    double fCoVarMatrix[ 21 ];
    EMSTIME timeEffective;
    double dVelocityDifference;
    double dRadiusDifference;
    }	EMSTLERECORD;

typedef struct _tagEMSTLERECORD __RPC_FAR *LPEMSTLERECORD;


#pragma pack()


extern RPC_IF_HANDLE IEMSTLEdata_v0_0_c_ifspec;
extern RPC_IF_HANDLE IEMSTLEdata_v0_0_s_ifspec;
#endif /* __IEMSTLEdata_INTERFACE_DEFINED__ */

/* interface __MIDL_itf_emstle_0008 */
/* [local] */ 

#endif //INC_EMSTLE


extern RPC_IF_HANDLE __MIDL_itf_emstle_0008_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_emstle_0008_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
