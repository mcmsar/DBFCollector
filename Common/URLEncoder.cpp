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

	$Log:
	$
********************************************************************/

#include "urlencoder.h"
#include <sstream>

const EMSENCODINGTABLE CEMSURLEncoder::ms_caEncoding[] = {	{ L"=", L"%3D" },
															{ L"$", L"%24" },
															{ L"&", L"%26" }, 
															{ L"+", L"%2B" },
															{ L",", L"%2C" },
															{ L"/", L"%2F" },
															{ L":", L"%3A" },
															{ L";", L"%3B" },
															
															{ L"?", L"%3F" },
															{ L"@", L"%40" }
														};

CEMSURLEncoder::CEMSURLEncoder()
{
}

CEMSURLEncoder::CEMSURLEncoder( const CEMSURLEncoder& x )
{
}

CEMSURLEncoder::~CEMSURLEncoder()
{
}

std::wstring 
CEMSURLEncoder::Encode( const wchar_t* cwszSrc )
{
	std::wstringstream wstrmRet;

	if( cwszSrc )
	{
		for( long l = 0; l < wcslen( cwszSrc ); l ++ )
		{
			wstrmRet << _Encode( cwszSrc[l] );
		}
	}

	return wstrmRet.str();
}

std::wstring 
CEMSURLEncoder::Decode( const wchar_t* cwszSrc )
{
	std::wstring owszSrc;

	if( cwszSrc )
	{
		// Search string for all sequences of encoded values and
		// replace them.
		owszSrc = cwszSrc;

		for( long l = 0; l < sizeof( ms_caEncoding ) / sizeof(EMSENCODINGTABLE); l++ )
		{
			bool bFound = true;
			while( bFound )
			{
				std::wstring::size_type iPos = owszSrc.find( ms_caEncoding[l].wEncodedValue );

				if( std::wstring::npos != iPos )
				{
					bFound = true;
					// Do a replacement
					owszSrc.erase( iPos, wcslen(ms_caEncoding[l].wEncodedValue) );
					owszSrc.insert( iPos, ms_caEncoding[l].wCharacter );
				}
				else
					bFound = false;
			}
		}
	}

	return owszSrc;
}

std::wstring
CEMSURLEncoder::_Encode( const wchar_t cwChar )
{
	std::wstringstream owszRet;

	bool bFound = false;
	for( int i = 0; i < sizeof( ms_caEncoding ) / sizeof(EMSENCODINGTABLE) &&!bFound; i++ )
	{
		if( cwChar == ms_caEncoding[i].wCharacter[0] )
		{
			bFound = true;
			owszRet << ms_caEncoding[i].wEncodedValue;
		}
	}

	if( !bFound )
		owszRet << cwChar;

	return owszRet.str();
}
