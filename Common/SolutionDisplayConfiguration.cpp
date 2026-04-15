/*********************************************************************
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

	$Log$
********************************************************************/

#include "solutiondisplayconfiguration.h"
#include "beaconlayerconfigurationaccessor.h"
#include "sdbeaconsymbolconfiguration.h"
#include "emsexcpt.h"
#include "rgbcolour.h"
#include "configmanagermsgs.h"

#include <crtdbg.h>
#include <sstream>

const wchar_t* CEMSSolutionDisplayConfiguration::ms_cwszSDGroup = L"SOD";
const wchar_t* CEMSSolutionDisplayConfiguration::ms_cwszSDNoGroupID = c_pwcsNoGroupID;
const wchar_t* CEMSSolutionDisplayConfiguration::ms_cwszBeacon121BitmapSymbol = L"Beacon.121.Bitmap.Symbol";
const wchar_t* CEMSSolutionDisplayConfiguration::ms_cwszBeacon243BitmapSymbol = L"Beacon.243.Bitmap.Symbol";
const wchar_t* CEMSSolutionDisplayConfiguration::ms_cwszBeacon406BitmapSymbol = L"Beacon.406.Bitmap.Symbol";
const wchar_t* CEMSSolutionDisplayConfiguration::ms_cwszBeacon406InterfererBitmapSymbol = L"Beacon.406Interferer.Bitmap.Symbol";
const wchar_t* CEMSSolutionDisplayConfiguration::ms_cwszSDSatelliteTrackColour = L"SatelliteTrack.Colour";
const wchar_t* CEMSSolutionDisplayConfiguration::ms_cwszSDMutualVisRegionColour = L"MutualVisibility.Colour";
const wchar_t* CEMSSolutionDisplayConfiguration::ms_cwszSDSatelliteTrackWidth = L"SatelliteTrack.Width";
const wchar_t* CEMSSolutionDisplayConfiguration::ms_cwszSDGeosetTransform = L"GEOSet.Transform";

CEMSSolutionDisplayConfiguration CEMSSolutionDisplayConfiguration::ms_oConfig;


CEMSSolutionDisplayConfiguration::CEMSSolutionDisplayConfiguration()
{
}


CEMSSolutionDisplayConfiguration::~CEMSSolutionDisplayConfiguration()
{
}


CEMSSolutionDisplayConfiguration* 
CEMSSolutionDisplayConfiguration::GetInstance()
{
	return &ms_oConfig;
}

CEMSSDBeaconSymbolConfig* 
CEMSSolutionDisplayConfiguration::GetBeaconSymbolInfo( const wchar_t* cwszBeaconType )
{
	CEMSSDBeaconSymbolConfig* pRet = 0;
	
	IEMSConfigurationManager* pCM = 0;

	const int iCount = 1;
	EMSCONFIGURATIONITEM vValue[iCount];
	memset( &vValue, 0, iCount*sizeof(EMSCONFIGURATIONITEM) );
	int iRet = 0;

	try
	{
		if( cwszBeaconType )
		{
			std::wstring wszKey = _GetBeaconSymbolKey( cwszBeaconType );

			if( wszKey.empty() )
			{
#pragma message("JB--Need an message here.")
				THROW_NULL_POINTER_EXCEPTION();
			}

			pCM = _GetConfigManager();

			if( !pCM )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			const wchar_t* awszKeys[1];
			awszKeys[0] = wszKey.c_str();

			EMS_RESULT hr = pCM->GetEx(ms_cwszSDGroup, ms_cwszSDNoGroupID, awszKeys, iCount, vValue, &iRet );

			if( FAILED(hr) )
			{
#pragma message("JB--Need a specific message here.")
				THROW_RUNTIME_EXCEPTION( hr );
			}

			pCM->Release();
			pCM = 0;

			// Expecting a set of 3 configuration values:  A-side bitmap, B-side bitmap and bitmap size.
			if( 3 != vValue[0].uiValues )
			{
#pragma message("JB--Need a specific message here.")
				THROW_NULL_POINTER_EXCEPTION();
			}

			_ASSERTE( EMSVARITYPE_DATATYPE_STRING == vValue[0].ValueList[0].dataType );
			_ASSERTE( EMSVARITYPE_DATATYPE_STRING == vValue[0].ValueList[1].dataType );
			_ASSERTE( EMSVARITYPE_DATATYPE_INT == vValue[0].ValueList[2].dataType );

			std::wstring wszSideABitmap;
			if( vValue[0].ValueList[0].pwcsVal )
			{
				wszSideABitmap = vValue[0].ValueList[0].pwcsVal;
			}
			else
			{
#pragma message("JB--Need a specific message here.")
				THROW_NULL_POINTER_EXCEPTION();

			}

			std::wstring wszSideBBitmap;
			if( vValue[0].ValueList[1].pwcsVal )
			{
				wszSideBBitmap = vValue[0].ValueList[1].pwcsVal;
			}
			else
			{
#pragma message("JB--Need a specific message here.")
				THROW_NULL_POINTER_EXCEPTION();

			}

			int iPointSize = vValue[0].ValueList[2].iVal;

			pRet = new CEMSSDBeaconSymbolConfig( wszSideABitmap.c_str(), wszSideBBitmap.c_str(),
												iPointSize );

			if( !pRet )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			for( int i = 0; i < iRet; i++ )
			{
				for( unsigned short s = 0; s < vValue[i].uiValues; s++ )
				{
					if( EMSVARITYPE_DATATYPE_STRING == vValue[i].ValueList[s].dataType )
					{
						if( vValue[i].ValueList[s].pwcsVal )
						{
							CoTaskMemFree( vValue[i].ValueList[s].pwcsVal );
						}
					}
				}

				if( vValue[i].ValueList )
					CoTaskMemFree( vValue[i].ValueList );
			}

		}
	}
	catch( ... )
	{
		if( pRet )
		{
			pRet->Release();
			pRet = 0;
		}

		for( int i = 0; i < iRet; i++ )
		{
			for( unsigned short s = 0; s < vValue[i].uiValues; s++ )
			{
				if( EMSVARITYPE_DATATYPE_STRING == vValue[i].ValueList[s].dataType )
				{
					if( vValue[i].ValueList[s].pwcsVal )
					{
						CoTaskMemFree( vValue[i].ValueList[s].pwcsVal );
					}
				}
			}

			if( vValue[i].ValueList )
				CoTaskMemFree( vValue[i].ValueList );
		}

		if( pCM )
		{
			pCM->Release();
			pCM = 0;
		}

		throw;
	}

	return pRet;
}

