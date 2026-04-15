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

#ifndef __WSHOST_H__
#define __WSHOST_H__

#include "pointerlist.h"

#ifdef WIN32
#include "ws.h"
#include "eservice.h"     // for CEMSService class
#include "loghelper.h"

// {16AA2E91-13B3-48a6-AA8D-122EF4DEDEA8}
DEFINE_GUID( APPID_EMSWSHost, 0x16aa2e91, 0x13b3, 0x48a6, 0xaa, 0x8d, 0x12, 0x2e, 0xf4, 0xde, 0xde, 0xa8);

//! A generic Web Service Host class.  This class is derived from CEMSService, allowing it to run
//! as a Windows Service.  It also provides the basics for hosting plugin Web Services.
class CEMSWSHost : public CEMSService
{
	public:
		CEMSWSHost();
		virtual ~CEMSWSHost();
		
		//! Derived classes should override this method.  The return value is used in log messages
		//! to identify the source.  It is also used to lookup the configuration file in the registry.
		//! The registry key is HKEY_LOCAL_MACHINE/SOFTWARE/EMS TECHNOLOGIES/Components/<component>.
		virtual const wchar_t* GetComponent() { return L"WSHost"; }

		//! Derived classes should override this method to provide a unique service name.  This is the
		//! Windows Service name.
		virtual const TCHAR* GetService() { return TEXT("EMSWSHost"); }

	protected:
		virtual EMS_RESULT StartEMSService( DWORD dwArgc, LPTSTR *lpszArgv );
		virtual EMS_RESULT StopEMSService( void );
		virtual EMS_RESULT PauseEMSService( void );
		virtual EMS_RESULT ContinueEMSService( void );
	    virtual EMS_RESULT InstallEMSService( void );
	    virtual EMS_RESULT RemoveEMSService( void );
	    virtual BOOL StopEMSIsAccepted( void );

		//! If the derived class has overriden _ServiceProcessLoop then it should call this 
		//! method prior to entering the main processing loop.
		virtual void _Startup();

		//! If the derived class has overriden _ServiceProcessLoop then it should call this 
		//! method after exiting the main processing loop.
		virtual void _Shutdown();

		virtual EMS_RESULT _ServiceProcessLoop(void);

		virtual BOOL _OkayToStop( void );

		//! Derived classes should override this method to provide a unique application identifier.
		virtual const CLSID* _GetAppID() { return &APPID_EMSWSHost; }

		//! Derived classes should override this method to provide a unique logger category for the service.
		virtual const USHORT _GetLoggerCategory() { return EMSLOGCAT_WSHost; }

		virtual void _StartWebServices();
		virtual void _StopWebServices();
		virtual void _InitWebServices();
		virtual void _InitWebServicesEx();
		virtual CEMSPointerList<IEMSWS> _GetWebServices();

		virtual std::wstring _GetConfigFile();

		virtual std::wstring _GetXMLWSConfig(){ return L""; }

		//! Derived classes can override this to provide special initialization.
		virtual void _Init();

		//! Derived classes can override this to capture configuration strings for Web Services.
		virtual void _OnWSConfig( const wchar_t* cwszConfig) {}

	protected:	// constants
		//! The maximum amount of time that the service will wait for running web services
		//! to shutdown before the service itself exits.
		static const long ms_clMaxShutdownMilliseconds;
		
		static const ULONG ms_culTimeoutInterval;

		static const wchar_t* ms_cwszWS;
		static const wchar_t* ms_cwszWSClassID;

	protected: //data
		HANDLE					m_hEventStop;
		HANDLE					m_hEventSignal;
		BOOL					m_bPaused;
		DWORD					m_dwThreadID;
		ULONG					m_ulMinObjCount;
		BOOL					m_bStopEnabled;
		CEMSLogHelper		    m_logger;	
		CEMSPointerList<IEMSWS> m_olstWebServices;
};

#elif defined(__VMS)

class CEMSWebService;

typedef IEMSWS CEMSWebService;

//! VMS definition of WSHost class.
class CEMSWSHost
{
	public:
		CEMSWSHost();
		virtual ~CEMSWSHost();

	protected:
		virtual EMS_RESULT StartEMSService( DWORD dwArgc, LPTSTR *lpszArgv );

		//! If the derived class has overriden _ServiceProcessLoop then it should call this 
		//! method prior to entering the main processing loop.
		virtual void _Startup();

		//! If the derived class has overriden _ServiceProcessLoop then it should call this 
		//! method after exiting the main processing loop.
		virtual void _Shutdown();

		virtual EMS_RESULT _ServiceProcessLoop(void);

		virtual void _StartWebServices();
		virtual void _StopWebServices();
		virtual void _InitWebServices();
		virtual CEMSPointerList<IEMSWS> _GetWebServices();

		virtual std::wstring _GetConfigFile();

		//! Derived classes can override this to provide special initialization.
		virtual void _Init();

		//! Derived classes can override this to capture configuration strings for Web Services.
		virtual void _OnWSConfig( const wchar_t* cwszConfig) {}

		//! Dervied class must implement this method to create the actual web service object instance and return
		//! a pointer to its IEMSWS interface.
		virtual IEMSWS* _CreateWS() = 0;

	protected:	// constants
		//! The maximum amount of time that the service will wait for running web services
		//! to shutdown before the service itself exits.
		static const long ms_clMaxShutdownMilliseconds;
		
		static const ULONG ms_culTimeoutInterval;

		static const wchar_t* ms_cwszWS;
		static const wchar_t* ms_cwszWSClassID;

	protected: //data
		CEMSPointerList<IEMSWS> m_olstWebServices;
};

#endif

#endif // __WSHOST_H__

