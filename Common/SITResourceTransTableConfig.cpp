#pragma warning(disable:4786)	// disable compiler warnings for stl debug symbol sizes.

#include "sitresourcetranstableconfig.h"

#include "sitrestranstableconstants.h"
#include "emserror.h"
#include "emsexcpt.h"
#include <string>


CEMSRTTConfig::CEMSRTTConfig()
{
}

CEMSRTTConfig::CEMSRTTConfig( const CEMSRTTConfig& x )
{
}

CEMSRTTConfig::~CEMSRTTConfig()
{
}

void 
CEMSRTTConfig::SetResource( const long clSit, const EMSRESOURCEIDENTIFIER ceResource )
{
	std::map<long,EMSRESOURCEIDENTIFIER>::iterator itFind = m_mapResources.find( clSit );

	if( itFind != m_mapResources.end() )
	{
		itFind->second = ceResource;
	}
	else
	{
		m_mapResources.insert( std::pair<long,EMSRESOURCEIDENTIFIER>( clSit, ceResource ) );
	}

}

EMSRESOURCEIDENTIFIER 
CEMSRTTConfig::GetResource( const long clSit )
{
	EMSRESOURCEIDENTIFIER eResource = EMSRES_UKNOWN;

	std::map<long,EMSRESOURCEIDENTIFIER>::iterator itFind = m_mapResources.find( clSit );

	if( itFind != m_mapResources.end() )
	{
		eResource = itFind->second;
	}

	return eResource;
}

