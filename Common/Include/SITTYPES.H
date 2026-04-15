/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon May 11 12:45:47 2009
 */
/* Compiler settings for ..\Common\Include\SITTypes.idl:
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

#ifndef __SITTypes_h__
#define __SITTypes_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISITTypes_FWD_DEFINED__
#define __ISITTypes_FWD_DEFINED__
typedef interface ISITTypes ISITTypes;
#endif 	/* __ISITTypes_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_SITTypes_0000 */
/* [local] */ 

#define EMS_MAX_SATS_PER_ABL_ALERT 16
#define EMS_MAX_LUTS_PER_ABL_ALERT 13

#pragma pack(1)


extern RPC_IF_HANDLE __MIDL_itf_SITTypes_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_SITTypes_0000_v0_0_s_ifspec;

#ifndef __ISITTypes_INTERFACE_DEFINED__
#define __ISITTypes_INTERFACE_DEFINED__

/* interface ISITTypes */
/* [object][unique][helpstring][uuid] */ 

typedef 
enum tagEMSSITSOLNTYPE
    {	EMSSST_Unknown	= 'U',
	EMSSST_Beacon	= 'C',
	EMSSST_Interferer	= 'I'
    }	EMSSITSOLNTYPE;

typedef 
enum tagEMSSITMSGTYPE
    {	EMSSMT_Invalid	= 3,
	EMSSMT_Normal	= 0,
	EMSSMT_Test	= 1,
	EMSSMT_Combination	= 2
    }	EMSSITMSGTYPE;

typedef 
enum tagEMSITCONTROLCODE
    {	EMSSCC_Info	= 1,
	EMSSCC_Validate	= 2,
	EMSSCC_Execute	= 3,
	EMSSCC_ValidateInstall	= 4,
	EMSSCC_Install	= 5,
	EMSSCC_Append	= 6,
	EMSSCC_InstallManoeuvre	= 7,
	EMSSCC_ValidData	= 10,
	EMSSCC_InvalidData	= 11,
	EMSSCC_CommandAccepted	= 12,
	EMSSCC_CommandRejected	= 13,
	EMSSCC_UnknownCommand	= 14,
	EMSSCC_ProcessOkay	= 15,
	EMSSCC_ProcessFailed	= 16,
	EMSSCC_Last	= EMSSCC_ProcessFailed + 1,
	EMSSCC_First	= 1,
	EMSSCC_Unknown	= 0
    }	EMSSITCONTROLCODE;

typedef struct  _tagEMSSITLOCALERTHEADER
    {
    ULONG ulPass;
    int nPrimaryLutID;
    BOOL bLocalFlag;
    int nFreqBand;
    WORD wDataTypes;
    int nSecondaryLutID;
    int nSideBands;
    int nSweepPeriod;
    int nSweepPeriodSdev;
    int nNumPoints;
    INT64 i64BeaconID;
    BYTE cBeaconMsg[ 18 ];
    EMSSITSOLNTYPE solnType;
    EMSSITMSGTYPE msgType;
    int nBitErrorsPreamble;
    int nBitErrorsField1;
    int nBitErrorsField2;
    int nDupCopyCount;
    double dPower;
    double dRecvFreq;
    double dLutFreqOffset;
    EMSTIME timeMsg;
    double dLutTimeOffset;
    }	EMSSITLOCALERTHEADER;

typedef struct _tagEMSSITLOCALERTHEADER __RPC_FAR *LPEMSSITLOCALERTHEADER;

typedef struct  _tagEMSSITLOCALERTSIDESOLN
    {
    double dBias;
    double dBSdev;
    double dDrift;
    EMSTIME timeTCA;
    WORD wWindowFactor;
    WORD wIterations;
    double dCTA;
    int nNumPoints;
    int nServiceArea;
    int nAmbiguityRes;
    double dLatitude;
    double dLongitude;
    double dErrEllipseAngle;
    double dErrEllipseMajAxis;
    double dErrEllipseMinAxis;
    double dProbability;
    EMSTIME timeNextVisibility;
    double dConfidence;
    double dDataResSdev;
    double dDataResTrend;
    double dLatLongCorrCoeff;
    double dLatCorrCoeff;
    double dLongCorrCoeff;
    }	EMSSITLOCALERTSIDESOLN;

typedef struct _tagEMSSITLOCALERTSIDESOLN __RPC_FAR *LPEMSSITLOCALERTSIDESOLN;

typedef struct  _tagEMSSITLOCALERTSOLUTION
    {
    EMSSITLOCALERTHEADER hdr;
    EMSSITLOCALERTSIDESOLN sideA;
    EMSSITLOCALERTSIDESOLN sideB;
    }	EMSSITLOCALERTSOLUTION;

typedef struct _tagEMSSITLOCALERTSOLUTION __RPC_FAR *LPEMSSITLOCALERTSOLUTION;

struct  tagEMS605AData
    {
    /* [string] */ wchar_t __RPC_FAR *wszType;
    /* [string] */ wchar_t __RPC_FAR *wszSource;
    /* [string] */ wchar_t __RPC_FAR *wszStatus;
    };
typedef struct tagEMS605AData EMS605ADATA;

struct  tagEMSSIT215DATA
    {
    unsigned long ulSatID;
    unsigned long ulOrbitNumber;
    unsigned long ulOrbitVectors;
    EMSTIME timeOrbit;
    EMSTIME timeEffective;
    EMSVECTOR vOrbitPosition;
    EMSVECTOR vOrbitVelocity;
    };
typedef struct tagEMSSIT215DATA EMSSIT215DATA;

