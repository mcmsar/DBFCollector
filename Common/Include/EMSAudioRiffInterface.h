/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue May 24 13:01:32 2005
 */
/* Compiler settings for D:\dev\common\Include\EMSAudioRiffInterface.idl:
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

#ifndef __EMSAudioRiffInterface_h__
#define __EMSAudioRiffInterface_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSAudioRiffInterface_FWD_DEFINED__
#define __IEMSAudioRiffInterface_FWD_DEFINED__
typedef interface IEMSAudioRiffInterface IEMSAudioRiffInterface;
#endif 	/* __IEMSAudioRiffInterface_FWD_DEFINED__ */


#ifndef __IEMSAudioStream_FWD_DEFINED__
#define __IEMSAudioStream_FWD_DEFINED__
typedef interface IEMSAudioStream IEMSAudioStream;
#endif 	/* __IEMSAudioStream_FWD_DEFINED__ */


#ifndef __IEMSAudioStream2_FWD_DEFINED__
#define __IEMSAudioStream2_FWD_DEFINED__
typedef interface IEMSAudioStream2 IEMSAudioStream2;
#endif 	/* __IEMSAudioStream2_FWD_DEFINED__ */


#ifndef __IEMSAudioRiffDataStream_FWD_DEFINED__
#define __IEMSAudioRiffDataStream_FWD_DEFINED__
typedef interface IEMSAudioRiffDataStream IEMSAudioRiffDataStream;
#endif 	/* __IEMSAudioRiffDataStream_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emsaudio.h"
#include "igateway.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_EMSAudioRiffInterface_0000 */
/* [local] */ 

 
#include "emserror.h"
 
// {92B437C4-D022-43d0-AEEF-FD153D019E6D}
DEFINE_GUID( IID_IEMSAudioRiffDataStream, 0x92b437c4, 0xd022, 0x43d0, 0xae, 0xef, 0xfd, 0x15, 0x3d, 0x1, 0x9e, 0x6d);
// {90903D19-13F4-41a7-8BB8-ABC541A3E9D7}
DEFINE_GUID( CLSID_EMSAudioInterface, 0x90903d19, 0x13f4, 0x41a7, 0x8b, 0xb8, 0xab, 0xc5, 0x41, 0xa3, 0xe9, 0xd7);
// {0E2ED242-DE88-4e08-9A5A-52359A17FE14}
DEFINE_GUID( IID_IEMSAudioRiffInterface, 0xe2ed242, 0xde88, 0x4e08, 0x9a, 0x5a, 0x52, 0x35, 0x9a, 0x17, 0xfe, 0x14);
// {F25795DC-0A43-46cf-9376-B2168A30F095}
DEFINE_GUID( IID_IEMSAudioStream, 0xf25795dc, 0xa43, 0x46cf, 0x93, 0x76, 0xb2, 0x16, 0x8a, 0x30, 0xf0, 0x95);
// {E2EDFFE6-E40C-4aa7-81EC-5F5900DCBD86}
DEFINE_GUID( IID_IEMSAudioStream2, 0xe2edffe6, 0xe40c, 0x4aa7, 0x81, 0xec, 0x5f, 0x59, 0x0, 0xdc, 0xbd, 0x86);
#define CLSID_EMSAudioRiffInterface CLSID_EMSAudioInterface


extern RPC_IF_HANDLE __MIDL_itf_EMSAudioRiffInterface_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSAudioRiffInterface_0000_v0_0_s_ifspec;

#ifndef __IEMSAudioRiffInterface_INTERFACE_DEFINED__
#define __IEMSAudioRiffInterface_INTERFACE_DEFINED__

