/********************************************************************
*	Module:			EMSMutex.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	Interface to CEMSMutex class
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

	0.0	2001 Apr 10	rvw	start

********************************************************************/
#ifndef INC_EMSMUTEX
#define INC_EMSMUTEX

#include "emstypes.h"
#include "emserror.h"

class CEMSMutex
{
public:
	CEMSMutex( LPCTSTR lpcszName = 0 );
	virtual ~CEMSMutex();

	BOOL SetName( LPCTSTR lpcszName = 0 );

	EMS_RESULT Create( LPCTSTR lpcszName = 0 );
	EMS_RESULT Close( void );

	BOOL Lock( ULONG ulTimeout = 0xFFFFFFFF );
	void Unlock( void );

private: // data
	TCHAR 	*m_lpszName;
	HANDLE	m_hMutex;
};

#endif // INC_EMSMUTEX

