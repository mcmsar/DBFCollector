/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Mar 13 23:07:28 2007
 */
/* Compiler settings for ..\Common\Include\CALIB406EXT.IDL:
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

#ifndef __CALIB406EXT_h__
#define __CALIB406EXT_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "sigdata.h"
#include "calib406.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_CALIB406EXT_0000 */
/* [local] */ 

/********************************************************************
*	Module:			calib406ext.h
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

********************************************************************/

#ifndef INC_CALIB406EXT
#define INC_CALIB406EXT

#define	EMSCALIB406EXTVERSION	( 1 )



extern RPC_IF_HANDLE __MIDL_itf_CALIB406EXT_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_CALIB406EXT_0000_v0_0_s_ifspec;

#ifndef __IEMSCALIB406dataEXT_INTERFACE_DEFINED__
#define __IEMSCALIB406dataEXT_INTERFACE_DEFINED__

/* interface IEMSCALIB406dataEXT */
/* [auto_handle][unique][helpstring][uuid] */ 


#pragma pack(1)
typedef 
enum _tagEMSCALIB406EXTPROCESSFLAGS
    {	EMS_C406PF_REF_BEACON_MASK	= 0xf,
	EMS_C406PF_REF_BEACON_FLAG	= 0x1,
	EMS_C406PF_REF_TIME_FLAG	= 0x2,
	EMS_C406PF_REF_FREQ_FLAG	= 0x4,
	EMS_C406PF_PROCESS_MASK	= 0xf0,
	EMS_C406PF_PROCESS_TIME_FLAG	= 0x10,
	EMS_C406PF_PROCESS_FREQ_FLAG	= 0x20,
	EMS_C406PF_PROCESS_FDOA_FLAG	= 0x40,
	EMS_C406PF_PROCESS_TDOA_FLAG	= 0x80,
	EMS_C406PF_ACCEPT_MASK	= 0xf00,
	EMS_C406PF_ACCEPT_TIME_FLAG	= 0x100,
	EMS_C406PF_ACCEPT_FREQ_FLAG	= 0x200,
	EMS_C406PF_SAT_MASK	= 0xf000,
	EMS_C406PF_SAT_REMOVE_DLINKFREQ_FLAG	= 0x1000,
	EMS_C406PF_SAT_REMOVE_DLINKTIME_FLAG	= 0x2000,
	EMS_C406PF_SAT_INVERTED_SPECTRUM_FLAG	= 0x4000,
	EMS_C406PF_LUT_MASK	= 0xf0000,
	EMS_C406PF_LUT_INVERTED_SPECTRUM_FLAG	= 0x10000,
	EMS_C406PF_RESET_FLAGS	= 0,
	EMS_C406PF_None	= 0
    }	EMSCALIB406EXTPROCESSFLAGS;

typedef struct  _tagEMSCALIB406EXTRAS
    {
    DWORD dwProcessFlags;
    EMSTIMECOORDD SatTPVC;
    EMSVECTORD BeaconVector;
    EMSTIME timeTransmit;
    double dTxFrequency;
    double dTimeResidual;
    double dFreqResidual;
    WORD wBurstNumber;
    }	EMSCALIB406EXTRAS;

typedef struct  _tagEMSCALIB406DATAEXT
    {
    EMSCALIB406DATA2 calib406;
    EMSCALIB406EXTRAS extras;
    }	EMSCALIB406DATAEXT;

typedef struct _tagEMSCALIB406DATAEXT __RPC_FAR *LPEMSCALIB406DATAEXT;


#pragma pack()


extern RPC_IF_HANDLE IEMSCALIB406dataEXT_v0_0_c_ifspec;
extern RPC_IF_HANDLE IEMSCALIB406dataEXT_v0_0_s_ifspec;
#endif /* __IEMSCALIB406dataEXT_INTERFACE_DEFINED__ */

/* interface __MIDL_itf_CALIB406EXT_0020 */
/* [local] */ 

#endif //INC_CALIB406EXT


extern RPC_IF_HANDLE __MIDL_itf_CALIB406EXT_0020_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_CALIB406EXT_0020_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
