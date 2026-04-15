/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Jan 31 15:33:10 2003
 */
/* Compiler settings for sarpdata.idl:
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

#ifndef __sarpdata_h__
#define __sarpdata_h__

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

/* interface __MIDL_itf_sarpdata_0000 */
/* [local] */ 

/********************************************************************
*	Module:			sarpdata.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	data structure used to describe the output of the 
*						SARP ( SARP processor ) wideband process 
*						and is also used as the input to the SARP Calibration 
*						process. { Also known as PDS data }
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
#ifndef INC_SARPDATA
#define INC_SARPDATA
#define EMSSARPMSGLENGTH ( 24 )
#define EMSSARPBEACONMSGLENGTH ( 18 )

// definitions for ( wStatus )
#define EMSSARPFLAG_PSEUDOMSG	( 0x0001 )
#define EMSSARPFLAG_DRU0			( 0x0002 )
#define EMSSARPFLAG_DRU1			( 0x0004 )
#define EMSSARPFLAG_DRU2			( 0x0008 )
#define EMSSARPFLAG_DRU3			( 0x0010 )
#define EMSSARPFLAG_LONGMSG		( 0x0020 )	// set if long msg format
#define EMSSARPFLAG_ROLLOVER		( 0x0040 )
#define EMSSARPFLAG_REALDUMP		( 0x0080 )        // realtime data or dump data
#define EMSSARPFLAG_FREQPARITY	( 0x0100 )	// set if error
#define EMSSARPFLAG_TIMEPARITY	( 0x0200 )	// set if error
#define EMSSARPFLAG_NEWDAYSTART	( 0x0400 )	// start of a new day (cospas only) 
#define EMS_FLAG_INVERTED_FRAMESYNC	( 0x0800 )	// inverted framesync

#define EMS_FLAG_TIME_VALID		( 0x1000 ) 
#define EMS_FLAG_TEST_MSG		( 0x2000 )	
#define EMS_FLAG_HISTORICAL_MSG	( 0x4000 )	
#define EMS_FLAG_PROCESSED_MSG	( 0x8000 )	


extern RPC_IF_HANDLE __MIDL_itf_sarpdata_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_sarpdata_0000_v0_0_s_ifspec;

#ifndef __IEMSSARPdata_INTERFACE_DEFINED__
#define __IEMSSARPdata_INTERFACE_DEFINED__

/* interface IEMSSARPdata */
/* [auto_handle][unique][helpstring][uuid] */ 


#pragma pack(1)
typedef 
enum _tagEMSSARPDATATYPE
    {	EMSSARPTYPE_COSPAS	= 0x8000,
	EMSSARPTYPE_SARSAT	= 0x4000,
	EMSSARPTYPE_HOUSEKEEPING	= 0x2000,
	EMSSARPTYPE_SARP0	= 0,
	EMSSARPTYPE_SARP1	= 0x1,
	EMSSARPTYPE_SARP2	= 0x2,
	EMSSARPTYPE_SARP3	= 0x3,
	EMSSARPTYPE_SARSATSARP0	= EMSSARPTYPE_SARSAT + EMSSARPTYPE_SARP0,
	EMSSARPTYPE_SARSATSARP1	= EMSSARPTYPE_SARSAT + EMSSARPTYPE_SARP1,
	EMSSARPTYPE_SARSATSARP2	= EMSSARPTYPE_SARSAT + EMSSARPTYPE_SARP2,
	EMSSARPTYPE_SARSATSARP3	= EMSSARPTYPE_SARSAT + EMSSARPTYPE_SARP3,
	EMSSARPTYPE_SARSATSARP3HK	= EMSSARPTYPE_SARSAT + EMSSARPTYPE_SARP3 + EMSSARPTYPE_HOUSEKEEPING,
	EMSSARPTYPE_COSPASSARP0	= EMSSARPTYPE_COSPAS + EMSSARPTYPE_SARP0,
	EMSSARPTYPE_COSPASSARP1	= EMSSARPTYPE_COSPAS + EMSSARPTYPE_SARP1,
	EMSSARPTYPE_COSPASSARP2	= EMSSARPTYPE_COSPAS + EMSSARPTYPE_SARP2
    }	EMSSARPDATATYPE;

#define EMSSARPTYPE_SARPNUMBERMASK    0x000F  // reserve 4 LSBs for sarp type (ie. sarp-0, sarp-1, etc...)
#define SARPTYPE( val )        ( val & EMSSARPTYPE_SARPNUMBERMASK )
#define ISHKSARPMSG( val )     ((val & EMSSARPTYPE_HOUSEKEEPING) != 0 )
#define ISCOSPASSARPMSG( val ) ((val & EMSSARPTYPE_COSPAS) != 0 )
#define ISSARSATSARPMSG( val ) ((val & EMSSARPTYPE_SARSAT) != 0 )
typedef struct  _tagEMSSARPDATA
    {
    EMSSIGDATAIDTYPE hdr;
    ULONG ulPassID;
    INT64 i64BeaconID;
    EMSTIME timeMsg;
    INT64 i64TimeOffset;
    WORD wStatus;
    double dFrequency;
    float fFreqOffset;
    float fAvgPower;
    float fCarrierPower;
    WORD wBitErrorFrameSync;
    WORD wBitErrorField1;
    WORD wBitErrorField2;
    float fBitRate;
    BYTE cMsg[ 24 ];
    BYTE cBeaconMsg[ 18 ];
    }	EMSSARPDATA;

typedef struct _tagEMSSARPDATA __RPC_FAR *LPEMSSARPDATA;


#pragma pack()


extern RPC_IF_HANDLE IEMSSARPdata_v0_0_c_ifspec;
extern RPC_IF_HANDLE IEMSSARPdata_v0_0_s_ifspec;
#endif /* __IEMSSARPdata_INTERFACE_DEFINED__ */

/* interface __MIDL_itf_sarpdata_0012 */
/* [local] */ 

#endif // INC_SARPDATA


extern RPC_IF_HANDLE __MIDL_itf_sarpdata_0012_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_sarpdata_0012_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
