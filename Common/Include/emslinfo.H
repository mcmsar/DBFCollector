/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Mar 18 13:20:37 2007
 */
/* Compiler settings for ..\common\Include\EMSLINFO.IDL:
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

#ifndef __EMSLINFO_h__
#define __EMSLINFO_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSLutInfo_FWD_DEFINED__
#define __IEMSLutInfo_FWD_DEFINED__
typedef interface IEMSLutInfo IEMSLutInfo;
#endif 	/* __IEMSLutInfo_FWD_DEFINED__ */


#ifndef __IEMSLutInfo2_FWD_DEFINED__
#define __IEMSLutInfo2_FWD_DEFINED__
typedef interface IEMSLutInfo2 IEMSLutInfo2;
#endif 	/* __IEMSLutInfo2_FWD_DEFINED__ */


#ifndef __IEMSLutInfo3_FWD_DEFINED__
#define __IEMSLutInfo3_FWD_DEFINED__
typedef interface IEMSLutInfo3 IEMSLutInfo3;
#endif 	/* __IEMSLutInfo3_FWD_DEFINED__ */


#ifndef __IEMSLutType_FWD_DEFINED__
#define __IEMSLutType_FWD_DEFINED__
typedef interface IEMSLutType IEMSLutType;
#endif 	/* __IEMSLutType_FWD_DEFINED__ */


#ifndef __IEMSTransfer_FWD_DEFINED__
#define __IEMSTransfer_FWD_DEFINED__
typedef interface IEMSTransfer IEMSTransfer;
#endif 	/* __IEMSTransfer_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "emsicfg.h"
#include "antennacfg.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_EMSLINFO_0000 */
/* [local] */ 

 
#include "emserror.h"
 
// {7FBD4401-4EDE-11d5-8BB6-009027912866}
DEFINE_GUID( CLSID_EMSLutInfo, 0x7fbd4401, 0x4ede, 0x11d5, 0x8b, 0xb6, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);
 
// {7FBD4402-4EDE-11d5-8BB6-009027912866}
DEFINE_GUID( IID_IEMSLutInfo, 0x7fbd4402, 0x4ede, 0x11d5, 0x8b, 0xb6, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);
 
// {612A6FA4-ED98-4fb2-87D0-BEF1EBC8608D}
DEFINE_GUID( IID_IEMSLutType, 0x612a6fa4, 0xed98, 0x4fb2, 0x87, 0xd0, 0xbe, 0xf1, 0xeb, 0xc8, 0x60, 0x8d);
// {CE11BC87-66F2-4c53-93C4-FB2E956EC1EF}
DEFINE_GUID(IID_IEMSTransfer, 0xce11bc87, 0x66f2, 0x4c53, 0x93, 0xc4, 0xfb, 0x2e, 0x95, 0x6e, 0xc1, 0xef);
 
// {0CE3EE4B-4D0C-47fd-91E6-97C59F95D632}
DEFINE_GUID( IID_IEMSLutInfo2, 0xce3ee4b, 0x4d0c, 0x47fd, 0x91, 0xe6, 0x97, 0xc5, 0x9f, 0x95, 0xd6, 0x32);
 
// {17676BA9-605F-493a-BB3A-F66BC4795418}
DEFINE_GUID( IID_IEMSLutInfo3, 0x17676ba9, 0x605f, 0x493a, 0xbb, 0x3a, 0xf6, 0x6b, 0xc4, 0x79, 0x54, 0x18);
 
typedef 
enum _tagEMSLUTTYPECODE
    {	EMSLut600Series	= 0x800,
	EMSLut500Series	= 0x400,
	EMSLutForeignSeries	= 0x200,
	EMSGeoLutType	= 0x80,
	EMSLeoLutType	= 0x40,
	EMSLutClopType	= 0x20,
	EMSOpIntType	= 0x10,
	EMSMeoLutType	= 0x1,
	EMSGeoLut600	= EMSLut600Series + EMSGeoLutType,
	EMSLeoLut600	= EMSLut600Series + EMSLeoLutType,
	EMSMeoLut600	= EMSLut600Series + EMSMeoLutType,
	EMSATLut500	= EMSLut500Series + EMSLeoLutType,
	EMSTSILeoLut	= EMSLutForeignSeries + EMSLeoLutType,
	EMSLutTypeUnknown	= 0
    }	EMSLUTTYPECODE;



