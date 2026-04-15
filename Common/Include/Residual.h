/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat Nov 16 11:15:35 2002
 */
/* Compiler settings for Residual.idl:
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

#ifndef __Residual_h__
#define __Residual_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "sigdata.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_Residual_0000 */
/* [local] */ 

/********************************************************************
*	Module:			residual.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Data structure for Residual Data 
*					( i.e. residuals output from Locate )
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

	Rev	Date		Auth	Changes
	===	====		====	=======

	0.0	02/10/29	rcr		start

********************************************************************/

#ifndef INC_RESIDUAL
#define INC_RESIDUAL



extern RPC_IF_HANDLE __MIDL_itf_Residual_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_Residual_0000_v0_0_s_ifspec;

#ifndef __IEMSRESIDUALdata_INTERFACE_DEFINED__
#define __IEMSRESIDUALdata_INTERFACE_DEFINED__

/* interface IEMSRESIDUALdata */
/* [auto_handle][unique][helpstring][uuid] */ 


#pragma pack(1)
typedef struct  _tagEMSRESIDUALDATAD
    {

    ULONG    ulReferenceID;
    EMSSIGDATAIDTYPE hdr;
    INT64    i64BeaconID;
    ULONG    ulSatPassID;
    EMSTIME  timeMsg;
    INT64    i64TimeOffset;
    float    fLutSatTimeOffset;
    double   dMeasurement;
    float    fFreqOffset;
    float    fLutSatFreqOffset;
    double   dPower;
    WORD     wProcessFlag;
    double   dResidual;
    WORD     wProcessFlags[4];
    double   dResiduals[4];

    EMSSIGDATAIDTYPE hdr1;
    EMSSIGDATAIDTYPE hdr2;
    EMSTIME  timeMsg2;
    INT64    i64TimeOffset2;
    float    fLutSatTimeOffset2;
    double   dMeasurement2;
    float    fFreqOffset2;
    float    fLutSatFreqOffset2;
    double   dPower2;

    }	EMSRESIDUALDATAD;

typedef struct _tagEMSRESIDUALDATAD __RPC_FAR *LPEMSRESIDUALDATAD;

typedef struct  _tagEMSRESIDUALDATA
    {
    EMSSIGDATAIDTYPE hdr;
    ULONG ulSatPassID;
    ULONG ulReferenceID;
    INT64 i64BeaconID;
    EMSTIME timeMsg;
    double dMeasurement;
    float fResidual;
    float fPower;
    WORD wProcessFlag;
    }	EMSRESIDUALDATA;

typedef struct _tagEMSRESIDUALDATA __RPC_FAR *LPEMSRESIDUALDATA;


#pragma pack()


extern RPC_IF_HANDLE IEMSRESIDUALdata_v0_0_c_ifspec;
extern RPC_IF_HANDLE IEMSRESIDUALdata_v0_0_s_ifspec;
#endif /* __IEMSRESIDUALdata_INTERFACE_DEFINED__ */

/* interface __MIDL_itf_Residual_0012 */
/* [local] */ 

#endif //INC_RESIDUAL


extern RPC_IF_HANDLE __MIDL_itf_Residual_0012_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_Residual_0012_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
