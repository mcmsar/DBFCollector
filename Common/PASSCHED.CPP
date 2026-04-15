/*******************************************************************
*	Module:			PasSched.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	LeoLut600 CEMSPassSchedule class
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:		NOTE: The EMSSATELLITETRACK data structures currently
*						used actualStartTime and actualEndTime for the AOS 
*						LOS respectively.  We track from timeAOS to timeLOS
*						( This should be fixed in a future release )
*
*********************************************************************
*	              Copyright (c) 2001 by EMS Technologies, Inc.,
*										All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	02/08/12		rvw	start

********************************************************************/
#pragma warning(disable:4786)

#include <assert.h>
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <io.h>
#include <errno.h>

#include <map>

#include "emstime.h"
#include "emsclock.h"
#include "emscoord.h"
#include "emsconfg.h"
#include "passched.h"
#include "convutility.h"

// assume logging already initialized in mainline
#include "emsexcpt.h"
#include "logMsgParam.h"
#include "logHelper.h"
#include "MastMsgs.h"

const CEMSSystemClock 	c_sysClock;
const ULONG				c_ulMaxValidPasses	= 8;
const int				c_nMaxOpenRetries 	= 30;
const TCHAR 			c_szPassSchedTxtFile[] = TEXT("PassSched.txt");
const TCHAR 			c_szPassSchedDatFile[] = TEXT("PassSched.dat");
const unsigned int 		c_unStackSize = 0;	// use default stack size
const clock_t 			c_clkThreadExitTimeout = CLOCKS_PER_SEC * 60 * 2; // two minutes
const float 			c_fMinutesBeforeSchedule = 20; 
const float 			c_fHoursInSchedule			= 24.0;
const double			c_dMinMinutesBeforeLOS		= 5.0;

const CEMSCoordSystem	c_coordSys;


CEMSPassSchedule::CEMSPassSchedule()
{
	m_hrLastError = EMS_OK;

	m_hThread = INVALID_HANDLE_VALUE;
	m_unThreadID = 0;

	m_hMutexSchedule = CreateMutex( 0, FALSE , 0);

	memset( &m_sched, 0, sizeof( m_sched ) );

	memset( &m_schedSettings, 0, sizeof( m_schedSettings ) );

	m_schedSettings.dDuration = (double)c_fHoursInSchedule;
	m_schedSettings.dFrequency = (double)c_fHoursInSchedule;
	m_schedSettings.flags = EMSSchedFlag_Default;

	m_ulSatCount = 0;
	memset( m_ulSatellites, 0, sizeof( m_ulSatellites ) );

	m_ulSecondaryLutCount = 0;
	memset( m_ulSecondaryLuts, 0, sizeof( m_ulSecondaryLuts ) );

	m_ulLutID = 9999; // Current Location ( default )

	m_lpszDataDirectory = 0;

	m_lpTrackSched = 0;

	m_lpOrbit = 0;

	m_bFirstTimeAfterStartup = TRUE;

	m_bNewScheduleGenerated = FALSE;
	m_bNewScheduleInstalled = FALSE;

	m_dPrePassDuration = 60.0 * 4.0;	// ie 4 minutes
}

CEMSPassSchedule::~CEMSPassSchedule()
{
	Reset();

	if ( m_lpszDataDirectory )
	{
		delete [] m_lpszDataDirectory;
		m_lpszDataDirectory = 0;
	}

	if ( m_hMutexSchedule != INVALID_HANDLE_VALUE )
	{
		CloseHandle( m_hMutexSchedule );

		m_hMutexSchedule = INVALID_HANDLE_VALUE;
	}
}

EMS_RESULT CEMSPassSchedule::Initialize( EMSSCHEDULEINFO settings, 
			ULONG *lpulSatellites, ULONG ulSatCount, ULONG ulLutID, 
			EMSLOCATION locationLUT,
			ULONG *lpulSecondaryLuts, ULONG ulSecondaryLutCount, 
			IEMSTrackSchedule *lpTrackSchedObj, IEMSOrbit *lpOrbit )
{
	EMS_RESULT hr = EMS_OK;
	ULONG i;

	if ( lpTrackSchedObj )
	{
		lpTrackSchedObj->AddRef();
	}

	if ( lpOrbit )
	{
		lpOrbit->AddRef();
	}

	Reset();

	m_locationLUT = locationLUT;

	m_bFirstTimeAfterStartup = TRUE;

	m_schedSettings = settings;

	m_ulLutID = ulLutID; 

	m_ulSatCount = ( ulSatCount <= EMS_MAX_SATELLITES ) ? ulSatCount : EMS_MAX_SATELLITES;

	for ( i = 0; lpulSatellites && ( i < m_ulSatCount ); i++ )
		m_ulSatellites[i] = lpulSatellites[i];

	m_ulSecondaryLutCount = ( ulSecondaryLutCount <= EMS_MAX_LUTS ) ? ulSecondaryLutCount : EMS_MAX_LUTS;

	for ( i = 0; lpulSecondaryLuts && ( i < m_ulSecondaryLutCount ); i++ )
		m_ulSecondaryLuts[i] = lpulSecondaryLuts[i];


	m_lpTrackSched = lpTrackSchedObj;

	m_lpOrbit = lpOrbit;

	return EMS_OK;
}

EMS_RESULT CEMSPassSchedule::Reset( void )
{
	if ( m_lpTrackSched )
	{
		m_lpTrackSched->Release();
		m_lpTrackSched = 0;
	}

	if ( m_lpOrbit )
	{
		m_lpOrbit->Release();
		m_lpOrbit = 0;
	}
	return EMS_OK;
}

// "Valid" if Lut didn't suppress the pass
//
INT CEMSPassSchedule::GetValidPassCount( void )
{
	INT nValidCount = 0;
	TCHAR szFlags[8];

	for ( int i = 0; i < (int)m_sched.ulCount; i++ )
	{
		switch ( m_sched.track[i].PassInfo.ulFlags & EMS_PASSFLAG_ORIGIN_MASK )	// origin
		{
			default:								szFlags[0] = '.'; break;
			case EMS_PASSFLAG_LUT:			szFlags[0] = 'L'; break;
			case EMS_PASSFLAG_MCC:			szFlags[0] = 'M'; break;
			case EMS_PASSFLAG_RCC:			szFlags[0] = 'R'; break;
			case EMS_PASSFLAG_OPERATOR:	szFlags[0] = 'O'; break;
		}

		switch ( m_sched.track[i].PassInfo.ulFlags & EMS_PASSFLAG_STATUS_MASK )
		{
			default:								szFlags[1] = 'P'; break;
			case EMS_PASSFLAG_SUPPRESS: 	szFlags[1] = 'X'; break;
			case EMS_PASSFLAG_PROCESS:		szFlags[1] = 'F'; break;
			case EMS_PASSFLAG_REDUNDANT:	szFlags[1] = 'R'; break;
		}

		szFlags[2] = 0;

		if ( lstrcmp( szFlags, TEXT("LX") ) != 0 ) 
			nValidCount++;
	}
	return nValidCount;
}

EMSTIME CEMSPassSchedule::GetActualLOSTime( ULONG ulIndex )
{
	return ( ulIndex < m_sched.ulCount ) ? m_sched.track[ulIndex].actualEndTime : CEMSTime(0);
}

EMSTIME CEMSPassSchedule::GetLOSTime( ULONG ulIndex )
{
	return ( ulIndex < m_sched.ulCount ) ? m_sched.track[ulIndex].PassInfo.timeLOS : CEMSTime(0);
}

bool CEMSPassSchedule::IsPassTruncated( ULONG ulIndex )
{
	bool bTruncated = false;
	CEMSTime timeBegin, timeEnd;

	timeBegin.SetTime( GetAOSTime( ulIndex ) );

	timeEnd.SetTime( GetLOSTime( ulIndex ) );

	if ( ( timeBegin.SecondsDifferent( GetActualAOSTime( ulIndex ) )  < -1.0 ) || 
			( timeEnd.SecondsDifferent( GetActualLOSTime( ulIndex ) ) > 1.0 ) ) 
	{
		bTruncated = true;
	}

	return bTruncated;
}

EMSTIME CEMSPassSchedule::GetActualAOSTime( ULONG ulIndex )
{
	return ( ulIndex < m_sched.ulCount ) ? m_sched.track[ulIndex].actualStartTime : CEMSTime(0);
}

