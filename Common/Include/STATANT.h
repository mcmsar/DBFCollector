/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Nov 19 11:37:27 2007
 */
/* Compiler settings for ..\common\include\STATANT.IDL:
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

#ifndef __STATANT_h__
#define __STATANT_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSAntennaStatus_FWD_DEFINED__
#define __IEMSAntennaStatus_FWD_DEFINED__
typedef interface IEMSAntennaStatus IEMSAntennaStatus;
#endif 	/* __IEMSAntennaStatus_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "emstatus.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_STATANT_0000 */
/* [local] */ 

// {56628AF2-97FC-11d5-8C04-009027912866}
DEFINE_GUID( IID_IEMSAntennaStatus, 0x56628af2, 0x97fc, 0x11d5, 0x8c, 0x4, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);
 
#define EMSANTINFOFLAG_STATUS_TRACKING		0x001 // currently tracking a pass - actual motion
#define EMSANTINFOFLAG_STATUS_INBEAM		0x002 // satellite in beam
#define EMSANTINFOFLAG_STATUS_FAULT			0x004 // generic fault
#define EMSANTINFOFLAG_STATUS_CALCTRACK		0x008 // trying to setup/calculate/track a pass
#define EMSANTINFOFLAG_STATUS_HOMING		0x010 // currently homing


extern RPC_IF_HANDLE __MIDL_itf_STATANT_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_STATANT_0000_v0_0_s_ifspec;

#ifndef __IEMSAntennaStatus_INTERFACE_DEFINED__
#define __IEMSAntennaStatus_INTERFACE_DEFINED__

/* interface IEMSAntennaStatus */
/* [unique][helpstring][uuid][object] */ 


#pragma pack(1)
typedef struct  _tagEMSANTENNAINFO
    {
    EMSAZEL azelDesired;
    EMSAZEL azelActual;
    float fAzimuth;
    float fElevation;
    unsigned short uAntennaStatus;
    }	EMSANTENNAINFO;

typedef struct _tagEMSANTENNAINFO __RPC_FAR *LPEMSANTENNAINFO;


#pragma pack()

EXTERN_C const IID IID_IEMSAntennaStatus;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56628AF2-97FC-11d5-8C04-009027912866")
    IEMSAntennaStatus : public IEMSStatus
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ResetAntennaInfo( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAntennaInfo( 
            /* [in] */ EMSANTENNAINFO __RPC_FAR *lpInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAntennaInfo( 
            /* [out] */ EMSANTENNAINFO __RPC_FAR *lpInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSAntennaStatusVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSAntennaStatus __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSAntennaStatus __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSAntennaStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetAntennaInfo )( 
            IEMSAntennaStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetAntennaInfo )( 
            IEMSAntennaStatus __RPC_FAR * This,
            /* [in] */ EMSANTENNAINFO __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAntennaInfo )( 
            IEMSAntennaStatus __RPC_FAR * This,
            /* [out] */ EMSANTENNAINFO __RPC_FAR *lpInfo);
        
        END_INTERFACE
    } IEMSAntennaStatusVtbl;

    interface IEMSAntennaStatus
    {
        CONST_VTBL struct IEMSAntennaStatusVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSAntennaStatus_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSAntennaStatus_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSAntennaStatus_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IEMSAntennaStatus_ResetAntennaInfo(This)	\
    (This)->lpVtbl -> ResetAntennaInfo(This)

#define IEMSAntennaStatus_SetAntennaInfo(This,lpInfo)	\
    (This)->lpVtbl -> SetAntennaInfo(This,lpInfo)

#define IEMSAntennaStatus_GetAntennaInfo(This,lpInfo)	\
    (This)->lpVtbl -> GetAntennaInfo(This,lpInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSAntennaStatus_ResetAntennaInfo_Proxy( 
    IEMSAntennaStatus __RPC_FAR * This);


void __RPC_STUB IEMSAntennaStatus_ResetAntennaInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAntennaStatus_SetAntennaInfo_Proxy( 
    IEMSAntennaStatus __RPC_FAR * This,
    /* [in] */ EMSANTENNAINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSAntennaStatus_SetAntennaInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSAntennaStatus_GetAntennaInfo_Proxy( 
    IEMSAntennaStatus __RPC_FAR * This,
    /* [out] */ EMSANTENNAINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSAntennaStatus_GetAntennaInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSAntennaStatus_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_STATANT_0015 */
/* [local] */ 

typedef /* [unique] */ IEMSAntennaStatus __RPC_FAR *LPEMSANTENNASTATUS;



extern RPC_IF_HANDLE __MIDL_itf_STATANT_0015_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_STATANT_0015_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