extern RPC_IF_HANDLE __MIDL_itf_EMSLINFO_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSLINFO_0000_v0_0_s_ifspec;

#ifndef __IEMSLutInfo_INTERFACE_DEFINED__
#define __IEMSLutInfo_INTERFACE_DEFINED__

/* interface IEMSLutInfo */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSLutInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7FBD4402-4EDE-11d5-8BB6-009027912866")
    IEMSLutInfo : public IEMSConfigSettings
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetName( 
            /* [in] */ ULONG ulLutID,
            /* [length_is][size_is][out] */ unsigned char __RPC_FAR *pv,
            /* [in] */ ULONG cbMaxLength,
            /* [out] */ ULONG __RPC_FAR *pcbLength) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDescription( 
            /* [in] */ ULONG ulLutID,
            /* [length_is][size_is][out] */ unsigned char __RPC_FAR *pv,
            /* [in] */ ULONG cbMaxLength,
            /* [out] */ ULONG __RPC_FAR *pcbLength) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSiteLocation( 
            /* [in] */ ULONG ulLutID,
            /* [out] */ EMSLOCATION __RPC_FAR *lpLocation) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSiteProfile( 
            /* [in] */ ULONG ulLutID,
            /* [length_is][size_is][out] */ EMSAZEL __RPC_FAR *pAZEL,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbReturned) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSLutInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSLutInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSLutInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSLutInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfigFlags )( 
            IEMSLutInfo __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigFlags )( 
            IEMSLutInfo __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *lpdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReloadConfigData )( 
            IEMSLutInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfigValueA )( 
            IEMSLutInfo __RPC_FAR * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [string][in] */ LPCSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigValueA )( 
            IEMSLutInfo __RPC_FAR * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [length_is][size_is][out] */ unsigned char __RPC_FAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG __RPC_FAR *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfigValueW )( 
            IEMSLutInfo __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [string][in] */ LPCWSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigValueW )( 
            IEMSLutInfo __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [length_is][size_is][out] */ WCHAR __RPC_FAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG __RPC_FAR *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetName )( 
            IEMSLutInfo __RPC_FAR * This,
            /* [in] */ ULONG ulLutID,
            /* [length_is][size_is][out] */ unsigned char __RPC_FAR *pv,
            /* [in] */ ULONG cbMaxLength,
            /* [out] */ ULONG __RPC_FAR *pcbLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDescription )( 
            IEMSLutInfo __RPC_FAR * This,
            /* [in] */ ULONG ulLutID,
            /* [length_is][size_is][out] */ unsigned char __RPC_FAR *pv,
            /* [in] */ ULONG cbMaxLength,
            /* [out] */ ULONG __RPC_FAR *pcbLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSiteLocation )( 
            IEMSLutInfo __RPC_FAR * This,
            /* [in] */ ULONG ulLutID,
            /* [out] */ EMSLOCATION __RPC_FAR *lpLocation);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSiteProfile )( 
            IEMSLutInfo __RPC_FAR * This,
            /* [in] */ ULONG ulLutID,
            /* [length_is][size_is][out] */ EMSAZEL __RPC_FAR *pAZEL,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbReturned);
        
        END_INTERFACE
    } IEMSLutInfoVtbl;

    interface IEMSLutInfo
    {
        CONST_VTBL struct IEMSLutInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSLutInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSLutInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSLutInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSLutInfo_SetConfigFlags(This,dwFlags)	\
    (This)->lpVtbl -> SetConfigFlags(This,dwFlags)

#define IEMSLutInfo_GetConfigFlags(This,lpdwFlags)	\
    (This)->lpVtbl -> GetConfigFlags(This,lpdwFlags)

#define IEMSLutInfo_ReloadConfigData(This)	\
    (This)->lpVtbl -> ReloadConfigData(This)

#define IEMSLutInfo_SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)	\
    (This)->lpVtbl -> SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)

#define IEMSLutInfo_GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    (This)->lpVtbl -> GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)

#define IEMSLutInfo_SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)	\
    (This)->lpVtbl -> SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)

#define IEMSLutInfo_GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    (This)->lpVtbl -> GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)


