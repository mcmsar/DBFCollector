#include "passsummaryformatter.h"

#include "emsit661.h"
#include "statodet.h"

CEMSPassSummaryFormatter::CEMSPassSummaryFormatter()
{
}

CEMSPassSummaryFormatter::CEMSPassSummaryFormatter( const CEMSPassSummaryFormatter& x )
{
}

CEMSPassSummaryFormatter::~CEMSPassSummaryFormatter()
{
}

EMSPASSSUMMARYINFO2 
CEMSPassSummaryFormatter::GetPassSummaryInfo( CEMSSit661A* pSit661A ) const
{
	EMSPASSSUMMARYINFO2 ret;
	memset( &ret, 0, sizeof(EMSPASSSUMMARYINFO2) );

	if( pSit661A )
	{
		EMSSATELLITETRACK track;

		memset( &track, 0, sizeof( track ) );

		track.ulLutID = pSit661A->GetReportingMCC();
		track.PassInfo.timeAOS = track.actualStartTime = pSit661A->GetAOSTime();
		track.PassInfo.timeLOS = track.actualEndTime = pSit661A->GetLOSTime();

		ret.thisTrack = track;

		memset( &track, 0, sizeof( track ) );

		track.ulLutID = pSit661A->GetReportingMCC();

//		track.PassInfo.timeAOS = track.actualStartTime = lpSit661->GetNextAOSTime();

		// stamped with the same time as the corresponding sched track record
		track.PassInfo.timeAOS = track.actualStartTime = pSit661A->GetAOSTime();

		track.PassInfo.timeLOS = track.actualEndTime = pSit661A->GetNextLOSTime();

		ret.nextTrack = track;

		ret.wSecsDuration = pSit661A->GetSecondsDuration();
		ret.wSecsCollecting = pSit661A->GetSecondsCollecting();
		ret.wPercentageCollecting = pSit661A->GetPercentageCollecting();
		ret.nPDSRecoveryRate = pSit661A->GetPDSRecoveryRate();
		ret.wFramesMissed = pSit661A->GetFramesMissed();
		ret.nTotalPDSCount = pSit661A->GetTotalPDSCount();
		ret.nDistinctPDSCount = pSit661A->GetDistinctPDSCount();
		ret.wSarrMessages = pSit661A->GetSarrMessages();
		ret.timeOrbitEpoch = pSit661A->GetOrbitEpoch();
		ret.vOrbitPosition = pSit661A->GetOrbitPosition();
		ret.vOrbitVelocity = pSit661A->GetOrbitVelocity();

		switch( pSit661A->GetOrbitUpdateStatus() )
		{
			case EMSSIT661OrbitUpdateInSpec:
				ret.wOrbitUpdateStatus = EMS_ORBUPD_Updated;
				break;
			case EMSSIT661OrbitUpdatePredict:
				ret.wOrbitUpdateStatus = EMS_ORBUPD_TooFewData;
				break;
			case EMSSIT661OrbitUpdateOutSpec:
				ret.wOrbitUpdateStatus = EMS_ORBUPD_Error;
				break;
			case EMSSIT661OrbitUpdateUnknown:
			default:
				ret.wOrbitUpdateStatus = EMS_ORBUPD_Unknown;
				break;
		}

		ret.fOrbitPositionOffset = (float)pSit661A->GetOrbitPositionOffset();
		ret.fOrbitVelocityOffset = (float)pSit661A->GetOrbitVelocityOffset();
		ret.timeCalibration = ret.timeOrbitEpoch;
		ret.timeRollover = pSit661A->GetRolloverTime();
		ret.fUSOFreq = pSit661A->GetUSOFreq();
		ret.w121Transmitters = pSit661A->Get121Transmitters();
		ret.w243Transmitters = pSit661A->Get243Transmitters();
		ret.w406Interferers = pSit661A->Get406Interferers();
		ret.w406LocatedBeacons = pSit661A->Get406LocatedBeacons();
		ret.w406UnlocatedBeacons = pSit661A->Get406UnlocatedBeacons();
		ret.wUnlocatedAlerts = pSit661A->GetUnlocatedAlerts();
		ret.wWarnings = pSit661A->GetWarningMessages();
		ret.wAlarms = pSit661A->GetAlarmMessages();

		ret.fSARR406FreqOff = (float)pSit661A->GetSarr406FreqOffset();
		ret.timeSolnProcessing = pSit661A->GetSolutionProcessingTime();
	}

	return ret;
}

EMSSATELLITETRACK	
CEMSPassSummaryFormatter::GetPassSchedule( CEMSSit661A* pSit661A ) const
{
	EMSSATELLITETRACK ret;
	memset( &ret, 0, sizeof(EMSSATELLITETRACK) );

	if( pSit661A )
	{
		ret.ulLutID = pSit661A->GetReportingMCC();

//		track.ulLutID += 1000;	// just for testing

		ret.PassInfo.ulSatelliteID = pSit661A->GetSatelliteID();

		ret.PassInfo.ulFlags = pSit661A->GetPassStatus();

		ret.PassInfo.ulOrbitNumber = pSit661A->GetOrbitNumber();

		ret.dWeight = 100;

		ret.PassInfo.degMaxElevation = 0.0;

		ret.PassInfo.degMinElevation = 0.0;

		ret.PassInfo.degAzimuthAOS = 0.0;

		ret.PassInfo.degAzimuthLOS = 0.0;

		ret.PassInfo.timeAOS = ret.actualStartTime = pSit661A->GetAOSTime();

		ret.PassInfo.timeLOS = ret.actualEndTime = pSit661A->GetLOSTime();

		ret.PassInfo.timePeak = ret.PassInfo.timeAOS;

		ret.PassInfo.timePeak.intTime += ( ret.actualEndTime.intTime - ret.actualStartTime.intTime ) / 2;
	}

	return ret;
}

int 
CEMSPassSummaryFormatter::_ConvertStatus( WORD w1, WORD w2, WORD w3 ) const
{
	int nStatus = 0;

	switch ( w1 )
	{
		default:	// fall through to 'L'
		case 'L': 	nStatus |= EMS_PASSFLAG_LUT; break;
		case 'M': 	nStatus |= EMS_PASSFLAG_MCC; break;
		case 'R': 	nStatus |= EMS_PASSFLAG_RCC; break;
		case 'O': 	nStatus |= EMS_PASSFLAG_OPERATOR; break;
	}

	switch ( w2 )
	{
		default:		
		case 'F':
		case 'P': 	nStatus |= EMS_PASSFLAG_PROCESS; break;
		case 'X': 	nStatus |= EMS_PASSFLAG_SUPPRESS; break;
		case 'R': 	nStatus |= EMS_PASSFLAG_REDUNDANT; break;
	}

	switch ( w3 )
	{
		default:		
		case '.':	break;
		case 'S': 	nStatus |= EMS_PASSFLAG_SUCCESS; break;
		case 'A': 	nStatus |= EMS_PASSFLAG_ABORT; break;
		case 'X': 	nStatus |= EMS_PASSFLAG_ERROR; break;
	}
	return nStatus;
}