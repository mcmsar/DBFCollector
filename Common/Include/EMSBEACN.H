/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Jul 04 10:39:17 2011
 */
/* Compiler settings for ..\common\Include\EMSBEACN.IDL:
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

#ifndef __EMSBEACN_h__
#define __EMSBEACN_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSRefBeaconInfo_FWD_DEFINED__
#define __IEMSRefBeaconInfo_FWD_DEFINED__
typedef interface IEMSRefBeaconInfo IEMSRefBeaconInfo;
#endif 	/* __IEMSRefBeaconInfo_FWD_DEFINED__ */


#ifndef __IEMSRefBeaconInfo2_FWD_DEFINED__
#define __IEMSRefBeaconInfo2_FWD_DEFINED__
typedef interface IEMSRefBeaconInfo2 IEMSRefBeaconInfo2;
#endif 	/* __IEMSRefBeaconInfo2_FWD_DEFINED__ */


#ifndef __IEMSRefBeaconInfo3_FWD_DEFINED__
#define __IEMSRefBeaconInfo3_FWD_DEFINED__
typedef interface IEMSRefBeaconInfo3 IEMSRefBeaconInfo3;
#endif 	/* __IEMSRefBeaconInfo3_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "emsicfg.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_EMSBEACN_0000 */
/* [local] */ 

 
#include "emserror.h"
 
// {E22CF571-964F-11d5-8C04-009027912866}
DEFINE_GUID( CLSID_EMSRefBeaconInfo, 0xe22cf571, 0x964f, 0x11d5, 0x8c, 0x4, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);
// {E22CF572-964F-11d5-8C04-009027912866}
DEFINE_GUID( IID_IEMSRefBeaconInfo, 0xe22cf572, 0x964f, 0x11d5, 0x8c, 0x4, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);
// {0072892C-5517-44a5-A002-E3D9900432A8}
DEFINE_GUID( IID_IEMSRefBeaconInfo2, 0x72892c, 0x5517, 0x44a5, 0xa0, 0x2, 0xe3, 0xd9, 0x90, 0x4, 0x32, 0xa8);
// {4FBBD782-85C0-4d69-931E-6662537B69BC}
DEFINE_GUID( IID_IEMSRefBeaconInfo3, 0x4fbbd782, 0x85c0, 0x4d69, 0x93, 0x1e, 0x66, 0x62, 0x53, 0x7b, 0x69, 0xbc);
 
#define EMS_BEACON_BEACONTYPE           (0x1F00) // 4 bits for beacon type (see below)
 
#define EMS_BEACON_LEO_REFFREQ           (0x0080)
#define EMS_BEACON_USEREFFREQ           (0x0040)
#define EMS_BEACON_GEO_REFFREQ           (EMS_BEACON_USEREFFREQ)
#define EMS_BEACON_ACTIVE			    	(0x0020)
#define EMS_BEACON_TCAL				    	(0x0010)
#define EMS_BEACON_MCCSUPPRESS	    	   (0x0008)
#define EMS_BEACON_ORBITUPDATEFLAG    	(0x0004)
#define EMS_BEACON_CHECK_ACCURACY		(0x0002)
#define EMS_BEACON_USE_EE_ADJUST			(0x0001)
 
#define EMS_BEACON_BEACONTYPE_ORBIT     (0x0100)
#define EMS_BEACON_BEACONTYPE_REF       (0x0200)
#define EMS_BEACON_BEACONTYPE_TEST      (0x0400)
#define EMS_BEACON_BEACONTYPE_121       (0x0800)
#define EMS_BEACON_BEACONTYPE_243       (0x1000)
#define EMS_BEACON_BEACONTYPE_406	   (0x2000)
#define EMS_BEACON_MCCSUPPRESS_ADVISORY (0x4000)
 
//Legacy symbols now point to new high order positioning of beacon type:
 
