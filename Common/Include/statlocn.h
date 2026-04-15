/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri May 02 17:33:38 2008
 */
/* Compiler settings for ..\common\include\STATLOCN.IDL:
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

#ifndef __STATLOCN_h__
#define __STATLOCN_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSLocationStatus_FWD_DEFINED__
#define __IEMSLocationStatus_FWD_DEFINED__
typedef interface IEMSLocationStatus IEMSLocationStatus;
#endif 	/* __IEMSLocationStatus_FWD_DEFINED__ */


#ifndef __IEMSLocnAnalysisStatus_FWD_DEFINED__
#define __IEMSLocnAnalysisStatus_FWD_DEFINED__
typedef interface IEMSLocnAnalysisStatus IEMSLocnAnalysisStatus;
#endif 	/* __IEMSLocnAnalysisStatus_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "emstatus.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_STATLOCN_0000 */
/* [local] */ 

#ifndef INC_STATLOCN
#define INC_STATLOCN

// {ABFAD671-F182-11d5-8D38-009027912866}
DEFINE_GUID( IID_IEMSLocationStatus, 0xabfad671, 0xf182, 0x11d5, 0x8d, 0x38, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);
 
// {3CD5BAEE-56D9-4c83-BC82-6560FC48DFA6}
DEFINE_GUID( IID_IEMSLocnAnalysisStatus, 0x3cd5baee, 0x56d9, 0x4c83, 0xbc, 0x82, 0x65, 0x60, 0xfc, 0x48, 0xdf, 0xa6);
 


extern RPC_IF_HANDLE __MIDL_itf_STATLOCN_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_STATLOCN_0000_v0_0_s_ifspec;

#ifndef __IEMSLocationStatus_INTERFACE_DEFINED__
#define __IEMSLocationStatus_INTERFACE_DEFINED__

/* interface IEMSLocationStatus */
/* [unique][helpstring][uuid][object] */ 

typedef /* [v1_enum] */ 
enum _tagEMSLOCATIONSTATE
    {	EMS_LS_Idle	= 0,
	EMS_LS_Initialized	= 1,
	EMS_LS_Processing	= 2,
	EMS_LS_WaitingToProcess	= 3,
	EMS_LS_Shutdown	= 4
    }	EMSLOCATIONSTATE;


#pragma pack(1)
typedef struct  _tagEMSLOCATIONINFO
    {
    WORD wStatus;
    WORD wNumBeacons;
    WORD wTotalCbc121Solutions;
    WORD wTotalCbc243Solutions;
    WORD wTotalCbc406Solutions;
    WORD wTotal406FdoaSolutions;
    WORD wTotal406Solutions;
    WORD wTotal406UnlocatedSolutions;
    WORD wTotal406SingleBursts;
    ULONG ulResidualRecords;
    ULONG ulInputRecords;
    ULONG ulOutputRecords;
    }	EMSLOCATIONINFO;

typedef struct _tagEMSLOCATIONINFO __RPC_FAR *LPEMSLOCATIONINFO;


#pragma pack()

