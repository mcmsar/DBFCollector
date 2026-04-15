/*********************************************************************
*	              Copyright (c) 2005 by EMS Technologies, Inc.,
*										All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:
	$
********************************************************************/

#ifndef __LOG_PROCESS_SETTINGS_H__
#define __LOG_PROCESS_SETTINGS_H__

#include "criticalsection.h"
#include <log4cxx/config_msvc.h>
#include "logstring.h"

//! Holds process-wide settings for logging.
class LOG4CXX_EXPORT CEMSLogProcessSettings
{
	public:
		~CEMSLogProcessSettings();

		//! Consumers call this method to retrieve a pointer to the object.  The object is statically
		//! allocated and there is no need to call Release() when finished with the pointer.
		static CEMSLogProcessSettings* GetInstance();

		//! Set the LUT Identifier that the process is associated with.
		void SetLutID( const ULONG culLutID );

		//! Get the LUT Identifier tha the process is associated with.
		ULONG GetLutID();

		//! Set the Identifier of the process.
		void SetProcessID( const ULONG culProcessID );

		//! Get the Identifier of the process.
		ULONG GetProcessID();

		//! Set the process name.  This could be the name of a service.
		//! The name is used to build a logger hierarchy.  Any loggers created within
		//! this process will be children of the process level logger.
		void SetProcessName( const wchar_t* cwszProcessName );

		//! Get the name of the process.  This could be the name of a service.
		//! The name is used to build a logger hierarchy.  Any loggers created within
		//! this process will be children of the process level logger.
		EMSLOGString GetProcessName();

	private:
		CEMSLogProcessSettings();
		static CEMSLogProcessSettings m_oLogProcessSettings;

	private:
		ULONG m_ulLutID;
		ULONG m_ulProcessID;
		EMSLOGString m_oszProcessName;
		CEMSCriticalSection m_csSettings;
};

#endif