/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri May 01 16:49:38 2009
 */
/* Compiler settings for ..\Common\Include\ABLData.idl:
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

#ifndef __ABLData_h__
#define __ABLData_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_ABLData_0000 */
/* [local] */ 

/********************************************************************
*	Module:			abldata.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Data structure for Active Beacon List Record 
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2009 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date		Auth	Changes
	===	====		====	=======


********************************************************************/
#ifndef INC_ABL_DATA
#define INC_ABL_DATA

typedef 
enum tagEMSWaveFormType
    {	WAVEFORM_NORMAL	= 0,
	WAVEFORM_TEST	= -1,
	WAVEFORM_RESERVED_MIN	= 1,
	WAVEFORM_RESERVED_MAX	= 30
    }	EMSWAVEFORMTYPE;

#define IS_RESERVED_WAVEFORM(e) (e>= WAVEFORM_RESERVED_MIN && e<=WAVEFORM_RESERVED_MAX)
#define IS_TEST_WAVEFORM(e) (WAVEFORM_TEST == e)
#define IS_NORMAL_WAVEFORM(e) (WAVEFORM_NORMAL == e)
#define	EMSABLDATAVERSION	( 1 )



extern RPC_IF_HANDLE __MIDL_itf_ABLData_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ABLData_0000_v0_0_s_ifspec;

#ifndef __IEMSABLData_INTERFACE_DEFINED__
#define __IEMSABLData_INTERFACE_DEFINED__

/* interface IEMSABLData */
/* [auto_handle][unique][helpstring][uuid] */ 


#pragma pack(1)
#define MAX_ABL_LUTS 16
#define MAX_ABL_SATS 16
typedef 
enum _tagEMSABLSTATUSFLAGS
    {	EMS_ABL_CHECK_BCN_MSG	= 0x1,
	EMS_ABL_REFERENCE_BCN	= 0x200,
	EMS_ABL_ENCODED_LOCN_BCN	= 0x10000
    }	EMSABLSTATUSFLAGS;

typedef enum _tagEMSABLSTATUSFLAGS __RPC_FAR *LPEMSABLSTATUSFLAGS;

typedef struct  _tagEMSMERGEID
    {
    EMSTIME timestamp;
    ULONG ulLUTID;
    INT64 i64BeaconID;
    BYTE acBeaconMsg[ 18 ];
    WORD wBitErrorFS;
    WORD wBitErrorField1;
    WORD wBitErrorField2;
    WORD wType;
    DWORD dwCSFlags;
    DWORD dwEMSFlags;
    WORD wCountryCode;
    WORD wProtocolFlag;
    WORD wProtocolCode;
    WORD wWaveFormID;
    BYTE acSatIDs[ 16 ];
    BYTE acLutIDs[ 16 ];
    }	EMSMERGEID;

typedef struct _tagEMSMERGEID __RPC_FAR *LPEMSMERGEID;

typedef struct  _tagEMSMERGELOCATEINFO
    {
    double dLatitude;
    double dLongitude;
    double dAltitude;
    double dProbability;
    double dMajorError;
    double dMinorError;
    double dHeading;
    double dRadiusErrEllipse;
    double dTOANoise;
    double dFOANoise;
    double dHDOP;
    double dLocationError;
    double dEncodedLat;
    double dEncodedLong;
    double dComputedQualityFactor;
    double dEncodedQualityFactor;
    }	EMSMERGELOCATEINFO;

typedef struct _tagEMSMERGELOCATEINFO __RPC_FAR *LPEMSMERGELOCATEINFO;

typedef struct  _tagEMSMERGEDETECTINFO
    {
    WORD wNumMsgs;
    WORD wNumFOAMsgsUsed;
    WORD wNumTOAMsgsUsed;
    WORD wNumBursts;
    EMSTIME timeDataStart;
    EMSTIME timeDataEnd;
    }	EMSMERGEDETECTINFO;

typedef struct _tagEMSMERGEDETECTINFO __RPC_FAR *LPEMSMERGEDETECTINFO;

typedef struct  _tagEMSMERGEBEACONINFO
    {
    double dCNR_Ave;
    double dCNR_Sigma;
    double dFrequency_Ave;
    double dFrequency_Sigma;
    double dBitRate_Ave;
    double dBitRate_Sigma;
    double dRepetitionRate_Ave;
    double dRepetitionRate_Sigma;
    }	EMSMERGEBEACONINFO;

typedef struct _tagEMSMERGEBEACONINFO __RPC_FAR *LPEMSMERGEBEACONINFO;

typedef struct  _tagEMSABLData
    {
    EMSMERGEID Id;
    EMSMERGELOCATEINFO Locate;
    EMSMERGEDETECTINFO Detect;
    EMSMERGEBEACONINFO Beacon;
    WORD wReserved;
    ULONG ulReserved1;
    ULONG ulReserved2;
    ULONG ulReserved3;
    ULONG ulReserved4;
    ULONG ulReserved5;
    ULONG ulReserved6;
    INT64 i64Reserved1;
    INT64 i64Reserved2;
    INT64 i64Reserved3;
    INT64 i64Reserved4;
    INT64 i64Reserved5;
    double dReserved1;
    double dReserved2;
    double dReserved3;
    double dReserved4;
    double dReserved5;
    }	EMSABLData;

typedef struct _tagEMSABLData __RPC_FAR *LPEMSABLData;


#pragma pack()


extern RPC_IF_HANDLE IEMSABLData_v0_0_c_ifspec;
extern RPC_IF_HANDLE IEMSABLData_v0_0_s_ifspec;
#endif /* __IEMSABLData_INTERFACE_DEFINED__ */

/* interface __MIDL_itf_ABLData_0011 */
/* [local] */ 

#endif //INC_ABL_DATA


extern RPC_IF_HANDLE __MIDL_itf_ABLData_0011_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_ABLData_0011_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
