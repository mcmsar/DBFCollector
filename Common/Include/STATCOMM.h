/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Jul 11 08:47:23 2006
 */
/* Compiler settings for ..\common\include\STATCOMM.IDL:
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

#ifndef __STATCOMM_h__
#define __STATCOMM_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSCommsStatus_FWD_DEFINED__
#define __IEMSCommsStatus_FWD_DEFINED__
typedef interface IEMSCommsStatus IEMSCommsStatus;
#endif 	/* __IEMSCommsStatus_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "emstatus.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_STATCOMM_0000 */
/* [local] */ 

// {56628AF8-97FC-11d5-8C04-009027912866}
DEFINE_GUID( IID_IEMSCommsStatus, 0x56628af8, 0x97fc, 0x11d5, 0x8c, 0x4, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);
 


extern RPC_IF_HANDLE __MIDL_itf_STATCOMM_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_STATCOMM_0000_v0_0_s_ifspec;

#ifndef __IEMSCommsStatus_INTERFACE_DEFINED__
#define __IEMSCommsStatus_INTERFACE_DEFINED__

/* interface IEMSCommsStatus */
/* [unique][helpstring][uuid][object] */ 


#pragma pack(1)
typedef struct  _tagEMSCOMMSINFO
    {
    WORD wCommsStatus;
    ULONG ulMsgID;
    ULONG ulRouteID;
    EMSTIME timeTx;
    EMSTIME timeRx;
    ULONG ulRetryCount;
    ULONG ulLossCount;
    ULONG ulLossDuration;
    }	EMSCOMMSINFO;

typedef struct _tagEMSCOMMSINFO __RPC_FAR *LPEMSCOMMSINFO;


#pragma pack()
typedef 
enum _tagEMSCOMMSSTATUS
    {	EMS_COMMS_STATUS_UNKNOWN	= 0,
	EMS_COMMS_STATUS_OK	= 1,
	EMS_COMMS_STATUS_WARN	= 2,
	EMS_COMMS_STATUS_ALARM	= 3
    }	EMSCOMMSSTATUS;


EXTERN_C const IID IID_IEMSCommsStatus;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("56628AF8-97FC-11d5-8C04-009027912866")
    IEMSCommsStatus : public IEMSStatus
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ResetCommsInfo( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetCommsInfo( 
            /* [in] */ EMSCOMMSINFO __RPC_FAR *lpInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCommsInfo( 
            /* [out] */ EMSCOMMSINFO __RPC_FAR *lpInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSCommsStatusVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSCommsStatus __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSCommsStatus __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSCommsStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetCommsInfo )( 
            IEMSCommsStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCommsInfo )( 
            IEMSCommsStatus __RPC_FAR * This,
            /* [in] */ EMSCOMMSINFO __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCommsInfo )( 
            IEMSCommsStatus __RPC_FAR * This,
            /* [out] */ EMSCOMMSINFO __RPC_FAR *lpInfo);
        
        END_INTERFACE
    } IEMSCommsStatusVtbl;

    interface IEMSCommsStatus
    {
        CONST_VTBL struct IEMSCommsStatusVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSCommsStatus_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSCommsStatus_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSCommsStatus_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IEMSCommsStatus_ResetCommsInfo(This)	\
    (This)->lpVtbl -> ResetCommsInfo(This)

#define IEMSCommsStatus_SetCommsInfo(This,lpInfo)	\
    (This)->lpVtbl -> SetCommsInfo(This,lpInfo)

#define IEMSCommsStatus_GetCommsInfo(This,lpInfo)	\
    (This)->lpVtbl -> GetCommsInfo(This,lpInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSCommsStatus_ResetCommsInfo_Proxy( 
    IEMSCommsStatus __RPC_FAR * This);


void __RPC_STUB IEMSCommsStatus_ResetCommsInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSCommsStatus_SetCommsInfo_Proxy( 
    IEMSCommsStatus __RPC_FAR * This,
    /* [in] */ EMSCOMMSINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSCommsStatus_SetCommsInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSCommsStatus_GetCommsInfo_Proxy( 
    IEMSCommsStatus __RPC_FAR * This,
    /* [out] */ EMSCOMMSINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSCommsStatus_GetCommsInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSCommsStatus_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_STATCOMM_0015 */
/* [local] */ 

typedef /* [unique] */ IEMSCommsStatus __RPC_FAR *LPEMSCOMMSSTATUS;



extern RPC_IF_HANDLE __MIDL_itf_STATCOMM_0015_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_STATCOMM_0015_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