#define EMS_BEACON_ORBITOGRAPHY       	EMS_BEACON_BEACONTYPE_ORBIT
#define EMS_BEACON_REFERENCE          	EMS_BEACON_BEACONTYPE_REF
 


extern RPC_IF_HANDLE __MIDL_itf_EMSBEACN_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSBEACN_0000_v0_0_s_ifspec;

#ifndef __IEMSRefBeaconInfo_INTERFACE_DEFINED__
#define __IEMSRefBeaconInfo_INTERFACE_DEFINED__

/* interface IEMSRefBeaconInfo */
/* [unique][helpstring][uuid][object] */ 

typedef struct  _tagEMSREFBEACONDATA
    {
    EMSTIME timeUpdate;
    unsigned short uFlag;
    unsigned short uGroup;
    unsigned char cBeaconId[ 8 ];
    unsigned char cBeaconMsg[ 18 ];
    double dLatitude;
    double dLongitude;
    double dAltitude;
    double dFrequency;
    double dPower;
    double dRepRate;
    double dBitRate;
    double dModIndex;
    }	EMSREFBEACONDATA;

typedef struct _tagEMSREFBEACONDATA __RPC_FAR *LPEMSREFBEACONDATA;

typedef struct  _tagEMSREFBEACONDATAEX
    {
    INT64 i64BeaconID;
    EMSREFBEACONDATA data;
    }	EMSREFBEACONDATAEX;

typedef struct _tagEMSREFBEACONDATAEX __RPC_FAR *LPEMSREFBEACONDATAEX;


EXTERN_C const IID IID_IEMSRefBeaconInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E22CF572-964F-11d5-8C04-009027912866")
    IEMSRefBeaconInfo : public IEMSConfigSettings
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetData( 
            /* [in] */ __int64 i64BeaconID,
            /* [out] */ EMSREFBEACONDATA __RPC_FAR *lpData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIndexedData( 
            /* [in] */ int nIndex,
            /* [out] */ __int64 __RPC_FAR *lpi64BeaconID,
            /* [out] */ EMSREFBEACONDATA __RPC_FAR *lpData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCount( 
            /* [out] */ ULONG __RPC_FAR *lpulCount) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSRefBeaconInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSRefBeaconInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSRefBeaconInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSRefBeaconInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfigFlags )( 
            IEMSRefBeaconInfo __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigFlags )( 
            IEMSRefBeaconInfo __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *lpdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReloadConfigData )( 
            IEMSRefBeaconInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfigValueA )( 
            IEMSRefBeaconInfo __RPC_FAR * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [string][in] */ LPCSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigValueA )( 
            IEMSRefBeaconInfo __RPC_FAR * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [length_is][size_is][out] */ unsigned char __RPC_FAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG __RPC_FAR *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfigValueW )( 
            IEMSRefBeaconInfo __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [string][in] */ LPCWSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigValueW )( 
            IEMSRefBeaconInfo __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [length_is][size_is][out] */ WCHAR __RPC_FAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG __RPC_FAR *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetData )( 
            IEMSRefBeaconInfo __RPC_FAR * This,
            /* [in] */ __int64 i64BeaconID,
            /* [out] */ EMSREFBEACONDATA __RPC_FAR *lpData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIndexedData )( 
            IEMSRefBeaconInfo __RPC_FAR * This,
            /* [in] */ int nIndex,
            /* [out] */ __int64 __RPC_FAR *lpi64BeaconID,
            /* [out] */ EMSREFBEACONDATA __RPC_FAR *lpData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCount )( 
            IEMSRefBeaconInfo __RPC_FAR * This,
            /* [out] */ ULONG __RPC_FAR *lpulCount);
        
        END_INTERFACE
    } IEMSRefBeaconInfoVtbl;

    interface IEMSRefBeaconInfo
    {
        CONST_VTBL struct IEMSRefBeaconInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSRefBeaconInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSRefBeaconInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSRefBeaconInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSRefBeaconInfo_SetConfigFlags(This,dwFlags)	\
    (This)->lpVtbl -> SetConfigFlags(This,dwFlags)

#define IEMSRefBeaconInfo_GetConfigFlags(This,lpdwFlags)	\
    (This)->lpVtbl -> GetConfigFlags(This,lpdwFlags)

#define IEMSRefBeaconInfo_ReloadConfigData(This)	\
    (This)->lpVtbl -> ReloadConfigData(This)

#define IEMSRefBeaconInfo_SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)	\
    (This)->lpVtbl -> SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)

