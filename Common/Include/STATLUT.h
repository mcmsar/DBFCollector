/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Mar 20 13:30:24 2009
 */
/* Compiler settings for ..\Common\Include\STATLUT.IDL:
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

#ifndef __STATLUT_h__
#define __STATLUT_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSSysTestStatus_FWD_DEFINED__
#define __IEMSSysTestStatus_FWD_DEFINED__
typedef interface IEMSSysTestStatus IEMSSysTestStatus;
#endif 	/* __IEMSSysTestStatus_FWD_DEFINED__ */


#ifndef __IEMSLutStatus_FWD_DEFINED__
#define __IEMSLutStatus_FWD_DEFINED__
typedef interface IEMSLutStatus IEMSLutStatus;
#endif 	/* __IEMSLutStatus_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "emstatus.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_STATLUT_0000 */
/* [local] */ 

/********************************************************************

	Module:			StatLUT.h
	Description: 	Interface and data structures to access IEMSLUTStatus

*********************************************************************
*
*	              Copyright (c) 2009 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef INC_STATLUT
#define INC_STATLUT

// {28AB7DA2-0ACC-4332-8D0C-CCD76FE95544}
DEFINE_GUID( IID_IEMSLutStatus, 0x28ab7da2, 0xacc, 0x4332, 0x8d, 0xc, 0xcc, 0xd7, 0x6f, 0xe9, 0x55, 0x44);

// {12CD4C14-537F-4583-81A5-FD96BE139B9B}
DEFINE_GUID( IID_IEMSSysTestStatus, 0x12cd4c14, 0x537f, 0x4583, 0x81, 0xa5, 0xfd, 0x96, 0xbe, 0x13, 0x9b, 0x9b);


#pragma pack(1)


extern RPC_IF_HANDLE __MIDL_itf_STATLUT_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_STATLUT_0000_v0_0_s_ifspec;

#ifndef __IEMSSysTestStatus_INTERFACE_DEFINED__
#define __IEMSSysTestStatus_INTERFACE_DEFINED__

/* interface IEMSSysTestStatus */
/* [unique][helpstring][uuid][object] */ 

typedef /* [v1_enum] */ 
enum _tagEMSSYSTESTSTATUS
    {	EMSSYSTESTSTATUS_Unknown	= 0,
	EMSSYSTESTSTATUS_Passed	= 1,
	EMSSYSTESTSTATUS_Fail_Power	= 2,
	EMSSYSTESTSTATUS_Warning_Power	= 3,
	EMSSYSTESTSTATUS_Fail_Antenna	= 4,
	EMSSYSTESTSTATUS_Warning_Antenna	= 5
    }	EMSSYSTESTSTATUS;


