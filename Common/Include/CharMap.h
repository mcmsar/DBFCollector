/********************************************************************
*	Module:			CharMap.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Holds a character mapping and can apply it to 
*					a supplied string.
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
#ifndef _EMS_CHAR_MAP_H
#define _EMS_CHAR_MAP_H

#pragma warning( disable : 4786)

#include <string>
using std::wstring;

#include <map>
using std::map;

#include "emserror.h"


// Work in Unicode for unambiguous results
class CEMSCharMap
{
public:
	CEMSCharMap() : m_iDefault(-1) {}
	~CEMSCharMap() {};

	EMS_RESULT	LoadMap( LPCTSTR szFilename );

	EMS_RESULT	RemapString( wchar_t* wszInOut, const int iLen );
	EMS_RESULT	RemapString( char* szInOut, const int iLen );

private:
	wchar_t		_GetChar( const wchar_t wChar );
	EMS_RESULT	_RemapString( wchar_t* wszIn, const int iLen );

	std::map<int,int>	m_mapChar;
	int					m_iDefault;
};

#endif // _EMS_CHAR_MAP_H
