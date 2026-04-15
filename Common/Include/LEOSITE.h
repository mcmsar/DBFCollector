/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Apr 15 16:31:03 2004
 */
/* Compiler settings for LEOSITE.IDL:
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

#ifndef __LEOSITE_h__
#define __LEOSITE_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSLeoLut600SiteInfo_FWD_DEFINED__
#define __IEMSLeoLut600SiteInfo_FWD_DEFINED__
typedef interface IEMSLeoLut600SiteInfo IEMSLeoLut600SiteInfo;
#endif 	/* __IEMSLeoLut600SiteInfo_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "emsiteif.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_LEOSITE_0000 */
/* [local] */ 

// {47C5A1B2-B987-11d5-8C6D-009027912866}
DEFINE_GUID( IID_IEMSLeoLut600SiteInfo, 0x47C5A1B2, 0xB987, 0x11d5, 0x8c, 0x6d, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);
typedef struct  _tagEMSLEOARCHIVEINFO
    {
    double dRawCBCDataDays;
    double dRaw406DataDays;
    double dSpectrumDataDays;
    double dCalibCBCDataDays;
    double dCalib406DataDays;
    double dStatsDataDays;
    double dAlarmDataDays;
    double dTLEDataDays;
    double dLocationDataDays;
    double dPassDataDays;
    double dPassSchedDays;
    double dCommsDataDays;
    double dLogDataDays;
    double dSensorDataDays;
    double dEnvironDataDays;
    }	EMSLEOARCHIVEINFO;

typedef struct _tagEMSLEOARCHIVEINFO __RPC_FAR *LPEMSLEOARCHIVEINFO;


// default values for LEOALARMTHRESHOLDS fields

static const int c_nEMSAlarmMinReport = 1;
static const int c_nEMSAlarmMaxReport = 5;
static const double c_dEMSAlarmFreqReport = 60.0;
static const int c_nEMSWarnMinReport = 1;
static const int c_nEMSWarnMaxReport = 5;
static const double c_dEMSAlarmMinElevation = 5.0;
static const double c_dEMSWarnMinElevation = 5.0;
static const double c_dEMSAlarmAntennaBeamAngle = 5.0;
static const double c_dEMSAlarmAntennaMinAngle = 5.0;
static const double c_dEMSAlarmAntennaDelay = 10.0; // seconds
static const double c_dEMSAlarmCommsContactFreq = 0.0; // mins
static const int c_nEMSAlarmCommsMaxRetries = 3;
static const int c_nEMSAlarmMinCBC121Counts = 0;
static const int c_nEMSAlarmMinCBC243Counts = 0;
static const int c_nEMSAlarmMinCBC406Counts = 0;
static const int c_nEMSAlarmMinSARR406Counts = 0;
static const int c_nEMSAlarmMinSARP406Counts = 0;
static const double c_dEMSAlarmMinCBC121Time = 600.0;
static const double c_dEMSAlarmMinCBC243Time = 600.0;
static const double c_dEMSAlarmMinCBC406Time = 1200.0;
static const double c_dEMSAlarmMinSARR406Time = 600.0;
static const double c_dEMSAlarmMinSARP406Time = 600.0;
static const double c_dEMSAlarmMinOutsideTemp = -55.0;
static const double c_dEMSAlarmMaxOutsideTemp = +45.0;
static const double c_dEMSAlarmMinInsideTemp = -1.0;
static const double c_dEMSAlarmMaxInsideTemp = +45.0;
static const double c_dEMSAlarmMinEquipTemp = -55.0;
static const double c_dEMSAlarmMaxEquipTemp = +80.0;
static const int c_nEMSAlarmMaxWidebandSyncLosses = 10;
static const double c_dEMSAlarmMaxCollectorModIndex = 1.75;
static const double c_dEMSAlarmMinCollectorADCRMC = 100.0;
static const int c_nEMSAlarmMinCBC121Solns = 0;
static const int c_nEMSAlarmMinCBC243Solns = 0;
static const int c_nEMSAlarmMinCBC406Solns = 0;
static const int c_nEMSAlarmMinSARR406Solns = 0;
static const int c_nEMSAlarmMinSARP406Solns = 0;

