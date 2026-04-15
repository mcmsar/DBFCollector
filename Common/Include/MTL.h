/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Aug 24 16:02:59 2011
 */
/* Compiler settings for ..\..\common\include\MTL.idl:
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

#ifndef __MTL_h__
#define __MTL_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSMsgServer_FWD_DEFINED__
#define __IEMSMsgServer_FWD_DEFINED__
typedef interface IEMSMsgServer IEMSMsgServer;
#endif 	/* __IEMSMsgServer_FWD_DEFINED__ */


#ifndef __IEMSMTLClient_FWD_DEFINED__
#define __IEMSMTLClient_FWD_DEFINED__
typedef interface IEMSMTLClient IEMSMTLClient;
#endif 	/* __IEMSMTLClient_FWD_DEFINED__ */


#ifndef __IEMSTransmitEphemeris_FWD_DEFINED__
#define __IEMSTransmitEphemeris_FWD_DEFINED__
typedef interface IEMSTransmitEphemeris IEMSTransmitEphemeris;
#endif 	/* __IEMSTransmitEphemeris_FWD_DEFINED__ */


#ifndef __IEMSSendSolution_FWD_DEFINED__
#define __IEMSSendSolution_FWD_DEFINED__
typedef interface IEMSSendSolution IEMSSendSolution;
#endif 	/* __IEMSSendSolution_FWD_DEFINED__ */


#ifndef __IEMSSendStatus_FWD_DEFINED__
#define __IEMSSendStatus_FWD_DEFINED__
typedef interface IEMSSendStatus IEMSSendStatus;
#endif 	/* __IEMSSendStatus_FWD_DEFINED__ */


#ifndef __IEMSSendDetection_FWD_DEFINED__
#define __IEMSSendDetection_FWD_DEFINED__
typedef interface IEMSSendDetection IEMSSendDetection;
#endif 	/* __IEMSSendDetection_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "gpsephem.h"
#include "calib406ext.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_MTL_0000 */
/* [local] */ 

// {98C74BAD-87BD-4b0f-B78F-FABA78559D43}
DEFINE_GUID(IID_IEMSMsgServer, 0x98c74bad, 0x87bd, 0x4b0f, 0xb7, 0x8f, 0xfa, 0xba, 0x78, 0x55, 0x9d, 0x43);
// {0450518F-CADC-46ba-ADF0-6C3245202802}
DEFINE_GUID(CLSID_EMSSITServer, 0x450518f, 0xcadc, 0x46ba, 0xad, 0xf0, 0x6c, 0x32, 0x45, 0x20, 0x28, 0x2);
// {32C3B0AF-822C-4c2f-A917-517A4E32A5FC}
DEFINE_GUID(CLSID_EMSBinaryServer, 0x32c3b0af, 0x822c, 0x4c2f, 0xa9, 0x17, 0x51, 0x7a, 0x4e, 0x32, 0xa5, 0xfc);
// {6FC3A854-65FE-4136-B5BA-544B062CD7A9}
DEFINE_GUID(CLSID_EMSMTLClient, 0x6fc3a854, 0x65fe, 0x4136, 0xb5, 0xba, 0x54, 0x4b, 0x6, 0x2c, 0xd7, 0xa9);
// {459C9AD9-753F-4a23-B4B7-559A143880ED}
DEFINE_GUID(IID_IEMSMTLClient, 0x459c9ad9, 0x753f, 0x4a23, 0xb4, 0xb7, 0x55, 0x9a, 0x14, 0x38, 0x80, 0xed);
// {2795E98A-3D07-4845-A7B6-F5D30036EFBC}
DEFINE_GUID(IID_IEMSTransmitEphemeris, 0x2795e98a, 0x3d07, 0x4845, 0xa7, 0xb6, 0xf5, 0xd3, 0x0, 0x36, 0xef, 0xbc);
// {DE16331C-E8E4-491d-82F8-529E3865A095}
DEFINE_GUID(IID_IEMSSendSolution, 0xde16331c, 0xe8e4, 0x491d, 0x82, 0xf8, 0x52, 0x9e, 0x38, 0x65, 0xa0, 0x95);
// {0A9FC803-7D70-427f-884C-645754E03B5C}
DEFINE_GUID(IID_IEMSSendStatus, 0xa9fc803, 0x7d70, 0x427f, 0x88, 0x4c, 0x64, 0x57, 0x54, 0xe0, 0x3b, 0x5c);
// {7863162D-A57C-492e-9966-FA6571B6484D}
DEFINE_GUID(IID_IEMSSendDetection,0x7863162d, 0xa57c, 0x492e, 0x99, 0x66, 0xfa, 0x65, 0x71, 0xb6, 0x48, 0x4d);
typedef 
enum eInputType
    {	IT_UNKNOWN	= 0,
	IT_FILESPEC	= 1,
	IT_RAWDATA	= 2,
	IT_FILESPEC_XML	= 3,
	IT_FILESPEC_CSV	= 4,
	IT_LAST	= IT_FILESPEC_CSV + 1
    }	EMSINPUTTYPE;



