/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed May 06 07:52:43 2009
 */
/* Compiler settings for ..\common\include\IGATEWAY.IDL:
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

#ifndef __IGATEWAY_h__
#define __IGATEWAY_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSGatewayConnection_FWD_DEFINED__
#define __IEMSGatewayConnection_FWD_DEFINED__
typedef interface IEMSGatewayConnection IEMSGatewayConnection;
#endif 	/* __IEMSGatewayConnection_FWD_DEFINED__ */


#ifndef __IEMSGatewayNotification_FWD_DEFINED__
#define __IEMSGatewayNotification_FWD_DEFINED__
typedef interface IEMSGatewayNotification IEMSGatewayNotification;
#endif 	/* __IEMSGatewayNotification_FWD_DEFINED__ */


#ifndef __IEMSGatewayEventManager_FWD_DEFINED__
#define __IEMSGatewayEventManager_FWD_DEFINED__
typedef interface IEMSGatewayEventManager IEMSGatewayEventManager;
#endif 	/* __IEMSGatewayEventManager_FWD_DEFINED__ */


#ifndef __IEMSGtwySecure_FWD_DEFINED__
#define __IEMSGtwySecure_FWD_DEFINED__
typedef interface IEMSGtwySecure IEMSGtwySecure;
#endif 	/* __IEMSGtwySecure_FWD_DEFINED__ */


#ifndef __IEMSDataTransferGtwy_FWD_DEFINED__
#define __IEMSDataTransferGtwy_FWD_DEFINED__
typedef interface IEMSDataTransferGtwy IEMSDataTransferGtwy;
#endif 	/* __IEMSDataTransferGtwy_FWD_DEFINED__ */


#ifndef __IEMSMCCGtwy_FWD_DEFINED__
#define __IEMSMCCGtwy_FWD_DEFINED__
typedef interface IEMSMCCGtwy IEMSMCCGtwy;
#endif 	/* __IEMSMCCGtwy_FWD_DEFINED__ */


#ifndef __IEMSDALGtwy_FWD_DEFINED__
#define __IEMSDALGtwy_FWD_DEFINED__
typedef interface IEMSDALGtwy IEMSDALGtwy;
#endif 	/* __IEMSDALGtwy_FWD_DEFINED__ */


#ifndef __IEMSLocationGtwy_FWD_DEFINED__
#define __IEMSLocationGtwy_FWD_DEFINED__
typedef interface IEMSLocationGtwy IEMSLocationGtwy;
#endif 	/* __IEMSLocationGtwy_FWD_DEFINED__ */


#ifndef __IEMSAlertGenGtwy_FWD_DEFINED__
#define __IEMSAlertGenGtwy_FWD_DEFINED__
typedef interface IEMSAlertGenGtwy IEMSAlertGenGtwy;
#endif 	/* __IEMSAlertGenGtwy_FWD_DEFINED__ */


#ifndef __IEMSAlertManagerGtwy_FWD_DEFINED__
#define __IEMSAlertManagerGtwy_FWD_DEFINED__
typedef interface IEMSAlertManagerGtwy IEMSAlertManagerGtwy;
#endif 	/* __IEMSAlertManagerGtwy_FWD_DEFINED__ */


#ifndef __IEMSAlertManagerGtwy2_FWD_DEFINED__
#define __IEMSAlertManagerGtwy2_FWD_DEFINED__
typedef interface IEMSAlertManagerGtwy2 IEMSAlertManagerGtwy2;
#endif 	/* __IEMSAlertManagerGtwy2_FWD_DEFINED__ */


#ifndef __IEMSAlertManagerGtwy3_FWD_DEFINED__
#define __IEMSAlertManagerGtwy3_FWD_DEFINED__
typedef interface IEMSAlertManagerGtwy3 IEMSAlertManagerGtwy3;
#endif 	/* __IEMSAlertManagerGtwy3_FWD_DEFINED__ */


#ifndef __IEMSDACGtwy_FWD_DEFINED__
#define __IEMSDACGtwy_FWD_DEFINED__
typedef interface IEMSDACGtwy IEMSDACGtwy;
#endif 	/* __IEMSDACGtwy_FWD_DEFINED__ */


#ifndef __IEMSAudioGtwy_FWD_DEFINED__
#define __IEMSAudioGtwy_FWD_DEFINED__
typedef interface IEMSAudioGtwy IEMSAudioGtwy;
#endif 	/* __IEMSAudioGtwy_FWD_DEFINED__ */


#ifndef __IEMSConfigGtwy_FWD_DEFINED__
#define __IEMSConfigGtwy_FWD_DEFINED__
typedef interface IEMSConfigGtwy IEMSConfigGtwy;
#endif 	/* __IEMSConfigGtwy_FWD_DEFINED__ */


#ifndef __IEMSSITGtwy_FWD_DEFINED__
#define __IEMSSITGtwy_FWD_DEFINED__
typedef interface IEMSSITGtwy IEMSSITGtwy;
#endif 	/* __IEMSSITGtwy_FWD_DEFINED__ */


#ifndef __IEMSMCCGtwy2_FWD_DEFINED__
#define __IEMSMCCGtwy2_FWD_DEFINED__
typedef interface IEMSMCCGtwy2 IEMSMCCGtwy2;
#endif 	/* __IEMSMCCGtwy2_FWD_DEFINED__ */


#ifndef __IEMSHealthStatusGtwy_FWD_DEFINED__
#define __IEMSHealthStatusGtwy_FWD_DEFINED__
typedef interface IEMSHealthStatusGtwy IEMSHealthStatusGtwy;
#endif 	/* __IEMSHealthStatusGtwy_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emscommontypes.h"
#include "emscc.h"
#include "iconfigmanager.h"
#include "ABLData.h"
#include "HealthStatusTypes.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_IGATEWAY_0000 */
/* [local] */ 

// {C0AE5A01-0314-11d7-9D3F-000021FAA228}
DEFINE_GUID( CLSID_EMSGateway, 0xc0ae5a01, 0x314, 0x11d7, 0x9d, 0x3f, 0x0, 0x0, 0x21, 0xfa, 0xa2, 0x28); 
// {E4EAC144-030C-11d7-9D3F-000021FAA228}
DEFINE_GUID( IID_IEMSGatewayConnection, 0xe4eac144, 0x30c, 0x11d7, 0x9d, 0x3f, 0x0, 0x0, 0x21, 0xfa, 0xa2, 0x28);
 
// {E4EAC145-030C-11d7-9D3F-000021FAA228}
DEFINE_GUID( IID_IEMSGatewayNotification, 0xe4eac145, 0x30c, 0x11d7, 0x9d, 0x3f, 0x0, 0x0, 0x21, 0xfa, 0xa2, 0x28);
 
// {2E941035-468A-4d65-AF78-3D6F81B9A37B}
DEFINE_GUID( IID_IEMSMCCGtwy, 0x2e941035, 0x468a, 0x4d65, 0xaf, 0x78, 0x3d, 0x6f, 0x81, 0xb9, 0xa3, 0x7b);
 
// {E4EAC146-030C-11d7-9D3F-000021FAA228}
DEFINE_GUID( IID_IEMSGatewayEventManager, 0xe4eac146, 0x30c, 0x11d7, 0x9d, 0x3f, 0x0, 0x0, 0x21, 0xfa, 0xa2, 0x28);
 
// {35F83B1B-148A-46b8-94CE-CF74AA587626}
DEFINE_GUID(CLSID_EMSGateway2, 0x35f83b1b, 0x148a, 0x46b8, 0x94, 0xce, 0xcf, 0x74, 0xaa, 0x58, 0x76, 0x26);
 
// {7D399DD3-5BAE-48b3-AB2E-37EF540B05EB}
DEFINE_GUID(IID_IEMSDALGtwy, 0x7d399dd3, 0x5bae, 0x48b3, 0xab, 0x2e, 0x37, 0xef, 0x54, 0xb, 0x5, 0xeb);
 
// {11CA4B54-7D62-45a2-9620-052049A3AA39}
DEFINE_GUID(IID_IEMSLocationGtwy, 0x11ca4b54, 0x7d62, 0x45a2, 0x96, 0x20, 0x5, 0x20, 0x49, 0xa3, 0xaa, 0x39);
 
// {EF7FD937-6AC3-4dd6-98C9-C255117542F5}
DEFINE_GUID(IID_IEMSAlertGenGtwy, 0xef7fd937, 0x6ac3, 0x4dd6, 0x98, 0xc9, 0xc2, 0x55, 0x11, 0x75, 0x42, 0xf5);
 
// {B3305C7E-91DC-42cf-8976-39D3D759B83B}
DEFINE_GUID(IID_IEMSDACGtwy, 0xb3305c7e, 0x91dc, 0x42cf, 0x89, 0x76, 0x39, 0xd3, 0xd7, 0x59, 0xb8, 0x3b);
 
// {2030FA6F-8600-4534-8A29-B07AD50C34EC}
DEFINE_GUID(IID_IEMSAudioGtwy, 0x2030fa6f, 0x8600, 0x4534, 0x8a, 0x29, 0xb0, 0x7a, 0xd5, 0xc, 0x34, 0xec);
 
// {771DD684-BEB2-408d-9051-CF0929A3C583}
DEFINE_GUID(IID_IEMSDataTransferGtwy, 0x771dd684, 0xbeb2, 0x408d, 0x90, 0x51, 0xcf, 0x9, 0x29, 0xa3, 0xc5, 0x83);
 
// {A1B37799-1BF3-4e15-81A0-805A80A5603A}
DEFINE_GUID(IID_IEMSConfigGtwy, 0xa1b37799, 0x1bf3, 0x4e15, 0x81, 0xa0, 0x80, 0x5a, 0x80, 0xa5, 0x60, 0x3a);
 
// {BE75FFD8-9FC3-41b5-ABF1-9E03688A5A87}
DEFINE_GUID(IID_IEMSGtwySecure, 0xbe75ffd8, 0x9fc3, 0x41b5, 0xab, 0xf1, 0x9e, 0x3, 0x68, 0x8a, 0x5a, 0x87);
 
// {EC92FCFC-7E9D-4b5b-88E6-BC7587FF0668}
DEFINE_GUID(IID_IEMSAlertManagerGtwy, 0xec92fcfc, 0x7e9d, 0x4b5b, 0x88, 0xe6, 0xbc, 0x75, 0x87, 0xff, 0x6, 0x68);
 
// {1E29E10B-804F-4e3f-AEA1-0CB7939C1459}
DEFINE_GUID(IID_IEMSAlertManagerGtwy2, 0x1e29e10b, 0x804f, 0x4e3f, 0xae, 0xa1, 0xc, 0xb7, 0x93, 0x9c, 0x14, 0x59);
 
// {EB381D22-7D01-40aa-89B3-6BB8F3F1C053}
DEFINE_GUID(IID_IEMSAlertManagerGtwy3, 0xeb381d22, 0x7d01, 0x40aa, 0x89, 0xb3, 0x6b, 0xb8, 0xf3, 0xf1, 0xc0, 0x53);
 
// {D6C68EA6-A751-4944-B72D-C75BB0B2BB03}
DEFINE_GUID(IID_IEMSSITGtwy, 0xd6c68ea6, 0xa751, 0x4944, 0xb7, 0x2d, 0xc7, 0x5b, 0xb0, 0xb2, 0xbb, 0x3);
 
// {43AC17C3-43AE-400d-816C-6A2759B3C346}
DEFINE_GUID(IID_IEMSMCCGtwy2, 0x43ac17c3, 0x43ae, 0x400d, 0x81, 0x6c, 0x6a, 0x27, 0x59, 0xb3, 0xc3, 0x46);
 
// {9C33E067-BB2A-48c2-809C-CF791705310A}
DEFINE_GUID(IID_IEMSHealthStatusGtwy, 0x9c33e067, 0xbb2a, 0x48c2, 0x80, 0x9c, 0xcf, 0x79, 0x17, 0x5, 0x31, 0xa);
 
#define ORIG_DEST_SIZE 64
typedef 
enum tagEMSGATEWAYDATATYPE
    {	EMSGatewayDataUnknown	= 0,
	EMSGatewayPtrFlag	= 0x8000,
	EMSGatewaySitMsg	= 1,
	EMSGatewaySITMsgFile	= 2,
	EMSGatewaySITPtr	= 3,
	EMSGatewaySitMsgPtr	= 1 + EMSGatewayPtrFlag
    }	EMSGATEWAYDATATYPE;

typedef enum tagEMSGATEWAYDATATYPE __RPC_FAR *LPEMSGATEWAYDATATYPE;


#pragma pack(1)
typedef 
enum tagEMSGATEWAYADDRESSTYPE
    {	EMSGatewayCSAddress	= 1,
	EMSGatewayIPAddress	= 2
    }	EMSGATEWAYADDRESSTYPE;

typedef enum tagEMSGATEWAYADDRESSTYPE __RPC_FAR *LPEMSGATEWAYADDRESSTYPE;

 
// Although cAddress is declared as a byte array it ALWAYS 
// holds a char* representation of the address.
// e.g. sprintf( (char*)lpTo->cAddress, "%u", ulLutID );
 
typedef struct  tagEMSGATEWAYADDRESS
    {
    EMSGATEWAYADDRESSTYPE type;
    BYTE cAddress[ 64 ];
    }	EMSGATEWAYADDRESS;

typedef struct tagEMSGATEWAYADDRESS __RPC_FAR *LPEMSGATEWAYADDRESS;



extern RPC_IF_HANDLE __MIDL_itf_IGATEWAY_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_IGATEWAY_0000_v0_0_s_ifspec;

#ifndef __IEMSGatewayConnection_INTERFACE_DEFINED__
#define __IEMSGatewayConnection_INTERFACE_DEFINED__

