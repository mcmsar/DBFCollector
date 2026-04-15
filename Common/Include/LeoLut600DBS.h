/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Jun 09 13:28:00 2009
 */
/* Compiler settings for ..\Common\Include\LeoLut600DBS.idl:
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

#ifndef __LeoLut600DBS_h__
#define __LeoLut600DBS_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ICCBCData_FWD_DEFINED__
#define __ICCBCData_FWD_DEFINED__
typedef interface ICCBCData ICCBCData;
#endif 	/* __ICCBCData_FWD_DEFINED__ */


#ifndef __ISARPData_FWD_DEFINED__
#define __ISARPData_FWD_DEFINED__
typedef interface ISARPData ISARPData;
#endif 	/* __ISARPData_FWD_DEFINED__ */


#ifndef __ISARRData_FWD_DEFINED__
#define __ISARRData_FWD_DEFINED__
typedef interface ISARRData ISARRData;
#endif 	/* __ISARRData_FWD_DEFINED__ */


#ifndef __ISpectrum_FWD_DEFINED__
#define __ISpectrum_FWD_DEFINED__
typedef interface ISpectrum ISpectrum;
#endif 	/* __ISpectrum_FWD_DEFINED__ */


#ifndef __ILeoStatus_FWD_DEFINED__
#define __ILeoStatus_FWD_DEFINED__
typedef interface ILeoStatus ILeoStatus;
#endif 	/* __ILeoStatus_FWD_DEFINED__ */


#ifndef __IEMSLogger_FWD_DEFINED__
#define __IEMSLogger_FWD_DEFINED__
typedef interface IEMSLogger IEMSLogger;
#endif 	/* __IEMSLogger_FWD_DEFINED__ */


#ifndef __IEMSLocate_FWD_DEFINED__
#define __IEMSLocate_FWD_DEFINED__
typedef interface IEMSLocate IEMSLocate;
#endif 	/* __IEMSLocate_FWD_DEFINED__ */


#ifndef __ICalibrate406_FWD_DEFINED__
#define __ICalibrate406_FWD_DEFINED__
typedef interface ICalibrate406 ICalibrate406;
#endif 	/* __ICalibrate406_FWD_DEFINED__ */


#ifndef __ICBCOut_FWD_DEFINED__
#define __ICBCOut_FWD_DEFINED__
typedef interface ICBCOut ICBCOut;
#endif 	/* __ICBCOut_FWD_DEFINED__ */


#ifndef __IEMSTLE_FWD_DEFINED__
#define __IEMSTLE_FWD_DEFINED__
typedef interface IEMSTLE IEMSTLE;
#endif 	/* __IEMSTLE_FWD_DEFINED__ */


#ifndef __IAlarmData_FWD_DEFINED__
#define __IAlarmData_FWD_DEFINED__
typedef interface IAlarmData IAlarmData;
#endif 	/* __IAlarmData_FWD_DEFINED__ */


#ifndef __ISatTrack_FWD_DEFINED__
#define __ISatTrack_FWD_DEFINED__
typedef interface ISatTrack ISatTrack;
#endif 	/* __ISatTrack_FWD_DEFINED__ */


#ifndef __IResidualData_FWD_DEFINED__
#define __IResidualData_FWD_DEFINED__
typedef interface IResidualData IResidualData;
#endif 	/* __IResidualData_FWD_DEFINED__ */


#ifndef __IConfigData_FWD_DEFINED__
#define __IConfigData_FWD_DEFINED__
typedef interface IConfigData IConfigData;
#endif 	/* __IConfigData_FWD_DEFINED__ */


#ifndef __ICombined406Data_FWD_DEFINED__
#define __ICombined406Data_FWD_DEFINED__
typedef interface ICombined406Data ICombined406Data;
#endif 	/* __ICombined406Data_FWD_DEFINED__ */


#ifndef __ISarpCalibData_FWD_DEFINED__
#define __ISarpCalibData_FWD_DEFINED__
typedef interface ISarpCalibData ISarpCalibData;
#endif 	/* __ISarpCalibData_FWD_DEFINED__ */


#ifndef __ISarrCalibData_FWD_DEFINED__
#define __ISarrCalibData_FWD_DEFINED__
typedef interface ISarrCalibData ISarrCalibData;
#endif 	/* __ISarrCalibData_FWD_DEFINED__ */


#ifndef __IAudioRiff_FWD_DEFINED__
#define __IAudioRiff_FWD_DEFINED__
typedef interface IAudioRiff IAudioRiff;
#endif 	/* __IAudioRiff_FWD_DEFINED__ */


#ifndef __ICalibrate406Ex_FWD_DEFINED__
#define __ICalibrate406Ex_FWD_DEFINED__
typedef interface ICalibrate406Ex ICalibrate406Ex;
#endif 	/* __ICalibrate406Ex_FWD_DEFINED__ */


#ifndef __ICalibrate406_2_FWD_DEFINED__
#define __ICalibrate406_2_FWD_DEFINED__
typedef interface ICalibrate406_2 ICalibrate406_2;
#endif 	/* __ICalibrate406_2_FWD_DEFINED__ */


#ifndef __IABLData_FWD_DEFINED__
#define __IABLData_FWD_DEFINED__
typedef interface IABLData IABLData;
#endif 	/* __IABLData_FWD_DEFINED__ */


#ifndef __IHealthStatus_FWD_DEFINED__
#define __IHealthStatus_FWD_DEFINED__
typedef interface IHealthStatus IHealthStatus;
#endif 	/* __IHealthStatus_FWD_DEFINED__ */


#ifndef __IHealthDetections_FWD_DEFINED__
#define __IHealthDetections_FWD_DEFINED__
typedef interface IHealthDetections IHealthDetections;
#endif 	/* __IHealthDetections_FWD_DEFINED__ */


#ifndef __IBeaconAdvisory_FWD_DEFINED__
#define __IBeaconAdvisory_FWD_DEFINED__
typedef interface IBeaconAdvisory IBeaconAdvisory;
#endif 	/* __IBeaconAdvisory_FWD_DEFINED__ */


#ifndef __CCBCData_FWD_DEFINED__
#define __CCBCData_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCBCData CCBCData;
#else
typedef struct CCBCData CCBCData;
#endif /* __cplusplus */

#endif 	/* __CCBCData_FWD_DEFINED__ */


#ifndef __SARPData_FWD_DEFINED__
#define __SARPData_FWD_DEFINED__

#ifdef __cplusplus
typedef class SARPData SARPData;
#else
typedef struct SARPData SARPData;
#endif /* __cplusplus */

#endif 	/* __SARPData_FWD_DEFINED__ */


#ifndef __SARRData_FWD_DEFINED__
#define __SARRData_FWD_DEFINED__

#ifdef __cplusplus
typedef class SARRData SARRData;
#else
typedef struct SARRData SARRData;
#endif /* __cplusplus */

#endif 	/* __SARRData_FWD_DEFINED__ */


#ifndef __Spectrum_FWD_DEFINED__
#define __Spectrum_FWD_DEFINED__

#ifdef __cplusplus
typedef class Spectrum Spectrum;
#else
typedef struct Spectrum Spectrum;
#endif /* __cplusplus */

#endif 	/* __Spectrum_FWD_DEFINED__ */


#ifndef __LeoStatus_FWD_DEFINED__
#define __LeoStatus_FWD_DEFINED__

#ifdef __cplusplus
typedef class LeoStatus LeoStatus;
#else
typedef struct LeoStatus LeoStatus;
#endif /* __cplusplus */

#endif 	/* __LeoStatus_FWD_DEFINED__ */


#ifndef __EMSLogger_FWD_DEFINED__
#define __EMSLogger_FWD_DEFINED__

#ifdef __cplusplus
typedef class EMSLogger EMSLogger;
#else
typedef struct EMSLogger EMSLogger;
#endif /* __cplusplus */

#endif 	/* __EMSLogger_FWD_DEFINED__ */


#ifndef __EMSLocate_FWD_DEFINED__
#define __EMSLocate_FWD_DEFINED__

#ifdef __cplusplus
typedef class EMSLocate EMSLocate;
#else
typedef struct EMSLocate EMSLocate;
#endif /* __cplusplus */

#endif 	/* __EMSLocate_FWD_DEFINED__ */


#ifndef __Calibrate406_FWD_DEFINED__
#define __Calibrate406_FWD_DEFINED__

#ifdef __cplusplus
typedef class Calibrate406 Calibrate406;
#else
typedef struct Calibrate406 Calibrate406;
#endif /* __cplusplus */

#endif 	/* __Calibrate406_FWD_DEFINED__ */


#ifndef __CBCOut_FWD_DEFINED__
#define __CBCOut_FWD_DEFINED__

#ifdef __cplusplus
typedef class CBCOut CBCOut;
#else
typedef struct CBCOut CBCOut;
#endif /* __cplusplus */

#endif 	/* __CBCOut_FWD_DEFINED__ */


#ifndef __EMSTLE_FWD_DEFINED__
#define __EMSTLE_FWD_DEFINED__

#ifdef __cplusplus
typedef class EMSTLE EMSTLE;
#else
typedef struct EMSTLE EMSTLE;
#endif /* __cplusplus */

#endif 	/* __EMSTLE_FWD_DEFINED__ */


#ifndef __AlarmData_FWD_DEFINED__
#define __AlarmData_FWD_DEFINED__

#ifdef __cplusplus
typedef class AlarmData AlarmData;
#else
typedef struct AlarmData AlarmData;
#endif /* __cplusplus */

#endif 	/* __AlarmData_FWD_DEFINED__ */


#ifndef __SatTrack_FWD_DEFINED__
#define __SatTrack_FWD_DEFINED__

#ifdef __cplusplus
typedef class SatTrack SatTrack;
#else
typedef struct SatTrack SatTrack;
#endif /* __cplusplus */

#endif 	/* __SatTrack_FWD_DEFINED__ */


#ifndef __ResidualData_FWD_DEFINED__
#define __ResidualData_FWD_DEFINED__

#ifdef __cplusplus
typedef class ResidualData ResidualData;
#else
typedef struct ResidualData ResidualData;
#endif /* __cplusplus */

#endif 	/* __ResidualData_FWD_DEFINED__ */


