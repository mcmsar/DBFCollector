/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
*********************************************************************************/

#include "emserror.h"
#include "sittoken.h"
#include "configurationaccessor.h"
#include "xmlmfdefns.h"
#include "ActiveBeacon.h"
#include "convutility.h"
#include "PointerList.h"
#include "uniquetimeprovider.h"
#include "emsdomnode.h"
#include "emsexcpt.h"
#include "emsencod.h"
#include "HexUtilis.h"


const wchar_t* ActiveBeacon::ms_cwszGeneratedByLutId = L"@generatedByLutId";
const wchar_t* ActiveBeacon::ms_cwszBeaconId = L"@beaconId";
const wchar_t* ActiveBeacon::ms_cwszBcnMsg36Hex = L"@bcnMsg36Hex";
const wchar_t* ActiveBeacon::ms_cwszCountryCode = L"@countryCode";

const wchar_t* ActiveBeacon::ms_cwszAvgLocLocationNode = L"ns3:avgLocation/ns2:location";
const wchar_t* ActiveBeacon::ms_cwszAltitude = L"Altitude";
const wchar_t* ActiveBeacon::ms_cwszLatitude = L"Latitude";
const wchar_t* ActiveBeacon::ms_cwszLongitude = L"Longitude";

const wchar_t* ActiveBeacon::ms_cwszAvgLocErrEllipseNode = L"ns3:avgLocation/ns2:errEllipse";
const wchar_t* ActiveBeacon::ms_cwszHeading = L"heading";
const wchar_t* ActiveBeacon::ms_cwszMajorRadius = L"majorRadius";
const wchar_t* ActiveBeacon::ms_cwszMinorRadius = L"minorRadius";
const wchar_t* ActiveBeacon::ms_cwszRadius = L"radius";

const wchar_t* ActiveBeacon::ms_cwszAvgLocation = L"ns3:avgLocation";
const wchar_t* ActiveBeacon::ms_cwszQualityFactor = L"qualityFactor";

const wchar_t* ActiveBeacon::ms_cwszNumToaFoaMeasurements = L"@numToaFoaMeasurements";
const wchar_t* ActiveBeacon::ms_cwszFirstDetectionTime = L"@firstDetectionTime";
const wchar_t* ActiveBeacon::ms_cwszLastDetectionTime = L"@lastDetectionTime";

const wchar_t* ActiveBeacon::ms_cwszAvgCnr = L"@avgCnr";
const wchar_t* ActiveBeacon::ms_cwszFrequency = L"@frequency";

const wchar_t* ActiveBeacon::ms_cwszSatIds = L"ns3:satIds/ns2:satId";
const wchar_t* ActiveBeacon::ms_cwszAntennaIds = L"ns3:antennaIds/ns2:antennaId";


ActiveBeacon::ActiveBeacon()
{
}

ActiveBeacon::ActiveBeacon( const ActiveBeacon& x )
{
	m_olstActiveBeacon = x.m_olstActiveBeacon;
	m_oAccessor = x.m_oAccessor;
	m_ABLDataRec = x.m_ABLDataRec;
}

ActiveBeacon::~ActiveBeacon()
{
	m_olstActiveBeacon.Clear();
}

EMSABLData ActiveBeacon::GetActiveBeaconRec()
{
	return m_ABLDataRec;
}

