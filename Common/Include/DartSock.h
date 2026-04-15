/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Apr 09 14:17:49 2001
 */
/* Compiler settings for DartSock.idl:
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

#ifndef __DartSock_h__
#define __DartSock_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef ___ITcpEvents_FWD_DEFINED__
#define ___ITcpEvents_FWD_DEFINED__
typedef interface _ITcpEvents _ITcpEvents;
#endif 	/* ___ITcpEvents_FWD_DEFINED__ */


#ifndef __Tcp_FWD_DEFINED__
#define __Tcp_FWD_DEFINED__

#ifdef __cplusplus
typedef class Tcp Tcp;
#else
typedef struct Tcp Tcp;
#endif /* __cplusplus */

#endif 	/* __Tcp_FWD_DEFINED__ */


#ifndef __System_FWD_DEFINED__
#define __System_FWD_DEFINED__

#ifdef __cplusplus
typedef class System System;
#else
typedef struct System System;
#endif /* __cplusplus */

#endif 	/* __System_FWD_DEFINED__ */


#ifndef ___IDaemonEvents_FWD_DEFINED__
#define ___IDaemonEvents_FWD_DEFINED__
typedef interface _IDaemonEvents _IDaemonEvents;
#endif 	/* ___IDaemonEvents_FWD_DEFINED__ */


#ifndef __Daemon_FWD_DEFINED__
#define __Daemon_FWD_DEFINED__

#ifdef __cplusplus
typedef class Daemon Daemon;
#else
typedef struct Daemon Daemon;
#endif /* __cplusplus */

#endif 	/* __Daemon_FWD_DEFINED__ */


#ifndef ___IUdpEvents_FWD_DEFINED__
#define ___IUdpEvents_FWD_DEFINED__
typedef interface _IUdpEvents _IUdpEvents;
#endif 	/* ___IUdpEvents_FWD_DEFINED__ */


#ifndef __Udp_FWD_DEFINED__
#define __Udp_FWD_DEFINED__

#ifdef __cplusplus
typedef class Udp Udp;
#else
typedef struct Udp Udp;
#endif /* __cplusplus */

#endif 	/* __Udp_FWD_DEFINED__ */


#ifndef __DartStrings_FWD_DEFINED__
#define __DartStrings_FWD_DEFINED__

#ifdef __cplusplus
typedef class DartStrings DartStrings;
#else
typedef struct DartStrings DartStrings;
#endif /* __cplusplus */

#endif 	/* __DartStrings_FWD_DEFINED__ */


#ifndef __DartStream_FWD_DEFINED__
#define __DartStream_FWD_DEFINED__

#ifdef __cplusplus
typedef class DartStream DartStream;
#else
typedef struct DartStream DartStream;
#endif /* __cplusplus */

#endif 	/* __DartStream_FWD_DEFINED__ */


#ifndef __DartStreams_FWD_DEFINED__
#define __DartStreams_FWD_DEFINED__

#ifdef __cplusplus
typedef class DartStreams DartStreams;
#else
typedef struct DartStreams DartStreams;
#endif /* __cplusplus */

#endif 	/* __DartStreams_FWD_DEFINED__ */


#ifndef __IDartStrings_FWD_DEFINED__
#define __IDartStrings_FWD_DEFINED__
typedef interface IDartStrings IDartStrings;
#endif 	/* __IDartStrings_FWD_DEFINED__ */


#ifndef __ISystem_FWD_DEFINED__
#define __ISystem_FWD_DEFINED__
typedef interface ISystem ISystem;
#endif 	/* __ISystem_FWD_DEFINED__ */


#ifndef __ITcp_FWD_DEFINED__
#define __ITcp_FWD_DEFINED__
typedef interface ITcp ITcp;
#endif 	/* __ITcp_FWD_DEFINED__ */


#ifndef __IDaemon_FWD_DEFINED__
#define __IDaemon_FWD_DEFINED__
typedef interface IDaemon IDaemon;
#endif 	/* __IDaemon_FWD_DEFINED__ */


#ifndef __IUdp_FWD_DEFINED__
#define __IUdp_FWD_DEFINED__
typedef interface IUdp IUdp;
#endif 	/* __IUdp_FWD_DEFINED__ */


#ifndef __IDartStream_FWD_DEFINED__
#define __IDartStream_FWD_DEFINED__
typedef interface IDartStream IDartStream;
#endif 	/* __IDartStream_FWD_DEFINED__ */


#ifndef __IDartStreams_FWD_DEFINED__
#define __IDartStreams_FWD_DEFINED__
typedef interface IDartStreams IDartStreams;
#endif 	/* __IDartStreams_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 


#ifndef __DartSock_LIBRARY_DEFINED__
#define __DartSock_LIBRARY_DEFINED__

/* library DartSock */
/* [helpstring][helpcontext][helpfile][version][uuid] */ 

typedef /* [unique] */ IDartStream __RPC_FAR *LPDARTSTREAM;

typedef /* [unique] */ IDartStreams __RPC_FAR *LPDARTSTREAMS;

typedef /* [helpstring][helpcontext][uuid] */ 
enum StateConstants
    {	tcpClosed	= 0,
	tcpConnecting	= 1,
	tcpConnected	= 2,
	tcpClosing	= 3
    }	StateConstants;

typedef /* [helpcontext][helpstring][uuid] */ 
enum ProxyTypeConstants
    {	ptNone	= 0,
	ptSocks4	= 1,
	ptSocks5	= 2
    }	ProxyTypeConstants;

typedef /* [helpstring][helpcontext][uuid] */ 
enum DgProtocolConstants
    {	ptIcmp	= 1,
	ptIgmp	= 2,
	ptGgp	= 3,
	ptUdp	= 17,
	ptRaw	= 255
    }	DgProtocolConstants;

typedef /* [helpstring][helpcontext][uuid] */ 
enum ErrorConstants
    {	ptOk	= 0,
	ptNoAccess	= 10013,
	ptOptionNotSupported	= 10042,
	ptAddressInUse	= 10048,
	ptAddressNotAvailable	= 10049,
	ptNetworkDown	= 10050,
	ptNetworkUnreachable	= 10051,
	ptNetworkReset	= 10052,
	ptConnectionAborted	= 10053,
	ptConnectionReset	= 10054,
	ptNoBufferSpace	= 10055,
	ptNotConnected	= 10057,
	ptTimeout	= 10060,
	ptConnectionRefused	= 10061,
	ptHostUnreachable	= 10065,
	ptNotInitialized	= 10093,
	ptHostNotFound	= 11001,
	ptTryAgain	= 11002,
	ptNoRecovery	= 11003,
	ptNoData	= 11004,
	ptError	= 11100,
	ptProtocol	= 11101,
	ptFile	= 11102,
	ptAbort	= 11103,
	ptInvalidParam1	= 12001,
	ptInvalidParam2	= 12002,
	ptInvalidParam3	= 12003,
	ptInvalidParam4	= 12004,
	ptInvalidProperty	= 12009,
	ptBlocked	= 12011,
	ptAuthentication	= 12012,
	ptCompile	= 12013,
	ptConnected	= 12014,
	ptFormatError	= 12015,
	ptServerError	= 12016,
	ptNotFound	= 12017,
	ptNotImplemented	= 12018,
	ptOperationRefused	= 12019,
	ptNoCertificate	= 12020,
	ptInvalidMailAddress	= 12021,
	ptNoSecurity	= 12022,
	ptSocks4NoAcceptableMethods	= 12024,
	ptSocks5ServerFailure	= 12031,
	ptSocks5NoRuleSet	= 12032,
	ptSocks5NetworkUnreachable	= 12033,
	ptSocks5HostUnreachable	= 12034,
	ptSocks5ConnectionRefused	= 12035,
	ptSocks5TTLExpired	= 12036,
	ptSocks5CommandNotSupported	= 12037,
	ptSocks5AddressTypeNotSupported	= 12038,
	ptSocks5AuthFailed	= 12039,
	ptSocks4RequestRejected	= 12091,
	ptSocks4NoIdentd	= 12092,
	ptSocks4DifferentUserID	= 12093
    }	ErrorConstants;

