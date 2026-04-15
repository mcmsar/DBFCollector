/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Feb 10 13:47:30 2004
 */
/* Compiler settings for ..\common\include\EMSCC.IDL:
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

#ifndef __EMSCC_h__
#define __EMSCC_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSCommand_FWD_DEFINED__
#define __IEMSCommand_FWD_DEFINED__
typedef interface IEMSCommand IEMSCommand;
#endif 	/* __IEMSCommand_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "EMSTYPEX.h"
#include "emscommontypes.h"
#include "ialertgen.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_EMSCC_0000 */
/* [local] */ 

// {3E3B73A3-CAC6-43e5-A255-B1BEA6A63C76}
DEFINE_GUID( CLSID_EMSCC, 0x3e3b73a3, 0xcac6, 0x43e5, 0xa2, 0x55, 0xb1, 0xbe, 0xa6, 0xa6, 0x3c, 0x76);
// {96EF00A3-F66C-49cc-BA3C-A0D70C58F45F}
DEFINE_GUID( IID_IEMSCommand, 0x96ef00a3, 0xf66c, 0x49cc, 0xba, 0x3c, 0xa0, 0xd7, 0xc, 0x58, 0xf4, 0x5f);
#define	MAX_LOCATION_KEYS	( 256 )

typedef 
enum tagCmdType
    {	CMD_UNKNOWN	= 0,
	CMD_OPCMD	= 1,
	CMD_RETRANSMIT	= 2,
	CMD_ORBV	= 3,
	CMD_TLE	= 4,
	CMD_PASS_SCHED	= 5,
	CMD_SARP_CALIB	= 6,
	CMD_SARR_CALIB	= 7,
	CMD_STARTUP	= 8,
	CMD_GEN_ALERT	= 9,
	CMD_LAST	= CMD_GEN_ALERT + 1
    }	EMSCMDTYPE;

typedef struct  tagEMSLocationKey
    {
    EMSTIME timestamp;
    ULONG ulLutID;
    __int64 i64BeaconID;
    unsigned short usType;
    }	EMSLOCATIONKEY;

typedef struct  tagCmdGenAlert
    {
    ULONG ulNumDestinations;
    ULONG aulDestinationIDs[ 32 ];
    ULONG ulNumLocationsKeys;
    EMSLOCATIONKEY locationKey[ 256 ];
    DWORD dwFlags;
    /* [string] */ unsigned char szUserID[ 21 ];
    }	EMSCMDGENALERT;

typedef struct  tagCmdRetransmit
    {
    ULONG ulSendToID;
    ULONG ulSeqStart;
    ULONG ulSeqEnd;
    }	EMSCMDRETRANSMIT;

typedef struct  tagCmdOrbitVector
    {
    ULONG ulSitID;
    EMSSITCONTROLCODE eCtrlCode;
    EMSSIT215DATA orbVector;
    }	EMSCMDORBITVECTOR;

typedef struct  tagCmdTLE
    {
    EMSSITCONTROLCODE eCtrlCode;
    EMSSIT255ADATA tleData;
    }	EMSCMDTLE;

typedef struct  tagCmdPassSched
    {
    EMSSCHEDUSAGE eUsage;
    EMSSATELLITETRACK satTrack;
    }	EMSCMDPASSSCHED;

typedef struct  tagCmdSARPCalib
    {
    ULONG ulSit;
    EMSSITCONTROLCODE eCtrlCode;
    ULONG ulMsgRequestNumber;
    ULONG ulSatID;
    ULONG ulPassID;
    EMSTIME timeRollover;
    double dUSOFrequency;
    }	EMSCMDSARPCALIB;

typedef struct  tagCmdSARRCalib
    {
    ULONG ulSit;
    EMSSITCONTROLCODE eCtrlCode;
    ULONG ulMsgRequestNumber;
    EMSSARRCALIBDATA sarrCalib;
    }	EMSCMDSARRCALIB;

typedef struct  tagCmdStartup
    {
    ULONG ulFromID;
    }	EMSCMDSTARTUP;