typedef struct  _tagEMSLEOALARMTHRESHOLDS
    {
    int nMinReport;
    int nMaxReport;
    double dFreqReport;
    double dMinElevation;
    double dAntennaMinAngle;
    double dAntennaDelay;
    double dAntennaBeamAngle;
    int nCommsRetries;
    double dCommsContactFreq;
    int nMinCBC121Counts;
    int nMinCBC243Counts;
    int nMinCBC406Counts;
    int nMinSARR406Counts;
    int nMinSARP406Counts;
    double dMinCBC121Time;
    double dMinCBC243Time;
    double dMinCBC406Time;
    double dMinSARR406Time;
    double dMinSARP406Time;
    int nMinCBC121Solns;
    int nMinCBC243Solns;
    int nMinCBC406Solns;
    int nMinSARR406Solns;
    int nMinSARP406Solns;
    int nWidebandSyncLosses;
    double dCollectorModIndex;
    double dCollectorADCRMC;
    double dMinOutsideTemp;
    double dMaxOutsideTemp;
    double dMinInsideTemp;
    double dMaxInsideTemp;
    double dMinEquipTemp;
    double dMaxEquipTemp;
    }	EMSLEOALARMTHRESHOLDS;

typedef struct _tagEMSLEOALARMTHRESHOLDS __RPC_FAR *LPEMSLEOALARMTHRESHOLDS;

typedef struct  _tagEMSLEOALARMINFO
    {
    EMSLEOALARMTHRESHOLDS alarm;
    EMSLEOALARMTHRESHOLDS warn;
    }	EMSLEOALARMINFO;

typedef struct _tagEMSLEOALARMINFO __RPC_FAR *LPEMSLEOALARMINFO;

typedef 
enum _tagEMSSCHEDULEFLAGS
    {	EMSSchedFlag_None	= 0,
	EMSSchedFlag_Automatic	= 0x1,
	EMSSchedFlag_AcceptMCC	= 0x2,
	EMSSchedFlag_AcceptTruncated	= 0x4,
	EMSSchedFlag_Default	= EMSSchedFlag_Automatic + EMSSchedFlag_AcceptTruncated
    }	EMSSCHEDULEFLAGS;

typedef struct  _tagEMSSCHEDULEINFO
    {
    double dDuration;
    double dFrequency;
    double dScheduleTolerance;
    double dPrePassDuration;
    EMSSCHEDULEFLAGS flags;
    }	EMSSCHEDULEINFO;

typedef struct _tagEMSSCHEDULEINFO __RPC_FAR *LPEMSSCHEDULEINFO;



extern RPC_IF_HANDLE __MIDL_itf_LEOSITE_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_LEOSITE_0000_v0_0_s_ifspec;

#ifndef __IEMSLeoLut600SiteInfo_INTERFACE_DEFINED__
#define __IEMSLeoLut600SiteInfo_INTERFACE_DEFINED__

