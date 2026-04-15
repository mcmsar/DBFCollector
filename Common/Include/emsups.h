/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Feb 04 16:10:05 2003
 */
/* Compiler settings for emsups.idl:
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

#ifndef __emsups_h__
#define __emsups_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSUPS_FWD_DEFINED__
#define __IEMSUPS_FWD_DEFINED__
typedef interface IEMSUPS IEMSUPS;
#endif 	/* __IEMSUPS_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "objidl.h"
#include "EMSDEVICES.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_emsups_0000 */
/* [local] */ 

 
#include "emserror.h"
 
// {5DD5D8A4-352A-470f-8A67-FAE3C87EBBE3}
DEFINE_GUID(IID_IEMSUPS, 0x5dd5d8a4, 0x352a, 0x470f, 0x8a, 0x67, 0xfa, 0xe3, 0xc8, 0x7e, 0xbb, 0xe3);
#define	UPS_STATUS_OK	( 0 )

#define	UPS_STATUS_AC_FAILURE	( 0x1 )

#define	UPS_STATUS_UPS_FAILURE	( 0x2 )

#define	UPS_STATUS_OTHER	( 0x3 )



extern RPC_IF_HANDLE __MIDL_itf_emsups_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_emsups_0000_v0_0_s_ifspec;

#ifndef __IEMSUPS_INTERFACE_DEFINED__
#define __IEMSUPS_INTERFACE_DEFINED__

/* interface IEMSUPS */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSUPS;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5DD5D8A4-352A-470f-8A67-FAE3C87EBBE3")
    IEMSUPS : public IEMSSubDevice
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetUPSStatus( 
            /* [out] */ LPDWORD lpdwStatus) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBatteryTime( 
            /* [out] */ LPDWORD lpdwTimeMinutes) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSUPSVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSUPS __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSUPS __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSUPS __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParentDevice )( 
            IEMSUPS __RPC_FAR * This,
            /* [out] */ LPEMSDEVICE __RPC_FAR *lpDev);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDeviceID )( 
            IEMSUPS __RPC_FAR * This,
            /* [out] */ LPDWORD lpDevID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetUPSStatus )( 
            IEMSUPS __RPC_FAR * This,
            /* [out] */ LPDWORD lpdwStatus);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBatteryTime )( 
            IEMSUPS __RPC_FAR * This,
            /* [out] */ LPDWORD lpdwTimeMinutes);
        
        END_INTERFACE
    } IEMSUPSVtbl;

    interface IEMSUPS
    {
        CONST_VTBL struct IEMSUPSVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSUPS_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSUPS_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSUPS_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSUPS_GetParentDevice(This,lpDev)	\
    (This)->lpVtbl -> GetParentDevice(This,lpDev)

#define IEMSUPS_GetDeviceID(This,lpDevID)	\
    (This)->lpVtbl -> GetDeviceID(This,lpDevID)


#define IEMSUPS_GetUPSStatus(This,lpdwStatus)	\
    (This)->lpVtbl -> GetUPSStatus(This,lpdwStatus)

#define IEMSUPS_GetBatteryTime(This,lpdwTimeMinutes)	\
    (This)->lpVtbl -> GetBatteryTime(This,lpdwTimeMinutes)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSUPS_GetUPSStatus_Proxy( 
    IEMSUPS __RPC_FAR * This,
    /* [out] */ LPDWORD lpdwStatus);


void __RPC_STUB IEMSUPS_GetUPSStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSUPS_GetBatteryTime_Proxy( 
    IEMSUPS __RPC_FAR * This,
    /* [out] */ LPDWORD lpdwTimeMinutes);


void __RPC_STUB IEMSUPS_GetBatteryTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSUPS_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_emsups_0085 */
/* [local] */ 

typedef /* [unique] */ IEMSUPS __RPC_FAR *LPEMSUPS;



extern RPC_IF_HANDLE __MIDL_itf_emsups_0085_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_emsups_0085_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
