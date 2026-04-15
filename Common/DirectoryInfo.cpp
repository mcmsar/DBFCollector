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


#include "directoryinfo.h"

CEMSDirectoryInfo::CEMSDirectoryInfo() : m_hDir( INVALID_HANDLE_VALUE ), m_ulBufferLength(0)
{
	memset( m_byBuffer, 0, MAX_BUFFER*sizeof(char) );

	memset( &m_strOverLapped, 0, sizeof(OVERLAPPED) );
}

void 
CEMSDirectoryInfo::Clear()
{
	memset( m_byBuffer, 0, MAX_BUFFER*sizeof(char) );
	m_ulBufferLength = 0;

	memset( &m_strOverLapped, 0, sizeof(OVERLAPPED) );

	if( INVALID_HANDLE_VALUE != m_hDir) { CloseHandle(m_hDir); }

	m_hDir = INVALID_HANDLE_VALUE;
	m_wszDirName.erase();

}