#define IEMSRefBeaconInfo_GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    (This)->lpVtbl -> GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)

#define IEMSRefBeaconInfo_SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)	\
    (This)->lpVtbl -> SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)

#define IEMSRefBeaconInfo_GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    (This)->lpVtbl -> GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)


#define IEMSRefBeaconInfo_GetData(This,i64BeaconID,lpData)	\
    (This)->lpVtbl -> GetData(This,i64BeaconID,lpData)

#define IEMSRefBeaconInfo_GetIndexedData(This,nIndex,lpi64BeaconID,lpData)	\
    (This)->lpVtbl -> GetIndexedData(This,nIndex,lpi64BeaconID,lpData)

#define IEMSRefBeaconInfo_GetCount(This,lpulCount)	\
    (This)->lpVtbl -> GetCount(This,lpulCount)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSRefBeaconInfo_GetData_Proxy( 
    IEMSRefBeaconInfo __RPC_FAR * This,
    /* [in] */ __int64 i64BeaconID,
    /* [out] */ EMSREFBEACONDATA __RPC_FAR *lpData);


void __RPC_STUB IEMSRefBeaconInfo_GetData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSRefBeaconInfo_GetIndexedData_Proxy( 
    IEMSRefBeaconInfo __RPC_FAR * This,
    /* [in] */ int nIndex,
    /* [out] */ __int64 __RPC_FAR *lpi64BeaconID,
    /* [out] */ EMSREFBEACONDATA __RPC_FAR *lpData);


void __RPC_STUB IEMSRefBeaconInfo_GetIndexedData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSRefBeaconInfo_GetCount_Proxy( 
    IEMSRefBeaconInfo __RPC_FAR * This,
    /* [out] */ ULONG __RPC_FAR *lpulCount);


void __RPC_STUB IEMSRefBeaconInfo_GetCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSRefBeaconInfo_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSBEACN_0012 */
/* [local] */ 

typedef /* [unique] */ IEMSRefBeaconInfo __RPC_FAR *LPEMSREFBEACONINFO;



extern RPC_IF_HANDLE __MIDL_itf_EMSBEACN_0012_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSBEACN_0012_v0_0_s_ifspec;

#ifndef __IEMSRefBeaconInfo2_INTERFACE_DEFINED__
#define __IEMSRefBeaconInfo2_INTERFACE_DEFINED__

/* interface IEMSRefBeaconInfo2 */
/* [unique][helpstring][uuid][object] */ 


#pragma pack(1)
typedef struct  _tagEMSREFBEACONACCURACY
    {
    double dMinCTA;
    double dMaxCTA;
    double dMaxTCARange;
    INT nMinPts;
    double dWarnDistance;
    double dAlarmDistance;
    double dReserved1;
    double dReserved2;
    INT nReserved3;
    INT nReserved4;
    }	EMSREFBEACONACCURACY;

typedef struct _tagEMSREFBEACONACCURACY __RPC_FAR *LPEMSREFBEACONACCURACY;


#pragma pack()

