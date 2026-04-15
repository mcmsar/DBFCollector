/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Jun 03 15:43:51 2010
 */
/* Compiler settings for ..\common\Include\EMSITEIF.IDL:
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

#ifndef __EMSITEIF_h__
#define __EMSITEIF_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSSiteInfo_FWD_DEFINED__
#define __IEMSSiteInfo_FWD_DEFINED__
typedef interface IEMSSiteInfo IEMSSiteInfo;
#endif 	/* __IEMSSiteInfo_FWD_DEFINED__ */


#ifndef __IEMSOffline_FWD_DEFINED__
#define __IEMSOffline_FWD_DEFINED__
typedef interface IEMSOffline IEMSOffline;
#endif 	/* __IEMSOffline_FWD_DEFINED__ */


#ifndef __IEMSCollectorPPS_FWD_DEFINED__
#define __IEMSCollectorPPS_FWD_DEFINED__
typedef interface IEMSCollectorPPS IEMSCollectorPPS;
#endif 	/* __IEMSCollectorPPS_FWD_DEFINED__ */


#ifndef __IEMSDestinationsInfo_FWD_DEFINED__
#define __IEMSDestinationsInfo_FWD_DEFINED__
typedef interface IEMSDestinationsInfo IEMSDestinationsInfo;
#endif 	/* __IEMSDestinationsInfo_FWD_DEFINED__ */


#ifndef __IEMSDestinationsInfo3_FWD_DEFINED__
#define __IEMSDestinationsInfo3_FWD_DEFINED__
typedef interface IEMSDestinationsInfo3 IEMSDestinationsInfo3;
#endif 	/* __IEMSDestinationsInfo3_FWD_DEFINED__ */


#ifndef __IEMSSystemTestSettings_FWD_DEFINED__
#define __IEMSSystemTestSettings_FWD_DEFINED__
typedef interface IEMSSystemTestSettings IEMSSystemTestSettings;
#endif 	/* __IEMSSystemTestSettings_FWD_DEFINED__ */


#ifndef __IEMSSiteType_FWD_DEFINED__
#define __IEMSSiteType_FWD_DEFINED__
typedef interface IEMSSiteType IEMSSiteType;
#endif 	/* __IEMSSiteType_FWD_DEFINED__ */


#ifndef __IEMSMsgArchiveConfig_FWD_DEFINED__
#define __IEMSMsgArchiveConfig_FWD_DEFINED__
typedef interface IEMSMsgArchiveConfig IEMSMsgArchiveConfig;
#endif 	/* __IEMSMsgArchiveConfig_FWD_DEFINED__ */


#ifndef __IEMSSitMsgProperties_FWD_DEFINED__
#define __IEMSSitMsgProperties_FWD_DEFINED__
typedef interface IEMSSitMsgProperties IEMSSitMsgProperties;
#endif 	/* __IEMSSitMsgProperties_FWD_DEFINED__ */


#ifndef __IEMSAutoSendSit_FWD_DEFINED__
#define __IEMSAutoSendSit_FWD_DEFINED__
typedef interface IEMSAutoSendSit IEMSAutoSendSit;
#endif 	/* __IEMSAutoSendSit_FWD_DEFINED__ */


#ifndef __IEMSRouteInfo_FWD_DEFINED__
#define __IEMSRouteInfo_FWD_DEFINED__
typedef interface IEMSRouteInfo IEMSRouteInfo;
#endif 	/* __IEMSRouteInfo_FWD_DEFINED__ */


#ifndef __IEMSRouteInfo2_FWD_DEFINED__
#define __IEMSRouteInfo2_FWD_DEFINED__
typedef interface IEMSRouteInfo2 IEMSRouteInfo2;
#endif 	/* __IEMSRouteInfo2_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "emsicfg.h"
#include "netconnmgr.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_EMSITEIF_0000 */
/* [local] */ 

 
#include "emserror.h"
 
// {47C5A1B1-B987-11d5-8C6D-009027912866}
DEFINE_GUID( CLSID_EMSSiteInfo, 0x47c5a1b1, 0xb987, 0x11d5, 0x8c, 0x6d, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);
// {C28EB166-045F-4d3f-AABB-D9E3A83D3529}
DEFINE_GUID( IID_IEMSSiteInfo, 0xc28eb166, 0x45f, 0x4d3f, 0xaa, 0xbb, 0xd9, 0xe3, 0xa8, 0x3d, 0x35, 0x29);
// {3FD55374-41F4-4f64-96BE-CC1F4EC1202A}
DEFINE_GUID( IID_IEMSDestinationsInfo, 0x3fd55374, 0x41f4, 0x4f64, 0x96, 0xbe, 0xcc, 0x1f, 0x4e, 0xc1, 0x20, 0x2a);
// {520F4DFC-FCE4-45d0-BDB6-46025FBA891C}
DEFINE_GUID( IID_IEMSDestinationsInfo3, 0x520f4dfc, 0xfce4, 0x45d0, 0xbd, 0xb6, 0x46, 0x2, 0x5f, 0xba, 0x89, 0x1c);
// {48EBD324-2101-4572-8026-4A0DC439DC36}
DEFINE_GUID( IID_IEMSSystemTestSettings, 0x48ebd324, 0x2101, 0x4572, 0x80, 0x26, 0x4a, 0xd, 0xc4, 0x39, 0xdc, 0x36);
 
// {B73D76CD-2160-44ff-9AC5-E08EA6AF207D}
DEFINE_GUID( IID_IEMSSiteType, 0xb73d76cd, 0x2160, 0x44ff, 0x9a, 0xc5, 0xe0, 0x8e, 0xa6, 0xaf, 0x20, 0x7d );
// {6435FB6A-A496-460d-9830-13FB88CCA195}
DEFINE_GUID( IID_IEMSMsgArchiveConfig, 0x6435fb6a, 0xa496, 0x460d, 0x98, 0x30, 0x13, 0xfb, 0x88, 0xcc, 0xa1, 0x95);
// {9C603A34-0C3C-4847-8A61-E657A2D10B89}
DEFINE_GUID( IID_IEMSSitMsgProperties, 0x9c603a34, 0xc3c, 0x4847, 0x8a, 0x61, 0xe6, 0x57, 0xa2, 0xd1, 0xb, 0x89);
// {2B02EDF5-880A-4555-B67E-577BBF157220}
DEFINE_GUID(IID_IEMSAutoSendSit, 0x2b02edf5, 0x880a, 0x4555, 0xb6, 0x7e, 0x57, 0x7b, 0xbf, 0x15, 0x72, 0x20);
// {9E586623-5E8A-48d0-B650-966FCA6B4221}
DEFINE_GUID( IID_IEMSRouteInfo, 0x9e586623, 0x5e8a, 0x48d0, 0xb6, 0x50, 0x96, 0x6f, 0xca, 0x6b, 0x42, 0x21);
// {3A3D750F-E940-4abf-93C7-93E2A63C254D}
DEFINE_GUID(IID_IEMSRouteInfo2, 0x3a3d750f, 0xe940, 0x4abf, 0x93, 0xc7, 0x93, 0xe2, 0xa6, 0x3c, 0x25, 0x4d);
// {7CE97B78-51F2-4d81-BAC3-360B3F5B36D4}
DEFINE_GUID(IID_IEMSOffline, 0x7ce97b78, 0x51f2, 0x4d81, 0xba, 0xc3, 0x36, 0xb, 0x3f, 0x5b, 0x36, 0xd4);
// {7A92B265-E833-4403-B937-5CACAEDF51CE}
DEFINE_GUID(IID_IEMSCollectorPPS, 0x7a92b265, 0xe833, 0x4403, 0xb9, 0x37, 0x5c, 0xac, 0xae, 0xdf, 0x51, 0xce);
#define EMS_MAX_SERVICES		  (32)
#define EMS_MAX_ROUTES			  (256)
#define EMS_MAX_SOURCES			  (32)
#define EMS_MAX_DESTINATIONS	  (32)
#define EMS_MAX_TRANS_TABLE_NAMELEN	  (32)
#define EMS_MAX_TRANS_TABLE_NUM  (32)
#define EMS_MAX_TRANS_TABLE_LEN  (32)
#define EMS_MAX_TRANS_RECORD_LEN  (10)
#define EMS_SERVICE_NAME_LENGTH (32)
#define EMS_ROUTE_NAME_LENGTH  (32)
 
// dwFlags 
#define EMS_SERVICE_FLAG_START  (0x1)
#define EMS_SERVICE_FLAG_RESTART  (0x2)
#define EMS_SERVICE_FLAG_ESSENTIAL (0x4)
 
