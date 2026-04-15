/*********************************************************************
*	              Copyright (c) 2011 by EMS Technologies, Inc.,
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

#ifndef __DBF_COLLECTOR_H__
#define __DBF_COLLECTOR_H__

#include "eservice.h"

class CEMSDBFCollectorService : public CEMSService
{
	public:
		CEMSDBFCollectorService();
		virtual ~CEMSDBFCollectorService(); 
		void Stop() { StopEMSService(); }

	protected:
		virtual EMS_RESULT StartEMSService( DWORD dwArgc, LPTSTR *lpszArgv );
		virtual EMS_RESULT StopEMSService( void );
		virtual EMS_RESULT PauseEMSService( void );
		virtual EMS_RESULT ContinueEMSService( void );
		virtual EMS_RESULT InstallEMSService( void );
		virtual EMS_RESULT RemoveEMSService( void );
		virtual BOOL StopIsAccepted( void );

	private: // methods
		EMS_RESULT _ServiceProcessLoop(void);
		void _ReleaseObjects( void );
		BOOL _OkayToStop( void );
		void _Init();

	private: //data
		HANDLE					m_hEventStop;
		HANDLE					m_hEventSignal;
		BOOL					m_bPaused;
		DWORD					m_dwRegister;
		DWORD					m_dwThreadID;
		ULONG					m_ulMinObjCount;
		BOOL					m_bStopEnabled;
};

#endif // __DBF_COLLECTOR_H__

