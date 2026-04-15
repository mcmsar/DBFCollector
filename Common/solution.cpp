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

#include "solution.h"
#include "convutility.h"
#include "burstdata.h"
#include "CBcnMsgDecodeBase.h"
#include "emsbeacon.h"
 
const wchar_t* CEMSSolution::LUTID_ATTR = L"lutid";
const wchar_t* CEMSSolution::BEACONID_ATTR = L"beaconid";
const wchar_t* CEMSSolution::SOLUTION_ELEMENT = L"locate";
const wchar_t* CEMSSolution::ITERATIONS_ATTR = L"iterations";
const wchar_t* CEMSSolution::START_TIME_ATTR = L"start_time";
const wchar_t* CEMSSolution::END_TIME_ATTR = L"end_time";
const wchar_t* CEMSSolution::POWER_ATTR = L"power";
const wchar_t* CEMSSolution::MSG406_ATTR = L"msg406";
const wchar_t* CEMSSolution::RADIUS_ERR_ELLIPSE_ATTR = L"radius_ee";
const wchar_t* CEMSSolution::TYPE_ATTR = L"type";
const wchar_t* CEMSSolution::POSITION_ELEMENT = L"position";
const wchar_t* CEMSSolution::LAT_ATTR = L"lat";
const wchar_t* CEMSSolution::LNG_ATTR = L"lng";
const wchar_t* CEMSSolution::ALT_ATTR = L"alt";
const wchar_t* CEMSSolution::ENCODED_ELEMENT = L"encoded_pos";
const wchar_t* CEMSSolution::BURST_DATA_ELEMENT = L"burst_data";
const wchar_t* CEMSSolution::MODE_ATTR = L"mode";
const wchar_t* CEMSSolution::DETECT_ONLY_ATTR = L"detect_only";
const wchar_t* CEMSSolution::COUNTRY_CODE_ATTR = L"cc";

const wchar_t* CEMSSolution::MODE_NORMAL = L"NORMAL";
const wchar_t* CEMSSolution::MODE_TEST = L"TEST";

const wchar_t* CEMSSolution::PROCESS_TIME_ATTR = L"process_time";
const wchar_t* CEMSSolution::POSITION_ERROR_ATTR = L"poserr";
const wchar_t* CEMSSolution::CONFIDENCE_ATTR = L"confidence";
const wchar_t* CEMSSolution::TX_FREQUENCY_ATTR = L"txfrequency";
const wchar_t* CEMSSolution::MAJOR_AXIS_ERR_ELLIPSE_ATTR = L"major_ee";
const wchar_t* CEMSSolution::MINOR_AXIS_ERR_ELLIPSE_ATTR = L"minor_ee";
const wchar_t* CEMSSolution::HEADING_ERR_ELLIPSE_ATTR = L"heading_ee";
const wchar_t* CEMSSolution::FOA_RMS_ATTR = L"foa_rms";
const wchar_t* CEMSSolution::TOA_RMS_ATTR = L"toa_rms";
const wchar_t* CEMSSolution::NUM_MSG_ATTR = L"num_messages";
const wchar_t* CEMSSolution::NUM_TOA_MSG_USED_ATTR = L"num_toa_used";
const wchar_t* CEMSSolution::NUM_FOA_MSG_USED_ATTR = L"num_foa_used";
const wchar_t* CEMSSolution::NUM_BURSTS_ATTR = L"num_bursts";
const wchar_t* CEMSSolution::HDOP_ATTR = L"hdop";

CEMSSolution::CEMSSolution() : m_ulLutID(0), m_i64BeaconID(0)
{
	memset( &m_finalSolution, 0, sizeof(m_finalSolution) );
}

CEMSSolution::CEMSSolution( const CEMSSolution& x ) : 
													m_ulLutID(x.m_ulLutID),
													m_i64BeaconID(x.m_i64BeaconID),		
													m_burstData( x.m_burstData ),
													m_finalSolution( x.m_finalSolution )
{
}

CEMSSolution::~CEMSSolution()
{
}

void
CEMSSolution::Reset()
{
	m_ulLutID = 0;
	m_i64BeaconID = 0;
	memset( &m_finalSolution, 0, sizeof(m_finalSolution) );
	m_burstData.Clear();
	
}