#ifndef __ConfigData_FWD_DEFINED__
#define __ConfigData_FWD_DEFINED__

#ifdef __cplusplus
typedef class ConfigData ConfigData;
#else
typedef struct ConfigData ConfigData;
#endif /* __cplusplus */

#endif 	/* __ConfigData_FWD_DEFINED__ */


#ifndef __Combined406Data_FWD_DEFINED__
#define __Combined406Data_FWD_DEFINED__

#ifdef __cplusplus
typedef class Combined406Data Combined406Data;
#else
typedef struct Combined406Data Combined406Data;
#endif /* __cplusplus */

#endif 	/* __Combined406Data_FWD_DEFINED__ */


#ifndef __SarpCalibData_FWD_DEFINED__
#define __SarpCalibData_FWD_DEFINED__

#ifdef __cplusplus
typedef class SarpCalibData SarpCalibData;
#else
typedef struct SarpCalibData SarpCalibData;
#endif /* __cplusplus */

#endif 	/* __SarpCalibData_FWD_DEFINED__ */


#ifndef __SarrCalibData_FWD_DEFINED__
#define __SarrCalibData_FWD_DEFINED__

#ifdef __cplusplus
typedef class SarrCalibData SarrCalibData;
#else
typedef struct SarrCalibData SarrCalibData;
#endif /* __cplusplus */

#endif 	/* __SarrCalibData_FWD_DEFINED__ */


#ifndef __AudioRiff_FWD_DEFINED__
#define __AudioRiff_FWD_DEFINED__

#ifdef __cplusplus
typedef class AudioRiff AudioRiff;
#else
typedef struct AudioRiff AudioRiff;
#endif /* __cplusplus */

#endif 	/* __AudioRiff_FWD_DEFINED__ */


#ifndef __Calibrate406Ex_FWD_DEFINED__
#define __Calibrate406Ex_FWD_DEFINED__

#ifdef __cplusplus
typedef class Calibrate406Ex Calibrate406Ex;
#else
typedef struct Calibrate406Ex Calibrate406Ex;
#endif /* __cplusplus */

#endif 	/* __Calibrate406Ex_FWD_DEFINED__ */


#ifndef __Calibrate406_2_FWD_DEFINED__
#define __Calibrate406_2_FWD_DEFINED__

#ifdef __cplusplus
typedef class Calibrate406_2 Calibrate406_2;
#else
typedef struct Calibrate406_2 Calibrate406_2;
#endif /* __cplusplus */

#endif 	/* __Calibrate406_2_FWD_DEFINED__ */


#ifndef __ABLData_FWD_DEFINED__
#define __ABLData_FWD_DEFINED__

#ifdef __cplusplus
typedef class ABLData ABLData;
#else
typedef struct ABLData ABLData;
#endif /* __cplusplus */

#endif 	/* __ABLData_FWD_DEFINED__ */


#ifndef __HealthStatus_FWD_DEFINED__
#define __HealthStatus_FWD_DEFINED__

#ifdef __cplusplus
typedef class HealthStatus HealthStatus;
#else
typedef struct HealthStatus HealthStatus;
#endif /* __cplusplus */

#endif 	/* __HealthStatus_FWD_DEFINED__ */


#ifndef __HealthDetections_FWD_DEFINED__
#define __HealthDetections_FWD_DEFINED__

#ifdef __cplusplus
typedef class HealthDetections HealthDetections;
#else
typedef struct HealthDetections HealthDetections;
#endif /* __cplusplus */

#endif 	/* __HealthDetections_FWD_DEFINED__ */


#ifndef __BeaconAdvisory_FWD_DEFINED__
#define __BeaconAdvisory_FWD_DEFINED__

#ifdef __cplusplus
typedef class BeaconAdvisory BeaconAdvisory;
#else
typedef struct BeaconAdvisory BeaconAdvisory;
#endif /* __cplusplus */

#endif 	/* __BeaconAdvisory_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "cbcdata.h"
#include "sarpdata.h"
#include "sarrdata.h"
#include "spectrum.h"
#include "leostats.h"
#include "emslog.h"
#include "locate.h"
#include "cbcout.h"
#include "calib406.h"
#include "emstle.h"
#include "emsalarm.h"
#include "residual.h"
#include "emsicfg.h"
#include "combine406.h"
#include "sarpcalib.h"
#include "sarrcalib.h"
#include "emsaudio.h"
#include "calib406ext.h"
#include "ABLData.h"
#include "HealthStatusTypes.h"
#include "BeaconAdvisoryTypes.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_LeoLut600DBS_0000 */
/* [local] */ 

#ifndef INC_LEODBSIDL
#define INC_LEODBSIDL

// NOTE:  The BeaconID parameter is currently ignored by all software except for the SitGenerator
// If you add code to use this ... please use -1 to indicate that the parameter is to be ignored
// as a value of 0 (zero) is actually a valid beacon identifier
typedef struct  tagSelectionCriteria
    {
    ULONG ulSatID1;
    ULONG ulSatID2;
    ULONG ulOrbitNumber1;
    ULONG ulOrbitNumber2;
    EMSTIME timeStart;
    EMSTIME timeEnd;
    INT64 i64BeaconID;
    BOOL bOrderByTimestamp;
    BOOL bOrderDescending;
    ULONG ulMaxRecords;
    }	EMSSELECTCRITERIA;



extern RPC_IF_HANDLE __MIDL_itf_LeoLut600DBS_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_LeoLut600DBS_0000_v0_0_s_ifspec;

#ifndef __ICCBCData_INTERFACE_DEFINED__
#define __ICCBCData_INTERFACE_DEFINED__