typedef struct  tagCCInput
    {
    EMSTRIGGER eTrigger;
    EMSCMDTYPE eCmdType;
    ULONG ulSourceID;
    ULONG ulCmdMsgSequence;
    /* [switch_is][switch_type] */ union 
        {
        /* [case()] */ EMSOPERATORCMD cmdOp;
        /* [case()] */ EMSCMDRETRANSMIT cmdRetransmit;
        /* [case()] */ EMSCMDORBITVECTOR cmdOrbV;
        /* [case()] */ EMSCMDTLE cmdTLE;
        /* [case()] */ EMSCMDPASSSCHED cmdPassSched;
        /* [case()] */ EMSCMDSARPCALIB cmdSarpCalib;
        /* [case()] */ EMSCMDSARRCALIB cmdSarrCalib;
        /* [case()] */ EMSCMDSTARTUP cmdStartup;
        /* [case()] */ EMSCMDGENALERT cmdGenAlert;
        /* [default] */  /* Empty union arm */ 
        }	exData;
    }	EMSCCSPEC;



extern RPC_IF_HANDLE __MIDL_itf_EMSCC_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSCC_0000_v0_0_s_ifspec;

#ifndef __IEMSCommand_INTERFACE_DEFINED__
#define __IEMSCommand_INTERFACE_DEFINED__

