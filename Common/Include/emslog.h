/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat Nov 16 11:15:31 2002
 */
/* Compiler settings for EMSLOG.IDL:
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

#ifndef __EMSLOG_h__
#define __EMSLOG_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_EMSLOG_0000 */
/* [local] */ 

/********************************************************************
*	Module:			emslog.h 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	data structure used to describe the logger output
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
#ifndef INC_EMSLOG
#define INC_EMSLOG


extern RPC_IF_HANDLE __MIDL_itf_EMSLOG_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSLOG_0000_v0_0_s_ifspec;

#ifndef __IEMSLOGdata_INTERFACE_DEFINED__
#define __IEMSLOGdata_INTERFACE_DEFINED__

/* interface IEMSLOGdata */
/* [auto_handle][unique][helpstring][uuid] */ 


#pragma pack(1)
typedef struct  _tagEMSLOGDATA
    {
    EMSTIME time;
    ULONG ulLutID;
    ULONG ulProcessID;
    DWORD dwMsgNumber;
    BYTE cTaskID;
    BYTE cMsgType;
    BYTE cMsg[ 256 ];
    }	EMSLOGDATA;

typedef struct _tagEMSLOGDATA __RPC_FAR *LPEMSLOGDATA;


#pragma pack()


extern RPC_IF_HANDLE IEMSLOGdata_v0_0_c_ifspec;
extern RPC_IF_HANDLE IEMSLOGdata_v0_0_s_ifspec;
#endif /* __IEMSLOGdata_INTERFACE_DEFINED__ */

/* interface __MIDL_itf_EMSLOG_0008 */
/* [local] */ 

#endif //INC_EMSLOG


extern RPC_IF_HANDLE __MIDL_itf_EMSLOG_0008_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSLOG_0008_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