void
CEMSSolution::Deserialize(  const char* cszRec )
{
	Reset();

	if( cszRec )
	{
		CEMSConfigurationAccessor model;
		model.SetSource( CEMSConversionUtil::ConvertToString(cszRec).c_str() );

		m_ulLutID = model.GetAttributeValueULong( _PrependAt(LUTID_ATTR).c_str() );
		m_i64BeaconID = model.GetAttributeValueHexI64( _PrependAt(BEACONID_ATTR).c_str() );

		_DeserializeBurstData( model );
		_DeserializeFinalSolution( model );
	}
}

std::string 
CEMSSolution::Serialize() 
{
	std::string ret;
	
	const wchar_t* cwszRoot = L"<locate_output/>";

	CEMSConfigurationAccessor model;
	model.SetSource( cwszRoot );

	model.SetAttributeValue( LUTID_ATTR, CEMSConversionUtil::ConvertToString( m_ulLutID ).c_str() );
	model.SetAttributeValue( BEACONID_ATTR, CEMSConversionUtil::ConvertToHexString( m_i64BeaconID ).c_str() );

	_SerializeBurstData( model );
	_SerializeFinalSolution( model );

	ret = CEMSConversionUtil::ConvertToString( model.Serialize().c_str() );

	return ret;
}

void 
CEMSSolution::AddBurstData( CEMSBurstData* pBurst )
{
	m_burstData.Add( pBurst );
}

bool
CEMSSolution::IsDetectOnly() const
{
	bool bRet = false;

	if( 0 == m_finalSolution.wType ||
		(m_finalSolution.wType & EMSLOCTYPE_DETECT_ONLY) == EMSLOCTYPE_DETECT_ONLY )
		bRet = true;

	return bRet;
}

