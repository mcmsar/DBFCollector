/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Jul 16 10:14:47 2002
 */
/* Compiler settings for D:\Devsar\include\EMSSWITCH.IDL:
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

#ifndef __EMSSWITCH_h__
#define __EMSSWITCH_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSSwitch_FWD_DEFINED__
#define __IEMSSwitch_FWD_DEFINED__
typedef interface IEMSSwitch IEMSSwitch;
#endif 	/* __IEMSSwitch_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "EMSDEVICES.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_EMSSWITCH_0000 */
/* [local] */ 

 
#include "emserror.h"
 
// {A5160908-2489-4d33-AE2B-E7709DB93EC9}
DEFINE_GUID(IID_IEMSSwitch, 0xa5160908, 0x2489, 0x4d33, 0xae, 0x2b, 0xe7, 0x70, 0x9d, 0xb9, 0x3e, 0xc9);
 


extern RPC_IF_HANDLE __MIDL_itf_EMSSWITCH_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSSWITCH_0000_v0_0_s_ifspec;

#ifndef __IEMSSwitch_INTERFACE_DEFINED__
#define __IEMSSwitch_INTERFACE_DEFINED__

/* interface IEMSSwitch */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSSwitch;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A5160908-2489-4d33-AE2B-E7709DB93EC9")
    IEMSSwitch : public IEMSSubDevice
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Set( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReSet( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Test( 
            /* [out] */ BOOL __RPC_FAR *lpbSwitch) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Latched( 
            /* [out] */ BOOL __RPC_FAR *lpbLatched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ClearLatch( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSwitchVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSSwitch __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSSwitch __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSSwitch __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParentDevice )( 
            IEMSSwitch __RPC_FAR * This,
            LPEMSDEVICE __RPC_FAR *lpDev);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDeviceID )( 
            IEMSSwitch __RPC_FAR * This,
            LPDWORD lpDevID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Set )( 
            IEMSSwitch __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReSet )( 
            IEMSSwitch __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Test )( 
            IEMSSwitch __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *lpbSwitch);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Latched )( 
            IEMSSwitch __RPC_FAR * This,
            /* [out] */ BOOL __RPC_FAR *lpbLatched);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClearLatch )( 
            IEMSSwitch __RPC_FAR * This);
        
        END_INTERFACE
    } IEMSSwitchVtbl;

    interface IEMSSwitch
    {
        CONST_VTBL struct IEMSSwitchVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSwitch_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSSwitch_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSSwitch_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSSwitch_GetParentDevice(This,lpDev)	\
    (This)->lpVtbl -> GetParentDevice(This,lpDev)

#define IEMSSwitch_GetDeviceID(This,lpDevID)	\
    (This)->lpVtbl -> GetDeviceID(This,lpDevID)


#define IEMSSwitch_Set(This)	\
    (This)->lpVtbl -> Set(This)

#define IEMSSwitch_ReSet(This)	\
    (This)->lpVtbl -> ReSet(This)

#define IEMSSwitch_Test(This,lpbSwitch)	\
    (This)->lpVtbl -> Test(This,lpbSwitch)

#define IEMSSwitch_Latched(This,lpbLatched)	\
    (This)->lpVtbl -> Latched(This,lpbLatched)

#define IEMSSwitch_ClearLatch(This)	\
    (This)->lpVtbl -> ClearLatch(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSSwitch_Set_Proxy( 
    IEMSSwitch __RPC_FAR * This);


void __RPC_STUB IEMSSwitch_Set_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSwitch_ReSet_Proxy( 
    IEMSSwitch __RPC_FAR * This);


void __RPC_STUB IEMSSwitch_ReSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSwitch_Test_Proxy( 
    IEMSSwitch __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *lpbSwitch);


void __RPC_STUB IEMSSwitch_Test_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSwitch_Latched_Proxy( 
    IEMSSwitch __RPC_FAR * This,
    /* [out] */ BOOL __RPC_FAR *lpbLatched);


void __RPC_STUB IEMSSwitch_Latched_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSwitch_ClearLatch_Proxy( 
    IEMSSwitch __RPC_FAR * This);


void __RPC_STUB IEMSSwitch_ClearLatch_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSSwitch_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSSWITCH_0084 */
/* [local] */ 

typedef /* [unique] */ IEMSSwitch __RPC_FAR *LPEMSSWITCH;



extern RPC_IF_HANDLE __MIDL_itf_EMSSWITCH_0084_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSSWITCH_0084_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
