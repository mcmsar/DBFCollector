/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Feb 21 12:30:41 2008
 */
/* Compiler settings for ..\Common\Include\beacondecoder.idl:
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

#ifndef __beacondecoder_h__
#define __beacondecoder_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSBeaconDecoder_FWD_DEFINED__
#define __IEMSBeaconDecoder_FWD_DEFINED__
typedef interface IEMSBeaconDecoder IEMSBeaconDecoder;
#endif 	/* __IEMSBeaconDecoder_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emsbeacontype.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_beacondecoder_0000 */
/* [local] */ 

// {C6D6C252-FD77-4f2a-B478-371B0D2F626C}
DEFINE_GUID(IID_IEMSBeaconDecoder, 0xc6d6c252, 0xfd77, 0x4f2a, 0xb4, 0x78, 0x37, 0x1b, 0xd, 0x2f, 0x62, 0x6c);


extern RPC_IF_HANDLE __MIDL_itf_beacondecoder_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_beacondecoder_0000_v0_0_s_ifspec;

#ifndef __IEMSBeaconDecoder_INTERFACE_DEFINED__
#define __IEMSBeaconDecoder_INTERFACE_DEFINED__

/* interface IEMSBeaconDecoder */
/* [object][unique][helpstring][uuid] */ 

typedef struct  tagBeaconLocation
    {
    INT64 i64BeaconID;
    BOOL bHasGPSLocation;
    double dLat;
    double dLong;
    }	EMSBEACONLOCATION;


EXTERN_C const IID IID_IEMSBeaconDecoder;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C6D6C252-FD77-4f2a-B478-371B0D2F626C")
    IEMSBeaconDecoder : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetBeaconID( 
            /* [string][in] */ const char __RPC_FAR *cszBeaconData,
            /* [out] */ INT64 __RPC_FAR *pi64BeaconID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBeaconLocation( 
            /* [string][in] */ const char __RPC_FAR *cszBeaconData,
            /* [out] */ EMSBEACONLOCATION __RPC_FAR *pstrLocation) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBeaconType( 
            /* [string][in] */ const char __RPC_FAR *cszBeaconData,
            /* [out] */ EMSBEACONTYPE __RPC_FAR *peBeaconType) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSBeaconDecoderVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSBeaconDecoder __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSBeaconDecoder __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSBeaconDecoder __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBeaconID )( 
            IEMSBeaconDecoder __RPC_FAR * This,
            /* [string][in] */ const char __RPC_FAR *cszBeaconData,
            /* [out] */ INT64 __RPC_FAR *pi64BeaconID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBeaconLocation )( 
            IEMSBeaconDecoder __RPC_FAR * This,
            /* [string][in] */ const char __RPC_FAR *cszBeaconData,
            /* [out] */ EMSBEACONLOCATION __RPC_FAR *pstrLocation);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBeaconType )( 
            IEMSBeaconDecoder __RPC_FAR * This,
            /* [string][in] */ const char __RPC_FAR *cszBeaconData,
            /* [out] */ EMSBEACONTYPE __RPC_FAR *peBeaconType);
        
        END_INTERFACE
    } IEMSBeaconDecoderVtbl;

    interface IEMSBeaconDecoder
    {
        CONST_VTBL struct IEMSBeaconDecoderVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSBeaconDecoder_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSBeaconDecoder_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSBeaconDecoder_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSBeaconDecoder_GetBeaconID(This,cszBeaconData,pi64BeaconID)	\
    (This)->lpVtbl -> GetBeaconID(This,cszBeaconData,pi64BeaconID)

#define IEMSBeaconDecoder_GetBeaconLocation(This,cszBeaconData,pstrLocation)	\
    (This)->lpVtbl -> GetBeaconLocation(This,cszBeaconData,pstrLocation)

#define IEMSBeaconDecoder_GetBeaconType(This,cszBeaconData,peBeaconType)	\
    (This)->lpVtbl -> GetBeaconType(This,cszBeaconData,peBeaconType)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSBeaconDecoder_GetBeaconID_Proxy( 
    IEMSBeaconDecoder __RPC_FAR * This,
    /* [string][in] */ const char __RPC_FAR *cszBeaconData,
    /* [out] */ INT64 __RPC_FAR *pi64BeaconID);


void __RPC_STUB IEMSBeaconDecoder_GetBeaconID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSBeaconDecoder_GetBeaconLocation_Proxy( 
    IEMSBeaconDecoder __RPC_FAR * This,
    /* [string][in] */ const char __RPC_FAR *cszBeaconData,
    /* [out] */ EMSBEACONLOCATION __RPC_FAR *pstrLocation);


void __RPC_STUB IEMSBeaconDecoder_GetBeaconLocation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSBeaconDecoder_GetBeaconType_Proxy( 
    IEMSBeaconDecoder __RPC_FAR * This,
    /* [string][in] */ const char __RPC_FAR *cszBeaconData,
    /* [out] */ EMSBEACONTYPE __RPC_FAR *peBeaconType);


void __RPC_STUB IEMSBeaconDecoder_GetBeaconType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSBeaconDecoder_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