EXTERN_C const IID IID_IEMSSysTestStatus;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("12CD4C14-537F-4583-81A5-FD96BE139B9B")
    IEMSSysTestStatus : public IEMSStatus
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetSysTestStatus( 
            /* [in] */ const EMSSYSTESTSTATUS ceSysTestStatus) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSysTestStatus( 
            /* [out] */ EMSSYSTESTSTATUS __RPC_FAR *peSysTestStatus) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSysTestStatusVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSSysTestStatus __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSSysTestStatus __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSSysTestStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSysTestStatus )( 
            IEMSSysTestStatus __RPC_FAR * This,
            /* [in] */ const EMSSYSTESTSTATUS ceSysTestStatus);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSysTestStatus )( 
            IEMSSysTestStatus __RPC_FAR * This,
            /* [out] */ EMSSYSTESTSTATUS __RPC_FAR *peSysTestStatus);
        
        END_INTERFACE
    } IEMSSysTestStatusVtbl;

    interface IEMSSysTestStatus
    {
        CONST_VTBL struct IEMSSysTestStatusVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSysTestStatus_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSSysTestStatus_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSSysTestStatus_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IEMSSysTestStatus_SetSysTestStatus(This,ceSysTestStatus)	\
    (This)->lpVtbl -> SetSysTestStatus(This,ceSysTestStatus)

#define IEMSSysTestStatus_GetSysTestStatus(This,peSysTestStatus)	\
    (This)->lpVtbl -> GetSysTestStatus(This,peSysTestStatus)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSSysTestStatus_SetSysTestStatus_Proxy( 
    IEMSSysTestStatus __RPC_FAR * This,
    /* [in] */ const EMSSYSTESTSTATUS ceSysTestStatus);


void __RPC_STUB IEMSSysTestStatus_SetSysTestStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSysTestStatus_GetSysTestStatus_Proxy( 
    IEMSSysTestStatus __RPC_FAR * This,
    /* [out] */ EMSSYSTESTSTATUS __RPC_FAR *peSysTestStatus);


void __RPC_STUB IEMSSysTestStatus_GetSysTestStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSSysTestStatus_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_STATLUT_0015 */
/* [local] */ 

typedef /* [unique] */ IEMSSysTestStatus __RPC_FAR *LPEMSSYSTESTSTATUS;



extern RPC_IF_HANDLE __MIDL_itf_STATLUT_0015_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_STATLUT_0015_v0_0_s_ifspec;

#ifndef __IEMSLutStatus_INTERFACE_DEFINED__
#define __IEMSLutStatus_INTERFACE_DEFINED__

/* interface IEMSLutStatus */
/* [unique][helpstring][uuid][object] */ 

typedef /* [v1_enum] */ 
enum _tagEMSLUTSTATE
    {	EMSLUTSTATE_Unknown	= 0,
	EMSLUTSTATE_Idle	= 1,
	EMSLUTSTATE_PassInProgress	= 2,
	EMSLUTSTATE_SystemTest	= 3
    }	EMSLUTSTATE;

typedef struct  _tagEMSLUTSTATUSINFO
    {
    EMSLUTSTATE eLutState;
    ULONG ulLastSatID;
    ULONG ulLastPassID;
    EMSTIME timeLastSysTestEnd;
    EMSSYSTESTSTATUS eLastSysTestStatus;
    EMSTIME timeLastLutStart;
    ULONG ulReserved1;
    ULONG ulReserved2;
    EMSTIME timeReserved1;
    EMSTIME timeReserved2;
    double dReserved;
    }	EMSLUTSTATUSINFO;

typedef struct _tagEMSLUTSTATUSINFO __RPC_FAR *LPEMSLUTSTATUSINFO;


EXTERN_C const IID IID_IEMSLutStatus;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("28AB7DA2-0ACC-4332-8D0C-CCD76FE95544")
    IEMSLutStatus : public IEMSStatus
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE LutStarted( 
            /* [in] */ const EMSTIME ctimeStarted) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLutStatus( 
            /* [out] */ LPEMSLUTSTATUSINFO pStatusInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSLutStatusVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSLutStatus __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSLutStatus __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSLutStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LutStarted )( 
            IEMSLutStatus __RPC_FAR * This,
            /* [in] */ const EMSTIME ctimeStarted);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLutStatus )( 
            IEMSLutStatus __RPC_FAR * This,
            /* [out] */ LPEMSLUTSTATUSINFO pStatusInfo);
        
        END_INTERFACE
    } IEMSLutStatusVtbl;

    interface IEMSLutStatus
    {
        CONST_VTBL struct IEMSLutStatusVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSLutStatus_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSLutStatus_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSLutStatus_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IEMSLutStatus_LutStarted(This,ctimeStarted)	\
    (This)->lpVtbl -> LutStarted(This,ctimeStarted)

#define IEMSLutStatus_GetLutStatus(This,pStatusInfo)	\
    (This)->lpVtbl -> GetLutStatus(This,pStatusInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSLutStatus_LutStarted_Proxy( 
    IEMSLutStatus __RPC_FAR * This,
    /* [in] */ const EMSTIME ctimeStarted);


void __RPC_STUB IEMSLutStatus_LutStarted_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSLutStatus_GetLutStatus_Proxy( 
    IEMSLutStatus __RPC_FAR * This,
    /* [out] */ LPEMSLUTSTATUSINFO pStatusInfo);


void __RPC_STUB IEMSLutStatus_GetLutStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSLutStatus_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_STATLUT_0016 */
/* [local] */ 

typedef /* [unique] */ IEMSLutStatus __RPC_FAR *LPEMSLUTSTATUS;


#pragma pack()
#endif //INC_STATLUT


extern RPC_IF_HANDLE __MIDL_itf_STATLUT_0016_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_STATLUT_0016_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
