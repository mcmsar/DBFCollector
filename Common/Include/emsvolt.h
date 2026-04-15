/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Jul 16 09:10:47 2002
 */
/* Compiler settings for D:\Devsar\include\emsvolt.idl:
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

#ifndef __emsvolt_h__
#define __emsvolt_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSVoltageGauge_FWD_DEFINED__
#define __IEMSVoltageGauge_FWD_DEFINED__
typedef interface IEMSVoltageGauge IEMSVoltageGauge;
#endif 	/* __IEMSVoltageGauge_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "objidl.h"
#include "EMSDEVICES.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_emsvolt_0000 */
/* [local] */ 

 
#include "emserror.h"
 
// {175725A6-4B7F-4f26-AA50-0D92F55A4A6D}
DEFINE_GUID(IID_IEMSVoltageGauge, 0x175725a6, 0x4b7f, 0x4f26, 0xaa, 0x50, 0xd, 0x92, 0xf5, 0x5a, 0x4a, 0x6d);
#define	GAUGETYPE_VOLTAGE	( 0x1 )



extern RPC_IF_HANDLE __MIDL_itf_emsvolt_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_emsvolt_0000_v0_0_s_ifspec;

#ifndef __IEMSVoltageGauge_INTERFACE_DEFINED__
#define __IEMSVoltageGauge_INTERFACE_DEFINED__

/* interface IEMSVoltageGauge */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSVoltageGauge;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("175725A6-4B7F-4f26-AA50-0D92F55A4A6D")
    IEMSVoltageGauge : public IEMSSubDevice
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetVoltage( 
            /* [out] */ double __RPC_FAR *lpdVoltage) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSVoltageGaugeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSVoltageGauge __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSVoltageGauge __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSVoltageGauge __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParentDevice )( 
            IEMSVoltageGauge __RPC_FAR * This,
            LPEMSDEVICE __RPC_FAR *lpDev);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDeviceID )( 
            IEMSVoltageGauge __RPC_FAR * This,
            LPDWORD lpDevID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetVoltage )( 
            IEMSVoltageGauge __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *lpdVoltage);
        
        END_INTERFACE
    } IEMSVoltageGaugeVtbl;

    interface IEMSVoltageGauge
    {
        CONST_VTBL struct IEMSVoltageGaugeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSVoltageGauge_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSVoltageGauge_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSVoltageGauge_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSVoltageGauge_GetParentDevice(This,lpDev)	\
    (This)->lpVtbl -> GetParentDevice(This,lpDev)

#define IEMSVoltageGauge_GetDeviceID(This,lpDevID)	\
    (This)->lpVtbl -> GetDeviceID(This,lpDevID)


#define IEMSVoltageGauge_GetVoltage(This,lpdVoltage)	\
    (This)->lpVtbl -> GetVoltage(This,lpdVoltage)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSVoltageGauge_GetVoltage_Proxy( 
    IEMSVoltageGauge __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *lpdVoltage);


void __RPC_STUB IEMSVoltageGauge_GetVoltage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSVoltageGauge_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_emsvolt_0085 */
/* [local] */ 

typedef /* [unique] */ IEMSVoltageGauge __RPC_FAR *LPEMSVOLTAGEGAUGE;



extern RPC_IF_HANDLE __MIDL_itf_emsvolt_0085_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_emsvolt_0085_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