CEMSRGBColour* 
CEMSSolutionDisplayConfiguration::GetSatelliteTrackColour()
{
	CEMSRGBColour* pRet = 0;

	IEMSConfigurationManager* pCM = 0;

	const int ciCount = 1;
	EMSCONFIGURATIONITEM vValue[ciCount];
	memset( &vValue, 0, ciCount*sizeof(EMSCONFIGURATIONITEM) );
	int iRet = 0;

	try
	{
		pCM = _GetConfigManager();

		if( !pCM )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		EMS_RESULT hr = pCM->GetEx(ms_cwszSDGroup, ms_cwszSDNoGroupID, &ms_cwszSDSatelliteTrackColour, 
									ciCount, vValue, &iRet );

		if( FAILED(hr) )
		{
#pragma message("JB--Need a specific message here.")
			THROW_RUNTIME_EXCEPTION( hr );
		}

		if( 3 != vValue[0].uiValues )
		{
#pragma message("JB--Need a specific message here.")
			THROW_NULL_POINTER_EXCEPTION();
		}

		_ASSERTE( EMSVARITYPE_DATATYPE_INT == vValue[0].ValueList[0].dataType );
		_ASSERTE( EMSVARITYPE_DATATYPE_INT == vValue[0].ValueList[1].dataType );
		_ASSERTE( EMSVARITYPE_DATATYPE_INT == vValue[0].ValueList[2].dataType );

		pRet = new CEMSRGBColour( vValue[0].ValueList[0].iVal, vValue[0].ValueList[1].iVal,
									vValue[0].ValueList[2].iVal );

		if( !pRet )
		{
			THROW_NOMEMORY_EXCEPTION()
		}

		if( vValue[0].ValueList )
		{
			CoTaskMemFree( vValue[0].ValueList );
			vValue[0].ValueList = 0;
		}

		pCM->Release();
		pCM = 0;

	}
	catch( ... )
	{
		if( pRet )
		{
			pRet->Release();
			pRet = 0;
		}

		if( vValue[0].ValueList )
		{
			CoTaskMemFree( vValue[0].ValueList );
			vValue[0].ValueList = 0;
		}

		if( pCM )
		{
			pCM->Release();
			pCM = 0;
		}

		throw;
	}

	return pRet;
}