#define IEMSLutInfo_GetName(This,ulLutID,pv,cbMaxLength,pcbLength)	\
    (This)->lpVtbl -> GetName(This,ulLutID,pv,cbMaxLength,pcbLength)

#define IEMSLutInfo_GetDescription(This,ulLutID,pv,cbMaxLength,pcbLength)	\
    (This)->lpVtbl -> GetDescription(This,ulLutID,pv,cbMaxLength,pcbLength)

#define IEMSLutInfo_GetSiteLocation(This,ulLutID,lpLocation)	\
    (This)->lpVtbl -> GetSiteLocation(This,ulLutID,lpLocation)

#define IEMSLutInfo_GetSiteProfile(This,ulLutID,pAZEL,cb,pcbReturned)	\
    (This)->lpVtbl -> GetSiteProfile(This,ulLutID,pAZEL,cb,pcbReturned)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSLutInfo_GetName_Proxy( 
    IEMSLutInfo __RPC_FAR * This,
    /* [in] */ ULONG ulLutID,
    /* [length_is][size_is][out] */ unsigned char __RPC_FAR *pv,
    /* [in] */ ULONG cbMaxLength,
    /* [out] */ ULONG __RPC_FAR *pcbLength);


void __RPC_STUB IEMSLutInfo_GetName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSLutInfo_GetDescription_Proxy( 
    IEMSLutInfo __RPC_FAR * This,
    /* [in] */ ULONG ulLutID,
    /* [length_is][size_is][out] */ unsigned char __RPC_FAR *pv,
    /* [in] */ ULONG cbMaxLength,
    /* [out] */ ULONG __RPC_FAR *pcbLength);


void __RPC_STUB IEMSLutInfo_GetDescription_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSLutInfo_GetSiteLocation_Proxy( 
    IEMSLutInfo __RPC_FAR * This,
    /* [in] */ ULONG ulLutID,
    /* [out] */ EMSLOCATION __RPC_FAR *lpLocation);


void __RPC_STUB IEMSLutInfo_GetSiteLocation_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSLutInfo_GetSiteProfile_Proxy( 
    IEMSLutInfo __RPC_FAR * This,
    /* [in] */ ULONG ulLutID,
    /* [length_is][size_is][out] */ EMSAZEL __RPC_FAR *pAZEL,
    /* [in] */ ULONG cb,
    /* [out] */ ULONG __RPC_FAR *pcbReturned);


void __RPC_STUB IEMSLutInfo_GetSiteProfile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSLutInfo_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSLINFO_0023 */
/* [local] */ 

typedef /* [unique] */ IEMSLutInfo __RPC_FAR *LPEMSLUTINFO;



extern RPC_IF_HANDLE __MIDL_itf_EMSLINFO_0023_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSLINFO_0023_v0_0_s_ifspec;

#ifndef __IEMSLutInfo2_INTERFACE_DEFINED__
#define __IEMSLutInfo2_INTERFACE_DEFINED__