EXTERN_C const IID IID_IEMSRefBeaconInfo2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("0072892C-5517-44a5-A002-E3D9900432A8")
    IEMSRefBeaconInfo2 : public IEMSRefBeaconInfo
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetAccuracyInfo( 
            /* [in] */ INT64 i64BeaconID,
            /* [out] */ LPEMSREFBEACONACCURACY lpInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAccuracyInfoByIndex( 
            /* [in] */ INT nIndex,
            /* [out] */ INT64 __RPC_FAR *lpi64BeaconID,
            /* [out] */ LPEMSREFBEACONACCURACY lpInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSRefBeaconInfo2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSRefBeaconInfo2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSRefBeaconInfo2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSRefBeaconInfo2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfigFlags )( 
            IEMSRefBeaconInfo2 __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigFlags )( 
            IEMSRefBeaconInfo2 __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *lpdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReloadConfigData )( 
            IEMSRefBeaconInfo2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfigValueA )( 
            IEMSRefBeaconInfo2 __RPC_FAR * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [string][in] */ LPCSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigValueA )( 
            IEMSRefBeaconInfo2 __RPC_FAR * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [length_is][size_is][out] */ unsigned char __RPC_FAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG __RPC_FAR *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfigValueW )( 
            IEMSRefBeaconInfo2 __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [string][in] */ LPCWSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigValueW )( 
            IEMSRefBeaconInfo2 __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [length_is][size_is][out] */ WCHAR __RPC_FAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG __RPC_FAR *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetData )( 
            IEMSRefBeaconInfo2 __RPC_FAR * This,
            /* [in] */ __int64 i64BeaconID,
            /* [out] */ EMSREFBEACONDATA __RPC_FAR *lpData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIndexedData )( 
            IEMSRefBeaconInfo2 __RPC_FAR * This,
            /* [in] */ int nIndex,
            /* [out] */ __int64 __RPC_FAR *lpi64BeaconID,
            /* [out] */ EMSREFBEACONDATA __RPC_FAR *lpData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCount )( 
            IEMSRefBeaconInfo2 __RPC_FAR * This,
            /* [out] */ ULONG __RPC_FAR *lpulCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAccuracyInfo )( 
            IEMSRefBeaconInfo2 __RPC_FAR * This,
            /* [in] */ INT64 i64BeaconID,
            /* [out] */ LPEMSREFBEACONACCURACY lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAccuracyInfoByIndex )( 
            IEMSRefBeaconInfo2 __RPC_FAR * This,
            /* [in] */ INT nIndex,
            /* [out] */ INT64 __RPC_FAR *lpi64BeaconID,
            /* [out] */ LPEMSREFBEACONACCURACY lpInfo);
        
        END_INTERFACE
    } IEMSRefBeaconInfo2Vtbl;

    interface IEMSRefBeaconInfo2
    {
        CONST_VTBL struct IEMSRefBeaconInfo2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSRefBeaconInfo2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSRefBeaconInfo2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSRefBeaconInfo2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSRefBeaconInfo2_SetConfigFlags(This,dwFlags)	\
    (This)->lpVtbl -> SetConfigFlags(This,dwFlags)

#define IEMSRefBeaconInfo2_GetConfigFlags(This,lpdwFlags)	\
    (This)->lpVtbl -> GetConfigFlags(This,lpdwFlags)

#define IEMSRefBeaconInfo2_ReloadConfigData(This)	\
    (This)->lpVtbl -> ReloadConfigData(This)

#define IEMSRefBeaconInfo2_SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)	\
    (This)->lpVtbl -> SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)

#define IEMSRefBeaconInfo2_GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    (This)->lpVtbl -> GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)

#define IEMSRefBeaconInfo2_SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)	\
    (This)->lpVtbl -> SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)

#define IEMSRefBeaconInfo2_GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    (This)->lpVtbl -> GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)


#define IEMSRefBeaconInfo2_GetData(This,i64BeaconID,lpData)	\
    (This)->lpVtbl -> GetData(This,i64BeaconID,lpData)

#define IEMSRefBeaconInfo2_GetIndexedData(This,nIndex,lpi64BeaconID,lpData)	\
    (This)->lpVtbl -> GetIndexedData(This,nIndex,lpi64BeaconID,lpData)

