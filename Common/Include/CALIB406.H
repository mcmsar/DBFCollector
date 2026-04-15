/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Mar 06 11:57:38 2007
 */
/* Compiler settings for calib406.idl:
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

#ifndef __calib406_h__
#define __calib406_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "sigdata.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_calib406_0000 */
/* [local] */ 

/********************************************************************
*	Module:			calib406.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Data structure for Calibrated 406 Data 
*						( i.e. SARP and SARR records Post Calibration )
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
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

	0.0	01/04/05	rvw		start
	0.0	02/10/05	rcr		additional data types
	0.0	03/11/05	ch		added version number
	0.0	16/10/06	rcr		additional fields and new version

********************************************************************/

#ifndef INC_CALIB406
#define INC_CALIB406

#include "sarpdata.h"			// for definitions of status flags
#define	EMSCALIB406VERSION	( 1 )



extern RPC_IF_HANDLE __MIDL_itf_calib406_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_calib406_0000_v0_0_s_ifspec;

#ifndef __IEMSCALIB406data_INTERFACE_DEFINED__
#define __IEMSCALIB406data_INTERFACE_DEFINED__

/* interface IEMSCALIB406data */
/* [auto_handle][unique][helpstring][uuid] */ 


#pragma pack(1)
typedef 
enum _tagEMSCALIB406TYPE
    {	EMSCALIBTYPE_406_SARP	= 0x21,
	EMSCALIBTYPE_406_SARR	= 0x22,
	EMSCALIBTYPE_406_SARP_SARR	= 0x23
    }	EMSCALIB406TYPE;

typedef struct  _tagEMSCALIB406DATA
    {
    EMSSIGDATAIDTYPE hdr;
    ULONG ulPassID;
    INT64 i64BeaconID;
    EMSTIME timeMsg;
    INT64 i64TimeOffset;
    WORD wStatus;
    WORD wDuplicateMsgCount;
    double dFrequency;
    float fFreqOffset;
    float fCarrierPower;
    WORD wBitErrorField1;
    WORD wBitErrorField2;
    WORD wBitErrorFrameSynch;
    BYTE cBeaconMsg[ 18 ];
    }	EMSCALIB406DATA;

typedef struct _tagEMSCALIB406DATA __RPC_FAR *LPEMSCALIB406DATA;

typedef 
enum _tagEMSCALIB406DATAFLAGS
    {	EMS_C406DF_FLAG_01	= 0x1,
	EMS_C406DF_FLAG_02	= 0x2,
	EMS_C406DF_FLAG_03	= 0x4,
	EMS_C406DF_FLAG_04	= 0x8,
	EMS_C406DF_FLAG_05	= 0x10,
	EMS_C406DF_FLAG_06	= 0x20,
	EMS_C406DF_FLAG_07	= 0x40,
	EMS_C406DF_FLAG_08	= 0x80,
	EMS_C406DF_FLAG_09	= 0x100,
	EMS_C406DF_FLAG_10	= 0x200,
	EMS_C406DF_FLAG_11	= 0x400,
	EMS_C406DF_FLAG_12	= 0x800,
	EMS_C406DF_FLAG_13	= 0x1000,
	EMS_C406DF_FLAG_14	= 0x2000,
	EMS_C406DF_FLAG_15	= 0x4000,
	EMS_C406DF_FLAG_16	= 0x8000,
	EMS_C406DF_None	= 0
    }	EMSCALIB406DATAFLAGS;

typedef 
enum _tagEMSCALIB406RESOLUTIONFLAGS
    {	EMS_C406RF_TIMERES_UKN	= 0,
	EMS_C406RF_TIMERES_LOW	= 0x1,
	EMS_C406RF_TIMERES_MID	= 0x2,
	EMS_C406RF_TIMERES_HIGH	= 0x4,
	EMS_C406RF_TIMERES_MASK	= 0xf,
	EMS_C406RF_FREQRES_UKN	= 0,
	EMS_C406RF_FREQRES_LOW	= 0x100,
	EMS_C406RF_FREQRES_MID	= 0x200,
	EMS_C406RF_FREQRES_HIGH	= 0x400,
	EMS_C406RF_FREQRES_MASK	= 0xf00,
	EMS_C406RF_POWERRES_UKN	= 0,
	EMS_C406RF_POWERRES_LOW	= 0x10000,
	EMS_C406RF_POWERRES_MID	= 0x20000,
	EMS_C406RF_POWERRES_HIGH	= 0x40000,
	EMS_C406RF_POWERRES_MASK	= 0xf0000,
	EMS_C406RF_BPSRES_UKN	= 0,
	EMS_C406RF_BPSRES_LOW	= 0x1000000,
	EMS_C406RF_BPSRES_MID	= 0x2000000,
	EMS_C406RF_BPSRES_HIGH	= 0x4000000,
	EMS_C406RF_BPSRES_MASK	= 0xf000000,
	EMS_C406RF_None	= 0
    }	EMSCALIB406RESOLUTIONFLAGS;

typedef struct  _tagEMSCALIB406DATA2
    {
    EMSSIGDATAIDTYPE hdr;
    WORD wAntennaID;
    ULONG ulPassID;
    INT64 i64BeaconID;
    EMSTIME timeMsg;
    INT64 i64TimeOffset;
    WORD wStatus;
    WORD wDuplicateMsgCount;
    double dFrequency;
    double dFreqOffset;
    double dCarrierPower;
    WORD wBitErrorField1;
    WORD wBitErrorField2;
    WORD wBitErrorFrameSynch;
    BYTE cBeaconMsg[ 18 ];
    double dBitRate;
    DWORD dwDataFlags;
    DWORD dwResolutionFlags;
    DWORD dwReserve0;
    double dReserve1;
    double dReserve2;
    double dReserve3;
    }	EMSCALIB406DATA2;

typedef struct _tagEMSCALIB406DATA2 __RPC_FAR *LPEMSCALIB406DATA2;


#pragma pack()


extern RPC_IF_HANDLE IEMSCALIB406data_v0_0_c_ifspec;
extern RPC_IF_HANDLE IEMSCALIB406data_v0_0_s_ifspec;
#endif /* __IEMSCALIB406data_INTERFACE_DEFINED__ */

/* interface __MIDL_itf_calib406_0012 */
/* [local] */ 

#endif //INC_CALIB406


extern RPC_IF_HANDLE __MIDL_itf_calib406_0012_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_calib406_0012_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
