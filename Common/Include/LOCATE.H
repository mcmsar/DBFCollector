

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0500 */
/* at Mon Dec 19 21:36:15 2011
 */
/* Compiler settings for d:\dev\LUT600\Common\Include\locate.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

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


#ifndef __locate_h__
#define __locate_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_locate_0000_0000 */
/* [local] */ 

/********************************************************************
*	Module:			locate.h 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	data structure used to describe the output of the 
*						location process ( to be used by both CBC & 406 data )
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

	0.0	01/03/22		rvw		start
	0.1	02/10/05		rcr		addition of DOA data types

********************************************************************/
#ifndef INC_LOCATE
#define INC_LOCATE


extern RPC_IF_HANDLE __MIDL_itf_locate_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_locate_0000_0000_v0_0_s_ifspec;

#ifndef __IEMSLOCATEdata_INTERFACE_DEFINED__
#define __IEMSLOCATEdata_INTERFACE_DEFINED__

/* interface IEMSLOCATEdata */
/* [unique][helpstring][uuid] */ 


#pragma pack(1)
#define EMSBEACONMSGLEN ( 18 ) // ie 144 bits
#define EMSMAXSATIDS	( 128 )
#define EMSMAXLUTIDS	( 128 )
#define EMS_LOCATE_COVARMATRIX_LENGTH (10) 
#define EMS_LOCATE_MAX_ITERATIONS_FLAG (0x8000) 
#define EMS_LOCATE_WINDOWFACTOR_MASK 		( 0x0FFF )
#define EMS_LOCATE_WINDOWFACTOR_LOCAL_FLAG ( 0x8000 )
typedef 
enum _tagEMSLOCATETYPE
    {	EMSLOCTYPE_CBC	= 0x10,
	EMSLOCTYPE_406_MERGE	= 0x8,
	EMSLOCTYPE_406	= 0x20,
	EMSLOCTYPE_FDOA	= 0x40,
	EMSLOCTYPE_406_GEO	= 0x80,
	EMSLOCTYPE_TDOA	= 0x100,
	EMSLOCTYPE_BASETYPE_MASK	= 0x1ff,
	EMSLOCTYPE_UNCONFIRMED	= 0x200,
	EMSLOCTYPE_DETECT_ONLY	= 0x400,
	EMSLOCTYPE_REAL_BASE_MASK	= 0x7ff,
	EMSLOCTYPE_A_SIDE	= 0,
	EMSLOCTYPE_B_SIDE	= 0x800,
	EMSLOCTYPE_TEST	= 0x1000,
	EMSLOCTYPE_ENCODED	= 0x2000,
	EMSLOCTYPE_ENCODED_ENCRYPTED	= 0x4000,
	EMSLOCTYPE_ABGEN	= 0x8000,
	EMSLOCTYPE_406_FDOA	= ( EMSLOCTYPE_406 | EMSLOCTYPE_FDOA ) ,
	EMSLOCTYPE_406_FDOA_DETECT	= ( EMSLOCTYPE_406_FDOA | EMSLOCTYPE_DETECT_ONLY ) ,
	EMSLOCTYPE_406_TDOA	= ( EMSLOCTYPE_406 | EMSLOCTYPE_TDOA ) ,
	EMSLOCTYPE_406_FDOA_TDOA	= ( EMSLOCTYPE_406_TDOA | EMSLOCTYPE_406_FDOA ) ,
	EMSLOCTYPE_CBC_DETECT	= 0x410,
	EMSLOCTYPE_406_DETECT	= 0x420,
	EMSLOCTYPE_CBC_B	= 0x810,
	EMSLOCTYPE_406_B	= 0x820,
	EMSLOCTYPE_CBC_121	= ( EMSLOCTYPE_CBC + 1 ) ,
	EMSLOCTYPE_CBC_243	= ( EMSLOCTYPE_CBC + 2 ) ,
	EMSLOCTYPE_CBC_121_243	= ( EMSLOCTYPE_CBC + 3 ) ,
	EMSLOCTYPE_CBC_406	= ( EMSLOCTYPE_CBC + 4 ) ,
	EMSLOCTYPE_406_SARP	= ( EMSLOCTYPE_406 + 1 ) ,
	EMSLOCTYPE_406_SARR	= ( EMSLOCTYPE_406 + 2 ) ,
	EMSLOCTYPE_406_SARP_SARR	= ( EMSLOCTYPE_406 + 3 ) ,
	EMSLOCTYPE_406_FDOA_SARP	= ( EMSLOCTYPE_406_FDOA | EMSLOCTYPE_406_SARP ) ,
	EMSLOCTYPE_406_FDOA_SARR	= ( EMSLOCTYPE_406_FDOA | EMSLOCTYPE_406_SARR ) ,
	EMSLOCTYPE_406_FDOA_SARP_SARR	= ( EMSLOCTYPE_406_FDOA | EMSLOCTYPE_406_SARP_SARR ) ,
	EMSLOCTYPE_CBC_121_B	= ( EMSLOCTYPE_CBC_B + 1 ) ,
	EMSLOCTYPE_CBC_243_B	= ( EMSLOCTYPE_CBC_B + 2 ) ,
	EMSLOCTYPE_CBC_121_243_B	= ( EMSLOCTYPE_CBC_B + 3 ) ,
	EMSLOCTYPE_CBC_406_B	= ( EMSLOCTYPE_CBC_B + 4 ) ,
	EMSLOCTYPE_406_SARP_B	= ( EMSLOCTYPE_406_B + 1 ) ,
	EMSLOCTYPE_406_SARR_B	= ( EMSLOCTYPE_406_B + 2 ) ,
	EMSLOCTYPE_406_SARP_SARR_B	= ( EMSLOCTYPE_406_B + 3 ) ,
	EMSLOCTYPE_CBC_121_DETECT	= ( EMSLOCTYPE_CBC_DETECT + 1 ) ,
	EMSLOCTYPE_CBC_243_DETECT	= ( EMSLOCTYPE_CBC_DETECT + 2 ) ,
	EMSLOCTYPE_CBC_121_243_DETECT	= ( EMSLOCTYPE_CBC_DETECT + 3 ) ,
	EMSLOCTYPE_CBC_406_DETECT	= ( EMSLOCTYPE_CBC_DETECT + 4 ) ,
	EMSLOCTYPE_406_SARP_DETECT	= ( EMSLOCTYPE_406_DETECT + 1 ) ,
	EMSLOCTYPE_406_SARR_DETECT	= ( EMSLOCTYPE_406_DETECT + 2 ) ,
	EMSLOCTYPE_406_SARP_SARR_DETECT	= ( EMSLOCTYPE_406_DETECT + 3 ) ,
	EMSLOCTYPE_406_FDOA_SARP_B	= ( EMSLOCTYPE_406_FDOA_SARP | EMSLOCTYPE_B_SIDE ) ,
	EMSLOCTYPE_406_FDOA_SARR_B	= ( EMSLOCTYPE_406_FDOA_SARR | EMSLOCTYPE_B_SIDE ) ,
	EMSLOCTYPE_406_FDOA_SARP_SARR_B	= ( EMSLOCTYPE_406_FDOA_SARP_SARR | EMSLOCTYPE_B_SIDE ) ,
	EMSLOCTYPE_406_FDOA_SARP_DETECT	= ( EMSLOCTYPE_406_FDOA_SARP | EMSLOCTYPE_DETECT_ONLY ) ,
	EMSLOCTYPE_406_FDOA_SARR_DETECT	= ( EMSLOCTYPE_406_FDOA_SARR | EMSLOCTYPE_DETECT_ONLY ) ,
	EMSLOCTYPE_406_FDOA_SARP_SARR_DETECT	= ( EMSLOCTYPE_406_FDOA_SARP_SARR | EMSLOCTYPE_DETECT_ONLY ) ,
	EMSLOCTYPE_GEO_SARR	= ( EMSLOCTYPE_406_GEO + EMSLOCTYPE_406_SARR_DETECT ) ,
	EMSLOCTYPE_GEO_SARR_UNCONFIRMED	= ( EMSLOCTYPE_GEO_SARR + EMSLOCTYPE_UNCONFIRMED ) 
    } 	EMSLOCATETYPE;