#define IEMSRefBeaconInfo2_GetCount(This,lpulCount)	\
    (This)->lpVtbl -> GetCount(This,lpulCount)


#define IEMSRefBeaconInfo2_GetAccuracyInfo(This,i64BeaconID,lpInfo)	\
    (This)->lpVtbl -> GetAccuracyInfo(This,i64BeaconID,lpInfo)

#define IEMSRefBeaconInfo2_GetAccuracyInfoByIndex(This,nIndex,lpi64BeaconID,lpInfo)	\
    (This)->lpVtbl -> GetAccuracyInfoByIndex(This,nIndex,lpi64BeaconID,lpInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSRefBeaconInfo2_GetAccuracyInfo_Proxy( 
    IEMSRefBeaconInfo2 __RPC_FAR * This,
    /* [in] */ INT64 i64BeaconID,
    /* [out] */ LPEMSREFBEACONACCURACY lpInfo);


void __RPC_STUB IEMSRefBeaconInfo2_GetAccuracyInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSRefBeaconInfo2_GetAccuracyInfoByIndex_Proxy( 
    IEMSRefBeaconInfo2 __RPC_FAR * This,
    /* [in] */ INT nIndex,
    /* [out] */ INT64 __RPC_FAR *lpi64BeaconID,
    /* [out] */ LPEMSREFBEACONACCURACY lpInfo);


void __RPC_STUB IEMSRefBeaconInfo2_GetAccuracyInfoByIndex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSRefBeaconInfo2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSBEACN_0013 */
/* [local] */ 

typedef /* [unique] */ IEMSRefBeaconInfo2 __RPC_FAR *LPEMSREFBEACONINFO2;



extern RPC_IF_HANDLE __MIDL_itf_EMSBEACN_0013_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSBEACN_0013_v0_0_s_ifspec;

#ifndef __IEMSRefBeaconInfo3_INTERFACE_DEFINED__
#define __IEMSRefBeaconInfo3_INTERFACE_DEFINED__

/* interface IEMSRefBeaconInfo3 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSRefBeaconInfo3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4FBBD782-85C0-4d69-931E-6662537B69BC")
    IEMSRefBeaconInfo3 : public IEMSRefBeaconInfo2
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetIsQMS( 
            /* [in] */ const INT64 ci64BeaconID,
            /* [out] */ BOOL __RPC_FAR *pbIsQMS) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSRefBeaconInfo3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSRefBeaconInfo3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSRefBeaconInfo3 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSRefBeaconInfo3 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfigFlags )( 
            IEMSRefBeaconInfo3 __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigFlags )( 
            IEMSRefBeaconInfo3 __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *lpdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReloadConfigData )( 
            IEMSRefBeaconInfo3 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfigValueA )( 
            IEMSRefBeaconInfo3 __RPC_FAR * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [string][in] */ LPCSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigValueA )( 
            IEMSRefBeaconInfo3 __RPC_FAR * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [length_is][size_is][out] */ unsigned char __RPC_FAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG __RPC_FAR *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfigValueW )( 
            IEMSRefBeaconInfo3 __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [string][in] */ LPCWSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigValueW )( 
            IEMSRefBeaconInfo3 __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [length_is][size_is][out] */ WCHAR __RPC_FAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG __RPC_FAR *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetData )( 
            IEMSRefBeaconInfo3 __RPC_FAR * This,
            /* [in] */ __int64 i64BeaconID,
            /* [out] */ EMSREFBEACONDATA __RPC_FAR *lpData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIndexedData )( 
            IEMSRefBeaconInfo3 __RPC_FAR * This,
            /* [in] */ int nIndex,
            /* [out] */ __int64 __RPC_FAR *lpi64BeaconID,
            /* [out] */ EMSREFBEACONDATA __RPC_FAR *lpData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetCount )( 
            IEMSRefBeaconInfo3 __RPC_FAR * This,
            /* [out] */ ULONG __RPC_FAR *lpulCount);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAccuracyInfo )( 
            IEMSRefBeaconInfo3 __RPC_FAR * This,
            /* [in] */ INT64 i64BeaconID,
            /* [out] */ LPEMSREFBEACONACCURACY lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAccuracyInfoByIndex )( 
            IEMSRefBeaconInfo3 __RPC_FAR * This,
            /* [in] */ INT nIndex,
            /* [out] */ INT64 __RPC_FAR *lpi64BeaconID,
            /* [out] */ LPEMSREFBEACONACCURACY lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIsQMS )( 
            IEMSRefBeaconInfo3 __RPC_FAR * This,
            /* [in] */ const INT64 ci64BeaconID,
            /* [out] */ BOOL __RPC_FAR *pbIsQMS);
        
        END_INTERFACE
    } IEMSRefBeaconInfo3Vtbl;

    interface IEMSRefBeaconInfo3
    {
        CONST_VTBL struct IEMSRefBeaconInfo3Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSRefBeaconInfo3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSRefBeaconInfo3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSRefBeaconInfo3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSRefBeaconInfo3_SetConfigFlags(This,dwFlags)	\
    (This)->lpVtbl -> SetConfigFlags(This,dwFlags)

#define IEMSRefBeaconInfo3_GetConfigFlags(This,lpdwFlags)	\
    (This)->lpVtbl -> GetConfigFlags(This,lpdwFlags)

#define IEMSRefBeaconInfo3_ReloadConfigData(This)	\
    (This)->lpVtbl -> ReloadConfigData(This)

#define IEMSRefBeaconInfo3_SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)	\
    (This)->lpVtbl -> SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)

