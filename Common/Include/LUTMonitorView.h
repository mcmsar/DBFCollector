/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Jun 20 15:44:59 2006
 */
/* Compiler settings for C:\dev\LUT600 2.1.1\common\include\LUTMonitorView.idl:
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

#ifndef __LUTMonitorView_h__
#define __LUTMonitorView_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSOIPluginControl_FWD_DEFINED__
#define __IEMSOIPluginControl_FWD_DEFINED__
typedef interface IEMSOIPluginControl IEMSOIPluginControl;
#endif 	/* __IEMSOIPluginControl_FWD_DEFINED__ */


#ifndef __IEMSLUTMonitorCtrl_FWD_DEFINED__
#define __IEMSLUTMonitorCtrl_FWD_DEFINED__
typedef interface IEMSLUTMonitorCtrl IEMSLUTMonitorCtrl;
#endif 	/* __IEMSLUTMonitorCtrl_FWD_DEFINED__ */


#ifndef __IEMSRunningLUTMonitors_FWD_DEFINED__
#define __IEMSRunningLUTMonitors_FWD_DEFINED__
typedef interface IEMSRunningLUTMonitors IEMSRunningLUTMonitors;
#endif 	/* __IEMSRunningLUTMonitors_FWD_DEFINED__ */


#ifndef __EMSLUTMonitorCtrl_FWD_DEFINED__
#define __EMSLUTMonitorCtrl_FWD_DEFINED__

#ifdef __cplusplus
typedef class EMSLUTMonitorCtrl EMSLUTMonitorCtrl;
#else
typedef struct EMSLUTMonitorCtrl EMSLUTMonitorCtrl;
#endif /* __cplusplus */

#endif 	/* __EMSLUTMonitorCtrl_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_LUTMonitorView_0000 */
/* [local] */ 

#ifndef _LUTMONITORVIEW_IDL_H_
#define _LUTMONITORVIEW_IDL_H_
// {926E6E0A-DC72-4079-81E9-51E7809DBE65}
DEFINE_GUID( IID_IEMSLUTMonitorCtrl, 0x926E6E0A, 0xDC72, 0x4079, 0x81, 0xE9, 0x51, 0xE7, 0x80, 0x9D, 0xBE, 0x65 );
// {496BF701-79CE-4353-A91B-85E440AB8212}
DEFINE_GUID( IID_IEMSRunningLUTMonitors, 0x496bf701, 0x79ce, 0x4353, 0xa9, 0x1b, 0x85, 0xe4, 0x40, 0xab, 0x82, 0x12 );
// {E1E339FA-A90B-46C3-8D57-3512DF706C1A}
DEFINE_GUID( CLSID_EMSLUTMonitorCtrl, 0xE1E339FA, 0xA90B, 0x46C3, 0x8D, 0x57, 0x35, 0x12, 0xDF, 0x70, 0x6C, 0x1A ); 


extern RPC_IF_HANDLE __MIDL_itf_LUTMonitorView_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_LUTMonitorView_0000_v0_0_s_ifspec;

#ifndef __IEMSOIPluginControl_INTERFACE_DEFINED__
#define __IEMSOIPluginControl_INTERFACE_DEFINED__

