/*********************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:
	$
********************************************************************/

#include "adchannel.h"
#include "memtypes.h"
#include "collmsgs.h"
#include "wave/waveex.h"
#include "convutility.h"

#include <assert.h>
#include <sstream>

CEMSADChannel::CEMSADChannel() : m_pBoard(NULL), m_ausBuffer(NULL), m_ulBufferLen(0), m_bIsRunning(false),
								m_iChannelNo(0), m_iADBoardNo(0), m_ulDmaOffset(0), m_ulLutID(0), m_ulSatID(0),
								m_ulAntennaID(0), m_ulProcessFlags(0), m_i64Dropouts(0),
								m_i64LastBlockCount(0), m_dwADBoardBufferSize(0),
								m_dwADBoardSampleSize(0), m_dwADBoardSampleRate(0),
								m_hBoardEvent(INVALID_HANDLE_VALUE), m_pData(NULL)
{
	m_oLogger.SetParent( L"CEMSADChannel" );
	memset( &m_statusInfo, 0, sizeof(m_statusInfo) );

	m_pData = new TDataExport;

	if( !m_pData )
	{
		THROW_NOMEMORY_EXCEPTION();
	}

	memset( m_pData, 0, sizeof(TDataExport) );
}

CEMSADChannel::CEMSADChannel( const CEMSADChannel& x ) : m_pBoard( x.m_pBoard ),
														m_bIsRunning(false), m_iChannelNo( x.m_iChannelNo ),
														m_iADBoardNo( x.m_iADBoardNo ),
														m_oChannelProcessor( x.m_oChannelProcessor ),
														m_ulDmaOffset( x.m_ulDmaOffset ),
														m_oqueueWave( x.m_oqueueWave ),
														m_oLogger( x.m_oLogger ),
														m_ulLutID( x.m_ulLutID ), 
														m_ulSatID( x.m_ulSatID ),
														m_ulAntennaID( x.m_ulAntennaID ),
														m_ulProcessFlags( x.m_ulProcessFlags ),
														m_statusInfo( x.m_statusInfo ),
														m_i64Dropouts( x.m_i64Dropouts ),
														m_i64LastBlockCount( x.m_i64LastBlockCount ),
														m_dwADBoardBufferSize( x.m_dwADBoardBufferSize ),
														m_dwADBoardSampleSize( x.m_dwADBoardSampleSize), 
														m_dwADBoardSampleRate( x.m_dwADBoardSampleRate ),
														m_hBoardEvent( x.m_hBoardEvent ),
														m_owszBoardEventName( x.m_owszBoardEventName ),
														m_pData(NULL)
{
	if( m_pBoard )
		m_pBoard->AddRef();

	_AllocateBuffer( x.m_ulBufferLen );

	if( m_ausBuffer )
		memcpy( m_ausBuffer, x.m_ausBuffer, x.m_ulBufferLen*sizeof(m_ausBuffer[0]) );

	m_pData = new TDataExport;

	if( !m_pData )
	{
		THROW_NOMEMORY_EXCEPTION();
	}

	if( x.m_pData )
		memcpy( m_pData, x.m_pData, sizeof(TDataExport) );
	else
		memset( m_pData, 0, sizeof(TDataExport) );
}

CEMSADChannel::~CEMSADChannel()
{
	Stop();
	_ReleaseBuffer();
	_ReleaseBoard();

	if( INVALID_HANDLE_VALUE != m_hBoardEvent )
	{
		CloseHandle( m_hBoardEvent );
	}

	if( m_pData )
	{
		delete m_pData;
		m_pData = NULL;
	}
}

void 
CEMSADChannel::SetBufferLen( const ULONG culBufferLen )
{
	bool bWasRunning = m_bIsRunning;

	Stop();

	_AllocateBuffer( culBufferLen );

	if( bWasRunning )
		Start();
	
}

void 
CEMSADChannel::SetADBoardProperties( const DWORD cdwBufferSize, const DWORD cdwSampleSize, 
										const DWORD cdwSampleRate )
{
	m_dwADBoardBufferSize = cdwBufferSize;
	m_dwADBoardSampleSize = cdwSampleSize;
	m_dwADBoardSampleRate = cdwSampleRate;
}

void 
CEMSADChannel::SetProcessFlags( const ULONG culFlags ) 
{ 
	m_ulProcessFlags = culFlags; 

	m_ulDmaOffset = ( m_ulProcessFlags == CEMSChannelProcessor::ms_cdwDnlkNoPhaseModulation ) ? FIR_OVERLAP : EMS_RAW_OVERLAP;
}


