/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Nov 06 14:53:18 2006
 */
/* Compiler settings for ..\Common\Include\NetConnMgr.idl:
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

#ifndef __NetConnMgr_h__
#define __NetConnMgr_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSNetConnMgr_FWD_DEFINED__
#define __IEMSNetConnMgr_FWD_DEFINED__
typedef interface IEMSNetConnMgr IEMSNetConnMgr;
#endif 	/* __IEMSNetConnMgr_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_NetConnMgr_0000 */
/* [local] */ 

// {F2CD981B-37BD-4fd2-A886-98574C46B473}
DEFINE_GUID(CLSID_EMSNetConnMgr, 0xf2cd981b, 0x37bd, 0x4fd2, 0xa8, 0x86, 0x98, 0x57, 0x4c, 0x46, 0xb4, 0x73);
 
// {07D430D0-3CE4-4300-BDD4-71722737A985}
DEFINE_GUID(IID_IEMSNetConnMgr, 0x7d430d0, 0x3ce4, 0x4300, 0xbd, 0xd4, 0x71, 0x72, 0x27, 0x37, 0xa9, 0x85);
 
#define EMS_IPADDR_LEN 15
#define EMS_CONNECTION_NAME_LEN 255


extern RPC_IF_HANDLE __MIDL_itf_NetConnMgr_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_NetConnMgr_0000_v0_0_s_ifspec;

#ifndef __IEMSNetConnMgr_INTERFACE_DEFINED__
#define __IEMSNetConnMgr_INTERFACE_DEFINED__

/* interface IEMSNetConnMgr */
/* [object][unique][helpstring][uuid] */ 

typedef /* [public][public][public][public] */ 
enum __MIDL_IEMSNetConnMgr_0001
    {	CONN_TYPE_UNKNOWN	= 0,
	CONN_TYPE_ETHERNET	= 1,
	CONN_TYPE_DIALUP	= 2,
	CONN_TYPE_DIALUP_STORM	= 3,
	CONN_TYPE_PDT	= 4
    }	EMSCONNECTION_TYPE;

typedef struct  _tagEMSConnectionInfo
    {
    EMSCONNECTION_TYPE ConnType;
    unsigned char szIPAddr[ 16 ];
    wchar_t wszConnName[ 256 ];
    }	EMSCONNINFO;

typedef struct _tagEMSConnectionInfo __RPC_FAR *LPEMSCONNINFO;


