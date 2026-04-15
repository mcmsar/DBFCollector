

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Wed Jan 26 14:35:49 2005
 */
/* Compiler settings for ..\common\include\EMSLOGGR.IDL:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


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

#ifndef __EMSLOGGR_h__
#define __EMSLOGGR_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IEMSLeo600Logger_FWD_DEFINED__
#define __IEMSLeo600Logger_FWD_DEFINED__
typedef interface IEMSLeo600Logger IEMSLeo600Logger;
#endif 	/* __IEMSLeo600Logger_FWD_DEFINED__ */


#ifndef __IEMS600Logger_FWD_DEFINED__
#define __IEMS600Logger_FWD_DEFINED__
typedef interface IEMS600Logger IEMS600Logger;
#endif 	/* __IEMS600Logger_FWD_DEFINED__ */


#ifndef __IEMS600LoggerEx_FWD_DEFINED__
#define __IEMS600LoggerEx_FWD_DEFINED__
typedef interface IEMS600LoggerEx IEMS600LoggerEx;
#endif 	/* __IEMS600LoggerEx_FWD_DEFINED__ */


#ifndef __EMSLeo600Logger_FWD_DEFINED__
#define __EMSLeo600Logger_FWD_DEFINED__

#ifdef __cplusplus
typedef class EMSLeo600Logger EMSLeo600Logger;
#else
typedef struct EMSLeo600Logger EMSLeo600Logger;
#endif /* __cplusplus */

#endif 	/* __EMSLeo600Logger_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_EMSLOGGR_0000 */
/* [local] */ 

 
#include "emserror.h"
#include "loggrcat.h"
 
// {73FF4561-01F2-11d6-8D67-009027912866}
DEFINE_GUID( CLSID_EMSLeo600Logger, 0x73ff4561, 0x1f2, 0x11d6, 0x8d, 0x67, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);
// {A6C83E4F-B831-417d-8A9C-0FEF53C4182C}
DEFINE_GUID( IID_IEMS600LoggerEx, 0xa6c83e4f, 0xb831, 0x417d, 0x8a, 0x9c, 0x0f, 0xef, 0x53, 0xc4, 0x18, 0x2c );
//*** The following interfaces are deprecated. Use IEMS600LoggerEx instead.
// {73FF4562-01F2-11d6-8D67-009027912866}
DEFINE_GUID( IID_IEMSLeo600Logger, 0x73ff4562, 0x1f2, 0x11d6, 0x8d, 0x67, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);
// {50C0ED6D-39DE-4751-B0C1-CCAFA14AD41D}
DEFINE_GUID( IID_IEMS600Logger, 0x50c0ed6d, 0x39de, 0x4751, 0xb0, 0xc1, 0xcc, 0xaf, 0xa1, 0x4a, 0xd4, 0x1d );
//*** End of deprecated interaces
 
#define EMS_LOGGER_MAX_STRINGS (32)
 
// 
// cMsgType & 0x80 == set of msgs 
#define EMS_LOGMSG_MORE_FLAG      (0x80)
typedef /* [public][public][public][public] */ 
const enum __MIDL___MIDL_itf_EMSLOGGR_0000_0001
    {	EMSLogMsgMoreFlag	= 0x80,
	EMSLogMsgTrace	= 0,
	EMSLogMsgDebug	= 1,
	EMSLogMsgStatus	= 2,
	EMSLogMsgMoreStatus	= EMSLogMsgStatus + EMSLogMsgMoreFlag,
	EMSLogMsgInfo	= 3,
	EMSLogMsgWarn	= 4,
	EMSLogMsgAlarm	= 5,
	EMSLogMsgFatal	= 6,
	EMSLogMsgStartup	= 7
    } 	EMSLOGMSGTYPE;

 
//*** Note that the ReportLogEvent methods belong to the deprecated interfaces.
//*** Use Report() instead.
 
#ifdef UNICODE
#define ReportLogEvent     ReportLogEventW
#else
#define ReportLogEvent     ReportLogEventA
#endif // UNICODE


extern RPC_IF_HANDLE __MIDL_itf_EMSLOGGR_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSLOGGR_0000_v0_0_s_ifspec;

#ifndef __IEMSLeo600Logger_INTERFACE_DEFINED__
#define __IEMSLeo600Logger_INTERFACE_DEFINED__

