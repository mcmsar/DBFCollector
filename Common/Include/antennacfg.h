/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Jan 09 14:44:04 2007
 */
/* Compiler settings for antennacfg.idl:
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

#ifndef __antennacfg_h__
#define __antennacfg_h__

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

/* interface __MIDL_itf_antennacfg_0000 */
/* [local] */ 

/********************************************************************
*	Module:			antennacfg.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
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

	0.0  2006/11/20 	rvw	start

********************************************************************/
#ifndef INC_ANTENNACFG
#define INC_ANTENNACFG
 
#define EMS_ANTENNACFG_MAX_SATELLITES (128)
 


extern RPC_IF_HANDLE __MIDL_itf_antennacfg_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_antennacfg_0000_v0_0_s_ifspec;

#ifndef __IEMSANTENNACONFIGData_INTERFACE_DEFINED__
#define __IEMSANTENNACONFIGData_INTERFACE_DEFINED__

/* interface IEMSANTENNACONFIGData */
/* [auto_handle][unique][helpstring][uuid] */ 

typedef 
enum _tagEMSANTENNATYPECODE
    {	EMSAntennaTrackingType	= 0x800,
	EMSAntennaNativeType	= 0x400,
	EMSAntennaForeignType	= 0x200,
	EMSAntennaGeoType	= 0x80,
	EMSAntennaLeoType	= 0x40,
	EMSAntennaMeoType	= 0x20,
	EMSAntennaDBFType	= 0x10,
	EMSAntennaGeoLut600	= EMSAntennaGeoType + EMSAntennaNativeType,
	EMSAntennaLeoLut600	= EMSAntennaLeoType + EMSAntennaTrackingType + EMSAntennaNativeType,
	EMSAntennaMeoLut600	= EMSAntennaMeoType + EMSAntennaTrackingType + EMSAntennaNativeType,
	EMSAntennaTypeUnknown	= 0
    }	EMSANTENNATYPECODE;


#pragma pack(1)
typedef struct  _tagEMSANTENNACONFIG
    {
    ULONG ulLutID;
    ULONG ulAntennaID;
    EMSANTENNATYPECODE type;
    double dMaxDuration;
    double dAzMin;
    double dAzMax;
    double dElMin;
    double dElMax;
    ULONG ulSatCount;
    ULONG ulSatellites[ 128 ];
    }	EMSANTENNACONFIG;

typedef struct _tagEMSANTENNACONFIG __RPC_FAR *LPEMSANTENNACONFIG;


#pragma pack()


extern RPC_IF_HANDLE IEMSANTENNACONFIGData_v0_0_c_ifspec;
extern RPC_IF_HANDLE IEMSANTENNACONFIGData_v0_0_s_ifspec;
#endif /* __IEMSANTENNACONFIGData_INTERFACE_DEFINED__ */

/* interface __MIDL_itf_antennacfg_0012 */
/* [local] */ 

#endif // INC_ANTENNACFG


extern RPC_IF_HANDLE __MIDL_itf_antennacfg_0012_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_antennacfg_0012_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
