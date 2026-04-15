/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Aug 10 09:24:19 2005
 */
/* Compiler settings for psnotify.idl:
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

#ifndef __psnotify_h__
#define __psnotify_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSPassAlarmCountNotify_FWD_DEFINED__
#define __IEMSPassAlarmCountNotify_FWD_DEFINED__
typedef interface IEMSPassAlarmCountNotify IEMSPassAlarmCountNotify;
#endif 	/* __IEMSPassAlarmCountNotify_FWD_DEFINED__ */


#ifndef __IEMSPassStatusNotify_FWD_DEFINED__
#define __IEMSPassStatusNotify_FWD_DEFINED__
typedef interface IEMSPassStatusNotify IEMSPassStatusNotify;
#endif 	/* __IEMSPassStatusNotify_FWD_DEFINED__ */


#ifndef __IEMSSummaryPeriodNotify_FWD_DEFINED__
#define __IEMSSummaryPeriodNotify_FWD_DEFINED__
typedef interface IEMSSummaryPeriodNotify IEMSSummaryPeriodNotify;
#endif 	/* __IEMSSummaryPeriodNotify_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "emstatus.h"
#include "emstrack.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_psnotify_0000 */
/* [local] */ 

/********************************************************************
*	Module:			psnotify.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Interface and data structures to access IEMSPassStatusNotify
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
 0.1 2005/08/10		rvw add Summary interface

********************************************************************/
#ifndef INC_PSNOTIFY
#define INC_PSNOTIFY

// {34E90721-211F-11d6-8DBD-009027912866}
DEFINE_GUID( IID_IEMSPassStatusNotify, 0x34e90721, 0x211f, 0x11d6, 0x8d, 0xbd, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);
 
// {05DC2160-FDDF-4535-A9C6-277B8ABE4625}
DEFINE_GUID( IID_IEMSPassAlarmCountNotify, 0x5dc2160, 0xfddf, 0x4535, 0xa9, 0xc6, 0x27, 0x7b, 0x8a, 0xbe, 0x46, 0x25);
 
// {926EDDBA-36E0-4d18-A6BD-0DCBB4264BA9}
DEFINE_GUID( IID_IEMSSummaryPeriodNotify, 0x926eddba, 0x36e0, 0x4d18, 0xa6, 0xbd, 0xd, 0xcb, 0xb4, 0x26, 0x4b, 0xa9);
 


extern RPC_IF_HANDLE __MIDL_itf_psnotify_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_psnotify_0000_v0_0_s_ifspec;

#ifndef __IEMSPassAlarmCountNotify_INTERFACE_DEFINED__
#define __IEMSPassAlarmCountNotify_INTERFACE_DEFINED__

