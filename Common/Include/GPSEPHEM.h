

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu Sep 13 14:15:50 2012
 */
/* Compiler settings for C:\dev\All_SAR\Common\Include\GPSEPHEM.IDL:
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

#ifndef __GPSEPHEM_h__
#define __GPSEPHEM_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IEMSGpsEphemeris_FWD_DEFINED__
#define __IEMSGpsEphemeris_FWD_DEFINED__
typedef interface IEMSGpsEphemeris IEMSGpsEphemeris;
#endif 	/* __IEMSGpsEphemeris_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_GPSEPHEM_0000_0000 */
/* [local] */ 

/********************************************************************
*	Module:			gpsephem.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Interface definition for GPS Ephemeris data
*						
*						
*						
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2005 by EMS Technologies, Inc.,
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

	0.0	2005/01/23	rvw	start

********************************************************************/
#ifndef INC_GPSEPHEM
#define INC_GPSEPHEM

// {E93E168D-B1CF-4499-8944-42531049A4E6}
DEFINE_GUID( IID_IEMSGpsEphemeris, 0xe93e168d, 0xb1cf, 0x4499, 0x89, 0x44, 0x42, 0x53, 0x10, 0x49, 0xa4, 0xe6);

#pragma pack(1)
typedef struct _tagEMSEPHEMERISDATA
    {
    ULONG ulSatPRN;
    double dTimeCollection;
    INT nWeekNum;
    BYTE cCodeL2;
    BYTE cL2PData;
    BYTE cSVAccRaw;
    BYTE cSVHealth;
    INT nIODC;
    double dTGD;
    double dTOC;
    double dAF2;
    double dAF1;
    double dAF0;
    double dSVAcc;
    BYTE cIODE;
    BYTE cFitInterval;
    double dCRS;
    double dDeltaN;
    double dM0;
    double dUC;
    double dE;
    double dCUS;
    double dSqrtA;
    double dTOE;
    double dCIC;
    double dOmegaO;
    double dCIS;
    double dIO;
    double dCrc;
    double dOmega;
    double dOmegaDot;
    double dIDot;
    double dAxis;
    double dN;
    double dR1ME2;
    double dOmegaN;
    double dODotN;
    } 	EMSEPHEMERISDATA;

typedef struct _tagEMSEPHEMERISDATA *LPEMSEPHEMERISDATA;

typedef struct _tagUTCCONVERSION
    {
    INT nA0;
    INT nA1;
    unsigned char cDelTime;
    BYTE cRefTime;
    BYTE cUTCRef;
    BYTE cWeekNb;
    BYTE cDayNb;
    unsigned char cLeapSec;
    } 	EMSUTCCONVERSION;

typedef struct _tagUTCCONVERSION *LPEMSUTCCONVERSION;

typedef struct _tagEMSSCALEDEPHEMERISDATA
    {
    INT nWeekNum;
    INT nIODC;
    BYTE cIODE;
    INT64 i64DeltaN;
    INT64 i64M0;
    INT64 i64UC;
    INT64 i64E;
    INT64 i64CUS;
    INT64 i64CRC;
    INT64 i64CRS;
    INT64 i64SqrtA;
    ULONG ulTOE;
    INT64 i64CIC;
    INT64 i64OmegaO;
    INT64 i64CIS;
    INT64 i64IO;
    INT64 i64Omega;
    INT64 i64OmegaDot;
    INT64 i64IDot;
    INT64 i64N;
    } 	EMSSCALEDEPHEMERISDATA;

typedef struct _tagEMSSCALEDEPHEMERISDATA *LPEMSSCALEDEPHEMERISDATA;

typedef 
enum _tagCONSTELLATION
    {	EMS_CONSTELLATION_UNKNOWN	= 0,
	EMS_CONSTELLATION_DASS	= 1,
	EMS_CONSTELLATION_GALILEO	= 2,
	EMS_CONSTELLATION_GLONASS	= 3
    } 	EMSCONSTELLATION;

typedef struct _tagEMSEPHEMERISDATA2
    {
    ULONG ulSatID;
    EMSCONSTELLATION constellation;
    EMSEPHEMERISDATA baseData;
    } 	EMSEPHEMERISDATA2;

typedef struct _tagEMSEPHEMERISDATA2 *LPEMSEPHEMERISDATA2;

typedef struct _tagEMSSCALEDEPHEMERISDATAEX
    {
    ULONG ulSatID;
    EMSCONSTELLATION constellation;
    EMSSCALEDEPHEMERISDATA baseData;
    } 	EMSSCALEDEPHEMERISDATAEX;

typedef struct _tagEMSSCALEDEPHEMERISDATAEX *LPEMSSCALEDEPHEMERISDATAEX;


#pragma pack()


extern RPC_IF_HANDLE __MIDL_itf_GPSEPHEM_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_GPSEPHEM_0000_0000_v0_0_s_ifspec;

#ifndef __IEMSGpsEphemeris_INTERFACE_DEFINED__
#define __IEMSGpsEphemeris_INTERFACE_DEFINED__

/* interface IEMSGpsEphemeris */
/* [object][unique][helpstring][uuid] */ 


EXTERN_C const IID IID_IEMSGpsEphemeris;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E93E168D-B1CF-4499-8944-42531049A4E6")
    IEMSGpsEphemeris : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetGpsEphemerisData( 
            /* [in] */ ULONG ulSatPRN,
            /* [out] */ EMSEPHEMERISDATA *lpData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEMSGpsEphemerisVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEMSGpsEphemeris * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEMSGpsEphemeris * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEMSGpsEphemeris * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetGpsEphemerisData )( 
            IEMSGpsEphemeris * This,
            /* [in] */ ULONG ulSatPRN,
            /* [out] */ EMSEPHEMERISDATA *lpData);
        
        END_INTERFACE
    } IEMSGpsEphemerisVtbl;

    interface IEMSGpsEphemeris
    {
        CONST_VTBL struct IEMSGpsEphemerisVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEMSGpsEphemeris_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEMSGpsEphemeris_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEMSGpsEphemeris_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEMSGpsEphemeris_GetGpsEphemerisData(This,ulSatPRN,lpData)	\
    ( (This)->lpVtbl -> GetGpsEphemerisData(This,ulSatPRN,lpData) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEMSGpsEphemeris_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_GPSEPHEM_0000_0001 */
/* [local] */ 

typedef /* [unique] */ IEMSGpsEphemeris *LPEMSGPSEPHEMERIS;

#endif // INC_GPSEPHEM


extern RPC_IF_HANDLE __MIDL_itf_GPSEPHEM_0000_0001_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_GPSEPHEM_0000_0001_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


