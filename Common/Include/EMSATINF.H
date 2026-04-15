

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Mon May 20 10:17:55 2013
 */
/* Compiler settings for ..\..\Common\Include\EMSATINF.IDL:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
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

#ifndef __EMSATINF_h__
#define __EMSATINF_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IEMSSatelliteInfo_FWD_DEFINED__
#define __IEMSSatelliteInfo_FWD_DEFINED__
typedef interface IEMSSatelliteInfo IEMSSatelliteInfo;
#endif 	/* __IEMSSatelliteInfo_FWD_DEFINED__ */


#ifndef __IEMSSatelliteInfo2_FWD_DEFINED__
#define __IEMSSatelliteInfo2_FWD_DEFINED__
typedef interface IEMSSatelliteInfo2 IEMSSatelliteInfo2;
#endif 	/* __IEMSSatelliteInfo2_FWD_DEFINED__ */


#ifndef __IEMSSatelliteInfo3_FWD_DEFINED__
#define __IEMSSatelliteInfo3_FWD_DEFINED__
typedef interface IEMSSatelliteInfo3 IEMSSatelliteInfo3;
#endif 	/* __IEMSSatelliteInfo3_FWD_DEFINED__ */


#ifndef __IEMSSatelliteInfo4_FWD_DEFINED__
#define __IEMSSatelliteInfo4_FWD_DEFINED__
typedef interface IEMSSatelliteInfo4 IEMSSatelliteInfo4;
#endif 	/* __IEMSSatelliteInfo4_FWD_DEFINED__ */


#ifndef __IEMSSatelliteInfo5_FWD_DEFINED__
#define __IEMSSatelliteInfo5_FWD_DEFINED__
typedef interface IEMSSatelliteInfo5 IEMSSatelliteInfo5;
#endif 	/* __IEMSSatelliteInfo5_FWD_DEFINED__ */


#ifndef __IEMSSatelliteInfo6_FWD_DEFINED__
#define __IEMSSatelliteInfo6_FWD_DEFINED__
typedef interface IEMSSatelliteInfo6 IEMSSatelliteInfo6;
#endif 	/* __IEMSSatelliteInfo6_FWD_DEFINED__ */


#ifndef __IEMSSatelliteInfo7_FWD_DEFINED__
#define __IEMSSatelliteInfo7_FWD_DEFINED__
typedef interface IEMSSatelliteInfo7 IEMSSatelliteInfo7;
#endif 	/* __IEMSSatelliteInfo7_FWD_DEFINED__ */


#ifndef __IEMSSatelliteInfo8_FWD_DEFINED__
#define __IEMSSatelliteInfo8_FWD_DEFINED__
typedef interface IEMSSatelliteInfo8 IEMSSatelliteInfo8;
#endif 	/* __IEMSSatelliteInfo8_FWD_DEFINED__ */


#ifndef __IEMSSatelliteInfo9_FWD_DEFINED__
#define __IEMSSatelliteInfo9_FWD_DEFINED__
typedef interface IEMSSatelliteInfo9 IEMSSatelliteInfo9;
#endif 	/* __IEMSSatelliteInfo9_FWD_DEFINED__ */


#ifndef __IEMSSatelliteInfo10_FWD_DEFINED__
#define __IEMSSatelliteInfo10_FWD_DEFINED__
typedef interface IEMSSatelliteInfo10 IEMSSatelliteInfo10;
#endif 	/* __IEMSSatelliteInfo10_FWD_DEFINED__ */


#ifndef __IEMSSatelliteInfo11_FWD_DEFINED__
#define __IEMSSatelliteInfo11_FWD_DEFINED__
typedef interface IEMSSatelliteInfo11 IEMSSatelliteInfo11;
#endif 	/* __IEMSSatelliteInfo11_FWD_DEFINED__ */


#ifndef __IEMSSatelliteInfo12_FWD_DEFINED__
#define __IEMSSatelliteInfo12_FWD_DEFINED__
typedef interface IEMSSatelliteInfo12 IEMSSatelliteInfo12;
#endif 	/* __IEMSSatelliteInfo12_FWD_DEFINED__ */


#ifndef __IEMSSatelliteInfo13_FWD_DEFINED__
#define __IEMSSatelliteInfo13_FWD_DEFINED__
typedef interface IEMSSatelliteInfo13 IEMSSatelliteInfo13;
#endif 	/* __IEMSSatelliteInfo13_FWD_DEFINED__ */


#ifndef __IEMSSatelliteInfo14_FWD_DEFINED__
#define __IEMSSatelliteInfo14_FWD_DEFINED__
typedef interface IEMSSatelliteInfo14 IEMSSatelliteInfo14;
#endif 	/* __IEMSSatelliteInfo14_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "emsicfg.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_EMSATINF_0000_0000 */
/* [local] */ 

 
#include "emserror.h"
 
// {F17394E1-4D52-11d5-8BB5-009027912866} 
DEFINE_GUID( CLSID_EMSSatelliteInfo, 0xf17394e1, 0x4d52, 0x11d5, 0x8b, 0xb5, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);
 
// {F17394E2-4D52-11d5-8BB5-009027912866}
DEFINE_GUID( IID_IEMSSatelliteInfo, 0xf17394e2, 0x4d52, 0x11d5, 0x8b, 0xb5, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);
 
// {7607D4F0-56D5-4ff6-8CDC-B54C5909E99F}
DEFINE_GUID( IID_IEMSSatelliteInfo2, 0x7607d4f0, 0x56d5, 0x4ff6, 0x8c, 0xdc, 0xb5, 0x4c, 0x59, 0x9, 0xe9, 0x9f);
// {EE8C892B-B6BB-4d4e-A747-D9D4793B55D8}
DEFINE_GUID( IID_IEMSSatelliteInfo3, 0xee8c892b, 0xb6bb, 0x4d4e, 0xa7, 0x47, 0xd9, 0xd4, 0x79, 0x3b, 0x55, 0xd8);
// {1892B319-9DB3-4cdc-A78B-728EF2F8CBB2}
DEFINE_GUID( IID_IEMSSatelliteInfo4, 0x1892b319, 0x9db3, 0x4cdc, 0xa7, 0x8b, 0x72, 0x8e, 0xf2, 0xf8, 0xcb, 0xb2);
// {6C426984-DCA1-4b55-9C07-6F45322073A0}
DEFINE_GUID( IID_IEMSSatelliteInfo5, 0x6c426984, 0xdca1, 0x4b55, 0x9c, 0x7, 0x6f, 0x45, 0x32, 0x20, 0x73, 0xa0);
// {52D3FE92-2255-4f37-9846-56BD322B4282}
DEFINE_GUID(IID_IEMSSatelliteInfo6, 0x52d3fe92, 0x2255, 0x4f37, 0x98, 0x46, 0x56, 0xbd, 0x32, 0x2b, 0x42, 0x82);
 
// {D0591B7D-1AD9-4f23-BFF7-ACF4BC3C2B5C}
DEFINE_GUID( IID_IEMSSatelliteInfo7,0xd0591b7d, 0x1ad9, 0x4f23, 0xbf, 0xf7, 0xac, 0xf4, 0xbc, 0x3c, 0x2b, 0x5c);
 
// {A2ECC7CD-1D08-4fd8-908F-376B4536B6E1}
DEFINE_GUID( IID_IEMSSatelliteInfo8, 0xa2ecc7cd, 0x1d08, 0x4fd8, 0x90, 0x8f, 0x37, 0x6b, 0x45, 0x36, 0xb6, 0xe1);
 
// {8E742C5A-0B5F-4b10-A037-CED8E88B5507}
DEFINE_GUID( IID_IEMSSatelliteInfo9, 0x8e742c5a, 0xb5f, 0x4b10, 0xa0, 0x37, 0xce, 0xd8, 0xe8, 0x8b, 0x55, 0x7);
 
// {8FB9583E-9E07-4d64-9501-796154B263FD}
DEFINE_GUID( IID_IEMSSatelliteInfo10, 0x8fb9583e, 0x9e07, 0x4d64, 0x95, 0x1, 0x79, 0x61, 0x54, 0xb2, 0x63, 0xfd);
 
// {DD309AAC-DF15-48f7-9382-C48E4D52D1A8}
DEFINE_GUID(IID_IEMSSatelliteInfo11, 0xdd309aac, 0xdf15, 0x48f7, 0x93, 0x82, 0xc4, 0x8e, 0x4d, 0x52, 0xd1, 0xa8);
 
// {A18342E2-9189-40b0-A477-DEE313BC67D8}
DEFINE_GUID(IID_IEMSSatelliteInfo12, 0xa18342e2, 0x9189, 0x40b0, 0xa4, 0x77, 0xde, 0xe3, 0x13, 0xbc, 0x67, 0xd8);
 
// {9B683CBB-D88A-4e5b-8290-B1FC2CA60FB6}
DEFINE_GUID(IID_IEMSSatelliteInfo13, 0x9b683cbb, 0xd88a, 0x4e5b, 0x82, 0x90, 0xb1, 0xfc, 0x2c, 0xa6, 0xf, 0xb6);
 
// {CE538E71-CA9D-43fe-BAB1-F188209645FF}
DEFINE_GUID(IID_IEMSSatelliteInfo14, 0xce538e71, 0xca9d, 0x43fe, 0xba, 0xb1, 0xf1, 0x88, 0x20, 0x96, 0x45, 0xff); 
 
// Bit Flags for GetCaps 
#define EMS_SATCAP_121_CBC					(0x0001)
#define EMS_SATCAP_243_CBC					(0x0002)
#define EMS_SATCAP_406_CBC					(0x0004)
#define EMS_SATCAP_406_SARP					(0x0008)
#define EMS_SATCAP_406_SARR					(0x0010)
#define EMS_SATCAP_406_SARP_LONG_MSG			(0x0020)
#define EMS_SATCAP_AUDIO						(0x0040)
#define EMS_SATCAP_SPECTRUM					(0x0080)
 
#define EMSSATCONFIGAUDIO_MAX_BANDS (5)
 
#define EMS_SATINFO_MAX_BEHAVIOURS (32)
#define EMS_SATINFO_MAX_ORBITINFO (32)
 
const WORD     c_wSatInfoMI406ConfirmMaxFSErr	       = 0;
const WORD     c_wSatInfoMI406ConfirmMaxPDF1Err	       = 3;
const WORD     c_wSatInfoMI406ConfirmMaxPDF2Err	       = 1;
const WORD     c_wSatInfoMI406ValidMaxFSErr	      	   = 0;
const WORD     c_wSatInfoMI406ValidMaxPDF1Err	       = 2;
const WORD     c_wSatInfoMI406ValidMaxPDF2Err	       = 1;
const WORD     c_wSatInfoMI406IntegrateMaxFSErr	       = 0;
const WORD     c_wSatInfoMI406IntegrateMaxPDF1Err	   = 2;
const WORD     c_wSatInfoMI406IntegrateMaxPDF2Err	   = 1;
const double   c_dSatInfoMI406IntegrateAgeout	       = 20.0;
const double   c_dSatInfoMI406BeaconAgeout	    	   = 8.0 * 60.0;
const double   c_dSatInfoMI406MinMsgInterval	   = 5.0;
const double   c_dSatInfoMI406MaxMsgInterval	   = 0.0; /* never */
const double   c_dSatInfoMI406ValidMsgInterval  = 5.0;
const BOOL     c_bSatInfoMI406Restart                 = TRUE;
const float    c_fSatInfoMI406WindowFreqHz            = 15;  
const float    c_fSatInfoMI406WindowTimeSecs          = 2.5; 
const int      c_iSatInfoMI406WindowBits              = 28;  
const int      c_iSatInfoMI406OutOfSpecWindowBits     = -1;  
const double   c_dSatInfoMI406MsgTimeoutMin           = 20;  
const BOOL     c_bSatInfoMI406MsgForceUpdate          = TRUE;
const int      c_iSatInfoMI406MaxFSErr                = 2;   
const int      c_iSatInfoMI406PF1Err                  = 3;   
const int      c_iSatInfoMI406PF2Err                  = 2;   
const int      c_iSatInfoMI406AgeoutMin               = 30;  
const float    c_fSatInfoMI406CNR1Threshold_dBHz      = 20;  
const float    c_fSatInfoMI406CNR2Threshold_dBHz      = 30;  
const double   c_dSatInfoMI406SarrFreqOffsetThreshold = 10.0;
const double   c_dSatInfoMI406SummaryInterval         = 60.0;
const int      c_dSatInfoMI406QMSOutputRate           = 20;

const	BOOL	c_bSatInfoCalib406SarrSarpCombine = FALSE;
const	double	c_dSatInfoCalib406SarrSarpAgeOutDays = 7.0;
const	double	c_dSatInfoCalib406SarrSarpFreqDiffHz = 500.0;
const	double	c_dSatInfoCalib406SarrSarpTimeDiffSecs = 2.0;
const	int 	c_nSatInfoCalib406SarrSarpMinCount = 250;
const	double	c_dSatInfoCalib406RealTimeDelaySecs = 15.0;


extern RPC_IF_HANDLE __MIDL_itf_EMSATINF_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSATINF_0000_0000_v0_0_s_ifspec;

#ifndef __IEMSSatelliteInfo_INTERFACE_DEFINED__
#define __IEMSSatelliteInfo_INTERFACE_DEFINED__

/* interface IEMSSatelliteInfo */
/* [unique][helpstring][uuid][object] */ 

typedef 
enum _tagEMSSATELLITETYPE
    {	EMSSatTypeLEOCospas	= 0,
	EMSSatTypeLEOSarsat	= 0x1,
	EMSSatTypeGEO	= 0x2,
	EMSSatTypeMEO	= 0x4,
	EMSSatTypeUNKNOWN	= 0x8000
    } 	EMSSATELLITETYPE;

typedef enum _tagEMSSATELLITETYPE *LPEMSSATELLITETYPE;

typedef struct _tagEMS406SIGNALDATA
    {
    unsigned short uProfile;
    EMSTIME updateTime;
    unsigned short uReserved;
    unsigned short uDelete1;
    float fCentreFreq121;
    float fCentreFreq243;
    float fCentreFreq406;
    float fBandwidth121;
    float fBandwidth243;
    float fBandwidth406;
    float fDetectThres;
    float fDetectThres406;
    unsigned short uMaxNumBPP;
    float fMinFreqBPP;
    float fMaxFreqBPP;
    float fDetectThresBPP;
    float fMinCNRBPP;
    unsigned short uMaxFSerrBPP;
    unsigned short uModeMI;
    unsigned short uRestartMI;
    float fAgeoutMI;
    float fPartialAgeoutMI;
    float fWindFreqMI;
    float fWindTimeMI;
    unsigned short uWindBitMI;
    unsigned short uMaxFSerrMI;
    unsigned short uMaxPF1MI;
    unsigned short uMaxPF2MI;
    float fMinCNRMI;
    float fMinCNRPF2MI;
    unsigned short uShortMsgFillMI;
    float fBitRatePDS;
    unsigned short uSARPtypePDS;
    unsigned short uPlaybackPDS;
    long lNfloorDet0;
    long lNfloorDet1;
    long lDetTestMsg;
    float fOnDet406;
    float fOffDet406;
    float fCoeffDet;
    unsigned short uDetTestMsgMI;
    unsigned short uNumPartialOutMI;
    float fTimePartialOutMI;
    float fFreqOffset406;
    double dSarrPowerConstant;
    } 	EMS406SIGNALDATA;

typedef struct _tagEMS406SIGNALDATA *LPEMS406SIGNALDATA;

typedef struct _tagEMSCBCSIGNALDATA
    {
    int nfloor0;
    int nfloor1;
    int nsmooth0;
    int nsmooth1;
    float fpkfak[ 3 ];
    float fAmp[ 3 ];
    float fIncoherentOffset;
    float fDetectThres;
    float fMinFreq[ 3 ];
    float fMaxFreq[ 3 ];
    float fDetFreq;
    unsigned short uDataC1;
    unsigned short uDataC2;
    unsigned short uDataC4;
    } 	EMSCBCSIGNALDATA;

typedef struct _tagEMSCBCSIGNALDATA *LPEMSCBCSIGNALDATA;

typedef struct _tagEMSPDSSIGNALDATA
    {
    unsigned char cReserved1[ 25 ];
    EMSTIME timeUpdate;
    double dReserved2;
    INT64 i64RolloverPeriod;
    EMSTIME timeRollover;
    float fReserved3;
    float fBaudRate;
    float fBaudWindow;
    float fBaudStep;
    unsigned short uBaudDuration;
    float fBaudStart;
    float fBaudStop;
    unsigned short uBaudElapsed;
    unsigned short uSarpSatellite;
    unsigned short uSarpProcessor;
    unsigned short uSarpPlayback;
    unsigned short uSarpType;
    unsigned short uPlaybackPDS;
    unsigned short uDataPD;
    unsigned short uDataRP;
    unsigned short uDataTI;
    unsigned short uDataRPO;
    } 	EMSPDSSIGNALDATA;

typedef struct _tagEMSPDSSIGNALDATA *LPEMSPDSSIGNALDATA;


EXTERN_C const IID IID_IEMSSatelliteInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F17394E2-4D52-11d5-8BB5-009027912866")
    IEMSSatelliteInfo : public IEMSConfigSettings
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetName( 
            /* [in] */ ULONG ulSatelliteID,
            /* [length_is][size_is][out] */ BYTE *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG *pcbRead) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetNoradID( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulNoradID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSatelliteID( 
            /* [in] */ ULONG ulNoradID,
            /* [out] */ ULONG *lpulSatelliteID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFreqBandwidth( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LONG *lplBandwidth) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCaps( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulCapabilities) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Get406SignalData( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMS406SIGNALDATA *lpSignalData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCBCSignalData( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSCBCSIGNALDATA *lpSignalData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPDSSignalData( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSPDSSIGNALDATA *lpSignalData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRolloverPeriod( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64Period) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetRolloverPeriod( 
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64Period) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRolloverTime( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeRollover) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetRolloverTime( 
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIME timeRollover) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRefFreq( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreq) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetRefFreq( 
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreq) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSarrFreqOffset( 
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreqOffset) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSarrFreqOffset( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreqOffset) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSarrTimeOffset( 
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSarrTimeOffset( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64TimeOffset) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSarpFreqOffset( 
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreqOffset) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSarpFreqOffset( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreqOffset) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSarpTimeOffset( 
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSarpTimeOffset( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64TimeOffset) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSatelliteInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEMSSatelliteInfo * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEMSSatelliteInfo * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEMSSatelliteInfo * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigFlags )( 
            IEMSSatelliteInfo * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigFlags )( 
            IEMSSatelliteInfo * This,
            /* [out] */ DWORD *lpdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *ReloadConfigData )( 
            IEMSSatelliteInfo * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigValueA )( 
            IEMSSatelliteInfo * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [string][in] */ LPCSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigValueA )( 
            IEMSSatelliteInfo * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [length_is][size_is][out] */ unsigned char *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigValueW )( 
            IEMSSatelliteInfo * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [string][in] */ LPCWSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigValueW )( 
            IEMSSatelliteInfo * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [length_is][size_is][out] */ WCHAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE *GetName )( 
            IEMSSatelliteInfo * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [length_is][size_is][out] */ BYTE *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG *pcbRead);
        
        HRESULT ( STDMETHODCALLTYPE *GetNoradID )( 
            IEMSSatelliteInfo * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulNoradID);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatelliteID )( 
            IEMSSatelliteInfo * This,
            /* [in] */ ULONG ulNoradID,
            /* [out] */ ULONG *lpulSatelliteID);
        
        HRESULT ( STDMETHODCALLTYPE *GetFreqBandwidth )( 
            IEMSSatelliteInfo * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LONG *lplBandwidth);
        
        HRESULT ( STDMETHODCALLTYPE *GetCaps )( 
            IEMSSatelliteInfo * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulCapabilities);
        
        HRESULT ( STDMETHODCALLTYPE *Get406SignalData )( 
            IEMSSatelliteInfo * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMS406SIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetCBCSignalData )( 
            IEMSSatelliteInfo * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSCBCSIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetPDSSignalData )( 
            IEMSSatelliteInfo * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSPDSSIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetRolloverPeriod )( 
            IEMSSatelliteInfo * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64Period);
        
        HRESULT ( STDMETHODCALLTYPE *SetRolloverPeriod )( 
            IEMSSatelliteInfo * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64Period);
        
        HRESULT ( STDMETHODCALLTYPE *GetRolloverTime )( 
            IEMSSatelliteInfo * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeRollover);
        
        HRESULT ( STDMETHODCALLTYPE *SetRolloverTime )( 
            IEMSSatelliteInfo * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIME timeRollover);
        
        HRESULT ( STDMETHODCALLTYPE *GetRefFreq )( 
            IEMSSatelliteInfo * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreq);
        
        HRESULT ( STDMETHODCALLTYPE *SetRefFreq )( 
            IEMSSatelliteInfo * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreq);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrFreqOffset )( 
            IEMSSatelliteInfo * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrFreqOffset )( 
            IEMSSatelliteInfo * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrTimeOffset )( 
            IEMSSatelliteInfo * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrTimeOffset )( 
            IEMSSatelliteInfo * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpFreqOffset )( 
            IEMSSatelliteInfo * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpFreqOffset )( 
            IEMSSatelliteInfo * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpTimeOffset )( 
            IEMSSatelliteInfo * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpTimeOffset )( 
            IEMSSatelliteInfo * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64TimeOffset);
        
        END_INTERFACE
    } IEMSSatelliteInfoVtbl;

    interface IEMSSatelliteInfo
    {
        CONST_VTBL struct IEMSSatelliteInfoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSatelliteInfo_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEMSSatelliteInfo_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEMSSatelliteInfo_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEMSSatelliteInfo_SetConfigFlags(This,dwFlags)	\
    ( (This)->lpVtbl -> SetConfigFlags(This,dwFlags) ) 

#define IEMSSatelliteInfo_GetConfigFlags(This,lpdwFlags)	\
    ( (This)->lpVtbl -> GetConfigFlags(This,lpdwFlags) ) 

#define IEMSSatelliteInfo_ReloadConfigData(This)	\
    ( (This)->lpVtbl -> ReloadConfigData(This) ) 

#define IEMSSatelliteInfo_SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)	\
    ( (This)->lpVtbl -> SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue) ) 

#define IEMSSatelliteInfo_GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    ( (This)->lpVtbl -> GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead) ) 

#define IEMSSatelliteInfo_SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)	\
    ( (This)->lpVtbl -> SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue) ) 

#define IEMSSatelliteInfo_GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    ( (This)->lpVtbl -> GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead) ) 


#define IEMSSatelliteInfo_GetName(This,ulSatelliteID,pv,cb,pcbRead)	\
    ( (This)->lpVtbl -> GetName(This,ulSatelliteID,pv,cb,pcbRead) ) 

#define IEMSSatelliteInfo_GetNoradID(This,ulSatelliteID,lpulNoradID)	\
    ( (This)->lpVtbl -> GetNoradID(This,ulSatelliteID,lpulNoradID) ) 

#define IEMSSatelliteInfo_GetSatelliteID(This,ulNoradID,lpulSatelliteID)	\
    ( (This)->lpVtbl -> GetSatelliteID(This,ulNoradID,lpulSatelliteID) ) 

#define IEMSSatelliteInfo_GetFreqBandwidth(This,ulSatelliteID,lplBandwidth)	\
    ( (This)->lpVtbl -> GetFreqBandwidth(This,ulSatelliteID,lplBandwidth) ) 

#define IEMSSatelliteInfo_GetCaps(This,ulSatelliteID,lpulCapabilities)	\
    ( (This)->lpVtbl -> GetCaps(This,ulSatelliteID,lpulCapabilities) ) 

#define IEMSSatelliteInfo_Get406SignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> Get406SignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo_GetCBCSignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> GetCBCSignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo_GetPDSSignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> GetPDSSignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo_GetRolloverPeriod(This,ulSatelliteID,lpi64Period)	\
    ( (This)->lpVtbl -> GetRolloverPeriod(This,ulSatelliteID,lpi64Period) ) 

#define IEMSSatelliteInfo_SetRolloverPeriod(This,ulSatelliteID,i64Period)	\
    ( (This)->lpVtbl -> SetRolloverPeriod(This,ulSatelliteID,i64Period) ) 

#define IEMSSatelliteInfo_GetRolloverTime(This,ulSatelliteID,lpTimeRollover)	\
    ( (This)->lpVtbl -> GetRolloverTime(This,ulSatelliteID,lpTimeRollover) ) 

#define IEMSSatelliteInfo_SetRolloverTime(This,ulSatelliteID,timeRollover)	\
    ( (This)->lpVtbl -> SetRolloverTime(This,ulSatelliteID,timeRollover) ) 

#define IEMSSatelliteInfo_GetRefFreq(This,ulSatelliteID,lpdFreq)	\
    ( (This)->lpVtbl -> GetRefFreq(This,ulSatelliteID,lpdFreq) ) 

#define IEMSSatelliteInfo_SetRefFreq(This,ulSatelliteID,dFreq)	\
    ( (This)->lpVtbl -> SetRefFreq(This,ulSatelliteID,dFreq) ) 

#define IEMSSatelliteInfo_SetSarrFreqOffset(This,ulSatelliteID,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarrFreqOffset(This,ulSatelliteID,dFreqOffset) ) 

#define IEMSSatelliteInfo_GetSarrFreqOffset(This,ulSatelliteID,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarrFreqOffset(This,ulSatelliteID,lpdFreqOffset) ) 

#define IEMSSatelliteInfo_SetSarrTimeOffset(This,ulSatelliteID,i64TimeOffset)	\
    ( (This)->lpVtbl -> SetSarrTimeOffset(This,ulSatelliteID,i64TimeOffset) ) 

#define IEMSSatelliteInfo_GetSarrTimeOffset(This,ulSatelliteID,lpi64TimeOffset)	\
    ( (This)->lpVtbl -> GetSarrTimeOffset(This,ulSatelliteID,lpi64TimeOffset) ) 

#define IEMSSatelliteInfo_SetSarpFreqOffset(This,ulSatelliteID,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarpFreqOffset(This,ulSatelliteID,dFreqOffset) ) 

#define IEMSSatelliteInfo_GetSarpFreqOffset(This,ulSatelliteID,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarpFreqOffset(This,ulSatelliteID,lpdFreqOffset) ) 

#define IEMSSatelliteInfo_SetSarpTimeOffset(This,ulSatelliteID,i64TimeOffset)	\
    ( (This)->lpVtbl -> SetSarpTimeOffset(This,ulSatelliteID,i64TimeOffset) ) 

#define IEMSSatelliteInfo_GetSarpTimeOffset(This,ulSatelliteID,lpi64TimeOffset)	\
    ( (This)->lpVtbl -> GetSarpTimeOffset(This,ulSatelliteID,lpi64TimeOffset) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEMSSatelliteInfo_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSATINF_0000_0001 */
/* [local] */ 

typedef /* [unique] */ IEMSSatelliteInfo *LPEMSSATELLITEINFO;



extern RPC_IF_HANDLE __MIDL_itf_EMSATINF_0000_0001_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSATINF_0000_0001_v0_0_s_ifspec;

#ifndef __IEMSSatelliteInfo2_INTERFACE_DEFINED__
#define __IEMSSatelliteInfo2_INTERFACE_DEFINED__

/* interface IEMSSatelliteInfo2 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSSatelliteInfo2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7607D4F0-56D5-4ff6-8CDC-B54C5909E99F")
    IEMSSatelliteInfo2 : public IEMSSatelliteInfo
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetPhaseDemodSetting( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulPhaseDemod) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSatelliteInfo2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEMSSatelliteInfo2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEMSSatelliteInfo2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEMSSatelliteInfo2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigFlags )( 
            IEMSSatelliteInfo2 * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigFlags )( 
            IEMSSatelliteInfo2 * This,
            /* [out] */ DWORD *lpdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *ReloadConfigData )( 
            IEMSSatelliteInfo2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigValueA )( 
            IEMSSatelliteInfo2 * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [string][in] */ LPCSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigValueA )( 
            IEMSSatelliteInfo2 * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [length_is][size_is][out] */ unsigned char *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigValueW )( 
            IEMSSatelliteInfo2 * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [string][in] */ LPCWSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigValueW )( 
            IEMSSatelliteInfo2 * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [length_is][size_is][out] */ WCHAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE *GetName )( 
            IEMSSatelliteInfo2 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [length_is][size_is][out] */ BYTE *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG *pcbRead);
        
        HRESULT ( STDMETHODCALLTYPE *GetNoradID )( 
            IEMSSatelliteInfo2 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulNoradID);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatelliteID )( 
            IEMSSatelliteInfo2 * This,
            /* [in] */ ULONG ulNoradID,
            /* [out] */ ULONG *lpulSatelliteID);
        
        HRESULT ( STDMETHODCALLTYPE *GetFreqBandwidth )( 
            IEMSSatelliteInfo2 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LONG *lplBandwidth);
        
        HRESULT ( STDMETHODCALLTYPE *GetCaps )( 
            IEMSSatelliteInfo2 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulCapabilities);
        
        HRESULT ( STDMETHODCALLTYPE *Get406SignalData )( 
            IEMSSatelliteInfo2 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMS406SIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetCBCSignalData )( 
            IEMSSatelliteInfo2 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSCBCSIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetPDSSignalData )( 
            IEMSSatelliteInfo2 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSPDSSIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetRolloverPeriod )( 
            IEMSSatelliteInfo2 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64Period);
        
        HRESULT ( STDMETHODCALLTYPE *SetRolloverPeriod )( 
            IEMSSatelliteInfo2 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64Period);
        
        HRESULT ( STDMETHODCALLTYPE *GetRolloverTime )( 
            IEMSSatelliteInfo2 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeRollover);
        
        HRESULT ( STDMETHODCALLTYPE *SetRolloverTime )( 
            IEMSSatelliteInfo2 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIME timeRollover);
        
        HRESULT ( STDMETHODCALLTYPE *GetRefFreq )( 
            IEMSSatelliteInfo2 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreq);
        
        HRESULT ( STDMETHODCALLTYPE *SetRefFreq )( 
            IEMSSatelliteInfo2 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreq);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrFreqOffset )( 
            IEMSSatelliteInfo2 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrFreqOffset )( 
            IEMSSatelliteInfo2 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrTimeOffset )( 
            IEMSSatelliteInfo2 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrTimeOffset )( 
            IEMSSatelliteInfo2 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpFreqOffset )( 
            IEMSSatelliteInfo2 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpFreqOffset )( 
            IEMSSatelliteInfo2 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpTimeOffset )( 
            IEMSSatelliteInfo2 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpTimeOffset )( 
            IEMSSatelliteInfo2 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetPhaseDemodSetting )( 
            IEMSSatelliteInfo2 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulPhaseDemod);
        
        END_INTERFACE
    } IEMSSatelliteInfo2Vtbl;

    interface IEMSSatelliteInfo2
    {
        CONST_VTBL struct IEMSSatelliteInfo2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSatelliteInfo2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEMSSatelliteInfo2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEMSSatelliteInfo2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEMSSatelliteInfo2_SetConfigFlags(This,dwFlags)	\
    ( (This)->lpVtbl -> SetConfigFlags(This,dwFlags) ) 

#define IEMSSatelliteInfo2_GetConfigFlags(This,lpdwFlags)	\
    ( (This)->lpVtbl -> GetConfigFlags(This,lpdwFlags) ) 

#define IEMSSatelliteInfo2_ReloadConfigData(This)	\
    ( (This)->lpVtbl -> ReloadConfigData(This) ) 

#define IEMSSatelliteInfo2_SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)	\
    ( (This)->lpVtbl -> SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue) ) 

#define IEMSSatelliteInfo2_GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    ( (This)->lpVtbl -> GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead) ) 

#define IEMSSatelliteInfo2_SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)	\
    ( (This)->lpVtbl -> SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue) ) 

#define IEMSSatelliteInfo2_GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    ( (This)->lpVtbl -> GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead) ) 


#define IEMSSatelliteInfo2_GetName(This,ulSatelliteID,pv,cb,pcbRead)	\
    ( (This)->lpVtbl -> GetName(This,ulSatelliteID,pv,cb,pcbRead) ) 

#define IEMSSatelliteInfo2_GetNoradID(This,ulSatelliteID,lpulNoradID)	\
    ( (This)->lpVtbl -> GetNoradID(This,ulSatelliteID,lpulNoradID) ) 

#define IEMSSatelliteInfo2_GetSatelliteID(This,ulNoradID,lpulSatelliteID)	\
    ( (This)->lpVtbl -> GetSatelliteID(This,ulNoradID,lpulSatelliteID) ) 

#define IEMSSatelliteInfo2_GetFreqBandwidth(This,ulSatelliteID,lplBandwidth)	\
    ( (This)->lpVtbl -> GetFreqBandwidth(This,ulSatelliteID,lplBandwidth) ) 

#define IEMSSatelliteInfo2_GetCaps(This,ulSatelliteID,lpulCapabilities)	\
    ( (This)->lpVtbl -> GetCaps(This,ulSatelliteID,lpulCapabilities) ) 

#define IEMSSatelliteInfo2_Get406SignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> Get406SignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo2_GetCBCSignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> GetCBCSignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo2_GetPDSSignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> GetPDSSignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo2_GetRolloverPeriod(This,ulSatelliteID,lpi64Period)	\
    ( (This)->lpVtbl -> GetRolloverPeriod(This,ulSatelliteID,lpi64Period) ) 

#define IEMSSatelliteInfo2_SetRolloverPeriod(This,ulSatelliteID,i64Period)	\
    ( (This)->lpVtbl -> SetRolloverPeriod(This,ulSatelliteID,i64Period) ) 

#define IEMSSatelliteInfo2_GetRolloverTime(This,ulSatelliteID,lpTimeRollover)	\
    ( (This)->lpVtbl -> GetRolloverTime(This,ulSatelliteID,lpTimeRollover) ) 

#define IEMSSatelliteInfo2_SetRolloverTime(This,ulSatelliteID,timeRollover)	\
    ( (This)->lpVtbl -> SetRolloverTime(This,ulSatelliteID,timeRollover) ) 

#define IEMSSatelliteInfo2_GetRefFreq(This,ulSatelliteID,lpdFreq)	\
    ( (This)->lpVtbl -> GetRefFreq(This,ulSatelliteID,lpdFreq) ) 

#define IEMSSatelliteInfo2_SetRefFreq(This,ulSatelliteID,dFreq)	\
    ( (This)->lpVtbl -> SetRefFreq(This,ulSatelliteID,dFreq) ) 

#define IEMSSatelliteInfo2_SetSarrFreqOffset(This,ulSatelliteID,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarrFreqOffset(This,ulSatelliteID,dFreqOffset) ) 

#define IEMSSatelliteInfo2_GetSarrFreqOffset(This,ulSatelliteID,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarrFreqOffset(This,ulSatelliteID,lpdFreqOffset) ) 