// RouteInfo & DestInfo dwFlags 
#define EMS_DESTFLAG_SUPPRESS_REF_BEACONS ( 0x0001 )
#define EMS_DESTFLAG_SUPPRESS_ORB_BEACONS ( 0x0002 )
#define EMS_DESTFLAG_SUPPRESS_WARNINGS 	( 0x0004 )
#define EMS_DESTFLAG_HIRES_MF3			( 0x0000008 )
#define EMS_DESTFLAG_CALC_NEXTVIS		( 0x0000010 )
#define EMS_DESTFLAG_TIMEOUT_SHIFT		( 16 )
#define EMS_DESTFLAG_TIMEOUT_MASK		( 0xFFF )
 
 
// EMSFILTERINFO.dwFlags settings
 
#define EMS_FILTER_FREQBAND_121			( 0x00000001 )
#define EMS_FILTER_FREQBAND_243			( 0x00000002 )
#define EMS_FILTER_FREQBAND_406			( 0x00000004 )
#define EMS_FILTER_DATA_SARR				( 0x00000008 )
#define EMS_FILTER_DATA_SARP				( 0x00000010 )
#define EMS_FILTER_DATA_CBC				( 0x00000020 )
#define EMS_FILTER_DETECT_INTERFERER	( 0x00000040 )
#define EMS_FILTER_DETECT_UNKNOWN		( 0x00000080 )
#define EMS_FILTER_DETECT_DISTRESS		( 0x00000100 )
#define EMS_FILTER_DETECT_UNLOCATED		( 0x00000200 )
#define EMS_FILTER_MODE_SELFTEST	   	( 0x00000400 )
#define EMS_FILTER_MODE_OPERATIONAL	   ( 0x00000800 )
#define EMS_FILTER_BEACON_INVALID	   ( 0x00001000 )
#define EMS_FILTER_SUPPRESS_REF_BEACONS 		( 0x00002000 )
#define EMS_FILTER_SUPPRESS_ORB_BEACONS 		( 0x00004000 )
#define EMS_FILTER_SUPPRESS_TEST_BEACONS 		( 0x00008000 )
#define EMS_FILTER_SUPPRESS_INVERTED_FRAME_SYNC ( 0x00010000 )
#define EMS_FILTER_SUPPRESS_WARNINGS 	 		(	0x00020000 )
#define EMS_FILTER_SUPPRESS_INVALID_BEACONS  (	0x00040000 )
#define EMS_FILTER_SUPPRESS_INVALID_UNLOCATED1 (0x00080000 )
#define EMS_FILTER_SUPPRESS_INVALID_UNLOCATED2 (0x00100000 )
#define EMS_FILTER_SUPPRESS_406_BEACONS        (0x00200000)
#define EMS_FILTER_SUPPRESS_INVALID_FIXED_BITS (0x00400000)
#define EMS_FILTER_ENABLED					  (0x10000000 )
 
 
// EMSABLFILTERINFO.dwFlags settings
 
#define EMS_ABLFILTER_SUPPRESS_NORMAL	( 0x00000001 )
#define EMS_ABLFILTER_ALLOW_RESERVED		( 0x00000002 )
#define EMS_ABLFILTER_CC					( 0x00000004 )
// Structure array sizes
#define EMS_MAX_COUNTRY_CODES		( 32 )
#define EMS_MAX_USER_TYPES			( 32 )
#define EMS_MAX_ALLOWRESERVE_COUNT	( 32 )
typedef struct  _tagEMSREPLICATEINFO
    {
    DWORD dwFlags;
    double dFrequency;
    }	EMSREPLICATEINFO;

typedef struct _tagEMSREPLICATEINFO __RPC_FAR *LPEMSREPLICATEINFO;

typedef struct  _tagEMSRETRYINFO
    {
    double dCheckMinutes;
    double dRetryMinutes;
    int nRetryLimit;
    }	EMSRETRYINFO;

typedef struct _tagEMSRETRYINFO __RPC_FAR *LPEMSRETRYINFO;

typedef struct  _tagEMSFILTERINFO
    {
    DWORD dwFlags;
    ULONG ulMaxBCHErrors;
    int nCountryCodesCount;
    ULONG ulCountryCodes[ 32 ];
    int nUserTypeCount;
    ULONG ulUserTypes[ 32 ];
    }	EMSFILTERINFO;

typedef struct _tagEMSFILTERINFO __RPC_FAR *LPEMSFILTERINFO;

typedef struct  _tagEMSABLFILTERINFO
    {
    DWORD dwFlags;
    ULONG ulCountryCode;
    short sAllowReservedCount;
    short asAllowReserved[ 32 ];
    }	EMSABLFILTERINFO;

typedef struct _tagEMSABLFILTERINFO __RPC_FAR *LPEMSABLFILTERINFO;

// dwFlags 
#define EMS_SYSTEST_ON_PREPASS	( 0x0000001 )
#define EMS_SYSTEST_ON_STARTUP	( 0x0000002 )
#define EMS_SYSTEST_AVOID_CONFLICT ( 0x0000004 )
 
typedef struct  _tagEMSSYSTEMTESTINFO
    {
    DWORD dwFlags;
    WORD wSwitchID;
    double dThreshold;
    EMSAZEL azelTestHorn;
    EMSAZEL azelSweepFrom;
    EMSAZEL azelSweepTo;
    double dMinDuration;
    }	EMSSYSTEMTESTINFO;

typedef struct _tagEMSSYSTEMTESTINFO __RPC_FAR *LPEMSSYSTEMTESTINFO;

typedef struct  _tagEMSAGCINFO
    {
    DWORD dwFlags;
    WORD wSwitchID;
    }	EMSAGCINFO;

typedef struct _tagEMSAGCINFO __RPC_FAR *LPEMSAGCINFO;

#define	c_dwDefaultAGCFlags	( 0 )

#define	c_wDefaultAGCSwitchID	( 24 )

#define	EMS_ROUTE_MAX_PATHLEN	( 256 )

#define	EMS_ROUTE_SHORT_NAMELEN	( 8 )

#define	EMS_ROUTE_LONG_NAMELEN	( 256 )

#define	EMS_ROUTE_SIT_LIST_LENGTH	( 256 )

#define	EMS_ROUTE_FILTER_LIST_LENGTH	( 256 )

typedef 
enum _tagEMSROUTEDIRECTION
    {	EMS_RD_Unknown	= 0,
	EMS_RD_Outbound	= 1,
	EMS_RD_Inbound	= 2
    }	EMSROUTEDIRECTION;

typedef 
enum _tagEMSROUTEMSGFMT
    {	EMS_RMF_Unknown	= 0,
	EMS_RMF_Sit	= 1,
	EMS_RMF_MultiSit	= 2
    }	EMSROUTEMSGFMT;

typedef 
enum _tagEMSROUTECOMMTYPE
    {	EMS_RCT_Unknown	= 0,
	EMS_RCT_Direct	= 1,
	EMS_RCT_FTP	= 2,
	EMS_RCT_TCPIP	= 3
    }	EMSROUTECOMMTYPE;

typedef struct  _tagEMSROUTEDIRINFO
    {
    unsigned char szPath[ 256 ];
    }	EMSROUTEDIRINFO;

typedef struct _tagEMSROUTEDIRINFO __RPC_FAR *LPEMSROUTEDIRINFO;

typedef struct  _tagEMSROUTEFTPINFO
    {
    int nPort;
    unsigned char szHost[ 64 ];
    unsigned char szLogin[ 64 ];
    unsigned char szPassword[ 64 ];
    unsigned char szPath[ 256 ];
    }	EMSROUTEFTPINFO;

typedef struct _tagEMSROUTEFTPINFO __RPC_FAR *LPEMSROUTEFTPINFO;

#define	EMS_MAX_SIT_MSG_NUMBERS	( 64 )

#define	EMS_TRANS_TABLE_NAMELEN	( 32 )

typedef struct  _tagEMSSITTRANSTABLE
    {
    int nCounts;
    unsigned char szName[ 32 ];
    DWORD dwCode[ 64 ];
    DWORD dwSit[ 64 ];
    }	EMSSITTRANSTABLE;

typedef struct _tagEMSSITTRANSTABLE __RPC_FAR *LPEMSSITTRANSTABLE;

typedef struct  _tagEMSSITMSGLIST
    {
    int nCount;
    DWORD dwSitCodes[ 64 ];
    int nSitNumbers[ 64 ];
    }	EMSSITMSGLIST;

typedef struct _tagEMSSITMSGLIST __RPC_FAR *LPEMSSITMSGLIST;

typedef struct  _tagEMSROUTEINFO
    {
    EMSROUTECOMMTYPE commType;
    DWORD dwFlags;
    EMSROUTEMSGFMT msgFmt;
    EMSROUTEDIRECTION direction;
    EMSSITMSGLIST sitMsgs;
    EMSRETRYINFO retry;
    unsigned char szShortName[ 8 ];
    unsigned char szLongName[ 256 ];
    unsigned char szFilterList[ 256 ];
    /* [switch_is][switch_type] */ union 
        {
        /* [case()] */ EMSROUTEFTPINFO ftp;
        /* [case()] */ EMSROUTEDIRINFO dir;
        /* [default] */  /* Empty union arm */ 
        }	info;
    }	EMSROUTEINFO;

