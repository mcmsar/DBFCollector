/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Feb 01 13:30:15 2007
 */
/* Compiler settings for ..\common\Include\ChangeMonitor.idl:
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

#ifndef __ChangeMonitor_h__
#define __ChangeMonitor_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSDataChangeSink_FWD_DEFINED__
#define __IEMSDataChangeSink_FWD_DEFINED__
typedef interface IEMSDataChangeSink IEMSDataChangeSink;
#endif 	/* __IEMSDataChangeSink_FWD_DEFINED__ */


#ifndef __IEMSChangeMonitor_FWD_DEFINED__
#define __IEMSChangeMonitor_FWD_DEFINED__
typedef interface IEMSChangeMonitor IEMSChangeMonitor;
#endif 	/* __IEMSChangeMonitor_FWD_DEFINED__ */


#ifndef __IEMSChangeMonitor2_FWD_DEFINED__
#define __IEMSChangeMonitor2_FWD_DEFINED__
typedef interface IEMSChangeMonitor2 IEMSChangeMonitor2;
#endif 	/* __IEMSChangeMonitor2_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_ChangeMonitor_0000 */
/* [local] */ 

#ifndef _CHANGEMONITOR_IDL_H_
#define _CHANGEMONITOR_IDL_H_
// {900457F9-EFE3-4298-9755-FD430A113271}
DEFINE_GUID(IID_IEMSDataChangeSink, 0x900457f9, 0xefe3, 0x4298, 0x97, 0x55, 0xfd, 0x43, 0xa, 0x11, 0x32, 0x71);
// {C6307BFB-28C1-47c0-B630-30C665D66A0B}
DEFINE_GUID(IID_IEMSChangeMonitor, 0xc6307bfb, 0x28c1, 0x47c0, 0xb6, 0x30, 0x30, 0xc6, 0x65, 0xd6, 0x6a, 0xb);
// {EABC9150-CF98-4a61-AC45-AEEF30D79D3A}
DEFINE_GUID(IID_IEMSChangeMonitor2, 0xeabc9150, 0xcf98, 0x4a61, 0xac, 0x45, 0xae, 0xef, 0x30, 0xd7, 0x9d, 0x3a);
// {F13551B8-35AB-446c-924C-47E29D19E4E7}
DEFINE_GUID(CLSID_EMSChangeMonitor, 0xf13551b8, 0x35ab, 0x446c, 0x92, 0x4c, 0x47, 0xe2, 0x9d, 0x19, 0xe4, 0xe7);

// EMSDATACHANGE_DISPLAY_STATE = Any display state change
// EMSDATACHANGE_LUT_STATUS_DATA triggered by new status record or online/offline transition
typedef 
enum tagLutEventEnum
    {	EMSDATACHANGE_MIN	= 0,
	EMSDATACHANGE_UNKNOWN	= 0,
	EMSDATACHANGE_DISPLAY_STATE	= 1,
	EMSDATACHANGE_DISPLAY_STATE_OFFLINE	= 2,
	EMSDATACHANGE_DISPLAY_STATE_IDLE	= 3,
	EMSDATACHANGE_DISPLAY_STATE_PASS	= 4,
	EMSDATACHANGE_DISPLAY_STATE_POSTPASS	= 5,
	EMSDATACHANGE_DISPLAY_STATE_SYSTEM_TEST	= 6,
	EMSDATACHANGE_LUT_STATUS_DATA	= 7,
	EMSDATACHANGE_LOG_ENTRY	= 8,
	EMSDATACHANGE_MAX	= 8
    }	EMSDATACHANGE;

#define EMSDATACHANGE_COUNT			(EMSDATACHANGE_MAX+1)
#define VALID_EMSDATACHANGE(x)		(x>=EMSDATACHANGE_MIN && x<=EMSDATACHANGE_MAX)
typedef 
enum tagLutDisplayStateEnum
    {	LUTDISPLAYSTATE_MIN	= 0,
	LUTDISPLAYSTATE_UNKNOWN	= 0,
	LUTDISPLAYSTATE_OFFLINE	= 1,
	LUTDISPLAYSTATE_IDLE	= 2,
	LUTDISPLAYSTATE_PASS	= 3,
	LUTDISPLAYSTATE_POSTPASS	= 4,
	LUTDISPLAYSTATE_SYSTEM_TEST	= 5,
	LUTDISPLAYSTATE_MAX	= 5
    }	LUTDISPLAYSTATE;