EMS_RESULT  
ActiveBeacon::ParseActiveBeaconXML( CEMSSitTokenizer *lpTokenizer  )
{
	EMS_RESULT hr = EMS_OK;
	CEMSDOMNode*		pNode = NULL;
	CEMSDOMNodeList*	pNodeList = NULL;


	if( lpTokenizer )
	{
		std::string oszFullMessage;
		hr = lpTokenizer->ReadAllText( oszFullMessage );

		if( (EMS_OK == hr) && !oszFullMessage.empty() )
		{

			try
			{
		 		m_oAccessor.SetSource( CEMSConversionUtil::ConvertToString( oszFullMessage.c_str() ).c_str(), gs_cwszActBcnNS );
	//			m_oAccessor.SetSourceFile( CEMSConversionUtil::ConvertToString( oszFullMessage.c_str() ).c_str(), gs_cwsz722ToaFoaNS );

				memset( &m_ABLDataRec, 0, sizeof(m_ABLDataRec) );

				// Get Merge Id params
				m_ABLDataRec.Id.timestamp = CEMSUniqueTimeProvider::GetInstance()->GetTime();
				m_ABLDataRec.Id.ulLUTID = m_oAccessor.GetElementValueULong( ms_cwszGeneratedByLutId );
				m_ABLDataRec.Id.i64BeaconID = m_oAccessor.GetElementValueUI64( ms_cwszBeaconId );

				wstring wszBcnMsg36Hex =  m_oAccessor.GetElementValue(ms_cwszBcnMsg36Hex);
				string szBcnMsg36Hex = CEMSConversionUtil::ConvertToString( (wchar_t *)wszBcnMsg36Hex.c_str() );
				HexReadEx( (char*)(szBcnMsg36Hex.c_str()), m_ABLDataRec.Id.acBeaconMsg, 36 );

				m_ABLDataRec.Id.wBitErrorFS = 0;	//TBC
				m_ABLDataRec.Id.wBitErrorField1 = 0;	//TBC
				m_ABLDataRec.Id.wBitErrorField2 = 0;	//TBC
				m_ABLDataRec.Id.wType = 1 ? m_oAccessor.GetElementValueBoolean( L"@located" ) : 0;	//TBC
				m_ABLDataRec.Id.dwCSFlags = 0;	//TBC
				m_ABLDataRec.Id.dwEMSFlags = 0;
				m_ABLDataRec.Id.wCountryCode = m_oAccessor.GetElementValueUShort( ms_cwszCountryCode );
				m_ABLDataRec.Id.wProtocolFlag = 0; //TBC
				m_ABLDataRec.Id.wProtocolCode = 0; //TBC
				m_ABLDataRec.Id.wWaveFormID = 0;	//TBC

				// Get the list of sat Ids.
				hr = _GetSatIds();

				// Get the list of Lut Ids.
				hr = _GetLutIds();

				// Get Merge Locate Info params
				pNode = m_oAccessor.GetNode( ms_cwszAvgLocLocationNode );
				if ( pNode )
				{
					m_ABLDataRec.Locate.dAltitude = pNode->GetAttributeValueDouble( ms_cwszAltitude );
					m_ABLDataRec.Locate.dLongitude = pNode->GetAttributeValueDouble( ms_cwszLongitude );
					m_ABLDataRec.Locate.dLatitude = pNode->GetAttributeValueDouble( ms_cwszLatitude );
					pNode->Release();
					pNode = NULL;
				}

				m_ABLDataRec.Locate.dProbability = 0;	//TBC

				pNode = m_oAccessor.GetNode( ms_cwszAvgLocErrEllipseNode );
				if ( pNode )
				{
					m_ABLDataRec.Locate.dMajorError = pNode->GetAttributeValueDouble( ms_cwszMajorRadius );
					m_ABLDataRec.Locate.dMinorError = pNode->GetAttributeValueDouble( ms_cwszMinorRadius );
					m_ABLDataRec.Locate.dHeading = pNode->GetAttributeValueDouble( ms_cwszHeading );
					m_ABLDataRec.Locate.dRadiusErrEllipse = pNode->GetAttributeValueDouble( ms_cwszRadius );
					pNode->Release();
					pNode = NULL;
				}

				m_ABLDataRec.Locate.dTOANoise = 0;	//TBC
				m_ABLDataRec.Locate.dFOANoise = 0;	//TBC
				m_ABLDataRec.Locate.dHDOP = 0;	//TBC
				m_ABLDataRec.Locate.dLocationError = 0.0;	//TBC

				m_ABLDataRec.Locate.dEncodedLat = 0;	//TBC (refer to CEMSActiveBeacon::_UpdateMergeID() )
				m_ABLDataRec.Locate.dEncodedLong = 0;	//TBC

				pNode = m_oAccessor.GetNode( ms_cwszAvgLocation );
				if ( pNode )
				{
					m_ABLDataRec.Locate.dComputedQualityFactor = pNode->GetAttributeValueDouble( ms_cwszQualityFactor );
					pNode->Release();
					pNode = NULL;
				}
				m_ABLDataRec.Locate.dEncodedQualityFactor = 0;	//TBC  (check CEMSActiveBeacon::_UpdateMQF())


				// Get Merged Detect Info params
				m_ABLDataRec.Detect.wNumMsgs = 0;	//TBC  (check CEMSActiveBeacon::_UpdateMergeDetectInfo())
				m_ABLDataRec.Detect.wNumFOAMsgsUsed = (WORD)(m_oAccessor.GetAttributeValueULong( ms_cwszNumToaFoaMeasurements ));
				m_ABLDataRec.Detect.wNumTOAMsgsUsed = (WORD)(m_oAccessor.GetAttributeValueULong( ms_cwszNumToaFoaMeasurements )); //TBC
				m_ABLDataRec.Detect.wNumBursts = 0;	//TBC  (check CEMSActiveBeacon::_UpdateMergeDetectInfo())

				wstring wszValue = m_oAccessor.GetAttributeValue( ms_cwszFirstDetectionTime );
				if( !wszValue.empty() )
				{
					m_ABLDataRec.Detect.timeDataStart = CEMSConversionUtil::ConvertToTime( wszValue.c_str() );
				}

				wszValue = m_oAccessor.GetAttributeValue( ms_cwszLastDetectionTime );
				if( !wszValue.empty() )
				{
					m_ABLDataRec.Detect.timeDataEnd = CEMSConversionUtil::ConvertToTime( wszValue.c_str() );
				}

				// Get Merged Beacon Info params
				m_ABLDataRec.Beacon.dCNR_Ave = m_oAccessor.GetElementValueDouble( ms_cwszAvgCnr );
				m_ABLDataRec.Beacon.dCNR_Sigma = 0.0;	//TBC
				m_ABLDataRec.Beacon.dFrequency_Ave = m_oAccessor.GetElementValueDouble( ms_cwszFrequency );
				m_ABLDataRec.Beacon.dFrequency_Sigma = 0.0;	//TBC
				m_ABLDataRec.Beacon.dBitRate_Ave = 0.0;	//TBC
				m_ABLDataRec.Beacon.dBitRate_Sigma = 0.0;	//TBC
				m_ABLDataRec.Beacon.dRepetitionRate_Ave = 0.0;	//TBC
				m_ABLDataRec.Beacon.dRepetitionRate_Sigma = 0.0;
			}
			catch( CEMSException& e )
			{
				// Couldn't load it as XML.
				hr = e.GetErrCode();
				if ( pNode )
				{
					pNode->Release();
					pNode = NULL;
				}
			}
			catch( ... )
			{
				// Couldn't load it as XML.
				hr = EMS_DATA_INVALID;
				if ( pNode )
				{
					pNode->Release();
					pNode = NULL;
				}
			}
		}
	}
	return hr;
}


