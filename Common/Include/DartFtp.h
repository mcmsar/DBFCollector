/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Apr 09 14:19:07 2001
 */
/* Compiler settings for .\DartFtp.idl:
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

#ifndef __DartFtp_h__
#define __DartFtp_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __DartStrings_FWD_DEFINED__
#define __DartStrings_FWD_DEFINED__

#ifdef __cplusplus
typedef class DartStrings DartStrings;
#else
typedef struct DartStrings DartStrings;
#endif /* __cplusplus */

#endif 	/* __DartStrings_FWD_DEFINED__ */


#ifndef ___IFtpEvents_FWD_DEFINED__
#define ___IFtpEvents_FWD_DEFINED__
typedef interface _IFtpEvents _IFtpEvents;
#endif 	/* ___IFtpEvents_FWD_DEFINED__ */


#ifndef __Ftp_FWD_DEFINED__
#define __Ftp_FWD_DEFINED__

#ifdef __cplusplus
typedef class Ftp Ftp;
#else
typedef struct Ftp Ftp;
#endif /* __cplusplus */

#endif 	/* __Ftp_FWD_DEFINED__ */


#ifndef __ListEntry_FWD_DEFINED__
#define __ListEntry_FWD_DEFINED__

#ifdef __cplusplus
typedef class ListEntry ListEntry;
#else
typedef struct ListEntry ListEntry;
#endif /* __cplusplus */

#endif 	/* __ListEntry_FWD_DEFINED__ */


#ifndef __ListEntries_FWD_DEFINED__
#define __ListEntries_FWD_DEFINED__

#ifdef __cplusplus
typedef class ListEntries ListEntries;
#else
typedef struct ListEntries ListEntries;
#endif /* __cplusplus */

#endif 	/* __ListEntries_FWD_DEFINED__ */


#ifndef __IListEntry_FWD_DEFINED__
#define __IListEntry_FWD_DEFINED__
typedef interface IListEntry IListEntry;
#endif 	/* __IListEntry_FWD_DEFINED__ */


#ifndef __IListEntries_FWD_DEFINED__
#define __IListEntries_FWD_DEFINED__
typedef interface IListEntries IListEntries;
#endif 	/* __IListEntries_FWD_DEFINED__ */


#ifndef __IFtp_FWD_DEFINED__
#define __IFtp_FWD_DEFINED__
typedef interface IFtp IFtp;
#endif 	/* __IFtp_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "DartSock.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

DEFINE_GUID( CLSID_Ftp, 0x39fda070,0x61ba,0x11d2, 0xad,0x84,0x00,0x10,0x5a,0x17,0xb6,0x08);
DEFINE_GUID( IID_IFtp, 0x39fda06f,0x61ba,0x11d2, 0xad,0x84,0x00,0x10,0x5a,0x17,0xb6,0x08);


#ifndef __DartFtp_LIBRARY_DEFINED__
#define __DartFtp_LIBRARY_DEFINED__

/* library DartFtp */
/* [helpcontext][helpfile][helpstring][version][uuid] */ 

typedef /* [helpstring][helpcontext][uuid] */ enum ErrorConstants ErrorConstants;

typedef /* [helpstring][helpcontext][uuid] */ enum StateConstants StateConstants;

typedef /* [helpcontext][helpstring][uuid] */ 
enum FtpFormatConstants
    {	formatUnix	= 0,
	formatDos	= 1,
	formatOther	= 2
    }	FtpFormatConstants;

typedef /* [helpstring][helpcontext][uuid] */ 
enum TypeConstants
    {	ftpAscii	= 0,
	ftpImage	= 1,
	ftpEbcdic	= 2
    }	TypeConstants;

typedef /* [helpstring][helpcontext][uuid] */ 
enum TransferModeConstants
    {	ftpStream	= 0,
	ftpBlock	= 1,
	ftpCompressed	= 2
    }	TransferModeConstants;

typedef /* [helpstring][helpcontext][uuid] */ 
enum FileStructureConstants
    {	ftpFile	= 0,
	ftpRecord	= 1,
	ftpPage	= 2
    }	FileStructureConstants;

typedef /* [helpstring][helpcontext][uuid] */ 
enum StatusConstants
    {	ftpOk	= 0,
	ftpInProgress	= 1,
	ftpError	= 2
    }	StatusConstants;

typedef /* [helpstring][helpcontext][uuid] */ 
enum StoreConstants
    {	storeReplace	= 0,
	storeUnique	= 1,
	storeAppend	= 2
    }	StoreConstants;

typedef /* [helpstring][helpcontext][uuid] */ 
enum CommandConstants
    {	ftpUserCommand	= 0,
	ftpUser	= 1,
	ftpPassword	= 2,
	ftpAccount	= 3,
	ftpChangeDirectory	= 4,
	ftpChangeDirectoryUp	= 5,
	ftpStructureMount	= 6,
	ftpQuit	= 7,
	ftpReinitialize	= 8,
	ftpPort	= 9,
	ftpPassive	= 10,
	ftpType	= 11,
	ftpFileStructure	= 12,
	ftpTransferMode	= 13,
	ftpRetrieve	= 14,
	ftpStore	= 15,
	ftpStoreUnique	= 16,
	ftpAppend	= 17,
	ftpAllocate	= 18,
	ftpRestart	= 19,
	ftpRenameFrom	= 20,
	ftpRenameTo	= 21,
	ftpAbort	= 22,
	ftpDelete	= 23,
	ftpRemoveDirectory	= 24,
	ftpMakeDirectory	= 25,
	ftpPrintDirectory	= 26,
	ftpList	= 27,
	ftpNameList	= 28,
	ftpSite	= 29,
	ftpSystem	= 30,
	ftpStatus	= 31,
	ftpHelp	= 32,
	ftpNoOperation	= 33,
	ftpSize	= 34,
	ftpOpen	= 35
    }	CommandConstants;