#define LUTDISPLAYSTATE_COUNT	(LUTDISPLAYSTATE_MAX+1)
#define VALID_LUTDISPLAYSTATE(x)	(x>=LUTDISPLAYSTATE_MIN && x<=LUTDISPLAYSTATE_MAX)


extern RPC_IF_HANDLE __MIDL_itf_ChangeMonitor_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ChangeMonitor_0000_v0_0_s_ifspec;

#ifndef __IEMSDataChangeSink_INTERFACE_DEFINED__
#define __IEMSDataChangeSink_INTERFACE_DEFINED__

/* interface IEMSDataChangeSink */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IEMSDataChangeSink;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("900457F9-EFE3-4298-9755-FD430A113271")
    IEMSDataChangeSink : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnChange( 
            /* [in] */ const ULONG culLutID,
            /* [in] */ const EMSDATACHANGE ceChange,
            /* [in] */ const ULONG culUserDataSize,
            /* [size_is][in] */ const BYTE __RPC_FAR *cabyUserData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSDataChangeSinkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSDataChangeSink __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSDataChangeSink __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSDataChangeSink __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnChange )( 
            IEMSDataChangeSink __RPC_FAR * This,
            /* [in] */ const ULONG culLutID,
            /* [in] */ const EMSDATACHANGE ceChange,
            /* [in] */ const ULONG culUserDataSize,
            /* [size_is][in] */ const BYTE __RPC_FAR *cabyUserData);
        
        END_INTERFACE
    } IEMSDataChangeSinkVtbl;

    interface IEMSDataChangeSink
    {
        CONST_VTBL struct IEMSDataChangeSinkVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSDataChangeSink_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSDataChangeSink_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSDataChangeSink_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSDataChangeSink_OnChange(This,culLutID,ceChange,culUserDataSize,cabyUserData)	\
    (This)->lpVtbl -> OnChange(This,culLutID,ceChange,culUserDataSize,cabyUserData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSDataChangeSink_OnChange_Proxy( 
    IEMSDataChangeSink __RPC_FAR * This,
    /* [in] */ const ULONG culLutID,
    /* [in] */ const EMSDATACHANGE ceChange,
    /* [in] */ const ULONG culUserDataSize,
    /* [size_is][in] */ const BYTE __RPC_FAR *cabyUserData);


void __RPC_STUB IEMSDataChangeSink_OnChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSDataChangeSink_INTERFACE_DEFINED__ */


#ifndef __IEMSChangeMonitor_INTERFACE_DEFINED__
#define __IEMSChangeMonitor_INTERFACE_DEFINED__

/* interface IEMSChangeMonitor */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IEMSChangeMonitor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C6307BFB-28C1-47c0-B630-30C665D66A0B")
    IEMSChangeMonitor : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Subscribe( 
            /* [in] */ IEMSDataChangeSink __RPC_FAR *pSink,
            /* [in] */ const ULONG culLutID,
            /* [in] */ const EMSDATACHANGE ceDataChange,
            /* [in] */ const ULONG culUserDataSize,
            /* [size_is][in] */ const BYTE __RPC_FAR *cabyUserData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Unsubscribe( 
            /* [in] */ IEMSDataChangeSink __RPC_FAR *pSink,
            /* [in] */ const ULONG culLutID,
            /* [in] */ const EMSDATACHANGE ceDataChange) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnsubscribeAll( 
            /* [in] */ IEMSDataChangeSink __RPC_FAR *pSink) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSChangeMonitorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSChangeMonitor __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSChangeMonitor __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSChangeMonitor __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Subscribe )( 
            IEMSChangeMonitor __RPC_FAR * This,
            /* [in] */ IEMSDataChangeSink __RPC_FAR *pSink,
            /* [in] */ const ULONG culLutID,
            /* [in] */ const EMSDATACHANGE ceDataChange,
            /* [in] */ const ULONG culUserDataSize,
            /* [size_is][in] */ const BYTE __RPC_FAR *cabyUserData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Unsubscribe )( 
            IEMSChangeMonitor __RPC_FAR * This,
            /* [in] */ IEMSDataChangeSink __RPC_FAR *pSink,
            /* [in] */ const ULONG culLutID,
            /* [in] */ const EMSDATACHANGE ceDataChange);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnsubscribeAll )( 
            IEMSChangeMonitor __RPC_FAR * This,
            /* [in] */ IEMSDataChangeSink __RPC_FAR *pSink);
        
        END_INTERFACE
    } IEMSChangeMonitorVtbl;

    interface IEMSChangeMonitor
    {
        CONST_VTBL struct IEMSChangeMonitorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSChangeMonitor_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSChangeMonitor_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSChangeMonitor_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSChangeMonitor_Subscribe(This,pSink,culLutID,ceDataChange,culUserDataSize,cabyUserData)	\
    (This)->lpVtbl -> Subscribe(This,pSink,culLutID,ceDataChange,culUserDataSize,cabyUserData)

#define IEMSChangeMonitor_Unsubscribe(This,pSink,culLutID,ceDataChange)	\
    (This)->lpVtbl -> Unsubscribe(This,pSink,culLutID,ceDataChange)

#define IEMSChangeMonitor_UnsubscribeAll(This,pSink)	\
    (This)->lpVtbl -> UnsubscribeAll(This,pSink)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSChangeMonitor_Subscribe_Proxy( 
    IEMSChangeMonitor __RPC_FAR * This,
    /* [in] */ IEMSDataChangeSink __RPC_FAR *pSink,
    /* [in] */ const ULONG culLutID,
    /* [in] */ const EMSDATACHANGE ceDataChange,
    /* [in] */ const ULONG culUserDataSize,
    /* [size_is][in] */ const BYTE __RPC_FAR *cabyUserData);


void __RPC_STUB IEMSChangeMonitor_Subscribe_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSChangeMonitor_Unsubscribe_Proxy( 
    IEMSChangeMonitor __RPC_FAR * This,
    /* [in] */ IEMSDataChangeSink __RPC_FAR *pSink,
    /* [in] */ const ULONG culLutID,
    /* [in] */ const EMSDATACHANGE ceDataChange);


void __RPC_STUB IEMSChangeMonitor_Unsubscribe_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSChangeMonitor_UnsubscribeAll_Proxy( 
    IEMSChangeMonitor __RPC_FAR * This,
    /* [in] */ IEMSDataChangeSink __RPC_FAR *pSink);


void __RPC_STUB IEMSChangeMonitor_UnsubscribeAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSChangeMonitor_INTERFACE_DEFINED__ */


#ifndef __IEMSChangeMonitor2_INTERFACE_DEFINED__
#define __IEMSChangeMonitor2_INTERFACE_DEFINED__

/* interface IEMSChangeMonitor2 */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IEMSChangeMonitor2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EABC9150-CF98-4a61-AC45-AEEF30D79D3A")
    IEMSChangeMonitor2 : public IEMSChangeMonitor
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SubscribeEx( 
            /* [in] */ IEMSDataChangeSink __RPC_FAR *pSink,
            /* [in] */ const ULONG culCalleeID,
            /* [in] */ const ULONG culFilterLutID,
            /* [in] */ const EMSDATACHANGE ceDataChange,
            /* [in] */ const ULONG culUserDataSize,
            /* [size_is][in] */ const BYTE __RPC_FAR *cabyUserData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnsubscribeEx( 
            /* [in] */ IEMSDataChangeSink __RPC_FAR *pSink,
            /* [in] */ const ULONG culCalleeID,
            /* [in] */ const ULONG culFilterLutID,
            /* [in] */ const EMSDATACHANGE ceDataChange) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSChangeMonitor2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSChangeMonitor2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSChangeMonitor2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSChangeMonitor2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Subscribe )( 
            IEMSChangeMonitor2 __RPC_FAR * This,
            /* [in] */ IEMSDataChangeSink __RPC_FAR *pSink,
            /* [in] */ const ULONG culLutID,
            /* [in] */ const EMSDATACHANGE ceDataChange,
            /* [in] */ const ULONG culUserDataSize,
            /* [size_is][in] */ const BYTE __RPC_FAR *cabyUserData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Unsubscribe )( 
            IEMSChangeMonitor2 __RPC_FAR * This,
            /* [in] */ IEMSDataChangeSink __RPC_FAR *pSink,
            /* [in] */ const ULONG culLutID,
            /* [in] */ const EMSDATACHANGE ceDataChange);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnsubscribeAll )( 
            IEMSChangeMonitor2 __RPC_FAR * This,
            /* [in] */ IEMSDataChangeSink __RPC_FAR *pSink);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SubscribeEx )( 
            IEMSChangeMonitor2 __RPC_FAR * This,
            /* [in] */ IEMSDataChangeSink __RPC_FAR *pSink,
            /* [in] */ const ULONG culCalleeID,
            /* [in] */ const ULONG culFilterLutID,
            /* [in] */ const EMSDATACHANGE ceDataChange,
            /* [in] */ const ULONG culUserDataSize,
            /* [size_is][in] */ const BYTE __RPC_FAR *cabyUserData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnsubscribeEx )( 
            IEMSChangeMonitor2 __RPC_FAR * This,
            /* [in] */ IEMSDataChangeSink __RPC_FAR *pSink,
            /* [in] */ const ULONG culCalleeID,
            /* [in] */ const ULONG culFilterLutID,
            /* [in] */ const EMSDATACHANGE ceDataChange);
        
        END_INTERFACE
    } IEMSChangeMonitor2Vtbl;

    interface IEMSChangeMonitor2
    {
        CONST_VTBL struct IEMSChangeMonitor2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSChangeMonitor2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSChangeMonitor2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSChangeMonitor2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSChangeMonitor2_Subscribe(This,pSink,culLutID,ceDataChange,culUserDataSize,cabyUserData)	\
    (This)->lpVtbl -> Subscribe(This,pSink,culLutID,ceDataChange,culUserDataSize,cabyUserData)

#define IEMSChangeMonitor2_Unsubscribe(This,pSink,culLutID,ceDataChange)	\
    (This)->lpVtbl -> Unsubscribe(This,pSink,culLutID,ceDataChange)

#define IEMSChangeMonitor2_UnsubscribeAll(This,pSink)	\
    (This)->lpVtbl -> UnsubscribeAll(This,pSink)


#define IEMSChangeMonitor2_SubscribeEx(This,pSink,culCalleeID,culFilterLutID,ceDataChange,culUserDataSize,cabyUserData)	\
    (This)->lpVtbl -> SubscribeEx(This,pSink,culCalleeID,culFilterLutID,ceDataChange,culUserDataSize,cabyUserData)

#define IEMSChangeMonitor2_UnsubscribeEx(This,pSink,culCalleeID,culFilterLutID,ceDataChange)	\
    (This)->lpVtbl -> UnsubscribeEx(This,pSink,culCalleeID,culFilterLutID,ceDataChange)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSChangeMonitor2_SubscribeEx_Proxy( 
    IEMSChangeMonitor2 __RPC_FAR * This,
    /* [in] */ IEMSDataChangeSink __RPC_FAR *pSink,
    /* [in] */ const ULONG culCalleeID,
    /* [in] */ const ULONG culFilterLutID,
    /* [in] */ const EMSDATACHANGE ceDataChange,
    /* [in] */ const ULONG culUserDataSize,
    /* [size_is][in] */ const BYTE __RPC_FAR *cabyUserData);


void __RPC_STUB IEMSChangeMonitor2_SubscribeEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSChangeMonitor2_UnsubscribeEx_Proxy( 
    IEMSChangeMonitor2 __RPC_FAR * This,
    /* [in] */ IEMSDataChangeSink __RPC_FAR *pSink,
    /* [in] */ const ULONG culCalleeID,
    /* [in] */ const ULONG culFilterLutID,
    /* [in] */ const EMSDATACHANGE ceDataChange);


void __RPC_STUB IEMSChangeMonitor2_UnsubscribeEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSChangeMonitor2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_ChangeMonitor_0011 */
/* [local] */ 

#endif //_CHANGEMONITOR_IDL_H_


extern RPC_IF_HANDLE __MIDL_itf_ChangeMonitor_0011_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ChangeMonitor_0011_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
