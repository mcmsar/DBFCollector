/********************************************************************
*	Module:			LogEvent.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*********************************************************************
* Copyright (c) 2001-2005 by EMS Technologies, Inc.,
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

	0.0	2001/07/30		rvw	start

********************************************************************/
#ifndef INC_LOGEVENT
#define INC_LOGEVENT

#include "emserror.h"
#include "emsloggr.h"

#define MAX_LOGGERNAME_LEN 64

class CEMSLogEvent 
{
public:
	CEMSLogEvent( LPCWSTR wszLoggerName = NULL );
	virtual ~CEMSLogEvent();

	EMS_RESULT ReportEvent( EMSLOGMSGTYPE msgType, DWORD dwEvent, WORD wCategory,  
		WORD wNumParams=0, LPCSTR *aszParams=0 );

	EMS_RESULT ReportEventW( EMSLOGMSGTYPE msgType, DWORD dwEvent, WORD wCategory,  
		WORD wNumParams=0, LPCWSTR *awszParams=0 );

private: // data
	WORD		m_wProcessID;

	WORD		GetEventType( EMSLOGMSGTYPE msgType );
	wchar_t		m_wszLoggerName[MAX_LOGGERNAME_LEN];

};

#endif // INC_LOGEVENT
