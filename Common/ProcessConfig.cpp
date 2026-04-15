
#include "processconfig.h"
#include "iconfigmanager.h"
#include "emserror.h"
#include "emsexcpt.h"
#include "processconfigconstants.h"
#include <string>

CEMSProcessConfig::CEMSProcessConfig() : m_wszSITOutDir(0), m_wszProcessingDir(0),
										m_wszBinaryProcessedDir(0),
										m_bSerializedMode(true), m_lCmdTimeout(0),
										m_bSitPassThrough(false), m_ulThisLutID(0),
										m_iSOAPPort(0), m_iMaxBackLog(0), m_lHandlerThreads(0),
										m_wszSITUndeliveredDir(0)
{
}

CEMSProcessConfig::CEMSProcessConfig( const CEMSProcessConfig& x ) : m_wszSITOutDir(0), m_wszProcessingDir(0),
																	m_wszBinaryProcessedDir(0),
																	m_bSerializedMode(true), m_lCmdTimeout(0),
																	m_bSitPassThrough(false), m_ulThisLutID(0),
																	m_iSOAPPort(0), m_iMaxBackLog(0),
																	m_lHandlerThreads(0), m_wszSITUndeliveredDir(0)
{
	_SetString( m_wszSITOutDir, x.m_wszSITOutDir );
	_SetString( m_wszSITUndeliveredDir, x.m_wszSITUndeliveredDir );
	_SetString( m_wszProcessingDir, x.m_wszProcessingDir );
	_SetString( m_wszBinaryProcessedDir, x.m_wszBinaryProcessedDir );

	m_bSerializedMode = x.m_bSerializedMode;
	m_lCmdTimeout = x.m_lCmdTimeout;
	m_bSitPassThrough = x.m_bSitPassThrough;
	m_ulThisLutID = x.m_ulThisLutID;
	m_iSOAPPort = x.m_iSOAPPort;
	m_iMaxBackLog = x.m_iMaxBackLog;
	m_lHandlerThreads = x.m_lHandlerThreads;
}

CEMSProcessConfig::~CEMSProcessConfig()
{
	if( m_wszSITOutDir )
	{
		delete[] m_wszSITOutDir;
		m_wszSITOutDir = 0;
	}

	if( m_wszSITUndeliveredDir )
	{
		delete[] m_wszSITUndeliveredDir;
		m_wszSITUndeliveredDir = 0;
	}

	if( m_wszProcessingDir )
	{
		delete[] m_wszProcessingDir;
		m_wszProcessingDir = 0;
	}

	if( m_wszBinaryProcessedDir )
	{
		delete[] m_wszBinaryProcessedDir;
		m_wszBinaryProcessedDir = 0;
	}
}

void 
CEMSProcessConfig::SetSITOutDirectory( const wchar_t* cwszDir )
{
	_SetString( m_wszSITOutDir, cwszDir );
}

wchar_t* 
CEMSProcessConfig::GetSITOutDirectory()
{
	wchar_t* wszRet = 0;

	_SetString( wszRet, m_wszSITOutDir );

	return wszRet;
}

void 
CEMSProcessConfig::SetSITUndeliveredDirectory( const wchar_t* cwszDir )
{
	_SetString( m_wszSITUndeliveredDir, cwszDir );
}

wchar_t* 
CEMSProcessConfig::GetSITUndeliveredDirectory()
{
	wchar_t* wszRet = 0;

	_SetString( wszRet, m_wszSITUndeliveredDir );

	return wszRet;
}

void 
CEMSProcessConfig::SetProcessingDirectory( const wchar_t* cwszDir )
{
	_SetString( m_wszProcessingDir, cwszDir );
}

wchar_t* 
CEMSProcessConfig::GetProcessingDirectory()
{
	wchar_t* wszRet = 0;

	_SetString( wszRet, m_wszProcessingDir );

	return wszRet;
}

void 
CEMSProcessConfig::SetProcessedBinaryDirectory( const wchar_t* cwszDir )
{
	_SetString( m_wszBinaryProcessedDir, cwszDir );
}

wchar_t* 
CEMSProcessConfig::GetProcessedBinaryDirectory()
{
	wchar_t* wszRet = 0;

	_SetString( wszRet, m_wszBinaryProcessedDir );

	return wszRet;
}