/* interface ICCBCData */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ICCBCData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C9794F50-63B5-4BC2-87E8-5D7435804878")
    ICCBCData : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE init( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE get_cbcData( 
            /* [out][in] */ EMSCBCDATA __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE put_cbcData( 
            /* [in] */ EMSCBCDATA __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE get_cbcDataSet( 
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ LPEMSCBCDATA __RPC_FAR *__RPC_FAR *papData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICCBCDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICCBCData __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICCBCData __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICCBCData __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *init )( 
            ICCBCData __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_cbcData )( 
            ICCBCData __RPC_FAR * This,
            /* [out][in] */ EMSCBCDATA __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_cbcData )( 
            ICCBCData __RPC_FAR * This,
            /* [in] */ EMSCBCDATA __RPC_FAR *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_cbcDataSet )( 
            ICCBCData __RPC_FAR * This,
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ LPEMSCBCDATA __RPC_FAR *__RPC_FAR *papData);
        
        END_INTERFACE
    } ICCBCDataVtbl;

    interface ICCBCData
    {
        CONST_VTBL struct ICCBCDataVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICCBCData_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICCBCData_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICCBCData_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICCBCData_init(This)	\
    (This)->lpVtbl -> init(This)

#define ICCBCData_get_cbcData(This,pVal)	\
    (This)->lpVtbl -> get_cbcData(This,pVal)

#define ICCBCData_put_cbcData(This,newVal)	\
    (This)->lpVtbl -> put_cbcData(This,newVal)

#define ICCBCData_get_cbcDataSet(This,pCriteria,plCount,papData)	\
    (This)->lpVtbl -> get_cbcDataSet(This,pCriteria,plCount,papData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICCBCData_init_Proxy( 
    ICCBCData __RPC_FAR * This);


void __RPC_STUB ICCBCData_init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICCBCData_get_cbcData_Proxy( 
    ICCBCData __RPC_FAR * This,
    /* [out][in] */ EMSCBCDATA __RPC_FAR *pVal);


void __RPC_STUB ICCBCData_get_cbcData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICCBCData_put_cbcData_Proxy( 
    ICCBCData __RPC_FAR * This,
    /* [in] */ EMSCBCDATA __RPC_FAR *newVal);


void __RPC_STUB ICCBCData_put_cbcData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICCBCData_get_cbcDataSet_Proxy( 
    ICCBCData __RPC_FAR * This,
    /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
    /* [out][in] */ long __RPC_FAR *plCount,
    /* [size_is][size_is][out] */ LPEMSCBCDATA __RPC_FAR *__RPC_FAR *papData);


void __RPC_STUB ICCBCData_get_cbcDataSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICCBCData_INTERFACE_DEFINED__ */


#ifndef __ISARPData_INTERFACE_DEFINED__
#define __ISARPData_INTERFACE_DEFINED__

/* interface ISARPData */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISARPData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D00C36F0-4F1A-4ef3-9220-858896575BB4")
    ISARPData : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE init( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE get_sarpData( 
            /* [out][in] */ EMSSARPDATA __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE put_sarpData( 
            /* [in] */ EMSSARPDATA __RPC_FAR *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISARPDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISARPData __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISARPData __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISARPData __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *init )( 
            ISARPData __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_sarpData )( 
            ISARPData __RPC_FAR * This,
            /* [out][in] */ EMSSARPDATA __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_sarpData )( 
            ISARPData __RPC_FAR * This,
            /* [in] */ EMSSARPDATA __RPC_FAR *newVal);
        
        END_INTERFACE
    } ISARPDataVtbl;

    interface ISARPData
    {
        CONST_VTBL struct ISARPDataVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISARPData_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISARPData_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISARPData_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISARPData_init(This)	\
    (This)->lpVtbl -> init(This)

#define ISARPData_get_sarpData(This,pVal)	\
    (This)->lpVtbl -> get_sarpData(This,pVal)

#define ISARPData_put_sarpData(This,newVal)	\
    (This)->lpVtbl -> put_sarpData(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISARPData_init_Proxy( 
    ISARPData __RPC_FAR * This);


void __RPC_STUB ISARPData_init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISARPData_get_sarpData_Proxy( 
    ISARPData __RPC_FAR * This,
    /* [out][in] */ EMSSARPDATA __RPC_FAR *pVal);


void __RPC_STUB ISARPData_get_sarpData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISARPData_put_sarpData_Proxy( 
    ISARPData __RPC_FAR * This,
    /* [in] */ EMSSARPDATA __RPC_FAR *newVal);


void __RPC_STUB ISARPData_put_sarpData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISARPData_INTERFACE_DEFINED__ */


#ifndef __ISARRData_INTERFACE_DEFINED__
#define __ISARRData_INTERFACE_DEFINED__

/* interface ISARRData */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISARRData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BC010FE6-F1CB-4bab-947B-A220978C17E5")
    ISARRData : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE init( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE get_sarrData( 
            /* [out][in] */ EMSSARRDATA __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE put_sarrData( 
            /* [in] */ EMSSARRDATA __RPC_FAR *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISARRDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISARRData __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISARRData __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISARRData __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *init )( 
            ISARRData __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_sarrData )( 
            ISARRData __RPC_FAR * This,
            /* [out][in] */ EMSSARRDATA __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_sarrData )( 
            ISARRData __RPC_FAR * This,
            /* [in] */ EMSSARRDATA __RPC_FAR *newVal);
        
        END_INTERFACE
    } ISARRDataVtbl;

    interface ISARRData
    {
        CONST_VTBL struct ISARRDataVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISARRData_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISARRData_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISARRData_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISARRData_init(This)	\
    (This)->lpVtbl -> init(This)

#define ISARRData_get_sarrData(This,pVal)	\
    (This)->lpVtbl -> get_sarrData(This,pVal)

#define ISARRData_put_sarrData(This,newVal)	\
    (This)->lpVtbl -> put_sarrData(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISARRData_init_Proxy( 
    ISARRData __RPC_FAR * This);


void __RPC_STUB ISARRData_init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISARRData_get_sarrData_Proxy( 
    ISARRData __RPC_FAR * This,
    /* [out][in] */ EMSSARRDATA __RPC_FAR *pVal);


void __RPC_STUB ISARRData_get_sarrData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISARRData_put_sarrData_Proxy( 
    ISARRData __RPC_FAR * This,
    /* [in] */ EMSSARRDATA __RPC_FAR *newVal);


void __RPC_STUB ISARRData_put_sarrData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISARRData_INTERFACE_DEFINED__ */


#ifndef __ISpectrum_INTERFACE_DEFINED__
#define __ISpectrum_INTERFACE_DEFINED__

/* interface ISpectrum */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISpectrum;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("85444CEB-20BE-476C-A23A-0D2FE217DB64")
    ISpectrum : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE init( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE get_spectrum( 
            /* [out][in] */ EMSSPECTRUM __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE put_spectrum( 
            /* [in] */ EMSSPECTRUM __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE get_IDSet( 
            /* [in] */ EMSSIGDATAID minID,
            /* [in] */ EMSSIGDATAID maxID,
            /* [in] */ ULONG sizeIn,
            /* [size_is][out] */ EMSSIGDATAID __RPC_FAR pIDMatches[  ],
            /* [out] */ ULONG __RPC_FAR *pIDMatchesCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE get_spectrumDataSet( 
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ LPEMSSPECTRUM __RPC_FAR *__RPC_FAR *papData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISpectrumVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISpectrum __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISpectrum __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISpectrum __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *init )( 
            ISpectrum __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_spectrum )( 
            ISpectrum __RPC_FAR * This,
            /* [out][in] */ EMSSPECTRUM __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_spectrum )( 
            ISpectrum __RPC_FAR * This,
            /* [in] */ EMSSPECTRUM __RPC_FAR *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_IDSet )( 
            ISpectrum __RPC_FAR * This,
            /* [in] */ EMSSIGDATAID minID,
            /* [in] */ EMSSIGDATAID maxID,
            /* [in] */ ULONG sizeIn,
            /* [size_is][out] */ EMSSIGDATAID __RPC_FAR pIDMatches[  ],
            /* [out] */ ULONG __RPC_FAR *pIDMatchesCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_spectrumDataSet )( 
            ISpectrum __RPC_FAR * This,
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ LPEMSSPECTRUM __RPC_FAR *__RPC_FAR *papData);
        
        END_INTERFACE
    } ISpectrumVtbl;

    interface ISpectrum
    {
        CONST_VTBL struct ISpectrumVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISpectrum_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISpectrum_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISpectrum_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISpectrum_init(This)	\
    (This)->lpVtbl -> init(This)

#define ISpectrum_get_spectrum(This,pVal)	\
    (This)->lpVtbl -> get_spectrum(This,pVal)

#define ISpectrum_put_spectrum(This,newVal)	\
    (This)->lpVtbl -> put_spectrum(This,newVal)

#define ISpectrum_get_IDSet(This,minID,maxID,sizeIn,pIDMatches,pIDMatchesCount)	\
    (This)->lpVtbl -> get_IDSet(This,minID,maxID,sizeIn,pIDMatches,pIDMatchesCount)

#define ISpectrum_get_spectrumDataSet(This,pCriteria,plCount,papData)	\
    (This)->lpVtbl -> get_spectrumDataSet(This,pCriteria,plCount,papData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISpectrum_init_Proxy( 
    ISpectrum __RPC_FAR * This);


void __RPC_STUB ISpectrum_init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISpectrum_get_spectrum_Proxy( 
    ISpectrum __RPC_FAR * This,
    /* [out][in] */ EMSSPECTRUM __RPC_FAR *pVal);


void __RPC_STUB ISpectrum_get_spectrum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISpectrum_put_spectrum_Proxy( 
    ISpectrum __RPC_FAR * This,
    /* [in] */ EMSSPECTRUM __RPC_FAR *newVal);


void __RPC_STUB ISpectrum_put_spectrum_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISpectrum_get_IDSet_Proxy( 
    ISpectrum __RPC_FAR * This,
    /* [in] */ EMSSIGDATAID minID,
    /* [in] */ EMSSIGDATAID maxID,
    /* [in] */ ULONG sizeIn,
    /* [size_is][out] */ EMSSIGDATAID __RPC_FAR pIDMatches[  ],
    /* [out] */ ULONG __RPC_FAR *pIDMatchesCount);


void __RPC_STUB ISpectrum_get_IDSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISpectrum_get_spectrumDataSet_Proxy( 
    ISpectrum __RPC_FAR * This,
    /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
    /* [out][in] */ long __RPC_FAR *plCount,
    /* [size_is][size_is][out] */ LPEMSSPECTRUM __RPC_FAR *__RPC_FAR *papData);


void __RPC_STUB ISpectrum_get_spectrumDataSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISpectrum_INTERFACE_DEFINED__ */


#ifndef __ILeoStatus_INTERFACE_DEFINED__
#define __ILeoStatus_INTERFACE_DEFINED__

/* interface ILeoStatus */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ILeoStatus;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("49F79346-37DF-4529-80C7-AD9417D85100")
    ILeoStatus : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE init( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE put_leoStats( 
            /* [in] */ EMSLEOSTATUSUPDATE __RPC_FAR *newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE get_leoStatsDataSet( 
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [in] */ const EMSLEOSTATUSTYPE ceType,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ LPEMSLEOSTATUSUPDATE __RPC_FAR *__RPC_FAR *papData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILeoStatusVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ILeoStatus __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ILeoStatus __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ILeoStatus __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *init )( 
            ILeoStatus __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_leoStats )( 
            ILeoStatus __RPC_FAR * This,
            /* [in] */ EMSLEOSTATUSUPDATE __RPC_FAR *newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_leoStatsDataSet )( 
            ILeoStatus __RPC_FAR * This,
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [in] */ const EMSLEOSTATUSTYPE ceType,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ LPEMSLEOSTATUSUPDATE __RPC_FAR *__RPC_FAR *papData);
        
        END_INTERFACE
    } ILeoStatusVtbl;

    interface ILeoStatus
    {
        CONST_VTBL struct ILeoStatusVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILeoStatus_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ILeoStatus_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ILeoStatus_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ILeoStatus_init(This)	\
    (This)->lpVtbl -> init(This)

#define ILeoStatus_put_leoStats(This,newVal)	\
    (This)->lpVtbl -> put_leoStats(This,newVal)

#define ILeoStatus_get_leoStatsDataSet(This,pCriteria,ceType,plCount,papData)	\
    (This)->lpVtbl -> get_leoStatsDataSet(This,pCriteria,ceType,plCount,papData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILeoStatus_init_Proxy( 
    ILeoStatus __RPC_FAR * This);


void __RPC_STUB ILeoStatus_init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILeoStatus_put_leoStats_Proxy( 
    ILeoStatus __RPC_FAR * This,
    /* [in] */ EMSLEOSTATUSUPDATE __RPC_FAR *newVal);


void __RPC_STUB ILeoStatus_put_leoStats_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ILeoStatus_get_leoStatsDataSet_Proxy( 
    ILeoStatus __RPC_FAR * This,
    /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
    /* [in] */ const EMSLEOSTATUSTYPE ceType,
    /* [out][in] */ long __RPC_FAR *plCount,
    /* [size_is][size_is][out] */ LPEMSLEOSTATUSUPDATE __RPC_FAR *__RPC_FAR *papData);


void __RPC_STUB ILeoStatus_get_leoStatsDataSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ILeoStatus_INTERFACE_DEFINED__ */


#ifndef __IEMSLogger_INTERFACE_DEFINED__
#define __IEMSLogger_INTERFACE_DEFINED__

/* interface IEMSLogger */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSLogger;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CC9C5777-17B8-4CA5-8145-7A966E86DFFA")
    IEMSLogger : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE init( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE get_logData( 
            /* [out][in] */ EMSLOGDATA __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE put_logData( 
            /* [in] */ EMSLOGDATA __RPC_FAR *pNewVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE get_logDataSet( 
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ LPEMSLOGDATA __RPC_FAR *__RPC_FAR *papData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSLoggerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSLogger __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSLogger __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSLogger __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *init )( 
            IEMSLogger __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_logData )( 
            IEMSLogger __RPC_FAR * This,
            /* [out][in] */ EMSLOGDATA __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_logData )( 
            IEMSLogger __RPC_FAR * This,
            /* [in] */ EMSLOGDATA __RPC_FAR *pNewVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_logDataSet )( 
            IEMSLogger __RPC_FAR * This,
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ LPEMSLOGDATA __RPC_FAR *__RPC_FAR *papData);
        
        END_INTERFACE
    } IEMSLoggerVtbl;

    interface IEMSLogger
    {
        CONST_VTBL struct IEMSLoggerVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSLogger_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSLogger_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSLogger_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSLogger_init(This)	\
    (This)->lpVtbl -> init(This)

#define IEMSLogger_get_logData(This,pVal)	\
    (This)->lpVtbl -> get_logData(This,pVal)

#define IEMSLogger_put_logData(This,pNewVal)	\
    (This)->lpVtbl -> put_logData(This,pNewVal)

#define IEMSLogger_get_logDataSet(This,pCriteria,plCount,papData)	\
    (This)->lpVtbl -> get_logDataSet(This,pCriteria,plCount,papData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEMSLogger_init_Proxy( 
    IEMSLogger __RPC_FAR * This);


void __RPC_STUB IEMSLogger_init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEMSLogger_get_logData_Proxy( 
    IEMSLogger __RPC_FAR * This,
    /* [out][in] */ EMSLOGDATA __RPC_FAR *pVal);


void __RPC_STUB IEMSLogger_get_logData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEMSLogger_put_logData_Proxy( 
    IEMSLogger __RPC_FAR * This,
    /* [in] */ EMSLOGDATA __RPC_FAR *pNewVal);


void __RPC_STUB IEMSLogger_put_logData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEMSLogger_get_logDataSet_Proxy( 
    IEMSLogger __RPC_FAR * This,
    /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
    /* [out][in] */ long __RPC_FAR *plCount,
    /* [size_is][size_is][out] */ LPEMSLOGDATA __RPC_FAR *__RPC_FAR *papData);


void __RPC_STUB IEMSLogger_get_logDataSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSLogger_INTERFACE_DEFINED__ */


#ifndef __IEMSLocate_INTERFACE_DEFINED__
#define __IEMSLocate_INTERFACE_DEFINED__

/* interface IEMSLocate */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSLocate;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EC4EEC24-54A1-4D28-AE46-078AF0C9CC7A")
    IEMSLocate : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE init( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE get_locateData( 
            /* [out][in] */ EMSLOCATE __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE put_locateData( 
            /* [in] */ EMSLOCATE __RPC_FAR *pNewVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE get_locateDataSet( 
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ LPEMSLOCATE __RPC_FAR *__RPC_FAR *papData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSLocateVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSLocate __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSLocate __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSLocate __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *init )( 
            IEMSLocate __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_locateData )( 
            IEMSLocate __RPC_FAR * This,
            /* [out][in] */ EMSLOCATE __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_locateData )( 
            IEMSLocate __RPC_FAR * This,
            /* [in] */ EMSLOCATE __RPC_FAR *pNewVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_locateDataSet )( 
            IEMSLocate __RPC_FAR * This,
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ LPEMSLOCATE __RPC_FAR *__RPC_FAR *papData);
        
        END_INTERFACE
    } IEMSLocateVtbl;

    interface IEMSLocate
    {
        CONST_VTBL struct IEMSLocateVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSLocate_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSLocate_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSLocate_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSLocate_init(This)	\
    (This)->lpVtbl -> init(This)

#define IEMSLocate_get_locateData(This,pVal)	\
    (This)->lpVtbl -> get_locateData(This,pVal)

#define IEMSLocate_put_locateData(This,pNewVal)	\
    (This)->lpVtbl -> put_locateData(This,pNewVal)

#define IEMSLocate_get_locateDataSet(This,pCriteria,plCount,papData)	\
    (This)->lpVtbl -> get_locateDataSet(This,pCriteria,plCount,papData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEMSLocate_init_Proxy( 
    IEMSLocate __RPC_FAR * This);


void __RPC_STUB IEMSLocate_init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEMSLocate_get_locateData_Proxy( 
    IEMSLocate __RPC_FAR * This,
    /* [out][in] */ EMSLOCATE __RPC_FAR *pVal);


void __RPC_STUB IEMSLocate_get_locateData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEMSLocate_put_locateData_Proxy( 
    IEMSLocate __RPC_FAR * This,
    /* [in] */ EMSLOCATE __RPC_FAR *pNewVal);


void __RPC_STUB IEMSLocate_put_locateData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEMSLocate_get_locateDataSet_Proxy( 
    IEMSLocate __RPC_FAR * This,
    /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
    /* [out][in] */ long __RPC_FAR *plCount,
    /* [size_is][size_is][out] */ LPEMSLOCATE __RPC_FAR *__RPC_FAR *papData);


void __RPC_STUB IEMSLocate_get_locateDataSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSLocate_INTERFACE_DEFINED__ */


#ifndef __ICalibrate406_INTERFACE_DEFINED__
#define __ICalibrate406_INTERFACE_DEFINED__

/* interface ICalibrate406 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ICalibrate406;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9CDFEC2D-0742-48CE-B94D-518B10974508")
    ICalibrate406 : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE init( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE put_calib406( 
            /* [in] */ EMSCALIB406DATA __RPC_FAR *pNewVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE get_calib406DataSet( 
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ LPEMSCALIB406DATA __RPC_FAR *__RPC_FAR *papData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICalibrate406Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICalibrate406 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICalibrate406 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICalibrate406 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *init )( 
            ICalibrate406 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_calib406 )( 
            ICalibrate406 __RPC_FAR * This,
            /* [in] */ EMSCALIB406DATA __RPC_FAR *pNewVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_calib406DataSet )( 
            ICalibrate406 __RPC_FAR * This,
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ LPEMSCALIB406DATA __RPC_FAR *__RPC_FAR *papData);
        
        END_INTERFACE
    } ICalibrate406Vtbl;

    interface ICalibrate406
    {
        CONST_VTBL struct ICalibrate406Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICalibrate406_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICalibrate406_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICalibrate406_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICalibrate406_init(This)	\
    (This)->lpVtbl -> init(This)

#define ICalibrate406_put_calib406(This,pNewVal)	\
    (This)->lpVtbl -> put_calib406(This,pNewVal)

#define ICalibrate406_get_calib406DataSet(This,pCriteria,plCount,papData)	\
    (This)->lpVtbl -> get_calib406DataSet(This,pCriteria,plCount,papData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICalibrate406_init_Proxy( 
    ICalibrate406 __RPC_FAR * This);


void __RPC_STUB ICalibrate406_init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICalibrate406_put_calib406_Proxy( 
    ICalibrate406 __RPC_FAR * This,
    /* [in] */ EMSCALIB406DATA __RPC_FAR *pNewVal);


void __RPC_STUB ICalibrate406_put_calib406_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICalibrate406_get_calib406DataSet_Proxy( 
    ICalibrate406 __RPC_FAR * This,
    /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
    /* [out][in] */ long __RPC_FAR *plCount,
    /* [size_is][size_is][out] */ LPEMSCALIB406DATA __RPC_FAR *__RPC_FAR *papData);


void __RPC_STUB ICalibrate406_get_calib406DataSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICalibrate406_INTERFACE_DEFINED__ */


#ifndef __ICBCOut_INTERFACE_DEFINED__
#define __ICBCOut_INTERFACE_DEFINED__

/* interface ICBCOut */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ICBCOut;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9A328FB0-AFE1-4623-831A-3A40637161C8")
    ICBCOut : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE init( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE put_cbcOutData( 
            /* [in] */ EMSCBCOUTPUTDATA __RPC_FAR *pNewVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICBCOutVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICBCOut __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICBCOut __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICBCOut __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *init )( 
            ICBCOut __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_cbcOutData )( 
            ICBCOut __RPC_FAR * This,
            /* [in] */ EMSCBCOUTPUTDATA __RPC_FAR *pNewVal);
        
        END_INTERFACE
    } ICBCOutVtbl;

    interface ICBCOut
    {
        CONST_VTBL struct ICBCOutVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICBCOut_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICBCOut_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICBCOut_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICBCOut_init(This)	\
    (This)->lpVtbl -> init(This)

#define ICBCOut_put_cbcOutData(This,pNewVal)	\
    (This)->lpVtbl -> put_cbcOutData(This,pNewVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICBCOut_init_Proxy( 
    ICBCOut __RPC_FAR * This);


void __RPC_STUB ICBCOut_init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICBCOut_put_cbcOutData_Proxy( 
    ICBCOut __RPC_FAR * This,
    /* [in] */ EMSCBCOUTPUTDATA __RPC_FAR *pNewVal);


void __RPC_STUB ICBCOut_put_cbcOutData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICBCOut_INTERFACE_DEFINED__ */


#ifndef __IEMSTLE_INTERFACE_DEFINED__
#define __IEMSTLE_INTERFACE_DEFINED__

/* interface IEMSTLE */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSTLE;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B24B8C75-EBDC-452A-B960-C7B66A4DE6F5")
    IEMSTLE : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE init( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE put_tleData( 
            /* [in] */ EMSTLERECORD __RPC_FAR *pNewVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE get_tleDataSet( 
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ LPEMSTLERECORD __RPC_FAR *__RPC_FAR *papData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSTLEVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSTLE __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSTLE __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSTLE __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *init )( 
            IEMSTLE __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_tleData )( 
            IEMSTLE __RPC_FAR * This,
            /* [in] */ EMSTLERECORD __RPC_FAR *pNewVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_tleDataSet )( 
            IEMSTLE __RPC_FAR * This,
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ LPEMSTLERECORD __RPC_FAR *__RPC_FAR *papData);
        
        END_INTERFACE
    } IEMSTLEVtbl;

    interface IEMSTLE
    {
        CONST_VTBL struct IEMSTLEVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSTLE_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSTLE_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSTLE_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSTLE_init(This)	\
    (This)->lpVtbl -> init(This)

#define IEMSTLE_put_tleData(This,pNewVal)	\
    (This)->lpVtbl -> put_tleData(This,pNewVal)

#define IEMSTLE_get_tleDataSet(This,pCriteria,plCount,papData)	\
    (This)->lpVtbl -> get_tleDataSet(This,pCriteria,plCount,papData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEMSTLE_init_Proxy( 
    IEMSTLE __RPC_FAR * This);


void __RPC_STUB IEMSTLE_init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEMSTLE_put_tleData_Proxy( 
    IEMSTLE __RPC_FAR * This,
    /* [in] */ EMSTLERECORD __RPC_FAR *pNewVal);


void __RPC_STUB IEMSTLE_put_tleData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IEMSTLE_get_tleDataSet_Proxy( 
    IEMSTLE __RPC_FAR * This,
    /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
    /* [out][in] */ long __RPC_FAR *plCount,
    /* [size_is][size_is][out] */ LPEMSTLERECORD __RPC_FAR *__RPC_FAR *papData);


void __RPC_STUB IEMSTLE_get_tleDataSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSTLE_INTERFACE_DEFINED__ */


#ifndef __IAlarmData_INTERFACE_DEFINED__
#define __IAlarmData_INTERFACE_DEFINED__

/* interface IAlarmData */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAlarmData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7C3ED967-7F3A-427A-B091-889782F5EAA8")
    IAlarmData : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE init( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE put_alarmData( 
            /* [in] */ EMSALARMDATA __RPC_FAR *pNewVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAlarmDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAlarmData __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAlarmData __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAlarmData __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *init )( 
            IAlarmData __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_alarmData )( 
            IAlarmData __RPC_FAR * This,
            /* [in] */ EMSALARMDATA __RPC_FAR *pNewVal);
        
        END_INTERFACE
    } IAlarmDataVtbl;

    interface IAlarmData
    {
        CONST_VTBL struct IAlarmDataVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAlarmData_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAlarmData_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAlarmData_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAlarmData_init(This)	\
    (This)->lpVtbl -> init(This)

#define IAlarmData_put_alarmData(This,pNewVal)	\
    (This)->lpVtbl -> put_alarmData(This,pNewVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IAlarmData_init_Proxy( 
    IAlarmData __RPC_FAR * This);


void __RPC_STUB IAlarmData_init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IAlarmData_put_alarmData_Proxy( 
    IAlarmData __RPC_FAR * This,
    /* [in] */ EMSALARMDATA __RPC_FAR *pNewVal);


void __RPC_STUB IAlarmData_put_alarmData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAlarmData_INTERFACE_DEFINED__ */


#ifndef __ISatTrack_INTERFACE_DEFINED__
#define __ISatTrack_INTERFACE_DEFINED__

/* interface ISatTrack */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISatTrack;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BAB87800-EB68-4BCA-92B5-874CD9C0367B")
    ISatTrack : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE init( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE put_satTrackRecord( 
            /* [in] */ EMSSATTRACKRECORD __RPC_FAR *pNewVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE get_satTrackRecords( 
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ LPEMSSATTRACKRECORD __RPC_FAR *__RPC_FAR *papData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISatTrackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISatTrack __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISatTrack __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISatTrack __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *init )( 
            ISatTrack __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_satTrackRecord )( 
            ISatTrack __RPC_FAR * This,
            /* [in] */ EMSSATTRACKRECORD __RPC_FAR *pNewVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_satTrackRecords )( 
            ISatTrack __RPC_FAR * This,
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ LPEMSSATTRACKRECORD __RPC_FAR *__RPC_FAR *papData);
        
        END_INTERFACE
    } ISatTrackVtbl;

    interface ISatTrack
    {
        CONST_VTBL struct ISatTrackVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISatTrack_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISatTrack_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISatTrack_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISatTrack_init(This)	\
    (This)->lpVtbl -> init(This)

#define ISatTrack_put_satTrackRecord(This,pNewVal)	\
    (This)->lpVtbl -> put_satTrackRecord(This,pNewVal)

#define ISatTrack_get_satTrackRecords(This,pCriteria,plCount,papData)	\
    (This)->lpVtbl -> get_satTrackRecords(This,pCriteria,plCount,papData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISatTrack_init_Proxy( 
    ISatTrack __RPC_FAR * This);


void __RPC_STUB ISatTrack_init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISatTrack_put_satTrackRecord_Proxy( 
    ISatTrack __RPC_FAR * This,
    /* [in] */ EMSSATTRACKRECORD __RPC_FAR *pNewVal);


void __RPC_STUB ISatTrack_put_satTrackRecord_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISatTrack_get_satTrackRecords_Proxy( 
    ISatTrack __RPC_FAR * This,
    /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
    /* [out][in] */ long __RPC_FAR *plCount,
    /* [size_is][size_is][out] */ LPEMSSATTRACKRECORD __RPC_FAR *__RPC_FAR *papData);


void __RPC_STUB ISatTrack_get_satTrackRecords_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISatTrack_INTERFACE_DEFINED__ */


#ifndef __IResidualData_INTERFACE_DEFINED__
#define __IResidualData_INTERFACE_DEFINED__

/* interface IResidualData */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IResidualData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FAB32507-D244-4665-8D6D-0D9231FEC795")
    IResidualData : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE init( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE get_residualData( 
            /* [out][in] */ EMSRESIDUALDATA __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE put_residualData( 
            /* [in] */ EMSRESIDUALDATA __RPC_FAR *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IResidualDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IResidualData __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IResidualData __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IResidualData __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *init )( 
            IResidualData __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_residualData )( 
            IResidualData __RPC_FAR * This,
            /* [out][in] */ EMSRESIDUALDATA __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_residualData )( 
            IResidualData __RPC_FAR * This,
            /* [in] */ EMSRESIDUALDATA __RPC_FAR *newVal);
        
        END_INTERFACE
    } IResidualDataVtbl;

    interface IResidualData
    {
        CONST_VTBL struct IResidualDataVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IResidualData_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IResidualData_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IResidualData_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IResidualData_init(This)	\
    (This)->lpVtbl -> init(This)

#define IResidualData_get_residualData(This,pVal)	\
    (This)->lpVtbl -> get_residualData(This,pVal)

#define IResidualData_put_residualData(This,newVal)	\
    (This)->lpVtbl -> put_residualData(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IResidualData_init_Proxy( 
    IResidualData __RPC_FAR * This);


void __RPC_STUB IResidualData_init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IResidualData_get_residualData_Proxy( 
    IResidualData __RPC_FAR * This,
    /* [out][in] */ EMSRESIDUALDATA __RPC_FAR *pVal);


void __RPC_STUB IResidualData_get_residualData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IResidualData_put_residualData_Proxy( 
    IResidualData __RPC_FAR * This,
    /* [in] */ EMSRESIDUALDATA __RPC_FAR *newVal);


void __RPC_STUB IResidualData_put_residualData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IResidualData_INTERFACE_DEFINED__ */


#ifndef __IConfigData_INTERFACE_DEFINED__
#define __IConfigData_INTERFACE_DEFINED__

/* interface IConfigData */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IConfigData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D1FD29BB-2A5D-4B2B-A81D-889E76B7CF97")
    IConfigData : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE init( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE get_configData( 
            /* [out][in] */ EMSCONFIGRECORD __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE put_configData( 
            /* [in] */ EMSCONFIGRECORD __RPC_FAR *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IConfigDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IConfigData __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IConfigData __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IConfigData __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *init )( 
            IConfigData __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_configData )( 
            IConfigData __RPC_FAR * This,
            /* [out][in] */ EMSCONFIGRECORD __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_configData )( 
            IConfigData __RPC_FAR * This,
            /* [in] */ EMSCONFIGRECORD __RPC_FAR *newVal);
        
        END_INTERFACE
    } IConfigDataVtbl;

    interface IConfigData
    {
        CONST_VTBL struct IConfigDataVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IConfigData_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IConfigData_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IConfigData_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IConfigData_init(This)	\
    (This)->lpVtbl -> init(This)

#define IConfigData_get_configData(This,pVal)	\
    (This)->lpVtbl -> get_configData(This,pVal)

#define IConfigData_put_configData(This,newVal)	\
    (This)->lpVtbl -> put_configData(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IConfigData_init_Proxy( 
    IConfigData __RPC_FAR * This);


void __RPC_STUB IConfigData_init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IConfigData_get_configData_Proxy( 
    IConfigData __RPC_FAR * This,
    /* [out][in] */ EMSCONFIGRECORD __RPC_FAR *pVal);


void __RPC_STUB IConfigData_get_configData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IConfigData_put_configData_Proxy( 
    IConfigData __RPC_FAR * This,
    /* [in] */ EMSCONFIGRECORD __RPC_FAR *newVal);


void __RPC_STUB IConfigData_put_configData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IConfigData_INTERFACE_DEFINED__ */


#ifndef __ICombined406Data_INTERFACE_DEFINED__
#define __ICombined406Data_INTERFACE_DEFINED__

/* interface ICombined406Data */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ICombined406Data;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FF4846DB-3F97-4D39-BA98-1DC1B8394257")
    ICombined406Data : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE init( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE get_combined406Data( 
            /* [out][in] */ EMSCOMBINE406DATA __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE put_combined406Data( 
            /* [in] */ EMSCOMBINE406DATA __RPC_FAR *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICombined406DataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICombined406Data __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICombined406Data __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICombined406Data __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *init )( 
            ICombined406Data __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_combined406Data )( 
            ICombined406Data __RPC_FAR * This,
            /* [out][in] */ EMSCOMBINE406DATA __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_combined406Data )( 
            ICombined406Data __RPC_FAR * This,
            /* [in] */ EMSCOMBINE406DATA __RPC_FAR *newVal);
        
        END_INTERFACE
    } ICombined406DataVtbl;

    interface ICombined406Data
    {
        CONST_VTBL struct ICombined406DataVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICombined406Data_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICombined406Data_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICombined406Data_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICombined406Data_init(This)	\
    (This)->lpVtbl -> init(This)

#define ICombined406Data_get_combined406Data(This,pVal)	\
    (This)->lpVtbl -> get_combined406Data(This,pVal)

#define ICombined406Data_put_combined406Data(This,newVal)	\
    (This)->lpVtbl -> put_combined406Data(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICombined406Data_init_Proxy( 
    ICombined406Data __RPC_FAR * This);


void __RPC_STUB ICombined406Data_init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICombined406Data_get_combined406Data_Proxy( 
    ICombined406Data __RPC_FAR * This,
    /* [out][in] */ EMSCOMBINE406DATA __RPC_FAR *pVal);


void __RPC_STUB ICombined406Data_get_combined406Data_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICombined406Data_put_combined406Data_Proxy( 
    ICombined406Data __RPC_FAR * This,
    /* [in] */ EMSCOMBINE406DATA __RPC_FAR *newVal);


void __RPC_STUB ICombined406Data_put_combined406Data_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICombined406Data_INTERFACE_DEFINED__ */


#ifndef __ISarpCalibData_INTERFACE_DEFINED__
#define __ISarpCalibData_INTERFACE_DEFINED__

/* interface ISarpCalibData */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISarpCalibData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BBA571BA-312B-4C4C-85AA-5A7AD0192A1C")
    ISarpCalibData : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE init( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE get_sarpCalibDataSet( 
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ LPEMSSARPCALIBDATA __RPC_FAR *__RPC_FAR *papData) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE put_sarpCalibData( 
            /* [in] */ EMSSARPCALIBDATA __RPC_FAR *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISarpCalibDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISarpCalibData __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISarpCalibData __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISarpCalibData __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *init )( 
            ISarpCalibData __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_sarpCalibDataSet )( 
            ISarpCalibData __RPC_FAR * This,
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ LPEMSSARPCALIBDATA __RPC_FAR *__RPC_FAR *papData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_sarpCalibData )( 
            ISarpCalibData __RPC_FAR * This,
            /* [in] */ EMSSARPCALIBDATA __RPC_FAR *newVal);
        
        END_INTERFACE
    } ISarpCalibDataVtbl;

    interface ISarpCalibData
    {
        CONST_VTBL struct ISarpCalibDataVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISarpCalibData_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISarpCalibData_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISarpCalibData_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISarpCalibData_init(This)	\
    (This)->lpVtbl -> init(This)

#define ISarpCalibData_get_sarpCalibDataSet(This,pCriteria,plCount,papData)	\
    (This)->lpVtbl -> get_sarpCalibDataSet(This,pCriteria,plCount,papData)

#define ISarpCalibData_put_sarpCalibData(This,newVal)	\
    (This)->lpVtbl -> put_sarpCalibData(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISarpCalibData_init_Proxy( 
    ISarpCalibData __RPC_FAR * This);


void __RPC_STUB ISarpCalibData_init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISarpCalibData_get_sarpCalibDataSet_Proxy( 
    ISarpCalibData __RPC_FAR * This,
    /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
    /* [out][in] */ long __RPC_FAR *plCount,
    /* [size_is][size_is][out] */ LPEMSSARPCALIBDATA __RPC_FAR *__RPC_FAR *papData);


void __RPC_STUB ISarpCalibData_get_sarpCalibDataSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISarpCalibData_put_sarpCalibData_Proxy( 
    ISarpCalibData __RPC_FAR * This,
    /* [in] */ EMSSARPCALIBDATA __RPC_FAR *newVal);


void __RPC_STUB ISarpCalibData_put_sarpCalibData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISarpCalibData_INTERFACE_DEFINED__ */


#ifndef __ISarrCalibData_INTERFACE_DEFINED__
#define __ISarrCalibData_INTERFACE_DEFINED__

/* interface ISarrCalibData */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISarrCalibData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2DA81053-2E59-40A1-8851-BC6A96447061")
    ISarrCalibData : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE init( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE get_sarrCalibDataSet( 
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ LPEMSSARRCALIBDATA __RPC_FAR *__RPC_FAR *papData) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE put_sarrCalibData( 
            /* [in] */ EMSSARRCALIBDATA __RPC_FAR *newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISarrCalibDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISarrCalibData __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISarrCalibData __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISarrCalibData __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *init )( 
            ISarrCalibData __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_sarrCalibDataSet )( 
            ISarrCalibData __RPC_FAR * This,
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ LPEMSSARRCALIBDATA __RPC_FAR *__RPC_FAR *papData);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_sarrCalibData )( 
            ISarrCalibData __RPC_FAR * This,
            /* [in] */ EMSSARRCALIBDATA __RPC_FAR *newVal);
        
        END_INTERFACE
    } ISarrCalibDataVtbl;

    interface ISarrCalibData
    {
        CONST_VTBL struct ISarrCalibDataVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISarrCalibData_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISarrCalibData_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISarrCalibData_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISarrCalibData_init(This)	\
    (This)->lpVtbl -> init(This)

#define ISarrCalibData_get_sarrCalibDataSet(This,pCriteria,plCount,papData)	\
    (This)->lpVtbl -> get_sarrCalibDataSet(This,pCriteria,plCount,papData)

#define ISarrCalibData_put_sarrCalibData(This,newVal)	\
    (This)->lpVtbl -> put_sarrCalibData(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISarrCalibData_init_Proxy( 
    ISarrCalibData __RPC_FAR * This);


void __RPC_STUB ISarrCalibData_init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISarrCalibData_get_sarrCalibDataSet_Proxy( 
    ISarrCalibData __RPC_FAR * This,
    /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
    /* [out][in] */ long __RPC_FAR *plCount,
    /* [size_is][size_is][out] */ LPEMSSARRCALIBDATA __RPC_FAR *__RPC_FAR *papData);


void __RPC_STUB ISarrCalibData_get_sarrCalibDataSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISarrCalibData_put_sarrCalibData_Proxy( 
    ISarrCalibData __RPC_FAR * This,
    /* [in] */ EMSSARRCALIBDATA __RPC_FAR *newVal);


void __RPC_STUB ISarrCalibData_put_sarrCalibData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISarrCalibData_INTERFACE_DEFINED__ */


#ifndef __IAudioRiff_INTERFACE_DEFINED__
#define __IAudioRiff_INTERFACE_DEFINED__

/* interface IAudioRiff */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAudioRiff;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4E566532-09F0-4E41-B685-C64EFA36FA5A")
    IAudioRiff : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE init( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE get_audioRiffData( 
            /* [out][in] */ EMSAUDIODATARECORD_RIFF __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE put_audioRiffData( 
            /* [in] */ EMSAUDIODATARECORD_RIFF __RPC_FAR *pNewVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE get_audioRiffDataSet( 
            /* [in] */ EMSAUDIOSELECTCRITERIA __RPC_FAR *pAudioCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ LPEMSAUDIODATARECORD_RIFF __RPC_FAR *__RPC_FAR *papData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAudioRiffVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAudioRiff __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAudioRiff __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAudioRiff __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *init )( 
            IAudioRiff __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_audioRiffData )( 
            IAudioRiff __RPC_FAR * This,
            /* [out][in] */ EMSAUDIODATARECORD_RIFF __RPC_FAR *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_audioRiffData )( 
            IAudioRiff __RPC_FAR * This,
            /* [in] */ EMSAUDIODATARECORD_RIFF __RPC_FAR *pNewVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_audioRiffDataSet )( 
            IAudioRiff __RPC_FAR * This,
            /* [in] */ EMSAUDIOSELECTCRITERIA __RPC_FAR *pAudioCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ LPEMSAUDIODATARECORD_RIFF __RPC_FAR *__RPC_FAR *papData);
        
        END_INTERFACE
    } IAudioRiffVtbl;

    interface IAudioRiff
    {
        CONST_VTBL struct IAudioRiffVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAudioRiff_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAudioRiff_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAudioRiff_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAudioRiff_init(This)	\
    (This)->lpVtbl -> init(This)

#define IAudioRiff_get_audioRiffData(This,pVal)	\
    (This)->lpVtbl -> get_audioRiffData(This,pVal)

#define IAudioRiff_put_audioRiffData(This,pNewVal)	\
    (This)->lpVtbl -> put_audioRiffData(This,pNewVal)

#define IAudioRiff_get_audioRiffDataSet(This,pAudioCriteria,plCount,papData)	\
    (This)->lpVtbl -> get_audioRiffDataSet(This,pAudioCriteria,plCount,papData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IAudioRiff_init_Proxy( 
    IAudioRiff __RPC_FAR * This);


void __RPC_STUB IAudioRiff_init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IAudioRiff_get_audioRiffData_Proxy( 
    IAudioRiff __RPC_FAR * This,
    /* [out][in] */ EMSAUDIODATARECORD_RIFF __RPC_FAR *pVal);


void __RPC_STUB IAudioRiff_get_audioRiffData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IAudioRiff_put_audioRiffData_Proxy( 
    IAudioRiff __RPC_FAR * This,
    /* [in] */ EMSAUDIODATARECORD_RIFF __RPC_FAR *pNewVal);


void __RPC_STUB IAudioRiff_put_audioRiffData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IAudioRiff_get_audioRiffDataSet_Proxy( 
    IAudioRiff __RPC_FAR * This,
    /* [in] */ EMSAUDIOSELECTCRITERIA __RPC_FAR *pAudioCriteria,
    /* [out][in] */ long __RPC_FAR *plCount,
    /* [size_is][size_is][out] */ LPEMSAUDIODATARECORD_RIFF __RPC_FAR *__RPC_FAR *papData);


void __RPC_STUB IAudioRiff_get_audioRiffDataSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAudioRiff_INTERFACE_DEFINED__ */


#ifndef __ICalibrate406Ex_INTERFACE_DEFINED__
#define __ICalibrate406Ex_INTERFACE_DEFINED__

/* interface ICalibrate406Ex */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ICalibrate406Ex;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("ACB1CB0B-79EB-40C1-BA27-779FDEA7B436")
    ICalibrate406Ex : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE init( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE put_calib406ex( 
            /* [in] */ EMSCALIB406DATAEXT __RPC_FAR *pNewVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE get_calib406exDataSet( 
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ LPEMSCALIB406DATAEXT __RPC_FAR *__RPC_FAR *papData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICalibrate406ExVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICalibrate406Ex __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICalibrate406Ex __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICalibrate406Ex __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *init )( 
            ICalibrate406Ex __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_calib406ex )( 
            ICalibrate406Ex __RPC_FAR * This,
            /* [in] */ EMSCALIB406DATAEXT __RPC_FAR *pNewVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_calib406exDataSet )( 
            ICalibrate406Ex __RPC_FAR * This,
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ LPEMSCALIB406DATAEXT __RPC_FAR *__RPC_FAR *papData);
        
        END_INTERFACE
    } ICalibrate406ExVtbl;

    interface ICalibrate406Ex
    {
        CONST_VTBL struct ICalibrate406ExVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICalibrate406Ex_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICalibrate406Ex_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICalibrate406Ex_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICalibrate406Ex_init(This)	\
    (This)->lpVtbl -> init(This)

#define ICalibrate406Ex_put_calib406ex(This,pNewVal)	\
    (This)->lpVtbl -> put_calib406ex(This,pNewVal)

#define ICalibrate406Ex_get_calib406exDataSet(This,pCriteria,plCount,papData)	\
    (This)->lpVtbl -> get_calib406exDataSet(This,pCriteria,plCount,papData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICalibrate406Ex_init_Proxy( 
    ICalibrate406Ex __RPC_FAR * This);


void __RPC_STUB ICalibrate406Ex_init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICalibrate406Ex_put_calib406ex_Proxy( 
    ICalibrate406Ex __RPC_FAR * This,
    /* [in] */ EMSCALIB406DATAEXT __RPC_FAR *pNewVal);


void __RPC_STUB ICalibrate406Ex_put_calib406ex_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICalibrate406Ex_get_calib406exDataSet_Proxy( 
    ICalibrate406Ex __RPC_FAR * This,
    /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
    /* [out][in] */ long __RPC_FAR *plCount,
    /* [size_is][size_is][out] */ LPEMSCALIB406DATAEXT __RPC_FAR *__RPC_FAR *papData);


void __RPC_STUB ICalibrate406Ex_get_calib406exDataSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICalibrate406Ex_INTERFACE_DEFINED__ */


#ifndef __ICalibrate406_2_INTERFACE_DEFINED__
#define __ICalibrate406_2_INTERFACE_DEFINED__

/* interface ICalibrate406_2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ICalibrate406_2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EF65B3C4-FF67-40fe-A39E-8FCBDB162018")
    ICalibrate406_2 : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE init( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE put_calib406_2( 
            /* [in] */ EMSCALIB406DATA2 __RPC_FAR *pNewVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE get_calib406_2DataSet( 
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ LPEMSCALIB406DATA2 __RPC_FAR *__RPC_FAR *papData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICalibrate406_2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ICalibrate406_2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ICalibrate406_2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ICalibrate406_2 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *init )( 
            ICalibrate406_2 __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_calib406_2 )( 
            ICalibrate406_2 __RPC_FAR * This,
            /* [in] */ EMSCALIB406DATA2 __RPC_FAR *pNewVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_calib406_2DataSet )( 
            ICalibrate406_2 __RPC_FAR * This,
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ LPEMSCALIB406DATA2 __RPC_FAR *__RPC_FAR *papData);
        
        END_INTERFACE
    } ICalibrate406_2Vtbl;

    interface ICalibrate406_2
    {
        CONST_VTBL struct ICalibrate406_2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICalibrate406_2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICalibrate406_2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICalibrate406_2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICalibrate406_2_init(This)	\
    (This)->lpVtbl -> init(This)

#define ICalibrate406_2_put_calib406_2(This,pNewVal)	\
    (This)->lpVtbl -> put_calib406_2(This,pNewVal)

#define ICalibrate406_2_get_calib406_2DataSet(This,pCriteria,plCount,papData)	\
    (This)->lpVtbl -> get_calib406_2DataSet(This,pCriteria,plCount,papData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICalibrate406_2_init_Proxy( 
    ICalibrate406_2 __RPC_FAR * This);


void __RPC_STUB ICalibrate406_2_init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICalibrate406_2_put_calib406_2_Proxy( 
    ICalibrate406_2 __RPC_FAR * This,
    /* [in] */ EMSCALIB406DATA2 __RPC_FAR *pNewVal);


void __RPC_STUB ICalibrate406_2_put_calib406_2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICalibrate406_2_get_calib406_2DataSet_Proxy( 
    ICalibrate406_2 __RPC_FAR * This,
    /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
    /* [out][in] */ long __RPC_FAR *plCount,
    /* [size_is][size_is][out] */ LPEMSCALIB406DATA2 __RPC_FAR *__RPC_FAR *papData);


void __RPC_STUB ICalibrate406_2_get_calib406_2DataSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICalibrate406_2_INTERFACE_DEFINED__ */


#ifndef __IABLData_INTERFACE_DEFINED__
#define __IABLData_INTERFACE_DEFINED__

/* interface IABLData */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IABLData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7E157C7D-E1D1-464F-A1C3-08428F267E31")
    IABLData : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE init( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE put_abldata( 
            /* [in] */ EMSABLData __RPC_FAR *pNewVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE get_ablDataSet( 
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ LPEMSABLData __RPC_FAR *__RPC_FAR *papData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IABLDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IABLData __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IABLData __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IABLData __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *init )( 
            IABLData __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_abldata )( 
            IABLData __RPC_FAR * This,
            /* [in] */ EMSABLData __RPC_FAR *pNewVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_ablDataSet )( 
            IABLData __RPC_FAR * This,
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ LPEMSABLData __RPC_FAR *__RPC_FAR *papData);
        
        END_INTERFACE
    } IABLDataVtbl;

    interface IABLData
    {
        CONST_VTBL struct IABLDataVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IABLData_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IABLData_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IABLData_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IABLData_init(This)	\
    (This)->lpVtbl -> init(This)

#define IABLData_put_abldata(This,pNewVal)	\
    (This)->lpVtbl -> put_abldata(This,pNewVal)

#define IABLData_get_ablDataSet(This,pCriteria,plCount,papData)	\
    (This)->lpVtbl -> get_ablDataSet(This,pCriteria,plCount,papData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IABLData_init_Proxy( 
    IABLData __RPC_FAR * This);


void __RPC_STUB IABLData_init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IABLData_put_abldata_Proxy( 
    IABLData __RPC_FAR * This,
    /* [in] */ EMSABLData __RPC_FAR *pNewVal);


void __RPC_STUB IABLData_put_abldata_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IABLData_get_ablDataSet_Proxy( 
    IABLData __RPC_FAR * This,
    /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
    /* [out][in] */ long __RPC_FAR *plCount,
    /* [size_is][size_is][out] */ LPEMSABLData __RPC_FAR *__RPC_FAR *papData);


void __RPC_STUB IABLData_get_ablDataSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IABLData_INTERFACE_DEFINED__ */


#ifndef __IHealthStatus_INTERFACE_DEFINED__
#define __IHealthStatus_INTERFACE_DEFINED__

/* interface IHealthStatus */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IHealthStatus;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("FA7B2A46-2239-4294-BDF0-6148C9604740")
    IHealthStatus : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE init( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE put_healthStatus( 
            /* [in] */ EMSHEALTHSTATUS __RPC_FAR *pNewVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE get_healthStatus_DataSet( 
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ EMSHEALTHSTATUS __RPC_FAR *__RPC_FAR *papData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHealthStatusVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IHealthStatus __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IHealthStatus __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IHealthStatus __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *init )( 
            IHealthStatus __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_healthStatus )( 
            IHealthStatus __RPC_FAR * This,
            /* [in] */ EMSHEALTHSTATUS __RPC_FAR *pNewVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_healthStatus_DataSet )( 
            IHealthStatus __RPC_FAR * This,
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ EMSHEALTHSTATUS __RPC_FAR *__RPC_FAR *papData);
        
        END_INTERFACE
    } IHealthStatusVtbl;

    interface IHealthStatus
    {
        CONST_VTBL struct IHealthStatusVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHealthStatus_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHealthStatus_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IHealthStatus_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IHealthStatus_init(This)	\
    (This)->lpVtbl -> init(This)

#define IHealthStatus_put_healthStatus(This,pNewVal)	\
    (This)->lpVtbl -> put_healthStatus(This,pNewVal)

#define IHealthStatus_get_healthStatus_DataSet(This,pCriteria,plCount,papData)	\
    (This)->lpVtbl -> get_healthStatus_DataSet(This,pCriteria,plCount,papData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IHealthStatus_init_Proxy( 
    IHealthStatus __RPC_FAR * This);


void __RPC_STUB IHealthStatus_init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IHealthStatus_put_healthStatus_Proxy( 
    IHealthStatus __RPC_FAR * This,
    /* [in] */ EMSHEALTHSTATUS __RPC_FAR *pNewVal);


void __RPC_STUB IHealthStatus_put_healthStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IHealthStatus_get_healthStatus_DataSet_Proxy( 
    IHealthStatus __RPC_FAR * This,
    /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
    /* [out][in] */ long __RPC_FAR *plCount,
    /* [size_is][size_is][out] */ EMSHEALTHSTATUS __RPC_FAR *__RPC_FAR *papData);


void __RPC_STUB IHealthStatus_get_healthStatus_DataSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHealthStatus_INTERFACE_DEFINED__ */


#ifndef __IHealthDetections_INTERFACE_DEFINED__
#define __IHealthDetections_INTERFACE_DEFINED__

/* interface IHealthDetections */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IHealthDetections;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F0A383C6-D7AF-47f1-BD7F-1BC3DA517054")
    IHealthDetections : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE init( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE put_healthDetections( 
            /* [in] */ EMSHEALTHDETECTIONS __RPC_FAR *pNewVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE get_healthDetections_DataSet( 
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ EMSHEALTHDETECTIONS __RPC_FAR *__RPC_FAR *papData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IHealthDetectionsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IHealthDetections __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IHealthDetections __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IHealthDetections __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *init )( 
            IHealthDetections __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_healthDetections )( 
            IHealthDetections __RPC_FAR * This,
            /* [in] */ EMSHEALTHDETECTIONS __RPC_FAR *pNewVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_healthDetections_DataSet )( 
            IHealthDetections __RPC_FAR * This,
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ EMSHEALTHDETECTIONS __RPC_FAR *__RPC_FAR *papData);
        
        END_INTERFACE
    } IHealthDetectionsVtbl;

    interface IHealthDetections
    {
        CONST_VTBL struct IHealthDetectionsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IHealthDetections_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IHealthDetections_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IHealthDetections_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IHealthDetections_init(This)	\
    (This)->lpVtbl -> init(This)

#define IHealthDetections_put_healthDetections(This,pNewVal)	\
    (This)->lpVtbl -> put_healthDetections(This,pNewVal)

#define IHealthDetections_get_healthDetections_DataSet(This,pCriteria,plCount,papData)	\
    (This)->lpVtbl -> get_healthDetections_DataSet(This,pCriteria,plCount,papData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IHealthDetections_init_Proxy( 
    IHealthDetections __RPC_FAR * This);


void __RPC_STUB IHealthDetections_init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IHealthDetections_put_healthDetections_Proxy( 
    IHealthDetections __RPC_FAR * This,
    /* [in] */ EMSHEALTHDETECTIONS __RPC_FAR *pNewVal);


void __RPC_STUB IHealthDetections_put_healthDetections_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IHealthDetections_get_healthDetections_DataSet_Proxy( 
    IHealthDetections __RPC_FAR * This,
    /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
    /* [out][in] */ long __RPC_FAR *plCount,
    /* [size_is][size_is][out] */ EMSHEALTHDETECTIONS __RPC_FAR *__RPC_FAR *papData);


void __RPC_STUB IHealthDetections_get_healthDetections_DataSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IHealthDetections_INTERFACE_DEFINED__ */


#ifndef __IBeaconAdvisory_INTERFACE_DEFINED__
#define __IBeaconAdvisory_INTERFACE_DEFINED__

/* interface IBeaconAdvisory */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IBeaconAdvisory;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2FB132FE-ADF4-4517-A2EC-DAEF834D5C5D")
    IBeaconAdvisory : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE init( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE put_beaconAdvisory( 
            /* [in] */ EMS_BEACON_ADVISORY __RPC_FAR *pBeacon) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE get_beaconAdvisory_DataSet( 
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ EMS_BEACON_ADVISORY __RPC_FAR *__RPC_FAR *papData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBeaconAdvisoryVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IBeaconAdvisory __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IBeaconAdvisory __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IBeaconAdvisory __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *init )( 
            IBeaconAdvisory __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_beaconAdvisory )( 
            IBeaconAdvisory __RPC_FAR * This,
            /* [in] */ EMS_BEACON_ADVISORY __RPC_FAR *pBeacon);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_beaconAdvisory_DataSet )( 
            IBeaconAdvisory __RPC_FAR * This,
            /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
            /* [out][in] */ long __RPC_FAR *plCount,
            /* [size_is][size_is][out] */ EMS_BEACON_ADVISORY __RPC_FAR *__RPC_FAR *papData);
        
        END_INTERFACE
    } IBeaconAdvisoryVtbl;

    interface IBeaconAdvisory
    {
        CONST_VTBL struct IBeaconAdvisoryVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBeaconAdvisory_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IBeaconAdvisory_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IBeaconAdvisory_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IBeaconAdvisory_init(This)	\
    (This)->lpVtbl -> init(This)

#define IBeaconAdvisory_put_beaconAdvisory(This,pBeacon)	\
    (This)->lpVtbl -> put_beaconAdvisory(This,pBeacon)

#define IBeaconAdvisory_get_beaconAdvisory_DataSet(This,pCriteria,plCount,papData)	\
    (This)->lpVtbl -> get_beaconAdvisory_DataSet(This,pCriteria,plCount,papData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IBeaconAdvisory_init_Proxy( 
    IBeaconAdvisory __RPC_FAR * This);


void __RPC_STUB IBeaconAdvisory_init_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IBeaconAdvisory_put_beaconAdvisory_Proxy( 
    IBeaconAdvisory __RPC_FAR * This,
    /* [in] */ EMS_BEACON_ADVISORY __RPC_FAR *pBeacon);


void __RPC_STUB IBeaconAdvisory_put_beaconAdvisory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IBeaconAdvisory_get_beaconAdvisory_DataSet_Proxy( 
    IBeaconAdvisory __RPC_FAR * This,
    /* [in] */ EMSSELECTCRITERIA __RPC_FAR *pCriteria,
    /* [out][in] */ long __RPC_FAR *plCount,
    /* [size_is][size_is][out] */ EMS_BEACON_ADVISORY __RPC_FAR *__RPC_FAR *papData);


void __RPC_STUB IBeaconAdvisory_get_beaconAdvisory_DataSet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IBeaconAdvisory_INTERFACE_DEFINED__ */



#ifndef __LEOLUT600DBSLib_LIBRARY_DEFINED__
#define __LEOLUT600DBSLib_LIBRARY_DEFINED__

/* library LEOLUT600DBSLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_LEOLUT600DBSLib;

EXTERN_C const CLSID CLSID_CCBCData;

#ifdef __cplusplus

class DECLSPEC_UUID("21B267E6-5C43-43C9-BB8C-A47162FE3DA5")
CCBCData;
#endif

EXTERN_C const CLSID CLSID_SARPData;

#ifdef __cplusplus

class DECLSPEC_UUID("CECD73DC-CBA4-41ae-A33D-F225C344AAC7")
SARPData;
#endif

EXTERN_C const CLSID CLSID_SARRData;

#ifdef __cplusplus

class DECLSPEC_UUID("DB012CE2-7DE2-4b2d-B7A6-8CF5EBCC416D")
SARRData;
#endif

EXTERN_C const CLSID CLSID_Spectrum;

#ifdef __cplusplus

class DECLSPEC_UUID("E17224FC-479A-42F5-9100-D69F6DC72804")
Spectrum;
#endif

EXTERN_C const CLSID CLSID_LeoStatus;

#ifdef __cplusplus

class DECLSPEC_UUID("6C27DF54-9DA1-4982-ADA3-4CF17CCE9E9C")
LeoStatus;
#endif

EXTERN_C const CLSID CLSID_EMSLogger;

#ifdef __cplusplus

class DECLSPEC_UUID("F97B4ABB-318B-41D4-9636-AE3CDAB6C6B6")
EMSLogger;
#endif

EXTERN_C const CLSID CLSID_EMSLocate;

#ifdef __cplusplus

class DECLSPEC_UUID("0CB72146-7D0B-46E9-BCC1-859F59E278E3")
EMSLocate;
#endif

EXTERN_C const CLSID CLSID_Calibrate406;

#ifdef __cplusplus

class DECLSPEC_UUID("E7D38C4E-15C0-4DA9-AE8E-23BA559ED100")
Calibrate406;
#endif

EXTERN_C const CLSID CLSID_CBCOut;

#ifdef __cplusplus

class DECLSPEC_UUID("BFC1B1E1-8811-4775-A3C8-639A77AB6131")
CBCOut;
#endif

EXTERN_C const CLSID CLSID_EMSTLE;

#ifdef __cplusplus

class DECLSPEC_UUID("3A8C993A-8FB0-4033-8CA0-A80187D298C4")
EMSTLE;
#endif

EXTERN_C const CLSID CLSID_AlarmData;

#ifdef __cplusplus

class DECLSPEC_UUID("0E800B99-9448-4CA7-99A0-5DF1C6DBA1E4")
AlarmData;
#endif

EXTERN_C const CLSID CLSID_SatTrack;

#ifdef __cplusplus

class DECLSPEC_UUID("9C71DA27-2F24-4CE2-9B97-F5473C626FE3")
SatTrack;
#endif

EXTERN_C const CLSID CLSID_ResidualData;

#ifdef __cplusplus

class DECLSPEC_UUID("513D6E4A-B6F5-450b-B86D-F04C0BD90E76")
ResidualData;
#endif

EXTERN_C const CLSID CLSID_ConfigData;

#ifdef __cplusplus

class DECLSPEC_UUID("92AF213E-1752-44F5-8F6C-0DC2E83751BB")
ConfigData;
#endif

EXTERN_C const CLSID CLSID_Combined406Data;

#ifdef __cplusplus

class DECLSPEC_UUID("506B448D-580C-41C1-B0ED-2114E7E36450")
Combined406Data;
#endif

EXTERN_C const CLSID CLSID_SarpCalibData;

#ifdef __cplusplus

class DECLSPEC_UUID("0929DB03-9651-4069-B239-118F080495E0")
SarpCalibData;
#endif

EXTERN_C const CLSID CLSID_SarrCalibData;

#ifdef __cplusplus

class DECLSPEC_UUID("0FB7EAFD-130A-4755-8DFC-6973698359A3")
SarrCalibData;
#endif

EXTERN_C const CLSID CLSID_AudioRiff;

#ifdef __cplusplus

class DECLSPEC_UUID("1184594E-7981-4E8A-89EC-423EF9556E28")
AudioRiff;
#endif

EXTERN_C const CLSID CLSID_Calibrate406Ex;

#ifdef __cplusplus

class DECLSPEC_UUID("E5A3066E-4DDD-4746-A00B-BD8175F84ECC")
Calibrate406Ex;
#endif

EXTERN_C const CLSID CLSID_Calibrate406_2;

#ifdef __cplusplus

class DECLSPEC_UUID("3F6DBDB4-4C3B-40cc-86B0-08DABF836A73")
Calibrate406_2;
#endif

EXTERN_C const CLSID CLSID_ABLData;

#ifdef __cplusplus

class DECLSPEC_UUID("9AC9E0AD-2E51-4370-BF25-0A9314EDC483")
ABLData;
#endif

EXTERN_C const CLSID CLSID_HealthStatus;

#ifdef __cplusplus

class DECLSPEC_UUID("2B035B0D-6808-4ae1-A4CB-5DB0C365EB37")
HealthStatus;
#endif

EXTERN_C const CLSID CLSID_HealthDetections;

#ifdef __cplusplus

class DECLSPEC_UUID("F47C58C2-630F-417c-B892-CFCBBDC9D827")
HealthDetections;
#endif

EXTERN_C const CLSID CLSID_BeaconAdvisory;

#ifdef __cplusplus

class DECLSPEC_UUID("AE4D9BF1-5DBB-4e14-A935-C1256EBDA255")
BeaconAdvisory;
#endif
#endif /* __LEOLUT600DBSLib_LIBRARY_DEFINED__ */

/* interface __MIDL_itf_LeoLut600DBS_0485 */
/* [local] */ 

#endif //INC_LEODBSIDL


extern RPC_IF_HANDLE __MIDL_itf_LeoLut600DBS_0485_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_LeoLut600DBS_0485_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