#define IEMSSatelliteInfo2_SetSarrTimeOffset(This,ulSatelliteID,i64TimeOffset)	\
    ( (This)->lpVtbl -> SetSarrTimeOffset(This,ulSatelliteID,i64TimeOffset) ) 

#define IEMSSatelliteInfo2_GetSarrTimeOffset(This,ulSatelliteID,lpi64TimeOffset)	\
    ( (This)->lpVtbl -> GetSarrTimeOffset(This,ulSatelliteID,lpi64TimeOffset) ) 

#define IEMSSatelliteInfo2_SetSarpFreqOffset(This,ulSatelliteID,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarpFreqOffset(This,ulSatelliteID,dFreqOffset) ) 

#define IEMSSatelliteInfo2_GetSarpFreqOffset(This,ulSatelliteID,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarpFreqOffset(This,ulSatelliteID,lpdFreqOffset) ) 

#define IEMSSatelliteInfo2_SetSarpTimeOffset(This,ulSatelliteID,i64TimeOffset)	\
    ( (This)->lpVtbl -> SetSarpTimeOffset(This,ulSatelliteID,i64TimeOffset) ) 

#define IEMSSatelliteInfo2_GetSarpTimeOffset(This,ulSatelliteID,lpi64TimeOffset)	\
    ( (This)->lpVtbl -> GetSarpTimeOffset(This,ulSatelliteID,lpi64TimeOffset) ) 


#define IEMSSatelliteInfo2_GetPhaseDemodSetting(This,ulSatelliteID,lpulPhaseDemod)	\
    ( (This)->lpVtbl -> GetPhaseDemodSetting(This,ulSatelliteID,lpulPhaseDemod) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEMSSatelliteInfo2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSATINF_0000_0002 */
/* [local] */ 

typedef /* [unique] */ IEMSSatelliteInfo2 *LPEMSSATELLITEINFO2;



extern RPC_IF_HANDLE __MIDL_itf_EMSATINF_0000_0002_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSATINF_0000_0002_v0_0_s_ifspec;

#ifndef __IEMSSatelliteInfo3_INTERFACE_DEFINED__
#define __IEMSSatelliteInfo3_INTERFACE_DEFINED__

/* interface IEMSSatelliteInfo3 */
/* [unique][helpstring][uuid][object] */ 

typedef struct _tagEMSSATCONFIGBOOLDATAPROP
    {
    BOOL bSpectrum;
    BOOL bAudio;
    BOOL bSarr;
    BOOL bSarp;
    BOOL bCbc121;
    BOOL bCbc243;
    BOOL bCbc406;
    BOOL bMI406;
    BOOL bLeoGeo;
    BOOL bLeoLeo;
    BOOL bGeoGeo;
    } 	EMSSATCONFIGBOOLDATAPROP;

typedef struct _tagEMSSATCONFIGBOOLDATAPROP *LPEMSSATCONFIGBOOLDATAPROP;

typedef struct _tagEMSSATCONFIGDOUBLEDATAPROP
    {
    DOUBLE dSpectrum;
    DOUBLE dAudio;
    DOUBLE dSarr;
    DOUBLE dSarp;
    DOUBLE dCbc121;
    DOUBLE dCbc243;
    DOUBLE dCbc406;
    DOUBLE dMI406;
    DOUBLE dLeoGeo;
    DOUBLE dLeoLeo;
    DOUBLE dGeoGeo;
    } 	EMSSATCONFIGDOUBLEDATAPROP;

typedef struct _tagEMSSATCONFIGDOUBLEDATAPROP *LPEMSSATCONFIGDOUBLEDATAPROP;

typedef struct _tagEMSSATCONFIGINTDATAPROP
    {
    INT nSpectrum;
    INT nAudio;
    INT nSarr;
    INT nSarp;
    INT nCbc121;
    INT nCbc243;
    INT nCbc406;
    INT nMI406;
    INT nLeoGeo;
    INT nLeoLeo;
    INT nGeoGeo;
    } 	EMSSATCONFIGINTDATAPROP;

typedef struct _tagEMSSATCONFIGINTDATAPROP *LPEMSSATCONFIGINTDATAPROP;

typedef struct _tagEMSSATCONFIGMCCFILTERLEOGEO
    {
    int nWindowFactor;
    int nNumPts;
    double dMinCrossTrackAngle;
    double dMaxCrossTrackAngle;
    } 	EMSSATCONFIGMCCFILTERLEOGEO;

typedef struct _tagEMSSATCONFIGMCCFILTERLEOGEO *LPEMSSATCONFIGMCCFILTERLEOGEO;

typedef struct _tagEMSSATCONFIGMCCSUPPRESS
    {
    EMSSATCONFIGBOOLDATAPROP Located;
    EMSSATCONFIGBOOLDATAPROP UnLocated;
    EMSSATCONFIGBOOLDATAPROP UnLocated1;
    EMSSATCONFIGBOOLDATAPROP UnLocated2;
    EMSSATCONFIGMCCFILTERLEOGEO LeoGeo;
    } 	EMSSATCONFIGMCCSUPPRESS;

typedef struct _tagEMSSATCONFIGMCCSUPPRESS *LPEMSSATCONFIGMCCSUPPRESS;

typedef struct _tagEMSSATCONFIGPROCESS
    {
    EMSSATCONFIGBOOLDATAPROP Normal;
    EMSSATCONFIGBOOLDATAPROP MultiPass;
    EMSSATCONFIGBOOLDATAPROP MultiSat;
    } 	EMSSATCONFIGPROCESS;

typedef struct _tagEMSSATCONFIGPROCESS *LPEMSSATCONFIGPROCESS;

typedef struct _tagEMSSATCONFIGAUDIO
    {
    double dFileDuration;
    double dArchiveDuration;
    ULONG ulFileSize;
    ULONG ulArchiveSize;
    int nBands;
    struct 
        {
        double dMinFreq;
        double dMaxFreq;
        } 	band[ 5 ];
    } 	EMSSATCONFIGAUDIO;

typedef struct _tagEMSSATCONFIGAUDIO *LPEMSSATCONFIGAUDIO;

typedef struct _tagEMSSATCONFIGTCAL
    {
    int nMinPts;
    double dThresholdTime;
    double dThresholdFrequency;
    } 	EMSSATCONFIGTCAL;

typedef struct _tagEMSSATCONFIGTCAL *LPEMSSATCONFIGTCAL;

typedef struct _tagEMSSATCONFIGORBIT
    {
    double dThresholdPosition;
    double dThresholdVelocity;
    int nMinPtsDownlink;
    int nMinPtsBeacon;
    EMSTIME refTime;
    } 	EMSSATCONFIGORBIT;

typedef struct _tagEMSSATCONFIGORBIT *LPEMSSATCONFIGORBIT;


EXTERN_C const IID IID_IEMSSatelliteInfo3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EE8C892B-B6BB-4d4e-A747-D9D4793B55D8")
    IEMSSatelliteInfo3 : public IEMSSatelliteInfo2
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetMCCSuppressInfo( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGMCCSUPPRESS *lpMCCSUPPRESSInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTCALInfo( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGTCAL *lpTCALInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOrbitInfo( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGORBIT *lpOrbitInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAudioInfo( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGAUDIO *lpAudioInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetProcessInfo( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGPROCESS *lpProcessInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCollectInfo( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGBOOLDATAPROP *lpCollectInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPassSchedulePriority( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulPriority) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSarpCalibration( 
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIME timeRollover,
            /* [in] */ double dRefFreq) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSarpCalibration( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeStamp,
            /* [out] */ EMSTIME *lpTimeRollover,
            /* [out] */ double *lpdRefFreq) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDownlinkFreq( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdDownlinkFreq) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSatelliteInfo3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEMSSatelliteInfo3 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEMSSatelliteInfo3 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigFlags )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigFlags )( 
            IEMSSatelliteInfo3 * This,
            /* [out] */ DWORD *lpdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *ReloadConfigData )( 
            IEMSSatelliteInfo3 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigValueA )( 
            IEMSSatelliteInfo3 * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [string][in] */ LPCSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigValueA )( 
            IEMSSatelliteInfo3 * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [length_is][size_is][out] */ unsigned char *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigValueW )( 
            IEMSSatelliteInfo3 * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [string][in] */ LPCWSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigValueW )( 
            IEMSSatelliteInfo3 * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [length_is][size_is][out] */ WCHAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE *GetName )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [length_is][size_is][out] */ BYTE *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG *pcbRead);
        
        HRESULT ( STDMETHODCALLTYPE *GetNoradID )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulNoradID);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatelliteID )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulNoradID,
            /* [out] */ ULONG *lpulSatelliteID);
        
        HRESULT ( STDMETHODCALLTYPE *GetFreqBandwidth )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LONG *lplBandwidth);
        
        HRESULT ( STDMETHODCALLTYPE *GetCaps )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulCapabilities);
        
        HRESULT ( STDMETHODCALLTYPE *Get406SignalData )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMS406SIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetCBCSignalData )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSCBCSIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetPDSSignalData )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSPDSSIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetRolloverPeriod )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64Period);
        
        HRESULT ( STDMETHODCALLTYPE *SetRolloverPeriod )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64Period);
        
        HRESULT ( STDMETHODCALLTYPE *GetRolloverTime )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeRollover);
        
        HRESULT ( STDMETHODCALLTYPE *SetRolloverTime )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIME timeRollover);
        
        HRESULT ( STDMETHODCALLTYPE *GetRefFreq )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreq);
        
        HRESULT ( STDMETHODCALLTYPE *SetRefFreq )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreq);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrFreqOffset )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrFreqOffset )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrTimeOffset )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrTimeOffset )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpFreqOffset )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpFreqOffset )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpTimeOffset )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpTimeOffset )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetPhaseDemodSetting )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulPhaseDemod);
        
        HRESULT ( STDMETHODCALLTYPE *GetMCCSuppressInfo )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGMCCSUPPRESS *lpMCCSUPPRESSInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTCALInfo )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGTCAL *lpTCALInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetOrbitInfo )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGORBIT *lpOrbitInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetAudioInfo )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGAUDIO *lpAudioInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetProcessInfo )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGPROCESS *lpProcessInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetCollectInfo )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGBOOLDATAPROP *lpCollectInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetPassSchedulePriority )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulPriority);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpCalibration )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIME timeRollover,
            /* [in] */ double dRefFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpCalibration )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeStamp,
            /* [out] */ EMSTIME *lpTimeRollover,
            /* [out] */ double *lpdRefFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetDownlinkFreq )( 
            IEMSSatelliteInfo3 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdDownlinkFreq);
        
        END_INTERFACE
    } IEMSSatelliteInfo3Vtbl;

    interface IEMSSatelliteInfo3
    {
        CONST_VTBL struct IEMSSatelliteInfo3Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSatelliteInfo3_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEMSSatelliteInfo3_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEMSSatelliteInfo3_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEMSSatelliteInfo3_SetConfigFlags(This,dwFlags)	\
    ( (This)->lpVtbl -> SetConfigFlags(This,dwFlags) ) 

#define IEMSSatelliteInfo3_GetConfigFlags(This,lpdwFlags)	\
    ( (This)->lpVtbl -> GetConfigFlags(This,lpdwFlags) ) 

#define IEMSSatelliteInfo3_ReloadConfigData(This)	\
    ( (This)->lpVtbl -> ReloadConfigData(This) ) 

#define IEMSSatelliteInfo3_SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)	\
    ( (This)->lpVtbl -> SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue) ) 

#define IEMSSatelliteInfo3_GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    ( (This)->lpVtbl -> GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead) ) 

#define IEMSSatelliteInfo3_SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)	\
    ( (This)->lpVtbl -> SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue) ) 

#define IEMSSatelliteInfo3_GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    ( (This)->lpVtbl -> GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead) ) 


#define IEMSSatelliteInfo3_GetName(This,ulSatelliteID,pv,cb,pcbRead)	\
    ( (This)->lpVtbl -> GetName(This,ulSatelliteID,pv,cb,pcbRead) ) 

#define IEMSSatelliteInfo3_GetNoradID(This,ulSatelliteID,lpulNoradID)	\
    ( (This)->lpVtbl -> GetNoradID(This,ulSatelliteID,lpulNoradID) ) 

#define IEMSSatelliteInfo3_GetSatelliteID(This,ulNoradID,lpulSatelliteID)	\
    ( (This)->lpVtbl -> GetSatelliteID(This,ulNoradID,lpulSatelliteID) ) 

#define IEMSSatelliteInfo3_GetFreqBandwidth(This,ulSatelliteID,lplBandwidth)	\
    ( (This)->lpVtbl -> GetFreqBandwidth(This,ulSatelliteID,lplBandwidth) ) 

#define IEMSSatelliteInfo3_GetCaps(This,ulSatelliteID,lpulCapabilities)	\
    ( (This)->lpVtbl -> GetCaps(This,ulSatelliteID,lpulCapabilities) ) 

#define IEMSSatelliteInfo3_Get406SignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> Get406SignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo3_GetCBCSignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> GetCBCSignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo3_GetPDSSignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> GetPDSSignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo3_GetRolloverPeriod(This,ulSatelliteID,lpi64Period)	\
    ( (This)->lpVtbl -> GetRolloverPeriod(This,ulSatelliteID,lpi64Period) ) 

#define IEMSSatelliteInfo3_SetRolloverPeriod(This,ulSatelliteID,i64Period)	\
    ( (This)->lpVtbl -> SetRolloverPeriod(This,ulSatelliteID,i64Period) ) 

#define IEMSSatelliteInfo3_GetRolloverTime(This,ulSatelliteID,lpTimeRollover)	\
    ( (This)->lpVtbl -> GetRolloverTime(This,ulSatelliteID,lpTimeRollover) ) 

#define IEMSSatelliteInfo3_SetRolloverTime(This,ulSatelliteID,timeRollover)	\
    ( (This)->lpVtbl -> SetRolloverTime(This,ulSatelliteID,timeRollover) ) 

#define IEMSSatelliteInfo3_GetRefFreq(This,ulSatelliteID,lpdFreq)	\
    ( (This)->lpVtbl -> GetRefFreq(This,ulSatelliteID,lpdFreq) ) 

#define IEMSSatelliteInfo3_SetRefFreq(This,ulSatelliteID,dFreq)	\
    ( (This)->lpVtbl -> SetRefFreq(This,ulSatelliteID,dFreq) ) 

#define IEMSSatelliteInfo3_SetSarrFreqOffset(This,ulSatelliteID,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarrFreqOffset(This,ulSatelliteID,dFreqOffset) ) 

#define IEMSSatelliteInfo3_GetSarrFreqOffset(This,ulSatelliteID,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarrFreqOffset(This,ulSatelliteID,lpdFreqOffset) ) 

#define IEMSSatelliteInfo3_SetSarrTimeOffset(This,ulSatelliteID,i64TimeOffset)	\
    ( (This)->lpVtbl -> SetSarrTimeOffset(This,ulSatelliteID,i64TimeOffset) ) 

#define IEMSSatelliteInfo3_GetSarrTimeOffset(This,ulSatelliteID,lpi64TimeOffset)	\
    ( (This)->lpVtbl -> GetSarrTimeOffset(This,ulSatelliteID,lpi64TimeOffset) ) 

#define IEMSSatelliteInfo3_SetSarpFreqOffset(This,ulSatelliteID,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarpFreqOffset(This,ulSatelliteID,dFreqOffset) ) 

#define IEMSSatelliteInfo3_GetSarpFreqOffset(This,ulSatelliteID,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarpFreqOffset(This,ulSatelliteID,lpdFreqOffset) ) 

#define IEMSSatelliteInfo3_SetSarpTimeOffset(This,ulSatelliteID,i64TimeOffset)	\
    ( (This)->lpVtbl -> SetSarpTimeOffset(This,ulSatelliteID,i64TimeOffset) ) 

#define IEMSSatelliteInfo3_GetSarpTimeOffset(This,ulSatelliteID,lpi64TimeOffset)	\
    ( (This)->lpVtbl -> GetSarpTimeOffset(This,ulSatelliteID,lpi64TimeOffset) ) 


#define IEMSSatelliteInfo3_GetPhaseDemodSetting(This,ulSatelliteID,lpulPhaseDemod)	\
    ( (This)->lpVtbl -> GetPhaseDemodSetting(This,ulSatelliteID,lpulPhaseDemod) ) 


#define IEMSSatelliteInfo3_GetMCCSuppressInfo(This,ulSatelliteID,lpMCCSUPPRESSInfo)	\
    ( (This)->lpVtbl -> GetMCCSuppressInfo(This,ulSatelliteID,lpMCCSUPPRESSInfo) ) 

#define IEMSSatelliteInfo3_GetTCALInfo(This,ulSatelliteID,lpTCALInfo)	\
    ( (This)->lpVtbl -> GetTCALInfo(This,ulSatelliteID,lpTCALInfo) ) 

#define IEMSSatelliteInfo3_GetOrbitInfo(This,ulSatelliteID,lpOrbitInfo)	\
    ( (This)->lpVtbl -> GetOrbitInfo(This,ulSatelliteID,lpOrbitInfo) ) 

#define IEMSSatelliteInfo3_GetAudioInfo(This,ulSatelliteID,lpAudioInfo)	\
    ( (This)->lpVtbl -> GetAudioInfo(This,ulSatelliteID,lpAudioInfo) ) 

#define IEMSSatelliteInfo3_GetProcessInfo(This,ulSatelliteID,lpProcessInfo)	\
    ( (This)->lpVtbl -> GetProcessInfo(This,ulSatelliteID,lpProcessInfo) ) 

#define IEMSSatelliteInfo3_GetCollectInfo(This,ulSatelliteID,lpCollectInfo)	\
    ( (This)->lpVtbl -> GetCollectInfo(This,ulSatelliteID,lpCollectInfo) ) 

#define IEMSSatelliteInfo3_GetPassSchedulePriority(This,ulSatelliteID,lpulPriority)	\
    ( (This)->lpVtbl -> GetPassSchedulePriority(This,ulSatelliteID,lpulPriority) ) 

#define IEMSSatelliteInfo3_SetSarpCalibration(This,ulSatelliteID,timeRollover,dRefFreq)	\
    ( (This)->lpVtbl -> SetSarpCalibration(This,ulSatelliteID,timeRollover,dRefFreq) ) 

#define IEMSSatelliteInfo3_GetSarpCalibration(This,ulSatelliteID,lpTimeStamp,lpTimeRollover,lpdRefFreq)	\
    ( (This)->lpVtbl -> GetSarpCalibration(This,ulSatelliteID,lpTimeStamp,lpTimeRollover,lpdRefFreq) ) 

#define IEMSSatelliteInfo3_GetDownlinkFreq(This,ulSatelliteID,lpdDownlinkFreq)	\
    ( (This)->lpVtbl -> GetDownlinkFreq(This,ulSatelliteID,lpdDownlinkFreq) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEMSSatelliteInfo3_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSATINF_0000_0003 */
/* [local] */ 

typedef /* [unique] */ IEMSSatelliteInfo3 *LPEMSSATELLITEINFO3;

// {1892B319-9DB3-4cdc-A78B-728EF2F8CBB2}


extern RPC_IF_HANDLE __MIDL_itf_EMSATINF_0000_0003_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSATINF_0000_0003_v0_0_s_ifspec;

#ifndef __IEMSSatelliteInfo4_INTERFACE_DEFINED__
#define __IEMSSatelliteInfo4_INTERFACE_DEFINED__

/* interface IEMSSatelliteInfo4 */
/* [unique][helpstring][uuid][object] */ 

typedef struct _tagEMSSATCONFIGBOOLDATAPROPEX
    {
    BOOL bSpectrum;
    BOOL bAudio;
    BOOL bSarr;
    BOOL bSarp;
    BOOL bCbc121;
    BOOL bCbc243;
    BOOL bCbc406;
    BOOL bMI406;
    BOOL bLeoGeo;
    BOOL bLeoLeo;
    BOOL bGeoGeo;
    BOOL bReserved;
    } 	EMSSATCONFIGBOOLDATAPROPEX;

typedef struct _tagEMSSATCONFIGBOOLDATAPROPEX *LPEMSSATCONFIGBOOLDATAPROPEX;

typedef struct _tagEMSSATCONFIGMCCSUPPRESSEX
    {
    EMSSATCONFIGBOOLDATAPROPEX Located;
    EMSSATCONFIGBOOLDATAPROPEX UnLocated;
    EMSSATCONFIGBOOLDATAPROPEX UnLocated1;
    EMSSATCONFIGBOOLDATAPROPEX UnLocated2;
    EMSSATCONFIGMCCFILTERLEOGEO LeoGeo;
    } 	EMSSATCONFIGMCCSUPPRESSEX;

typedef struct _tagEMSSATCONFIGMCCSUPPRESSEX *LPEMSSATCONFIGMCCSUPPRESSEX;


EXTERN_C const IID IID_IEMSSatelliteInfo4;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("1892B319-9DB3-4cdc-A78B-728EF2F8CBB2")
    IEMSSatelliteInfo4 : public IEMSSatelliteInfo3
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetMCCSuppressInfoEx( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGMCCSUPPRESSEX *lpMCCSUPPRESSInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSarrCalibration( 
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset,
            /* [in] */ double dFreqOffset) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSarrCalibration( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeStamp,
            /* [out] */ INT64 *lpi64TimeOffset,
            /* [out] */ double *lpdFreqOffset) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetForwardingInfo( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGBOOLDATAPROP *lpForwardingInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSatelliteInfo4Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEMSSatelliteInfo4 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEMSSatelliteInfo4 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigFlags )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigFlags )( 
            IEMSSatelliteInfo4 * This,
            /* [out] */ DWORD *lpdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *ReloadConfigData )( 
            IEMSSatelliteInfo4 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigValueA )( 
            IEMSSatelliteInfo4 * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [string][in] */ LPCSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigValueA )( 
            IEMSSatelliteInfo4 * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [length_is][size_is][out] */ unsigned char *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigValueW )( 
            IEMSSatelliteInfo4 * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [string][in] */ LPCWSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigValueW )( 
            IEMSSatelliteInfo4 * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [length_is][size_is][out] */ WCHAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE *GetName )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [length_is][size_is][out] */ BYTE *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG *pcbRead);
        
        HRESULT ( STDMETHODCALLTYPE *GetNoradID )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulNoradID);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatelliteID )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulNoradID,
            /* [out] */ ULONG *lpulSatelliteID);
        
        HRESULT ( STDMETHODCALLTYPE *GetFreqBandwidth )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LONG *lplBandwidth);
        
        HRESULT ( STDMETHODCALLTYPE *GetCaps )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulCapabilities);
        
        HRESULT ( STDMETHODCALLTYPE *Get406SignalData )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMS406SIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetCBCSignalData )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSCBCSIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetPDSSignalData )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSPDSSIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetRolloverPeriod )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64Period);
        
        HRESULT ( STDMETHODCALLTYPE *SetRolloverPeriod )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64Period);
        
        HRESULT ( STDMETHODCALLTYPE *GetRolloverTime )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeRollover);
        
        HRESULT ( STDMETHODCALLTYPE *SetRolloverTime )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIME timeRollover);
        
        HRESULT ( STDMETHODCALLTYPE *GetRefFreq )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreq);
        
        HRESULT ( STDMETHODCALLTYPE *SetRefFreq )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreq);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrFreqOffset )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrFreqOffset )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrTimeOffset )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrTimeOffset )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpFreqOffset )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpFreqOffset )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpTimeOffset )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpTimeOffset )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetPhaseDemodSetting )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulPhaseDemod);
        
        HRESULT ( STDMETHODCALLTYPE *GetMCCSuppressInfo )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGMCCSUPPRESS *lpMCCSUPPRESSInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTCALInfo )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGTCAL *lpTCALInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetOrbitInfo )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGORBIT *lpOrbitInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetAudioInfo )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGAUDIO *lpAudioInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetProcessInfo )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGPROCESS *lpProcessInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetCollectInfo )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGBOOLDATAPROP *lpCollectInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetPassSchedulePriority )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulPriority);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpCalibration )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIME timeRollover,
            /* [in] */ double dRefFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpCalibration )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeStamp,
            /* [out] */ EMSTIME *lpTimeRollover,
            /* [out] */ double *lpdRefFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetDownlinkFreq )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdDownlinkFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetMCCSuppressInfoEx )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGMCCSUPPRESSEX *lpMCCSUPPRESSInfo);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrCalibration )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrCalibration )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeStamp,
            /* [out] */ INT64 *lpi64TimeOffset,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetForwardingInfo )( 
            IEMSSatelliteInfo4 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGBOOLDATAPROP *lpForwardingInfo);
        
        END_INTERFACE
    } IEMSSatelliteInfo4Vtbl;

    interface IEMSSatelliteInfo4
    {
        CONST_VTBL struct IEMSSatelliteInfo4Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSatelliteInfo4_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEMSSatelliteInfo4_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEMSSatelliteInfo4_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEMSSatelliteInfo4_SetConfigFlags(This,dwFlags)	\
    ( (This)->lpVtbl -> SetConfigFlags(This,dwFlags) ) 

#define IEMSSatelliteInfo4_GetConfigFlags(This,lpdwFlags)	\
    ( (This)->lpVtbl -> GetConfigFlags(This,lpdwFlags) ) 

#define IEMSSatelliteInfo4_ReloadConfigData(This)	\
    ( (This)->lpVtbl -> ReloadConfigData(This) ) 

#define IEMSSatelliteInfo4_SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)	\
    ( (This)->lpVtbl -> SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue) ) 

#define IEMSSatelliteInfo4_GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    ( (This)->lpVtbl -> GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead) ) 

#define IEMSSatelliteInfo4_SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)	\
    ( (This)->lpVtbl -> SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue) ) 

#define IEMSSatelliteInfo4_GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    ( (This)->lpVtbl -> GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead) ) 


#define IEMSSatelliteInfo4_GetName(This,ulSatelliteID,pv,cb,pcbRead)	\
    ( (This)->lpVtbl -> GetName(This,ulSatelliteID,pv,cb,pcbRead) ) 

#define IEMSSatelliteInfo4_GetNoradID(This,ulSatelliteID,lpulNoradID)	\
    ( (This)->lpVtbl -> GetNoradID(This,ulSatelliteID,lpulNoradID) ) 

#define IEMSSatelliteInfo4_GetSatelliteID(This,ulNoradID,lpulSatelliteID)	\
    ( (This)->lpVtbl -> GetSatelliteID(This,ulNoradID,lpulSatelliteID) ) 

#define IEMSSatelliteInfo4_GetFreqBandwidth(This,ulSatelliteID,lplBandwidth)	\
    ( (This)->lpVtbl -> GetFreqBandwidth(This,ulSatelliteID,lplBandwidth) ) 

#define IEMSSatelliteInfo4_GetCaps(This,ulSatelliteID,lpulCapabilities)	\
    ( (This)->lpVtbl -> GetCaps(This,ulSatelliteID,lpulCapabilities) ) 

#define IEMSSatelliteInfo4_Get406SignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> Get406SignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo4_GetCBCSignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> GetCBCSignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo4_GetPDSSignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> GetPDSSignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo4_GetRolloverPeriod(This,ulSatelliteID,lpi64Period)	\
    ( (This)->lpVtbl -> GetRolloverPeriod(This,ulSatelliteID,lpi64Period) ) 

#define IEMSSatelliteInfo4_SetRolloverPeriod(This,ulSatelliteID,i64Period)	\
    ( (This)->lpVtbl -> SetRolloverPeriod(This,ulSatelliteID,i64Period) ) 

#define IEMSSatelliteInfo4_GetRolloverTime(This,ulSatelliteID,lpTimeRollover)	\
    ( (This)->lpVtbl -> GetRolloverTime(This,ulSatelliteID,lpTimeRollover) ) 

#define IEMSSatelliteInfo4_SetRolloverTime(This,ulSatelliteID,timeRollover)	\
    ( (This)->lpVtbl -> SetRolloverTime(This,ulSatelliteID,timeRollover) ) 

#define IEMSSatelliteInfo4_GetRefFreq(This,ulSatelliteID,lpdFreq)	\
    ( (This)->lpVtbl -> GetRefFreq(This,ulSatelliteID,lpdFreq) ) 

#define IEMSSatelliteInfo4_SetRefFreq(This,ulSatelliteID,dFreq)	\
    ( (This)->lpVtbl -> SetRefFreq(This,ulSatelliteID,dFreq) ) 

#define IEMSSatelliteInfo4_SetSarrFreqOffset(This,ulSatelliteID,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarrFreqOffset(This,ulSatelliteID,dFreqOffset) ) 

#define IEMSSatelliteInfo4_GetSarrFreqOffset(This,ulSatelliteID,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarrFreqOffset(This,ulSatelliteID,lpdFreqOffset) ) 

#define IEMSSatelliteInfo4_SetSarrTimeOffset(This,ulSatelliteID,i64TimeOffset)	\
    ( (This)->lpVtbl -> SetSarrTimeOffset(This,ulSatelliteID,i64TimeOffset) ) 

#define IEMSSatelliteInfo4_GetSarrTimeOffset(This,ulSatelliteID,lpi64TimeOffset)	\
    ( (This)->lpVtbl -> GetSarrTimeOffset(This,ulSatelliteID,lpi64TimeOffset) ) 

#define IEMSSatelliteInfo4_SetSarpFreqOffset(This,ulSatelliteID,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarpFreqOffset(This,ulSatelliteID,dFreqOffset) ) 

#define IEMSSatelliteInfo4_GetSarpFreqOffset(This,ulSatelliteID,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarpFreqOffset(This,ulSatelliteID,lpdFreqOffset) ) 

#define IEMSSatelliteInfo4_SetSarpTimeOffset(This,ulSatelliteID,i64TimeOffset)	\
    ( (This)->lpVtbl -> SetSarpTimeOffset(This,ulSatelliteID,i64TimeOffset) ) 

#define IEMSSatelliteInfo4_GetSarpTimeOffset(This,ulSatelliteID,lpi64TimeOffset)	\
    ( (This)->lpVtbl -> GetSarpTimeOffset(This,ulSatelliteID,lpi64TimeOffset) ) 


#define IEMSSatelliteInfo4_GetPhaseDemodSetting(This,ulSatelliteID,lpulPhaseDemod)	\
    ( (This)->lpVtbl -> GetPhaseDemodSetting(This,ulSatelliteID,lpulPhaseDemod) ) 


#define IEMSSatelliteInfo4_GetMCCSuppressInfo(This,ulSatelliteID,lpMCCSUPPRESSInfo)	\
    ( (This)->lpVtbl -> GetMCCSuppressInfo(This,ulSatelliteID,lpMCCSUPPRESSInfo) ) 

#define IEMSSatelliteInfo4_GetTCALInfo(This,ulSatelliteID,lpTCALInfo)	\
    ( (This)->lpVtbl -> GetTCALInfo(This,ulSatelliteID,lpTCALInfo) ) 

#define IEMSSatelliteInfo4_GetOrbitInfo(This,ulSatelliteID,lpOrbitInfo)	\
    ( (This)->lpVtbl -> GetOrbitInfo(This,ulSatelliteID,lpOrbitInfo) ) 

#define IEMSSatelliteInfo4_GetAudioInfo(This,ulSatelliteID,lpAudioInfo)	\
    ( (This)->lpVtbl -> GetAudioInfo(This,ulSatelliteID,lpAudioInfo) ) 

#define IEMSSatelliteInfo4_GetProcessInfo(This,ulSatelliteID,lpProcessInfo)	\
    ( (This)->lpVtbl -> GetProcessInfo(This,ulSatelliteID,lpProcessInfo) ) 

#define IEMSSatelliteInfo4_GetCollectInfo(This,ulSatelliteID,lpCollectInfo)	\
    ( (This)->lpVtbl -> GetCollectInfo(This,ulSatelliteID,lpCollectInfo) ) 

#define IEMSSatelliteInfo4_GetPassSchedulePriority(This,ulSatelliteID,lpulPriority)	\
    ( (This)->lpVtbl -> GetPassSchedulePriority(This,ulSatelliteID,lpulPriority) ) 

#define IEMSSatelliteInfo4_SetSarpCalibration(This,ulSatelliteID,timeRollover,dRefFreq)	\
    ( (This)->lpVtbl -> SetSarpCalibration(This,ulSatelliteID,timeRollover,dRefFreq) ) 

#define IEMSSatelliteInfo4_GetSarpCalibration(This,ulSatelliteID,lpTimeStamp,lpTimeRollover,lpdRefFreq)	\
    ( (This)->lpVtbl -> GetSarpCalibration(This,ulSatelliteID,lpTimeStamp,lpTimeRollover,lpdRefFreq) ) 

#define IEMSSatelliteInfo4_GetDownlinkFreq(This,ulSatelliteID,lpdDownlinkFreq)	\
    ( (This)->lpVtbl -> GetDownlinkFreq(This,ulSatelliteID,lpdDownlinkFreq) ) 


#define IEMSSatelliteInfo4_GetMCCSuppressInfoEx(This,ulSatelliteID,lpMCCSUPPRESSInfo)	\
    ( (This)->lpVtbl -> GetMCCSuppressInfoEx(This,ulSatelliteID,lpMCCSUPPRESSInfo) ) 

#define IEMSSatelliteInfo4_SetSarrCalibration(This,ulSatelliteID,i64TimeOffset,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarrCalibration(This,ulSatelliteID,i64TimeOffset,dFreqOffset) ) 

#define IEMSSatelliteInfo4_GetSarrCalibration(This,ulSatelliteID,lpTimeStamp,lpi64TimeOffset,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarrCalibration(This,ulSatelliteID,lpTimeStamp,lpi64TimeOffset,lpdFreqOffset) ) 