EXTERN_C const IID IID_IEMSLocationStatus;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ABFAD671-F182-11d5-8D38-009027912866")
    IEMSLocationStatus : public IEMSStatus
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ResetLocationInfo( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetLocationInfo( 
            /* [in] */ EMSLOCATIONINFO __RPC_FAR *lpInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLocationInfo( 
            /* [out] */ EMSLOCATIONINFO __RPC_FAR *lpInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSLocationStatusVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSLocationStatus __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSLocationStatus __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSLocationStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetLocationInfo )( 
            IEMSLocationStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetLocationInfo )( 
            IEMSLocationStatus __RPC_FAR * This,
            /* [in] */ EMSLOCATIONINFO __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLocationInfo )( 
            IEMSLocationStatus __RPC_FAR * This,
            /* [out] */ EMSLOCATIONINFO __RPC_FAR *lpInfo);
        
        END_INTERFACE
    } IEMSLocationStatusVtbl;

    interface IEMSLocationStatus
    {
        CONST_VTBL struct IEMSLocationStatusVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSLocationStatus_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSLocationStatus_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSLocationStatus_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IEMSLocationStatus_ResetLocationInfo(This)	\
    (This)->lpVtbl -> ResetLocationInfo(This)

#define IEMSLocationStatus_SetLocationInfo(This,lpInfo)	\
    (This)->lpVtbl -> SetLocationInfo(This,lpInfo)

#define IEMSLocationStatus_GetLocationInfo(This,lpInfo)	\
    (This)->lpVtbl -> GetLocationInfo(This,lpInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSLocationStatus_ResetLocationInfo_Proxy( 
    IEMSLocationStatus __RPC_FAR * This);


void __RPC_STUB IEMSLocationStatus_ResetLocationInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSLocationStatus_SetLocationInfo_Proxy( 
    IEMSLocationStatus __RPC_FAR * This,
    /* [in] */ EMSLOCATIONINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSLocationStatus_SetLocationInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSLocationStatus_GetLocationInfo_Proxy( 
    IEMSLocationStatus __RPC_FAR * This,
    /* [out] */ EMSLOCATIONINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSLocationStatus_GetLocationInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSLocationStatus_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_STATLOCN_0015 */
/* [local] */ 

typedef /* [unique] */ IEMSLocationStatus __RPC_FAR *LPEMSLOCATIONSTATUS;



extern RPC_IF_HANDLE __MIDL_itf_STATLOCN_0015_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_STATLOCN_0015_v0_0_s_ifspec;

#ifndef __IEMSLocnAnalysisStatus_INTERFACE_DEFINED__
#define __IEMSLocnAnalysisStatus_INTERFACE_DEFINED__

/* interface IEMSLocnAnalysisStatus */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSLocnAnalysisStatus;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3CD5BAEE-56D9-4c83-BC82-6560FC48DFA6")
    IEMSLocnAnalysisStatus : public IEMSStatus
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ResetLocnError( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetMedianLocnError( 
            /* [in] */ const WORD cwSampleSize,
            /* [in] */ const double cdMedianError) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMedianLocnError( 
            /* [out] */ WORD __RPC_FAR *pwSampleSize,
            /* [out] */ double __RPC_FAR *pdMedianError) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSLocnAnalysisStatusVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSLocnAnalysisStatus __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSLocnAnalysisStatus __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSLocnAnalysisStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetLocnError )( 
            IEMSLocnAnalysisStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetMedianLocnError )( 
            IEMSLocnAnalysisStatus __RPC_FAR * This,
            /* [in] */ const WORD cwSampleSize,
            /* [in] */ const double cdMedianError);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMedianLocnError )( 
            IEMSLocnAnalysisStatus __RPC_FAR * This,
            /* [out] */ WORD __RPC_FAR *pwSampleSize,
            /* [out] */ double __RPC_FAR *pdMedianError);
        
        END_INTERFACE
    } IEMSLocnAnalysisStatusVtbl;

    interface IEMSLocnAnalysisStatus
    {
        CONST_VTBL struct IEMSLocnAnalysisStatusVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSLocnAnalysisStatus_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSLocnAnalysisStatus_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSLocnAnalysisStatus_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IEMSLocnAnalysisStatus_ResetLocnError(This)	\
    (This)->lpVtbl -> ResetLocnError(This)

#define IEMSLocnAnalysisStatus_SetMedianLocnError(This,cwSampleSize,cdMedianError)	\
    (This)->lpVtbl -> SetMedianLocnError(This,cwSampleSize,cdMedianError)

#define IEMSLocnAnalysisStatus_GetMedianLocnError(This,pwSampleSize,pdMedianError)	\
    (This)->lpVtbl -> GetMedianLocnError(This,pwSampleSize,pdMedianError)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSLocnAnalysisStatus_ResetLocnError_Proxy( 
    IEMSLocnAnalysisStatus __RPC_FAR * This);


void __RPC_STUB IEMSLocnAnalysisStatus_ResetLocnError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSLocnAnalysisStatus_SetMedianLocnError_Proxy( 
    IEMSLocnAnalysisStatus __RPC_FAR * This,
    /* [in] */ const WORD cwSampleSize,
    /* [in] */ const double cdMedianError);


void __RPC_STUB IEMSLocnAnalysisStatus_SetMedianLocnError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSLocnAnalysisStatus_GetMedianLocnError_Proxy( 
    IEMSLocnAnalysisStatus __RPC_FAR * This,
    /* [out] */ WORD __RPC_FAR *pwSampleSize,
    /* [out] */ double __RPC_FAR *pdMedianError);


void __RPC_STUB IEMSLocnAnalysisStatus_GetMedianLocnError_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSLocnAnalysisStatus_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_STATLOCN_0016 */
/* [local] */ 

typedef /* [unique] */ IEMSLocnAnalysisStatus __RPC_FAR *LPEMSLOCNANALYSISSTATUS;

#endif //INC_STATLOCN


extern RPC_IF_HANDLE __MIDL_itf_STATLOCN_0016_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_STATLOCN_0016_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