/* interface IEMSLutInfo2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSLutInfo2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0CE3EE4B-4D0C-47fd-91E6-97C59F95D632")
    IEMSLutInfo2 : public IEMSLutInfo
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetAntennaCount( 
            /* [in] */ ULONG ulLutID,
            /* [out] */ ULONG __RPC_FAR *lpulAntennaCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAntennaInfo( 
            /* [in] */ ULONG ulLutID,
            /* [in] */ ULONG cb,
            /* [length_is][size_is][out] */ EMSANTENNACONFIG __RPC_FAR *pInfo,
            /* [out] */ ULONG __RPC_FAR *pcbReturned) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSLutInfo2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSLutInfo2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSLutInfo2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSLutInfo2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfigFlags )( 
            IEMSLutInfo2 __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigFlags )( 
            IEMSLutInfo2 __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *lpdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReloadConfigData )( 
            IEMSLutInfo2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfigValueA )( 
            IEMSLutInfo2 __RPC_FAR * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [string][in] */ LPCSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigValueA )( 
            IEMSLutInfo2 __RPC_FAR * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [length_is][size_is][out] */ unsigned char __RPC_FAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG __RPC_FAR *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfigValueW )( 
            IEMSLutInfo2 __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [string][in] */ LPCWSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigValueW )( 
            IEMSLutInfo2 __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [length_is][size_is][out] */ WCHAR __RPC_FAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG __RPC_FAR *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetName )( 
            IEMSLutInfo2 __RPC_FAR * This,
            /* [in] */ ULONG ulLutID,
            /* [length_is][size_is][out] */ unsigned char __RPC_FAR *pv,
            /* [in] */ ULONG cbMaxLength,
            /* [out] */ ULONG __RPC_FAR *pcbLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDescription )( 
            IEMSLutInfo2 __RPC_FAR * This,
            /* [in] */ ULONG ulLutID,
            /* [length_is][size_is][out] */ unsigned char __RPC_FAR *pv,
            /* [in] */ ULONG cbMaxLength,
            /* [out] */ ULONG __RPC_FAR *pcbLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSiteLocation )( 
            IEMSLutInfo2 __RPC_FAR * This,
            /* [in] */ ULONG ulLutID,
            /* [out] */ EMSLOCATION __RPC_FAR *lpLocation);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSiteProfile )( 
            IEMSLutInfo2 __RPC_FAR * This,
            /* [in] */ ULONG ulLutID,
            /* [length_is][size_is][out] */ EMSAZEL __RPC_FAR *pAZEL,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbReturned);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAntennaCount )( 
            IEMSLutInfo2 __RPC_FAR * This,
            /* [in] */ ULONG ulLutID,
            /* [out] */ ULONG __RPC_FAR *lpulAntennaCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAntennaInfo )( 
            IEMSLutInfo2 __RPC_FAR * This,
            /* [in] */ ULONG ulLutID,
            /* [in] */ ULONG cb,
            /* [length_is][size_is][out] */ EMSANTENNACONFIG __RPC_FAR *pInfo,
            /* [out] */ ULONG __RPC_FAR *pcbReturned);
        
        END_INTERFACE
    } IEMSLutInfo2Vtbl;

    interface IEMSLutInfo2
    {
        CONST_VTBL struct IEMSLutInfo2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSLutInfo2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSLutInfo2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSLutInfo2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSLutInfo2_SetConfigFlags(This,dwFlags)	\
    (This)->lpVtbl -> SetConfigFlags(This,dwFlags)

#define IEMSLutInfo2_GetConfigFlags(This,lpdwFlags)	\
    (This)->lpVtbl -> GetConfigFlags(This,lpdwFlags)

#define IEMSLutInfo2_ReloadConfigData(This)	\
    (This)->lpVtbl -> ReloadConfigData(This)

#define IEMSLutInfo2_SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)	\
    (This)->lpVtbl -> SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)

#define IEMSLutInfo2_GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    (This)->lpVtbl -> GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)

#define IEMSLutInfo2_SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)	\
    (This)->lpVtbl -> SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)

#define IEMSLutInfo2_GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    (This)->lpVtbl -> GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)


#define IEMSLutInfo2_GetName(This,ulLutID,pv,cbMaxLength,pcbLength)	\
    (This)->lpVtbl -> GetName(This,ulLutID,pv,cbMaxLength,pcbLength)

#define IEMSLutInfo2_GetDescription(This,ulLutID,pv,cbMaxLength,pcbLength)	\
    (This)->lpVtbl -> GetDescription(This,ulLutID,pv,cbMaxLength,pcbLength)

#define IEMSLutInfo2_GetSiteLocation(This,ulLutID,lpLocation)	\
    (This)->lpVtbl -> GetSiteLocation(This,ulLutID,lpLocation)

#define IEMSLutInfo2_GetSiteProfile(This,ulLutID,pAZEL,cb,pcbReturned)	\
    (This)->lpVtbl -> GetSiteProfile(This,ulLutID,pAZEL,cb,pcbReturned)


#define IEMSLutInfo2_GetAntennaCount(This,ulLutID,lpulAntennaCount)	\
    (This)->lpVtbl -> GetAntennaCount(This,ulLutID,lpulAntennaCount)

#define IEMSLutInfo2_GetAntennaInfo(This,ulLutID,cb,pInfo,pcbReturned)	\
    (This)->lpVtbl -> GetAntennaInfo(This,ulLutID,cb,pInfo,pcbReturned)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSLutInfo2_GetAntennaCount_Proxy( 
    IEMSLutInfo2 __RPC_FAR * This,
    /* [in] */ ULONG ulLutID,
    /* [out] */ ULONG __RPC_FAR *lpulAntennaCount);


