/*********************************************************************
*	              Copyright (c) 2008 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:$
********************************************************************/

#ifndef __CC_ACCESSOR_H__
#define __CC_ACCESSOR_H__

#include "emstypes.h"
#include "criticalsection.h"
#include "objectset.h"
#include <string>

//! Accessor for a file holding a system's country codes.
class CEMSCCAccessor
{
	public:
		CEMSCCAccessor();
		CEMSCCAccessor( const CEMSCCAccessor& x );
		~CEMSCCAccessor();

		void Init( const char* cszFile, const char* cszPwd );

		CEMSObjectSet<ULONG> GetCountryCodes();

		void SetCountryCodes( const ULONG culNum, const ULONG* caulCodes );

		bool IsInSet( const ULONG culCode );

	private:
		void _ReadCountryCodes();

	private:
		CEMSCriticalSection m_ocsFileAccess;
		std::string m_oszFilePath;
		std::string m_oszPwd;
		CEMSObjectSet<ULONG> m_osetCCs;

};

#endif