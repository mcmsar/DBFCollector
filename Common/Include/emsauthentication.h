/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Oct 31 15:29:41 2003
 */
/* Compiler settings for C:\dev\common\Include\emsauthentication.idl:
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

#ifndef __emsauthentication_h__
#define __emsauthentication_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSAuthentication_FWD_DEFINED__
#define __IEMSAuthentication_FWD_DEFINED__
typedef interface IEMSAuthentication IEMSAuthentication;
#endif 	/* __IEMSAuthentication_FWD_DEFINED__ */


#ifndef __EMSAuthentication_FWD_DEFINED__
#define __EMSAuthentication_FWD_DEFINED__

#ifdef __cplusplus
typedef class EMSAuthentication EMSAuthentication;
#else
typedef struct EMSAuthentication EMSAuthentication;
#endif /* __cplusplus */

#endif 	/* __EMSAuthentication_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "igateway.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_emsauthentication_0000 */
/* [local] */ 


// {DC36C7F3-7E85-42f4-BD85-5BB1744A77B9}
DEFINE_GUID( CLSID_EMSAuthentication, 0xdc36c7f3, 0x7e85, 0x42f4, 0xbd, 0x85, 0x5b, 0xb1, 0x74, 0x4a, 0x77, 0xb9);

// {BD39F8D5-6FF2-48fe-923C-95BA613F0472}
DEFINE_GUID( IID_IEMSAuthentication, 0xbd39f8d5, 0x6ff2, 0x48fe, 0x92, 0x3c, 0x95, 0xba, 0x61, 0x3f, 0x4, 0x72);



extern RPC_IF_HANDLE __MIDL_itf_emsauthentication_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_emsauthentication_0000_v0_0_s_ifspec;

#ifndef __IEMSAuthentication_INTERFACE_DEFINED__
#define __IEMSAuthentication_INTERFACE_DEFINED__

/* interface IEMSAuthentication */
/* [unique][uuid][object] */ 

typedef /* [unique] */ IEMSAuthentication __RPC_FAR *LPEMSAUTHENTICATION;


EXTERN_C const IID IID_IEMSAuthentication;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BD39F8D5-6FF2-48fe-923C-95BA613F0472")
    IEMSAuthentication : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Authenticate( 
            /* [in] */ unsigned long ulNetworkID,
            /* [in] */ unsigned long ulLUTID,
            /* [out] */ LPEMSGATEWAYTOKEN lpSecurityToken) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AuthenticateA( 
            /* [in] */ unsigned long ulNetworkID,
            /* [in] */ unsigned long ulLUTID,
            /* [size_is][in] */ BYTE __RPC_FAR userAccount[  ],
            /* [in] */ long lUserAccountSize,
            /* [size_is][in] */ BYTE __RPC_FAR password[  ],
            /* [in] */ long lPasswordSize,
            /* [out] */ LPEMSGATEWAYTOKEN lpSecurityToken) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSAuthenticationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSAuthentication __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSAuthentication __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSAuthentication __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Authenticate )( 
            IEMSAuthentication __RPC_FAR * This,
            /* [in] */ unsigned long ulNetworkID,
            /* [in] */ unsigned long ulLUTID,
            /* [out] */ LPEMSGATEWAYTOKEN lpSecurityToken);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AuthenticateA )( 
            IEMSAuthentication __RPC_FAR * This,
            /* [in] */ unsigned long ulNetworkID,
            /* [in] */ unsigned long ulLUTID,
            /* [size_is][in] */ BYTE __RPC_FAR userAccount[  ],
            /* [in] */ long lUserAccountSize,
            /* [size_is][in] */ BYTE __RPC_FAR password[  ],
            /* [in] */ long lPasswordSize,
            /* [out] */ LPEMSGATEWAYTOKEN lpSecurityToken);
        
        END_INTERFACE
    } IEMSAuthenticationVtbl;

    interface IEMSAuthentication
    {
        CONST_VTBL struct IEMSAuthenticationVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSAuthentication_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSAuthentication_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSAuthentication_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSAuthentication_Authenticate(This,ulNetworkID,ulLUTID,lpSecurityToken)	\
    (This)->lpVtbl -> Authenticate(This,ulNetworkID,ulLUTID,lpSecurityToken)

#define IEMSAuthentication_AuthenticateA(This,ulNetworkID,ulLUTID,userAccount,lUserAccountSize,password,lPasswordSize,lpSecurityToken)	\
    (This)->lpVtbl -> AuthenticateA(This,ulNetworkID,ulLUTID,userAccount,lUserAccountSize,password,lPasswordSize,lpSecurityToken)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSAuthentication_Authenticate_Proxy( 
    IEMSAuthentication __RPC_FAR * This,
    /* [in] */ unsigned long ulNetworkID,
    /* [in] */ unsigned long ulLUTID,
    /* [out] */ LPEMSGATEWAYTOKEN lpSecurityToken);


void __RPC_STUB IEMSAuthentication_Authenticate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAuthentication_AuthenticateA_Proxy( 
    IEMSAuthentication __RPC_FAR * This,
    /* [in] */ unsigned long ulNetworkID,
    /* [in] */ unsigned long ulLUTID,
    /* [size_is][in] */ BYTE __RPC_FAR userAccount[  ],
    /* [in] */ long lUserAccountSize,
    /* [size_is][in] */ BYTE __RPC_FAR password[  ],
    /* [in] */ long lPasswordSize,
    /* [out] */ LPEMSGATEWAYTOKEN lpSecurityToken);


void __RPC_STUB IEMSAuthentication_AuthenticateA_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSAuthentication_INTERFACE_DEFINED__ */



#ifndef __EMSAuthenticationLib_LIBRARY_DEFINED__
#define __EMSAuthenticationLib_LIBRARY_DEFINED__

/* library EMSAuthenticationLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_EMSAuthenticationLib;

EXTERN_C const CLSID CLSID_EMSAuthentication;

#ifdef __cplusplus

class DECLSPEC_UUID("DC36C7F3-7E85-42f4-BD85-5BB1744A77B9")
EMSAuthentication;
#endif
#endif /* __EMSAuthenticationLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