/* interface IEMSPassAlarmCountNotify */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSPassAlarmCountNotify;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("05DC2160-FDDF-4535-A9C6-277B8ABE4625")
    IEMSPassAlarmCountNotify : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE IncrAlarmCount( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IncrWarningCount( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAlarmCount( 
            /* [in] */ ULONG ulCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetWarningCount( 
            /* [in] */ ULONG ulCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ResetAlarmWarningCounts( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAlarmWarningCounts( 
            /* [out] */ ULONG __RPC_FAR *lpulAlarmCount,
            /* [out] */ ULONG __RPC_FAR *lpulWarningCount) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSPassAlarmCountNotifyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSPassAlarmCountNotify __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSPassAlarmCountNotify __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSPassAlarmCountNotify __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IncrAlarmCount )( 
            IEMSPassAlarmCountNotify __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IncrWarningCount )( 
            IEMSPassAlarmCountNotify __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAlarmCount )( 
            IEMSPassAlarmCountNotify __RPC_FAR * This,
            /* [in] */ ULONG ulCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetWarningCount )( 
            IEMSPassAlarmCountNotify __RPC_FAR * This,
            /* [in] */ ULONG ulCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetAlarmWarningCounts )( 
            IEMSPassAlarmCountNotify __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAlarmWarningCounts )( 
            IEMSPassAlarmCountNotify __RPC_FAR * This,
            /* [out] */ ULONG __RPC_FAR *lpulAlarmCount,
            /* [out] */ ULONG __RPC_FAR *lpulWarningCount);
        
        END_INTERFACE
    } IEMSPassAlarmCountNotifyVtbl;

    interface IEMSPassAlarmCountNotify
    {
        CONST_VTBL struct IEMSPassAlarmCountNotifyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSPassAlarmCountNotify_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSPassAlarmCountNotify_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSPassAlarmCountNotify_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSPassAlarmCountNotify_IncrAlarmCount(This)	\
    (This)->lpVtbl -> IncrAlarmCount(This)

#define IEMSPassAlarmCountNotify_IncrWarningCount(This)	\
    (This)->lpVtbl -> IncrWarningCount(This)

#define IEMSPassAlarmCountNotify_SetAlarmCount(This,ulCount)	\
    (This)->lpVtbl -> SetAlarmCount(This,ulCount)

#define IEMSPassAlarmCountNotify_SetWarningCount(This,ulCount)	\
    (This)->lpVtbl -> SetWarningCount(This,ulCount)

#define IEMSPassAlarmCountNotify_ResetAlarmWarningCounts(This)	\
    (This)->lpVtbl -> ResetAlarmWarningCounts(This)

#define IEMSPassAlarmCountNotify_GetAlarmWarningCounts(This,lpulAlarmCount,lpulWarningCount)	\
    (This)->lpVtbl -> GetAlarmWarningCounts(This,lpulAlarmCount,lpulWarningCount)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSPassAlarmCountNotify_IncrAlarmCount_Proxy( 
    IEMSPassAlarmCountNotify __RPC_FAR * This);


void __RPC_STUB IEMSPassAlarmCountNotify_IncrAlarmCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSPassAlarmCountNotify_IncrWarningCount_Proxy( 
    IEMSPassAlarmCountNotify __RPC_FAR * This);


void __RPC_STUB IEMSPassAlarmCountNotify_IncrWarningCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSPassAlarmCountNotify_SetAlarmCount_Proxy( 
    IEMSPassAlarmCountNotify __RPC_FAR * This,
    /* [in] */ ULONG ulCount);


void __RPC_STUB IEMSPassAlarmCountNotify_SetAlarmCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSPassAlarmCountNotify_SetWarningCount_Proxy( 
    IEMSPassAlarmCountNotify __RPC_FAR * This,
    /* [in] */ ULONG ulCount);


void __RPC_STUB IEMSPassAlarmCountNotify_SetWarningCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSPassAlarmCountNotify_ResetAlarmWarningCounts_Proxy( 
    IEMSPassAlarmCountNotify __RPC_FAR * This);


void __RPC_STUB IEMSPassAlarmCountNotify_ResetAlarmWarningCounts_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSPassAlarmCountNotify_GetAlarmWarningCounts_Proxy( 
    IEMSPassAlarmCountNotify __RPC_FAR * This,
    /* [out] */ ULONG __RPC_FAR *lpulAlarmCount,
    /* [out] */ ULONG __RPC_FAR *lpulWarningCount);


void __RPC_STUB IEMSPassAlarmCountNotify_GetAlarmWarningCounts_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSPassAlarmCountNotify_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_psnotify_0021 */
/* [local] */ 

typedef /* [unique] */ IEMSPassAlarmCountNotify __RPC_FAR *LPEMSPASSALARMCOUNTNOTIFY;



extern RPC_IF_HANDLE __MIDL_itf_psnotify_0021_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_psnotify_0021_v0_0_s_ifspec;

#ifndef __IEMSPassStatusNotify_INTERFACE_DEFINED__
#define __IEMSPassStatusNotify_INTERFACE_DEFINED__

/* interface IEMSPassStatusNotify */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSPassStatusNotify;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("34E90721-211F-11d6-8DBD-009027912866")
    IEMSPassStatusNotify : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE StartPass( 
            ULONG ulSatID,
            ULONG ulPassID,
            EMSTIME timeAOS,
            EMSTIME timeLOS) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE EndPass( 
            ULONG ulSatID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSPassStatusNotifyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSPassStatusNotify __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSPassStatusNotify __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSPassStatusNotify __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StartPass )( 
            IEMSPassStatusNotify __RPC_FAR * This,
            ULONG ulSatID,
            ULONG ulPassID,
            EMSTIME timeAOS,
            EMSTIME timeLOS);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EndPass )( 
            IEMSPassStatusNotify __RPC_FAR * This,
            ULONG ulSatID);
        
        END_INTERFACE
    } IEMSPassStatusNotifyVtbl;

    interface IEMSPassStatusNotify
    {
        CONST_VTBL struct IEMSPassStatusNotifyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSPassStatusNotify_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSPassStatusNotify_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSPassStatusNotify_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSPassStatusNotify_StartPass(This,ulSatID,ulPassID,timeAOS,timeLOS)	\
    (This)->lpVtbl -> StartPass(This,ulSatID,ulPassID,timeAOS,timeLOS)

#define IEMSPassStatusNotify_EndPass(This,ulSatID)	\
    (This)->lpVtbl -> EndPass(This,ulSatID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSPassStatusNotify_StartPass_Proxy( 
    IEMSPassStatusNotify __RPC_FAR * This,
    ULONG ulSatID,
    ULONG ulPassID,
    EMSTIME timeAOS,
    EMSTIME timeLOS);


void __RPC_STUB IEMSPassStatusNotify_StartPass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSPassStatusNotify_EndPass_Proxy( 
    IEMSPassStatusNotify __RPC_FAR * This,
    ULONG ulSatID);


void __RPC_STUB IEMSPassStatusNotify_EndPass_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSPassStatusNotify_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_psnotify_0022 */
/* [local] */ 

typedef /* [unique] */ IEMSPassStatusNotify __RPC_FAR *LPEMSPASSSTATUSNOTIFY;



extern RPC_IF_HANDLE __MIDL_itf_psnotify_0022_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_psnotify_0022_v0_0_s_ifspec;

#ifndef __IEMSSummaryPeriodNotify_INTERFACE_DEFINED__
#define __IEMSSummaryPeriodNotify_INTERFACE_DEFINED__

/* interface IEMSSummaryPeriodNotify */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSSummaryPeriodNotify;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("926EDDBA-36E0-4d18-A6BD-0DCBB4264BA9")
    IEMSSummaryPeriodNotify : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetSummaryPeriod( 
            /* [in] */ EMSTIME timeStart,
            /* [in] */ double dDuration) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSummaryPeriod( 
            /* [out] */ EMSTIME __RPC_FAR *lpTimeStart,
            /* [out] */ double __RPC_FAR *lpdDuration) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSummaryPeriodNotifyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSSummaryPeriodNotify __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSSummaryPeriodNotify __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSSummaryPeriodNotify __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSummaryPeriod )( 
            IEMSSummaryPeriodNotify __RPC_FAR * This,
            /* [in] */ EMSTIME timeStart,
            /* [in] */ double dDuration);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSummaryPeriod )( 
            IEMSSummaryPeriodNotify __RPC_FAR * This,
            /* [out] */ EMSTIME __RPC_FAR *lpTimeStart,
            /* [out] */ double __RPC_FAR *lpdDuration);
        
        END_INTERFACE
    } IEMSSummaryPeriodNotifyVtbl;

    interface IEMSSummaryPeriodNotify
    {
        CONST_VTBL struct IEMSSummaryPeriodNotifyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSummaryPeriodNotify_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSSummaryPeriodNotify_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSSummaryPeriodNotify_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSSummaryPeriodNotify_SetSummaryPeriod(This,timeStart,dDuration)	\
    (This)->lpVtbl -> SetSummaryPeriod(This,timeStart,dDuration)

#define IEMSSummaryPeriodNotify_GetSummaryPeriod(This,lpTimeStart,lpdDuration)	\
    (This)->lpVtbl -> GetSummaryPeriod(This,lpTimeStart,lpdDuration)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSSummaryPeriodNotify_SetSummaryPeriod_Proxy( 
    IEMSSummaryPeriodNotify __RPC_FAR * This,
    /* [in] */ EMSTIME timeStart,
    /* [in] */ double dDuration);


void __RPC_STUB IEMSSummaryPeriodNotify_SetSummaryPeriod_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSummaryPeriodNotify_GetSummaryPeriod_Proxy( 
    IEMSSummaryPeriodNotify __RPC_FAR * This,
    /* [out] */ EMSTIME __RPC_FAR *lpTimeStart,
    /* [out] */ double __RPC_FAR *lpdDuration);


void __RPC_STUB IEMSSummaryPeriodNotify_GetSummaryPeriod_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSSummaryPeriodNotify_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_psnotify_0023 */
/* [local] */ 

typedef /* [unique] */ IEMSSummaryPeriodNotify __RPC_FAR *LPEMSSUMMARYPERIODNOTIFY;

#endif //INC_PSNOTIFY


extern RPC_IF_HANDLE __MIDL_itf_psnotify_0023_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_psnotify_0023_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
