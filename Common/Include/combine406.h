/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Nov 05 15:45:46 2003
 */
/* Compiler settings for .\Include\combine406.idl:
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

#ifndef __combine406_h__
#define __combine406_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "calib406.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_combine406_0000 */
/* [local] */ 

/********************************************************************
*	Module:			combine406.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Data structure for Combined 406 Data
*						
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
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

	0.0	2002/10/28		rvw		start
	0.0	2003/11/05		ch		added version number

********************************************************************/

#ifndef INC_COMBINE406
#define INC_COMBINE406

#include "calib406.h"	
#define	EMSCOMBINE406VERSION	( 1 )



extern RPC_IF_HANDLE __MIDL_itf_combine406_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_combine406_0000_v0_0_s_ifspec;

#ifndef __IEMSCOMBINE406data_INTERFACE_DEFINED__
#define __IEMSCOMBINE406data_INTERFACE_DEFINED__

/* interface IEMSCOMBINE406data */
/* [auto_handle][unique][helpstring][uuid] */ 


#pragma pack(1)
typedef 
enum _tagEMSCOMBINE406TYPE
    {	EMSCOMBINETYPE_406_FDOA	= 0x41,
	EMSCOMBINETYPE_406_TDOA	= 0x42,
	EMSCOMBINETYPE_406_FDOA_TDOA	= 0x43
    }	EMSCOMBINE406TYPE;

typedef struct  _tagEMSCOMBINE406DATA
    {
    EMSSIGDATAIDTYPE hdr;
    EMSCALIB406DATA dataA;
    EMSCALIB406DATA dataB;
    }	EMSCOMBINE406DATA;

typedef struct _tagEMSCOMBINE406DATA __RPC_FAR *LPEMSCOMBINE406DATA;


#pragma pack()


extern RPC_IF_HANDLE IEMSCOMBINE406data_v0_0_c_ifspec;
extern RPC_IF_HANDLE IEMSCOMBINE406data_v0_0_s_ifspec;
#endif /* __IEMSCOMBINE406data_INTERFACE_DEFINED__ */

/* interface __MIDL_itf_combine406_0016 */
/* [local] */ 

#endif //INC_COMBINE406


extern RPC_IF_HANDLE __MIDL_itf_combine406_0016_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_combine406_0016_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
