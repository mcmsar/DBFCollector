/*********************************************************************
*	              Copyright (c) 2005 by EMS Technologies, Inc.,
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

#ifndef __LOCATEEX_H__
#define __LOCATEEX_H__

#include "aobjbase.h"
#include "locate.h"

//! @class CEMSLocate
//! This class wraps the EMSLOCATE record.  It is used for reading and writing 
//! EMSLOCATE records.
class CEMSLocate : public CApiObjBase
{
	public:
		CEMSLocate( const EMSLOCATE* cpLocate );
		CEMSLocate( const CEMSLocate& cLocate );
		CEMSLocate();
		~CEMSLocate();

		void Set( const EMSLOCATE* cpLocate );
		bool IsSideBExpected();
		ULONG GetFirstSatID();
		ULONG GetOrbitNumber();
		INT64 GetBeaconID() const;
		EMSLOCATION GetLocation() const;
		EMSTIME GetTimestamp() const;
		WORD GetType() const;
		bool IsSideA() const;
		EMSTIME GetTimeTCA() const { return m_Locate.timeTCA; }

		EMSLOCATE operator=( CEMSLocate& locate );
		EMSLOCATE GetLocateRecord();

	private:
		EMSLOCATE	m_Locate;
};

#endif