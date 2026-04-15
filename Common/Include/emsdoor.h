/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Jul 16 10:14:47 2002
 */
/* Compiler settings for D:\Devsar\include\emsdoor.idl:
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

#ifndef __emsdoor_h__
#define __emsdoor_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSDoor_FWD_DEFINED__
#define __IEMSDoor_FWD_DEFINED__
typedef interface IEMSDoor IEMSDoor;
#endif 	/* __IEMSDoor_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "objidl.h"
#include "EMSDEVICES.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_emsdoor_0000 */
/* [local] */ 

 
#include "emserror.h"
 
// {EA7570FC-70E3-4787-9235-DAA6816687FA}
DEFINE_GUID(IID_IEMSDoor, 0xea7570fc, 0x70e3, 0x4787, 0x92, 0x35, 0xda, 0xa6, 0x81, 0x66, 0x87, 0xfa);
#define	EVENT_OPENED	( 0x1 )

#define	EVENT_CLOSED	( 0x2 )

#define	DOOR_STATUS_OPEN	( 0x4 )

#define	DOOR_STATUS_CLOSED	( 0x8 )



extern RPC_IF_HANDLE __MIDL_itf_emsdoor_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_emsdoor_0000_v0_0_s_ifspec;

#ifndef __IEMSDoor_INTERFACE_DEFINED__
#define __IEMSDoor_INTERFACE_DEFINED__

/* interface IEMSDoor */
/* [unique][helpstring][uuid][object] */ 

typedef struct  _tagDoorEvent
    {
    EMSTIME eventTime;
    DWORD eventType;
    }	EMSDOOREVENT;

typedef struct _tagDoorEvent __RPC_FAR *LPEMSDOOREVENT;


EXTERN_C const IID IID_IEMSDoor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EA7570FC-70E3-4787-9235-DAA6816687FA")
    IEMSDoor : public IEMSSubDevice
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetDoorStatus( 
            /* [out] */ LPDWORD lpdwStatus) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDoorLog( 
            /* [out][in] */ LPDWORD dwNumEvents,
            /* [size_is][out] */ EMSDOOREVENT __RPC_FAR DoorEvents[  ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PeekDoorLog( 
            /* [out][in] */ LPDWORD dwNumEvents,
            /* [size_is][out] */ EMSDOOREVENT __RPC_FAR DoorEvents[  ]) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ClearDoorLog( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSDoorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSDoor __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSDoor __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSDoor __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParentDevice )( 
            IEMSDoor __RPC_FAR * This,
            LPEMSDEVICE __RPC_FAR *lpDev);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDeviceID )( 
            IEMSDoor __RPC_FAR * This,
            LPDWORD lpDevID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDoorStatus )( 
            IEMSDoor __RPC_FAR * This,
            /* [out] */ LPDWORD lpdwStatus);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDoorLog )( 
            IEMSDoor __RPC_FAR * This,
            /* [out][in] */ LPDWORD dwNumEvents,
            /* [size_is][out] */ EMSDOOREVENT __RPC_FAR DoorEvents[  ]);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PeekDoorLog )( 
            IEMSDoor __RPC_FAR * This,
            /* [out][in] */ LPDWORD dwNumEvents,
            /* [size_is][out] */ EMSDOOREVENT __RPC_FAR DoorEvents[  ]);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClearDoorLog )( 
            IEMSDoor __RPC_FAR * This);
        
        END_INTERFACE
    } IEMSDoorVtbl;

    interface IEMSDoor
    {
        CONST_VTBL struct IEMSDoorVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSDoor_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSDoor_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSDoor_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSDoor_GetParentDevice(This,lpDev)	\
    (This)->lpVtbl -> GetParentDevice(This,lpDev)

#define IEMSDoor_GetDeviceID(This,lpDevID)	\
    (This)->lpVtbl -> GetDeviceID(This,lpDevID)


#define IEMSDoor_GetDoorStatus(This,lpdwStatus)	\
    (This)->lpVtbl -> GetDoorStatus(This,lpdwStatus)

#define IEMSDoor_GetDoorLog(This,dwNumEvents,DoorEvents)	\
    (This)->lpVtbl -> GetDoorLog(This,dwNumEvents,DoorEvents)

#define IEMSDoor_PeekDoorLog(This,dwNumEvents,DoorEvents)	\
    (This)->lpVtbl -> PeekDoorLog(This,dwNumEvents,DoorEvents)

#define IEMSDoor_ClearDoorLog(This)	\
    (This)->lpVtbl -> ClearDoorLog(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSDoor_GetDoorStatus_Proxy( 
    IEMSDoor __RPC_FAR * This,
    /* [out] */ LPDWORD lpdwStatus);


void __RPC_STUB IEMSDoor_GetDoorStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDoor_GetDoorLog_Proxy( 
    IEMSDoor __RPC_FAR * This,
    /* [out][in] */ LPDWORD dwNumEvents,
    /* [size_is][out] */ EMSDOOREVENT __RPC_FAR DoorEvents[  ]);


void __RPC_STUB IEMSDoor_GetDoorLog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDoor_PeekDoorLog_Proxy( 
    IEMSDoor __RPC_FAR * This,
    /* [out][in] */ LPDWORD dwNumEvents,
    /* [size_is][out] */ EMSDOOREVENT __RPC_FAR DoorEvents[  ]);


void __RPC_STUB IEMSDoor_PeekDoorLog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSDoor_ClearDoorLog_Proxy( 
    IEMSDoor __RPC_FAR * This);


void __RPC_STUB IEMSDoor_ClearDoorLog_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSDoor_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_emsdoor_0085 */
/* [local] */ 

typedef /* [unique] */ IEMSDoor __RPC_FAR *LPEMSDOOR;



extern RPC_IF_HANDLE __MIDL_itf_emsdoor_0085_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_emsdoor_0085_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