void __RPC_STUB IEMSLutInfo2_GetAntennaCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSLutInfo2_GetAntennaInfo_Proxy( 
    IEMSLutInfo2 __RPC_FAR * This,
    /* [in] */ ULONG ulLutID,
    /* [in] */ ULONG cb,
    /* [length_is][size_is][out] */ EMSANTENNACONFIG __RPC_FAR *pInfo,
    /* [out] */ ULONG __RPC_FAR *pcbReturned);


void __RPC_STUB IEMSLutInfo2_GetAntennaInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSLutInfo2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSLINFO_0024 */
/* [local] */ 

typedef /* [unique] */ IEMSLutInfo2 __RPC_FAR *LPEMSLUTINFO2;



extern RPC_IF_HANDLE __MIDL_itf_EMSLINFO_0024_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSLINFO_0024_v0_0_s_ifspec;

#ifndef __IEMSLutInfo3_INTERFACE_DEFINED__
#define __IEMSLutInfo3_INTERFACE_DEFINED__

/* interface IEMSLutInfo3 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSLutInfo3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("17676BA9-605F-493a-BB3A-F66BC4795418")
    IEMSLutInfo3 : public IEMSLutInfo2
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetSarrCalibration( 
            /* [in] */ ULONG ulLutID,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset,
            /* [in] */ double dFreqOffset) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSarrCalibration( 
            /* [in] */ ULONG ulLutID,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME __RPC_FAR *lpTimeStamp,
            /* [out] */ INT64 __RPC_FAR *lpi64TimeOffset,
            /* [out] */ double __RPC_FAR *lpdFreqOffset) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSLutInfo3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSLutInfo3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSLutInfo3 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSLutInfo3 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfigFlags )( 
            IEMSLutInfo3 __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigFlags )( 
            IEMSLutInfo3 __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *lpdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReloadConfigData )( 
            IEMSLutInfo3 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfigValueA )( 
            IEMSLutInfo3 __RPC_FAR * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [string][in] */ LPCSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigValueA )( 
            IEMSLutInfo3 __RPC_FAR * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [length_is][size_is][out] */ unsigned char __RPC_FAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG __RPC_FAR *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfigValueW )( 
            IEMSLutInfo3 __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [string][in] */ LPCWSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigValueW )( 
            IEMSLutInfo3 __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [length_is][size_is][out] */ WCHAR __RPC_FAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG __RPC_FAR *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetName )( 
            IEMSLutInfo3 __RPC_FAR * This,
            /* [in] */ ULONG ulLutID,
            /* [length_is][size_is][out] */ unsigned char __RPC_FAR *pv,
            /* [in] */ ULONG cbMaxLength,
            /* [out] */ ULONG __RPC_FAR *pcbLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDescription )( 
            IEMSLutInfo3 __RPC_FAR * This,
            /* [in] */ ULONG ulLutID,
            /* [length_is][size_is][out] */ unsigned char __RPC_FAR *pv,
            /* [in] */ ULONG cbMaxLength,
            /* [out] */ ULONG __RPC_FAR *pcbLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSiteLocation )( 
            IEMSLutInfo3 __RPC_FAR * This,
            /* [in] */ ULONG ulLutID,
            /* [out] */ EMSLOCATION __RPC_FAR *lpLocation);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSiteProfile )( 
            IEMSLutInfo3 __RPC_FAR * This,
            /* [in] */ ULONG ulLutID,
            /* [length_is][size_is][out] */ EMSAZEL __RPC_FAR *pAZEL,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbReturned);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAntennaCount )( 
            IEMSLutInfo3 __RPC_FAR * This,
            /* [in] */ ULONG ulLutID,
            /* [out] */ ULONG __RPC_FAR *lpulAntennaCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAntennaInfo )( 
            IEMSLutInfo3 __RPC_FAR * This,
            /* [in] */ ULONG ulLutID,
            /* [in] */ ULONG cb,
            /* [length_is][size_is][out] */ EMSANTENNACONFIG __RPC_FAR *pInfo,
            /* [out] */ ULONG __RPC_FAR *pcbReturned);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSarrCalibration )( 
            IEMSLutInfo3 __RPC_FAR * This,
            /* [in] */ ULONG ulLutID,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSarrCalibration )( 
            IEMSLutInfo3 __RPC_FAR * This,
            /* [in] */ ULONG ulLutID,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME __RPC_FAR *lpTimeStamp,
            /* [out] */ INT64 __RPC_FAR *lpi64TimeOffset,
            /* [out] */ double __RPC_FAR *lpdFreqOffset);
        
        END_INTERFACE
    } IEMSLutInfo3Vtbl;

    interface IEMSLutInfo3
    {
        CONST_VTBL struct IEMSLutInfo3Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSLutInfo3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSLutInfo3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSLutInfo3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSLutInfo3_SetConfigFlags(This,dwFlags)	\
    (This)->lpVtbl -> SetConfigFlags(This,dwFlags)

#define IEMSLutInfo3_GetConfigFlags(This,lpdwFlags)	\
    (This)->lpVtbl -> GetConfigFlags(This,lpdwFlags)

#define IEMSLutInfo3_ReloadConfigData(This)	\
    (This)->lpVtbl -> ReloadConfigData(This)

#define IEMSLutInfo3_SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)	\
    (This)->lpVtbl -> SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)

