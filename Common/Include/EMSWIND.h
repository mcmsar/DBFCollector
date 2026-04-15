/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Jul 16 09:29:30 2002
 */
/* Compiler settings for D:\Devsar\include\EMSWIND.IDL:
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

#ifndef __EMSWIND_h__
#define __EMSWIND_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSWindDirectionGauge_FWD_DEFINED__
#define __IEMSWindDirectionGauge_FWD_DEFINED__
typedef interface IEMSWindDirectionGauge IEMSWindDirectionGauge;
#endif 	/* __IEMSWindDirectionGauge_FWD_DEFINED__ */


#ifndef __IEMSWindSpeedGauge_FWD_DEFINED__
#define __IEMSWindSpeedGauge_FWD_DEFINED__
typedef interface IEMSWindSpeedGauge IEMSWindSpeedGauge;
#endif 	/* __IEMSWindSpeedGauge_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "objidl.h"
#include "EMSDEVICES.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_EMSWIND_0000 */
/* [local] */ 

 
#include "emserror.h"
 
// {917364D3-8F4C-4024-A252-7444713283EB}
DEFINE_GUID(IID_IEMSWindDirectionGauge, 0x917364d3, 0x8f4c, 0x4024, 0xa2, 0x52, 0x74, 0x44, 0x71, 0x32, 0x83, 0xeb);
// {C4C093DD-9A98-4cc1-8F0C-B3D68C1F05AE}
DEFINE_GUID(IID_IEMSWindSpeedGauge, 0xc4c093dd, 0x9a98, 0x4cc1, 0x8f, 0xc, 0xb3, 0xd6, 0x8c, 0x1f, 0x5, 0xae);
// {8D6A7F46-F940-4e4b-961A-FE9C9BC218A6}
DEFINE_GUID(IID_IEMSWindSpeedDevice, 0x8d6a7f46, 0xf940, 0x4e4b, 0x96, 0x1a, 0xfe, 0x9c, 0x9b, 0xc2, 0x18, 0xa6);
#define	GAUGETYPE_WINDDIR	( 0x8 )



extern RPC_IF_HANDLE __MIDL_itf_EMSWIND_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSWIND_0000_v0_0_s_ifspec;

#ifndef __IEMSWindDirectionGauge_INTERFACE_DEFINED__
#define __IEMSWindDirectionGauge_INTERFACE_DEFINED__

/* interface IEMSWindDirectionGauge */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSWindDirectionGauge;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("917364D3-8F4C-4024-A252-7444713283EB")
    IEMSWindDirectionGauge : public IEMSSubDevice
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetWindDirection( 
            /* [out] */ double __RPC_FAR *lpdWindDir) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSWindDirectionGaugeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSWindDirectionGauge __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSWindDirectionGauge __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSWindDirectionGauge __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParentDevice )( 
            IEMSWindDirectionGauge __RPC_FAR * This,
            LPEMSDEVICE __RPC_FAR *lpDev);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDeviceID )( 
            IEMSWindDirectionGauge __RPC_FAR * This,
            LPDWORD lpDevID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetWindDirection )( 
            IEMSWindDirectionGauge __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *lpdWindDir);
        
        END_INTERFACE
    } IEMSWindDirectionGaugeVtbl;

    interface IEMSWindDirectionGauge
    {
        CONST_VTBL struct IEMSWindDirectionGaugeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSWindDirectionGauge_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSWindDirectionGauge_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSWindDirectionGauge_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSWindDirectionGauge_GetParentDevice(This,lpDev)	\
    (This)->lpVtbl -> GetParentDevice(This,lpDev)

#define IEMSWindDirectionGauge_GetDeviceID(This,lpDevID)	\
    (This)->lpVtbl -> GetDeviceID(This,lpDevID)


#define IEMSWindDirectionGauge_GetWindDirection(This,lpdWindDir)	\
    (This)->lpVtbl -> GetWindDirection(This,lpdWindDir)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSWindDirectionGauge_GetWindDirection_Proxy( 
    IEMSWindDirectionGauge __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *lpdWindDir);


void __RPC_STUB IEMSWindDirectionGauge_GetWindDirection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSWindDirectionGauge_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSWIND_0085 */
/* [local] */ 

typedef /* [unique] */ IEMSWindDirectionGauge __RPC_FAR *LPEMSWINDDIRGAUGE;

#define	GAUGETYPE_WINDSPD	( 0x10 )



extern RPC_IF_HANDLE __MIDL_itf_EMSWIND_0085_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSWIND_0085_v0_0_s_ifspec;

#ifndef __IEMSWindSpeedGauge_INTERFACE_DEFINED__
#define __IEMSWindSpeedGauge_INTERFACE_DEFINED__

/* interface IEMSWindSpeedGauge */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSWindSpeedGauge;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C4C093DD-9A98-4cc1-8F0C-B3D68C1F05AE")
    IEMSWindSpeedGauge : public IEMSSubDevice
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetWindSpeed( 
            /* [out] */ double __RPC_FAR *lpdWindSpeed) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSWindSpeedGaugeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSWindSpeedGauge __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSWindSpeedGauge __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSWindSpeedGauge __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetParentDevice )( 
            IEMSWindSpeedGauge __RPC_FAR * This,
            LPEMSDEVICE __RPC_FAR *lpDev);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDeviceID )( 
            IEMSWindSpeedGauge __RPC_FAR * This,
            LPDWORD lpDevID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetWindSpeed )( 
            IEMSWindSpeedGauge __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *lpdWindSpeed);
        
        END_INTERFACE
    } IEMSWindSpeedGaugeVtbl;

    interface IEMSWindSpeedGauge
    {
        CONST_VTBL struct IEMSWindSpeedGaugeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSWindSpeedGauge_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSWindSpeedGauge_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSWindSpeedGauge_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSWindSpeedGauge_GetParentDevice(This,lpDev)	\
    (This)->lpVtbl -> GetParentDevice(This,lpDev)

#define IEMSWindSpeedGauge_GetDeviceID(This,lpDevID)	\
    (This)->lpVtbl -> GetDeviceID(This,lpDevID)


#define IEMSWindSpeedGauge_GetWindSpeed(This,lpdWindSpeed)	\
    (This)->lpVtbl -> GetWindSpeed(This,lpdWindSpeed)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSWindSpeedGauge_GetWindSpeed_Proxy( 
    IEMSWindSpeedGauge __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *lpdWindSpeed);


void __RPC_STUB IEMSWindSpeedGauge_GetWindSpeed_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSWindSpeedGauge_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSWIND_0086 */
/* [local] */ 

typedef /* [unique] */ IEMSWindSpeedGauge __RPC_FAR *LPEMSWINDSPDGAUGE;



extern RPC_IF_HANDLE __MIDL_itf_EMSWIND_0086_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSWIND_0086_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
