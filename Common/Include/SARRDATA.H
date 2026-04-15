/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Jan 31 15:33:14 2003
 */
/* Compiler settings for sarrdata.idl:
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

#ifndef __sarrdata_h__
#define __sarrdata_h__

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

/* interface __MIDL_itf_sarrdata_0000 */
/* [local] */ 

/********************************************************************
*	Module:			sarrdata.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	data structure used to describe the output of the 
*						SARR ( bent pipe data (BPD) ) wideband process 
*						and is also used as the input to the SARR Calibration 
*						process
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
#ifndef INC_SARRDATA
#define INC_SARRDATA

#define EMSSARRMSGLENGTH	(18)			// 144 bits


extern RPC_IF_HANDLE __MIDL_itf_sarrdata_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_sarrdata_0000_v0_0_s_ifspec;

#ifndef __IEMSSARRdata_INTERFACE_DEFINED__
#define __IEMSSARRdata_INTERFACE_DEFINED__

/* interface IEMSSARRdata */
/* [auto_handle][unique][helpstring][uuid] */ 


#pragma pack(1)
typedef struct  _tagEMSSARRDATA
    {
    EMSSIGDATAIDTYPE hdr;
    ULONG ulPassID;
    EMSTIME timeMsg;
    INT64 i64TimeOffset;
    INT64 i64BeaconID;
    BYTE cBeaconMsg[ 18 ];
    double dFrequency;
    float fFreqOffset;
    float fFreqBandwidth;
    float fCarrierToNoiseRatio;
    float fSignalToNoiseRatio;
    WORD wBitErrorField1;
    WORD wBitErrorField2;
    WORD wBitErrorFrameSynch;
    float fBitRate;
    float fModIndex;
    float fShortMessIndex;
    float fFrameSyncMessIndex;
    float fFrameSyncBitOffset;
    float fRawBitPower[ 144 ];
    }	EMSSARRDATA;

typedef struct _tagEMSSARRDATA __RPC_FAR *LPEMSSARRDATA;


#pragma pack()


extern RPC_IF_HANDLE IEMSSARRdata_v0_0_c_ifspec;
extern RPC_IF_HANDLE IEMSSARRdata_v0_0_s_ifspec;
#endif /* __IEMSSARRdata_INTERFACE_DEFINED__ */

/* interface __MIDL_itf_sarrdata_0012 */
/* [local] */ 

#endif // INC_SARRDATA


extern RPC_IF_HANDLE __MIDL_itf_sarrdata_0012_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_sarrdata_0012_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