void 
CEMSRTTConfig::Populate( const wchar_t* cwszTable, IEMSConfigurationManager* pConfig )
{
	if( !cwszTable || !pConfig )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	int iCount = 0;
	EMSCONFIGURATIONITEM**  apConfigData   = 0;

	try
	{
		EMS_RESULT hr = pConfig->GetGroup( cwszRTTGroup, cwszTable, &iCount, &apConfigData );

		for( int i = 0; i < iCount; i++ )
		{
			if( !apConfigData[i] )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}
			
			if( !apConfigData[i]->pwcsKeyName )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			if( !apConfigData[i]->uiValues )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			std::wstring wszTemp( apConfigData[i]->pwcsKeyName );

			if( cwszSIT115A == wszTemp )
			{
				SetResource( 0x115A, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT115B == wszTemp )
			{
				SetResource( 0x115B, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT115C == wszTemp )
			{
				SetResource( 0x115C, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT115 == wszTemp )
			{
				SetResource( 115, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT121A == wszTemp )
			{
				SetResource( 0x121A, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT121B == wszTemp )
			{
				SetResource( 0x121B, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT121 == wszTemp )		
			{
				SetResource( 121, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT122A == wszTemp )
			{
				SetResource( 0x122A, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT122B == wszTemp )
			{
				SetResource( 0x122B, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT122C == wszTemp )
			{
				SetResource( 0x122C, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT122E == wszTemp )
			{
				SetResource( 0x122E, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT122 == wszTemp )
			{
				SetResource( 122, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT125A == wszTemp )
			{
				SetResource( 0x125A, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT125B == wszTemp )
			{
				SetResource( 0x125B, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT125 == wszTemp )
			{
				SetResource( 0x125, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT215A == wszTemp )
			{
				SetResource( 0x215A, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT215B == wszTemp )
			{
				SetResource( 0x215B, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT215 == wszTemp )
			{
				SetResource( 215, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT255A == wszTemp )
			{
				SetResource( 0x255A, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT260A == wszTemp )
			{
				SetResource( 0x260A, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT270A == wszTemp )
			{
				SetResource( 0x270A, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT415A == wszTemp )
			{
				SetResource( 0x415A, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT415 == wszTemp )
			{
				SetResource( 415, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT417A == wszTemp )
			{
				SetResource( 0x417A, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT417B == wszTemp )
			{
				SetResource( 0x417B, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT417 == wszTemp )
			{
				SetResource( 417, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT510A == wszTemp )
			{
				SetResource( 0x510A, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT510 == wszTemp )
			{
				SetResource( 510, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT605A == wszTemp )
			{
				SetResource( 0x605A, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT605B == wszTemp )
			{
				SetResource( 0x605B, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT605C == wszTemp )
			{
				SetResource( 0x605C, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT605D == wszTemp )
			{
				SetResource( 0x605D, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT661A == wszTemp )
			{
				SetResource( 0x661A, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT661B == wszTemp )
			{
				SetResource( 0x661B, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT662A == wszTemp )
			{
				SetResource( 0x662A, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT750A == wszTemp )
			{
				SetResource( 0x750A, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT751A == wszTemp )
			{
				SetResource( 0x751A, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT760A == wszTemp )
			{
				SetResource( 0x760A, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT770A == wszTemp )
			{
				SetResource( 0x770A, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT915 == wszTemp )
			{
				SetResource( 915, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}	
			else if( cwszSIT925 == wszTemp )
			{
				SetResource( 925, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT950A == wszTemp )
			{
				SetResource( 0x950A, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			else if( cwszSIT951A == wszTemp )
			{
				SetResource( 0x951A, _GetResourceCode( apConfigData[i]->ValueList[0].pwcsVal ) );
			}
			

		}

		if( apConfigData )
		{
			for( int i = 0; i < iCount; i++ )
			{
				if( apConfigData[i] )
				{
					if( apConfigData[i]->ValueList )
					{
						for( unsigned short i2 = 0; i2 < apConfigData[i]->uiValues; i2++ )
						{
							if( EMSVARITYPE_DATATYPE_STRING == apConfigData[i]->ValueList[i2].dataType )
							{
								if( apConfigData[i]->ValueList[i2].pwcsVal ) 
								{	
									CoTaskMemFree( apConfigData[i]->ValueList[i2].pwcsVal );
									apConfigData[i]->ValueList[i2].pwcsVal = 0;
								}
							}
						}

						CoTaskMemFree( apConfigData[i]->ValueList );
						apConfigData[i]->ValueList = 0;
					}

					CoTaskMemFree( apConfigData[i] );
					apConfigData[i] = 0;
				}
			}

			CoTaskMemFree( apConfigData );
			apConfigData = 0;
		}
		
	}
	catch( ... )
	{
		if( apConfigData )
		{
			for( int i = 0; i < iCount; i++ )
			{
				if( apConfigData[i] )
				{
					if( apConfigData[i]->ValueList )
					{
						for( unsigned short i2 = 0; i2 < apConfigData[i]->uiValues; i2++ )
						{
							if( EMSVARITYPE_DATATYPE_STRING == apConfigData[i]->ValueList[i2].dataType )
							{
								if( apConfigData[i]->ValueList[i2].pwcsVal ) 
								{	
									CoTaskMemFree( apConfigData[i]->ValueList[i2].pwcsVal );
									apConfigData[i]->ValueList[i2].pwcsVal = 0;
								}
							}
						}

						CoTaskMemFree( apConfigData[i]->ValueList );
						apConfigData[i]->ValueList = 0;
					}

					CoTaskMemFree( apConfigData[i] );
					apConfigData[i] = 0;
				}
			}

			CoTaskMemFree( apConfigData );
			apConfigData = 0;
		}

		throw;
	}
}

EMSRESOURCEIDENTIFIER 
CEMSRTTConfig::_GetResourceCode( const wchar_t* cwszResource )
{
	bool bFound = false;
	EMSRESOURCEIDENTIFIER eRet = EMSRES_UKNOWN;
	long i = 0;

	while( caResourceMap[i].wszName && !bFound )
	{
		if( wcsicmp( cwszResource, caResourceMap[i].wszName ) == 0 )
		{
			bFound = true;
			eRet = caResourceMap[i].resID;
		}

		i++;
	}

	return eRet;
}