/* interface IEMSGatewayConnection */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IEMSGatewayConnection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E4EAC144-030C-11d7-9D3F-000021FAA228")
    IEMSGatewayConnection : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Connect( 
            EMSGATEWAYADDRESS __RPC_FAR *lpFromAddress,
            DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Disconnect( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Send( 
            /* [in] */ EMSGATEWAYDATATYPE eType,
            /* [size_is][in] */ BYTE __RPC_FAR cMsg[  ],
            /* [in] */ long lMsgSize,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *lpSecurityToken,
            /* [in] */ EMSGATEWAYADDRESS __RPC_FAR *lpToAddress) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSGatewayConnectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSGatewayConnection __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSGatewayConnection __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSGatewayConnection __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Connect )( 
            IEMSGatewayConnection __RPC_FAR * This,
            EMSGATEWAYADDRESS __RPC_FAR *lpFromAddress,
            DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Disconnect )( 
            IEMSGatewayConnection __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Send )( 
            IEMSGatewayConnection __RPC_FAR * This,
            /* [in] */ EMSGATEWAYDATATYPE eType,
            /* [size_is][in] */ BYTE __RPC_FAR cMsg[  ],
            /* [in] */ long lMsgSize,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *lpSecurityToken,
            /* [in] */ EMSGATEWAYADDRESS __RPC_FAR *lpToAddress);
        
        END_INTERFACE
    } IEMSGatewayConnectionVtbl;

    interface IEMSGatewayConnection
    {
        CONST_VTBL struct IEMSGatewayConnectionVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSGatewayConnection_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSGatewayConnection_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSGatewayConnection_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSGatewayConnection_Connect(This,lpFromAddress,dwFlags)	\
    (This)->lpVtbl -> Connect(This,lpFromAddress,dwFlags)

#define IEMSGatewayConnection_Disconnect(This)	\
    (This)->lpVtbl -> Disconnect(This)

#define IEMSGatewayConnection_Send(This,eType,cMsg,lMsgSize,lpSecurityToken,lpToAddress)	\
    (This)->lpVtbl -> Send(This,eType,cMsg,lMsgSize,lpSecurityToken,lpToAddress)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSGatewayConnection_Connect_Proxy( 
    IEMSGatewayConnection __RPC_FAR * This,
    EMSGATEWAYADDRESS __RPC_FAR *lpFromAddress,
    DWORD dwFlags);


void __RPC_STUB IEMSGatewayConnection_Connect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSGatewayConnection_Disconnect_Proxy( 
    IEMSGatewayConnection __RPC_FAR * This);


void __RPC_STUB IEMSGatewayConnection_Disconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSGatewayConnection_Send_Proxy( 
    IEMSGatewayConnection __RPC_FAR * This,
    /* [in] */ EMSGATEWAYDATATYPE eType,
    /* [size_is][in] */ BYTE __RPC_FAR cMsg[  ],
    /* [in] */ long lMsgSize,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *lpSecurityToken,
    /* [in] */ EMSGATEWAYADDRESS __RPC_FAR *lpToAddress);


void __RPC_STUB IEMSGatewayConnection_Send_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSGatewayConnection_INTERFACE_DEFINED__ */


#ifndef __IEMSGatewayNotification_INTERFACE_DEFINED__
#define __IEMSGatewayNotification_INTERFACE_DEFINED__

/* interface IEMSGatewayNotification */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IEMSGatewayNotification;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E4EAC145-030C-11d7-9D3F-000021FAA228")
    IEMSGatewayNotification : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnMsgReceived( 
            /* [in] */ EMSGATEWAYDATATYPE eType,
            /* [size_is][in] */ BYTE __RPC_FAR cMsg[  ],
            /* [in] */ long lMsgSize,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *lpSecurityToken,
            /* [in] */ EMSGATEWAYADDRESS __RPC_FAR *lpFromAddress) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSGatewayNotificationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSGatewayNotification __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSGatewayNotification __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSGatewayNotification __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnMsgReceived )( 
            IEMSGatewayNotification __RPC_FAR * This,
            /* [in] */ EMSGATEWAYDATATYPE eType,
            /* [size_is][in] */ BYTE __RPC_FAR cMsg[  ],
            /* [in] */ long lMsgSize,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *lpSecurityToken,
            /* [in] */ EMSGATEWAYADDRESS __RPC_FAR *lpFromAddress);
        
        END_INTERFACE
    } IEMSGatewayNotificationVtbl;

    interface IEMSGatewayNotification
    {
        CONST_VTBL struct IEMSGatewayNotificationVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSGatewayNotification_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSGatewayNotification_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSGatewayNotification_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSGatewayNotification_OnMsgReceived(This,eType,cMsg,lMsgSize,lpSecurityToken,lpFromAddress)	\
    (This)->lpVtbl -> OnMsgReceived(This,eType,cMsg,lMsgSize,lpSecurityToken,lpFromAddress)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSGatewayNotification_OnMsgReceived_Proxy( 
    IEMSGatewayNotification __RPC_FAR * This,
    /* [in] */ EMSGATEWAYDATATYPE eType,
    /* [size_is][in] */ BYTE __RPC_FAR cMsg[  ],
    /* [in] */ long lMsgSize,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *lpSecurityToken,
    /* [in] */ EMSGATEWAYADDRESS __RPC_FAR *lpFromAddress);


void __RPC_STUB IEMSGatewayNotification_OnMsgReceived_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSGatewayNotification_INTERFACE_DEFINED__ */


#ifndef __IEMSGatewayEventManager_INTERFACE_DEFINED__
#define __IEMSGatewayEventManager_INTERFACE_DEFINED__

/* interface IEMSGatewayEventManager */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IEMSGatewayEventManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E4EAC146-030C-11d7-9D3F-000021FAA228")
    IEMSGatewayEventManager : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Advise( 
            /* [in] */ IEMSGatewayNotification __RPC_FAR *pNotify,
            /* [in] */ BOOL bRemote,
            /* [out] */ DWORD __RPC_FAR *pdwCookie) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Unadvise( 
            /* [in] */ DWORD dwCookie) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSGatewayEventManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSGatewayEventManager __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSGatewayEventManager __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSGatewayEventManager __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Advise )( 
            IEMSGatewayEventManager __RPC_FAR * This,
            /* [in] */ IEMSGatewayNotification __RPC_FAR *pNotify,
            /* [in] */ BOOL bRemote,
            /* [out] */ DWORD __RPC_FAR *pdwCookie);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Unadvise )( 
            IEMSGatewayEventManager __RPC_FAR * This,
            /* [in] */ DWORD dwCookie);
        
        END_INTERFACE
    } IEMSGatewayEventManagerVtbl;

    interface IEMSGatewayEventManager
    {
        CONST_VTBL struct IEMSGatewayEventManagerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSGatewayEventManager_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSGatewayEventManager_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSGatewayEventManager_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSGatewayEventManager_Advise(This,pNotify,bRemote,pdwCookie)	\
    (This)->lpVtbl -> Advise(This,pNotify,bRemote,pdwCookie)

#define IEMSGatewayEventManager_Unadvise(This,dwCookie)	\
    (This)->lpVtbl -> Unadvise(This,dwCookie)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSGatewayEventManager_Advise_Proxy( 
    IEMSGatewayEventManager __RPC_FAR * This,
    /* [in] */ IEMSGatewayNotification __RPC_FAR *pNotify,
    /* [in] */ BOOL bRemote,
    /* [out] */ DWORD __RPC_FAR *pdwCookie);


void __RPC_STUB IEMSGatewayEventManager_Advise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSGatewayEventManager_Unadvise_Proxy( 
    IEMSGatewayEventManager __RPC_FAR * This,
    /* [in] */ DWORD dwCookie);


void __RPC_STUB IEMSGatewayEventManager_Unadvise_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSGatewayEventManager_INTERFACE_DEFINED__ */


#ifndef __IEMSGtwySecure_INTERFACE_DEFINED__
#define __IEMSGtwySecure_INTERFACE_DEFINED__

/* interface IEMSGtwySecure */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IEMSGtwySecure;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BE75FFD8-9FC3-41b5-ABF1-9E03688A5A87")
    IEMSGtwySecure : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SendMsg( 
            /* [in] */ EMSGATEWAYDATATYPE eType,
            /* [size_is][in] */ BYTE __RPC_FAR cMsg[  ],
            /* [in] */ long lMsgSize,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *lpSecurityToken,
            /* [in] */ EMSGATEWAYADDRESS __RPC_FAR *lpToAddress,
            /* [in] */ long lSitType,
            /* [in] */ EMSSITCONTROLCODE eCtrlCode) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSGtwySecureVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSGtwySecure __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSGtwySecure __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSGtwySecure __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendMsg )( 
            IEMSGtwySecure __RPC_FAR * This,
            /* [in] */ EMSGATEWAYDATATYPE eType,
            /* [size_is][in] */ BYTE __RPC_FAR cMsg[  ],
            /* [in] */ long lMsgSize,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *lpSecurityToken,
            /* [in] */ EMSGATEWAYADDRESS __RPC_FAR *lpToAddress,
            /* [in] */ long lSitType,
            /* [in] */ EMSSITCONTROLCODE eCtrlCode);
        
        END_INTERFACE
    } IEMSGtwySecureVtbl;

    interface IEMSGtwySecure
    {
        CONST_VTBL struct IEMSGtwySecureVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSGtwySecure_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSGtwySecure_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSGtwySecure_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSGtwySecure_SendMsg(This,eType,cMsg,lMsgSize,lpSecurityToken,lpToAddress,lSitType,eCtrlCode)	\
    (This)->lpVtbl -> SendMsg(This,eType,cMsg,lMsgSize,lpSecurityToken,lpToAddress,lSitType,eCtrlCode)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSGtwySecure_SendMsg_Proxy( 
    IEMSGtwySecure __RPC_FAR * This,
    /* [in] */ EMSGATEWAYDATATYPE eType,
    /* [size_is][in] */ BYTE __RPC_FAR cMsg[  ],
    /* [in] */ long lMsgSize,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *lpSecurityToken,
    /* [in] */ EMSGATEWAYADDRESS __RPC_FAR *lpToAddress,
    /* [in] */ long lSitType,
    /* [in] */ EMSSITCONTROLCODE eCtrlCode);


void __RPC_STUB IEMSGtwySecure_SendMsg_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSGtwySecure_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_IGATEWAY_0368 */
/* [local] */ 

typedef 
enum tagEMSResourceIdentifier
    {	EMSRES_UKNOWN	= 0,
	EMSRES_SEND_LOCATION	= 1,
	EMSRES_SEND_ALARM	= 2,
	EMSRES_SEND_WARNING	= 3,
	EMSRES_SEND_STATUS	= 4,
	EMSRES_SEND_ORBV	= 5,
	EMSRES_SEND_TLE	= 6,
	EMSRES_SEND_PASS_SCHED	= 7,
	EMSRES_SEND_METOP_SCHED	= 8,
	EMSRES_SEND_SARP_CALIB	= 9,
	EMSRES_SEND_SARR_CALIB	= 10,
	EMSRES_SEND_STARTUP	= 11,
	EMSRES_SEND_LEO_PASS_SUMMARY	= 12,
	EMSRES_SEND_GEO_PASS_SUMMARY	= 13,
	EMSRES_SEND_CMD_ACK	= 14,
	EMSRES_SEND_COMMS_CHECK	= 15,
	EMSRES_SEND_CMD	= 16,
	EMSRES_RETRANSMIT_MSGS	= 17,
	EMSRES_SEND_MSGS	= 18,
	EMSRES_GET_DATA	= 19,
	EMSRES_INIT_MAN_PROC	= 20,
	EMSRES_REMOVE_DATA	= 21,
	EMSRES_UPLOAD_DATA	= 22,
	EMSRES_PROCESS_406	= 23,
	EMSRES_CANCEL_SESSION	= 24,
	EMSRES_GEN_ALERTS	= 25,
	EMSRES_SEND_DATA	= 26,
	EMSRES_RECOVER_DATA	= 27,
	EMSRES_GET_CONTROL_FILENAMES	= 28,
	EMSRES_SEND_DATA_REPORT	= 29,
	EMSRES_CONFIG_GET	= 30,
	EMSRES_CONFIG_SET_STRING	= 31,
	EMSRES_ALERT_SEND_SOLNS	= 32,
	EMSRES_ALERT_TRANSMIT	= 33,
	EMSRES_SIT_TRANSMIT	= 34,
	EMSRES_AUDIO_CONNECT	= 35,
	EMSRES_AUDIO_GETDATA	= 36,
	EMSRES_AUDIO_SETPARAM	= 37,
	EMSRES_AUDIO_DISCONNECT	= 38,
	EMSRES_AUDIO_MAKEFREEREQUEST	= 39,
	EMSRES_AUDIO_GETFREEREQUESTDATA	= 40,
	EMSRES_AUDIO_CANCELFREEREQUEST	= 41,
	EMSRES_LAST	= EMSRES_AUDIO_CANCELFREEREQUEST + 1
    }	EMSRESOURCEIDENTIFIER;



extern RPC_IF_HANDLE __MIDL_itf_IGATEWAY_0368_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_IGATEWAY_0368_v0_0_s_ifspec;

#ifndef __IEMSDataTransferGtwy_INTERFACE_DEFINED__
#define __IEMSDataTransferGtwy_INTERFACE_DEFINED__

/* interface IEMSDataTransferGtwy */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSDataTransferGtwy;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("771DD684-BEB2-408d-9051-CF0929A3C583")
    IEMSDataTransferGtwy : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE UploadData( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ unsigned long ulUploadTarget,
            /* [in] */ EMSRECORDTYPE eRecordType,
            /* [in] */ unsigned long ulMaxPackageSize,
            /* [string][in] */ wchar_t __RPC_FAR *wszSQLWhere) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSDataTransferGtwyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSDataTransferGtwy __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSDataTransferGtwy __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSDataTransferGtwy __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *UploadData )( 
            IEMSDataTransferGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ unsigned long ulUploadTarget,
            /* [in] */ EMSRECORDTYPE eRecordType,
            /* [in] */ unsigned long ulMaxPackageSize,
            /* [string][in] */ wchar_t __RPC_FAR *wszSQLWhere);
        
        END_INTERFACE
    } IEMSDataTransferGtwyVtbl;

    interface IEMSDataTransferGtwy
    {
        CONST_VTBL struct IEMSDataTransferGtwyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSDataTransferGtwy_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSDataTransferGtwy_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSDataTransferGtwy_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSDataTransferGtwy_UploadData(This,ulDestID,psecToken,ulUploadTarget,eRecordType,ulMaxPackageSize,wszSQLWhere)	\
    (This)->lpVtbl -> UploadData(This,ulDestID,psecToken,ulUploadTarget,eRecordType,ulMaxPackageSize,wszSQLWhere)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSDataTransferGtwy_UploadData_Proxy( 
    IEMSDataTransferGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ unsigned long ulUploadTarget,
    /* [in] */ EMSRECORDTYPE eRecordType,
    /* [in] */ unsigned long ulMaxPackageSize,
    /* [string][in] */ wchar_t __RPC_FAR *wszSQLWhere);


void __RPC_STUB IEMSDataTransferGtwy_UploadData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSDataTransferGtwy_INTERFACE_DEFINED__ */


#ifndef __IEMSMCCGtwy_INTERFACE_DEFINED__
#define __IEMSMCCGtwy_INTERFACE_DEFINED__

/* interface IEMSMCCGtwy */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSMCCGtwy;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2E941035-468A-4d65-AF78-3D6F81B9A37B")
    IEMSMCCGtwy : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SendLocation( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulSits,
            /* [size_is][in] */ long __RPC_FAR *alSitIDs,
            /* [in] */ unsigned long ulSatID,
            /* [in] */ unsigned long ulPassID,
            /* [in] */ unsigned long ulLocations,
            /* [size_is][in] */ EMSSITLOCALERTSOLUTION __RPC_FAR *__RPC_FAR *apLocations) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendAlarm( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [string][in] */ wchar_t __RPC_FAR *wszSource,
            /* [string][in] */ wchar_t __RPC_FAR *wszMsg,
            /* [in] */ unsigned long ulSatID,
            /* [in] */ unsigned long ulPassID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendWarning( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [string][in] */ wchar_t __RPC_FAR *wszSource,
            /* [string][in] */ wchar_t __RPC_FAR *wszMsg,
            /* [in] */ unsigned long ulSatID,
            /* [in] */ unsigned long ulPassID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendStatus( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulNumStatus,
            /* [size_is][in] */ EMS605ADATA __RPC_FAR *__RPC_FAR *apStatus,
            /* [in] */ unsigned long ulSatID,
            /* [in] */ unsigned long ulPassID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendOrbitVector( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCmdMsgSequence,
            /* [in] */ unsigned long ulSitID,
            /* [in] */ EMSSITCONTROLCODE eCtrlCode,
            /* [in] */ unsigned long ulOrbits,
            /* [size_is][in] */ EMSSIT215DATA __RPC_FAR *__RPC_FAR *apOrbVectors) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendTLE( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCmdMsgSequence,
            /* [in] */ EMSSITCONTROLCODE eCtrlCode,
            /* [in] */ unsigned long ulOrbits,
            /* [size_is][in] */ EMSSIT255ADATA __RPC_FAR *__RPC_FAR *apTLEs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendPassSchedule( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCmdMsgSequence,
            /* [in] */ EMSSCHEDUSAGE eUsage,
            /* [in] */ long lSatelliteCount,
            /* [in] */ unsigned long ulPasses,
            /* [size_is][in] */ EMSSATELLITETRACK __RPC_FAR *__RPC_FAR *apPasses) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendMetopSchedule( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulEntries,
            /* [size_is][in] */ EMSMANOEUVREDATA __RPC_FAR *__RPC_FAR *apManoeuvres) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendSARPCalib( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCmdMsgSequence,
            /* [in] */ unsigned long ulSit,
            /* [in] */ EMSSITCONTROLCODE eCtrlCode,
            /* [in] */ unsigned long ulMsgRequestNumber,
            /* [in] */ unsigned long ulSatID,
            /* [in] */ unsigned long ulPassID,
            /* [in] */ EMSTIME timeRollover,
            /* [in] */ double dUSOFrequency) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendSARRCalib( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCmdMsgSequence,
            /* [in] */ unsigned long ulSit,
            /* [in] */ EMSSITCONTROLCODE eCtrlCode,
            /* [in] */ unsigned long ulSatellites,
            /* [size_is][in] */ EMSSARRCALIBDATA __RPC_FAR *__RPC_FAR *apSarrData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendStartUp( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCmdMsgSequence) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendLEOPassSummary( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulSatID,
            /* [in] */ unsigned long ulPassID,
            /* [in] */ EMSPASSSUMMARYINFO2 __RPC_FAR *pSummary) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendGEOPassSummary( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulSatID,
            /* [in] */ unsigned long ulPassID,
            /* [in] */ EMSGEOSUMMARYINFO __RPC_FAR *pSummary) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendCmdAck( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCommandMsgSequence,
            /* [string][in] */ wchar_t __RPC_FAR *wszStatus) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendCommsCheck( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendCommand( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCmdMsgSequence,
            /* [in] */ EMSOPERATORCMD __RPC_FAR *popCommand) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RequestRetransmitMsgs( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCmdMsgSequence,
            /* [in] */ unsigned long ulSendToID,
            /* [in] */ unsigned long ulSeqStart,
            /* [in] */ unsigned long ulSeqEnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendMessages( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCount,
            /* [size_is][string][in] */ wchar_t __RPC_FAR *__RPC_FAR *awszFilePath) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendDataReport( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulMessages,
            /* [size_is][string][in] */ wchar_t __RPC_FAR *__RPC_FAR *awszMessages) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendAlarmsAsLog( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulAlarms,
            /* [size_is][in] */ EMSLOGDATA __RPC_FAR *aLogData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendWarningsAsLog( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulWarnings,
            /* [size_is][in] */ EMSLOGDATA __RPC_FAR *aLogData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendStatusAsLog( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulStatus,
            /* [size_is][in] */ EMSLOGDATA __RPC_FAR *aLogData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSMCCGtwyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSMCCGtwy __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSMCCGtwy __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSMCCGtwy __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendLocation )( 
            IEMSMCCGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulSits,
            /* [size_is][in] */ long __RPC_FAR *alSitIDs,
            /* [in] */ unsigned long ulSatID,
            /* [in] */ unsigned long ulPassID,
            /* [in] */ unsigned long ulLocations,
            /* [size_is][in] */ EMSSITLOCALERTSOLUTION __RPC_FAR *__RPC_FAR *apLocations);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendAlarm )( 
            IEMSMCCGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [string][in] */ wchar_t __RPC_FAR *wszSource,
            /* [string][in] */ wchar_t __RPC_FAR *wszMsg,
            /* [in] */ unsigned long ulSatID,
            /* [in] */ unsigned long ulPassID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendWarning )( 
            IEMSMCCGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [string][in] */ wchar_t __RPC_FAR *wszSource,
            /* [string][in] */ wchar_t __RPC_FAR *wszMsg,
            /* [in] */ unsigned long ulSatID,
            /* [in] */ unsigned long ulPassID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendStatus )( 
            IEMSMCCGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulNumStatus,
            /* [size_is][in] */ EMS605ADATA __RPC_FAR *__RPC_FAR *apStatus,
            /* [in] */ unsigned long ulSatID,
            /* [in] */ unsigned long ulPassID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendOrbitVector )( 
            IEMSMCCGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCmdMsgSequence,
            /* [in] */ unsigned long ulSitID,
            /* [in] */ EMSSITCONTROLCODE eCtrlCode,
            /* [in] */ unsigned long ulOrbits,
            /* [size_is][in] */ EMSSIT215DATA __RPC_FAR *__RPC_FAR *apOrbVectors);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendTLE )( 
            IEMSMCCGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCmdMsgSequence,
            /* [in] */ EMSSITCONTROLCODE eCtrlCode,
            /* [in] */ unsigned long ulOrbits,
            /* [size_is][in] */ EMSSIT255ADATA __RPC_FAR *__RPC_FAR *apTLEs);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendPassSchedule )( 
            IEMSMCCGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCmdMsgSequence,
            /* [in] */ EMSSCHEDUSAGE eUsage,
            /* [in] */ long lSatelliteCount,
            /* [in] */ unsigned long ulPasses,
            /* [size_is][in] */ EMSSATELLITETRACK __RPC_FAR *__RPC_FAR *apPasses);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendMetopSchedule )( 
            IEMSMCCGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulEntries,
            /* [size_is][in] */ EMSMANOEUVREDATA __RPC_FAR *__RPC_FAR *apManoeuvres);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendSARPCalib )( 
            IEMSMCCGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCmdMsgSequence,
            /* [in] */ unsigned long ulSit,
            /* [in] */ EMSSITCONTROLCODE eCtrlCode,
            /* [in] */ unsigned long ulMsgRequestNumber,
            /* [in] */ unsigned long ulSatID,
            /* [in] */ unsigned long ulPassID,
            /* [in] */ EMSTIME timeRollover,
            /* [in] */ double dUSOFrequency);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendSARRCalib )( 
            IEMSMCCGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCmdMsgSequence,
            /* [in] */ unsigned long ulSit,
            /* [in] */ EMSSITCONTROLCODE eCtrlCode,
            /* [in] */ unsigned long ulSatellites,
            /* [size_is][in] */ EMSSARRCALIBDATA __RPC_FAR *__RPC_FAR *apSarrData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendStartUp )( 
            IEMSMCCGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCmdMsgSequence);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendLEOPassSummary )( 
            IEMSMCCGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulSatID,
            /* [in] */ unsigned long ulPassID,
            /* [in] */ EMSPASSSUMMARYINFO2 __RPC_FAR *pSummary);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendGEOPassSummary )( 
            IEMSMCCGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulSatID,
            /* [in] */ unsigned long ulPassID,
            /* [in] */ EMSGEOSUMMARYINFO __RPC_FAR *pSummary);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendCmdAck )( 
            IEMSMCCGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCommandMsgSequence,
            /* [string][in] */ wchar_t __RPC_FAR *wszStatus);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendCommsCheck )( 
            IEMSMCCGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendCommand )( 
            IEMSMCCGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCmdMsgSequence,
            /* [in] */ EMSOPERATORCMD __RPC_FAR *popCommand);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RequestRetransmitMsgs )( 
            IEMSMCCGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCmdMsgSequence,
            /* [in] */ unsigned long ulSendToID,
            /* [in] */ unsigned long ulSeqStart,
            /* [in] */ unsigned long ulSeqEnd);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendMessages )( 
            IEMSMCCGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCount,
            /* [size_is][string][in] */ wchar_t __RPC_FAR *__RPC_FAR *awszFilePath);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendDataReport )( 
            IEMSMCCGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulMessages,
            /* [size_is][string][in] */ wchar_t __RPC_FAR *__RPC_FAR *awszMessages);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendAlarmsAsLog )( 
            IEMSMCCGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulAlarms,
            /* [size_is][in] */ EMSLOGDATA __RPC_FAR *aLogData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendWarningsAsLog )( 
            IEMSMCCGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulWarnings,
            /* [size_is][in] */ EMSLOGDATA __RPC_FAR *aLogData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendStatusAsLog )( 
            IEMSMCCGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulStatus,
            /* [size_is][in] */ EMSLOGDATA __RPC_FAR *aLogData);
        
        END_INTERFACE
    } IEMSMCCGtwyVtbl;

    interface IEMSMCCGtwy
    {
        CONST_VTBL struct IEMSMCCGtwyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSMCCGtwy_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSMCCGtwy_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSMCCGtwy_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSMCCGtwy_SendLocation(This,ulDestID,psecToken,eTrigger,ulSits,alSitIDs,ulSatID,ulPassID,ulLocations,apLocations)	\
    (This)->lpVtbl -> SendLocation(This,ulDestID,psecToken,eTrigger,ulSits,alSitIDs,ulSatID,ulPassID,ulLocations,apLocations)

#define IEMSMCCGtwy_SendAlarm(This,ulDestID,psecToken,eTrigger,wszSource,wszMsg,ulSatID,ulPassID)	\
    (This)->lpVtbl -> SendAlarm(This,ulDestID,psecToken,eTrigger,wszSource,wszMsg,ulSatID,ulPassID)

#define IEMSMCCGtwy_SendWarning(This,ulDestID,psecToken,eTrigger,wszSource,wszMsg,ulSatID,ulPassID)	\
    (This)->lpVtbl -> SendWarning(This,ulDestID,psecToken,eTrigger,wszSource,wszMsg,ulSatID,ulPassID)

#define IEMSMCCGtwy_SendStatus(This,ulDestID,psecToken,eTrigger,ulNumStatus,apStatus,ulSatID,ulPassID)	\
    (This)->lpVtbl -> SendStatus(This,ulDestID,psecToken,eTrigger,ulNumStatus,apStatus,ulSatID,ulPassID)

#define IEMSMCCGtwy_SendOrbitVector(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence,ulSitID,eCtrlCode,ulOrbits,apOrbVectors)	\
    (This)->lpVtbl -> SendOrbitVector(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence,ulSitID,eCtrlCode,ulOrbits,apOrbVectors)

#define IEMSMCCGtwy_SendTLE(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence,eCtrlCode,ulOrbits,apTLEs)	\
    (This)->lpVtbl -> SendTLE(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence,eCtrlCode,ulOrbits,apTLEs)

#define IEMSMCCGtwy_SendPassSchedule(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence,eUsage,lSatelliteCount,ulPasses,apPasses)	\
    (This)->lpVtbl -> SendPassSchedule(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence,eUsage,lSatelliteCount,ulPasses,apPasses)

#define IEMSMCCGtwy_SendMetopSchedule(This,ulDestID,psecToken,eTrigger,ulEntries,apManoeuvres)	\
    (This)->lpVtbl -> SendMetopSchedule(This,ulDestID,psecToken,eTrigger,ulEntries,apManoeuvres)

#define IEMSMCCGtwy_SendSARPCalib(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence,ulSit,eCtrlCode,ulMsgRequestNumber,ulSatID,ulPassID,timeRollover,dUSOFrequency)	\
    (This)->lpVtbl -> SendSARPCalib(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence,ulSit,eCtrlCode,ulMsgRequestNumber,ulSatID,ulPassID,timeRollover,dUSOFrequency)

#define IEMSMCCGtwy_SendSARRCalib(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence,ulSit,eCtrlCode,ulSatellites,apSarrData)	\
    (This)->lpVtbl -> SendSARRCalib(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence,ulSit,eCtrlCode,ulSatellites,apSarrData)

#define IEMSMCCGtwy_SendStartUp(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence)	\
    (This)->lpVtbl -> SendStartUp(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence)

#define IEMSMCCGtwy_SendLEOPassSummary(This,ulDestID,psecToken,eTrigger,ulSatID,ulPassID,pSummary)	\
    (This)->lpVtbl -> SendLEOPassSummary(This,ulDestID,psecToken,eTrigger,ulSatID,ulPassID,pSummary)

#define IEMSMCCGtwy_SendGEOPassSummary(This,ulDestID,psecToken,eTrigger,ulSatID,ulPassID,pSummary)	\
    (This)->lpVtbl -> SendGEOPassSummary(This,ulDestID,psecToken,eTrigger,ulSatID,ulPassID,pSummary)

#define IEMSMCCGtwy_SendCmdAck(This,ulDestID,psecToken,eTrigger,ulCommandMsgSequence,wszStatus)	\
    (This)->lpVtbl -> SendCmdAck(This,ulDestID,psecToken,eTrigger,ulCommandMsgSequence,wszStatus)

#define IEMSMCCGtwy_SendCommsCheck(This,ulDestID,psecToken,eTrigger)	\
    (This)->lpVtbl -> SendCommsCheck(This,ulDestID,psecToken,eTrigger)

#define IEMSMCCGtwy_SendCommand(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence,popCommand)	\
    (This)->lpVtbl -> SendCommand(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence,popCommand)

#define IEMSMCCGtwy_RequestRetransmitMsgs(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence,ulSendToID,ulSeqStart,ulSeqEnd)	\
    (This)->lpVtbl -> RequestRetransmitMsgs(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence,ulSendToID,ulSeqStart,ulSeqEnd)

#define IEMSMCCGtwy_SendMessages(This,ulDestID,psecToken,eTrigger,ulCount,awszFilePath)	\
    (This)->lpVtbl -> SendMessages(This,ulDestID,psecToken,eTrigger,ulCount,awszFilePath)

#define IEMSMCCGtwy_SendDataReport(This,ulDestID,psecToken,eTrigger,ulMessages,awszMessages)	\
    (This)->lpVtbl -> SendDataReport(This,ulDestID,psecToken,eTrigger,ulMessages,awszMessages)

#define IEMSMCCGtwy_SendAlarmsAsLog(This,ulDestID,psecToken,eTrigger,ulAlarms,aLogData)	\
    (This)->lpVtbl -> SendAlarmsAsLog(This,ulDestID,psecToken,eTrigger,ulAlarms,aLogData)

#define IEMSMCCGtwy_SendWarningsAsLog(This,ulDestID,psecToken,eTrigger,ulWarnings,aLogData)	\
    (This)->lpVtbl -> SendWarningsAsLog(This,ulDestID,psecToken,eTrigger,ulWarnings,aLogData)

#define IEMSMCCGtwy_SendStatusAsLog(This,ulDestID,psecToken,eTrigger,ulStatus,aLogData)	\
    (This)->lpVtbl -> SendStatusAsLog(This,ulDestID,psecToken,eTrigger,ulStatus,aLogData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSMCCGtwy_SendLocation_Proxy( 
    IEMSMCCGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ EMSTRIGGER eTrigger,
    /* [in] */ unsigned long ulSits,
    /* [size_is][in] */ long __RPC_FAR *alSitIDs,
    /* [in] */ unsigned long ulSatID,
    /* [in] */ unsigned long ulPassID,
    /* [in] */ unsigned long ulLocations,
    /* [size_is][in] */ EMSSITLOCALERTSOLUTION __RPC_FAR *__RPC_FAR *apLocations);


void __RPC_STUB IEMSMCCGtwy_SendLocation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSMCCGtwy_SendAlarm_Proxy( 
    IEMSMCCGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ EMSTRIGGER eTrigger,
    /* [string][in] */ wchar_t __RPC_FAR *wszSource,
    /* [string][in] */ wchar_t __RPC_FAR *wszMsg,
    /* [in] */ unsigned long ulSatID,
    /* [in] */ unsigned long ulPassID);


void __RPC_STUB IEMSMCCGtwy_SendAlarm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSMCCGtwy_SendWarning_Proxy( 
    IEMSMCCGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ EMSTRIGGER eTrigger,
    /* [string][in] */ wchar_t __RPC_FAR *wszSource,
    /* [string][in] */ wchar_t __RPC_FAR *wszMsg,
    /* [in] */ unsigned long ulSatID,
    /* [in] */ unsigned long ulPassID);


void __RPC_STUB IEMSMCCGtwy_SendWarning_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSMCCGtwy_SendStatus_Proxy( 
    IEMSMCCGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ EMSTRIGGER eTrigger,
    /* [in] */ unsigned long ulNumStatus,
    /* [size_is][in] */ EMS605ADATA __RPC_FAR *__RPC_FAR *apStatus,
    /* [in] */ unsigned long ulSatID,
    /* [in] */ unsigned long ulPassID);


void __RPC_STUB IEMSMCCGtwy_SendStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSMCCGtwy_SendOrbitVector_Proxy( 
    IEMSMCCGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ EMSTRIGGER eTrigger,
    /* [in] */ unsigned long ulCmdMsgSequence,
    /* [in] */ unsigned long ulSitID,
    /* [in] */ EMSSITCONTROLCODE eCtrlCode,
    /* [in] */ unsigned long ulOrbits,
    /* [size_is][in] */ EMSSIT215DATA __RPC_FAR *__RPC_FAR *apOrbVectors);


void __RPC_STUB IEMSMCCGtwy_SendOrbitVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSMCCGtwy_SendTLE_Proxy( 
    IEMSMCCGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ EMSTRIGGER eTrigger,
    /* [in] */ unsigned long ulCmdMsgSequence,
    /* [in] */ EMSSITCONTROLCODE eCtrlCode,
    /* [in] */ unsigned long ulOrbits,
    /* [size_is][in] */ EMSSIT255ADATA __RPC_FAR *__RPC_FAR *apTLEs);


void __RPC_STUB IEMSMCCGtwy_SendTLE_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSMCCGtwy_SendPassSchedule_Proxy( 
    IEMSMCCGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ EMSTRIGGER eTrigger,
    /* [in] */ unsigned long ulCmdMsgSequence,
    /* [in] */ EMSSCHEDUSAGE eUsage,
    /* [in] */ long lSatelliteCount,
    /* [in] */ unsigned long ulPasses,
    /* [size_is][in] */ EMSSATELLITETRACK __RPC_FAR *__RPC_FAR *apPasses);


void __RPC_STUB IEMSMCCGtwy_SendPassSchedule_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSMCCGtwy_SendMetopSchedule_Proxy( 
    IEMSMCCGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ EMSTRIGGER eTrigger,
    /* [in] */ unsigned long ulEntries,
    /* [size_is][in] */ EMSMANOEUVREDATA __RPC_FAR *__RPC_FAR *apManoeuvres);


void __RPC_STUB IEMSMCCGtwy_SendMetopSchedule_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSMCCGtwy_SendSARPCalib_Proxy( 
    IEMSMCCGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ EMSTRIGGER eTrigger,
    /* [in] */ unsigned long ulCmdMsgSequence,
    /* [in] */ unsigned long ulSit,
    /* [in] */ EMSSITCONTROLCODE eCtrlCode,
    /* [in] */ unsigned long ulMsgRequestNumber,
    /* [in] */ unsigned long ulSatID,
    /* [in] */ unsigned long ulPassID,
    /* [in] */ EMSTIME timeRollover,
    /* [in] */ double dUSOFrequency);


void __RPC_STUB IEMSMCCGtwy_SendSARPCalib_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSMCCGtwy_SendSARRCalib_Proxy( 
    IEMSMCCGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ EMSTRIGGER eTrigger,
    /* [in] */ unsigned long ulCmdMsgSequence,
    /* [in] */ unsigned long ulSit,
    /* [in] */ EMSSITCONTROLCODE eCtrlCode,
    /* [in] */ unsigned long ulSatellites,
    /* [size_is][in] */ EMSSARRCALIBDATA __RPC_FAR *__RPC_FAR *apSarrData);


void __RPC_STUB IEMSMCCGtwy_SendSARRCalib_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSMCCGtwy_SendStartUp_Proxy( 
    IEMSMCCGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ EMSTRIGGER eTrigger,
    /* [in] */ unsigned long ulCmdMsgSequence);


void __RPC_STUB IEMSMCCGtwy_SendStartUp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSMCCGtwy_SendLEOPassSummary_Proxy( 
    IEMSMCCGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ EMSTRIGGER eTrigger,
    /* [in] */ unsigned long ulSatID,
    /* [in] */ unsigned long ulPassID,
    /* [in] */ EMSPASSSUMMARYINFO2 __RPC_FAR *pSummary);


void __RPC_STUB IEMSMCCGtwy_SendLEOPassSummary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSMCCGtwy_SendGEOPassSummary_Proxy( 
    IEMSMCCGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ EMSTRIGGER eTrigger,
    /* [in] */ unsigned long ulSatID,
    /* [in] */ unsigned long ulPassID,
    /* [in] */ EMSGEOSUMMARYINFO __RPC_FAR *pSummary);


void __RPC_STUB IEMSMCCGtwy_SendGEOPassSummary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSMCCGtwy_SendCmdAck_Proxy( 
    IEMSMCCGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ EMSTRIGGER eTrigger,
    /* [in] */ unsigned long ulCommandMsgSequence,
    /* [string][in] */ wchar_t __RPC_FAR *wszStatus);


void __RPC_STUB IEMSMCCGtwy_SendCmdAck_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSMCCGtwy_SendCommsCheck_Proxy( 
    IEMSMCCGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ EMSTRIGGER eTrigger);


void __RPC_STUB IEMSMCCGtwy_SendCommsCheck_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSMCCGtwy_SendCommand_Proxy( 
    IEMSMCCGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ EMSTRIGGER eTrigger,
    /* [in] */ unsigned long ulCmdMsgSequence,
    /* [in] */ EMSOPERATORCMD __RPC_FAR *popCommand);


void __RPC_STUB IEMSMCCGtwy_SendCommand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSMCCGtwy_RequestRetransmitMsgs_Proxy( 
    IEMSMCCGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ EMSTRIGGER eTrigger,
    /* [in] */ unsigned long ulCmdMsgSequence,
    /* [in] */ unsigned long ulSendToID,
    /* [in] */ unsigned long ulSeqStart,
    /* [in] */ unsigned long ulSeqEnd);


void __RPC_STUB IEMSMCCGtwy_RequestRetransmitMsgs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSMCCGtwy_SendMessages_Proxy( 
    IEMSMCCGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ EMSTRIGGER eTrigger,
    /* [in] */ unsigned long ulCount,
    /* [size_is][string][in] */ wchar_t __RPC_FAR *__RPC_FAR *awszFilePath);


void __RPC_STUB IEMSMCCGtwy_SendMessages_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSMCCGtwy_SendDataReport_Proxy( 
    IEMSMCCGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ EMSTRIGGER eTrigger,
    /* [in] */ unsigned long ulMessages,
    /* [size_is][string][in] */ wchar_t __RPC_FAR *__RPC_FAR *awszMessages);


void __RPC_STUB IEMSMCCGtwy_SendDataReport_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSMCCGtwy_SendAlarmsAsLog_Proxy( 
    IEMSMCCGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ EMSTRIGGER eTrigger,
    /* [in] */ unsigned long ulAlarms,
    /* [size_is][in] */ EMSLOGDATA __RPC_FAR *aLogData);


void __RPC_STUB IEMSMCCGtwy_SendAlarmsAsLog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSMCCGtwy_SendWarningsAsLog_Proxy( 
    IEMSMCCGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ EMSTRIGGER eTrigger,
    /* [in] */ unsigned long ulWarnings,
    /* [size_is][in] */ EMSLOGDATA __RPC_FAR *aLogData);


void __RPC_STUB IEMSMCCGtwy_SendWarningsAsLog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSMCCGtwy_SendStatusAsLog_Proxy( 
    IEMSMCCGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ EMSTRIGGER eTrigger,
    /* [in] */ unsigned long ulStatus,
    /* [size_is][in] */ EMSLOGDATA __RPC_FAR *aLogData);


void __RPC_STUB IEMSMCCGtwy_SendStatusAsLog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSMCCGtwy_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_IGATEWAY_0370 */
/* [local] */ 

struct  tagEMSCalib406DataIdentity
    {
    EMSCALIB406DATA data;
    unsigned long ulIdentity;
    };
typedef struct tagEMSCalib406DataIdentity EMSCALIB406DATAIDENTITY;



extern RPC_IF_HANDLE __MIDL_itf_IGATEWAY_0370_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_IGATEWAY_0370_v0_0_s_ifspec;

#ifndef __IEMSDALGtwy_INTERFACE_DEFINED__
#define __IEMSDALGtwy_INTERFACE_DEFINED__

/* interface IEMSDALGtwy */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSDALGtwy;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7D399DD3-5BAE-48b3-AB2E-37EF540B05EB")
    IEMSDALGtwy : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetData( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [out][in] */ EMSDALCACHEID __RPC_FAR *pCacheID,
            /* [in] */ const unsigned long culMaxRecords,
            /* [in] */ const boolean cbReturnDescriptor,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszOutputFileSpec,
            /* [out][in] */ unsigned long __RPC_FAR *pulTotalRecords,
            /* [out][in] */ unsigned long __RPC_FAR *pulRecordSize,
            /* [out][in] */ boolean __RPC_FAR *pbCacheOverflow,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszConnection,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszSQLQuery,
            /* [out][in] */ unsigned long __RPC_FAR *pulFields,
            /* [size_is][size_is][out] */ EMSFIELDDESCRIPTOR __RPC_FAR *__RPC_FAR *paFields,
            /* [out][in] */ unsigned long __RPC_FAR *pulDataSize,
            /* [size_is][size_is][out] */ unsigned char __RPC_FAR *__RPC_FAR *paData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSDALGtwyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSDALGtwy __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSDALGtwy __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSDALGtwy __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetData )( 
            IEMSDALGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [out][in] */ EMSDALCACHEID __RPC_FAR *pCacheID,
            /* [in] */ const unsigned long culMaxRecords,
            /* [in] */ const boolean cbReturnDescriptor,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszOutputFileSpec,
            /* [out][in] */ unsigned long __RPC_FAR *pulTotalRecords,
            /* [out][in] */ unsigned long __RPC_FAR *pulRecordSize,
            /* [out][in] */ boolean __RPC_FAR *pbCacheOverflow,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszConnection,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszSQLQuery,
            /* [out][in] */ unsigned long __RPC_FAR *pulFields,
            /* [size_is][size_is][out] */ EMSFIELDDESCRIPTOR __RPC_FAR *__RPC_FAR *paFields,
            /* [out][in] */ unsigned long __RPC_FAR *pulDataSize,
            /* [size_is][size_is][out] */ unsigned char __RPC_FAR *__RPC_FAR *paData);
        
        END_INTERFACE
    } IEMSDALGtwyVtbl;

    interface IEMSDALGtwy
    {
        CONST_VTBL struct IEMSDALGtwyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSDALGtwy_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSDALGtwy_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSDALGtwy_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSDALGtwy_GetData(This,ulDestID,psecToken,pCacheID,culMaxRecords,cbReturnDescriptor,cwszOutputFileSpec,pulTotalRecords,pulRecordSize,pbCacheOverflow,cwszConnection,cwszSQLQuery,pulFields,paFields,pulDataSize,paData)	\
    (This)->lpVtbl -> GetData(This,ulDestID,psecToken,pCacheID,culMaxRecords,cbReturnDescriptor,cwszOutputFileSpec,pulTotalRecords,pulRecordSize,pbCacheOverflow,cwszConnection,cwszSQLQuery,pulFields,paFields,pulDataSize,paData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSDALGtwy_GetData_Proxy( 
    IEMSDALGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [out][in] */ EMSDALCACHEID __RPC_FAR *pCacheID,
    /* [in] */ const unsigned long culMaxRecords,
    /* [in] */ const boolean cbReturnDescriptor,
    /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszOutputFileSpec,
    /* [out][in] */ unsigned long __RPC_FAR *pulTotalRecords,
    /* [out][in] */ unsigned long __RPC_FAR *pulRecordSize,
    /* [out][in] */ boolean __RPC_FAR *pbCacheOverflow,
    /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszConnection,
    /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszSQLQuery,
    /* [out][in] */ unsigned long __RPC_FAR *pulFields,
    /* [size_is][size_is][out] */ EMSFIELDDESCRIPTOR __RPC_FAR *__RPC_FAR *paFields,
    /* [out][in] */ unsigned long __RPC_FAR *pulDataSize,
    /* [size_is][size_is][out] */ unsigned char __RPC_FAR *__RPC_FAR *paData);


void __RPC_STUB IEMSDALGtwy_GetData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSDALGtwy_INTERFACE_DEFINED__ */


#ifndef __IEMSLocationGtwy_INTERFACE_DEFINED__
#define __IEMSLocationGtwy_INTERFACE_DEFINED__

/* interface IEMSLocationGtwy */
/* [unique][helpstring][uuid][object] */ 

typedef 
enum tagManualProcessingMode
    {	EMS_MANUAL_MODE_UNKNOWN	= 0,
	EMS_MANUAL_MODE_LEO_ONLY	= 1,
	EMS_MANUAL_MODE_LEO_GEO	= 2,
	EMS_MANUAL_MODE_LEO_GEO_COMBINED	= 3,
	EMS_MANUAL_MODE_LAST	= EMS_MANUAL_MODE_LEO_GEO_COMBINED
    }	EMSMANUALPROCESSINGMODE;


EXTERN_C const IID IID_IEMSLocationGtwy;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11CA4B54-7D62-45a2-9620-052049A3AA39")
    IEMSLocationGtwy : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE InitManualProcessing( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *pToken,
            /* [string][in] */ wchar_t __RPC_FAR *wszWhereClause,
            /* [out] */ unsigned long __RPC_FAR *pulSessionID,
            /* [out][in] */ unsigned long __RPC_FAR *pulRecords,
            /* [size_is][size_is][out] */ EMSCALIB406DATA __RPC_FAR *__RPC_FAR *paBeaconData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveDataFromSet( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *pToken,
            /* [in] */ unsigned long ulSessionID,
            /* [in] */ unsigned long ulKeys,
            /* [size_is][in] */ unsigned long __RPC_FAR *aulKeys) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Process406( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ unsigned long ulSessionID,
            /* [string][in] */ wchar_t __RPC_FAR *wszControlFilename,
            /* [out][in] */ unsigned long __RPC_FAR *pulResults,
            /* [size_is][size_is][out] */ EMSLOCATE __RPC_FAR *__RPC_FAR *paLocations) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CancelSession( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ unsigned long ulSessionID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetControlFilenames( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [out] */ unsigned long __RPC_FAR *pulCount,
            /* [size_is][size_is][string][out] */ wchar_t __RPC_FAR *__RPC_FAR *__RPC_FAR *ppaControlFilenames) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InitManual( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *pToken,
            /* [string][in] */ const wchar_t __RPC_FAR *cwszWhereClause,
            /* [in] */ const EMSMANUALPROCESSINGMODE ceProcessingMode,
            /* [out] */ unsigned long __RPC_FAR *pulSessionID,
            /* [out][in] */ unsigned long __RPC_FAR *pulRecords,
            /* [size_is][size_is][out] */ EMSVARIANTRECORD __RPC_FAR *__RPC_FAR *paData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSLocationGtwyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSLocationGtwy __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSLocationGtwy __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSLocationGtwy __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InitManualProcessing )( 
            IEMSLocationGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *pToken,
            /* [string][in] */ wchar_t __RPC_FAR *wszWhereClause,
            /* [out] */ unsigned long __RPC_FAR *pulSessionID,
            /* [out][in] */ unsigned long __RPC_FAR *pulRecords,
            /* [size_is][size_is][out] */ EMSCALIB406DATA __RPC_FAR *__RPC_FAR *paBeaconData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveDataFromSet )( 
            IEMSLocationGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *pToken,
            /* [in] */ unsigned long ulSessionID,
            /* [in] */ unsigned long ulKeys,
            /* [size_is][in] */ unsigned long __RPC_FAR *aulKeys);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Process406 )( 
            IEMSLocationGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ unsigned long ulSessionID,
            /* [string][in] */ wchar_t __RPC_FAR *wszControlFilename,
            /* [out][in] */ unsigned long __RPC_FAR *pulResults,
            /* [size_is][size_is][out] */ EMSLOCATE __RPC_FAR *__RPC_FAR *paLocations);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CancelSession )( 
            IEMSLocationGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ unsigned long ulSessionID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetControlFilenames )( 
            IEMSLocationGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [out] */ unsigned long __RPC_FAR *pulCount,
            /* [size_is][size_is][string][out] */ wchar_t __RPC_FAR *__RPC_FAR *__RPC_FAR *ppaControlFilenames);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *InitManual )( 
            IEMSLocationGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *pToken,
            /* [string][in] */ const wchar_t __RPC_FAR *cwszWhereClause,
            /* [in] */ const EMSMANUALPROCESSINGMODE ceProcessingMode,
            /* [out] */ unsigned long __RPC_FAR *pulSessionID,
            /* [out][in] */ unsigned long __RPC_FAR *pulRecords,
            /* [size_is][size_is][out] */ EMSVARIANTRECORD __RPC_FAR *__RPC_FAR *paData);
        
        END_INTERFACE
    } IEMSLocationGtwyVtbl;

    interface IEMSLocationGtwy
    {
        CONST_VTBL struct IEMSLocationGtwyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSLocationGtwy_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSLocationGtwy_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSLocationGtwy_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSLocationGtwy_InitManualProcessing(This,ulDestID,pToken,wszWhereClause,pulSessionID,pulRecords,paBeaconData)	\
    (This)->lpVtbl -> InitManualProcessing(This,ulDestID,pToken,wszWhereClause,pulSessionID,pulRecords,paBeaconData)

#define IEMSLocationGtwy_RemoveDataFromSet(This,ulDestID,pToken,ulSessionID,ulKeys,aulKeys)	\
    (This)->lpVtbl -> RemoveDataFromSet(This,ulDestID,pToken,ulSessionID,ulKeys,aulKeys)

#define IEMSLocationGtwy_Process406(This,ulDestID,psecToken,ulSessionID,wszControlFilename,pulResults,paLocations)	\
    (This)->lpVtbl -> Process406(This,ulDestID,psecToken,ulSessionID,wszControlFilename,pulResults,paLocations)

#define IEMSLocationGtwy_CancelSession(This,ulDestID,psecToken,ulSessionID)	\
    (This)->lpVtbl -> CancelSession(This,ulDestID,psecToken,ulSessionID)

#define IEMSLocationGtwy_GetControlFilenames(This,ulDestID,psecToken,pulCount,ppaControlFilenames)	\
    (This)->lpVtbl -> GetControlFilenames(This,ulDestID,psecToken,pulCount,ppaControlFilenames)

#define IEMSLocationGtwy_InitManual(This,ulDestID,pToken,cwszWhereClause,ceProcessingMode,pulSessionID,pulRecords,paData)	\
    (This)->lpVtbl -> InitManual(This,ulDestID,pToken,cwszWhereClause,ceProcessingMode,pulSessionID,pulRecords,paData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSLocationGtwy_InitManualProcessing_Proxy( 
    IEMSLocationGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *pToken,
    /* [string][in] */ wchar_t __RPC_FAR *wszWhereClause,
    /* [out] */ unsigned long __RPC_FAR *pulSessionID,
    /* [out][in] */ unsigned long __RPC_FAR *pulRecords,
    /* [size_is][size_is][out] */ EMSCALIB406DATA __RPC_FAR *__RPC_FAR *paBeaconData);


void __RPC_STUB IEMSLocationGtwy_InitManualProcessing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSLocationGtwy_RemoveDataFromSet_Proxy( 
    IEMSLocationGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *pToken,
    /* [in] */ unsigned long ulSessionID,
    /* [in] */ unsigned long ulKeys,
    /* [size_is][in] */ unsigned long __RPC_FAR *aulKeys);


void __RPC_STUB IEMSLocationGtwy_RemoveDataFromSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSLocationGtwy_Process406_Proxy( 
    IEMSLocationGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ unsigned long ulSessionID,
    /* [string][in] */ wchar_t __RPC_FAR *wszControlFilename,
    /* [out][in] */ unsigned long __RPC_FAR *pulResults,
    /* [size_is][size_is][out] */ EMSLOCATE __RPC_FAR *__RPC_FAR *paLocations);


void __RPC_STUB IEMSLocationGtwy_Process406_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSLocationGtwy_CancelSession_Proxy( 
    IEMSLocationGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ unsigned long ulSessionID);


void __RPC_STUB IEMSLocationGtwy_CancelSession_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSLocationGtwy_GetControlFilenames_Proxy( 
    IEMSLocationGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [out] */ unsigned long __RPC_FAR *pulCount,
    /* [size_is][size_is][string][out] */ wchar_t __RPC_FAR *__RPC_FAR *__RPC_FAR *ppaControlFilenames);


void __RPC_STUB IEMSLocationGtwy_GetControlFilenames_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSLocationGtwy_InitManual_Proxy( 
    IEMSLocationGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *pToken,
    /* [string][in] */ const wchar_t __RPC_FAR *cwszWhereClause,
    /* [in] */ const EMSMANUALPROCESSINGMODE ceProcessingMode,
    /* [out] */ unsigned long __RPC_FAR *pulSessionID,
    /* [out][in] */ unsigned long __RPC_FAR *pulRecords,
    /* [size_is][size_is][out] */ EMSVARIANTRECORD __RPC_FAR *__RPC_FAR *paData);


void __RPC_STUB IEMSLocationGtwy_InitManual_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSLocationGtwy_INTERFACE_DEFINED__ */


#ifndef __IEMSAlertGenGtwy_INTERFACE_DEFINED__
#define __IEMSAlertGenGtwy_INTERFACE_DEFINED__

/* interface IEMSAlertGenGtwy */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSAlertGenGtwy;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EF7FD937-6AC3-4dd6-98C9-C255117542F5")
    IEMSAlertGenGtwy : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GenerateAlerts( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ unsigned long ulDestinations,
            /* [size_is][in] */ unsigned long __RPC_FAR *aulDestinationIDs,
            /* [in] */ unsigned long ulLocations,
            /* [size_is][in] */ EMSLOCATIONKEY __RPC_FAR *aLocations) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSAlertGenGtwyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSAlertGenGtwy __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSAlertGenGtwy __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSAlertGenGtwy __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GenerateAlerts )( 
            IEMSAlertGenGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ unsigned long ulDestinations,
            /* [size_is][in] */ unsigned long __RPC_FAR *aulDestinationIDs,
            /* [in] */ unsigned long ulLocations,
            /* [size_is][in] */ EMSLOCATIONKEY __RPC_FAR *aLocations);
        
        END_INTERFACE
    } IEMSAlertGenGtwyVtbl;

    interface IEMSAlertGenGtwy
    {
        CONST_VTBL struct IEMSAlertGenGtwyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSAlertGenGtwy_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSAlertGenGtwy_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSAlertGenGtwy_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSAlertGenGtwy_GenerateAlerts(This,ulDestID,psecToken,ulDestinations,aulDestinationIDs,ulLocations,aLocations)	\
    (This)->lpVtbl -> GenerateAlerts(This,ulDestID,psecToken,ulDestinations,aulDestinationIDs,ulLocations,aLocations)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSAlertGenGtwy_GenerateAlerts_Proxy( 
    IEMSAlertGenGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ unsigned long ulDestinations,
    /* [size_is][in] */ unsigned long __RPC_FAR *aulDestinationIDs,
    /* [in] */ unsigned long ulLocations,
    /* [size_is][in] */ EMSLOCATIONKEY __RPC_FAR *aLocations);


void __RPC_STUB IEMSAlertGenGtwy_GenerateAlerts_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSAlertGenGtwy_INTERFACE_DEFINED__ */


#ifndef __IEMSAlertManagerGtwy_INTERFACE_DEFINED__
#define __IEMSAlertManagerGtwy_INTERFACE_DEFINED__

/* interface IEMSAlertManagerGtwy */
/* [unique][helpstring][uuid][object] */ 

#define	MAX_ALERT_RECORDS	( 2 )


EXTERN_C const IID IID_IEMSAlertManagerGtwy;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EC92FCFC-7E9D-4b5b-88E6-BC7587FF0668")
    IEMSAlertManagerGtwy : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SendSolution( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulSolutionDestination,
            /* [in] */ unsigned long ulSatID,
            /* [in] */ unsigned long ulPassID,
            /* [in] */ EMSLOCATE __RPC_FAR aLocations[ 2 ],
            /* [in] */ unsigned char __RPC_FAR szUserID[ 21 ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TransmitAutoAlerts( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSAlertManagerGtwyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSAlertManagerGtwy __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSAlertManagerGtwy __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSAlertManagerGtwy __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendSolution )( 
            IEMSAlertManagerGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulSolutionDestination,
            /* [in] */ unsigned long ulSatID,
            /* [in] */ unsigned long ulPassID,
            /* [in] */ EMSLOCATE __RPC_FAR aLocations[ 2 ],
            /* [in] */ unsigned char __RPC_FAR szUserID[ 21 ]);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TransmitAutoAlerts )( 
            IEMSAlertManagerGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger);
        
        END_INTERFACE
    } IEMSAlertManagerGtwyVtbl;

    interface IEMSAlertManagerGtwy
    {
        CONST_VTBL struct IEMSAlertManagerGtwyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSAlertManagerGtwy_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSAlertManagerGtwy_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSAlertManagerGtwy_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSAlertManagerGtwy_SendSolution(This,ulDestID,psecToken,eTrigger,ulSolutionDestination,ulSatID,ulPassID,aLocations,szUserID)	\
    (This)->lpVtbl -> SendSolution(This,ulDestID,psecToken,eTrigger,ulSolutionDestination,ulSatID,ulPassID,aLocations,szUserID)

#define IEMSAlertManagerGtwy_TransmitAutoAlerts(This,ulDestID,psecToken,eTrigger)	\
    (This)->lpVtbl -> TransmitAutoAlerts(This,ulDestID,psecToken,eTrigger)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSAlertManagerGtwy_SendSolution_Proxy( 
    IEMSAlertManagerGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ EMSTRIGGER eTrigger,
    /* [in] */ unsigned long ulSolutionDestination,
    /* [in] */ unsigned long ulSatID,
    /* [in] */ unsigned long ulPassID,
    /* [in] */ EMSLOCATE __RPC_FAR aLocations[ 2 ],
    /* [in] */ unsigned char __RPC_FAR szUserID[ 21 ]);


void __RPC_STUB IEMSAlertManagerGtwy_SendSolution_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAlertManagerGtwy_TransmitAutoAlerts_Proxy( 
    IEMSAlertManagerGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ EMSTRIGGER eTrigger);


void __RPC_STUB IEMSAlertManagerGtwy_TransmitAutoAlerts_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSAlertManagerGtwy_INTERFACE_DEFINED__ */


#ifndef __IEMSAlertManagerGtwy2_INTERFACE_DEFINED__
#define __IEMSAlertManagerGtwy2_INTERFACE_DEFINED__

/* interface IEMSAlertManagerGtwy2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSAlertManagerGtwy2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1E29E10B-804F-4e3f-AEA1-0CB7939C1459")
    IEMSAlertManagerGtwy2 : public IEMSAlertManagerGtwy
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SendSolutionNow( 
            /* [in] */ const unsigned long culDestID,
            /* [in] */ const EMSGATEWAYTOKEN __RPC_FAR *cpsecToken,
            /* [in] */ const EMSTRIGGER ceTrigger,
            /* [in] */ const unsigned long culSolutionDestination,
            /* [in] */ const unsigned long culSatID,
            /* [in] */ const unsigned long culPassID,
            /* [in] */ const EMSLOCATE __RPC_FAR caLocations[ 2 ],
            /* [in] */ const unsigned char __RPC_FAR cszUserID[ 21 ]) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSAlertManagerGtwy2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSAlertManagerGtwy2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSAlertManagerGtwy2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSAlertManagerGtwy2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendSolution )( 
            IEMSAlertManagerGtwy2 __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulSolutionDestination,
            /* [in] */ unsigned long ulSatID,
            /* [in] */ unsigned long ulPassID,
            /* [in] */ EMSLOCATE __RPC_FAR aLocations[ 2 ],
            /* [in] */ unsigned char __RPC_FAR szUserID[ 21 ]);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TransmitAutoAlerts )( 
            IEMSAlertManagerGtwy2 __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendSolutionNow )( 
            IEMSAlertManagerGtwy2 __RPC_FAR * This,
            /* [in] */ const unsigned long culDestID,
            /* [in] */ const EMSGATEWAYTOKEN __RPC_FAR *cpsecToken,
            /* [in] */ const EMSTRIGGER ceTrigger,
            /* [in] */ const unsigned long culSolutionDestination,
            /* [in] */ const unsigned long culSatID,
            /* [in] */ const unsigned long culPassID,
            /* [in] */ const EMSLOCATE __RPC_FAR caLocations[ 2 ],
            /* [in] */ const unsigned char __RPC_FAR cszUserID[ 21 ]);
        
        END_INTERFACE
    } IEMSAlertManagerGtwy2Vtbl;

    interface IEMSAlertManagerGtwy2
    {
        CONST_VTBL struct IEMSAlertManagerGtwy2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSAlertManagerGtwy2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSAlertManagerGtwy2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSAlertManagerGtwy2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSAlertManagerGtwy2_SendSolution(This,ulDestID,psecToken,eTrigger,ulSolutionDestination,ulSatID,ulPassID,aLocations,szUserID)	\
    (This)->lpVtbl -> SendSolution(This,ulDestID,psecToken,eTrigger,ulSolutionDestination,ulSatID,ulPassID,aLocations,szUserID)

#define IEMSAlertManagerGtwy2_TransmitAutoAlerts(This,ulDestID,psecToken,eTrigger)	\
    (This)->lpVtbl -> TransmitAutoAlerts(This,ulDestID,psecToken,eTrigger)


#define IEMSAlertManagerGtwy2_SendSolutionNow(This,culDestID,cpsecToken,ceTrigger,culSolutionDestination,culSatID,culPassID,caLocations,cszUserID)	\
    (This)->lpVtbl -> SendSolutionNow(This,culDestID,cpsecToken,ceTrigger,culSolutionDestination,culSatID,culPassID,caLocations,cszUserID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSAlertManagerGtwy2_SendSolutionNow_Proxy( 
    IEMSAlertManagerGtwy2 __RPC_FAR * This,
    /* [in] */ const unsigned long culDestID,
    /* [in] */ const EMSGATEWAYTOKEN __RPC_FAR *cpsecToken,
    /* [in] */ const EMSTRIGGER ceTrigger,
    /* [in] */ const unsigned long culSolutionDestination,
    /* [in] */ const unsigned long culSatID,
    /* [in] */ const unsigned long culPassID,
    /* [in] */ const EMSLOCATE __RPC_FAR caLocations[ 2 ],
    /* [in] */ const unsigned char __RPC_FAR cszUserID[ 21 ]);


void __RPC_STUB IEMSAlertManagerGtwy2_SendSolutionNow_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSAlertManagerGtwy2_INTERFACE_DEFINED__ */


#ifndef __IEMSAlertManagerGtwy3_INTERFACE_DEFINED__
#define __IEMSAlertManagerGtwy3_INTERFACE_DEFINED__

/* interface IEMSAlertManagerGtwy3 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSAlertManagerGtwy3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EB381D22-7D01-40aa-89B3-6BB8F3F1C053")
    IEMSAlertManagerGtwy3 : public IEMSAlertManagerGtwy2
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SendSolutionEx( 
            /* [in] */ const unsigned long culDestID,
            /* [in] */ const EMSGATEWAYTOKEN __RPC_FAR *cpsecToken,
            /* [in] */ const EMSTRIGGER ceTrigger,
            /* [in] */ const unsigned long culSolutionDestination,
            /* [in] */ const unsigned long culSatID,
            /* [in] */ const unsigned long culPassID,
            /* [in] */ const EMSABLData __RPC_FAR *cpABLData,
            /* [in] */ const unsigned char __RPC_FAR cszUserID[ 21 ],
            /* [in] */ const BOOL cbSendNow) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSAlertManagerGtwy3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSAlertManagerGtwy3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSAlertManagerGtwy3 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSAlertManagerGtwy3 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendSolution )( 
            IEMSAlertManagerGtwy3 __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulSolutionDestination,
            /* [in] */ unsigned long ulSatID,
            /* [in] */ unsigned long ulPassID,
            /* [in] */ EMSLOCATE __RPC_FAR aLocations[ 2 ],
            /* [in] */ unsigned char __RPC_FAR szUserID[ 21 ]);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TransmitAutoAlerts )( 
            IEMSAlertManagerGtwy3 __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendSolutionNow )( 
            IEMSAlertManagerGtwy3 __RPC_FAR * This,
            /* [in] */ const unsigned long culDestID,
            /* [in] */ const EMSGATEWAYTOKEN __RPC_FAR *cpsecToken,
            /* [in] */ const EMSTRIGGER ceTrigger,
            /* [in] */ const unsigned long culSolutionDestination,
            /* [in] */ const unsigned long culSatID,
            /* [in] */ const unsigned long culPassID,
            /* [in] */ const EMSLOCATE __RPC_FAR caLocations[ 2 ],
            /* [in] */ const unsigned char __RPC_FAR cszUserID[ 21 ]);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendSolutionEx )( 
            IEMSAlertManagerGtwy3 __RPC_FAR * This,
            /* [in] */ const unsigned long culDestID,
            /* [in] */ const EMSGATEWAYTOKEN __RPC_FAR *cpsecToken,
            /* [in] */ const EMSTRIGGER ceTrigger,
            /* [in] */ const unsigned long culSolutionDestination,
            /* [in] */ const unsigned long culSatID,
            /* [in] */ const unsigned long culPassID,
            /* [in] */ const EMSABLData __RPC_FAR *cpABLData,
            /* [in] */ const unsigned char __RPC_FAR cszUserID[ 21 ],
            /* [in] */ const BOOL cbSendNow);
        
        END_INTERFACE
    } IEMSAlertManagerGtwy3Vtbl;

    interface IEMSAlertManagerGtwy3
    {
        CONST_VTBL struct IEMSAlertManagerGtwy3Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSAlertManagerGtwy3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSAlertManagerGtwy3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSAlertManagerGtwy3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSAlertManagerGtwy3_SendSolution(This,ulDestID,psecToken,eTrigger,ulSolutionDestination,ulSatID,ulPassID,aLocations,szUserID)	\
    (This)->lpVtbl -> SendSolution(This,ulDestID,psecToken,eTrigger,ulSolutionDestination,ulSatID,ulPassID,aLocations,szUserID)

#define IEMSAlertManagerGtwy3_TransmitAutoAlerts(This,ulDestID,psecToken,eTrigger)	\
    (This)->lpVtbl -> TransmitAutoAlerts(This,ulDestID,psecToken,eTrigger)


#define IEMSAlertManagerGtwy3_SendSolutionNow(This,culDestID,cpsecToken,ceTrigger,culSolutionDestination,culSatID,culPassID,caLocations,cszUserID)	\
    (This)->lpVtbl -> SendSolutionNow(This,culDestID,cpsecToken,ceTrigger,culSolutionDestination,culSatID,culPassID,caLocations,cszUserID)


#define IEMSAlertManagerGtwy3_SendSolutionEx(This,culDestID,cpsecToken,ceTrigger,culSolutionDestination,culSatID,culPassID,cpABLData,cszUserID,cbSendNow)	\
    (This)->lpVtbl -> SendSolutionEx(This,culDestID,cpsecToken,ceTrigger,culSolutionDestination,culSatID,culPassID,cpABLData,cszUserID,cbSendNow)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSAlertManagerGtwy3_SendSolutionEx_Proxy( 
    IEMSAlertManagerGtwy3 __RPC_FAR * This,
    /* [in] */ const unsigned long culDestID,
    /* [in] */ const EMSGATEWAYTOKEN __RPC_FAR *cpsecToken,
    /* [in] */ const EMSTRIGGER ceTrigger,
    /* [in] */ const unsigned long culSolutionDestination,
    /* [in] */ const unsigned long culSatID,
    /* [in] */ const unsigned long culPassID,
    /* [in] */ const EMSABLData __RPC_FAR *cpABLData,
    /* [in] */ const unsigned char __RPC_FAR cszUserID[ 21 ],
    /* [in] */ const BOOL cbSendNow);


void __RPC_STUB IEMSAlertManagerGtwy3_SendSolutionEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSAlertManagerGtwy3_INTERFACE_DEFINED__ */


#ifndef __IEMSDACGtwy_INTERFACE_DEFINED__
#define __IEMSDACGtwy_INTERFACE_DEFINED__

/* interface IEMSDACGtwy */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSDACGtwy;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B3305C7E-91DC-42cf-8976-39D3D759B83B")
    IEMSDACGtwy : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE RecoverData( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ unsigned long ulNumLuts,
            /* [size_is][in] */ unsigned long __RPC_FAR *aulLutIDs,
            /* [in] */ unsigned long ulNumDataTypes,
            /* [size_is][in] */ EMSRECORDTYPE __RPC_FAR *aeDataTypes,
            /* [in] */ EMSTIME timeStart,
            /* [in] */ EMSTIME timeEnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendData( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [string][in] */ wchar_t __RPC_FAR *wszFilePath) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendData2( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ unsigned long ulSourceID,
            /* [in] */ unsigned long ulRecords,
            /* [size_is][in] */ EMSVARIANTRECORD __RPC_FAR *aRecords) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSDACGtwyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSDACGtwy __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSDACGtwy __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSDACGtwy __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RecoverData )( 
            IEMSDACGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ unsigned long ulNumLuts,
            /* [size_is][in] */ unsigned long __RPC_FAR *aulLutIDs,
            /* [in] */ unsigned long ulNumDataTypes,
            /* [size_is][in] */ EMSRECORDTYPE __RPC_FAR *aeDataTypes,
            /* [in] */ EMSTIME timeStart,
            /* [in] */ EMSTIME timeEnd);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendData )( 
            IEMSDACGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [string][in] */ wchar_t __RPC_FAR *wszFilePath);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendData2 )( 
            IEMSDACGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ unsigned long ulSourceID,
            /* [in] */ unsigned long ulRecords,
            /* [size_is][in] */ EMSVARIANTRECORD __RPC_FAR *aRecords);
        
        END_INTERFACE
    } IEMSDACGtwyVtbl;

    interface IEMSDACGtwy
    {
        CONST_VTBL struct IEMSDACGtwyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSDACGtwy_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSDACGtwy_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSDACGtwy_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSDACGtwy_RecoverData(This,ulDestID,psecToken,ulNumLuts,aulLutIDs,ulNumDataTypes,aeDataTypes,timeStart,timeEnd)	\
    (This)->lpVtbl -> RecoverData(This,ulDestID,psecToken,ulNumLuts,aulLutIDs,ulNumDataTypes,aeDataTypes,timeStart,timeEnd)

#define IEMSDACGtwy_SendData(This,ulDestID,psecToken,wszFilePath)	\
    (This)->lpVtbl -> SendData(This,ulDestID,psecToken,wszFilePath)

#define IEMSDACGtwy_SendData2(This,ulDestID,psecToken,ulSourceID,ulRecords,aRecords)	\
    (This)->lpVtbl -> SendData2(This,ulDestID,psecToken,ulSourceID,ulRecords,aRecords)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSDACGtwy_RecoverData_Proxy( 
    IEMSDACGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ unsigned long ulNumLuts,
    /* [size_is][in] */ unsigned long __RPC_FAR *aulLutIDs,
    /* [in] */ unsigned long ulNumDataTypes,
    /* [size_is][in] */ EMSRECORDTYPE __RPC_FAR *aeDataTypes,
    /* [in] */ EMSTIME timeStart,
    /* [in] */ EMSTIME timeEnd);


void __RPC_STUB IEMSDACGtwy_RecoverData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDACGtwy_SendData_Proxy( 
    IEMSDACGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [string][in] */ wchar_t __RPC_FAR *wszFilePath);


void __RPC_STUB IEMSDACGtwy_SendData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDACGtwy_SendData2_Proxy( 
    IEMSDACGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ unsigned long ulSourceID,
    /* [in] */ unsigned long ulRecords,
    /* [size_is][in] */ EMSVARIANTRECORD __RPC_FAR *aRecords);


void __RPC_STUB IEMSDACGtwy_SendData2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSDACGtwy_INTERFACE_DEFINED__ */


#ifndef __IEMSAudioGtwy_INTERFACE_DEFINED__
#define __IEMSAudioGtwy_INTERFACE_DEFINED__

/* interface IEMSAudioGtwy */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSAudioGtwy;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2030FA6F-8600-4534-8A29-B07AD50C34EC")
    IEMSAudioGtwy : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE AudioConnect( 
            /* [in] */ const unsigned long culLutID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [out][in] */ unsigned long __RPC_FAR *ulSession) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AudioGetData( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ const unsigned long ulSession,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [size_is][out][in] */ unsigned char __RPC_FAR *pData,
            /* [out][in] */ unsigned int __RPC_FAR *pLen) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AudioSetParameters( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ const unsigned long ulSession,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ const float fCenterFreq,
            /* [in] */ const float fBandwidth) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AudioDisconnect( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ const unsigned long culSession,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AudioMakeFreeRequest( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSAUDIOREQUEST audreq,
            /* [out][in] */ unsigned long __RPC_FAR *pulSessionID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AudioGetFreeRequestData( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ unsigned long ulSessionID,
            /* [out][in] */ EMSAUDIODATARECORD_RIFF __RPC_FAR *audrec) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AudioCancelFreeRequest( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ unsigned long ulSessionID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSAudioGtwyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSAudioGtwy __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSAudioGtwy __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSAudioGtwy __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AudioConnect )( 
            IEMSAudioGtwy __RPC_FAR * This,
            /* [in] */ const unsigned long culLutID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [out][in] */ unsigned long __RPC_FAR *ulSession);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AudioGetData )( 
            IEMSAudioGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ const unsigned long ulSession,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [size_is][out][in] */ unsigned char __RPC_FAR *pData,
            /* [out][in] */ unsigned int __RPC_FAR *pLen);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AudioSetParameters )( 
            IEMSAudioGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ const unsigned long ulSession,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ const float fCenterFreq,
            /* [in] */ const float fBandwidth);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AudioDisconnect )( 
            IEMSAudioGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ const unsigned long culSession,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AudioMakeFreeRequest )( 
            IEMSAudioGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSAUDIOREQUEST audreq,
            /* [out][in] */ unsigned long __RPC_FAR *pulSessionID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AudioGetFreeRequestData )( 
            IEMSAudioGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ unsigned long ulSessionID,
            /* [out][in] */ EMSAUDIODATARECORD_RIFF __RPC_FAR *audrec);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AudioCancelFreeRequest )( 
            IEMSAudioGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ unsigned long ulSessionID);
        
        END_INTERFACE
    } IEMSAudioGtwyVtbl;

    interface IEMSAudioGtwy
    {
        CONST_VTBL struct IEMSAudioGtwyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSAudioGtwy_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSAudioGtwy_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSAudioGtwy_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSAudioGtwy_AudioConnect(This,culLutID,psecToken,ulSession)	\
    (This)->lpVtbl -> AudioConnect(This,culLutID,psecToken,ulSession)

#define IEMSAudioGtwy_AudioGetData(This,ulDestID,ulSession,psecToken,pData,pLen)	\
    (This)->lpVtbl -> AudioGetData(This,ulDestID,ulSession,psecToken,pData,pLen)

#define IEMSAudioGtwy_AudioSetParameters(This,ulDestID,ulSession,psecToken,fCenterFreq,fBandwidth)	\
    (This)->lpVtbl -> AudioSetParameters(This,ulDestID,ulSession,psecToken,fCenterFreq,fBandwidth)

#define IEMSAudioGtwy_AudioDisconnect(This,ulDestID,culSession,psecToken)	\
    (This)->lpVtbl -> AudioDisconnect(This,ulDestID,culSession,psecToken)

#define IEMSAudioGtwy_AudioMakeFreeRequest(This,ulDestID,psecToken,audreq,pulSessionID)	\
    (This)->lpVtbl -> AudioMakeFreeRequest(This,ulDestID,psecToken,audreq,pulSessionID)

#define IEMSAudioGtwy_AudioGetFreeRequestData(This,ulDestID,psecToken,ulSessionID,audrec)	\
    (This)->lpVtbl -> AudioGetFreeRequestData(This,ulDestID,psecToken,ulSessionID,audrec)

#define IEMSAudioGtwy_AudioCancelFreeRequest(This,ulDestID,psecToken,ulSessionID)	\
    (This)->lpVtbl -> AudioCancelFreeRequest(This,ulDestID,psecToken,ulSessionID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSAudioGtwy_AudioConnect_Proxy( 
    IEMSAudioGtwy __RPC_FAR * This,
    /* [in] */ const unsigned long culLutID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [out][in] */ unsigned long __RPC_FAR *ulSession);


void __RPC_STUB IEMSAudioGtwy_AudioConnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAudioGtwy_AudioGetData_Proxy( 
    IEMSAudioGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ const unsigned long ulSession,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [size_is][out][in] */ unsigned char __RPC_FAR *pData,
    /* [out][in] */ unsigned int __RPC_FAR *pLen);


void __RPC_STUB IEMSAudioGtwy_AudioGetData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAudioGtwy_AudioSetParameters_Proxy( 
    IEMSAudioGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ const unsigned long ulSession,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ const float fCenterFreq,
    /* [in] */ const float fBandwidth);


void __RPC_STUB IEMSAudioGtwy_AudioSetParameters_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAudioGtwy_AudioDisconnect_Proxy( 
    IEMSAudioGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ const unsigned long culSession,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken);


void __RPC_STUB IEMSAudioGtwy_AudioDisconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAudioGtwy_AudioMakeFreeRequest_Proxy( 
    IEMSAudioGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ EMSAUDIOREQUEST audreq,
    /* [out][in] */ unsigned long __RPC_FAR *pulSessionID);


void __RPC_STUB IEMSAudioGtwy_AudioMakeFreeRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAudioGtwy_AudioGetFreeRequestData_Proxy( 
    IEMSAudioGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ unsigned long ulSessionID,
    /* [out][in] */ EMSAUDIODATARECORD_RIFF __RPC_FAR *audrec);


void __RPC_STUB IEMSAudioGtwy_AudioGetFreeRequestData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAudioGtwy_AudioCancelFreeRequest_Proxy( 
    IEMSAudioGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ unsigned long ulSessionID);


void __RPC_STUB IEMSAudioGtwy_AudioCancelFreeRequest_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSAudioGtwy_INTERFACE_DEFINED__ */


#ifndef __IEMSConfigGtwy_INTERFACE_DEFINED__
#define __IEMSConfigGtwy_INTERFACE_DEFINED__

/* interface IEMSConfigGtwy */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSConfigGtwy;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A1B37799-1BF3-4e15-81A0-805A80A5603A")
    IEMSConfigGtwy : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Get( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [string][in] */ const wchar_t __RPC_FAR *cwszGroupType,
            /* [string][in] */ const wchar_t __RPC_FAR *cwszGroupID,
            /* [string][in] */ const wchar_t __RPC_FAR *cwszKeyName,
            /* [out][in] */ EMSVARITYPE __RPC_FAR *pValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetString( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [string][in] */ const wchar_t __RPC_FAR *pwcsGroupType,
            /* [string][in] */ const wchar_t __RPC_FAR *pwcsGroupID,
            /* [string][in] */ const wchar_t __RPC_FAR *pwcsKeyName,
            /* [string][in] */ const wchar_t __RPC_FAR *pwcsValue) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSConfigGtwyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSConfigGtwy __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSConfigGtwy __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSConfigGtwy __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get )( 
            IEMSConfigGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [string][in] */ const wchar_t __RPC_FAR *cwszGroupType,
            /* [string][in] */ const wchar_t __RPC_FAR *cwszGroupID,
            /* [string][in] */ const wchar_t __RPC_FAR *cwszKeyName,
            /* [out][in] */ EMSVARITYPE __RPC_FAR *pValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetString )( 
            IEMSConfigGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [string][in] */ const wchar_t __RPC_FAR *pwcsGroupType,
            /* [string][in] */ const wchar_t __RPC_FAR *pwcsGroupID,
            /* [string][in] */ const wchar_t __RPC_FAR *pwcsKeyName,
            /* [string][in] */ const wchar_t __RPC_FAR *pwcsValue);
        
        END_INTERFACE
    } IEMSConfigGtwyVtbl;

    interface IEMSConfigGtwy
    {
        CONST_VTBL struct IEMSConfigGtwyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSConfigGtwy_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSConfigGtwy_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSConfigGtwy_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSConfigGtwy_Get(This,ulDestID,psecToken,cwszGroupType,cwszGroupID,cwszKeyName,pValue)	\
    (This)->lpVtbl -> Get(This,ulDestID,psecToken,cwszGroupType,cwszGroupID,cwszKeyName,pValue)

#define IEMSConfigGtwy_SetString(This,ulDestID,psecToken,pwcsGroupType,pwcsGroupID,pwcsKeyName,pwcsValue)	\
    (This)->lpVtbl -> SetString(This,ulDestID,psecToken,pwcsGroupType,pwcsGroupID,pwcsKeyName,pwcsValue)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSConfigGtwy_Get_Proxy( 
    IEMSConfigGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [string][in] */ const wchar_t __RPC_FAR *cwszGroupType,
    /* [string][in] */ const wchar_t __RPC_FAR *cwszGroupID,
    /* [string][in] */ const wchar_t __RPC_FAR *cwszKeyName,
    /* [out][in] */ EMSVARITYPE __RPC_FAR *pValue);


void __RPC_STUB IEMSConfigGtwy_Get_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSConfigGtwy_SetString_Proxy( 
    IEMSConfigGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [string][in] */ const wchar_t __RPC_FAR *pwcsGroupType,
    /* [string][in] */ const wchar_t __RPC_FAR *pwcsGroupID,
    /* [string][in] */ const wchar_t __RPC_FAR *pwcsKeyName,
    /* [string][in] */ const wchar_t __RPC_FAR *pwcsValue);


void __RPC_STUB IEMSConfigGtwy_SetString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSConfigGtwy_INTERFACE_DEFINED__ */


#ifndef __IEMSSITGtwy_INTERFACE_DEFINED__
#define __IEMSSITGtwy_INTERFACE_DEFINED__

/* interface IEMSSITGtwy */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSSITGtwy;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D6C68EA6-A751-4944-B72D-C75BB0B2BB03")
    IEMSSITGtwy : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Transmit( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ const EMSTRIGGER ceTrigger,
            /* [in] */ const EMSCONTROLDATAVALUE ceControlData,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszUserID,
            /* [string][in] */ const wchar_t __RPC_FAR *cwszRouteID,
            /* [in] */ const unsigned long culNumMessages,
            /* [size_is][string][in] */ const wchar_t __RPC_FAR *__RPC_FAR *cawszMessages) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSITGtwyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSSITGtwy __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSSITGtwy __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSSITGtwy __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Transmit )( 
            IEMSSITGtwy __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ const EMSTRIGGER ceTrigger,
            /* [in] */ const EMSCONTROLDATAVALUE ceControlData,
            /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszUserID,
            /* [string][in] */ const wchar_t __RPC_FAR *cwszRouteID,
            /* [in] */ const unsigned long culNumMessages,
            /* [size_is][string][in] */ const wchar_t __RPC_FAR *__RPC_FAR *cawszMessages);
        
        END_INTERFACE
    } IEMSSITGtwyVtbl;

    interface IEMSSITGtwy
    {
        CONST_VTBL struct IEMSSITGtwyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSITGtwy_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSSITGtwy_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSSITGtwy_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSSITGtwy_Transmit(This,ulDestID,psecToken,ceTrigger,ceControlData,cwszUserID,cwszRouteID,culNumMessages,cawszMessages)	\
    (This)->lpVtbl -> Transmit(This,ulDestID,psecToken,ceTrigger,ceControlData,cwszUserID,cwszRouteID,culNumMessages,cawszMessages)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSSITGtwy_Transmit_Proxy( 
    IEMSSITGtwy __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ const EMSTRIGGER ceTrigger,
    /* [in] */ const EMSCONTROLDATAVALUE ceControlData,
    /* [unique][string][in] */ const wchar_t __RPC_FAR *cwszUserID,
    /* [string][in] */ const wchar_t __RPC_FAR *cwszRouteID,
    /* [in] */ const unsigned long culNumMessages,
    /* [size_is][string][in] */ const wchar_t __RPC_FAR *__RPC_FAR *cawszMessages);


void __RPC_STUB IEMSSITGtwy_Transmit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSSITGtwy_INTERFACE_DEFINED__ */


#ifndef __IEMSMCCGtwy2_INTERFACE_DEFINED__
#define __IEMSMCCGtwy2_INTERFACE_DEFINED__

/* interface IEMSMCCGtwy2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSMCCGtwy2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("43AC17C3-43AE-400d-816C-6A2759B3C346")
    IEMSMCCGtwy2 : public IEMSMCCGtwy
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SendPassSchedule2( 
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCmdMsgSequence,
            /* [in] */ EMSSCHEDUSAGE eUsage,
            /* [in] */ long lSatelliteCount,
            /* [in] */ unsigned long ulPasses,
            /* [size_is][in] */ EMSSATELLITETRACK2 __RPC_FAR *__RPC_FAR *apPasses) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSMCCGtwy2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSMCCGtwy2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSMCCGtwy2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSMCCGtwy2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendLocation )( 
            IEMSMCCGtwy2 __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulSits,
            /* [size_is][in] */ long __RPC_FAR *alSitIDs,
            /* [in] */ unsigned long ulSatID,
            /* [in] */ unsigned long ulPassID,
            /* [in] */ unsigned long ulLocations,
            /* [size_is][in] */ EMSSITLOCALERTSOLUTION __RPC_FAR *__RPC_FAR *apLocations);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendAlarm )( 
            IEMSMCCGtwy2 __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [string][in] */ wchar_t __RPC_FAR *wszSource,
            /* [string][in] */ wchar_t __RPC_FAR *wszMsg,
            /* [in] */ unsigned long ulSatID,
            /* [in] */ unsigned long ulPassID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendWarning )( 
            IEMSMCCGtwy2 __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [string][in] */ wchar_t __RPC_FAR *wszSource,
            /* [string][in] */ wchar_t __RPC_FAR *wszMsg,
            /* [in] */ unsigned long ulSatID,
            /* [in] */ unsigned long ulPassID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendStatus )( 
            IEMSMCCGtwy2 __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulNumStatus,
            /* [size_is][in] */ EMS605ADATA __RPC_FAR *__RPC_FAR *apStatus,
            /* [in] */ unsigned long ulSatID,
            /* [in] */ unsigned long ulPassID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendOrbitVector )( 
            IEMSMCCGtwy2 __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCmdMsgSequence,
            /* [in] */ unsigned long ulSitID,
            /* [in] */ EMSSITCONTROLCODE eCtrlCode,
            /* [in] */ unsigned long ulOrbits,
            /* [size_is][in] */ EMSSIT215DATA __RPC_FAR *__RPC_FAR *apOrbVectors);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendTLE )( 
            IEMSMCCGtwy2 __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCmdMsgSequence,
            /* [in] */ EMSSITCONTROLCODE eCtrlCode,
            /* [in] */ unsigned long ulOrbits,
            /* [size_is][in] */ EMSSIT255ADATA __RPC_FAR *__RPC_FAR *apTLEs);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendPassSchedule )( 
            IEMSMCCGtwy2 __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCmdMsgSequence,
            /* [in] */ EMSSCHEDUSAGE eUsage,
            /* [in] */ long lSatelliteCount,
            /* [in] */ unsigned long ulPasses,
            /* [size_is][in] */ EMSSATELLITETRACK __RPC_FAR *__RPC_FAR *apPasses);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendMetopSchedule )( 
            IEMSMCCGtwy2 __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulEntries,
            /* [size_is][in] */ EMSMANOEUVREDATA __RPC_FAR *__RPC_FAR *apManoeuvres);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendSARPCalib )( 
            IEMSMCCGtwy2 __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCmdMsgSequence,
            /* [in] */ unsigned long ulSit,
            /* [in] */ EMSSITCONTROLCODE eCtrlCode,
            /* [in] */ unsigned long ulMsgRequestNumber,
            /* [in] */ unsigned long ulSatID,
            /* [in] */ unsigned long ulPassID,
            /* [in] */ EMSTIME timeRollover,
            /* [in] */ double dUSOFrequency);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendSARRCalib )( 
            IEMSMCCGtwy2 __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCmdMsgSequence,
            /* [in] */ unsigned long ulSit,
            /* [in] */ EMSSITCONTROLCODE eCtrlCode,
            /* [in] */ unsigned long ulSatellites,
            /* [size_is][in] */ EMSSARRCALIBDATA __RPC_FAR *__RPC_FAR *apSarrData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendStartUp )( 
            IEMSMCCGtwy2 __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCmdMsgSequence);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendLEOPassSummary )( 
            IEMSMCCGtwy2 __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulSatID,
            /* [in] */ unsigned long ulPassID,
            /* [in] */ EMSPASSSUMMARYINFO2 __RPC_FAR *pSummary);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendGEOPassSummary )( 
            IEMSMCCGtwy2 __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulSatID,
            /* [in] */ unsigned long ulPassID,
            /* [in] */ EMSGEOSUMMARYINFO __RPC_FAR *pSummary);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendCmdAck )( 
            IEMSMCCGtwy2 __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCommandMsgSequence,
            /* [string][in] */ wchar_t __RPC_FAR *wszStatus);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendCommsCheck )( 
            IEMSMCCGtwy2 __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendCommand )( 
            IEMSMCCGtwy2 __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCmdMsgSequence,
            /* [in] */ EMSOPERATORCMD __RPC_FAR *popCommand);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RequestRetransmitMsgs )( 
            IEMSMCCGtwy2 __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCmdMsgSequence,
            /* [in] */ unsigned long ulSendToID,
            /* [in] */ unsigned long ulSeqStart,
            /* [in] */ unsigned long ulSeqEnd);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendMessages )( 
            IEMSMCCGtwy2 __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCount,
            /* [size_is][string][in] */ wchar_t __RPC_FAR *__RPC_FAR *awszFilePath);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendDataReport )( 
            IEMSMCCGtwy2 __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulMessages,
            /* [size_is][string][in] */ wchar_t __RPC_FAR *__RPC_FAR *awszMessages);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendAlarmsAsLog )( 
            IEMSMCCGtwy2 __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulAlarms,
            /* [size_is][in] */ EMSLOGDATA __RPC_FAR *aLogData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendWarningsAsLog )( 
            IEMSMCCGtwy2 __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulWarnings,
            /* [size_is][in] */ EMSLOGDATA __RPC_FAR *aLogData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendStatusAsLog )( 
            IEMSMCCGtwy2 __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulStatus,
            /* [size_is][in] */ EMSLOGDATA __RPC_FAR *aLogData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendPassSchedule2 )( 
            IEMSMCCGtwy2 __RPC_FAR * This,
            /* [in] */ unsigned long ulDestID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ unsigned long ulCmdMsgSequence,
            /* [in] */ EMSSCHEDUSAGE eUsage,
            /* [in] */ long lSatelliteCount,
            /* [in] */ unsigned long ulPasses,
            /* [size_is][in] */ EMSSATELLITETRACK2 __RPC_FAR *__RPC_FAR *apPasses);
        
        END_INTERFACE
    } IEMSMCCGtwy2Vtbl;

    interface IEMSMCCGtwy2
    {
        CONST_VTBL struct IEMSMCCGtwy2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSMCCGtwy2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSMCCGtwy2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSMCCGtwy2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSMCCGtwy2_SendLocation(This,ulDestID,psecToken,eTrigger,ulSits,alSitIDs,ulSatID,ulPassID,ulLocations,apLocations)	\
    (This)->lpVtbl -> SendLocation(This,ulDestID,psecToken,eTrigger,ulSits,alSitIDs,ulSatID,ulPassID,ulLocations,apLocations)

#define IEMSMCCGtwy2_SendAlarm(This,ulDestID,psecToken,eTrigger,wszSource,wszMsg,ulSatID,ulPassID)	\
    (This)->lpVtbl -> SendAlarm(This,ulDestID,psecToken,eTrigger,wszSource,wszMsg,ulSatID,ulPassID)

#define IEMSMCCGtwy2_SendWarning(This,ulDestID,psecToken,eTrigger,wszSource,wszMsg,ulSatID,ulPassID)	\
    (This)->lpVtbl -> SendWarning(This,ulDestID,psecToken,eTrigger,wszSource,wszMsg,ulSatID,ulPassID)

#define IEMSMCCGtwy2_SendStatus(This,ulDestID,psecToken,eTrigger,ulNumStatus,apStatus,ulSatID,ulPassID)	\
    (This)->lpVtbl -> SendStatus(This,ulDestID,psecToken,eTrigger,ulNumStatus,apStatus,ulSatID,ulPassID)

#define IEMSMCCGtwy2_SendOrbitVector(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence,ulSitID,eCtrlCode,ulOrbits,apOrbVectors)	\
    (This)->lpVtbl -> SendOrbitVector(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence,ulSitID,eCtrlCode,ulOrbits,apOrbVectors)

#define IEMSMCCGtwy2_SendTLE(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence,eCtrlCode,ulOrbits,apTLEs)	\
    (This)->lpVtbl -> SendTLE(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence,eCtrlCode,ulOrbits,apTLEs)

#define IEMSMCCGtwy2_SendPassSchedule(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence,eUsage,lSatelliteCount,ulPasses,apPasses)	\
    (This)->lpVtbl -> SendPassSchedule(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence,eUsage,lSatelliteCount,ulPasses,apPasses)

#define IEMSMCCGtwy2_SendMetopSchedule(This,ulDestID,psecToken,eTrigger,ulEntries,apManoeuvres)	\
    (This)->lpVtbl -> SendMetopSchedule(This,ulDestID,psecToken,eTrigger,ulEntries,apManoeuvres)

#define IEMSMCCGtwy2_SendSARPCalib(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence,ulSit,eCtrlCode,ulMsgRequestNumber,ulSatID,ulPassID,timeRollover,dUSOFrequency)	\
    (This)->lpVtbl -> SendSARPCalib(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence,ulSit,eCtrlCode,ulMsgRequestNumber,ulSatID,ulPassID,timeRollover,dUSOFrequency)

#define IEMSMCCGtwy2_SendSARRCalib(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence,ulSit,eCtrlCode,ulSatellites,apSarrData)	\
    (This)->lpVtbl -> SendSARRCalib(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence,ulSit,eCtrlCode,ulSatellites,apSarrData)

#define IEMSMCCGtwy2_SendStartUp(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence)	\
    (This)->lpVtbl -> SendStartUp(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence)

#define IEMSMCCGtwy2_SendLEOPassSummary(This,ulDestID,psecToken,eTrigger,ulSatID,ulPassID,pSummary)	\
    (This)->lpVtbl -> SendLEOPassSummary(This,ulDestID,psecToken,eTrigger,ulSatID,ulPassID,pSummary)

#define IEMSMCCGtwy2_SendGEOPassSummary(This,ulDestID,psecToken,eTrigger,ulSatID,ulPassID,pSummary)	\
    (This)->lpVtbl -> SendGEOPassSummary(This,ulDestID,psecToken,eTrigger,ulSatID,ulPassID,pSummary)

#define IEMSMCCGtwy2_SendCmdAck(This,ulDestID,psecToken,eTrigger,ulCommandMsgSequence,wszStatus)	\
    (This)->lpVtbl -> SendCmdAck(This,ulDestID,psecToken,eTrigger,ulCommandMsgSequence,wszStatus)

#define IEMSMCCGtwy2_SendCommsCheck(This,ulDestID,psecToken,eTrigger)	\
    (This)->lpVtbl -> SendCommsCheck(This,ulDestID,psecToken,eTrigger)

#define IEMSMCCGtwy2_SendCommand(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence,popCommand)	\
    (This)->lpVtbl -> SendCommand(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence,popCommand)

#define IEMSMCCGtwy2_RequestRetransmitMsgs(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence,ulSendToID,ulSeqStart,ulSeqEnd)	\
    (This)->lpVtbl -> RequestRetransmitMsgs(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence,ulSendToID,ulSeqStart,ulSeqEnd)

#define IEMSMCCGtwy2_SendMessages(This,ulDestID,psecToken,eTrigger,ulCount,awszFilePath)	\
    (This)->lpVtbl -> SendMessages(This,ulDestID,psecToken,eTrigger,ulCount,awszFilePath)

#define IEMSMCCGtwy2_SendDataReport(This,ulDestID,psecToken,eTrigger,ulMessages,awszMessages)	\
    (This)->lpVtbl -> SendDataReport(This,ulDestID,psecToken,eTrigger,ulMessages,awszMessages)

#define IEMSMCCGtwy2_SendAlarmsAsLog(This,ulDestID,psecToken,eTrigger,ulAlarms,aLogData)	\
    (This)->lpVtbl -> SendAlarmsAsLog(This,ulDestID,psecToken,eTrigger,ulAlarms,aLogData)

#define IEMSMCCGtwy2_SendWarningsAsLog(This,ulDestID,psecToken,eTrigger,ulWarnings,aLogData)	\
    (This)->lpVtbl -> SendWarningsAsLog(This,ulDestID,psecToken,eTrigger,ulWarnings,aLogData)

#define IEMSMCCGtwy2_SendStatusAsLog(This,ulDestID,psecToken,eTrigger,ulStatus,aLogData)	\
    (This)->lpVtbl -> SendStatusAsLog(This,ulDestID,psecToken,eTrigger,ulStatus,aLogData)


#define IEMSMCCGtwy2_SendPassSchedule2(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence,eUsage,lSatelliteCount,ulPasses,apPasses)	\
    (This)->lpVtbl -> SendPassSchedule2(This,ulDestID,psecToken,eTrigger,ulCmdMsgSequence,eUsage,lSatelliteCount,ulPasses,apPasses)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSMCCGtwy2_SendPassSchedule2_Proxy( 
    IEMSMCCGtwy2 __RPC_FAR * This,
    /* [in] */ unsigned long ulDestID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *psecToken,
    /* [in] */ EMSTRIGGER eTrigger,
    /* [in] */ unsigned long ulCmdMsgSequence,
    /* [in] */ EMSSCHEDUSAGE eUsage,
    /* [in] */ long lSatelliteCount,
    /* [in] */ unsigned long ulPasses,
    /* [size_is][in] */ EMSSATELLITETRACK2 __RPC_FAR *__RPC_FAR *apPasses);


void __RPC_STUB IEMSMCCGtwy2_SendPassSchedule2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSMCCGtwy2_INTERFACE_DEFINED__ */


#ifndef __IEMSHealthStatusGtwy_INTERFACE_DEFINED__
#define __IEMSHealthStatusGtwy_INTERFACE_DEFINED__

/* interface IEMSHealthStatusGtwy */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSHealthStatusGtwy;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9C33E067-BB2A-48c2-809C-CF791705310A")
    IEMSHealthStatusGtwy : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SendHealthStatus( 
            /* [in] */ const unsigned long culDestID,
            /* [in] */ const EMSGATEWAYTOKEN __RPC_FAR *cpsecToken,
            /* [in] */ const EMSTRIGGER ceTrigger,
            /* [in] */ const unsigned long culSendStatusTo,
            /* [in] */ const EMSHEALTHSTATUS cStatus,
            /* [in] */ const unsigned long culRecCount,
            /* [size_is][in] */ const EMSHEALTHDETECTIONS __RPC_FAR *caDetectionRecords) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSHealthStatusGtwyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSHealthStatusGtwy __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSHealthStatusGtwy __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSHealthStatusGtwy __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendHealthStatus )( 
            IEMSHealthStatusGtwy __RPC_FAR * This,
            /* [in] */ const unsigned long culDestID,
            /* [in] */ const EMSGATEWAYTOKEN __RPC_FAR *cpsecToken,
            /* [in] */ const EMSTRIGGER ceTrigger,
            /* [in] */ const unsigned long culSendStatusTo,
            /* [in] */ const EMSHEALTHSTATUS cStatus,
            /* [in] */ const unsigned long culRecCount,
            /* [size_is][in] */ const EMSHEALTHDETECTIONS __RPC_FAR *caDetectionRecords);
        
        END_INTERFACE
    } IEMSHealthStatusGtwyVtbl;

    interface IEMSHealthStatusGtwy
    {
        CONST_VTBL struct IEMSHealthStatusGtwyVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSHealthStatusGtwy_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSHealthStatusGtwy_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSHealthStatusGtwy_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSHealthStatusGtwy_SendHealthStatus(This,culDestID,cpsecToken,ceTrigger,culSendStatusTo,cStatus,culRecCount,caDetectionRecords)	\
    (This)->lpVtbl -> SendHealthStatus(This,culDestID,cpsecToken,ceTrigger,culSendStatusTo,cStatus,culRecCount,caDetectionRecords)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSHealthStatusGtwy_SendHealthStatus_Proxy( 
    IEMSHealthStatusGtwy __RPC_FAR * This,
    /* [in] */ const unsigned long culDestID,
    /* [in] */ const EMSGATEWAYTOKEN __RPC_FAR *cpsecToken,
    /* [in] */ const EMSTRIGGER ceTrigger,
    /* [in] */ const unsigned long culSendStatusTo,
    /* [in] */ const EMSHEALTHSTATUS cStatus,
    /* [in] */ const unsigned long culRecCount,
    /* [size_is][in] */ const EMSHEALTHDETECTIONS __RPC_FAR *caDetectionRecords);


void __RPC_STUB IEMSHealthStatusGtwy_SendHealthStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSHealthStatusGtwy_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_IGATEWAY_0382 */
/* [local] */ 


#pragma pack()


extern RPC_IF_HANDLE __MIDL_itf_IGATEWAY_0382_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_IGATEWAY_0382_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
