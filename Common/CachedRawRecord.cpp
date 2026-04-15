/*********************************************************************
*	              Copyright (c) 2008 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:
	$
********************************************************************/

#ifdef WIN32
#pragma warning(disable:4786)	// disable compiler warnings for STL debug symbol size
#endif

#include "cachedrawrecord.h"
#include "rawdatarecord.h"

CEMSCachedRawRecord::CEMSCachedRawRecord() : m_pRs(0)
{
	m_tmCached.intTime = 0;
}

CEMSCachedRawRecord::CEMSCachedRawRecord( const CEMSCachedRawRecord& x ) : m_pRs(0)
{
	Set( x.m_pRs, x.m_tmCached );
}

CEMSCachedRawRecord::CEMSCachedRawRecord( CEMSRawDataRecord* pRs, const EMSTIME ctmCached ) : m_pRs(0)
{
	Set( pRs, ctmCached );
}

CEMSCachedRawRecord::~CEMSCachedRawRecord()
{
	if( m_pRs )
	{
		m_pRs->Release();
		m_pRs = 0;
	}
}

void
CEMSCachedRawRecord::Set( CEMSRawDataRecord* pRs, const EMSTIME ctmCached )
{
	if( m_pRs )
	{
		m_pRs->Release();
		m_pRs = 0;
	}


	if( pRs )
	{
		m_pRs = pRs;
		m_pRs->AddRef();
	}

	m_tmCached = ctmCached;
}

CEMSRawDataRecord*
CEMSCachedRawRecord::GetRecordset()
{
	CEMSRawDataRecord* pRs = 0;

	pRs = m_pRs;

	if( pRs )
		pRs->AddRef();

	return pRs;
}