/* interface IEMSLeo600Logger */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSLeo600Logger;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("73FF4562-01F2-11d6-8D67-009027912866")
    IEMSLeo600Logger : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ ULONG ulLutID,
            /* [in] */ WORD wProcessID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReportLogEventW( 
            /* [in] */ EMSLOGMSGTYPE msgType,
            /* [in] */ DWORD dwEvent,
            /* [size_is][in] */ const LPWSTR lpszStrings,
            /* [in] */ ULONG ulLength) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReportLogEventA( 
            /* [in] */ EMSLOGMSGTYPE msgType,
            /* [in] */ DWORD dwEvent,
            /* [size_is][in] */ const LPSTR lpszStrings,
            /* [in] */ ULONG ulLength) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSLeo600LoggerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEMSLeo600Logger * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEMSLeo600Logger * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEMSLeo600Logger * This);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IEMSLeo600Logger * This,
            /* [in] */ ULONG ulLutID,
            /* [in] */ WORD wProcessID);
        
        HRESULT ( STDMETHODCALLTYPE *ReportLogEventW )( 
            IEMSLeo600Logger * This,
            /* [in] */ EMSLOGMSGTYPE msgType,
            /* [in] */ DWORD dwEvent,
            /* [size_is][in] */ const LPWSTR lpszStrings,
            /* [in] */ ULONG ulLength);
        
        HRESULT ( STDMETHODCALLTYPE *ReportLogEventA )( 
            IEMSLeo600Logger * This,
            /* [in] */ EMSLOGMSGTYPE msgType,
            /* [in] */ DWORD dwEvent,
            /* [size_is][in] */ const LPSTR lpszStrings,
            /* [in] */ ULONG ulLength);
        
        END_INTERFACE
    } IEMSLeo600LoggerVtbl;

    interface IEMSLeo600Logger
    {
        CONST_VTBL struct IEMSLeo600LoggerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSLeo600Logger_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSLeo600Logger_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSLeo600Logger_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSLeo600Logger_Initialize(This,ulLutID,wProcessID)	\
    (This)->lpVtbl -> Initialize(This,ulLutID,wProcessID)

#define IEMSLeo600Logger_ReportLogEventW(This,msgType,dwEvent,lpszStrings,ulLength)	\
    (This)->lpVtbl -> ReportLogEventW(This,msgType,dwEvent,lpszStrings,ulLength)

#define IEMSLeo600Logger_ReportLogEventA(This,msgType,dwEvent,lpszStrings,ulLength)	\
    (This)->lpVtbl -> ReportLogEventA(This,msgType,dwEvent,lpszStrings,ulLength)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSLeo600Logger_Initialize_Proxy( 
    IEMSLeo600Logger * This,
    /* [in] */ ULONG ulLutID,
    /* [in] */ WORD wProcessID);


void __RPC_STUB IEMSLeo600Logger_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSLeo600Logger_ReportLogEventW_Proxy( 
    IEMSLeo600Logger * This,
    /* [in] */ EMSLOGMSGTYPE msgType,
    /* [in] */ DWORD dwEvent,
    /* [size_is][in] */ const LPWSTR lpszStrings,
    /* [in] */ ULONG ulLength);


void __RPC_STUB IEMSLeo600Logger_ReportLogEventW_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSLeo600Logger_ReportLogEventA_Proxy( 
    IEMSLeo600Logger * This,
    /* [in] */ EMSLOGMSGTYPE msgType,
    /* [in] */ DWORD dwEvent,
    /* [size_is][in] */ const LPSTR lpszStrings,
    /* [in] */ ULONG ulLength);


void __RPC_STUB IEMSLeo600Logger_ReportLogEventA_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSLeo600Logger_INTERFACE_DEFINED__ */


#ifndef __IEMS600Logger_INTERFACE_DEFINED__
#define __IEMS600Logger_INTERFACE_DEFINED__

/* interface IEMS600Logger */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMS600Logger;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("50C0ED6D-39DE-4751-B0C1-CCAFA14AD41D")
    IEMS600Logger : public IEMSLeo600Logger
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetRaceSuppressionInterval( 
            /* [in] */ double dSeconds) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMS600LoggerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEMS600Logger * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEMS600Logger * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEMS600Logger * This);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IEMS600Logger * This,
            /* [in] */ ULONG ulLutID,
            /* [in] */ WORD wProcessID);
        
        HRESULT ( STDMETHODCALLTYPE *ReportLogEventW )( 
            IEMS600Logger * This,
            /* [in] */ EMSLOGMSGTYPE msgType,
            /* [in] */ DWORD dwEvent,
            /* [size_is][in] */ const LPWSTR lpszStrings,
            /* [in] */ ULONG ulLength);
        
        HRESULT ( STDMETHODCALLTYPE *ReportLogEventA )( 
            IEMS600Logger * This,
            /* [in] */ EMSLOGMSGTYPE msgType,
            /* [in] */ DWORD dwEvent,
            /* [size_is][in] */ const LPSTR lpszStrings,
            /* [in] */ ULONG ulLength);
        
        HRESULT ( STDMETHODCALLTYPE *SetRaceSuppressionInterval )( 
            IEMS600Logger * This,
            /* [in] */ double dSeconds);
        
        END_INTERFACE
    } IEMS600LoggerVtbl;

    interface IEMS600Logger
    {
        CONST_VTBL struct IEMS600LoggerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMS600Logger_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMS600Logger_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMS600Logger_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMS600Logger_Initialize(This,ulLutID,wProcessID)	\
    (This)->lpVtbl -> Initialize(This,ulLutID,wProcessID)

#define IEMS600Logger_ReportLogEventW(This,msgType,dwEvent,lpszStrings,ulLength)	\
    (This)->lpVtbl -> ReportLogEventW(This,msgType,dwEvent,lpszStrings,ulLength)

#define IEMS600Logger_ReportLogEventA(This,msgType,dwEvent,lpszStrings,ulLength)	\
    (This)->lpVtbl -> ReportLogEventA(This,msgType,dwEvent,lpszStrings,ulLength)


#define IEMS600Logger_SetRaceSuppressionInterval(This,dSeconds)	\
    (This)->lpVtbl -> SetRaceSuppressionInterval(This,dSeconds)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMS600Logger_SetRaceSuppressionInterval_Proxy( 
    IEMS600Logger * This,
    /* [in] */ double dSeconds);


void __RPC_STUB IEMS600Logger_SetRaceSuppressionInterval_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMS600Logger_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSLOGGR_0012 */
/* [local] */ 

 
//*** End of deprecated interfaces ***
 


extern RPC_IF_HANDLE __MIDL_itf_EMSLOGGR_0012_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSLOGGR_0012_v0_0_s_ifspec;

#ifndef __IEMS600LoggerEx_INTERFACE_DEFINED__
#define __IEMS600LoggerEx_INTERFACE_DEFINED__

/* interface IEMS600LoggerEx */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMS600LoggerEx;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A6C83E4F-B831-417d-8A9C-0FEF53C4182C")
    IEMS600LoggerEx : public IEMS600Logger
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ ULONG ulLutID,
            /* [in] */ WORD wProcessID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Report( 
            /* [in] */ const EMSLOGMSGTYPE msgType,
            /* [in] */ const DWORD dwEventStringID,
            /* [in] */ const WORD wParamCount,
            /* [size_is][string][in] */ const wchar_t **awszParams) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RaceSuppressionInterval( 
            /* [in] */ double dSeconds) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMS600LoggerExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEMS600LoggerEx * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEMS600LoggerEx * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEMS600LoggerEx * This);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IEMS600LoggerEx * This,
            /* [in] */ ULONG ulLutID,
            /* [in] */ WORD wProcessID);
        
        HRESULT ( STDMETHODCALLTYPE *ReportLogEventW )( 
            IEMS600LoggerEx * This,
            /* [in] */ EMSLOGMSGTYPE msgType,
            /* [in] */ DWORD dwEvent,
            /* [size_is][in] */ const LPWSTR lpszStrings,
            /* [in] */ ULONG ulLength);
        
        HRESULT ( STDMETHODCALLTYPE *ReportLogEventA )( 
            IEMS600LoggerEx * This,
            /* [in] */ EMSLOGMSGTYPE msgType,
            /* [in] */ DWORD dwEvent,
            /* [size_is][in] */ const LPSTR lpszStrings,
            /* [in] */ ULONG ulLength);
        
        HRESULT ( STDMETHODCALLTYPE *SetRaceSuppressionInterval )( 
            IEMS600LoggerEx * This,
            /* [in] */ double dSeconds);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            IEMS600LoggerEx * This,
            /* [in] */ ULONG ulLutID,
            /* [in] */ WORD wProcessID);
        
        HRESULT ( STDMETHODCALLTYPE *Report )( 
            IEMS600LoggerEx * This,
            /* [in] */ const EMSLOGMSGTYPE msgType,
            /* [in] */ const DWORD dwEventStringID,
            /* [in] */ const WORD wParamCount,
            /* [size_is][string][in] */ const wchar_t **awszParams);
        
        HRESULT ( STDMETHODCALLTYPE *RaceSuppressionInterval )( 
            IEMS600LoggerEx * This,
            /* [in] */ double dSeconds);
        
        END_INTERFACE
    } IEMS600LoggerExVtbl;

    interface IEMS600LoggerEx
    {
        CONST_VTBL struct IEMS600LoggerExVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMS600LoggerEx_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMS600LoggerEx_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMS600LoggerEx_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMS600LoggerEx_Initialize(This,ulLutID,wProcessID)	\
    (This)->lpVtbl -> Initialize(This,ulLutID,wProcessID)

#define IEMS600LoggerEx_ReportLogEventW(This,msgType,dwEvent,lpszStrings,ulLength)	\
    (This)->lpVtbl -> ReportLogEventW(This,msgType,dwEvent,lpszStrings,ulLength)

#define IEMS600LoggerEx_ReportLogEventA(This,msgType,dwEvent,lpszStrings,ulLength)	\
    (This)->lpVtbl -> ReportLogEventA(This,msgType,dwEvent,lpszStrings,ulLength)


#define IEMS600LoggerEx_SetRaceSuppressionInterval(This,dSeconds)	\
    (This)->lpVtbl -> SetRaceSuppressionInterval(This,dSeconds)


#define IEMS600LoggerEx_Init(This,ulLutID,wProcessID)	\
    (This)->lpVtbl -> Init(This,ulLutID,wProcessID)

#define IEMS600LoggerEx_Report(This,msgType,dwEventStringID,wParamCount,awszParams)	\
    (This)->lpVtbl -> Report(This,msgType,dwEventStringID,wParamCount,awszParams)

#define IEMS600LoggerEx_RaceSuppressionInterval(This,dSeconds)	\
    (This)->lpVtbl -> RaceSuppressionInterval(This,dSeconds)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMS600LoggerEx_Init_Proxy( 
    IEMS600LoggerEx * This,
    /* [in] */ ULONG ulLutID,
    /* [in] */ WORD wProcessID);


void __RPC_STUB IEMS600LoggerEx_Init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMS600LoggerEx_Report_Proxy( 
    IEMS600LoggerEx * This,
    /* [in] */ const EMSLOGMSGTYPE msgType,
    /* [in] */ const DWORD dwEventStringID,
    /* [in] */ const WORD wParamCount,
    /* [size_is][string][in] */ const wchar_t **awszParams);


void __RPC_STUB IEMS600LoggerEx_Report_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMS600LoggerEx_RaceSuppressionInterval_Proxy( 
    IEMS600LoggerEx * This,
    /* [in] */ double dSeconds);


void __RPC_STUB IEMS600LoggerEx_RaceSuppressionInterval_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMS600LoggerEx_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSLOGGR_0013 */
/* [local] */ 

typedef /* [unique] */ IEMS600LoggerEx *LPEMSLOGGER;

typedef /* [unique] */ IEMS600LoggerEx *LPEMS600LOGGER;



extern RPC_IF_HANDLE __MIDL_itf_EMSLOGGR_0013_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSLOGGR_0013_v0_0_s_ifspec;


#ifndef __EMSLEO600LOGGERLib_LIBRARY_DEFINED__
#define __EMSLEO600LOGGERLib_LIBRARY_DEFINED__

/* library EMSLEO600LOGGERLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_EMSLEO600LOGGERLib;

EXTERN_C const CLSID CLSID_EMSLeo600Logger;

#ifdef __cplusplus

class DECLSPEC_UUID("73FF4561-01F2-11d6-8D67-009027912866")
EMSLeo600Logger;
#endif
#endif /* __EMSLEO600LOGGERLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


