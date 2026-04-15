/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Jul 16 09:10:46 2002
 */
/* Compiler settings for D:\Devsar\include\emshumid.idl:
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

#ifndef __emshumid_h__
#define __emshumid_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSHumidityGauge_FWD_DEFINED__
#define __IEMSHumidityGauge_FWD_DEFINED__
typedef interface IEMSHumidityGauge IEMSHumidityGauge;
#endif 	/* __IEMSHumidityGauge_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "objidl.h"
#include "EMSDEVICES.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_emshumid_0000 */
/* [local] */ 

 
#include "emserror.h"
 
// {77A3A72F-1778-4250-B47A-FEDDE37DF27A}
DEFINE_GUID(IID_IEMSHumidityGauge, 0x77a3a72f, 0x1778, 0x4250, 0xb4, 0x7a, 0xfe, 0xdd, 0xe3, 0x7d, 0xf2, 0x7a);
#define	GAUGETYPE_HUMIDITY	( 0x4 )



extern RPC_IF_HANDLE __MIDL_itf_emshumid_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_emshumid_0000_v0_0_s_ifspec;

#ifndef __IEMSHumidityGauge_INTERFACE_DEFINED__
#define __IEMSHumidityGauge_INTERFACE_DEFINED__

/* interface IEMSHumidityGauge */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSHumidityGauge;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("77A3A72F-1778-4250-B47A-FEDDE37DF27A")
    IEMSHumidityGauge : public IEMSSubDevice
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetRelativeHumidity( 
            /* [out] */ double __RPC_FAR *lpdHumidity) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSHumidityGaugeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSHumidityGauge __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSHumidityGauge __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSHumidityGauge __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParentDevice )( 
            IEMSHumidityGauge __RPC_FAR * This,
            LPEMSDEVICE __RPC_FAR *lpDev);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDeviceID )( 
            IEMSHumidityGauge __RPC_FAR * This,
            LPDWORD lpDevID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRelativeHumidity )( 
            IEMSHumidityGauge __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *lpdHumidity);
        
        END_INTERFACE
    } IEMSHumidityGaugeVtbl;

    interface IEMSHumidityGauge
    {
        CONST_VTBL struct IEMSHumidityGaugeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSHumidityGauge_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSHumidityGauge_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSHumidityGauge_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSHumidityGauge_GetParentDevice(This,lpDev)	\
    (This)->lpVtbl -> GetParentDevice(This,lpDev)

#define IEMSHumidityGauge_GetDeviceID(This,lpDevID)	\
    (This)->lpVtbl -> GetDeviceID(This,lpDevID)


#define IEMSHumidityGauge_GetRelativeHumidity(This,lpdHumidity)	\
    (This)->lpVtbl -> GetRelativeHumidity(This,lpdHumidity)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSHumidityGauge_GetRelativeHumidity_Proxy( 
    IEMSHumidityGauge __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *lpdHumidity);


void __RPC_STUB IEMSHumidityGauge_GetRelativeHumidity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSHumidityGauge_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_emshumid_0085 */
/* [local] */ 

typedef /* [unique] */ IEMSHumidityGauge __RPC_FAR *LPEMSHUMIDITYGAUGE;



extern RPC_IF_HANDLE __MIDL_itf_emshumid_0085_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_emshumid_0085_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
