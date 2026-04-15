/********************************************************************
*	Module:			lineterminator.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	The line terminator in a SIT message.
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*					
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

	0.0	2003/02/04		jb		start

********************************************************************/
#ifndef INC_LINETERMINATOR
#define INC_LINETERMINATOR

#include "emserror.h"
#include <tchar.h>

#define clWriteTermMaxLength  8

class CEMSLineTerminator
{
public:
	CEMSLineTerminator( );
	CEMSLineTerminator( CEMSLineTerminator& oLT );
	virtual ~CEMSLineTerminator();

	// Sets an array of valid terminators for use when parsing SITs.
	EMS_RESULT SetValid( const long clCount, TCHAR** alpszTerminators );
	// Adds a valid terminator to the array for use when parsing SITs.
	EMS_RESULT AddValid(  TCHAR* lpszTerminator );
	// Sets the terminator sequence to use when writing.
	EMS_RESULT Use(  TCHAR* lpszTerminator );
	// Retrieves the terminator string for use when writing a SIT.
	TCHAR* WriteEOL();
	// Check if the given string is a valid EOL.
	BOOL IsEOL(  TCHAR* lpszField );
	// Check if the given character is a valid EOL character.
	BOOL IsEOL( TCHAR cValue );
	// Check if the given character fits any of the EOL sequences.
	BOOL MatchesEOLSequence( TCHAR cValue, unsigned long ulPos );
	
private:	// methods
	void _ReleaseTerminators();
	void _ReleaseWriteTerminator();

private: // data
	TCHAR**		m_alpszTerminators;
	long		m_lNumTerminators;
	TCHAR		m_lpszTerminator[ clWriteTermMaxLength ];
	
};

#endif // INC_SITFIELD