#define IEMSLutInfo3_GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    (This)->lpVtbl -> GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)

#define IEMSLutInfo3_SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)	\
    (This)->lpVtbl -> SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)

#define IEMSLutInfo3_GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    (This)->lpVtbl -> GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)


#define IEMSLutInfo3_GetName(This,ulLutID,pv,cbMaxLength,pcbLength)	\
    (This)->lpVtbl -> GetName(This,ulLutID,pv,cbMaxLength,pcbLength)

#define IEMSLutInfo3_GetDescription(This,ulLutID,pv,cbMaxLength,pcbLength)	\
    (This)->lpVtbl -> GetDescription(This,ulLutID,pv,cbMaxLength,pcbLength)

#define IEMSLutInfo3_GetSiteLocation(This,ulLutID,lpLocation)	\
    (This)->lpVtbl -> GetSiteLocation(This,ulLutID,lpLocation)

#define IEMSLutInfo3_GetSiteProfile(This,ulLutID,pAZEL,cb,pcbReturned)	\
    (This)->lpVtbl -> GetSiteProfile(This,ulLutID,pAZEL,cb,pcbReturned)


#define IEMSLutInfo3_GetAntennaCount(This,ulLutID,lpulAntennaCount)	\
    (This)->lpVtbl -> GetAntennaCount(This,ulLutID,lpulAntennaCount)

#define IEMSLutInfo3_GetAntennaInfo(This,ulLutID,cb,pInfo,pcbReturned)	\
    (This)->lpVtbl -> GetAntennaInfo(This,ulLutID,cb,pInfo,pcbReturned)


#define IEMSLutInfo3_SetSarrCalibration(This,ulLutID,ulSatelliteID,i64TimeOffset,dFreqOffset)	\
    (This)->lpVtbl -> SetSarrCalibration(This,ulLutID,ulSatelliteID,i64TimeOffset,dFreqOffset)

#define IEMSLutInfo3_GetSarrCalibration(This,ulLutID,ulSatelliteID,lpTimeStamp,lpi64TimeOffset,lpdFreqOffset)	\
    (This)->lpVtbl -> GetSarrCalibration(This,ulLutID,ulSatelliteID,lpTimeStamp,lpi64TimeOffset,lpdFreqOffset)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSLutInfo3_SetSarrCalibration_Proxy( 
    IEMSLutInfo3 __RPC_FAR * This,
    /* [in] */ ULONG ulLutID,
    /* [in] */ ULONG ulSatelliteID,
    /* [in] */ INT64 i64TimeOffset,
    /* [in] */ double dFreqOffset);


void __RPC_STUB IEMSLutInfo3_SetSarrCalibration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSLutInfo3_GetSarrCalibration_Proxy( 
    IEMSLutInfo3 __RPC_FAR * This,
    /* [in] */ ULONG ulLutID,
    /* [in] */ ULONG ulSatelliteID,
    /* [out] */ EMSTIME __RPC_FAR *lpTimeStamp,
    /* [out] */ INT64 __RPC_FAR *lpi64TimeOffset,
    /* [out] */ double __RPC_FAR *lpdFreqOffset);