#define IEMSSatelliteInfo4_GetForwardingInfo(This,ulSatelliteID,lpForwardingInfo)	\
    ( (This)->lpVtbl -> GetForwardingInfo(This,ulSatelliteID,lpForwardingInfo) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEMSSatelliteInfo4_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSATINF_0000_0004 */
/* [local] */ 

typedef /* [unique] */ IEMSSatelliteInfo4 *LPEMSSATELLITEINFO4;



extern RPC_IF_HANDLE __MIDL_itf_EMSATINF_0000_0004_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSATINF_0000_0004_v0_0_s_ifspec;

#ifndef __IEMSSatelliteInfo5_INTERFACE_DEFINED__
#define __IEMSSatelliteInfo5_INTERFACE_DEFINED__

/* interface IEMSSatelliteInfo5 */
/* [unique][helpstring][uuid][object] */ 


#pragma pack(1)
typedef 
enum _tagEMSSATBEHAVIOURTYPE
    {	EMS_SBT_InPlaneManoeuvre	= 1,
	EMS_SBT_OutPlaneManoeuvre	= 2,
	EMS_SBT_OutOfService	= 3,
	EMS_SBT_Unknown	= 0
    } 	EMSSATBEHAVIOURTYPE;

typedef 
enum _tagEMSSATBEHAVIOURSTATUS
    {	EMS_SBS_Planned	= 1,
	EMS_SBS_Executed	= 2,
	EMS_SBS_Cancelled	= 3,
	EMS_SBS_Unknown	= 0
    } 	EMSSATBEHAVIOURSTATUS;

typedef struct _tagEMSSATBEHAVIOUR
    {
    ULONG ulSatID;
    EMSTIME timeBegin;
    double dDurationSeconds;
    EMSSATBEHAVIOURTYPE type;
    EMSSATBEHAVIOURSTATUS status;
    } 	EMSSATBEHAVIOUR;

typedef struct _tagEMSSATBEHAVIOUR *LPEMSSATBEHAVIOUR;

typedef struct _tagEMSSATORBITINFO
    {
    ULONG ulSatID;
    EMSTIME timeModified;
    EMSTIME timeEffective;
    EMSTIME timeEpoch;
    } 	EMSSATORBITINFO;

typedef struct _tagEMSSATORBITINFO *LPEMSSATORBITINFO;


#pragma pack()

EXTERN_C const IID IID_IEMSSatelliteInfo5;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6C426984-DCA1-4b55-9C07-6F45322073A0")
    IEMSSatelliteInfo5 : public IEMSSatelliteInfo4
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetSatBehaviourMaxCount( 
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSatBehaviourCount( 
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSatBehaviour( 
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [in] */ EMSSATBEHAVIOUR *lpBehaviour) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSatBehaviourMaxCount( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSatBehaviourCount( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSatBehaviour( 
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [out] */ EMSSATBEHAVIOUR *lpBehaviour) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSatOrbitInfoMaxCount( 
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSatOrbitInfoCount( 
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSatOrbitInfo( 
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [in] */ EMSSATORBITINFO *lpOrbit) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSatOrbitInfoMaxCount( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSatOrbitInfoCount( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSatOrbitInfo( 
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [out] */ EMSSATORBITINFO *lpOrbit) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSatelliteInfo5Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEMSSatelliteInfo5 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEMSSatelliteInfo5 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigFlags )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigFlags )( 
            IEMSSatelliteInfo5 * This,
            /* [out] */ DWORD *lpdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *ReloadConfigData )( 
            IEMSSatelliteInfo5 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigValueA )( 
            IEMSSatelliteInfo5 * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [string][in] */ LPCSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigValueA )( 
            IEMSSatelliteInfo5 * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [length_is][size_is][out] */ unsigned char *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigValueW )( 
            IEMSSatelliteInfo5 * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [string][in] */ LPCWSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigValueW )( 
            IEMSSatelliteInfo5 * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [length_is][size_is][out] */ WCHAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE *GetName )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [length_is][size_is][out] */ BYTE *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG *pcbRead);
        
        HRESULT ( STDMETHODCALLTYPE *GetNoradID )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulNoradID);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatelliteID )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulNoradID,
            /* [out] */ ULONG *lpulSatelliteID);
        
        HRESULT ( STDMETHODCALLTYPE *GetFreqBandwidth )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LONG *lplBandwidth);
        
        HRESULT ( STDMETHODCALLTYPE *GetCaps )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulCapabilities);
        
        HRESULT ( STDMETHODCALLTYPE *Get406SignalData )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMS406SIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetCBCSignalData )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSCBCSIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetPDSSignalData )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSPDSSIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetRolloverPeriod )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64Period);
        
        HRESULT ( STDMETHODCALLTYPE *SetRolloverPeriod )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64Period);
        
        HRESULT ( STDMETHODCALLTYPE *GetRolloverTime )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeRollover);
        
        HRESULT ( STDMETHODCALLTYPE *SetRolloverTime )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIME timeRollover);
        
        HRESULT ( STDMETHODCALLTYPE *GetRefFreq )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreq);
        
        HRESULT ( STDMETHODCALLTYPE *SetRefFreq )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreq);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrFreqOffset )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrFreqOffset )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrTimeOffset )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrTimeOffset )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpFreqOffset )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpFreqOffset )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpTimeOffset )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpTimeOffset )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetPhaseDemodSetting )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulPhaseDemod);
        
        HRESULT ( STDMETHODCALLTYPE *GetMCCSuppressInfo )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGMCCSUPPRESS *lpMCCSUPPRESSInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTCALInfo )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGTCAL *lpTCALInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetOrbitInfo )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGORBIT *lpOrbitInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetAudioInfo )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGAUDIO *lpAudioInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetProcessInfo )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGPROCESS *lpProcessInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetCollectInfo )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGBOOLDATAPROP *lpCollectInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetPassSchedulePriority )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulPriority);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpCalibration )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIME timeRollover,
            /* [in] */ double dRefFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpCalibration )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeStamp,
            /* [out] */ EMSTIME *lpTimeRollover,
            /* [out] */ double *lpdRefFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetDownlinkFreq )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdDownlinkFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetMCCSuppressInfoEx )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGMCCSUPPRESSEX *lpMCCSUPPRESSInfo);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrCalibration )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrCalibration )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeStamp,
            /* [out] */ INT64 *lpi64TimeOffset,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetForwardingInfo )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGBOOLDATAPROP *lpForwardingInfo);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatBehaviourMaxCount )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatBehaviourCount )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatBehaviour )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [in] */ EMSSATBEHAVIOUR *lpBehaviour);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatBehaviourMaxCount )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatBehaviourCount )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatBehaviour )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [out] */ EMSSATBEHAVIOUR *lpBehaviour);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatOrbitInfoMaxCount )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatOrbitInfoCount )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatOrbitInfo )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [in] */ EMSSATORBITINFO *lpOrbit);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatOrbitInfoMaxCount )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatOrbitInfoCount )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatOrbitInfo )( 
            IEMSSatelliteInfo5 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [out] */ EMSSATORBITINFO *lpOrbit);
        
        END_INTERFACE
    } IEMSSatelliteInfo5Vtbl;

    interface IEMSSatelliteInfo5
    {
        CONST_VTBL struct IEMSSatelliteInfo5Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSatelliteInfo5_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEMSSatelliteInfo5_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEMSSatelliteInfo5_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEMSSatelliteInfo5_SetConfigFlags(This,dwFlags)	\
    ( (This)->lpVtbl -> SetConfigFlags(This,dwFlags) ) 

#define IEMSSatelliteInfo5_GetConfigFlags(This,lpdwFlags)	\
    ( (This)->lpVtbl -> GetConfigFlags(This,lpdwFlags) ) 

#define IEMSSatelliteInfo5_ReloadConfigData(This)	\
    ( (This)->lpVtbl -> ReloadConfigData(This) ) 

#define IEMSSatelliteInfo5_SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)	\
    ( (This)->lpVtbl -> SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue) ) 

#define IEMSSatelliteInfo5_GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    ( (This)->lpVtbl -> GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead) ) 

#define IEMSSatelliteInfo5_SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)	\
    ( (This)->lpVtbl -> SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue) ) 

#define IEMSSatelliteInfo5_GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    ( (This)->lpVtbl -> GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead) ) 


#define IEMSSatelliteInfo5_GetName(This,ulSatelliteID,pv,cb,pcbRead)	\
    ( (This)->lpVtbl -> GetName(This,ulSatelliteID,pv,cb,pcbRead) ) 

#define IEMSSatelliteInfo5_GetNoradID(This,ulSatelliteID,lpulNoradID)	\
    ( (This)->lpVtbl -> GetNoradID(This,ulSatelliteID,lpulNoradID) ) 

#define IEMSSatelliteInfo5_GetSatelliteID(This,ulNoradID,lpulSatelliteID)	\
    ( (This)->lpVtbl -> GetSatelliteID(This,ulNoradID,lpulSatelliteID) ) 

#define IEMSSatelliteInfo5_GetFreqBandwidth(This,ulSatelliteID,lplBandwidth)	\
    ( (This)->lpVtbl -> GetFreqBandwidth(This,ulSatelliteID,lplBandwidth) ) 

#define IEMSSatelliteInfo5_GetCaps(This,ulSatelliteID,lpulCapabilities)	\
    ( (This)->lpVtbl -> GetCaps(This,ulSatelliteID,lpulCapabilities) ) 

#define IEMSSatelliteInfo5_Get406SignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> Get406SignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo5_GetCBCSignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> GetCBCSignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo5_GetPDSSignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> GetPDSSignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo5_GetRolloverPeriod(This,ulSatelliteID,lpi64Period)	\
    ( (This)->lpVtbl -> GetRolloverPeriod(This,ulSatelliteID,lpi64Period) ) 

#define IEMSSatelliteInfo5_SetRolloverPeriod(This,ulSatelliteID,i64Period)	\
    ( (This)->lpVtbl -> SetRolloverPeriod(This,ulSatelliteID,i64Period) ) 

#define IEMSSatelliteInfo5_GetRolloverTime(This,ulSatelliteID,lpTimeRollover)	\
    ( (This)->lpVtbl -> GetRolloverTime(This,ulSatelliteID,lpTimeRollover) ) 

#define IEMSSatelliteInfo5_SetRolloverTime(This,ulSatelliteID,timeRollover)	\
    ( (This)->lpVtbl -> SetRolloverTime(This,ulSatelliteID,timeRollover) ) 

#define IEMSSatelliteInfo5_GetRefFreq(This,ulSatelliteID,lpdFreq)	\
    ( (This)->lpVtbl -> GetRefFreq(This,ulSatelliteID,lpdFreq) ) 

#define IEMSSatelliteInfo5_SetRefFreq(This,ulSatelliteID,dFreq)	\
    ( (This)->lpVtbl -> SetRefFreq(This,ulSatelliteID,dFreq) ) 

#define IEMSSatelliteInfo5_SetSarrFreqOffset(This,ulSatelliteID,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarrFreqOffset(This,ulSatelliteID,dFreqOffset) ) 

#define IEMSSatelliteInfo5_GetSarrFreqOffset(This,ulSatelliteID,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarrFreqOffset(This,ulSatelliteID,lpdFreqOffset) ) 

#define IEMSSatelliteInfo5_SetSarrTimeOffset(This,ulSatelliteID,i64TimeOffset)	\
    ( (This)->lpVtbl -> SetSarrTimeOffset(This,ulSatelliteID,i64TimeOffset) ) 

#define IEMSSatelliteInfo5_GetSarrTimeOffset(This,ulSatelliteID,lpi64TimeOffset)	\
    ( (This)->lpVtbl -> GetSarrTimeOffset(This,ulSatelliteID,lpi64TimeOffset) ) 

#define IEMSSatelliteInfo5_SetSarpFreqOffset(This,ulSatelliteID,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarpFreqOffset(This,ulSatelliteID,dFreqOffset) ) 

#define IEMSSatelliteInfo5_GetSarpFreqOffset(This,ulSatelliteID,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarpFreqOffset(This,ulSatelliteID,lpdFreqOffset) ) 

#define IEMSSatelliteInfo5_SetSarpTimeOffset(This,ulSatelliteID,i64TimeOffset)	\
    ( (This)->lpVtbl -> SetSarpTimeOffset(This,ulSatelliteID,i64TimeOffset) ) 

#define IEMSSatelliteInfo5_GetSarpTimeOffset(This,ulSatelliteID,lpi64TimeOffset)	\
    ( (This)->lpVtbl -> GetSarpTimeOffset(This,ulSatelliteID,lpi64TimeOffset) ) 


#define IEMSSatelliteInfo5_GetPhaseDemodSetting(This,ulSatelliteID,lpulPhaseDemod)	\
    ( (This)->lpVtbl -> GetPhaseDemodSetting(This,ulSatelliteID,lpulPhaseDemod) ) 


#define IEMSSatelliteInfo5_GetMCCSuppressInfo(This,ulSatelliteID,lpMCCSUPPRESSInfo)	\
    ( (This)->lpVtbl -> GetMCCSuppressInfo(This,ulSatelliteID,lpMCCSUPPRESSInfo) ) 

#define IEMSSatelliteInfo5_GetTCALInfo(This,ulSatelliteID,lpTCALInfo)	\
    ( (This)->lpVtbl -> GetTCALInfo(This,ulSatelliteID,lpTCALInfo) ) 

#define IEMSSatelliteInfo5_GetOrbitInfo(This,ulSatelliteID,lpOrbitInfo)	\
    ( (This)->lpVtbl -> GetOrbitInfo(This,ulSatelliteID,lpOrbitInfo) ) 

#define IEMSSatelliteInfo5_GetAudioInfo(This,ulSatelliteID,lpAudioInfo)	\
    ( (This)->lpVtbl -> GetAudioInfo(This,ulSatelliteID,lpAudioInfo) ) 

#define IEMSSatelliteInfo5_GetProcessInfo(This,ulSatelliteID,lpProcessInfo)	\
    ( (This)->lpVtbl -> GetProcessInfo(This,ulSatelliteID,lpProcessInfo) ) 

#define IEMSSatelliteInfo5_GetCollectInfo(This,ulSatelliteID,lpCollectInfo)	\
    ( (This)->lpVtbl -> GetCollectInfo(This,ulSatelliteID,lpCollectInfo) ) 

#define IEMSSatelliteInfo5_GetPassSchedulePriority(This,ulSatelliteID,lpulPriority)	\
    ( (This)->lpVtbl -> GetPassSchedulePriority(This,ulSatelliteID,lpulPriority) ) 

#define IEMSSatelliteInfo5_SetSarpCalibration(This,ulSatelliteID,timeRollover,dRefFreq)	\
    ( (This)->lpVtbl -> SetSarpCalibration(This,ulSatelliteID,timeRollover,dRefFreq) ) 

#define IEMSSatelliteInfo5_GetSarpCalibration(This,ulSatelliteID,lpTimeStamp,lpTimeRollover,lpdRefFreq)	\
    ( (This)->lpVtbl -> GetSarpCalibration(This,ulSatelliteID,lpTimeStamp,lpTimeRollover,lpdRefFreq) ) 

#define IEMSSatelliteInfo5_GetDownlinkFreq(This,ulSatelliteID,lpdDownlinkFreq)	\
    ( (This)->lpVtbl -> GetDownlinkFreq(This,ulSatelliteID,lpdDownlinkFreq) ) 


#define IEMSSatelliteInfo5_GetMCCSuppressInfoEx(This,ulSatelliteID,lpMCCSUPPRESSInfo)	\
    ( (This)->lpVtbl -> GetMCCSuppressInfoEx(This,ulSatelliteID,lpMCCSUPPRESSInfo) ) 

#define IEMSSatelliteInfo5_SetSarrCalibration(This,ulSatelliteID,i64TimeOffset,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarrCalibration(This,ulSatelliteID,i64TimeOffset,dFreqOffset) ) 

#define IEMSSatelliteInfo5_GetSarrCalibration(This,ulSatelliteID,lpTimeStamp,lpi64TimeOffset,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarrCalibration(This,ulSatelliteID,lpTimeStamp,lpi64TimeOffset,lpdFreqOffset) ) 

#define IEMSSatelliteInfo5_GetForwardingInfo(This,ulSatelliteID,lpForwardingInfo)	\
    ( (This)->lpVtbl -> GetForwardingInfo(This,ulSatelliteID,lpForwardingInfo) ) 


#define IEMSSatelliteInfo5_SetSatBehaviourMaxCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatBehaviourMaxCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo5_SetSatBehaviourCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatBehaviourCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo5_SetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour)	\
    ( (This)->lpVtbl -> SetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour) ) 

#define IEMSSatelliteInfo5_GetSatBehaviourMaxCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatBehaviourMaxCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo5_GetSatBehaviourCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatBehaviourCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo5_GetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour)	\
    ( (This)->lpVtbl -> GetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour) ) 

#define IEMSSatelliteInfo5_SetSatOrbitInfoMaxCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatOrbitInfoMaxCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo5_SetSatOrbitInfoCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatOrbitInfoCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo5_SetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit)	\
    ( (This)->lpVtbl -> SetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit) ) 

#define IEMSSatelliteInfo5_GetSatOrbitInfoMaxCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatOrbitInfoMaxCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo5_GetSatOrbitInfoCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatOrbitInfoCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo5_GetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit)	\
    ( (This)->lpVtbl -> GetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEMSSatelliteInfo5_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSATINF_0000_0005 */
/* [local] */ 

typedef /* [unique] */ IEMSSatelliteInfo5 *LPEMSSATELLITEINFO5;



extern RPC_IF_HANDLE __MIDL_itf_EMSATINF_0000_0005_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSATINF_0000_0005_v0_0_s_ifspec;

#ifndef __IEMSSatelliteInfo6_INTERFACE_DEFINED__
#define __IEMSSatelliteInfo6_INTERFACE_DEFINED__

/* interface IEMSSatelliteInfo6 */
/* [unique][helpstring][uuid][object] */ 

typedef struct _tagEMSCALIBCBCCONFIGDATA
    {
    BYTE bAmplitudeMinimum;
    double dTimeResolution;
    double dFrequencyResolution;
    double dFrequencyBandwidth;
    double dCorrelationThreshold;
    long lTemplateNumber;
    double dTemplateDuration;
    } 	EMSCALIBCBCCONFIGDATA;

typedef struct _tagEMSCALIBCBCCONFIGDATA *LPEMSCALIBCBCCONFIGDATA;

typedef struct _tagEMSTCALCONFIGDATA
    {
    double dUpdatePeriod;
    double dDuration;
    long lMinPts;
    double dTimeThreshold;
    double dFrequencyThreshold;
    } 	EMSTCALCONFIGDATA;

typedef struct _tagEMSTCALCONFIGDATA *LPEMSTCALCONFIGDATA;

typedef struct _tagEMSMI406CONFIGDATA
    {
    BOOL bRestart;
    double dWindowFreq;
    double dWindowTime;
    DWORD dwWindowBits;
    INT nOutOfSpecWindowBits;
    double dMsgTimeoutMinutes;
    BOOL bMsgForceUpdate;
    DWORD dwFSErrMax;
    DWORD dwPF1ErrMax;
    DWORD dwPF2ErrMax;
    DWORD dwAgeout;
    double dCNR1Threshold;
    double dCNR2Threshold;
    double dSarrFreqOffsetThreshold;
    double dSummaryInterval;
    } 	EMSMI406CONFIGDATA;

typedef struct _tagEMSMI406CONFIGDATA *LPEMSMI406CONFIGDATA;

typedef struct _tagEMSCALIB406CONFIGDATA
    {
    EMSTIME timeLastMsg;
    double dRealTimeDelaySecs;
    double dSarrSarpHistoryAgeoutDays;
    double dSarrSarpFreqDiffHz;
    double dSarrSarpTimeDiffSecs;
    INT nSarrSarpMinCount;
    BOOL bSarrSarpCombine;
    } 	EMSCALIB406CONFIGDATA;

typedef struct _tagEMSCALIB406CONFIGDATA *LPEMSCALIB406CONFIGDATA;

typedef struct _tagEMSORBITDETCONFIGDATA
    {
    double dPositionThreshold;
    double dVelocityThreshold;
    double dDurationMaximum;
    int iIterationMinimum;
    int iIterationMaximum;
    double dResidualMinimum;
    double dResidualMaximum;
    BOOL bDownlink;
    ULONG ulBeaconMinPts;
    } 	EMSORBITDETCONFIGDATA;

typedef struct _tagEMSORBITDETCONFIGDATA *LPEMSORBITDETCONFIGDATA;

typedef struct _tagEMSLOCATECBCCONFIGDATA
    {
    ULONG ulDetectMinimum;
    BYTE cAmplitudeRangeMin;
    BYTE cAmplitudeRangeMax;
    ULONG ulIterationsMaximum;
    double dThreshold;
    double dCorrelationMaximum;
    BOOL bDrift;
    double dEEScaleFactors[ 3 ];
    double dEEAdjustments[ 3 ];
    double dSweepThreshold;
    ULONG ulSweepMinPoints;
    } 	EMSLOCATECBCCONFIGDATA;

typedef struct _tagEMSLOCATECBCCONFIGDATA *LPEMSLOCATECBCCONFIGDATA;

typedef struct _tagEMSLOCATE406CONFIGDATA
    {
    ULONG ulIterationsMaximum;
    double dThreshold;
    double dCorrelationMaximum;
    BOOL bDrift;
    BOOL bAltitude;
    double dEEScaleFactors[ 3 ];
    double dEEAdjustments[ 3 ];
    } 	EMSLOCATE406CONFIGDATA;

typedef struct _tagEMSLOCATE406CONFIGDATA *LPEMSLOCATE406CONFIGDATA;


EXTERN_C const IID IID_IEMSSatelliteInfo6;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("52D3FE92-2255-4f37-9846-56BD322B4282")
    IEMSSatelliteInfo6 : public IEMSSatelliteInfo5
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetCalibCbcConfigData( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LPEMSCALIBCBCCONFIGDATA lpCalibCbcConfigData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTcalConfigData( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LPEMSTCALCONFIGDATA lpTcalConfigData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMI406ConfigData( 
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSMI406CONFIGDATA lpMI406ConfigData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCalib406ConfigData( 
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSCALIB406CONFIGDATA lpCalib406ConfigData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOrbitDetConfigData( 
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSORBITDETCONFIGDATA lpOrbitDetConfigData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLocateCBCConfigData( 
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSLOCATECBCCONFIGDATA lpLocateCbcConfigData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLocate406ConfigData( 
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSLOCATE406CONFIGDATA lpLocate406ConfigData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSatelliteInfo6Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEMSSatelliteInfo6 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEMSSatelliteInfo6 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigFlags )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigFlags )( 
            IEMSSatelliteInfo6 * This,
            /* [out] */ DWORD *lpdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *ReloadConfigData )( 
            IEMSSatelliteInfo6 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigValueA )( 
            IEMSSatelliteInfo6 * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [string][in] */ LPCSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigValueA )( 
            IEMSSatelliteInfo6 * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [length_is][size_is][out] */ unsigned char *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigValueW )( 
            IEMSSatelliteInfo6 * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [string][in] */ LPCWSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigValueW )( 
            IEMSSatelliteInfo6 * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [length_is][size_is][out] */ WCHAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE *GetName )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [length_is][size_is][out] */ BYTE *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG *pcbRead);
        
        HRESULT ( STDMETHODCALLTYPE *GetNoradID )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulNoradID);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatelliteID )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulNoradID,
            /* [out] */ ULONG *lpulSatelliteID);
        
        HRESULT ( STDMETHODCALLTYPE *GetFreqBandwidth )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LONG *lplBandwidth);
        
        HRESULT ( STDMETHODCALLTYPE *GetCaps )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulCapabilities);
        
        HRESULT ( STDMETHODCALLTYPE *Get406SignalData )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMS406SIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetCBCSignalData )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSCBCSIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetPDSSignalData )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSPDSSIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetRolloverPeriod )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64Period);
        
        HRESULT ( STDMETHODCALLTYPE *SetRolloverPeriod )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64Period);
        
        HRESULT ( STDMETHODCALLTYPE *GetRolloverTime )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeRollover);
        
        HRESULT ( STDMETHODCALLTYPE *SetRolloverTime )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIME timeRollover);
        
        HRESULT ( STDMETHODCALLTYPE *GetRefFreq )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreq);
        
        HRESULT ( STDMETHODCALLTYPE *SetRefFreq )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreq);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrFreqOffset )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrFreqOffset )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrTimeOffset )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrTimeOffset )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpFreqOffset )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpFreqOffset )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpTimeOffset )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpTimeOffset )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetPhaseDemodSetting )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulPhaseDemod);
        
        HRESULT ( STDMETHODCALLTYPE *GetMCCSuppressInfo )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGMCCSUPPRESS *lpMCCSUPPRESSInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTCALInfo )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGTCAL *lpTCALInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetOrbitInfo )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGORBIT *lpOrbitInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetAudioInfo )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGAUDIO *lpAudioInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetProcessInfo )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGPROCESS *lpProcessInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetCollectInfo )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGBOOLDATAPROP *lpCollectInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetPassSchedulePriority )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulPriority);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpCalibration )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIME timeRollover,
            /* [in] */ double dRefFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpCalibration )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeStamp,
            /* [out] */ EMSTIME *lpTimeRollover,
            /* [out] */ double *lpdRefFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetDownlinkFreq )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdDownlinkFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetMCCSuppressInfoEx )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGMCCSUPPRESSEX *lpMCCSUPPRESSInfo);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrCalibration )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrCalibration )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeStamp,
            /* [out] */ INT64 *lpi64TimeOffset,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetForwardingInfo )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGBOOLDATAPROP *lpForwardingInfo);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatBehaviourMaxCount )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatBehaviourCount )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatBehaviour )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [in] */ EMSSATBEHAVIOUR *lpBehaviour);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatBehaviourMaxCount )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatBehaviourCount )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatBehaviour )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [out] */ EMSSATBEHAVIOUR *lpBehaviour);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatOrbitInfoMaxCount )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatOrbitInfoCount )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatOrbitInfo )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [in] */ EMSSATORBITINFO *lpOrbit);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatOrbitInfoMaxCount )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatOrbitInfoCount )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatOrbitInfo )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [out] */ EMSSATORBITINFO *lpOrbit);
        
        HRESULT ( STDMETHODCALLTYPE *GetCalibCbcConfigData )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LPEMSCALIBCBCCONFIGDATA lpCalibCbcConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetTcalConfigData )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LPEMSTCALCONFIGDATA lpTcalConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetMI406ConfigData )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSMI406CONFIGDATA lpMI406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetCalib406ConfigData )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSCALIB406CONFIGDATA lpCalib406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetOrbitDetConfigData )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSORBITDETCONFIGDATA lpOrbitDetConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetLocateCBCConfigData )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSLOCATECBCCONFIGDATA lpLocateCbcConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetLocate406ConfigData )( 
            IEMSSatelliteInfo6 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSLOCATE406CONFIGDATA lpLocate406ConfigData);
        
        END_INTERFACE
    } IEMSSatelliteInfo6Vtbl;

    interface IEMSSatelliteInfo6
    {
        CONST_VTBL struct IEMSSatelliteInfo6Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSatelliteInfo6_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEMSSatelliteInfo6_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEMSSatelliteInfo6_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEMSSatelliteInfo6_SetConfigFlags(This,dwFlags)	\
    ( (This)->lpVtbl -> SetConfigFlags(This,dwFlags) ) 

#define IEMSSatelliteInfo6_GetConfigFlags(This,lpdwFlags)	\
    ( (This)->lpVtbl -> GetConfigFlags(This,lpdwFlags) ) 

#define IEMSSatelliteInfo6_ReloadConfigData(This)	\
    ( (This)->lpVtbl -> ReloadConfigData(This) ) 

#define IEMSSatelliteInfo6_SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)	\
    ( (This)->lpVtbl -> SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue) ) 

#define IEMSSatelliteInfo6_GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    ( (This)->lpVtbl -> GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead) ) 

#define IEMSSatelliteInfo6_SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)	\
    ( (This)->lpVtbl -> SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue) ) 

#define IEMSSatelliteInfo6_GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    ( (This)->lpVtbl -> GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead) ) 


#define IEMSSatelliteInfo6_GetName(This,ulSatelliteID,pv,cb,pcbRead)	\
    ( (This)->lpVtbl -> GetName(This,ulSatelliteID,pv,cb,pcbRead) ) 

#define IEMSSatelliteInfo6_GetNoradID(This,ulSatelliteID,lpulNoradID)	\
    ( (This)->lpVtbl -> GetNoradID(This,ulSatelliteID,lpulNoradID) ) 

#define IEMSSatelliteInfo6_GetSatelliteID(This,ulNoradID,lpulSatelliteID)	\
    ( (This)->lpVtbl -> GetSatelliteID(This,ulNoradID,lpulSatelliteID) ) 

#define IEMSSatelliteInfo6_GetFreqBandwidth(This,ulSatelliteID,lplBandwidth)	\
    ( (This)->lpVtbl -> GetFreqBandwidth(This,ulSatelliteID,lplBandwidth) ) 

#define IEMSSatelliteInfo6_GetCaps(This,ulSatelliteID,lpulCapabilities)	\
    ( (This)->lpVtbl -> GetCaps(This,ulSatelliteID,lpulCapabilities) ) 

#define IEMSSatelliteInfo6_Get406SignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> Get406SignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo6_GetCBCSignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> GetCBCSignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo6_GetPDSSignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> GetPDSSignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo6_GetRolloverPeriod(This,ulSatelliteID,lpi64Period)	\
    ( (This)->lpVtbl -> GetRolloverPeriod(This,ulSatelliteID,lpi64Period) ) 

#define IEMSSatelliteInfo6_SetRolloverPeriod(This,ulSatelliteID,i64Period)	\
    ( (This)->lpVtbl -> SetRolloverPeriod(This,ulSatelliteID,i64Period) ) 

#define IEMSSatelliteInfo6_GetRolloverTime(This,ulSatelliteID,lpTimeRollover)	\
    ( (This)->lpVtbl -> GetRolloverTime(This,ulSatelliteID,lpTimeRollover) ) 

#define IEMSSatelliteInfo6_SetRolloverTime(This,ulSatelliteID,timeRollover)	\
    ( (This)->lpVtbl -> SetRolloverTime(This,ulSatelliteID,timeRollover) ) 

#define IEMSSatelliteInfo6_GetRefFreq(This,ulSatelliteID,lpdFreq)	\
    ( (This)->lpVtbl -> GetRefFreq(This,ulSatelliteID,lpdFreq) ) 

#define IEMSSatelliteInfo6_SetRefFreq(This,ulSatelliteID,dFreq)	\
    ( (This)->lpVtbl -> SetRefFreq(This,ulSatelliteID,dFreq) ) 

#define IEMSSatelliteInfo6_SetSarrFreqOffset(This,ulSatelliteID,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarrFreqOffset(This,ulSatelliteID,dFreqOffset) ) 

#define IEMSSatelliteInfo6_GetSarrFreqOffset(This,ulSatelliteID,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarrFreqOffset(This,ulSatelliteID,lpdFreqOffset) ) 

#define IEMSSatelliteInfo6_SetSarrTimeOffset(This,ulSatelliteID,i64TimeOffset)	\
    ( (This)->lpVtbl -> SetSarrTimeOffset(This,ulSatelliteID,i64TimeOffset) ) 

#define IEMSSatelliteInfo6_GetSarrTimeOffset(This,ulSatelliteID,lpi64TimeOffset)	\
    ( (This)->lpVtbl -> GetSarrTimeOffset(This,ulSatelliteID,lpi64TimeOffset) ) 

#define IEMSSatelliteInfo6_SetSarpFreqOffset(This,ulSatelliteID,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarpFreqOffset(This,ulSatelliteID,dFreqOffset) ) 

#define IEMSSatelliteInfo6_GetSarpFreqOffset(This,ulSatelliteID,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarpFreqOffset(This,ulSatelliteID,lpdFreqOffset) ) 

#define IEMSSatelliteInfo6_SetSarpTimeOffset(This,ulSatelliteID,i64TimeOffset)	\
    ( (This)->lpVtbl -> SetSarpTimeOffset(This,ulSatelliteID,i64TimeOffset) ) 

#define IEMSSatelliteInfo6_GetSarpTimeOffset(This,ulSatelliteID,lpi64TimeOffset)	\
    ( (This)->lpVtbl -> GetSarpTimeOffset(This,ulSatelliteID,lpi64TimeOffset) ) 


#define IEMSSatelliteInfo6_GetPhaseDemodSetting(This,ulSatelliteID,lpulPhaseDemod)	\
    ( (This)->lpVtbl -> GetPhaseDemodSetting(This,ulSatelliteID,lpulPhaseDemod) ) 


#define IEMSSatelliteInfo6_GetMCCSuppressInfo(This,ulSatelliteID,lpMCCSUPPRESSInfo)	\
    ( (This)->lpVtbl -> GetMCCSuppressInfo(This,ulSatelliteID,lpMCCSUPPRESSInfo) ) 

#define IEMSSatelliteInfo6_GetTCALInfo(This,ulSatelliteID,lpTCALInfo)	\
    ( (This)->lpVtbl -> GetTCALInfo(This,ulSatelliteID,lpTCALInfo) ) 

#define IEMSSatelliteInfo6_GetOrbitInfo(This,ulSatelliteID,lpOrbitInfo)	\
    ( (This)->lpVtbl -> GetOrbitInfo(This,ulSatelliteID,lpOrbitInfo) ) 

#define IEMSSatelliteInfo6_GetAudioInfo(This,ulSatelliteID,lpAudioInfo)	\
    ( (This)->lpVtbl -> GetAudioInfo(This,ulSatelliteID,lpAudioInfo) ) 

#define IEMSSatelliteInfo6_GetProcessInfo(This,ulSatelliteID,lpProcessInfo)	\
    ( (This)->lpVtbl -> GetProcessInfo(This,ulSatelliteID,lpProcessInfo) ) 

#define IEMSSatelliteInfo6_GetCollectInfo(This,ulSatelliteID,lpCollectInfo)	\
    ( (This)->lpVtbl -> GetCollectInfo(This,ulSatelliteID,lpCollectInfo) ) 

#define IEMSSatelliteInfo6_GetPassSchedulePriority(This,ulSatelliteID,lpulPriority)	\
    ( (This)->lpVtbl -> GetPassSchedulePriority(This,ulSatelliteID,lpulPriority) ) 

#define IEMSSatelliteInfo6_SetSarpCalibration(This,ulSatelliteID,timeRollover,dRefFreq)	\
    ( (This)->lpVtbl -> SetSarpCalibration(This,ulSatelliteID,timeRollover,dRefFreq) ) 

#define IEMSSatelliteInfo6_GetSarpCalibration(This,ulSatelliteID,lpTimeStamp,lpTimeRollover,lpdRefFreq)	\
    ( (This)->lpVtbl -> GetSarpCalibration(This,ulSatelliteID,lpTimeStamp,lpTimeRollover,lpdRefFreq) ) 

#define IEMSSatelliteInfo6_GetDownlinkFreq(This,ulSatelliteID,lpdDownlinkFreq)	\
    ( (This)->lpVtbl -> GetDownlinkFreq(This,ulSatelliteID,lpdDownlinkFreq) ) 


#define IEMSSatelliteInfo6_GetMCCSuppressInfoEx(This,ulSatelliteID,lpMCCSUPPRESSInfo)	\
    ( (This)->lpVtbl -> GetMCCSuppressInfoEx(This,ulSatelliteID,lpMCCSUPPRESSInfo) ) 

#define IEMSSatelliteInfo6_SetSarrCalibration(This,ulSatelliteID,i64TimeOffset,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarrCalibration(This,ulSatelliteID,i64TimeOffset,dFreqOffset) ) 

#define IEMSSatelliteInfo6_GetSarrCalibration(This,ulSatelliteID,lpTimeStamp,lpi64TimeOffset,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarrCalibration(This,ulSatelliteID,lpTimeStamp,lpi64TimeOffset,lpdFreqOffset) ) 

#define IEMSSatelliteInfo6_GetForwardingInfo(This,ulSatelliteID,lpForwardingInfo)	\
    ( (This)->lpVtbl -> GetForwardingInfo(This,ulSatelliteID,lpForwardingInfo) ) 


