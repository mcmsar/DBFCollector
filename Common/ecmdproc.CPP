/********************************************************************
*	Module:			ecmdproc.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	 CEMSCommandProcessor class
*						
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2001 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	01/03/22		rvw	start

********************************************************************/
#include <string.h>
#include "ecmdproc.h"

const char c_szCmdSeperators[] = " ";
const char c_szParamSeperators[] = ",;";

CEMSCommandProcessor::CEMSCommandProcessor( BYTE cCmdType, INT nMaxLength )
	: CEMSCommandSink( cCmdType, nMaxLength )
{
	m_cCmdType = cCmdType;
	m_lpBuffer = new BYTE[ EMS_PIPE_MAX_COMMAND_LENGTH + 1];
	m_lpszCmd = 0;
	m_bSyntaxError = FALSE;

	m_nParamCount = 0;

	for ( int i = 0; i < EMS_MAX_COMMAND_PARAMS; i++ )
	{
		m_lpszParam[ i ] = 0;

		m_lpszValue[ i ] = 0;
	}
}

CEMSCommandProcessor::~CEMSCommandProcessor()
{
	EndCommand();

	if ( m_lpBuffer )
	{
		delete [ ] m_lpBuffer;
		m_lpBuffer = 0;
	}
}

EMS_RESULT CEMSCommandProcessor::ParseCommand( void )
{	
	EMS_RESULT hr = EMS_FALSE;
	LPSTR lpszTokens[ EMS_MAX_COMMAND_PARAMS + 1 ];
	int i, nTokens = 0;

	EndCommand();

	hr = Read( m_lpBuffer, EMS_PIPE_MAX_COMMAND_LENGTH, &m_ulCmdLength );

	if ( ( hr == EMS_OK ) && ( m_ulCmdLength > 1 ) && ( m_lpBuffer[0] == m_cCmdType ) )
	{
		// don't forget the leading BYTE with the destination ID
		LPSTR lpszThisToken = 0;
		LPSTR lpszTempBuffer = new char [ m_ulCmdLength ];

		m_lpBuffer[ m_ulCmdLength ] = 0;

		if ( lpszTempBuffer )
		{
			strcpy( lpszTempBuffer, (LPSTR)&m_lpBuffer[1] );

//			lpszThisToken = strtok( (char*)&m_lpBuffer[1], c_szCmdSeperators );
			lpszThisToken = strtok( lpszTempBuffer, c_szCmdSeperators );

			while ( lpszThisToken )
			{
				if ( nTokens < EMS_MAX_COMMAND_PARAMS + 1 )
				{
					lpszTokens[ nTokens ] = new char [ strlen( lpszThisToken ) + 1 ];

					if ( lpszTokens[ nTokens ] )
						strcpy( lpszTokens[ nTokens ], lpszThisToken );

					nTokens++;
				}

				lpszThisToken = strtok( 0, c_szParamSeperators );
			}
			delete [ ] lpszTempBuffer;
		}

		for ( i = 0; i < nTokens; i++ )
 		{
			if ( i == 0 )
				_ProcessCommand( lpszTokens[i] );
			else
				_ProcessParam( lpszTokens[i] );

			delete [ ] lpszTokens[i];
			lpszTokens[i] = 0;
		}
	}
	else
		hr = EMS_FALSE;

	return hr;
}

EMS_RESULT CEMSCommandProcessor::EndCommand( void )
{	
	EMS_RESULT hr = EMS_OK;
	int i;

	m_bSyntaxError = FALSE;

	m_ulCmdLength = 0;

	for ( i = 0; i < m_nParamCount; i++ )
	{
		if ( m_lpszParam[ i ] )
		{						  
			delete [ ] m_lpszParam[ i ];

			m_lpszParam[ i ] = 0;
		}

		if ( m_lpszValue[ i ] )
		{						  
			delete [ ] m_lpszValue[ i ];

			m_lpszValue[ i ] = 0;
		}
	}

	m_nParamCount = 0;

	if ( m_lpszCmd )
	{
		delete [ ] m_lpszCmd;
		m_lpszCmd = 0;
	}

	return hr;
}

BOOL CEMSCommandProcessor::IsCommand( LPCTSTR lpcszCmd )
{	
	BOOL bYes = FALSE;

	if ( m_lpszCmd && m_ulCmdLength && ( lstrcmpi( lpcszCmd, m_lpszCmd ) == 0 ) )
		bYes = TRUE;

	return bYes;
}

