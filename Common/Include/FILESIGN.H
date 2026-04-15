/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Jun 18 11:29:00 2003
 */
/* Compiler settings for filesign.idl:
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

#ifndef __filesign_h__
#define __filesign_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_filesign_0000 */
/* [local] */ 

/********************************************************************
*	Module:			filesign.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Definion of EMSFILESIGNATURE                     
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

	0.0	02/11/2		rvw	start

********************************************************************/
#ifndef INC_FILESIGN
#define INC_FILESIGN




extern RPC_IF_HANDLE __MIDL_itf_filesign_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_filesign_0000_v0_0_s_ifspec;

#ifndef __IEMSFILESIGNATURE_INTERFACE_DEFINED__
#define __IEMSFILESIGNATURE_INTERFACE_DEFINED__

/* interface IEMSFILESIGNATURE */
/* [auto_handle][unique][helpstring][uuid] */ 


#pragma pack(1)
typedef struct  _tagEMSFILESIGNATURE
    {
    BYTE cEMS[ 3 ];
    BYTE cType[ 5 ];
    union 
        {
        WORD wNumber;
        struct  
            {
            BYTE cMinor;
            BYTE cMajor;
            }	number;
        }	version;
    }	EMSFILESIGNATURE;

typedef struct _tagEMSFILESIGNATURE __RPC_FAR *LPEMSFILESIGNATURE;

typedef struct  _tagEMSCAPTUREFILESIGNATURE
    {
    EMSFILESIGNATURE sig;
    INT nChannel;
    INT nRecLength;
    }	EMSCAPTUREFILESIGNATURE;

typedef struct _tagEMSCAPTUREFILESIGNATURE __RPC_FAR *LPEMSCAPTUREFILESIGNATURE;

typedef struct  _tagEMSCHANNELSIGNATURE
    {
    union 
        {
        WORD wNumber;
        struct  
            {
            BYTE cMinor;
            BYTE cMajor;
            }	number;
        }	version;
    WORD wChannel;
    INT nRecLength;
    }	EMSCHANNELSIGNATURE;

typedef struct _tagEMSCHANNELSIGNATURE __RPC_FAR *LPEMSCHANNELSIGNATURE;


#pragma pack()


extern RPC_IF_HANDLE IEMSFILESIGNATURE_v0_0_c_ifspec;
extern RPC_IF_HANDLE IEMSFILESIGNATURE_v0_0_s_ifspec;
#endif /* __IEMSFILESIGNATURE_INTERFACE_DEFINED__ */

/* interface __MIDL_itf_filesign_0008 */
/* [local] */ 

#endif // INC_FILESIGN


extern RPC_IF_HANDLE __MIDL_itf_filesign_0008_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_filesign_0008_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
