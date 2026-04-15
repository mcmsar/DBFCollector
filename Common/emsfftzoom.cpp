/********************************************************************
*	Module:			emsFFTZoom.cpp
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
#include "emsFFTZoom.h"

const float c_dRoomFact             = 1.25; // used to limit Max Data Value

CEMSFFTZoomBase::CEMSFFTZoomBase()
{
}

CEMSFFTZoomBase::~CEMSFFTZoomBase()
{
}


EMS_RESULT CEMSFFTZoomBase::SetFFTHeader( EMSFFTHEADER2 *lpHeader )
{
	if ( lpHeader )
		m_hdr = *lpHeader;

	return EMS_OK;
}

EMS_RESULT CEMSFFTZoomBase::Extract(  EMSTIME timeData, EMSCOMPLEX *lpBuffer, LONG lCount, 
		double dStartFreq, double dEndFreq )
{
	EMS_RESULT hr = EMS_OK;

	// make sure we have header

	if ( lpBuffer && lCount )
	{
		LONG lDataIndex = 0, lDataNumber = 0, lFFTOffset=0;

		hr = _CalcOffsets( dStartFreq, dEndFreq, &lDataIndex, &lDataNumber );

		if ( ( EMS_OK == hr ) && lCount )
		{
			INT nStartBin = (INT)( dStartFreq / m_hdr.fFreqBinSize );
			double dFreqBuffer = nStartBin * m_hdr.fFreqBinSize;
			INT64 i64FFTTimeInterval = (INT64)((double)m_hdr.i64DurationFFT * ( 1.0 - m_hdr.fFFTOverlapFactor )); 
			CEMSTime timeBuffer( timeData );
			bool bContinue;

			if ( ( lDataIndex+lDataNumber ) > lCount )
				lDataNumber = lCount - lDataIndex;

			for ( int i = 0; i < m_hdr.wNumFFTs; i++ )
			{
				bContinue = OnFFTDataBlock( timeBuffer, dFreqBuffer, 
						&lpBuffer[ lFFTOffset + lDataIndex ], lDataNumber );

				lFFTOffset += m_hdr.wNumFFTBins; 

				timeBuffer.AddNanoseconds( (LONG)i64FFTTimeInterval );
			}
		}
	}
	return hr;
}

EMS_RESULT CEMSFFTZoomBase::_CalcOffsets( double dStartFreq, double dEndFreq, LPLONG lplIndex, LPLONG lplCount )
{
	// validate the header for FreqBinSize == 0; and add exception handling

	EMS_RESULT hr = EMS_OK;
	INT nStartBin = (INT)( dStartFreq / m_hdr.fFreqBinSize );
	INT nStopBin = (INT)( dEndFreq / m_hdr.fFreqBinSize );
	INT nBand = _FindBand( nStartBin );
	LONG  lIndex = 0;

	if ( nBand >= 0 )
	{
		if ( nStopBin > m_hdr.band[ nBand ].wStopFreqBin )
			nStopBin = m_hdr.band[ nBand ].wStopFreqBin;

		for ( int i = 0; i < nBand; i++ )
		{
			lIndex += ( m_hdr.band[i].wStopFreqBin - 
									m_hdr.band[i].wStartFreqBin + 1 );
		}
		lIndex += ( nStartBin - m_hdr.band[ nBand ].wStartFreqBin );

		if ( lplIndex )
			*lplIndex = lIndex;

		if ( lplCount )
			*lplCount = nStopBin - nStartBin + 1;
	}
	else
		hr = EMS_UNKNOWN_ERROR;

	return hr;
}				

INT CEMSFFTZoomBase::_FindBand( INT nFreqBin )
{
	INT nIndex = -1;

	for ( int i = 0; ( -1 == nIndex ) && ( i < m_hdr.wNumBands ); i++ )
	{
		if ( ( nFreqBin >= m_hdr.band[i].wStartFreqBin ) && 
								( nFreqBin <= m_hdr.band[i].wStopFreqBin ) )
		{
			nIndex = i;
		}
	}
	return nIndex;
}