LONG CEMSCommandProcessor::TextParam( LPCTSTR lpcszParam, LPTSTR lpszValue, INT nMaxLen, LPCTSTR lpcszDefault )
{
	LONG lLength = 0;
	BOOL bFound = FALSE;

	if ( lpszValue ) 
		*lpszValue = 0;

	for ( int i = 0; i < m_nParamCount; i++ )
	{
		if ( m_lpszParam[i] && (lstrcmpi( m_lpszParam[i], lpcszParam) == 0 ) )
		{
			if ( lpszValue && m_lpszValue[i] )
			{
				lstrcpyn( lpszValue, m_lpszValue[i], nMaxLen );

				bFound = TRUE;
			}
		}
	}

	if ( lpszValue )
	{
		if ( !bFound )
		{
			lstrcpyn( lpszValue, lpcszDefault, nMaxLen );
		}

		lLength = lstrlen( lpszValue );		
	}

	return lLength;
}

LONG CEMSCommandProcessor::LongParam( LPCTSTR lpcszParam, LONG lDefault )
{
	LONG lValue = lDefault;

	for ( int i = 0; i < m_nParamCount; i++ )
	{
		if ( m_lpszParam[i] && (lstrcmpi( m_lpszParam[i], lpcszParam) == 0 ) )
			lValue = atol( m_lpszValue[i] );
	}

	return lValue;
}

INT CEMSCommandProcessor::IntParam( LPCTSTR lpcszParam, INT nDefault )
{
	return (INT)LongParam( lpcszParam, (LONG)nDefault );
}

BOOL CEMSCommandProcessor::_ProcessCommand( LPSTR lpszCmd )
{
	if ( lpszCmd && *lpszCmd )
	{
		int nLength = strlen( lpszCmd ) + 1;
		if ( m_lpszCmd )
		{
			delete [] m_lpszCmd;
			m_lpszCmd = 0;
		}
		m_lpszCmd = new TCHAR [ nLength ];

		if ( m_lpszCmd )		
		{
			for ( int j = 0; j < nLength; j++ )
				m_lpszCmd[j] = (TCHAR)lpszCmd[j];
		}
	}

	return ( m_lpszCmd != 0 );
}

BOOL CEMSCommandProcessor::_ProcessParam( LPSTR lpszParam )
{
	char szTemp[ EMS_PIPE_MAX_COMMAND_LENGTH + 1];
	LPSTR lpszToken = 0;
	int i,nLength, nCount = 0;

	strcpy( szTemp, lpszParam );

	lpszToken = strtok( szTemp, "= " ); 

	while ( lpszToken )
	{
		switch ( nCount++ )
		{
			case 0: 
				nLength = strlen( lpszToken ) + 1;

				m_lpszParam[ m_nParamCount ] = new TCHAR[ nLength ];

				if ( m_lpszParam[ m_nParamCount ] )
				{
					for ( i = 0; i < nLength; i++ )
					{
						m_lpszParam[ m_nParamCount ][i] = (TCHAR)lpszToken[i];
					}
				}

				m_nParamCount++;
				
				break;

			case 1:
				nLength = strlen( lpszToken ) + 1;

				m_lpszValue[ m_nParamCount - 1] = new TCHAR[ nLength ];

				if ( m_lpszValue[ m_nParamCount - 1 ] )
				{
					for ( i = 0; i < nLength; i++ )
					{
						m_lpszValue[ m_nParamCount - 1 ][i] = (TCHAR)lpszToken[i];
					}
				}
				break;

			default:
				m_bSyntaxError = TRUE;
				break;
		}

		lpszToken = strtok( 0, "=" ); 
	}

	return TRUE;
}

LPCTSTR CEMSCommandProcessor::GetParamName( int nIndex ) 
{ 
	return (( nIndex >= 0 ) && ( nIndex < m_nParamCount ) ) ? (LPCTSTR)m_lpszParam[ nIndex ] : 0;
}

LPCTSTR CEMSCommandProcessor::GetParamValue( int nIndex )
{ 
	return (( nIndex >= 0 ) && ( nIndex < m_nParamCount ) ) ? (LPCTSTR)m_lpszValue[ nIndex ] : 0;
}

LPCSTR CEMSCommandProcessor::GetCmdLine( void )
{
	return ( m_lpBuffer && ( m_ulCmdLength > 1) ) ? (LPCSTR)&m_lpBuffer[1] : 0;
}
