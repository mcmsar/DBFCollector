/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Oct 31 15:27:45 2003
 */
/* Compiler settings for C:\dev\common\Include\EmsKeyManager.idl:
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

#ifndef __EmsKeyManager_h__
#define __EmsKeyManager_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSKeyManager_FWD_DEFINED__
#define __IEMSKeyManager_FWD_DEFINED__
typedef interface IEMSKeyManager IEMSKeyManager;
#endif 	/* __IEMSKeyManager_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_EmsKeyManager_0000 */
/* [local] */ 

 
#include "emserror.h"
 
// {326B28D0-2EDA-4913-92F8-FE872C0D1780}
DEFINE_GUID( CLSID_EMSKeyManager, 0x326b28d0, 0x2eda, 0x4913, 0x92, 0xf8, 0xfe, 0x87, 0x2c, 0xd, 0x17, 0x80);
// {B4792947-8BE1-44c9-990D-78CF624C7277}
DEFINE_GUID( IID_IEMSKeyManager, 0xb4792947, 0x8be1, 0x44c9, 0x99, 0xd, 0x78, 0xcf, 0x62, 0x4c, 0x72, 0x77);


extern RPC_IF_HANDLE __MIDL_itf_EmsKeyManager_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EmsKeyManager_0000_v0_0_s_ifspec;

#ifndef __IEMSKeyManager_INTERFACE_DEFINED__
#define __IEMSKeyManager_INTERFACE_DEFINED__

/* interface IEMSKeyManager */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSKeyManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B4792947-8BE1-44c9-990D-78CF624C7277")
    IEMSKeyManager : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE generatePublicKey( 
            /* [string][in] */ LPCWSTR szFileName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE generateSymmetricKey( 
            /* [string][in] */ LPCWSTR szPublicKeyFileName,
            /* [string][in] */ LPCWSTR szSymmetricKeyFileName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE generateSymmetricKeyProtect( 
            /* [string][in] */ LPCWSTR szFileName,
            /* [in] */ BOOL bProtect) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSKeyManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSKeyManager __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSKeyManager __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSKeyManager __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *generatePublicKey )( 
            IEMSKeyManager __RPC_FAR * This,
            /* [string][in] */ LPCWSTR szFileName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *generateSymmetricKey )( 
            IEMSKeyManager __RPC_FAR * This,
            /* [string][in] */ LPCWSTR szPublicKeyFileName,
            /* [string][in] */ LPCWSTR szSymmetricKeyFileName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *generateSymmetricKeyProtect )( 
            IEMSKeyManager __RPC_FAR * This,
            /* [string][in] */ LPCWSTR szFileName,
            /* [in] */ BOOL bProtect);
        
        END_INTERFACE
    } IEMSKeyManagerVtbl;

    interface IEMSKeyManager
    {
        CONST_VTBL struct IEMSKeyManagerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSKeyManager_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSKeyManager_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSKeyManager_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSKeyManager_generatePublicKey(This,szFileName)	\
    (This)->lpVtbl -> generatePublicKey(This,szFileName)

#define IEMSKeyManager_generateSymmetricKey(This,szPublicKeyFileName,szSymmetricKeyFileName)	\
    (This)->lpVtbl -> generateSymmetricKey(This,szPublicKeyFileName,szSymmetricKeyFileName)

#define IEMSKeyManager_generateSymmetricKeyProtect(This,szFileName,bProtect)	\
    (This)->lpVtbl -> generateSymmetricKeyProtect(This,szFileName,bProtect)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSKeyManager_generatePublicKey_Proxy( 
    IEMSKeyManager __RPC_FAR * This,
    /* [string][in] */ LPCWSTR szFileName);


void __RPC_STUB IEMSKeyManager_generatePublicKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSKeyManager_generateSymmetricKey_Proxy( 
    IEMSKeyManager __RPC_FAR * This,
    /* [string][in] */ LPCWSTR szPublicKeyFileName,
    /* [string][in] */ LPCWSTR szSymmetricKeyFileName);


void __RPC_STUB IEMSKeyManager_generateSymmetricKey_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSKeyManager_generateSymmetricKeyProtect_Proxy( 
    IEMSKeyManager __RPC_FAR * This,
    /* [string][in] */ LPCWSTR szFileName,
    /* [in] */ BOOL bProtect);


void __RPC_STUB IEMSKeyManager_generateSymmetricKeyProtect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSKeyManager_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EmsKeyManager_0006 */
/* [local] */ 

typedef /* [unique] */ IEMSKeyManager __RPC_FAR *LPEMSKEYMANAGER;



extern RPC_IF_HANDLE __MIDL_itf_EmsKeyManager_0006_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EmsKeyManager_0006_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
