/******************************************************************** 
*	Module:			captread.cpp 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	CEMSCaptureFileReader
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
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

	0.0	2003 June 18 rvw	start

********************************************************************/
#include <stdio.h>

#define EMSERROR_NODEFINE_TYPES		// prevent annoying Windows dupl defintions

#include "captread.h"
#include "leodefns.h"
#include "leostats.h"				// EMSLEOSTATUSUPDATE

const WORD 	c_wCurrentVersion = MAKEWORD( 0, 1 );	// 1.0

CEMSCaptureFileReader::CEMSCaptureFileReader()
{
	m_wCurrentVersion = c_wCurrentVersion;
	m_wOverrideVersion = 0;
	m_lpcBuffer = 0;
	m_nMaxRecLength = 0;
}

CEMSCaptureFileReader::~CEMSCaptureFileReader()
{
	Reset();
}

EMS_RESULT CEMSCaptureFileReader::Initialize( int nMaxRecLen )
{
	EMS_RESULT hr = EMS_OK;

	if ( m_nMaxRecLength != nMaxRecLen )
	{
		Reset();

		if ( nMaxRecLen > 0 )
		{
			m_lpcBuffer = new BYTE[ nMaxRecLen ];

			if ( m_lpcBuffer )
				m_nMaxRecLength = nMaxRecLen;
			else
				hr = EMS_NO_MEMORY;
		}
	}

	if ( hr == EMS_OK )
		hr = _Init( );

	return hr;
}

EMS_RESULT CEMSCaptureFileReader::_Init( void )
{
	EMS_RESULT hr = EMS_OK;

	m_nMaxRecLengthRead = 0;

	m_nRecordsRead = 0;

	memset( m_bDataPresent, 0, sizeof( m_bDataPresent ) );

	return hr;
}

EMS_RESULT CEMSCaptureFileReader::Reset( void )
{
	EMS_RESULT hr = EMS_OK;

	if ( m_lpcBuffer )
	{
		delete [ ] m_lpcBuffer;
		m_lpcBuffer = 0;
	}

	m_nMaxRecLength = 0;

	return hr;
}

EMS_RESULT CEMSCaptureFileReader::ProcessFile( LPCTSTR lpcszFilespec, CEMSCaptureRecordProcessor *lpProcessor )
{
	EMS_RESULT hr = EMS_OK;

	_Init( );

	if ( lpcszFilespec && *lpcszFilespec )
	{
		EMSFILESIGNATURE fileSign;
		FILE *lpFile = 0;
		int nRetcode = 0;
		DWORD dwCurrentOffset = 0;

		lpFile = fopen( lpcszFilespec, "rb" );

		if ( lpFile )
		{
			nRetcode = fread( &fileSign, sizeof( fileSign ), 1, lpFile );

			if ( memcmp( fileSign.cEMS, "EMScaptr", 8 ) == 0 )
			{
			}
			else
				hr = EMS_UNKNOWN_ERROR;

			dwCurrentOffset += sizeof( fileSign );

			while ( hr == EMS_OK )
			{
				if ( lpProcessor )
				{
					EMSCHANNELSIGNATURE *lpChannelSign = (EMSCHANNELSIGNATURE*)m_lpcBuffer;
					LPBYTE lpRecord = m_lpcBuffer + sizeof( EMSCHANNELSIGNATURE );

					nRetcode = fread( lpChannelSign, sizeof( EMSCHANNELSIGNATURE ), 1, lpFile );

					if ( nRetcode == 1 )
					{
						switch ( lpChannelSign->wChannel )
						{
							case LEO_SOLUTION_DATA:
								lpChannelSign->wChannel = LEO_LOCATE_DATA;
								break;

							case 0:	// chance to fix bugs in DBUTIL
								if ( lpChannelSign->nRecLength == sizeof( EMSLEOSTATUSUPDATE ) )
									lpChannelSign->wChannel = LEO_STATUS_DATA;
								break;

							default:
								break;
						}

						if ( lpChannelSign->nRecLength )
						{
							nRetcode = fread( lpRecord, lpChannelSign->nRecLength, 1, lpFile );
						}

						if ( nRetcode == 1 )
						{
							lpProcessor->SetFileOffset( dwCurrentOffset );

							hr = lpProcessor->OnCaptureRecord( lpChannelSign->wChannel, 
														lpChannelSign->version.wNumber, 
														lpChannelSign->nRecLength, lpRecord );

							dwCurrentOffset += sizeof( EMSCHANNELSIGNATURE );

							dwCurrentOffset += lpChannelSign->nRecLength;
						}							
						else
							hr = EMS_IO_ERROR;
					}
					else
						hr = EMS_EOF;
				}
			}
			if ( EMS_EOF == hr )
				hr = EMS_OK;

			fclose( lpFile );
		}
		else
		{
			hr = HRESULT_FROM_WIN32( GetLastError() );
		}
	}
	else
		hr = EMS_BAD_PARAM;

	return hr;
}

