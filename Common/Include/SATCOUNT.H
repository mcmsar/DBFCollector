/********************************************************************
*	Module:			satcount.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	CEMSSatCounter 	
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*
*********************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
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

	0.0	2007/03/10	rvw	start

********************************************************************/

#ifndef INC_SATCOUNT
#define INC_SATCOUNT

#include "emstypes.h"
#include "emserror.h"

class CEMSSatCounter
{
public:
	CEMSSatCounter( int nMaxCount = 128 );
	virtual ~CEMSSatCounter( );

	virtual EMS_RESULT AddSat( ULONG ulSatID );
	virtual void Reset( void );

	int GetSatCount( void );			// get number of satellites
	int GetSatCount( ULONG ulSatID );		// get incidents of specified satellite
	inline int GetMaxCount( void ) { return m_nMaxCount; }
	bool TestSat( ULONG ulSatID ) { return GetSatCount( ulSatID ) > 0; } 

	int GetSatsInDescOrder( ULONG *lpulSats );

protected: // methods
	INT _GetSatIndex( ULONG ulSatID );
	EMS_RESULT _Reset( INT nIndex );
	void _SortDescOrder( void );

private:
	int		m_nMaxCount;
	int		m_nCurrCount;	
	ULONG		*m_lpulSatID;
	ULONG		*m_lpulCount;
};

class CEMSSatSorter
{
public:
	CEMSSatSorter( int nMaxCount = 128 );
	virtual ~CEMSSatSorter( );

	virtual EMS_RESULT AddSat( ULONG ulSatID, EMSTIME timeDetection );
	virtual void Reset( void );

	int GetSatCount( void );			// get number of satellites
	int GetSatCount( ULONG ulSatID );		// get incidents of specified satellite
	inline int GetMaxCount( void ) { return m_nMaxCount; }
	bool TestSat( ULONG ulSatID ) { return GetSatCount( ulSatID ) > 0; } 

	int GetSatsInDescOrder( ULONG *lpulSats );

protected: // methods
	INT _GetSatIndex( ULONG ulSatID );
	EMS_RESULT _Reset( INT nIndex );
	void _SortDescOrder( void );

private:
	int		m_nMaxCount;
	int		m_nCurrCount;	
	ULONG		*m_lpulSatID;
	ULONG		*m_lpulCount;
	EMSTIME	*m_lptimeLastDetection;
};						  


#endif // INC_SATCOUNT
