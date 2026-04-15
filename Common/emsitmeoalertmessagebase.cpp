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

#include "emsitmeoalertmessagebase.h"
#include "sitfield.h"
#include "CBcnMsgDecodeBase.h"

CEMSSitMEOAlertMessageBase::CEMSSitMEOAlertMessageBase() : m_i64BeaconID(0), m_ulLutID(0)
{
}


CEMSSitMEOAlertMessageBase::CEMSSitMEOAlertMessageBase( const CEMSSitMEOAlertMessageBase& x ) :
															m_i64BeaconID( x.m_i64BeaconID ),
															m_ulLutID( x.m_ulLutID ),
															m_lstBurstData(x.m_lstBurstData)
{
}

CEMSSitMEOAlertMessageBase::~CEMSSitMEOAlertMessageBase()
{
}

void 
CEMSSitMEOAlertMessageBase::Reset( )
{
	CEMSSitMessageBase::Reset();


	m_i64BeaconID = 0;
	m_ulLutID = 0;
	m_lstBurstData.Clear();
}

EMS_RESULT
CEMSSitMEOAlertMessageBase::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];
		memset( szBuffer, 0, sizeof(szBuffer) );
		
		_sntprintf( szBuffer, sizeof(szBuffer) - 1, TEXT("/%03d/%04d"), GetSitNumber(), GetSitDestination() );

		hr = WriteLine( lpStream, szBuffer );
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT 
CEMSSitMEOAlertMessageBase::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;

	CEMSBurstData* pBurstData = NULL;

	try
	{

		if ( lpStream )
		{
			// Final Solution Header (single instance)		
				// Burst Data Line (repeated for each burst)
					// Link Data Lines (repeated for each measurement)
					// Solution Data Line

			ULONG ulBursts = m_lstBurstData.Count();

			
			TCHAR szBuffer[512];
			memset( szBuffer, 0, sizeof(szBuffer) );

			CEMSSitMsgField msgField;


			ULONG ulMaxBursts = GetMaxBursts();

			// Final Solution Header Line
			// MF11/MF22/MF21
			_stprintf( szBuffer, TEXT("/%04d/%s/%02d"), m_ulLutID, msgField.TextMF22(m_i64BeaconID), min(ulBursts,ulMaxBursts) );
			hr = WriteLine( lpStream, szBuffer );

			if( EMS_OK == hr )
			{
				m_lstBurstData.MoveFirst();

				for( ULONG i = 0; (i < ulBursts) && (i < ulMaxBursts ); i++ )
				{
					// Burst Data Line
					// MFA01/MF13/MFA02

					pBurstData = m_lstBurstData.GetNext();

					EMSLOCATE locate = pBurstData->GetBurstSolution();

					CEMSObjectList<EMSCALIB406DATAEXT> lstPairs = pBurstData->GetBurstMeasurements();
					ULONG ulPairs = lstPairs.Count();

					_stprintf( szBuffer, TEXT("/%s/%s/%02d"), msgField.TextMFA01( pBurstData->GetTxTime() ),
															 msgField.TextMF13( 99999.9,
																				999.9,
																				99.99 ),
															 min(ulPairs,ulMaxBursts) );
															

					hr = WriteLine( lpStream, szBuffer );
					
					if( EMS_OK == hr )
					{
						lstPairs.MoveFirst();

						for( long j = 0; (j < ulPairs) && (j < ulMaxBursts ) && SUCCEEDED(hr); j++ )
						{
							EMSCALIB406DATAEXT linkPair = lstPairs.GetNext();

							// Link Data line.
							// /MF06/MF34/MF75/MF76/MF11/MF23/MF71/MFE02/MFE03/MF25/MF26/MF67/MF69/MF68/MF70/MF72/MF67/MFE01/MFE04/MFE05/MFE06/MF73/MFE07/MF23

							// E07 is expected to contain the uncorrected message.  It is not available
							// so fill with zeroes.

							// The second instance of MF23 is the 406 message (MF#23 30 Hexa) after elimination 
							// of the synchro bit but before correction of error.  It is not available, so
							// fill with zeroes.
							BYTE cZeroBeaconMsg[ 18 ];
							memset( cZeroBeaconMsg, 0, sizeof(cZeroBeaconMsg));

							double dLat = 0.0, dLong = 0.0;
							_GetEncodedLatLong( linkPair.calib406.cBeaconMsg, dLat, dLong );

							// Azimuth value needs to be between 0 and 360 degrees.
							// Expect we could get negative azimuths
							if( linkPair.calib406.dReserve1 < 0.0 )
							{
								while( linkPair.calib406.dReserve1 < 0.0 )
								{
									linkPair.calib406.dReserve1 += 360.0;
								}
							}

							// Don't allow negative elevations
							if( linkPair.calib406.dReserve2 < 0.0 )
							{
								linkPair.calib406.dReserve2 = 0.0;
							}

							TCHAR szUplinkToa[ 64 ];
							memset( szUplinkToa, 0, sizeof(szUplinkToa) );
							_tcscpy( szUplinkToa, msgField.TextMF67(linkPair.calib406.timeMsg) );

							TCHAR szToaGroundStation[ 64 ];
							memset( szToaGroundStation, 0, sizeof(szToaGroundStation) );
							_tcscpy( szToaGroundStation, msgField.TextMF67(linkPair.calib406.timeMsg.intTime + linkPair.calib406.i64TimeOffset) );

							// Note the two instances of MF23 below.  The spec. is not clear on the difference except that
							// the second instance (last field) is defined as the bit corrected message.  We only have the
							// corrected message at this point.  So, both instances will contain the corrected message.
							// Should this change, note that the TextMF23 method returns a pointer to a static.  So, two
							// distinct values cannot be obtained when calling the method within hte _stprintf call. To workaround
							// this, call TextMF23 for each field prior to _stprintf and store a copy of the return values in
							// a temp variable to be used in the _stprintf call.
							_stprintf( szBuffer, 
								TEXT("/%03d/%s/%s/%s/%04d/%s/%02d/%05.1f/%04.1f/%s/%s/%s/%08.6f/%013.3f/%+010.3f/%04.1f/%s/%014.3f/%1d/%1d/%1d/%07.3f/%s/%s"), 
										linkPair.calib406.hdr.id.ulSatID,
										msgField.TextMF34( linkPair.extras.SatTPVC.vTime),
										msgField.TextMF75A( linkPair.extras.SatTPVC.coord.radius.dX,
															linkPair.extras.SatTPVC.coord.radius.dY,
															linkPair.extras.SatTPVC.coord.radius.dZ),
										msgField.TextMF76A( linkPair.extras.SatTPVC.coord.velocity.dX,
															linkPair.extras.SatTPVC.coord.velocity.dY,
															linkPair.extras.SatTPVC.coord.velocity.dZ),
										linkPair.calib406.hdr.id.ulLutID,
										msgField.TextMF23( linkPair.calib406.cBeaconMsg),
										linkPair.calib406.wAntennaID,
										linkPair.calib406.dReserve1,	// Azimuth nnn.n
										linkPair.calib406.dReserve2,	// Elevation nn.n
										msgField.TextMF25( dLat ),
										msgField.TextMF26( dLong ),
										szUplinkToa,
										(linkPair.calib406.i64TimeOffset * 1e-9),
										linkPair.calib406.dFrequency,
										linkPair.calib406.dFreqOffset,
										linkPair.calib406.dCarrierPower,
										szToaGroundStation,
										linkPair.calib406.dFrequency + linkPair.calib406.dFreqOffset, //E01 nnnnnnnnnn.nnn (in Hz)
										linkPair.calib406.wBitErrorField1, //E04
										linkPair.calib406.wBitErrorField1, //E05
										linkPair.calib406.wBitErrorFrameSynch, //E06
										linkPair.calib406.dBitRate, //MF73
										msgField.TextMFE07( cZeroBeaconMsg ), //MFE07
										msgField.TextMF23( linkPair.calib406.cBeaconMsg)
								);

							hr = WriteLine( lpStream, szBuffer );
						}
					}

					if( EMS_OK == hr )
					{
						// Solution Data Line
						// Only applies for BurstData that not detect-only.
						if( !pBurstData->IsDetectOnly() )
						{
							EMSLOCATE location = pBurstData->GetBurstSolution();

							TCHAR szSolution[256];
							memset( szSolution, 0, sizeof(szSolution));

							_GetSolutionLine( location, szSolution, 255 );

							hr = WriteLine( lpStream, szSolution );

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
CEMSSitMEOAlertMessageBase::_GetEncodedLatLong( const BYTE cBeaconMsg[18], double& rdLat, double& rdLong )
{
	CBeaconMessage bcnMsg(cBeaconMsg );
	CBcnMsgDecodeBase decoder;
	decoder.Initialize();
	decoder.DecodeEx( bcnMsg );
	bool bHasEncoded = false;
	decoder.GetEncodedLocation( bHasEncoded, rdLat, rdLong );

	if( !bHasEncoded )
	{
		rdLat = 0.0;
		rdLong = 0.0;
	}

}

void
CEMSSitMEOAlertMessageBase::_GetSolutionLine( const EMSLOCATE& crLocate, TCHAR* szLine, const int ciMaxBuffer )
{

	CEMSSitMsgField msgField;

#ifdef UNICODE
	std::wstring firstData = msgField.TextMF14( crLocate.timeFirstData );
	std::wstring lastData = msgField.TextMF14( crLocate.timeLastData );
#else
	std::string firstData = msgField.TextMF14( crLocate.timeFirstData );
	std::string lastData = msgField.TextMF14( crLocate.timeLastData );
#endif

	// /MF16/MF14/MF14/MF25/MF26/MF77/MF79/MFA03
	_sntprintf( szLine, ciMaxBuffer, TEXT("/%1d/%s/%s/%s/%s/%s/%s/%05.2f"), 
				min( crLocate.wlsSolution.wNumIterations, 9 ),
				firstData.c_str(),
				lastData.c_str(),
				msgField.TextMF25( crLocate.wlsSolution.location.degLatitude ),
				msgField.TextMF26( crLocate.wlsSolution.location.degLongitude),
				// Altitude is spec'd as MF77 in ICD. This is already used for Bcn Msg.
				// Pending clarification, use a float.
				msgField.TextMF77( double( crLocate.wlsSolution.location.fAltitude ) ),
				// CNR is spec'd as MF79 in ICD.  This is not defined.
				// Pending clarification, assume it should be MF 72.
				msgField.TextMF79( double( crLocate.fPower ) ),
				(crLocate.wlsSolution.fRadiusErrEllipse > 99.99) ? 99.99 : crLocate.wlsSolution.fRadiusErrEllipse
				);
}