typedef /* [helpcontext][helpstring][uuid] */ 
enum FtpProxyTypeConstants
    {	ftpProxyNone	= 0,
	ftpProxySocks4	= 1,
	ftpProxySocks5	= 2,
	ftpProxySiteHost	= 3,
	ftpProxyUserLogin	= 4,
	ftpProxyUserNoLogin	= 5,
	ftpProxyOpen	= 6,
	ftpProxyPipe	= 7
    }	FtpProxyTypeConstants;


EXTERN_C const IID LIBID_DartFtp;

EXTERN_C const CLSID CLSID_DartStrings;

#ifdef __cplusplus

class DECLSPEC_UUID("E9D55102-9683-11D2-BA68-0040053687FE")
DartStrings;
#endif

#ifndef ___IFtpEvents_DISPINTERFACE_DEFINED__
#define ___IFtpEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IFtpEvents */
/* [helpcontext][helpstring][uuid] */ 


EXTERN_C const IID DIID__IFtpEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("39FDA071-61BA-11D2-AD84-00105A17B608")
    _IFtpEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IFtpEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IFtpEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IFtpEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IFtpEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IFtpEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IFtpEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IFtpEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IFtpEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IFtpEventsVtbl;

    interface _IFtpEvents
    {
        CONST_VTBL struct _IFtpEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IFtpEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IFtpEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IFtpEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IFtpEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IFtpEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IFtpEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IFtpEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IFtpEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Ftp;

#ifdef __cplusplus

class DECLSPEC_UUID("39FDA070-61BA-11D2-AD84-00105A17B608")
Ftp;
#endif

EXTERN_C const CLSID CLSID_ListEntry;

#ifdef __cplusplus

class DECLSPEC_UUID("A1EEDAA7-C4D8-11D2-AD9C-00105A17B608")
ListEntry;
#endif

EXTERN_C const CLSID CLSID_ListEntries;

#ifdef __cplusplus

class DECLSPEC_UUID("BCBDDE0B-C5A6-11D2-AD9C-00105A17B608")
ListEntries;
#endif
#endif /* __DartFtp_LIBRARY_DEFINED__ */

#ifndef __IListEntry_INTERFACE_DEFINED__
#define __IListEntry_INTERFACE_DEFINED__

/* interface IListEntry */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 

typedef /* [unique] */ IListEntry __RPC_FAR *LPLISTENTRY;


EXTERN_C const IID IID_IListEntry;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F6241E16-C4F7-11D2-AD9C-00105A17B608")
    IListEntry : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Name( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Permissions( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Directory( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Owner( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_GroupName( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Size( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TimeStamp( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Links( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Destination( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Text( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Text( 
            /* [in] */ BSTR newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IListEntryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IListEntry __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IListEntry __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IListEntry __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IListEntry __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IListEntry __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IListEntry __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IListEntry __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Name )( 
            IListEntry __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            IListEntry __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Permissions )( 
            IListEntry __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Directory )( 
            IListEntry __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Owner )( 
            IListEntry __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_GroupName )( 
            IListEntry __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Size )( 
            IListEntry __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TimeStamp )( 
            IListEntry __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Links )( 
            IListEntry __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Destination )( 
            IListEntry __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Text )( 
            IListEntry __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Text )( 
            IListEntry __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        END_INTERFACE
    } IListEntryVtbl;

    interface IListEntry
    {
        CONST_VTBL struct IListEntryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IListEntry_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IListEntry_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IListEntry_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IListEntry_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IListEntry_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IListEntry_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IListEntry_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IListEntry_get_Name(This,pVal)	\
    (This)->lpVtbl -> get_Name(This,pVal)

#define IListEntry_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define IListEntry_get_Permissions(This,pVal)	\
    (This)->lpVtbl -> get_Permissions(This,pVal)

#define IListEntry_get_Directory(This,pVal)	\
    (This)->lpVtbl -> get_Directory(This,pVal)

#define IListEntry_get_Owner(This,pVal)	\
    (This)->lpVtbl -> get_Owner(This,pVal)

#define IListEntry_get_GroupName(This,pVal)	\
    (This)->lpVtbl -> get_GroupName(This,pVal)

#define IListEntry_get_Size(This,pVal)	\
    (This)->lpVtbl -> get_Size(This,pVal)

#define IListEntry_get_TimeStamp(This,pVal)	\
    (This)->lpVtbl -> get_TimeStamp(This,pVal)

#define IListEntry_get_Links(This,pVal)	\
    (This)->lpVtbl -> get_Links(This,pVal)

#define IListEntry_get_Destination(This,pVal)	\
    (This)->lpVtbl -> get_Destination(This,pVal)

#define IListEntry_get_Text(This,pVal)	\
    (This)->lpVtbl -> get_Text(This,pVal)

#define IListEntry_put_Text(This,newVal)	\
    (This)->lpVtbl -> put_Text(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IListEntry_get_Name_Proxy( 
    IListEntry __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IListEntry_get_Name_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IListEntry_get_Type_Proxy( 
    IListEntry __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IListEntry_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IListEntry_get_Permissions_Proxy( 
    IListEntry __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IListEntry_get_Permissions_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IListEntry_get_Directory_Proxy( 
    IListEntry __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IListEntry_get_Directory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IListEntry_get_Owner_Proxy( 
    IListEntry __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IListEntry_get_Owner_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IListEntry_get_GroupName_Proxy( 
    IListEntry __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IListEntry_get_GroupName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IListEntry_get_Size_Proxy( 
    IListEntry __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IListEntry_get_Size_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IListEntry_get_TimeStamp_Proxy( 
    IListEntry __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IListEntry_get_TimeStamp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IListEntry_get_Links_Proxy( 
    IListEntry __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IListEntry_get_Links_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IListEntry_get_Destination_Proxy( 
    IListEntry __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IListEntry_get_Destination_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IListEntry_get_Text_Proxy( 
    IListEntry __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IListEntry_get_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IListEntry_put_Text_Proxy( 
    IListEntry __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IListEntry_put_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IListEntry_INTERFACE_DEFINED__ */


#ifndef __IListEntries_INTERFACE_DEFINED__
#define __IListEntries_INTERFACE_DEFINED__

/* interface IListEntries */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 

typedef /* [unique] */ IListEntries __RPC_FAR *LPLISTENTRIES;


EXTERN_C const IID IID_IListEntries;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BCBDDE0A-C5A6-11D2-AD9C-00105A17B608")
    IListEntries : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Text( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Text( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Format( 
            /* [retval][out] */ FtpFormatConstants __RPC_FAR *pVal) = 0;
        
        virtual /* [restricted][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get__NewEnum( 
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Item( 
            /* [in] */ VARIANT Index,
            /* [retval][out] */ LPLISTENTRY __RPC_FAR *pItem) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Append( 
            /* [in] */ BSTR Listing) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IListEntriesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IListEntries __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IListEntries __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IListEntries __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IListEntries __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IListEntries __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IListEntries __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IListEntries __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Text )( 
            IListEntries __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Text )( 
            IListEntries __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Count )( 
            IListEntries __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Format )( 
            IListEntries __RPC_FAR * This,
            /* [retval][out] */ FtpFormatConstants __RPC_FAR *pVal);
        
        /* [restricted][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get__NewEnum )( 
            IListEntries __RPC_FAR * This,
            /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Item )( 
            IListEntries __RPC_FAR * This,
            /* [in] */ VARIANT Index,
            /* [retval][out] */ LPLISTENTRY __RPC_FAR *pItem);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Append )( 
            IListEntries __RPC_FAR * This,
            /* [in] */ BSTR Listing);
        
        END_INTERFACE
    } IListEntriesVtbl;

    interface IListEntries
    {
        CONST_VTBL struct IListEntriesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IListEntries_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IListEntries_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IListEntries_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IListEntries_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IListEntries_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IListEntries_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IListEntries_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IListEntries_get_Text(This,pVal)	\
    (This)->lpVtbl -> get_Text(This,pVal)

#define IListEntries_put_Text(This,newVal)	\
    (This)->lpVtbl -> put_Text(This,newVal)

#define IListEntries_get_Count(This,pVal)	\
    (This)->lpVtbl -> get_Count(This,pVal)

#define IListEntries_get_Format(This,pVal)	\
    (This)->lpVtbl -> get_Format(This,pVal)

#define IListEntries_get__NewEnum(This,pVal)	\
    (This)->lpVtbl -> get__NewEnum(This,pVal)

#define IListEntries_Item(This,Index,pItem)	\
    (This)->lpVtbl -> Item(This,Index,pItem)

#define IListEntries_Append(This,Listing)	\
    (This)->lpVtbl -> Append(This,Listing)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IListEntries_get_Text_Proxy( 
    IListEntries __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IListEntries_get_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IListEntries_put_Text_Proxy( 
    IListEntries __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IListEntries_put_Text_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IListEntries_get_Count_Proxy( 
    IListEntries __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IListEntries_get_Count_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IListEntries_get_Format_Proxy( 
    IListEntries __RPC_FAR * This,
    /* [retval][out] */ FtpFormatConstants __RPC_FAR *pVal);


void __RPC_STUB IListEntries_get_Format_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [restricted][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IListEntries_get__NewEnum_Proxy( 
    IListEntries __RPC_FAR * This,
    /* [retval][out] */ LPUNKNOWN __RPC_FAR *pVal);


void __RPC_STUB IListEntries_get__NewEnum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IListEntries_Item_Proxy( 
    IListEntries __RPC_FAR * This,
    /* [in] */ VARIANT Index,
    /* [retval][out] */ LPLISTENTRY __RPC_FAR *pItem);


void __RPC_STUB IListEntries_Item_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IListEntries_Append_Proxy( 
    IListEntries __RPC_FAR * This,
    /* [in] */ BSTR Listing);


void __RPC_STUB IListEntries_Append_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IListEntries_INTERFACE_DEFINED__ */


#ifndef __IFtp_INTERFACE_DEFINED__
#define __IFtp_INTERFACE_DEFINED__

/* interface IFtp */
/* [unique][helpcontext][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IFtp;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("39FDA06F-61BA-11D2-AD84-00105A17B608")
    IFtp : public IDispatch
    {
    public:
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Allocate( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Allocate( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Directory( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Directory( 
            /* [in] */ BSTR newval) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_FileStructure( 
            /* [retval][out] */ FileStructureConstants __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_FileStructure( 
            /* [in] */ FileStructureConstants newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Listing( 
            /* [retval][out] */ LPLISTENTRIES __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Listing( 
            /* [in] */ IListEntries __RPC_FAR *newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Passive( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Passive( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_StoreType( 
            /* [retval][out] */ StoreConstants __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_StoreType( 
            /* [in] */ StoreConstants newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TimeOut( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TimeOut( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TransferMode( 
            /* [retval][out] */ TransferModeConstants __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TransferMode( 
            /* [in] */ TransferModeConstants newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Type( 
            /* [retval][out] */ TypeConstants __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_Type( 
            /* [in] */ TypeConstants newVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Blocked( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LocalAddress( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_LocalPort( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RemoteAddress( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_RemotePort( 
            /* [retval][out] */ long __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Restart( 
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_State( 
            /* [retval][out] */ StateConstants __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_System( 
            /* [retval][out] */ BSTR __RPC_FAR *pVal) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE About( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Abort( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE AbortCommand( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE ChangeDirectoryUp( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Command( 
            /* [in] */ BSTR FtpCommand,
            VARIANT __RPC_FAR *Result) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Trace( 
            /* [out][in][optional] */ VARIANT __RPC_FAR *Result,
            /* [optional] */ VARIANT_BOOL Send,
            /* [optional] */ VARIANT_BOOL Receive,
            /* [optional] */ BSTR SendPrompt,
            /* [optional] */ BSTR ReceivePrompt) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Delete( 
            /* [in] */ BSTR PathName) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Help( 
            VARIANT __RPC_FAR *Result,
            /* [optional][in] */ BSTR Command) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE List( 
            /* [optional][in] */ BSTR PathName) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Login( 
            /* [optional][in] */ BSTR RemoteName,
            /* [optional][in] */ BSTR User,
            /* [optional][in] */ BSTR Password,
            /* [optional][in] */ BSTR Account,
            /* [optional][in] */ long RemotePort) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Logout( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE MakeDirectory( 
            /* [in] */ BSTR PathName) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE NameList( 
            /* [optional][in] */ BSTR PathName) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE NoOperation( void) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveDirectory( 
            /* [in] */ BSTR PathName) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Rename( 
            /* [in] */ BSTR FromFileName,
            /* [in] */ BSTR ToFileName) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Retrieve( 
            /* [in] */ BSTR RemoteFileName,
            /* [optional][out][in] */ VARIANT __RPC_FAR *Result,
            /* [optional][in] */ long Marker) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Site( 
            /* [in] */ BSTR Modifier,
            VARIANT __RPC_FAR *Result) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Status( 
            VARIANT __RPC_FAR *Result,
            /* [optional][in] */ BSTR PathName) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Store( 
            /* [in] */ BSTR RemoteFileName,
            /* [optional][in] */ VARIANT Data,
            /* [optional][in] */ long Marker) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE StructureMount( 
            /* [in] */ BSTR PathName) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Get( 
            /* [in] */ BSTR Url,
            /* [optional][out][in] */ VARIANT __RPC_FAR *Result,
            /* [optional][in] */ long Marker) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE Put( 
            /* [in] */ BSTR Url,
            /* [optional][in] */ VARIANT Source,
            /* [optional][in] */ long Marker) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE MGet( 
            /* [defaultvalue][optional][in] */ BSTR Source,
            /* [defaultvalue][optional][in] */ BSTR Destination,
            /* [optional][in] */ VARIANT FilesTransferred,
            /* [optional][in] */ VARIANT FileErrors) = 0;
        
        virtual /* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE MPut( 
            /* [defaultvalue][optional][in] */ BSTR Source,
            /* [defaultvalue][optional][in] */ BSTR Destination,
            /* [optional][in] */ VARIANT FilesTransferred,
            /* [optional][in] */ VARIANT FileErrors) = 0;
        
        virtual /* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_ProxyType( 
            /* [retval][out] */ FtpProxyTypeConstants __RPC_FAR *pVal) = 0;
        
        virtual /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_ProxyType( 
            /* [in] */ FtpProxyTypeConstants newVal) = 0;
        
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

    typedef struct IFtpVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IFtp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IFtp __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IFtp __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IFtp __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IFtp __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IFtp __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IFtp __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Allocate )( 
            IFtp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Allocate )( 
            IFtp __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Directory )( 
            IFtp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Directory )( 
            IFtp __RPC_FAR * This,
            /* [in] */ BSTR newval);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_FileStructure )( 
            IFtp __RPC_FAR * This,
            /* [retval][out] */ FileStructureConstants __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_FileStructure )( 
            IFtp __RPC_FAR * This,
            /* [in] */ FileStructureConstants newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Listing )( 
            IFtp __RPC_FAR * This,
            /* [retval][out] */ LPLISTENTRIES __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Listing )( 
            IFtp __RPC_FAR * This,
            /* [in] */ IListEntries __RPC_FAR *newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Passive )( 
            IFtp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Passive )( 
            IFtp __RPC_FAR * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StoreType )( 
            IFtp __RPC_FAR * This,
            /* [retval][out] */ StoreConstants __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_StoreType )( 
            IFtp __RPC_FAR * This,
            /* [in] */ StoreConstants newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TimeOut )( 
            IFtp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TimeOut )( 
            IFtp __RPC_FAR * This,
            /* [in] */ long newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TransferMode )( 
            IFtp __RPC_FAR * This,
            /* [retval][out] */ TransferModeConstants __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TransferMode )( 
            IFtp __RPC_FAR * This,
            /* [in] */ TransferModeConstants newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Type )( 
            IFtp __RPC_FAR * This,
            /* [retval][out] */ TypeConstants __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Type )( 
            IFtp __RPC_FAR * This,
            /* [in] */ TypeConstants newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Blocked )( 
            IFtp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocalAddress )( 
            IFtp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_LocalPort )( 
            IFtp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RemoteAddress )( 
            IFtp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_RemotePort )( 
            IFtp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Restart )( 
            IFtp __RPC_FAR * This,
            /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_State )( 
            IFtp __RPC_FAR * This,
            /* [retval][out] */ StateConstants __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_System )( 
            IFtp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *About )( 
            IFtp __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Abort )( 
            IFtp __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AbortCommand )( 
            IFtp __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ChangeDirectoryUp )( 
            IFtp __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Command )( 
            IFtp __RPC_FAR * This,
            /* [in] */ BSTR FtpCommand,
            VARIANT __RPC_FAR *Result);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Trace )( 
            IFtp __RPC_FAR * This,
            /* [out][in][optional] */ VARIANT __RPC_FAR *Result,
            /* [optional] */ VARIANT_BOOL Send,
            /* [optional] */ VARIANT_BOOL Receive,
            /* [optional] */ BSTR SendPrompt,
            /* [optional] */ BSTR ReceivePrompt);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Delete )( 
            IFtp __RPC_FAR * This,
            /* [in] */ BSTR PathName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Help )( 
            IFtp __RPC_FAR * This,
            VARIANT __RPC_FAR *Result,
            /* [optional][in] */ BSTR Command);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *List )( 
            IFtp __RPC_FAR * This,
            /* [optional][in] */ BSTR PathName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Login )( 
            IFtp __RPC_FAR * This,
            /* [optional][in] */ BSTR RemoteName,
            /* [optional][in] */ BSTR User,
            /* [optional][in] */ BSTR Password,
            /* [optional][in] */ BSTR Account,
            /* [optional][in] */ long RemotePort);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Logout )( 
            IFtp __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MakeDirectory )( 
            IFtp __RPC_FAR * This,
            /* [in] */ BSTR PathName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NameList )( 
            IFtp __RPC_FAR * This,
            /* [optional][in] */ BSTR PathName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *NoOperation )( 
            IFtp __RPC_FAR * This);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RemoveDirectory )( 
            IFtp __RPC_FAR * This,
            /* [in] */ BSTR PathName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Rename )( 
            IFtp __RPC_FAR * This,
            /* [in] */ BSTR FromFileName,
            /* [in] */ BSTR ToFileName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Retrieve )( 
            IFtp __RPC_FAR * This,
            /* [in] */ BSTR RemoteFileName,
            /* [optional][out][in] */ VARIANT __RPC_FAR *Result,
            /* [optional][in] */ long Marker);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Site )( 
            IFtp __RPC_FAR * This,
            /* [in] */ BSTR Modifier,
            VARIANT __RPC_FAR *Result);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Status )( 
            IFtp __RPC_FAR * This,
            VARIANT __RPC_FAR *Result,
            /* [optional][in] */ BSTR PathName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Store )( 
            IFtp __RPC_FAR * This,
            /* [in] */ BSTR RemoteFileName,
            /* [optional][in] */ VARIANT Data,
            /* [optional][in] */ long Marker);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *StructureMount )( 
            IFtp __RPC_FAR * This,
            /* [in] */ BSTR PathName);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Get )( 
            IFtp __RPC_FAR * This,
            /* [in] */ BSTR Url,
            /* [optional][out][in] */ VARIANT __RPC_FAR *Result,
            /* [optional][in] */ long Marker);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Put )( 
            IFtp __RPC_FAR * This,
            /* [in] */ BSTR Url,
            /* [optional][in] */ VARIANT Source,
            /* [optional][in] */ long Marker);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MGet )( 
            IFtp __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Source,
            /* [defaultvalue][optional][in] */ BSTR Destination,
            /* [optional][in] */ VARIANT FilesTransferred,
            /* [optional][in] */ VARIANT FileErrors);
        
        /* [helpcontext][helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *MPut )( 
            IFtp __RPC_FAR * This,
            /* [defaultvalue][optional][in] */ BSTR Source,
            /* [defaultvalue][optional][in] */ BSTR Destination,
            /* [optional][in] */ VARIANT FilesTransferred,
            /* [optional][in] */ VARIANT FileErrors);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProxyType )( 
            IFtp __RPC_FAR * This,
            /* [retval][out] */ FtpProxyTypeConstants __RPC_FAR *pVal);
        
        /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProxyType )( 
            IFtp __RPC_FAR * This,
            /* [in] */ FtpProxyTypeConstants newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProxyHost )( 
            IFtp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProxyHost )( 
            IFtp __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProxyUsername )( 
            IFtp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProxyUsername )( 
            IFtp __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProxyPassword )( 
            IFtp __RPC_FAR * This,
            /* [retval][out] */ BSTR __RPC_FAR *pVal);
        
        /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProxyPassword )( 
            IFtp __RPC_FAR * This,
            /* [in] */ BSTR newVal);
        
        /* [helpcontext][helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ProxyPort )( 
            IFtp __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_ProxyPort )( 
            IFtp __RPC_FAR * This,
            /* [in] */ long newVal);
        
        END_INTERFACE
    } IFtpVtbl;

    interface IFtp
    {
        CONST_VTBL struct IFtpVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFtp_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IFtp_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IFtp_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IFtp_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IFtp_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IFtp_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IFtp_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IFtp_get_Allocate(This,pVal)	\
    (This)->lpVtbl -> get_Allocate(This,pVal)

#define IFtp_put_Allocate(This,newVal)	\
    (This)->lpVtbl -> put_Allocate(This,newVal)

#define IFtp_get_Directory(This,pVal)	\
    (This)->lpVtbl -> get_Directory(This,pVal)

#define IFtp_put_Directory(This,newval)	\
    (This)->lpVtbl -> put_Directory(This,newval)

#define IFtp_get_FileStructure(This,pVal)	\
    (This)->lpVtbl -> get_FileStructure(This,pVal)

#define IFtp_put_FileStructure(This,newVal)	\
    (This)->lpVtbl -> put_FileStructure(This,newVal)

#define IFtp_get_Listing(This,pVal)	\
    (This)->lpVtbl -> get_Listing(This,pVal)

#define IFtp_put_Listing(This,newVal)	\
    (This)->lpVtbl -> put_Listing(This,newVal)

#define IFtp_get_Passive(This,pVal)	\
    (This)->lpVtbl -> get_Passive(This,pVal)

#define IFtp_put_Passive(This,newVal)	\
    (This)->lpVtbl -> put_Passive(This,newVal)

#define IFtp_get_StoreType(This,pVal)	\
    (This)->lpVtbl -> get_StoreType(This,pVal)

#define IFtp_put_StoreType(This,newVal)	\
    (This)->lpVtbl -> put_StoreType(This,newVal)

#define IFtp_get_TimeOut(This,pVal)	\
    (This)->lpVtbl -> get_TimeOut(This,pVal)

#define IFtp_put_TimeOut(This,newVal)	\
    (This)->lpVtbl -> put_TimeOut(This,newVal)

#define IFtp_get_TransferMode(This,pVal)	\
    (This)->lpVtbl -> get_TransferMode(This,pVal)

#define IFtp_put_TransferMode(This,newVal)	\
    (This)->lpVtbl -> put_TransferMode(This,newVal)

#define IFtp_get_Type(This,pVal)	\
    (This)->lpVtbl -> get_Type(This,pVal)

#define IFtp_put_Type(This,newVal)	\
    (This)->lpVtbl -> put_Type(This,newVal)

#define IFtp_get_Blocked(This,pVal)	\
    (This)->lpVtbl -> get_Blocked(This,pVal)

#define IFtp_get_LocalAddress(This,pVal)	\
    (This)->lpVtbl -> get_LocalAddress(This,pVal)

#define IFtp_get_LocalPort(This,pVal)	\
    (This)->lpVtbl -> get_LocalPort(This,pVal)

#define IFtp_get_RemoteAddress(This,pVal)	\
    (This)->lpVtbl -> get_RemoteAddress(This,pVal)

#define IFtp_get_RemotePort(This,pVal)	\
    (This)->lpVtbl -> get_RemotePort(This,pVal)

#define IFtp_get_Restart(This,pVal)	\
    (This)->lpVtbl -> get_Restart(This,pVal)

#define IFtp_get_State(This,pVal)	\
    (This)->lpVtbl -> get_State(This,pVal)

#define IFtp_get_System(This,pVal)	\
    (This)->lpVtbl -> get_System(This,pVal)

#define IFtp_About(This)	\
    (This)->lpVtbl -> About(This)

#define IFtp_Abort(This)	\
    (This)->lpVtbl -> Abort(This)

#define IFtp_AbortCommand(This)	\
    (This)->lpVtbl -> AbortCommand(This)

#define IFtp_ChangeDirectoryUp(This)	\
    (This)->lpVtbl -> ChangeDirectoryUp(This)

#define IFtp_Command(This,FtpCommand,Result)	\
    (This)->lpVtbl -> Command(This,FtpCommand,Result)

#define IFtp_Trace(This,Result,Send,Receive,SendPrompt,ReceivePrompt)	\
    (This)->lpVtbl -> Trace(This,Result,Send,Receive,SendPrompt,ReceivePrompt)

#define IFtp_Delete(This,PathName)	\
    (This)->lpVtbl -> Delete(This,PathName)

#define IFtp_Help(This,Result,Command)	\
    (This)->lpVtbl -> Help(This,Result,Command)

#define IFtp_List(This,PathName)	\
    (This)->lpVtbl -> List(This,PathName)

#define IFtp_Login(This,RemoteName,User,Password,Account,RemotePort)	\
    (This)->lpVtbl -> Login(This,RemoteName,User,Password,Account,RemotePort)

#define IFtp_Logout(This)	\
    (This)->lpVtbl -> Logout(This)

#define IFtp_MakeDirectory(This,PathName)	\
    (This)->lpVtbl -> MakeDirectory(This,PathName)

#define IFtp_NameList(This,PathName)	\
    (This)->lpVtbl -> NameList(This,PathName)

#define IFtp_NoOperation(This)	\
    (This)->lpVtbl -> NoOperation(This)

#define IFtp_RemoveDirectory(This,PathName)	\
    (This)->lpVtbl -> RemoveDirectory(This,PathName)

#define IFtp_Rename(This,FromFileName,ToFileName)	\
    (This)->lpVtbl -> Rename(This,FromFileName,ToFileName)

#define IFtp_Retrieve(This,RemoteFileName,Result,Marker)	\
    (This)->lpVtbl -> Retrieve(This,RemoteFileName,Result,Marker)

#define IFtp_Site(This,Modifier,Result)	\
    (This)->lpVtbl -> Site(This,Modifier,Result)

#define IFtp_Status(This,Result,PathName)	\
    (This)->lpVtbl -> Status(This,Result,PathName)

#define IFtp_Store(This,RemoteFileName,Data,Marker)	\
    (This)->lpVtbl -> Store(This,RemoteFileName,Data,Marker)

#define IFtp_StructureMount(This,PathName)	\
    (This)->lpVtbl -> StructureMount(This,PathName)

#define IFtp_Get(This,Url,Result,Marker)	\
    (This)->lpVtbl -> Get(This,Url,Result,Marker)

#define IFtp_Put(This,Url,Source,Marker)	\
    (This)->lpVtbl -> Put(This,Url,Source,Marker)

#define IFtp_MGet(This,Source,Destination,FilesTransferred,FileErrors)	\
    (This)->lpVtbl -> MGet(This,Source,Destination,FilesTransferred,FileErrors)

#define IFtp_MPut(This,Source,Destination,FilesTransferred,FileErrors)	\
    (This)->lpVtbl -> MPut(This,Source,Destination,FilesTransferred,FileErrors)

#define IFtp_get_ProxyType(This,pVal)	\
    (This)->lpVtbl -> get_ProxyType(This,pVal)

#define IFtp_put_ProxyType(This,newVal)	\
    (This)->lpVtbl -> put_ProxyType(This,newVal)

#define IFtp_get_ProxyHost(This,pVal)	\
    (This)->lpVtbl -> get_ProxyHost(This,pVal)

#define IFtp_put_ProxyHost(This,newVal)	\
    (This)->lpVtbl -> put_ProxyHost(This,newVal)

#define IFtp_get_ProxyUsername(This,pVal)	\
    (This)->lpVtbl -> get_ProxyUsername(This,pVal)

#define IFtp_put_ProxyUsername(This,newVal)	\
    (This)->lpVtbl -> put_ProxyUsername(This,newVal)

#define IFtp_get_ProxyPassword(This,pVal)	\
    (This)->lpVtbl -> get_ProxyPassword(This,pVal)

#define IFtp_put_ProxyPassword(This,newVal)	\
    (This)->lpVtbl -> put_ProxyPassword(This,newVal)

#define IFtp_get_ProxyPort(This,pVal)	\
    (This)->lpVtbl -> get_ProxyPort(This,pVal)

#define IFtp_put_ProxyPort(This,newVal)	\
    (This)->lpVtbl -> put_ProxyPort(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFtp_get_Allocate_Proxy( 
    IFtp __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IFtp_get_Allocate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFtp_put_Allocate_Proxy( 
    IFtp __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IFtp_put_Allocate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFtp_get_Directory_Proxy( 
    IFtp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IFtp_get_Directory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFtp_put_Directory_Proxy( 
    IFtp __RPC_FAR * This,
    /* [in] */ BSTR newval);


void __RPC_STUB IFtp_put_Directory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFtp_get_FileStructure_Proxy( 
    IFtp __RPC_FAR * This,
    /* [retval][out] */ FileStructureConstants __RPC_FAR *pVal);


void __RPC_STUB IFtp_get_FileStructure_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFtp_put_FileStructure_Proxy( 
    IFtp __RPC_FAR * This,
    /* [in] */ FileStructureConstants newVal);


void __RPC_STUB IFtp_put_FileStructure_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFtp_get_Listing_Proxy( 
    IFtp __RPC_FAR * This,
    /* [retval][out] */ LPLISTENTRIES __RPC_FAR *pVal);


void __RPC_STUB IFtp_get_Listing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFtp_put_Listing_Proxy( 
    IFtp __RPC_FAR * This,
    /* [in] */ IListEntries __RPC_FAR *newVal);


void __RPC_STUB IFtp_put_Listing_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFtp_get_Passive_Proxy( 
    IFtp __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IFtp_get_Passive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFtp_put_Passive_Proxy( 
    IFtp __RPC_FAR * This,
    /* [in] */ VARIANT_BOOL newVal);


void __RPC_STUB IFtp_put_Passive_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFtp_get_StoreType_Proxy( 
    IFtp __RPC_FAR * This,
    /* [retval][out] */ StoreConstants __RPC_FAR *pVal);


void __RPC_STUB IFtp_get_StoreType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFtp_put_StoreType_Proxy( 
    IFtp __RPC_FAR * This,
    /* [in] */ StoreConstants newVal);


void __RPC_STUB IFtp_put_StoreType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFtp_get_TimeOut_Proxy( 
    IFtp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IFtp_get_TimeOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFtp_put_TimeOut_Proxy( 
    IFtp __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IFtp_put_TimeOut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFtp_get_TransferMode_Proxy( 
    IFtp __RPC_FAR * This,
    /* [retval][out] */ TransferModeConstants __RPC_FAR *pVal);


void __RPC_STUB IFtp_get_TransferMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFtp_put_TransferMode_Proxy( 
    IFtp __RPC_FAR * This,
    /* [in] */ TransferModeConstants newVal);


void __RPC_STUB IFtp_put_TransferMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFtp_get_Type_Proxy( 
    IFtp __RPC_FAR * This,
    /* [retval][out] */ TypeConstants __RPC_FAR *pVal);


void __RPC_STUB IFtp_get_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFtp_put_Type_Proxy( 
    IFtp __RPC_FAR * This,
    /* [in] */ TypeConstants newVal);


void __RPC_STUB IFtp_put_Type_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFtp_get_Blocked_Proxy( 
    IFtp __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IFtp_get_Blocked_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFtp_get_LocalAddress_Proxy( 
    IFtp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IFtp_get_LocalAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFtp_get_LocalPort_Proxy( 
    IFtp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IFtp_get_LocalPort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFtp_get_RemoteAddress_Proxy( 
    IFtp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IFtp_get_RemoteAddress_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFtp_get_RemotePort_Proxy( 
    IFtp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IFtp_get_RemotePort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFtp_get_Restart_Proxy( 
    IFtp __RPC_FAR * This,
    /* [retval][out] */ VARIANT_BOOL __RPC_FAR *pVal);


void __RPC_STUB IFtp_get_Restart_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFtp_get_State_Proxy( 
    IFtp __RPC_FAR * This,
    /* [retval][out] */ StateConstants __RPC_FAR *pVal);


void __RPC_STUB IFtp_get_State_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFtp_get_System_Proxy( 
    IFtp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IFtp_get_System_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IFtp_About_Proxy( 
    IFtp __RPC_FAR * This);


void __RPC_STUB IFtp_About_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IFtp_Abort_Proxy( 
    IFtp __RPC_FAR * This);


void __RPC_STUB IFtp_Abort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IFtp_AbortCommand_Proxy( 
    IFtp __RPC_FAR * This);


void __RPC_STUB IFtp_AbortCommand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IFtp_ChangeDirectoryUp_Proxy( 
    IFtp __RPC_FAR * This);


void __RPC_STUB IFtp_ChangeDirectoryUp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IFtp_Command_Proxy( 
    IFtp __RPC_FAR * This,
    /* [in] */ BSTR FtpCommand,
    VARIANT __RPC_FAR *Result);


void __RPC_STUB IFtp_Command_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IFtp_Trace_Proxy( 
    IFtp __RPC_FAR * This,
    /* [out][in][optional] */ VARIANT __RPC_FAR *Result,
    /* [optional] */ VARIANT_BOOL Send,
    /* [optional] */ VARIANT_BOOL Receive,
    /* [optional] */ BSTR SendPrompt,
    /* [optional] */ BSTR ReceivePrompt);


void __RPC_STUB IFtp_Trace_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IFtp_Delete_Proxy( 
    IFtp __RPC_FAR * This,
    /* [in] */ BSTR PathName);


void __RPC_STUB IFtp_Delete_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IFtp_Help_Proxy( 
    IFtp __RPC_FAR * This,
    VARIANT __RPC_FAR *Result,
    /* [optional][in] */ BSTR Command);


void __RPC_STUB IFtp_Help_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IFtp_List_Proxy( 
    IFtp __RPC_FAR * This,
    /* [optional][in] */ BSTR PathName);


void __RPC_STUB IFtp_List_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IFtp_Login_Proxy( 
    IFtp __RPC_FAR * This,
    /* [optional][in] */ BSTR RemoteName,
    /* [optional][in] */ BSTR User,
    /* [optional][in] */ BSTR Password,
    /* [optional][in] */ BSTR Account,
    /* [optional][in] */ long RemotePort);


void __RPC_STUB IFtp_Login_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IFtp_Logout_Proxy( 
    IFtp __RPC_FAR * This);


void __RPC_STUB IFtp_Logout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IFtp_MakeDirectory_Proxy( 
    IFtp __RPC_FAR * This,
    /* [in] */ BSTR PathName);


void __RPC_STUB IFtp_MakeDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IFtp_NameList_Proxy( 
    IFtp __RPC_FAR * This,
    /* [optional][in] */ BSTR PathName);


void __RPC_STUB IFtp_NameList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IFtp_NoOperation_Proxy( 
    IFtp __RPC_FAR * This);


void __RPC_STUB IFtp_NoOperation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IFtp_RemoveDirectory_Proxy( 
    IFtp __RPC_FAR * This,
    /* [in] */ BSTR PathName);


void __RPC_STUB IFtp_RemoveDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IFtp_Rename_Proxy( 
    IFtp __RPC_FAR * This,
    /* [in] */ BSTR FromFileName,
    /* [in] */ BSTR ToFileName);


void __RPC_STUB IFtp_Rename_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IFtp_Retrieve_Proxy( 
    IFtp __RPC_FAR * This,
    /* [in] */ BSTR RemoteFileName,
    /* [optional][out][in] */ VARIANT __RPC_FAR *Result,
    /* [optional][in] */ long Marker);


void __RPC_STUB IFtp_Retrieve_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IFtp_Site_Proxy( 
    IFtp __RPC_FAR * This,
    /* [in] */ BSTR Modifier,
    VARIANT __RPC_FAR *Result);


void __RPC_STUB IFtp_Site_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IFtp_Status_Proxy( 
    IFtp __RPC_FAR * This,
    VARIANT __RPC_FAR *Result,
    /* [optional][in] */ BSTR PathName);


void __RPC_STUB IFtp_Status_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IFtp_Store_Proxy( 
    IFtp __RPC_FAR * This,
    /* [in] */ BSTR RemoteFileName,
    /* [optional][in] */ VARIANT Data,
    /* [optional][in] */ long Marker);


void __RPC_STUB IFtp_Store_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IFtp_StructureMount_Proxy( 
    IFtp __RPC_FAR * This,
    /* [in] */ BSTR PathName);


void __RPC_STUB IFtp_StructureMount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IFtp_Get_Proxy( 
    IFtp __RPC_FAR * This,
    /* [in] */ BSTR Url,
    /* [optional][out][in] */ VARIANT __RPC_FAR *Result,
    /* [optional][in] */ long Marker);


void __RPC_STUB IFtp_Get_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IFtp_Put_Proxy( 
    IFtp __RPC_FAR * This,
    /* [in] */ BSTR Url,
    /* [optional][in] */ VARIANT Source,
    /* [optional][in] */ long Marker);


void __RPC_STUB IFtp_Put_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IFtp_MGet_Proxy( 
    IFtp __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Source,
    /* [defaultvalue][optional][in] */ BSTR Destination,
    /* [optional][in] */ VARIANT FilesTransferred,
    /* [optional][in] */ VARIANT FileErrors);


void __RPC_STUB IFtp_MGet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id] */ HRESULT STDMETHODCALLTYPE IFtp_MPut_Proxy( 
    IFtp __RPC_FAR * This,
    /* [defaultvalue][optional][in] */ BSTR Source,
    /* [defaultvalue][optional][in] */ BSTR Destination,
    /* [optional][in] */ VARIANT FilesTransferred,
    /* [optional][in] */ VARIANT FileErrors);


void __RPC_STUB IFtp_MPut_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFtp_get_ProxyType_Proxy( 
    IFtp __RPC_FAR * This,
    /* [retval][out] */ FtpProxyTypeConstants __RPC_FAR *pVal);


void __RPC_STUB IFtp_get_ProxyType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFtp_put_ProxyType_Proxy( 
    IFtp __RPC_FAR * This,
    /* [in] */ FtpProxyTypeConstants newVal);


void __RPC_STUB IFtp_put_ProxyType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFtp_get_ProxyHost_Proxy( 
    IFtp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IFtp_get_ProxyHost_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFtp_put_ProxyHost_Proxy( 
    IFtp __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IFtp_put_ProxyHost_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFtp_get_ProxyUsername_Proxy( 
    IFtp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IFtp_get_ProxyUsername_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFtp_put_ProxyUsername_Proxy( 
    IFtp __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IFtp_put_ProxyUsername_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFtp_get_ProxyPassword_Proxy( 
    IFtp __RPC_FAR * This,
    /* [retval][out] */ BSTR __RPC_FAR *pVal);


void __RPC_STUB IFtp_get_ProxyPassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFtp_put_ProxyPassword_Proxy( 
    IFtp __RPC_FAR * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IFtp_put_ProxyPassword_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpcontext][helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IFtp_get_ProxyPort_Proxy( 
    IFtp __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *pVal);


void __RPC_STUB IFtp_get_ProxyPort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [nonbrowsable][helpcontext][helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IFtp_put_ProxyPort_Proxy( 
    IFtp __RPC_FAR * This,
    /* [in] */ long newVal);


void __RPC_STUB IFtp_put_ProxyPort_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IFtp_INTERFACE_DEFINED__ */


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
