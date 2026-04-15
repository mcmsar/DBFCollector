/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Jan 05 22:18:31 2003
 */
/* Compiler settings for emsicfg.idl:
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

#ifndef __emsicfg_h__
#define __emsicfg_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSConfigSettings_FWD_DEFINED__
#define __IEMSConfigSettings_FWD_DEFINED__
typedef interface IEMSConfigSettings IEMSConfigSettings;
#endif 	/* __IEMSConfigSettings_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_emsicfg_0000 */
/* [local] */ 

 
#include "emserror.h"
 
// {6FB2B03E-2C1E-4314-A07F-CF9BAFFA63A6}
DEFINE_GUID( IID_IEMSConfigSettings, 0x6fb2b03e, 0x2c1e, 0x4314, 0xa0, 0x7f, 0xcf, 0x9b, 0xaf, 0xfa, 0x63, 0xa6);
 
// Bit settings for dwFlags 
#define EMS_ICFG_READONLY					(0x0001)
#define EMS_ICFG_RELOADABLE				(0x0002)
#define EMS_ICFG_CHANGED					(0x0004)
//  
// Bit settings for EMSCONFIGPACKET.wFlags 
#define EMS_ICFG_CHANGE						(0x0001)
#define EMS_ICFG_QUERY						(0x0002)
//  
 
#ifdef UNICODE
#define SetConfigValue     SetConfigValueW
#define GetConfigValue     GetConfigValueW
#else
#define SetConfigValue     SetConfigValueA
#define GetConfigValue     GetConfigValueA
#endif // UNICODE
 


extern RPC_IF_HANDLE __MIDL_itf_emsicfg_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_emsicfg_0000_v0_0_s_ifspec;

#ifndef __IEMSConfigSettings_INTERFACE_DEFINED__
#define __IEMSConfigSettings_INTERFACE_DEFINED__

/* interface IEMSConfigSettings */
/* [unique][helpstring][uuid][object] */ 


#pragma pack(1)
typedef struct  _tagEMSCONFIGDATA
    {
    BYTE szInstance[ 33 ];
    BYTE szField[ 65 ];
    BYTE szValue[ 129 ];
    }	EMSCONFIGDATA;

typedef struct _tagEMSCONFIGDATA __RPC_FAR *LPEMSCONFIGDATA;

typedef 
enum _tagEMSCONFIGTYPE
    {	EMSConfigTypeSat	= 1,
	EMSConfigTypeLut	= 2,
	EMSConfigTypeBeacon	= 3,
	EMSConfigTypeTable	= 4,
	EMSConfigTypeUnknown	= 0
    }	EMSCONFIGTYPE;

typedef 
enum _tagEMSCONFIGLEVEL
    {	EMSConfigLevelBase	= 1,
	EMSConfigLevelInstalled	= 2,
	EMSConfigLevelCustomer	= 3,
	EMSConfigLevelDynamic	= 3,
	EMSConfigLevelTest	= 4,
	EMSConfigLevelUnknown	= 0
    }	EMSCONFIGLEVEL;

typedef struct  _tagEMSCONFIGRECORD
    {
    EMSTIME timeModified;
    ULONG ulLutID;
    ULONG ulSourceID;
    WORD wFileLevel;
    WORD wType;
    EMSCONFIGDATA cfg;
    BYTE szUserID[ 9 ];
    }	EMSCONFIGRECORD;

typedef struct _tagEMSCONFIGRECORD __RPC_FAR *LPEMSCONFIGRECORD;

typedef struct  _tagEMSCONFIGPACKET
    {
    WORD wFlags;
    INT nDestID;
    INT nRequestID;
    EMSCONFIGRECORD rec;
    }	EMSCONFIGPACKET;

typedef struct _tagEMSCONFIGPACKET __RPC_FAR *LPEMSCONFIGPACKET;


#pragma pack()