extern RPC_IF_HANDLE __MIDL_itf_MTL_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_MTL_0000_v0_0_s_ifspec;

#ifndef __IEMSMsgServer_INTERFACE_DEFINED__
#define __IEMSMsgServer_INTERFACE_DEFINED__

/* interface IEMSMsgServer */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IEMSMsgServer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("98C74BAD-87BD-4b0f-B78F-FABA78559D43")
    IEMSMsgServer : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnMsgReceived( 
            /* [in] */ EMSINPUTTYPE eInputType,
            /* [in] */ unsigned long ulLength,
            /* [size_is][in] */ byte __RPC_FAR abyStream[  ]) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSMsgServerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSMsgServer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSMsgServer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSMsgServer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnMsgReceived )( 
            IEMSMsgServer __RPC_FAR * This,
            /* [in] */ EMSINPUTTYPE eInputType,
            /* [in] */ unsigned long ulLength,
            /* [size_is][in] */ byte __RPC_FAR abyStream[  ]);
        
        END_INTERFACE
    } IEMSMsgServerVtbl;

    interface IEMSMsgServer
    {
        CONST_VTBL struct IEMSMsgServerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSMsgServer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSMsgServer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSMsgServer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSMsgServer_OnMsgReceived(This,eInputType,ulLength,abyStream)	\
    (This)->lpVtbl -> OnMsgReceived(This,eInputType,ulLength,abyStream)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSMsgServer_OnMsgReceived_Proxy( 
    IEMSMsgServer __RPC_FAR * This,
    /* [in] */ EMSINPUTTYPE eInputType,
    /* [in] */ unsigned long ulLength,
    /* [size_is][in] */ byte __RPC_FAR abyStream[  ]);


void __RPC_STUB IEMSMsgServer_OnMsgReceived_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSMsgServer_INTERFACE_DEFINED__ */


#ifndef __IEMSMTLClient_INTERFACE_DEFINED__
#define __IEMSMTLClient_INTERFACE_DEFINED__

/* interface IEMSMTLClient */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IEMSMTLClient;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("459C9AD9-753F-4a23-B4B7-559A143880ED")
    IEMSMTLClient : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Connect( 
            /* [in] */ const unsigned long culSourceLutID,
            /* [in] */ const DWORD cdwFlags) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSMTLClientVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSMTLClient __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSMTLClient __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSMTLClient __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Connect )( 
            IEMSMTLClient __RPC_FAR * This,
            /* [in] */ const unsigned long culSourceLutID,
            /* [in] */ const DWORD cdwFlags);
        
        END_INTERFACE
    } IEMSMTLClientVtbl;

    interface IEMSMTLClient
    {
        CONST_VTBL struct IEMSMTLClientVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSMTLClient_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSMTLClient_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSMTLClient_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSMTLClient_Connect(This,culSourceLutID,cdwFlags)	\
    (This)->lpVtbl -> Connect(This,culSourceLutID,cdwFlags)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSMTLClient_Connect_Proxy( 
    IEMSMTLClient __RPC_FAR * This,
    /* [in] */ const unsigned long culSourceLutID,
    /* [in] */ const DWORD cdwFlags);


void __RPC_STUB IEMSMTLClient_Connect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSMTLClient_INTERFACE_DEFINED__ */


#ifndef __IEMSTransmitEphemeris_INTERFACE_DEFINED__
#define __IEMSTransmitEphemeris_INTERFACE_DEFINED__

/* interface IEMSTransmitEphemeris */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IEMSTransmitEphemeris;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2795E98A-3D07-4845-A7B6-F5D30036EFBC")
    IEMSTransmitEphemeris : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SendEphemeris( 
            /* [in] */ const ULONG culRecs,
            /* [size_is][in] */ const EMSSCALEDEPHEMERISDATAEX __RPC_FAR caEphemeris[  ]) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSTransmitEphemerisVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSTransmitEphemeris __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSTransmitEphemeris __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSTransmitEphemeris __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendEphemeris )( 
            IEMSTransmitEphemeris __RPC_FAR * This,
            /* [in] */ const ULONG culRecs,
            /* [size_is][in] */ const EMSSCALEDEPHEMERISDATAEX __RPC_FAR caEphemeris[  ]);
        
        END_INTERFACE
    } IEMSTransmitEphemerisVtbl;

    interface IEMSTransmitEphemeris
    {
        CONST_VTBL struct IEMSTransmitEphemerisVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSTransmitEphemeris_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSTransmitEphemeris_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSTransmitEphemeris_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSTransmitEphemeris_SendEphemeris(This,culRecs,caEphemeris)	\
    (This)->lpVtbl -> SendEphemeris(This,culRecs,caEphemeris)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSTransmitEphemeris_SendEphemeris_Proxy( 
    IEMSTransmitEphemeris __RPC_FAR * This,
    /* [in] */ const ULONG culRecs,
    /* [size_is][in] */ const EMSSCALEDEPHEMERISDATAEX __RPC_FAR caEphemeris[  ]);


void __RPC_STUB IEMSTransmitEphemeris_SendEphemeris_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSTransmitEphemeris_INTERFACE_DEFINED__ */


#ifndef __IEMSSendSolution_INTERFACE_DEFINED__
#define __IEMSSendSolution_INTERFACE_DEFINED__

/* interface IEMSSendSolution */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IEMSSendSolution;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DE16331C-E8E4-491d-82F8-529E3865A095")
    IEMSSendSolution : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SendSolution( 
            /* [string][in] */ const wchar_t __RPC_FAR *cszSerializedSolution) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSendSolutionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSSendSolution __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSSendSolution __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSSendSolution __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendSolution )( 
            IEMSSendSolution __RPC_FAR * This,
            /* [string][in] */ const wchar_t __RPC_FAR *cszSerializedSolution);
        
        END_INTERFACE
    } IEMSSendSolutionVtbl;

    interface IEMSSendSolution
    {
        CONST_VTBL struct IEMSSendSolutionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSendSolution_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSSendSolution_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSSendSolution_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSSendSolution_SendSolution(This,cszSerializedSolution)	\
    (This)->lpVtbl -> SendSolution(This,cszSerializedSolution)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSSendSolution_SendSolution_Proxy( 
    IEMSSendSolution __RPC_FAR * This,
    /* [string][in] */ const wchar_t __RPC_FAR *cszSerializedSolution);


void __RPC_STUB IEMSSendSolution_SendSolution_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSSendSolution_INTERFACE_DEFINED__ */


#ifndef __IEMSSendStatus_INTERFACE_DEFINED__
#define __IEMSSendStatus_INTERFACE_DEFINED__

/* interface IEMSSendStatus */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IEMSSendStatus;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0A9FC803-7D70-427f-884C-645754E03B5C")
    IEMSSendStatus : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE BroadcastStatus( 
            /* [string][in] */ const wchar_t __RPC_FAR *cszType,
            /* [string][in] */ const wchar_t __RPC_FAR *cszSource,
            /* [string][in] */ const wchar_t __RPC_FAR *cszStatus,
            /* [string][in] */ const wchar_t __RPC_FAR *cszStatusMsg) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE BroadcastMsg( 
            /* [in] */ const BYTE cMsgType,
            /* [string][in] */ const wchar_t __RPC_FAR *cszSource,
            /* [string][in] */ const wchar_t __RPC_FAR *cszMsg) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSendStatusVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSSendStatus __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSSendStatus __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSSendStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BroadcastStatus )( 
            IEMSSendStatus __RPC_FAR * This,
            /* [string][in] */ const wchar_t __RPC_FAR *cszType,
            /* [string][in] */ const wchar_t __RPC_FAR *cszSource,
            /* [string][in] */ const wchar_t __RPC_FAR *cszStatus,
            /* [string][in] */ const wchar_t __RPC_FAR *cszStatusMsg);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BroadcastMsg )( 
            IEMSSendStatus __RPC_FAR * This,
            /* [in] */ const BYTE cMsgType,
            /* [string][in] */ const wchar_t __RPC_FAR *cszSource,
            /* [string][in] */ const wchar_t __RPC_FAR *cszMsg);
        
        END_INTERFACE
    } IEMSSendStatusVtbl;

    interface IEMSSendStatus
    {
        CONST_VTBL struct IEMSSendStatusVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSendStatus_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSSendStatus_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSSendStatus_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSSendStatus_BroadcastStatus(This,cszType,cszSource,cszStatus,cszStatusMsg)	\
    (This)->lpVtbl -> BroadcastStatus(This,cszType,cszSource,cszStatus,cszStatusMsg)

#define IEMSSendStatus_BroadcastMsg(This,cMsgType,cszSource,cszMsg)	\
    (This)->lpVtbl -> BroadcastMsg(This,cMsgType,cszSource,cszMsg)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSSendStatus_BroadcastStatus_Proxy( 
    IEMSSendStatus __RPC_FAR * This,
    /* [string][in] */ const wchar_t __RPC_FAR *cszType,
    /* [string][in] */ const wchar_t __RPC_FAR *cszSource,
    /* [string][in] */ const wchar_t __RPC_FAR *cszStatus,
    /* [string][in] */ const wchar_t __RPC_FAR *cszStatusMsg);


void __RPC_STUB IEMSSendStatus_BroadcastStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSendStatus_BroadcastMsg_Proxy( 
    IEMSSendStatus __RPC_FAR * This,
    /* [in] */ const BYTE cMsgType,
    /* [string][in] */ const wchar_t __RPC_FAR *cszSource,
    /* [string][in] */ const wchar_t __RPC_FAR *cszMsg);


void __RPC_STUB IEMSSendStatus_BroadcastMsg_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSSendStatus_INTERFACE_DEFINED__ */


#ifndef __IEMSSendDetection_INTERFACE_DEFINED__
#define __IEMSSendDetection_INTERFACE_DEFINED__

/* interface IEMSSendDetection */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IEMSSendDetection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7863162D-A57C-492e-9966-FA6571B6484D")
    IEMSSendDetection : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SendDetection( 
            /* [in] */ const EMSCALIB406DATAEXT cDetection) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSendDetectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSSendDetection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSSendDetection __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSSendDetection __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendDetection )( 
            IEMSSendDetection __RPC_FAR * This,
            /* [in] */ const EMSCALIB406DATAEXT cDetection);
        
        END_INTERFACE
    } IEMSSendDetectionVtbl;

    interface IEMSSendDetection
    {
        CONST_VTBL struct IEMSSendDetectionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSendDetection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSSendDetection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSSendDetection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSSendDetection_SendDetection(This,cDetection)	\
    (This)->lpVtbl -> SendDetection(This,cDetection)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSSendDetection_SendDetection_Proxy( 
    IEMSSendDetection __RPC_FAR * This,
    /* [in] */ const EMSCALIB406DATAEXT cDetection);


void __RPC_STUB IEMSSendDetection_SendDetection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSSendDetection_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
