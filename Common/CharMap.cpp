/********************************************************************
*	Module:			CharMap.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Will remap the characters in a supplied string
*						
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
* Copyright (c) 2005 by EMS Technologies, Inc.,
* All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======
	0.0	02Feb2005		CH		Started

********************************************************************/

#include <assert.h>
#include "emsexcpt.h"
#include "charmap.h"

#include "convutility.h"

EMS_RESULT
CEMSCharMap::LoadMap( LPCTSTR szFilename )
{
	EMS_RESULT	hr = EMS_OK;
	wchar_t		wszLine[1024];
	int			iFrom;
	int			iTo;
	int			iDefault = -1;
	int			iCount = 0;

	FILE*		fp = _tfopen( szFilename, TEXT("r") );
	if ( !fp ) hr = CEMSConversionUtil::ErrnoToEMSResult( errno );

	try
	{
		while ( !feof(fp) && SUCCEEDED(hr) )
		{
			if ( fgetws( wszLine, 1024, fp ) )
			{
				// is this the default?
				if ( wcsncmp( wszLine, L"default=", 8 ) == 0 )
				{
					if ( 1 == swscanf( wszLine, L"default=%x", &iDefault ) )
					{
						if ( m_iDefault >=0 ) 
						{
							hr = EMS_DATA_INVALID;
							break;
						}
						m_iDefault = iDefault;
					}
				}
				else if ( wcsncmp( wszLine, L"{0x", 3 ) == 0 )
				{
					// fragile ... spacing and format cannot change
					if ( 2 == swscanf( wszLine, L"{%x, %x}", &iFrom, &iTo ) )
					{
						m_mapChar.insert( std::pair<int,int>( iFrom, iTo ) );
						iCount++;
					}
					// otherwise ignore
				}
			}
			else if ( ferror(fp) )
			{
				hr = CEMSConversionUtil::ErrnoToEMSResult( errno );
			}
		}

		fclose( fp );

		// was a default specified?
		if ( m_iDefault < 0 )
		{
			// default to a space
			m_iDefault = 0x0020;
		}
	}
	catch( ... )
	{
		if ( fp ) fclose( fp );
		hr = EMS_EXCEPTION;
	}
	return hr;
}

wchar_t
CEMSCharMap::_GetChar( const wchar_t wChar )
{
	wchar_t	wRet;

	std::map<int,int>::iterator itFind = m_mapChar.find( wChar );
	if( itFind != m_mapChar.end()  )
	{
		wRet = itFind->second;
	}
	else
	{
		wRet = m_iDefault;
	}
	return wRet;
}

EMS_RESULT
CEMSCharMap::_RemapString( wchar_t* wszInOut, const int iLen )
{
	assert( wszInOut );
	assert( iLen > 0 );

	for ( int i=0; i<iLen; i++ )
	{
		wszInOut[i] = _GetChar( wszInOut[i] );
	}
	return EMS_OK;
}

EMS_RESULT
CEMSCharMap::RemapString( wchar_t* wszInOut, const int iLen )
{
	return _RemapString( wszInOut, iLen );
}

EMS_RESULT
CEMSCharMap::RemapString( char* szInOut, const int iLen )
{
	assert( szInOut );
	assert( iLen > 0 );

	EMS_RESULT	hr = EMS_OK;
	LPWSTR		wszTemp = new wchar_t[iLen+1];
	if ( !wszTemp )
	{
		hr = EMS_NO_MEMORY;
	}
	try
	{
		memset( wszTemp, 0, (iLen+1)*sizeof(wchar_t) );

		// Convert to wide
		wstring	wstr = CEMSConversionUtil::ConvertToString( szInOut );
		wcsncpy( wszTemp, wstr.c_str(), iLen );

		// remap
		if ( SUCCEEDED(hr = _RemapString( wszTemp, iLen ) ) )
		{
			// revert to char*
			string str = CEMSConversionUtil::ConvertToString( wszTemp );

			strncpy( szInOut, str.c_str(), iLen );
		}
		delete[] wszTemp;
		wszTemp = NULL;
	}
	catch( ... )
	{
		delete[] wszTemp;
		hr = EMS_EXCEPTION;
	}
	return hr;
}