void 
CEMSADChannel::Start()
{
	if( !m_bIsRunning )
	{
		assert( m_pBoard );

		if( !m_pBoard )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		assert( m_ausBuffer );

		if( !m_ausBuffer )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		_ResetCounters();

		EMS_RESULT hr = EMS_OK;

		if( !m_owszBoardEventName.empty() )
		{
			hr = m_pBoard->SetEventNameA( const_cast<unsigned char*>(reinterpret_cast<const unsigned char*>(CEMSConversionUtil::ConvertToString( m_owszBoardEventName.c_str() ).c_str())) );

			if( EMS_OK != hr )
			{
				THROW_RUNTIME_EXCEPTION(hr);
			}
		}

		hr = m_pBoard->SetTransferBuffer( (short *) &(m_ausBuffer[ m_ulDmaOffset ]) );

		if( EMS_OK != hr )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		hr = m_pBoard->Start();

		if( EMS_OK != hr )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}
		
		m_bIsRunning = true;
	}
}

void 
CEMSADChannel::Stop()
{
	if( m_bIsRunning )
	{
		assert( m_pBoard );

		if( !m_pBoard )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		EMS_RESULT hr = m_pBoard->Stop();
		
		if( EMS_OK != hr )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		m_bIsRunning = false;
	}
}

void 
CEMSADChannel::SetSource( const int ciADBoardNo, const int ciChannelNo, LPEMSADBOARD pADBoard )
{
	m_iADBoardNo = ciADBoardNo;
	m_iChannelNo = ciChannelNo;

	if( m_pBoard )
	{
		_ReleaseBoard();
	}

	m_pBoard = pADBoard;

	if( m_pBoard )
		m_pBoard->AddRef();

}

HANDLE 
CEMSADChannel::GetDataReadyHandle( const ULONG culBoardID )
{
	HANDLE hRet = INVALID_HANDLE_VALUE;

	if( INVALID_HANDLE_VALUE == m_hBoardEvent )
	{
		std::wstringstream owstrmEvent;
		owstrmEvent << culBoardID << L"_" << m_iChannelNo;

		m_owszBoardEventName = owstrmEvent.str();

		// The event must be manually reset.  This allows testing whether the event is signalled
		// without WaitForMultipleObjects telling us so.
		m_hBoardEvent = CreateEventW( NULL, TRUE, FALSE, m_owszBoardEventName.c_str() );

		if( INVALID_HANDLE_VALUE == m_hBoardEvent )
		{
			THROW_RUNTIME_EXCEPTION( CEMSConversionUtil::ErrnoToEMSResult( GetLastError() ) );
		}
	}

	hRet = m_hBoardEvent;

	
	return hRet;
}

