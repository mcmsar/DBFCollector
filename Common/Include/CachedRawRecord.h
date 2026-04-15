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

#ifndef __CACHED_RAWRECORD_H__
#define __CACHED_RAWRECORD_H__

#include "aobjbase.h"

class CEMSRawDataRecord;

class CEMSCachedRawRecord : public CApiObjBase
{
	public:
		CEMSCachedRawRecord();
		CEMSCachedRawRecord( const CEMSCachedRawRecord& x );
		CEMSCachedRawRecord( CEMSRawDataRecord* pRs, const EMSTIME ctmCached );
		~CEMSCachedRawRecord();

		void Set( CEMSRawDataRecord* pRs, const EMSTIME ctmCached );
		inline EMSTIME GetCachedTime() const { return m_tmCached; }
		CEMSRawDataRecord* GetRecordset();

	private:
		CEMSRawDataRecord*	m_pRs;
		EMSTIME m_tmCached;

};

#endif // __CACHED_RAWRECORD_H__