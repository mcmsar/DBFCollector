/********************************************************************
*       Module:         emsit663.h
*       Description:    Description of CEMSSit663A Class
*						Beacon Advisory Report SIT Message
*
*********************************************************************
*	Copyright (c) 2009 by EMS Technologies, Inc.,
*	All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
********************************************************************/

#ifndef INC_EMSIT663
#define INC_EMSIT663

#include "emssit.h"
#include "emscollsummary.h"
#include "beaconadvisoryTypes.h"

class CEMSSit663A : public CEMSSitMessageBase
{
public:
	CEMSSit663A();
	virtual ~CEMSSit663A();

	virtual void Reset( void );

	virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream );
	virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );

	virtual EMS_RESULT ParseSitMessage( CEMSSitTokenizer *lpTokenizer ) { return EMS_UNSUPPORTED; }
	virtual EMS_RESULT ParseSitHeader( CEMSSitTokenizer *lpTokenizer, BOOL bPeek=FALSE ) { return EMS_UNSUPPORTED; }

	EMS_RESULT SetCount( const int ciCount );
	EMS_RESULT AddBeaconAdvisory( const EMS_BEACON_ADVISORY& advisory );

	int GetBeaconCount( void ) { return m_iBeaconCount; }
	void GetBeacon( const int ciIndex, EMS_BEACON_ADVISORY& beacon );

private: // methods
	virtual EMS_RESULT _GenerateSitBodyBeaconLines( const int ciIndex, IEMSSeqStream *lpStream );

protected:
	int						m_iBeaconAlloc;
	int						m_iBeaconCount;
	EMS_BEACON_ADVISORY*	m_aBeaconData;
	bool					m_bInitialized;
};

#endif // INC_EMSIT663