/* interface IEMSOIPluginControl */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IEMSOIPluginControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("82BC777B-BEFF-47f0-92A3-ABC02A76E3D2")
    IEMSOIPluginControl : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Refresh( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Stop( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EditProperties( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Export( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Print( 
            /* [in] */ long hDC) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Deserialize( 
            /* [in] */ const BSTR cbstrData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Serialize( 
            /* [out] */ BSTR __RPC_FAR *pbstrData) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ZoomIn( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ZoomOut( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Pan( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Select( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Custom( 
            /* [in] */ const int ciAction) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Connection( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Connection( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Name( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FilterLutID( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FilterLutID( 
            /* [in] */ long newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSOIPluginControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSOIPluginControl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSOIPluginControl __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSOIPluginControl __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IEMSOIPluginControl __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IEMSOIPluginControl __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IEMSOIPluginControl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IEMSOIPluginControl __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Refresh )( 
            IEMSOIPluginControl __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Stop )( 
            IEMSOIPluginControl __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *EditProperties )( 
            IEMSOIPluginControl __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Export )( 
            IEMSOIPluginControl __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Print )( 
            IEMSOIPluginControl __RPC_FAR * This,
            /* [in] */ long hDC);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Deserialize )( 
            IEMSOIPluginControl __RPC_FAR * This,
            /* [in] */ const BSTR cbstrData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Serialize )( 
            IEMSOIPluginControl __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *pbstrData);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ZoomIn )( 
            IEMSOIPluginControl __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ZoomOut )( 
            IEMSOIPluginControl __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Pan )( 
            IEMSOIPluginControl __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Select )( 
            IEMSOIPluginControl __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Custom )( 
            IEMSOIPluginControl __RPC_FAR * This,
            /* [in] */ const int ciAction);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Connection )( 
            IEMSOIPluginControl __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Connection )( 
            IEMSOIPluginControl __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IEMSOIPluginControl __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Name )( 
            IEMSOIPluginControl __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FilterLutID )( 
            IEMSOIPluginControl __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FilterLutID )( 
            IEMSOIPluginControl __RPC_FAR * This,
            /* [in] */ long newVal);
        
        END_INTERFACE
    } IEMSOIPluginControlVtbl;

    interface IEMSOIPluginControl
    {
        CONST_VTBL struct IEMSOIPluginControlVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSOIPluginControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSOIPluginControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSOIPluginControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSOIPluginControl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IEMSOIPluginControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IEMSOIPluginControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IEMSOIPluginControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IEMSOIPluginControl_Refresh(This)	\
    (This)->lpVtbl -> Refresh(This)

#define IEMSOIPluginControl_Stop(This)	\
    (This)->lpVtbl -> Stop(This)

#define IEMSOIPluginControl_EditProperties(This)	\
    (This)->lpVtbl -> EditProperties(This)

#define IEMSOIPluginControl_Export(This)	\
    (This)->lpVtbl -> Export(This)

#define IEMSOIPluginControl_Print(This,hDC)	\
    (This)->lpVtbl -> Print(This,hDC)

#define IEMSOIPluginControl_Deserialize(This,cbstrData)	\
    (This)->lpVtbl -> Deserialize(This,cbstrData)

#define IEMSOIPluginControl_Serialize(This,pbstrData)	\
    (This)->lpVtbl -> Serialize(This,pbstrData)

#define IEMSOIPluginControl_ZoomIn(This)	\
    (This)->lpVtbl -> ZoomIn(This)

#define IEMSOIPluginControl_ZoomOut(This)	\
    (This)->lpVtbl -> ZoomOut(This)

#define IEMSOIPluginControl_Pan(This)	\
    (This)->lpVtbl -> Pan(This)

#define IEMSOIPluginControl_Select(This)	\
    (This)->lpVtbl -> Select(This)

#define IEMSOIPluginControl_Custom(This,ciAction)	\
    (This)->lpVtbl -> Custom(This,ciAction)

#define IEMSOIPluginControl_get_Connection(This,pVal)	\
    (This)->lpVtbl -> get_Connection(This,pVal)

#define IEMSOIPluginControl_put_Connection(This,newVal)	\
    (This)->lpVtbl -> put_Connection(This,newVal)

#define IEMSOIPluginControl_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IEMSOIPluginControl_put_Name(This,newVal)	\
    (This)->lpVtbl -> put_Name(This,newVal)

#define IEMSOIPluginControl_get_FilterLutID(This,pVal)	\
    (This)->lpVtbl -> get_FilterLutID(This,pVal)

#define IEMSOIPluginControl_put_FilterLutID(This,newVal)	\
    (This)->lpVtbl -> put_FilterLutID(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEMSOIPluginControl_Refresh_Proxy( 
    IEMSOIPluginControl __RPC_FAR * This);


void __RPC_STUB IEMSOIPluginControl_Refresh_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEMSOIPluginControl_Stop_Proxy( 
    IEMSOIPluginControl __RPC_FAR * This);


void __RPC_STUB IEMSOIPluginControl_Stop_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEMSOIPluginControl_EditProperties_Proxy( 
    IEMSOIPluginControl __RPC_FAR * This);


void __RPC_STUB IEMSOIPluginControl_EditProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEMSOIPluginControl_Export_Proxy( 
    IEMSOIPluginControl __RPC_FAR * This);


void __RPC_STUB IEMSOIPluginControl_Export_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEMSOIPluginControl_Print_Proxy( 
    IEMSOIPluginControl __RPC_FAR * This,
    /* [in] */ long hDC);


void __RPC_STUB IEMSOIPluginControl_Print_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEMSOIPluginControl_Deserialize_Proxy( 
    IEMSOIPluginControl __RPC_FAR * This,
    /* [in] */ const BSTR cbstrData);


void __RPC_STUB IEMSOIPluginControl_Deserialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEMSOIPluginControl_Serialize_Proxy( 
    IEMSOIPluginControl __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *pbstrData);


void __RPC_STUB IEMSOIPluginControl_Serialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEMSOIPluginControl_ZoomIn_Proxy( 
    IEMSOIPluginControl __RPC_FAR * This);


void __RPC_STUB IEMSOIPluginControl_ZoomIn_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEMSOIPluginControl_ZoomOut_Proxy( 
    IEMSOIPluginControl __RPC_FAR * This);


void __RPC_STUB IEMSOIPluginControl_ZoomOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEMSOIPluginControl_Pan_Proxy( 
    IEMSOIPluginControl __RPC_FAR * This);


void __RPC_STUB IEMSOIPluginControl_Pan_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEMSOIPluginControl_Select_Proxy( 
    IEMSOIPluginControl __RPC_FAR * This);


void __RPC_STUB IEMSOIPluginControl_Select_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IEMSOIPluginControl_Custom_Proxy( 
    IEMSOIPluginControl __RPC_FAR * This,
    /* [in] */ const int ciAction);


void __RPC_STUB IEMSOIPluginControl_Custom_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEMSOIPluginControl_get_Connection_Proxy( 
    IEMSOIPluginControl __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IEMSOIPluginControl_get_Connection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IEMSOIPluginControl_put_Connection_Proxy( 
    IEMSOIPluginControl __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IEMSOIPluginControl_put_Connection_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEMSOIPluginControl_get_Name_Proxy( 
    IEMSOIPluginControl __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IEMSOIPluginControl_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IEMSOIPluginControl_put_Name_Proxy( 
    IEMSOIPluginControl __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IEMSOIPluginControl_put_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IEMSOIPluginControl_get_FilterLutID_Proxy( 
    IEMSOIPluginControl __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IEMSOIPluginControl_get_FilterLutID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IEMSOIPluginControl_put_FilterLutID_Proxy( 
    IEMSOIPluginControl __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IEMSOIPluginControl_put_FilterLutID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSOIPluginControl_INTERFACE_DEFINED__ */


#ifndef __IEMSLUTMonitorCtrl_INTERFACE_DEFINED__
#define __IEMSLUTMonitorCtrl_INTERFACE_DEFINED__

/* interface IEMSLUTMonitorCtrl */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IEMSLUTMonitorCtrl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("926E6E0A-DC72-4079-81E9-51E7809DBE65")
    IEMSLUTMonitorCtrl : public IDispatch
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IEMSLUTMonitorCtrlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSLUTMonitorCtrl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSLUTMonitorCtrl __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSLUTMonitorCtrl __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IEMSLUTMonitorCtrl __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IEMSLUTMonitorCtrl __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IEMSLUTMonitorCtrl __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IEMSLUTMonitorCtrl __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } IEMSLUTMonitorCtrlVtbl;

    interface IEMSLUTMonitorCtrl
    {
        CONST_VTBL struct IEMSLUTMonitorCtrlVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSLUTMonitorCtrl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSLUTMonitorCtrl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSLUTMonitorCtrl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSLUTMonitorCtrl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IEMSLUTMonitorCtrl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IEMSLUTMonitorCtrl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IEMSLUTMonitorCtrl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEMSLUTMonitorCtrl_INTERFACE_DEFINED__ */


#ifndef __IEMSRunningLUTMonitors_INTERFACE_DEFINED__
#define __IEMSRunningLUTMonitors_INTERFACE_DEFINED__

/* interface IEMSRunningLUTMonitors */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSRunningLUTMonitors;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("496BF701-79CE-4353-A91B-85E440AB8212")
    IEMSRunningLUTMonitors : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE IsMonitorRunning( 
            /* [in] */ const ULONG culLutID,
            /* [out] */ BOOL __RPC_FAR *pbRunning) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSRunningLUTMonitorsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSRunningLUTMonitors __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSRunningLUTMonitors __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSRunningLUTMonitors __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsMonitorRunning )( 
            IEMSRunningLUTMonitors __RPC_FAR * This,
            /* [in] */ const ULONG culLutID,
            /* [out] */ BOOL __RPC_FAR *pbRunning);
        
        END_INTERFACE
    } IEMSRunningLUTMonitorsVtbl;

    interface IEMSRunningLUTMonitors
    {
        CONST_VTBL struct IEMSRunningLUTMonitorsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSRunningLUTMonitors_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSRunningLUTMonitors_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSRunningLUTMonitors_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSRunningLUTMonitors_IsMonitorRunning(This,culLutID,pbRunning)	\
    (This)->lpVtbl -> IsMonitorRunning(This,culLutID,pbRunning)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSRunningLUTMonitors_IsMonitorRunning_Proxy( 
    IEMSRunningLUTMonitors __RPC_FAR * This,
    /* [in] */ const ULONG culLutID,
    /* [out] */ BOOL __RPC_FAR *pbRunning);


void __RPC_STUB IEMSRunningLUTMonitors_IsMonitorRunning_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSRunningLUTMonitors_INTERFACE_DEFINED__ */



#ifndef __LUTMONITORVIEWLib_LIBRARY_DEFINED__
#define __LUTMONITORVIEWLib_LIBRARY_DEFINED__

/* library LUTMONITORVIEWLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_LUTMONITORVIEWLib;

EXTERN_C const CLSID CLSID_EMSLUTMonitorCtrl;

#ifdef __cplusplus

class DECLSPEC_UUID("E1E339FA-A90B-46C3-8D57-3512DF706C1A")
EMSLUTMonitorCtrl;
#endif
#endif /* __LUTMONITORVIEWLib_LIBRARY_DEFINED__ */

/* interface __MIDL_itf_LUTMonitorView_0262 */
/* [local] */ 

#endif //_LUTMONITORVIEW_IDL_H_


extern RPC_IF_HANDLE __MIDL_itf_LUTMonitorView_0262_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_LUTMonitorView_0262_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
