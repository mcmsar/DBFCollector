/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Aug 13 16:30:23 2007
 */
/* Compiler settings for ..\common\include\EMSALARM.IDL:
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

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __EMSALARM_h__
#define __EMSALARM_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSAlarmStatus_FWD_DEFINED__
#define __IEMSAlarmStatus_FWD_DEFINED__
typedef interface IEMSAlarmStatus IEMSAlarmStatus;
#endif 	/* __IEMSAlarmStatus_FWD_DEFINED__ */


#ifndef __IEMSAlarmStatus2_FWD_DEFINED__
#define __IEMSAlarmStatus2_FWD_DEFINED__
typedef interface IEMSAlarmStatus2 IEMSAlarmStatus2;
#endif 	/* __IEMSAlarmStatus2_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "emstatus.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_EMSALARM_0000 */
/* [local] */ 

/********************************************************************
*	Module:			emsalarm.h 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	data structure used to describe alarm states
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

	0.0	02/01/18		rvw	start

********************************************************************/
#ifndef INC_EMSALARM
#define INC_EMSALARM
// {CE2EFB3E-82EE-46f7-88C5-255C6AD4A95D}
DEFINE_GUID( IID_IEMSAlarmStatus, 0xce2efb3e, 0x82ee, 0x46f7, 0x88, 0xc5, 0x25, 0x5c, 0x6a, 0xd4, 0xa9, 0x5d);
 
// {86B46CFF-1921-4060-A5B6-E2D153834938}
DEFINE_GUID( IID_IEMSAlarmStatus2, 0x86b46cff, 0x1921, 0x4060, 0xa5, 0xb6, 0xe2, 0xd1, 0x53, 0x83, 0x49, 0x38);
 


extern RPC_IF_HANDLE __MIDL_itf_EMSALARM_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSALARM_0000_v0_0_s_ifspec;

#ifndef __IEMSAlarmStatus_INTERFACE_DEFINED__
#define __IEMSAlarmStatus_INTERFACE_DEFINED__

/* interface IEMSAlarmStatus */
/* [unique][helpstring][uuid][object] */ 


#pragma pack(1)
typedef 
enum _tagEMSALARMSTATE
    {	EMSALARM_Okay	= 0,
	EMSALARM_Warning	= 1,
	EMSALARM_Severe	= 2
    }	EMSALARMSTATE;

typedef struct  _tagEMSALARMDATA
    {
    EMSTIME time;
    ULONG ulLutID;
    DWORD dwStatus;
    BYTE cSummary;
    BYTE cEnvironment;
    BYTE cAntenna;
    BYTE cCollector;
    BYTE cWideband;
    BYTE cComms;
    BYTE cPass;
    BYTE cPower;
    BYTE cAlarm;
    BYTE cHardware;
    BYTE cLocate;
    BYTE cCalibrate;
    }	EMSALARMDATA;

typedef struct _tagEMSALARMDATA __RPC_FAR *LPEMSALARMDATA;

typedef struct  _tagEMSALARMINSTANCE
    {
    EMSTIME timeLast;
    HRESULT hrLast;
    int nCount;
    }	EMSALARMINSTANCE;

typedef struct _tagEMSALARMINSTANCE __RPC_FAR *LPEMSALARMINSTANCE;

typedef struct  _tagEMSALARMELEMENT
    {
    EMSALARMINSTANCE alarm;
    EMSALARMINSTANCE warn;
    }	EMSALARMELEMENT;

typedef struct _tagEMSALARMELEMENT __RPC_FAR *LPEMSALARMELEMENT;

typedef struct  _tagEMSALARMDATAEX
    {
    EMSALARMDATA data;
    EMSALARMELEMENT environment;
    EMSALARMELEMENT antenna;
    EMSALARMELEMENT collector;
    EMSALARMELEMENT wideband;
    EMSALARMELEMENT comms;
    EMSALARMELEMENT pass;
    }	EMSALARMDATAEX;

typedef struct _tagEMSALARMDATAEX __RPC_FAR *LPEMSALARMDATAEX;


#pragma pack()