/* interface IEMSCommand */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IEMSCommand;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("96EF00A3-F66C-49cc-BA3C-A0D70C58F45F")
    IEMSCommand : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SendCommand( 
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ ULONG ulCommandMsgSequence,
            /* [in] */ ULONG ulSourceID,
            /* [in] */ EMSOPERATORCMD __RPC_FAR *pCommand) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RequestRetransmitMsgs( 
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ ULONG ulCommandMsgSequence,
            /* [in] */ ULONG ulSendToID,
            /* [in] */ ULONG ulSeqStart,
            /* [in] */ ULONG ulSeqEnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendOrbitVector( 
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ ULONG ulCommandMsgSequence,
            /* [in] */ ULONG ulSourceID,
            /* [in] */ ULONG ulSitID,
            /* [in] */ EMSSITCONTROLCODE eCtrlCode,
            /* [in] */ ULONG ulOrbits,
            /* [size_is][in] */ EMSSIT215DATA __RPC_FAR *__RPC_FAR *apOrbVectors) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendTLE( 
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ ULONG ulCommandMsgSequence,
            /* [in] */ ULONG ulSourceID,
            /* [in] */ EMSSITCONTROLCODE eCtrlCode,
            /* [in] */ ULONG ulOrbits,
            /* [size_is][in] */ EMSSIT255ADATA __RPC_FAR *__RPC_FAR *apTLEs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendPassSchedule( 
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ ULONG ulCommandMsgSequence,
            /* [in] */ ULONG ulSourceID,
            /* [in] */ EMSSCHEDUSAGE eUsage,
            /* [in] */ LONG lSatelliteCount,
            /* [in] */ ULONG ulPasses,
            /* [size_is][in] */ EMSSATELLITETRACK __RPC_FAR *__RPC_FAR *apPasses) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendSARPCalib( 
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ ULONG ulCommandMsgSequence,
            /* [in] */ ULONG ulSourceID,
            /* [in] */ ULONG ulSit,
            /* [in] */ EMSSITCONTROLCODE eCtrlCode,
            /* [in] */ ULONG ulMsgRequestNumber,
            /* [in] */ ULONG ulSatID,
            /* [in] */ ULONG ulPassID,
            /* [in] */ EMSTIME timeRollover,
            /* [in] */ double dUSOFrequency) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendSARRCalib( 
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ ULONG ulCommandMsgSequence,
            /* [in] */ ULONG ulSourceID,
            /* [in] */ ULONG ulSit,
            /* [in] */ EMSSITCONTROLCODE eCtrlCode,
            /* [in] */ ULONG ulMsgRequestNumber,
            /* [in] */ ULONG ulSatellites,
            /* [size_is][in] */ EMSSARRCALIBDATA __RPC_FAR *__RPC_FAR *apSarrData) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SendStartUp( 
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ ULONG ulCommandMsgSequence,
            /* [in] */ ULONG ulFromID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GenerateAlerts( 
            /* [in] */ ULONG ulSourceID,
            /* [in] */ ULONG ulNumDestinations,
            /* [size_is][in] */ ULONG __RPC_FAR *ulDestinationIDs,
            /* [in] */ ULONG ulLocations,
            /* [size_is][in] */ EMSLOCATIONKEY __RPC_FAR *ulLocationKeys,
            /* [string][unique][in] */ unsigned char __RPC_FAR szUserID[ 21 ]) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSCommandVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSCommand __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSCommand __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSCommand __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendCommand )( 
            IEMSCommand __RPC_FAR * This,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ ULONG ulCommandMsgSequence,
            /* [in] */ ULONG ulSourceID,
            /* [in] */ EMSOPERATORCMD __RPC_FAR *pCommand);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RequestRetransmitMsgs )( 
            IEMSCommand __RPC_FAR * This,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ ULONG ulCommandMsgSequence,
            /* [in] */ ULONG ulSendToID,
            /* [in] */ ULONG ulSeqStart,
            /* [in] */ ULONG ulSeqEnd);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendOrbitVector )( 
            IEMSCommand __RPC_FAR * This,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ ULONG ulCommandMsgSequence,
            /* [in] */ ULONG ulSourceID,
            /* [in] */ ULONG ulSitID,
            /* [in] */ EMSSITCONTROLCODE eCtrlCode,
            /* [in] */ ULONG ulOrbits,
            /* [size_is][in] */ EMSSIT215DATA __RPC_FAR *__RPC_FAR *apOrbVectors);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendTLE )( 
            IEMSCommand __RPC_FAR * This,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ ULONG ulCommandMsgSequence,
            /* [in] */ ULONG ulSourceID,
            /* [in] */ EMSSITCONTROLCODE eCtrlCode,
            /* [in] */ ULONG ulOrbits,
            /* [size_is][in] */ EMSSIT255ADATA __RPC_FAR *__RPC_FAR *apTLEs);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendPassSchedule )( 
            IEMSCommand __RPC_FAR * This,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ ULONG ulCommandMsgSequence,
            /* [in] */ ULONG ulSourceID,
            /* [in] */ EMSSCHEDUSAGE eUsage,
            /* [in] */ LONG lSatelliteCount,
            /* [in] */ ULONG ulPasses,
            /* [size_is][in] */ EMSSATELLITETRACK __RPC_FAR *__RPC_FAR *apPasses);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendSARPCalib )( 
            IEMSCommand __RPC_FAR * This,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ ULONG ulCommandMsgSequence,
            /* [in] */ ULONG ulSourceID,
            /* [in] */ ULONG ulSit,
            /* [in] */ EMSSITCONTROLCODE eCtrlCode,
            /* [in] */ ULONG ulMsgRequestNumber,
            /* [in] */ ULONG ulSatID,
            /* [in] */ ULONG ulPassID,
            /* [in] */ EMSTIME timeRollover,
            /* [in] */ double dUSOFrequency);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendSARRCalib )( 
            IEMSCommand __RPC_FAR * This,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ ULONG ulCommandMsgSequence,
            /* [in] */ ULONG ulSourceID,
            /* [in] */ ULONG ulSit,
            /* [in] */ EMSSITCONTROLCODE eCtrlCode,
            /* [in] */ ULONG ulMsgRequestNumber,
            /* [in] */ ULONG ulSatellites,
            /* [size_is][in] */ EMSSARRCALIBDATA __RPC_FAR *__RPC_FAR *apSarrData);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SendStartUp )( 
            IEMSCommand __RPC_FAR * This,
            /* [in] */ EMSTRIGGER eTrigger,
            /* [in] */ ULONG ulCommandMsgSequence,
            /* [in] */ ULONG ulFromID);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GenerateAlerts )( 
            IEMSCommand __RPC_FAR * This,
            /* [in] */ ULONG ulSourceID,
            /* [in] */ ULONG ulNumDestinations,
            /* [size_is][in] */ ULONG __RPC_FAR *ulDestinationIDs,
            /* [in] */ ULONG ulLocations,
            /* [size_is][in] */ EMSLOCATIONKEY __RPC_FAR *ulLocationKeys,
            /* [string][unique][in] */ unsigned char __RPC_FAR szUserID[ 21 ]);
        
        END_INTERFACE
    } IEMSCommandVtbl;

    interface IEMSCommand
    {
        CONST_VTBL struct IEMSCommandVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSCommand_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSCommand_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSCommand_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEMSCommand_SendCommand(This,eTrigger,ulCommandMsgSequence,ulSourceID,pCommand)	\
    (This)->lpVtbl -> SendCommand(This,eTrigger,ulCommandMsgSequence,ulSourceID,pCommand)

#define IEMSCommand_RequestRetransmitMsgs(This,eTrigger,ulCommandMsgSequence,ulSendToID,ulSeqStart,ulSeqEnd)	\
    (This)->lpVtbl -> RequestRetransmitMsgs(This,eTrigger,ulCommandMsgSequence,ulSendToID,ulSeqStart,ulSeqEnd)

#define IEMSCommand_SendOrbitVector(This,eTrigger,ulCommandMsgSequence,ulSourceID,ulSitID,eCtrlCode,ulOrbits,apOrbVectors)	\
    (This)->lpVtbl -> SendOrbitVector(This,eTrigger,ulCommandMsgSequence,ulSourceID,ulSitID,eCtrlCode,ulOrbits,apOrbVectors)

#define IEMSCommand_SendTLE(This,eTrigger,ulCommandMsgSequence,ulSourceID,eCtrlCode,ulOrbits,apTLEs)	\
    (This)->lpVtbl -> SendTLE(This,eTrigger,ulCommandMsgSequence,ulSourceID,eCtrlCode,ulOrbits,apTLEs)

#define IEMSCommand_SendPassSchedule(This,eTrigger,ulCommandMsgSequence,ulSourceID,eUsage,lSatelliteCount,ulPasses,apPasses)	\
    (This)->lpVtbl -> SendPassSchedule(This,eTrigger,ulCommandMsgSequence,ulSourceID,eUsage,lSatelliteCount,ulPasses,apPasses)

#define IEMSCommand_SendSARPCalib(This,eTrigger,ulCommandMsgSequence,ulSourceID,ulSit,eCtrlCode,ulMsgRequestNumber,ulSatID,ulPassID,timeRollover,dUSOFrequency)	\
    (This)->lpVtbl -> SendSARPCalib(This,eTrigger,ulCommandMsgSequence,ulSourceID,ulSit,eCtrlCode,ulMsgRequestNumber,ulSatID,ulPassID,timeRollover,dUSOFrequency)

#define IEMSCommand_SendSARRCalib(This,eTrigger,ulCommandMsgSequence,ulSourceID,ulSit,eCtrlCode,ulMsgRequestNumber,ulSatellites,apSarrData)	\
    (This)->lpVtbl -> SendSARRCalib(This,eTrigger,ulCommandMsgSequence,ulSourceID,ulSit,eCtrlCode,ulMsgRequestNumber,ulSatellites,apSarrData)

#define IEMSCommand_SendStartUp(This,eTrigger,ulCommandMsgSequence,ulFromID)	\
    (This)->lpVtbl -> SendStartUp(This,eTrigger,ulCommandMsgSequence,ulFromID)

#define IEMSCommand_GenerateAlerts(This,ulSourceID,ulNumDestinations,ulDestinationIDs,ulLocations,ulLocationKeys,szUserID)	\
    (This)->lpVtbl -> GenerateAlerts(This,ulSourceID,ulNumDestinations,ulDestinationIDs,ulLocations,ulLocationKeys,szUserID)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSCommand_SendCommand_Proxy( 
    IEMSCommand __RPC_FAR * This,
    /* [in] */ EMSTRIGGER eTrigger,
    /* [in] */ ULONG ulCommandMsgSequence,
    /* [in] */ ULONG ulSourceID,
    /* [in] */ EMSOPERATORCMD __RPC_FAR *pCommand);


void __RPC_STUB IEMSCommand_SendCommand_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSCommand_RequestRetransmitMsgs_Proxy( 
    IEMSCommand __RPC_FAR * This,
    /* [in] */ EMSTRIGGER eTrigger,
    /* [in] */ ULONG ulCommandMsgSequence,
    /* [in] */ ULONG ulSendToID,
    /* [in] */ ULONG ulSeqStart,
    /* [in] */ ULONG ulSeqEnd);


void __RPC_STUB IEMSCommand_RequestRetransmitMsgs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSCommand_SendOrbitVector_Proxy( 
    IEMSCommand __RPC_FAR * This,
    /* [in] */ EMSTRIGGER eTrigger,
    /* [in] */ ULONG ulCommandMsgSequence,
    /* [in] */ ULONG ulSourceID,
    /* [in] */ ULONG ulSitID,
    /* [in] */ EMSSITCONTROLCODE eCtrlCode,
    /* [in] */ ULONG ulOrbits,
    /* [size_is][in] */ EMSSIT215DATA __RPC_FAR *__RPC_FAR *apOrbVectors);


void __RPC_STUB IEMSCommand_SendOrbitVector_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSCommand_SendTLE_Proxy( 
    IEMSCommand __RPC_FAR * This,
    /* [in] */ EMSTRIGGER eTrigger,
    /* [in] */ ULONG ulCommandMsgSequence,
    /* [in] */ ULONG ulSourceID,
    /* [in] */ EMSSITCONTROLCODE eCtrlCode,
    /* [in] */ ULONG ulOrbits,
    /* [size_is][in] */ EMSSIT255ADATA __RPC_FAR *__RPC_FAR *apTLEs);


void __RPC_STUB IEMSCommand_SendTLE_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSCommand_SendPassSchedule_Proxy( 
    IEMSCommand __RPC_FAR * This,
    /* [in] */ EMSTRIGGER eTrigger,
    /* [in] */ ULONG ulCommandMsgSequence,
    /* [in] */ ULONG ulSourceID,
    /* [in] */ EMSSCHEDUSAGE eUsage,
    /* [in] */ LONG lSatelliteCount,
    /* [in] */ ULONG ulPasses,
    /* [size_is][in] */ EMSSATELLITETRACK __RPC_FAR *__RPC_FAR *apPasses);


void __RPC_STUB IEMSCommand_SendPassSchedule_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSCommand_SendSARPCalib_Proxy( 
    IEMSCommand __RPC_FAR * This,
    /* [in] */ EMSTRIGGER eTrigger,
    /* [in] */ ULONG ulCommandMsgSequence,
    /* [in] */ ULONG ulSourceID,
    /* [in] */ ULONG ulSit,
    /* [in] */ EMSSITCONTROLCODE eCtrlCode,
    /* [in] */ ULONG ulMsgRequestNumber,
    /* [in] */ ULONG ulSatID,
    /* [in] */ ULONG ulPassID,
    /* [in] */ EMSTIME timeRollover,
    /* [in] */ double dUSOFrequency);


void __RPC_STUB IEMSCommand_SendSARPCalib_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSCommand_SendSARRCalib_Proxy( 
    IEMSCommand __RPC_FAR * This,
    /* [in] */ EMSTRIGGER eTrigger,
    /* [in] */ ULONG ulCommandMsgSequence,
    /* [in] */ ULONG ulSourceID,
    /* [in] */ ULONG ulSit,
    /* [in] */ EMSSITCONTROLCODE eCtrlCode,
    /* [in] */ ULONG ulMsgRequestNumber,
    /* [in] */ ULONG ulSatellites,
    /* [size_is][in] */ EMSSARRCALIBDATA __RPC_FAR *__RPC_FAR *apSarrData);


void __RPC_STUB IEMSCommand_SendSARRCalib_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSCommand_SendStartUp_Proxy( 
    IEMSCommand __RPC_FAR * This,
    /* [in] */ EMSTRIGGER eTrigger,
    /* [in] */ ULONG ulCommandMsgSequence,
    /* [in] */ ULONG ulFromID);


void __RPC_STUB IEMSCommand_SendStartUp_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSCommand_GenerateAlerts_Proxy( 
    IEMSCommand __RPC_FAR * This,
    /* [in] */ ULONG ulSourceID,
    /* [in] */ ULONG ulNumDestinations,
    /* [size_is][in] */ ULONG __RPC_FAR *ulDestinationIDs,
    /* [in] */ ULONG ulLocations,
    /* [size_is][in] */ EMSLOCATIONKEY __RPC_FAR *ulLocationKeys,
    /* [string][unique][in] */ unsigned char __RPC_FAR szUserID[ 21 ]);


void __RPC_STUB IEMSCommand_GenerateAlerts_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSCommand_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_EMSCC_0209 */
/* [local] */ 

typedef IEMSCommand __RPC_FAR *LPEMSCOMMAND;



extern RPC_IF_HANDLE __MIDL_itf_EMSCC_0209_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_EMSCC_0209_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
