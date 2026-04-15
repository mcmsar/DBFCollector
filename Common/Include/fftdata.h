/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Mar 07 10:43:55 2005
 */
/* Compiler settings for fftdata.idl:
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

#ifndef __fftdata_h__
#define __fftdata_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

/* header files for imported files */
#include "unknwn.h"
#include "emstypex.h"
#include "sigdata.h"
#include "filesign.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_fftdata_0000 */
/* [local] */ 

/********************************************************************
*	Module:			fftdata.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Data structures used to define FFT file data format
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2002 by EMS Technologies, Inc.,
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

	0.0	02/11/2		rvw	start

********************************************************************/
#ifndef INC_FFTDATA
#define INC_FFTDATA

#define EMS_MAX_FFT_FREQ_BANDS ( 5 )



extern RPC_IF_HANDLE __MIDL_itf_fftdata_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_fftdata_0000_v0_0_s_ifspec;

#ifndef __IEMSFFTdata_INTERFACE_DEFINED__
#define __IEMSFFTdata_INTERFACE_DEFINED__

/* interface IEMSFFTdata */
/* [auto_handle][unique][helpstring][uuid] */ 


#pragma pack(1)
typedef struct  _tagEMSFFTHEADER
    {
    EMSFILESIGNATURE sig;
    EMSSIGDATAID id;
    ULONG ulPassNumber;
    ULONG ulDataRecordSize;
    INT64 i64DurationFFT;
    float fFreqBinSize;
    WORD wNumFFTs;
    WORD wNumBands;
    struct  
        {
        WORD wStartFreqBin;
        WORD wStopFreqBin;
        }	band[ 5 ];
    }	EMSFFTHEADER;

typedef struct _tagEMSFFTHEADER __RPC_FAR *LPEMSFFTHEADER;

typedef struct  _tagEMSFFTHEADER2
    {
    EMSFILESIGNATURE sig;
    EMSSIGDATAID id;
    ULONG ulPassNumber;
    ULONG ulDataRecordSize;
    INT64 i64DurationFFT;
    float fFFTOverlapFactor;
    float fFreqBinSize;
    WORD wNumFFTBins;
    WORD wNumFFTs;
    WORD wNumBands;
    struct  
        {
        WORD wStartFreqBin;
        WORD wStopFreqBin;
        }	band[ 5 ];
    }	EMSFFTHEADER2;

typedef struct _tagEMSFFTHEADER2 __RPC_FAR *LPEMSFFTHEADER2;

typedef struct  _tagEMSFFTDATA
    {
    EMSTIME timeStamp;
    float fCarrierFrequency;
    float fCarrierModIndexMax;
    float fCarrierModIndexMean;
    float fCarrierModIndexRMS;
    float fADCMean;
    float fADCRMS;
    ULONG ulMarkerBitRate;
    }	EMSFFTDATA;

typedef struct _tagEMSFFTDATA __RPC_FAR *LPEMSFFTDATA;


#pragma pack()


extern RPC_IF_HANDLE IEMSFFTdata_v0_0_c_ifspec;
extern RPC_IF_HANDLE IEMSFFTdata_v0_0_s_ifspec;
#endif /* __IEMSFFTdata_INTERFACE_DEFINED__ */

/* interface __MIDL_itf_fftdata_0016 */
/* [local] */ 

#endif // INC_FFTDATA


extern RPC_IF_HANDLE __MIDL_itf_fftdata_0016_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_fftdata_0016_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