#define IEMSSatelliteInfo6_SetSatBehaviourMaxCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatBehaviourMaxCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo6_SetSatBehaviourCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatBehaviourCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo6_SetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour)	\
    ( (This)->lpVtbl -> SetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour) ) 

#define IEMSSatelliteInfo6_GetSatBehaviourMaxCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatBehaviourMaxCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo6_GetSatBehaviourCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatBehaviourCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo6_GetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour)	\
    ( (This)->lpVtbl -> GetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour) ) 

#define IEMSSatelliteInfo6_SetSatOrbitInfoMaxCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatOrbitInfoMaxCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo6_SetSatOrbitInfoCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatOrbitInfoCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo6_SetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit)	\
    ( (This)->lpVtbl -> SetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit) ) 

#define IEMSSatelliteInfo6_GetSatOrbitInfoMaxCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatOrbitInfoMaxCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo6_GetSatOrbitInfoCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatOrbitInfoCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo6_GetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit)	\
    ( (This)->lpVtbl -> GetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit) ) 


#define IEMSSatelliteInfo6_GetCalibCbcConfigData(This,ulSatelliteID,lpCalibCbcConfigData)	\
    ( (This)->lpVtbl -> GetCalibCbcConfigData(This,ulSatelliteID,lpCalibCbcConfigData) ) 

#define IEMSSatelliteInfo6_GetTcalConfigData(This,ulSatelliteID,lpTcalConfigData)	\
    ( (This)->lpVtbl -> GetTcalConfigData(This,ulSatelliteID,lpTcalConfigData) ) 

#define IEMSSatelliteInfo6_GetMI406ConfigData(This,ulSatID,lpMI406ConfigData)	\
    ( (This)->lpVtbl -> GetMI406ConfigData(This,ulSatID,lpMI406ConfigData) ) 

#define IEMSSatelliteInfo6_GetCalib406ConfigData(This,ulSatID,lpCalib406ConfigData)	\
    ( (This)->lpVtbl -> GetCalib406ConfigData(This,ulSatID,lpCalib406ConfigData) ) 

#define IEMSSatelliteInfo6_GetOrbitDetConfigData(This,ulSatID,lpOrbitDetConfigData)	\
    ( (This)->lpVtbl -> GetOrbitDetConfigData(This,ulSatID,lpOrbitDetConfigData) ) 

#define IEMSSatelliteInfo6_GetLocateCBCConfigData(This,ulSatID,lpLocateCbcConfigData)	\
    ( (This)->lpVtbl -> GetLocateCBCConfigData(This,ulSatID,lpLocateCbcConfigData) ) 

#define IEMSSatelliteInfo6_GetLocate406ConfigData(This,ulSatID,lpLocate406ConfigData)	\
    ( (This)->lpVtbl -> GetLocate406ConfigData(This,ulSatID,lpLocate406ConfigData) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEMSSatelliteInfo6_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSATINF_0000_0006 */
/* [local] */ 

typedef /* [unique] */ IEMSSatelliteInfo6 *LPEMSSATELLITEINFO6;

//Bit assigns for dwFlags field 
#define EMS_TESTCFG_SarpSarrTestLocations ( 0x1 )
#define EMS_TESTCFG_SuppressInvertedFrameSynch ( 0x2 )
#define EMS_TESTCFG_GeoRestrictIntegrationCount ( 0x4 )
#define EMS_TESTCFG_PostManoeuvreUseEffectiveTime ( 0x8 )
#define EMS_TESTCFG_IgnoreConfirmationRules ( 0x10 )
#define EMS_TESTCFG_SuppressCombinationMessage ( 0x20 )
 


extern RPC_IF_HANDLE __MIDL_itf_EMSATINF_0000_0006_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSATINF_0000_0006_v0_0_s_ifspec;

#ifndef __IEMSSatelliteInfo7_INTERFACE_DEFINED__
#define __IEMSSatelliteInfo7_INTERFACE_DEFINED__

/* interface IEMSSatelliteInfo7 */
/* [unique][helpstring][uuid][object] */ 

typedef struct _tagEMSTESTCONFIGDATA
    {
    DWORD dwFlags;
    double dMaxOrbitVectorAge;
    double dReserved2;
    double dReserved3;
    double dReserved4;
    INT nReserved5;
    INT nReserved6;
    INT nReserved7;
    INT nReserved8;
    } 	EMSTESTCONFIGDATA;

typedef struct _tagEMSTESTCONFIGDATA *LPEMSTESTCONFIGDATA;


EXTERN_C const IID IID_IEMSSatelliteInfo7;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D0591B7D-1AD9-4f23-BFF7-ACF4BC3C2B5C")
    IEMSSatelliteInfo7 : public IEMSSatelliteInfo6
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetTestConfigData( 
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSTESTCONFIGDATA lpTestConfigData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSatelliteInfo7Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEMSSatelliteInfo7 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEMSSatelliteInfo7 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigFlags )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigFlags )( 
            IEMSSatelliteInfo7 * This,
            /* [out] */ DWORD *lpdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *ReloadConfigData )( 
            IEMSSatelliteInfo7 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigValueA )( 
            IEMSSatelliteInfo7 * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [string][in] */ LPCSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigValueA )( 
            IEMSSatelliteInfo7 * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [length_is][size_is][out] */ unsigned char *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigValueW )( 
            IEMSSatelliteInfo7 * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [string][in] */ LPCWSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigValueW )( 
            IEMSSatelliteInfo7 * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [length_is][size_is][out] */ WCHAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE *GetName )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [length_is][size_is][out] */ BYTE *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG *pcbRead);
        
        HRESULT ( STDMETHODCALLTYPE *GetNoradID )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulNoradID);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatelliteID )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulNoradID,
            /* [out] */ ULONG *lpulSatelliteID);
        
        HRESULT ( STDMETHODCALLTYPE *GetFreqBandwidth )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LONG *lplBandwidth);
        
        HRESULT ( STDMETHODCALLTYPE *GetCaps )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulCapabilities);
        
        HRESULT ( STDMETHODCALLTYPE *Get406SignalData )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMS406SIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetCBCSignalData )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSCBCSIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetPDSSignalData )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSPDSSIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetRolloverPeriod )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64Period);
        
        HRESULT ( STDMETHODCALLTYPE *SetRolloverPeriod )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64Period);
        
        HRESULT ( STDMETHODCALLTYPE *GetRolloverTime )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeRollover);
        
        HRESULT ( STDMETHODCALLTYPE *SetRolloverTime )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIME timeRollover);
        
        HRESULT ( STDMETHODCALLTYPE *GetRefFreq )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreq);
        
        HRESULT ( STDMETHODCALLTYPE *SetRefFreq )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreq);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrFreqOffset )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrFreqOffset )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrTimeOffset )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrTimeOffset )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpFreqOffset )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpFreqOffset )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpTimeOffset )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpTimeOffset )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetPhaseDemodSetting )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulPhaseDemod);
        
        HRESULT ( STDMETHODCALLTYPE *GetMCCSuppressInfo )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGMCCSUPPRESS *lpMCCSUPPRESSInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTCALInfo )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGTCAL *lpTCALInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetOrbitInfo )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGORBIT *lpOrbitInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetAudioInfo )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGAUDIO *lpAudioInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetProcessInfo )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGPROCESS *lpProcessInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetCollectInfo )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGBOOLDATAPROP *lpCollectInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetPassSchedulePriority )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulPriority);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpCalibration )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIME timeRollover,
            /* [in] */ double dRefFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpCalibration )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeStamp,
            /* [out] */ EMSTIME *lpTimeRollover,
            /* [out] */ double *lpdRefFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetDownlinkFreq )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdDownlinkFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetMCCSuppressInfoEx )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGMCCSUPPRESSEX *lpMCCSUPPRESSInfo);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrCalibration )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrCalibration )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeStamp,
            /* [out] */ INT64 *lpi64TimeOffset,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetForwardingInfo )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGBOOLDATAPROP *lpForwardingInfo);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatBehaviourMaxCount )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatBehaviourCount )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatBehaviour )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [in] */ EMSSATBEHAVIOUR *lpBehaviour);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatBehaviourMaxCount )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatBehaviourCount )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatBehaviour )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [out] */ EMSSATBEHAVIOUR *lpBehaviour);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatOrbitInfoMaxCount )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatOrbitInfoCount )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatOrbitInfo )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [in] */ EMSSATORBITINFO *lpOrbit);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatOrbitInfoMaxCount )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatOrbitInfoCount )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatOrbitInfo )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [out] */ EMSSATORBITINFO *lpOrbit);
        
        HRESULT ( STDMETHODCALLTYPE *GetCalibCbcConfigData )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LPEMSCALIBCBCCONFIGDATA lpCalibCbcConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetTcalConfigData )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LPEMSTCALCONFIGDATA lpTcalConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetMI406ConfigData )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSMI406CONFIGDATA lpMI406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetCalib406ConfigData )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSCALIB406CONFIGDATA lpCalib406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetOrbitDetConfigData )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSORBITDETCONFIGDATA lpOrbitDetConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetLocateCBCConfigData )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSLOCATECBCCONFIGDATA lpLocateCbcConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetLocate406ConfigData )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSLOCATE406CONFIGDATA lpLocate406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetTestConfigData )( 
            IEMSSatelliteInfo7 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSTESTCONFIGDATA lpTestConfigData);
        
        END_INTERFACE
    } IEMSSatelliteInfo7Vtbl;

    interface IEMSSatelliteInfo7
    {
        CONST_VTBL struct IEMSSatelliteInfo7Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSatelliteInfo7_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEMSSatelliteInfo7_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEMSSatelliteInfo7_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEMSSatelliteInfo7_SetConfigFlags(This,dwFlags)	\
    ( (This)->lpVtbl -> SetConfigFlags(This,dwFlags) ) 

#define IEMSSatelliteInfo7_GetConfigFlags(This,lpdwFlags)	\
    ( (This)->lpVtbl -> GetConfigFlags(This,lpdwFlags) ) 

#define IEMSSatelliteInfo7_ReloadConfigData(This)	\
    ( (This)->lpVtbl -> ReloadConfigData(This) ) 

#define IEMSSatelliteInfo7_SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)	\
    ( (This)->lpVtbl -> SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue) ) 

#define IEMSSatelliteInfo7_GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    ( (This)->lpVtbl -> GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead) ) 

#define IEMSSatelliteInfo7_SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)	\
    ( (This)->lpVtbl -> SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue) ) 

#define IEMSSatelliteInfo7_GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    ( (This)->lpVtbl -> GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead) ) 


#define IEMSSatelliteInfo7_GetName(This,ulSatelliteID,pv,cb,pcbRead)	\
    ( (This)->lpVtbl -> GetName(This,ulSatelliteID,pv,cb,pcbRead) ) 

#define IEMSSatelliteInfo7_GetNoradID(This,ulSatelliteID,lpulNoradID)	\
    ( (This)->lpVtbl -> GetNoradID(This,ulSatelliteID,lpulNoradID) ) 

#define IEMSSatelliteInfo7_GetSatelliteID(This,ulNoradID,lpulSatelliteID)	\
    ( (This)->lpVtbl -> GetSatelliteID(This,ulNoradID,lpulSatelliteID) ) 

#define IEMSSatelliteInfo7_GetFreqBandwidth(This,ulSatelliteID,lplBandwidth)	\
    ( (This)->lpVtbl -> GetFreqBandwidth(This,ulSatelliteID,lplBandwidth) ) 

#define IEMSSatelliteInfo7_GetCaps(This,ulSatelliteID,lpulCapabilities)	\
    ( (This)->lpVtbl -> GetCaps(This,ulSatelliteID,lpulCapabilities) ) 

#define IEMSSatelliteInfo7_Get406SignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> Get406SignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo7_GetCBCSignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> GetCBCSignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo7_GetPDSSignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> GetPDSSignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo7_GetRolloverPeriod(This,ulSatelliteID,lpi64Period)	\
    ( (This)->lpVtbl -> GetRolloverPeriod(This,ulSatelliteID,lpi64Period) ) 

#define IEMSSatelliteInfo7_SetRolloverPeriod(This,ulSatelliteID,i64Period)	\
    ( (This)->lpVtbl -> SetRolloverPeriod(This,ulSatelliteID,i64Period) ) 

#define IEMSSatelliteInfo7_GetRolloverTime(This,ulSatelliteID,lpTimeRollover)	\
    ( (This)->lpVtbl -> GetRolloverTime(This,ulSatelliteID,lpTimeRollover) ) 

#define IEMSSatelliteInfo7_SetRolloverTime(This,ulSatelliteID,timeRollover)	\
    ( (This)->lpVtbl -> SetRolloverTime(This,ulSatelliteID,timeRollover) ) 

#define IEMSSatelliteInfo7_GetRefFreq(This,ulSatelliteID,lpdFreq)	\
    ( (This)->lpVtbl -> GetRefFreq(This,ulSatelliteID,lpdFreq) ) 

#define IEMSSatelliteInfo7_SetRefFreq(This,ulSatelliteID,dFreq)	\
    ( (This)->lpVtbl -> SetRefFreq(This,ulSatelliteID,dFreq) ) 

#define IEMSSatelliteInfo7_SetSarrFreqOffset(This,ulSatelliteID,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarrFreqOffset(This,ulSatelliteID,dFreqOffset) ) 

#define IEMSSatelliteInfo7_GetSarrFreqOffset(This,ulSatelliteID,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarrFreqOffset(This,ulSatelliteID,lpdFreqOffset) ) 

#define IEMSSatelliteInfo7_SetSarrTimeOffset(This,ulSatelliteID,i64TimeOffset)	\
    ( (This)->lpVtbl -> SetSarrTimeOffset(This,ulSatelliteID,i64TimeOffset) ) 

#define IEMSSatelliteInfo7_GetSarrTimeOffset(This,ulSatelliteID,lpi64TimeOffset)	\
    ( (This)->lpVtbl -> GetSarrTimeOffset(This,ulSatelliteID,lpi64TimeOffset) ) 

#define IEMSSatelliteInfo7_SetSarpFreqOffset(This,ulSatelliteID,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarpFreqOffset(This,ulSatelliteID,dFreqOffset) ) 

#define IEMSSatelliteInfo7_GetSarpFreqOffset(This,ulSatelliteID,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarpFreqOffset(This,ulSatelliteID,lpdFreqOffset) ) 

#define IEMSSatelliteInfo7_SetSarpTimeOffset(This,ulSatelliteID,i64TimeOffset)	\
    ( (This)->lpVtbl -> SetSarpTimeOffset(This,ulSatelliteID,i64TimeOffset) ) 

#define IEMSSatelliteInfo7_GetSarpTimeOffset(This,ulSatelliteID,lpi64TimeOffset)	\
    ( (This)->lpVtbl -> GetSarpTimeOffset(This,ulSatelliteID,lpi64TimeOffset) ) 


#define IEMSSatelliteInfo7_GetPhaseDemodSetting(This,ulSatelliteID,lpulPhaseDemod)	\
    ( (This)->lpVtbl -> GetPhaseDemodSetting(This,ulSatelliteID,lpulPhaseDemod) ) 


#define IEMSSatelliteInfo7_GetMCCSuppressInfo(This,ulSatelliteID,lpMCCSUPPRESSInfo)	\
    ( (This)->lpVtbl -> GetMCCSuppressInfo(This,ulSatelliteID,lpMCCSUPPRESSInfo) ) 

#define IEMSSatelliteInfo7_GetTCALInfo(This,ulSatelliteID,lpTCALInfo)	\
    ( (This)->lpVtbl -> GetTCALInfo(This,ulSatelliteID,lpTCALInfo) ) 

#define IEMSSatelliteInfo7_GetOrbitInfo(This,ulSatelliteID,lpOrbitInfo)	\
    ( (This)->lpVtbl -> GetOrbitInfo(This,ulSatelliteID,lpOrbitInfo) ) 

#define IEMSSatelliteInfo7_GetAudioInfo(This,ulSatelliteID,lpAudioInfo)	\
    ( (This)->lpVtbl -> GetAudioInfo(This,ulSatelliteID,lpAudioInfo) ) 

#define IEMSSatelliteInfo7_GetProcessInfo(This,ulSatelliteID,lpProcessInfo)	\
    ( (This)->lpVtbl -> GetProcessInfo(This,ulSatelliteID,lpProcessInfo) ) 

#define IEMSSatelliteInfo7_GetCollectInfo(This,ulSatelliteID,lpCollectInfo)	\
    ( (This)->lpVtbl -> GetCollectInfo(This,ulSatelliteID,lpCollectInfo) ) 

#define IEMSSatelliteInfo7_GetPassSchedulePriority(This,ulSatelliteID,lpulPriority)	\
    ( (This)->lpVtbl -> GetPassSchedulePriority(This,ulSatelliteID,lpulPriority) ) 

#define IEMSSatelliteInfo7_SetSarpCalibration(This,ulSatelliteID,timeRollover,dRefFreq)	\
    ( (This)->lpVtbl -> SetSarpCalibration(This,ulSatelliteID,timeRollover,dRefFreq) ) 

#define IEMSSatelliteInfo7_GetSarpCalibration(This,ulSatelliteID,lpTimeStamp,lpTimeRollover,lpdRefFreq)	\
    ( (This)->lpVtbl -> GetSarpCalibration(This,ulSatelliteID,lpTimeStamp,lpTimeRollover,lpdRefFreq) ) 

#define IEMSSatelliteInfo7_GetDownlinkFreq(This,ulSatelliteID,lpdDownlinkFreq)	\
    ( (This)->lpVtbl -> GetDownlinkFreq(This,ulSatelliteID,lpdDownlinkFreq) ) 


#define IEMSSatelliteInfo7_GetMCCSuppressInfoEx(This,ulSatelliteID,lpMCCSUPPRESSInfo)	\
    ( (This)->lpVtbl -> GetMCCSuppressInfoEx(This,ulSatelliteID,lpMCCSUPPRESSInfo) ) 

#define IEMSSatelliteInfo7_SetSarrCalibration(This,ulSatelliteID,i64TimeOffset,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarrCalibration(This,ulSatelliteID,i64TimeOffset,dFreqOffset) ) 

#define IEMSSatelliteInfo7_GetSarrCalibration(This,ulSatelliteID,lpTimeStamp,lpi64TimeOffset,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarrCalibration(This,ulSatelliteID,lpTimeStamp,lpi64TimeOffset,lpdFreqOffset) ) 

#define IEMSSatelliteInfo7_GetForwardingInfo(This,ulSatelliteID,lpForwardingInfo)	\
    ( (This)->lpVtbl -> GetForwardingInfo(This,ulSatelliteID,lpForwardingInfo) ) 


#define IEMSSatelliteInfo7_SetSatBehaviourMaxCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatBehaviourMaxCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo7_SetSatBehaviourCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatBehaviourCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo7_SetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour)	\
    ( (This)->lpVtbl -> SetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour) ) 

#define IEMSSatelliteInfo7_GetSatBehaviourMaxCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatBehaviourMaxCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo7_GetSatBehaviourCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatBehaviourCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo7_GetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour)	\
    ( (This)->lpVtbl -> GetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour) ) 

#define IEMSSatelliteInfo7_SetSatOrbitInfoMaxCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatOrbitInfoMaxCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo7_SetSatOrbitInfoCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatOrbitInfoCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo7_SetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit)	\
    ( (This)->lpVtbl -> SetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit) ) 

#define IEMSSatelliteInfo7_GetSatOrbitInfoMaxCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatOrbitInfoMaxCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo7_GetSatOrbitInfoCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatOrbitInfoCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo7_GetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit)	\
    ( (This)->lpVtbl -> GetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit) ) 


#define IEMSSatelliteInfo7_GetCalibCbcConfigData(This,ulSatelliteID,lpCalibCbcConfigData)	\
    ( (This)->lpVtbl -> GetCalibCbcConfigData(This,ulSatelliteID,lpCalibCbcConfigData) ) 

#define IEMSSatelliteInfo7_GetTcalConfigData(This,ulSatelliteID,lpTcalConfigData)	\
    ( (This)->lpVtbl -> GetTcalConfigData(This,ulSatelliteID,lpTcalConfigData) ) 

#define IEMSSatelliteInfo7_GetMI406ConfigData(This,ulSatID,lpMI406ConfigData)	\
    ( (This)->lpVtbl -> GetMI406ConfigData(This,ulSatID,lpMI406ConfigData) ) 

#define IEMSSatelliteInfo7_GetCalib406ConfigData(This,ulSatID,lpCalib406ConfigData)	\
    ( (This)->lpVtbl -> GetCalib406ConfigData(This,ulSatID,lpCalib406ConfigData) ) 

#define IEMSSatelliteInfo7_GetOrbitDetConfigData(This,ulSatID,lpOrbitDetConfigData)	\
    ( (This)->lpVtbl -> GetOrbitDetConfigData(This,ulSatID,lpOrbitDetConfigData) ) 

#define IEMSSatelliteInfo7_GetLocateCBCConfigData(This,ulSatID,lpLocateCbcConfigData)	\
    ( (This)->lpVtbl -> GetLocateCBCConfigData(This,ulSatID,lpLocateCbcConfigData) ) 

#define IEMSSatelliteInfo7_GetLocate406ConfigData(This,ulSatID,lpLocate406ConfigData)	\
    ( (This)->lpVtbl -> GetLocate406ConfigData(This,ulSatID,lpLocate406ConfigData) ) 


#define IEMSSatelliteInfo7_GetTestConfigData(This,ulSatID,lpTestConfigData)	\
    ( (This)->lpVtbl -> GetTestConfigData(This,ulSatID,lpTestConfigData) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEMSSatelliteInfo7_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSATINF_0000_0007 */
/* [local] */ 

typedef /* [unique] */ IEMSSatelliteInfo7 *LPEMSSATELLITEINFO7;



extern RPC_IF_HANDLE __MIDL_itf_EMSATINF_0000_0007_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSATINF_0000_0007_v0_0_s_ifspec;

#ifndef __IEMSSatelliteInfo8_INTERFACE_DEFINED__
#define __IEMSSatelliteInfo8_INTERFACE_DEFINED__

/* interface IEMSSatelliteInfo8 */
/* [unique][helpstring][uuid][object] */ 

typedef struct _tagEMSMI406CONFIGDATA2
    {
    BOOL bRestart;
    double dWindowFreq;
    double dWindowTime;
    DWORD dwWindowBits;
    INT nOutOfSpecWindowBits;
    BOOL bMsgForceUpdate;
    double dCNR1Threshold;
    double dCNR2Threshold;
    double dSarrFreqOffsetThreshold;
    double dSummaryInterval;
    double dMinUpdateInterval;
    double dMaxUpdateInterval;
    double dMinValidInterval;
    WORD wFSErrMaxIntegration;
    WORD wPDF1ErrMaxIntegration;
    WORD wPDF2ErrMaxIntegration;
    WORD wPDF1ErrMaxValid;
    WORD wPDF2ErrMaxValid;
    WORD wFSErrMaxValid;
    WORD wPDF1ErrMaxConfirm;
    WORD wPDF2ErrMaxConfirm;
    WORD wFSErrMaxConfirm;
    double dIntegrationAgeout;
    double dActiveBeaconAgeout;
    } 	EMSMI406CONFIGDATA2;

typedef struct _tagEMSMI406CONFIGDATA2 *LPEMSMI406CONFIGDATA2;


EXTERN_C const IID IID_IEMSSatelliteInfo8;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A2ECC7CD-1D08-4fd8-908F-376B4536B6E1")
    IEMSSatelliteInfo8 : public IEMSSatelliteInfo7
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetMI406ConfigData2( 
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSMI406CONFIGDATA2 lpMI406ConfigData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSatelliteInfo8Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEMSSatelliteInfo8 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEMSSatelliteInfo8 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigFlags )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigFlags )( 
            IEMSSatelliteInfo8 * This,
            /* [out] */ DWORD *lpdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *ReloadConfigData )( 
            IEMSSatelliteInfo8 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigValueA )( 
            IEMSSatelliteInfo8 * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [string][in] */ LPCSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigValueA )( 
            IEMSSatelliteInfo8 * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [length_is][size_is][out] */ unsigned char *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigValueW )( 
            IEMSSatelliteInfo8 * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [string][in] */ LPCWSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigValueW )( 
            IEMSSatelliteInfo8 * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [length_is][size_is][out] */ WCHAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE *GetName )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [length_is][size_is][out] */ BYTE *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG *pcbRead);
        
        HRESULT ( STDMETHODCALLTYPE *GetNoradID )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulNoradID);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatelliteID )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulNoradID,
            /* [out] */ ULONG *lpulSatelliteID);
        
        HRESULT ( STDMETHODCALLTYPE *GetFreqBandwidth )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LONG *lplBandwidth);
        
        HRESULT ( STDMETHODCALLTYPE *GetCaps )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulCapabilities);
        
        HRESULT ( STDMETHODCALLTYPE *Get406SignalData )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMS406SIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetCBCSignalData )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSCBCSIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetPDSSignalData )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSPDSSIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetRolloverPeriod )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64Period);
        
        HRESULT ( STDMETHODCALLTYPE *SetRolloverPeriod )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64Period);
        
        HRESULT ( STDMETHODCALLTYPE *GetRolloverTime )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeRollover);
        
        HRESULT ( STDMETHODCALLTYPE *SetRolloverTime )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIME timeRollover);
        
        HRESULT ( STDMETHODCALLTYPE *GetRefFreq )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreq);
        
        HRESULT ( STDMETHODCALLTYPE *SetRefFreq )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreq);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrFreqOffset )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrFreqOffset )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrTimeOffset )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrTimeOffset )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpFreqOffset )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpFreqOffset )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpTimeOffset )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpTimeOffset )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetPhaseDemodSetting )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulPhaseDemod);
        
        HRESULT ( STDMETHODCALLTYPE *GetMCCSuppressInfo )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGMCCSUPPRESS *lpMCCSUPPRESSInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTCALInfo )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGTCAL *lpTCALInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetOrbitInfo )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGORBIT *lpOrbitInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetAudioInfo )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGAUDIO *lpAudioInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetProcessInfo )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGPROCESS *lpProcessInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetCollectInfo )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGBOOLDATAPROP *lpCollectInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetPassSchedulePriority )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulPriority);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpCalibration )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIME timeRollover,
            /* [in] */ double dRefFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpCalibration )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeStamp,
            /* [out] */ EMSTIME *lpTimeRollover,
            /* [out] */ double *lpdRefFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetDownlinkFreq )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdDownlinkFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetMCCSuppressInfoEx )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGMCCSUPPRESSEX *lpMCCSUPPRESSInfo);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrCalibration )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrCalibration )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeStamp,
            /* [out] */ INT64 *lpi64TimeOffset,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetForwardingInfo )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGBOOLDATAPROP *lpForwardingInfo);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatBehaviourMaxCount )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatBehaviourCount )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatBehaviour )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [in] */ EMSSATBEHAVIOUR *lpBehaviour);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatBehaviourMaxCount )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatBehaviourCount )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatBehaviour )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [out] */ EMSSATBEHAVIOUR *lpBehaviour);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatOrbitInfoMaxCount )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatOrbitInfoCount )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatOrbitInfo )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [in] */ EMSSATORBITINFO *lpOrbit);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatOrbitInfoMaxCount )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatOrbitInfoCount )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatOrbitInfo )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [out] */ EMSSATORBITINFO *lpOrbit);
        
        HRESULT ( STDMETHODCALLTYPE *GetCalibCbcConfigData )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LPEMSCALIBCBCCONFIGDATA lpCalibCbcConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetTcalConfigData )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LPEMSTCALCONFIGDATA lpTcalConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetMI406ConfigData )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSMI406CONFIGDATA lpMI406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetCalib406ConfigData )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSCALIB406CONFIGDATA lpCalib406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetOrbitDetConfigData )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSORBITDETCONFIGDATA lpOrbitDetConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetLocateCBCConfigData )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSLOCATECBCCONFIGDATA lpLocateCbcConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetLocate406ConfigData )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSLOCATE406CONFIGDATA lpLocate406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetTestConfigData )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSTESTCONFIGDATA lpTestConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetMI406ConfigData2 )( 
            IEMSSatelliteInfo8 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSMI406CONFIGDATA2 lpMI406ConfigData);
        
        END_INTERFACE
    } IEMSSatelliteInfo8Vtbl;

    interface IEMSSatelliteInfo8
    {
        CONST_VTBL struct IEMSSatelliteInfo8Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSatelliteInfo8_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEMSSatelliteInfo8_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEMSSatelliteInfo8_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEMSSatelliteInfo8_SetConfigFlags(This,dwFlags)	\
    ( (This)->lpVtbl -> SetConfigFlags(This,dwFlags) ) 

#define IEMSSatelliteInfo8_GetConfigFlags(This,lpdwFlags)	\
    ( (This)->lpVtbl -> GetConfigFlags(This,lpdwFlags) ) 

#define IEMSSatelliteInfo8_ReloadConfigData(This)	\
    ( (This)->lpVtbl -> ReloadConfigData(This) ) 

#define IEMSSatelliteInfo8_SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)	\
    ( (This)->lpVtbl -> SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue) ) 

#define IEMSSatelliteInfo8_GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    ( (This)->lpVtbl -> GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead) ) 

#define IEMSSatelliteInfo8_SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)	\
    ( (This)->lpVtbl -> SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue) ) 

#define IEMSSatelliteInfo8_GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    ( (This)->lpVtbl -> GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead) ) 


#define IEMSSatelliteInfo8_GetName(This,ulSatelliteID,pv,cb,pcbRead)	\
    ( (This)->lpVtbl -> GetName(This,ulSatelliteID,pv,cb,pcbRead) ) 

#define IEMSSatelliteInfo8_GetNoradID(This,ulSatelliteID,lpulNoradID)	\
    ( (This)->lpVtbl -> GetNoradID(This,ulSatelliteID,lpulNoradID) ) 

#define IEMSSatelliteInfo8_GetSatelliteID(This,ulNoradID,lpulSatelliteID)	\
    ( (This)->lpVtbl -> GetSatelliteID(This,ulNoradID,lpulSatelliteID) ) 

#define IEMSSatelliteInfo8_GetFreqBandwidth(This,ulSatelliteID,lplBandwidth)	\
    ( (This)->lpVtbl -> GetFreqBandwidth(This,ulSatelliteID,lplBandwidth) ) 

#define IEMSSatelliteInfo8_GetCaps(This,ulSatelliteID,lpulCapabilities)	\
    ( (This)->lpVtbl -> GetCaps(This,ulSatelliteID,lpulCapabilities) ) 

#define IEMSSatelliteInfo8_Get406SignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> Get406SignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo8_GetCBCSignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> GetCBCSignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo8_GetPDSSignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> GetPDSSignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo8_GetRolloverPeriod(This,ulSatelliteID,lpi64Period)	\
    ( (This)->lpVtbl -> GetRolloverPeriod(This,ulSatelliteID,lpi64Period) ) 

#define IEMSSatelliteInfo8_SetRolloverPeriod(This,ulSatelliteID,i64Period)	\
    ( (This)->lpVtbl -> SetRolloverPeriod(This,ulSatelliteID,i64Period) ) 

#define IEMSSatelliteInfo8_GetRolloverTime(This,ulSatelliteID,lpTimeRollover)	\
    ( (This)->lpVtbl -> GetRolloverTime(This,ulSatelliteID,lpTimeRollover) ) 

#define IEMSSatelliteInfo8_SetRolloverTime(This,ulSatelliteID,timeRollover)	\
    ( (This)->lpVtbl -> SetRolloverTime(This,ulSatelliteID,timeRollover) ) 

#define IEMSSatelliteInfo8_GetRefFreq(This,ulSatelliteID,lpdFreq)	\
    ( (This)->lpVtbl -> GetRefFreq(This,ulSatelliteID,lpdFreq) ) 

#define IEMSSatelliteInfo8_SetRefFreq(This,ulSatelliteID,dFreq)	\
    ( (This)->lpVtbl -> SetRefFreq(This,ulSatelliteID,dFreq) ) 

#define IEMSSatelliteInfo8_SetSarrFreqOffset(This,ulSatelliteID,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarrFreqOffset(This,ulSatelliteID,dFreqOffset) ) 

#define IEMSSatelliteInfo8_GetSarrFreqOffset(This,ulSatelliteID,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarrFreqOffset(This,ulSatelliteID,lpdFreqOffset) ) 

#define IEMSSatelliteInfo8_SetSarrTimeOffset(This,ulSatelliteID,i64TimeOffset)	\
    ( (This)->lpVtbl -> SetSarrTimeOffset(This,ulSatelliteID,i64TimeOffset) ) 

#define IEMSSatelliteInfo8_GetSarrTimeOffset(This,ulSatelliteID,lpi64TimeOffset)	\
    ( (This)->lpVtbl -> GetSarrTimeOffset(This,ulSatelliteID,lpi64TimeOffset) ) 

#define IEMSSatelliteInfo8_SetSarpFreqOffset(This,ulSatelliteID,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarpFreqOffset(This,ulSatelliteID,dFreqOffset) ) 

#define IEMSSatelliteInfo8_GetSarpFreqOffset(This,ulSatelliteID,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarpFreqOffset(This,ulSatelliteID,lpdFreqOffset) ) 

#define IEMSSatelliteInfo8_SetSarpTimeOffset(This,ulSatelliteID,i64TimeOffset)	\
    ( (This)->lpVtbl -> SetSarpTimeOffset(This,ulSatelliteID,i64TimeOffset) ) 

#define IEMSSatelliteInfo8_GetSarpTimeOffset(This,ulSatelliteID,lpi64TimeOffset)	\
    ( (This)->lpVtbl -> GetSarpTimeOffset(This,ulSatelliteID,lpi64TimeOffset) ) 


#define IEMSSatelliteInfo8_GetPhaseDemodSetting(This,ulSatelliteID,lpulPhaseDemod)	\
    ( (This)->lpVtbl -> GetPhaseDemodSetting(This,ulSatelliteID,lpulPhaseDemod) ) 


#define IEMSSatelliteInfo8_GetMCCSuppressInfo(This,ulSatelliteID,lpMCCSUPPRESSInfo)	\
    ( (This)->lpVtbl -> GetMCCSuppressInfo(This,ulSatelliteID,lpMCCSUPPRESSInfo) ) 

#define IEMSSatelliteInfo8_GetTCALInfo(This,ulSatelliteID,lpTCALInfo)	\
    ( (This)->lpVtbl -> GetTCALInfo(This,ulSatelliteID,lpTCALInfo) ) 

#define IEMSSatelliteInfo8_GetOrbitInfo(This,ulSatelliteID,lpOrbitInfo)	\
    ( (This)->lpVtbl -> GetOrbitInfo(This,ulSatelliteID,lpOrbitInfo) ) 

#define IEMSSatelliteInfo8_GetAudioInfo(This,ulSatelliteID,lpAudioInfo)	\
    ( (This)->lpVtbl -> GetAudioInfo(This,ulSatelliteID,lpAudioInfo) ) 

