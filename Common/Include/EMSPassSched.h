/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Mar 28 18:52:34 2003
 */
/* Compiler settings for D:\Devsar\leo600\GUI\EMSPassSched\EMSPassSched.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
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

#ifndef __EMSPassSched_h__
#define __EMSPassSched_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSPassSchedCtrl_FWD_DEFINED__
#define __IEMSPassSchedCtrl_FWD_DEFINED__
typedef interface IEMSPassSchedCtrl IEMSPassSchedCtrl;
#endif 	/* __IEMSPassSchedCtrl_FWD_DEFINED__ */


#ifndef __EMSPassSchedCtrl_FWD_DEFINED__
#define __EMSPassSchedCtrl_FWD_DEFINED__

#ifdef __cplusplus
typedef class EMSPassSchedCtrl EMSPassSchedCtrl;
#else
typedef struct EMSPassSchedCtrl EMSPassSchedCtrl;
#endif /* __cplusplus */

#endif 	/* __EMSPassSchedCtrl_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IEMSPassSchedCtrl_INTERFACE_DEFINED__
#define __IEMSPassSchedCtrl_INTERFACE_DEFINED__

/* interface IEMSPassSchedCtrl */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IEMSPassSchedCtrl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0965EA69-2921-4304-B670-F130E9A738FB")
    IEMSPassSchedCtrl : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GenerateNewPassSchedule( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ApplySchedule( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DisplayCurrentSchedule( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DisplayOptions( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ExportToCSV( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnableColour( 
            /* [in] */ BOOL bEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Print( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetTimeRange( 
            /* [in] */ VARIANT TimeTo,
            /* [in] */ VARIANT TimeFrom) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetTimeRange( 
            /* [out] */ VARIANT __RPC_FAR *TimeTo,
            /* [out] */ VARIANT __RPC_FAR *TimeFrom) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Connection( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Connection( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ScheduleTolerance( 
            /* [retval][out] */ double __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ScheduleTolerance( 
            /* [in] */ double newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSPassSchedCtrlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSPassSchedCtrl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSPassSchedCtrl __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSPassSchedCtrl __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IEMSPassSchedCtrl __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IEMSPassSchedCtrl __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IEMSPassSchedCtrl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IEMSPassSchedCtrl __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IEMSPassSchedCtrl __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GenerateNewPassSchedule )( 
            IEMSPassSchedCtrl __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ApplySchedule )( 
            IEMSPassSchedCtrl __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DisplayCurrentSchedule )( 
            IEMSPassSchedCtrl __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DisplayOptions )( 
            IEMSPassSchedCtrl __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ExportToCSV )( 
            IEMSPassSchedCtrl __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EnableColour )( 
            IEMSPassSchedCtrl __RPC_FAR * This,
            /* [in] */ BOOL bEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Print )( 
            IEMSPassSchedCtrl __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTimeRange )( 
            IEMSPassSchedCtrl __RPC_FAR * This,
            /* [in] */ VARIANT TimeTo,
            /* [in] */ VARIANT TimeFrom);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTimeRange )( 
            IEMSPassSchedCtrl __RPC_FAR * This,
            /* [out] */ VARIANT __RPC_FAR *TimeTo,
            /* [out] */ VARIANT __RPC_FAR *TimeFrom);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Connection )( 
            IEMSPassSchedCtrl __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Connection )( 
            IEMSPassSchedCtrl __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ScheduleTolerance )( 
            IEMSPassSchedCtrl __RPC_FAR * This,
            /* [retval][out] */ double __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ScheduleTolerance )( 
            IEMSPassSchedCtrl __RPC_FAR * This,
            /* [in] */ double newVal);
        
        END_INTERFACE
    } IEMSPassSchedCtrlVtbl;

    interface IEMSPassSchedCtrl
    {
        CONST_VTBL struct IEMSPassSchedCtrlVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSPassSchedCtrl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSPassSchedCtrl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSPassSchedCtrl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSPassSchedCtrl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IEMSPassSchedCtrl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IEMSPassSchedCtrl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IEMSPassSchedCtrl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IEMSPassSchedCtrl_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IEMSPassSchedCtrl_GenerateNewPassSchedule(This)	\
    (This)->lpVtbl -> GenerateNewPassSchedule(This)

#define IEMSPassSchedCtrl_ApplySchedule(This)	\
    (This)->lpVtbl -> ApplySchedule(This)

#define IEMSPassSchedCtrl_DisplayCurrentSchedule(This)	\
    (This)->lpVtbl -> DisplayCurrentSchedule(This)

#define IEMSPassSchedCtrl_DisplayOptions(This)	\
    (This)->lpVtbl -> DisplayOptions(This)

#define IEMSPassSchedCtrl_ExportToCSV(This)	\
    (This)->lpVtbl -> ExportToCSV(This)

#define IEMSPassSchedCtrl_EnableColour(This,bEnable)	\
    (This)->lpVtbl -> EnableColour(This,bEnable)

#define IEMSPassSchedCtrl_Print(This)	\
    (This)->lpVtbl -> Print(This)

#define IEMSPassSchedCtrl_SetTimeRange(This,TimeTo,TimeFrom)	\
    (This)->lpVtbl -> SetTimeRange(This,TimeTo,TimeFrom)

#define IEMSPassSchedCtrl_GetTimeRange(This,TimeTo,TimeFrom)	\
    (This)->lpVtbl -> GetTimeRange(This,TimeTo,TimeFrom)

#define IEMSPassSchedCtrl_get_Connection(This,pVal)	\
    (This)->lpVtbl -> get_Connection(This,pVal)

#define IEMSPassSchedCtrl_put_Connection(This,newVal)	\
    (This)->lpVtbl -> put_Connection(This,newVal)

#define IEMSPassSchedCtrl_get_ScheduleTolerance(This,pVal)	\
    (This)->lpVtbl -> get_ScheduleTolerance(This,pVal)

#define IEMSPassSchedCtrl_put_ScheduleTolerance(This,newVal)	\
    (This)->lpVtbl -> put_ScheduleTolerance(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEMSPassSchedCtrl_Refresh_Proxy( 
    IEMSPassSchedCtrl __RPC_FAR * This);


void __RPC_STUB IEMSPassSchedCtrl_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEMSPassSchedCtrl_GenerateNewPassSchedule_Proxy( 
    IEMSPassSchedCtrl __RPC_FAR * This);


void __RPC_STUB IEMSPassSchedCtrl_GenerateNewPassSchedule_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEMSPassSchedCtrl_ApplySchedule_Proxy( 
    IEMSPassSchedCtrl __RPC_FAR * This);


void __RPC_STUB IEMSPassSchedCtrl_ApplySchedule_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEMSPassSchedCtrl_DisplayCurrentSchedule_Proxy( 
    IEMSPassSchedCtrl __RPC_FAR * This);


void __RPC_STUB IEMSPassSchedCtrl_DisplayCurrentSchedule_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEMSPassSchedCtrl_DisplayOptions_Proxy( 
    IEMSPassSchedCtrl __RPC_FAR * This);


void __RPC_STUB IEMSPassSchedCtrl_DisplayOptions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEMSPassSchedCtrl_ExportToCSV_Proxy( 
    IEMSPassSchedCtrl __RPC_FAR * This);


void __RPC_STUB IEMSPassSchedCtrl_ExportToCSV_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEMSPassSchedCtrl_EnableColour_Proxy( 
    IEMSPassSchedCtrl __RPC_FAR * This,
    /* [in] */ BOOL bEnable);


void __RPC_STUB IEMSPassSchedCtrl_EnableColour_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEMSPassSchedCtrl_Print_Proxy( 
    IEMSPassSchedCtrl __RPC_FAR * This);


void __RPC_STUB IEMSPassSchedCtrl_Print_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEMSPassSchedCtrl_SetTimeRange_Proxy( 
    IEMSPassSchedCtrl __RPC_FAR * This,
    /* [in] */ VARIANT TimeTo,
    /* [in] */ VARIANT TimeFrom);


void __RPC_STUB IEMSPassSchedCtrl_SetTimeRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEMSPassSchedCtrl_GetTimeRange_Proxy( 
    IEMSPassSchedCtrl __RPC_FAR * This,
    /* [out] */ VARIANT __RPC_FAR *TimeTo,
    /* [out] */ VARIANT __RPC_FAR *TimeFrom);


void __RPC_STUB IEMSPassSchedCtrl_GetTimeRange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEMSPassSchedCtrl_get_Connection_Proxy( 
    IEMSPassSchedCtrl __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IEMSPassSchedCtrl_get_Connection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IEMSPassSchedCtrl_put_Connection_Proxy( 
    IEMSPassSchedCtrl __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IEMSPassSchedCtrl_put_Connection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEMSPassSchedCtrl_get_ScheduleTolerance_Proxy( 
    IEMSPassSchedCtrl __RPC_FAR * This,
    /* [retval][out] */ double __RPC_FAR *pVal);


void __RPC_STUB IEMSPassSchedCtrl_get_ScheduleTolerance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IEMSPassSchedCtrl_put_ScheduleTolerance_Proxy( 
    IEMSPassSchedCtrl __RPC_FAR * This,
    /* [in] */ double newVal);


void __RPC_STUB IEMSPassSchedCtrl_put_ScheduleTolerance_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSPassSchedCtrl_INTERFACE_DEFINED__ */



#ifndef __EMSPASSSCHEDLib_LIBRARY_DEFINED__
#define __EMSPASSSCHEDLib_LIBRARY_DEFINED__

/* library EMSPASSSCHEDLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_EMSPASSSCHEDLib;

EXTERN_C const CLSID CLSID_EMSPassSchedCtrl;

#ifdef __cplusplus

class DECLSPEC_UUID("E5590D10-49AF-4E1A-8C8F-1D3AF1185FC0")
EMSPassSchedCtrl;
#endif
#endif /* __EMSPASSSCHEDLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
