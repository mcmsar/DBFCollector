/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Oct 17 18:41:54 2005
 */
/* Compiler settings for statgeo.idl:
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

#ifndef __statgeo_h__
#define __statgeo_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSGeoCalib406Stats_FWD_DEFINED__
#define __IEMSGeoCalib406Stats_FWD_DEFINED__
typedef interface IEMSGeoCalib406Stats IEMSGeoCalib406Stats;
#endif 	/* __IEMSGeoCalib406Stats_FWD_DEFINED__ */


#ifndef __IEMSGeoSummary_FWD_DEFINED__
#define __IEMSGeoSummary_FWD_DEFINED__
typedef interface IEMSGeoSummary IEMSGeoSummary;
#endif 	/* __IEMSGeoSummary_FWD_DEFINED__ */


#ifndef __IEMSGeoActiveBeaconStats_FWD_DEFINED__
#define __IEMSGeoActiveBeaconStats_FWD_DEFINED__
typedef interface IEMSGeoActiveBeaconStats IEMSGeoActiveBeaconStats;
#endif 	/* __IEMSGeoActiveBeaconStats_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "emstatus.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_statgeo_0000 */
/* [local] */ 

// {600E9B8C-282C-47f9-9CB2-526057482E43}
DEFINE_GUID( IID_IEMSGeoSummary, 0x600e9b8c, 0x282c, 0x47f9, 0x9c, 0xb2, 0x52, 0x60, 0x57, 0x48, 0x2e, 0x43);
 
// {6E0BA7F3-F8BE-4d52-9A82-91F7AA7E24E3}
DEFINE_GUID( IID_IEMSGeoCalib406Stats, 0x6e0ba7f3, 0xf8be, 0x4d52, 0x9a, 0x82, 0x91, 0xf7, 0xaa, 0x7e, 0x24, 0xe3);
 
// {78739D36-D0B3-4b12-BD9B-196919B7BBB9}
DEFINE_GUID( IID_IEMSGeoActiveBeaconStats, 0x78739d36, 0xd0b3, 0x4b12, 0xbd, 0x9b, 0x19, 0x69, 0x19, 0xb7, 0xbb, 0xb9);
 


extern RPC_IF_HANDLE __MIDL_itf_statgeo_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_statgeo_0000_v0_0_s_ifspec;

#ifndef __IEMSGeoCalib406Stats_INTERFACE_DEFINED__
#define __IEMSGeoCalib406Stats_INTERFACE_DEFINED__

/* interface IEMSGeoCalib406Stats */
/* [unique][helpstring][uuid][object] */ 


#pragma pack(1)
typedef struct  _tagEMSGEOCALIB406INFO
    {
    ULONG ulNumGroups;
    ULONG ulNumDetections;
    ULONG ulNumRawMsgs;
    ULONG ulNumIntMsgs;
    ULONG ulNumBeaconID;
    ULONG ulNumGroupsMax;
    ULONG ulNumGroupsMin;
    EMSTIME timeLastDetection;
    EMSTIME timeLastRefDetection;
    }	EMSGEOCALIB406INFO;

typedef struct _tagEMSGEOCALIB406INFO __RPC_FAR *LPEMSGEOCALIB406INFO;


#pragma pack()