typedef struct _tagEMSWLSLOCATE
    {
    EMSLOCATION location;
    double dFrequency;
    float fFreqDrift;
    WORD wNumMsgs;
    WORD wNumMsgsUsed;
    WORD wNumBurstsUsed;
    WORD wNumIterations;
    float fRadiusErrEllipse;
    float fFreqBiasError;
    float fMajorError;
    float fMinorError;
    float fHeading;
    float fRMS;
    float fTrend;
    float fCoVarianceMatrix[ 10 ];
    } 	EMSWLSLOCATE;

typedef struct _tagEMSWLSLOCATE *LPEMSWLSLOCATE;

typedef struct _tagEMSCBCLOCATE
    {
    float fSweep;
    float fSweepError;
    WORD wSidebands;
    } 	EMSCBCLOCATE;

typedef struct _tagEMSCBCLOCATE *LPEMSCBCLOCATE;

typedef struct _tagEMS406LOCATE
    {
    BYTE cBeaconMsg[ 18 ];
    WORD wBitErrorFrameSync;
    WORD wBitErrorField1;
    WORD wBitErrorField2;
    } 	EMS406LOCATE;

typedef struct _tagEMS406LOCATE *LPEMS406LOCATE;

typedef struct _tagEMSLOCATE
    {
    EMSTIME time;
    ULONG ulLutID;
    WORD wType;
    BYTE cSatIDs[ 16 ];
    BYTE cLutIDs[ 16 ];
    ULONG ulSatPassID;
    INT64 i64BeaconID;
    EMSWLSLOCATE wlsSolution;
    EMSTIME timeTCA;
    float fCrossTrackAngle;
    WORD wWindowFactor;
    float fConfidence;
    float fProbability;
    float fPower;
    EMSTIME timeFirstData;
    EMSTIME timeLastData;
    union 
        {
        EMSCBCLOCATE recCBC;
        EMS406LOCATE rec406;
        } 	info;
    } 	EMSLOCATE;

typedef struct _tagEMSLOCATE *LPEMSLOCATE;


#pragma pack()


extern RPC_IF_HANDLE IEMSLOCATEdata_v0_0_c_ifspec;
extern RPC_IF_HANDLE IEMSLOCATEdata_v0_0_s_ifspec;
#endif /* __IEMSLOCATEdata_INTERFACE_DEFINED__ */

/* interface __MIDL_itf_locate_0000_0001 */
/* [local] */ 

#endif //INC_LOCATE


extern RPC_IF_HANDLE __MIDL_itf_locate_0000_0001_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_locate_0000_0001_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


