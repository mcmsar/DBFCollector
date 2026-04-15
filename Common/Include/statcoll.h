/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Oct 18 15:07:30 2006
 */
/* Compiler settings for ..\common\include\STATCOLL.IDL:
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

#ifndef __STATCOLL_h__
#define __STATCOLL_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSCollectorStatus_FWD_DEFINED__
#define __IEMSCollectorStatus_FWD_DEFINED__
typedef interface IEMSCollectorStatus IEMSCollectorStatus;
#endif 	/* __IEMSCollectorStatus_FWD_DEFINED__ */


#ifndef __IEMSCollectorStatus2_FWD_DEFINED__
#define __IEMSCollectorStatus2_FWD_DEFINED__
typedef interface IEMSCollectorStatus2 IEMSCollectorStatus2;
#endif 	/* __IEMSCollectorStatus2_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "emstatus.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_STATCOLL_0000 */
/* [local] */ 

#ifndef _STATCOLL_IDL_H
#define _STATCOLL_IDL_H
// {56628AF6-97FC-11d5-8C04-009027912866}
DEFINE_GUID( IID_IEMSCollectorStatus, 0x56628af6, 0x97fc, 0x11d5, 0x8c, 0x4, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);
// {17E7E0F6-38A2-421f-8287-2D754842F75E}
DEFINE_GUID(IID_IEMSCollectorStatus2, 0x17e7e0f6, 0x38a2, 0x421f, 0x82, 0x87, 0x2d, 0x75, 0x48, 0x42, 0xf7, 0x5e);
 
#define EMS_MIN_LOCKED_MOD_INDEX (1.0f)
#define EMS_STATE_COLLECTING (0x1)
 


extern RPC_IF_HANDLE __MIDL_itf_STATCOLL_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_STATCOLL_0000_v0_0_s_ifspec;

#ifndef __IEMSCollectorStatus_INTERFACE_DEFINED__
#define __IEMSCollectorStatus_INTERFACE_DEFINED__

/* interface IEMSCollectorStatus */
/* [unique][helpstring][uuid][object] */ 


#pragma pack(1)
typedef struct  _tagEMSCOLLECTORINFO
    {
    unsigned long ulSatID;
    unsigned short uCollectorStatus;
    EMSTIME carrierTime;
    unsigned short uCarrierLossCount;
    unsigned short uCarrierLossDuration;
    float fCarrierFrequency;
    float fCarrierModIndexMax;
    float fCarrierModIndexMean;
    float fCarrierModIndexRMS;
    float fAGCMean;
    float fAGCRMS;
    ULONG ulMarkerBitRate;
    }	EMSCOLLECTORINFO;

typedef struct _tagEMSCOLLECTORINFO __RPC_FAR *LPEMSCOLLECTORINFO;


#pragma pack()