typedef /* [helpcontext][helpstring][uuid] */ 
enum FileModeConstants
    {	createAlways	= 0,
	createExisting	= 1,
	createUnique	= 2,
	createOpen	= 3
    }	FileModeConstants;


EXTERN_C const IID LIBID_DartSock;

#ifndef ___ITcpEvents_DISPINTERFACE_DEFINED__
#define ___ITcpEvents_DISPINTERFACE_DEFINED__

/* dispinterface _ITcpEvents */
/* [helpcontext][helpstring][uuid] */ 


EXTERN_C const IID DIID__ITcpEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("0F1D12D5-FA60-11d1-AA98-0020AFFAEFB4")
    _ITcpEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _ITcpEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _ITcpEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _ITcpEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _ITcpEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _ITcpEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _ITcpEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _ITcpEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _ITcpEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _ITcpEventsVtbl;

    interface _ITcpEvents
    {
        CONST_VTBL struct _ITcpEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _ITcpEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _ITcpEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _ITcpEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _ITcpEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _ITcpEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _ITcpEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _ITcpEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___ITcpEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Tcp;

#ifdef __cplusplus

class DECLSPEC_UUID("CA4FC24B-C65C-11D1-AA6F-000000000000")
Tcp;
#endif

EXTERN_C const CLSID CLSID_System;

#ifdef __cplusplus

class DECLSPEC_UUID("DDD136CE-517B-11D2-AD03-00105A17B608")
System;
#endif

#ifndef ___IDaemonEvents_DISPINTERFACE_DEFINED__
#define ___IDaemonEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IDaemonEvents */
/* [helpcontext][helpstring][uuid] */ 


EXTERN_C const IID DIID__IDaemonEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("4F99A076-5227-11D2-AD06-00105A17B608")
    _IDaemonEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IDaemonEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IDaemonEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IDaemonEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IDaemonEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IDaemonEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IDaemonEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IDaemonEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IDaemonEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IDaemonEventsVtbl;

    interface _IDaemonEvents
    {
        CONST_VTBL struct _IDaemonEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IDaemonEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IDaemonEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IDaemonEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IDaemonEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IDaemonEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IDaemonEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IDaemonEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IDaemonEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Daemon;

#ifdef __cplusplus

class DECLSPEC_UUID("4F99A075-5227-11D2-AD06-00105A17B608")
Daemon;
#endif

#ifndef ___IUdpEvents_DISPINTERFACE_DEFINED__
#define ___IUdpEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IUdpEvents */
/* [helpcontext][helpstring][uuid] */ 


EXTERN_C const IID DIID__IUdpEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("371D0744-7A57-11D2-AD5A-00105A17B608")
    _IUdpEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IUdpEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IUdpEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IUdpEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IUdpEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IUdpEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IUdpEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IUdpEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IUdpEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IUdpEventsVtbl;

    interface _IUdpEvents
    {
        CONST_VTBL struct _IUdpEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IUdpEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IUdpEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IUdpEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IUdpEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IUdpEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IUdpEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IUdpEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IUdpEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Udp;

#ifdef __cplusplus

class DECLSPEC_UUID("371D0743-7A57-11D2-AD5A-00105A17B608")
Udp;
#endif

EXTERN_C const CLSID CLSID_DartStrings;

#ifdef __cplusplus

class DECLSPEC_UUID("E9D55102-9683-11D2-BA68-0040053687FE")
DartStrings;
#endif

EXTERN_C const CLSID CLSID_DartStream;

#ifdef __cplusplus

class DECLSPEC_UUID("0C1F87AE-AE62-11D3-911C-00105A17B608")
DartStream;
#endif

EXTERN_C const CLSID CLSID_DartStreams;

#ifdef __cplusplus

class DECLSPEC_UUID("B22FE43C-D1E8-432A-A862-9F83D5F04732")
DartStreams;
#endif
#endif /* __DartSock_LIBRARY_DEFINED__ */

#ifndef __IDartStrings_INTERFACE_DEFINED__
#define __IDartStrings_INTERFACE_DEFINED__

/* interface IDartStrings */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 

typedef /* [unique] */ IDartStrings __RPC_FAR *LPSTRINGS;


EXTERN_C const IID IID_IDartStrings;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E9D55101-9683-11D2-BA68-0040053687FE")
    IDartStrings : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Item( 
            VARIANT __RPC_FAR *Index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Item( 
            VARIANT __RPC_FAR *Index,
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Delimiter( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Delimiter( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_All( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [restricted][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Find( 
            BSTR SubString,
            /* [optional] */ VARIANT __RPC_FAR *StartAfter,
            /* [retval][out] */ BSTR __RPC_FAR *Value) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            VARIANT __RPC_FAR *Index,
            /* [retval][out] */ BSTR __RPC_FAR *Value) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Add( 
            BSTR Item,
            /* [optional] */ long Index) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDartStringsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDartStrings __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDartStrings __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDartStrings __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDartStrings __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDartStrings __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDartStrings __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDartStrings __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Item )( 
            IDartStrings __RPC_FAR * This,
            VARIANT __RPC_FAR *Index,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Item )( 
            IDartStrings __RPC_FAR * This,
            VARIANT __RPC_FAR *Index,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Delimiter )( 
            IDartStrings __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Delimiter )( 
            IDartStrings __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IDartStrings __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_All )( 
            IDartStrings __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [restricted][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IDartStrings __RPC_FAR * This,
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Find )( 
            IDartStrings __RPC_FAR * This,
            BSTR SubString,
            /* [optional] */ VARIANT __RPC_FAR *StartAfter,
            /* [retval][out] */ BSTR __RPC_FAR *Value);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clear )( 
            IDartStrings __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            IDartStrings __RPC_FAR * This,
            VARIANT __RPC_FAR *Index,
            /* [retval][out] */ BSTR __RPC_FAR *Value);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IDartStrings __RPC_FAR * This,
            BSTR Item,
            /* [optional] */ long Index);
        
        END_INTERFACE
    } IDartStringsVtbl;

    interface IDartStrings
    {
        CONST_VTBL struct IDartStringsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDartStrings_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDartStrings_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDartStrings_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDartStrings_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDartStrings_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDartStrings_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDartStrings_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDartStrings_get_Item(This,Index,pVal)	\
    (This)->lpVtbl -> get_Item(This,Index,pVal)

#define IDartStrings_put_Item(This,Index,newVal)	\
    (This)->lpVtbl -> put_Item(This,Index,newVal)

#define IDartStrings_get_Delimiter(This,pVal)	\
    (This)->lpVtbl -> get_Delimiter(This,pVal)

#define IDartStrings_put_Delimiter(This,newVal)	\
    (This)->lpVtbl -> put_Delimiter(This,newVal)

#define IDartStrings_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IDartStrings_get_All(This,pVal)	\
    (This)->lpVtbl -> get_All(This,pVal)

#define IDartStrings_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define IDartStrings_Find(This,SubString,StartAfter,Value)	\
    (This)->lpVtbl -> Find(This,SubString,StartAfter,Value)

#define IDartStrings_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define IDartStrings_Remove(This,Index,Value)	\
    (This)->lpVtbl -> Remove(This,Index,Value)

#define IDartStrings_Add(This,Item,Index)	\
    (This)->lpVtbl -> Add(This,Item,Index)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDartStrings_get_Item_Proxy( 
    IDartStrings __RPC_FAR * This,
    VARIANT __RPC_FAR *Index,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IDartStrings_get_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDartStrings_put_Item_Proxy( 
    IDartStrings __RPC_FAR * This,
    VARIANT __RPC_FAR *Index,
    /* [in] */ BSTR newVal);


void __RPC_STUB IDartStrings_put_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDartStrings_get_Delimiter_Proxy( 
    IDartStrings __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IDartStrings_get_Delimiter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDartStrings_put_Delimiter_Proxy( 
    IDartStrings __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IDartStrings_put_Delimiter_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDartStrings_get_Count_Proxy( 
    IDartStrings __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IDartStrings_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDartStrings_get_All_Proxy( 
    IDartStrings __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IDartStrings_get_All_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDartStrings_get__NewEnum_Proxy( 
    IDartStrings __RPC_FAR * This,
    /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);


void __RPC_STUB IDartStrings_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IDartStrings_Find_Proxy( 
    IDartStrings __RPC_FAR * This,
    BSTR SubString,
    /* [optional] */ VARIANT __RPC_FAR *StartAfter,
    /* [retval][out] */ BSTR __RPC_FAR *Value);


void __RPC_STUB IDartStrings_Find_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IDartStrings_Clear_Proxy( 
    IDartStrings __RPC_FAR * This);


void __RPC_STUB IDartStrings_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IDartStrings_Remove_Proxy( 
    IDartStrings __RPC_FAR * This,
    VARIANT __RPC_FAR *Index,
    /* [retval][out] */ BSTR __RPC_FAR *Value);


void __RPC_STUB IDartStrings_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IDartStrings_Add_Proxy( 
    IDartStrings __RPC_FAR * This,
    BSTR Item,
    /* [optional] */ long Index);


void __RPC_STUB IDartStrings_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDartStrings_INTERFACE_DEFINED__ */


#ifndef __ISystem_INTERFACE_DEFINED__
#define __ISystem_INTERFACE_DEFINED__

/* interface ISystem */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 

typedef /* [unique] */ ISystem __RPC_FAR *LPSYSTEM;


EXTERN_C const IID IID_ISystem;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DDD136CD-517B-11D2-AD03-00105A17B608")
    ISystem : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Addresses( 
            /* [retval][out] */ LPSTRINGS __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MajorVersion( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MinorVersion( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Status( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISystemVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISystem __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISystem __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISystem __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ISystem __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ISystem __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ISystem __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ISystem __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Description )( 
            ISystem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Addresses )( 
            ISystem __RPC_FAR * This,
            /* [retval][out] */ LPSTRINGS __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            ISystem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MajorVersion )( 
            ISystem __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MinorVersion )( 
            ISystem __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Status )( 
            ISystem __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        END_INTERFACE
    } ISystemVtbl;

    interface ISystem
    {
        CONST_VTBL struct ISystemVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISystem_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISystem_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISystem_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISystem_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ISystem_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ISystem_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ISystem_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ISystem_get_Description(This,pVal)	\
    (This)->lpVtbl -> get_Description(This,pVal)

#define ISystem_get_Addresses(This,pVal)	\
    (This)->lpVtbl -> get_Addresses(This,pVal)

#define ISystem_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define ISystem_get_MajorVersion(This,pVal)	\
    (This)->lpVtbl -> get_MajorVersion(This,pVal)

#define ISystem_get_MinorVersion(This,pVal)	\
    (This)->lpVtbl -> get_MinorVersion(This,pVal)

#define ISystem_get_Status(This,pVal)	\
    (This)->lpVtbl -> get_Status(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISystem_get_Description_Proxy( 
    ISystem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ISystem_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISystem_get_Addresses_Proxy( 
    ISystem __RPC_FAR * This,
    /* [retval][out] */ LPSTRINGS __RPC_FAR *pVal);


void __RPC_STUB ISystem_get_Addresses_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISystem_get_Name_Proxy( 
    ISystem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ISystem_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISystem_get_MajorVersion_Proxy( 
    ISystem __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB ISystem_get_MajorVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISystem_get_MinorVersion_Proxy( 
    ISystem __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB ISystem_get_MinorVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ISystem_get_Status_Proxy( 
    ISystem __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ISystem_get_Status_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISystem_INTERFACE_DEFINED__ */


#ifndef __ITcp_INTERFACE_DEFINED__
#define __ITcp_INTERFACE_DEFINED__

/* interface ITcp */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ITcp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1D8A335E-C678-11D1-AA6F-000000000000")
    ITcp : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Ref( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Ref( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ReuseAddress( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ReuseAddress( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_NoDelay( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_NoDelay( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_KeepAlive( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_KeepAlive( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Timeout( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Timeout( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ReceiveBufferSize( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ReceiveBufferSize( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SendBufferSize( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_SendBufferSize( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Socket( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Socket( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Blocked( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RemoteAddress( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RemotePort( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LocalAddress( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LocalPort( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ReceiveBufferCount( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SendBufferCount( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_State( 
            /* [retval][out] */ StateConstants __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Connect( 
            BSTR RemoteName,
            long RemotePort,
            /* [optional] */ BSTR LocalName,
            /* [optional] */ long LocalPort) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Send( 
            VARIANT __RPC_FAR *Data,
            /* [optional] */ long LimitCount,
            /* [optional] */ VARIANT_BOOL Urgent,
            /* [retval][out] */ long __RPC_FAR *Count) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Receive( 
            VARIANT __RPC_FAR *Data,
            /* [retval][out] */ long __RPC_FAR *Count) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Fill( 
            VARIANT __RPC_FAR *Data,
            /* [retval][out] */ long __RPC_FAR *Count) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Search( 
            VARIANT __RPC_FAR *Data,
            VARIANT __RPC_FAR *Token,
            /* [retval][out] */ long __RPC_FAR *Count) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Abort( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Trace( 
            /* [optional][out][in] */ VARIANT __RPC_FAR *Result,
            /* [optional] */ VARIANT_BOOL Send,
            /* [optional] */ VARIANT_BOOL Receive,
            /* [optional] */ BSTR SendPrompt,
            /* [optional] */ BSTR ReceivePrompt) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE About( void) = 0;
        
        virtual /* [hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_hWnd( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProxyType( 
            /* [retval][out] */ ProxyTypeConstants __RPC_FAR *pVal) = 0;
        
        virtual /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProxyType( 
            /* [in] */ ProxyTypeConstants newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProxyHost( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProxyHost( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProxyUsername( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProxyUsername( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProxyPassword( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProxyPassword( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProxyPort( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProxyPort( 
            /* [in] */ long newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ITcpVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ITcp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ITcp __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ITcp __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            ITcp __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            ITcp __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            ITcp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            ITcp __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Ref )( 
            ITcp __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Ref )( 
            ITcp __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReuseAddress )( 
            ITcp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ReuseAddress )( 
            ITcp __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_NoDelay )( 
            ITcp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_NoDelay )( 
            ITcp __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_KeepAlive )( 
            ITcp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_KeepAlive )( 
            ITcp __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Timeout )( 
            ITcp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Timeout )( 
            ITcp __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReceiveBufferSize )( 
            ITcp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ReceiveBufferSize )( 
            ITcp __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SendBufferSize )( 
            ITcp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_SendBufferSize )( 
            ITcp __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Socket )( 
            ITcp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Socket )( 
            ITcp __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Blocked )( 
            ITcp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RemoteAddress )( 
            ITcp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RemotePort )( 
            ITcp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocalAddress )( 
            ITcp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocalPort )( 
            ITcp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReceiveBufferCount )( 
            ITcp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SendBufferCount )( 
            ITcp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_State )( 
            ITcp __RPC_FAR * This,
            /* [retval][out] */ StateConstants __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Connect )( 
            ITcp __RPC_FAR * This,
            BSTR RemoteName,
            long RemotePort,
            /* [optional] */ BSTR LocalName,
            /* [optional] */ long LocalPort);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Send )( 
            ITcp __RPC_FAR * This,
            VARIANT __RPC_FAR *Data,
            /* [optional] */ long LimitCount,
            /* [optional] */ VARIANT_BOOL Urgent,
            /* [retval][out] */ long __RPC_FAR *Count);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Receive )( 
            ITcp __RPC_FAR * This,
            VARIANT __RPC_FAR *Data,
            /* [retval][out] */ long __RPC_FAR *Count);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Fill )( 
            ITcp __RPC_FAR * This,
            VARIANT __RPC_FAR *Data,
            /* [retval][out] */ long __RPC_FAR *Count);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Search )( 
            ITcp __RPC_FAR * This,
            VARIANT __RPC_FAR *Data,
            VARIANT __RPC_FAR *Token,
            /* [retval][out] */ long __RPC_FAR *Count);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            ITcp __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Abort )( 
            ITcp __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Trace )( 
            ITcp __RPC_FAR * This,
            /* [optional][out][in] */ VARIANT __RPC_FAR *Result,
            /* [optional] */ VARIANT_BOOL Send,
            /* [optional] */ VARIANT_BOOL Receive,
            /* [optional] */ BSTR SendPrompt,
            /* [optional] */ BSTR ReceivePrompt);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *About )( 
            ITcp __RPC_FAR * This);
        
        /* [hidden][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_hWnd )( 
            ITcp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProxyType )( 
            ITcp __RPC_FAR * This,
            /* [retval][out] */ ProxyTypeConstants __RPC_FAR *pVal);
        
        /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProxyType )( 
            ITcp __RPC_FAR * This,
            /* [in] */ ProxyTypeConstants newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProxyHost )( 
            ITcp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProxyHost )( 
            ITcp __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProxyUsername )( 
            ITcp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProxyUsername )( 
            ITcp __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProxyPassword )( 
            ITcp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProxyPassword )( 
            ITcp __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProxyPort )( 
            ITcp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProxyPort )( 
            ITcp __RPC_FAR * This,
            /* [in] */ long newVal);
        
        END_INTERFACE
    } ITcpVtbl;

    interface ITcp
    {
        CONST_VTBL struct ITcpVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ITcp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ITcp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ITcp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ITcp_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define ITcp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define ITcp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define ITcp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define ITcp_get_Ref(This,pVal)	\
    (This)->lpVtbl -> get_Ref(This,pVal)

#define ITcp_put_Ref(This,newVal)	\
    (This)->lpVtbl -> put_Ref(This,newVal)

#define ITcp_get_ReuseAddress(This,pVal)	\
    (This)->lpVtbl -> get_ReuseAddress(This,pVal)

#define ITcp_put_ReuseAddress(This,newVal)	\
    (This)->lpVtbl -> put_ReuseAddress(This,newVal)

#define ITcp_get_NoDelay(This,pVal)	\
    (This)->lpVtbl -> get_NoDelay(This,pVal)

#define ITcp_put_NoDelay(This,newVal)	\
    (This)->lpVtbl -> put_NoDelay(This,newVal)

#define ITcp_get_KeepAlive(This,pVal)	\
    (This)->lpVtbl -> get_KeepAlive(This,pVal)

#define ITcp_put_KeepAlive(This,newVal)	\
    (This)->lpVtbl -> put_KeepAlive(This,newVal)

#define ITcp_get_Timeout(This,pVal)	\
    (This)->lpVtbl -> get_Timeout(This,pVal)

#define ITcp_put_Timeout(This,newVal)	\
    (This)->lpVtbl -> put_Timeout(This,newVal)

#define ITcp_get_ReceiveBufferSize(This,pVal)	\
    (This)->lpVtbl -> get_ReceiveBufferSize(This,pVal)

#define ITcp_put_ReceiveBufferSize(This,newVal)	\
    (This)->lpVtbl -> put_ReceiveBufferSize(This,newVal)

#define ITcp_get_SendBufferSize(This,pVal)	\
    (This)->lpVtbl -> get_SendBufferSize(This,pVal)

#define ITcp_put_SendBufferSize(This,newVal)	\
    (This)->lpVtbl -> put_SendBufferSize(This,newVal)

#define ITcp_get_Socket(This,pVal)	\
    (This)->lpVtbl -> get_Socket(This,pVal)

#define ITcp_put_Socket(This,newVal)	\
    (This)->lpVtbl -> put_Socket(This,newVal)

#define ITcp_get_Blocked(This,pVal)	\
    (This)->lpVtbl -> get_Blocked(This,pVal)

#define ITcp_get_RemoteAddress(This,pVal)	\
    (This)->lpVtbl -> get_RemoteAddress(This,pVal)

#define ITcp_get_RemotePort(This,pVal)	\
    (This)->lpVtbl -> get_RemotePort(This,pVal)

#define ITcp_get_LocalAddress(This,pVal)	\
    (This)->lpVtbl -> get_LocalAddress(This,pVal)

#define ITcp_get_LocalPort(This,pVal)	\
    (This)->lpVtbl -> get_LocalPort(This,pVal)

#define ITcp_get_ReceiveBufferCount(This,pVal)	\
    (This)->lpVtbl -> get_ReceiveBufferCount(This,pVal)

#define ITcp_get_SendBufferCount(This,pVal)	\
    (This)->lpVtbl -> get_SendBufferCount(This,pVal)

#define ITcp_get_State(This,pVal)	\
    (This)->lpVtbl -> get_State(This,pVal)

#define ITcp_Connect(This,RemoteName,RemotePort,LocalName,LocalPort)	\
    (This)->lpVtbl -> Connect(This,RemoteName,RemotePort,LocalName,LocalPort)

#define ITcp_Send(This,Data,LimitCount,Urgent,Count)	\
    (This)->lpVtbl -> Send(This,Data,LimitCount,Urgent,Count)

#define ITcp_Receive(This,Data,Count)	\
    (This)->lpVtbl -> Receive(This,Data,Count)

#define ITcp_Fill(This,Data,Count)	\
    (This)->lpVtbl -> Fill(This,Data,Count)

#define ITcp_Search(This,Data,Token,Count)	\
    (This)->lpVtbl -> Search(This,Data,Token,Count)

#define ITcp_Close(This)	\
    (This)->lpVtbl -> Close(This)

#define ITcp_Abort(This)	\
    (This)->lpVtbl -> Abort(This)

#define ITcp_Trace(This,Result,Send,Receive,SendPrompt,ReceivePrompt)	\
    (This)->lpVtbl -> Trace(This,Result,Send,Receive,SendPrompt,ReceivePrompt)

#define ITcp_About(This)	\
    (This)->lpVtbl -> About(This)

#define ITcp_get_hWnd(This,pVal)	\
    (This)->lpVtbl -> get_hWnd(This,pVal)

#define ITcp_get_ProxyType(This,pVal)	\
    (This)->lpVtbl -> get_ProxyType(This,pVal)

#define ITcp_put_ProxyType(This,newVal)	\
    (This)->lpVtbl -> put_ProxyType(This,newVal)

#define ITcp_get_ProxyHost(This,pVal)	\
    (This)->lpVtbl -> get_ProxyHost(This,pVal)

#define ITcp_put_ProxyHost(This,newVal)	\
    (This)->lpVtbl -> put_ProxyHost(This,newVal)

#define ITcp_get_ProxyUsername(This,pVal)	\
    (This)->lpVtbl -> get_ProxyUsername(This,pVal)

#define ITcp_put_ProxyUsername(This,newVal)	\
    (This)->lpVtbl -> put_ProxyUsername(This,newVal)

#define ITcp_get_ProxyPassword(This,pVal)	\
    (This)->lpVtbl -> get_ProxyPassword(This,pVal)

#define ITcp_put_ProxyPassword(This,newVal)	\
    (This)->lpVtbl -> put_ProxyPassword(This,newVal)

#define ITcp_get_ProxyPort(This,pVal)	\
    (This)->lpVtbl -> get_ProxyPort(This,pVal)

#define ITcp_put_ProxyPort(This,newVal)	\
    (This)->lpVtbl -> put_ProxyPort(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITcp_get_Ref_Proxy( 
    ITcp __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB ITcp_get_Ref_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITcp_put_Ref_Proxy( 
    ITcp __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB ITcp_put_Ref_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITcp_get_ReuseAddress_Proxy( 
    ITcp __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB ITcp_get_ReuseAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITcp_put_ReuseAddress_Proxy( 
    ITcp __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB ITcp_put_ReuseAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITcp_get_NoDelay_Proxy( 
    ITcp __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB ITcp_get_NoDelay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITcp_put_NoDelay_Proxy( 
    ITcp __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB ITcp_put_NoDelay_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITcp_get_KeepAlive_Proxy( 
    ITcp __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB ITcp_get_KeepAlive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITcp_put_KeepAlive_Proxy( 
    ITcp __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB ITcp_put_KeepAlive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITcp_get_Timeout_Proxy( 
    ITcp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITcp_get_Timeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITcp_put_Timeout_Proxy( 
    ITcp __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ITcp_put_Timeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITcp_get_ReceiveBufferSize_Proxy( 
    ITcp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITcp_get_ReceiveBufferSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITcp_put_ReceiveBufferSize_Proxy( 
    ITcp __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ITcp_put_ReceiveBufferSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITcp_get_SendBufferSize_Proxy( 
    ITcp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITcp_get_SendBufferSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITcp_put_SendBufferSize_Proxy( 
    ITcp __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ITcp_put_SendBufferSize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITcp_get_Socket_Proxy( 
    ITcp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITcp_get_Socket_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITcp_put_Socket_Proxy( 
    ITcp __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ITcp_put_Socket_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITcp_get_Blocked_Proxy( 
    ITcp __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB ITcp_get_Blocked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITcp_get_RemoteAddress_Proxy( 
    ITcp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITcp_get_RemoteAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITcp_get_RemotePort_Proxy( 
    ITcp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITcp_get_RemotePort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITcp_get_LocalAddress_Proxy( 
    ITcp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITcp_get_LocalAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITcp_get_LocalPort_Proxy( 
    ITcp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITcp_get_LocalPort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITcp_get_ReceiveBufferCount_Proxy( 
    ITcp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITcp_get_ReceiveBufferCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITcp_get_SendBufferCount_Proxy( 
    ITcp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITcp_get_SendBufferCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITcp_get_State_Proxy( 
    ITcp __RPC_FAR * This,
    /* [retval][out] */ StateConstants __RPC_FAR *pVal);


void __RPC_STUB ITcp_get_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITcp_Connect_Proxy( 
    ITcp __RPC_FAR * This,
    BSTR RemoteName,
    long RemotePort,
    /* [optional] */ BSTR LocalName,
    /* [optional] */ long LocalPort);


void __RPC_STUB ITcp_Connect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITcp_Send_Proxy( 
    ITcp __RPC_FAR * This,
    VARIANT __RPC_FAR *Data,
    /* [optional] */ long LimitCount,
    /* [optional] */ VARIANT_BOOL Urgent,
    /* [retval][out] */ long __RPC_FAR *Count);


void __RPC_STUB ITcp_Send_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITcp_Receive_Proxy( 
    ITcp __RPC_FAR * This,
    VARIANT __RPC_FAR *Data,
    /* [retval][out] */ long __RPC_FAR *Count);


void __RPC_STUB ITcp_Receive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITcp_Fill_Proxy( 
    ITcp __RPC_FAR * This,
    VARIANT __RPC_FAR *Data,
    /* [retval][out] */ long __RPC_FAR *Count);


void __RPC_STUB ITcp_Fill_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITcp_Search_Proxy( 
    ITcp __RPC_FAR * This,
    VARIANT __RPC_FAR *Data,
    VARIANT __RPC_FAR *Token,
    /* [retval][out] */ long __RPC_FAR *Count);


void __RPC_STUB ITcp_Search_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITcp_Close_Proxy( 
    ITcp __RPC_FAR * This);


void __RPC_STUB ITcp_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITcp_Abort_Proxy( 
    ITcp __RPC_FAR * This);


void __RPC_STUB ITcp_Abort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITcp_Trace_Proxy( 
    ITcp __RPC_FAR * This,
    /* [optional][out][in] */ VARIANT __RPC_FAR *Result,
    /* [optional] */ VARIANT_BOOL Send,
    /* [optional] */ VARIANT_BOOL Receive,
    /* [optional] */ BSTR SendPrompt,
    /* [optional] */ BSTR ReceivePrompt);


void __RPC_STUB ITcp_Trace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ITcp_About_Proxy( 
    ITcp __RPC_FAR * This);


void __RPC_STUB ITcp_About_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [hidden][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITcp_get_hWnd_Proxy( 
    ITcp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITcp_get_hWnd_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITcp_get_ProxyType_Proxy( 
    ITcp __RPC_FAR * This,
    /* [retval][out] */ ProxyTypeConstants __RPC_FAR *pVal);


void __RPC_STUB ITcp_get_ProxyType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITcp_put_ProxyType_Proxy( 
    ITcp __RPC_FAR * This,
    /* [in] */ ProxyTypeConstants newVal);


void __RPC_STUB ITcp_put_ProxyType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITcp_get_ProxyHost_Proxy( 
    ITcp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITcp_get_ProxyHost_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITcp_put_ProxyHost_Proxy( 
    ITcp __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITcp_put_ProxyHost_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITcp_get_ProxyUsername_Proxy( 
    ITcp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITcp_get_ProxyUsername_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITcp_put_ProxyUsername_Proxy( 
    ITcp __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITcp_put_ProxyUsername_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITcp_get_ProxyPassword_Proxy( 
    ITcp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB ITcp_get_ProxyPassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITcp_put_ProxyPassword_Proxy( 
    ITcp __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ITcp_put_ProxyPassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE ITcp_get_ProxyPort_Proxy( 
    ITcp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB ITcp_get_ProxyPort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE ITcp_put_ProxyPort_Proxy( 
    ITcp __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB ITcp_put_ProxyPort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ITcp_INTERFACE_DEFINED__ */


#ifndef __IDaemon_INTERFACE_DEFINED__
#define __IDaemon_INTERFACE_DEFINED__

/* interface IDaemon */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IDaemon;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4F99A074-5227-11D2-AD06-00105A17B608")
    IDaemon : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LocalAddress( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LocalPort( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ReuseAddress( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ReuseAddress( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Timeout( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Timeout( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE About( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Listen( 
            long LocalPort,
            /* [optional] */ BSTR LocalAddress,
            /* [optional] */ long Backlog) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Accept( 
            /* [retval][out] */ long __RPC_FAR *SocketOut) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDaemonVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDaemon __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDaemon __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDaemon __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDaemon __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDaemon __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDaemon __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDaemon __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocalAddress )( 
            IDaemon __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocalPort )( 
            IDaemon __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ReuseAddress )( 
            IDaemon __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ReuseAddress )( 
            IDaemon __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Timeout )( 
            IDaemon __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Timeout )( 
            IDaemon __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *About )( 
            IDaemon __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Listen )( 
            IDaemon __RPC_FAR * This,
            long LocalPort,
            /* [optional] */ BSTR LocalAddress,
            /* [optional] */ long Backlog);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            IDaemon __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Accept )( 
            IDaemon __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *SocketOut);
        
        END_INTERFACE
    } IDaemonVtbl;

    interface IDaemon
    {
        CONST_VTBL struct IDaemonVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDaemon_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDaemon_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDaemon_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDaemon_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDaemon_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDaemon_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDaemon_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDaemon_get_LocalAddress(This,pVal)	\
    (This)->lpVtbl -> get_LocalAddress(This,pVal)

#define IDaemon_get_LocalPort(This,pVal)	\
    (This)->lpVtbl -> get_LocalPort(This,pVal)

#define IDaemon_get_ReuseAddress(This,pVal)	\
    (This)->lpVtbl -> get_ReuseAddress(This,pVal)

#define IDaemon_put_ReuseAddress(This,newVal)	\
    (This)->lpVtbl -> put_ReuseAddress(This,newVal)

#define IDaemon_get_Timeout(This,pVal)	\
    (This)->lpVtbl -> get_Timeout(This,pVal)

#define IDaemon_put_Timeout(This,newVal)	\
    (This)->lpVtbl -> put_Timeout(This,newVal)

#define IDaemon_About(This)	\
    (This)->lpVtbl -> About(This)

#define IDaemon_Listen(This,LocalPort,LocalAddress,Backlog)	\
    (This)->lpVtbl -> Listen(This,LocalPort,LocalAddress,Backlog)

#define IDaemon_Close(This)	\
    (This)->lpVtbl -> Close(This)

#define IDaemon_Accept(This,SocketOut)	\
    (This)->lpVtbl -> Accept(This,SocketOut)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDaemon_get_LocalAddress_Proxy( 
    IDaemon __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IDaemon_get_LocalAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDaemon_get_LocalPort_Proxy( 
    IDaemon __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IDaemon_get_LocalPort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDaemon_get_ReuseAddress_Proxy( 
    IDaemon __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IDaemon_get_ReuseAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDaemon_put_ReuseAddress_Proxy( 
    IDaemon __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IDaemon_put_ReuseAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDaemon_get_Timeout_Proxy( 
    IDaemon __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IDaemon_get_Timeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IDaemon_put_Timeout_Proxy( 
    IDaemon __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IDaemon_put_Timeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IDaemon_About_Proxy( 
    IDaemon __RPC_FAR * This);


void __RPC_STUB IDaemon_About_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IDaemon_Listen_Proxy( 
    IDaemon __RPC_FAR * This,
    long LocalPort,
    /* [optional] */ BSTR LocalAddress,
    /* [optional] */ long Backlog);


void __RPC_STUB IDaemon_Listen_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IDaemon_Close_Proxy( 
    IDaemon __RPC_FAR * This);


void __RPC_STUB IDaemon_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IDaemon_Accept_Proxy( 
    IDaemon __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *SocketOut);


void __RPC_STUB IDaemon_Accept_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDaemon_INTERFACE_DEFINED__ */


#ifndef __IUdp_INTERFACE_DEFINED__
#define __IUdp_INTERFACE_DEFINED__

/* interface IUdp */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IUdp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("371D0742-7A57-11D2-AD5A-00105A17B608")
    IUdp : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Timeout( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Timeout( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Protocol( 
            /* [retval][out] */ DgProtocolConstants __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Protocol( 
            /* [in] */ DgProtocolConstants newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_UserHeaders( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_UserHeaders( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Blocked( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LocalAddress( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LocalPort( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_SendDatagramCount( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Open( 
            /* [optional][in] */ long LocalPort,
            /* [optional][in] */ BSTR LocalName) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Receive( 
            VARIANT __RPC_FAR *Data,
            /* [optional] */ VARIANT __RPC_FAR *RemoteAddress,
            /* [optional] */ VARIANT __RPC_FAR *RemotePort,
            /* [retval][out] */ long __RPC_FAR *Count) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Send( 
            VARIANT __RPC_FAR *Data,
            BSTR RemoteName,
            /* [optional] */ long RemotePort,
            /* [optional] */ long LimitCount,
            /* [optional] */ VARIANT_BOOL DontRoute,
            /* [retval][out] */ long __RPC_FAR *Count) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Abort( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE About( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Join( 
            /* [in] */ BSTR Group) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DontEcho( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DontEcho( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_MaxSubnets( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_MaxSubnets( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Trace( 
            /* [optional][out][in] */ VARIANT __RPC_FAR *Result,
            /* [optional] */ VARIANT_BOOL Send,
            /* [optional] */ VARIANT_BOOL Receive,
            /* [optional] */ BSTR SendPrompt,
            /* [optional] */ BSTR ReceivePrompt) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IUdpVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IUdp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IUdp __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IUdp __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IUdp __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IUdp __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IUdp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IUdp __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Timeout )( 
            IUdp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Timeout )( 
            IUdp __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Protocol )( 
            IUdp __RPC_FAR * This,
            /* [retval][out] */ DgProtocolConstants __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Protocol )( 
            IUdp __RPC_FAR * This,
            /* [in] */ DgProtocolConstants newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UserHeaders )( 
            IUdp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_UserHeaders )( 
            IUdp __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Blocked )( 
            IUdp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocalAddress )( 
            IUdp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocalPort )( 
            IUdp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_SendDatagramCount )( 
            IUdp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Close )( 
            IUdp __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Open )( 
            IUdp __RPC_FAR * This,
            /* [optional][in] */ long LocalPort,
            /* [optional][in] */ BSTR LocalName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Receive )( 
            IUdp __RPC_FAR * This,
            VARIANT __RPC_FAR *Data,
            /* [optional] */ VARIANT __RPC_FAR *RemoteAddress,
            /* [optional] */ VARIANT __RPC_FAR *RemotePort,
            /* [retval][out] */ long __RPC_FAR *Count);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Send )( 
            IUdp __RPC_FAR * This,
            VARIANT __RPC_FAR *Data,
            BSTR RemoteName,
            /* [optional] */ long RemotePort,
            /* [optional] */ long LimitCount,
            /* [optional] */ VARIANT_BOOL DontRoute,
            /* [retval][out] */ long __RPC_FAR *Count);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Abort )( 
            IUdp __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *About )( 
            IUdp __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Join )( 
            IUdp __RPC_FAR * This,
            /* [in] */ BSTR Group);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DontEcho )( 
            IUdp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DontEcho )( 
            IUdp __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MaxSubnets )( 
            IUdp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MaxSubnets )( 
            IUdp __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Trace )( 
            IUdp __RPC_FAR * This,
            /* [optional][out][in] */ VARIANT __RPC_FAR *Result,
            /* [optional] */ VARIANT_BOOL Send,
            /* [optional] */ VARIANT_BOOL Receive,
            /* [optional] */ BSTR SendPrompt,
            /* [optional] */ BSTR ReceivePrompt);
        
        END_INTERFACE
    } IUdpVtbl;

    interface IUdp
    {
        CONST_VTBL struct IUdpVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IUdp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IUdp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IUdp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IUdp_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IUdp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IUdp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IUdp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IUdp_get_Timeout(This,pVal)	\
    (This)->lpVtbl -> get_Timeout(This,pVal)

#define IUdp_put_Timeout(This,newVal)	\
    (This)->lpVtbl -> put_Timeout(This,newVal)

#define IUdp_get_Protocol(This,pVal)	\
    (This)->lpVtbl -> get_Protocol(This,pVal)

#define IUdp_put_Protocol(This,newVal)	\
    (This)->lpVtbl -> put_Protocol(This,newVal)

#define IUdp_get_UserHeaders(This,pVal)	\
    (This)->lpVtbl -> get_UserHeaders(This,pVal)

#define IUdp_put_UserHeaders(This,newVal)	\
    (This)->lpVtbl -> put_UserHeaders(This,newVal)

#define IUdp_get_Blocked(This,pVal)	\
    (This)->lpVtbl -> get_Blocked(This,pVal)

#define IUdp_get_LocalAddress(This,pVal)	\
    (This)->lpVtbl -> get_LocalAddress(This,pVal)

#define IUdp_get_LocalPort(This,pVal)	\
    (This)->lpVtbl -> get_LocalPort(This,pVal)

#define IUdp_get_SendDatagramCount(This,pVal)	\
    (This)->lpVtbl -> get_SendDatagramCount(This,pVal)

#define IUdp_Close(This)	\
    (This)->lpVtbl -> Close(This)

#define IUdp_Open(This,LocalPort,LocalName)	\
    (This)->lpVtbl -> Open(This,LocalPort,LocalName)

#define IUdp_Receive(This,Data,RemoteAddress,RemotePort,Count)	\
    (This)->lpVtbl -> Receive(This,Data,RemoteAddress,RemotePort,Count)

#define IUdp_Send(This,Data,RemoteName,RemotePort,LimitCount,DontRoute,Count)	\
    (This)->lpVtbl -> Send(This,Data,RemoteName,RemotePort,LimitCount,DontRoute,Count)

#define IUdp_Abort(This)	\
    (This)->lpVtbl -> Abort(This)

#define IUdp_About(This)	\
    (This)->lpVtbl -> About(This)

#define IUdp_Join(This,Group)	\
    (This)->lpVtbl -> Join(This,Group)

#define IUdp_get_DontEcho(This,pVal)	\
    (This)->lpVtbl -> get_DontEcho(This,pVal)

#define IUdp_put_DontEcho(This,newVal)	\
    (This)->lpVtbl -> put_DontEcho(This,newVal)

#define IUdp_get_MaxSubnets(This,pVal)	\
    (This)->lpVtbl -> get_MaxSubnets(This,pVal)

#define IUdp_put_MaxSubnets(This,newVal)	\
    (This)->lpVtbl -> put_MaxSubnets(This,newVal)

#define IUdp_Trace(This,Result,Send,Receive,SendPrompt,ReceivePrompt)	\
    (This)->lpVtbl -> Trace(This,Result,Send,Receive,SendPrompt,ReceivePrompt)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUdp_get_Timeout_Proxy( 
    IUdp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IUdp_get_Timeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUdp_put_Timeout_Proxy( 
    IUdp __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IUdp_put_Timeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUdp_get_Protocol_Proxy( 
    IUdp __RPC_FAR * This,
    /* [retval][out] */ DgProtocolConstants __RPC_FAR *pVal);


void __RPC_STUB IUdp_get_Protocol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUdp_put_Protocol_Proxy( 
    IUdp __RPC_FAR * This,
    /* [in] */ DgProtocolConstants newVal);


void __RPC_STUB IUdp_put_Protocol_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUdp_get_UserHeaders_Proxy( 
    IUdp __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IUdp_get_UserHeaders_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUdp_put_UserHeaders_Proxy( 
    IUdp __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IUdp_put_UserHeaders_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUdp_get_Blocked_Proxy( 
    IUdp __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IUdp_get_Blocked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUdp_get_LocalAddress_Proxy( 
    IUdp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IUdp_get_LocalAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUdp_get_LocalPort_Proxy( 
    IUdp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IUdp_get_LocalPort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUdp_get_SendDatagramCount_Proxy( 
    IUdp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IUdp_get_SendDatagramCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IUdp_Close_Proxy( 
    IUdp __RPC_FAR * This);


void __RPC_STUB IUdp_Close_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IUdp_Open_Proxy( 
    IUdp __RPC_FAR * This,
    /* [optional][in] */ long LocalPort,
    /* [optional][in] */ BSTR LocalName);


void __RPC_STUB IUdp_Open_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IUdp_Receive_Proxy( 
    IUdp __RPC_FAR * This,
    VARIANT __RPC_FAR *Data,
    /* [optional] */ VARIANT __RPC_FAR *RemoteAddress,
    /* [optional] */ VARIANT __RPC_FAR *RemotePort,
    /* [retval][out] */ long __RPC_FAR *Count);


void __RPC_STUB IUdp_Receive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IUdp_Send_Proxy( 
    IUdp __RPC_FAR * This,
    VARIANT __RPC_FAR *Data,
    BSTR RemoteName,
    /* [optional] */ long RemotePort,
    /* [optional] */ long LimitCount,
    /* [optional] */ VARIANT_BOOL DontRoute,
    /* [retval][out] */ long __RPC_FAR *Count);


void __RPC_STUB IUdp_Send_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IUdp_Abort_Proxy( 
    IUdp __RPC_FAR * This);


void __RPC_STUB IUdp_Abort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IUdp_About_Proxy( 
    IUdp __RPC_FAR * This);


void __RPC_STUB IUdp_About_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IUdp_Join_Proxy( 
    IUdp __RPC_FAR * This,
    /* [in] */ BSTR Group);


void __RPC_STUB IUdp_Join_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUdp_get_DontEcho_Proxy( 
    IUdp __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IUdp_get_DontEcho_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUdp_put_DontEcho_Proxy( 
    IUdp __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IUdp_put_DontEcho_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IUdp_get_MaxSubnets_Proxy( 
    IUdp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IUdp_get_MaxSubnets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IUdp_put_MaxSubnets_Proxy( 
    IUdp __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IUdp_put_MaxSubnets_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IUdp_Trace_Proxy( 
    IUdp __RPC_FAR * This,
    /* [optional][out][in] */ VARIANT __RPC_FAR *Result,
    /* [optional] */ VARIANT_BOOL Send,
    /* [optional] */ VARIANT_BOOL Receive,
    /* [optional] */ BSTR SendPrompt,
    /* [optional] */ BSTR ReceivePrompt);


void __RPC_STUB IUdp_Trace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IUdp_INTERFACE_DEFINED__ */


#ifndef __IDartStream_INTERFACE_DEFINED__
#define __IDartStream_INTERFACE_DEFINED__

/* interface IDartStream */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IDartStream;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0C1F87AD-AE62-11D3-911C-00105A17B608")
    IDartStream : public IDispatch
    {
    public:
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE put_FileName( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_DeleteOnDestroy( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE put_DeleteOnDestroy( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileMode( 
            /* [retval][out] */ FileModeConstants __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE put_FileMode( 
            /* [in] */ FileModeConstants newVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Ref( 
            /* [retval][out] */ VARIANT __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE put_Ref( 
            /* [in] */ VARIANT newVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Position( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE put_Position( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_UniqueName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Read( 
            /* [out][in] */ VARIANT __RPC_FAR *Buffer,
            /* [optional][in] */ long Count,
            /* [retval][out] */ long __RPC_FAR *Result) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Write( 
            /* [in] */ VARIANT Buffer,
            /* [optional][in] */ long Count,
            /* [retval][out] */ long __RPC_FAR *Result) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE ReadString( 
            /* [optional][in] */ long Count,
            /* [retval][out] */ BSTR __RPC_FAR *Data) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE ReadBytes( 
            /* [optional][in] */ long Count,
            /* [retval][out] */ VARIANT __RPC_FAR *Data) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDartStreamVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDartStream __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDartStream __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDartStream __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDartStream __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDartStream __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDartStream __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDartStream __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FileName )( 
            IDartStream __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FileName )( 
            IDartStream __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DeleteOnDestroy )( 
            IDartStream __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DeleteOnDestroy )( 
            IDartStream __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FileMode )( 
            IDartStream __RPC_FAR * This,
            /* [retval][out] */ FileModeConstants __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FileMode )( 
            IDartStream __RPC_FAR * This,
            /* [in] */ FileModeConstants newVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Ref )( 
            IDartStream __RPC_FAR * This,
            /* [retval][out] */ VARIANT __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Ref )( 
            IDartStream __RPC_FAR * This,
            /* [in] */ VARIANT newVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Position )( 
            IDartStream __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Position )( 
            IDartStream __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Size )( 
            IDartStream __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_UniqueName )( 
            IDartStream __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Read )( 
            IDartStream __RPC_FAR * This,
            /* [out][in] */ VARIANT __RPC_FAR *Buffer,
            /* [optional][in] */ long Count,
            /* [retval][out] */ long __RPC_FAR *Result);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Write )( 
            IDartStream __RPC_FAR * This,
            /* [in] */ VARIANT Buffer,
            /* [optional][in] */ long Count,
            /* [retval][out] */ long __RPC_FAR *Result);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clear )( 
            IDartStream __RPC_FAR * This);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReadString )( 
            IDartStream __RPC_FAR * This,
            /* [optional][in] */ long Count,
            /* [retval][out] */ BSTR __RPC_FAR *Data);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReadBytes )( 
            IDartStream __RPC_FAR * This,
            /* [optional][in] */ long Count,
            /* [retval][out] */ VARIANT __RPC_FAR *Data);
        
        END_INTERFACE
    } IDartStreamVtbl;

    interface IDartStream
    {
        CONST_VTBL struct IDartStreamVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDartStream_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDartStream_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDartStream_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDartStream_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDartStream_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDartStream_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDartStream_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDartStream_get_FileName(This,pVal)	\
    (This)->lpVtbl -> get_FileName(This,pVal)

#define IDartStream_put_FileName(This,newVal)	\
    (This)->lpVtbl -> put_FileName(This,newVal)

#define IDartStream_get_DeleteOnDestroy(This,pVal)	\
    (This)->lpVtbl -> get_DeleteOnDestroy(This,pVal)

#define IDartStream_put_DeleteOnDestroy(This,newVal)	\
    (This)->lpVtbl -> put_DeleteOnDestroy(This,newVal)

#define IDartStream_get_FileMode(This,pVal)	\
    (This)->lpVtbl -> get_FileMode(This,pVal)

#define IDartStream_put_FileMode(This,newVal)	\
    (This)->lpVtbl -> put_FileMode(This,newVal)

#define IDartStream_get_Ref(This,pVal)	\
    (This)->lpVtbl -> get_Ref(This,pVal)

#define IDartStream_put_Ref(This,newVal)	\
    (This)->lpVtbl -> put_Ref(This,newVal)

#define IDartStream_get_Position(This,pVal)	\
    (This)->lpVtbl -> get_Position(This,pVal)

#define IDartStream_put_Position(This,newVal)	\
    (This)->lpVtbl -> put_Position(This,newVal)

#define IDartStream_get_Size(This,pVal)	\
    (This)->lpVtbl -> get_Size(This,pVal)

#define IDartStream_get_UniqueName(This,pVal)	\
    (This)->lpVtbl -> get_UniqueName(This,pVal)

#define IDartStream_Read(This,Buffer,Count,Result)	\
    (This)->lpVtbl -> Read(This,Buffer,Count,Result)

#define IDartStream_Write(This,Buffer,Count,Result)	\
    (This)->lpVtbl -> Write(This,Buffer,Count,Result)

#define IDartStream_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define IDartStream_ReadString(This,Count,Data)	\
    (This)->lpVtbl -> ReadString(This,Count,Data)

#define IDartStream_ReadBytes(This,Count,Data)	\
    (This)->lpVtbl -> ReadBytes(This,Count,Data)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE IDartStream_get_FileName_Proxy( 
    IDartStream __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IDartStream_get_FileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE IDartStream_put_FileName_Proxy( 
    IDartStream __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IDartStream_put_FileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE IDartStream_get_DeleteOnDestroy_Proxy( 
    IDartStream __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IDartStream_get_DeleteOnDestroy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE IDartStream_put_DeleteOnDestroy_Proxy( 
    IDartStream __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IDartStream_put_DeleteOnDestroy_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE IDartStream_get_FileMode_Proxy( 
    IDartStream __RPC_FAR * This,
    /* [retval][out] */ FileModeConstants __RPC_FAR *pVal);


void __RPC_STUB IDartStream_get_FileMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE IDartStream_put_FileMode_Proxy( 
    IDartStream __RPC_FAR * This,
    /* [in] */ FileModeConstants newVal);


void __RPC_STUB IDartStream_put_FileMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE IDartStream_get_Ref_Proxy( 
    IDartStream __RPC_FAR * This,
    /* [retval][out] */ VARIANT __RPC_FAR *pVal);


void __RPC_STUB IDartStream_get_Ref_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE IDartStream_put_Ref_Proxy( 
    IDartStream __RPC_FAR * This,
    /* [in] */ VARIANT newVal);


void __RPC_STUB IDartStream_put_Ref_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE IDartStream_get_Position_Proxy( 
    IDartStream __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IDartStream_get_Position_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propput] */ HRESULT STDMETHODCALLTYPE IDartStream_put_Position_Proxy( 
    IDartStream __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IDartStream_put_Position_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE IDartStream_get_Size_Proxy( 
    IDartStream __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IDartStream_get_Size_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE IDartStream_get_UniqueName_Proxy( 
    IDartStream __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IDartStream_get_UniqueName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE IDartStream_Read_Proxy( 
    IDartStream __RPC_FAR * This,
    /* [out][in] */ VARIANT __RPC_FAR *Buffer,
    /* [optional][in] */ long Count,
    /* [retval][out] */ long __RPC_FAR *Result);


void __RPC_STUB IDartStream_Read_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE IDartStream_Write_Proxy( 
    IDartStream __RPC_FAR * This,
    /* [in] */ VARIANT Buffer,
    /* [optional][in] */ long Count,
    /* [retval][out] */ long __RPC_FAR *Result);


void __RPC_STUB IDartStream_Write_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE IDartStream_Clear_Proxy( 
    IDartStream __RPC_FAR * This);


void __RPC_STUB IDartStream_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE IDartStream_ReadString_Proxy( 
    IDartStream __RPC_FAR * This,
    /* [optional][in] */ long Count,
    /* [retval][out] */ BSTR __RPC_FAR *Data);


void __RPC_STUB IDartStream_ReadString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE IDartStream_ReadBytes_Proxy( 
    IDartStream __RPC_FAR * This,
    /* [optional][in] */ long Count,
    /* [retval][out] */ VARIANT __RPC_FAR *Data);


void __RPC_STUB IDartStream_ReadBytes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDartStream_INTERFACE_DEFINED__ */


#ifndef __IDartStreams_INTERFACE_DEFINED__
#define __IDartStreams_INTERFACE_DEFINED__

/* interface IDartStreams */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IDartStreams;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8243AD9B-A8D4-474D-9C44-CE20C67D4662")
    IDartStreams : public IDispatch
    {
    public:
        virtual /* [restricted][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Item( 
            long Index,
            /* [retval][out] */ LPDARTSTREAM __RPC_FAR *pItem) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Add( 
            LPDARTSTREAM pStream) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Remove( 
            long Index,
            /* [retval][out] */ LPDARTSTREAM __RPC_FAR *pItem) = 0;
        
        virtual /* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE Clear( void) = 0;
        
        virtual /* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDartStreamsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IDartStreams __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IDartStreams __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IDartStreams __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IDartStreams __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IDartStreams __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IDartStreams __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IDartStreams __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [restricted][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IDartStreams __RPC_FAR * This,
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            IDartStreams __RPC_FAR * This,
            long Index,
            /* [retval][out] */ LPDARTSTREAM __RPC_FAR *pItem);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Add )( 
            IDartStreams __RPC_FAR * This,
            LPDARTSTREAM pStream);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Remove )( 
            IDartStreams __RPC_FAR * This,
            long Index,
            /* [retval][out] */ LPDARTSTREAM __RPC_FAR *pItem);
        
        /* [helpstring][helpcontext][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Clear )( 
            IDartStreams __RPC_FAR * This);
        
        /* [helpstring][helpcontext][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IDartStreams __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        END_INTERFACE
    } IDartStreamsVtbl;

    interface IDartStreams
    {
        CONST_VTBL struct IDartStreamsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDartStreams_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IDartStreams_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IDartStreams_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IDartStreams_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IDartStreams_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IDartStreams_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IDartStreams_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IDartStreams_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define IDartStreams_Item(This,Index,pItem)	\
    (This)->lpVtbl -> Item(This,Index,pItem)

#define IDartStreams_Add(This,pStream)	\
    (This)->lpVtbl -> Add(This,pStream)

#define IDartStreams_Remove(This,Index,pItem)	\
    (This)->lpVtbl -> Remove(This,Index,pItem)

#define IDartStreams_Clear(This)	\
    (This)->lpVtbl -> Clear(This)

#define IDartStreams_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [restricted][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IDartStreams_get__NewEnum_Proxy( 
    IDartStreams __RPC_FAR * This,
    /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);


void __RPC_STUB IDartStreams_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE IDartStreams_Item_Proxy( 
    IDartStreams __RPC_FAR * This,
    long Index,
    /* [retval][out] */ LPDARTSTREAM __RPC_FAR *pItem);


void __RPC_STUB IDartStreams_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE IDartStreams_Add_Proxy( 
    IDartStreams __RPC_FAR * This,
    LPDARTSTREAM pStream);


void __RPC_STUB IDartStreams_Add_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE IDartStreams_Remove_Proxy( 
    IDartStreams __RPC_FAR * This,
    long Index,
    /* [retval][out] */ LPDARTSTREAM __RPC_FAR *pItem);


void __RPC_STUB IDartStreams_Remove_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id] */ HRESULT STDMETHODCALLTYPE IDartStreams_Clear_Proxy( 
    IDartStreams __RPC_FAR * This);


void __RPC_STUB IDartStreams_Clear_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][helpcontext][id][propget] */ HRESULT STDMETHODCALLTYPE IDartStreams_get_Count_Proxy( 
    IDartStreams __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IDartStreams_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IDartStreams_INTERFACE_DEFINED__ */


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
