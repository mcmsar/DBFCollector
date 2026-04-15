/********************************************************************
*	Module:			audiodat.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	data structure used to describe the output of the 
*						audio of the base band signal. 
*						Used only for display and measurement purposes.
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
#ifndef INC_AUDIODAT
#define INC_AUDIODAT

#include "emstypes.h"
#include "sigproc.h"
#include "sigdata.h"

#define EMSAUDIOFFTCOUNT ( 70 * 4097 ) 

//typedef struct _tagEMSCOMPLEX
//{
//	float 		fReal;
//	float			fImaginary;
//} EMSCOMPLEX, *LPEMSCOMPLEX;

typedef struct _tagEMSAUDIODATA
{
	EMSSIGDATAID id;							// time, ulSatID, ulLutID
	float			fMaxPower;					// Max power 
	float			fFreqOffset;       	   // Frequency offset in Hz
	float			fFreqQFactor;       	   // Frequency quantization factor (nominally 62 Hz)
	float       fAGCRMS;                  // RMS of A/D samples
	float       fAGCMean;                 // Mean value of A/D samples
	float       fCarrierFrequency;        // Carrier frequency (Hz)
	float       fModIndex;                // Maximum modulation index (radians)
	float       fModIndexMean;           // Mean value of modulation index (radians)
	float     	fModIndexRMS;            // RMS of modulation index (radians)
	ULONG			ulMarkerBitRate;          // Number of samples between marker bits
	WORD			wModIndexBlock;          // Block number with maximum mod index
	WORD			wFFTCount;
	WORD			wFFTSize;
	EMSCOMPLEX	fftData[ EMSAUDIOFFTCOUNT ];   // Raw fft buffer
} EMSAUDIODATA, *LPEMSAUDIODATA;

#endif // INC_AUDIODAT


