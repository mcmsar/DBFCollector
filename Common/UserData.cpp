/*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
*							All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
#include "assert.h"
#include "emsexcpt.h"
#include "UserData.h"

CEMSUserData::CEMSUserData( const BYTE* cabyData, const ULONG culDataSize )
{
	if ( cabyData && culDataSize )
	{
		m_abyData = new BYTE[culDataSize];
		if ( !m_abyData ) THROW_NOMEMORY_EXCEPTION();

		memcpy( m_abyData, cabyData, culDataSize );
		m_ulDataSize = culDataSize;
	}
	else
	{
		m_abyData = NULL;
		m_ulDataSize = 0;
	}
}

CEMSUserData::~CEMSUserData()
{
	if ( m_abyData )
	{
		delete[] m_abyData;
		m_abyData = NULL;
	}
	m_ulDataSize = 0;
}