#define IEMSSatelliteInfo8_GetProcessInfo(This,ulSatelliteID,lpProcessInfo)	\
    ( (This)->lpVtbl -> GetProcessInfo(This,ulSatelliteID,lpProcessInfo) ) 

#define IEMSSatelliteInfo8_GetCollectInfo(This,ulSatelliteID,lpCollectInfo)	\
    ( (This)->lpVtbl -> GetCollectInfo(This,ulSatelliteID,lpCollectInfo) ) 

#define IEMSSatelliteInfo8_GetPassSchedulePriority(This,ulSatelliteID,lpulPriority)	\
    ( (This)->lpVtbl -> GetPassSchedulePriority(This,ulSatelliteID,lpulPriority) ) 

#define IEMSSatelliteInfo8_SetSarpCalibration(This,ulSatelliteID,timeRollover,dRefFreq)	\
    ( (This)->lpVtbl -> SetSarpCalibration(This,ulSatelliteID,timeRollover,dRefFreq) ) 

#define IEMSSatelliteInfo8_GetSarpCalibration(This,ulSatelliteID,lpTimeStamp,lpTimeRollover,lpdRefFreq)	\
    ( (This)->lpVtbl -> GetSarpCalibration(This,ulSatelliteID,lpTimeStamp,lpTimeRollover,lpdRefFreq) ) 

#define IEMSSatelliteInfo8_GetDownlinkFreq(This,ulSatelliteID,lpdDownlinkFreq)	\
    ( (This)->lpVtbl -> GetDownlinkFreq(This,ulSatelliteID,lpdDownlinkFreq) ) 


#define IEMSSatelliteInfo8_GetMCCSuppressInfoEx(This,ulSatelliteID,lpMCCSUPPRESSInfo)	\
    ( (This)->lpVtbl -> GetMCCSuppressInfoEx(This,ulSatelliteID,lpMCCSUPPRESSInfo) ) 

#define IEMSSatelliteInfo8_SetSarrCalibration(This,ulSatelliteID,i64TimeOffset,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarrCalibration(This,ulSatelliteID,i64TimeOffset,dFreqOffset) ) 

#define IEMSSatelliteInfo8_GetSarrCalibration(This,ulSatelliteID,lpTimeStamp,lpi64TimeOffset,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarrCalibration(This,ulSatelliteID,lpTimeStamp,lpi64TimeOffset,lpdFreqOffset) ) 

#define IEMSSatelliteInfo8_GetForwardingInfo(This,ulSatelliteID,lpForwardingInfo)	\
    ( (This)->lpVtbl -> GetForwardingInfo(This,ulSatelliteID,lpForwardingInfo) ) 


#define IEMSSatelliteInfo8_SetSatBehaviourMaxCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatBehaviourMaxCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo8_SetSatBehaviourCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatBehaviourCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo8_SetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour)	\
    ( (This)->lpVtbl -> SetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour) ) 

#define IEMSSatelliteInfo8_GetSatBehaviourMaxCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatBehaviourMaxCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo8_GetSatBehaviourCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatBehaviourCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo8_GetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour)	\
    ( (This)->lpVtbl -> GetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour) ) 

#define IEMSSatelliteInfo8_SetSatOrbitInfoMaxCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatOrbitInfoMaxCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo8_SetSatOrbitInfoCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatOrbitInfoCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo8_SetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit)	\
    ( (This)->lpVtbl -> SetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit) ) 

#define IEMSSatelliteInfo8_GetSatOrbitInfoMaxCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatOrbitInfoMaxCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo8_GetSatOrbitInfoCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatOrbitInfoCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo8_GetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit)	\
    ( (This)->lpVtbl -> GetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit) ) 


#define IEMSSatelliteInfo8_GetCalibCbcConfigData(This,ulSatelliteID,lpCalibCbcConfigData)	\
    ( (This)->lpVtbl -> GetCalibCbcConfigData(This,ulSatelliteID,lpCalibCbcConfigData) ) 

#define IEMSSatelliteInfo8_GetTcalConfigData(This,ulSatelliteID,lpTcalConfigData)	\
    ( (This)->lpVtbl -> GetTcalConfigData(This,ulSatelliteID,lpTcalConfigData) ) 

#define IEMSSatelliteInfo8_GetMI406ConfigData(This,ulSatID,lpMI406ConfigData)	\
    ( (This)->lpVtbl -> GetMI406ConfigData(This,ulSatID,lpMI406ConfigData) ) 

#define IEMSSatelliteInfo8_GetCalib406ConfigData(This,ulSatID,lpCalib406ConfigData)	\
    ( (This)->lpVtbl -> GetCalib406ConfigData(This,ulSatID,lpCalib406ConfigData) ) 

#define IEMSSatelliteInfo8_GetOrbitDetConfigData(This,ulSatID,lpOrbitDetConfigData)	\
    ( (This)->lpVtbl -> GetOrbitDetConfigData(This,ulSatID,lpOrbitDetConfigData) ) 

#define IEMSSatelliteInfo8_GetLocateCBCConfigData(This,ulSatID,lpLocateCbcConfigData)	\
    ( (This)->lpVtbl -> GetLocateCBCConfigData(This,ulSatID,lpLocateCbcConfigData) ) 

#define IEMSSatelliteInfo8_GetLocate406ConfigData(This,ulSatID,lpLocate406ConfigData)	\
    ( (This)->lpVtbl -> GetLocate406ConfigData(This,ulSatID,lpLocate406ConfigData) ) 


#define IEMSSatelliteInfo8_GetTestConfigData(This,ulSatID,lpTestConfigData)	\
    ( (This)->lpVtbl -> GetTestConfigData(This,ulSatID,lpTestConfigData) ) 


#define IEMSSatelliteInfo8_GetMI406ConfigData2(This,ulSatID,lpMI406ConfigData)	\
    ( (This)->lpVtbl -> GetMI406ConfigData2(This,ulSatID,lpMI406ConfigData) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEMSSatelliteInfo8_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSATINF_0000_0008 */
/* [local] */ 

typedef /* [unique] */ IEMSSatelliteInfo8 *LPEMSSATELLITEINFO8;



extern RPC_IF_HANDLE __MIDL_itf_EMSATINF_0000_0008_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSATINF_0000_0008_v0_0_s_ifspec;

#ifndef __IEMSSatelliteInfo9_INTERFACE_DEFINED__
#define __IEMSSatelliteInfo9_INTERFACE_DEFINED__

/* interface IEMSSatelliteInfo9 */
/* [unique][helpstring][uuid][object] */ 

typedef struct _tagEMSTCALCONFIGDATA2
    {
    double dUpdatePeriod;
    double dDuration;
    long lMinPts;
    double dTimeThreshold;
    double dFrequencyThreshold;
    long lFreqAverageNumber;
    long lTimeOffset;
    double dMaxAge;
    } 	EMSTCALCONFIGDATA2;

typedef struct _tagEMSTCALCONFIGDATA2 *LPEMSTCALCONFIGDATA2;

typedef struct _tagEMSEECOEFFICIENT
    {
    double dScaleFactor;
    double dAdjustment;
    } 	EMSEECOEFFICIENT;

typedef struct _tagEMSEECOEFFICIENT *LPEMSEECOEFFICIENT;

typedef struct _tagEMS406EECOEFFICIENTS
    {
    EMSEECOEFFICIENT cfSarp;
    EMSEECOEFFICIENT cfSarr;
    EMSEECOEFFICIENT cfSarrSarp;
    } 	EMS406EECOEFFICIENTS;

typedef struct _tagEMS406EECOEFFICIENTS *LPEMS406EECOEFFICIENTS;

typedef struct _tagEMSCBCEECOEFFICIENTS
    {
    EMSEECOEFFICIENT cf121;
    EMSEECOEFFICIENT cf243;
    EMSEECOEFFICIENT cf406;
    } 	EMSCBCEECOEFFICIENTS;

typedef struct _tagEMSCBCEECOEFFICIENTS *LPEMSCBCEECOEFFICIENTS;

typedef struct _tagEMSEECOEFFICIENTS
    {
    EMSCBCEECOEFFICIENTS typeCBC;
    EMS406EECOEFFICIENTS type406;
    EMS406EECOEFFICIENTS typeFDOA;
    EMS406EECOEFFICIENTS typeTDOA;
    } 	EMSEECOEFFICIENTS;

typedef struct _tagEMSEECOEFFICIENTS *LPEMSEECOEFFICIENTS;

typedef struct _tagEMSEECONFIGDATA
    {
    EMSEECOEFFICIENTS nominal;
    EMSEECOEFFICIENTS marginal;
    long lReserved1;
    double dReserved2;
    } 	EMSEECONFIGDATA;

typedef struct _tagEMSEECONFIGDATA *LPEMSEECONFIGDATA;


EXTERN_C const IID IID_IEMSSatelliteInfo9;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8E742C5A-0B5F-4b10-A037-CED8E88B5507")
    IEMSSatelliteInfo9 : public IEMSSatelliteInfo8
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetTcalConfigData2( 
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSTCALCONFIGDATA2 lpTcalConfigData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetErrorEllipseConfigData( 
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSEECONFIGDATA lpData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetErrorEllipseConfigData( 
            /* [in] */ ULONG ulSatID,
            /* [in] */ LPEMSEECONFIGDATA lpData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSatelliteInfo9Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEMSSatelliteInfo9 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEMSSatelliteInfo9 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigFlags )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigFlags )( 
            IEMSSatelliteInfo9 * This,
            /* [out] */ DWORD *lpdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *ReloadConfigData )( 
            IEMSSatelliteInfo9 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigValueA )( 
            IEMSSatelliteInfo9 * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [string][in] */ LPCSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigValueA )( 
            IEMSSatelliteInfo9 * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [length_is][size_is][out] */ unsigned char *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigValueW )( 
            IEMSSatelliteInfo9 * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [string][in] */ LPCWSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigValueW )( 
            IEMSSatelliteInfo9 * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [length_is][size_is][out] */ WCHAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE *GetName )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [length_is][size_is][out] */ BYTE *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG *pcbRead);
        
        HRESULT ( STDMETHODCALLTYPE *GetNoradID )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulNoradID);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatelliteID )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulNoradID,
            /* [out] */ ULONG *lpulSatelliteID);
        
        HRESULT ( STDMETHODCALLTYPE *GetFreqBandwidth )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LONG *lplBandwidth);
        
        HRESULT ( STDMETHODCALLTYPE *GetCaps )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulCapabilities);
        
        HRESULT ( STDMETHODCALLTYPE *Get406SignalData )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMS406SIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetCBCSignalData )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSCBCSIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetPDSSignalData )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSPDSSIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetRolloverPeriod )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64Period);
        
        HRESULT ( STDMETHODCALLTYPE *SetRolloverPeriod )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64Period);
        
        HRESULT ( STDMETHODCALLTYPE *GetRolloverTime )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeRollover);
        
        HRESULT ( STDMETHODCALLTYPE *SetRolloverTime )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIME timeRollover);
        
        HRESULT ( STDMETHODCALLTYPE *GetRefFreq )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreq);
        
        HRESULT ( STDMETHODCALLTYPE *SetRefFreq )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreq);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrFreqOffset )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrFreqOffset )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrTimeOffset )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrTimeOffset )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpFreqOffset )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpFreqOffset )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpTimeOffset )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpTimeOffset )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetPhaseDemodSetting )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulPhaseDemod);
        
        HRESULT ( STDMETHODCALLTYPE *GetMCCSuppressInfo )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGMCCSUPPRESS *lpMCCSUPPRESSInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTCALInfo )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGTCAL *lpTCALInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetOrbitInfo )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGORBIT *lpOrbitInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetAudioInfo )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGAUDIO *lpAudioInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetProcessInfo )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGPROCESS *lpProcessInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetCollectInfo )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGBOOLDATAPROP *lpCollectInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetPassSchedulePriority )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulPriority);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpCalibration )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIME timeRollover,
            /* [in] */ double dRefFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpCalibration )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeStamp,
            /* [out] */ EMSTIME *lpTimeRollover,
            /* [out] */ double *lpdRefFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetDownlinkFreq )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdDownlinkFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetMCCSuppressInfoEx )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGMCCSUPPRESSEX *lpMCCSUPPRESSInfo);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrCalibration )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrCalibration )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeStamp,
            /* [out] */ INT64 *lpi64TimeOffset,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetForwardingInfo )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGBOOLDATAPROP *lpForwardingInfo);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatBehaviourMaxCount )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatBehaviourCount )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatBehaviour )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [in] */ EMSSATBEHAVIOUR *lpBehaviour);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatBehaviourMaxCount )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatBehaviourCount )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatBehaviour )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [out] */ EMSSATBEHAVIOUR *lpBehaviour);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatOrbitInfoMaxCount )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatOrbitInfoCount )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatOrbitInfo )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [in] */ EMSSATORBITINFO *lpOrbit);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatOrbitInfoMaxCount )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatOrbitInfoCount )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatOrbitInfo )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [out] */ EMSSATORBITINFO *lpOrbit);
        
        HRESULT ( STDMETHODCALLTYPE *GetCalibCbcConfigData )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LPEMSCALIBCBCCONFIGDATA lpCalibCbcConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetTcalConfigData )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LPEMSTCALCONFIGDATA lpTcalConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetMI406ConfigData )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSMI406CONFIGDATA lpMI406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetCalib406ConfigData )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSCALIB406CONFIGDATA lpCalib406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetOrbitDetConfigData )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSORBITDETCONFIGDATA lpOrbitDetConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetLocateCBCConfigData )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSLOCATECBCCONFIGDATA lpLocateCbcConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetLocate406ConfigData )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSLOCATE406CONFIGDATA lpLocate406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetTestConfigData )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSTESTCONFIGDATA lpTestConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetMI406ConfigData2 )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSMI406CONFIGDATA2 lpMI406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetTcalConfigData2 )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSTCALCONFIGDATA2 lpTcalConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetErrorEllipseConfigData )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSEECONFIGDATA lpData);
        
        HRESULT ( STDMETHODCALLTYPE *SetErrorEllipseConfigData )( 
            IEMSSatelliteInfo9 * This,
            /* [in] */ ULONG ulSatID,
            /* [in] */ LPEMSEECONFIGDATA lpData);
        
        END_INTERFACE
    } IEMSSatelliteInfo9Vtbl;

    interface IEMSSatelliteInfo9
    {
        CONST_VTBL struct IEMSSatelliteInfo9Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSatelliteInfo9_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEMSSatelliteInfo9_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEMSSatelliteInfo9_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEMSSatelliteInfo9_SetConfigFlags(This,dwFlags)	\
    ( (This)->lpVtbl -> SetConfigFlags(This,dwFlags) ) 

#define IEMSSatelliteInfo9_GetConfigFlags(This,lpdwFlags)	\
    ( (This)->lpVtbl -> GetConfigFlags(This,lpdwFlags) ) 

#define IEMSSatelliteInfo9_ReloadConfigData(This)	\
    ( (This)->lpVtbl -> ReloadConfigData(This) ) 

#define IEMSSatelliteInfo9_SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)	\
    ( (This)->lpVtbl -> SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue) ) 

#define IEMSSatelliteInfo9_GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    ( (This)->lpVtbl -> GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead) ) 

#define IEMSSatelliteInfo9_SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)	\
    ( (This)->lpVtbl -> SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue) ) 

#define IEMSSatelliteInfo9_GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    ( (This)->lpVtbl -> GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead) ) 


#define IEMSSatelliteInfo9_GetName(This,ulSatelliteID,pv,cb,pcbRead)	\
    ( (This)->lpVtbl -> GetName(This,ulSatelliteID,pv,cb,pcbRead) ) 

#define IEMSSatelliteInfo9_GetNoradID(This,ulSatelliteID,lpulNoradID)	\
    ( (This)->lpVtbl -> GetNoradID(This,ulSatelliteID,lpulNoradID) ) 

#define IEMSSatelliteInfo9_GetSatelliteID(This,ulNoradID,lpulSatelliteID)	\
    ( (This)->lpVtbl -> GetSatelliteID(This,ulNoradID,lpulSatelliteID) ) 

#define IEMSSatelliteInfo9_GetFreqBandwidth(This,ulSatelliteID,lplBandwidth)	\
    ( (This)->lpVtbl -> GetFreqBandwidth(This,ulSatelliteID,lplBandwidth) ) 

#define IEMSSatelliteInfo9_GetCaps(This,ulSatelliteID,lpulCapabilities)	\
    ( (This)->lpVtbl -> GetCaps(This,ulSatelliteID,lpulCapabilities) ) 

#define IEMSSatelliteInfo9_Get406SignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> Get406SignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo9_GetCBCSignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> GetCBCSignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo9_GetPDSSignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> GetPDSSignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo9_GetRolloverPeriod(This,ulSatelliteID,lpi64Period)	\
    ( (This)->lpVtbl -> GetRolloverPeriod(This,ulSatelliteID,lpi64Period) ) 

#define IEMSSatelliteInfo9_SetRolloverPeriod(This,ulSatelliteID,i64Period)	\
    ( (This)->lpVtbl -> SetRolloverPeriod(This,ulSatelliteID,i64Period) ) 

#define IEMSSatelliteInfo9_GetRolloverTime(This,ulSatelliteID,lpTimeRollover)	\
    ( (This)->lpVtbl -> GetRolloverTime(This,ulSatelliteID,lpTimeRollover) ) 

#define IEMSSatelliteInfo9_SetRolloverTime(This,ulSatelliteID,timeRollover)	\
    ( (This)->lpVtbl -> SetRolloverTime(This,ulSatelliteID,timeRollover) ) 

#define IEMSSatelliteInfo9_GetRefFreq(This,ulSatelliteID,lpdFreq)	\
    ( (This)->lpVtbl -> GetRefFreq(This,ulSatelliteID,lpdFreq) ) 

#define IEMSSatelliteInfo9_SetRefFreq(This,ulSatelliteID,dFreq)	\
    ( (This)->lpVtbl -> SetRefFreq(This,ulSatelliteID,dFreq) ) 

#define IEMSSatelliteInfo9_SetSarrFreqOffset(This,ulSatelliteID,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarrFreqOffset(This,ulSatelliteID,dFreqOffset) ) 

#define IEMSSatelliteInfo9_GetSarrFreqOffset(This,ulSatelliteID,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarrFreqOffset(This,ulSatelliteID,lpdFreqOffset) ) 

#define IEMSSatelliteInfo9_SetSarrTimeOffset(This,ulSatelliteID,i64TimeOffset)	\
    ( (This)->lpVtbl -> SetSarrTimeOffset(This,ulSatelliteID,i64TimeOffset) ) 

#define IEMSSatelliteInfo9_GetSarrTimeOffset(This,ulSatelliteID,lpi64TimeOffset)	\
    ( (This)->lpVtbl -> GetSarrTimeOffset(This,ulSatelliteID,lpi64TimeOffset) ) 

#define IEMSSatelliteInfo9_SetSarpFreqOffset(This,ulSatelliteID,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarpFreqOffset(This,ulSatelliteID,dFreqOffset) ) 

#define IEMSSatelliteInfo9_GetSarpFreqOffset(This,ulSatelliteID,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarpFreqOffset(This,ulSatelliteID,lpdFreqOffset) ) 

#define IEMSSatelliteInfo9_SetSarpTimeOffset(This,ulSatelliteID,i64TimeOffset)	\
    ( (This)->lpVtbl -> SetSarpTimeOffset(This,ulSatelliteID,i64TimeOffset) ) 

#define IEMSSatelliteInfo9_GetSarpTimeOffset(This,ulSatelliteID,lpi64TimeOffset)	\
    ( (This)->lpVtbl -> GetSarpTimeOffset(This,ulSatelliteID,lpi64TimeOffset) ) 


#define IEMSSatelliteInfo9_GetPhaseDemodSetting(This,ulSatelliteID,lpulPhaseDemod)	\
    ( (This)->lpVtbl -> GetPhaseDemodSetting(This,ulSatelliteID,lpulPhaseDemod) ) 


#define IEMSSatelliteInfo9_GetMCCSuppressInfo(This,ulSatelliteID,lpMCCSUPPRESSInfo)	\
    ( (This)->lpVtbl -> GetMCCSuppressInfo(This,ulSatelliteID,lpMCCSUPPRESSInfo) ) 

#define IEMSSatelliteInfo9_GetTCALInfo(This,ulSatelliteID,lpTCALInfo)	\
    ( (This)->lpVtbl -> GetTCALInfo(This,ulSatelliteID,lpTCALInfo) ) 

#define IEMSSatelliteInfo9_GetOrbitInfo(This,ulSatelliteID,lpOrbitInfo)	\
    ( (This)->lpVtbl -> GetOrbitInfo(This,ulSatelliteID,lpOrbitInfo) ) 

#define IEMSSatelliteInfo9_GetAudioInfo(This,ulSatelliteID,lpAudioInfo)	\
    ( (This)->lpVtbl -> GetAudioInfo(This,ulSatelliteID,lpAudioInfo) ) 

#define IEMSSatelliteInfo9_GetProcessInfo(This,ulSatelliteID,lpProcessInfo)	\
    ( (This)->lpVtbl -> GetProcessInfo(This,ulSatelliteID,lpProcessInfo) ) 

#define IEMSSatelliteInfo9_GetCollectInfo(This,ulSatelliteID,lpCollectInfo)	\
    ( (This)->lpVtbl -> GetCollectInfo(This,ulSatelliteID,lpCollectInfo) ) 

#define IEMSSatelliteInfo9_GetPassSchedulePriority(This,ulSatelliteID,lpulPriority)	\
    ( (This)->lpVtbl -> GetPassSchedulePriority(This,ulSatelliteID,lpulPriority) ) 

#define IEMSSatelliteInfo9_SetSarpCalibration(This,ulSatelliteID,timeRollover,dRefFreq)	\
    ( (This)->lpVtbl -> SetSarpCalibration(This,ulSatelliteID,timeRollover,dRefFreq) ) 

#define IEMSSatelliteInfo9_GetSarpCalibration(This,ulSatelliteID,lpTimeStamp,lpTimeRollover,lpdRefFreq)	\
    ( (This)->lpVtbl -> GetSarpCalibration(This,ulSatelliteID,lpTimeStamp,lpTimeRollover,lpdRefFreq) ) 

#define IEMSSatelliteInfo9_GetDownlinkFreq(This,ulSatelliteID,lpdDownlinkFreq)	\
    ( (This)->lpVtbl -> GetDownlinkFreq(This,ulSatelliteID,lpdDownlinkFreq) ) 


#define IEMSSatelliteInfo9_GetMCCSuppressInfoEx(This,ulSatelliteID,lpMCCSUPPRESSInfo)	\
    ( (This)->lpVtbl -> GetMCCSuppressInfoEx(This,ulSatelliteID,lpMCCSUPPRESSInfo) ) 

#define IEMSSatelliteInfo9_SetSarrCalibration(This,ulSatelliteID,i64TimeOffset,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarrCalibration(This,ulSatelliteID,i64TimeOffset,dFreqOffset) ) 

#define IEMSSatelliteInfo9_GetSarrCalibration(This,ulSatelliteID,lpTimeStamp,lpi64TimeOffset,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarrCalibration(This,ulSatelliteID,lpTimeStamp,lpi64TimeOffset,lpdFreqOffset) ) 

#define IEMSSatelliteInfo9_GetForwardingInfo(This,ulSatelliteID,lpForwardingInfo)	\
    ( (This)->lpVtbl -> GetForwardingInfo(This,ulSatelliteID,lpForwardingInfo) ) 


#define IEMSSatelliteInfo9_SetSatBehaviourMaxCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatBehaviourMaxCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo9_SetSatBehaviourCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatBehaviourCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo9_SetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour)	\
    ( (This)->lpVtbl -> SetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour) ) 

#define IEMSSatelliteInfo9_GetSatBehaviourMaxCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatBehaviourMaxCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo9_GetSatBehaviourCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatBehaviourCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo9_GetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour)	\
    ( (This)->lpVtbl -> GetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour) ) 

#define IEMSSatelliteInfo9_SetSatOrbitInfoMaxCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatOrbitInfoMaxCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo9_SetSatOrbitInfoCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatOrbitInfoCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo9_SetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit)	\
    ( (This)->lpVtbl -> SetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit) ) 

#define IEMSSatelliteInfo9_GetSatOrbitInfoMaxCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatOrbitInfoMaxCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo9_GetSatOrbitInfoCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatOrbitInfoCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo9_GetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit)	\
    ( (This)->lpVtbl -> GetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit) ) 


#define IEMSSatelliteInfo9_GetCalibCbcConfigData(This,ulSatelliteID,lpCalibCbcConfigData)	\
    ( (This)->lpVtbl -> GetCalibCbcConfigData(This,ulSatelliteID,lpCalibCbcConfigData) ) 

#define IEMSSatelliteInfo9_GetTcalConfigData(This,ulSatelliteID,lpTcalConfigData)	\
    ( (This)->lpVtbl -> GetTcalConfigData(This,ulSatelliteID,lpTcalConfigData) ) 

#define IEMSSatelliteInfo9_GetMI406ConfigData(This,ulSatID,lpMI406ConfigData)	\
    ( (This)->lpVtbl -> GetMI406ConfigData(This,ulSatID,lpMI406ConfigData) ) 

#define IEMSSatelliteInfo9_GetCalib406ConfigData(This,ulSatID,lpCalib406ConfigData)	\
    ( (This)->lpVtbl -> GetCalib406ConfigData(This,ulSatID,lpCalib406ConfigData) ) 

#define IEMSSatelliteInfo9_GetOrbitDetConfigData(This,ulSatID,lpOrbitDetConfigData)	\
    ( (This)->lpVtbl -> GetOrbitDetConfigData(This,ulSatID,lpOrbitDetConfigData) ) 

#define IEMSSatelliteInfo9_GetLocateCBCConfigData(This,ulSatID,lpLocateCbcConfigData)	\
    ( (This)->lpVtbl -> GetLocateCBCConfigData(This,ulSatID,lpLocateCbcConfigData) ) 

#define IEMSSatelliteInfo9_GetLocate406ConfigData(This,ulSatID,lpLocate406ConfigData)	\
    ( (This)->lpVtbl -> GetLocate406ConfigData(This,ulSatID,lpLocate406ConfigData) ) 


#define IEMSSatelliteInfo9_GetTestConfigData(This,ulSatID,lpTestConfigData)	\
    ( (This)->lpVtbl -> GetTestConfigData(This,ulSatID,lpTestConfigData) ) 


#define IEMSSatelliteInfo9_GetMI406ConfigData2(This,ulSatID,lpMI406ConfigData)	\
    ( (This)->lpVtbl -> GetMI406ConfigData2(This,ulSatID,lpMI406ConfigData) ) 


#define IEMSSatelliteInfo9_GetTcalConfigData2(This,ulSatID,lpTcalConfigData)	\
    ( (This)->lpVtbl -> GetTcalConfigData2(This,ulSatID,lpTcalConfigData) ) 

#define IEMSSatelliteInfo9_GetErrorEllipseConfigData(This,ulSatID,lpData)	\
    ( (This)->lpVtbl -> GetErrorEllipseConfigData(This,ulSatID,lpData) ) 

#define IEMSSatelliteInfo9_SetErrorEllipseConfigData(This,ulSatID,lpData)	\
    ( (This)->lpVtbl -> SetErrorEllipseConfigData(This,ulSatID,lpData) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEMSSatelliteInfo9_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSATINF_0000_0009 */
/* [local] */ 

typedef /* [unique] */ IEMSSatelliteInfo9 *LPEMSSATELLITEINFO9;



extern RPC_IF_HANDLE __MIDL_itf_EMSATINF_0000_0009_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSATINF_0000_0009_v0_0_s_ifspec;

#ifndef __IEMSSatelliteInfo10_INTERFACE_DEFINED__
#define __IEMSSatelliteInfo10_INTERFACE_DEFINED__

/* interface IEMSSatelliteInfo10 */
/* [unique][helpstring][uuid][object] */ 

typedef struct _tagEMSCALIBCBCCONFIGDATA2
    {
    BYTE bAmplitudeMinimum;
    double dTimeResolution;
    double dFrequencyResolution;
    double dFrequencyBandwidth;
    double dCorrelationThreshold;
    long lTemplateNumber;
    double dTemplateDuration;
    double dAudioDuration;
    double dAudioBandwidth;
    double dReserved1;
    double dReserved2;
    double dReserved3;
    ULONG ulReserved4;
    ULONG ulReserved5;
    } 	EMSCALIBCBCCONFIGDATA2;

typedef struct _tagEMSCALIBCBCCONFIGDATA2 *LPEMSCALIBCBCCONFIGDATA2;


EXTERN_C const IID IID_IEMSSatelliteInfo10;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("8FB9583E-9E07-4d64-9501-796154B263FD")
    IEMSSatelliteInfo10 : public IEMSSatelliteInfo9
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetCalibCbcConfigData2( 
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LPEMSCALIBCBCCONFIGDATA2 lpCalibCbcConfigData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSatelliteInfo10Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEMSSatelliteInfo10 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEMSSatelliteInfo10 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigFlags )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigFlags )( 
            IEMSSatelliteInfo10 * This,
            /* [out] */ DWORD *lpdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *ReloadConfigData )( 
            IEMSSatelliteInfo10 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigValueA )( 
            IEMSSatelliteInfo10 * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [string][in] */ LPCSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigValueA )( 
            IEMSSatelliteInfo10 * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [length_is][size_is][out] */ unsigned char *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigValueW )( 
            IEMSSatelliteInfo10 * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [string][in] */ LPCWSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigValueW )( 
            IEMSSatelliteInfo10 * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [length_is][size_is][out] */ WCHAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE *GetName )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [length_is][size_is][out] */ BYTE *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG *pcbRead);
        
        HRESULT ( STDMETHODCALLTYPE *GetNoradID )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulNoradID);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatelliteID )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulNoradID,
            /* [out] */ ULONG *lpulSatelliteID);
        
        HRESULT ( STDMETHODCALLTYPE *GetFreqBandwidth )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LONG *lplBandwidth);
        
        HRESULT ( STDMETHODCALLTYPE *GetCaps )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulCapabilities);
        
        HRESULT ( STDMETHODCALLTYPE *Get406SignalData )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMS406SIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetCBCSignalData )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSCBCSIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetPDSSignalData )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSPDSSIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetRolloverPeriod )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64Period);
        
        HRESULT ( STDMETHODCALLTYPE *SetRolloverPeriod )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64Period);
        
        HRESULT ( STDMETHODCALLTYPE *GetRolloverTime )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeRollover);
        
        HRESULT ( STDMETHODCALLTYPE *SetRolloverTime )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIME timeRollover);
        
        HRESULT ( STDMETHODCALLTYPE *GetRefFreq )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreq);
        
        HRESULT ( STDMETHODCALLTYPE *SetRefFreq )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreq);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrFreqOffset )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrFreqOffset )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrTimeOffset )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrTimeOffset )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpFreqOffset )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpFreqOffset )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpTimeOffset )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpTimeOffset )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetPhaseDemodSetting )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulPhaseDemod);
        
        HRESULT ( STDMETHODCALLTYPE *GetMCCSuppressInfo )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGMCCSUPPRESS *lpMCCSUPPRESSInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTCALInfo )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGTCAL *lpTCALInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetOrbitInfo )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGORBIT *lpOrbitInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetAudioInfo )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGAUDIO *lpAudioInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetProcessInfo )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGPROCESS *lpProcessInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetCollectInfo )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGBOOLDATAPROP *lpCollectInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetPassSchedulePriority )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulPriority);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpCalibration )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIME timeRollover,
            /* [in] */ double dRefFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpCalibration )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeStamp,
            /* [out] */ EMSTIME *lpTimeRollover,
            /* [out] */ double *lpdRefFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetDownlinkFreq )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdDownlinkFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetMCCSuppressInfoEx )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGMCCSUPPRESSEX *lpMCCSUPPRESSInfo);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrCalibration )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrCalibration )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeStamp,
            /* [out] */ INT64 *lpi64TimeOffset,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetForwardingInfo )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGBOOLDATAPROP *lpForwardingInfo);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatBehaviourMaxCount )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatBehaviourCount )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatBehaviour )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [in] */ EMSSATBEHAVIOUR *lpBehaviour);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatBehaviourMaxCount )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatBehaviourCount )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatBehaviour )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [out] */ EMSSATBEHAVIOUR *lpBehaviour);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatOrbitInfoMaxCount )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatOrbitInfoCount )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatOrbitInfo )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [in] */ EMSSATORBITINFO *lpOrbit);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatOrbitInfoMaxCount )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatOrbitInfoCount )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatOrbitInfo )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [out] */ EMSSATORBITINFO *lpOrbit);
        
        HRESULT ( STDMETHODCALLTYPE *GetCalibCbcConfigData )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LPEMSCALIBCBCCONFIGDATA lpCalibCbcConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetTcalConfigData )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LPEMSTCALCONFIGDATA lpTcalConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetMI406ConfigData )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSMI406CONFIGDATA lpMI406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetCalib406ConfigData )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSCALIB406CONFIGDATA lpCalib406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetOrbitDetConfigData )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSORBITDETCONFIGDATA lpOrbitDetConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetLocateCBCConfigData )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSLOCATECBCCONFIGDATA lpLocateCbcConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetLocate406ConfigData )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSLOCATE406CONFIGDATA lpLocate406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetTestConfigData )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSTESTCONFIGDATA lpTestConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetMI406ConfigData2 )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSMI406CONFIGDATA2 lpMI406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetTcalConfigData2 )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSTCALCONFIGDATA2 lpTcalConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetErrorEllipseConfigData )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSEECONFIGDATA lpData);
        
        HRESULT ( STDMETHODCALLTYPE *SetErrorEllipseConfigData )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatID,
            /* [in] */ LPEMSEECONFIGDATA lpData);
        
        HRESULT ( STDMETHODCALLTYPE *GetCalibCbcConfigData2 )( 
            IEMSSatelliteInfo10 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LPEMSCALIBCBCCONFIGDATA2 lpCalibCbcConfigData);
        
        END_INTERFACE
    } IEMSSatelliteInfo10Vtbl;

    interface IEMSSatelliteInfo10
    {
        CONST_VTBL struct IEMSSatelliteInfo10Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSatelliteInfo10_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEMSSatelliteInfo10_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEMSSatelliteInfo10_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEMSSatelliteInfo10_SetConfigFlags(This,dwFlags)	\
    ( (This)->lpVtbl -> SetConfigFlags(This,dwFlags) ) 

#define IEMSSatelliteInfo10_GetConfigFlags(This,lpdwFlags)	\
    ( (This)->lpVtbl -> GetConfigFlags(This,lpdwFlags) ) 

#define IEMSSatelliteInfo10_ReloadConfigData(This)	\
    ( (This)->lpVtbl -> ReloadConfigData(This) ) 

#define IEMSSatelliteInfo10_SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)	\
    ( (This)->lpVtbl -> SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue) ) 