/* interface IEMSLeoLut600SiteInfo */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSLeoLut600SiteInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("47C5A1B2-B987-11d5-8C6D-009027912866")
    IEMSLeoLut600SiteInfo : public IEMSSiteInfo
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetSatellites( 
            /* [length_is][size_is][out] */ ULONG __RPC_FAR *lpulSatellites,
            /* [in] */ ULONG ulMax,
            /* [out] */ ULONG __RPC_FAR *ulActual) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetScheduleInfo( 
            /* [out] */ EMSSCHEDULEINFO __RPC_FAR *lpInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLeoAlarmInfo( 
            /* [out] */ EMSLEOALARMINFO __RPC_FAR *lpInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLeoArchiveInfo( 
            /* [out] */ EMSLEOARCHIVEINFO __RPC_FAR *lpInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSLeoLut600SiteInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfigFlags )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigFlags )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *lpdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReloadConfigData )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfigValueA )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [string][in] */ LPCSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigValueA )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [length_is][size_is][out] */ unsigned char __RPC_FAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG __RPC_FAR *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfigValueW )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [string][in] */ LPCWSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigValueW )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [length_is][size_is][out] */ WCHAR __RPC_FAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG __RPC_FAR *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLutID )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [out] */ ULONG __RPC_FAR *lpulLutID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLutName )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [length_is][size_is][out] */ unsigned char __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSecondaryLuts )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [length_is][size_is][out] */ ULONG __RPC_FAR *lpulLuts,
            /* [in] */ ULONG ulMax,
            /* [out] */ ULONG __RPC_FAR *ulActual);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetServiceInfo )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [length_is][size_is][out] */ EMSSERVICEINFO __RPC_FAR *lpInfo,
            /* [in] */ ULONG ulMax,
            /* [out] */ ULONG __RPC_FAR *ulActual);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMonitorFrequency )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [out] */ ULONG __RPC_FAR *lpulFrequency);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGuardFrequency )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [out] */ ULONG __RPC_FAR *lpulFrequency);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTranslationTableInfo )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [length_is][size_is][out] */ EMSSITTRANSTABLE __RPC_FAR *lpInfo,
            /* [in] */ ULONG ulMax,
            /* [out] */ ULONG __RPC_FAR *ulActual);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRouteInfo )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [length_is][size_is][out] */ EMSROUTEINFO __RPC_FAR *lpInfo,
            /* [in] */ ULONG ulMax,
            /* [out] */ ULONG __RPC_FAR *ulActual);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDestinationsInfo )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [length_is][size_is][out] */ EMSDESTINATIONINFO __RPC_FAR *lpInfo,
            /* [in] */ ULONG ulMax,
            /* [out] */ ULONG __RPC_FAR *ulActual);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSourcesInfo )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [length_is][size_is][out] */ EMSSOURCEINFO __RPC_FAR *lpInfo,
            /* [in] */ ULONG ulMax,
            /* [out] */ ULONG __RPC_FAR *ulActual);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDataDirectory )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRecvMsgDirectory )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProcessedMsgDirectory )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSendMsgDirectory )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSentMsgDirectory )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetUndeliveredMsgDirectory )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetRecvdMsgNumber )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [string][in] */ unsigned char __RPC_FAR *lpszShortRouteName,
            /* [in] */ ULONG ulMsgNumber);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSentMsgNumber )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [string][in] */ unsigned char __RPC_FAR *lpszShortRouteName,
            /* [in] */ ULONG ulMsgNumber);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGpsAllowedDifference )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *lpdSeconds);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGpsCheckFrequency )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *lpdSeconds);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSystemTestInfo )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [out] */ EMSSYSTEMTESTINFO __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetReplicationInfo )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [out] */ EMSREPLICATEINFO __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAGCInfo )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [out] */ EMSAGCINFO __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSatellites )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [length_is][size_is][out] */ ULONG __RPC_FAR *lpulSatellites,
            /* [in] */ ULONG ulMax,
            /* [out] */ ULONG __RPC_FAR *ulActual);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetScheduleInfo )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [out] */ EMSSCHEDULEINFO __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLeoAlarmInfo )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [out] */ EMSLEOALARMINFO __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLeoArchiveInfo )( 
            IEMSLeoLut600SiteInfo __RPC_FAR * This,
            /* [out] */ EMSLEOARCHIVEINFO __RPC_FAR *lpInfo);
        
        END_INTERFACE
    } IEMSLeoLut600SiteInfoVtbl;

    interface IEMSLeoLut600SiteInfo
    {
        CONST_VTBL struct IEMSLeoLut600SiteInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSLeoLut600SiteInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSLeoLut600SiteInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSLeoLut600SiteInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSLeoLut600SiteInfo_SetConfigFlags(This,dwFlags)	\
    (This)->lpVtbl -> SetConfigFlags(This,dwFlags)

#define IEMSLeoLut600SiteInfo_GetConfigFlags(This,lpdwFlags)	\
    (This)->lpVtbl -> GetConfigFlags(This,lpdwFlags)

#define IEMSLeoLut600SiteInfo_ReloadConfigData(This)	\
    (This)->lpVtbl -> ReloadConfigData(This)

#define IEMSLeoLut600SiteInfo_SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)	\
    (This)->lpVtbl -> SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)