EMSTIME CEMSPassSchedule::GetAOSTime( ULONG ulIndex )
{
	return ( ulIndex < m_sched.ulCount ) ? m_sched.track[ ulIndex ].PassInfo.timeAOS : CEMSTime(0);
}

ULONG CEMSPassSchedule::GetSatID( ULONG ulIndex )
{
	return ( ulIndex < m_sched.ulCount ) ? m_sched.track[ ulIndex ].PassInfo.ulSatelliteID : 0;
}

ULONG CEMSPassSchedule::GetOrbitNumber( ULONG ulIndex )
{
	return ( ulIndex < m_sched.ulCount ) ? m_sched.track[ ulIndex ].PassInfo.ulOrbitNumber : 0;
}

WORD CEMSPassSchedule::GetState( ULONG ulIndex )
{
	return ( ulIndex < m_sched.ulCount ) ? m_sched.wState[ ulIndex ] : 0;
}


void CEMSPassSchedule::SetState( ULONG ulIndex, WORD wState )
{
	if ( ulIndex < m_sched.ulCount )
		m_sched.wState[ ulIndex ] = wState;
}

void CEMSPassSchedule::AddState( ULONG ulIndex, WORD wState )
{
	if ( ulIndex < m_sched.ulCount )
		m_sched.wState[ ulIndex ] += wState;
}

EMSTIME CEMSPassSchedule::GetPrePassTime( ULONG ulIndex )
{
	return ( ulIndex < m_sched.ulCount ) ? m_sched.timePrePass[ ulIndex ] : CEMSTime(0);
}

EMSSATELLITETRACK *CEMSPassSchedule::GetTrackPtr( ULONG ulIndex )
{
	return ( ulIndex < m_sched.ulCount ) ? &m_sched.track[ ulIndex ] : 0;
}

BOOL CEMSPassSchedule::LockSchedule( BOOL bWait )
{
	return ( WaitForSingleObject(m_hMutexSchedule, (bWait) ? INFINITE : 1) == WAIT_OBJECT_0 );
}

void CEMSPassSchedule::UnlockSchedule( void )
{
	ReleaseMutex( m_hMutexSchedule );
}

EMS_RESULT CEMSPassSchedule::SetDataDirectory( LPCTSTR lpcszDataDirectory )
{
	EMS_RESULT hr = EMS_OK;

	if ( m_lpszDataDirectory )
	{
		delete [ ] m_lpszDataDirectory;
		m_lpszDataDirectory = 0;
	}

	if ( lpcszDataDirectory && *lpcszDataDirectory )
	{
		m_lpszDataDirectory = new TCHAR[ lstrlen( lpcszDataDirectory ) + 1 ];

		if ( m_lpszDataDirectory )
			lstrcpy( m_lpszDataDirectory, lpcszDataDirectory );
		else
			hr = EMS_NO_MEMORY;
	}
	return hr;
}

EMS_RESULT CEMSPassSchedule::_OpenFileWhenNotBusy( FILE **lplpFilePtr, LPCTSTR lpcszFile, LPCTSTR lpcszOptions )
{
	FILE *lpFile = 0;
	EMS_RESULT hr = EMS_OK;
	int nRetries = 0;

	if ( lplpFilePtr && lpcszFile && *lpcszFile && lpcszOptions && *lpcszOptions )
	{
		TCHAR szFilespec[256];

		if ( m_lpszDataDirectory && *m_lpszDataDirectory )
			_stprintf( szFilespec, TEXT("%s\\%s"), m_lpszDataDirectory, lpcszFile );
		else
			lstrcpy( szFilespec, lpcszFile );

		while ( !lpFile && ( hr == EMS_OK ) )
		{
			lpFile = fopen( szFilespec, lpcszOptions );

			if ( !lpFile )
			{
				switch ( errno )
				{
					case EACCES:
					case EBUSY:	
						if ( nRetries++ > c_nMaxOpenRetries )
							hr = EMS_TIMEOUT;
						else
							Sleep( 1000 ); // stall for one second
						break;

					case ENOENT:
						hr = EMS_FILE_NOT_FOUND;
						break;

					default:
						hr = CEMSConversionUtil::ErrnoToEMSResult( errno );
				}
			}
		}
	}
	else
		hr = EMS_BAD_PARAM;

	if ( lplpFilePtr )
		*lplpFilePtr = lpFile;

	return hr;
}

void CEMSPassSchedule::_WriteFile( const void *lpBuffer, size_t size, size_t count, FILE *lpFile  )
{	
	if ( fwrite( lpBuffer, size, count, lpFile ) != count )
		throw EMS_IO_ERROR;
}

void CEMSPassSchedule::_ReadFile( void *lpBuffer, size_t size, size_t count, FILE *lpFile  )
{	
	size_t nCount = fread( lpBuffer, size, count, lpFile );
	
	if ( nCount != count )
		throw EMS_IO_ERROR;
}