#define IEMSSatelliteInfo10_GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    ( (This)->lpVtbl -> GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead) ) 

#define IEMSSatelliteInfo10_SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)	\
    ( (This)->lpVtbl -> SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue) ) 

#define IEMSSatelliteInfo10_GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    ( (This)->lpVtbl -> GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead) ) 


#define IEMSSatelliteInfo10_GetName(This,ulSatelliteID,pv,cb,pcbRead)	\
    ( (This)->lpVtbl -> GetName(This,ulSatelliteID,pv,cb,pcbRead) ) 

#define IEMSSatelliteInfo10_GetNoradID(This,ulSatelliteID,lpulNoradID)	\
    ( (This)->lpVtbl -> GetNoradID(This,ulSatelliteID,lpulNoradID) ) 

#define IEMSSatelliteInfo10_GetSatelliteID(This,ulNoradID,lpulSatelliteID)	\
    ( (This)->lpVtbl -> GetSatelliteID(This,ulNoradID,lpulSatelliteID) ) 

#define IEMSSatelliteInfo10_GetFreqBandwidth(This,ulSatelliteID,lplBandwidth)	\
    ( (This)->lpVtbl -> GetFreqBandwidth(This,ulSatelliteID,lplBandwidth) ) 

#define IEMSSatelliteInfo10_GetCaps(This,ulSatelliteID,lpulCapabilities)	\
    ( (This)->lpVtbl -> GetCaps(This,ulSatelliteID,lpulCapabilities) ) 

#define IEMSSatelliteInfo10_Get406SignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> Get406SignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo10_GetCBCSignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> GetCBCSignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo10_GetPDSSignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> GetPDSSignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo10_GetRolloverPeriod(This,ulSatelliteID,lpi64Period)	\
    ( (This)->lpVtbl -> GetRolloverPeriod(This,ulSatelliteID,lpi64Period) ) 

#define IEMSSatelliteInfo10_SetRolloverPeriod(This,ulSatelliteID,i64Period)	\
    ( (This)->lpVtbl -> SetRolloverPeriod(This,ulSatelliteID,i64Period) ) 

#define IEMSSatelliteInfo10_GetRolloverTime(This,ulSatelliteID,lpTimeRollover)	\
    ( (This)->lpVtbl -> GetRolloverTime(This,ulSatelliteID,lpTimeRollover) ) 

#define IEMSSatelliteInfo10_SetRolloverTime(This,ulSatelliteID,timeRollover)	\
    ( (This)->lpVtbl -> SetRolloverTime(This,ulSatelliteID,timeRollover) ) 

#define IEMSSatelliteInfo10_GetRefFreq(This,ulSatelliteID,lpdFreq)	\
    ( (This)->lpVtbl -> GetRefFreq(This,ulSatelliteID,lpdFreq) ) 

#define IEMSSatelliteInfo10_SetRefFreq(This,ulSatelliteID,dFreq)	\
    ( (This)->lpVtbl -> SetRefFreq(This,ulSatelliteID,dFreq) ) 

#define IEMSSatelliteInfo10_SetSarrFreqOffset(This,ulSatelliteID,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarrFreqOffset(This,ulSatelliteID,dFreqOffset) ) 

#define IEMSSatelliteInfo10_GetSarrFreqOffset(This,ulSatelliteID,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarrFreqOffset(This,ulSatelliteID,lpdFreqOffset) ) 

#define IEMSSatelliteInfo10_SetSarrTimeOffset(This,ulSatelliteID,i64TimeOffset)	\
    ( (This)->lpVtbl -> SetSarrTimeOffset(This,ulSatelliteID,i64TimeOffset) ) 

#define IEMSSatelliteInfo10_GetSarrTimeOffset(This,ulSatelliteID,lpi64TimeOffset)	\
    ( (This)->lpVtbl -> GetSarrTimeOffset(This,ulSatelliteID,lpi64TimeOffset) ) 

#define IEMSSatelliteInfo10_SetSarpFreqOffset(This,ulSatelliteID,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarpFreqOffset(This,ulSatelliteID,dFreqOffset) ) 

#define IEMSSatelliteInfo10_GetSarpFreqOffset(This,ulSatelliteID,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarpFreqOffset(This,ulSatelliteID,lpdFreqOffset) ) 

#define IEMSSatelliteInfo10_SetSarpTimeOffset(This,ulSatelliteID,i64TimeOffset)	\
    ( (This)->lpVtbl -> SetSarpTimeOffset(This,ulSatelliteID,i64TimeOffset) ) 

#define IEMSSatelliteInfo10_GetSarpTimeOffset(This,ulSatelliteID,lpi64TimeOffset)	\
    ( (This)->lpVtbl -> GetSarpTimeOffset(This,ulSatelliteID,lpi64TimeOffset) ) 


#define IEMSSatelliteInfo10_GetPhaseDemodSetting(This,ulSatelliteID,lpulPhaseDemod)	\
    ( (This)->lpVtbl -> GetPhaseDemodSetting(This,ulSatelliteID,lpulPhaseDemod) ) 


#define IEMSSatelliteInfo10_GetMCCSuppressInfo(This,ulSatelliteID,lpMCCSUPPRESSInfo)	\
    ( (This)->lpVtbl -> GetMCCSuppressInfo(This,ulSatelliteID,lpMCCSUPPRESSInfo) ) 

#define IEMSSatelliteInfo10_GetTCALInfo(This,ulSatelliteID,lpTCALInfo)	\
    ( (This)->lpVtbl -> GetTCALInfo(This,ulSatelliteID,lpTCALInfo) ) 

#define IEMSSatelliteInfo10_GetOrbitInfo(This,ulSatelliteID,lpOrbitInfo)	\
    ( (This)->lpVtbl -> GetOrbitInfo(This,ulSatelliteID,lpOrbitInfo) ) 

#define IEMSSatelliteInfo10_GetAudioInfo(This,ulSatelliteID,lpAudioInfo)	\
    ( (This)->lpVtbl -> GetAudioInfo(This,ulSatelliteID,lpAudioInfo) ) 

#define IEMSSatelliteInfo10_GetProcessInfo(This,ulSatelliteID,lpProcessInfo)	\
    ( (This)->lpVtbl -> GetProcessInfo(This,ulSatelliteID,lpProcessInfo) ) 

#define IEMSSatelliteInfo10_GetCollectInfo(This,ulSatelliteID,lpCollectInfo)	\
    ( (This)->lpVtbl -> GetCollectInfo(This,ulSatelliteID,lpCollectInfo) ) 

#define IEMSSatelliteInfo10_GetPassSchedulePriority(This,ulSatelliteID,lpulPriority)	\
    ( (This)->lpVtbl -> GetPassSchedulePriority(This,ulSatelliteID,lpulPriority) ) 

#define IEMSSatelliteInfo10_SetSarpCalibration(This,ulSatelliteID,timeRollover,dRefFreq)	\
    ( (This)->lpVtbl -> SetSarpCalibration(This,ulSatelliteID,timeRollover,dRefFreq) ) 

#define IEMSSatelliteInfo10_GetSarpCalibration(This,ulSatelliteID,lpTimeStamp,lpTimeRollover,lpdRefFreq)	\
    ( (This)->lpVtbl -> GetSarpCalibration(This,ulSatelliteID,lpTimeStamp,lpTimeRollover,lpdRefFreq) ) 

#define IEMSSatelliteInfo10_GetDownlinkFreq(This,ulSatelliteID,lpdDownlinkFreq)	\
    ( (This)->lpVtbl -> GetDownlinkFreq(This,ulSatelliteID,lpdDownlinkFreq) ) 


#define IEMSSatelliteInfo10_GetMCCSuppressInfoEx(This,ulSatelliteID,lpMCCSUPPRESSInfo)	\
    ( (This)->lpVtbl -> GetMCCSuppressInfoEx(This,ulSatelliteID,lpMCCSUPPRESSInfo) ) 

#define IEMSSatelliteInfo10_SetSarrCalibration(This,ulSatelliteID,i64TimeOffset,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarrCalibration(This,ulSatelliteID,i64TimeOffset,dFreqOffset) ) 

#define IEMSSatelliteInfo10_GetSarrCalibration(This,ulSatelliteID,lpTimeStamp,lpi64TimeOffset,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarrCalibration(This,ulSatelliteID,lpTimeStamp,lpi64TimeOffset,lpdFreqOffset) ) 

#define IEMSSatelliteInfo10_GetForwardingInfo(This,ulSatelliteID,lpForwardingInfo)	\
    ( (This)->lpVtbl -> GetForwardingInfo(This,ulSatelliteID,lpForwardingInfo) ) 


#define IEMSSatelliteInfo10_SetSatBehaviourMaxCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatBehaviourMaxCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo10_SetSatBehaviourCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatBehaviourCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo10_SetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour)	\
    ( (This)->lpVtbl -> SetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour) ) 

#define IEMSSatelliteInfo10_GetSatBehaviourMaxCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatBehaviourMaxCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo10_GetSatBehaviourCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatBehaviourCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo10_GetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour)	\
    ( (This)->lpVtbl -> GetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour) ) 

#define IEMSSatelliteInfo10_SetSatOrbitInfoMaxCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatOrbitInfoMaxCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo10_SetSatOrbitInfoCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatOrbitInfoCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo10_SetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit)	\
    ( (This)->lpVtbl -> SetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit) ) 

#define IEMSSatelliteInfo10_GetSatOrbitInfoMaxCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatOrbitInfoMaxCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo10_GetSatOrbitInfoCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatOrbitInfoCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo10_GetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit)	\
    ( (This)->lpVtbl -> GetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit) ) 


#define IEMSSatelliteInfo10_GetCalibCbcConfigData(This,ulSatelliteID,lpCalibCbcConfigData)	\
    ( (This)->lpVtbl -> GetCalibCbcConfigData(This,ulSatelliteID,lpCalibCbcConfigData) ) 

#define IEMSSatelliteInfo10_GetTcalConfigData(This,ulSatelliteID,lpTcalConfigData)	\
    ( (This)->lpVtbl -> GetTcalConfigData(This,ulSatelliteID,lpTcalConfigData) ) 

#define IEMSSatelliteInfo10_GetMI406ConfigData(This,ulSatID,lpMI406ConfigData)	\
    ( (This)->lpVtbl -> GetMI406ConfigData(This,ulSatID,lpMI406ConfigData) ) 

#define IEMSSatelliteInfo10_GetCalib406ConfigData(This,ulSatID,lpCalib406ConfigData)	\
    ( (This)->lpVtbl -> GetCalib406ConfigData(This,ulSatID,lpCalib406ConfigData) ) 

#define IEMSSatelliteInfo10_GetOrbitDetConfigData(This,ulSatID,lpOrbitDetConfigData)	\
    ( (This)->lpVtbl -> GetOrbitDetConfigData(This,ulSatID,lpOrbitDetConfigData) ) 

#define IEMSSatelliteInfo10_GetLocateCBCConfigData(This,ulSatID,lpLocateCbcConfigData)	\
    ( (This)->lpVtbl -> GetLocateCBCConfigData(This,ulSatID,lpLocateCbcConfigData) ) 

#define IEMSSatelliteInfo10_GetLocate406ConfigData(This,ulSatID,lpLocate406ConfigData)	\
    ( (This)->lpVtbl -> GetLocate406ConfigData(This,ulSatID,lpLocate406ConfigData) ) 


#define IEMSSatelliteInfo10_GetTestConfigData(This,ulSatID,lpTestConfigData)	\
    ( (This)->lpVtbl -> GetTestConfigData(This,ulSatID,lpTestConfigData) ) 


#define IEMSSatelliteInfo10_GetMI406ConfigData2(This,ulSatID,lpMI406ConfigData)	\
    ( (This)->lpVtbl -> GetMI406ConfigData2(This,ulSatID,lpMI406ConfigData) ) 


#define IEMSSatelliteInfo10_GetTcalConfigData2(This,ulSatID,lpTcalConfigData)	\
    ( (This)->lpVtbl -> GetTcalConfigData2(This,ulSatID,lpTcalConfigData) ) 

#define IEMSSatelliteInfo10_GetErrorEllipseConfigData(This,ulSatID,lpData)	\
    ( (This)->lpVtbl -> GetErrorEllipseConfigData(This,ulSatID,lpData) ) 

#define IEMSSatelliteInfo10_SetErrorEllipseConfigData(This,ulSatID,lpData)	\
    ( (This)->lpVtbl -> SetErrorEllipseConfigData(This,ulSatID,lpData) ) 


#define IEMSSatelliteInfo10_GetCalibCbcConfigData2(This,ulSatelliteID,lpCalibCbcConfigData)	\
    ( (This)->lpVtbl -> GetCalibCbcConfigData2(This,ulSatelliteID,lpCalibCbcConfigData) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEMSSatelliteInfo10_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSATINF_0000_0010 */
/* [local] */ 

typedef /* [unique] */ IEMSSatelliteInfo10 *LPEMSSATELLITEINFO10;



extern RPC_IF_HANDLE __MIDL_itf_EMSATINF_0000_0010_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSATINF_0000_0010_v0_0_s_ifspec;

#ifndef __IEMSSatelliteInfo11_INTERFACE_DEFINED__
#define __IEMSSatelliteInfo11_INTERFACE_DEFINED__

/* interface IEMSSatelliteInfo11 */
/* [unique][helpstring][uuid][object] */ 

typedef struct _tagEMSLOCATECBCCONFIGDATA2
    {
    ULONG ulDetectMinimum;
    BYTE cAmplitudeRangeMin;
    BYTE cAmplitudeRangeMax;
    ULONG ulIterationsMaximum;
    double dThreshold;
    double dCorrelationMaximum;
    BOOL bDrift;
    double dEEScaleFactors[ 3 ];
    double dEEAdjustments[ 3 ];
    double dSweepThreshold;
    ULONG ulSweepMinPoints;
    double dMaxNoise;
    ULONG ulMinPtsVisible;
    double dReserved1;
    double dReserved2;
    double dReserved3;
    ULONG ulReserved4;
    ULONG ulReserved5;
    } 	EMSLOCATECBCCONFIGDATA2;

typedef struct _tagEMSLOCATECBCCONFIGDATA2 *LPEMSLOCATECBCCONFIGDATA2;

typedef struct _tagEMSLOCATE406CONFIGDATA2
    {
    ULONG ulIterationsMaximum;
    double dThreshold;
    double dCorrelationMaximum;
    BOOL bDrift;
    BOOL bAltitude;
    double dEEScaleFactors[ 3 ];
    double dEEAdjustments[ 3 ];
    double dMaxNoise;
    ULONG ulMinPtsVisible;
    double dReserved1;
    double dReserved2;
    double dReserved3;
    ULONG ulReserved4;
    ULONG ulReserved5;
    } 	EMSLOCATE406CONFIGDATA2;

typedef struct _tagEMSLOCATE406CONFIGDATA2 *LPEMSLOCATE406CONFIGDATA2;


EXTERN_C const IID IID_IEMSSatelliteInfo11;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DD309AAC-DF15-48f7-9382-C48E4D52D1A8")
    IEMSSatelliteInfo11 : public IEMSSatelliteInfo10
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetLocateCBCConfigData2( 
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSLOCATECBCCONFIGDATA2 lpLocateCbcConfigData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLocate406ConfigData2( 
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSLOCATE406CONFIGDATA2 lpLocate406ConfigData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSatelliteInfo11Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEMSSatelliteInfo11 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEMSSatelliteInfo11 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigFlags )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigFlags )( 
            IEMSSatelliteInfo11 * This,
            /* [out] */ DWORD *lpdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *ReloadConfigData )( 
            IEMSSatelliteInfo11 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigValueA )( 
            IEMSSatelliteInfo11 * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [string][in] */ LPCSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigValueA )( 
            IEMSSatelliteInfo11 * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [length_is][size_is][out] */ unsigned char *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigValueW )( 
            IEMSSatelliteInfo11 * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [string][in] */ LPCWSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigValueW )( 
            IEMSSatelliteInfo11 * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [length_is][size_is][out] */ WCHAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE *GetName )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [length_is][size_is][out] */ BYTE *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG *pcbRead);
        
        HRESULT ( STDMETHODCALLTYPE *GetNoradID )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulNoradID);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatelliteID )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulNoradID,
            /* [out] */ ULONG *lpulSatelliteID);
        
        HRESULT ( STDMETHODCALLTYPE *GetFreqBandwidth )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LONG *lplBandwidth);
        
        HRESULT ( STDMETHODCALLTYPE *GetCaps )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulCapabilities);
        
        HRESULT ( STDMETHODCALLTYPE *Get406SignalData )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMS406SIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetCBCSignalData )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSCBCSIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetPDSSignalData )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSPDSSIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetRolloverPeriod )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64Period);
        
        HRESULT ( STDMETHODCALLTYPE *SetRolloverPeriod )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64Period);
        
        HRESULT ( STDMETHODCALLTYPE *GetRolloverTime )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeRollover);
        
        HRESULT ( STDMETHODCALLTYPE *SetRolloverTime )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIME timeRollover);
        
        HRESULT ( STDMETHODCALLTYPE *GetRefFreq )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreq);
        
        HRESULT ( STDMETHODCALLTYPE *SetRefFreq )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreq);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrFreqOffset )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrFreqOffset )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrTimeOffset )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrTimeOffset )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpFreqOffset )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpFreqOffset )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpTimeOffset )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpTimeOffset )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetPhaseDemodSetting )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulPhaseDemod);
        
        HRESULT ( STDMETHODCALLTYPE *GetMCCSuppressInfo )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGMCCSUPPRESS *lpMCCSUPPRESSInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTCALInfo )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGTCAL *lpTCALInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetOrbitInfo )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGORBIT *lpOrbitInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetAudioInfo )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGAUDIO *lpAudioInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetProcessInfo )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGPROCESS *lpProcessInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetCollectInfo )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGBOOLDATAPROP *lpCollectInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetPassSchedulePriority )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulPriority);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpCalibration )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIME timeRollover,
            /* [in] */ double dRefFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpCalibration )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeStamp,
            /* [out] */ EMSTIME *lpTimeRollover,
            /* [out] */ double *lpdRefFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetDownlinkFreq )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdDownlinkFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetMCCSuppressInfoEx )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGMCCSUPPRESSEX *lpMCCSUPPRESSInfo);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrCalibration )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrCalibration )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeStamp,
            /* [out] */ INT64 *lpi64TimeOffset,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetForwardingInfo )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGBOOLDATAPROP *lpForwardingInfo);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatBehaviourMaxCount )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatBehaviourCount )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatBehaviour )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [in] */ EMSSATBEHAVIOUR *lpBehaviour);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatBehaviourMaxCount )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatBehaviourCount )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatBehaviour )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [out] */ EMSSATBEHAVIOUR *lpBehaviour);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatOrbitInfoMaxCount )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatOrbitInfoCount )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatOrbitInfo )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [in] */ EMSSATORBITINFO *lpOrbit);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatOrbitInfoMaxCount )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatOrbitInfoCount )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatOrbitInfo )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [out] */ EMSSATORBITINFO *lpOrbit);
        
        HRESULT ( STDMETHODCALLTYPE *GetCalibCbcConfigData )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LPEMSCALIBCBCCONFIGDATA lpCalibCbcConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetTcalConfigData )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LPEMSTCALCONFIGDATA lpTcalConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetMI406ConfigData )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSMI406CONFIGDATA lpMI406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetCalib406ConfigData )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSCALIB406CONFIGDATA lpCalib406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetOrbitDetConfigData )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSORBITDETCONFIGDATA lpOrbitDetConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetLocateCBCConfigData )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSLOCATECBCCONFIGDATA lpLocateCbcConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetLocate406ConfigData )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSLOCATE406CONFIGDATA lpLocate406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetTestConfigData )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSTESTCONFIGDATA lpTestConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetMI406ConfigData2 )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSMI406CONFIGDATA2 lpMI406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetTcalConfigData2 )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSTCALCONFIGDATA2 lpTcalConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetErrorEllipseConfigData )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSEECONFIGDATA lpData);
        
        HRESULT ( STDMETHODCALLTYPE *SetErrorEllipseConfigData )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatID,
            /* [in] */ LPEMSEECONFIGDATA lpData);
        
        HRESULT ( STDMETHODCALLTYPE *GetCalibCbcConfigData2 )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LPEMSCALIBCBCCONFIGDATA2 lpCalibCbcConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetLocateCBCConfigData2 )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSLOCATECBCCONFIGDATA2 lpLocateCbcConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetLocate406ConfigData2 )( 
            IEMSSatelliteInfo11 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSLOCATE406CONFIGDATA2 lpLocate406ConfigData);
        
        END_INTERFACE
    } IEMSSatelliteInfo11Vtbl;

    interface IEMSSatelliteInfo11
    {
        CONST_VTBL struct IEMSSatelliteInfo11Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSatelliteInfo11_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEMSSatelliteInfo11_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEMSSatelliteInfo11_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEMSSatelliteInfo11_SetConfigFlags(This,dwFlags)	\
    ( (This)->lpVtbl -> SetConfigFlags(This,dwFlags) ) 

#define IEMSSatelliteInfo11_GetConfigFlags(This,lpdwFlags)	\
    ( (This)->lpVtbl -> GetConfigFlags(This,lpdwFlags) ) 

#define IEMSSatelliteInfo11_ReloadConfigData(This)	\
    ( (This)->lpVtbl -> ReloadConfigData(This) ) 

#define IEMSSatelliteInfo11_SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)	\
    ( (This)->lpVtbl -> SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue) ) 

#define IEMSSatelliteInfo11_GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    ( (This)->lpVtbl -> GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead) ) 

#define IEMSSatelliteInfo11_SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)	\
    ( (This)->lpVtbl -> SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue) ) 

#define IEMSSatelliteInfo11_GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    ( (This)->lpVtbl -> GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead) ) 


#define IEMSSatelliteInfo11_GetName(This,ulSatelliteID,pv,cb,pcbRead)	\
    ( (This)->lpVtbl -> GetName(This,ulSatelliteID,pv,cb,pcbRead) ) 

#define IEMSSatelliteInfo11_GetNoradID(This,ulSatelliteID,lpulNoradID)	\
    ( (This)->lpVtbl -> GetNoradID(This,ulSatelliteID,lpulNoradID) ) 

#define IEMSSatelliteInfo11_GetSatelliteID(This,ulNoradID,lpulSatelliteID)	\
    ( (This)->lpVtbl -> GetSatelliteID(This,ulNoradID,lpulSatelliteID) ) 

#define IEMSSatelliteInfo11_GetFreqBandwidth(This,ulSatelliteID,lplBandwidth)	\
    ( (This)->lpVtbl -> GetFreqBandwidth(This,ulSatelliteID,lplBandwidth) ) 

#define IEMSSatelliteInfo11_GetCaps(This,ulSatelliteID,lpulCapabilities)	\
    ( (This)->lpVtbl -> GetCaps(This,ulSatelliteID,lpulCapabilities) ) 

#define IEMSSatelliteInfo11_Get406SignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> Get406SignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo11_GetCBCSignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> GetCBCSignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo11_GetPDSSignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> GetPDSSignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo11_GetRolloverPeriod(This,ulSatelliteID,lpi64Period)	\
    ( (This)->lpVtbl -> GetRolloverPeriod(This,ulSatelliteID,lpi64Period) ) 

#define IEMSSatelliteInfo11_SetRolloverPeriod(This,ulSatelliteID,i64Period)	\
    ( (This)->lpVtbl -> SetRolloverPeriod(This,ulSatelliteID,i64Period) ) 

#define IEMSSatelliteInfo11_GetRolloverTime(This,ulSatelliteID,lpTimeRollover)	\
    ( (This)->lpVtbl -> GetRolloverTime(This,ulSatelliteID,lpTimeRollover) ) 

#define IEMSSatelliteInfo11_SetRolloverTime(This,ulSatelliteID,timeRollover)	\
    ( (This)->lpVtbl -> SetRolloverTime(This,ulSatelliteID,timeRollover) ) 

#define IEMSSatelliteInfo11_GetRefFreq(This,ulSatelliteID,lpdFreq)	\
    ( (This)->lpVtbl -> GetRefFreq(This,ulSatelliteID,lpdFreq) ) 

#define IEMSSatelliteInfo11_SetRefFreq(This,ulSatelliteID,dFreq)	\
    ( (This)->lpVtbl -> SetRefFreq(This,ulSatelliteID,dFreq) ) 

#define IEMSSatelliteInfo11_SetSarrFreqOffset(This,ulSatelliteID,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarrFreqOffset(This,ulSatelliteID,dFreqOffset) ) 

#define IEMSSatelliteInfo11_GetSarrFreqOffset(This,ulSatelliteID,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarrFreqOffset(This,ulSatelliteID,lpdFreqOffset) ) 

#define IEMSSatelliteInfo11_SetSarrTimeOffset(This,ulSatelliteID,i64TimeOffset)	\
    ( (This)->lpVtbl -> SetSarrTimeOffset(This,ulSatelliteID,i64TimeOffset) ) 

#define IEMSSatelliteInfo11_GetSarrTimeOffset(This,ulSatelliteID,lpi64TimeOffset)	\
    ( (This)->lpVtbl -> GetSarrTimeOffset(This,ulSatelliteID,lpi64TimeOffset) ) 

#define IEMSSatelliteInfo11_SetSarpFreqOffset(This,ulSatelliteID,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarpFreqOffset(This,ulSatelliteID,dFreqOffset) ) 

#define IEMSSatelliteInfo11_GetSarpFreqOffset(This,ulSatelliteID,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarpFreqOffset(This,ulSatelliteID,lpdFreqOffset) ) 

#define IEMSSatelliteInfo11_SetSarpTimeOffset(This,ulSatelliteID,i64TimeOffset)	\
    ( (This)->lpVtbl -> SetSarpTimeOffset(This,ulSatelliteID,i64TimeOffset) ) 

#define IEMSSatelliteInfo11_GetSarpTimeOffset(This,ulSatelliteID,lpi64TimeOffset)	\
    ( (This)->lpVtbl -> GetSarpTimeOffset(This,ulSatelliteID,lpi64TimeOffset) ) 


#define IEMSSatelliteInfo11_GetPhaseDemodSetting(This,ulSatelliteID,lpulPhaseDemod)	\
    ( (This)->lpVtbl -> GetPhaseDemodSetting(This,ulSatelliteID,lpulPhaseDemod) ) 


#define IEMSSatelliteInfo11_GetMCCSuppressInfo(This,ulSatelliteID,lpMCCSUPPRESSInfo)	\
    ( (This)->lpVtbl -> GetMCCSuppressInfo(This,ulSatelliteID,lpMCCSUPPRESSInfo) ) 

#define IEMSSatelliteInfo11_GetTCALInfo(This,ulSatelliteID,lpTCALInfo)	\
    ( (This)->lpVtbl -> GetTCALInfo(This,ulSatelliteID,lpTCALInfo) ) 

#define IEMSSatelliteInfo11_GetOrbitInfo(This,ulSatelliteID,lpOrbitInfo)	\
    ( (This)->lpVtbl -> GetOrbitInfo(This,ulSatelliteID,lpOrbitInfo) ) 

#define IEMSSatelliteInfo11_GetAudioInfo(This,ulSatelliteID,lpAudioInfo)	\
    ( (This)->lpVtbl -> GetAudioInfo(This,ulSatelliteID,lpAudioInfo) ) 

#define IEMSSatelliteInfo11_GetProcessInfo(This,ulSatelliteID,lpProcessInfo)	\
    ( (This)->lpVtbl -> GetProcessInfo(This,ulSatelliteID,lpProcessInfo) ) 

#define IEMSSatelliteInfo11_GetCollectInfo(This,ulSatelliteID,lpCollectInfo)	\
    ( (This)->lpVtbl -> GetCollectInfo(This,ulSatelliteID,lpCollectInfo) ) 

#define IEMSSatelliteInfo11_GetPassSchedulePriority(This,ulSatelliteID,lpulPriority)	\
    ( (This)->lpVtbl -> GetPassSchedulePriority(This,ulSatelliteID,lpulPriority) ) 

#define IEMSSatelliteInfo11_SetSarpCalibration(This,ulSatelliteID,timeRollover,dRefFreq)	\
    ( (This)->lpVtbl -> SetSarpCalibration(This,ulSatelliteID,timeRollover,dRefFreq) ) 

#define IEMSSatelliteInfo11_GetSarpCalibration(This,ulSatelliteID,lpTimeStamp,lpTimeRollover,lpdRefFreq)	\
    ( (This)->lpVtbl -> GetSarpCalibration(This,ulSatelliteID,lpTimeStamp,lpTimeRollover,lpdRefFreq) ) 

#define IEMSSatelliteInfo11_GetDownlinkFreq(This,ulSatelliteID,lpdDownlinkFreq)	\
    ( (This)->lpVtbl -> GetDownlinkFreq(This,ulSatelliteID,lpdDownlinkFreq) ) 


#define IEMSSatelliteInfo11_GetMCCSuppressInfoEx(This,ulSatelliteID,lpMCCSUPPRESSInfo)	\
    ( (This)->lpVtbl -> GetMCCSuppressInfoEx(This,ulSatelliteID,lpMCCSUPPRESSInfo) ) 

#define IEMSSatelliteInfo11_SetSarrCalibration(This,ulSatelliteID,i64TimeOffset,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarrCalibration(This,ulSatelliteID,i64TimeOffset,dFreqOffset) ) 

#define IEMSSatelliteInfo11_GetSarrCalibration(This,ulSatelliteID,lpTimeStamp,lpi64TimeOffset,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarrCalibration(This,ulSatelliteID,lpTimeStamp,lpi64TimeOffset,lpdFreqOffset) ) 

#define IEMSSatelliteInfo11_GetForwardingInfo(This,ulSatelliteID,lpForwardingInfo)	\
    ( (This)->lpVtbl -> GetForwardingInfo(This,ulSatelliteID,lpForwardingInfo) ) 


#define IEMSSatelliteInfo11_SetSatBehaviourMaxCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatBehaviourMaxCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo11_SetSatBehaviourCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatBehaviourCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo11_SetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour)	\
    ( (This)->lpVtbl -> SetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour) ) 

#define IEMSSatelliteInfo11_GetSatBehaviourMaxCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatBehaviourMaxCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo11_GetSatBehaviourCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatBehaviourCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo11_GetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour)	\
    ( (This)->lpVtbl -> GetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour) ) 

#define IEMSSatelliteInfo11_SetSatOrbitInfoMaxCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatOrbitInfoMaxCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo11_SetSatOrbitInfoCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatOrbitInfoCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo11_SetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit)	\
    ( (This)->lpVtbl -> SetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit) ) 

#define IEMSSatelliteInfo11_GetSatOrbitInfoMaxCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatOrbitInfoMaxCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo11_GetSatOrbitInfoCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatOrbitInfoCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo11_GetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit)	\
    ( (This)->lpVtbl -> GetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit) ) 


#define IEMSSatelliteInfo11_GetCalibCbcConfigData(This,ulSatelliteID,lpCalibCbcConfigData)	\
    ( (This)->lpVtbl -> GetCalibCbcConfigData(This,ulSatelliteID,lpCalibCbcConfigData) ) 

#define IEMSSatelliteInfo11_GetTcalConfigData(This,ulSatelliteID,lpTcalConfigData)	\
    ( (This)->lpVtbl -> GetTcalConfigData(This,ulSatelliteID,lpTcalConfigData) ) 

#define IEMSSatelliteInfo11_GetMI406ConfigData(This,ulSatID,lpMI406ConfigData)	\
    ( (This)->lpVtbl -> GetMI406ConfigData(This,ulSatID,lpMI406ConfigData) ) 

#define IEMSSatelliteInfo11_GetCalib406ConfigData(This,ulSatID,lpCalib406ConfigData)	\
    ( (This)->lpVtbl -> GetCalib406ConfigData(This,ulSatID,lpCalib406ConfigData) ) 

#define IEMSSatelliteInfo11_GetOrbitDetConfigData(This,ulSatID,lpOrbitDetConfigData)	\
    ( (This)->lpVtbl -> GetOrbitDetConfigData(This,ulSatID,lpOrbitDetConfigData) ) 

#define IEMSSatelliteInfo11_GetLocateCBCConfigData(This,ulSatID,lpLocateCbcConfigData)	\
    ( (This)->lpVtbl -> GetLocateCBCConfigData(This,ulSatID,lpLocateCbcConfigData) ) 

#define IEMSSatelliteInfo11_GetLocate406ConfigData(This,ulSatID,lpLocate406ConfigData)	\
    ( (This)->lpVtbl -> GetLocate406ConfigData(This,ulSatID,lpLocate406ConfigData) ) 


#define IEMSSatelliteInfo11_GetTestConfigData(This,ulSatID,lpTestConfigData)	\
    ( (This)->lpVtbl -> GetTestConfigData(This,ulSatID,lpTestConfigData) ) 


#define IEMSSatelliteInfo11_GetMI406ConfigData2(This,ulSatID,lpMI406ConfigData)	\
    ( (This)->lpVtbl -> GetMI406ConfigData2(This,ulSatID,lpMI406ConfigData) ) 


#define IEMSSatelliteInfo11_GetTcalConfigData2(This,ulSatID,lpTcalConfigData)	\
    ( (This)->lpVtbl -> GetTcalConfigData2(This,ulSatID,lpTcalConfigData) ) 

#define IEMSSatelliteInfo11_GetErrorEllipseConfigData(This,ulSatID,lpData)	\
    ( (This)->lpVtbl -> GetErrorEllipseConfigData(This,ulSatID,lpData) ) 

#define IEMSSatelliteInfo11_SetErrorEllipseConfigData(This,ulSatID,lpData)	\
    ( (This)->lpVtbl -> SetErrorEllipseConfigData(This,ulSatID,lpData) ) 


#define IEMSSatelliteInfo11_GetCalibCbcConfigData2(This,ulSatelliteID,lpCalibCbcConfigData)	\
    ( (This)->lpVtbl -> GetCalibCbcConfigData2(This,ulSatelliteID,lpCalibCbcConfigData) ) 


#define IEMSSatelliteInfo11_GetLocateCBCConfigData2(This,ulSatID,lpLocateCbcConfigData)	\
    ( (This)->lpVtbl -> GetLocateCBCConfigData2(This,ulSatID,lpLocateCbcConfigData) ) 

