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

#include "iniconfig.h"
#include "emsexcpt.h"

#ifdef WIN32
#pragma warning(disable:4250)
#pragma warning(disable:4251)
#include <windows.h>
#endif

const char* CEMSINIConfig::ms_cszLogger = "INIConfig";

CEMSINIConfig::CEMSINIConfig()
{
	m_pLogger = log4cxx::Logger::getLogger( ms_cszLogger );
}

CEMSINIConfig::CEMSINIConfig( const CEMSINIConfig& x ) : m_oszSourceFile(x.m_oszSourceFile), 
														m_pLogger(x.m_pLogger)
{
}

CEMSINIConfig::~CEMSINIConfig()
{
}

void 
CEMSINIConfig::SetSourceFile( const char* cszFilePath )
{
	if( cszFilePath )
	{
		m_oszSourceFile = cszFilePath;
		_DoAudit();
	}
}

void
CEMSINIConfig::AuditSection( const char* cszSection )
{
	const int iSize = 32768;
	char szBuffer[ iSize ];
	memset( szBuffer, 0, iSize );

	DWORD dwRet = GetPrivateProfileSectionA( cszSection, szBuffer, iSize - 1, m_oszSourceFile.c_str() );

	if( dwRet == ( iSize - 1 ) - 2 )
	{
		LOG4CXX_ERROR( _GetLogger(), "Error reading configuration for section " << cszSection << ".  Read buffer not large enough." );
		throw CEMSException();
	}

	LogIt( dwRet, szBuffer, cszSection );
}


void
CEMSINIConfig::LogIt( const DWORD cdwCharacters, const char* cszBuffer, const char* cszSection )
{

	if( cdwCharacters > 0 && cszBuffer )
	{
		const char* cszCurrent = cszBuffer;

		while( cszCurrent && ( ( cszCurrent - cszBuffer ) < cdwCharacters ) )
		{
			LOG4CXX_INFO( _GetLogger(), "Configuration audit:  [" << cszSection << "]." << cszCurrent );

			cszCurrent += strlen(cszCurrent) + 1;
		}
	}
}

CEMSObjectList<std::string>
CEMSINIConfig::GetSectionNames()
{
	CEMSObjectList<std::string> olstRet;

	const int iSize = 32768;
	char szBuffer[ iSize ];
	memset( szBuffer, 0, iSize );

	DWORD dwRet = GetPrivateProfileSectionNames( szBuffer, iSize - 1, m_oszSourceFile.c_str() );

	if( dwRet == ( iSize - 1 ) - 2 )
	{
		LOG4CXX_ERROR( _GetLogger(), "Error reading section names.  Read buffer not large enough." );
		throw CEMSException();
	}

	if( dwRet > 0 )
	{
		const char* cszCurrent = szBuffer;

		while( cszCurrent && ( ( cszCurrent - szBuffer ) < dwRet ) )
		{
			olstRet.Add( std::string( cszCurrent ) );		

			cszCurrent += strlen(cszCurrent) + 1;
		}
	}

	return olstRet;
}

std::string 
CEMSINIConfig::GetValue( const char* cszSection, const char* cszKey )
{
	std::string oszRet;

	if( cszSection && cszKey )
	{
		const int iSize = 32768;
		char szBuffer[ iSize ];
		memset( szBuffer, 0, iSize );

		DWORD dwRet = GetPrivateProfileStringA( cszSection, cszKey, NULL, szBuffer, iSize - 1, m_oszSourceFile.c_str() );

		if( dwRet == ( iSize - 1 ) - 2 ||
			dwRet == ( iSize - 1 ) - 1 )
		{
			LOG4CXX_ERROR( _GetLogger(), "Error reading configuration for section=" << cszSection << "key=" << cszKey << ".  Read buffer not large enough." );
			throw CEMSException();
		}

		if( dwRet > 0 )
			oszRet = szBuffer;
	}

	return oszRet;
}

int 
CEMSINIConfig::GetValueInt( const char* cszSection, const char* cszKey )
{
	int iRet = 0;

	std::string oszValue = GetValue( cszSection, cszKey );

	if( !oszValue.empty() )
	{
		iRet = strtol( oszValue.c_str(), 0, 10 );
	}

	return iRet;
}

ULONG 
CEMSINIConfig::GetValueULong( const char* cszSection, const char* cszKey )
{
	ULONG ulRet = 0;

	std::string oszValue = GetValue( cszSection, cszKey );

	if( !oszValue.empty() )
	{
		ulRet = strtoul( oszValue.c_str(), 0, 10 );
	}

	return ulRet;
}

short 
CEMSINIConfig::GetValueShort( const char* cszSection, const char* cszKey )
{
	short sRet = 0;

	std::string oszValue = GetValue( cszSection, cszKey );

	if( !oszValue.empty() )
	{
		sRet = (short) strtol( oszValue.c_str(), 0, 10 );
	}

	return sRet;
}

double 
CEMSINIConfig::GetValueDouble( const char* cszSection, const char* cszKey )
{
	double dRet = 0.0;

	std::string oszValue = GetValue( cszSection, cszKey );

	if( !oszValue.empty() )
	{
		dRet = strtod( oszValue.c_str(), NULL );
	}

	return dRet;
}

CEMSObjectList<std::string> 
CEMSINIConfig::GetSection( const char* cszSection )
{
	CEMSObjectList<std::string> olstRet;

	if( cszSection )
	{
		const int iSize = 32768;
		char szBuffer[ iSize ];
		memset( szBuffer, 0, iSize );

		DWORD dwRet = GetPrivateProfileSectionA( cszSection, szBuffer, iSize - 1, m_oszSourceFile.c_str() );

		if( dwRet == ( iSize - 1 ) - 2 )
		{
			LOG4CXX_ERROR( _GetLogger(), "Error reading configuration for section " << cszSection << ".  Read buffer not large enough." );
			throw CEMSException();
		}

		if( dwRet > 0 )
		{
			const char* cszCurrent = szBuffer;

			while( cszCurrent && ( ( cszCurrent - szBuffer ) < dwRet ) )
			{
				if( cszCurrent )
					olstRet.Add( std::string( cszCurrent ) );

				cszCurrent += strlen(cszCurrent) + 1;
			}
		}
	}

	return olstRet;
}

void 
CEMSINIConfig::SetValue( const char* cszSection, const char* cszKey, const char* cszValue )
{
	if( cszSection && cszValue )
	{
		if( !WritePrivateProfileStringA( cszSection, cszKey, cszValue, m_oszSourceFile.c_str() ) )
		{
			LOG4CXX_ERROR( _GetLogger(), "Error writing configuration for section=" << cszSection << ", key= " << (cszKey ? cszKey : "none") << ".  GetLastError returns " << GetLastError() << "."  );
			throw CEMSException();
		}
	}
}

bool 
CEMSINIConfig::GetValueBoolean( const char* cszSection, const char* cszKey )
{
	bool bRet = false;

	std::string oszValue = GetValue( cszSection, cszKey );

	if( !oszValue.empty() )
	{
		if( 0 == stricmp( oszValue.c_str(), "true" ) ||
			0 == stricmp( oszValue.c_str(), "yes" ) )
		{
			bRet = true;
		}
	}

	return bRet;
}