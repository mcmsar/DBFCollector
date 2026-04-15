/*********************************************************************
*	              Copyright (c) 2004 by EMS Technologies, Inc.,
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

#include "uniquefilenameprovider.h"
#include "uniquetimeprovider.h"
#include "convutility.h"
#include <sstream>

std::wstring 
CEMSUniqueFileNameProvider::GetUniqueFileName( const wchar_t* cwszDir, const wchar_t* cwszPrefix )
{
	std::wstringstream owstrmRet;

	// Use a unique time value to ensure that the filename is unique.
	EMSTIME timeUnique = CEMSUniqueTimeProvider::GetInstance()->GetTime();

	if( cwszDir &&
		wcslen(cwszDir) > 0 )
	{
		owstrmRet << cwszDir;
		
		if( L'\\' != owstrmRet.str().at( owstrmRet.str().length() - 1 ) )
			owstrmRet << L"\\";
	}

	if( cwszPrefix && wcslen(cwszPrefix) > 0 )
		owstrmRet << cwszPrefix << L"_";

	owstrmRet << CEMSConversionUtil::ConvertToString( timeUnique.intTime );

	return owstrmRet.str();

}

std::string 
CEMSUniqueFileNameProvider::GetUniqueFileName( const char* cszDir, const char* cszPrefix )
{
	std::stringstream ostrmRet;

	// Use a unique time value to ensure that the filename is unique.
	EMSTIME timeUnique = CEMSUniqueTimeProvider::GetInstance()->GetTime();

	if( cszDir && strlen(cszDir) > 0  )
	{
		ostrmRet << cszDir;
		
		if( '\\' != ostrmRet.str().at( ostrmRet.str().length() - 1 ) )
			ostrmRet << "\\";
	}

	if( cszPrefix && strlen(cszPrefix) > 0 )
		ostrmRet << cszPrefix << "_";

	ostrmRet << CEMSConversionUtil::ConvertToStringA( timeUnique.intTime );

	return ostrmRet.str();
}