#define IEMSRefBeaconInfo3_GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    (This)->lpVtbl -> GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)

#define IEMSRefBeaconInfo3_SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)	\
    (This)->lpVtbl -> SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)

#define IEMSRefBeaconInfo3_GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    (This)->lpVtbl -> GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)


#define IEMSRefBeaconInfo3_GetData(This,i64BeaconID,lpData)	\
    (This)->lpVtbl -> GetData(This,i64BeaconID,lpData)

#define IEMSRefBeaconInfo3_GetIndexedData(This,nIndex,lpi64BeaconID,lpData)	\
    (This)->lpVtbl -> GetIndexedData(This,nIndex,lpi64BeaconID,lpData)

#define IEMSRefBeaconInfo3_GetCount(This,lpulCount)	\
    (This)->lpVtbl -> GetCount(This,lpulCount)


#define IEMSRefBeaconInfo3_GetAccuracyInfo(This,i64BeaconID,lpInfo)	\
    (This)->lpVtbl -> GetAccuracyInfo(This,i64BeaconID,lpInfo)

#define IEMSRefBeaconInfo3_GetAccuracyInfoByIndex(This,nIndex,lpi64BeaconID,lpInfo)	\
    (This)->lpVtbl -> GetAccuracyInfoByIndex(This,nIndex,lpi64BeaconID,lpInfo)


#define IEMSRefBeaconInfo3_GetIsQMS(This,ci64BeaconID,pbIsQMS)	\
    (This)->lpVtbl -> GetIsQMS(This,ci64BeaconID,pbIsQMS)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSRefBeaconInfo3_GetIsQMS_Proxy( 
    IEMSRefBeaconInfo3 __RPC_FAR * This,
    /* [in] */ const INT64 ci64BeaconID,
    /* [out] */ BOOL __RPC_FAR *pbIsQMS);


void __RPC_STUB IEMSRefBeaconInfo3_GetIsQMS_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSRefBeaconInfo3_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSBEACN_0014 */
/* [local] */ 

typedef /* [unique] */ IEMSRefBeaconInfo3 __RPC_FAR *LPEMSREFBEACONINFO3;



extern RPC_IF_HANDLE __MIDL_itf_EMSBEACN_0014_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSBEACN_0014_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
