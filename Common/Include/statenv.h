/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat Nov 16 11:15:39 2002
 */
/* Compiler settings for STATENV.IDL:
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

#ifndef __STATENV_h__
#define __STATENV_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSEnvironStatus_FWD_DEFINED__
#define __IEMSEnvironStatus_FWD_DEFINED__
typedef interface IEMSEnvironStatus IEMSEnvironStatus;
#endif 	/* __IEMSEnvironStatus_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "emstatus.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_STATENV_0000 */
/* [local] */ 

// {56628AF4-97FC-11d5-8C04-009027912866}
DEFINE_GUID( IID_IEMSEnvironStatus, 0x56628af4, 0x97fc, 0x11d5, 0x8c, 0x4, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);
 


extern RPC_IF_HANDLE __MIDL_itf_STATENV_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_STATENV_0000_v0_0_s_ifspec;

#ifndef __IEMSEnvironStatus_INTERFACE_DEFINED__
#define __IEMSEnvironStatus_INTERFACE_DEFINED__

/* interface IEMSEnvironStatus */
/* [unique][helpstring][uuid][object] */ 


#pragma pack(1)
typedef struct  _tagEMSENVIRONINFO
    {
    WORD wEnvironStatus;
    DWORD dwEnvironStates;
    WORD wInsideTemp;
    WORD wOutsideTemp;
    WORD wWindSpeed;
    WORD wWindDirection;
    }	EMSENVIRONINFO;

typedef struct _tagEMSENVIRONINFO __RPC_FAR *LPEMSENVIRONINFO;


#pragma pack()

EXTERN_C const IID IID_IEMSEnvironStatus;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56628AF4-97FC-11d5-8C04-009027912866")
    IEMSEnvironStatus : public IEMSStatus
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ResetEnvironInfo( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetEnvironInfo( 
            /* [in] */ EMSENVIRONINFO __RPC_FAR *lpInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEnvironInfo( 
            /* [out] */ EMSENVIRONINFO __RPC_FAR *lpInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSEnvironStatusVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSEnvironStatus __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSEnvironStatus __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSEnvironStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetEnvironInfo )( 
            IEMSEnvironStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetEnvironInfo )( 
            IEMSEnvironStatus __RPC_FAR * This,
            /* [in] */ EMSENVIRONINFO __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetEnvironInfo )( 
            IEMSEnvironStatus __RPC_FAR * This,
            /* [out] */ EMSENVIRONINFO __RPC_FAR *lpInfo);
        
        END_INTERFACE
    } IEMSEnvironStatusVtbl;

    interface IEMSEnvironStatus
    {
        CONST_VTBL struct IEMSEnvironStatusVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSEnvironStatus_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSEnvironStatus_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSEnvironStatus_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IEMSEnvironStatus_ResetEnvironInfo(This)	\
    (This)->lpVtbl -> ResetEnvironInfo(This)

#define IEMSEnvironStatus_SetEnvironInfo(This,lpInfo)	\
    (This)->lpVtbl -> SetEnvironInfo(This,lpInfo)

#define IEMSEnvironStatus_GetEnvironInfo(This,lpInfo)	\
    (This)->lpVtbl -> GetEnvironInfo(This,lpInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSEnvironStatus_ResetEnvironInfo_Proxy( 
    IEMSEnvironStatus __RPC_FAR * This);


void __RPC_STUB IEMSEnvironStatus_ResetEnvironInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSEnvironStatus_SetEnvironInfo_Proxy( 
    IEMSEnvironStatus __RPC_FAR * This,
    /* [in] */ EMSENVIRONINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSEnvironStatus_SetEnvironInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSEnvironStatus_GetEnvironInfo_Proxy( 
    IEMSEnvironStatus __RPC_FAR * This,
    /* [out] */ EMSENVIRONINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSEnvironStatus_GetEnvironInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSEnvironStatus_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_STATENV_0012 */
/* [local] */ 

typedef /* [unique] */ IEMSEnvironStatus __RPC_FAR *LPEMSENVIRONSTATUS;



extern RPC_IF_HANDLE __MIDL_itf_STATENV_0012_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_STATENV_0012_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
