/********************************************************************
*	Module:			emsit959.h
*	Description:	Header for CEMSSit915  Class
*					(Health Status Narrative)
*
*********************************************************************
*	              Copyright (c) 2009 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef INC_EMSIT959
#define INC_EMSIT959

#include "emssit.h"
#include "healthStatusTypes.h"


class CEMSSit959A : public CEMSSitMessageBase
{
public:
	CEMSSit959A();
	virtual ~CEMSSit959A();

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream );
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );

	EMS_RESULT SetHealthStatus( 
					const EMSHEALTHSTATUS cStatus,
					const unsigned long culRecCount,
					const EMSHEALTHDETECTIONS* caDetectionRecords );

	virtual void Reset( void );

private: // methods
	void _resetStatus( );
	
private:	// data
	EMSHEALTHSTATUS			m_status;
	long					m_ulDetectRecCount;
	EMSHEALTHDETECTIONS*	m_paDetectionRecords;

};

#endif // INC_EMSIT959