#define IEMSSatelliteInfo11_GetLocate406ConfigData2(This,ulSatID,lpLocate406ConfigData)	\
    ( (This)->lpVtbl -> GetLocate406ConfigData2(This,ulSatID,lpLocate406ConfigData) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEMSSatelliteInfo11_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSATINF_0000_0011 */
/* [local] */ 

typedef /* [unique] */ IEMSSatelliteInfo11 *LPEMSSATELLITEINFO11;



extern RPC_IF_HANDLE __MIDL_itf_EMSATINF_0000_0011_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSATINF_0000_0011_v0_0_s_ifspec;

#ifndef __IEMSSatelliteInfo12_INTERFACE_DEFINED__
#define __IEMSSatelliteInfo12_INTERFACE_DEFINED__

/* interface IEMSSatelliteInfo12 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSSatelliteInfo12;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A18342E2-9189-40b0-A477-DEE313BC67D8")
    IEMSSatelliteInfo12 : public IEMSSatelliteInfo11
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetSARPCalibTimeThreshold( 
            /* [in] */ const ULONG culSatID,
            /* [out] */ double *pdThreshold) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSARPCalibTimeThreshold( 
            /* [in] */ const ULONG culSatID,
            /* [in] */ const double cdThreshold) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSARPUSOFreqThreshold( 
            /* [in] */ const ULONG culSatID,
            /* [out] */ double *pdThreshold) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSARPUSOFreqThreshold( 
            /* [in] */ const ULONG culSatID,
            /* [in] */ const double cdThreshold) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSatelliteInfo12Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEMSSatelliteInfo12 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEMSSatelliteInfo12 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigFlags )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigFlags )( 
            IEMSSatelliteInfo12 * This,
            /* [out] */ DWORD *lpdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *ReloadConfigData )( 
            IEMSSatelliteInfo12 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigValueA )( 
            IEMSSatelliteInfo12 * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [string][in] */ LPCSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigValueA )( 
            IEMSSatelliteInfo12 * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [length_is][size_is][out] */ unsigned char *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigValueW )( 
            IEMSSatelliteInfo12 * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [string][in] */ LPCWSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigValueW )( 
            IEMSSatelliteInfo12 * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [length_is][size_is][out] */ WCHAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE *GetName )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [length_is][size_is][out] */ BYTE *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG *pcbRead);
        
        HRESULT ( STDMETHODCALLTYPE *GetNoradID )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulNoradID);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatelliteID )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulNoradID,
            /* [out] */ ULONG *lpulSatelliteID);
        
        HRESULT ( STDMETHODCALLTYPE *GetFreqBandwidth )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LONG *lplBandwidth);
        
        HRESULT ( STDMETHODCALLTYPE *GetCaps )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulCapabilities);
        
        HRESULT ( STDMETHODCALLTYPE *Get406SignalData )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMS406SIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetCBCSignalData )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSCBCSIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetPDSSignalData )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSPDSSIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetRolloverPeriod )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64Period);
        
        HRESULT ( STDMETHODCALLTYPE *SetRolloverPeriod )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64Period);
        
        HRESULT ( STDMETHODCALLTYPE *GetRolloverTime )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeRollover);
        
        HRESULT ( STDMETHODCALLTYPE *SetRolloverTime )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIME timeRollover);
        
        HRESULT ( STDMETHODCALLTYPE *GetRefFreq )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreq);
        
        HRESULT ( STDMETHODCALLTYPE *SetRefFreq )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreq);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrFreqOffset )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrFreqOffset )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrTimeOffset )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrTimeOffset )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpFreqOffset )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpFreqOffset )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpTimeOffset )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpTimeOffset )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetPhaseDemodSetting )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulPhaseDemod);
        
        HRESULT ( STDMETHODCALLTYPE *GetMCCSuppressInfo )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGMCCSUPPRESS *lpMCCSUPPRESSInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTCALInfo )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGTCAL *lpTCALInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetOrbitInfo )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGORBIT *lpOrbitInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetAudioInfo )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGAUDIO *lpAudioInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetProcessInfo )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGPROCESS *lpProcessInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetCollectInfo )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGBOOLDATAPROP *lpCollectInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetPassSchedulePriority )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulPriority);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpCalibration )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIME timeRollover,
            /* [in] */ double dRefFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpCalibration )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeStamp,
            /* [out] */ EMSTIME *lpTimeRollover,
            /* [out] */ double *lpdRefFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetDownlinkFreq )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdDownlinkFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetMCCSuppressInfoEx )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGMCCSUPPRESSEX *lpMCCSUPPRESSInfo);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrCalibration )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrCalibration )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeStamp,
            /* [out] */ INT64 *lpi64TimeOffset,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetForwardingInfo )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGBOOLDATAPROP *lpForwardingInfo);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatBehaviourMaxCount )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatBehaviourCount )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatBehaviour )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [in] */ EMSSATBEHAVIOUR *lpBehaviour);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatBehaviourMaxCount )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatBehaviourCount )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatBehaviour )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [out] */ EMSSATBEHAVIOUR *lpBehaviour);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatOrbitInfoMaxCount )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatOrbitInfoCount )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatOrbitInfo )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [in] */ EMSSATORBITINFO *lpOrbit);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatOrbitInfoMaxCount )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatOrbitInfoCount )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatOrbitInfo )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [out] */ EMSSATORBITINFO *lpOrbit);
        
        HRESULT ( STDMETHODCALLTYPE *GetCalibCbcConfigData )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LPEMSCALIBCBCCONFIGDATA lpCalibCbcConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetTcalConfigData )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LPEMSTCALCONFIGDATA lpTcalConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetMI406ConfigData )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSMI406CONFIGDATA lpMI406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetCalib406ConfigData )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSCALIB406CONFIGDATA lpCalib406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetOrbitDetConfigData )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSORBITDETCONFIGDATA lpOrbitDetConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetLocateCBCConfigData )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSLOCATECBCCONFIGDATA lpLocateCbcConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetLocate406ConfigData )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSLOCATE406CONFIGDATA lpLocate406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetTestConfigData )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSTESTCONFIGDATA lpTestConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetMI406ConfigData2 )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSMI406CONFIGDATA2 lpMI406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetTcalConfigData2 )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSTCALCONFIGDATA2 lpTcalConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetErrorEllipseConfigData )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSEECONFIGDATA lpData);
        
        HRESULT ( STDMETHODCALLTYPE *SetErrorEllipseConfigData )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatID,
            /* [in] */ LPEMSEECONFIGDATA lpData);
        
        HRESULT ( STDMETHODCALLTYPE *GetCalibCbcConfigData2 )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LPEMSCALIBCBCCONFIGDATA2 lpCalibCbcConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetLocateCBCConfigData2 )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSLOCATECBCCONFIGDATA2 lpLocateCbcConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetLocate406ConfigData2 )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSLOCATE406CONFIGDATA2 lpLocate406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetSARPCalibTimeThreshold )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ const ULONG culSatID,
            /* [out] */ double *pdThreshold);
        
        HRESULT ( STDMETHODCALLTYPE *SetSARPCalibTimeThreshold )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ const ULONG culSatID,
            /* [in] */ const double cdThreshold);
        
        HRESULT ( STDMETHODCALLTYPE *GetSARPUSOFreqThreshold )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ const ULONG culSatID,
            /* [out] */ double *pdThreshold);
        
        HRESULT ( STDMETHODCALLTYPE *SetSARPUSOFreqThreshold )( 
            IEMSSatelliteInfo12 * This,
            /* [in] */ const ULONG culSatID,
            /* [in] */ const double cdThreshold);
        
        END_INTERFACE
    } IEMSSatelliteInfo12Vtbl;

    interface IEMSSatelliteInfo12
    {
        CONST_VTBL struct IEMSSatelliteInfo12Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSatelliteInfo12_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEMSSatelliteInfo12_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEMSSatelliteInfo12_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEMSSatelliteInfo12_SetConfigFlags(This,dwFlags)	\
    ( (This)->lpVtbl -> SetConfigFlags(This,dwFlags) ) 

#define IEMSSatelliteInfo12_GetConfigFlags(This,lpdwFlags)	\
    ( (This)->lpVtbl -> GetConfigFlags(This,lpdwFlags) ) 

#define IEMSSatelliteInfo12_ReloadConfigData(This)	\
    ( (This)->lpVtbl -> ReloadConfigData(This) ) 

#define IEMSSatelliteInfo12_SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)	\
    ( (This)->lpVtbl -> SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue) ) 

#define IEMSSatelliteInfo12_GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    ( (This)->lpVtbl -> GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead) ) 

#define IEMSSatelliteInfo12_SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)	\
    ( (This)->lpVtbl -> SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue) ) 

#define IEMSSatelliteInfo12_GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    ( (This)->lpVtbl -> GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead) ) 


#define IEMSSatelliteInfo12_GetName(This,ulSatelliteID,pv,cb,pcbRead)	\
    ( (This)->lpVtbl -> GetName(This,ulSatelliteID,pv,cb,pcbRead) ) 

#define IEMSSatelliteInfo12_GetNoradID(This,ulSatelliteID,lpulNoradID)	\
    ( (This)->lpVtbl -> GetNoradID(This,ulSatelliteID,lpulNoradID) ) 

#define IEMSSatelliteInfo12_GetSatelliteID(This,ulNoradID,lpulSatelliteID)	\
    ( (This)->lpVtbl -> GetSatelliteID(This,ulNoradID,lpulSatelliteID) ) 

#define IEMSSatelliteInfo12_GetFreqBandwidth(This,ulSatelliteID,lplBandwidth)	\
    ( (This)->lpVtbl -> GetFreqBandwidth(This,ulSatelliteID,lplBandwidth) ) 

#define IEMSSatelliteInfo12_GetCaps(This,ulSatelliteID,lpulCapabilities)	\
    ( (This)->lpVtbl -> GetCaps(This,ulSatelliteID,lpulCapabilities) ) 

#define IEMSSatelliteInfo12_Get406SignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> Get406SignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo12_GetCBCSignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> GetCBCSignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo12_GetPDSSignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> GetPDSSignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo12_GetRolloverPeriod(This,ulSatelliteID,lpi64Period)	\
    ( (This)->lpVtbl -> GetRolloverPeriod(This,ulSatelliteID,lpi64Period) ) 

#define IEMSSatelliteInfo12_SetRolloverPeriod(This,ulSatelliteID,i64Period)	\
    ( (This)->lpVtbl -> SetRolloverPeriod(This,ulSatelliteID,i64Period) ) 

#define IEMSSatelliteInfo12_GetRolloverTime(This,ulSatelliteID,lpTimeRollover)	\
    ( (This)->lpVtbl -> GetRolloverTime(This,ulSatelliteID,lpTimeRollover) ) 

#define IEMSSatelliteInfo12_SetRolloverTime(This,ulSatelliteID,timeRollover)	\
    ( (This)->lpVtbl -> SetRolloverTime(This,ulSatelliteID,timeRollover) ) 

#define IEMSSatelliteInfo12_GetRefFreq(This,ulSatelliteID,lpdFreq)	\
    ( (This)->lpVtbl -> GetRefFreq(This,ulSatelliteID,lpdFreq) ) 

#define IEMSSatelliteInfo12_SetRefFreq(This,ulSatelliteID,dFreq)	\
    ( (This)->lpVtbl -> SetRefFreq(This,ulSatelliteID,dFreq) ) 

#define IEMSSatelliteInfo12_SetSarrFreqOffset(This,ulSatelliteID,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarrFreqOffset(This,ulSatelliteID,dFreqOffset) ) 

#define IEMSSatelliteInfo12_GetSarrFreqOffset(This,ulSatelliteID,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarrFreqOffset(This,ulSatelliteID,lpdFreqOffset) ) 

#define IEMSSatelliteInfo12_SetSarrTimeOffset(This,ulSatelliteID,i64TimeOffset)	\
    ( (This)->lpVtbl -> SetSarrTimeOffset(This,ulSatelliteID,i64TimeOffset) ) 

#define IEMSSatelliteInfo12_GetSarrTimeOffset(This,ulSatelliteID,lpi64TimeOffset)	\
    ( (This)->lpVtbl -> GetSarrTimeOffset(This,ulSatelliteID,lpi64TimeOffset) ) 

#define IEMSSatelliteInfo12_SetSarpFreqOffset(This,ulSatelliteID,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarpFreqOffset(This,ulSatelliteID,dFreqOffset) ) 

#define IEMSSatelliteInfo12_GetSarpFreqOffset(This,ulSatelliteID,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarpFreqOffset(This,ulSatelliteID,lpdFreqOffset) ) 

#define IEMSSatelliteInfo12_SetSarpTimeOffset(This,ulSatelliteID,i64TimeOffset)	\
    ( (This)->lpVtbl -> SetSarpTimeOffset(This,ulSatelliteID,i64TimeOffset) ) 

#define IEMSSatelliteInfo12_GetSarpTimeOffset(This,ulSatelliteID,lpi64TimeOffset)	\
    ( (This)->lpVtbl -> GetSarpTimeOffset(This,ulSatelliteID,lpi64TimeOffset) ) 


#define IEMSSatelliteInfo12_GetPhaseDemodSetting(This,ulSatelliteID,lpulPhaseDemod)	\
    ( (This)->lpVtbl -> GetPhaseDemodSetting(This,ulSatelliteID,lpulPhaseDemod) ) 


#define IEMSSatelliteInfo12_GetMCCSuppressInfo(This,ulSatelliteID,lpMCCSUPPRESSInfo)	\
    ( (This)->lpVtbl -> GetMCCSuppressInfo(This,ulSatelliteID,lpMCCSUPPRESSInfo) ) 

#define IEMSSatelliteInfo12_GetTCALInfo(This,ulSatelliteID,lpTCALInfo)	\
    ( (This)->lpVtbl -> GetTCALInfo(This,ulSatelliteID,lpTCALInfo) ) 

#define IEMSSatelliteInfo12_GetOrbitInfo(This,ulSatelliteID,lpOrbitInfo)	\
    ( (This)->lpVtbl -> GetOrbitInfo(This,ulSatelliteID,lpOrbitInfo) ) 

#define IEMSSatelliteInfo12_GetAudioInfo(This,ulSatelliteID,lpAudioInfo)	\
    ( (This)->lpVtbl -> GetAudioInfo(This,ulSatelliteID,lpAudioInfo) ) 

#define IEMSSatelliteInfo12_GetProcessInfo(This,ulSatelliteID,lpProcessInfo)	\
    ( (This)->lpVtbl -> GetProcessInfo(This,ulSatelliteID,lpProcessInfo) ) 

#define IEMSSatelliteInfo12_GetCollectInfo(This,ulSatelliteID,lpCollectInfo)	\
    ( (This)->lpVtbl -> GetCollectInfo(This,ulSatelliteID,lpCollectInfo) ) 

#define IEMSSatelliteInfo12_GetPassSchedulePriority(This,ulSatelliteID,lpulPriority)	\
    ( (This)->lpVtbl -> GetPassSchedulePriority(This,ulSatelliteID,lpulPriority) ) 

#define IEMSSatelliteInfo12_SetSarpCalibration(This,ulSatelliteID,timeRollover,dRefFreq)	\
    ( (This)->lpVtbl -> SetSarpCalibration(This,ulSatelliteID,timeRollover,dRefFreq) ) 

#define IEMSSatelliteInfo12_GetSarpCalibration(This,ulSatelliteID,lpTimeStamp,lpTimeRollover,lpdRefFreq)	\
    ( (This)->lpVtbl -> GetSarpCalibration(This,ulSatelliteID,lpTimeStamp,lpTimeRollover,lpdRefFreq) ) 

#define IEMSSatelliteInfo12_GetDownlinkFreq(This,ulSatelliteID,lpdDownlinkFreq)	\
    ( (This)->lpVtbl -> GetDownlinkFreq(This,ulSatelliteID,lpdDownlinkFreq) ) 


#define IEMSSatelliteInfo12_GetMCCSuppressInfoEx(This,ulSatelliteID,lpMCCSUPPRESSInfo)	\
    ( (This)->lpVtbl -> GetMCCSuppressInfoEx(This,ulSatelliteID,lpMCCSUPPRESSInfo) ) 

#define IEMSSatelliteInfo12_SetSarrCalibration(This,ulSatelliteID,i64TimeOffset,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarrCalibration(This,ulSatelliteID,i64TimeOffset,dFreqOffset) ) 

#define IEMSSatelliteInfo12_GetSarrCalibration(This,ulSatelliteID,lpTimeStamp,lpi64TimeOffset,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarrCalibration(This,ulSatelliteID,lpTimeStamp,lpi64TimeOffset,lpdFreqOffset) ) 

#define IEMSSatelliteInfo12_GetForwardingInfo(This,ulSatelliteID,lpForwardingInfo)	\
    ( (This)->lpVtbl -> GetForwardingInfo(This,ulSatelliteID,lpForwardingInfo) ) 


#define IEMSSatelliteInfo12_SetSatBehaviourMaxCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatBehaviourMaxCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo12_SetSatBehaviourCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatBehaviourCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo12_SetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour)	\
    ( (This)->lpVtbl -> SetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour) ) 

#define IEMSSatelliteInfo12_GetSatBehaviourMaxCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatBehaviourMaxCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo12_GetSatBehaviourCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatBehaviourCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo12_GetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour)	\
    ( (This)->lpVtbl -> GetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour) ) 

#define IEMSSatelliteInfo12_SetSatOrbitInfoMaxCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatOrbitInfoMaxCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo12_SetSatOrbitInfoCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatOrbitInfoCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo12_SetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit)	\
    ( (This)->lpVtbl -> SetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit) ) 

#define IEMSSatelliteInfo12_GetSatOrbitInfoMaxCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatOrbitInfoMaxCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo12_GetSatOrbitInfoCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatOrbitInfoCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo12_GetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit)	\
    ( (This)->lpVtbl -> GetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit) ) 


#define IEMSSatelliteInfo12_GetCalibCbcConfigData(This,ulSatelliteID,lpCalibCbcConfigData)	\
    ( (This)->lpVtbl -> GetCalibCbcConfigData(This,ulSatelliteID,lpCalibCbcConfigData) ) 

#define IEMSSatelliteInfo12_GetTcalConfigData(This,ulSatelliteID,lpTcalConfigData)	\
    ( (This)->lpVtbl -> GetTcalConfigData(This,ulSatelliteID,lpTcalConfigData) ) 

#define IEMSSatelliteInfo12_GetMI406ConfigData(This,ulSatID,lpMI406ConfigData)	\
    ( (This)->lpVtbl -> GetMI406ConfigData(This,ulSatID,lpMI406ConfigData) ) 

#define IEMSSatelliteInfo12_GetCalib406ConfigData(This,ulSatID,lpCalib406ConfigData)	\
    ( (This)->lpVtbl -> GetCalib406ConfigData(This,ulSatID,lpCalib406ConfigData) ) 

#define IEMSSatelliteInfo12_GetOrbitDetConfigData(This,ulSatID,lpOrbitDetConfigData)	\
    ( (This)->lpVtbl -> GetOrbitDetConfigData(This,ulSatID,lpOrbitDetConfigData) ) 

#define IEMSSatelliteInfo12_GetLocateCBCConfigData(This,ulSatID,lpLocateCbcConfigData)	\
    ( (This)->lpVtbl -> GetLocateCBCConfigData(This,ulSatID,lpLocateCbcConfigData) ) 

#define IEMSSatelliteInfo12_GetLocate406ConfigData(This,ulSatID,lpLocate406ConfigData)	\
    ( (This)->lpVtbl -> GetLocate406ConfigData(This,ulSatID,lpLocate406ConfigData) ) 


#define IEMSSatelliteInfo12_GetTestConfigData(This,ulSatID,lpTestConfigData)	\
    ( (This)->lpVtbl -> GetTestConfigData(This,ulSatID,lpTestConfigData) ) 


#define IEMSSatelliteInfo12_GetMI406ConfigData2(This,ulSatID,lpMI406ConfigData)	\
    ( (This)->lpVtbl -> GetMI406ConfigData2(This,ulSatID,lpMI406ConfigData) ) 


#define IEMSSatelliteInfo12_GetTcalConfigData2(This,ulSatID,lpTcalConfigData)	\
    ( (This)->lpVtbl -> GetTcalConfigData2(This,ulSatID,lpTcalConfigData) ) 

#define IEMSSatelliteInfo12_GetErrorEllipseConfigData(This,ulSatID,lpData)	\
    ( (This)->lpVtbl -> GetErrorEllipseConfigData(This,ulSatID,lpData) ) 

#define IEMSSatelliteInfo12_SetErrorEllipseConfigData(This,ulSatID,lpData)	\
    ( (This)->lpVtbl -> SetErrorEllipseConfigData(This,ulSatID,lpData) ) 


#define IEMSSatelliteInfo12_GetCalibCbcConfigData2(This,ulSatelliteID,lpCalibCbcConfigData)	\
    ( (This)->lpVtbl -> GetCalibCbcConfigData2(This,ulSatelliteID,lpCalibCbcConfigData) ) 


#define IEMSSatelliteInfo12_GetLocateCBCConfigData2(This,ulSatID,lpLocateCbcConfigData)	\
    ( (This)->lpVtbl -> GetLocateCBCConfigData2(This,ulSatID,lpLocateCbcConfigData) ) 

#define IEMSSatelliteInfo12_GetLocate406ConfigData2(This,ulSatID,lpLocate406ConfigData)	\
    ( (This)->lpVtbl -> GetLocate406ConfigData2(This,ulSatID,lpLocate406ConfigData) ) 


#define IEMSSatelliteInfo12_GetSARPCalibTimeThreshold(This,culSatID,pdThreshold)	\
    ( (This)->lpVtbl -> GetSARPCalibTimeThreshold(This,culSatID,pdThreshold) ) 

#define IEMSSatelliteInfo12_SetSARPCalibTimeThreshold(This,culSatID,cdThreshold)	\
    ( (This)->lpVtbl -> SetSARPCalibTimeThreshold(This,culSatID,cdThreshold) ) 

#define IEMSSatelliteInfo12_GetSARPUSOFreqThreshold(This,culSatID,pdThreshold)	\
    ( (This)->lpVtbl -> GetSARPUSOFreqThreshold(This,culSatID,pdThreshold) ) 

#define IEMSSatelliteInfo12_SetSARPUSOFreqThreshold(This,culSatID,cdThreshold)	\
    ( (This)->lpVtbl -> SetSARPUSOFreqThreshold(This,culSatID,cdThreshold) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEMSSatelliteInfo12_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSATINF_0000_0012 */
/* [local] */ 

typedef /* [unique] */ IEMSSatelliteInfo12 *LPEMSSATELLITEINFO12;



extern RPC_IF_HANDLE __MIDL_itf_EMSATINF_0000_0012_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSATINF_0000_0012_v0_0_s_ifspec;

#ifndef __IEMSSatelliteInfo13_INTERFACE_DEFINED__
#define __IEMSSatelliteInfo13_INTERFACE_DEFINED__

/* interface IEMSSatelliteInfo13 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSSatelliteInfo13;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9B683CBB-D88A-4e5b-8290-B1FC2CA60FB6")
    IEMSSatelliteInfo13 : public IEMSSatelliteInfo12
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Get406HistoryDataStartTime( 
            /* [in] */ const ULONG culSatID,
            /* [out] */ EMSTIME *lpStartTime) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Set406HistoryDataStartTime( 
            /* [in] */ const ULONG culSatID,
            /* [in] */ const EMSTIME startTime) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSatelliteInfo13Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEMSSatelliteInfo13 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEMSSatelliteInfo13 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigFlags )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigFlags )( 
            IEMSSatelliteInfo13 * This,
            /* [out] */ DWORD *lpdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *ReloadConfigData )( 
            IEMSSatelliteInfo13 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigValueA )( 
            IEMSSatelliteInfo13 * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [string][in] */ LPCSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigValueA )( 
            IEMSSatelliteInfo13 * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [length_is][size_is][out] */ unsigned char *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigValueW )( 
            IEMSSatelliteInfo13 * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [string][in] */ LPCWSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigValueW )( 
            IEMSSatelliteInfo13 * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [length_is][size_is][out] */ WCHAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE *GetName )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [length_is][size_is][out] */ BYTE *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG *pcbRead);
        
        HRESULT ( STDMETHODCALLTYPE *GetNoradID )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulNoradID);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatelliteID )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulNoradID,
            /* [out] */ ULONG *lpulSatelliteID);
        
        HRESULT ( STDMETHODCALLTYPE *GetFreqBandwidth )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LONG *lplBandwidth);
        
        HRESULT ( STDMETHODCALLTYPE *GetCaps )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulCapabilities);
        
        HRESULT ( STDMETHODCALLTYPE *Get406SignalData )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMS406SIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetCBCSignalData )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSCBCSIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetPDSSignalData )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSPDSSIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetRolloverPeriod )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64Period);
        
        HRESULT ( STDMETHODCALLTYPE *SetRolloverPeriod )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64Period);
        
        HRESULT ( STDMETHODCALLTYPE *GetRolloverTime )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeRollover);
        
        HRESULT ( STDMETHODCALLTYPE *SetRolloverTime )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIME timeRollover);
        
        HRESULT ( STDMETHODCALLTYPE *GetRefFreq )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreq);
        
        HRESULT ( STDMETHODCALLTYPE *SetRefFreq )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreq);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrFreqOffset )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrFreqOffset )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrTimeOffset )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrTimeOffset )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpFreqOffset )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpFreqOffset )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpTimeOffset )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpTimeOffset )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetPhaseDemodSetting )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulPhaseDemod);
        
        HRESULT ( STDMETHODCALLTYPE *GetMCCSuppressInfo )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGMCCSUPPRESS *lpMCCSUPPRESSInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTCALInfo )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGTCAL *lpTCALInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetOrbitInfo )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGORBIT *lpOrbitInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetAudioInfo )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGAUDIO *lpAudioInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetProcessInfo )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGPROCESS *lpProcessInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetCollectInfo )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGBOOLDATAPROP *lpCollectInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetPassSchedulePriority )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulPriority);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpCalibration )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIME timeRollover,
            /* [in] */ double dRefFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpCalibration )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeStamp,
            /* [out] */ EMSTIME *lpTimeRollover,
            /* [out] */ double *lpdRefFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetDownlinkFreq )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdDownlinkFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetMCCSuppressInfoEx )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGMCCSUPPRESSEX *lpMCCSUPPRESSInfo);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrCalibration )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrCalibration )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeStamp,
            /* [out] */ INT64 *lpi64TimeOffset,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetForwardingInfo )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGBOOLDATAPROP *lpForwardingInfo);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatBehaviourMaxCount )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatBehaviourCount )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatBehaviour )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [in] */ EMSSATBEHAVIOUR *lpBehaviour);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatBehaviourMaxCount )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatBehaviourCount )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatBehaviour )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [out] */ EMSSATBEHAVIOUR *lpBehaviour);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatOrbitInfoMaxCount )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatOrbitInfoCount )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatOrbitInfo )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [in] */ EMSSATORBITINFO *lpOrbit);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatOrbitInfoMaxCount )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatOrbitInfoCount )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatOrbitInfo )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [out] */ EMSSATORBITINFO *lpOrbit);
        
        HRESULT ( STDMETHODCALLTYPE *GetCalibCbcConfigData )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LPEMSCALIBCBCCONFIGDATA lpCalibCbcConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetTcalConfigData )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LPEMSTCALCONFIGDATA lpTcalConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetMI406ConfigData )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSMI406CONFIGDATA lpMI406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetCalib406ConfigData )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSCALIB406CONFIGDATA lpCalib406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetOrbitDetConfigData )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSORBITDETCONFIGDATA lpOrbitDetConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetLocateCBCConfigData )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSLOCATECBCCONFIGDATA lpLocateCbcConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetLocate406ConfigData )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSLOCATE406CONFIGDATA lpLocate406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetTestConfigData )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSTESTCONFIGDATA lpTestConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetMI406ConfigData2 )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSMI406CONFIGDATA2 lpMI406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetTcalConfigData2 )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSTCALCONFIGDATA2 lpTcalConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetErrorEllipseConfigData )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSEECONFIGDATA lpData);
        
        HRESULT ( STDMETHODCALLTYPE *SetErrorEllipseConfigData )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatID,
            /* [in] */ LPEMSEECONFIGDATA lpData);
        
        HRESULT ( STDMETHODCALLTYPE *GetCalibCbcConfigData2 )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LPEMSCALIBCBCCONFIGDATA2 lpCalibCbcConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetLocateCBCConfigData2 )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSLOCATECBCCONFIGDATA2 lpLocateCbcConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetLocate406ConfigData2 )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSLOCATE406CONFIGDATA2 lpLocate406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetSARPCalibTimeThreshold )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ const ULONG culSatID,
            /* [out] */ double *pdThreshold);
        
        HRESULT ( STDMETHODCALLTYPE *SetSARPCalibTimeThreshold )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ const ULONG culSatID,
            /* [in] */ const double cdThreshold);
        
        HRESULT ( STDMETHODCALLTYPE *GetSARPUSOFreqThreshold )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ const ULONG culSatID,
            /* [out] */ double *pdThreshold);
        
        HRESULT ( STDMETHODCALLTYPE *SetSARPUSOFreqThreshold )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ const ULONG culSatID,
            /* [in] */ const double cdThreshold);
        
        HRESULT ( STDMETHODCALLTYPE *Get406HistoryDataStartTime )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ const ULONG culSatID,
            /* [out] */ EMSTIME *lpStartTime);
        
        HRESULT ( STDMETHODCALLTYPE *Set406HistoryDataStartTime )( 
            IEMSSatelliteInfo13 * This,
            /* [in] */ const ULONG culSatID,
            /* [in] */ const EMSTIME startTime);
        
        END_INTERFACE
    } IEMSSatelliteInfo13Vtbl;

    interface IEMSSatelliteInfo13
    {
        CONST_VTBL struct IEMSSatelliteInfo13Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSatelliteInfo13_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEMSSatelliteInfo13_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEMSSatelliteInfo13_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEMSSatelliteInfo13_SetConfigFlags(This,dwFlags)	\
    ( (This)->lpVtbl -> SetConfigFlags(This,dwFlags) ) 

#define IEMSSatelliteInfo13_GetConfigFlags(This,lpdwFlags)	\
    ( (This)->lpVtbl -> GetConfigFlags(This,lpdwFlags) ) 

#define IEMSSatelliteInfo13_ReloadConfigData(This)	\
    ( (This)->lpVtbl -> ReloadConfigData(This) ) 

#define IEMSSatelliteInfo13_SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)	\
    ( (This)->lpVtbl -> SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue) ) 

#define IEMSSatelliteInfo13_GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    ( (This)->lpVtbl -> GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead) ) 

#define IEMSSatelliteInfo13_SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)	\
    ( (This)->lpVtbl -> SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue) ) 

#define IEMSSatelliteInfo13_GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    ( (This)->lpVtbl -> GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead) ) 


#define IEMSSatelliteInfo13_GetName(This,ulSatelliteID,pv,cb,pcbRead)	\
    ( (This)->lpVtbl -> GetName(This,ulSatelliteID,pv,cb,pcbRead) ) 

#define IEMSSatelliteInfo13_GetNoradID(This,ulSatelliteID,lpulNoradID)	\
    ( (This)->lpVtbl -> GetNoradID(This,ulSatelliteID,lpulNoradID) ) 

#define IEMSSatelliteInfo13_GetSatelliteID(This,ulNoradID,lpulSatelliteID)	\
    ( (This)->lpVtbl -> GetSatelliteID(This,ulNoradID,lpulSatelliteID) ) 

#define IEMSSatelliteInfo13_GetFreqBandwidth(This,ulSatelliteID,lplBandwidth)	\
    ( (This)->lpVtbl -> GetFreqBandwidth(This,ulSatelliteID,lplBandwidth) ) 

#define IEMSSatelliteInfo13_GetCaps(This,ulSatelliteID,lpulCapabilities)	\
    ( (This)->lpVtbl -> GetCaps(This,ulSatelliteID,lpulCapabilities) ) 

#define IEMSSatelliteInfo13_Get406SignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> Get406SignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo13_GetCBCSignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> GetCBCSignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo13_GetPDSSignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> GetPDSSignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo13_GetRolloverPeriod(This,ulSatelliteID,lpi64Period)	\
    ( (This)->lpVtbl -> GetRolloverPeriod(This,ulSatelliteID,lpi64Period) ) 

#define IEMSSatelliteInfo13_SetRolloverPeriod(This,ulSatelliteID,i64Period)	\
    ( (This)->lpVtbl -> SetRolloverPeriod(This,ulSatelliteID,i64Period) ) 

#define IEMSSatelliteInfo13_GetRolloverTime(This,ulSatelliteID,lpTimeRollover)	\
    ( (This)->lpVtbl -> GetRolloverTime(This,ulSatelliteID,lpTimeRollover) ) 

#define IEMSSatelliteInfo13_SetRolloverTime(This,ulSatelliteID,timeRollover)	\
    ( (This)->lpVtbl -> SetRolloverTime(This,ulSatelliteID,timeRollover) ) 

#define IEMSSatelliteInfo13_GetRefFreq(This,ulSatelliteID,lpdFreq)	\
    ( (This)->lpVtbl -> GetRefFreq(This,ulSatelliteID,lpdFreq) ) 

#define IEMSSatelliteInfo13_SetRefFreq(This,ulSatelliteID,dFreq)	\
    ( (This)->lpVtbl -> SetRefFreq(This,ulSatelliteID,dFreq) ) 

#define IEMSSatelliteInfo13_SetSarrFreqOffset(This,ulSatelliteID,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarrFreqOffset(This,ulSatelliteID,dFreqOffset) ) 

#define IEMSSatelliteInfo13_GetSarrFreqOffset(This,ulSatelliteID,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarrFreqOffset(This,ulSatelliteID,lpdFreqOffset) ) 

#define IEMSSatelliteInfo13_SetSarrTimeOffset(This,ulSatelliteID,i64TimeOffset)	\
    ( (This)->lpVtbl -> SetSarrTimeOffset(This,ulSatelliteID,i64TimeOffset) ) 

#define IEMSSatelliteInfo13_GetSarrTimeOffset(This,ulSatelliteID,lpi64TimeOffset)	\
    ( (This)->lpVtbl -> GetSarrTimeOffset(This,ulSatelliteID,lpi64TimeOffset) ) 

#define IEMSSatelliteInfo13_SetSarpFreqOffset(This,ulSatelliteID,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarpFreqOffset(This,ulSatelliteID,dFreqOffset) ) 

#define IEMSSatelliteInfo13_GetSarpFreqOffset(This,ulSatelliteID,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarpFreqOffset(This,ulSatelliteID,lpdFreqOffset) ) 

#define IEMSSatelliteInfo13_SetSarpTimeOffset(This,ulSatelliteID,i64TimeOffset)	\
    ( (This)->lpVtbl -> SetSarpTimeOffset(This,ulSatelliteID,i64TimeOffset) ) 

#define IEMSSatelliteInfo13_GetSarpTimeOffset(This,ulSatelliteID,lpi64TimeOffset)	\
    ( (This)->lpVtbl -> GetSarpTimeOffset(This,ulSatelliteID,lpi64TimeOffset) ) 


#define IEMSSatelliteInfo13_GetPhaseDemodSetting(This,ulSatelliteID,lpulPhaseDemod)	\
    ( (This)->lpVtbl -> GetPhaseDemodSetting(This,ulSatelliteID,lpulPhaseDemod) ) 


