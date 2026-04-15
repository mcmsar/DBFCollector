/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Mar 11 17:09:08 2007
 */
/* Compiler settings for ..\..\..\Common\Include\SARRPlugin.idl:
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

#ifndef __SARRPlugin_h__
#define __SARRPlugin_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSDetectPlugin_FWD_DEFINED__
#define __IEMSDetectPlugin_FWD_DEFINED__
typedef interface IEMSDetectPlugin IEMSDetectPlugin;
#endif 	/* __IEMSDetectPlugin_FWD_DEFINED__ */


#ifndef __IEMSDecodePlugin_FWD_DEFINED__
#define __IEMSDecodePlugin_FWD_DEFINED__
typedef interface IEMSDecodePlugin IEMSDecodePlugin;
#endif 	/* __IEMSDecodePlugin_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "sarrdata.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_SARRPlugin_0000 */
/* [local] */ 

// {E13B85BC-66D9-4d42-8622-C0566F5C92FF}
DEFINE_GUID(IID_IEMSDetectPlugin, 0xe13b85bc, 0x66d9, 0x4d42, 0x86, 0x22, 0xc0, 0x56, 0x6f, 0x5c, 0x92, 0xff);
 
// {9A805D96-AB39-481b-BEDD-AA08EA09B157}
DEFINE_GUID(IID_IEMSDecodePlugin, 0x9a805d96, 0xab39, 0x481b, 0xbe, 0xdd, 0xaa, 0x8, 0xea, 0x9, 0xb1, 0x57);

#pragma pack(push, 1)
// Size is 2048 Elements of complex values with float components
#define	culSARRDataFFTElements	( 2048 )

#define	culSARRDataFFTSize	( culSARRDataFFTElements * 2 * 4 )

typedef 
enum _tagSarrStatus
    {	EMS_SARR_TIMERES_UKN	= 0,
	EMS_SARR_EX_TIMERES_UKN	= EMS_SARR_TIMERES_UKN,
	EMS_SARR_TIMERES_LOW	= 0x1000,
	EMS_SARR_EX_TIMERES_LOW	= EMS_SARR_TIMERES_LOW,
	EMS_SARR_TIMERES_MID	= 0x2000,
	EMS_SARR_EX_TIMERES_MID	= EMS_SARR_TIMERES_MID,
	EMS_SARR_TIMERES_HIGH	= 0x4000,
	EMS_SARR_EX_TIMERES_HIGH	= EMS_SARR_TIMERES_HIGH,
	EMS_SARR_EX_TIMERES_MASK	= 0x7000,
	EMS_SARR_EX_INVERTED_FRAMESYNC	= 0x8000,
	EMS_SARR_EX_GROUP_ID_MASK	= 0x7ff
    }	EMSSARRSTATUS;

typedef struct  _tagEMSFFTDATA
    {
    EMSTIME timeStart;
    double dStartFrequency;
    double dFreqBinSize;
    double dCorrelation;
    ULONG ulShiftIndex;
    BYTE aFFTData[ 16384 ];
    }	EMSFFTDATA;

typedef struct  _tagEMSSARRDATAEX
    {
    EMSSARRDATA sarrData;
    EMSFFTDATA fftData;
    WORD wDuplicateMsgCount;
    WORD wStatus;
    WORD wAntennaID;
    }	EMSSARRDATAEX;



extern RPC_IF_HANDLE __MIDL_itf_SARRPlugin_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_SARRPlugin_0000_v0_0_s_ifspec;

#ifndef __IEMSDetectPlugin_INTERFACE_DEFINED__
#define __IEMSDetectPlugin_INTERFACE_DEFINED__

