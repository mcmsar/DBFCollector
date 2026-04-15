/********************************************************************
*	Module:			emssitok.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Implementation of SIT Tokenizer class
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

	0.0	2001/07/5	rvw	start

********************************************************************/
#include <stdio.h>

#include "emscom.h"
#include "emstypes.h"
#include "emssit.h"
#include "sittoken.h"

CEMSSitTokenizer::CEMSSitTokenizer( IEMSSeqStream *lpStream )
{
	m_nUnreadValue = -1;
//	m_nUnreadFieldLen = -1;
	m_nUnreadCount = 0;
	m_lpStream = lpStream;

	if ( m_lpStream )
		m_lpStream->AddRef();
}

CEMSSitTokenizer::~CEMSSitTokenizer()
{
	if ( m_lpStream )
	{
		m_lpStream->Release();
		m_lpStream;
	}
}

void CEMSSitTokenizer::SetStream( IEMSSeqStream *lpStream )
{
	if ( lpStream )
		lpStream->AddRef();

	if ( m_lpStream )
		m_lpStream->Release();

	m_lpStream = lpStream;
}


EMS_RESULT CEMSSitTokenizer::ReadChar( TCHAR *lpcValue )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpcValue )
	{
		if ( m_nUnreadValue == -1 )
		{
			ULONG ulCount = 0;
			BYTE cByte = 0;

			if ( m_lpStream )
			{
				hr = m_lpStream->Read( &cByte, 1, &ulCount );

				if ( ( hr == EMS_OK ) && ( ulCount == 1 ) )
					*lpcValue = (int)cByte;
				else
					*lpcValue = 0;
			}
			else
				hr = EMS_INVALID_STREAM;
		}
		else
		{
			*lpcValue = (TCHAR)m_nUnreadValue;

			m_nUnreadValue = -1;
		}
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSSitTokenizer::UnReadChar( TCHAR cValue )
{
	EMS_RESULT hr = EMS_OK;

	if ( m_nUnreadValue == -1 )
		m_nUnreadValue = ( int )cValue;
	else
		hr = EMS_FALSE;

	return hr;
}

void CEMSSitTokenizer::ResetUnReadFields( void )
{
	m_nUnreadCount = 0;
}

EMS_RESULT CEMSSitTokenizer::UnReadField( LPTSTR lpszBuffer, ULONG ulLen )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpszBuffer && ulLen )
	{
		if ( m_nUnreadCount < EMS_MAX_SIT_FIELDS_UNREAD )
		{
			if ( ulLen < EMS_MAX_SIT_LINE_LENGTH )
			{
				memcpy( m_unreadFld[ m_nUnreadCount ].szText, lpszBuffer, 
											sizeof( lpszBuffer[0] ) * ( ulLen + 1 ) );

				m_unreadFld[ m_nUnreadCount].nLength = ulLen;

				m_nUnreadCount++;
			}
			else
				hr = EMS_LINE_LIMIT_EXCEEDED;
		}
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

EMS_RESULT CEMSSitTokenizer::_AppendChar( int nByte, LPTSTR lpszBuffer, ULONG ulMaxLen, ULONG *lpulCount )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpszBuffer && lpulCount && ( *lpulCount < ulMaxLen ) && ( nByte != -1 ) )
	{
		lpszBuffer[ *lpulCount ] = (TCHAR)nByte;

		if ( nByte != 0 )
			(*lpulCount)++;
	}
	else
		hr = EMS_FALSE;

	return hr;
}

