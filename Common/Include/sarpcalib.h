/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Jan 31 15:00:04 2003
 */
/* Compiler settings for sarpcalib.idl:
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

#ifndef __sarpcalib_h__
#define __sarpcalib_h__

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

/* interface __MIDL_itf_sarpcalib_0000 */
/* [local] */ 

/********************************************************************
*	Module:			sarpcalib.h
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
*	              Copyright (c) 2002 by EMS Technologies, Inc.,
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

	0.0	02/12/30		rvw	start

********************************************************************/
#ifndef INC_SARPCALIB
#define INC_SARPCALIB


extern RPC_IF_HANDLE __MIDL_itf_sarpcalib_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_sarpcalib_0000_v0_0_s_ifspec;

#ifndef __IEMSSARPCALIBData_INTERFACE_DEFINED__
#define __IEMSSARPCALIBData_INTERFACE_DEFINED__

/* interface IEMSSARPCALIBData */
/* [auto_handle][unique][helpstring][uuid] */ 


#pragma pack(1)
typedef struct  _tagEMSSARPCALIBDATA
    {
    EMSSIGDATAID hdr;
    ULONG ulPassID;
    WORD wSource;
    EMSTIME timeEffective;
    ULONG ulTCALNumber;
    EMSTIME timeRollover;
    double dUSOFrequency;
    }	EMSSARPCALIBDATA;

typedef struct _tagEMSSARPCALIBDATA __RPC_FAR *LPEMSSARPCALIBDATA;


#pragma pack()


extern RPC_IF_HANDLE IEMSSARPCALIBData_v0_0_c_ifspec;
extern RPC_IF_HANDLE IEMSSARPCALIBData_v0_0_s_ifspec;
#endif /* __IEMSSARPCALIBData_INTERFACE_DEFINED__ */

/* interface __MIDL_itf_sarpcalib_0012 */
/* [local] */ 

#endif // INC_SARPCALIB


extern RPC_IF_HANDLE __MIDL_itf_sarpcalib_0012_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_sarpcalib_0012_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
