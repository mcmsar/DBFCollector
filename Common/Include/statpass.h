/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Apr 29 15:23:46 2008
 */
/* Compiler settings for ..\common\include\STATPASS.IDL:
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

#ifndef __STATPASS_h__
#define __STATPASS_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IEMSPassSummaryStatus_FWD_DEFINED__
#define __IEMSPassSummaryStatus_FWD_DEFINED__
typedef interface IEMSPassSummaryStatus IEMSPassSummaryStatus;
#endif 	/* __IEMSPassSummaryStatus_FWD_DEFINED__ */


#ifndef __IEMSPassSummaryStatus2_FWD_DEFINED__
#define __IEMSPassSummaryStatus2_FWD_DEFINED__
typedef interface IEMSPassSummaryStatus2 IEMSPassSummaryStatus2;
#endif 	/* __IEMSPassSummaryStatus2_FWD_DEFINED__ */


#ifndef __IEMSPassSummaryStatus3_FWD_DEFINED__
#define __IEMSPassSummaryStatus3_FWD_DEFINED__
typedef interface IEMSPassSummaryStatus3 IEMSPassSummaryStatus3;
#endif 	/* __IEMSPassSummaryStatus3_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "emstatus.h"
#include "emstrack.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_STATPASS_0000 */
/* [local] */ 

/********************************************************************
*	Module:			statpass.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Interface and data structures to access IEMSPassSummaryStatus
*						data
*						
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2001 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	01/03/22		rvw	start

********************************************************************/
#ifndef INC_STATPASS
#define INC_STATPASS

// {CD360656-E910-11d5-8D1E-009027912866}
DEFINE_GUID( IID_IEMSPassSummaryStatus, 0xcd360656, 0xe910, 0x11d5, 0x8d, 0x1e, 0x0, 0x90, 0x27, 0x91, 0x28, 0x66);
 
// {5FF57DEB-6485-49fd-9F46-6B09189730E4}
DEFINE_GUID( IID_IEMSPassSummaryStatus2, 0x5ff57deb, 0x6485, 0x49fd, 0x9f, 0x46, 0x6b, 0x9, 0x18, 0x97, 0x30, 0xe4);
 
// {12C998E7-EB80-43f8-8EF2-0057C51C7E5A}
DEFINE_GUID(IID_IEMSPassSummaryStatus3, 0x12c998e7, 0xeb80, 0x43f8, 0x8e, 0xf2, 0x0, 0x57, 0xc5, 0x1c, 0x7e, 0x5a);
 

#pragma pack(1)


extern RPC_IF_HANDLE __MIDL_itf_STATPASS_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_STATPASS_0000_v0_0_s_ifspec;

#ifndef __IEMSPassSummaryStatus_INTERFACE_DEFINED__
#define __IEMSPassSummaryStatus_INTERFACE_DEFINED__

/* interface IEMSPassSummaryStatus */
/* [unique][helpstring][uuid][object] */ 

typedef struct  _tagEMSPASSSUMMARYINFO
    {
    EMSSATELLITETRACK track;
    unsigned short uPassStatus;
    unsigned short uCarrierLossCount;
    WORD wSarpTotalFrames;
    WORD wValidSarpRecords;
    WORD wTotalCbc121Solutions;
    WORD wTotalCbc243Solutions;
    WORD wTotalCbc406Solutions;
    WORD wTotal406SarrSolutions;
    WORD wTotal406SarpSolutions;
    }	EMSPASSSUMMARYINFO;

typedef struct _tagEMSPASSSUMMARYINFO __RPC_FAR *LPEMSPASSSUMMARYINFO;


