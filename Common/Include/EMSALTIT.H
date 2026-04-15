/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Dec 03 15:38:13 2003
 */
/* Compiler settings for C:\Dev\altitude\EMSALTIT.IDL:
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

#ifndef __EMSALTIT_h__
#define __EMSALTIT_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSAltit_FWD_DEFINED__
#define __IEMSAltit_FWD_DEFINED__
typedef interface IEMSAltit IEMSAltit;
#endif 	/* __IEMSAltit_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_EMSALTIT_0000 */
/* [local] */ 

 
#include "emserror.h"
 
// {A614E4A3-8B7F-48d6-9ACB-1168B8AA301B} 
DEFINE_GUID( CLSID_EMSAltit, 0xa614e4a3, 0x8b7f, 0x48d6, 0x9a, 0xcb, 0x11, 0x68, 0xb8, 0xaa, 0x30, 0x1b); 
 
// {288DEDC0-11A5-4563-8C8D-6F09A15C55D0} 
DEFINE_GUID( IID_IEMSAltit, 0x288dedc0, 0x11a5, 0x4563, 0x8c, 0x8d, 0x6f, 0x9, 0xa1, 0x5c, 0x55, 0xd0); 
 
extern RPC_IF_HANDLE __MIDL_itf_EMSALTIT_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSALTIT_0000_v0_0_s_ifspec;

#ifndef __IEMSAltit_INTERFACE_DEFINED__
#define __IEMSAltit_INTERFACE_DEFINED__

/* interface IEMSAltit */
/* [unique][helpstring][uuid][object] */ 

typedef 
enum _tagEMSTERRAINENUMTYPE
    {	TERRAIN_UNKNOWN	= 0,
	TERRAIN_LAND	= TERRAIN_UNKNOWN + 1,
	TERRAIN_WATER	= TERRAIN_LAND + 1,
	TERRAIN_MOUNTAINEOUS	= TERRAIN_WATER + 1,
	TERRAIN_FOREST	= TERRAIN_MOUNTAINEOUS + 1,
	TERRAIN_URBAN	= TERRAIN_FOREST + 1
    }	EMSTERRAINENUMTYPE;

typedef enum _tagEMSTERRAINENUMTYPE __RPC_FAR *LPEMSTERRAINENUMTYPE;


EXTERN_C const IID IID_IEMSAltit;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("288DEDC0-11A5-4563-8C8D-6F09A15C55D0")
    IEMSAltit : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE LoadAltitudeData( 
            /* [in] */ LPEMSLOCATION lpLocation) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLocationAltitudeInfo( 
            /* [out][in] */ LPEMSLOCATION lpLocation,
            /* [out] */ double __RPC_FAR *pdAltitError,
            /* [out] */ LPEMSTERRAINENUMTYPE peTerrainType) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSAltitVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSAltit __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSAltit __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSAltit __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *LoadAltitudeData )( 
            IEMSAltit __RPC_FAR * This,
            /* [in] */ LPEMSLOCATION lpLocation);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLocationAltitudeInfo )( 
            IEMSAltit __RPC_FAR * This,
            /* [out][in] */ LPEMSLOCATION lpLocation,
            /* [out] */ double __RPC_FAR *pdAltitError,
            /* [out] */ LPEMSTERRAINENUMTYPE peTerrainType);
        
        END_INTERFACE
    } IEMSAltitVtbl;

    interface IEMSAltit
    {
        CONST_VTBL struct IEMSAltitVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSAltit_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSAltit_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSAltit_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSAltit_LoadAltitudeData(This,lpLocation)	\
    (This)->lpVtbl -> LoadAltitudeData(This,lpLocation)

#define IEMSAltit_GetLocationAltitudeInfo(This,lpLocation,pdAltitError,peTerrainType)	\
    (This)->lpVtbl -> GetLocationAltitudeInfo(This,lpLocation,pdAltitError,peTerrainType)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSAltit_LoadAltitudeData_Proxy( 
    IEMSAltit __RPC_FAR * This,
    /* [in] */ LPEMSLOCATION lpLocation);


void __RPC_STUB IEMSAltit_LoadAltitudeData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAltit_GetLocationAltitudeInfo_Proxy( 
    IEMSAltit __RPC_FAR * This,
    /* [out][in] */ LPEMSLOCATION lpLocation,
    /* [out] */ double __RPC_FAR *pdAltitError,
    /* [out] */ LPEMSTERRAINENUMTYPE peTerrainType);


void __RPC_STUB IEMSAltit_GetLocationAltitudeInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSAltit_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSALTIT_0008 */
/* [local] */ 

typedef /* [unique] */ IEMSAltit __RPC_FAR *LPEMSAltit;



extern RPC_IF_HANDLE __MIDL_itf_EMSALTIT_0008_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSALTIT_0008_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