typedef struct _tagEMSROUTEINFO __RPC_FAR *LPEMSROUTEINFO;

typedef struct  _tagEMSDESTINATIONINFO
    {
    DWORD dwFlags;
    ULONG ulSeqNumber;
    ULONG ulID;
    EMSRETRYINFO retry;
    unsigned char szShortName[ 8 ];
    EMSROUTEMSGFMT msgFmt;
    EMSSITMSGLIST sitMsgs;
    EMSFILTERINFO filterInfo;
    int nRouteIndex;
    int nTransIndex;
    }	EMSDESTINATIONINFO;

typedef struct _tagEMSDESTINATIONINFO __RPC_FAR *LPEMSDESTINATIONINFO;

typedef struct  _tagEMSDESTINATIONINFO2
    {
    DWORD dwFlags;
    ULONG ulSeqNumber;
    ULONG ulRouteIdentifier;
    ULONG ulID;
    EMSRETRYINFO retry;
    unsigned char szShortName[ 8 ];
    unsigned char szSrcShortName[ 8 ];
    EMSROUTEMSGFMT msgFmt;
    EMSSITMSGLIST sitMsgs;
    EMSFILTERINFO filterInfo;
    int nRouteIndex;
    int nTransIndex;
    }	EMSDESTINATIONINFO2;

typedef struct _tagEMSDESTINATIONINFO2 __RPC_FAR *LPEMSDESTINATIONINFO2;

typedef struct  _tagEMSDESTINATIONINFO3
    {
    EMSDESTINATIONINFO2 info2;
    EMSABLFILTERINFO ablFilterInfo;
    }	EMSDESTINATIONINFO3;

typedef struct _tagEMSDESTINATIONINFO3 __RPC_FAR *LPEMSDESTINATIONINFO3;

typedef struct  _tagEMSSOURCEINFO
    {
    DWORD dwFlags;
    ULONG ulSeqNumber;
    ULONG ulID;
    EMSRETRYINFO retry;
    unsigned char szShortName[ 8 ];
    int nRouteIndex;
    }	EMSSOURCEINFO;

typedef struct _tagEMSSOURCEINFO __RPC_FAR *LPEMSSOURCEINFO;

#define	c_dwDefaultSourceInfoFlags	( 0 )

typedef struct  _tagEMSSERVICEINFO
    {
    unsigned char szName[ 32 ];
    WORD wFlags;
    }	EMSSERVICEINFO;

typedef struct _tagEMSSERVICEINFO __RPC_FAR *LPEMSSERVICEINFO;



extern RPC_IF_HANDLE __MIDL_itf_EMSITEIF_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSITEIF_0000_v0_0_s_ifspec;

#ifndef __IEMSSiteInfo_INTERFACE_DEFINED__
#define __IEMSSiteInfo_INTERFACE_DEFINED__

