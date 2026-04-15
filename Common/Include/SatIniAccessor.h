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

#ifndef __SAT_INI_ACCESSOR_H__
#define __SAT_INI_ACCESSOR_H__

#include "objectmap.h"
#include <string>
#include "inisectionaccessor.h"

//! Reads/writes a satellite .ini file.
class CEMSSatINIAccessor
{
	public:
		CEMSSatINIAccessor();
		CEMSSatINIAccessor( const CEMSSatINIAccessor& x );
		~CEMSSatINIAccessor();

		//! This should load all satellites from the given .ini file.  Currently,
		//! it just stores the file path.
		void Load( const wchar_t* cwszSrcFile );

		//! Writes all stored satellite data to the given .ini file.  If no path is specified,
		//! overwrites the loaded file (if it has been loaded).
		void Save( const wchar_t* cwszDestFile = 0 );

		//! Not implemented.
		bool GetByNoradID( const ULONG culNoradID, CEMSINISectionAccessor& roData );

		//! Retrieves all .ini entries for one satellite.
		bool GetBySatID( const ULONG culSatID, CEMSINISectionAccessor& roData  );

		//! Add a new .ini section (i.e., a satellite).
		void Add( CEMSINISectionAccessor& roData );
	

	private:
		static const wchar_t* ms_cwszAppName;
		static const int ms_ciDefaultStringLen;

	private:
		std::wstring m_owszFileName;

		// Map of TLES, keyed by NORAD ID.
		CEMSObjectMap<std::wstring,CEMSINISectionAccessor> m_omapSats;

};

#endif