#define IEMSSatelliteInfo13_GetMCCSuppressInfo(This,ulSatelliteID,lpMCCSUPPRESSInfo)	\
    ( (This)->lpVtbl -> GetMCCSuppressInfo(This,ulSatelliteID,lpMCCSUPPRESSInfo) ) 

#define IEMSSatelliteInfo13_GetTCALInfo(This,ulSatelliteID,lpTCALInfo)	\
    ( (This)->lpVtbl -> GetTCALInfo(This,ulSatelliteID,lpTCALInfo) ) 

#define IEMSSatelliteInfo13_GetOrbitInfo(This,ulSatelliteID,lpOrbitInfo)	\
    ( (This)->lpVtbl -> GetOrbitInfo(This,ulSatelliteID,lpOrbitInfo) ) 

#define IEMSSatelliteInfo13_GetAudioInfo(This,ulSatelliteID,lpAudioInfo)	\
    ( (This)->lpVtbl -> GetAudioInfo(This,ulSatelliteID,lpAudioInfo) ) 

#define IEMSSatelliteInfo13_GetProcessInfo(This,ulSatelliteID,lpProcessInfo)	\
    ( (This)->lpVtbl -> GetProcessInfo(This,ulSatelliteID,lpProcessInfo) ) 

#define IEMSSatelliteInfo13_GetCollectInfo(This,ulSatelliteID,lpCollectInfo)	\
    ( (This)->lpVtbl -> GetCollectInfo(This,ulSatelliteID,lpCollectInfo) ) 

#define IEMSSatelliteInfo13_GetPassSchedulePriority(This,ulSatelliteID,lpulPriority)	\
    ( (This)->lpVtbl -> GetPassSchedulePriority(This,ulSatelliteID,lpulPriority) ) 

#define IEMSSatelliteInfo13_SetSarpCalibration(This,ulSatelliteID,timeRollover,dRefFreq)	\
    ( (This)->lpVtbl -> SetSarpCalibration(This,ulSatelliteID,timeRollover,dRefFreq) ) 

#define IEMSSatelliteInfo13_GetSarpCalibration(This,ulSatelliteID,lpTimeStamp,lpTimeRollover,lpdRefFreq)	\
    ( (This)->lpVtbl -> GetSarpCalibration(This,ulSatelliteID,lpTimeStamp,lpTimeRollover,lpdRefFreq) ) 

#define IEMSSatelliteInfo13_GetDownlinkFreq(This,ulSatelliteID,lpdDownlinkFreq)	\
    ( (This)->lpVtbl -> GetDownlinkFreq(This,ulSatelliteID,lpdDownlinkFreq) ) 


#define IEMSSatelliteInfo13_GetMCCSuppressInfoEx(This,ulSatelliteID,lpMCCSUPPRESSInfo)	\
    ( (This)->lpVtbl -> GetMCCSuppressInfoEx(This,ulSatelliteID,lpMCCSUPPRESSInfo) ) 

#define IEMSSatelliteInfo13_SetSarrCalibration(This,ulSatelliteID,i64TimeOffset,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarrCalibration(This,ulSatelliteID,i64TimeOffset,dFreqOffset) ) 

#define IEMSSatelliteInfo13_GetSarrCalibration(This,ulSatelliteID,lpTimeStamp,lpi64TimeOffset,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarrCalibration(This,ulSatelliteID,lpTimeStamp,lpi64TimeOffset,lpdFreqOffset) ) 

#define IEMSSatelliteInfo13_GetForwardingInfo(This,ulSatelliteID,lpForwardingInfo)	\
    ( (This)->lpVtbl -> GetForwardingInfo(This,ulSatelliteID,lpForwardingInfo) ) 


#define IEMSSatelliteInfo13_SetSatBehaviourMaxCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatBehaviourMaxCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo13_SetSatBehaviourCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatBehaviourCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo13_SetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour)	\
    ( (This)->lpVtbl -> SetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour) ) 

#define IEMSSatelliteInfo13_GetSatBehaviourMaxCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatBehaviourMaxCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo13_GetSatBehaviourCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatBehaviourCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo13_GetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour)	\
    ( (This)->lpVtbl -> GetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour) ) 

#define IEMSSatelliteInfo13_SetSatOrbitInfoMaxCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatOrbitInfoMaxCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo13_SetSatOrbitInfoCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatOrbitInfoCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo13_SetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit)	\
    ( (This)->lpVtbl -> SetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit) ) 

#define IEMSSatelliteInfo13_GetSatOrbitInfoMaxCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatOrbitInfoMaxCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo13_GetSatOrbitInfoCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatOrbitInfoCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo13_GetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit)	\
    ( (This)->lpVtbl -> GetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit) ) 


#define IEMSSatelliteInfo13_GetCalibCbcConfigData(This,ulSatelliteID,lpCalibCbcConfigData)	\
    ( (This)->lpVtbl -> GetCalibCbcConfigData(This,ulSatelliteID,lpCalibCbcConfigData) ) 

#define IEMSSatelliteInfo13_GetTcalConfigData(This,ulSatelliteID,lpTcalConfigData)	\
    ( (This)->lpVtbl -> GetTcalConfigData(This,ulSatelliteID,lpTcalConfigData) ) 

#define IEMSSatelliteInfo13_GetMI406ConfigData(This,ulSatID,lpMI406ConfigData)	\
    ( (This)->lpVtbl -> GetMI406ConfigData(This,ulSatID,lpMI406ConfigData) ) 

#define IEMSSatelliteInfo13_GetCalib406ConfigData(This,ulSatID,lpCalib406ConfigData)	\
    ( (This)->lpVtbl -> GetCalib406ConfigData(This,ulSatID,lpCalib406ConfigData) ) 

#define IEMSSatelliteInfo13_GetOrbitDetConfigData(This,ulSatID,lpOrbitDetConfigData)	\
    ( (This)->lpVtbl -> GetOrbitDetConfigData(This,ulSatID,lpOrbitDetConfigData) ) 

#define IEMSSatelliteInfo13_GetLocateCBCConfigData(This,ulSatID,lpLocateCbcConfigData)	\
    ( (This)->lpVtbl -> GetLocateCBCConfigData(This,ulSatID,lpLocateCbcConfigData) ) 

#define IEMSSatelliteInfo13_GetLocate406ConfigData(This,ulSatID,lpLocate406ConfigData)	\
    ( (This)->lpVtbl -> GetLocate406ConfigData(This,ulSatID,lpLocate406ConfigData) ) 


#define IEMSSatelliteInfo13_GetTestConfigData(This,ulSatID,lpTestConfigData)	\
    ( (This)->lpVtbl -> GetTestConfigData(This,ulSatID,lpTestConfigData) ) 


#define IEMSSatelliteInfo13_GetMI406ConfigData2(This,ulSatID,lpMI406ConfigData)	\
    ( (This)->lpVtbl -> GetMI406ConfigData2(This,ulSatID,lpMI406ConfigData) ) 


#define IEMSSatelliteInfo13_GetTcalConfigData2(This,ulSatID,lpTcalConfigData)	\
    ( (This)->lpVtbl -> GetTcalConfigData2(This,ulSatID,lpTcalConfigData) ) 

#define IEMSSatelliteInfo13_GetErrorEllipseConfigData(This,ulSatID,lpData)	\
    ( (This)->lpVtbl -> GetErrorEllipseConfigData(This,ulSatID,lpData) ) 

#define IEMSSatelliteInfo13_SetErrorEllipseConfigData(This,ulSatID,lpData)	\
    ( (This)->lpVtbl -> SetErrorEllipseConfigData(This,ulSatID,lpData) ) 


#define IEMSSatelliteInfo13_GetCalibCbcConfigData2(This,ulSatelliteID,lpCalibCbcConfigData)	\
    ( (This)->lpVtbl -> GetCalibCbcConfigData2(This,ulSatelliteID,lpCalibCbcConfigData) ) 


#define IEMSSatelliteInfo13_GetLocateCBCConfigData2(This,ulSatID,lpLocateCbcConfigData)	\
    ( (This)->lpVtbl -> GetLocateCBCConfigData2(This,ulSatID,lpLocateCbcConfigData) ) 

#define IEMSSatelliteInfo13_GetLocate406ConfigData2(This,ulSatID,lpLocate406ConfigData)	\
    ( (This)->lpVtbl -> GetLocate406ConfigData2(This,ulSatID,lpLocate406ConfigData) ) 


#define IEMSSatelliteInfo13_GetSARPCalibTimeThreshold(This,culSatID,pdThreshold)	\
    ( (This)->lpVtbl -> GetSARPCalibTimeThreshold(This,culSatID,pdThreshold) ) 

#define IEMSSatelliteInfo13_SetSARPCalibTimeThreshold(This,culSatID,cdThreshold)	\
    ( (This)->lpVtbl -> SetSARPCalibTimeThreshold(This,culSatID,cdThreshold) ) 

#define IEMSSatelliteInfo13_GetSARPUSOFreqThreshold(This,culSatID,pdThreshold)	\
    ( (This)->lpVtbl -> GetSARPUSOFreqThreshold(This,culSatID,pdThreshold) ) 

#define IEMSSatelliteInfo13_SetSARPUSOFreqThreshold(This,culSatID,cdThreshold)	\
    ( (This)->lpVtbl -> SetSARPUSOFreqThreshold(This,culSatID,cdThreshold) ) 


#define IEMSSatelliteInfo13_Get406HistoryDataStartTime(This,culSatID,lpStartTime)	\
    ( (This)->lpVtbl -> Get406HistoryDataStartTime(This,culSatID,lpStartTime) ) 

#define IEMSSatelliteInfo13_Set406HistoryDataStartTime(This,culSatID,startTime)	\
    ( (This)->lpVtbl -> Set406HistoryDataStartTime(This,culSatID,startTime) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEMSSatelliteInfo13_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSATINF_0000_0013 */
/* [local] */ 

typedef /* [unique] */ IEMSSatelliteInfo13 *LPEMSSATELLITEINFO13;



extern RPC_IF_HANDLE __MIDL_itf_EMSATINF_0000_0013_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSATINF_0000_0013_v0_0_s_ifspec;

#ifndef __IEMSSatelliteInfo14_INTERFACE_DEFINED__
#define __IEMSSatelliteInfo14_INTERFACE_DEFINED__

/* interface IEMSSatelliteInfo14 */
/* [unique][helpstring][uuid][object] */ 

typedef struct _tagEMSMI406CONFIGDATA3
    {
    EMSMI406CONFIGDATA2 configData2;
    double dQMSOutputRateMinutes;
    } 	EMSMI406CONFIGDATA3;

typedef struct _tagEMSMI406CONFIGDATA3 *LPEMSMI406CONFIGDATA3;


EXTERN_C const IID IID_IEMSSatelliteInfo14;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CE538E71-CA9D-43fe-BAB1-F188209645FF")
    IEMSSatelliteInfo14 : public IEMSSatelliteInfo13
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetMI406ConfigData3( 
            /* [in] */ const ULONG culSatID,
            /* [out] */ LPEMSMI406CONFIGDATA3 lpMI406ConfigData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSatelliteInfo14Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEMSSatelliteInfo14 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEMSSatelliteInfo14 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigFlags )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigFlags )( 
            IEMSSatelliteInfo14 * This,
            /* [out] */ DWORD *lpdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE *ReloadConfigData )( 
            IEMSSatelliteInfo14 * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigValueA )( 
            IEMSSatelliteInfo14 * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [string][in] */ LPCSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigValueA )( 
            IEMSSatelliteInfo14 * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [length_is][size_is][out] */ unsigned char *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE *SetConfigValueW )( 
            IEMSSatelliteInfo14 * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [string][in] */ LPCWSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE *GetConfigValueW )( 
            IEMSSatelliteInfo14 * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [length_is][size_is][out] */ WCHAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE *GetName )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [length_is][size_is][out] */ BYTE *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG *pcbRead);
        
        HRESULT ( STDMETHODCALLTYPE *GetNoradID )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulNoradID);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatelliteID )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulNoradID,
            /* [out] */ ULONG *lpulSatelliteID);
        
        HRESULT ( STDMETHODCALLTYPE *GetFreqBandwidth )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LONG *lplBandwidth);
        
        HRESULT ( STDMETHODCALLTYPE *GetCaps )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulCapabilities);
        
        HRESULT ( STDMETHODCALLTYPE *Get406SignalData )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMS406SIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetCBCSignalData )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSCBCSIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetPDSSignalData )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSPDSSIGNALDATA *lpSignalData);
        
        HRESULT ( STDMETHODCALLTYPE *GetRolloverPeriod )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64Period);
        
        HRESULT ( STDMETHODCALLTYPE *SetRolloverPeriod )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64Period);
        
        HRESULT ( STDMETHODCALLTYPE *GetRolloverTime )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeRollover);
        
        HRESULT ( STDMETHODCALLTYPE *SetRolloverTime )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIME timeRollover);
        
        HRESULT ( STDMETHODCALLTYPE *GetRefFreq )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreq);
        
        HRESULT ( STDMETHODCALLTYPE *SetRefFreq )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreq);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrFreqOffset )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrFreqOffset )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrTimeOffset )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrTimeOffset )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpFreqOffset )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpFreqOffset )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpTimeOffset )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpTimeOffset )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ INT64 *lpi64TimeOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetPhaseDemodSetting )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulPhaseDemod);
        
        HRESULT ( STDMETHODCALLTYPE *GetMCCSuppressInfo )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGMCCSUPPRESS *lpMCCSUPPRESSInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTCALInfo )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGTCAL *lpTCALInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetOrbitInfo )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGORBIT *lpOrbitInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetAudioInfo )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGAUDIO *lpAudioInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetProcessInfo )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGPROCESS *lpProcessInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetCollectInfo )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGBOOLDATAPROP *lpCollectInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetPassSchedulePriority )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ ULONG *lpulPriority);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarpCalibration )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ EMSTIME timeRollover,
            /* [in] */ double dRefFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarpCalibration )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeStamp,
            /* [out] */ EMSTIME *lpTimeRollover,
            /* [out] */ double *lpdRefFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetDownlinkFreq )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ double *lpdDownlinkFreq);
        
        HRESULT ( STDMETHODCALLTYPE *GetMCCSuppressInfoEx )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGMCCSUPPRESSEX *lpMCCSUPPRESSInfo);
        
        HRESULT ( STDMETHODCALLTYPE *SetSarrCalibration )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ INT64 i64TimeOffset,
            /* [in] */ double dFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetSarrCalibration )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSTIME *lpTimeStamp,
            /* [out] */ INT64 *lpi64TimeOffset,
            /* [out] */ double *lpdFreqOffset);
        
        HRESULT ( STDMETHODCALLTYPE *GetForwardingInfo )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ EMSSATCONFIGBOOLDATAPROP *lpForwardingInfo);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatBehaviourMaxCount )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatBehaviourCount )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatBehaviour )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [in] */ EMSSATBEHAVIOUR *lpBehaviour);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatBehaviourMaxCount )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatBehaviourCount )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatBehaviour )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [out] */ EMSSATBEHAVIOUR *lpBehaviour);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatOrbitInfoMaxCount )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatOrbitInfoCount )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wCount);
        
        HRESULT ( STDMETHODCALLTYPE *SetSatOrbitInfo )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [in] */ EMSSATORBITINFO *lpOrbit);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatOrbitInfoMaxCount )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatOrbitInfoCount )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ WORD *lpwCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetSatOrbitInfo )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [in] */ WORD wIndex,
            /* [out] */ EMSSATORBITINFO *lpOrbit);
        
        HRESULT ( STDMETHODCALLTYPE *GetCalibCbcConfigData )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LPEMSCALIBCBCCONFIGDATA lpCalibCbcConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetTcalConfigData )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LPEMSTCALCONFIGDATA lpTcalConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetMI406ConfigData )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSMI406CONFIGDATA lpMI406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetCalib406ConfigData )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSCALIB406CONFIGDATA lpCalib406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetOrbitDetConfigData )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSORBITDETCONFIGDATA lpOrbitDetConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetLocateCBCConfigData )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSLOCATECBCCONFIGDATA lpLocateCbcConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetLocate406ConfigData )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSLOCATE406CONFIGDATA lpLocate406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetTestConfigData )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSTESTCONFIGDATA lpTestConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetMI406ConfigData2 )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSMI406CONFIGDATA2 lpMI406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetTcalConfigData2 )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSTCALCONFIGDATA2 lpTcalConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetErrorEllipseConfigData )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSEECONFIGDATA lpData);
        
        HRESULT ( STDMETHODCALLTYPE *SetErrorEllipseConfigData )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatID,
            /* [in] */ LPEMSEECONFIGDATA lpData);
        
        HRESULT ( STDMETHODCALLTYPE *GetCalibCbcConfigData2 )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatelliteID,
            /* [out] */ LPEMSCALIBCBCCONFIGDATA2 lpCalibCbcConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetLocateCBCConfigData2 )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSLOCATECBCCONFIGDATA2 lpLocateCbcConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetLocate406ConfigData2 )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ ULONG ulSatID,
            /* [out] */ LPEMSLOCATE406CONFIGDATA2 lpLocate406ConfigData);
        
        HRESULT ( STDMETHODCALLTYPE *GetSARPCalibTimeThreshold )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ const ULONG culSatID,
            /* [out] */ double *pdThreshold);
        
        HRESULT ( STDMETHODCALLTYPE *SetSARPCalibTimeThreshold )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ const ULONG culSatID,
            /* [in] */ const double cdThreshold);
        
        HRESULT ( STDMETHODCALLTYPE *GetSARPUSOFreqThreshold )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ const ULONG culSatID,
            /* [out] */ double *pdThreshold);
        
        HRESULT ( STDMETHODCALLTYPE *SetSARPUSOFreqThreshold )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ const ULONG culSatID,
            /* [in] */ const double cdThreshold);
        
        HRESULT ( STDMETHODCALLTYPE *Get406HistoryDataStartTime )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ const ULONG culSatID,
            /* [out] */ EMSTIME *lpStartTime);
        
        HRESULT ( STDMETHODCALLTYPE *Set406HistoryDataStartTime )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ const ULONG culSatID,
            /* [in] */ const EMSTIME startTime);
        
        HRESULT ( STDMETHODCALLTYPE *GetMI406ConfigData3 )( 
            IEMSSatelliteInfo14 * This,
            /* [in] */ const ULONG culSatID,
            /* [out] */ LPEMSMI406CONFIGDATA3 lpMI406ConfigData);
        
        END_INTERFACE
    } IEMSSatelliteInfo14Vtbl;

    interface IEMSSatelliteInfo14
    {
        CONST_VTBL struct IEMSSatelliteInfo14Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSatelliteInfo14_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEMSSatelliteInfo14_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEMSSatelliteInfo14_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEMSSatelliteInfo14_SetConfigFlags(This,dwFlags)	\
    ( (This)->lpVtbl -> SetConfigFlags(This,dwFlags) ) 

#define IEMSSatelliteInfo14_GetConfigFlags(This,lpdwFlags)	\
    ( (This)->lpVtbl -> GetConfigFlags(This,lpdwFlags) ) 

#define IEMSSatelliteInfo14_ReloadConfigData(This)	\
    ( (This)->lpVtbl -> ReloadConfigData(This) ) 

#define IEMSSatelliteInfo14_SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)	\
    ( (This)->lpVtbl -> SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue) ) 

#define IEMSSatelliteInfo14_GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    ( (This)->lpVtbl -> GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead) ) 

#define IEMSSatelliteInfo14_SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)	\
    ( (This)->lpVtbl -> SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue) ) 

#define IEMSSatelliteInfo14_GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    ( (This)->lpVtbl -> GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead) ) 


#define IEMSSatelliteInfo14_GetName(This,ulSatelliteID,pv,cb,pcbRead)	\
    ( (This)->lpVtbl -> GetName(This,ulSatelliteID,pv,cb,pcbRead) ) 

#define IEMSSatelliteInfo14_GetNoradID(This,ulSatelliteID,lpulNoradID)	\
    ( (This)->lpVtbl -> GetNoradID(This,ulSatelliteID,lpulNoradID) ) 

#define IEMSSatelliteInfo14_GetSatelliteID(This,ulNoradID,lpulSatelliteID)	\
    ( (This)->lpVtbl -> GetSatelliteID(This,ulNoradID,lpulSatelliteID) ) 

#define IEMSSatelliteInfo14_GetFreqBandwidth(This,ulSatelliteID,lplBandwidth)	\
    ( (This)->lpVtbl -> GetFreqBandwidth(This,ulSatelliteID,lplBandwidth) ) 

#define IEMSSatelliteInfo14_GetCaps(This,ulSatelliteID,lpulCapabilities)	\
    ( (This)->lpVtbl -> GetCaps(This,ulSatelliteID,lpulCapabilities) ) 

#define IEMSSatelliteInfo14_Get406SignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> Get406SignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo14_GetCBCSignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> GetCBCSignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo14_GetPDSSignalData(This,ulSatelliteID,lpSignalData)	\
    ( (This)->lpVtbl -> GetPDSSignalData(This,ulSatelliteID,lpSignalData) ) 

#define IEMSSatelliteInfo14_GetRolloverPeriod(This,ulSatelliteID,lpi64Period)	\
    ( (This)->lpVtbl -> GetRolloverPeriod(This,ulSatelliteID,lpi64Period) ) 

#define IEMSSatelliteInfo14_SetRolloverPeriod(This,ulSatelliteID,i64Period)	\
    ( (This)->lpVtbl -> SetRolloverPeriod(This,ulSatelliteID,i64Period) ) 

#define IEMSSatelliteInfo14_GetRolloverTime(This,ulSatelliteID,lpTimeRollover)	\
    ( (This)->lpVtbl -> GetRolloverTime(This,ulSatelliteID,lpTimeRollover) ) 

#define IEMSSatelliteInfo14_SetRolloverTime(This,ulSatelliteID,timeRollover)	\
    ( (This)->lpVtbl -> SetRolloverTime(This,ulSatelliteID,timeRollover) ) 

#define IEMSSatelliteInfo14_GetRefFreq(This,ulSatelliteID,lpdFreq)	\
    ( (This)->lpVtbl -> GetRefFreq(This,ulSatelliteID,lpdFreq) ) 

#define IEMSSatelliteInfo14_SetRefFreq(This,ulSatelliteID,dFreq)	\
    ( (This)->lpVtbl -> SetRefFreq(This,ulSatelliteID,dFreq) ) 

#define IEMSSatelliteInfo14_SetSarrFreqOffset(This,ulSatelliteID,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarrFreqOffset(This,ulSatelliteID,dFreqOffset) ) 

#define IEMSSatelliteInfo14_GetSarrFreqOffset(This,ulSatelliteID,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarrFreqOffset(This,ulSatelliteID,lpdFreqOffset) ) 

#define IEMSSatelliteInfo14_SetSarrTimeOffset(This,ulSatelliteID,i64TimeOffset)	\
    ( (This)->lpVtbl -> SetSarrTimeOffset(This,ulSatelliteID,i64TimeOffset) ) 

#define IEMSSatelliteInfo14_GetSarrTimeOffset(This,ulSatelliteID,lpi64TimeOffset)	\
    ( (This)->lpVtbl -> GetSarrTimeOffset(This,ulSatelliteID,lpi64TimeOffset) ) 

#define IEMSSatelliteInfo14_SetSarpFreqOffset(This,ulSatelliteID,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarpFreqOffset(This,ulSatelliteID,dFreqOffset) ) 

#define IEMSSatelliteInfo14_GetSarpFreqOffset(This,ulSatelliteID,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarpFreqOffset(This,ulSatelliteID,lpdFreqOffset) ) 

#define IEMSSatelliteInfo14_SetSarpTimeOffset(This,ulSatelliteID,i64TimeOffset)	\
    ( (This)->lpVtbl -> SetSarpTimeOffset(This,ulSatelliteID,i64TimeOffset) ) 

#define IEMSSatelliteInfo14_GetSarpTimeOffset(This,ulSatelliteID,lpi64TimeOffset)	\
    ( (This)->lpVtbl -> GetSarpTimeOffset(This,ulSatelliteID,lpi64TimeOffset) ) 


#define IEMSSatelliteInfo14_GetPhaseDemodSetting(This,ulSatelliteID,lpulPhaseDemod)	\
    ( (This)->lpVtbl -> GetPhaseDemodSetting(This,ulSatelliteID,lpulPhaseDemod) ) 


#define IEMSSatelliteInfo14_GetMCCSuppressInfo(This,ulSatelliteID,lpMCCSUPPRESSInfo)	\
    ( (This)->lpVtbl -> GetMCCSuppressInfo(This,ulSatelliteID,lpMCCSUPPRESSInfo) ) 

#define IEMSSatelliteInfo14_GetTCALInfo(This,ulSatelliteID,lpTCALInfo)	\
    ( (This)->lpVtbl -> GetTCALInfo(This,ulSatelliteID,lpTCALInfo) ) 

#define IEMSSatelliteInfo14_GetOrbitInfo(This,ulSatelliteID,lpOrbitInfo)	\
    ( (This)->lpVtbl -> GetOrbitInfo(This,ulSatelliteID,lpOrbitInfo) ) 

#define IEMSSatelliteInfo14_GetAudioInfo(This,ulSatelliteID,lpAudioInfo)	\
    ( (This)->lpVtbl -> GetAudioInfo(This,ulSatelliteID,lpAudioInfo) ) 

#define IEMSSatelliteInfo14_GetProcessInfo(This,ulSatelliteID,lpProcessInfo)	\
    ( (This)->lpVtbl -> GetProcessInfo(This,ulSatelliteID,lpProcessInfo) ) 

#define IEMSSatelliteInfo14_GetCollectInfo(This,ulSatelliteID,lpCollectInfo)	\
    ( (This)->lpVtbl -> GetCollectInfo(This,ulSatelliteID,lpCollectInfo) ) 

#define IEMSSatelliteInfo14_GetPassSchedulePriority(This,ulSatelliteID,lpulPriority)	\
    ( (This)->lpVtbl -> GetPassSchedulePriority(This,ulSatelliteID,lpulPriority) ) 

#define IEMSSatelliteInfo14_SetSarpCalibration(This,ulSatelliteID,timeRollover,dRefFreq)	\
    ( (This)->lpVtbl -> SetSarpCalibration(This,ulSatelliteID,timeRollover,dRefFreq) ) 

#define IEMSSatelliteInfo14_GetSarpCalibration(This,ulSatelliteID,lpTimeStamp,lpTimeRollover,lpdRefFreq)	\
    ( (This)->lpVtbl -> GetSarpCalibration(This,ulSatelliteID,lpTimeStamp,lpTimeRollover,lpdRefFreq) ) 

#define IEMSSatelliteInfo14_GetDownlinkFreq(This,ulSatelliteID,lpdDownlinkFreq)	\
    ( (This)->lpVtbl -> GetDownlinkFreq(This,ulSatelliteID,lpdDownlinkFreq) ) 


#define IEMSSatelliteInfo14_GetMCCSuppressInfoEx(This,ulSatelliteID,lpMCCSUPPRESSInfo)	\
    ( (This)->lpVtbl -> GetMCCSuppressInfoEx(This,ulSatelliteID,lpMCCSUPPRESSInfo) ) 

#define IEMSSatelliteInfo14_SetSarrCalibration(This,ulSatelliteID,i64TimeOffset,dFreqOffset)	\
    ( (This)->lpVtbl -> SetSarrCalibration(This,ulSatelliteID,i64TimeOffset,dFreqOffset) ) 

#define IEMSSatelliteInfo14_GetSarrCalibration(This,ulSatelliteID,lpTimeStamp,lpi64TimeOffset,lpdFreqOffset)	\
    ( (This)->lpVtbl -> GetSarrCalibration(This,ulSatelliteID,lpTimeStamp,lpi64TimeOffset,lpdFreqOffset) ) 

#define IEMSSatelliteInfo14_GetForwardingInfo(This,ulSatelliteID,lpForwardingInfo)	\
    ( (This)->lpVtbl -> GetForwardingInfo(This,ulSatelliteID,lpForwardingInfo) ) 


#define IEMSSatelliteInfo14_SetSatBehaviourMaxCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatBehaviourMaxCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo14_SetSatBehaviourCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatBehaviourCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo14_SetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour)	\
    ( (This)->lpVtbl -> SetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour) ) 

#define IEMSSatelliteInfo14_GetSatBehaviourMaxCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatBehaviourMaxCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo14_GetSatBehaviourCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatBehaviourCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo14_GetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour)	\
    ( (This)->lpVtbl -> GetSatBehaviour(This,ulSatelliteID,wIndex,lpBehaviour) ) 

#define IEMSSatelliteInfo14_SetSatOrbitInfoMaxCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatOrbitInfoMaxCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo14_SetSatOrbitInfoCount(This,ulSatelliteID,wCount)	\
    ( (This)->lpVtbl -> SetSatOrbitInfoCount(This,ulSatelliteID,wCount) ) 

#define IEMSSatelliteInfo14_SetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit)	\
    ( (This)->lpVtbl -> SetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit) ) 

#define IEMSSatelliteInfo14_GetSatOrbitInfoMaxCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatOrbitInfoMaxCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo14_GetSatOrbitInfoCount(This,ulSatelliteID,lpwCount)	\
    ( (This)->lpVtbl -> GetSatOrbitInfoCount(This,ulSatelliteID,lpwCount) ) 

#define IEMSSatelliteInfo14_GetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit)	\
    ( (This)->lpVtbl -> GetSatOrbitInfo(This,ulSatelliteID,wIndex,lpOrbit) ) 


#define IEMSSatelliteInfo14_GetCalibCbcConfigData(This,ulSatelliteID,lpCalibCbcConfigData)	\
    ( (This)->lpVtbl -> GetCalibCbcConfigData(This,ulSatelliteID,lpCalibCbcConfigData) ) 

#define IEMSSatelliteInfo14_GetTcalConfigData(This,ulSatelliteID,lpTcalConfigData)	\
    ( (This)->lpVtbl -> GetTcalConfigData(This,ulSatelliteID,lpTcalConfigData) ) 

#define IEMSSatelliteInfo14_GetMI406ConfigData(This,ulSatID,lpMI406ConfigData)	\
    ( (This)->lpVtbl -> GetMI406ConfigData(This,ulSatID,lpMI406ConfigData) ) 

#define IEMSSatelliteInfo14_GetCalib406ConfigData(This,ulSatID,lpCalib406ConfigData)	\
    ( (This)->lpVtbl -> GetCalib406ConfigData(This,ulSatID,lpCalib406ConfigData) ) 

#define IEMSSatelliteInfo14_GetOrbitDetConfigData(This,ulSatID,lpOrbitDetConfigData)	\
    ( (This)->lpVtbl -> GetOrbitDetConfigData(This,ulSatID,lpOrbitDetConfigData) ) 

#define IEMSSatelliteInfo14_GetLocateCBCConfigData(This,ulSatID,lpLocateCbcConfigData)	\
    ( (This)->lpVtbl -> GetLocateCBCConfigData(This,ulSatID,lpLocateCbcConfigData) ) 

#define IEMSSatelliteInfo14_GetLocate406ConfigData(This,ulSatID,lpLocate406ConfigData)	\
    ( (This)->lpVtbl -> GetLocate406ConfigData(This,ulSatID,lpLocate406ConfigData) ) 


#define IEMSSatelliteInfo14_GetTestConfigData(This,ulSatID,lpTestConfigData)	\
    ( (This)->lpVtbl -> GetTestConfigData(This,ulSatID,lpTestConfigData) ) 


#define IEMSSatelliteInfo14_GetMI406ConfigData2(This,ulSatID,lpMI406ConfigData)	\
    ( (This)->lpVtbl -> GetMI406ConfigData2(This,ulSatID,lpMI406ConfigData) ) 


#define IEMSSatelliteInfo14_GetTcalConfigData2(This,ulSatID,lpTcalConfigData)	\
    ( (This)->lpVtbl -> GetTcalConfigData2(This,ulSatID,lpTcalConfigData) ) 

#define IEMSSatelliteInfo14_GetErrorEllipseConfigData(This,ulSatID,lpData)	\
    ( (This)->lpVtbl -> GetErrorEllipseConfigData(This,ulSatID,lpData) ) 

#define IEMSSatelliteInfo14_SetErrorEllipseConfigData(This,ulSatID,lpData)	\
    ( (This)->lpVtbl -> SetErrorEllipseConfigData(This,ulSatID,lpData) ) 


#define IEMSSatelliteInfo14_GetCalibCbcConfigData2(This,ulSatelliteID,lpCalibCbcConfigData)	\
    ( (This)->lpVtbl -> GetCalibCbcConfigData2(This,ulSatelliteID,lpCalibCbcConfigData) ) 


#define IEMSSatelliteInfo14_GetLocateCBCConfigData2(This,ulSatID,lpLocateCbcConfigData)	\
    ( (This)->lpVtbl -> GetLocateCBCConfigData2(This,ulSatID,lpLocateCbcConfigData) ) 

#define IEMSSatelliteInfo14_GetLocate406ConfigData2(This,ulSatID,lpLocate406ConfigData)	\
    ( (This)->lpVtbl -> GetLocate406ConfigData2(This,ulSatID,lpLocate406ConfigData) ) 


#define IEMSSatelliteInfo14_GetSARPCalibTimeThreshold(This,culSatID,pdThreshold)	\
    ( (This)->lpVtbl -> GetSARPCalibTimeThreshold(This,culSatID,pdThreshold) ) 

#define IEMSSatelliteInfo14_SetSARPCalibTimeThreshold(This,culSatID,cdThreshold)	\
    ( (This)->lpVtbl -> SetSARPCalibTimeThreshold(This,culSatID,cdThreshold) ) 

#define IEMSSatelliteInfo14_GetSARPUSOFreqThreshold(This,culSatID,pdThreshold)	\
    ( (This)->lpVtbl -> GetSARPUSOFreqThreshold(This,culSatID,pdThreshold) ) 

#define IEMSSatelliteInfo14_SetSARPUSOFreqThreshold(This,culSatID,cdThreshold)	\
    ( (This)->lpVtbl -> SetSARPUSOFreqThreshold(This,culSatID,cdThreshold) ) 


#define IEMSSatelliteInfo14_Get406HistoryDataStartTime(This,culSatID,lpStartTime)	\
    ( (This)->lpVtbl -> Get406HistoryDataStartTime(This,culSatID,lpStartTime) ) 

#define IEMSSatelliteInfo14_Set406HistoryDataStartTime(This,culSatID,startTime)	\
    ( (This)->lpVtbl -> Set406HistoryDataStartTime(This,culSatID,startTime) ) 


#define IEMSSatelliteInfo14_GetMI406ConfigData3(This,culSatID,lpMI406ConfigData)	\
    ( (This)->lpVtbl -> GetMI406ConfigData3(This,culSatID,lpMI406ConfigData) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEMSSatelliteInfo14_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSATINF_0000_0014 */
/* [local] */ 

typedef /* [unique] */ IEMSSatelliteInfo14 *LPEMSSATELLITEINFO14;



extern RPC_IF_HANDLE __MIDL_itf_EMSATINF_0000_0014_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSATINF_0000_0014_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


