/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Apr 05 14:55:03 2007
 */
/* Compiler settings for emsadboard.idl:
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

#ifndef __emsadboard_h__
#define __emsadboard_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSADBoard_FWD_DEFINED__
#define __IEMSADBoard_FWD_DEFINED__
typedef interface IEMSADBoard IEMSADBoard;
#endif 	/* __IEMSADBoard_FWD_DEFINED__ */


#ifndef __IEMSADMultiBoard_FWD_DEFINED__
#define __IEMSADMultiBoard_FWD_DEFINED__
typedef interface IEMSADMultiBoard IEMSADMultiBoard;
#endif 	/* __IEMSADMultiBoard_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_emsadboard_0000 */
/* [local] */ 

// {46E23647-EEF1-4be7-872A-C94C6F8E74E5}
DEFINE_GUID( CLSID_EMSADBoard, 0x46e23647, 0xeef1, 0x4be7, 0x87, 0x2a, 0xc9, 0x4c, 0x6f, 0x8e, 0x74, 0xe5);
 
// {9BA6B8EC-F069-485b-AEEE-1F1F517BDD54}
DEFINE_GUID( IID_IEMSADBoard, 0x9ba6b8ec, 0xf069, 0x485b, 0xae, 0xee, 0x1f, 0x1f, 0x51, 0x7b, 0xdd, 0x54);
 
// {E638A167-CC54-4b53-8A13-8E765AD04C40}
DEFINE_GUID( IID_IEMSADMultiBoard, 0xe638a167, 0xcc54, 0x4b53, 0x8a, 0x13, 0x8e, 0x76, 0x5a, 0xd0, 0x4c, 0x40);
 
#ifdef UNICODE
#define GetVersionInfo GetVersionInfoW
#else
#define GetVersionInfo GetVersionInfoA
#endif


extern RPC_IF_HANDLE __MIDL_itf_emsadboard_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_emsadboard_0000_v0_0_s_ifspec;

#ifndef __IEMSADBoard_INTERFACE_DEFINED__
#define __IEMSADBoard_INTERFACE_DEFINED__