EXTERN_C const IID IID_IEMSGeoCalib406Stats;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6E0BA7F3-F8BE-4d52-9A82-91F7AA7E24E3")
    IEMSGeoCalib406Stats : public IEMSStatus
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ResetGeoCalib406Info( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetGeoCalib406Info( 
            /* [in] */ EMSGEOCALIB406INFO __RPC_FAR *lpInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetGeoCalib406Info( 
            /* [out] */ EMSGEOCALIB406INFO __RPC_FAR *lpInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSGeoCalib406StatsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSGeoCalib406Stats __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSGeoCalib406Stats __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSGeoCalib406Stats __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetGeoCalib406Info )( 
            IEMSGeoCalib406Stats __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGeoCalib406Info )( 
            IEMSGeoCalib406Stats __RPC_FAR * This,
            /* [in] */ EMSGEOCALIB406INFO __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGeoCalib406Info )( 
            IEMSGeoCalib406Stats __RPC_FAR * This,
            /* [out] */ EMSGEOCALIB406INFO __RPC_FAR *lpInfo);
        
        END_INTERFACE
    } IEMSGeoCalib406StatsVtbl;

    interface IEMSGeoCalib406Stats
    {
        CONST_VTBL struct IEMSGeoCalib406StatsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSGeoCalib406Stats_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSGeoCalib406Stats_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSGeoCalib406Stats_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IEMSGeoCalib406Stats_ResetGeoCalib406Info(This)	\
    (This)->lpVtbl -> ResetGeoCalib406Info(This)

#define IEMSGeoCalib406Stats_SetGeoCalib406Info(This,lpInfo)	\
    (This)->lpVtbl -> SetGeoCalib406Info(This,lpInfo)

#define IEMSGeoCalib406Stats_GetGeoCalib406Info(This,lpInfo)	\
    (This)->lpVtbl -> GetGeoCalib406Info(This,lpInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSGeoCalib406Stats_ResetGeoCalib406Info_Proxy( 
    IEMSGeoCalib406Stats __RPC_FAR * This);


void __RPC_STUB IEMSGeoCalib406Stats_ResetGeoCalib406Info_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSGeoCalib406Stats_SetGeoCalib406Info_Proxy( 
    IEMSGeoCalib406Stats __RPC_FAR * This,
    /* [in] */ EMSGEOCALIB406INFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSGeoCalib406Stats_SetGeoCalib406Info_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSGeoCalib406Stats_GetGeoCalib406Info_Proxy( 
    IEMSGeoCalib406Stats __RPC_FAR * This,
    /* [out] */ EMSGEOCALIB406INFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSGeoCalib406Stats_GetGeoCalib406Info_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSGeoCalib406Stats_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_statgeo_0012 */
/* [local] */ 

typedef /* [unique] */ IEMSGeoCalib406Stats __RPC_FAR *LPEMSGEOCALIB406STATS;



extern RPC_IF_HANDLE __MIDL_itf_statgeo_0012_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_statgeo_0012_v0_0_s_ifspec;

#ifndef __IEMSGeoSummary_INTERFACE_DEFINED__
#define __IEMSGeoSummary_INTERFACE_DEFINED__

/* interface IEMSGeoSummary */
/* [unique][helpstring][uuid][object] */ 


#pragma pack(1)
typedef struct  _tagEMSGEOSUMMARYINFO
    {
    EMSTIME timeStart;
    EMSTIME timeEnd;
    double dDuration;
    double dDurLoss;
    ULONG ulNumAlarms;
    ULONG ulNumWarnings;
    EMSGEOCALIB406INFO calib406Info;
    }	EMSGEOSUMMARYINFO;

typedef struct _tagEMSGEOSUMMARYINFO __RPC_FAR *LPEMSGEOSUMMARYINFO;


#pragma pack()

EXTERN_C const IID IID_IEMSGeoSummary;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("600E9B8C-282C-47f9-9CB2-526057482E43")
    IEMSGeoSummary : public IEMSStatus
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ResetGeoSummaryInfo( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetGeoSummaryInfo( 
            /* [in] */ EMSGEOSUMMARYINFO __RPC_FAR *lpInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetGeoSummaryInfo( 
            /* [out] */ EMSGEOSUMMARYINFO __RPC_FAR *lpInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSGeoSummaryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSGeoSummary __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSGeoSummary __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSGeoSummary __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetGeoSummaryInfo )( 
            IEMSGeoSummary __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGeoSummaryInfo )( 
            IEMSGeoSummary __RPC_FAR * This,
            /* [in] */ EMSGEOSUMMARYINFO __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGeoSummaryInfo )( 
            IEMSGeoSummary __RPC_FAR * This,
            /* [out] */ EMSGEOSUMMARYINFO __RPC_FAR *lpInfo);
        
        END_INTERFACE
    } IEMSGeoSummaryVtbl;

    interface IEMSGeoSummary
    {
        CONST_VTBL struct IEMSGeoSummaryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSGeoSummary_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSGeoSummary_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSGeoSummary_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IEMSGeoSummary_ResetGeoSummaryInfo(This)	\
    (This)->lpVtbl -> ResetGeoSummaryInfo(This)

#define IEMSGeoSummary_SetGeoSummaryInfo(This,lpInfo)	\
    (This)->lpVtbl -> SetGeoSummaryInfo(This,lpInfo)

#define IEMSGeoSummary_GetGeoSummaryInfo(This,lpInfo)	\
    (This)->lpVtbl -> GetGeoSummaryInfo(This,lpInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSGeoSummary_ResetGeoSummaryInfo_Proxy( 
    IEMSGeoSummary __RPC_FAR * This);


void __RPC_STUB IEMSGeoSummary_ResetGeoSummaryInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSGeoSummary_SetGeoSummaryInfo_Proxy( 
    IEMSGeoSummary __RPC_FAR * This,
    /* [in] */ EMSGEOSUMMARYINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSGeoSummary_SetGeoSummaryInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSGeoSummary_GetGeoSummaryInfo_Proxy( 
    IEMSGeoSummary __RPC_FAR * This,
    /* [out] */ EMSGEOSUMMARYINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSGeoSummary_GetGeoSummaryInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSGeoSummary_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_statgeo_0013 */
/* [local] */ 

typedef /* [unique] */ IEMSGeoSummary __RPC_FAR *LPEMSGEOSUMMARY;



extern RPC_IF_HANDLE __MIDL_itf_statgeo_0013_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_statgeo_0013_v0_0_s_ifspec;

#ifndef __IEMSGeoActiveBeaconStats_INTERFACE_DEFINED__
#define __IEMSGeoActiveBeaconStats_INTERFACE_DEFINED__

/* interface IEMSGeoActiveBeaconStats */
/* [unique][helpstring][uuid][object] */ 


#pragma pack(1)
typedef struct  _tagEMSGEOACTIVEBEACONINFO
    {
    ULONG ulNumAlerts;
    ULONG ulNumUniqueAlerts;
    ULONG ulReserved1;
    ULONG ulReserved2;
    ULONG ulReserved3;
    ULONG ulReserved4;
    }	EMSGEOACTIVEBEACONINFO;

typedef struct _tagEMSGEOACTIVEBEACONINFO __RPC_FAR *LPEMSGEOACTIVEBEACONINFO;


#pragma pack()

EXTERN_C const IID IID_IEMSGeoActiveBeaconStats;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("78739D36-D0B3-4b12-BD9B-196919B7BBB9")
    IEMSGeoActiveBeaconStats : public IEMSStatus
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ResetGeoActiveBeaconInfo( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetGeoActiveBeaconInfo( 
            /* [in] */ EMSGEOACTIVEBEACONINFO __RPC_FAR *lpInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetGeoActiveBeaconInfo( 
            /* [out] */ EMSGEOACTIVEBEACONINFO __RPC_FAR *lpInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetGeoActiveBeaconInfoEx( 
            /* [out] */ EMSGEOACTIVEBEACONINFO __RPC_FAR *lpInfo,
            /* [out] */ EMSTIME __RPC_FAR *lpTimeUpdate) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSGeoActiveBeaconStatsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSGeoActiveBeaconStats __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSGeoActiveBeaconStats __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSGeoActiveBeaconStats __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetGeoActiveBeaconInfo )( 
            IEMSGeoActiveBeaconStats __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetGeoActiveBeaconInfo )( 
            IEMSGeoActiveBeaconStats __RPC_FAR * This,
            /* [in] */ EMSGEOACTIVEBEACONINFO __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGeoActiveBeaconInfo )( 
            IEMSGeoActiveBeaconStats __RPC_FAR * This,
            /* [out] */ EMSGEOACTIVEBEACONINFO __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGeoActiveBeaconInfoEx )( 
            IEMSGeoActiveBeaconStats __RPC_FAR * This,
            /* [out] */ EMSGEOACTIVEBEACONINFO __RPC_FAR *lpInfo,
            /* [out] */ EMSTIME __RPC_FAR *lpTimeUpdate);
        
        END_INTERFACE
    } IEMSGeoActiveBeaconStatsVtbl;

    interface IEMSGeoActiveBeaconStats
    {
        CONST_VTBL struct IEMSGeoActiveBeaconStatsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSGeoActiveBeaconStats_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSGeoActiveBeaconStats_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSGeoActiveBeaconStats_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IEMSGeoActiveBeaconStats_ResetGeoActiveBeaconInfo(This)	\
    (This)->lpVtbl -> ResetGeoActiveBeaconInfo(This)

#define IEMSGeoActiveBeaconStats_SetGeoActiveBeaconInfo(This,lpInfo)	\
    (This)->lpVtbl -> SetGeoActiveBeaconInfo(This,lpInfo)

#define IEMSGeoActiveBeaconStats_GetGeoActiveBeaconInfo(This,lpInfo)	\
    (This)->lpVtbl -> GetGeoActiveBeaconInfo(This,lpInfo)

#define IEMSGeoActiveBeaconStats_GetGeoActiveBeaconInfoEx(This,lpInfo,lpTimeUpdate)	\
    (This)->lpVtbl -> GetGeoActiveBeaconInfoEx(This,lpInfo,lpTimeUpdate)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSGeoActiveBeaconStats_ResetGeoActiveBeaconInfo_Proxy( 
    IEMSGeoActiveBeaconStats __RPC_FAR * This);


void __RPC_STUB IEMSGeoActiveBeaconStats_ResetGeoActiveBeaconInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSGeoActiveBeaconStats_SetGeoActiveBeaconInfo_Proxy( 
    IEMSGeoActiveBeaconStats __RPC_FAR * This,
    /* [in] */ EMSGEOACTIVEBEACONINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSGeoActiveBeaconStats_SetGeoActiveBeaconInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSGeoActiveBeaconStats_GetGeoActiveBeaconInfo_Proxy( 
    IEMSGeoActiveBeaconStats __RPC_FAR * This,
    /* [out] */ EMSGEOACTIVEBEACONINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSGeoActiveBeaconStats_GetGeoActiveBeaconInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSGeoActiveBeaconStats_GetGeoActiveBeaconInfoEx_Proxy( 
    IEMSGeoActiveBeaconStats __RPC_FAR * This,
    /* [out] */ EMSGEOACTIVEBEACONINFO __RPC_FAR *lpInfo,
    /* [out] */ EMSTIME __RPC_FAR *lpTimeUpdate);


void __RPC_STUB IEMSGeoActiveBeaconStats_GetGeoActiveBeaconInfoEx_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSGeoActiveBeaconStats_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_statgeo_0014 */
/* [local] */ 

typedef /* [unique] */ IEMSGeoActiveBeaconStats __RPC_FAR *LPEMSGEOACTIVEBEACONSTATS;



extern RPC_IF_HANDLE __MIDL_itf_statgeo_0014_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_statgeo_0014_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
