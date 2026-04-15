/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Jan 31 15:41:01 2003
 */
/* Compiler settings for statcomb.idl:
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

#ifndef __statcomb_h__
#define __statcomb_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSCombine406Status_FWD_DEFINED__
#define __IEMSCombine406Status_FWD_DEFINED__
typedef interface IEMSCombine406Status IEMSCombine406Status;
#endif 	/* __IEMSCombine406Status_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "emstatus.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_statcomb_0000 */
/* [local] */ 

// {2D7FABF8-D55B-4b8d-8B50-E0BB6234177F}
DEFINE_GUID( IID_IEMSCombine406Status, 0x2d7fabf8, 0xd55b, 0x4b8d, 0x8b, 0x50, 0xe0, 0xbb, 0x62, 0x34, 0x17, 0x7f);
 


extern RPC_IF_HANDLE __MIDL_itf_statcomb_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_statcomb_0000_v0_0_s_ifspec;

#ifndef __IEMSCombine406Status_INTERFACE_DEFINED__
#define __IEMSCombine406Status_INTERFACE_DEFINED__

/* interface IEMSCombine406Status */
/* [unique][helpstring][uuid][object] */ 

typedef /* [v1_enum] */ 
enum _tagEMSCOMBINE406STATE
    {	EMS_CMB406_Idle	= 0,
	EMS_CMB406_Initialized	= 1,
	EMS_CMB406_Processing	= 2,
	EMS_CMB406_EndOfPass	= 3,
	EMS_CMB406_WaitingToProcess	= 4
    }	EMSCOMBINE406STATE;

typedef struct  _tagEMSCOMBINE406INFO
    {
    WORD wStatus;
    ULONG ulGeoSarrHistoryRecordsCurrent;
    ULONG ulGeoSarrHistoryRecordsInput;
    ULONG ulGeoSarrHistoryRecordsOutput;
    ULONG ulLeoCalib406RecordsInput;
    ULONG ulCombinedRecordsOutput;
    ULONG ulCombinedUniqueBeacons;
    }	EMSCOMBINE406INFO;

typedef struct _tagEMSCOMBINE406INFO __RPC_FAR *LPEMSCOMBINE406INFO;


EXTERN_C const IID IID_IEMSCombine406Status;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2D7FABF8-D55B-4b8d-8B50-E0BB6234177F")
    IEMSCombine406Status : public IEMSStatus
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ResetCombine406Info( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCombine406Info( 
            /* [in] */ EMSCOMBINE406INFO __RPC_FAR *lpInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCombine406Info( 
            /* [out] */ EMSCOMBINE406INFO __RPC_FAR *lpInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSCombine406StatusVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSCombine406Status __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSCombine406Status __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSCombine406Status __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetCombine406Info )( 
            IEMSCombine406Status __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCombine406Info )( 
            IEMSCombine406Status __RPC_FAR * This,
            /* [in] */ EMSCOMBINE406INFO __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCombine406Info )( 
            IEMSCombine406Status __RPC_FAR * This,
            /* [out] */ EMSCOMBINE406INFO __RPC_FAR *lpInfo);
        
        END_INTERFACE
    } IEMSCombine406StatusVtbl;

    interface IEMSCombine406Status
    {
        CONST_VTBL struct IEMSCombine406StatusVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSCombine406Status_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSCombine406Status_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSCombine406Status_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IEMSCombine406Status_ResetCombine406Info(This)	\
    (This)->lpVtbl -> ResetCombine406Info(This)

#define IEMSCombine406Status_SetCombine406Info(This,lpInfo)	\
    (This)->lpVtbl -> SetCombine406Info(This,lpInfo)

#define IEMSCombine406Status_GetCombine406Info(This,lpInfo)	\
    (This)->lpVtbl -> GetCombine406Info(This,lpInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSCombine406Status_ResetCombine406Info_Proxy( 
    IEMSCombine406Status __RPC_FAR * This);


void __RPC_STUB IEMSCombine406Status_ResetCombine406Info_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSCombine406Status_SetCombine406Info_Proxy( 
    IEMSCombine406Status __RPC_FAR * This,
    /* [in] */ EMSCOMBINE406INFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSCombine406Status_SetCombine406Info_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSCombine406Status_GetCombine406Info_Proxy( 
    IEMSCombine406Status __RPC_FAR * This,
    /* [out] */ EMSCOMBINE406INFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSCombine406Status_GetCombine406Info_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSCombine406Status_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_statcomb_0012 */
/* [local] */ 

typedef /* [unique] */ IEMSCombine406Status __RPC_FAR *LPEMSCOMBINE406STATUS;



extern RPC_IF_HANDLE __MIDL_itf_statcomb_0012_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_statcomb_0012_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
