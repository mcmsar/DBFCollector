/*********************************************************************
* Copyright (c) 2011 by EMS Technologies, Inc.,
* All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef __SIT_150_H__
#define __SIT_150_H__

#include "emsitsimplemeoalertmessagebase.h"

// Located MEO Alerts for MCC
class CEMSSit150 : public CEMSSitSimpleMEOAlertMessageBase
{
	public:
		CEMSSit150();
		CEMSSit150( const CEMSSit150& x );
		virtual ~CEMSSit150();

		void SetFinalSolution( const EMSLOCATE& crLocate ) { m_locate = crLocate; }
		EMSLOCATE GetFinalSolution() const { return m_locate; }

	protected:
		EMS_RESULT _WriteFinalSolution( IEMSSeqStream* lpStream );

	private:
		EMSLOCATE m_locate;

};

#endif