/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Thu Jan 15 14:40:46 2009
 */
/* Compiler settings for ..\common\include\LEOSTATS.IDL:
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

#ifndef __LEOSTATS_h__
#define __LEOSTATS_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "statant.h"
#include "statenv.h"
#include "statcoll.h"
#include "statwide.h"
#include "statcomm.h"
#include "statpass.h"
#include "statccbc.h"
#include "statc406.h"
#include "statodet.h"
#include "stattcal.h"
#include "statlocn.h"
#include "statsens.h"
#include "statcomb.h"
#include "statsarr.h"
#include "statgeo.h"
#include "statlut.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_LEOSTATS_0000 */
/* [local] */ 

/********************************************************************
*	Module:			leostats.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Data structures for LeoLut600 Status information
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
#ifndef INC_LEOSTATS
#define INC_LEOSTATS


extern RPC_IF_HANDLE __MIDL_itf_LEOSTATS_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_LEOSTATS_0000_v0_0_s_ifspec;

#ifndef __IEMSLEOSTATUSdata_INTERFACE_DEFINED__
#define __IEMSLEOSTATUSdata_INTERFACE_DEFINED__

/* interface IEMSLEOSTATUSdata */
/* [auto_handle][unique][helpstring][uuid] */ 

typedef 
enum _tagEMSLEOSTATUSTYPE
    {	EMSAntennaStatus	= 1,
	EMSCollectorStatus	= 2,
	EMSWidebandStatus	= 3,
	EMSEnvironStatus	= 4,
	EMSCommsStatus	= 5,
	EMSPassSummaryStatus	= 6,
	EMSCalibrate406Status	= 7,
	EMSCalibrateCBCStatus	= 8,
	EMSOrbitDetermineStatus	= 9,
	EMSLocationStatus	= 10,
	EMSSensorStatus	= 11,
	EMSTCalStatus	= 12,
	EMSCombine406Status	= 13,
	EMSCalibrateSarrStatus	= 14,
	EMSSensorStatusEx	= 15,
	EMSGeoSummary	= 16,
	EMSGeoCalib406Status	= 17,
	EMSLutStatus	= 18
    }	EMSLEOSTATUSTYPE;


#pragma pack(1)
typedef struct  _tagEMSLEOSTATUSUPDATE
    {
    EMSTIME timeTag;
    ULONG ulLutID;
    ULONG ulSatID;
    ULONG ulPassID;
    EMSLEOSTATUSTYPE type;
    /* [switch_is][switch_type] */ union 
        {
        /* [case()] */ EMSANTENNAINFO antenna;
        /* [case()] */ EMSCOLLECTORINFO collector;
        /* [case()] */ EMSWIDEBANDINFO wideband;
        /* [case()] */ EMSENVIRONINFO environ;
        /* [case()] */ EMSCOMMSINFO comms;
        /* [case()] */ EMSPASSSUMMARYINFO3 pass;
        /* [case()] */ EMSCALIBRATE406INFOEX calib406;
        /* [case()] */ EMSCALIBRATECBCINFO calibCBC;
        /* [case()] */ EMSORBITDETERMINEINFOEX orbitDet;
        /* [case()] */ EMSLOCATIONINFO location;
        /* [case()] */ EMSSENSORINFO sensor;
        /* [case()] */ EMSTCALINFO tcal;
        /* [case()] */ EMSCOMBINE406INFO combine406;
        /* [case()] */ EMSSARRCALIBINFO sarrCalib;
        /* [case()] */ EMSSENSORINFOEX sensorEx;
        /* [case()] */ EMSGEOSUMMARYINFO geoSummary;
        /* [case()] */ EMSGEOCALIB406INFO geoCalib406Info;
        /* [case()] */ EMSLUTSTATUSINFO lutStatusInfo;
        /* [default] */  /* Empty union arm */ 
        }	data;
    }	EMSLEOSTATUSUPDATE;

typedef struct _tagEMSLEOSTATUSUPDATE __RPC_FAR *LPEMSLEOSTATUSUPDATE;



extern RPC_IF_HANDLE IEMSLEOSTATUSdata_v0_0_c_ifspec;
extern RPC_IF_HANDLE IEMSLEOSTATUSdata_v0_0_s_ifspec;
#endif /* __IEMSLEOSTATUSdata_INTERFACE_DEFINED__ */

/* interface __MIDL_itf_LEOSTATS_0114 */
/* [local] */ 


#pragma pack()
#endif // INC_LEOSTATS


extern RPC_IF_HANDLE __MIDL_itf_LEOSTATS_0114_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_LEOSTATS_0114_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
