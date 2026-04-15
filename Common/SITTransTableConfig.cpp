#pragma warning(disable:4786)	// disable compiler warning for STL debug symbol length

#include "sittranstableconfig.h"

#include <string>
#include "iconfigmanager.h"
#include "sittranstableconstants.h"
#include "emserror.h"
#include "emsexcpt.h"

CEMSSTTConfig::CEMSSTTConfig() : m_eTimeFmt(SIT_TIME_FMT_UNKNOWN)
{
}

CEMSSTTConfig::CEMSSTTConfig( const CEMSSTTConfig& x )
{
}

CEMSSTTConfig::~CEMSSTTConfig()
{
}

void
CEMSSTTConfig::SetTranslation( const long clSitCode, const long clTranslation )
{
	std::map<long,long>::iterator itFind = m_mapTranslationTable.find( clSitCode );

	if( itFind != m_mapTranslationTable.end() )
	{
		itFind->second = clTranslation;
	}
	else
	{
		m_mapTranslationTable.insert( std::pair<long,long>( clSitCode, clTranslation ) );
	}
}

long 
CEMSSTTConfig::GetTranslation( const long clSitCode )
{
	long lRet = 0;

	std::map<long,long>::iterator itFind = m_mapTranslationTable.find( clSitCode );

	if( itFind != m_mapTranslationTable.end()  )
	{
		lRet = itFind->second;
	}

	return lRet;
}

void 
CEMSSTTConfig::Populate( const wchar_t* cwszTable, IEMSConfigurationManager* pConfig )
{
	if( !cwszTable || !pConfig )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	int iCount = 0;
	EMSCONFIGURATIONITEM**  apConfigData   = 0;

	try
	{
		EMS_RESULT hr = pConfig->GetGroup( cwszSTTGroup, cwszTable, &iCount, &apConfigData );

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

			if( std::wstring::npos != wszTemp.find( cwszTime ) )
			{
				if( apConfigData[i]->ValueList[0].pwcsVal )
				{
					if( wcsicmp( apConfigData[i]->ValueList[0].pwcsVal, cwszTimeSID ) == 0 )
					{
						SetTimeFormat( SIT_TIME_FMT_SID );
					}
					else if( wcsicmp( apConfigData[i]->ValueList[0].pwcsVal, cwszTimeExtended ) == 0 )
					{
						SetTimeFormat( SIT_TIME_FMT_EXTENDED );
					}
				}
			}
			else if( std::wstring::npos != wszTemp.find( cwsz115A ) )
			{
				SetTranslation( 0x115A, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz115B ) )
			{
				SetTranslation( 0x115B, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz115C ) )
			{
				SetTranslation( 0x115C, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz115 ) )		// Check must be aftr the extended types.
			{
				SetTranslation( 115, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz121A ) )
			{
				SetTranslation( 0x121A, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz121B ) )
			{
				SetTranslation( 0x121B, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz121 ) )		// Check must be aftr the extended types.
			{
				SetTranslation( 121, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz122A ) )
			{
				SetTranslation( 0x122A, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz122B ) )
			{
				SetTranslation( 0x122B, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz122C ) )
			{
				SetTranslation( 0x122C, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz122E ) )
			{
				SetTranslation( 0x122E, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz122 ) )		// Check must be aftr the extended types.
			{
				SetTranslation( 122, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz125A ) )
			{
				SetTranslation( 0x125A, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz125B ) )
			{
				SetTranslation( 0x125B, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz125 ) )		// Check must be aftr the extended types.
			{
				SetTranslation( 125, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz215A ) )
			{
				SetTranslation( 0x215A, apConfigData[i]->ValueList[0].iVal );
			}
			else if( wszTemp == cwsz165 )
			{
				SetTranslation( 165, apConfigData[i]->ValueList[0].iVal );
			}
			else if( wszTemp == cwsz173 )
			{
				SetTranslation( 173, apConfigData[i]->ValueList[0].iVal );
			}
			else if( wszTemp == cwsz175 )
			{
				SetTranslation( 175, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz215B ) )
			{
				SetTranslation( 0x215B, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz215 ) )		// Check must be aftr the extended types.
			{
				SetTranslation( 215, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz255A ) )
			{
				SetTranslation( 0x255A, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz260A ) )
			{
				SetTranslation( 0x260A, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz270A ) )
			{
				SetTranslation( 0x270A, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz415A ) )
			{
				SetTranslation( 0x415A, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz415 ) )		// Check must be aftr the extended types.
			{
				SetTranslation( 415, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz417A ) )
			{
				SetTranslation( 0x417A, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz417B ) )
			{
				SetTranslation( 0x417B, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz417 ) )		// Check must be aftr the extended types.
			{
				SetTranslation( 417, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz510A ) )
			{
				SetTranslation( 0x510A, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz510 ) )		// Check must be aftr the extended types.
			{
				SetTranslation( 510, apConfigData[i]->ValueList[0].iVal );	
			}
			else if( std::wstring::npos != wszTemp.find( cwsz605A ) )
			{
				SetTranslation( 0x605A, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz605B ) )
			{
				SetTranslation( 0x605B, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz605C ) )
			{
				SetTranslation( 0x605C, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz605D ) )
			{
				SetTranslation( 0x605D, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz661A ) )
			{
				SetTranslation( 0x661A, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz661B ) )
			{
				SetTranslation( 0x661B, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz662A ) )
			{
				SetTranslation( 0x662A, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz750A ) )
			{
				SetTranslation( 0x750A, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz751A ) )
			{
				SetTranslation( 0x751A, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz760A ) )
			{
				SetTranslation( 0x760A, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz770A ) )
			{
				SetTranslation( 0x770A, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz915 ) )
			{
				SetTranslation( 915, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz925 ) )
			{
				SetTranslation( 925, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz950A ) )
			{
				SetTranslation( 0x950A, apConfigData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwsz951A ) )
			{
				SetTranslation( 0x951A, apConfigData[i]->ValueList[0].iVal );
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
