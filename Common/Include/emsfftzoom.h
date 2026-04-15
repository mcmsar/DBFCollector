/********************************************************************
*	Module:			emsfftzoom.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	CEMSFFTZoomBase
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

	0.0	2005/3/5		rrr&rvw	start

********************************************************************/
#ifndef INC_EMSFFTZOOM
#define INC_EMSFFTZOOM

#define EMSERROR_NODEFINE_TYPES

#include "emstypes.h"
#include "emserror.h"
#include "fftdata.h"
#include "emstime.h"
#include "sigproc.h"
#include "emsaudio.h"
//#include "emsfftxfrm.h"			// CEMSFFTTransform

#define EMS_MAX_FFT_FREQ_COEFF ( 32 )

/*! \class CEMSFFTZoomBase
* \brief This class performs Zoom FFTs on FFT data used by Wideband Audio.
*
*/

class CEMSFFTZoomBase
{
public:
	CEMSFFTZoomBase( );
	virtual ~CEMSFFTZoomBase( );

/*! \fn EMS_RESULT CEMSFFTZoomBase::SetFFTHeader( EMSFFTHEADER2 *lpHeader );
* \brief This method sets the FFTHeader values
*
* \param lpHeader is a pointer to the EMSFFTHEADER2 structure containing the
*	desired values.
* \return EMS_OK if successful, or an error indicating why it failed
*/
	EMS_RESULT SetFFTHeader( EMSFFTHEADER2 *lpHeader );
	inline EMSFFTHEADER2 *GetFFTHeader( void ) { return &m_hdr; }

	EMS_RESULT Extract( EMSTIME timeData, EMSCOMPLEX *lpBuffer, LONG lCount, 
									double dStartFreq, double dEndFreq );

	virtual bool OnFFTDataBlock( EMSTIME timeData, double dFreq, EMSCOMPLEX *lpBuffer, LONG lCount ) = 0;

private: // methods
	INT _FindBand( INT nFreqBin );
	EMS_RESULT _CalcOffsets( double dStartFreq, double dEndFreq, LPLONG lplIndex, LPLONG lplCount );

private: // data
	EMSFFTHEADER2 m_hdr;
};


#endif // INC_EMSFFTZOOM
