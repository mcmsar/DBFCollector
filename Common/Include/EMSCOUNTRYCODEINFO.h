/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Jul 12 10:00:08 2006
 */
/* Compiler settings for ..\Common\Include\EMSCOUNTRYCODEINFO.IDL:
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

#ifndef __EMSCOUNTRYCODEINFO_h__
#define __EMSCOUNTRYCODEINFO_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSCountryCodeInfo_FWD_DEFINED__
#define __IEMSCountryCodeInfo_FWD_DEFINED__
typedef interface IEMSCountryCodeInfo IEMSCountryCodeInfo;
#endif 	/* __IEMSCountryCodeInfo_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "emsicfg.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_EMSCOUNTRYCODEINFO_0000 */
/* [local] */ 

/*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
#ifndef _EMS_COUNTRYCODE_INFO_H_
#define _EMS_COUNTRYCODE_INFO_H_
// {47577AD0-BB0E-4d14-B473-6A7D0C267F2D}
DEFINE_GUID(CLSID_EMSCountryCodeInfo, 0x47577ad0, 0xbb0e, 0x4d14, 0xb4, 0x73, 0x6a, 0x7d, 0xc, 0x26, 0x7f, 0x2d);
// {C40A2427-F7BC-4671-9CEF-C16B136024C0}
DEFINE_GUID(IID_IEMSCountryCodeInfo, 0xc40a2427, 0xf7bc, 0x4671, 0x9c, 0xef, 0xc1, 0x6b, 0x13, 0x60, 0x24, 0xc0); 
 
#define MAX_LONG_COUNTRY_NAME_LEN	10
#define MAX_SHORT_COUNTRY_NAME_LEN	3
 
typedef struct  _tagEMSCOUNTRYCODEINFO
    {
    wchar_t wszLongName[ 11 ];
    wchar_t wszShortName[ 4 ];
    ULONG ulCode;
    }	EMSCOUNTRYCODEINFO;

 
// This info should come from the schema but for now ... 
#define MIN_COUNTRY_CODE_VALUE 200 
#define MAX_COUNTRY_CODE_VALUE 780 
 
typedef 
enum _tagCOUNTRYNAMETYPE
    {	COUNTRYNAME_MIN	= 0,
	COUNTRYNAME_UNKNOWN	= 0,
	COUNTRYNAME_LONG	= 1,
	COUNTRYNAME_SHORT	= 2,
	COUNTRYNAME_MAX	= 3
    }	COUNTRYNAMETYPE;

#define VALID_COUNTRYNAMETYPE(x) (COUNTRYNAME_MIN <= x && COUNTRYNAME_MAX >= x)
 


extern RPC_IF_HANDLE __MIDL_itf_EMSCOUNTRYCODEINFO_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSCOUNTRYCODEINFO_0000_v0_0_s_ifspec;

#ifndef __IEMSCountryCodeInfo_INTERFACE_DEFINED__
#define __IEMSCountryCodeInfo_INTERFACE_DEFINED__

/* interface IEMSCountryCodeInfo */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSCountryCodeInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C40A2427-F7BC-4671-9CEF-C16B136024C0")
    IEMSCountryCodeInfo : public IEMSConfigSettings
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetCountryName( 
            /* [in] */ const ULONG culCode,
            /* [in] */ const COUNTRYNAMETYPE ceNameType,
            /* [out] */ BSTR __RPC_FAR *pbszName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE IsValidCountryCode( 
            /* [in] */ const ULONG culCode,
            /* [out] */ BOOL __RPC_FAR *pbValid) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSCountryCodeInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSCountryCodeInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSCountryCodeInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSCountryCodeInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfigFlags )( 
            IEMSCountryCodeInfo __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigFlags )( 
            IEMSCountryCodeInfo __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *lpdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReloadConfigData )( 
            IEMSCountryCodeInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfigValueA )( 
            IEMSCountryCodeInfo __RPC_FAR * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [string][in] */ LPCSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigValueA )( 
            IEMSCountryCodeInfo __RPC_FAR * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [length_is][size_is][out] */ unsigned char __RPC_FAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG __RPC_FAR *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfigValueW )( 
            IEMSCountryCodeInfo __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [string][in] */ LPCWSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigValueW )( 
            IEMSCountryCodeInfo __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [length_is][size_is][out] */ WCHAR __RPC_FAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG __RPC_FAR *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCountryName )( 
            IEMSCountryCodeInfo __RPC_FAR * This,
            /* [in] */ const ULONG culCode,
            /* [in] */ const COUNTRYNAMETYPE ceNameType,
            /* [out] */ BSTR __RPC_FAR *pbszName);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *IsValidCountryCode )( 
            IEMSCountryCodeInfo __RPC_FAR * This,
            /* [in] */ const ULONG culCode,
            /* [out] */ BOOL __RPC_FAR *pbValid);
        
        END_INTERFACE
    } IEMSCountryCodeInfoVtbl;

    interface IEMSCountryCodeInfo
    {
        CONST_VTBL struct IEMSCountryCodeInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSCountryCodeInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSCountryCodeInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSCountryCodeInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSCountryCodeInfo_SetConfigFlags(This,dwFlags)	\
    (This)->lpVtbl -> SetConfigFlags(This,dwFlags)

#define IEMSCountryCodeInfo_GetConfigFlags(This,lpdwFlags)	\
    (This)->lpVtbl -> GetConfigFlags(This,lpdwFlags)

#define IEMSCountryCodeInfo_ReloadConfigData(This)	\
    (This)->lpVtbl -> ReloadConfigData(This)

#define IEMSCountryCodeInfo_SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)	\
    (This)->lpVtbl -> SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)

#define IEMSCountryCodeInfo_GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    (This)->lpVtbl -> GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)

#define IEMSCountryCodeInfo_SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)	\
    (This)->lpVtbl -> SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)

#define IEMSCountryCodeInfo_GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    (This)->lpVtbl -> GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)


#define IEMSCountryCodeInfo_GetCountryName(This,culCode,ceNameType,pbszName)	\
    (This)->lpVtbl -> GetCountryName(This,culCode,ceNameType,pbszName)

#define IEMSCountryCodeInfo_IsValidCountryCode(This,culCode,pbValid)	\
    (This)->lpVtbl -> IsValidCountryCode(This,culCode,pbValid)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSCountryCodeInfo_GetCountryName_Proxy( 
    IEMSCountryCodeInfo __RPC_FAR * This,
    /* [in] */ const ULONG culCode,
    /* [in] */ const COUNTRYNAMETYPE ceNameType,
    /* [out] */ BSTR __RPC_FAR *pbszName);


void __RPC_STUB IEMSCountryCodeInfo_GetCountryName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSCountryCodeInfo_IsValidCountryCode_Proxy( 
    IEMSCountryCodeInfo __RPC_FAR * This,
    /* [in] */ const ULONG culCode,
    /* [out] */ BOOL __RPC_FAR *pbValid);


void __RPC_STUB IEMSCountryCodeInfo_IsValidCountryCode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSCountryCodeInfo_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSCOUNTRYCODEINFO_0015 */
/* [local] */ 

#endif //_EMS_COUNTRYCODE_INFO_H_


extern RPC_IF_HANDLE __MIDL_itf_EMSCOUNTRYCODEINFO_0015_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSCOUNTRYCODEINFO_0015_v0_0_s_ifspec;

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
