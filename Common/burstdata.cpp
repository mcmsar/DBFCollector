/*********************************************************************
*	Copyright (c) 2011 by EMS Technologies, Inc.,
*					All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be
*	reproduced in whole or in part, in any form or by any means whatsoever
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
#pragma warning(disable:4786)

#include "burstdata.h"
#include "convutility.h"
#include "CBcnMsgDecodeBase.h"
#include "emsbeacon.h"


const wchar_t* CEMSBurstData::BURST_DATA_ELEMENT = L"burst_data";
const wchar_t* CEMSBurstData::TXTIME_ATTR = L"txtime";
const wchar_t* CEMSBurstData::BURST_ELEMENT = L"burst";
const wchar_t* CEMSBurstData::LUTID_ATTR = L"lutid";
const wchar_t* CEMSBurstData::MSG406_ATTR = L"msg406";
const wchar_t* CEMSBurstData::UPLINK_TOA_ATTR = L"up_toa";
const wchar_t* CEMSBurstData::TIME_OFFSET_ATTR = L"time_offset";
const wchar_t* CEMSBurstData::UPLINK_FOA_ATTR = L"up_foa";
const wchar_t* CEMSBurstData::FREQ_OFFSET_ATTR = L"freq_offset";
const wchar_t* CEMSBurstData::CNR_ATTR = L"cnr";
const wchar_t* CEMSBurstData::TOA_ATTR = L"toa";
const wchar_t* CEMSBurstData::FOA_ATTR = L"foa";
const wchar_t* CEMSBurstData::BIT_ERR1_ATTR = L"biterr1";
const wchar_t* CEMSBurstData::BIT_ERR2_ATTR = L"biterr2";
const wchar_t* CEMSBurstData::BIT_ERRFS_ATTR = L"biterrfs";
const wchar_t* CEMSBurstData::BIT_RATE_ATTR = L"bit_rate";
const wchar_t* CEMSBurstData::RAW_MSG_ATTR = L"raw_msg";
const wchar_t* CEMSBurstData::CORRECTED_MSG_ATTR = L"corrected_msg";
const wchar_t* CEMSBurstData::SAT_ELEMENT = L"sat";
const wchar_t* CEMSBurstData::SATID_ATTR = L"id";
const wchar_t* CEMSBurstData::SAT_EPOCH_ATTR = L"time";
const wchar_t* CEMSBurstData::POS_VEC_ELEMENT = L"vpos";
const wchar_t* CEMSBurstData::X_ATTR = L"x";
const wchar_t* CEMSBurstData::Y_ATTR = L"y";
const wchar_t* CEMSBurstData::Z_ATTR = L"z";
const wchar_t* CEMSBurstData::VEL_VEC_ELEMENT = L"vvel";
const wchar_t* CEMSBurstData::ANT_ELEMENT = L"ant";
const wchar_t* CEMSBurstData::ANTID_ATTR = L"id";
const wchar_t* CEMSBurstData::ANT_AZ_ATTR = L"az";
const wchar_t* CEMSBurstData::ANT_EL_ATTR = L"el";
const wchar_t* CEMSBurstData::ENCODED_ELEMENT = L"encoded_pos";
const wchar_t* CEMSBurstData::LAT_ATTR = L"lat";
const wchar_t* CEMSBurstData::LNG_ATTR = L"lng";
const wchar_t* CEMSBurstData::SOLUTION_ELEMENT = L"locate";
const wchar_t* CEMSBurstData::ITERATIONS_ATTR = L"iterations";
const wchar_t* CEMSBurstData::START_TIME_ATTR = L"start_time";
const wchar_t* CEMSBurstData::END_TIME_ATTR = L"end_time";
const wchar_t* CEMSBurstData::POSITION_ELEMENT = L"position";
const wchar_t* CEMSBurstData::ALT_ATTR = L"alt";
const wchar_t* CEMSBurstData::POWER_ATTR = L"power";
const wchar_t* CEMSBurstData::RADIUS_ERR_ELLIPSE_ATTR = L"radius_ee";
const wchar_t* CEMSBurstData::TYPE_ATTR = L"type";

const wchar_t* CEMSBurstData::MODE_ATTR = L"mode";
const wchar_t* CEMSBurstData::DETECT_ONLY_ATTR = L"detect_only";
const wchar_t* CEMSBurstData::COUNTRY_CODE_ATTR = L"cc";

const wchar_t* CEMSBurstData::MODE_NORMAL = L"NORMAL";
const wchar_t* CEMSBurstData::MODE_TEST = L"TEST";


const wchar_t* CEMSBurstData::PROCESS_TIME_ATTR = L"process_time";
const wchar_t* CEMSBurstData::POSITION_ERROR_ATTR = L"poserr";
const wchar_t* CEMSBurstData::CONFIDENCE_ATTR = L"confidence";
const wchar_t* CEMSBurstData::TX_FREQUENCY_ATTR = L"txfrequency";
const wchar_t* CEMSBurstData::MAJOR_AXIS_ERR_ELLIPSE_ATTR = L"major_ee";
const wchar_t* CEMSBurstData::MINOR_AXIS_ERR_ELLIPSE_ATTR = L"minor_ee";
const wchar_t* CEMSBurstData::HEADING_ERR_ELLIPSE_ATTR = L"heading_ee";
const wchar_t* CEMSBurstData::FOA_RMS_ATTR = L"foa_rms";
const wchar_t* CEMSBurstData::TOA_RMS_ATTR = L"toa_rms";
const wchar_t* CEMSBurstData::NUM_MSG_ATTR = L"num_messages";
const wchar_t* CEMSBurstData::NUM_TOA_MSG_USED_ATTR = L"num_toa_used";
const wchar_t* CEMSBurstData::NUM_FOA_MSG_USED_ATTR = L"num_foa_used";
const wchar_t* CEMSBurstData::NUM_BURSTS_ATTR = L"num_bursts";
const wchar_t* CEMSBurstData::HDOP_ATTR = L"hdop";


CEMSBurstData::CEMSBurstData()
{
	m_timeTx.intTime = 0;
	memset( &m_solution, 0, sizeof(m_solution) );

}

CEMSBurstData::CEMSBurstData( const CEMSBurstData& x ) : m_timeTx( x.m_timeTx ), 
														m_burstData( x.m_burstData ),
														m_solution( x.m_solution )
{
}

CEMSBurstData::~CEMSBurstData()
{
}

void
CEMSBurstData::Reset()
{
	m_timeTx.intTime = 0;
	m_burstData.Clear();
	memset( &m_solution, 0, sizeof(m_solution) );
}

bool 
CEMSBurstData::IsDetectOnly() const
{
	bool bRet = false;

	// Detect-only if type explicitly set or.
	if( 0 == m_solution.wType ||
		((m_solution.wType & EMSLOCTYPE_DETECT_ONLY) == EMSLOCTYPE_DETECT_ONLY) )
		bRet = true;

	return bRet;
}

void 
CEMSBurstData::Serialize( CEMSConfigurationAccessor& rModel )
{
	CEMSConfigurationAccessor* pBurstData = NULL;
	CEMSConfigurationAccessor* pBurst = NULL;
	CEMSConfigurationAccessor* pSat = NULL;
	CEMSConfigurationAccessor* pPosVec = NULL;
	CEMSConfigurationAccessor* pVelVec = NULL;
	CEMSConfigurationAccessor* pAntenna = NULL;
	CEMSConfigurationAccessor* pEncoded = NULL;
	CEMSConfigurationAccessor* pSolution = NULL;
	CEMSConfigurationAccessor* pPosition = NULL;
		

	try
	{
		pBurstData = rModel.AddChildElement( NULL, BURST_DATA_ELEMENT );

		pBurstData->SetAttributeValue( TXTIME_ATTR, CEMSConversionUtil::ConvertToString(m_timeTx.intTime).c_str() );

		m_burstData.MoveFirst();

		ULONG ulMeasurements = m_burstData.Count();

		for( ULONG l = 0; l < ulMeasurements; l++ )
		{
			EMSCALIB406DATAEXT burst = m_burstData.GetNext();

			pBurst = pBurstData->AddChildElement( NULL, BURST_ELEMENT );

			pBurst->SetAttributeValue( LUTID_ATTR, CEMSConversionUtil::ConvertToString(burst.calib406.hdr.id.ulLutID).c_str() );
			pBurst->SetAttributeValue( MSG406_ATTR, CEMSConversionUtil::ConvertToHexStringW(sizeof(burst.calib406.cBeaconMsg),burst.calib406.cBeaconMsg).c_str() );
			pBurst->SetAttributeValue( UPLINK_TOA_ATTR, CEMSConversionUtil::ConvertToString(burst.calib406.timeMsg.intTime).c_str() );
			pBurst->SetAttributeValue( TIME_OFFSET_ATTR, CEMSConversionUtil::ConvertToString(burst.calib406.i64TimeOffset).c_str() );
			pBurst->SetAttributeValue( UPLINK_FOA_ATTR, CEMSConversionUtil::ConvertToString(burst.calib406.dFrequency).c_str() );
			pBurst->SetAttributeValue( FREQ_OFFSET_ATTR, CEMSConversionUtil::ConvertToString(burst.calib406.dFreqOffset).c_str() );
			pBurst->SetAttributeValue( CNR_ATTR, CEMSConversionUtil::ConvertToString(burst.calib406.dCarrierPower).c_str() );
			pBurst->SetAttributeValue( TOA_ATTR, CEMSConversionUtil::ConvertToString(burst.calib406.timeMsg.intTime + burst.calib406.i64TimeOffset).c_str() );
			pBurst->SetAttributeValue( FOA_ATTR, CEMSConversionUtil::ConvertToString(burst.calib406.dFrequency + burst.calib406.dFreqOffset).c_str() );
			pBurst->SetAttributeValue( BIT_ERR1_ATTR, CEMSConversionUtil::ConvertToString(burst.calib406.wBitErrorField1).c_str() );
			pBurst->SetAttributeValue( BIT_ERR2_ATTR, CEMSConversionUtil::ConvertToString(burst.calib406.wBitErrorField2).c_str() );
			pBurst->SetAttributeValue( BIT_ERRFS_ATTR, CEMSConversionUtil::ConvertToString(burst.calib406.wBitErrorFrameSynch).c_str() );
			pBurst->SetAttributeValue( BIT_RATE_ATTR, CEMSConversionUtil::ConvertToString(burst.calib406.dBitRate).c_str() );
			pBurst->SetAttributeValue( RAW_MSG_ATTR, CEMSConversionUtil::ConvertToHexStringW(sizeof(burst.calib406.cBeaconMsg),burst.calib406.cBeaconMsg).c_str() );
			pBurst->SetAttributeValue( CORRECTED_MSG_ATTR, CEMSConversionUtil::ConvertToHexStringW(sizeof(burst.calib406.cBeaconMsg),burst.calib406.cBeaconMsg).c_str() );

			pSat = pBurst->AddChildElement( NULL, SAT_ELEMENT );

			pSat->SetAttributeValue( SATID_ATTR, CEMSConversionUtil::ConvertToString(burst.calib406.hdr.id.ulSatID).c_str() );
			pSat->SetAttributeValue( SAT_EPOCH_ATTR, CEMSConversionUtil::ConvertToString(burst.extras.SatTPVC.vTime.intTime).c_str() );

			pPosVec = pSat->AddChildElement( NULL, POS_VEC_ELEMENT );

			pPosVec->SetAttributeValue( X_ATTR, CEMSConversionUtil::ConvertToString(burst.extras.SatTPVC.coord.radius.dX).c_str() );
			pPosVec->SetAttributeValue( Y_ATTR, CEMSConversionUtil::ConvertToString(burst.extras.SatTPVC.coord.radius.dY).c_str() );
			pPosVec->SetAttributeValue( Z_ATTR, CEMSConversionUtil::ConvertToString(burst.extras.SatTPVC.coord.radius.dZ).c_str() );

			pPosVec->Release();
			pPosVec = NULL;

			pVelVec = pSat->AddChildElement( NULL, VEL_VEC_ELEMENT );

			pVelVec->SetAttributeValue( X_ATTR, CEMSConversionUtil::ConvertToString(burst.extras.SatTPVC.coord.velocity.dX).c_str() );
			pVelVec->SetAttributeValue( Y_ATTR, CEMSConversionUtil::ConvertToString(burst.extras.SatTPVC.coord.velocity.dY).c_str() );
			pVelVec->SetAttributeValue( Z_ATTR, CEMSConversionUtil::ConvertToString(burst.extras.SatTPVC.coord.velocity.dZ).c_str() );

			pVelVec->Release();
			pVelVec = NULL;

			pAntenna = pBurst->AddChildElement( NULL, ANT_ELEMENT );

			pAntenna->SetAttributeValue( ANTID_ATTR, CEMSConversionUtil::ConvertToString(burst.calib406.wAntennaID).c_str() );
			pAntenna->SetAttributeValue( ANT_AZ_ATTR, CEMSConversionUtil::ConvertToString(burst.calib406.dReserve1).c_str() );
			pAntenna->SetAttributeValue( ANT_EL_ATTR, CEMSConversionUtil::ConvertToString(burst.calib406.dReserve2).c_str() );

			pAntenna->Release();
			pAntenna = NULL;

			CBeaconMessage bcnMsg( burst.calib406.cBeaconMsg );
			CBcnMsgDecodeBase decoder;
			decoder.Initialize();
			decoder.DecodeEx( bcnMsg );
			bool bHasEncoded = false;
			double dLat = 0.0;
			double dLong = 0.0;
			decoder.GetEncodedLocation( bHasEncoded, dLat, dLong );

			if( bHasEncoded )
			{
				pEncoded = pBurst->AddChildElement( NULL, ENCODED_ELEMENT );

				pEncoded->SetAttributeValue( LAT_ATTR, CEMSConversionUtil::ConvertToString(dLat).c_str() );
				pEncoded->SetAttributeValue( LNG_ATTR, CEMSConversionUtil::ConvertToString(dLong).c_str() );

				pEncoded->Release();
				pEncoded = NULL;
			}


			pSat->Release();
			pSat = NULL;

			pBurst->Release();
			pBurst = NULL;
		}

		// Do we have a location.  Look for non-zero timestamp or detect-only setting.
		bool isDetectOnly = ( EMSLOCTYPE_406_DETECT == (m_solution.wType & EMSLOCTYPE_406_DETECT ) );
		
		if( !isDetectOnly )
		{
			bool isNormalMode = ( '2F' == m_solution.info.rec406.cBeaconMsg[2] );
		
			ULONG ulCC = 0;
	 		CBeaconMsg bcn;
	 		bcn.Set( m_solution.info.rec406.cBeaconMsg );
			ulCC = bcn.getCountryCode( );

			pSolution = pBurstData->AddChildElement( NULL, SOLUTION_ELEMENT );

			pSolution->SetAttributeValue( ITERATIONS_ATTR, CEMSConversionUtil::ConvertToString(m_solution.wlsSolution.wNumIterations).c_str() );
			pSolution->SetAttributeValue( START_TIME_ATTR, CEMSConversionUtil::ConvertToString(m_solution.timeFirstData.intTime).c_str() );
			pSolution->SetAttributeValue( END_TIME_ATTR, CEMSConversionUtil::ConvertToString(m_solution.timeLastData.intTime).c_str() );
			pSolution->SetAttributeValue( PROCESS_TIME_ATTR, CEMSConversionUtil::ConvertToString(m_solution.time.intTime).c_str() );
			pSolution->SetAttributeValue( POWER_ATTR, CEMSConversionUtil::ConvertToString(m_solution.fPower).c_str() );
			pSolution->SetAttributeValue( TYPE_ATTR, CEMSConversionUtil::ConvertToString(m_solution.wType).c_str() );
		
			pSolution->SetAttributeValue( MODE_ATTR, isNormalMode ? MODE_NORMAL : MODE_TEST );
			pSolution->SetAttributeValue( DETECT_ONLY_ATTR, isDetectOnly );
			pSolution->SetAttributeValue( COUNTRY_CODE_ATTR, ulCC );

			pSolution->SetAttributeValue( TX_FREQUENCY_ATTR, CEMSConversionUtil::ConvertToString(m_solution.wlsSolution.dFrequency).c_str() );
			pSolution->SetAttributeValue( FOA_RMS_ATTR, CEMSConversionUtil::ConvertToString(m_solution.wlsSolution.fRMS).c_str() );
			pSolution->SetAttributeValue( TOA_RMS_ATTR, CEMSConversionUtil::ConvertToString(m_solution.wlsSolution.fTrend).c_str() );
			pSolution->SetAttributeValue( HDOP_ATTR, CEMSConversionUtil::ConvertToString(m_solution.wlsSolution.fFreqDrift).c_str() );
			pSolution->SetAttributeValue( CONFIDENCE_ATTR, CEMSConversionUtil::ConvertToString(m_solution.fConfidence).c_str() );

			pSolution->SetAttributeValue( NUM_MSG_ATTR, CEMSConversionUtil::ConvertToString(m_solution.wlsSolution.wNumMsgs).c_str() );
			pSolution->SetAttributeValue( NUM_TOA_MSG_USED_ATTR, CEMSConversionUtil::ConvertToString(floor(m_solution.wlsSolution.fFreqBiasError)).c_str() );
			pSolution->SetAttributeValue( NUM_FOA_MSG_USED_ATTR, CEMSConversionUtil::ConvertToString(m_solution.wlsSolution.wNumMsgsUsed).c_str() );
			pSolution->SetAttributeValue( NUM_BURSTS_ATTR, CEMSConversionUtil::ConvertToString(m_solution.wlsSolution.wNumBurstsUsed).c_str() );
			pSolution->SetAttributeValue( NUM_MSG_ATTR, CEMSConversionUtil::ConvertToString(m_solution.wlsSolution.wNumIterations).c_str() );

			pPosition = pSolution->AddChildElement( NULL, POSITION_ELEMENT );

			pPosition->SetAttributeValue( LAT_ATTR, CEMSConversionUtil::ConvertToString(m_solution.wlsSolution.location.degLatitude).c_str() );
			pPosition->SetAttributeValue( LNG_ATTR, CEMSConversionUtil::ConvertToString(m_solution.wlsSolution.location.degLongitude).c_str() );
			pPosition->SetAttributeValue( ALT_ATTR, CEMSConversionUtil::ConvertToString(m_solution.wlsSolution.location.fAltitude).c_str() );
			pPosition->SetAttributeValue( RADIUS_ERR_ELLIPSE_ATTR, CEMSConversionUtil::ConvertToString(m_solution.wlsSolution.fRadiusErrEllipse).c_str() );
			pPosition->SetAttributeValue( MAJOR_AXIS_ERR_ELLIPSE_ATTR, CEMSConversionUtil::ConvertToString(m_solution.wlsSolution.fMajorError).c_str() );
			pPosition->SetAttributeValue( MINOR_AXIS_ERR_ELLIPSE_ATTR, CEMSConversionUtil::ConvertToString(m_solution.wlsSolution.fMinorError).c_str() );
			pPosition->SetAttributeValue( HEADING_ERR_ELLIPSE_ATTR, CEMSConversionUtil::ConvertToString(m_solution.wlsSolution.fHeading).c_str() );
			pPosition->SetAttributeValue( POSITION_ERROR_ATTR, CEMSConversionUtil::ConvertToString(m_solution.fCrossTrackAngle).c_str() );
			
			pPosition->Release();
			pPosition = NULL;

			pSolution->Release();
			pSolution = NULL;


		}

		pBurstData->Release();
		pBurstData = NULL;


	}
	catch( ... )
	{
		if( pBurstData )
		{
			pBurstData->Release();
			pBurstData = NULL;
		}

		if( pBurst )
		{
			pBurst->Release();
			pBurst = NULL;
		}

		if( pSat )
		{
			pSat->Release();
			pSat = NULL;
		}

		if( pPosVec )
		{
			pPosVec->Release();
			pPosVec = NULL;
		}

		if( pVelVec )
		{
			pVelVec->Release();
			pVelVec = NULL;
		}

		if( pAntenna )
		{
			pAntenna->Release();
			pAntenna = NULL;
		}

		if( pEncoded )
		{
			pEncoded->Release();
			pEncoded = NULL;
		}

		if( pSolution )
		{
			pSolution->Release();
			pSolution = NULL;
		}

		if( pPosition )
		{
			pPosition->Release();
			pPosition = NULL;
		}

		throw;
	}
}

void 
CEMSBurstData::Deserialize( CEMSConfigurationAccessor& rModel )
{
	Reset();

	std::wstring txTime = rModel.GetAttributeValue( _PrependAt(TXTIME_ATTR).c_str() );
	if( !txTime.empty() )
		m_timeTx = CEMSConversionUtil::ConvertToTime( txTime.c_str() );

	CEMSObjectList<CEMSConfigurationAccessor> lstBurst = rModel.GetAccessorList( BURST_ELEMENT );

	ULONG ulMeasurements = lstBurst.Count();
	lstBurst.MoveFirst();

	for( ULONG l = 0; l < ulMeasurements; l++ )
	{
		CEMSConfigurationAccessor measurement = lstBurst.GetNext();

		EMSCALIB406DATAEXT burst;
		memset( &burst, 0, sizeof(burst) );

		burst.calib406.hdr.id.ulLutID = measurement.GetAttributeValueULong( _PrependAt(LUTID_ATTR).c_str() );

		std::wstring bcnMsg = measurement.GetAttributeValue( _PrependAt(MSG406_ATTR).c_str() );
		if( !bcnMsg.empty() )
			CEMSConversionUtil::ConvertHexStringToByteArray( bcnMsg.c_str(), sizeof(burst.calib406.cBeaconMsg), burst.calib406.cBeaconMsg );

		std::wstring uplinkToa = measurement.GetAttributeValue( _PrependAt(UPLINK_TOA_ATTR).c_str() );
		if( !uplinkToa.empty() )
			burst.calib406.timeMsg = CEMSConversionUtil::ConvertToTime( uplinkToa.c_str() );

		std::wstring timeOffset = measurement.GetAttributeValue( _PrependAt(TIME_OFFSET_ATTR).c_str() );
		if( !timeOffset.empty() )
			burst.calib406.i64TimeOffset = CEMSConversionUtil::ConvertStringToUInt64( timeOffset.c_str() );

		std::wstring uplinkFoa = measurement.GetAttributeValue( _PrependAt(UPLINK_FOA_ATTR).c_str() );
		if( !uplinkFoa.empty() )
			burst.calib406.dFrequency = CEMSConversionUtil::ConvertToDouble( uplinkFoa.c_str() );

		std::wstring freqOffset = measurement.GetAttributeValue( _PrependAt(FREQ_OFFSET_ATTR).c_str() );
		if( !freqOffset.empty() )
			burst.calib406.dFreqOffset = CEMSConversionUtil::ConvertToDouble( freqOffset.c_str() );

		std::wstring cnr = measurement.GetAttributeValue( _PrependAt(CNR_ATTR).c_str() );
		if( !cnr.empty() )
			burst.calib406.dCarrierPower = CEMSConversionUtil::ConvertToDouble( cnr.c_str() );

		std::wstring toa = measurement.GetAttributeValue( _PrependAt(TOA_ATTR).c_str() );
		if( !toa.empty() )
			burst.calib406.i64TimeOffset = CEMSConversionUtil::ConvertStringToUInt64( toa.c_str() ) - burst.calib406.timeMsg.intTime;

		// FOA_ATTR is redundant
		//std::wstring foa = measurement.GetAttributeValue( FOA_ATTR );
		//if( !foa.empty() )
		//	burst.calib406.dFreqOffset = CEMSConversionUtil::ConvertStringToUInt64( foa.c_str() ) - burst.calib406.dFrequency;

		std::wstring bitErr1 = measurement.GetAttributeValue( _PrependAt(BIT_ERR1_ATTR).c_str() );
		if( !bitErr1.empty() )
			burst.calib406.wBitErrorField1 = CEMSConversionUtil::ConvertToShort( bitErr1.c_str() );

		std::wstring bitErr2 = measurement.GetAttributeValue( _PrependAt(BIT_ERR2_ATTR).c_str() );
		if( !bitErr2.empty() )
			burst.calib406.wBitErrorField2 = CEMSConversionUtil::ConvertToShort( bitErr2.c_str() );

		std::wstring bitErrFS = measurement.GetAttributeValue( _PrependAt(BIT_ERRFS_ATTR).c_str() );
		if( !bitErrFS.empty() )
			burst.calib406.wBitErrorFrameSynch = CEMSConversionUtil::ConvertToShort( bitErrFS.c_str() );

		std::wstring bitRate = measurement.GetAttributeValue( _PrependAt(BIT_RATE_ATTR).c_str() );
		if( !bitRate.empty() )
			burst.calib406.dBitRate = CEMSConversionUtil::ConvertToDouble( bitRate.c_str() );

		CEMSConfigurationAccessor sat = measurement.GetAccessor( SAT_ELEMENT );

		burst.calib406.hdr.id.ulSatID = sat.GetAttributeValueULong( _PrependAt(SATID_ATTR).c_str() );
		
		std::wstring epochTime = sat.GetAttributeValue( _PrependAt(SAT_EPOCH_ATTR).c_str() );
		if( !epochTime.empty() )
			burst.extras.SatTPVC.vTime = CEMSConversionUtil::ConvertToTime( epochTime.c_str() );
		
		CEMSConfigurationAccessor posVec = sat.GetAccessor( POS_VEC_ELEMENT );

		std::wstring xPos = posVec.GetAttributeValue( _PrependAt(X_ATTR).c_str() );
		if( !xPos.empty() )
			burst.extras.SatTPVC.coord.radius.dX = CEMSConversionUtil::ConvertToDouble( xPos.c_str() );

		std::wstring yPos = posVec.GetAttributeValue( _PrependAt(Y_ATTR).c_str() );
		if( !yPos.empty() )
			burst.extras.SatTPVC.coord.radius.dY = CEMSConversionUtil::ConvertToDouble( yPos.c_str() );

		std::wstring zPos = posVec.GetAttributeValue( _PrependAt(Z_ATTR).c_str() );
		if( !zPos.empty() )
			burst.extras.SatTPVC.coord.radius.dZ = CEMSConversionUtil::ConvertToDouble( zPos.c_str() );

		CEMSConfigurationAccessor velVec = sat.GetAccessor( VEL_VEC_ELEMENT );

		std::wstring xVel = velVec.GetAttributeValue( _PrependAt(X_ATTR).c_str() );
		if( !xVel.empty() )
			burst.extras.SatTPVC.coord.velocity.dX = CEMSConversionUtil::ConvertToDouble( xVel.c_str() );

		std::wstring yVel = velVec.GetAttributeValue( _PrependAt(Y_ATTR).c_str() );
		if( !yVel.empty() )
			burst.extras.SatTPVC.coord.velocity.dY = CEMSConversionUtil::ConvertToDouble( yVel.c_str() );

		std::wstring zVel = velVec.GetAttributeValue( _PrependAt(Z_ATTR).c_str() );
		if( !zVel.empty() )
			burst.extras.SatTPVC.coord.velocity.dZ = CEMSConversionUtil::ConvertToDouble( zVel.c_str() );


		CEMSConfigurationAccessor ant = measurement.GetAccessor( ANT_ELEMENT );
		
		std::wstring antID = ant.GetAttributeValue( _PrependAt(ANTID_ATTR).c_str() );
		if( !antID.empty() )
			burst.calib406.wAntennaID = CEMSConversionUtil::ConvertToShort( antID.c_str() );

		std::wstring antAz = ant.GetAttributeValue( _PrependAt(ANT_AZ_ATTR).c_str() );
		if( !antAz.empty() )
			burst.calib406.dReserve1 = CEMSConversionUtil::ConvertToDouble( antAz.c_str() );

		std::wstring antEl = ant.GetAttributeValue( _PrependAt(ANT_EL_ATTR).c_str() );
		if( !antEl.empty() )
			burst.calib406.dReserve2 = CEMSConversionUtil::ConvertToDouble( antEl.c_str() );

		AddBurstMeasurement( burst );
	}


	if( rModel.DoesNodeExist( SOLUTION_ELEMENT ) )
	{
		CEMSConfigurationAccessor location = rModel.GetAccessor( SOLUTION_ELEMENT );

		std::wstring iterations = location.GetAttributeValue( _PrependAt(ITERATIONS_ATTR).c_str() );
		if( !iterations.empty() )
			m_solution.wlsSolution.wNumIterations = CEMSConversionUtil::ConvertToShort( iterations.c_str() );

		std::wstring startTime = location.GetAttributeValue( _PrependAt(START_TIME_ATTR).c_str() );
		if( !startTime.empty() )
			m_solution.timeFirstData = CEMSConversionUtil::ConvertToTime( startTime.c_str() );

		std::wstring endTime = location.GetAttributeValue( _PrependAt(END_TIME_ATTR).c_str() );
		if( !endTime.empty() )
			m_solution.timeLastData = CEMSConversionUtil::ConvertToTime( endTime.c_str() );

		std::wstring power = location.GetAttributeValue( _PrependAt(POWER_ATTR).c_str() );
		if( !power.empty() )
			m_solution.fPower = CEMSConversionUtil::ConvertToFloat( power.c_str() );

		std::wstring type = location.GetAttributeValue( _PrependAt(TYPE_ATTR).c_str() );
		if( !type.empty() )
			m_solution.wType = CEMSConversionUtil::ConvertToShort( type.c_str() );


		CEMSConfigurationAccessor position = location.GetAccessor( POSITION_ELEMENT );

		std::wstring lat = position.GetAttributeValue( _PrependAt(LAT_ATTR).c_str() );
		if( !lat.empty() )
			m_solution.wlsSolution.location.degLatitude = CEMSConversionUtil::ConvertToDouble( lat.c_str() );

		std::wstring lng = position.GetAttributeValue( _PrependAt(LNG_ATTR).c_str() );
		if( !lng.empty() )
			m_solution.wlsSolution.location.degLongitude = CEMSConversionUtil::ConvertToDouble( lng.c_str() );

		std::wstring alt = position.GetAttributeValue( _PrependAt(ALT_ATTR).c_str() );
		if( !alt.empty() )
			m_solution.wlsSolution.location.fAltitude = CEMSConversionUtil::ConvertToFloat( alt.c_str() );

		std::wstring radius_ee = position.GetAttributeValue( _PrependAt(RADIUS_ERR_ELLIPSE_ATTR).c_str() );
		if( !radius_ee.empty() )
			m_solution.wlsSolution.fRadiusErrEllipse = CEMSConversionUtil::ConvertToFloat( radius_ee.c_str() );

	}

}

std::wstring
CEMSBurstData::_PrependAt( const wchar_t* cwszAttr ) 
{
	std::wstring ret = L"@";

	ret.append( cwszAttr );
	
	return ret;
}