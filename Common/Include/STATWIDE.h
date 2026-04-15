/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sat Nov 16 11:15:41 2002
 */
/* Compiler settings for STATWIDE.IDL:
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

#ifndef __STATWIDE_h__
#define __STATWIDE_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSWidebandStatus_FWD_DEFINED__
#define __IEMSWidebandStatus_FWD_DEFINED__
typedef interface IEMSWidebandStatus IEMSWidebandStatus;
#endif 	/* __IEMSWidebandStatus_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "emstatus.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_STATWIDE_0000 */
/* [local] */ 

// {56628AF1-97FC-11d5-8C04-009027912866}
DEFINE_GUID( IID_IEMSWidebandStatus, 0x56628af1, 0x97fc, 0x11d5, 0x8c, 0x4, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);
 


extern RPC_IF_HANDLE __MIDL_itf_STATWIDE_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_STATWIDE_0000_v0_0_s_ifspec;

#ifndef __IEMSWidebandStatus_INTERFACE_DEFINED__
#define __IEMSWidebandStatus_INTERFACE_DEFINED__

/* interface IEMSWidebandStatus */
/* [unique][helpstring][uuid][object] */ 


#pragma pack(1)
typedef struct  _tagEMSWIDEBANDINFO
    {
    WORD wWidebandStatus;
    WORD wSarpTotalFrames;
    WORD wSarpTotalMessages;
    WORD wSarpTotalSyncLosses;
    WORD wSarpTotalNoSyncs;
    WORD wSarpCurrentSyncLosses;
    WORD wSarpCurrentNoSyncs;
    WORD wSarrTotalMessages;
    WORD wCBC121Counts;
    WORD wCBC243Counts;
    WORD wCBC406Counts;
    WORD wNumGroup;
    WORD wNumActive;
    WORD wNumActiveDistress;
    WORD wNumDistressMsg;
    WORD wNumMsg;
    WORD wNumDet;
    EMSTIME LastTimeDetect;
    EMSTIME LastRefBcnTimeDetect;
    }	EMSWIDEBANDINFO;

typedef struct _tagEMSWIDEBANDINFO __RPC_FAR *LPEMSWIDEBANDINFO;


#pragma pack()

EXTERN_C const IID IID_IEMSWidebandStatus;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56628AF1-97FC-11d5-8C04-009027912866")
    IEMSWidebandStatus : public IEMSStatus
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ResetWidebandInfo( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetWidebandInfo( 
            /* [in] */ EMSWIDEBANDINFO __RPC_FAR *lpInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetWidebandInfo( 
            /* [out] */ EMSWIDEBANDINFO __RPC_FAR *lpInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSWidebandStatusVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSWidebandStatus __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSWidebandStatus __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSWidebandStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetWidebandInfo )( 
            IEMSWidebandStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetWidebandInfo )( 
            IEMSWidebandStatus __RPC_FAR * This,
            /* [in] */ EMSWIDEBANDINFO __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetWidebandInfo )( 
            IEMSWidebandStatus __RPC_FAR * This,
            /* [out] */ EMSWIDEBANDINFO __RPC_FAR *lpInfo);
        
        END_INTERFACE
    } IEMSWidebandStatusVtbl;

    interface IEMSWidebandStatus
    {
        CONST_VTBL struct IEMSWidebandStatusVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSWidebandStatus_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSWidebandStatus_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSWidebandStatus_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IEMSWidebandStatus_ResetWidebandInfo(This)	\
    (This)->lpVtbl -> ResetWidebandInfo(This)

#define IEMSWidebandStatus_SetWidebandInfo(This,lpInfo)	\
    (This)->lpVtbl -> SetWidebandInfo(This,lpInfo)

#define IEMSWidebandStatus_GetWidebandInfo(This,lpInfo)	\
    (This)->lpVtbl -> GetWidebandInfo(This,lpInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSWidebandStatus_ResetWidebandInfo_Proxy( 
    IEMSWidebandStatus __RPC_FAR * This);


void __RPC_STUB IEMSWidebandStatus_ResetWidebandInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSWidebandStatus_SetWidebandInfo_Proxy( 
    IEMSWidebandStatus __RPC_FAR * This,
    /* [in] */ EMSWIDEBANDINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSWidebandStatus_SetWidebandInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSWidebandStatus_GetWidebandInfo_Proxy( 
    IEMSWidebandStatus __RPC_FAR * This,
    /* [out] */ EMSWIDEBANDINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSWidebandStatus_GetWidebandInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSWidebandStatus_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_STATWIDE_0012 */
/* [local] */ 

typedef /* [unique] */ IEMSWidebandStatus __RPC_FAR *LPEMSWIDEBANDSTATUS;



extern RPC_IF_HANDLE __MIDL_itf_STATWIDE_0012_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_STATWIDE_0012_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
