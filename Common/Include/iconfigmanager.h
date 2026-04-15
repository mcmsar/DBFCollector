
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Wed Nov 05 15:54:21 2003
 */
/* Compiler settings for iconfigmanager.idl:
    Os, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
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

#ifndef __iconfigmanager_h__
#define __iconfigmanager_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IEMSConfigurationManager_FWD_DEFINED__
#define __IEMSConfigurationManager_FWD_DEFINED__
typedef interface IEMSConfigurationManager IEMSConfigurationManager;
#endif 	/* __IEMSConfigurationManager_FWD_DEFINED__ */


#ifndef __IEMSConfigurationManagerSec_FWD_DEFINED__
#define __IEMSConfigurationManagerSec_FWD_DEFINED__
typedef interface IEMSConfigurationManagerSec IEMSConfigurationManagerSec;
#endif 	/* __IEMSConfigurationManagerSec_FWD_DEFINED__ */


#ifndef __EMSConfigurationManager_FWD_DEFINED__
#define __EMSConfigurationManager_FWD_DEFINED__

#ifdef __cplusplus
typedef class EMSConfigurationManager EMSConfigurationManager;
#else
typedef struct EMSConfigurationManager EMSConfigurationManager;
#endif /* __cplusplus */

#endif 	/* __EMSConfigurationManager_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "configmanagertypes.h"
#include "emsauthorization.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_iconfigmanager_0000 */
/* [local] */ 

// {8D31C737-0DE2-4e26-AF07-B49A1B5D4DDE}
DEFINE_GUID(CLSID_EMSConfigurationManager, 0x8d31c737, 0xde2, 0x4e26, 0xaf, 0x7, 0xb4, 0x9a, 0x1b, 0x5d, 0x4d, 0xde);
 
// {A46A208B-797C-4626-9DB3-434A8FF21D81}
DEFINE_GUID(IID_IEMSConfigurationManager, 0xa46a208b, 0x797c, 0x4626, 0x9d, 0xb3, 0x43, 0x4a, 0x8f, 0xf2, 0x1d, 0x81);
 
// {41E06ED4-1247-439a-A20B-61F4575E7783}
DEFINE_GUID(IID_IEMSConfigurationManagerSec, 0x41e06ed4, 0x1247, 0x439a, 0xa2, 0xb, 0x61, 0xf4, 0x57, 0x5e, 0x77, 0x83);
 
// constant declarations:
 
const wchar_t c_pwcsNoGroupID[] = L"";


extern RPC_IF_HANDLE __MIDL_itf_iconfigmanager_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_iconfigmanager_0000_v0_0_s_ifspec;

#ifndef __IEMSConfigurationManager_INTERFACE_DEFINED__
#define __IEMSConfigurationManager_INTERFACE_DEFINED__