/* interface IEMSAudioRiffInterface */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSAudioRiffInterface;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0E2ED242-DE88-4e08-9A5A-52359A17FE14")
    IEMSAudioRiffInterface : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE getAudioRiffData( 
            /* [in] */ EMSAUDIOSELECTCRITERIA __RPC_FAR *pAudioCriteria,
            /* [string][in] */ const wchar_t __RPC_FAR *szFileName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE getAudioRiffDataDAL( 
            /* [in] */ unsigned long ulSourceID,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ const unsigned long culMaxRecords,
            /* [in] */ EMSAUDIOSELECTCRITERIA __RPC_FAR *pAudioCriteria,
            /* [string][in] */ const wchar_t __RPC_FAR *szFileName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE cancel( 
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE MakeRequestAssinchronus( 
            /* [in] */ unsigned long ulSourceID,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ const unsigned long culMaxRecords,
            /* [in] */ EMSAUDIOSELECTCRITERIA __RPC_FAR *pAudioCriteria) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDataAssinchronus( 
            /* [out][in] */ short __RPC_FAR *pData,
            /* [out][in] */ unsigned int __RPC_FAR *pLen,
            /* [out][in] */ unsigned int __RPC_FAR *pSamplPerSec) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSAudioRiffInterfaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSAudioRiffInterface __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSAudioRiffInterface __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSAudioRiffInterface __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getAudioRiffData )( 
            IEMSAudioRiffInterface __RPC_FAR * This,
            /* [in] */ EMSAUDIOSELECTCRITERIA __RPC_FAR *pAudioCriteria,
            /* [string][in] */ const wchar_t __RPC_FAR *szFileName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *getAudioRiffDataDAL )( 
            IEMSAudioRiffInterface __RPC_FAR * This,
            /* [in] */ unsigned long ulSourceID,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ const unsigned long culMaxRecords,
            /* [in] */ EMSAUDIOSELECTCRITERIA __RPC_FAR *pAudioCriteria,
            /* [string][in] */ const wchar_t __RPC_FAR *szFileName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *cancel )( 
            IEMSAudioRiffInterface __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MakeRequestAssinchronus )( 
            IEMSAudioRiffInterface __RPC_FAR * This,
            /* [in] */ unsigned long ulSourceID,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ const unsigned long culMaxRecords,
            /* [in] */ EMSAUDIOSELECTCRITERIA __RPC_FAR *pAudioCriteria);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDataAssinchronus )( 
            IEMSAudioRiffInterface __RPC_FAR * This,
            /* [out][in] */ short __RPC_FAR *pData,
            /* [out][in] */ unsigned int __RPC_FAR *pLen,
            /* [out][in] */ unsigned int __RPC_FAR *pSamplPerSec);
        
        END_INTERFACE
    } IEMSAudioRiffInterfaceVtbl;

    interface IEMSAudioRiffInterface
    {
        CONST_VTBL struct IEMSAudioRiffInterfaceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSAudioRiffInterface_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSAudioRiffInterface_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSAudioRiffInterface_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSAudioRiffInterface_getAudioRiffData(This,pAudioCriteria,szFileName)	\
    (This)->lpVtbl -> getAudioRiffData(This,pAudioCriteria,szFileName)

#define IEMSAudioRiffInterface_getAudioRiffDataDAL(This,ulSourceID,ulDestID,psecToken,culMaxRecords,pAudioCriteria,szFileName)	\
    (This)->lpVtbl -> getAudioRiffDataDAL(This,ulSourceID,ulDestID,psecToken,culMaxRecords,pAudioCriteria,szFileName)

#define IEMSAudioRiffInterface_cancel(This,dwFlags)	\
    (This)->lpVtbl -> cancel(This,dwFlags)

#define IEMSAudioRiffInterface_MakeRequestAssinchronus(This,ulSourceID,ulDestID,culMaxRecords,pAudioCriteria)	\
    (This)->lpVtbl -> MakeRequestAssinchronus(This,ulSourceID,ulDestID,culMaxRecords,pAudioCriteria)

#define IEMSAudioRiffInterface_GetDataAssinchronus(This,pData,pLen,pSamplPerSec)	\
    (This)->lpVtbl -> GetDataAssinchronus(This,pData,pLen,pSamplPerSec)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSAudioRiffInterface_getAudioRiffData_Proxy( 
    IEMSAudioRiffInterface __RPC_FAR * This,
    /* [in] */ EMSAUDIOSELECTCRITERIA __RPC_FAR *pAudioCriteria,
    /* [string][in] */ const wchar_t __RPC_FAR *szFileName);


void __RPC_STUB IEMSAudioRiffInterface_getAudioRiffData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAudioRiffInterface_getAudioRiffDataDAL_Proxy( 
    IEMSAudioRiffInterface __RPC_FAR * This,
    /* [in] */ unsigned long ulSourceID,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ const unsigned long culMaxRecords,
    /* [in] */ EMSAUDIOSELECTCRITERIA __RPC_FAR *pAudioCriteria,
    /* [string][in] */ const wchar_t __RPC_FAR *szFileName);


void __RPC_STUB IEMSAudioRiffInterface_getAudioRiffDataDAL_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAudioRiffInterface_cancel_Proxy( 
    IEMSAudioRiffInterface __RPC_FAR * This,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IEMSAudioRiffInterface_cancel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAudioRiffInterface_MakeRequestAssinchronus_Proxy( 
    IEMSAudioRiffInterface __RPC_FAR * This,
    /* [in] */ unsigned long ulSourceID,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ const unsigned long culMaxRecords,
    /* [in] */ EMSAUDIOSELECTCRITERIA __RPC_FAR *pAudioCriteria);


void __RPC_STUB IEMSAudioRiffInterface_MakeRequestAssinchronus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAudioRiffInterface_GetDataAssinchronus_Proxy( 
    IEMSAudioRiffInterface __RPC_FAR * This,
    /* [out][in] */ short __RPC_FAR *pData,
    /* [out][in] */ unsigned int __RPC_FAR *pLen,
    /* [out][in] */ unsigned int __RPC_FAR *pSamplPerSec);


void __RPC_STUB IEMSAudioRiffInterface_GetDataAssinchronus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSAudioRiffInterface_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSAudioRiffInterface_0339 */
/* [local] */ 

typedef /* [unique] */ IEMSAudioRiffInterface __RPC_FAR *LPEMSAUDIORIFFINTERFACE;



extern RPC_IF_HANDLE __MIDL_itf_EMSAudioRiffInterface_0339_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSAudioRiffInterface_0339_v0_0_s_ifspec;

#ifndef __IEMSAudioStream_INTERFACE_DEFINED__
#define __IEMSAudioStream_INTERFACE_DEFINED__

/* interface IEMSAudioStream */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSAudioStream;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F25795DC-0A43-46cf-9376-B2168A30F095")
    IEMSAudioStream : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Connect( 
            /* [in] */ const unsigned long ulSourceID,
            /* [in] */ const unsigned long culLutID,
            /* [in] */ const unsigned long culBufferSize) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Disconnect( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetParameters( 
            /* [in] */ const float fCenterFreq,
            /* [in] */ const float fBandwidth) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetData( 
            /* [out][in] */ short __RPC_FAR *pData,
            /* [out][in] */ unsigned int __RPC_FAR *pLen) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSAudioStreamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSAudioStream __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSAudioStream __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSAudioStream __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Connect )( 
            IEMSAudioStream __RPC_FAR * This,
            /* [in] */ const unsigned long ulSourceID,
            /* [in] */ const unsigned long culLutID,
            /* [in] */ const unsigned long culBufferSize);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Disconnect )( 
            IEMSAudioStream __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetParameters )( 
            IEMSAudioStream __RPC_FAR * This,
            /* [in] */ const float fCenterFreq,
            /* [in] */ const float fBandwidth);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetData )( 
            IEMSAudioStream __RPC_FAR * This,
            /* [out][in] */ short __RPC_FAR *pData,
            /* [out][in] */ unsigned int __RPC_FAR *pLen);
        
        END_INTERFACE
    } IEMSAudioStreamVtbl;

    interface IEMSAudioStream
    {
        CONST_VTBL struct IEMSAudioStreamVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSAudioStream_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSAudioStream_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSAudioStream_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSAudioStream_Connect(This,ulSourceID,culLutID,culBufferSize)	\
    (This)->lpVtbl -> Connect(This,ulSourceID,culLutID,culBufferSize)

#define IEMSAudioStream_Disconnect(This)	\
    (This)->lpVtbl -> Disconnect(This)

#define IEMSAudioStream_SetParameters(This,fCenterFreq,fBandwidth)	\
    (This)->lpVtbl -> SetParameters(This,fCenterFreq,fBandwidth)

#define IEMSAudioStream_GetData(This,pData,pLen)	\
    (This)->lpVtbl -> GetData(This,pData,pLen)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSAudioStream_Connect_Proxy( 
    IEMSAudioStream __RPC_FAR * This,
    /* [in] */ const unsigned long ulSourceID,
    /* [in] */ const unsigned long culLutID,
    /* [in] */ const unsigned long culBufferSize);


void __RPC_STUB IEMSAudioStream_Connect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAudioStream_Disconnect_Proxy( 
    IEMSAudioStream __RPC_FAR * This);


void __RPC_STUB IEMSAudioStream_Disconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAudioStream_SetParameters_Proxy( 
    IEMSAudioStream __RPC_FAR * This,
    /* [in] */ const float fCenterFreq,
    /* [in] */ const float fBandwidth);


void __RPC_STUB IEMSAudioStream_SetParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAudioStream_GetData_Proxy( 
    IEMSAudioStream __RPC_FAR * This,
    /* [out][in] */ short __RPC_FAR *pData,
    /* [out][in] */ unsigned int __RPC_FAR *pLen);


void __RPC_STUB IEMSAudioStream_GetData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSAudioStream_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSAudioRiffInterface_0340 */
/* [local] */ 

typedef /* [unique] */ IEMSAudioStream __RPC_FAR *LPEMSAUDIOSTREAM;



extern RPC_IF_HANDLE __MIDL_itf_EMSAudioRiffInterface_0340_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSAudioRiffInterface_0340_v0_0_s_ifspec;

#ifndef __IEMSAudioStream2_INTERFACE_DEFINED__
#define __IEMSAudioStream2_INTERFACE_DEFINED__

/* interface IEMSAudioStream2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSAudioStream2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E2EDFFE6-E40C-4aa7-81EC-5F5900DCBD86")
    IEMSAudioStream2 : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE MakeFreeRequest( 
            /* [in] */ const unsigned long ulSourceID,
            /* [in] */ EMSAUDIOREQUEST audreq) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFreeRequestData( 
            /* [out][in] */ short __RPC_FAR *pData,
            /* [out][in] */ unsigned int __RPC_FAR *pLen,
            /* [out][in] */ unsigned int __RPC_FAR *pSamplPerSec) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CancelFreeRequest( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSAudioStream2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSAudioStream2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSAudioStream2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSAudioStream2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MakeFreeRequest )( 
            IEMSAudioStream2 __RPC_FAR * This,
            /* [in] */ const unsigned long ulSourceID,
            /* [in] */ EMSAUDIOREQUEST audreq);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetFreeRequestData )( 
            IEMSAudioStream2 __RPC_FAR * This,
            /* [out][in] */ short __RPC_FAR *pData,
            /* [out][in] */ unsigned int __RPC_FAR *pLen,
            /* [out][in] */ unsigned int __RPC_FAR *pSamplPerSec);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CancelFreeRequest )( 
            IEMSAudioStream2 __RPC_FAR * This);
        
        END_INTERFACE
    } IEMSAudioStream2Vtbl;

    interface IEMSAudioStream2
    {
        CONST_VTBL struct IEMSAudioStream2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSAudioStream2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSAudioStream2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSAudioStream2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSAudioStream2_MakeFreeRequest(This,ulSourceID,audreq)	\
    (This)->lpVtbl -> MakeFreeRequest(This,ulSourceID,audreq)

#define IEMSAudioStream2_GetFreeRequestData(This,pData,pLen,pSamplPerSec)	\
    (This)->lpVtbl -> GetFreeRequestData(This,pData,pLen,pSamplPerSec)

#define IEMSAudioStream2_CancelFreeRequest(This)	\
    (This)->lpVtbl -> CancelFreeRequest(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSAudioStream2_MakeFreeRequest_Proxy( 
    IEMSAudioStream2 __RPC_FAR * This,
    /* [in] */ const unsigned long ulSourceID,
    /* [in] */ EMSAUDIOREQUEST audreq);


void __RPC_STUB IEMSAudioStream2_MakeFreeRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAudioStream2_GetFreeRequestData_Proxy( 
    IEMSAudioStream2 __RPC_FAR * This,
    /* [out][in] */ short __RPC_FAR *pData,
    /* [out][in] */ unsigned int __RPC_FAR *pLen,
    /* [out][in] */ unsigned int __RPC_FAR *pSamplPerSec);


void __RPC_STUB IEMSAudioStream2_GetFreeRequestData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAudioStream2_CancelFreeRequest_Proxy( 
    IEMSAudioStream2 __RPC_FAR * This);


void __RPC_STUB IEMSAudioStream2_CancelFreeRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSAudioStream2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSAudioRiffInterface_0341 */
/* [local] */ 

typedef /* [unique] */ IEMSAudioStream2 __RPC_FAR *LPEMSAUDIOSTREAM2;



extern RPC_IF_HANDLE __MIDL_itf_EMSAudioRiffInterface_0341_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSAudioRiffInterface_0341_v0_0_s_ifspec;

#ifndef __IEMSAudioRiffDataStream_INTERFACE_DEFINED__
#define __IEMSAudioRiffDataStream_INTERFACE_DEFINED__

/* interface IEMSAudioRiffDataStream */
/* [unique][helpstring][uuid][object] */ 

typedef 
enum _tagEMSAUDIORIFFSTREAMTYPE
    {	EMSARST_Unknown	= 0,
	EMSARST_Realtime	= 1,
	EMSARST_Database	= 2,
	EMSARST_Request	= 3,
	EMSARST_File	= 4
    }	EMSAUDIORIFFSTREAMTYPE;

typedef enum _tagEMSAUDIORIFFSTREAMTYPE __RPC_FAR *LPEMSAUDIORIFFSTREAMTYPE;

typedef struct  _tagEMSAUDIORIFFINFO
    {
    BOOLEAN bSweepDetected;
    double dSweepRate;
    double dSweepConfidence;
    }	EMSAUDIORIFFINFO;

typedef struct _tagEMSAUDIORIFFINFO __RPC_FAR *LPEMSAUDIORIFFINFO;


EXTERN_C const IID IID_IEMSAudioRiffDataStream;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("92B437C4-D022-43d0-AEEF-FD153D019E6D")
    IEMSAudioRiffDataStream : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetAudioStreamType( 
            /* [out] */ LPEMSAUDIORIFFSTREAMTYPE lpType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAudioRiff( 
            /* [out] */ LPEMSAUDIODATARECORD_RIFF lpData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAudioRiffEx( 
            /* [out] */ LPEMSAUDIODATARECORD_RIFF lpData,
            /* [out] */ LPEMSAUDIORIFFINFO lpInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CancelAudioStream( 
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ClearAudioStream( 
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAudioStreamTimeout( 
            /* [in] */ double dTimeout) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetQueueSize( 
            /* [out] */ ULONG __RPC_FAR *pulSize) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSAudioRiffDataStreamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSAudioRiffDataStream __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSAudioRiffDataStream __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSAudioRiffDataStream __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAudioStreamType )( 
            IEMSAudioRiffDataStream __RPC_FAR * This,
            /* [out] */ LPEMSAUDIORIFFSTREAMTYPE lpType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAudioRiff )( 
            IEMSAudioRiffDataStream __RPC_FAR * This,
            /* [out] */ LPEMSAUDIODATARECORD_RIFF lpData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAudioRiffEx )( 
            IEMSAudioRiffDataStream __RPC_FAR * This,
            /* [out] */ LPEMSAUDIODATARECORD_RIFF lpData,
            /* [out] */ LPEMSAUDIORIFFINFO lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CancelAudioStream )( 
            IEMSAudioRiffDataStream __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClearAudioStream )( 
            IEMSAudioRiffDataStream __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAudioStreamTimeout )( 
            IEMSAudioRiffDataStream __RPC_FAR * This,
            /* [in] */ double dTimeout);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetQueueSize )( 
            IEMSAudioRiffDataStream __RPC_FAR * This,
            /* [out] */ ULONG __RPC_FAR *pulSize);
        
        END_INTERFACE
    } IEMSAudioRiffDataStreamVtbl;

    interface IEMSAudioRiffDataStream
    {
        CONST_VTBL struct IEMSAudioRiffDataStreamVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSAudioRiffDataStream_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSAudioRiffDataStream_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSAudioRiffDataStream_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSAudioRiffDataStream_GetAudioStreamType(This,lpType)	\
    (This)->lpVtbl -> GetAudioStreamType(This,lpType)

#define IEMSAudioRiffDataStream_GetAudioRiff(This,lpData)	\
    (This)->lpVtbl -> GetAudioRiff(This,lpData)

#define IEMSAudioRiffDataStream_GetAudioRiffEx(This,lpData,lpInfo)	\
    (This)->lpVtbl -> GetAudioRiffEx(This,lpData,lpInfo)

#define IEMSAudioRiffDataStream_CancelAudioStream(This,dwFlags)	\
    (This)->lpVtbl -> CancelAudioStream(This,dwFlags)

#define IEMSAudioRiffDataStream_ClearAudioStream(This,dwFlags)	\
    (This)->lpVtbl -> ClearAudioStream(This,dwFlags)

#define IEMSAudioRiffDataStream_SetAudioStreamTimeout(This,dTimeout)	\
    (This)->lpVtbl -> SetAudioStreamTimeout(This,dTimeout)

#define IEMSAudioRiffDataStream_GetQueueSize(This,pulSize)	\
    (This)->lpVtbl -> GetQueueSize(This,pulSize)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSAudioRiffDataStream_GetAudioStreamType_Proxy( 
    IEMSAudioRiffDataStream __RPC_FAR * This,
    /* [out] */ LPEMSAUDIORIFFSTREAMTYPE lpType);


void __RPC_STUB IEMSAudioRiffDataStream_GetAudioStreamType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAudioRiffDataStream_GetAudioRiff_Proxy( 
    IEMSAudioRiffDataStream __RPC_FAR * This,
    /* [out] */ LPEMSAUDIODATARECORD_RIFF lpData);


void __RPC_STUB IEMSAudioRiffDataStream_GetAudioRiff_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAudioRiffDataStream_GetAudioRiffEx_Proxy( 
    IEMSAudioRiffDataStream __RPC_FAR * This,
    /* [out] */ LPEMSAUDIODATARECORD_RIFF lpData,
    /* [out] */ LPEMSAUDIORIFFINFO lpInfo);


void __RPC_STUB IEMSAudioRiffDataStream_GetAudioRiffEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAudioRiffDataStream_CancelAudioStream_Proxy( 
    IEMSAudioRiffDataStream __RPC_FAR * This,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IEMSAudioRiffDataStream_CancelAudioStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAudioRiffDataStream_ClearAudioStream_Proxy( 
    IEMSAudioRiffDataStream __RPC_FAR * This,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IEMSAudioRiffDataStream_ClearAudioStream_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAudioRiffDataStream_SetAudioStreamTimeout_Proxy( 
    IEMSAudioRiffDataStream __RPC_FAR * This,
    /* [in] */ double dTimeout);


void __RPC_STUB IEMSAudioRiffDataStream_SetAudioStreamTimeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAudioRiffDataStream_GetQueueSize_Proxy( 
    IEMSAudioRiffDataStream __RPC_FAR * This,
    /* [out] */ ULONG __RPC_FAR *pulSize);


void __RPC_STUB IEMSAudioRiffDataStream_GetQueueSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSAudioRiffDataStream_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSAudioRiffInterface_0342 */
/* [local] */ 

typedef /* [unique] */ IEMSAudioRiffDataStream __RPC_FAR *LPEMSAUDIORIFFDATASTREAM;



extern RPC_IF_HANDLE __MIDL_itf_EMSAudioRiffInterface_0342_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSAudioRiffInterface_0342_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
