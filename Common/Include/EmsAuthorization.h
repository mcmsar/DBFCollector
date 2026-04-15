/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Feb 10 13:39:40 2004
 */
/* Compiler settings for ..\common\include\EmsAuthorization.idl:
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

#ifndef __EmsAuthorization_h__
#define __EmsAuthorization_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSAuthorization_FWD_DEFINED__
#define __IEMSAuthorization_FWD_DEFINED__
typedef interface IEMSAuthorization IEMSAuthorization;
#endif 	/* __IEMSAuthorization_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "securitytoken.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_EmsAuthorization_0000 */
/* [local] */ 

 
#include "emserror.h"
 
// {1BB891AE-E2FE-4008-8E9D-578F0D4BB3CE}
DEFINE_GUID( CLSID_EMSAuthorization, 0x1bb891ae, 0xe2fe, 0x4008, 0x8e, 0x9d, 0x57, 0x8f, 0xd, 0x4b, 0xb3, 0xce);
// {11C1D615-1625-4685-9DAC-40A086D237C8}
DEFINE_GUID( IID_IEMSAuthorization, 0x11c1d615, 0x1625, 0x4685, 0x9d, 0xac, 0x40, 0xa0, 0x86, 0xd2, 0x37, 0xc8);
#define	EMS_MAX_USER_NAME	( 21 )

typedef struct  _tagEMSAUTHORIZATIONINFO
    {
    unsigned char szUserName[ 21 ];
    ULONG ulRoleID;
    }	EMSAUTHORIZATIONINFO;

typedef struct _tagEMSAUTHORIZATIONINFO __RPC_FAR *LPEMSAUTHORIZATIONINFO;



extern RPC_IF_HANDLE __MIDL_itf_EmsAuthorization_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EmsAuthorization_0000_v0_0_s_ifspec;

#ifndef __IEMSAuthorization_INTERFACE_DEFINED__
#define __IEMSAuthorization_INTERFACE_DEFINED__

/* interface IEMSAuthorization */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSAuthorization;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("11C1D615-1625-4685-9DAC-40A086D237C8")
    IEMSAuthorization : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Authorize( 
            /* [in] */ ULONG ulResourceID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *lpSecurityToken,
            /* [out] */ EMSAUTHORIZATIONINFO __RPC_FAR *authorizationResult) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSAuthorizationVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSAuthorization __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSAuthorization __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSAuthorization __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Authorize )( 
            IEMSAuthorization __RPC_FAR * This,
            /* [in] */ ULONG ulResourceID,
            /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *lpSecurityToken,
            /* [out] */ EMSAUTHORIZATIONINFO __RPC_FAR *authorizationResult);
        
        END_INTERFACE
    } IEMSAuthorizationVtbl;

    interface IEMSAuthorization
    {
        CONST_VTBL struct IEMSAuthorizationVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSAuthorization_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSAuthorization_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSAuthorization_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSAuthorization_Authorize(This,ulResourceID,lpSecurityToken,authorizationResult)	\
    (This)->lpVtbl -> Authorize(This,ulResourceID,lpSecurityToken,authorizationResult)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSAuthorization_Authorize_Proxy( 
    IEMSAuthorization __RPC_FAR * This,
    /* [in] */ ULONG ulResourceID,
    /* [in] */ EMSGATEWAYTOKEN __RPC_FAR *lpSecurityToken,
    /* [out] */ EMSAUTHORIZATIONINFO __RPC_FAR *authorizationResult);


void __RPC_STUB IEMSAuthorization_Authorize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSAuthorization_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EmsAuthorization_0011 */
/* [local] */ 

typedef /* [unique] */ IEMSAuthorization __RPC_FAR *LPEMSAUTHORIZATION;



extern RPC_IF_HANDLE __MIDL_itf_EmsAuthorization_0011_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EmsAuthorization_0011_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