bool 
CEMSADChannel::ProcessBuffer()
{
	bool bRet = false;

	CEMSWaveEx* pWave = NULL;
	CEMSWaveEx* pWaveDC = NULL;
	
	bool bADBoardLocked = false;

	try
	{
		// Process only if in the signalled state.
		if( INVALID_HANDLE_VALUE != m_hBoardEvent &&
			WAIT_OBJECT_0 == WaitForSingleObject( m_hBoardEvent, 0 ) )
		{
			if( m_ausBuffer )
			{
				assert( m_pBoard );

				if( !m_pBoard )
				{
					THROW_NULL_POINTER_EXCEPTION();
				}

				assert( m_pData );

				if( !m_pData )
				{
					THROW_NULL_POINTER_EXCEPTION();
				}

				// Lock the A/D Board buffer.
				EMS_RESULT hr = m_pBoard->LockBuffer( TRUE );

				if( EMS_OK == hr )
				{
					bADBoardLocked = true;

					INT64 i64Dropouts = 0;
					hr = m_pBoard->GetDropoutCount( &i64Dropouts );

					if( EMS_OK != hr )
					{
						THROW_RUNTIME_EXCEPTION(hr);
					}

					if ( i64Dropouts > m_i64Dropouts )
					{
						m_i64Dropouts = i64Dropouts;

						if ( m_i64Dropouts < 3 )
						{
							EMSLOG0( (&m_oLogger), EMSLogMsgInfo, EMS_COLL_AD_OVERFLOW );
						}
						else if ( m_i64Dropouts < 10 )
						{
							EMSLOG0( (&m_oLogger), EMSLogMsgWarn, EMS_COLL_AD_OVERFLOW );
						}
						else
						{
							EMSLOG0( (&m_oLogger), EMSLogMsgAlarm, EMS_COLL_AD_OVERFLOW );
						}
					}

					// Map incoming data to export buffer
					memset( m_pData, 0, sizeof( TDataExport ) );

					// Get UTC time for beginning of this buffer
					hr = m_pBoard->GetBufferTime( &m_pData->timeBuffer );

					if( EMS_OK != hr )
					{
						THROW_RUNTIME_EXCEPTION(hr);
					}
					
					m_pData->timeStart = m_pData->timeBuffer;

					INT64 i64Blockcount = 0;
					hr = m_pBoard->GetBlockCount( &i64Blockcount );

					if( EMS_OK != hr )
					{
						THROW_RUNTIME_EXCEPTION( hr );
					}

					m_pData->Data_Identifier = (ULONG) i64Blockcount;

					// Have we lost a buffer?
					if ( m_pData->Data_Identifier != m_i64LastBlockCount + 1 )
					{
						m_oLogger.LogMsg( EMSLogMsgDebug, __FILE__, __LINE__, 
									L"Data ID not equal to last block count + 1.  DataID = %I64d, LastBlockCount = %I64d.", 
									m_pData->Data_Identifier, 
									m_i64LastBlockCount );

						m_oChannelProcessor.ResetLastCorrectedTime();
					}

					m_i64LastBlockCount = m_pData->Data_Identifier;

					m_pData->Data_Dropouts = i64Dropouts;

					INT64 i64MarkerTimeOffset = 0;

					hr = m_pBoard->GetMarkerTimeOffset( &i64MarkerTimeOffset );

					if( EMS_OK != hr )
					{
						THROW_RUNTIME_EXCEPTION( hr );
					}

					double dAGCRMS = 0.0;
					double dAGCMean = 0.0;
					bool bGoodMarkerBit = m_oChannelProcessor.ComputeADCMeasurements( m_ausBuffer, 
														m_ulBufferLen, i64MarkerTimeOffset, 
														m_pData->timeBuffer, m_pData->timeStart, 
														m_pData->Marker_Bit_Rate, 
														dAGCMean, dAGCRMS );

					m_pData->AGC_RMS = (float) dAGCRMS;
					m_pData->AGC_Mean = (float) dAGCMean;
					
					ULONG ulSize1 = m_ulBufferLen - m_ulDmaOffset;
					ULONG ulSampleBytes = sizeof(short)*SAMPLE_SIZE;

					ULONG ulSize = ( ulSampleBytes <= ulSize1) ? ulSampleBytes : ulSize1;

					BYTE* pbyData = (BYTE*) &(m_ausBuffer[ m_ulDmaOffset ]);

					// Build the wave.
					pWave = _GenerateWave( 	m_pData->timeBuffer, m_pData->Marker_Bit_Rate, bGoodMarkerBit, 
											m_pData->AGC_Mean, m_pData->AGC_RMS, ulSize, pbyData );

					assert( pWave );

					if( !pWave )
					{
						THROW_NULL_POINTER_EXCEPTION();
					}

					// Downconvert?
					// Assume requires down conversion and phase mod when phase mode setting is true.
					if ( m_ulProcessFlags == CEMSChannelProcessor::ms_cdwDnlkNoPhaseModulation )
						pWaveDC = m_oChannelProcessor.DigitalDownConvert( false, pWave );
					else
						pWaveDC = m_oChannelProcessor.DigitalDownConvert( true, pWave );

					pWave->Release();
					pWave = NULL;

					// Add Wave to queue.
					m_oqueueWave.Push( pWaveDC );

					pWaveDC->Release();
					pWaveDC = NULL;

					// Unlock the A/D Board buffer.
					hr = m_pBoard->UnlockBuffer();

					if( EMS_OK != hr )
					{
						THROW_RUNTIME_EXCEPTION(hr);
					}

					bADBoardLocked = false;

					// Save Collector stats.
					_SaveStats( m_pData );
				}

				// Reset the event.
				ResetEvent( m_hBoardEvent );
			
				bRet = true;
			}
		}
	}
	catch( ... )
	{
		if( bADBoardLocked )
		{
			if( m_pBoard )
				m_pBoard->UnlockBuffer();
		}

		if( pWave )
		{
			pWave->Release();
			pWave = NULL;
		}

		if( pWaveDC )
		{
			pWaveDC->Release();
			pWaveDC = NULL;
		}

		throw;
	}


	return bRet;
}

CEMSWaveEx* 
CEMSADChannel::GetNextWave()
{
	return m_oqueueWave.Pop();
}

