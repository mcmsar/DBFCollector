/********************************************************************
*	Module:			emsclock.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	CEMSSystemClock
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
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

	0.0	2001/09/17	rvw	start

********************************************************************/
#include <windows.h>
#include "emstime.h"
#include "emsclock.h"


EMS_RESULT CEMSSystemClock::SetTime( EMSTIME time )
{
	EMS_RESULT hr = EMS_OK;

	return hr;
}

EMSTIME CEMSSystemClock::GetTime( void )
{
	CEMSTime timeNow;
	SYSTEMTIME sysTime;

	GetSystemTime( &sysTime );

	timeNow.SetTime( sysTime.wYear, sysTime.wMonth, sysTime.wDay,
			sysTime.wHour, sysTime.wMinute, sysTime.wSecond,
			sysTime.wMilliseconds * 1000000 );

	return timeNow;
}

