/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Dec 15 15:50:42 2008
 */
/* Compiler settings for ..\..\Common\Include\EMSBEACONDEVICE.IDL:
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

#ifndef __EMSBEACONDEVICE_h__
#define __EMSBEACONDEVICE_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSBeaconDevice_FWD_DEFINED__
#define __IEMSBeaconDevice_FWD_DEFINED__
typedef interface IEMSBeaconDevice IEMSBeaconDevice;
#endif 	/* __IEMSBeaconDevice_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "objidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_EMSBEACONDEVICE_0000 */
/* [local] */ 

// Edmonton SERPE-IESM Orbitography Test Beacon
// {E9AB7FEB-9FF3-4622-8EA3-84461FB2C0B7}
DEFINE_GUID(CLSID_EMSEdmSIBeacon, 0xe9ab7feb, 0x9ff3, 0x4622, 0x8e, 0xa3, 0x84, 0x46, 0x1f, 0xb2, 0xc0, 0xb7); 
// {63A83A16-5218-4cdc-8512-E0392FEED340}
DEFINE_GUID(IID_IEMSBeaconDevice, 0x63a83a16, 0x5218, 0x4cdc, 0x85, 0x12, 0xe0, 0x39, 0x2f, 0xee, 0xd3, 0x40);
typedef 
enum _tagEMSBeaconState
    {	EMSBEACONSTATE_Min	= -1,
	EMSBEACONSTATE_UNKNOWN	= -1,
	EMSBEACONSTATE_OFF	= 0,
	EMSBEACONSTATE_ON	= 1,
	EMSBEACONSTATE_Max	= 1
    }	EMSBEACONSTATE;

// 30 digit beacon message as string (+ 1 for null terminator)
typedef char __RPC_FAR EMSBEACONMSGSTRING[ 31 ];



extern RPC_IF_HANDLE __MIDL_itf_EMSBEACONDEVICE_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSBEACONDEVICE_0000_v0_0_s_ifspec;

#ifndef __IEMSBeaconDevice_INTERFACE_DEFINED__
#define __IEMSBeaconDevice_INTERFACE_DEFINED__

/* interface IEMSBeaconDevice */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSBeaconDevice;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("63A83A16-5218-4cdc-8512-E0392FEED340")
    IEMSBeaconDevice : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Init( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TurnOn( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TurnOff( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetState( 
            /* [out] */ EMSBEACONSTATE __RPC_FAR *pBeaconState,
            /* [out][in] */ EMSBEACONMSGSTRING __RPC_FAR *pBeaconMsg) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSBeaconDeviceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSBeaconDevice __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSBeaconDevice __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSBeaconDevice __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Init )( 
            IEMSBeaconDevice __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IEMSBeaconDevice __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TurnOn )( 
            IEMSBeaconDevice __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *TurnOff )( 
            IEMSBeaconDevice __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetState )( 
            IEMSBeaconDevice __RPC_FAR * This,
            /* [out] */ EMSBEACONSTATE __RPC_FAR *pBeaconState,
            /* [out][in] */ EMSBEACONMSGSTRING __RPC_FAR *pBeaconMsg);
        
        END_INTERFACE
    } IEMSBeaconDeviceVtbl;

    interface IEMSBeaconDevice
    {
        CONST_VTBL struct IEMSBeaconDeviceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSBeaconDevice_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSBeaconDevice_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSBeaconDevice_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSBeaconDevice_Init(This)	\
    (This)->lpVtbl -> Init(This)

#define IEMSBeaconDevice_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEMSBeaconDevice_TurnOn(This)	\
    (This)->lpVtbl -> TurnOn(This)

#define IEMSBeaconDevice_TurnOff(This)	\
    (This)->lpVtbl -> TurnOff(This)

#define IEMSBeaconDevice_GetState(This,pBeaconState,pBeaconMsg)	\
    (This)->lpVtbl -> GetState(This,pBeaconState,pBeaconMsg)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSBeaconDevice_Init_Proxy( 
    IEMSBeaconDevice __RPC_FAR * This);


void __RPC_STUB IEMSBeaconDevice_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSBeaconDevice_Reset_Proxy( 
    IEMSBeaconDevice __RPC_FAR * This);


void __RPC_STUB IEMSBeaconDevice_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSBeaconDevice_TurnOn_Proxy( 
    IEMSBeaconDevice __RPC_FAR * This);


void __RPC_STUB IEMSBeaconDevice_TurnOn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSBeaconDevice_TurnOff_Proxy( 
    IEMSBeaconDevice __RPC_FAR * This);


void __RPC_STUB IEMSBeaconDevice_TurnOff_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSBeaconDevice_GetState_Proxy( 
    IEMSBeaconDevice __RPC_FAR * This,
    /* [out] */ EMSBEACONSTATE __RPC_FAR *pBeaconState,
    /* [out][in] */ EMSBEACONMSGSTRING __RPC_FAR *pBeaconMsg);


void __RPC_STUB IEMSBeaconDevice_GetState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSBeaconDevice_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSBEACONDEVICE_0096 */
/* [local] */ 

typedef /* [unique] */ IEMSBeaconDevice __RPC_FAR *LPEMSBEACONDEVICE;



extern RPC_IF_HANDLE __MIDL_itf_EMSBEACONDEVICE_0096_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSBEACONDEVICE_0096_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