CEMSWaveEx* 
CEMSADChannel::_GenerateWave(	const EMSTIME ctimeBuffer, const ULONG culSampleRate, 
								const bool cbGoodMarkerBit,	const float cfAGCMean, 
								const float cfAGCRMS, const ULONG culSize, const BYTE* cpData )
{
	CEMSWaveEx* pWaveOut = 0;

	try
	{
		if( cpData )
		{
			pWaveOut = new CEMSWaveEx;

			if( !pWaveOut )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			pWaveOut->Write( cpData, culSize );

			// Set format properties.

			pWaveOut->GetFormatChunkRef().SetAudioFormat( 1 );	// PCM
			pWaveOut->GetFormatChunkRef().SetNumChannels( 1 );	// Mono
			pWaveOut->GetFormatChunkRef().SetSampleRate( ( 0 != culSampleRate ) ? culSampleRate : SAMPLE_RATE );
			pWaveOut->GetFormatChunkRef().SetBitsPerSample( 16 );


			pWaveOut->GetExtendedInfoRef().GetLutDetailsRef().SetLutID( m_ulLutID );
			pWaveOut->GetExtendedInfoRef().GetLutDetailsRef().SetAntennaID( (WORD) m_ulAntennaID );
			pWaveOut->GetExtendedInfoRef().GetSatDetailsRef().SetSatID( m_ulSatID );
			pWaveOut->GetExtendedInfoRef().GetPropertiesRef().SetTimeStart( ctimeBuffer );

			// Set additional properties indicating whether the signal requires
			// phase demod or down-conversion.
			pWaveOut->GetExtendedInfoRef().GetSignalDetailsRef().SetMeanADC( cfAGCMean );
			pWaveOut->GetExtendedInfoRef().GetSignalDetailsRef().SetStdDevADC( cfAGCRMS );

			// Wave has not yet been downconverted:
			pWaveOut->GetExtendedInfoRef().GetSignalDetailsRef().SetDCState( EMS_DC_NO );
			
			// Set flag indicating whether the marker bit was found for this measurement.
			pWaveOut->GetExtendedInfoRef().GetSignalDetailsRef().SetFlags( cbGoodMarkerBit ? CEMSWaveExtSignalDetails::EMSWAVEEXSIGNAL_GOOD_MARKER_BIT : CEMSWaveExtSignalDetails::EMSWAVEEXSIGNAL_BAD_MARKER_BIT );

			if ( m_ulProcessFlags == CEMSChannelProcessor::ms_cdwDnlkNoPhaseModulation )
			{
				pWaveOut->GetExtendedInfoRef().GetSignalDetailsRef().SetPhaseModState( EMS_PHASE_MOD_NO );
			}
			else
			{
				pWaveOut->GetExtendedInfoRef().GetSignalDetailsRef().SetPhaseModState( EMS_PHASE_MOD_YES );
			}
		}
	}
	catch( ... )
	{
		if( pWaveOut )
		{
			pWaveOut->Release();
			pWaveOut = 0;
		}

		throw;
	}

	return pWaveOut;
}

void
CEMSADChannel::_SaveStats( const TDataExport* cpData )
{
	// Status block update
	m_statusInfo.carrierTime = cpData->timeBuffer;

	if ( cpData->Mod_Index_Mean > MOD_INDEX_THRESHOLD )
	{
		m_statusInfo.uCarrierLossCount++;
		m_statusInfo.uCarrierLossDuration++;
	}
	else
	{
		m_statusInfo.uCarrierLossDuration = 0;
	}

	m_statusInfo.fCarrierFrequency = cpData->Carrier_Frequency;
	m_statusInfo.fCarrierModIndexMax = cpData->Mod_Index;
	m_statusInfo.fCarrierModIndexMean = cpData->Mod_Index_Mean;
	m_statusInfo.fCarrierModIndexRMS = cpData->Mod_Index_RMS;
	m_statusInfo.ulMarkerBitRate = cpData->Marker_Bit_Rate;
	m_statusInfo.fAGCRMS = cpData->AGC_RMS;
	m_statusInfo.fAGCMean = cpData->AGC_Mean;

	CEMSTime timeDiff;
	timeDiff.SetTime( cpData->timeBuffer );
	m_statusInfo.fAGCMean = (float)timeDiff.SecondsDifferent( cpData->timeStart );
}

void 
CEMSADChannel::_AllocateBuffer( const ULONG culLen )
{
	if( culLen > 0 )
	{
		_ReleaseBuffer();

		m_ausBuffer = new USHORT[ culLen ];

		if( !m_ausBuffer )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( m_ausBuffer, 0, culLen*sizeof(m_ausBuffer[0]) );

		m_ulBufferLen = culLen;
	}
}

void
CEMSADChannel::_ReleaseBuffer()
{
	if( m_ausBuffer )
	{
		delete[] m_ausBuffer;
		m_ausBuffer = NULL;

		m_ulBufferLen = 0;
	}
}

void
CEMSADChannel::_ResetCounters()
{
	m_i64Dropouts = 0;
	m_i64LastBlockCount = 0;
	m_oChannelProcessor.InitPass( m_dwADBoardSampleRate, m_dwADBoardSampleSize, m_ulProcessFlags );
}

void 
CEMSADChannel::_ReleaseBoard()
{
	if( m_pBoard )
	{
		m_pBoard->Reset();
		m_pBoard->Release();
		m_pBoard = NULL;
	}
}