EXTERN_C const IID IID_IEMSCollectorStatus;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56628AF6-97FC-11d5-8C04-009027912866")
    IEMSCollectorStatus : public IEMSStatus
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ResetCollectorInfo( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCollectorInfo( 
            /* [in] */ EMSCOLLECTORINFO __RPC_FAR *lpInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCollectorInfo( 
            /* [out] */ EMSCOLLECTORINFO __RPC_FAR *lpInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSCollectorStatusVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSCollectorStatus __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSCollectorStatus __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSCollectorStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetCollectorInfo )( 
            IEMSCollectorStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCollectorInfo )( 
            IEMSCollectorStatus __RPC_FAR * This,
            /* [in] */ EMSCOLLECTORINFO __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCollectorInfo )( 
            IEMSCollectorStatus __RPC_FAR * This,
            /* [out] */ EMSCOLLECTORINFO __RPC_FAR *lpInfo);
        
        END_INTERFACE
    } IEMSCollectorStatusVtbl;

    interface IEMSCollectorStatus
    {
        CONST_VTBL struct IEMSCollectorStatusVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSCollectorStatus_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSCollectorStatus_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSCollectorStatus_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IEMSCollectorStatus_ResetCollectorInfo(This)	\
    (This)->lpVtbl -> ResetCollectorInfo(This)

#define IEMSCollectorStatus_SetCollectorInfo(This,lpInfo)	\
    (This)->lpVtbl -> SetCollectorInfo(This,lpInfo)

#define IEMSCollectorStatus_GetCollectorInfo(This,lpInfo)	\
    (This)->lpVtbl -> GetCollectorInfo(This,lpInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSCollectorStatus_ResetCollectorInfo_Proxy( 
    IEMSCollectorStatus __RPC_FAR * This);


void __RPC_STUB IEMSCollectorStatus_ResetCollectorInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSCollectorStatus_SetCollectorInfo_Proxy( 
    IEMSCollectorStatus __RPC_FAR * This,
    /* [in] */ EMSCOLLECTORINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSCollectorStatus_SetCollectorInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSCollectorStatus_GetCollectorInfo_Proxy( 
    IEMSCollectorStatus __RPC_FAR * This,
    /* [out] */ EMSCOLLECTORINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSCollectorStatus_GetCollectorInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSCollectorStatus_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_STATCOLL_0015 */
/* [local] */ 

typedef /* [unique] */ IEMSCollectorStatus __RPC_FAR *LPEMSCOLLECTORSTATUS;



extern RPC_IF_HANDLE __MIDL_itf_STATCOLL_0015_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_STATCOLL_0015_v0_0_s_ifspec;

#ifndef __IEMSCollectorStatus2_INTERFACE_DEFINED__
#define __IEMSCollectorStatus2_INTERFACE_DEFINED__

/* interface IEMSCollectorStatus2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSCollectorStatus2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("17E7E0F6-38A2-421f-8287-2D754842F75E")
    IEMSCollectorStatus2 : public IEMSCollectorStatus
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetCollectorInfoLastActive( 
            /* [out] */ EMSCOLLECTORINFO __RPC_FAR *lpInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSCollectorStatus2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSCollectorStatus2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSCollectorStatus2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSCollectorStatus2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetCollectorInfo )( 
            IEMSCollectorStatus2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCollectorInfo )( 
            IEMSCollectorStatus2 __RPC_FAR * This,
            /* [in] */ EMSCOLLECTORINFO __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCollectorInfo )( 
            IEMSCollectorStatus2 __RPC_FAR * This,
            /* [out] */ EMSCOLLECTORINFO __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCollectorInfoLastActive )( 
            IEMSCollectorStatus2 __RPC_FAR * This,
            /* [out] */ EMSCOLLECTORINFO __RPC_FAR *lpInfo);
        
        END_INTERFACE
    } IEMSCollectorStatus2Vtbl;

    interface IEMSCollectorStatus2
    {
        CONST_VTBL struct IEMSCollectorStatus2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSCollectorStatus2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSCollectorStatus2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSCollectorStatus2_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IEMSCollectorStatus2_ResetCollectorInfo(This)	\
    (This)->lpVtbl -> ResetCollectorInfo(This)

#define IEMSCollectorStatus2_SetCollectorInfo(This,lpInfo)	\
    (This)->lpVtbl -> SetCollectorInfo(This,lpInfo)

#define IEMSCollectorStatus2_GetCollectorInfo(This,lpInfo)	\
    (This)->lpVtbl -> GetCollectorInfo(This,lpInfo)


#define IEMSCollectorStatus2_GetCollectorInfoLastActive(This,lpInfo)	\
    (This)->lpVtbl -> GetCollectorInfoLastActive(This,lpInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSCollectorStatus2_GetCollectorInfoLastActive_Proxy( 
    IEMSCollectorStatus2 __RPC_FAR * This,
    /* [out] */ EMSCOLLECTORINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSCollectorStatus2_GetCollectorInfoLastActive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSCollectorStatus2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_STATCOLL_0016 */
/* [local] */ 

typedef /* [unique] */ IEMSCollectorStatus2 __RPC_FAR *LPEMSCOLLECTORSTATUS2;

#endif //_STATCOLL_IDL_H


extern RPC_IF_HANDLE __MIDL_itf_STATCOLL_0016_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_STATCOLL_0016_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