#define IEMSLeoLut600SiteInfo_GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    (This)->lpVtbl -> GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)

#define IEMSLeoLut600SiteInfo_SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)	\
    (This)->lpVtbl -> SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)

#define IEMSLeoLut600SiteInfo_GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    (This)->lpVtbl -> GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)


#define IEMSLeoLut600SiteInfo_GetLutID(This,lpulLutID)	\
    (This)->lpVtbl -> GetLutID(This,lpulLutID)

#define IEMSLeoLut600SiteInfo_GetLutName(This,pv,cb,pcbLength)	\
    (This)->lpVtbl -> GetLutName(This,pv,cb,pcbLength)

#define IEMSLeoLut600SiteInfo_GetSecondaryLuts(This,lpulLuts,ulMax,ulActual)	\
    (This)->lpVtbl -> GetSecondaryLuts(This,lpulLuts,ulMax,ulActual)

#define IEMSLeoLut600SiteInfo_GetServiceInfo(This,lpInfo,ulMax,ulActual)	\
    (This)->lpVtbl -> GetServiceInfo(This,lpInfo,ulMax,ulActual)

#define IEMSLeoLut600SiteInfo_GetMonitorFrequency(This,lpulFrequency)	\
    (This)->lpVtbl -> GetMonitorFrequency(This,lpulFrequency)

#define IEMSLeoLut600SiteInfo_GetGuardFrequency(This,lpulFrequency)	\
    (This)->lpVtbl -> GetGuardFrequency(This,lpulFrequency)

#define IEMSLeoLut600SiteInfo_GetTranslationTableInfo(This,lpInfo,ulMax,ulActual)	\
    (This)->lpVtbl -> GetTranslationTableInfo(This,lpInfo,ulMax,ulActual)

#define IEMSLeoLut600SiteInfo_GetRouteInfo(This,lpInfo,ulMax,ulActual)	\
    (This)->lpVtbl -> GetRouteInfo(This,lpInfo,ulMax,ulActual)

#define IEMSLeoLut600SiteInfo_GetDestinationsInfo(This,lpInfo,ulMax,ulActual)	\
    (This)->lpVtbl -> GetDestinationsInfo(This,lpInfo,ulMax,ulActual)

#define IEMSLeoLut600SiteInfo_GetSourcesInfo(This,lpInfo,ulMax,ulActual)	\
    (This)->lpVtbl -> GetSourcesInfo(This,lpInfo,ulMax,ulActual)

#define IEMSLeoLut600SiteInfo_GetDataDirectory(This,pv,cb,pcbRead)	\
    (This)->lpVtbl -> GetDataDirectory(This,pv,cb,pcbRead)

#define IEMSLeoLut600SiteInfo_GetRecvMsgDirectory(This,pv,cb,pcbRead)	\
    (This)->lpVtbl -> GetRecvMsgDirectory(This,pv,cb,pcbRead)

#define IEMSLeoLut600SiteInfo_GetProcessedMsgDirectory(This,pv,cb,pcbRead)	\
    (This)->lpVtbl -> GetProcessedMsgDirectory(This,pv,cb,pcbRead)

#define IEMSLeoLut600SiteInfo_GetSendMsgDirectory(This,pv,cb,pcbRead)	\
    (This)->lpVtbl -> GetSendMsgDirectory(This,pv,cb,pcbRead)

#define IEMSLeoLut600SiteInfo_GetSentMsgDirectory(This,pv,cb,pcbRead)	\
    (This)->lpVtbl -> GetSentMsgDirectory(This,pv,cb,pcbRead)

