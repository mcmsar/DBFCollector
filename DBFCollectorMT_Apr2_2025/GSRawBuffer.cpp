/*********************************************************************
*	              Copyright (c) 2011 by EMS Technologies, Inc.,
*									All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be
* reproduced in whole or in part, in any form or by any means whatsoever
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
// Local version using EMSDBFPASSRECORDS2 (from emsDBFtypes2.h)
// Replaces ADBoards\GS - 64\GSRawBuffer.cpp for this project.

#include "GSRawBuffer.h"
#include <stdio.h>


CEMSRawBuffObj::CEMSRawBuffObj(): m_aBuff(NULL), m_ulBuffSize(0)
{
	m_timeStamp.intTime = 0L;
}

CEMSRawBuffObj::CEMSRawBuffObj( const CEMSRawBuffObj& rawObj )
{
}

CEMSRawBuffObj::~CEMSRawBuffObj()
{
	Reset();
}

void
CEMSRawBuffObj::Initialize( unsigned long ulBuffSize )
{
	Reset();
	if( ulBuffSize )
	{
		m_aBuff = new unsigned char[ulBuffSize];
		memset(m_aBuff, 0, sizeof(unsigned char) * ulBuffSize);
		m_ulBuffSize = ulBuffSize;
	}
}

void
CEMSRawBuffObj::Reset()
{
	memset(&m_PassRecords, 0, sizeof(EMSDBFPASSRECORDS2) );
	if( m_aBuff )
	{
		delete[] m_aBuff;
		m_aBuff = NULL;
		m_ulBuffSize = 0;
	}
}

void
CEMSRawBuffObj::SetBuffData( const unsigned char*  aData, unsigned long ulSize )
{
	if( m_aBuff && (ulSize <= m_ulBuffSize) )
		memcpy( m_aBuff, aData, ulSize * sizeof( unsigned char ) );
}

unsigned long
CEMSRawBuffObj::GetBuffData( unsigned char*  aData, unsigned long ulMaxSize )
{
	if( m_aBuff )
	{
		unsigned long ulSize = ulMaxSize < m_ulBuffSize ? ulMaxSize : m_ulBuffSize;
		memcpy( (void*)aData, m_aBuff, ulSize * sizeof( unsigned char ) );
		return ulSize;
	}
	else
		return 0;
}

void
CEMSRawBuffObj::WriteToFile( const char* szFileName )
{
	if( strlen(szFileName) > 0 )
	{
		FILE* OneSecFile = NULL;

		OneSecFile = fopen(szFileName,"w+b");
		if( OneSecFile != NULL )
		{
			fwrite(m_aBuff, 1, m_ulBuffSize, OneSecFile);
			fclose(OneSecFile);
		}
	}
}

void
CEMSRawBuffObj::SetPassRecs( EMSDBFPASSRECORDS2& passRecs )
{
	memcpy( &m_PassRecords, &passRecs, sizeof(EMSDBFPASSRECORDS2) );
}