void __RPC_STUB IEMSLutInfo3_GetSarrCalibration_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSLutInfo3_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSLINFO_0025 */
/* [local] */ 

typedef /* [unique] */ IEMSLutInfo3 __RPC_FAR *LPEMSLUTINFO3;



extern RPC_IF_HANDLE __MIDL_itf_EMSLINFO_0025_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSLINFO_0025_v0_0_s_ifspec;

#ifndef __IEMSLutType_INTERFACE_DEFINED__
#define __IEMSLutType_INTERFACE_DEFINED__

/* interface IEMSLutType */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSLutType;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("612A6FA4-ED98-4fb2-87D0-BEF1EBC8608D")
    IEMSLutType : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetLutType( 
            /* [in] */ ULONG ulLutID,
            /* [out] */ LPWORD lpwLutType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLutVersion( 
            /* [in] */ ULONG ulLutID,
            /* [out] */ LPWORD lpwLutVersion) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSLutTypeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSLutType __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSLutType __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSLutType __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLutType )( 
            IEMSLutType __RPC_FAR * This,
            /* [in] */ ULONG ulLutID,
            /* [out] */ LPWORD lpwLutType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLutVersion )( 
            IEMSLutType __RPC_FAR * This,
            /* [in] */ ULONG ulLutID,
            /* [out] */ LPWORD lpwLutVersion);
        
        END_INTERFACE
    } IEMSLutTypeVtbl;

    interface IEMSLutType
    {
        CONST_VTBL struct IEMSLutTypeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSLutType_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSLutType_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSLutType_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSLutType_GetLutType(This,ulLutID,lpwLutType)	\
    (This)->lpVtbl -> GetLutType(This,ulLutID,lpwLutType)

#define IEMSLutType_GetLutVersion(This,ulLutID,lpwLutVersion)	\
    (This)->lpVtbl -> GetLutVersion(This,ulLutID,lpwLutVersion)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSLutType_GetLutType_Proxy( 
    IEMSLutType __RPC_FAR * This,
    /* [in] */ ULONG ulLutID,
    /* [out] */ LPWORD lpwLutType);


void __RPC_STUB IEMSLutType_GetLutType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSLutType_GetLutVersion_Proxy( 
    IEMSLutType __RPC_FAR * This,
    /* [in] */ ULONG ulLutID,
    /* [out] */ LPWORD lpwLutVersion);


void __RPC_STUB IEMSLutType_GetLutVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSLutType_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSLINFO_0026 */
/* [local] */ 

typedef /* [unique] */ IEMSLutType __RPC_FAR *LPEMSLUTTYPE;



extern RPC_IF_HANDLE __MIDL_itf_EMSLINFO_0026_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSLINFO_0026_v0_0_s_ifspec;

#ifndef __IEMSTransfer_INTERFACE_DEFINED__
#define __IEMSTransfer_INTERFACE_DEFINED__

/* interface IEMSTransfer */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSTransfer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CE11BC87-66F2-4c53-93C4-FB2E956EC1EF")
    IEMSTransfer : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetTransferDirectory( 
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSTransferVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSTransfer __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSTransfer __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSTransfer __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTransferDirectory )( 
            IEMSTransfer __RPC_FAR * This,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead);
        
        END_INTERFACE
    } IEMSTransferVtbl;

    interface IEMSTransfer
    {
        CONST_VTBL struct IEMSTransferVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSTransfer_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSTransfer_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSTransfer_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSTransfer_GetTransferDirectory(This,pv,cb,pcbRead)	\
    (This)->lpVtbl -> GetTransferDirectory(This,pv,cb,pcbRead)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSTransfer_GetTransferDirectory_Proxy( 
    IEMSTransfer __RPC_FAR * This,
    /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
    /* [in] */ ULONG cb,
    /* [out] */ ULONG __RPC_FAR *pcbRead);


void __RPC_STUB IEMSTransfer_GetTransferDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSTransfer_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSLINFO_0027 */
/* [local] */ 

typedef /* [unique] */ IEMSTransfer __RPC_FAR *LPEMSTRANSFER;



extern RPC_IF_HANDLE __MIDL_itf_EMSLINFO_0027_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSLINFO_0027_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