/* interface IEMSConfigurationManager */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSConfigurationManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A46A208B-797C-4626-9DB3-434A8FF21D81")
    IEMSConfigurationManager : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetGroupTypes( 
            /* [out] */ int *pCount,
            /* [size_is][size_is][string][out] */ wchar_t ***ppaGroupTypes) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetGroupIDs( 
            /* [string][in] */ const wchar_t *pwcsGroupType,
            /* [out] */ int *pCount,
            /* [size_is][size_is][string][out] */ wchar_t ***ppaGroupIDs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Get( 
            /* [string][in] */ const wchar_t *pwcsGroupType,
            /* [string][in] */ const wchar_t *pwcsGroupID,
            /* [string][in] */ const wchar_t *pwcsKeyName,
            /* [out] */ EMSVARITYPE *pValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEx( 
            /* [string][in] */ const wchar_t *pwcsGroupType,
            /* [string][in] */ const wchar_t *pwcsGroupID,
            /* [size_is][string][in] */ const wchar_t **pawcsKeyNames,
            /* [in] */ int count,
            /* [size_is][out][in] */ EMSCONFIGURATIONITEM aValues[  ],
            /* [retval][out] */ int *pResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetGroup( 
            /* [string][in] */ const wchar_t *pwcsGroupType,
            /* [string][in] */ const wchar_t *pwcsGroupID,
            /* [out] */ int *pCount,
            /* [size_is][size_is][out] */ EMSCONFIGURATIONITEM ***ppaValues) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetKeyTime( 
            /* [string][in] */ const wchar_t *pwcsGroupType,
            /* [string][in] */ const wchar_t *pwcsGroupID,
            /* [string][in] */ const wchar_t *pwcsKeyName,
            /* [out] */ EMSTIME *pTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Set( 
            /* [string][in] */ const wchar_t *pwcsGroupType,
            /* [string][in] */ const wchar_t *pwcsGroupID,
            /* [string][in] */ const wchar_t *pwcsKeyName,
            /* [in] */ EMSVARITYPE value) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetString( 
            /* [string][in] */ const wchar_t *pwcsGroupType,
            /* [string][in] */ const wchar_t *pwcsGroupID,
            /* [string][in] */ const wchar_t *pwcsKeyName,
            /* [string][in] */ const wchar_t *pwcsValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetEx( 
            /* [string][in] */ const wchar_t *pwcsGroupType,
            /* [string][in] */ const wchar_t *pwcsGroupID,
            /* [in] */ int count,
            /* [size_is][in] */ EMSCONFIGURATIONITEM aKeyValuePairs[  ]) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSConfigurationManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEMSConfigurationManager * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEMSConfigurationManager * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEMSConfigurationManager * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetGroupTypes )( 
            IEMSConfigurationManager * This,
            /* [out] */ int *pCount,
            /* [size_is][size_is][string][out] */ wchar_t ***ppaGroupTypes);
        
        HRESULT ( STDMETHODCALLTYPE *GetGroupIDs )( 
            IEMSConfigurationManager * This,
            /* [string][in] */ const wchar_t *pwcsGroupType,
            /* [out] */ int *pCount,
            /* [size_is][size_is][string][out] */ wchar_t ***ppaGroupIDs);
        
        HRESULT ( STDMETHODCALLTYPE *Get )( 
            IEMSConfigurationManager * This,
            /* [string][in] */ const wchar_t *pwcsGroupType,
            /* [string][in] */ const wchar_t *pwcsGroupID,
            /* [string][in] */ const wchar_t *pwcsKeyName,
            /* [out] */ EMSVARITYPE *pValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetEx )( 
            IEMSConfigurationManager * This,
            /* [string][in] */ const wchar_t *pwcsGroupType,
            /* [string][in] */ const wchar_t *pwcsGroupID,
            /* [size_is][string][in] */ const wchar_t **pawcsKeyNames,
            /* [in] */ int count,
            /* [size_is][out][in] */ EMSCONFIGURATIONITEM aValues[  ],
            /* [retval][out] */ int *pResult);
        
        HRESULT ( STDMETHODCALLTYPE *GetGroup )( 
            IEMSConfigurationManager * This,
            /* [string][in] */ const wchar_t *pwcsGroupType,
            /* [string][in] */ const wchar_t *pwcsGroupID,
            /* [out] */ int *pCount,
            /* [size_is][size_is][out] */ EMSCONFIGURATIONITEM ***ppaValues);
        
        HRESULT ( STDMETHODCALLTYPE *GetKeyTime )( 
            IEMSConfigurationManager * This,
            /* [string][in] */ const wchar_t *pwcsGroupType,
            /* [string][in] */ const wchar_t *pwcsGroupID,
            /* [string][in] */ const wchar_t *pwcsKeyName,
            /* [out] */ EMSTIME *pTime);
        
        HRESULT ( STDMETHODCALLTYPE *Set )( 
            IEMSConfigurationManager * This,
            /* [string][in] */ const wchar_t *pwcsGroupType,
            /* [string][in] */ const wchar_t *pwcsGroupID,
            /* [string][in] */ const wchar_t *pwcsKeyName,
            /* [in] */ EMSVARITYPE value);
        
        HRESULT ( STDMETHODCALLTYPE *SetString )( 
            IEMSConfigurationManager * This,
            /* [string][in] */ const wchar_t *pwcsGroupType,
            /* [string][in] */ const wchar_t *pwcsGroupID,
            /* [string][in] */ const wchar_t *pwcsKeyName,
            /* [string][in] */ const wchar_t *pwcsValue);
        
        HRESULT ( STDMETHODCALLTYPE *SetEx )( 
            IEMSConfigurationManager * This,
            /* [string][in] */ const wchar_t *pwcsGroupType,
            /* [string][in] */ const wchar_t *pwcsGroupID,
            /* [in] */ int count,
            /* [size_is][in] */ EMSCONFIGURATIONITEM aKeyValuePairs[  ]);
        
        END_INTERFACE
    } IEMSConfigurationManagerVtbl;

    interface IEMSConfigurationManager
    {
        CONST_VTBL struct IEMSConfigurationManagerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSConfigurationManager_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSConfigurationManager_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSConfigurationManager_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSConfigurationManager_GetGroupTypes(This,pCount,ppaGroupTypes)	\
    (This)->lpVtbl -> GetGroupTypes(This,pCount,ppaGroupTypes)

#define IEMSConfigurationManager_GetGroupIDs(This,pwcsGroupType,pCount,ppaGroupIDs)	\
    (This)->lpVtbl -> GetGroupIDs(This,pwcsGroupType,pCount,ppaGroupIDs)

#define IEMSConfigurationManager_Get(This,pwcsGroupType,pwcsGroupID,pwcsKeyName,pValue)	\
    (This)->lpVtbl -> Get(This,pwcsGroupType,pwcsGroupID,pwcsKeyName,pValue)

#define IEMSConfigurationManager_GetEx(This,pwcsGroupType,pwcsGroupID,pawcsKeyNames,count,aValues,pResult)	\
    (This)->lpVtbl -> GetEx(This,pwcsGroupType,pwcsGroupID,pawcsKeyNames,count,aValues,pResult)

#define IEMSConfigurationManager_GetGroup(This,pwcsGroupType,pwcsGroupID,pCount,ppaValues)	\
    (This)->lpVtbl -> GetGroup(This,pwcsGroupType,pwcsGroupID,pCount,ppaValues)

#define IEMSConfigurationManager_GetKeyTime(This,pwcsGroupType,pwcsGroupID,pwcsKeyName,pTime)	\
    (This)->lpVtbl -> GetKeyTime(This,pwcsGroupType,pwcsGroupID,pwcsKeyName,pTime)

#define IEMSConfigurationManager_Set(This,pwcsGroupType,pwcsGroupID,pwcsKeyName,value)	\
    (This)->lpVtbl -> Set(This,pwcsGroupType,pwcsGroupID,pwcsKeyName,value)

#define IEMSConfigurationManager_SetString(This,pwcsGroupType,pwcsGroupID,pwcsKeyName,pwcsValue)	\
    (This)->lpVtbl -> SetString(This,pwcsGroupType,pwcsGroupID,pwcsKeyName,pwcsValue)

#define IEMSConfigurationManager_SetEx(This,pwcsGroupType,pwcsGroupID,count,aKeyValuePairs)	\
    (This)->lpVtbl -> SetEx(This,pwcsGroupType,pwcsGroupID,count,aKeyValuePairs)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSConfigurationManager_GetGroupTypes_Proxy( 
    IEMSConfigurationManager * This,
    /* [out] */ int *pCount,
    /* [size_is][size_is][string][out] */ wchar_t ***ppaGroupTypes);


void __RPC_STUB IEMSConfigurationManager_GetGroupTypes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSConfigurationManager_GetGroupIDs_Proxy( 
    IEMSConfigurationManager * This,
    /* [string][in] */ const wchar_t *pwcsGroupType,
    /* [out] */ int *pCount,
    /* [size_is][size_is][string][out] */ wchar_t ***ppaGroupIDs);


void __RPC_STUB IEMSConfigurationManager_GetGroupIDs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSConfigurationManager_Get_Proxy( 
    IEMSConfigurationManager * This,
    /* [string][in] */ const wchar_t *pwcsGroupType,
    /* [string][in] */ const wchar_t *pwcsGroupID,
    /* [string][in] */ const wchar_t *pwcsKeyName,
    /* [out] */ EMSVARITYPE *pValue);


void __RPC_STUB IEMSConfigurationManager_Get_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSConfigurationManager_GetEx_Proxy( 
    IEMSConfigurationManager * This,
    /* [string][in] */ const wchar_t *pwcsGroupType,
    /* [string][in] */ const wchar_t *pwcsGroupID,
    /* [size_is][string][in] */ const wchar_t **pawcsKeyNames,
    /* [in] */ int count,
    /* [size_is][out][in] */ EMSCONFIGURATIONITEM aValues[  ],
    /* [retval][out] */ int *pResult);


void __RPC_STUB IEMSConfigurationManager_GetEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSConfigurationManager_GetGroup_Proxy( 
    IEMSConfigurationManager * This,
    /* [string][in] */ const wchar_t *pwcsGroupType,
    /* [string][in] */ const wchar_t *pwcsGroupID,
    /* [out] */ int *pCount,
    /* [size_is][size_is][out] */ EMSCONFIGURATIONITEM ***ppaValues);


void __RPC_STUB IEMSConfigurationManager_GetGroup_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSConfigurationManager_GetKeyTime_Proxy( 
    IEMSConfigurationManager * This,
    /* [string][in] */ const wchar_t *pwcsGroupType,
    /* [string][in] */ const wchar_t *pwcsGroupID,
    /* [string][in] */ const wchar_t *pwcsKeyName,
    /* [out] */ EMSTIME *pTime);


void __RPC_STUB IEMSConfigurationManager_GetKeyTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSConfigurationManager_Set_Proxy( 
    IEMSConfigurationManager * This,
    /* [string][in] */ const wchar_t *pwcsGroupType,
    /* [string][in] */ const wchar_t *pwcsGroupID,
    /* [string][in] */ const wchar_t *pwcsKeyName,
    /* [in] */ EMSVARITYPE value);


void __RPC_STUB IEMSConfigurationManager_Set_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSConfigurationManager_SetString_Proxy( 
    IEMSConfigurationManager * This,
    /* [string][in] */ const wchar_t *pwcsGroupType,
    /* [string][in] */ const wchar_t *pwcsGroupID,
    /* [string][in] */ const wchar_t *pwcsKeyName,
    /* [string][in] */ const wchar_t *pwcsValue);


void __RPC_STUB IEMSConfigurationManager_SetString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSConfigurationManager_SetEx_Proxy( 
    IEMSConfigurationManager * This,
    /* [string][in] */ const wchar_t *pwcsGroupType,
    /* [string][in] */ const wchar_t *pwcsGroupID,
    /* [in] */ int count,
    /* [size_is][in] */ EMSCONFIGURATIONITEM aKeyValuePairs[  ]);


void __RPC_STUB IEMSConfigurationManager_SetEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSConfigurationManager_INTERFACE_DEFINED__ */


#ifndef __IEMSConfigurationManagerSec_INTERFACE_DEFINED__
#define __IEMSConfigurationManagerSec_INTERFACE_DEFINED__

/* interface IEMSConfigurationManagerSec */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSConfigurationManagerSec;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("41E06ED4-1247-439a-A20B-61F4575E7783")
    IEMSConfigurationManagerSec : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Get( 
            /* [in] */ const EMSAUTHORIZATIONINFO *pIdentificationInfo,
            /* [string][in] */ const wchar_t *pwcsGroupType,
            /* [string][in] */ const wchar_t *pwcsGroupID,
            /* [string][in] */ const wchar_t *pwcsKeyName,
            /* [out] */ EMSVARITYPE *pValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetString( 
            /* [in] */ const EMSAUTHORIZATIONINFO *pIdentificationInfo,
            /* [string][in] */ const wchar_t *pwcsGroupType,
            /* [string][in] */ const wchar_t *pwcsGroupID,
            /* [string][in] */ const wchar_t *pwcsKeyName,
            /* [string][in] */ const wchar_t *pwcsValue) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSConfigurationManagerSecVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEMSConfigurationManagerSec * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEMSConfigurationManagerSec * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEMSConfigurationManagerSec * This);
        
        HRESULT ( STDMETHODCALLTYPE *Get )( 
            IEMSConfigurationManagerSec * This,
            /* [in] */ const EMSAUTHORIZATIONINFO *pIdentificationInfo,
            /* [string][in] */ const wchar_t *pwcsGroupType,
            /* [string][in] */ const wchar_t *pwcsGroupID,
            /* [string][in] */ const wchar_t *pwcsKeyName,
            /* [out] */ EMSVARITYPE *pValue);
        
        HRESULT ( STDMETHODCALLTYPE *SetString )( 
            IEMSConfigurationManagerSec * This,
            /* [in] */ const EMSAUTHORIZATIONINFO *pIdentificationInfo,
            /* [string][in] */ const wchar_t *pwcsGroupType,
            /* [string][in] */ const wchar_t *pwcsGroupID,
            /* [string][in] */ const wchar_t *pwcsKeyName,
            /* [string][in] */ const wchar_t *pwcsValue);
        
        END_INTERFACE
    } IEMSConfigurationManagerSecVtbl;

    interface IEMSConfigurationManagerSec
    {
        CONST_VTBL struct IEMSConfigurationManagerSecVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSConfigurationManagerSec_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSConfigurationManagerSec_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSConfigurationManagerSec_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSConfigurationManagerSec_Get(This,pIdentificationInfo,pwcsGroupType,pwcsGroupID,pwcsKeyName,pValue)	\
    (This)->lpVtbl -> Get(This,pIdentificationInfo,pwcsGroupType,pwcsGroupID,pwcsKeyName,pValue)

#define IEMSConfigurationManagerSec_SetString(This,pIdentificationInfo,pwcsGroupType,pwcsGroupID,pwcsKeyName,pwcsValue)	\
    (This)->lpVtbl -> SetString(This,pIdentificationInfo,pwcsGroupType,pwcsGroupID,pwcsKeyName,pwcsValue)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSConfigurationManagerSec_Get_Proxy( 
    IEMSConfigurationManagerSec * This,
    /* [in] */ const EMSAUTHORIZATIONINFO *pIdentificationInfo,
    /* [string][in] */ const wchar_t *pwcsGroupType,
    /* [string][in] */ const wchar_t *pwcsGroupID,
    /* [string][in] */ const wchar_t *pwcsKeyName,
    /* [out] */ EMSVARITYPE *pValue);


void __RPC_STUB IEMSConfigurationManagerSec_Get_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSConfigurationManagerSec_SetString_Proxy( 
    IEMSConfigurationManagerSec * This,
    /* [in] */ const EMSAUTHORIZATIONINFO *pIdentificationInfo,
    /* [string][in] */ const wchar_t *pwcsGroupType,
    /* [string][in] */ const wchar_t *pwcsGroupID,
    /* [string][in] */ const wchar_t *pwcsKeyName,
    /* [string][in] */ const wchar_t *pwcsValue);


void __RPC_STUB IEMSConfigurationManagerSec_SetString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSConfigurationManagerSec_INTERFACE_DEFINED__ */



#ifndef __SERVER2Lib_LIBRARY_DEFINED__
#define __SERVER2Lib_LIBRARY_DEFINED__

/* library SERVER2Lib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_SERVER2Lib;

EXTERN_C const CLSID CLSID_EMSConfigurationManager;

#ifdef __cplusplus

class DECLSPEC_UUID("8D31C737-0DE2-4e26-AF07-B49A1B5D4DDE")
EMSConfigurationManager;
#endif
#endif /* __SERVER2Lib_LIBRARY_DEFINED__ */

/* interface __MIDL_itf_iconfigmanager_0213 */
/* [local] */ 

typedef /* [unique] */ IEMSConfigurationManager *LPEMSCONFIGURATIONMANAGER;



extern RPC_IF_HANDLE __MIDL_itf_iconfigmanager_0213_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_iconfigmanager_0213_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


