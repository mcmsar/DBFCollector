/*********************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
*										All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef __EMS_LOCATEDATAACCESSHELPER_H__
#define __EMS_LOCATEDATAACCESSHELPER_H__

#include "locate.h"

#include <vector>
using std::vector;

#include <string>
using std::wstring;

class CEMSLocateDataAccessHelper
{	
	public:
		CEMSLocateDataAccessHelper();
		CEMSLocateDataAccessHelper( const CEMSLocateDataAccessHelper& x );
		~CEMSLocateDataAccessHelper();

		ULONG GetCount(
			const wchar_t*				cwszDSN,
			const wchar_t*				cwszSQLWhere );

		bool GetLocations(	
			const wchar_t*				cwszDSN,
			const wchar_t*				cwszWhere,
			std::vector<EMSLOCATE>&		rvectLocations,
			const ULONG					culMaxLocations = 0 ); // Use the default (the configured max)
		
		// To build a where clause to find location records of one or more types
		// E.g.		(	( wType & EMSLOCTYPE_REAL_BASE_MASK ) = EMSLOCTYPE_406_SARR
		//			 OR	( wType & EMSLOCTYPE_REAL_BASE_MASK ) = EMSLOCTYPE_406_SARP )
		std::wstring GetWhereClause_IncludeTypes( const std::vector<EMSLOCATETYPE>& crvectType );
		std::wstring GetWhereClause_IncludeType( const EMSLOCATETYPE ceType );

		// To build a where clause to exclude location records of one or more sub-types
		// E.g.		(	( wType & EMSLOCTYPE_DETECT_ONLY ) <> EMSLOCTYPE_DETECT_ONLY
		//			 AND	( wType & EMSLOCTYPE_B_SIDE ) <> EMSLOCTYPE_B_SIDE )
		std::wstring GetWhereClause_ExcludeSubTypes( const std::vector<EMSLOCATETYPE>& crvectType );
		std::wstring GetWhereClause_Time( const EMSTIME ctimeStart, const EMSTIME ctimeEnd );
		std::wstring GetWhereClause_Beacons( const std::vector<INT64>& crvectBeaconID );
		std::wstring GetWhereClause_Beacons( const INT64 ci64BeaconID );
		std::wstring GetWhereClause_Marginal();
		std::wstring GetWhereClause_Nominal();

	private:
};

#endif	// __EMS_LOCATEDATAACCESSHELPER_H__
