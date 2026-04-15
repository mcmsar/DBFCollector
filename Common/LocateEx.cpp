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

#include "locateex.h"
#include "emsencod.h"

// Taken from SITGenServ.h.  This should be moved to a common constants file.
const long MAX_SAT_NUMBER = 128;

CEMSLocate::CEMSLocate()
{
	memset( &m_Locate, 0, sizeof(EMSLOCATE) );
}

CEMSLocate::CEMSLocate( const EMSLOCATE* cpLocate )
{
	Set( cpLocate );
}
		
CEMSLocate::CEMSLocate( const CEMSLocate& cLocate )
{
	memcpy( &m_Locate, &(cLocate.m_Locate), sizeof(EMSLOCATE) );
}

CEMSLocate::~CEMSLocate()
{
}

void 
CEMSLocate::Set( const EMSLOCATE* cpLocate )
{
	if( cpLocate )
	{
		memcpy( &m_Locate, cpLocate, sizeof(EMSLOCATE) );
	}
}

bool
CEMSLocate::IsSideBExpected()
{
	bool bWantSideB = FALSE;

	switch ( m_Locate.wType & ~EMSLOCTYPE_TEST )
	{
		case EMSLOCTYPE_CBC_121:
		case EMSLOCTYPE_CBC_243:
		case EMSLOCTYPE_CBC_121_243:
		case EMSLOCTYPE_CBC_406:
		case EMSLOCTYPE_406_SARP:
		case EMSLOCTYPE_406_SARR:
		case EMSLOCTYPE_406_SARP_SARR:
		case EMSLOCTYPE_406_FDOA:
		case EMSLOCTYPE_406_TDOA:
		case EMSLOCTYPE_406_FDOA_TDOA:
		case EMSLOCTYPE_406_FDOA_SARR:
		case EMSLOCTYPE_406_FDOA_SARP:
		case EMSLOCTYPE_406_FDOA_SARP_SARR:
			bWantSideB = TRUE;					
			break;
		
		case EMSLOCTYPE_CBC_121_DETECT:
		case EMSLOCTYPE_CBC_243_DETECT:
		case EMSLOCTYPE_CBC_121_243_DETECT:
		case EMSLOCTYPE_CBC_406_DETECT:
		case EMSLOCTYPE_406_SARP_DETECT:
		case EMSLOCTYPE_406_SARR_DETECT:
		case EMSLOCTYPE_406_SARP_SARR_DETECT:
		case EMSLOCTYPE_406_FDOA_DETECT:
//			case EMSLOCTYPE_406_TDOA_DETECT:
//			case EMSLOCTYPE_406_FDOA_TDOA_DETECT:

			bWantSideB = FALSE;
			break;
		default:
			break;
	}

	return bWantSideB;
}

ULONG 
CEMSLocate::GetFirstSatID()
{
	ULONG ulSatID = 999;

	CEMSEncodedSatID satDecoder;

	ULONG ulNum = 0;
	ULONG ulSatIDArray[MAX_SAT_NUMBER];

	if ( satDecoder.Expand( &(m_Locate.cSatIDs),
					ulSatIDArray, MAX_SAT_NUMBER, &ulNum) == EMS_OK )
	{
		if ( ulNum > 0 )
			ulSatID = (int)ulSatIDArray[0];
	}

	return ulSatID;
}

ULONG 
CEMSLocate::GetOrbitNumber()
{
	// SitGen retrieves this value from the orbit subsystem.  Here, assume that the LOCATE
	// record is encoded with the correct value.
	return m_Locate.ulSatPassID;
}

EMSLOCATE 
CEMSLocate::GetLocateRecord()
{
	EMSLOCATE locate;
	memset( &locate, 0, sizeof(EMSLOCATE) );

	memcpy( &locate, &m_Locate, sizeof(EMSLOCATE) );

	return locate;
}

EMSTIME 
CEMSLocate::GetTimestamp() const
{
	EMSTIME timeRet;
	timeRet.intTime = 0;

	timeRet = m_Locate.time;

	return timeRet;
}

WORD 
CEMSLocate::GetType() const
{
	WORD wRet = 0;

	wRet = m_Locate.wType;

	return wRet;
}

EMSLOCATE 
CEMSLocate::operator=( CEMSLocate& locate )
{
	return GetLocateRecord();
}

EMSLOCATION 
CEMSLocate::GetLocation() const
{
	return m_Locate.wlsSolution.location;
}

INT64 
CEMSLocate::GetBeaconID() const
{
	return m_Locate.i64BeaconID;
}

bool 
CEMSLocate::IsSideA() const
{
	bool bRet = true;

	if( (m_Locate.wType & EMSLOCTYPE_B_SIDE) == EMSLOCTYPE_B_SIDE )
		bRet = false;

	return bRet;
}