void 
CEMSProcessConfig::Populate( IEMSConfigurationManager* pConfig )
{
	if( !pConfig )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	int iCount = 0;
	EMSCONFIGURATIONITEM** apData   = 0;

	try
	{
		EMS_RESULT hr = pConfig->GetGroup( cwszProcessGroup, c_pwcsNoGroupID, &iCount, &apData );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		for( int i = 0; i < iCount; i++ )
		{
			if( !apData[i] )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}
			
			if( !apData[i]->pwcsKeyName )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			if( !apData[i]->uiValues )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			std::wstring wszTemp( apData[i]->pwcsKeyName );

			if( std::wstring::npos != wszTemp.find( cwszDataDirectorySend ) )
			{
				SetSITOutDirectory( apData[i]->ValueList[0].pwcsVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwszDataDirectoryUndelivered ) )
			{
				SetSITUndeliveredDirectory( apData[i]->ValueList[0].pwcsVal );
			}
			else if( cwszDataDirectoryProcessing == wszTemp )
			{
				SetProcessingDirectory( apData[i]->ValueList[0].pwcsVal );
			}
			else if( cwszDataDirectoryProcessedBinary == wszTemp )
			{
				SetProcessedBinaryDirectory( apData[i]->ValueList[0].pwcsVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwszSerializedMode ) )
			{
				SetSerializedMode( (1 == apData[i]->ValueList[0].bVal) ? true : false );
			}
			else if( std::wstring::npos != wszTemp.find( cwszCommandTimeout ) )
			{
				SetCommandTimeout( apData[i]->ValueList[0].iVal );
			}
			else if( std::wstring::npos != wszTemp.find( cwszSitPassThrough ) )
			{
				SetSitGtwyPassThrough( (1 == apData[i]->ValueList[0].bVal) ? true : false );
			}
			else if( cwszSOAPServerPort == wszTemp )
			{
				SetSOAPPort( apData[i]->ValueList[0].iVal );
			}
			else if( cwszSOAPServerBacklogSize == wszTemp )
			{
				SetSOAPBackLogSize( apData[i]->ValueList[0].iVal );
			}
			else if( cwszLutID == wszTemp )
			{
				SetThisLutID( apData[i]->ValueList[0].uiVal );
			}
			else if( cwszSOAPServerHandlerThreads == wszTemp )
			{
				SetNumSOAPHandlerThreads(  apData[i]->ValueList[0].iVal );
			}
		}

		if( apData )
		{
			for( int i = 0; i < iCount; i++ )
			{
				if( apData[i] )
				{
					if( apData[i]->ValueList )
					{
						for( unsigned short i2 = 0; i2 < apData[i]->uiValues; i2++ )
						{
							if( EMSVARITYPE_DATATYPE_STRING == apData[i]->ValueList[i2].dataType )
							{
								if( apData[i]->ValueList[i2].pwcsVal ) 
								{	
									CoTaskMemFree( apData[i]->ValueList[i2].pwcsVal );
									apData[i]->ValueList[i2].pwcsVal = 0;
								}
							}
						}

						CoTaskMemFree( apData[i]->ValueList );
						apData[i]->ValueList = 0;
					}

					CoTaskMemFree( apData[i] );
					apData[i] = 0;
				}
			}

			CoTaskMemFree( apData );
			apData = 0;
		}


	}
	catch( ... )
	{
		if( apData )
		{
			for( int i = 0; i < iCount; i++ )
			{
				if( apData[i] )
				{
					if( apData[i]->ValueList )
					{
						for( unsigned short i2 = 0; i2 < apData[i]->uiValues; i2++ )
						{
							if( EMSVARITYPE_DATATYPE_STRING == apData[i]->ValueList[i2].dataType )
							{
								if( apData[i]->ValueList[i2].pwcsVal ) 
								{	
									CoTaskMemFree( apData[i]->ValueList[i2].pwcsVal );
									apData[i]->ValueList[i2].pwcsVal = 0;
								}
							}
						}

						CoTaskMemFree( apData[i]->ValueList );
						apData[i]->ValueList = 0;
					}

					CoTaskMemFree( apData[i] );
					apData[i] = 0;
				}
			}

			CoTaskMemFree( apData );
			apData = 0;
		}

		throw;
	}

}