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

	$Log:
	$
********************************************************************/

#ifndef __RAS_WRAPPER_H__
#define __RAS_WRAPPER_H__

#include "aobjbase.h"
#include "objectlist.h"
#include <string>
#include <windows.h>
#include <ras.h>
#include <log4cxx/logger.h>

class CEMSRAS : public CApiObjBase
{
	public:
		CEMSRAS();
		CEMSRAS( const char* cszName, const char* cszPhoneBook );
		CEMSRAS( const CEMSRAS& x );
		~CEMSRAS();

		static CEMSObjectList<std::string> EnumerateConnections( const char* cszPhoneBook );
		
		void SetConnection( const char* cszName, const char* cszPhoneBook );
		void Dial();
		void Hangup();
		bool IsConnected();
		std::string GetStatus();
		void SetLogger( log4cxx::LoggerPtr pLogger ) { if( pLogger ) m_pLogger = pLogger; }

	private:
		RASDIALPARAMS _GetDialParams();
		RASENTRY _GetEntryProperties();
		void _GetConnectionHandle();
		void _ForceDialAll();
		
	private:
		std::string m_oszName;
		std::string m_oszPhoneBook;
		HRASCONN m_hRASConnection;
		log4cxx::LoggerPtr m_pLogger;
		
};

#endif