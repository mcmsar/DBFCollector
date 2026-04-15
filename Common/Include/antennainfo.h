/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Nov 21 15:57:45 2006
 */
/* Compiler settings for antennainfo.idl:
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

#ifndef __antennainfo_h__
#define __antennainfo_h__

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

/* interface __MIDL_itf_antennainfo_0000 */
/* [local] */ 

/********************************************************************
*	Module:			antennainfo.h
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
#ifndef INC_ANTENNAINFO
#define INC_ANTENNAINFO
 
#define EMS_ANTENNAINFO_MAX_SATELLITES (128)
 


extern RPC_IF_HANDLE __MIDL_itf_antennainfo_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_antennainfo_0000_v0_0_s_ifspec;

#ifndef __IEMSANTENNAINFOData_INTERFACE_DEFINED__
#define __IEMSANTENNAINFOData_INTERFACE_DEFINED__

/* interface IEMSANTENNAINFOData */
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
	EMSAntennaTypeUnknown	= 0
    }	EMSANTENNATYPECODE;


#pragma pack(1)
typedef struct  _tagEMSANTENNAINFO
    {
    ULONG ulLutID;
    ULONG ulAntennaID;
    EMSANTENNATYPECODE type;
    double dAzMin;
    double dAzMax;
    double dElMin;
    double dElMax;
    ULONG ulSatCount;
    ULONG ulSatellites[ 128 ];
    }	EMSANTENNAINFO;

typedef struct _tagEMSANTENNAINFO __RPC_FAR *LPEMSANTENNAINFO;


#pragma pack()


extern RPC_IF_HANDLE IEMSANTENNAINFOData_v0_0_c_ifspec;
extern RPC_IF_HANDLE IEMSANTENNAINFOData_v0_0_s_ifspec;
#endif /* __IEMSANTENNAINFOData_INTERFACE_DEFINED__ */

/* interface __MIDL_itf_antennainfo_0012 */
/* [local] */ 

#endif // INC_ANTENNAINFO


extern RPC_IF_HANDLE __MIDL_itf_antennainfo_0012_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_antennainfo_0012_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
