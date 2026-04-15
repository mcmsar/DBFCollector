/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Jul 31 19:26:54 2002
 */
/* Compiler settings for D:\devsar\Devices\NI6711DIGIO\EMSSYSTEMTEST.IDL:
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

#ifndef __EMSSYSTEMTEST_h__
#define __EMSSYSTEMTEST_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSSystemTestSource_FWD_DEFINED__
#define __IEMSSystemTestSource_FWD_DEFINED__
typedef interface IEMSSystemTestSource IEMSSystemTestSource;
#endif 	/* __IEMSSystemTestSource_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "objidl.h"
#include "EMSDEVICES.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_EMSSYSTEMTEST_0000 */
/* [local] */ 

 
#include "emserror.h"
 
// {717ECF81-2426-43be-B751-1BAB651AEBC0}
DEFINE_GUID(IID_IEMSSystemTestSource, 0x717ecf81, 0x2426, 0x43be, 0xb7, 0x51, 0x1b, 0xab, 0x65, 0x1a, 0xeb, 0xc0);
 


extern RPC_IF_HANDLE __MIDL_itf_EMSSYSTEMTEST_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSSYSTEMTEST_0000_v0_0_s_ifspec;

#ifndef __IEMSSystemTestSource_INTERFACE_DEFINED__
#define __IEMSSystemTestSource_INTERFACE_DEFINED__

/* interface IEMSSystemTestSource */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSSystemTestSource;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("717ECF81-2426-43be-B751-1BAB651AEBC0")
    IEMSSystemTestSource : public IEMSSubDevice
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE setWaveFileName( 
            /* [in] */ LPCTSTR lpszWaveFileName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE setDuration( 
            /* [in] */ ULONG ulDuration) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE setPowerLevel( 
            /* [in] */ double dPowerLevel) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE play( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE stop( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSystemTestSourceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSSystemTestSource __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSSystemTestSource __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSSystemTestSource __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParentDevice )( 
            IEMSSystemTestSource __RPC_FAR * This,
            /* [out] */ LPEMSDEVICE __RPC_FAR *lpDev);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDeviceID )( 
            IEMSSystemTestSource __RPC_FAR * This,
            /* [out] */ LPDWORD lpDevID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setWaveFileName )( 
            IEMSSystemTestSource __RPC_FAR * This,
            /* [in] */ LPCTSTR lpszWaveFileName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setDuration )( 
            IEMSSystemTestSource __RPC_FAR * This,
            /* [in] */ ULONG ulDuration);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *setPowerLevel )( 
            IEMSSystemTestSource __RPC_FAR * This,
            /* [in] */ double dPowerLevel);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *play )( 
            IEMSSystemTestSource __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *stop )( 
            IEMSSystemTestSource __RPC_FAR * This);
        
        END_INTERFACE
    } IEMSSystemTestSourceVtbl;

    interface IEMSSystemTestSource
    {
        CONST_VTBL struct IEMSSystemTestSourceVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSystemTestSource_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSSystemTestSource_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSSystemTestSource_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSSystemTestSource_GetParentDevice(This,lpDev)	\
    (This)->lpVtbl -> GetParentDevice(This,lpDev)

#define IEMSSystemTestSource_GetDeviceID(This,lpDevID)	\
    (This)->lpVtbl -> GetDeviceID(This,lpDevID)


#define IEMSSystemTestSource_setWaveFileName(This,lpszWaveFileName)	\
    (This)->lpVtbl -> setWaveFileName(This,lpszWaveFileName)

#define IEMSSystemTestSource_setDuration(This,ulDuration)	\
    (This)->lpVtbl -> setDuration(This,ulDuration)

#define IEMSSystemTestSource_setPowerLevel(This,dPowerLevel)	\
    (This)->lpVtbl -> setPowerLevel(This,dPowerLevel)

#define IEMSSystemTestSource_play(This)	\
    (This)->lpVtbl -> play(This)

#define IEMSSystemTestSource_stop(This)	\
    (This)->lpVtbl -> stop(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSSystemTestSource_setWaveFileName_Proxy( 
    IEMSSystemTestSource __RPC_FAR * This,
    /* [in] */ LPCTSTR lpszWaveFileName);


void __RPC_STUB IEMSSystemTestSource_setWaveFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSystemTestSource_setDuration_Proxy( 
    IEMSSystemTestSource __RPC_FAR * This,
    /* [in] */ ULONG ulDuration);


void __RPC_STUB IEMSSystemTestSource_setDuration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSystemTestSource_setPowerLevel_Proxy( 
    IEMSSystemTestSource __RPC_FAR * This,
    /* [in] */ double dPowerLevel);


void __RPC_STUB IEMSSystemTestSource_setPowerLevel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSystemTestSource_play_Proxy( 
    IEMSSystemTestSource __RPC_FAR * This);


void __RPC_STUB IEMSSystemTestSource_play_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSystemTestSource_stop_Proxy( 
    IEMSSystemTestSource __RPC_FAR * This);


void __RPC_STUB IEMSSystemTestSource_stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSSystemTestSource_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSSYSTEMTEST_0085 */
/* [local] */ 

typedef /* [unique] */ IEMSSystemTestSource __RPC_FAR *LPEMSSYSTEMTESTSOURCE;



extern RPC_IF_HANDLE __MIDL_itf_EMSSYSTEMTEST_0085_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSSYSTEMTEST_0085_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