EMS_RESULT CEMSPassSchedule::_AddTrackToSchedule( EMSSATELLITETRACK *lpTrackInfo )
{
	EMS_RESULT hr = EMS_FALSE;

	if ( lpTrackInfo )
	{
		ULONG i;
		int nIndex = -1;
		CEMSTime timeStart( lpTrackInfo->actualStartTime ); // Really AOS

		nIndex = _FindPassIndex( lpTrackInfo->ulLutID, 
								lpTrackInfo->PassInfo.ulSatelliteID, 
								lpTrackInfo->actualStartTime, 0 );

		if ( nIndex >= 0 ) // replace existing entry
		{
			m_sched.track[ nIndex ] = *lpTrackInfo;

			m_sched.wState[ nIndex ] = 0;

			m_sched.timePrePass[ nIndex ];
		}
		else		// a new entry
		{
			if ( m_sched.ulCount < EMS_MAX_NUM_OPT_SAT_PASSES )
			{
				// now want to insert them in ascending start time order

				for ( i = 0; ( i < m_sched.ulCount ) && 
					( timeStart.SecondsDifferent( m_sched.track[i].actualStartTime) < 0.0 ); i++ )
				{
				}

				if ( i < m_sched.ulCount )	// need to insert : else just append
				{
					for ( ULONG j = m_sched.ulCount; j > i; j-- )
					{
						m_sched.track[ j ] = m_sched.track[ j - 1 ];
						m_sched.wState[ j ] = m_sched.wState[ j - 1 ];
						m_sched.timePrePass[ j ] = m_sched.timePrePass[ j - 1 ];
					}
			
				}

				m_sched.track[ i ] = *lpTrackInfo;

				m_sched.wState[ i ] = 0;

				m_sched.timePrePass[ i ];

				m_sched.ulCount++;
			}
			else
				hr = EMS_OVERFLOW;
		}
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

void CEMSPassSchedule::_SetTrackInfo( EMSSATELLITETRACK *lpTrackInfo, LPEMSSIT260DATA lpSitData ) 
{
	if ( lpTrackInfo )
	{
		CEMSTime timePassStart, timePassStop;
//		bool bLutCorrected = false;

		memset( lpTrackInfo, 0, sizeof( EMSSATELLITETRACK) );

		if ( lpSitData )
		{
			ULONG ulOrbitNumber = 0;

			lpTrackInfo->ulLutID = lpSitData->ulLutID;

			lpTrackInfo->PassInfo.ulSatelliteID = lpSitData->ulSatID;

			lpTrackInfo->PassInfo.ulOrbitNumber = lpSitData->ulOrbitNumber;

//			ulOrbitNumber = _GetOrbitNumber( lpSitData->ulSatID, lpSitData->timeAOS );
//
//			if ( ulOrbitNumber != lpTrackInfo->PassInfo.ulOrbitNumber )
//			{
//				// if non-zero : indicate that LUT changed it
//
//				if ( lpTrackInfo->PassInfo.ulOrbitNumber )
//				{
//					bLutCorrected = true;
//				}
//					
//				lpTrackInfo->PassInfo.ulOrbitNumber = ulOrbitNumber;
//			}

			// NOTE:: internal name(s) are reversed for AOS/LOS and actualStart/End

			lpTrackInfo->actualStartTime = lpSitData->timeAOS;

			timePassStart.SetTime( lpSitData->timeAOS );

			timePassStart.AddSeconds( (float)lpSitData->dStartDataCollectionOffset );
			
			lpTrackInfo->PassInfo.timeAOS = timePassStart;

			lpTrackInfo->actualEndTime = lpSitData->timeLOS;

			timePassStop.SetTime( lpSitData->timeLOS );

			timePassStop.AddSeconds( -(float)lpSitData->dStopDataCollectionOffset );
			
			lpTrackInfo->PassInfo.timeLOS = timePassStop;

			lpTrackInfo->PassInfo.degMaxElevation = lpSitData->degMaxElevation;

			lpTrackInfo->PassInfo.degAzimuthAOS = lpSitData->degAzimuthAOS;

			lpTrackInfo->PassInfo.degAzimuthLOS = lpSitData->degAzimuthLOS;

			switch ( lpSitData->wPassSchedOrigin )
			{
				case 'L':
					lpTrackInfo->PassInfo.ulFlags |= EMS_PASSFLAG_LUT;
					break;

				case 'M':
					lpTrackInfo->PassInfo.ulFlags |= EMS_PASSFLAG_MCC;
					break;

				case 'R':
					lpTrackInfo->PassInfo.ulFlags |= EMS_PASSFLAG_RCC;
					break;

				case 'O':
					lpTrackInfo->PassInfo.ulFlags |= EMS_PASSFLAG_OPERATOR;
					break;

				default:
					break;
			}

//			if ( bLutCorrected )
//			{
//				lpTrackInfo->PassInfo.ulFlags &= ~EMS_PASSFLAG_ORIGIN_MASK;
//
//				lpTrackInfo->PassInfo.ulFlags |= EMS_PASSFLAG_LUT;
//			}
			
			// First clear the status flag.
			lpTrackInfo->PassInfo.ulFlags &= ~EMS_PASSFLAG_STATUS_MASK;

			switch ( lpSitData->wPassSchedStatus )
			{
				case 'F':
					lpTrackInfo->PassInfo.ulFlags |= EMS_PASSFLAG_PROCESS;
					break;

				case 'X':
					lpTrackInfo->PassInfo.ulFlags |= EMS_PASSFLAG_SUPPRESS;
					break;

				case 'R':
					lpTrackInfo->PassInfo.ulFlags |= EMS_PASSFLAG_REDUNDANT;
					break;
					
				case 'P':
				default:
					break;
			}

			switch ( lpSitData->wPassProcessStatus )
			{
				case 'A':
					lpTrackInfo->PassInfo.ulFlags |= EMS_PASSFLAG_ABORT;
					break;

				case 'X':
					lpTrackInfo->PassInfo.ulFlags |= EMS_PASSFLAG_ERROR;
					break;

				case '.':
				case 'P':
				default:
					break;
			}

			lpTrackInfo->dWeight = 0.0;	// default value

			lpTrackInfo->PassInfo.timePeak = _DeterminePeakTime( lpSitData->ulSatID,
						timePassStart, timePassStop );

			lpTrackInfo->PassInfo.degMinElevation = _GetMinElevation( lpSitData->ulSatID,
						timePassStart, timePassStop );

			if ( fabs( lpTrackInfo->PassInfo.degAzimuthAOS ) < 0.001 )
			{
				lpTrackInfo->PassInfo.degAzimuthAOS = 
					_GetAzimuth( lpSitData->ulSatID, lpTrackInfo->PassInfo.timeAOS );
			}

			if ( fabs( lpTrackInfo->PassInfo.degAzimuthLOS ) < 0.001 )
			{
				lpTrackInfo->PassInfo.degAzimuthLOS = 
					_GetAzimuth( lpSitData->ulSatID, lpTrackInfo->PassInfo.timeLOS );
			}
		}
	}
}

EMS_RESULT 
CEMSPassSchedule::ValidateSchedule( ULONG				ulLutID, 
									LONG				lSatelliteCount, 
									EMSSATELLITETRACK	**apPasses )
{
	EMS_RESULT	hr = EMS_OK;
	ULONG		ulLUTPassID = 0;
	int			nProcessCount = 0;

	BOOL		bLogOrbitNumberMismatch = FALSE;
	BOOL		bLogTimeTolerance = FALSE;
	BOOL		bLogOutOfDate = FALSE;

	std::map<ULONG,int>	mapSatRejectCount;

	try
	{
		for( int i = 0; i < lSatelliteCount; i++ )
		{
			EMSPASSVALIDATION	ePassValid = PASS_VALID;
			if( ( apPasses[i] ) && ( apPasses[i]->ulLutID == ulLutID ) )
			{
				if( 0 != (apPasses[i]->PassInfo.ulFlags & EMS_PASSFLAG_SUPPRESS) )
				{
					// Use MCC orbit number for suppressed pass
					ulLUTPassID = apPasses[i]->PassInfo.ulOrbitNumber;
				}
				else
				{
					// validate pass
					hr = _ValidatePass(	ePassValid,
										apPasses[i]->PassInfo.ulSatelliteID,
										&ulLUTPassID,
										apPasses[i]->PassInfo.timeAOS,
										apPasses[i]->PassInfo.timeLOS,
										ulLutID );

					if ( EMS_OK == hr )
					{
						switch ( ePassValid )
						{
							case PASS_VALID:
							{
								nProcessCount++;

								// Check if the orbit number from LUT matches the one from MCC,
								// if not, use the LUT orbit number and log the info for now.
								//
								// Note that according to the Network Interface Spec the
								// pass is not validated by Orbit Number but by time
								//
								if( ( ulLUTPassID != apPasses[i]->PassInfo.ulOrbitNumber ) && ( ulLUTPassID > 0 ) )
								{
									if( 0 != apPasses[i]->PassInfo.ulOrbitNumber )
									{
										bLogOrbitNumberMismatch = TRUE;
									}

									/*
									NOTE:	Previously this code was not reached so am afraid 
											to do anything more than validation.
									apPasses[i]->PassInfo.ulOrbitNumber = ulLUTPassID;
									*/
								}
								break;
							}
							case PASS_INVALIDTIMETOLERANCE:
							{
								// Track which satellite so that we can determine 
								// whether our orbit data is out of wonk
								std::map<ULONG,int>::iterator itFind = mapSatRejectCount.find( apPasses[i]->PassInfo.ulSatelliteID );
								if ( itFind == mapSatRejectCount.end() )
								{
									mapSatRejectCount.insert( std::pair<ULONG, int>( apPasses[i]->PassInfo.ulSatelliteID, 1 ) );
								}
								else
								{
									itFind->second = itFind->second + 1;
								}

								// Log a message indicating mismatch
								bLogTimeTolerance = TRUE;
								break;
							}
							case PASS_INVALIDPAST:
							{
								bLogOutOfDate = TRUE;
								break;
							}
							default:
								assert( false );
						}
					}
					else
					{
						// log the error and keep on going
						CEMSLogMsgParam	param;
						param.AddX( hr );
						CEMSLogHelper::LogInfoMsg( EMS_MAST_PASS_ERROR_DURING_VALIDATION, param );

						hr = EMS_OK;
					}
				}
			}

			if ( PASS_VALID != ePassValid )
			{
				/*
				NOTE:	Previously this code was not reached so am afraid 
						to do anything more than validation.
						Also not sure that a validation method should be 
						changing data!
				apPasses[i]->PassInfo.ulFlags &= ~EMS_PASSFLAG_STATUS_MASK;
				apPasses[i]->PassInfo.ulFlags = EMS_PASSFLAG_LUT | EMS_PASSFLAG_SUPPRESS;
				*/
			}	
		}

		if ( bLogOrbitNumberMismatch )
		{
			CEMSLogHelper::LogInfoMsg( EMS_ORBIT_NUMBER_NOT_MATCH );
		}
		if ( bLogTimeTolerance )
		{
			CEMSLogHelper::LogInfoMsg( EMS_MAST_PASS_OUTSIDE_TOLERANCE );
		}
		if ( bLogOutOfDate )
		{
			CEMSLogHelper::LogInfoMsg( EMS_MAST_PASS_TOO_OLD );
		}


		// Did we find more than 2 passes out of tolerance for any given satellite?
		// If so, log a message indicating that there may be a problem with the orbit data
		std::map<ULONG,int>::iterator itFind = mapSatRejectCount.begin();
		for ( ; itFind != mapSatRejectCount.end( ) ; itFind++ )
		{
			if ( itFind->second > 2 )
			{
				CEMSLogMsgParam	param;
				param.Add( itFind->first );		// sat ID
				param.Add( itFind->second );	// rejection count
				CEMSLogHelper::LogInfoMsg( EMS_MAST_PASS_SCHED_ORBIT_VECTOR_SUSPECT, param );
			}
		}

		//
		// Return that the schedule is invalid if there are no passes to be processed
		//
		if ( SUCCEEDED(hr) && 0 == nProcessCount )
		{
			// Fail
			// Note assume that error codes are logged externally
			hr = EMS_MAST_PASS_SCHED_NO_VALID_PASSES;
		}
	}
	catch( CEMSException& excpt )
	{
		hr = excpt.GetErrCode();
	}
	catch( EMS_RESULT hrExcpt )
	{
		hr = hrExcpt;
	}
	catch( ... )
	{
		hr = EMS_EXCEPTION;
	}
	return  hr;
}

EMS_RESULT 
CEMSPassSchedule::ValidateSchedule( CEMSSit260A	*lpSitMsg )
{
	EMS_RESULT	hr = EMS_OK;

	int			nProcessCount = 0;
	int			nSuppressedByLUT = 0;

	BOOL		bLogOrbitNumberMismatch = FALSE;
	BOOL		bLogTimeTolerance = FALSE;
	BOOL		bLogOutOfDate = FALSE;

	ULONG		ulLUTPassID = 0;

	std::map<ULONG,int>	mapSatRejectCount;

	try
	{
		if ( lpSitMsg )
		{
			int nCount = lpSitMsg->GetSatelliteCount();

			for ( int i = 0; i < nCount; i++ )
			{
				LPEMSSIT260DATA lpPassData = lpSitMsg->GetPass( i );

				if ( ( lpPassData ) && ( lpPassData->ulLutID == m_ulLutID ) )
				{
					EMSPASSVALIDATION	eValid = PASS_VALID;

					switch ( lpPassData->wPassSchedStatus )
					{
						case 'X':	// suppressed passes are by defn valid
							
							ulLUTPassID = lpPassData->ulOrbitNumber;//Use MCC orbit number for suppressed pass 
							break;

						default:
						{
							hr = _ValidatePass( eValid,
												lpPassData->ulSatID,
												&ulLUTPassID,
												lpPassData->timeAOS, 
												lpPassData->timeLOS );
							if ( EMS_OK == hr )
							{
								switch( eValid )
								{
									case PASS_VALID:
									{
										nProcessCount++;

										// Check if the orbit number from LUT matches the one from MCC,
										// if not, use the LUT orbit number and log the info for now.
										//
										// Note that according to the Network Interface Spec the
										// pass is not validated by Orbit Number but by time
										//
										if ( ( ulLUTPassID != lpPassData->ulOrbitNumber ) && ( ulLUTPassID > 0 ) )
										{
											// Log an info message but only if an orbit number was given
											if ( lpPassData->ulOrbitNumber )
											{
												bLogOrbitNumberMismatch = TRUE;
											}
											lpPassData->ulOrbitNumber = ulLUTPassID;
										}
										break;
									}

									case PASS_INVALIDTIMETOLERANCE:
									{
										// Track which satellite so that we can determine 
										// whether our orbit data is out of wonk
										std::map<ULONG,int>::iterator itFind = mapSatRejectCount.find( lpPassData->ulSatID );
										if ( itFind == mapSatRejectCount.end() )
										{
											mapSatRejectCount.insert( std::pair<ULONG, int>( lpPassData->ulSatID, 1 ) );
										}
										else
										{
											itFind->second = itFind->second + 1;
										}

										// Log a message indicating mismatch
										bLogTimeTolerance = TRUE;
										break;
									}
									case PASS_INVALIDPAST:
									{
										bLogOutOfDate = TRUE;
										break;
									}
									default:
										assert( false );
								}// end switch eValid
							}
							else
							{
								// log the error and keep on going
								CEMSLogMsgParam	param;
								param.AddX( hr );
								CEMSLogHelper::LogInfoMsg( EMS_MAST_PASS_ERROR_DURING_VALIDATION, param );
							}
						}

					}

					if ( PASS_VALID != eValid || EMS_OK != hr )
					{
						lpPassData->wPassSchedOrigin = 'L';		// suppressed by LUT
						lpPassData->wPassSchedStatus = 'X';		// suppress
					}	
				}
			}

			// Log messages about pass suppressions
			if ( bLogOrbitNumberMismatch )
			{
				CEMSLogHelper::LogInfoMsg( EMS_ORBIT_NUMBER_NOT_MATCH );
			}
			if ( bLogTimeTolerance )
			{
				CEMSLogHelper::LogInfoMsg( EMS_MAST_PASS_OUTSIDE_TOLERANCE );
			}
			if ( bLogOutOfDate )
			{
				CEMSLogHelper::LogInfoMsg( EMS_MAST_PASS_TOO_OLD );
			}

			// Did we find more than 2 passes out of tolerance for any given satellite?
			// If so, log an info message indicating that there may be a problem with the orbit data
			std::map<ULONG,int>::iterator itFind = mapSatRejectCount.begin();
			for ( ; itFind != mapSatRejectCount.end( ) ; itFind++ )
			{
				if ( itFind->second > 2 )
				{
					CEMSLogMsgParam	param;
					param.Add( itFind->first );		// sat ID
					param.Add( itFind->second );	// rejection count
					CEMSLogHelper::LogInfoMsg( EMS_MAST_PASS_SCHED_ORBIT_VECTOR_SUSPECT, param );
				}
			}
		}

		//
		// Return that the schedule is invalid if there are no passes to be processed
		//
		if ( SUCCEEDED(hr) && 0 == nProcessCount )
		{
			// Return a failure status code
			// Note assume that error codes are logged externally
			hr = EMS_MAST_PASS_SCHED_NO_VALID_PASSES;
		}
	}
	catch( CEMSException& excpt )
	{
		hr = excpt.GetErrCode();
	}
	catch( EMS_RESULT hrExcpt )
	{
		hr = hrExcpt;
	}
	catch( ... )
	{
		hr = EMS_EXCEPTION;
	}
	return  hr;
}

EMS_RESULT CEMSPassSchedule::_RemoveExpiredEntries( void )
{
	EMS_RESULT hr = EMS_OK;
	EMSTIME timeNow = c_sysClock.GetTime();

	for ( ULONG i = 0; i < m_sched.ulCount; i++ )
	{
		if ( m_sched.track[i].PassInfo.timeLOS.intTime  < timeNow.intTime )
		{
			hr = _DeleteEntry( i );
		}
	}

	return hr;
}

EMS_RESULT CEMSPassSchedule::_DeleteEntry( int nIndex )
{
	EMS_RESULT hr = EMS_OK;

	if ( m_sched.ulCount && ( nIndex >= 0 ) && ( nIndex < (int)m_sched.ulCount ) )
	{
		for ( ULONG i = nIndex; i < m_sched.ulCount-1; i++ )
		{
			m_sched.track[ i ] = m_sched.track[ i + 1 ];
			m_sched.wState[ i ] = m_sched.wState[ i + 1 ];
			m_sched.timePrePass[ i ] = m_sched.timePrePass[ i + 1 ];
		}
		m_sched.ulCount--;
	}
	return hr;
}

EMS_RESULT 
CEMSPassSchedule::InstallScheduleFromSitMsg( CEMSSit260A *lpSitMsg )
{
	EMS_RESULT	hr = EMS_OK;
	BOOL		bLocked = FALSE;
	BOOL		bInstall = TRUE;

	try
	{
		if ( lpSitMsg )
		{
			if ( LockSchedule( TRUE ) )
			{
				bLocked = TRUE;
				int nCount = lpSitMsg->GetSatelliteCount();

				switch ( lpSitMsg->GetScheduleUsage() )
				{
					default:
					case EMSSchedUsageInfo:
					case EMSSchedUsageUnknown:	
					case EMSSchedUsageValidate:	// nothing to do
						nCount = 0;
						break;

					case EMSSchedUsageInstall:	// replaces existing
						memset( &m_sched, 0, sizeof( m_sched ) );
						break;

					case EMSSchedUsageAppend:
						_RemoveExpiredEntries( );
						break;
				}

				if ( nCount )
				{
					hr = ValidateSchedule( lpSitMsg );
				}

				// Only install schedule if asked to AND valid 
				if ( nCount && SUCCEEDED( hr ) )
				{
					for ( int i = 0; SUCCEEDED(hr) && i < nCount; i++ )
					{
						LPEMSSIT260DATA lpPassData = lpSitMsg->GetPass( i );

						if ( ( lpPassData ) && ( lpPassData->ulLutID == m_ulLutID ) )
						{
							EMSSATELLITETRACK trackInfo;

							_SetTrackInfo( &trackInfo, lpPassData );

							hr = _AddTrackToSchedule( &trackInfo );
						}
					}
					if ( SUCCEEDED(hr) )
					{
						m_sched.timeCreated =  c_sysClock.GetTime();

						hr = _InstallPassSchedule( TRUE );
					}
				}
				bLocked = FALSE;
				UnlockSchedule();
			}
		}
		else
		{
			hr = EMS_BAD_PARAM;
		}
	}
	catch( ... )
	{
		if ( bLocked )
		{
			UnlockSchedule();
		}
		throw;
	}
	return hr;
}

EMS_RESULT 
CEMSPassSchedule::InstallSchedule( ULONG ulLutID, EMSSCHEDUSAGE eUsage, 
								LONG lSatelliteCount, EMSSATELLITETRACK **apPasses )
{
	EMS_RESULT	hr = EMS_OK;
	BOOL		bLocked = FALSE;
	BOOL		bInstall = TRUE;

	try
	{
		if ( apPasses && (lSatelliteCount > 0)  )
		{
			if ( LockSchedule( TRUE ) )
			{
				bLocked = TRUE;
				int nCount = lSatelliteCount;

				switch ( eUsage )
				{
					default:
					case EMSSchedUsageInfo:
					case EMSSchedUsageUnknown:	
					case EMSSchedUsageValidate:	// nothing to do
						nCount = 0;
						break;

					case EMSSchedUsageInstall:	// replaces existing
						memset( &m_sched, 0, sizeof( m_sched ) );
						break;

					case EMSSchedUsageAppend:
						_RemoveExpiredEntries( );
						break;
				}

				if ( nCount )
				{
					hr = ValidateSchedule( ulLutID, nCount, apPasses );																
				}

				// Only install schedule if asked to AND valid 
				if ( nCount && bInstall && SUCCEEDED( hr ) )
				{
					for ( int i = 0; SUCCEEDED(hr) && i < nCount; i++ )
					{
						if ( apPasses[i] && (apPasses[i]->ulLutID == m_ulLutID) )
						{
							hr = _AddTrackToSchedule( apPasses[i] );
						}
					}

					if ( SUCCEEDED(hr) )
					{
						m_sched.timeCreated =  c_sysClock.GetTime();

						hr = _InstallPassSchedule( TRUE );
					}
				}
				bLocked = FALSE;
				UnlockSchedule();
			}
		}
		else
		{
			hr = EMS_BAD_PARAM;
		}
	}
	catch( ... )
	{
		if ( bLocked )
		{
			UnlockSchedule();
		}
		throw;
	}

	return hr;
}

EMS_RESULT CEMSPassSchedule::InstallScheduleFromFile( void )
{
	EMS_RESULT	hr = EMS_OK;
	BOOL		bLocked = FALSE;

	if ( LockSchedule( TRUE ) )
	{
		try
		{
			bLocked = TRUE;

			hr = _LoadScheduleFromFile();

			if ( hr == EMS_OK )
			{
				hr = _InstallPassSchedule( FALSE );
			}

			bLocked = FALSE;
			UnlockSchedule();
		}
		catch( ... )
		{
			if ( bLocked )
			{
				UnlockSchedule();
			}
			throw;
		}
	}
	return hr;
}

EMS_RESULT CEMSPassSchedule::_LoadScheduleFromFile( void )
{
	EMS_RESULT hr = EMS_OK;
	FILE *lpDatFile = 0;
	size_t nResult = 0;

	memset( &m_sched, 0, sizeof( m_sched ) );

	hr = _OpenFileWhenNotBusy( &lpDatFile, c_szPassSchedDatFile, "rb" );

	if ( ( hr == EMS_OK ) && lpDatFile )
	{
		try
		{
			_ReadFile( &m_sched.ulCount, sizeof(m_sched.ulCount), 1, lpDatFile );

			_ReadFile( &m_sched.ulIndex, sizeof(m_sched.ulIndex), 1, lpDatFile );

			_ReadFile( &m_sched.timeCreated, sizeof(m_sched.timeCreated), 1, lpDatFile );

			_ReadFile( &m_sched.timeInstalled, sizeof(m_sched.timeInstalled), 1, lpDatFile );

			_ReadFile( &m_sched.timeRenew, sizeof(m_sched.timeRenew), 1, lpDatFile );

			_ReadFile( &m_sched.timeOldest, sizeof(m_sched.timeOldest), 1, lpDatFile );

			_ReadFile( m_sched.wState, sizeof(m_sched.wState[0]), 
													m_sched.ulCount, lpDatFile );

			_ReadFile( m_sched.timePrePass, sizeof(m_sched.timePrePass[0]), 
													m_sched.ulCount, lpDatFile );

			_ReadFile( m_sched.track, sizeof(m_sched.track[0]), 
													m_sched.ulCount, lpDatFile );

			// Verify that the count is greater than 0.
			if( 1 > m_sched.ulCount )
			{
				// Essentially the same as the file not being present.
				memset( &m_sched, 0, sizeof( m_sched ) );
				hr = EMS_EMPTY;

			}
		}
		catch ( EMS_RESULT rc )
		{
			hr = rc;
		}
		catch( ... )
		{
			hr = EMS_EXCEPTION;
		}

		fclose( lpDatFile );
	}

	return hr;
}

EMS_RESULT CEMSPassSchedule::_SaveScheduleToFile( void )
{
	EMS_RESULT hr = EMS_OK;
	FILE *lpDatFile = 0;
	size_t nResult = 0;

	hr = _OpenFileWhenNotBusy( &lpDatFile, c_szPassSchedDatFile, "wb" );

	if ( ( hr == EMS_OK ) && lpDatFile )
	{
		try
		{
			_WriteFile( &m_sched.ulCount, sizeof(m_sched.ulCount), 1, lpDatFile );

			_WriteFile( &m_sched.ulIndex, sizeof(m_sched.ulIndex), 1, lpDatFile );

			_WriteFile( &m_sched.timeCreated, sizeof(m_sched.timeCreated), 1, lpDatFile );

			_WriteFile( &m_sched.timeInstalled, sizeof(m_sched.timeInstalled), 1, lpDatFile );

			_WriteFile( &m_sched.timeRenew, sizeof(m_sched.timeRenew), 1, lpDatFile );

			_WriteFile( &m_sched.timeOldest, sizeof(m_sched.timeOldest), 1, lpDatFile );

			_WriteFile( m_sched.wState, sizeof(m_sched.wState[0]), 
												m_sched.ulCount, lpDatFile );

			_WriteFile( m_sched.timePrePass, sizeof(m_sched.timePrePass[0]), 
												m_sched.ulCount, lpDatFile );

			_WriteFile( m_sched.track, sizeof(m_sched.track[0]), 
												m_sched.ulCount, lpDatFile );
		}

		catch ( EMS_RESULT r )
		{
			hr = r;
		}
		catch( ... )
		{
			hr = EMS_EXCEPTION;
		}

		fclose( lpDatFile );
	}

	return hr;
}

EMS_RESULT CEMSPassSchedule::_WriteScheduleToTextFile( void )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR szMsg[256], szTemp[256], szFlags[8];
	CEMSTime timeSched;
	EMSTIMEFIELDS timeFields;	
	FILE *lpTxtFile = 0;

	hr = _OpenFileWhenNotBusy( &lpTxtFile, c_szPassSchedTxtFile, "wt" );

	if ( ( hr == EMS_OK ) && lpTxtFile )
	{
		try
		{
			// print generated time and installed time

			timeSched.SetTime( m_sched.timeCreated );

			timeSched.GetTime( &timeFields );

			_ftprintf( lpTxtFile, TEXT("Pass Schedule:") );

			_ftprintf( lpTxtFile, TEXT(" Created-%04d %03d %02d:%02d"),
											timeFields.nYear, timeFields.nJulianDay, 
											timeFields.nHour,	timeFields.nMinute );

			timeSched.SetTime( m_sched.timeInstalled );

			timeSched.GetTime( &timeFields );

			_ftprintf( lpTxtFile, TEXT(" Installed-%04d %03d %02d:%02d"),
											timeFields.nYear, timeFields.nJulianDay, 
											timeFields.nHour,	timeFields.nMinute );

			timeSched.SetTime( m_sched.timeRenew );

			timeSched.GetTime( &timeFields );

			_ftprintf( lpTxtFile, TEXT(" Renew-%04d %03d %02d:%02d"),
									timeFields.nYear, timeFields.nJulianDay, 
									timeFields.nHour,	timeFields.nMinute );

			_ftprintf( lpTxtFile, TEXT("\n\n") );

			for ( int i = 0; i < (int)m_sched.ulCount; i++ )
			{
				CEMSTime timeStart, timeStop;

				timeStart.SetTime( m_sched.track[i].PassInfo.timeAOS );

				timeStop.SetTime( m_sched.track[i].PassInfo.timeLOS );

				timeStart.GetTime( &timeFields );

				switch ( m_sched.track[i].PassInfo.ulFlags & EMS_PASSFLAG_ORIGIN_MASK )	// origin
				{
					default:								szFlags[0] = '.'; break;
					case EMS_PASSFLAG_LUT:			szFlags[0] = 'L'; break;
					case EMS_PASSFLAG_MCC:			szFlags[0] = 'M'; break;
					case EMS_PASSFLAG_RCC:			szFlags[0] = 'R'; break;
					case EMS_PASSFLAG_OPERATOR:	szFlags[0] = 'O'; break;
				}

				switch ( m_sched.track[i].PassInfo.ulFlags & EMS_PASSFLAG_STATUS_MASK )
				{
					default:								szFlags[1] = 'P'; break;
					case EMS_PASSFLAG_SUPPRESS: 	szFlags[1] = 'X'; break;
					case EMS_PASSFLAG_PROCESS:		szFlags[1] = 'F'; break;
					case EMS_PASSFLAG_REDUNDANT:	szFlags[1] = 'R'; break;
				}

				switch ( m_sched.track[i].PassInfo.ulFlags & EMS_PASSFLAG_RESULT_MASK )
				{
					default:								szFlags[2] = '.'; break;
					case EMS_PASSFLAG_SUCCESS:		szFlags[2] = 'S'; break;
					case EMS_PASSFLAG_ABORT:		szFlags[2] = 'A'; break;
					case EMS_PASSFLAG_ERROR:		szFlags[2] = 'X'; break;
				}

				szFlags[3] = 0;

				_stprintf( szMsg, TEXT("Pass (%3d) SatID (%3ld) Orbit(%6ld) Flags(%s) Start( %02d:%02d:%02d )"), 
						i, m_sched.track[i].PassInfo.ulSatelliteID, 
						m_sched.track[i].PassInfo.ulOrbitNumber, szFlags,
						timeFields.nHour,	timeFields.nMinute, timeFields.nSecond );

				timeStop.GetTime( &timeFields );

				_stprintf( szTemp, " Stop( %02d:%02d:%02d )", 
						timeFields.nHour,	timeFields.nMinute, timeFields.nSecond );

				lstrcat( szMsg, szTemp );

				_ftprintf( lpTxtFile, "%s\n", szMsg );
			}
		}
		catch( ... )
		{
			hr = EMS_EXCEPTION;
		}
		fclose( lpTxtFile );
		lpTxtFile = 0;
	}

	return hr;
}

EMS_RESULT CEMSPassSchedule::_ValidatePass( 
	BOOL&				bValid,
	ULONG				ulSatID, 
	ULONG*				lpPassID, 
	CEMSTime			timeAOS, 
	CEMSTime			timeLOS, 
	EMSSATELLITEPASS*	lpPassInfo, 
	ULONG				ulCount )
{
	EMS_RESULT hr = EMS_OK;
	bValid = FALSE;

	if ( lpPassInfo && ulCount )
	{	
		for ( ULONG i = 0; !bValid && i < ulCount; i++ )
		{
			if ( lpPassInfo[i].ulSatelliteID == ulSatID )
			{	
				if ( ( fabs( timeAOS.MinutesDifferent( lpPassInfo[i].timeAOS ) )
					<= m_schedSettings.dScheduleTolerance ) && 
					( fabs( timeLOS.MinutesDifferent( lpPassInfo[i].timeLOS ) )
					<= m_schedSettings.dScheduleTolerance ) )
				{
					*lpPassID = lpPassInfo[i].ulOrbitNumber;
					bValid = TRUE;
				}
			}
		}
	}

	return hr;
}

EMS_RESULT CEMSPassSchedule::_ValidatePass(
	BOOL&		bValid,
	ULONG		ulSatID,
	ULONG*		lpPassID, 
	EMSTIME		timeAOS,
	EMSTIME		timeLOS,
	ULONG		ulLutID )
{
	EMS_RESULT			hr = EMS_OK;
	IEMSPassSchedule *	lpPassSched = 0;

	bValid = FALSE;

	try
	{
		if ( m_lpTrackSched )
		{
			hr = m_lpTrackSched->QueryInterface( IID_IEMSPassSchedule, (LPVOID*)&lpPassSched );

			if ( ( hr == EMS_OK ) && lpPassSched )
			{
				CEMSTime timeStart( timeAOS ) , timeStop( timeLOS ); 

				hr = lpPassSched->SetSatellites( 1, &ulSatID );			

				if ( EMS_OK == hr )
				{
					hr = lpPassSched->SetPrimaryLut( 0 == ulLutID ? m_ulLutID : ulLutID );
				}

				if ( EMS_OK == hr )
				{
					timeStart.AddMinutes( (float)-m_schedSettings.dScheduleTolerance );

					timeStop.AddMinutes( (float)m_schedSettings.dScheduleTolerance );
        
					hr = lpPassSched->GenerateSchedule( timeStart, timeStop );
				}

				if ( hr == EMS_OK )
				{
					ULONG ulCount = 0;
					EMSTIME timeF, timeL;
					EMSSATELLITEPASS passData[ c_ulMaxValidPasses ];

					hr = lpPassSched->GetSchedule( c_ulMaxValidPasses, passData,
										&ulCount, &timeF, &timeL );

					if ( hr == EMS_OK )
					{
						hr = _ValidatePass( 
									bValid,
									ulSatID,
									lpPassID, 
									timeAOS, 
									timeLOS, 
									passData, 
									ulCount );
					}
					else if ( EMS_PASS_NO_DATA == hr )
					{
						bValid = FALSE;
						hr = EMS_OK;
					}
				}
        
				lpPassSched->Release();
				lpPassSched = 0;
			}
		}
		else
		{
			hr = EMS_INVALID_PTR;
		}
	}
	catch( ... )
	{
		if ( lpPassSched )
		{
			lpPassSched->Release();
			lpPassSched = 0;
		}
	}
	return hr;
}

EMS_RESULT CEMSPassSchedule::GeneratePassSchedule( EMSTIME timeStart )
{
	EMS_RESULT hr = EMS_FALSE;

	if ( m_lpTrackSched )
	{
		EMSTIMEFIELDS timeFields;
		CEMSTime startTime, stopTime;

		if ( timeStart.intTime == 0 )
			startTime.SetTime( c_sysClock.GetTime() );
		else
			startTime.SetTime( timeStart );

		if ( m_bFirstTimeAfterStartup )
		{
			startTime.AddMinutes( -c_fMinutesBeforeSchedule );

			m_bFirstTimeAfterStartup = FALSE;
		}

		startTime.GetTime( &timeFields );

		stopTime.SetTime( startTime );

		stopTime.AddHours( (float)m_schedSettings.dDuration );

		hr = m_lpTrackSched->SetLuts( 1, &m_ulLutID );	

		hr = m_lpTrackSched->SetSatellites( m_ulSatCount, m_ulSatellites );

		hr = m_lpTrackSched->GenerateSchedule( startTime, stopTime );

		m_bNewScheduleGenerated = ( hr == EMS_OK );
	}
	else
		hr = EMS_INVALID_PTR;

	return hr;
}

EMS_RESULT CEMSPassSchedule::_CalcPrePassTimes( void )
{
	EMS_RESULT hr = EMS_OK;
	CEMSTime timeTemp;
	
	for ( ULONG i = 0; i < m_sched.ulCount; i++ )
	{
		timeTemp.SetTime( m_sched.track[i].PassInfo.timeAOS );

//		timeTemp.AddSeconds( -c_nPrePassSeconds );

		timeTemp.AddSeconds( -(float)m_dPrePassDuration );

		m_sched.timePrePass[i] = timeTemp;
	}

	return hr;
}

EMS_RESULT CEMSPassSchedule::_DetermineOldestScheduleTime( EMSTIME *lpTimeOldest )
{
	EMSTIME timeOldest = CEMSTime(0);

	for ( ULONG i = 0; i < m_sched.ulCount; i++ )
	{
		if ( m_sched.track[i].PassInfo.timeLOS.intTime  > timeOldest.intTime )
			timeOldest = m_sched.track[i].PassInfo.timeLOS;
	}

	if ( lpTimeOldest )
		*lpTimeOldest = timeOldest;

	return ( timeOldest.intTime == 0 ) ? EMS_FALSE : EMS_OK;
}

EMS_RESULT 
CEMSPassSchedule::_DetermineRenewScheduleTime( EMSTIME *lpTimeRenew )
{
	assert( lpTimeRenew );
	if ( !lpTimeRenew ) return EMS_BAD_PARAM;

	CEMSTime		timeRenew( c_sysClock.GetTime() );
	EMSTIMEFIELDS	timeFields;

	// FYI: In Oct 2005 the default frequency was 24hours
	timeRenew.AddHours( (float)m_schedSettings.dFrequency );

	// Base the renewal time on the LOS of the last pass 
	// flagged for processing within the renewal period 
	int		iRenewAfter = -1;
	for ( int i = 0; i < m_sched.ulCount; i++ )
	{
		if ( EMS_PASSFLAG_PROCESS == (m_sched.track[i].PassInfo.ulFlags & EMS_PASSFLAG_STATUS_MASK) )
		{
			if ( m_sched.track[i].PassInfo.timeAOS.intTime  > timeRenew.GetTimeNano() )
			{
				break;
			}
			else
			{
				iRenewAfter = i;
			}
		}
	}

	// Did we identify a pass that we should renew after?
	if ( iRenewAfter >= 0 )
	{
		timeRenew.SetTime( m_sched.track[iRenewAfter].PassInfo.timeLOS );
		timeRenew.AddSeconds( 60.0f );
	}
	else
	{
		// There are NO passes within the renewal period
		// that are flagged for processing.  
		// Indicate that the schedule should be renewed right away
		timeRenew.SetTime( c_sysClock.GetTime() );
	}

	timeRenew.GetTime( &timeFields );

	*lpTimeRenew = timeRenew;

	return EMS_OK;
}

static unsigned __stdcall _GetScheduleThreadRoutine( void *pThis )
{
	if ( pThis )
	{
		EMS_RESULT hr = EMS_OK;
		CEMSTime timeStart( c_sysClock.GetTime( ) );

		hr = ((CEMSPassSchedule *)pThis)->GeneratePassSchedule( timeStart );

		((CEMSPassSchedule *)pThis)->_ResetThreadHandle( );
	}

	_endthreadex(0);

	return 0;
}

EMS_RESULT CEMSPassSchedule::InstallGeneratedSchedule( void )
{
	EMS_RESULT	hr = EMS_OK;
	BOOL		bLocked = FALSE;

	try
	{
		if ( m_lpTrackSched )
		{	
			if ( LockSchedule( TRUE ) )
			{
				bLocked = TRUE;

				EMSTIME startTime, stopTime;

				memset( &m_sched, 0, sizeof( m_sched ) );

				hr = m_lpTrackSched->GetOptSchedule( EMS_MAX_NUM_OPT_SAT_PASSES,
						m_ulLutID, m_sched.track, &m_sched.ulCount, &startTime, &stopTime );

				if ( hr == EMS_OK )
				{
					m_sched.timeCreated = c_sysClock.GetTime();

					for ( int i = 0; i < (int)m_sched.ulCount; i++ )
					{
						m_sched.track[i].PassInfo.timeAOS.intTime += (INT64)i;
					}

					hr = _InstallPassSchedule( TRUE );
				}
				bLocked = FALSE;
				UnlockSchedule();
			}
		}
	}
	catch( ... )
	{
		if ( bLocked )
		{
			UnlockSchedule();
		}
		throw;
	}

	return hr;
}

EMS_RESULT CEMSPassSchedule::GenerateNewPassScheduleInBackground( void )
{
	if ( m_hThread == INVALID_HANDLE_VALUE )
	{
		m_hThread = (HANDLE)_beginthreadex( NULL, c_unStackSize, 
								&_GetScheduleThreadRoutine, this, 
								0, &m_unThreadID );
	}

	return ( m_hThread != INVALID_HANDLE_VALUE ) ? EMS_OK : EMS_FALSE; 
}

EMS_RESULT CEMSPassSchedule::_InstallPassSchedule( BOOL bSaveToDisk )
{
	EMS_RESULT hr = EMS_OK;
	EMSTIME timeOldest, timeLast;

	m_sched.ulIndex = 0;

	m_sched.timeInstalled = c_sysClock.GetTime();

	timeLast.intTime = 0;	

	for ( int i = 0; i < (int)m_sched.ulCount; i++ )
	{
		CEMSTime timeStart, timeStop;

		// Database keys are not unique enough 
		// so add a nanosecond if there is a conflict

		if ( timeLast.intTime == m_sched.track[i].PassInfo.timeAOS.intTime )
		{
			timeLast.intTime = ++m_sched.track[i].PassInfo.timeAOS.intTime;
		}

		m_sched.wState[i] = 0;

		if ( !_IsTruncatedAllowed() && IsPassTruncated( i ) )
		{
			if ( ( m_sched.track[i].PassInfo.ulFlags & EMS_PASSFLAG_SUPPRESS )
				!= EMS_PASSFLAG_SUPPRESS )
			{
				m_sched.track[i].PassInfo.ulFlags &= ~EMS_PASSFLAG_STATUS_MASK;

				m_sched.track[i].PassInfo.ulFlags |= EMS_PASSFLAG_SUPPRESS;

				m_sched.track[i].PassInfo.ulFlags &= ~EMS_PASSFLAG_ORIGIN_MASK;

				m_sched.track[i].PassInfo.ulFlags |= EMS_PASSFLAG_LUT;
			}
		}

		if ( ( m_sched.track[i].PassInfo.ulFlags & EMS_PASSFLAG_SKIP ) ||
			( m_sched.track[i].ulLutID != m_ulLutID ) ||
			( m_sched.track[i].PassInfo.ulFlags & EMS_PASSFLAG_ERROR ) ||
			( m_sched.track[i].PassInfo.ulFlags & EMS_PASSFLAG_ABORT ) )
//		( ( ( m_sched.track[i].PassInfo.ulFlags & EMS_PASSFLAG_PROCESS ) == 0 ) &&
//			( ( m_sched.track[i].PassInfo.ulFlags & EMS_PASSFLAG_REDUNDANT ) == 0 ) ) )
			m_sched.wState[i] = EMS_PS_FLAG_IGNORE;
	}

	_CalcPrePassTimes();

	hr = _DetermineRenewScheduleTime( &timeOldest );
	if ( hr == EMS_OK )
		m_sched.timeRenew = timeOldest;
	// else keep current and proceed 

	hr = _DetermineOldestScheduleTime( &timeOldest );
	if ( hr == EMS_OK )
		m_sched.timeOldest = timeOldest;
	// else keep current and proceed 

	hr = _WriteScheduleToTextFile(); // save passsched.txt
	if ( bSaveToDisk )
	{
		hr = _SaveScheduleToFile();	// save passsched.dat
	}

	m_bNewScheduleInstalled = TRUE;

	return hr;
}

EMS_RESULT CEMSPassSchedule::_WaitForThreadsToComplete( void )
{
	EMS_RESULT hr = EMS_OK;
	DWORD dwExitStatus = STILL_ACTIVE;
	BOOL bOK = TRUE;
	clock_t clkNow = clock();

	while ( bOK && ( m_hThread != INVALID_HANDLE_VALUE ) && 
		( dwExitStatus == STILL_ACTIVE) && ( clock() - clkNow < c_clkThreadExitTimeout ) )
	{
		bOK = GetExitCodeThread( m_hThread, &dwExitStatus );

		if ( bOK )
			Sleep( 10 );
	}
	return hr;
}

int CEMSPassSchedule::_FindPassIndex( ULONG ulLutID, ULONG ulSatID, EMSTIME timeAOS, ULONG ulOrbitNumber )
{
	int nIndex = -1;
	CEMSTime timeTemp;

	for ( ULONG i = 0; ( i < m_sched.ulCount ) && ( nIndex == -1 ); i++ )
	{
		if ( ( m_sched.track[i].ulLutID == ulLutID ) && 
			( m_sched.track[i].PassInfo.ulSatelliteID == ulSatID ) )
		{
			timeTemp.SetTime( m_sched.track[i].PassInfo.timeAOS );

			if ( fabs( timeTemp.MinutesDifferent( timeAOS ) ) <=
										 m_schedSettings.dScheduleTolerance )  
			{
				if ( !ulOrbitNumber || 
						( m_sched.track[i].PassInfo.ulOrbitNumber == ulOrbitNumber ) )
				{
					nIndex = (int)i;
				}
			}
		}
	}

	return nIndex;
}


EMS_RESULT CEMSPassSchedule::MarkPassToBeProcessed( ULONG ulLutID, ULONG ulSatID, EMSTIME timeAOS, ULONG ulOrbitNumber )
{
	int nIndex = _FindPassIndex( ulLutID, ulSatID, timeAOS, ulOrbitNumber );

	if ( nIndex >= 0 )
	{
		m_sched.track[ nIndex ].PassInfo.ulFlags	&= EMS_PASSFLAG_ORIGIN_MASK;

		m_sched.track[ nIndex ].PassInfo.ulFlags &= ~EMS_PASSFLAG_STATUS_MASK;	// clear it first.
		m_sched.track[ nIndex ].PassInfo.ulFlags	|= EMS_PASSFLAG_PROCESS;
	}

	return ( nIndex != -1 ) ? EMS_OK : EMS_FALSE;
}

EMS_RESULT CEMSPassSchedule::MarkPassToBeSuppressed( ULONG ulLutID, ULONG ulSatID, EMSTIME timeAOS, ULONG ulOrbitNumber )
{
	int nIndex = _FindPassIndex( ulLutID, ulSatID, timeAOS, ulOrbitNumber );

	if ( nIndex >= 0 )
	{
		m_sched.track[ nIndex ].PassInfo.ulFlags	&= EMS_PASSFLAG_ORIGIN_MASK;

		m_sched.track[ nIndex ].PassInfo.ulFlags &= ~EMS_PASSFLAG_STATUS_MASK;	// clear it first.
		m_sched.track[ nIndex ].PassInfo.ulFlags	|= EMS_PASSFLAG_SUPPRESS;
	}

	return ( nIndex != -1 ) ? EMS_OK : EMS_FALSE;
}

bool CEMSPassSchedule::IsPassConflict( EMSTIME timeStart, double dDuration, bool bIncludeSuppress )
{
	bool bConflict = false;
	CEMSTime timeAOS, timeLOS, timeStop;

	timeStop.SetTime( timeStart );

	timeStop.AddSeconds( dDuration );

	for ( ULONG i = 0; ( i < m_sched.ulCount ) && !bConflict;  i++ )
	{
 		if ( ( ( m_sched.track[i].PassInfo.ulFlags & EMS_PASSFLAG_STATUS_MASK ) != 
									EMS_PASSFLAG_SUPPRESS ) || bIncludeSuppress )
		{
			timeAOS.SetTime( GetAOSTime( i ) );

			timeLOS.SetTime( GetLOSTime( i ) );

			if ( ( ( timeAOS.SecondsDifferent( timeStart ) > 0.0 ) &&
				( timeLOS.SecondsDifferent( timeStart ) < 0.0 ) ) || 
				( ( timeAOS.SecondsDifferent( timeStop ) > 0.0 ) &&
				( timeLOS.SecondsDifferent( timeStop ) < 0.0 ) ) )
			{
				bConflict = true;
			}
		}
	}

	return bConflict;
}

ULONG CEMSPassSchedule::_GetOrbitNumber( ULONG ulSatID, EMSTIME t )
{
	ULONG ulOrbitNumber = 0;
	EMS_RESULT hr = EMS_FALSE;

	if ( m_lpOrbit && t.intTime )
	{
		hr = 	m_lpOrbit->GetOrbitNumber( ulSatID, t , &ulOrbitNumber );
	}

	return ( hr == EMS_OK ) ? ulOrbitNumber : 0;
}

EMS_RESULT CEMSPassSchedule::_GetSatelliteAZEL( ULONG ulSatID, EMSTIME timeNow, EMSLOCATION location, LPEMSAZELVECTOR lpAzElVector )
{
	EMSAZELVECTOR azelVector;
	EMS_RESULT hr = EMS_OK;

	memset( &azelVector, 0, sizeof( azelVector ) );

	if ( m_lpOrbit )
	{
		EMSTIMECOORD timeCoord;
		ULONG ulCount = 0;

		hr = m_lpOrbit->InertialOrbit( ulSatID, &timeNow, 1, &timeCoord, &ulCount);

		if ( hr == EMS_OK )
		{
			EMSVECTOR vDiff, vObserver = c_coordSys.ToInertialPosition( location, timeNow );
			EMSESUVECTOR esuVector;

			vDiff.fX = timeCoord.coord.radius.fX - vObserver.fX;
			vDiff.fY = timeCoord.coord.radius.fY - vObserver.fY;
			vDiff.fZ = timeCoord.coord.radius.fZ - vObserver.fZ;

			esuVector = c_coordSys.ToTopocentricHorizon( vDiff, location, timeNow );

			azelVector = c_coordSys.ToAzimuthAndElevation( esuVector );
		}
	}
	else
		hr = EMS_NO_ORBIT_OBJ;

	if ( lpAzElVector )
		*lpAzElVector = azelVector;

	return hr;
}

EMSTIME CEMSPassSchedule::_DeterminePeakTime( ULONG ulSatID, CEMSTime timeAOS, CEMSTime timeLOS )
{
	EMS_RESULT hr = EMS_OK;
	EMSDEGREES degMax = 0.0;
	CEMSTime timePeak( timeAOS ), timeTest( timeAOS );
	EMSAZELVECTOR azelVector;

	while ( timeTest.SecondsDifferent( timeLOS ) > 0.0 )
	{
		if (  _GetSatelliteAZEL( ulSatID, timeTest, 
				m_locationLUT, &azelVector ) == EMS_OK )
		{
			if ( azelVector.azel.degElevation > degMax )
			{
				degMax = azelVector.azel.degElevation;

				timePeak.SetTime( timeTest );
			}
		}
		timeTest.AddSeconds( 10.0 );
	}

	return timePeak;
}

EMSDEGREES CEMSPassSchedule::_GetAzimuth( ULONG ulSatID, CEMSTime timeT )
{
	EMSDEGREES degAz = 0.0;
	EMSAZELVECTOR azelVector;

	if (  _GetSatelliteAZEL( ulSatID, timeT, m_locationLUT, &azelVector ) == EMS_OK )
	{
		degAz = azelVector.azel.degAzimuth;
	}

	return degAz;
}


EMSDEGREES CEMSPassSchedule::_GetMinElevation( ULONG ulSatID, CEMSTime timeAOS, CEMSTime timeLOS )
{
	EMS_RESULT hr = EMS_OK;
	EMSDEGREES degMin = 0.0;
	EMSAZELVECTOR azelVector;

	if (  _GetSatelliteAZEL( ulSatID, timeAOS, 
				m_locationLUT, &azelVector ) == EMS_OK )
	{
		degMin = azelVector.azel.degElevation;

		if ( degMin < 0.0 )
			degMin = 0.0;
	}

	if (  _GetSatelliteAZEL( ulSatID, timeLOS, 
				m_locationLUT, &azelVector ) == EMS_OK )
	{
		if ( azelVector.azel.degElevation < 0.0 )
			azelVector.azel.degElevation = 0.0;

		if ( azelVector.azel.degElevation < degMin )
			degMin = azelVector.azel.degElevation; 
	}
	return degMin;
}


EMS_RESULT 
CEMSPassSchedule::_ValidatePass( 
	EMSPASSVALIDATION&			eValid,
	ULONG						ulSatID,
	ULONG*						lpPassID, 
	CEMSTime					timeAOS, 
	CEMSTime					timeLOS,
	ULONG						ulLutID )
{
	EMS_RESULT	hr = EMS_OK;

	CEMSTime	timeTemp( c_sysClock.GetTime() );
	
	eValid = PASS_VALID;

	// Reject passes that are in the past
	if ( timeTemp.MinutesDifferent( timeLOS ) < c_dMinMinutesBeforeLOS )
	{
		eValid = PASS_INVALIDPAST;
	}
	else
	{
		// Or are not within tolerance of the LUT predictions
		BOOL	bValid = TRUE;
		hr = _ValidatePass(	bValid,
							ulSatID,
							lpPassID,
							timeAOS, 
							timeLOS, 
							ulLutID );
		if ( EMS_OK == hr && !bValid )
		{
			eValid = PASS_INVALIDTIMETOLERANCE;
		}
	}
	return hr;
}