EXTERN_C const IID IID_IEMSAlarmStatus;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CE2EFB3E-82EE-46f7-88C5-255C6AD4A95D")
    IEMSAlarmStatus : public IEMSStatus
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ResetAlarmStatusInfo( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAlarmStatusInfo( 
            /* [in] */ EMSALARMDATAEX __RPC_FAR *lpInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAlarmStatusInfo( 
            /* [out] */ EMSALARMDATAEX __RPC_FAR *lpInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSAlarmStatusVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSAlarmStatus __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSAlarmStatus __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSAlarmStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetAlarmStatusInfo )( 
            IEMSAlarmStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAlarmStatusInfo )( 
            IEMSAlarmStatus __RPC_FAR * This,
            /* [in] */ EMSALARMDATAEX __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAlarmStatusInfo )( 
            IEMSAlarmStatus __RPC_FAR * This,
            /* [out] */ EMSALARMDATAEX __RPC_FAR *lpInfo);
        
        END_INTERFACE
    } IEMSAlarmStatusVtbl;

    interface IEMSAlarmStatus
    {
        CONST_VTBL struct IEMSAlarmStatusVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSAlarmStatus_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSAlarmStatus_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSAlarmStatus_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IEMSAlarmStatus_ResetAlarmStatusInfo(This)	\
    (This)->lpVtbl -> ResetAlarmStatusInfo(This)

#define IEMSAlarmStatus_SetAlarmStatusInfo(This,lpInfo)	\
    (This)->lpVtbl -> SetAlarmStatusInfo(This,lpInfo)

#define IEMSAlarmStatus_GetAlarmStatusInfo(This,lpInfo)	\
    (This)->lpVtbl -> GetAlarmStatusInfo(This,lpInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSAlarmStatus_ResetAlarmStatusInfo_Proxy( 
    IEMSAlarmStatus __RPC_FAR * This);


void __RPC_STUB IEMSAlarmStatus_ResetAlarmStatusInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAlarmStatus_SetAlarmStatusInfo_Proxy( 
    IEMSAlarmStatus __RPC_FAR * This,
    /* [in] */ EMSALARMDATAEX __RPC_FAR *lpInfo);


void __RPC_STUB IEMSAlarmStatus_SetAlarmStatusInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAlarmStatus_GetAlarmStatusInfo_Proxy( 
    IEMSAlarmStatus __RPC_FAR * This,
    /* [out] */ EMSALARMDATAEX __RPC_FAR *lpInfo);


void __RPC_STUB IEMSAlarmStatus_GetAlarmStatusInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSAlarmStatus_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSALARM_0015 */
/* [local] */ 

typedef /* [unique] */ IEMSAlarmStatus __RPC_FAR *LPEMSALARMSTATUS;



extern RPC_IF_HANDLE __MIDL_itf_EMSALARM_0015_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSALARM_0015_v0_0_s_ifspec;

#ifndef __IEMSAlarmStatus2_INTERFACE_DEFINED__
#define __IEMSAlarmStatus2_INTERFACE_DEFINED__

/* interface IEMSAlarmStatus2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSAlarmStatus2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("86B46CFF-1921-4060-A5B6-E2D153834938")
    IEMSAlarmStatus2 : public IEMSAlarmStatus
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE CheckStatus( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSAlarmStatus2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSAlarmStatus2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSAlarmStatus2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSAlarmStatus2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetAlarmStatusInfo )( 
            IEMSAlarmStatus2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAlarmStatusInfo )( 
            IEMSAlarmStatus2 __RPC_FAR * This,
            /* [in] */ EMSALARMDATAEX __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAlarmStatusInfo )( 
            IEMSAlarmStatus2 __RPC_FAR * This,
            /* [out] */ EMSALARMDATAEX __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CheckStatus )( 
            IEMSAlarmStatus2 __RPC_FAR * This);
        
        END_INTERFACE
    } IEMSAlarmStatus2Vtbl;

    interface IEMSAlarmStatus2
    {
        CONST_VTBL struct IEMSAlarmStatus2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSAlarmStatus2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSAlarmStatus2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSAlarmStatus2_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IEMSAlarmStatus2_ResetAlarmStatusInfo(This)	\
    (This)->lpVtbl -> ResetAlarmStatusInfo(This)

#define IEMSAlarmStatus2_SetAlarmStatusInfo(This,lpInfo)	\
    (This)->lpVtbl -> SetAlarmStatusInfo(This,lpInfo)

#define IEMSAlarmStatus2_GetAlarmStatusInfo(This,lpInfo)	\
    (This)->lpVtbl -> GetAlarmStatusInfo(This,lpInfo)


#define IEMSAlarmStatus2_CheckStatus(This)	\
    (This)->lpVtbl -> CheckStatus(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSAlarmStatus2_CheckStatus_Proxy( 
    IEMSAlarmStatus2 __RPC_FAR * This);


void __RPC_STUB IEMSAlarmStatus2_CheckStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSAlarmStatus2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSALARM_0016 */
/* [local] */ 

typedef /* [unique] */ IEMSAlarmStatus2 __RPC_FAR *LPEMSALARMSTATUS2;

#endif //INC_EMSALARM


extern RPC_IF_HANDLE __MIDL_itf_EMSALARM_0016_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSALARM_0016_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
