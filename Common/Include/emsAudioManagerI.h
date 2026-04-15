/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Jan 09 18:38:02 2005
 */
/* Compiler settings for C:\dev\common\Include\emsAudioManagerI.idl:
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

#ifndef __emsAudioManagerI_h__
#define __emsAudioManagerI_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSAudioManager_FWD_DEFINED__
#define __IEMSAudioManager_FWD_DEFINED__
typedef interface IEMSAudioManager IEMSAudioManager;
#endif 	/* __IEMSAudioManager_FWD_DEFINED__ */


#ifndef __EMSAudioManager_FWD_DEFINED__
#define __EMSAudioManager_FWD_DEFINED__

#ifdef __cplusplus
typedef class EMSAudioManager EMSAudioManager;
#else
typedef struct EMSAudioManager EMSAudioManager;
#endif /* __cplusplus */

#endif 	/* __EMSAudioManager_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emsaudio.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_emsAudioManagerI_0000 */
/* [local] */ 


// {E027FBBF-A988-4863-825B-4D080E93572C}
DEFINE_GUID( CLSID_EMSAudioManager, 0xe027fbbf, 0xa988, 0x4863, 0x82, 0x5b, 0x4d, 0x8, 0xe, 0x93, 0x57, 0x2c);

// {D4F86CA8-617F-4967-97A0-EF122E0FBF95}
DEFINE_GUID( IID_IEMSAudioManager, 0xd4f86ca8, 0x617f, 0x4967, 0x97, 0xa0, 0xef, 0x12, 0x2e, 0xf, 0xbf, 0x95);



extern RPC_IF_HANDLE __MIDL_itf_emsAudioManagerI_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_emsAudioManagerI_0000_v0_0_s_ifspec;

#ifndef __IEMSAudioManager_INTERFACE_DEFINED__
#define __IEMSAudioManager_INTERFACE_DEFINED__

/* interface IEMSAudioManager */
/* [unique][uuid][object] */ 

typedef /* [unique] */ IEMSAudioManager __RPC_FAR *LPEMSAUDIOMANAGER;


