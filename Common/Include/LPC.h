

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Mon Feb 16 12:28:37 2004
 */
/* Compiler settings for ..\Common\Include\LPC.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
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

#ifndef __LPC_h__
#define __LPC_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IEMSLPC_FWD_DEFINED__
#define __IEMSLPC_FWD_DEFINED__
typedef interface IEMSLPC IEMSLPC;
#endif 	/* __IEMSLPC_FWD_DEFINED__ */


/* header files for imported files */
#include "igateway.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_LPC_0000 */
/* [local] */ 

// {D98983C2-8E44-4185-82C7-C7B6ED688B17}
DEFINE_GUID(IID_IEMSLPC, 0xd98983c2, 0x8e44, 0x4185, 0x82, 0xc7, 0xc7, 0xb6, 0xed, 0x68, 0x8b, 0x17);
// {3CFE2B64-9CDB-4fd2-BE2D-C452509322B1}
DEFINE_GUID(CLSID_EMSLPC, 0x3cfe2b64, 0x9cdb, 0x4fd2, 0xbe, 0x2d, 0xc4, 0x52, 0x50, 0x93, 0x22, 0xb1);


extern RPC_IF_HANDLE __MIDL_itf_LPC_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_LPC_0000_v0_0_s_ifspec;

#ifndef __IEMSLPC_INTERFACE_DEFINED__
#define __IEMSLPC_INTERFACE_DEFINED__