typedef struct tagEMSSIT215DATA __RPC_FAR *LPEMSSIT215DATA;

struct  tagEMSSIT255ADATA
    {
    ULONG ulSatID;
    ULONG ulOrbitNumber;
    ULONG ulNoradNumber;
    ULONG ulElementNumber;
    EMSTIME timeEpoch;
    double fXndt2o;
    double fXndd6o;
    double fBStar;
    int nReserved;
    double fInclination;
    double fRightAscNode;
    double fEccentricity;
    double fArgPerigee;
    double fMeanAnomaly;
    double fMeanMotion;
    };
typedef struct tagEMSSIT255ADATA EMSSIT255ADATA;

typedef struct tagEMSSIT255ADATA __RPC_FAR *LPEMSSIT255ADATA;


enum tagEMSSCHEDUSAGE
    {	EMSSchedUsageUnknown	= 0,
	EMSSchedUsageInstall	= 1,
	EMSSchedUsageAppend	= 2,
	EMSSchedUsageInfo	= 3,
	EMSSchedUsageValidate	= 4
    };
typedef enum tagEMSSCHEDUSAGE EMSSCHEDUSAGE;

struct  _tagEMSSIT260DATA
    {
    ULONG ulLutID;
    ULONG ulSatID;
    WORD wPassSchedOrigin;
    WORD wPassSchedStatus;
    WORD wPassProcessStatus;
    ULONG ulOrbitNumber;
    EMSTIME timeAOS;
    EMSTIME timeLOS;
    double dPrePassOffset;
    double dStartDataCollectionOffset;
    double dStopDataCollectionOffset;
    EMSDEGREES degMaxElevation;
    EMSDEGREES degAzimuthAOS;
    EMSDEGREES degAzimuthPeak;
    EMSDEGREES degAzimuthLOS;
    };
typedef struct _tagEMSSIT260DATA EMSSIT260DATA;

typedef struct _tagEMSSIT260DATA __RPC_FAR *LPEMSSIT260DATA;

struct  _tagEMSSIT260DATAEX
    {
    ULONG ulLutID;
    ULONG ulSatID;
    WORD wPassSchedOrigin;
    WORD wPassSchedStatus;
    WORD wPassProcessStatus;
    ULONG ulOrbitNumber;
    EMSTIME timeAOS;
    EMSTIME timeLOS;
    double dPrePassOffset;
    double dStartDataCollectionOffset;
    double dStopDataCollectionOffset;
    EMSDEGREES degMaxElevation;
    EMSDEGREES degAzimuthAOS;
    EMSDEGREES degAzimuthPeak;
    EMSDEGREES degAzimuthLOS;
    ULONG ulAntennaID;
    };
typedef struct _tagEMSSIT260DATAEX EMSSIT260DATAEX;

typedef struct _tagEMSSIT260DATAEX __RPC_FAR *LPEMSSIT260DATAEX;


enum _tagEMSMANOEUVRETYPE
    {	MANOEUVRETYPE_IP	= 1,
	MANOEUVRETYPE_OP	= 2
    };
typedef enum _tagEMSMANOEUVRETYPE EMSMANOEUVRETYPE;


enum _tagEMSMANOEUVRESTATUS
    {	MANOEUVRESTATUS_PL	= 1,
	MANOEUVRESTATUS_AC	= 2,
	MANOEUVRESTATUS_XX	= 3
    };
typedef enum _tagEMSMANOEUVRESTATUS EMSMANOEUVRESTATUS;

struct  _tagEMSMANOEUVREDATA
    {
    ULONG ulSatID;
    EMSMANOEUVRETYPE type;
    EMSTIME startTime;
    WORD wDuration;
    EMSMANOEUVRESTATUS status;
    };
typedef struct _tagEMSMANOEUVREDATA EMSMANOEUVREDATA;

struct  tagEMSSIT510DATA
    {
    ULONG ulSatID;
    double dFreqOffset;
    double dFreqDrift;
    EMSTIME timeCalibration;
    };
typedef struct tagEMSSIT510DATA EMSSIT510DATA;

typedef struct tagEMSSIT510DATA __RPC_FAR *LPEMSSIT510DATA;

struct  tagEMSSITABLDATA
    {
    int iLUTID;
    int iNumMsgs;
    int iNumBursts;
    int iWaveForm;
    INT64 i64BeaconID;
    EMSTIME timeFirst;
    EMSTIME timeLast;
    double dFrequency;
    double dLatitude;
    double dLongitude;
    double dMajorError;
    double dMinorError;
    double dHeading;
    double dProbability;
    double dLQF;
    double dMQF;
    double dFOANoise;
    double dTOANoise;
    BYTE acBeaconMsg[ 18 ];
    int aiSatIDs[ 16 ];
    int aiLutIDs[ 13 ];
    };
typedef struct tagEMSSITABLDATA EMSSITABLDATA;

typedef struct tagEMSSITABLDATA __RPC_FAR *LPEMSSITABLDATA;


EXTERN_C const IID IID_ISITTypes;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2B08F2F4-3DAA-428d-9C99-89FF2E009ECB")
    ISITTypes : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct ISITTypesVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISITTypes __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISITTypes __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISITTypes __RPC_FAR * This);
        
        END_INTERFACE
    } ISITTypesVtbl;

    interface ISITTypes
    {
        CONST_VTBL struct ISITTypesVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISITTypes_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISITTypes_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISITTypes_Release(This)	\
    (This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISITTypes_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_SITTypes_0011 */
/* [local] */ 


#pragma pack()


extern RPC_IF_HANDLE __MIDL_itf_SITTypes_0011_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_SITTypes_0011_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