EXTERN_C const IID IID_IEMSAudioManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D4F86CA8-617F-4967-97A0-EF122E0FBF95")
    IEMSAudioManager : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AudioConnect( 
            /* [out][in] */ unsigned long __RPC_FAR *ulSession) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AudioGetData( 
            /* [in] */ const unsigned long culSession,
            /* [size_is][out][in] */ unsigned char __RPC_FAR *pData,
            /* [out][in] */ unsigned int __RPC_FAR *pLen) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AudioSetParameters( 
            /* [in] */ const unsigned long culSession,
            /* [in] */ const float fCenterFreq,
            /* [in] */ const float fBandwidth) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AudioDisconnect( 
            /* [in] */ const unsigned long culSession) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MakeFreeRequest( 
            /* [in] */ EMSAUDIOREQUEST audreq,
            /* [out][in] */ unsigned long __RPC_FAR *pulSessionID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFreeRequestData( 
            /* [in] */ unsigned long ulSessionID,
            /* [out][in] */ EMSAUDIODATARECORD_RIFF __RPC_FAR *audrec) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CancelFreeRequest( 
            /* [in] */ unsigned long ulSessionID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSAudioManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSAudioManager __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSAudioManager __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSAudioManager __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AudioConnect )( 
            IEMSAudioManager __RPC_FAR * This,
            /* [out][in] */ unsigned long __RPC_FAR *ulSession);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AudioGetData )( 
            IEMSAudioManager __RPC_FAR * This,
            /* [in] */ const unsigned long culSession,
            /* [size_is][out][in] */ unsigned char __RPC_FAR *pData,
            /* [out][in] */ unsigned int __RPC_FAR *pLen);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AudioSetParameters )( 
            IEMSAudioManager __RPC_FAR * This,
            /* [in] */ const unsigned long culSession,
            /* [in] */ const float fCenterFreq,
            /* [in] */ const float fBandwidth);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AudioDisconnect )( 
            IEMSAudioManager __RPC_FAR * This,
            /* [in] */ const unsigned long culSession);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MakeFreeRequest )( 
            IEMSAudioManager __RPC_FAR * This,
            /* [in] */ EMSAUDIOREQUEST audreq,
            /* [out][in] */ unsigned long __RPC_FAR *pulSessionID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFreeRequestData )( 
            IEMSAudioManager __RPC_FAR * This,
            /* [in] */ unsigned long ulSessionID,
            /* [out][in] */ EMSAUDIODATARECORD_RIFF __RPC_FAR *audrec);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CancelFreeRequest )( 
            IEMSAudioManager __RPC_FAR * This,
            /* [in] */ unsigned long ulSessionID);
        
        END_INTERFACE
    } IEMSAudioManagerVtbl;

    interface IEMSAudioManager
    {
        CONST_VTBL struct IEMSAudioManagerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSAudioManager_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSAudioManager_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSAudioManager_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSAudioManager_AudioConnect(This,ulSession)	\
    (This)->lpVtbl -> AudioConnect(This,ulSession)

#define IEMSAudioManager_AudioGetData(This,culSession,pData,pLen)	\
    (This)->lpVtbl -> AudioGetData(This,culSession,pData,pLen)

#define IEMSAudioManager_AudioSetParameters(This,culSession,fCenterFreq,fBandwidth)	\
    (This)->lpVtbl -> AudioSetParameters(This,culSession,fCenterFreq,fBandwidth)

#define IEMSAudioManager_AudioDisconnect(This,culSession)	\
    (This)->lpVtbl -> AudioDisconnect(This,culSession)

#define IEMSAudioManager_MakeFreeRequest(This,audreq,pulSessionID)	\
    (This)->lpVtbl -> MakeFreeRequest(This,audreq,pulSessionID)

#define IEMSAudioManager_GetFreeRequestData(This,ulSessionID,audrec)	\
    (This)->lpVtbl -> GetFreeRequestData(This,ulSessionID,audrec)

#define IEMSAudioManager_CancelFreeRequest(This,ulSessionID)	\
    (This)->lpVtbl -> CancelFreeRequest(This,ulSessionID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSAudioManager_AudioConnect_Proxy( 
    IEMSAudioManager __RPC_FAR * This,
    /* [out][in] */ unsigned long __RPC_FAR *ulSession);


void __RPC_STUB IEMSAudioManager_AudioConnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAudioManager_AudioGetData_Proxy( 
    IEMSAudioManager __RPC_FAR * This,
    /* [in] */ const unsigned long culSession,
    /* [size_is][out][in] */ unsigned char __RPC_FAR *pData,
    /* [out][in] */ unsigned int __RPC_FAR *pLen);


void __RPC_STUB IEMSAudioManager_AudioGetData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAudioManager_AudioSetParameters_Proxy( 
    IEMSAudioManager __RPC_FAR * This,
    /* [in] */ const unsigned long culSession,
    /* [in] */ const float fCenterFreq,
    /* [in] */ const float fBandwidth);


void __RPC_STUB IEMSAudioManager_AudioSetParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAudioManager_AudioDisconnect_Proxy( 
    IEMSAudioManager __RPC_FAR * This,
    /* [in] */ const unsigned long culSession);


void __RPC_STUB IEMSAudioManager_AudioDisconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAudioManager_MakeFreeRequest_Proxy( 
    IEMSAudioManager __RPC_FAR * This,
    /* [in] */ EMSAUDIOREQUEST audreq,
    /* [out][in] */ unsigned long __RPC_FAR *pulSessionID);


void __RPC_STUB IEMSAudioManager_MakeFreeRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAudioManager_GetFreeRequestData_Proxy( 
    IEMSAudioManager __RPC_FAR * This,
    /* [in] */ unsigned long ulSessionID,
    /* [out][in] */ EMSAUDIODATARECORD_RIFF __RPC_FAR *audrec);


void __RPC_STUB IEMSAudioManager_GetFreeRequestData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAudioManager_CancelFreeRequest_Proxy( 
    IEMSAudioManager __RPC_FAR * This,
    /* [in] */ unsigned long ulSessionID);


void __RPC_STUB IEMSAudioManager_CancelFreeRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSAudioManager_INTERFACE_DEFINED__ */



#ifndef __EMSAudioManagerLib_LIBRARY_DEFINED__
#define __EMSAudioManagerLib_LIBRARY_DEFINED__

/* library EMSAudioManagerLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_EMSAudioManagerLib;

EXTERN_C const CLSID CLSID_EMSAudioManager;

#ifdef __cplusplus

class DECLSPEC_UUID("E027FBBF-A988-4863-825B-4D080E93572C")
EMSAudioManager;
#endif
#endif /* __EMSAudioManagerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