EXTERN_C const IID IID_IEMSNetConnMgr;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("07D430D0-3CE4-4300-BDD4-71722737A985")
    IEMSNetConnMgr : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Init( 
            /* [string][in] */ const wchar_t __RPC_FAR *cwszXmlString) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Connect( 
            /* [string][in] */ const wchar_t __RPC_FAR *cwszConnName,
            /* [out] */ long __RPC_FAR *pRefID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ConnectEx( 
            /* [string][in] */ const wchar_t __RPC_FAR *cwszConnName,
            /* [out][in] */ long __RPC_FAR *pRefID,
            /* [in] */ const BOOL cbBlocking) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Disconnect( 
            /* [string][in] */ const wchar_t __RPC_FAR *cwszConnName,
            /* [in] */ const long lRefID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIPAddresses( 
            /* [out] */ unsigned long __RPC_FAR *pulCount,
            /* [size_is][size_is][string][out] */ wchar_t __RPC_FAR *__RPC_FAR *__RPC_FAR *pawszIPAddresses) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetConnections( 
            /* [out] */ unsigned long __RPC_FAR *pulCount,
            /* [size_is][size_is][out] */ EMSCONNINFO __RPC_FAR *__RPC_FAR *paConnsInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSNetConnMgrVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSNetConnMgr __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSNetConnMgr __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSNetConnMgr __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Init )( 
            IEMSNetConnMgr __RPC_FAR * This,
            /* [string][in] */ const wchar_t __RPC_FAR *cwszXmlString);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Connect )( 
            IEMSNetConnMgr __RPC_FAR * This,
            /* [string][in] */ const wchar_t __RPC_FAR *cwszConnName,
            /* [out] */ long __RPC_FAR *pRefID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ConnectEx )( 
            IEMSNetConnMgr __RPC_FAR * This,
            /* [string][in] */ const wchar_t __RPC_FAR *cwszConnName,
            /* [out][in] */ long __RPC_FAR *pRefID,
            /* [in] */ const BOOL cbBlocking);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Disconnect )( 
            IEMSNetConnMgr __RPC_FAR * This,
            /* [string][in] */ const wchar_t __RPC_FAR *cwszConnName,
            /* [in] */ const long lRefID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIPAddresses )( 
            IEMSNetConnMgr __RPC_FAR * This,
            /* [out] */ unsigned long __RPC_FAR *pulCount,
            /* [size_is][size_is][string][out] */ wchar_t __RPC_FAR *__RPC_FAR *__RPC_FAR *pawszIPAddresses);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConnections )( 
            IEMSNetConnMgr __RPC_FAR * This,
            /* [out] */ unsigned long __RPC_FAR *pulCount,
            /* [size_is][size_is][out] */ EMSCONNINFO __RPC_FAR *__RPC_FAR *paConnsInfo);
        
        END_INTERFACE
    } IEMSNetConnMgrVtbl;

    interface IEMSNetConnMgr
    {
        CONST_VTBL struct IEMSNetConnMgrVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSNetConnMgr_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSNetConnMgr_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSNetConnMgr_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSNetConnMgr_Init(This,cwszXmlString)	\
    (This)->lpVtbl -> Init(This,cwszXmlString)

#define IEMSNetConnMgr_Connect(This,cwszConnName,pRefID)	\
    (This)->lpVtbl -> Connect(This,cwszConnName,pRefID)

#define IEMSNetConnMgr_ConnectEx(This,cwszConnName,pRefID,cbBlocking)	\
    (This)->lpVtbl -> ConnectEx(This,cwszConnName,pRefID,cbBlocking)

#define IEMSNetConnMgr_Disconnect(This,cwszConnName,lRefID)	\
    (This)->lpVtbl -> Disconnect(This,cwszConnName,lRefID)

#define IEMSNetConnMgr_GetIPAddresses(This,pulCount,pawszIPAddresses)	\
    (This)->lpVtbl -> GetIPAddresses(This,pulCount,pawszIPAddresses)

#define IEMSNetConnMgr_GetConnections(This,pulCount,paConnsInfo)	\
    (This)->lpVtbl -> GetConnections(This,pulCount,paConnsInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSNetConnMgr_Init_Proxy( 
    IEMSNetConnMgr __RPC_FAR * This,
    /* [string][in] */ const wchar_t __RPC_FAR *cwszXmlString);


void __RPC_STUB IEMSNetConnMgr_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSNetConnMgr_Connect_Proxy( 
    IEMSNetConnMgr __RPC_FAR * This,
    /* [string][in] */ const wchar_t __RPC_FAR *cwszConnName,
    /* [out] */ long __RPC_FAR *pRefID);


void __RPC_STUB IEMSNetConnMgr_Connect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSNetConnMgr_ConnectEx_Proxy( 
    IEMSNetConnMgr __RPC_FAR * This,
    /* [string][in] */ const wchar_t __RPC_FAR *cwszConnName,
    /* [out][in] */ long __RPC_FAR *pRefID,
    /* [in] */ const BOOL cbBlocking);


void __RPC_STUB IEMSNetConnMgr_ConnectEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSNetConnMgr_Disconnect_Proxy( 
    IEMSNetConnMgr __RPC_FAR * This,
    /* [string][in] */ const wchar_t __RPC_FAR *cwszConnName,
    /* [in] */ const long lRefID);


void __RPC_STUB IEMSNetConnMgr_Disconnect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSNetConnMgr_GetIPAddresses_Proxy( 
    IEMSNetConnMgr __RPC_FAR * This,
    /* [out] */ unsigned long __RPC_FAR *pulCount,
    /* [size_is][size_is][string][out] */ wchar_t __RPC_FAR *__RPC_FAR *__RPC_FAR *pawszIPAddresses);


void __RPC_STUB IEMSNetConnMgr_GetIPAddresses_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSNetConnMgr_GetConnections_Proxy( 
    IEMSNetConnMgr __RPC_FAR * This,
    /* [out] */ unsigned long __RPC_FAR *pulCount,
    /* [size_is][size_is][out] */ EMSCONNINFO __RPC_FAR *__RPC_FAR *paConnsInfo);


void __RPC_STUB IEMSNetConnMgr_GetConnections_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSNetConnMgr_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
