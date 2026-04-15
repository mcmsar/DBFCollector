/*********************************************************************
*	Copyright (c) 2004-2005 by EMS Technologies, Inc.,
*	All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log$
********************************************************************/

#ifndef __SERVICE_CONTROLLER_H__
#define __SERVICE_CONTROLLER_H__

#ifdef WIN32
#include <windows.h>
#include <winsvc.h>
#endif

#include "emstypes.h"
#include <string>

//! @class CEMSServiceController
//! Used to control a service.
class CEMSServiceController
{
	public:
		CEMSServiceController();
		CEMSServiceController( const wchar_t* cwszName, const ULONG culWaitTime );
		CEMSServiceController( const CEMSServiceController& x );
		~CEMSServiceController();

		void SetServiceName( const wchar_t* cwszName );
		void SetWaitTime( const ULONG culWaitTime );

		bool Start( SERVICE_STATUS& ssInitialStatus );
		bool Start();
		bool Stop();

		bool IsRunning();

		bool IsRegistered();

	private:
		std::wstring m_wszServiceName;
		ULONG m_ulWaitTime;

		static const ULONG ms_ulDefaultWaitTime;
		static const ULONG ms_culWaitBetweenChecks;

//		SERVICE_STATUS	_GetStatus( SC_HANDLE& schService );
		bool			_Open( SC_HANDLE& schSCManager, SC_HANDLE& schService );
		void			_Close( SC_HANDLE& schSCManager, SC_HANDLE& schService );
};

#endif