/* interface IEMSDetectPlugin */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSDetectPlugin;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E13B85BC-66D9-4d42-8622-C0566F5C92FF")
    IEMSDetectPlugin : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Process( 
            /* [in] */ const ULONG culBytes,
            /* [size_is][in] */ const unsigned char __RPC_FAR *cabyInData,
            /* [out] */ ULONG __RPC_FAR *pulElements,
            /* [size_is][size_is][out] */ EMSSARRDATAEX __RPC_FAR *__RPC_FAR *paSarrData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Init( 
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszConfig) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSDetectPluginVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSDetectPlugin __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSDetectPlugin __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSDetectPlugin __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Process )( 
            IEMSDetectPlugin __RPC_FAR * This,
            /* [in] */ const ULONG culBytes,
            /* [size_is][in] */ const unsigned char __RPC_FAR *cabyInData,
            /* [out] */ ULONG __RPC_FAR *pulElements,
            /* [size_is][size_is][out] */ EMSSARRDATAEX __RPC_FAR *__RPC_FAR *paSarrData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Init )( 
            IEMSDetectPlugin __RPC_FAR * This,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszConfig);
        
        END_INTERFACE
    } IEMSDetectPluginVtbl;

    interface IEMSDetectPlugin
    {
        CONST_VTBL struct IEMSDetectPluginVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSDetectPlugin_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSDetectPlugin_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSDetectPlugin_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSDetectPlugin_Process(This,culBytes,cabyInData,pulElements,paSarrData)	\
    (This)->lpVtbl -> Process(This,culBytes,cabyInData,pulElements,paSarrData)

#define IEMSDetectPlugin_Init(This,cwszConfig)	\
    (This)->lpVtbl -> Init(This,cwszConfig)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSDetectPlugin_Process_Proxy( 
    IEMSDetectPlugin __RPC_FAR * This,
    /* [in] */ const ULONG culBytes,
    /* [size_is][in] */ const unsigned char __RPC_FAR *cabyInData,
    /* [out] */ ULONG __RPC_FAR *pulElements,
    /* [size_is][size_is][out] */ EMSSARRDATAEX __RPC_FAR *__RPC_FAR *paSarrData);


void __RPC_STUB IEMSDetectPlugin_Process_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDetectPlugin_Init_Proxy( 
    IEMSDetectPlugin __RPC_FAR * This,
    /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszConfig);


void __RPC_STUB IEMSDetectPlugin_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSDetectPlugin_INTERFACE_DEFINED__ */


#ifndef __IEMSDecodePlugin_INTERFACE_DEFINED__
#define __IEMSDecodePlugin_INTERFACE_DEFINED__

/* interface IEMSDecodePlugin */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSDecodePlugin;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9A805D96-AB39-481b-BEDD-AA08EA09B157")
    IEMSDecodePlugin : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Process( 
            /* [in] */ const ULONG culElements,
            /* [size_is][size_is][out][in] */ EMSSARRDATAEX __RPC_FAR *__RPC_FAR *paSarrData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Init( 
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszConfig) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSDecodePluginVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSDecodePlugin __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSDecodePlugin __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSDecodePlugin __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Process )( 
            IEMSDecodePlugin __RPC_FAR * This,
            /* [in] */ const ULONG culElements,
            /* [size_is][size_is][out][in] */ EMSSARRDATAEX __RPC_FAR *__RPC_FAR *paSarrData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Init )( 
            IEMSDecodePlugin __RPC_FAR * This,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszConfig);
        
        END_INTERFACE
    } IEMSDecodePluginVtbl;

    interface IEMSDecodePlugin
    {
        CONST_VTBL struct IEMSDecodePluginVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSDecodePlugin_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSDecodePlugin_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSDecodePlugin_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSDecodePlugin_Process(This,culElements,paSarrData)	\
    (This)->lpVtbl -> Process(This,culElements,paSarrData)

#define IEMSDecodePlugin_Init(This,cwszConfig)	\
    (This)->lpVtbl -> Init(This,cwszConfig)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSDecodePlugin_Process_Proxy( 
    IEMSDecodePlugin __RPC_FAR * This,
    /* [in] */ const ULONG culElements,
    /* [size_is][size_is][out][in] */ EMSSARRDATAEX __RPC_FAR *__RPC_FAR *paSarrData);


void __RPC_STUB IEMSDecodePlugin_Process_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDecodePlugin_Init_Proxy( 
    IEMSDecodePlugin __RPC_FAR * This,
    /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszConfig);


void __RPC_STUB IEMSDecodePlugin_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSDecodePlugin_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_SARRPlugin_0019 */
/* [local] */ 


#pragma pack(pop)


extern RPC_IF_HANDLE __MIDL_itf_SARRPlugin_0019_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_SARRPlugin_0019_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