CEMSRGBColour* 
CEMSSolutionDisplayConfiguration::GetMutualVisRegionColour()
{
	CEMSRGBColour* pRet = 0;

	IEMSConfigurationManager* pCM = 0;

	const int ciCount = 1;
	EMSCONFIGURATIONITEM vValue[ciCount];
	memset( &vValue, 0, ciCount*sizeof(EMSCONFIGURATIONITEM) );
	int iRet = 0;

	try
	{
		pCM = _GetConfigManager();

		if( !pCM )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		EMS_RESULT hr = pCM->GetEx(ms_cwszSDGroup, ms_cwszSDNoGroupID, &ms_cwszSDMutualVisRegionColour, 
									ciCount, vValue, &iRet );

		if( FAILED(hr) )
		{
#pragma message("JB--Need a specific message here.")
			THROW_RUNTIME_EXCEPTION( hr );
		}

		if( 3 != vValue[0].uiValues )
		{
#pragma message("JB--Need a specific message here.")
			THROW_NULL_POINTER_EXCEPTION();
		}

		_ASSERTE( EMSVARITYPE_DATATYPE_INT == vValue[0].ValueList[0].dataType );
		_ASSERTE( EMSVARITYPE_DATATYPE_INT == vValue[0].ValueList[1].dataType );
		_ASSERTE( EMSVARITYPE_DATATYPE_INT == vValue[0].ValueList[2].dataType );

		pRet = new CEMSRGBColour( vValue[0].ValueList[0].iVal, vValue[0].ValueList[1].iVal,
									vValue[0].ValueList[2].iVal );

		if( !pRet )
		{
			THROW_NOMEMORY_EXCEPTION()
		}

		if( vValue[0].ValueList )
		{
			CoTaskMemFree( vValue[0].ValueList );
			vValue[0].ValueList = 0;
		}

		pCM->Release();
		pCM = 0;

	}
	catch( ... )
	{
		if( pRet )
		{
			pRet->Release();
			pRet = 0;
		}

		if( vValue[0].ValueList )
		{
			CoTaskMemFree( vValue[0].ValueList );
			vValue[0].ValueList = 0;
		}

		if( pCM )
		{
			pCM->Release();
			pCM = 0;
		}

		throw;
	}

	return pRet;
}

ULONG 
CEMSSolutionDisplayConfiguration::GetSatelliteTrackWidth()
{
	ULONG ulRet = 0;

	IEMSConfigurationManager* pCM = 0;

	EMSVARITYPE vValue;
	memset( &vValue, 0, sizeof(EMSVARITYPE) );

	try
	{
		pCM = _GetConfigManager();

		if( !pCM )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		EMS_RESULT hr = pCM->Get(ms_cwszSDGroup, ms_cwszSDNoGroupID, ms_cwszSDSatelliteTrackWidth, 
									&vValue );

		if( FAILED(hr) )
		{
#pragma message("JB--Need a specific message here.")
			THROW_RUNTIME_EXCEPTION( hr );
		}

		_ASSERTE( EMSVARITYPE_DATATYPE_INT == vValue.dataType );

		ulRet = vValue.iVal;

		pCM->Release();
		pCM = 0;

	}
	catch( ... )
	{
		if( pCM )
		{
			pCM->Release();
			pCM = 0;
		}

		throw;
	}

	return ulRet;
}