/* interface IEMSLPC */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IEMSLPC;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D98983C2-8E44-4185-82C7-C7B6ED688B17")
    IEMSLPC : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE InitManualProcessing( 
            /* [string][in] */ wchar_t *wszWhereClause,
            /* [out] */ unsigned long *pulSessionID,
            /* [out][in] */ unsigned long *pulRecords,
            /* [size_is][size_is][out] */ EMSCALIB406DATA **paBeaconData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InitManual( 
            /* [string][in] */ const wchar_t *cwszWhereClause,
            /* [in] */ const EMSMANUALPROCESSINGMODE ceProcessingMode,
            /* [out] */ unsigned long *pulSessionID,
            /* [out][in] */ unsigned long *pulRecords,
            /* [size_is][size_is][out] */ EMSVARIANTRECORD **paData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveDataFromSet( 
            /* [in] */ const unsigned long culSessionID,
            /* [in] */ const unsigned long culCount,
            /* [size_is][in] */ const unsigned long *caulIndex) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Process406( 
            /* [in] */ const unsigned long culSessionID,
            /* [string][in] */ const wchar_t *cwszControlFilename,
            /* [out][in] */ unsigned long *pulResults,
            /* [size_is][size_is][out] */ EMSLOCATE **paLocations) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CancelSession( 
            /* [in] */ const unsigned long culSessionID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetControlFilenames( 
            /* [out] */ unsigned long *pulCount,
            /* [size_is][size_is][string][out] */ wchar_t ***ppaControlFilenames) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSLPCVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEMSLPC * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEMSLPC * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEMSLPC * This);
        
        HRESULT ( STDMETHODCALLTYPE *InitManualProcessing )( 
            IEMSLPC * This,
            /* [string][in] */ wchar_t *wszWhereClause,
            /* [out] */ unsigned long *pulSessionID,
            /* [out][in] */ unsigned long *pulRecords,
            /* [size_is][size_is][out] */ EMSCALIB406DATA **paBeaconData);
        
        HRESULT ( STDMETHODCALLTYPE *InitManual )( 
            IEMSLPC * This,
            /* [string][in] */ const wchar_t *cwszWhereClause,
            /* [in] */ const EMSMANUALPROCESSINGMODE ceProcessingMode,
            /* [out] */ unsigned long *pulSessionID,
            /* [out][in] */ unsigned long *pulRecords,
            /* [size_is][size_is][out] */ EMSVARIANTRECORD **paData);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveDataFromSet )( 
            IEMSLPC * This,
            /* [in] */ const unsigned long culSessionID,
            /* [in] */ const unsigned long culCount,
            /* [size_is][in] */ const unsigned long *caulIndex);
        
        HRESULT ( STDMETHODCALLTYPE *Process406 )( 
            IEMSLPC * This,
            /* [in] */ const unsigned long culSessionID,
            /* [string][in] */ const wchar_t *cwszControlFilename,
            /* [out][in] */ unsigned long *pulResults,
            /* [size_is][size_is][out] */ EMSLOCATE **paLocations);
        
        HRESULT ( STDMETHODCALLTYPE *CancelSession )( 
            IEMSLPC * This,
            /* [in] */ const unsigned long culSessionID);
        
        HRESULT ( STDMETHODCALLTYPE *GetControlFilenames )( 
            IEMSLPC * This,
            /* [out] */ unsigned long *pulCount,
            /* [size_is][size_is][string][out] */ wchar_t ***ppaControlFilenames);
        
        END_INTERFACE
    } IEMSLPCVtbl;

    interface IEMSLPC
    {
        CONST_VTBL struct IEMSLPCVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSLPC_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSLPC_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSLPC_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSLPC_InitManualProcessing(This,wszWhereClause,pulSessionID,pulRecords,paBeaconData)	\
    (This)->lpVtbl -> InitManualProcessing(This,wszWhereClause,pulSessionID,pulRecords,paBeaconData)

#define IEMSLPC_InitManual(This,cwszWhereClause,ceProcessingMode,pulSessionID,pulRecords,paData)	\
    (This)->lpVtbl -> InitManual(This,cwszWhereClause,ceProcessingMode,pulSessionID,pulRecords,paData)

#define IEMSLPC_RemoveDataFromSet(This,culSessionID,culCount,caulIndex)	\
    (This)->lpVtbl -> RemoveDataFromSet(This,culSessionID,culCount,caulIndex)

#define IEMSLPC_Process406(This,culSessionID,cwszControlFilename,pulResults,paLocations)	\
    (This)->lpVtbl -> Process406(This,culSessionID,cwszControlFilename,pulResults,paLocations)

#define IEMSLPC_CancelSession(This,culSessionID)	\
    (This)->lpVtbl -> CancelSession(This,culSessionID)

#define IEMSLPC_GetControlFilenames(This,pulCount,ppaControlFilenames)	\
    (This)->lpVtbl -> GetControlFilenames(This,pulCount,ppaControlFilenames)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSLPC_InitManualProcessing_Proxy( 
    IEMSLPC * This,
    /* [string][in] */ wchar_t *wszWhereClause,
    /* [out] */ unsigned long *pulSessionID,
    /* [out][in] */ unsigned long *pulRecords,
    /* [size_is][size_is][out] */ EMSCALIB406DATA **paBeaconData);


void __RPC_STUB IEMSLPC_InitManualProcessing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSLPC_InitManual_Proxy( 
    IEMSLPC * This,
    /* [string][in] */ const wchar_t *cwszWhereClause,
    /* [in] */ const EMSMANUALPROCESSINGMODE ceProcessingMode,
    /* [out] */ unsigned long *pulSessionID,
    /* [out][in] */ unsigned long *pulRecords,
    /* [size_is][size_is][out] */ EMSVARIANTRECORD **paData);


void __RPC_STUB IEMSLPC_InitManual_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSLPC_RemoveDataFromSet_Proxy( 
    IEMSLPC * This,
    /* [in] */ const unsigned long culSessionID,
    /* [in] */ const unsigned long culCount,
    /* [size_is][in] */ const unsigned long *caulIndex);


void __RPC_STUB IEMSLPC_RemoveDataFromSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSLPC_Process406_Proxy( 
    IEMSLPC * This,
    /* [in] */ const unsigned long culSessionID,
    /* [string][in] */ const wchar_t *cwszControlFilename,
    /* [out][in] */ unsigned long *pulResults,
    /* [size_is][size_is][out] */ EMSLOCATE **paLocations);


void __RPC_STUB IEMSLPC_Process406_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSLPC_CancelSession_Proxy( 
    IEMSLPC * This,
    /* [in] */ const unsigned long culSessionID);


void __RPC_STUB IEMSLPC_CancelSession_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSLPC_GetControlFilenames_Proxy( 
    IEMSLPC * This,
    /* [out] */ unsigned long *pulCount,
    /* [size_is][size_is][string][out] */ wchar_t ***ppaControlFilenames);


void __RPC_STUB IEMSLPC_GetControlFilenames_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSLPC_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


