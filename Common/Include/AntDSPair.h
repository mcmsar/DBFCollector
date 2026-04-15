/*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
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

#ifndef __ANT_DS_PAIR_SCHEDULE_H__
#define __ANT_DS_PAIR_SCHEDULE_H__

#include "aobjbase.h"
#include "emstrack.h"

//! Holds the pass schedule for an antenna/data stream pair.
class CEMSPairSchedule : public CApiObjBase
{
	public:
		CEMSPairSchedule();
		CEMSPairSchedule( const ULONG culPairID, const ULONG culAntID, const ULONG culDSID,
							const ULONG culPasses, const EMSSATTRACKRECORD* caPasses );
		CEMSPairSchedule( const CEMSPairSchedule& x );
		~CEMSPairSchedule();

		ULONG GetPairID() const { return m_ulPairID; }

		ULONG GetAntennaID() const { return m_ulAntennaID; }

		ULONG GetDataStreamID() const { return m_ulDSID; }

		ULONG GetNumPasses() const { return m_ulPasses; };

		//! Caller must delete the returned array.
		EMSSATTRACKRECORD* GetPasses() const;

		//! Get the current pass.  Returns NULL if there is no current pass.
		//! Caller must delete the returned structure.
		EMSSATTRACKRECORD* GetCurrentPass() const;

		//! Determine whether the given pass record is in the current schedule.  It must be identical.
		int IsInSchedule( const EMSSATTRACKRECORD& crstrPass );

		//! Write the schedule to file in binary format.
		void Serialize( const wchar_t* cwszOutput );

		//! Read the schedule in from a binary format file.
		void Deserialize( const wchar_t* cwszInput );

	private:
		void _SetSchedule( const ULONG culPasses, const EMSSATTRACKRECORD* caPasses );

	private:
		ULONG				m_ulPairID;
		ULONG				m_ulAntennaID;
		ULONG				m_ulDSID;
		ULONG				m_ulPasses;
		EMSSATTRACKRECORD*	m_aPasses;
};

#endif