CEMSSolutionDisplayConfiguration::EMSGEOSETTRANSFORM 
CEMSSolutionDisplayConfiguration::GetGeosetTransform( const wchar_t* cwszGeoset )
{
	EMSGEOSETTRANSFORM strRet;
	memset( &strRet, 0, sizeof(EMSGEOSETTRANSFORM) );

	if( cwszGeoset )
	{
		IEMSConfigurationManager* pCM = 0;

		const int ciItems = 100;
		EMSCONFIGURATIONITEM aItem[ciItems];
		memset( aItem, 0, ciItems*sizeof(EMSCONFIGURATIONITEM) );
		int iItems = 0;

		wchar_t* awszKeys[ciItems];
		memset( awszKeys, 0, sizeof(wchar_t*)*ciItems );
		const int ciMaxKeySize = 64;

		
		try
		{
			for( int i = 0; i < ciItems; i++ )
			{
				awszKeys[i] = new wchar_t[ ciMaxKeySize ];

				if( !awszKeys )
				{
					THROW_NOMEMORY_EXCEPTION();
				}

				std::wstringstream owstrmBufTemp;
				owstrmBufTemp << ms_cwszSDGeosetTransform << L"." << (i+1);

				wcsncpy( awszKeys[i], owstrmBufTemp.str().c_str(), ciMaxKeySize - 1 );
			}

			pCM = _GetConfigManager();

			if( !pCM )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			EMS_RESULT hr = pCM->GetEx(ms_cwszSDGroup, ms_cwszSDNoGroupID, (const wchar_t**) awszKeys, 
										ciItems, aItem, &iItems );

			if( FAILED(hr) && 
				(EMS_CM_NO_DATA != hr)  )
			{
				THROW_RUNTIME_EXCEPTION( hr );
			}

			if( iItems > 0 &&
				aItem )
			{
			
				bool bFound = false;

				for( ULONG l = 0; l < iItems && !bFound; l++ )
				{
					if( 4 == aItem[l].uiValues )
					{
						if( aItem[l].ValueList[0].dataType != EMSVARITYPE_DATATYPE_STRING )
						{
							// Raise an error.  Means incorrect configuration syntax was used.
							THROW_RUNTIME_EXCEPTION( EMS_SYNTAX_ERROR );
						}

						std::wstring owszGeoset = aItem[l].ValueList[0].pwcsVal;
						
						if( 0 == wcsicmp( owszGeoset.c_str(), cwszGeoset ) )
						{
							strRet.dXOffset = aItem[l].ValueList[1].dVal;
							strRet.dXMin = aItem[l].ValueList[2].dVal;
							strRet.dXMax = aItem[l].ValueList[3].dVal;

							bFound = true;
						}
					}
					else
					{
						// Raise an error.  Means incorrect configuration syntax was used.
						THROW_RUNTIME_EXCEPTION( EMS_SYNTAX_ERROR );
					}
				}
			}

			for( ULONG l = 0; l < iItems; l++ )
			{
				for( ULONG k = 0; k < aItem[l].uiValues; k++ )
				{
					if( aItem[l].ValueList[k].dataType == EMSVARITYPE_DATATYPE_STRING )
					{
						CoTaskMemFree( aItem[l].ValueList[k].pwcsVal );
						aItem[l].ValueList[k].pwcsVal = 0;
					}
				}
			}

			for( i = 0; i < ciItems; i++ )
			{
				if( awszKeys[i] )
				{
					delete[] awszKeys[i];
					awszKeys[i] = 0;
				}
			}
	
			pCM->Release();
			pCM = 0;

		}
		catch( ... )
		{
			for( ULONG l = 0; l < iItems; l++ )
			{
				for( ULONG k = 0; k < aItem[l].uiValues; k++ )
				{
					if( aItem[l].ValueList[k].dataType == EMSVARITYPE_DATATYPE_STRING )
					{
						CoTaskMemFree( aItem[l].ValueList[k].pwcsVal );
						aItem[l].ValueList[k].pwcsVal = 0;
					}
				}
			}

			for( int i = 0; i < ciItems; i++ )
			{
				if( awszKeys[i] )
				{
					delete[] awszKeys[i];
					awszKeys[i] = 0;
				}
			}

			if( pCM )
			{
				pCM->Release();
				pCM = 0;
			}

			throw;
		}
	}

	return strRet;
}

std::wstring
CEMSSolutionDisplayConfiguration::_GetBeaconSymbolKey( const wchar_t* cwszBeaconType )
{
	std::wstring wszRet;

	if( 0 == wcsicmp( cwszBeaconType, CEMSBeaconLayerConfigurationAccessor::ms_cwszBeaconType121 ) )
	{
		wszRet = ms_cwszBeacon121BitmapSymbol;
	}
	else if( 0 == wcsicmp( cwszBeaconType, CEMSBeaconLayerConfigurationAccessor::ms_cwszBeaconType243 ) )
	{
		wszRet = ms_cwszBeacon243BitmapSymbol;
	}
	else if( 0 == wcsicmp( cwszBeaconType, CEMSBeaconLayerConfigurationAccessor::ms_cwszBeaconType406 ) )
	{
		wszRet = ms_cwszBeacon406BitmapSymbol;
	}
	else if( 0 == wcsicmp( cwszBeaconType, CEMSBeaconLayerConfigurationAccessor::ms_cwszBeaconType406Interferer ) )
	{
		wszRet = ms_cwszBeacon406InterfererBitmapSymbol;
	}


	return wszRet;
}

IEMSConfigurationManager* 
CEMSSolutionDisplayConfiguration::_GetConfigManager()
{
	IEMSConfigurationManager* pRet = 0;

	// Not caching in case pointer goes bad.  CM is out-of-process.

	HRESULT hr = CoCreateInstance( CLSID_EMSConfigurationManager, 0, CLSCTX_ALL,
								IID_IEMSConfigurationManager, (LPVOID*)&pRet );

	if( FAILED(hr) || !pRet )
	{
#pragma message("JB--Add specific message.")
		THROW_RUNTIME_EXCEPTION( hr );
	}

	return pRet;
}