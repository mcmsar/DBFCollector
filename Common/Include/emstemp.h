/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Jul 16 09:10:47 2002
 */
/* Compiler settings for D:\Devsar\include\emstemp.idl:
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

#ifndef __emstemp_h__
#define __emstemp_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSTemperatureGauge_FWD_DEFINED__
#define __IEMSTemperatureGauge_FWD_DEFINED__
typedef interface IEMSTemperatureGauge IEMSTemperatureGauge;
#endif 	/* __IEMSTemperatureGauge_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "objidl.h"
#include "EMSDEVICES.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_emstemp_0000 */
/* [local] */ 

 
#include "emserror.h"
 
// {8C42E87C-F7F7-4554-8745-EC1E66EA4CF4}
DEFINE_GUID(IID_IEMSTemperatureGauge, 0x8c42e87c, 0xf7f7, 0x4554, 0x87, 0x45, 0xec, 0x1e, 0x66, 0xea, 0x4c, 0xf4);
#define	GAUGETYPE_TEMPERATURE	( 0x2 )



extern RPC_IF_HANDLE __MIDL_itf_emstemp_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_emstemp_0000_v0_0_s_ifspec;

#ifndef __IEMSTemperatureGauge_INTERFACE_DEFINED__
#define __IEMSTemperatureGauge_INTERFACE_DEFINED__

/* interface IEMSTemperatureGauge */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSTemperatureGauge;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8C42E87C-F7F7-4554-8745-EC1E66EA4CF4")
    IEMSTemperatureGauge : public IEMSSubDevice
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetTemperatureCelsius( 
            /* [out] */ double __RPC_FAR *lpdTemperature) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTemperatureKelvin( 
            /* [out] */ double __RPC_FAR *lpdTemperature) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTemperatureFahrenheit( 
            /* [out] */ double __RPC_FAR *lpdTemperature) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTemperatureRankine( 
            /* [out] */ double __RPC_FAR *lpdTemperature) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSTemperatureGaugeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSTemperatureGauge __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSTemperatureGauge __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSTemperatureGauge __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParentDevice )( 
            IEMSTemperatureGauge __RPC_FAR * This,
            LPEMSDEVICE __RPC_FAR *lpDev);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDeviceID )( 
            IEMSTemperatureGauge __RPC_FAR * This,
            LPDWORD lpDevID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTemperatureCelsius )( 
            IEMSTemperatureGauge __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *lpdTemperature);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTemperatureKelvin )( 
            IEMSTemperatureGauge __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *lpdTemperature);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTemperatureFahrenheit )( 
            IEMSTemperatureGauge __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *lpdTemperature);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTemperatureRankine )( 
            IEMSTemperatureGauge __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *lpdTemperature);
        
        END_INTERFACE
    } IEMSTemperatureGaugeVtbl;

    interface IEMSTemperatureGauge
    {
        CONST_VTBL struct IEMSTemperatureGaugeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSTemperatureGauge_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSTemperatureGauge_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSTemperatureGauge_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSTemperatureGauge_GetParentDevice(This,lpDev)	\
    (This)->lpVtbl -> GetParentDevice(This,lpDev)

#define IEMSTemperatureGauge_GetDeviceID(This,lpDevID)	\
    (This)->lpVtbl -> GetDeviceID(This,lpDevID)


#define IEMSTemperatureGauge_GetTemperatureCelsius(This,lpdTemperature)	\
    (This)->lpVtbl -> GetTemperatureCelsius(This,lpdTemperature)

#define IEMSTemperatureGauge_GetTemperatureKelvin(This,lpdTemperature)	\
    (This)->lpVtbl -> GetTemperatureKelvin(This,lpdTemperature)

#define IEMSTemperatureGauge_GetTemperatureFahrenheit(This,lpdTemperature)	\
    (This)->lpVtbl -> GetTemperatureFahrenheit(This,lpdTemperature)

#define IEMSTemperatureGauge_GetTemperatureRankine(This,lpdTemperature)	\
    (This)->lpVtbl -> GetTemperatureRankine(This,lpdTemperature)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSTemperatureGauge_GetTemperatureCelsius_Proxy( 
    IEMSTemperatureGauge __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *lpdTemperature);


void __RPC_STUB IEMSTemperatureGauge_GetTemperatureCelsius_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSTemperatureGauge_GetTemperatureKelvin_Proxy( 
    IEMSTemperatureGauge __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *lpdTemperature);


void __RPC_STUB IEMSTemperatureGauge_GetTemperatureKelvin_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSTemperatureGauge_GetTemperatureFahrenheit_Proxy( 
    IEMSTemperatureGauge __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *lpdTemperature);


void __RPC_STUB IEMSTemperatureGauge_GetTemperatureFahrenheit_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSTemperatureGauge_GetTemperatureRankine_Proxy( 
    IEMSTemperatureGauge __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *lpdTemperature);


void __RPC_STUB IEMSTemperatureGauge_GetTemperatureRankine_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSTemperatureGauge_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_emstemp_0085 */
/* [local] */ 

typedef /* [unique] */ IEMSTemperatureGauge __RPC_FAR *LPEMSTEMPERATUREGAUGE;



extern RPC_IF_HANDLE __MIDL_itf_emstemp_0085_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_emstemp_0085_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