EXTERN_C const IID IID_IEMSConfigSettings;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6FB2B03E-2C1E-4314-A07F-CF9BAFFA63A6")
    IEMSConfigSettings : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetConfigFlags( 
            /* [in] */ DWORD dwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetConfigFlags( 
            /* [out] */ DWORD __RPC_FAR *lpdwFlags) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ReloadConfigData( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetConfigValueA( 
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [string][in] */ LPCSTR lpcszValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetConfigValueA( 
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [length_is][size_is][out] */ unsigned char __RPC_FAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG __RPC_FAR *lpulRead) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetConfigValueW( 
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [string][in] */ LPCWSTR lpcszValue) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetConfigValueW( 
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [length_is][size_is][out] */ WCHAR __RPC_FAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG __RPC_FAR *lpulRead) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSConfigSettingsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSConfigSettings __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSConfigSettings __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSConfigSettings __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfigFlags )( 
            IEMSConfigSettings __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigFlags )( 
            IEMSConfigSettings __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *lpdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReloadConfigData )( 
            IEMSConfigSettings __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfigValueA )( 
            IEMSConfigSettings __RPC_FAR * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [string][in] */ LPCSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigValueA )( 
            IEMSConfigSettings __RPC_FAR * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [length_is][size_is][out] */ unsigned char __RPC_FAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG __RPC_FAR *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfigValueW )( 
            IEMSConfigSettings __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [string][in] */ LPCWSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigValueW )( 
            IEMSConfigSettings __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [length_is][size_is][out] */ WCHAR __RPC_FAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG __RPC_FAR *lpulRead);
        
        END_INTERFACE
    } IEMSConfigSettingsVtbl;

    interface IEMSConfigSettings
    {
        CONST_VTBL struct IEMSConfigSettingsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSConfigSettings_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSConfigSettings_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSConfigSettings_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSConfigSettings_SetConfigFlags(This,dwFlags)	\
    (This)->lpVtbl -> SetConfigFlags(This,dwFlags)

#define IEMSConfigSettings_GetConfigFlags(This,lpdwFlags)	\
    (This)->lpVtbl -> GetConfigFlags(This,lpdwFlags)

#define IEMSConfigSettings_ReloadConfigData(This)	\
    (This)->lpVtbl -> ReloadConfigData(This)

#define IEMSConfigSettings_SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)	\
    (This)->lpVtbl -> SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)

#define IEMSConfigSettings_GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    (This)->lpVtbl -> GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)

#define IEMSConfigSettings_SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)	\
    (This)->lpVtbl -> SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)

#define IEMSConfigSettings_GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    (This)->lpVtbl -> GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSConfigSettings_SetConfigFlags_Proxy( 
    IEMSConfigSettings __RPC_FAR * This,
    /* [in] */ DWORD dwFlags);


void __RPC_STUB IEMSConfigSettings_SetConfigFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSConfigSettings_GetConfigFlags_Proxy( 
    IEMSConfigSettings __RPC_FAR * This,
    /* [out] */ DWORD __RPC_FAR *lpdwFlags);


void __RPC_STUB IEMSConfigSettings_GetConfigFlags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSConfigSettings_ReloadConfigData_Proxy( 
    IEMSConfigSettings __RPC_FAR * This);


void __RPC_STUB IEMSConfigSettings_ReloadConfigData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSConfigSettings_SetConfigValueA_Proxy( 
    IEMSConfigSettings __RPC_FAR * This,
    /* [string][in] */ LPCSTR lpcszSection,
    /* [string][in] */ LPCSTR lpcszKey,
    /* [string][in] */ LPCSTR lpcszValue);


void __RPC_STUB IEMSConfigSettings_SetConfigValueA_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSConfigSettings_GetConfigValueA_Proxy( 
    IEMSConfigSettings __RPC_FAR * This,
    /* [string][in] */ LPCSTR lpcszSection,
    /* [string][in] */ LPCSTR lpcszKey,
    /* [length_is][size_is][out] */ unsigned char __RPC_FAR *lpszValue,
    /* [in] */ ULONG ulMaxLen,
    /* [out] */ ULONG __RPC_FAR *lpulRead);


void __RPC_STUB IEMSConfigSettings_GetConfigValueA_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSConfigSettings_SetConfigValueW_Proxy( 
    IEMSConfigSettings __RPC_FAR * This,
    /* [string][in] */ LPCWSTR lpcszSection,
    /* [string][in] */ LPCWSTR lpcszKey,
    /* [string][in] */ LPCWSTR lpcszValue);


void __RPC_STUB IEMSConfigSettings_SetConfigValueW_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSConfigSettings_GetConfigValueW_Proxy( 
    IEMSConfigSettings __RPC_FAR * This,
    /* [string][in] */ LPCWSTR lpcszSection,
    /* [string][in] */ LPCWSTR lpcszKey,
    /* [length_is][size_is][out] */ WCHAR __RPC_FAR *lpszValue,
    /* [in] */ ULONG ulMaxLen,
    /* [out] */ ULONG __RPC_FAR *lpulRead);


void __RPC_STUB IEMSConfigSettings_GetConfigValueW_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSConfigSettings_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_emsicfg_0008 */
/* [local] */ 

typedef /* [unique] */ IEMSConfigSettings __RPC_FAR *LPEMSCONFIGSETTINGS;



extern RPC_IF_HANDLE __MIDL_itf_emsicfg_0008_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_emsicfg_0008_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