/* interface IEMSSiteInfo */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSSiteInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C28EB166-045F-4d3f-AABB-D9E3A83D3529")
    IEMSSiteInfo : public IEMSConfigSettings
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetLutID( 
            /* [out] */ ULONG __RPC_FAR *lpulLutID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLutName( 
            /* [length_is][size_is][out] */ unsigned char __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbLength) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSecondaryLuts( 
            /* [length_is][size_is][out] */ ULONG __RPC_FAR *lpulLuts,
            /* [in] */ ULONG ulMax,
            /* [out] */ ULONG __RPC_FAR *ulActual) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetServiceInfo( 
            /* [length_is][size_is][out] */ EMSSERVICEINFO __RPC_FAR *lpInfo,
            /* [in] */ ULONG ulMax,
            /* [out] */ ULONG __RPC_FAR *ulActual) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMonitorFrequency( 
            /* [out] */ ULONG __RPC_FAR *lpulFrequency) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetGuardFrequency( 
            /* [out] */ ULONG __RPC_FAR *lpulFrequency) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTranslationTableInfo( 
            /* [length_is][size_is][out] */ EMSSITTRANSTABLE __RPC_FAR *lpInfo,
            /* [in] */ ULONG ulMax,
            /* [out] */ ULONG __RPC_FAR *ulActual) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRouteInfo( 
            /* [length_is][size_is][out] */ EMSROUTEINFO __RPC_FAR *lpInfo,
            /* [in] */ ULONG ulMax,
            /* [out] */ ULONG __RPC_FAR *ulActual) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDestinationsInfo( 
            /* [length_is][size_is][out] */ EMSDESTINATIONINFO __RPC_FAR *lpInfo,
            /* [in] */ ULONG ulMax,
            /* [out] */ ULONG __RPC_FAR *ulActual) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSourcesInfo( 
            /* [length_is][size_is][out] */ EMSSOURCEINFO __RPC_FAR *lpInfo,
            /* [in] */ ULONG ulMax,
            /* [out] */ ULONG __RPC_FAR *ulActual) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetDataDirectory( 
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRecvMsgDirectory( 
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetProcessedMsgDirectory( 
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSendMsgDirectory( 
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSentMsgDirectory( 
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetUndeliveredMsgDirectory( 
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetRecvdMsgNumber( 
            /* [string][in] */ unsigned char __RPC_FAR *lpszShortRouteName,
            /* [in] */ ULONG ulMsgNumber) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSentMsgNumber( 
            /* [string][in] */ unsigned char __RPC_FAR *lpszShortRouteName,
            /* [in] */ ULONG ulMsgNumber) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetGpsAllowedDifference( 
            /* [out] */ double __RPC_FAR *lpdSeconds) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetGpsCheckFrequency( 
            /* [out] */ double __RPC_FAR *lpdSeconds) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSystemTestInfo( 
            /* [out] */ EMSSYSTEMTESTINFO __RPC_FAR *lpInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetReplicationInfo( 
            /* [out] */ EMSREPLICATEINFO __RPC_FAR *lpInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAGCInfo( 
            /* [out] */ EMSAGCINFO __RPC_FAR *lpInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSiteInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSSiteInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSSiteInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSSiteInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfigFlags )( 
            IEMSSiteInfo __RPC_FAR * This,
            /* [in] */ DWORD dwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigFlags )( 
            IEMSSiteInfo __RPC_FAR * This,
            /* [out] */ DWORD __RPC_FAR *lpdwFlags);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ReloadConfigData )( 
            IEMSSiteInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfigValueA )( 
            IEMSSiteInfo __RPC_FAR * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [string][in] */ LPCSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigValueA )( 
            IEMSSiteInfo __RPC_FAR * This,
            /* [string][in] */ LPCSTR lpcszSection,
            /* [string][in] */ LPCSTR lpcszKey,
            /* [length_is][size_is][out] */ unsigned char __RPC_FAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG __RPC_FAR *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetConfigValueW )( 
            IEMSSiteInfo __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [string][in] */ LPCWSTR lpcszValue);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConfigValueW )( 
            IEMSSiteInfo __RPC_FAR * This,
            /* [string][in] */ LPCWSTR lpcszSection,
            /* [string][in] */ LPCWSTR lpcszKey,
            /* [length_is][size_is][out] */ WCHAR __RPC_FAR *lpszValue,
            /* [in] */ ULONG ulMaxLen,
            /* [out] */ ULONG __RPC_FAR *lpulRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLutID )( 
            IEMSSiteInfo __RPC_FAR * This,
            /* [out] */ ULONG __RPC_FAR *lpulLutID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLutName )( 
            IEMSSiteInfo __RPC_FAR * This,
            /* [length_is][size_is][out] */ unsigned char __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbLength);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSecondaryLuts )( 
            IEMSSiteInfo __RPC_FAR * This,
            /* [length_is][size_is][out] */ ULONG __RPC_FAR *lpulLuts,
            /* [in] */ ULONG ulMax,
            /* [out] */ ULONG __RPC_FAR *ulActual);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetServiceInfo )( 
            IEMSSiteInfo __RPC_FAR * This,
            /* [length_is][size_is][out] */ EMSSERVICEINFO __RPC_FAR *lpInfo,
            /* [in] */ ULONG ulMax,
            /* [out] */ ULONG __RPC_FAR *ulActual);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMonitorFrequency )( 
            IEMSSiteInfo __RPC_FAR * This,
            /* [out] */ ULONG __RPC_FAR *lpulFrequency);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGuardFrequency )( 
            IEMSSiteInfo __RPC_FAR * This,
            /* [out] */ ULONG __RPC_FAR *lpulFrequency);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTranslationTableInfo )( 
            IEMSSiteInfo __RPC_FAR * This,
            /* [length_is][size_is][out] */ EMSSITTRANSTABLE __RPC_FAR *lpInfo,
            /* [in] */ ULONG ulMax,
            /* [out] */ ULONG __RPC_FAR *ulActual);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRouteInfo )( 
            IEMSSiteInfo __RPC_FAR * This,
            /* [length_is][size_is][out] */ EMSROUTEINFO __RPC_FAR *lpInfo,
            /* [in] */ ULONG ulMax,
            /* [out] */ ULONG __RPC_FAR *ulActual);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDestinationsInfo )( 
            IEMSSiteInfo __RPC_FAR * This,
            /* [length_is][size_is][out] */ EMSDESTINATIONINFO __RPC_FAR *lpInfo,
            /* [in] */ ULONG ulMax,
            /* [out] */ ULONG __RPC_FAR *ulActual);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSourcesInfo )( 
            IEMSSiteInfo __RPC_FAR * This,
            /* [length_is][size_is][out] */ EMSSOURCEINFO __RPC_FAR *lpInfo,
            /* [in] */ ULONG ulMax,
            /* [out] */ ULONG __RPC_FAR *ulActual);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDataDirectory )( 
            IEMSSiteInfo __RPC_FAR * This,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRecvMsgDirectory )( 
            IEMSSiteInfo __RPC_FAR * This,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetProcessedMsgDirectory )( 
            IEMSSiteInfo __RPC_FAR * This,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSendMsgDirectory )( 
            IEMSSiteInfo __RPC_FAR * This,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSentMsgDirectory )( 
            IEMSSiteInfo __RPC_FAR * This,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetUndeliveredMsgDirectory )( 
            IEMSSiteInfo __RPC_FAR * This,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetRecvdMsgNumber )( 
            IEMSSiteInfo __RPC_FAR * This,
            /* [string][in] */ unsigned char __RPC_FAR *lpszShortRouteName,
            /* [in] */ ULONG ulMsgNumber);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetSentMsgNumber )( 
            IEMSSiteInfo __RPC_FAR * This,
            /* [string][in] */ unsigned char __RPC_FAR *lpszShortRouteName,
            /* [in] */ ULONG ulMsgNumber);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGpsAllowedDifference )( 
            IEMSSiteInfo __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *lpdSeconds);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetGpsCheckFrequency )( 
            IEMSSiteInfo __RPC_FAR * This,
            /* [out] */ double __RPC_FAR *lpdSeconds);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSystemTestInfo )( 
            IEMSSiteInfo __RPC_FAR * This,
            /* [out] */ EMSSYSTEMTESTINFO __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetReplicationInfo )( 
            IEMSSiteInfo __RPC_FAR * This,
            /* [out] */ EMSREPLICATEINFO __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAGCInfo )( 
            IEMSSiteInfo __RPC_FAR * This,
            /* [out] */ EMSAGCINFO __RPC_FAR *lpInfo);
        
        END_INTERFACE
    } IEMSSiteInfoVtbl;

    interface IEMSSiteInfo
    {
        CONST_VTBL struct IEMSSiteInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSiteInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSSiteInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSSiteInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSSiteInfo_SetConfigFlags(This,dwFlags)	\
    (This)->lpVtbl -> SetConfigFlags(This,dwFlags)

#define IEMSSiteInfo_GetConfigFlags(This,lpdwFlags)	\
    (This)->lpVtbl -> GetConfigFlags(This,lpdwFlags)

#define IEMSSiteInfo_ReloadConfigData(This)	\
    (This)->lpVtbl -> ReloadConfigData(This)

#define IEMSSiteInfo_SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)	\
    (This)->lpVtbl -> SetConfigValueA(This,lpcszSection,lpcszKey,lpcszValue)

#define IEMSSiteInfo_GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    (This)->lpVtbl -> GetConfigValueA(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)

#define IEMSSiteInfo_SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)	\
    (This)->lpVtbl -> SetConfigValueW(This,lpcszSection,lpcszKey,lpcszValue)

#define IEMSSiteInfo_GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)	\
    (This)->lpVtbl -> GetConfigValueW(This,lpcszSection,lpcszKey,lpszValue,ulMaxLen,lpulRead)


#define IEMSSiteInfo_GetLutID(This,lpulLutID)	\
    (This)->lpVtbl -> GetLutID(This,lpulLutID)

#define IEMSSiteInfo_GetLutName(This,pv,cb,pcbLength)	\
    (This)->lpVtbl -> GetLutName(This,pv,cb,pcbLength)

#define IEMSSiteInfo_GetSecondaryLuts(This,lpulLuts,ulMax,ulActual)	\
    (This)->lpVtbl -> GetSecondaryLuts(This,lpulLuts,ulMax,ulActual)

#define IEMSSiteInfo_GetServiceInfo(This,lpInfo,ulMax,ulActual)	\
    (This)->lpVtbl -> GetServiceInfo(This,lpInfo,ulMax,ulActual)

#define IEMSSiteInfo_GetMonitorFrequency(This,lpulFrequency)	\
    (This)->lpVtbl -> GetMonitorFrequency(This,lpulFrequency)

#define IEMSSiteInfo_GetGuardFrequency(This,lpulFrequency)	\
    (This)->lpVtbl -> GetGuardFrequency(This,lpulFrequency)

#define IEMSSiteInfo_GetTranslationTableInfo(This,lpInfo,ulMax,ulActual)	\
    (This)->lpVtbl -> GetTranslationTableInfo(This,lpInfo,ulMax,ulActual)

#define IEMSSiteInfo_GetRouteInfo(This,lpInfo,ulMax,ulActual)	\
    (This)->lpVtbl -> GetRouteInfo(This,lpInfo,ulMax,ulActual)

#define IEMSSiteInfo_GetDestinationsInfo(This,lpInfo,ulMax,ulActual)	\
    (This)->lpVtbl -> GetDestinationsInfo(This,lpInfo,ulMax,ulActual)

#define IEMSSiteInfo_GetSourcesInfo(This,lpInfo,ulMax,ulActual)	\
    (This)->lpVtbl -> GetSourcesInfo(This,lpInfo,ulMax,ulActual)

#define IEMSSiteInfo_GetDataDirectory(This,pv,cb,pcbRead)	\
    (This)->lpVtbl -> GetDataDirectory(This,pv,cb,pcbRead)

#define IEMSSiteInfo_GetRecvMsgDirectory(This,pv,cb,pcbRead)	\
    (This)->lpVtbl -> GetRecvMsgDirectory(This,pv,cb,pcbRead)

#define IEMSSiteInfo_GetProcessedMsgDirectory(This,pv,cb,pcbRead)	\
    (This)->lpVtbl -> GetProcessedMsgDirectory(This,pv,cb,pcbRead)

#define IEMSSiteInfo_GetSendMsgDirectory(This,pv,cb,pcbRead)	\
    (This)->lpVtbl -> GetSendMsgDirectory(This,pv,cb,pcbRead)

#define IEMSSiteInfo_GetSentMsgDirectory(This,pv,cb,pcbRead)	\
    (This)->lpVtbl -> GetSentMsgDirectory(This,pv,cb,pcbRead)

#define IEMSSiteInfo_GetUndeliveredMsgDirectory(This,pv,cb,pcbRead)	\
    (This)->lpVtbl -> GetUndeliveredMsgDirectory(This,pv,cb,pcbRead)

#define IEMSSiteInfo_SetRecvdMsgNumber(This,lpszShortRouteName,ulMsgNumber)	\
    (This)->lpVtbl -> SetRecvdMsgNumber(This,lpszShortRouteName,ulMsgNumber)

#define IEMSSiteInfo_SetSentMsgNumber(This,lpszShortRouteName,ulMsgNumber)	\
    (This)->lpVtbl -> SetSentMsgNumber(This,lpszShortRouteName,ulMsgNumber)

#define IEMSSiteInfo_GetGpsAllowedDifference(This,lpdSeconds)	\
    (This)->lpVtbl -> GetGpsAllowedDifference(This,lpdSeconds)

#define IEMSSiteInfo_GetGpsCheckFrequency(This,lpdSeconds)	\
    (This)->lpVtbl -> GetGpsCheckFrequency(This,lpdSeconds)

#define IEMSSiteInfo_GetSystemTestInfo(This,lpInfo)	\
    (This)->lpVtbl -> GetSystemTestInfo(This,lpInfo)

#define IEMSSiteInfo_GetReplicationInfo(This,lpInfo)	\
    (This)->lpVtbl -> GetReplicationInfo(This,lpInfo)

#define IEMSSiteInfo_GetAGCInfo(This,lpInfo)	\
    (This)->lpVtbl -> GetAGCInfo(This,lpInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSSiteInfo_GetLutID_Proxy( 
    IEMSSiteInfo __RPC_FAR * This,
    /* [out] */ ULONG __RPC_FAR *lpulLutID);


void __RPC_STUB IEMSSiteInfo_GetLutID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSiteInfo_GetLutName_Proxy( 
    IEMSSiteInfo __RPC_FAR * This,
    /* [length_is][size_is][out] */ unsigned char __RPC_FAR *pv,
    /* [in] */ ULONG cb,
    /* [out] */ ULONG __RPC_FAR *pcbLength);


void __RPC_STUB IEMSSiteInfo_GetLutName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSiteInfo_GetSecondaryLuts_Proxy( 
    IEMSSiteInfo __RPC_FAR * This,
    /* [length_is][size_is][out] */ ULONG __RPC_FAR *lpulLuts,
    /* [in] */ ULONG ulMax,
    /* [out] */ ULONG __RPC_FAR *ulActual);


void __RPC_STUB IEMSSiteInfo_GetSecondaryLuts_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSiteInfo_GetServiceInfo_Proxy( 
    IEMSSiteInfo __RPC_FAR * This,
    /* [length_is][size_is][out] */ EMSSERVICEINFO __RPC_FAR *lpInfo,
    /* [in] */ ULONG ulMax,
    /* [out] */ ULONG __RPC_FAR *ulActual);


void __RPC_STUB IEMSSiteInfo_GetServiceInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSiteInfo_GetMonitorFrequency_Proxy( 
    IEMSSiteInfo __RPC_FAR * This,
    /* [out] */ ULONG __RPC_FAR *lpulFrequency);


void __RPC_STUB IEMSSiteInfo_GetMonitorFrequency_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSiteInfo_GetGuardFrequency_Proxy( 
    IEMSSiteInfo __RPC_FAR * This,
    /* [out] */ ULONG __RPC_FAR *lpulFrequency);


void __RPC_STUB IEMSSiteInfo_GetGuardFrequency_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSiteInfo_GetTranslationTableInfo_Proxy( 
    IEMSSiteInfo __RPC_FAR * This,
    /* [length_is][size_is][out] */ EMSSITTRANSTABLE __RPC_FAR *lpInfo,
    /* [in] */ ULONG ulMax,
    /* [out] */ ULONG __RPC_FAR *ulActual);


void __RPC_STUB IEMSSiteInfo_GetTranslationTableInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSiteInfo_GetRouteInfo_Proxy( 
    IEMSSiteInfo __RPC_FAR * This,
    /* [length_is][size_is][out] */ EMSROUTEINFO __RPC_FAR *lpInfo,
    /* [in] */ ULONG ulMax,
    /* [out] */ ULONG __RPC_FAR *ulActual);


void __RPC_STUB IEMSSiteInfo_GetRouteInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSiteInfo_GetDestinationsInfo_Proxy( 
    IEMSSiteInfo __RPC_FAR * This,
    /* [length_is][size_is][out] */ EMSDESTINATIONINFO __RPC_FAR *lpInfo,
    /* [in] */ ULONG ulMax,
    /* [out] */ ULONG __RPC_FAR *ulActual);


void __RPC_STUB IEMSSiteInfo_GetDestinationsInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSiteInfo_GetSourcesInfo_Proxy( 
    IEMSSiteInfo __RPC_FAR * This,
    /* [length_is][size_is][out] */ EMSSOURCEINFO __RPC_FAR *lpInfo,
    /* [in] */ ULONG ulMax,
    /* [out] */ ULONG __RPC_FAR *ulActual);


void __RPC_STUB IEMSSiteInfo_GetSourcesInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSiteInfo_GetDataDirectory_Proxy( 
    IEMSSiteInfo __RPC_FAR * This,
    /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
    /* [in] */ ULONG cb,
    /* [out] */ ULONG __RPC_FAR *pcbRead);


void __RPC_STUB IEMSSiteInfo_GetDataDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSiteInfo_GetRecvMsgDirectory_Proxy( 
    IEMSSiteInfo __RPC_FAR * This,
    /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
    /* [in] */ ULONG cb,
    /* [out] */ ULONG __RPC_FAR *pcbRead);


void __RPC_STUB IEMSSiteInfo_GetRecvMsgDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSiteInfo_GetProcessedMsgDirectory_Proxy( 
    IEMSSiteInfo __RPC_FAR * This,
    /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
    /* [in] */ ULONG cb,
    /* [out] */ ULONG __RPC_FAR *pcbRead);


void __RPC_STUB IEMSSiteInfo_GetProcessedMsgDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSiteInfo_GetSendMsgDirectory_Proxy( 
    IEMSSiteInfo __RPC_FAR * This,
    /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
    /* [in] */ ULONG cb,
    /* [out] */ ULONG __RPC_FAR *pcbRead);


void __RPC_STUB IEMSSiteInfo_GetSendMsgDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSiteInfo_GetSentMsgDirectory_Proxy( 
    IEMSSiteInfo __RPC_FAR * This,
    /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
    /* [in] */ ULONG cb,
    /* [out] */ ULONG __RPC_FAR *pcbRead);


void __RPC_STUB IEMSSiteInfo_GetSentMsgDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSiteInfo_GetUndeliveredMsgDirectory_Proxy( 
    IEMSSiteInfo __RPC_FAR * This,
    /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
    /* [in] */ ULONG cb,
    /* [out] */ ULONG __RPC_FAR *pcbRead);


void __RPC_STUB IEMSSiteInfo_GetUndeliveredMsgDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSiteInfo_SetRecvdMsgNumber_Proxy( 
    IEMSSiteInfo __RPC_FAR * This,
    /* [string][in] */ unsigned char __RPC_FAR *lpszShortRouteName,
    /* [in] */ ULONG ulMsgNumber);


void __RPC_STUB IEMSSiteInfo_SetRecvdMsgNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSiteInfo_SetSentMsgNumber_Proxy( 
    IEMSSiteInfo __RPC_FAR * This,
    /* [string][in] */ unsigned char __RPC_FAR *lpszShortRouteName,
    /* [in] */ ULONG ulMsgNumber);


void __RPC_STUB IEMSSiteInfo_SetSentMsgNumber_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSiteInfo_GetGpsAllowedDifference_Proxy( 
    IEMSSiteInfo __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *lpdSeconds);


void __RPC_STUB IEMSSiteInfo_GetGpsAllowedDifference_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSiteInfo_GetGpsCheckFrequency_Proxy( 
    IEMSSiteInfo __RPC_FAR * This,
    /* [out] */ double __RPC_FAR *lpdSeconds);


void __RPC_STUB IEMSSiteInfo_GetGpsCheckFrequency_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSiteInfo_GetSystemTestInfo_Proxy( 
    IEMSSiteInfo __RPC_FAR * This,
    /* [out] */ EMSSYSTEMTESTINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSSiteInfo_GetSystemTestInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSiteInfo_GetReplicationInfo_Proxy( 
    IEMSSiteInfo __RPC_FAR * This,
    /* [out] */ EMSREPLICATEINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSSiteInfo_GetReplicationInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSiteInfo_GetAGCInfo_Proxy( 
    IEMSSiteInfo __RPC_FAR * This,
    /* [out] */ EMSAGCINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSSiteInfo_GetAGCInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSSiteInfo_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSITEIF_0018 */
/* [local] */ 

typedef /* [unique] */ IEMSSiteInfo __RPC_FAR *LPEMSSITEINFO;



extern RPC_IF_HANDLE __MIDL_itf_EMSITEIF_0018_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSITEIF_0018_v0_0_s_ifspec;

#ifndef __IEMSOffline_INTERFACE_DEFINED__
#define __IEMSOffline_INTERFACE_DEFINED__

/* interface IEMSOffline */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSOffline;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7CE97B78-51F2-4d81-BAC3-360B3F5B36D4")
    IEMSOffline : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetOfflineMsgDirectory( 
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaxOfflinefilesCount( 
            /* [out] */ ULONG __RPC_FAR *lpulMaxFileCnt) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSOfflineVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSOffline __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSOffline __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSOffline __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetOfflineMsgDirectory )( 
            IEMSOffline __RPC_FAR * This,
            /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
            /* [in] */ ULONG cb,
            /* [out] */ ULONG __RPC_FAR *pcbRead);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMaxOfflinefilesCount )( 
            IEMSOffline __RPC_FAR * This,
            /* [out] */ ULONG __RPC_FAR *lpulMaxFileCnt);
        
        END_INTERFACE
    } IEMSOfflineVtbl;

    interface IEMSOffline
    {
        CONST_VTBL struct IEMSOfflineVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSOffline_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSOffline_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSOffline_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSOffline_GetOfflineMsgDirectory(This,pv,cb,pcbRead)	\
    (This)->lpVtbl -> GetOfflineMsgDirectory(This,pv,cb,pcbRead)

#define IEMSOffline_GetMaxOfflinefilesCount(This,lpulMaxFileCnt)	\
    (This)->lpVtbl -> GetMaxOfflinefilesCount(This,lpulMaxFileCnt)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSOffline_GetOfflineMsgDirectory_Proxy( 
    IEMSOffline __RPC_FAR * This,
    /* [length_is][size_is][out] */ BYTE __RPC_FAR *pv,
    /* [in] */ ULONG cb,
    /* [out] */ ULONG __RPC_FAR *pcbRead);


void __RPC_STUB IEMSOffline_GetOfflineMsgDirectory_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSOffline_GetMaxOfflinefilesCount_Proxy( 
    IEMSOffline __RPC_FAR * This,
    /* [out] */ ULONG __RPC_FAR *lpulMaxFileCnt);


void __RPC_STUB IEMSOffline_GetMaxOfflinefilesCount_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSOffline_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSITEIF_0019 */
/* [local] */ 

typedef /* [unique] */ IEMSOffline __RPC_FAR *LPEMSOFFLINE;



extern RPC_IF_HANDLE __MIDL_itf_EMSITEIF_0019_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSITEIF_0019_v0_0_s_ifspec;

#ifndef __IEMSCollectorPPS_INTERFACE_DEFINED__
#define __IEMSCollectorPPS_INTERFACE_DEFINED__

/* interface IEMSCollectorPPS */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSCollectorPPS;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("7A92B265-E833-4403-B937-5CACAEDF51CE")
    IEMSCollectorPPS : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetMinPPSLostCountToAlarm( 
            /* [out] */ ULONG __RPC_FAR *lpulMinCnt) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSCollectorPPSVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSCollectorPPS __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSCollectorPPS __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSCollectorPPS __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMinPPSLostCountToAlarm )( 
            IEMSCollectorPPS __RPC_FAR * This,
            /* [out] */ ULONG __RPC_FAR *lpulMinCnt);
        
        END_INTERFACE
    } IEMSCollectorPPSVtbl;

    interface IEMSCollectorPPS
    {
        CONST_VTBL struct IEMSCollectorPPSVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSCollectorPPS_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSCollectorPPS_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSCollectorPPS_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSCollectorPPS_GetMinPPSLostCountToAlarm(This,lpulMinCnt)	\
    (This)->lpVtbl -> GetMinPPSLostCountToAlarm(This,lpulMinCnt)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSCollectorPPS_GetMinPPSLostCountToAlarm_Proxy( 
    IEMSCollectorPPS __RPC_FAR * This,
    /* [out] */ ULONG __RPC_FAR *lpulMinCnt);


void __RPC_STUB IEMSCollectorPPS_GetMinPPSLostCountToAlarm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSCollectorPPS_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSITEIF_0020 */
/* [local] */ 

typedef /* [unique] */ IEMSCollectorPPS __RPC_FAR *LPEMSCollectorPPS;



extern RPC_IF_HANDLE __MIDL_itf_EMSITEIF_0020_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSITEIF_0020_v0_0_s_ifspec;

#ifndef __IEMSDestinationsInfo_INTERFACE_DEFINED__
#define __IEMSDestinationsInfo_INTERFACE_DEFINED__

/* interface IEMSDestinationsInfo */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSDestinationsInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3FD55374-41F4-4f64-96BE-CC1F4EC1202A")
    IEMSDestinationsInfo : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetDestinationsInfo2( 
            /* [length_is][size_is][out] */ EMSDESTINATIONINFO2 __RPC_FAR *lpInfo,
            /* [in] */ ULONG ulMax,
            /* [out] */ ULONG __RPC_FAR *ulActual) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSDestinationsInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSDestinationsInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSDestinationsInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSDestinationsInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDestinationsInfo2 )( 
            IEMSDestinationsInfo __RPC_FAR * This,
            /* [length_is][size_is][out] */ EMSDESTINATIONINFO2 __RPC_FAR *lpInfo,
            /* [in] */ ULONG ulMax,
            /* [out] */ ULONG __RPC_FAR *ulActual);
        
        END_INTERFACE
    } IEMSDestinationsInfoVtbl;

    interface IEMSDestinationsInfo
    {
        CONST_VTBL struct IEMSDestinationsInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSDestinationsInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSDestinationsInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSDestinationsInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSDestinationsInfo_GetDestinationsInfo2(This,lpInfo,ulMax,ulActual)	\
    (This)->lpVtbl -> GetDestinationsInfo2(This,lpInfo,ulMax,ulActual)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSDestinationsInfo_GetDestinationsInfo2_Proxy( 
    IEMSDestinationsInfo __RPC_FAR * This,
    /* [length_is][size_is][out] */ EMSDESTINATIONINFO2 __RPC_FAR *lpInfo,
    /* [in] */ ULONG ulMax,
    /* [out] */ ULONG __RPC_FAR *ulActual);


void __RPC_STUB IEMSDestinationsInfo_GetDestinationsInfo2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSDestinationsInfo_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSITEIF_0021 */
/* [local] */ 

typedef /* [unique] */ IEMSDestinationsInfo __RPC_FAR *LPEMSDESTINATIONSINFO;



extern RPC_IF_HANDLE __MIDL_itf_EMSITEIF_0021_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSITEIF_0021_v0_0_s_ifspec;

#ifndef __IEMSDestinationsInfo3_INTERFACE_DEFINED__
#define __IEMSDestinationsInfo3_INTERFACE_DEFINED__

/* interface IEMSDestinationsInfo3 */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSDestinationsInfo3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("520F4DFC-FCE4-45d0-BDB6-46025FBA891C")
    IEMSDestinationsInfo3 : public IEMSDestinationsInfo
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetDestinationsInfo3( 
            /* [length_is][size_is][out] */ EMSDESTINATIONINFO3 __RPC_FAR *lpInfo,
            /* [in] */ ULONG ulMax,
            /* [out] */ ULONG __RPC_FAR *ulActual) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSDestinationsInfo3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSDestinationsInfo3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSDestinationsInfo3 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSDestinationsInfo3 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDestinationsInfo2 )( 
            IEMSDestinationsInfo3 __RPC_FAR * This,
            /* [length_is][size_is][out] */ EMSDESTINATIONINFO2 __RPC_FAR *lpInfo,
            /* [in] */ ULONG ulMax,
            /* [out] */ ULONG __RPC_FAR *ulActual);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDestinationsInfo3 )( 
            IEMSDestinationsInfo3 __RPC_FAR * This,
            /* [length_is][size_is][out] */ EMSDESTINATIONINFO3 __RPC_FAR *lpInfo,
            /* [in] */ ULONG ulMax,
            /* [out] */ ULONG __RPC_FAR *ulActual);
        
        END_INTERFACE
    } IEMSDestinationsInfo3Vtbl;

    interface IEMSDestinationsInfo3
    {
        CONST_VTBL struct IEMSDestinationsInfo3Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSDestinationsInfo3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSDestinationsInfo3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSDestinationsInfo3_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSDestinationsInfo3_GetDestinationsInfo2(This,lpInfo,ulMax,ulActual)	\
    (This)->lpVtbl -> GetDestinationsInfo2(This,lpInfo,ulMax,ulActual)


#define IEMSDestinationsInfo3_GetDestinationsInfo3(This,lpInfo,ulMax,ulActual)	\
    (This)->lpVtbl -> GetDestinationsInfo3(This,lpInfo,ulMax,ulActual)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSDestinationsInfo3_GetDestinationsInfo3_Proxy( 
    IEMSDestinationsInfo3 __RPC_FAR * This,
    /* [length_is][size_is][out] */ EMSDESTINATIONINFO3 __RPC_FAR *lpInfo,
    /* [in] */ ULONG ulMax,
    /* [out] */ ULONG __RPC_FAR *ulActual);


void __RPC_STUB IEMSDestinationsInfo3_GetDestinationsInfo3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSDestinationsInfo3_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSITEIF_0022 */
/* [local] */ 

typedef /* [unique] */ IEMSDestinationsInfo3 __RPC_FAR *LPEMSDESTINATIONSINFO3;



extern RPC_IF_HANDLE __MIDL_itf_EMSITEIF_0022_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSITEIF_0022_v0_0_s_ifspec;

#ifndef __IEMSSystemTestSettings_INTERFACE_DEFINED__
#define __IEMSSystemTestSettings_INTERFACE_DEFINED__

/* interface IEMSSystemTestSettings */
/* [unique][helpstring][uuid][object] */ 

typedef struct  _tagEMSSYSTEMTESTINFO2
    {
    DWORD dwFlags;
    WORD wSwitchID;
    double dThreshold;
    EMSAZEL azelTestHorn;
    EMSAZEL azelSweepFrom;
    EMSAZEL azelSweepTo;
    double dMinDuration;
    double dMaxModIndex;
    double dReserved1;
    LONG lReserved2;
    }	EMSSYSTEMTESTINFO2;

typedef struct _tagEMSSYSTEMTESTINFO2 __RPC_FAR *LPEMSSYSTEMTESTINFO2;


EXTERN_C const IID IID_IEMSSystemTestSettings;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("48EBD324-2101-4572-8026-4A0DC439DC36")
    IEMSSystemTestSettings : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetSystemTestInfo2( 
            /* [out] */ EMSSYSTEMTESTINFO2 __RPC_FAR *lpInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSystemTestSettingsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSSystemTestSettings __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSSystemTestSettings __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSSystemTestSettings __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSystemTestInfo2 )( 
            IEMSSystemTestSettings __RPC_FAR * This,
            /* [out] */ EMSSYSTEMTESTINFO2 __RPC_FAR *lpInfo);
        
        END_INTERFACE
    } IEMSSystemTestSettingsVtbl;

    interface IEMSSystemTestSettings
    {
        CONST_VTBL struct IEMSSystemTestSettingsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSystemTestSettings_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSSystemTestSettings_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSSystemTestSettings_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSSystemTestSettings_GetSystemTestInfo2(This,lpInfo)	\
    (This)->lpVtbl -> GetSystemTestInfo2(This,lpInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSSystemTestSettings_GetSystemTestInfo2_Proxy( 
    IEMSSystemTestSettings __RPC_FAR * This,
    /* [out] */ EMSSYSTEMTESTINFO2 __RPC_FAR *lpInfo);


void __RPC_STUB IEMSSystemTestSettings_GetSystemTestInfo2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSSystemTestSettings_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSITEIF_0023 */
/* [local] */ 

typedef /* [unique] */ IEMSSystemTestSettings __RPC_FAR *LPEMSSYSTEMTESTSETTINGS;

typedef struct  _tagEMSMSGARCHIVEINFO
    {
    double dCheckIntervalDays;
    double dSentMsgsDays;
    double dSendMsgsDays;
    double dRecvMsgsDays;
    double dUndeliveredMsgsDays;
    double dProcessedMsgsDays;
    }	EMSMSGARCHIVEINFO;

typedef struct _tagEMSMSGARCHIVEINFO __RPC_FAR *LPEMSMSGARCHIVEINFO;

#define	c_dSiteInfoMsgArchiveIntervalDays	( 1 )



extern RPC_IF_HANDLE __MIDL_itf_EMSITEIF_0023_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSITEIF_0023_v0_0_s_ifspec;

#ifndef __IEMSSiteType_INTERFACE_DEFINED__
#define __IEMSSiteType_INTERFACE_DEFINED__

/* interface IEMSSiteType */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSSiteType;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B73D76CD-2160-44ff-9AC5-E08EA6AF207D")
    IEMSSiteType : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetSiteType( 
            /* [out] */ LPWORD lpwSiteType) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSiteVersion( 
            /* [out] */ LPWORD lpwSiteVersion) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSiteTypeVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSSiteType __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSSiteType __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSSiteType __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSiteType )( 
            IEMSSiteType __RPC_FAR * This,
            /* [out] */ LPWORD lpwSiteType);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetSiteVersion )( 
            IEMSSiteType __RPC_FAR * This,
            /* [out] */ LPWORD lpwSiteVersion);
        
        END_INTERFACE
    } IEMSSiteTypeVtbl;

    interface IEMSSiteType
    {
        CONST_VTBL struct IEMSSiteTypeVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSiteType_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSSiteType_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSSiteType_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSSiteType_GetSiteType(This,lpwSiteType)	\
    (This)->lpVtbl -> GetSiteType(This,lpwSiteType)

#define IEMSSiteType_GetSiteVersion(This,lpwSiteVersion)	\
    (This)->lpVtbl -> GetSiteVersion(This,lpwSiteVersion)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSSiteType_GetSiteType_Proxy( 
    IEMSSiteType __RPC_FAR * This,
    /* [out] */ LPWORD lpwSiteType);


void __RPC_STUB IEMSSiteType_GetSiteType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSSiteType_GetSiteVersion_Proxy( 
    IEMSSiteType __RPC_FAR * This,
    /* [out] */ LPWORD lpwSiteVersion);


void __RPC_STUB IEMSSiteType_GetSiteVersion_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSSiteType_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSITEIF_0024 */
/* [local] */ 

typedef /* [unique] */ IEMSSiteType __RPC_FAR *LPEMSSITETYPE;



extern RPC_IF_HANDLE __MIDL_itf_EMSITEIF_0024_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSITEIF_0024_v0_0_s_ifspec;

#ifndef __IEMSMsgArchiveConfig_INTERFACE_DEFINED__
#define __IEMSMsgArchiveConfig_INTERFACE_DEFINED__

/* interface IEMSMsgArchiveConfig */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSMsgArchiveConfig;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6435FB6A-A496-460d-9830-13FB88CCA195")
    IEMSMsgArchiveConfig : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetMsgArchiveConfigData( 
            /* [out] */ LPEMSMSGARCHIVEINFO lpConfigData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSMsgArchiveConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSMsgArchiveConfig __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSMsgArchiveConfig __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSMsgArchiveConfig __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMsgArchiveConfigData )( 
            IEMSMsgArchiveConfig __RPC_FAR * This,
            /* [out] */ LPEMSMSGARCHIVEINFO lpConfigData);
        
        END_INTERFACE
    } IEMSMsgArchiveConfigVtbl;

    interface IEMSMsgArchiveConfig
    {
        CONST_VTBL struct IEMSMsgArchiveConfigVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSMsgArchiveConfig_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSMsgArchiveConfig_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSMsgArchiveConfig_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSMsgArchiveConfig_GetMsgArchiveConfigData(This,lpConfigData)	\
    (This)->lpVtbl -> GetMsgArchiveConfigData(This,lpConfigData)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSMsgArchiveConfig_GetMsgArchiveConfigData_Proxy( 
    IEMSMsgArchiveConfig __RPC_FAR * This,
    /* [out] */ LPEMSMSGARCHIVEINFO lpConfigData);


void __RPC_STUB IEMSMsgArchiveConfig_GetMsgArchiveConfigData_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSMsgArchiveConfig_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSITEIF_0025 */
/* [local] */ 

typedef /* [unique] */ IEMSMsgArchiveConfig __RPC_FAR *LPEMSMSGARCHIVECONFIG;



extern RPC_IF_HANDLE __MIDL_itf_EMSITEIF_0025_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSITEIF_0025_v0_0_s_ifspec;

#ifndef __IEMSSitMsgProperties_INTERFACE_DEFINED__
#define __IEMSSitMsgProperties_INTERFACE_DEFINED__

/* interface IEMSSitMsgProperties */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSSitMsgProperties;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9C603A34-0C3C-4847-8A61-E657A2D10B89")
    IEMSSitMsgProperties : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetMaxSizeInBytes( 
            /* [out] */ ULONG __RPC_FAR *pulMaxBytes) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSSitMsgPropertiesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSSitMsgProperties __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSSitMsgProperties __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSSitMsgProperties __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetMaxSizeInBytes )( 
            IEMSSitMsgProperties __RPC_FAR * This,
            /* [out] */ ULONG __RPC_FAR *pulMaxBytes);
        
        END_INTERFACE
    } IEMSSitMsgPropertiesVtbl;

    interface IEMSSitMsgProperties
    {
        CONST_VTBL struct IEMSSitMsgPropertiesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSSitMsgProperties_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSSitMsgProperties_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSSitMsgProperties_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSSitMsgProperties_GetMaxSizeInBytes(This,pulMaxBytes)	\
    (This)->lpVtbl -> GetMaxSizeInBytes(This,pulMaxBytes)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSSitMsgProperties_GetMaxSizeInBytes_Proxy( 
    IEMSSitMsgProperties __RPC_FAR * This,
    /* [out] */ ULONG __RPC_FAR *pulMaxBytes);


void __RPC_STUB IEMSSitMsgProperties_GetMaxSizeInBytes_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSSitMsgProperties_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSITEIF_0026 */
/* [local] */ 

typedef /* [unique] */ IEMSSitMsgProperties __RPC_FAR *LPEMSSITMSGPROPERTIES;



extern RPC_IF_HANDLE __MIDL_itf_EMSITEIF_0026_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSITEIF_0026_v0_0_s_ifspec;

#ifndef __IEMSAutoSendSit_INTERFACE_DEFINED__
#define __IEMSAutoSendSit_INTERFACE_DEFINED__

/* interface IEMSAutoSendSit */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IEMSAutoSendSit;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2B02EDF5-880A-4555-B67E-577BBF157220")
    IEMSAutoSendSit : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetAutoSend( 
            /* [in] */ ULONG ulDestID,
            /* [in] */ ULONG ulSitCode,
            /* [out] */ BOOL __RPC_FAR *pbAutoSend) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSAutoSendSitVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSAutoSendSit __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSAutoSendSit __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSAutoSendSit __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetAutoSend )( 
            IEMSAutoSendSit __RPC_FAR * This,
            /* [in] */ ULONG ulDestID,
            /* [in] */ ULONG ulSitCode,
            /* [out] */ BOOL __RPC_FAR *pbAutoSend);
        
        END_INTERFACE
    } IEMSAutoSendSitVtbl;

    interface IEMSAutoSendSit
    {
        CONST_VTBL struct IEMSAutoSendSitVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSAutoSendSit_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSAutoSendSit_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSAutoSendSit_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSAutoSendSit_GetAutoSend(This,ulDestID,ulSitCode,pbAutoSend)	\
    (This)->lpVtbl -> GetAutoSend(This,ulDestID,ulSitCode,pbAutoSend)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSAutoSendSit_GetAutoSend_Proxy( 
    IEMSAutoSendSit __RPC_FAR * This,
    /* [in] */ ULONG ulDestID,
    /* [in] */ ULONG ulSitCode,
    /* [out] */ BOOL __RPC_FAR *pbAutoSend);


void __RPC_STUB IEMSAutoSendSit_GetAutoSend_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSAutoSendSit_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSITEIF_0027 */
/* [local] */ 

typedef /* [unique] */ IEMSAutoSendSit __RPC_FAR *LPEMSAUTOSENDSIT;



extern RPC_IF_HANDLE __MIDL_itf_EMSITEIF_0027_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSITEIF_0027_v0_0_s_ifspec;

#ifndef __IEMSRouteInfo_INTERFACE_DEFINED__
#define __IEMSRouteInfo_INTERFACE_DEFINED__

/* interface IEMSRouteInfo */
/* [unique][helpstring][uuid][object] */ 

#define EMS_MAX_CONNECTION_LEN 255
#define EMS_MAX_CONNECTIONS 8
typedef struct  _tagEMSCOMMSPATH
    {
    EMSROUTECOMMTYPE eCommType;
    /* [switch_is][switch_type] */ union 
        {
        /* [case()] */ EMSROUTEFTPINFO ftp;
        /* [case()] */ EMSROUTEDIRINFO dir;
        /* [default] */  /* Empty union arm */ 
        }	info;
    ULONG ulTimeout;
    ULONG ulAlternateConnections;
    BOOL bCompress;
    wchar_t awszConnections[ 8 ][ 256 ];
    }	EMSCOMMSPATH;

typedef struct _tagEMSCOMMSPATH __RPC_FAR *PEMSCOMMSPATH;

typedef struct  _tagEMSCOMMSROUTE
    {
    ULONG ulRouteID;
    DWORD dwFlags;
    EMSROUTEDIRECTION eDirection;
    EMSRETRYINFO retry;
    unsigned char szShortName[ 8 ];
    unsigned char szLongName[ 256 ];
    ULONG ulAlternateMaxDuration;
    EMSCOMMSPATH strPathPrimary;
    EMSCOMMSPATH strPathAlternate;
    }	EMSCOMMSROUTE;

typedef struct _tagEMSCOMMSROUTE __RPC_FAR *PEMSCOMMSROUTE;


EXTERN_C const IID IID_IEMSRouteInfo;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9E586623-5E8A-48d0-B650-966FCA6B4221")
    IEMSRouteInfo : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetRouteInfo2( 
            /* [length_is][size_is][out] */ EMSCOMMSROUTE __RPC_FAR *aRouteInfo,
            /* [in] */ const ULONG culMax,
            /* [out] */ ULONG __RPC_FAR *pulActual) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSRouteInfoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSRouteInfo __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSRouteInfo __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSRouteInfo __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRouteInfo2 )( 
            IEMSRouteInfo __RPC_FAR * This,
            /* [length_is][size_is][out] */ EMSCOMMSROUTE __RPC_FAR *aRouteInfo,
            /* [in] */ const ULONG culMax,
            /* [out] */ ULONG __RPC_FAR *pulActual);
        
        END_INTERFACE
    } IEMSRouteInfoVtbl;

    interface IEMSRouteInfo
    {
        CONST_VTBL struct IEMSRouteInfoVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSRouteInfo_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSRouteInfo_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSRouteInfo_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSRouteInfo_GetRouteInfo2(This,aRouteInfo,culMax,pulActual)	\
    (This)->lpVtbl -> GetRouteInfo2(This,aRouteInfo,culMax,pulActual)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSRouteInfo_GetRouteInfo2_Proxy( 
    IEMSRouteInfo __RPC_FAR * This,
    /* [length_is][size_is][out] */ EMSCOMMSROUTE __RPC_FAR *aRouteInfo,
    /* [in] */ const ULONG culMax,
    /* [out] */ ULONG __RPC_FAR *pulActual);


void __RPC_STUB IEMSRouteInfo_GetRouteInfo2_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSRouteInfo_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSITEIF_0028 */
/* [local] */ 

typedef /* [unique] */ IEMSRouteInfo __RPC_FAR *PEMSROUTEINFO;



extern RPC_IF_HANDLE __MIDL_itf_EMSITEIF_0028_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSITEIF_0028_v0_0_s_ifspec;

#ifndef __IEMSRouteInfo2_INTERFACE_DEFINED__
#define __IEMSRouteInfo2_INTERFACE_DEFINED__

/* interface IEMSRouteInfo2 */
/* [unique][helpstring][uuid][object] */ 

typedef struct  _tagEMSCOMMSROUTE2
    {
    ULONG ulRouteID;
    DWORD dwFlags;
    EMSROUTEDIRECTION eDirection;
    EMSRETRYINFO retry;
    unsigned char szShortName[ 8 ];
    unsigned char szLongName[ 256 ];
    ULONG ulAlternateMaxDuration;
    EMSCOMMSPATH strPathPrimary;
    EMSCOMMSPATH strPathAlternate;
    double dUndeliverableAge;
    }	EMSCOMMSROUTE2;

typedef struct _tagEMSCOMMSROUTE2 __RPC_FAR *PEMSCOMMSROUTE2;


EXTERN_C const IID IID_IEMSRouteInfo2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3A3D750F-E940-4abf-93C7-93E2A63C254D")
    IEMSRouteInfo2 : public IEMSRouteInfo
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetRouteInfo3( 
            /* [length_is][size_is][out] */ EMSCOMMSROUTE2 __RPC_FAR *aRouteInfo,
            /* [in] */ const ULONG culMax,
            /* [out] */ ULONG __RPC_FAR *pulActual) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSRouteInfo2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSRouteInfo2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSRouteInfo2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSRouteInfo2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRouteInfo2 )( 
            IEMSRouteInfo2 __RPC_FAR * This,
            /* [length_is][size_is][out] */ EMSCOMMSROUTE __RPC_FAR *aRouteInfo,
            /* [in] */ const ULONG culMax,
            /* [out] */ ULONG __RPC_FAR *pulActual);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetRouteInfo3 )( 
            IEMSRouteInfo2 __RPC_FAR * This,
            /* [length_is][size_is][out] */ EMSCOMMSROUTE2 __RPC_FAR *aRouteInfo,
            /* [in] */ const ULONG culMax,
            /* [out] */ ULONG __RPC_FAR *pulActual);
        
        END_INTERFACE
    } IEMSRouteInfo2Vtbl;

    interface IEMSRouteInfo2
    {
        CONST_VTBL struct IEMSRouteInfo2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSRouteInfo2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSRouteInfo2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSRouteInfo2_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSRouteInfo2_GetRouteInfo2(This,aRouteInfo,culMax,pulActual)	\
    (This)->lpVtbl -> GetRouteInfo2(This,aRouteInfo,culMax,pulActual)


#define IEMSRouteInfo2_GetRouteInfo3(This,aRouteInfo,culMax,pulActual)	\
    (This)->lpVtbl -> GetRouteInfo3(This,aRouteInfo,culMax,pulActual)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSRouteInfo2_GetRouteInfo3_Proxy( 
    IEMSRouteInfo2 __RPC_FAR * This,
    /* [length_is][size_is][out] */ EMSCOMMSROUTE2 __RPC_FAR *aRouteInfo,
    /* [in] */ const ULONG culMax,
    /* [out] */ ULONG __RPC_FAR *pulActual);


void __RPC_STUB IEMSRouteInfo2_GetRouteInfo3_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSRouteInfo2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSITEIF_0029 */
/* [local] */ 

typedef /* [unique] */ IEMSRouteInfo2 __RPC_FAR *PEMSROUTEINFO2;



extern RPC_IF_HANDLE __MIDL_itf_EMSITEIF_0029_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSITEIF_0029_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