EXTERN_C const IID IID_IEMSPassSummaryStatus;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("CD360656-E910-11d5-8D1E-009027912866")
    IEMSPassSummaryStatus : public IEMSStatus
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ResetPassSummaryInfo( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPassSummaryInfo( 
            /* [in] */ EMSPASSSUMMARYINFO __RPC_FAR *lpInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPassSummaryInfo( 
            /* [out] */ EMSPASSSUMMARYINFO __RPC_FAR *lpInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSPassSummaryStatusVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSPassSummaryStatus __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSPassSummaryStatus __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSPassSummaryStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetPassSummaryInfo )( 
            IEMSPassSummaryStatus __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPassSummaryInfo )( 
            IEMSPassSummaryStatus __RPC_FAR * This,
            /* [in] */ EMSPASSSUMMARYINFO __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPassSummaryInfo )( 
            IEMSPassSummaryStatus __RPC_FAR * This,
            /* [out] */ EMSPASSSUMMARYINFO __RPC_FAR *lpInfo);
        
        END_INTERFACE
    } IEMSPassSummaryStatusVtbl;

    interface IEMSPassSummaryStatus
    {
        CONST_VTBL struct IEMSPassSummaryStatusVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSPassSummaryStatus_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSPassSummaryStatus_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSPassSummaryStatus_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IEMSPassSummaryStatus_ResetPassSummaryInfo(This)	\
    (This)->lpVtbl -> ResetPassSummaryInfo(This)

#define IEMSPassSummaryStatus_SetPassSummaryInfo(This,lpInfo)	\
    (This)->lpVtbl -> SetPassSummaryInfo(This,lpInfo)

#define IEMSPassSummaryStatus_GetPassSummaryInfo(This,lpInfo)	\
    (This)->lpVtbl -> GetPassSummaryInfo(This,lpInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSPassSummaryStatus_ResetPassSummaryInfo_Proxy( 
    IEMSPassSummaryStatus __RPC_FAR * This);


void __RPC_STUB IEMSPassSummaryStatus_ResetPassSummaryInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSPassSummaryStatus_SetPassSummaryInfo_Proxy( 
    IEMSPassSummaryStatus __RPC_FAR * This,
    /* [in] */ EMSPASSSUMMARYINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSPassSummaryStatus_SetPassSummaryInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSPassSummaryStatus_GetPassSummaryInfo_Proxy( 
    IEMSPassSummaryStatus __RPC_FAR * This,
    /* [out] */ EMSPASSSUMMARYINFO __RPC_FAR *lpInfo);


void __RPC_STUB IEMSPassSummaryStatus_GetPassSummaryInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSPassSummaryStatus_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_STATPASS_0026 */
/* [local] */ 

typedef /* [unique] */ IEMSPassSummaryStatus __RPC_FAR *LPEMSPASSSUMMARYSTATUS;



extern RPC_IF_HANDLE __MIDL_itf_STATPASS_0026_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_STATPASS_0026_v0_0_s_ifspec;

#ifndef __IEMSPassSummaryStatus2_INTERFACE_DEFINED__
#define __IEMSPassSummaryStatus2_INTERFACE_DEFINED__

/* interface IEMSPassSummaryStatus2 */
/* [unique][helpstring][uuid][object] */ 

typedef struct  _tagEMSPASSSUMMARYINFO2
    {
    EMSSATELLITETRACK thisTrack;
    EMSSATELLITETRACK nextTrack;
    WORD wSecsDuration;
    WORD wSecsCollecting;
    WORD wPercentageCollecting;
    INT nPDSRecoveryRate;
    WORD wFramesMissed;
    INT nTotalPDSCount;
    INT nDistinctPDSCount;
    WORD wSarrMessages;
    EMSTIME timeOrbitEpoch;
    EMSVECTOR vOrbitPosition;
    EMSVECTOR vOrbitVelocity;
    WORD wOrbitUpdateStatus;
    float fOrbitPositionOffset;
    float fOrbitVelocityOffset;
    EMSTIME timeCalibration;
    EMSTIME timeRollover;
    float fUSOFreq;
    float fSARR406FreqOff;
    EMSTIME timeSolnProcessing;
    WORD w121Transmitters;
    WORD w243Transmitters;
    WORD w406Interferers;
    WORD w406LocatedBeacons;
    WORD w406UnlocatedBeacons;
    WORD wUnlocatedAlerts;
    WORD wWarnings;
    WORD wAlarms;
    }	EMSPASSSUMMARYINFO2;

typedef struct _tagEMSPASSSUMMARYINFO2 __RPC_FAR *LPEMSPASSSUMMARYINFO2;


EXTERN_C const IID IID_IEMSPassSummaryStatus2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5FF57DEB-6485-49fd-9F46-6B09189730E4")
    IEMSPassSummaryStatus2 : public IEMSPassSummaryStatus
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ResetPassSummary2Info( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPassSummary2Info( 
            /* [in] */ EMSPASSSUMMARYINFO2 __RPC_FAR *lpInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPassSummary2Info( 
            /* [out] */ EMSPASSSUMMARYINFO2 __RPC_FAR *lpInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSPassSummaryStatus2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSPassSummaryStatus2 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSPassSummaryStatus2 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSPassSummaryStatus2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetPassSummaryInfo )( 
            IEMSPassSummaryStatus2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPassSummaryInfo )( 
            IEMSPassSummaryStatus2 __RPC_FAR * This,
            /* [in] */ EMSPASSSUMMARYINFO __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPassSummaryInfo )( 
            IEMSPassSummaryStatus2 __RPC_FAR * This,
            /* [out] */ EMSPASSSUMMARYINFO __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetPassSummary2Info )( 
            IEMSPassSummaryStatus2 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPassSummary2Info )( 
            IEMSPassSummaryStatus2 __RPC_FAR * This,
            /* [in] */ EMSPASSSUMMARYINFO2 __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPassSummary2Info )( 
            IEMSPassSummaryStatus2 __RPC_FAR * This,
            /* [out] */ EMSPASSSUMMARYINFO2 __RPC_FAR *lpInfo);
        
        END_INTERFACE
    } IEMSPassSummaryStatus2Vtbl;

    interface IEMSPassSummaryStatus2
    {
        CONST_VTBL struct IEMSPassSummaryStatus2Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSPassSummaryStatus2_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSPassSummaryStatus2_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSPassSummaryStatus2_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IEMSPassSummaryStatus2_ResetPassSummaryInfo(This)	\
    (This)->lpVtbl -> ResetPassSummaryInfo(This)

#define IEMSPassSummaryStatus2_SetPassSummaryInfo(This,lpInfo)	\
    (This)->lpVtbl -> SetPassSummaryInfo(This,lpInfo)

#define IEMSPassSummaryStatus2_GetPassSummaryInfo(This,lpInfo)	\
    (This)->lpVtbl -> GetPassSummaryInfo(This,lpInfo)


#define IEMSPassSummaryStatus2_ResetPassSummary2Info(This)	\
    (This)->lpVtbl -> ResetPassSummary2Info(This)

#define IEMSPassSummaryStatus2_SetPassSummary2Info(This,lpInfo)	\
    (This)->lpVtbl -> SetPassSummary2Info(This,lpInfo)

#define IEMSPassSummaryStatus2_GetPassSummary2Info(This,lpInfo)	\
    (This)->lpVtbl -> GetPassSummary2Info(This,lpInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSPassSummaryStatus2_ResetPassSummary2Info_Proxy( 
    IEMSPassSummaryStatus2 __RPC_FAR * This);


void __RPC_STUB IEMSPassSummaryStatus2_ResetPassSummary2Info_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSPassSummaryStatus2_SetPassSummary2Info_Proxy( 
    IEMSPassSummaryStatus2 __RPC_FAR * This,
    /* [in] */ EMSPASSSUMMARYINFO2 __RPC_FAR *lpInfo);


void __RPC_STUB IEMSPassSummaryStatus2_SetPassSummary2Info_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSPassSummaryStatus2_GetPassSummary2Info_Proxy( 
    IEMSPassSummaryStatus2 __RPC_FAR * This,
    /* [out] */ EMSPASSSUMMARYINFO2 __RPC_FAR *lpInfo);


void __RPC_STUB IEMSPassSummaryStatus2_GetPassSummary2Info_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSPassSummaryStatus2_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_STATPASS_0027 */
/* [local] */ 

typedef /* [unique] */ IEMSPassSummaryStatus2 __RPC_FAR *LPEMSPASSSUMMARYSTATUS2;



extern RPC_IF_HANDLE __MIDL_itf_STATPASS_0027_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_STATPASS_0027_v0_0_s_ifspec;

#ifndef __IEMSPassSummaryStatus3_INTERFACE_DEFINED__
#define __IEMSPassSummaryStatus3_INTERFACE_DEFINED__

/* interface IEMSPassSummaryStatus3 */
/* [unique][helpstring][uuid][object] */ 

typedef struct  _tagEMSPASSSUMMARYINFO3
    {
    EMSSATELLITETRACK thisTrack;
    EMSSATELLITETRACK nextTrack;
    WORD wSecsDuration;
    WORD wSecsCollecting;
    WORD wPercentageCollecting;
    INT nPDSRecoveryRate;
    WORD wFramesMissed;
    INT nTotalPDSCount;
    INT nDistinctPDSCount;
    WORD wSarrMessages;
    EMSTIME timeOrbitEpoch;
    EMSVECTOR vOrbitPosition;
    EMSVECTOR vOrbitVelocity;
    WORD wOrbitUpdateStatus;
    float fOrbitPositionOffset;
    float fOrbitVelocityOffset;
    EMSTIME timeCalibration;
    EMSTIME timeRollover;
    double dUSOFreq;
    double dSARR406FreqOff;
    EMSTIME timeSolnProcessing;
    WORD w121Transmitters;
    WORD w243Transmitters;
    WORD w406Interferers;
    WORD w406LocatedBeacons;
    WORD w406UnlocatedBeacons;
    WORD wUnlocatedAlerts;
    WORD wWarnings;
    WORD wAlarms;
    EMSTIME timeLastClockSync;
    EMSTIME timeMsgSARPCalibNewest;
    EMSTIME timeMsgSARPCalibOldest;
    WORD wMedianLocnErrorSampleCount;
    double dMedianLocnError;
    ULONG ulOrbitNumberAtEpoch;
    WORD wGeneralStatus;
    double dUnused1;
    double dUnused2;
    double dUnused3;
    double dUnused4;
    INT iUnused1;
    INT iUnused2;
    EMSTIME timeUnused1;
    EMSTIME timeUnused2;
    }	EMSPASSSUMMARYINFO3;

typedef struct _tagEMSPASSSUMMARYINFO3 __RPC_FAR *LPEMSPASSSUMMARYINFO3;


EXTERN_C const IID IID_IEMSPassSummaryStatus3;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("12C998E7-EB80-43f8-8EF2-0057C51C7E5A")
    IEMSPassSummaryStatus3 : public IEMSPassSummaryStatus
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE ResetPassSummary3Info( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetPassSummary3Info( 
            /* [in] */ EMSPASSSUMMARYINFO3 __RPC_FAR *lpInfo) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPassSummary3Info( 
            /* [out] */ EMSPASSSUMMARYINFO3 __RPC_FAR *lpInfo) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSPassSummaryStatus3Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IEMSPassSummaryStatus3 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IEMSPassSummaryStatus3 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IEMSPassSummaryStatus3 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetPassSummaryInfo )( 
            IEMSPassSummaryStatus3 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPassSummaryInfo )( 
            IEMSPassSummaryStatus3 __RPC_FAR * This,
            /* [in] */ EMSPASSSUMMARYINFO __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPassSummaryInfo )( 
            IEMSPassSummaryStatus3 __RPC_FAR * This,
            /* [out] */ EMSPASSSUMMARYINFO __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ResetPassSummary3Info )( 
            IEMSPassSummaryStatus3 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetPassSummary3Info )( 
            IEMSPassSummaryStatus3 __RPC_FAR * This,
            /* [in] */ EMSPASSSUMMARYINFO3 __RPC_FAR *lpInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPassSummary3Info )( 
            IEMSPassSummaryStatus3 __RPC_FAR * This,
            /* [out] */ EMSPASSSUMMARYINFO3 __RPC_FAR *lpInfo);
        
        END_INTERFACE
    } IEMSPassSummaryStatus3Vtbl;

    interface IEMSPassSummaryStatus3
    {
        CONST_VTBL struct IEMSPassSummaryStatus3Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSPassSummaryStatus3_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEMSPassSummaryStatus3_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEMSPassSummaryStatus3_Release(This)	\
    (This)->lpVtbl -> Release(This)



#define IEMSPassSummaryStatus3_ResetPassSummaryInfo(This)	\
    (This)->lpVtbl -> ResetPassSummaryInfo(This)

#define IEMSPassSummaryStatus3_SetPassSummaryInfo(This,lpInfo)	\
    (This)->lpVtbl -> SetPassSummaryInfo(This,lpInfo)

#define IEMSPassSummaryStatus3_GetPassSummaryInfo(This,lpInfo)	\
    (This)->lpVtbl -> GetPassSummaryInfo(This,lpInfo)


#define IEMSPassSummaryStatus3_ResetPassSummary3Info(This)	\
    (This)->lpVtbl -> ResetPassSummary3Info(This)

#define IEMSPassSummaryStatus3_SetPassSummary3Info(This,lpInfo)	\
    (This)->lpVtbl -> SetPassSummary3Info(This,lpInfo)

#define IEMSPassSummaryStatus3_GetPassSummary3Info(This,lpInfo)	\
    (This)->lpVtbl -> GetPassSummary3Info(This,lpInfo)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEMSPassSummaryStatus3_ResetPassSummary3Info_Proxy( 
    IEMSPassSummaryStatus3 __RPC_FAR * This);


void __RPC_STUB IEMSPassSummaryStatus3_ResetPassSummary3Info_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSPassSummaryStatus3_SetPassSummary3Info_Proxy( 
    IEMSPassSummaryStatus3 __RPC_FAR * This,
    /* [in] */ EMSPASSSUMMARYINFO3 __RPC_FAR *lpInfo);


void __RPC_STUB IEMSPassSummaryStatus3_SetPassSummary3Info_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEMSPassSummaryStatus3_GetPassSummary3Info_Proxy( 
    IEMSPassSummaryStatus3 __RPC_FAR * This,
    /* [out] */ EMSPASSSUMMARYINFO3 __RPC_FAR *lpInfo);


void __RPC_STUB IEMSPassSummaryStatus3_GetPassSummary3Info_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEMSPassSummaryStatus3_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_STATPASS_0028 */
/* [local] */ 

typedef /* [unique] */ IEMSPassSummaryStatus3 __RPC_FAR *LPEMSPASSSUMMARYSTATUS3;


#pragma pack()
#endif //INC_STATPASS


extern RPC_IF_HANDLE __MIDL_itf_STATPASS_0028_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_STATPASS_0028_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