EMS_RESULT CEMSSitTokenizer::ReadField( LPTSTR lpszBuffer, ULONG ulMaxLen, ULONG *lpulCount )
{
	EMS_RESULT hr = EMS_OK;
	ULONG ulCount = 0, ulLength=0;
	TCHAR cByte, cTerminatorByte=0;
	int nFirstByte = -1, nByte = -1;
	BOOL bDone = FALSE;

	if ( lpszBuffer && ulMaxLen )
	{
		if ( m_nUnreadCount > 0 )
		{
			m_nUnreadCount--;

			memcpy( lpszBuffer, m_unreadFld[ m_nUnreadCount].szText, 
				sizeof( lpszBuffer[0] ) * ( m_unreadFld[ m_nUnreadCount].nLength + 1 ) );

			ulLength = m_unreadFld[ m_nUnreadCount ].nLength;
		}
		else 	if ( m_lpStream )
		{
			BOOL bFirstIsEOL = FALSE;
			while ( nByte != 0 )
			{
				hr = ReadChar( &cByte );

				nByte = ( hr == EMS_OK ) ? (int)cByte : 0;

				if( EMS_EOF == hr )
				{
					nByte = 0;
					hr = EMS_OK;
				}
				
				if ( nFirstByte == -1 )
				{
				 	_AppendChar( nByte ,lpszBuffer, ulMaxLen, &ulLength );

					nFirstByte = nByte;

					bFirstIsEOL = m_LT.IsEOL( nFirstByte );
				}
				else 
				{
					if( m_LT.IsEOL( nByte ) )
					{
						if( bFirstIsEOL )
						{
							// If the current field being read began with a character belonging to a 
							// valid EOL sequence then continue to read the whole sequence.
							_AppendChar( nByte, lpszBuffer, ulMaxLen, &ulLength );
						}
						else
						{
							// End of current field.  Stop reading.
							_AppendChar( 0, lpszBuffer, ulMaxLen, &ulLength );
							UnReadChar( cByte );
							nByte = 0;
						}
					}
					else
					{
						// If the first byte was an EOL character and this one is not then
						// we've reached the end of the EOL sequence.
						if( bFirstIsEOL )
						{
							_AppendChar( 0, lpszBuffer, ulMaxLen, &ulLength );
							UnReadChar( cByte );
							nByte = 0;
						}
						else
						{
							switch ( nByte )
							{
								case 0:
									_AppendChar( 0 ,lpszBuffer, ulMaxLen, &ulLength );
									break;

								case '/':	
									_AppendChar( 0 ,lpszBuffer, ulMaxLen, &ulLength );

									UnReadChar( nByte );
									nByte = 0;
									break;

/*								case 13:	// terminator unless this is NL field

									if ( nFirstByte == 13 )
										_AppendChar( 13, lpszBuffer, ulMaxLen, &ulLength );
									else
									{
										_AppendChar( 0 ,lpszBuffer, ulMaxLen, &ulLength );
										UnReadChar( cByte );
										nByte = 0;
									}
									break;

								case 10:
									_AppendChar( 10 ,lpszBuffer, ulMaxLen, &ulLength );

									_AppendChar( 0 ,lpszBuffer, ulMaxLen, &ulLength );

									nByte = 0;
									break;
*/
								default:
									_AppendChar( nByte ,lpszBuffer, ulMaxLen, &ulLength );
									break;
							}
						}
					}
				}
			}
		}
		else
			hr = EMS_INVALID_STREAM;
	}
	else
		hr = EMS_BAD_PARAM;

	if ( lpulCount )
		*lpulCount = ulLength;

	return ( ulLength ) ? hr : EMS_EOF;
}

EMS_RESULT CEMSSitTokenizer::_FlushEOL( void )
{
	EMS_RESULT hr = EMS_OK;
	TCHAR cChar;

	BOOL bEOL = TRUE;
	while( bEOL && SUCCEEDED(hr) )
	{
		// Keep reading until characters no longer match any valid EOL characters.
		hr = ReadChar( &cChar );

		if( EMS_OK == hr )
		{
			if( !m_LT.IsEOL( cChar ) )
			{
				bEOL = FALSE;

				// Because it was necesary to read ahead, set the next character processed to be
				// the one just read.
				UnReadChar( cChar );
			}
		}
	}

	return hr;
}

EMS_RESULT CEMSSitTokenizer::ReadLine( LPTSTR lpszBuffer, ULONG ulMaxLen, ULONG *lpulCount )
{
	EMS_RESULT hr = EMS_OK;
	ULONG ulCount = 0;
	TCHAR cChar; //, cNextChar;
	BOOL bDone=FALSE;

	if ( m_lpStream )
	{
		hr = ReadChar( &cChar );

		while ( ( hr == EMS_OK  ) && !bDone ) 
		{
			if ( ulCount < ulMaxLen )
			{
				// For now, any character that can be found in the valid EOL sequences
				// is considered the end of line.
				if( m_LT.IsEOL( cChar ) )
				{
					// Current character matches the start of a valid EOL sequence.
					lpszBuffer[ ulCount ] = 0;

					hr = _FlushEOL( );

					bDone = TRUE;
				}
				else
				{
					lpszBuffer[ ulCount++ ] = cChar;
				}
			}
			else
				hr = EMS_OVERFLOW;

			if ( !bDone )
				hr = ReadChar( &cChar );
		}
	}
	else
		hr = EMS_INVALID_STREAM;

	if ( lpulCount )
		*lpulCount = ulCount;

	return hr;
}

EMS_RESULT CEMSSitTokenizer::ReadAllText( std::string& roszAll )
{
	EMS_RESULT hr = EMS_OK;

	if( m_lpStream )
	{
		ULONG ulCount = 0;

		do
		{
			char aChar[1024];
			memset( aChar, 0, sizeof(aChar));

			hr = m_lpStream->Read( (BYTE*) aChar, sizeof(aChar)-1, &ulCount );

			if( (EMS_OK == hr) && (ulCount > 0))
				roszAll.append(aChar);

		} while( (ulCount > 0) && (EMS_OK == hr) );

		if( EMS_EOF == hr )
			hr = EMS_OK;
	}
	else
	{
		hr = EMS_INVALID_STREAM;
	}

	return hr;
}