void 
CEMSSolution::_SerializeBurstData( CEMSConfigurationAccessor& rModel  ) 
{
	CEMSBurstData* pBurst = NULL;

	try
	{
		ULONG ulBursts = m_burstData.Count();
		m_burstData.MoveFirst();

		for( int i = 0; i < ulBursts; i++ )
		{
			pBurst = m_burstData.GetNext();

			pBurst->Serialize( rModel );

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

void 
CEMSSolution::_DeserializeBurstData( CEMSConfigurationAccessor& rModel  ) 
{
	CEMSBurstData* pBurstData = NULL;

	try
	{
		CEMSObjectList<CEMSConfigurationAccessor> lstBursts = rModel.GetAccessorList( BURST_DATA_ELEMENT );

		ULONG ulBursts = lstBursts.Count();
		lstBursts.MoveFirst();
		for( ULONG l = 0; l < ulBursts; l++ )
		{
			CEMSConfigurationAccessor burst = lstBursts.GetNext();

			pBurstData = new CEMSBurstData();

			pBurstData->Deserialize( burst );

			AddBurstData( pBurstData );

			pBurstData->Release();
			pBurstData = NULL;

		}
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
}

void 
CEMSSolution::_SerializeFinalSolution( CEMSConfigurationAccessor& rModel  ) 
{
	CEMSConfigurationAccessor* pFinalSolution = NULL;
	CEMSConfigurationAccessor* pPosition = NULL;
	CEMSConfigurationAccessor* pEncoded = NULL;

	try
	{
		bool isDetectOnly = ( EMSLOCTYPE_406_DETECT == (m_finalSolution.wType & EMSLOCTYPE_406_DETECT ) );
		bool isNormalMode = ( '2F' == m_finalSolution.info.rec406.cBeaconMsg[2] );
		
		ULONG ulCC = 0;
	 	CBeaconMsg bcn;
	 	bcn.Set( m_finalSolution.info.rec406.cBeaconMsg );
		ulCC = bcn.getCountryCode( );

		pFinalSolution = rModel.AddChildElement( NULL, SOLUTION_ELEMENT );

		pFinalSolution->SetAttributeValue( ITERATIONS_ATTR, CEMSConversionUtil::ConvertToString(m_finalSolution.wlsSolution.wNumIterations).c_str() );
		pFinalSolution->SetAttributeValue( START_TIME_ATTR, CEMSConversionUtil::ConvertToString(m_finalSolution.timeFirstData.intTime).c_str() );
		pFinalSolution->SetAttributeValue( END_TIME_ATTR, CEMSConversionUtil::ConvertToString(m_finalSolution.timeLastData.intTime).c_str() );
		pFinalSolution->SetAttributeValue( PROCESS_TIME_ATTR, CEMSConversionUtil::ConvertToString(m_finalSolution.time.intTime).c_str() );
		pFinalSolution->SetAttributeValue( TYPE_ATTR, CEMSConversionUtil::ConvertToString(m_finalSolution.wType).c_str() );
		pFinalSolution->SetAttributeValue( POWER_ATTR, CEMSConversionUtil::ConvertToString(m_finalSolution.fPower).c_str() );
		pFinalSolution->SetAttributeValue( MSG406_ATTR, CEMSConversionUtil::ConvertToHexStringW(sizeof(m_finalSolution.info.rec406.cBeaconMsg),m_finalSolution.info.rec406.cBeaconMsg).c_str() );

		pFinalSolution->SetAttributeValue( MODE_ATTR, isNormalMode ? MODE_NORMAL : MODE_TEST );
		pFinalSolution->SetAttributeValue( DETECT_ONLY_ATTR, isDetectOnly );
		pFinalSolution->SetAttributeValue( COUNTRY_CODE_ATTR, ulCC );

		pFinalSolution->SetAttributeValue( TX_FREQUENCY_ATTR, CEMSConversionUtil::ConvertToString(m_finalSolution.wlsSolution.dFrequency).c_str() );
		pFinalSolution->SetAttributeValue( FOA_RMS_ATTR, CEMSConversionUtil::ConvertToString(m_finalSolution.wlsSolution.fRMS).c_str() );
		pFinalSolution->SetAttributeValue( TOA_RMS_ATTR, CEMSConversionUtil::ConvertToString(m_finalSolution.wlsSolution.fTrend).c_str() );
		pFinalSolution->SetAttributeValue( HDOP_ATTR, CEMSConversionUtil::ConvertToString(m_finalSolution.wlsSolution.fFreqDrift).c_str() );
		pFinalSolution->SetAttributeValue( CONFIDENCE_ATTR, CEMSConversionUtil::ConvertToString(m_finalSolution.fConfidence).c_str() );

		pFinalSolution->SetAttributeValue( NUM_MSG_ATTR, CEMSConversionUtil::ConvertToString(m_finalSolution.wlsSolution.wNumMsgs).c_str() );
		pFinalSolution->SetAttributeValue( NUM_TOA_MSG_USED_ATTR, CEMSConversionUtil::ConvertToString(floor(m_finalSolution.wlsSolution.fFreqBiasError)).c_str() );
		pFinalSolution->SetAttributeValue( NUM_FOA_MSG_USED_ATTR, CEMSConversionUtil::ConvertToString(m_finalSolution.wlsSolution.wNumMsgsUsed).c_str() );
		pFinalSolution->SetAttributeValue( NUM_BURSTS_ATTR, CEMSConversionUtil::ConvertToString(m_finalSolution.wlsSolution.wNumBurstsUsed).c_str() );
		pFinalSolution->SetAttributeValue( NUM_MSG_ATTR, CEMSConversionUtil::ConvertToString(m_finalSolution.wlsSolution.wNumIterations).c_str() );

		pPosition = pFinalSolution->AddChildElement( NULL, POSITION_ELEMENT );

		pPosition->SetAttributeValue( LAT_ATTR, CEMSConversionUtil::ConvertToString(m_finalSolution.wlsSolution.location.degLatitude).c_str() );
		pPosition->SetAttributeValue( LNG_ATTR, CEMSConversionUtil::ConvertToString(m_finalSolution.wlsSolution.location.degLongitude).c_str() );
		pPosition->SetAttributeValue( ALT_ATTR, CEMSConversionUtil::ConvertToString(m_finalSolution.wlsSolution.location.fAltitude).c_str() );
		pPosition->SetAttributeValue( RADIUS_ERR_ELLIPSE_ATTR, CEMSConversionUtil::ConvertToString(m_finalSolution.wlsSolution.fRadiusErrEllipse).c_str() );
		pPosition->SetAttributeValue( MAJOR_AXIS_ERR_ELLIPSE_ATTR, CEMSConversionUtil::ConvertToString(m_finalSolution.wlsSolution.fMajorError).c_str() );
		pPosition->SetAttributeValue( MINOR_AXIS_ERR_ELLIPSE_ATTR, CEMSConversionUtil::ConvertToString(m_finalSolution.wlsSolution.fMinorError).c_str() );
		pPosition->SetAttributeValue( HEADING_ERR_ELLIPSE_ATTR, CEMSConversionUtil::ConvertToString(m_finalSolution.wlsSolution.fHeading).c_str() );
		pPosition->SetAttributeValue( POSITION_ERROR_ATTR, CEMSConversionUtil::ConvertToString(m_finalSolution.fCrossTrackAngle).c_str() );

		pPosition->Release();
		pPosition = NULL;

		CBeaconMessage bcnMsg( m_finalSolution.info.rec406.cBeaconMsg );
		CBcnMsgDecodeBase decoder;
		decoder.Initialize();
		decoder.DecodeEx( bcnMsg );
		bool bHasEncoded = false;
		double dLat = 0.0;
		double dLong = 0.0;
		decoder.GetEncodedLocation( bHasEncoded, dLat, dLong );

		if( bHasEncoded )
		{
			pEncoded = pFinalSolution->AddChildElement( NULL, ENCODED_ELEMENT );

			pEncoded->SetAttributeValue( LAT_ATTR, CEMSConversionUtil::ConvertToString(dLat).c_str() );
			pEncoded->SetAttributeValue( LNG_ATTR, CEMSConversionUtil::ConvertToString(dLong).c_str() );

			pEncoded->Release();
			pEncoded = NULL;
		}

		pFinalSolution->Release();
		pFinalSolution = NULL;

	}
	catch( ... )
	{
		if( pFinalSolution )
		{
			pFinalSolution->Release();
			pFinalSolution = NULL;
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
CEMSSolution::_DeserializeFinalSolution( CEMSConfigurationAccessor& rModel )
{
	CEMSConfigurationAccessor solution = rModel.GetAccessor( SOLUTION_ELEMENT );


	std::wstring numIterations = solution.GetAttributeValue( _PrependAt(ITERATIONS_ATTR).c_str() );
	if( !numIterations.empty() )
		m_finalSolution.wlsSolution.wNumIterations = CEMSConversionUtil::ConvertToShort( numIterations.c_str() );

	std::wstring startTime = solution.GetAttributeValue( _PrependAt(START_TIME_ATTR).c_str() );
	if( !startTime.empty() )
		m_finalSolution.timeFirstData = CEMSConversionUtil::ConvertToTime( startTime.c_str() );

	std::wstring endTime = solution.GetAttributeValue( _PrependAt(END_TIME_ATTR).c_str() );
	if( !endTime.empty() )
		m_finalSolution.timeLastData = CEMSConversionUtil::ConvertToTime( endTime.c_str() );

	std::wstring type = solution.GetAttributeValue( _PrependAt(TYPE_ATTR).c_str() );
	if( !type.empty() )
		m_finalSolution.wType = CEMSConversionUtil::ConvertToShort(type.c_str() );

	std::wstring power = solution.GetAttributeValue( _PrependAt(POWER_ATTR).c_str() );
	if( !power.empty() )
		m_finalSolution.fPower = CEMSConversionUtil::ConvertToFloat( power.c_str() );

	std::wstring bcnMsg = solution.GetAttributeValue( _PrependAt(MSG406_ATTR).c_str() );
	if( !bcnMsg.empty() )
		CEMSConversionUtil::ConvertHexStringToByteArray( bcnMsg.c_str(), sizeof(m_finalSolution.info.rec406.cBeaconMsg), m_finalSolution.info.rec406.cBeaconMsg );

	CEMSConfigurationAccessor position = solution.GetAccessor( POSITION_ELEMENT );

	std::wstring lat = position.GetAttributeValue( _PrependAt(LAT_ATTR).c_str() );
	if( !lat.empty() )
		m_finalSolution.wlsSolution.location.degLatitude = CEMSConversionUtil::ConvertToDouble( lat.c_str() );

	std::wstring lng = position.GetAttributeValue( _PrependAt(LNG_ATTR).c_str() );
	if( !lng.empty() )
		m_finalSolution.wlsSolution.location.degLongitude = CEMSConversionUtil::ConvertToDouble( lng.c_str() );

	std::wstring alt = position.GetAttributeValue( _PrependAt(ALT_ATTR).c_str() );
	if( !alt.empty() )
		m_finalSolution.wlsSolution.location.fAltitude = CEMSConversionUtil::ConvertToFloat( alt.c_str() );

	std::wstring radius_ee = position.GetAttributeValue( _PrependAt(RADIUS_ERR_ELLIPSE_ATTR).c_str() );
	if( !radius_ee.empty() )
		m_finalSolution.wlsSolution.fRadiusErrEllipse = CEMSConversionUtil::ConvertToFloat( radius_ee.c_str() );

}

std::wstring
CEMSSolution::_PrependAt( const wchar_t* cwszAttr ) 
{
	std::wstring ret = L"@";

	ret.append( cwszAttr );
	
	return ret;
}