#define IEMSLeoLut600SiteInfo_GetUndeliveredMsgDirectory(This,pv,cb,pcbRead)	\
    (This)->lpVtbl -> GetUndeliveredMsgDirectory(This,pv,cb,pcbRead)

#define IEMSLeoLut600SiteInfo_SetRecvdMsgNumber(This,lpszShortRouteName,ulMsgNumber)	\
    (This)->lpVtbl -> SetRecvdMsgNumber(This,lpszShortRouteName,ulMsgNumber)

#define IEMSLeoLut600SiteInfo_SetSentMsgNumber(This,lpszShortRouteName,ulMsgNumber)	\
    (This)->lpVtbl -> SetSentMsgNumber(This,lpszShortRouteName,ulMsgNumber)

#define IEMSLeoLut600SiteInfo_GetGpsAllowedDifference(This,lpdSeconds)	\
    (This)->lpVtbl -> GetGpsAllowedDifference(This,lpdSeconds)

#define IEMSLeoLut600SiteInfo_GetGpsCheckFrequency(This,lpdSeconds)	\
    (This)->lpVtbl -> GetGpsCheckFrequency(This,lpdSeconds)

#define IEMSLeoLut600SiteInfo_GetSystemTestInfo(This,lpInfo)	\
    (This)->lpVtbl -> GetSystemTestInfo(This,lpInfo)

#define IEMSLeoLut600SiteInfo_GetReplicationInfo(This,lpInfo)	\
    (This)->lpVtbl -> GetReplicationInfo(This,lpInfo)

#define IEMSLeoLut600SiteInfo_GetAGCInfo(This,lpInfo)	\
    (This)->lpVtbl -> GetAGCInfo(This,lpInfo)


#define IEMSLeoLut600SiteInfo_GetSatellites(This,lpulSatellites,ulMax,ulActual)	\
    (This)->lpVtbl -> GetSatellites(This,lpulSatellites,ulMax,ulActual)

#define IEMSLeoLut600SiteInfo_GetScheduleInfo(This,lpInfo)	\
    (This)->lpVtbl -> GetScheduleInfo(This,lpInfo)

#define IEMSLeoLut600SiteInfo_GetLeoAlarmInfo(This,lpInfo)	\
    (This)->lpVtbl -> GetLeoAlarmInfo(This,lpInfo)

#define IEMSLeoLut600SiteInfo_GetLeoArchiveInfo(This,lpInfo)	\
    (This)->lpVtbl -> GetLeoArchiveInfo(This,lpInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSLeoLut600SiteInfo_GetSatellites_Proxy( 
    IEMSLeoLut600SiteInfo __RPC_FAR * This,
    /* [length_is][size_is][out] */ ULONG __RPC_FAR *lpulSatellites,
    /* [in] */ ULONG ulMax,
    /* [out] */ ULONG __RPC_FAR *ulActual);


void __RPC_STUB IEMSLeoLut600SiteInfo_GetSatellites_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSLeoLut600SiteInfo_GetScheduleInfo_Proxy( 
    IEMSLeoLut600SiteInfo __RPC_FAR * This,
    /* [out] */ EMSSCHEDULEINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSLeoLut600SiteInfo_GetScheduleInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSLeoLut600SiteInfo_GetLeoAlarmInfo_Proxy( 
    IEMSLeoLut600SiteInfo __RPC_FAR * This,
    /* [out] */ EMSLEOALARMINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSLeoLut600SiteInfo_GetLeoAlarmInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSLeoLut600SiteInfo_GetLeoArchiveInfo_Proxy( 
    IEMSLeoLut600SiteInfo __RPC_FAR * This,
    /* [out] */ EMSLEOARCHIVEINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSLeoLut600SiteInfo_GetLeoArchiveInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSLeoLut600SiteInfo_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_LEOSITE_0020 */
/* [local] */ 

typedef /* [unique] */ IEMSLeoLut600SiteInfo __RPC_FAR *LPEMSLEOLUT600SITEINFO;



extern RPC_IF_HANDLE __MIDL_itf_LEOSITE_0020_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_LEOSITE_0020_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
