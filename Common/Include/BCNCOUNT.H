/********************************************************************
*	Module:			bcncount.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	CEMSBeaconCounter 	
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*
*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2003/03/30	rvw	start

********************************************************************/

#ifndef INC_BCNCOUNT
#define INC_BCNCOUNT

#include "emstypes.h"
#include "emserror.h"

typedef enum _tagEMSBTCUPDATEMODE
{
	EMSBTC_UpdateNever = 0,
	EMSBTC_UpdateOlder = 1,
	EMSBTC_UpdateNewer = 2,
	EMSBTC_UpdateDefault = EMSBTC_UpdateNewer
} EMSBTCUPDATEMODE;

class CEMSBeaconCounter
{
public:
	CEMSBeaconCounter( int nMaxCount = 1000 );
	virtual ~CEMSBeaconCounter( );

	virtual EMS_RESULT AddBeacon( INT64 i64BeaconID );
	virtual void Reset( void );

//	inline int GetCount( void ) { return m_nCurrCount; }
	int GetCount( void );
	inline int GetMaxCount( void ) { return m_nMaxCount; }
	bool TestBeacon( INT64 i64BeaconID );
	INT64 GetBeaconID( INT nIndex );

protected: // methods
	INT _GetBeaconIndex( INT64 i64BeaconID );
	EMS_RESULT _Reset( INT nIndex );

private:
	int		m_nMaxCount;
	int		m_nCurrCount;	
	INT64		*m_lpi64BeaconID;
};

class CEMSBeaconTimeCounter : public CEMSBeaconCounter
{
public:
	CEMSBeaconTimeCounter( int nMaxCount = 1000 );
	virtual ~CEMSBeaconTimeCounter( );

	virtual EMS_RESULT AddBeacon( INT64 i64BeaconID );
	virtual EMS_RESULT AddBeacon( INT64 i64BeaconID, EMSTIME timeRef );
	virtual void Reset( void );
	virtual INT Reset( EMSTIME timeStart );

	EMSTIME GetBeaconTime( INT64 i64BeaconID );
	EMSTIME GetBeaconTime( INT iIndex );
	void SetBeaconTime( INT iIndex, EMSTIME timeRef );

	inline EMSBTCUPDATEMODE GetUpdateMode( void ) { return m_updateMode; }
	inline void SetUpdateMode( EMSBTCUPDATEMODE mode ) { m_updateMode = mode; }

private: // data
	EMSTIME				*m_lpTimeRef;
	EMSBTCUPDATEMODE	m_updateMode;
};

#endif // INC_BCNCOUNT
