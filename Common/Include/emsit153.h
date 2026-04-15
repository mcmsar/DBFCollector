/*********************************************************************
* Copyright (c) 2011 by EMS Technologies, Inc.,
* All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef __SIT_153_H__
#define __SIT_153_H__

#include "emsitmeoalertmessagebase.h"

// Located MEO Alerts
class CEMSSit153 : public CEMSSitMEOAlertMessageBase
{
	public:
		CEMSSit153();
		CEMSSit153( const CEMSSit153& x );
		virtual ~CEMSSit153();

		void SetFinalSolution( const EMSLOCATE& crLocate ) { m_locate = crLocate; }
		EMSLOCATE GetFinalSolution() const { return m_locate; }

		virtual void Reset( void );

	protected:
		EMS_RESULT _WriteFinalSolution( IEMSSeqStream* lpStream );

	private:
		EMSLOCATE m_locate;
};

#endif