/* interface IEMSADBoard */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSADBoard;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9BA6B8EC-F069-485b-AEEE-1F1F517BDD54")
    IEMSADBoard : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Init( 
            DWORD dwBufferSize,
            DWORD dwSampleSize,
            DWORD dwSampleRate) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Start( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Pause( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Continue( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetTransferBuffer( 
            short __RPC_FAR *lpBuffer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE LockBuffer( 
            BOOL bWait) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnlockBuffer( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBlockCount( 
            INT64 __RPC_FAR *lpi64Count) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDropoutCount( 
            INT64 __RPC_FAR *lpi64Count) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetDropoutCount( 
            INT64 i64Count) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBufferTime( 
            EMSTIME __RPC_FAR *lpTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMarkerTimeOffset( 
            INT64 __RPC_FAR *lpi64TimeOffset) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetEventNameA( 
            unsigned char __RPC_FAR *lpszEventName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetEventNameW( 
            WCHAR __RPC_FAR *lpszEventName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVersionInfoA( 
            WORD __RPC_FAR *lpwVersion,
            unsigned char __RPC_FAR *lpszModel,
            WORD wMax,
            WORD __RPC_FAR *lpwLength) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVersionInfoW( 
            WORD __RPC_FAR *lpwVersion,
            WCHAR __RPC_FAR *lpszModel,
            WORD wMax,
            WORD __RPC_FAR *lpwLength) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSADBoardVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSADBoard __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSADBoard __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSADBoard __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Init )( 
            IEMSADBoard __RPC_FAR * This,
            DWORD dwBufferSize,
            DWORD dwSampleSize,
            DWORD dwSampleRate);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEMSADBoard __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Start )( 
            IEMSADBoard __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IEMSADBoard __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Pause )( 
            IEMSADBoard __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Continue )( 
            IEMSADBoard __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTransferBuffer )( 
            IEMSADBoard __RPC_FAR * This,
            short __RPC_FAR *lpBuffer);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LockBuffer )( 
            IEMSADBoard __RPC_FAR * This,
            BOOL bWait);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UnlockBuffer )( 
            IEMSADBoard __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBlockCount )( 
            IEMSADBoard __RPC_FAR * This,
            INT64 __RPC_FAR *lpi64Count);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDropoutCount )( 
            IEMSADBoard __RPC_FAR * This,
            INT64 __RPC_FAR *lpi64Count);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetDropoutCount )( 
            IEMSADBoard __RPC_FAR * This,
            INT64 i64Count);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBufferTime )( 
            IEMSADBoard __RPC_FAR * This,
            EMSTIME __RPC_FAR *lpTime);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMarkerTimeOffset )( 
            IEMSADBoard __RPC_FAR * This,
            INT64 __RPC_FAR *lpi64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetEventNameA )( 
            IEMSADBoard __RPC_FAR * This,
            unsigned char __RPC_FAR *lpszEventName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetEventNameW )( 
            IEMSADBoard __RPC_FAR * This,
            WCHAR __RPC_FAR *lpszEventName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVersionInfoA )( 
            IEMSADBoard __RPC_FAR * This,
            WORD __RPC_FAR *lpwVersion,
            unsigned char __RPC_FAR *lpszModel,
            WORD wMax,
            WORD __RPC_FAR *lpwLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVersionInfoW )( 
            IEMSADBoard __RPC_FAR * This,
            WORD __RPC_FAR *lpwVersion,
            WCHAR __RPC_FAR *lpszModel,
            WORD wMax,
            WORD __RPC_FAR *lpwLength);
        
        END_INTERFACE
    } IEMSADBoardVtbl;

    interface IEMSADBoard
    {
        CONST_VTBL struct IEMSADBoardVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSADBoard_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSADBoard_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSADBoard_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSADBoard_Init(This,dwBufferSize,dwSampleSize,dwSampleRate)	\
    (This)->lpVtbl -> Init(This,dwBufferSize,dwSampleSize,dwSampleRate)

#define IEMSADBoard_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEMSADBoard_Start(This)	\
    (This)->lpVtbl -> Start(This)

#define IEMSADBoard_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IEMSADBoard_Pause(This)	\
    (This)->lpVtbl -> Pause(This)

#define IEMSADBoard_Continue(This)	\
    (This)->lpVtbl -> Continue(This)

#define IEMSADBoard_SetTransferBuffer(This,lpBuffer)	\
    (This)->lpVtbl -> SetTransferBuffer(This,lpBuffer)

#define IEMSADBoard_LockBuffer(This,bWait)	\
    (This)->lpVtbl -> LockBuffer(This,bWait)

#define IEMSADBoard_UnlockBuffer(This)	\
    (This)->lpVtbl -> UnlockBuffer(This)

#define IEMSADBoard_GetBlockCount(This,lpi64Count)	\
    (This)->lpVtbl -> GetBlockCount(This,lpi64Count)

#define IEMSADBoard_GetDropoutCount(This,lpi64Count)	\
    (This)->lpVtbl -> GetDropoutCount(This,lpi64Count)

#define IEMSADBoard_SetDropoutCount(This,i64Count)	\
    (This)->lpVtbl -> SetDropoutCount(This,i64Count)

#define IEMSADBoard_GetBufferTime(This,lpTime)	\
    (This)->lpVtbl -> GetBufferTime(This,lpTime)

#define IEMSADBoard_GetMarkerTimeOffset(This,lpi64TimeOffset)	\
    (This)->lpVtbl -> GetMarkerTimeOffset(This,lpi64TimeOffset)

#define IEMSADBoard_SetEventNameA(This,lpszEventName)	\
    (This)->lpVtbl -> SetEventNameA(This,lpszEventName)

#define IEMSADBoard_SetEventNameW(This,lpszEventName)	\
    (This)->lpVtbl -> SetEventNameW(This,lpszEventName)

#define IEMSADBoard_GetVersionInfoA(This,lpwVersion,lpszModel,wMax,lpwLength)	\
    (This)->lpVtbl -> GetVersionInfoA(This,lpwVersion,lpszModel,wMax,lpwLength)

#define IEMSADBoard_GetVersionInfoW(This,lpwVersion,lpszModel,wMax,lpwLength)	\
    (This)->lpVtbl -> GetVersionInfoW(This,lpwVersion,lpszModel,wMax,lpwLength)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSADBoard_Init_Proxy( 
    IEMSADBoard __RPC_FAR * This,
    DWORD dwBufferSize,
    DWORD dwSampleSize,
    DWORD dwSampleRate);


void __RPC_STUB IEMSADBoard_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSADBoard_Reset_Proxy( 
    IEMSADBoard __RPC_FAR * This);


void __RPC_STUB IEMSADBoard_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSADBoard_Start_Proxy( 
    IEMSADBoard __RPC_FAR * This);


void __RPC_STUB IEMSADBoard_Start_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSADBoard_Stop_Proxy( 
    IEMSADBoard __RPC_FAR * This);


void __RPC_STUB IEMSADBoard_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSADBoard_Pause_Proxy( 
    IEMSADBoard __RPC_FAR * This);


void __RPC_STUB IEMSADBoard_Pause_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSADBoard_Continue_Proxy( 
    IEMSADBoard __RPC_FAR * This);


void __RPC_STUB IEMSADBoard_Continue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSADBoard_SetTransferBuffer_Proxy( 
    IEMSADBoard __RPC_FAR * This,
    short __RPC_FAR *lpBuffer);


void __RPC_STUB IEMSADBoard_SetTransferBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSADBoard_LockBuffer_Proxy( 
    IEMSADBoard __RPC_FAR * This,
    BOOL bWait);


void __RPC_STUB IEMSADBoard_LockBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSADBoard_UnlockBuffer_Proxy( 
    IEMSADBoard __RPC_FAR * This);


void __RPC_STUB IEMSADBoard_UnlockBuffer_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSADBoard_GetBlockCount_Proxy( 
    IEMSADBoard __RPC_FAR * This,
    INT64 __RPC_FAR *lpi64Count);


void __RPC_STUB IEMSADBoard_GetBlockCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSADBoard_GetDropoutCount_Proxy( 
    IEMSADBoard __RPC_FAR * This,
    INT64 __RPC_FAR *lpi64Count);


void __RPC_STUB IEMSADBoard_GetDropoutCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSADBoard_SetDropoutCount_Proxy( 
    IEMSADBoard __RPC_FAR * This,
    INT64 i64Count);


void __RPC_STUB IEMSADBoard_SetDropoutCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSADBoard_GetBufferTime_Proxy( 
    IEMSADBoard __RPC_FAR * This,
    EMSTIME __RPC_FAR *lpTime);


void __RPC_STUB IEMSADBoard_GetBufferTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSADBoard_GetMarkerTimeOffset_Proxy( 
    IEMSADBoard __RPC_FAR * This,
    INT64 __RPC_FAR *lpi64TimeOffset);


void __RPC_STUB IEMSADBoard_GetMarkerTimeOffset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSADBoard_SetEventNameA_Proxy( 
    IEMSADBoard __RPC_FAR * This,
    unsigned char __RPC_FAR *lpszEventName);


void __RPC_STUB IEMSADBoard_SetEventNameA_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSADBoard_SetEventNameW_Proxy( 
    IEMSADBoard __RPC_FAR * This,
    WCHAR __RPC_FAR *lpszEventName);


void __RPC_STUB IEMSADBoard_SetEventNameW_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSADBoard_GetVersionInfoA_Proxy( 
    IEMSADBoard __RPC_FAR * This,
    WORD __RPC_FAR *lpwVersion,
    unsigned char __RPC_FAR *lpszModel,
    WORD wMax,
    WORD __RPC_FAR *lpwLength);


void __RPC_STUB IEMSADBoard_GetVersionInfoA_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSADBoard_GetVersionInfoW_Proxy( 
    IEMSADBoard __RPC_FAR * This,
    WORD __RPC_FAR *lpwVersion,
    WCHAR __RPC_FAR *lpszModel,
    WORD wMax,
    WORD __RPC_FAR *lpwLength);


void __RPC_STUB IEMSADBoard_GetVersionInfoW_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSADBoard_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_emsadboard_0008 */
/* [local] */ 

typedef /* [unique] */ IEMSADBoard __RPC_FAR *LPEMSADBOARD;



extern RPC_IF_HANDLE __MIDL_itf_emsadboard_0008_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_emsadboard_0008_v0_0_s_ifspec;

#ifndef __IEMSADMultiBoard_INTERFACE_DEFINED__
#define __IEMSADMultiBoard_INTERFACE_DEFINED__

/* interface IEMSADMultiBoard */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSADMultiBoard;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E638A167-CC54-4b53-8A13-8E765AD04C40")
    IEMSADMultiBoard : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetChannelCount( 
            /* [out] */ WORD __RPC_FAR *lpwCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetChannelInterface( 
            /* [in] */ WORD wChannel,
            /* [out] */ LPEMSADBOARD __RPC_FAR *lplpInterface) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StopAll( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSADMultiBoardVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSADMultiBoard __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSADMultiBoard __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSADMultiBoard __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetChannelCount )( 
            IEMSADMultiBoard __RPC_FAR * This,
            /* [out] */ WORD __RPC_FAR *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetChannelInterface )( 
            IEMSADMultiBoard __RPC_FAR * This,
            /* [in] */ WORD wChannel,
            /* [out] */ LPEMSADBOARD __RPC_FAR *lplpInterface);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StopAll )( 
            IEMSADMultiBoard __RPC_FAR * This);
        
        END_INTERFACE
    } IEMSADMultiBoardVtbl;

    interface IEMSADMultiBoard
    {
        CONST_VTBL struct IEMSADMultiBoardVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSADMultiBoard_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSADMultiBoard_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSADMultiBoard_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSADMultiBoard_GetChannelCount(This,lpwCount)	\
    (This)->lpVtbl -> GetChannelCount(This,lpwCount)

#define IEMSADMultiBoard_GetChannelInterface(This,wChannel,lplpInterface)	\
    (This)->lpVtbl -> GetChannelInterface(This,wChannel,lplpInterface)

#define IEMSADMultiBoard_StopAll(This)	\
    (This)->lpVtbl -> StopAll(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSADMultiBoard_GetChannelCount_Proxy( 
    IEMSADMultiBoard __RPC_FAR * This,
    /* [out] */ WORD __RPC_FAR *lpwCount);


void __RPC_STUB IEMSADMultiBoard_GetChannelCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSADMultiBoard_GetChannelInterface_Proxy( 
    IEMSADMultiBoard __RPC_FAR * This,
    /* [in] */ WORD wChannel,
    /* [out] */ LPEMSADBOARD __RPC_FAR *lplpInterface);


void __RPC_STUB IEMSADMultiBoard_GetChannelInterface_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSADMultiBoard_StopAll_Proxy( 
    IEMSADMultiBoard __RPC_FAR * This);


void __RPC_STUB IEMSADMultiBoard_StopAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSADMultiBoard_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_emsadboard_0009 */
/* [local] */ 

typedef /* [unique] */ IEMSADMultiBoard __RPC_FAR *LPEMSADMULTIBOARD;



extern RPC_IF_HANDLE __MIDL_itf_emsadboard_0009_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_emsadboard_0009_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