EMS_RESULT
ActiveBeacon::_GetSatIds()
{
	EMS_RESULT			hr = EMS_OK;
	CEMSDOMNode*		pNode = NULL;
	CEMSDOMNodeList*	pNodeList = NULL;

	try
	{
		CEMSEncodedSatID::Reset( (EMSENCODEDSATID*)&m_ABLDataRec.Id.acSatIDs );
		pNodeList = m_oAccessor.GetNodes( ms_cwszSatIds );
		if ( pNodeList )
		{
			pNode = pNodeList->NextNode();
			while ( pNode ) 
			{
				ULONG	ulSatId = CEMSConversionUtil::ConvertToLong( pNode->GetElementText() );
				CEMSEncodedSatID::Set( (EMSENCODEDSATID*) &m_ABLDataRec.Id.acSatIDs, ulSatId );
				pNode->Release();
				pNode = NULL;
				pNode = pNodeList->NextNode();
			}
			pNodeList->Release();
			pNodeList = NULL;
		}
	}
	catch( CEMSException& e )
	{
		hr = e.GetErrCode();
		if ( pNode )
		{
			pNode->Release();
			pNode = NULL;
		}
		if ( pNodeList )
		{
			pNodeList->Release();
			pNodeList = NULL;
		}
	}
	catch( ... )
	{
		hr = EMS_DATA_INVALID;
		if ( pNode )
		{
			pNode->Release();
			pNode = NULL;
		}
		if ( pNodeList )
		{
			pNodeList->Release();
			pNodeList = NULL;
		}
	}
	return hr;
}


EMS_RESULT
ActiveBeacon::_GetLutIds()
{
	EMS_RESULT			hr = EMS_OK;
	CEMSDOMNode*		pNode = NULL;
	CEMSDOMNodeList*	pNodeList = NULL;

	try
	{
		CEMSEncodedLutID::Reset( (EMSENCODEDLUTID*)&m_ABLDataRec.Id.acLutIDs );
		pNodeList = m_oAccessor.GetNodes( ms_cwszAntennaIds );
		if ( pNodeList )
		{
			pNode = pNodeList->NextNode();
			while ( pNode ) 
			{
				ULONG	ulLutId = CEMSConversionUtil::ConvertToLong( pNode->GetElementText() );
				CEMSEncodedLutID::Set( (EMSENCODEDLUTID*) &m_ABLDataRec.Id.acLutIDs, ulLutId );
				pNode->Release();
				pNode = NULL;
				pNode = pNodeList->NextNode();
			}
			pNodeList->Release();
			pNodeList = NULL;
		}
	}
	catch( CEMSException& e )
	{
		hr = e.GetErrCode();
		if ( pNode )
		{
			pNode->Release();
			pNode = NULL;
		}
		if ( pNodeList )
		{
			pNodeList->Release();
			pNodeList = NULL;
		}
	}
	catch( ... )
	{
		hr = EMS_DATA_INVALID;
		if ( pNode )
		{
			pNode->Release();
			pNode = NULL;
		}
		if ( pNodeList )
		{
			pNodeList->Release();
			pNodeList = NULL;
		}
	}
	return hr;
}

