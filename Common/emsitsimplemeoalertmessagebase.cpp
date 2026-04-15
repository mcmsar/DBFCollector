/*********************************************************************
* Copyright (c) 2011 by EMS Technologies, Inc.,
* All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
#pragma warning(disable:4786)

#include "emsitsimplemeoalertmessagebase.h"
#include "sitfield.h"
#include "CBcnMsgDecodeBase.h"

CEMSSitSimpleMEOAlertMessageBase::CEMSSitSimpleMEOAlertMessageBase() : m_ulLutID(0)
{
}


CEMSSitSimpleMEOAlertMessageBase::CEMSSitSimpleMEOAlertMessageBase( const CEMSSitSimpleMEOAlertMessageBase& x ) :
															m_ulLutID( x.m_ulLutID ),
															m_lstBurstData(x.m_lstBurstData)
{
}

CEMSSitSimpleMEOAlertMessageBase::~CEMSSitSimpleMEOAlertMessageBase()
{
}

void 
CEMSSitSimpleMEOAlertMessageBase::Reset( )
{
	CEMSSitMessageBase::Reset();


	m_ulLutID = 0;
	m_lstBurstData.Clear();
}

EMS_RESULT
CEMSSitSimpleMEOAlertMessageBase::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];
		memset( szBuffer, 0, sizeof(szBuffer) );
		
		// There is only ever one alert per message.  So, hardcoded-here
		_sntprintf( szBuffer, sizeof(szBuffer) - 1, TEXT("/%03d/%04d/%02d"), 
									GetSitNumber(), GetSitDestination(), 1 );

		hr = WriteLine( lpStream, szBuffer );
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT 
CEMSSitSimpleMEOAlertMessageBase::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;

	CEMSBurstData* pBurstData = NULL;

	try
	{

		if ( lpStream )
		{
			// Solution Header (single instance)		
				// Burst Data Line (repeated for each burst)
					// Link Data Lines (repeated for each measurement)
					// Solution Data Line

			ULONG ulBursts = m_lstBurstData.Count();

			
			TCHAR szBuffer[512];
			memset( szBuffer, 0, sizeof(szBuffer) );

			CEMSSitMsgField msgField;

			hr = _GenerateSolutionHeaderLine( lpStream );

			if( EMS_OK == hr )
			{

				m_lstBurstData.MoveFirst();

				ULONG ulMaxBursts = GetMaxBursts();
				for( ULONG i = 0; (i < ulBursts) && (i < ulMaxBursts ); i++ )
				{
					// Burst Data Line
					// MFA01/MFA02

					pBurstData = m_lstBurstData.GetNext();

					CEMSObjectList<EMSCALIB406DATAEXT> lstPairs = pBurstData->GetBurstMeasurements();
					ULONG ulPairs = lstPairs.Count();

					_stprintf( szBuffer, TEXT("/%s/%02d"), msgField.TextMFA01( pBurstData->GetTxTime() ),
															 min(ulPairs,ulMaxBursts) );
															

					hr = WriteLine( lpStream, szBuffer );
					
					if( EMS_OK == hr )
					{
						lstPairs.MoveFirst();

						for( long j = 0; (j < ulPairs) && (j < ulMaxBursts ) && SUCCEEDED(hr); j++ )
						{
							EMSCALIB406DATAEXT linkPair = lstPairs.GetNext();

							// Link Data line.
							// /MF06/MF67/MF68/MF72

							_stprintf( szBuffer, 
								TEXT("/%03d/%s/%013.3f/%04.1f"), 
										linkPair.calib406.hdr.id.ulSatID,
										msgField.TextMF67( linkPair.calib406.timeMsg ),
										linkPair.calib406.dFrequency,
										linkPair.calib406.dCarrierPower );

							hr = WriteLine( lpStream, szBuffer );
						}
					}


					pBurstData->Release();
					pBurstData = NULL;
				}
			}

			// Final Solution.  If there is one.
			if( EMS_OK == hr )
			{
				hr = _WriteFinalSolution( lpStream );
			}
							
		}
		else
			hr = EMS_INVALID_STREAM;
	}
	catch( ... )
	{
		if( pBurstData )
		{
			pBurstData->Release();
			pBurstData = NULL;
		}

		throw;
	}

	return hr;
}

void
CEMSSitSimpleMEOAlertMessageBase::_GetSolutionLine( const EMSLOCATE& crLocate, TCHAR* szLine, const int ciMaxBuffer )
{

	CEMSSitMsgField msgField;

	// /MF25/MF26/MF77/MFA03/MF78
	//	Note MF78 content not defined in spec, using confidence factor for now.
	_sntprintf( szLine, ciMaxBuffer, TEXT("/%s/%s/%s/%05.2f/%03d"), 
				msgField.TextMF25( crLocate.wlsSolution.location.degLatitude ),
				msgField.TextMF26( crLocate.wlsSolution.location.degLongitude),
				msgField.TextMF77( double(crLocate.wlsSolution.location.fAltitude) ),
				(crLocate.wlsSolution.fRadiusErrEllipse > 99.99) ? 99.99 : crLocate.wlsSolution.fRadiusErrEllipse,
				min( 0, 999 )
				);
}

EMS_RESULT 
CEMSSitSimpleMEOAlertMessageBase::_GenerateSolutionHeaderLine( IEMSSeqStream* lpStream )
{
	EMS_RESULT hr = EMS_OK;

	if( !lpStream ) 
	{
		hr = EMS_INVALID_PTR;
	}

	if( EMS_OK == hr )
	{
		// Solution Header Line
		// MF11/MF23/MF21
		CEMSSitMsgField msgField;
		TCHAR szBuffer[128];

		// We need the 406 Msg.  Get it from one of the burst data measurements, arbitrarily
		// choose the first one.
		CEMSBurstData* pBurst = NULL;

		try
		{
			m_lstBurstData.MoveFirst();
			pBurst = m_lstBurstData.GetNext();

			if( !pBurst )
			{
				hr = EMS_INVALID_PTR;
			}

			if( EMS_OK == hr )
			{
				CEMSObjectList<EMSCALIB406DATAEXT> lstMeas = pBurst->GetBurstMeasurements();

				if( lstMeas.Count() > 0 )
				{

					lstMeas.MoveFirst();
					EMSCALIB406DATAEXT measurement = lstMeas.GetNext();

					_stprintf( szBuffer, TEXT("/%04d/%s/%02d"), GetLutID(),
																msgField.TextMF23( measurement.calib406.cBeaconMsg ),
																min(GetBurstCount(),GetMaxBursts()) );
					hr = WriteLine( lpStream, szBuffer );
				}
				else
					hr = EMS_EMPTY;
			}

			if( pBurst )
			{
				pBurst->Release();
				pBurst = NULL;
			}
		}
		catch( ... )
		{
			if( pBurst )
			{
				pBurst->Release();
				pBurst = NULL;
			}

			throw;
		}
	}

	return hr;
}