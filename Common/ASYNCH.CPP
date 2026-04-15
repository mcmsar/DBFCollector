/********************************************************************
*   Module:         Asynch.cpp
*   Process ID:
*   S/W Platforms:
*   H/W Platforms:
*   Compiler:
*   Description:    Implementation of CEMSAsynch Object
*                       
*
*   Usage:
*   Entry Point:
*   Input Files:
*   Output Files:
*   Comments:
*
*********************************************************************
*	   Copyright (c) 2000 by EMS Technologies Canada, Ltd. Ottawa ON
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies Canada, Ltd.  It may 
* not be reproduced in whole or in part, in any form or by any means 
* whatsoever without the express written permission of EMS Technologies 
* Canada, Ltd.
*
********************************************************************/

/*******************************************************************

  Revision Record

    Rev Date            Auth    Changes
    === ====            ====    =======

    0.0 99/08/4     rvw start

********************************************************************/
#include <time.h>

#include "asynch.h"

CEMSAsynch::CEMSAsynch()
{
	m_lpfnCallback = 0;
	m_lpContextCallback = 0;
	m_bInitialized = FALSE;
	m_bOpen = FALSE;
}

CEMSAsynch::~CEMSAsynch()
{
}

void CEMSAsynch::SetEventCallback(LPFNASYNCHEVENT lpfnCallback, LPVOID lpContext /* = (LPVOID)this */)
{
	m_lpfnCallback = lpfnCallback;
	m_lpContextCallback = lpContext;
}

BOOL CEMSAsynch::DoEventCallback( DWORD dwEvent )
{
	return (m_lpfnCallback) ? (*m_lpfnCallback)( dwEvent, m_lpContextCallback ) : TRUE;
}

EMS_RESULT CEMSAsynch::WriteByte(BYTE cData)
{
	return WriteData(&cData, sizeof(BYTE));
}

EMS_RESULT CEMSAsynch::ReadByte(LPBYTE lpcData, DWORD dwTimeout)
{
	return ReadData( (LPVOID)lpcData, 1, dwTimeout);
}

