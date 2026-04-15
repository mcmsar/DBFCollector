/*********************************************************************
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

	$Log:
	$
********************************************************************/

#ifndef __INI_CONFIG_H__
#define __INI_CONFIG_H__

#include "objectlist.h"
#include <string>
#include <log4cxx/logger.h>

//! Provides access to an INI file.
class CEMSINIConfig
{
	public:
		CEMSINIConfig();
		CEMSINIConfig( const CEMSINIConfig& x );
		~CEMSINIConfig();
		
		//! Set the path to the underlying source file.
		void SetSourceFile( const char* cszFilePath );

		void AuditSection( const char* cszSection );
		void LogIt( const DWORD dwCharacters, const char* cszBuffer, const char* cszSection );
		CEMSObjectList<std::string> GetSectionNames();
		std::string GetValue( const char* cszSection, const char* cszKey );
		int GetValueInt( const char* cszSection, const char* cszKey );
		ULONG GetValueULong( const char* cszSection, const char* cszKey );
		short GetValueShort( const char* cszSection, const char* cszKey );
		double GetValueDouble( const char* cszSection, const char* cszKey );
		CEMSObjectList<std::string> GetSection( const char* cszSection );
		void SetValue( const char* cszSection, const char* cszKey, const char* cszValue );
		bool GetValueBoolean( const char* cszSection, const char* cszKey );

	private:
		//! Override in a derived class to provide unique logger.
		virtual log4cxx::LoggerPtr _GetLogger() { return m_pLogger; }

		//! Override in a derived class to provide calls to AuditSection for each section.
		virtual void _DoAudit() {}
		
	private:
		std::string	m_oszSourceFile;
		
		static const char* ms_cszLogger;
		log4cxx::LoggerPtr	m_pLogger;
};

#endif