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

#include "raswrapper.h"
#include "convutility.h"
#include "emsexcpt.h"
#include "raserror.h"

CEMSRAS::CEMSRAS() : CApiObjBase(TEXT("CEMSRAS")), m_hRASConnection(NULL), m_pLogger(NULL)
{
}

CEMSRAS::CEMSRAS( const char* cszName, const char* cszPhoneBook ) : CApiObjBase(TEXT("CEMSRAS")), m_hRASConnection(NULL),
																m_pLogger(NULL)
{
	SetConnection( cszName, cszPhoneBook );
}

CEMSRAS::CEMSRAS( const CEMSRAS& x ) : CApiObjBase(TEXT("CEMSRAS")), m_oszName(x.m_oszName),
									m_oszPhoneBook(x.m_oszPhoneBook),
									m_hRASConnection(x.m_hRASConnection),
									m_pLogger(x.m_pLogger)
{
}

CEMSRAS::~CEMSRAS()
{
	Hangup();
}

CEMSObjectList<std::string> 
CEMSRAS::EnumerateConnections( const char* cszPhoneBook )
{
	CEMSObjectList<std::string> olstRet;

	DWORD dwCb = sizeof(RASENTRYNAME);
    DWORD dwErr = ERROR_SUCCESS;
    DWORD dwRetries = 5;
    DWORD dwEntries = 0;
    RASENTRYNAME* lpRasEntryName = NULL;

    //
    // Loop through in case the information from RAS changes between calls.
    //
    while (dwRetries--)
    {
        //
        // If the memory is allocated, free it.
        //
        if (NULL != lpRasEntryName)
        {
            HeapFree(GetProcessHeap(), 0, lpRasEntryName);
            lpRasEntryName = NULL;
        }
        //
        // Allocate the size need for the RAS structure.
        //
        lpRasEntryName = (RASENTRYNAME*) HeapAlloc(GetProcessHeap(), 0, dwCb);
        if (NULL == lpRasEntryName)
        {
            dwErr = ERROR_NOT_ENOUGH_MEMORY;
            break;
        }
        //
        // Set the structure size for version checking purposes.
        //
        lpRasEntryName->dwSize = sizeof(RASENTRYNAME);
        //
        // Call the RAS API, bail on the loop if we are successful or an unknown
        // error occurs.
        //
        dwErr = RasEnumEntries(
                    NULL,
                    cszPhoneBook,
                    lpRasEntryName,
                    &dwCb,
                    &dwEntries);
        if (ERROR_BUFFER_TOO_SMALL != dwErr)
        {
            break;
        }
    }
    //
    // In the success case print the names of the entries.
    //
    if (ERROR_SUCCESS == dwErr)
    {
        DWORD i;
        for (i = 0; i < dwEntries; i++)
        {
			std::string oszEntry( lpRasEntryName[i].szEntryName );
			olstRet.Add( oszEntry );
        }
    }
    else
    {
		printf( "RasEnumEntries failed: Error = %d.",  dwErr );
    }
    //
    // Free the memory if necessary.
    //
    if (NULL != lpRasEntryName)
    {
        HeapFree(GetProcessHeap(), 0, lpRasEntryName);
        lpRasEntryName = NULL;
    }

	return olstRet;
}

void 
CEMSRAS::SetConnection( const char* cszName, const char* cszPhoneBook )
{
	if( cszName )
		m_oszName = cszName;

	if( cszPhoneBook )
		m_oszPhoneBook = cszPhoneBook;
}

void 
CEMSRAS::Dial()
{
	_GetConnectionHandle();

	if( NULL == m_hRASConnection )
	{
		if( m_pLogger )
		{
			LOG4CXX_DEBUG( m_pLogger, "RAS Dial command invoked.  No handle to a RAS connection currently held.");
		}

		if( !m_oszName.empty() )
		{
			//_ForceDialAll();

			RASDIALPARAMS strDialParams = _GetDialParams();

			DWORD dwRet = RasDial( NULL, m_oszPhoneBook.empty() ? NULL : m_oszPhoneBook.c_str(), &strDialParams, 0, NULL, &m_hRASConnection );

			if( 0 != dwRet )
			{
				if( m_pLogger )
				{
					LOG4CXX_ERROR( m_pLogger, "Failure dialing.  Error number=" << dwRet << "." );
					//LOG4CXX_DEBUG( m_pLogger, "Connection status:  " << GetStatus().c_str() << "." );
				}

				Hangup();

				// Often get this the first time:  ERROR_FROM_DEVICE
				if( ERROR_FROM_DEVICE == dwRet )
				{
					if( m_pLogger )
					{
						LOG4CXX_INFO( m_pLogger, "Device error.  Attempting dial again.");
					}

					dwRet = RasDial( NULL, m_oszPhoneBook.empty() ? NULL : m_oszPhoneBook.c_str(), &strDialParams, 0, NULL, &m_hRASConnection );
				}

				if( 0 != dwRet )
				{
					Hangup();
					THROW_RUNTIME_EXCEPTION( dwRet );
				}
			}

			if( m_pLogger )
			{
				LOG4CXX_INFO( m_pLogger, "RAS status = " << GetStatus().c_str() << "." );
			}
		}
		else
		{
			if( m_pLogger )
			{
				LOG4CXX_WARN( m_pLogger, "RAS Dial command invoked, but no dial interface specified.");
			}
		}
	}
	else
	{
		if( m_pLogger )
		{
			LOG4CXX_WARN( m_pLogger, "RAS Dial command invoked, but a handle to a RAS connection is already held.  Ignoring dial request.")
		}
	}
}

void 
CEMSRAS::Hangup()
{
	_GetConnectionHandle();

	if( NULL != m_hRASConnection )
	{
		if( m_pLogger )
		{
			LOG4CXX_DEBUG( m_pLogger, "RAS Hangup command invoked.  A handle to a RAS connection is currently held.  RAS hangup will be attempted.")
		}

		DWORD dwRet = RasHangUp( m_hRASConnection );

		if( 0 != dwRet )
		{
			if( m_pLogger )
			{
				LOG4CXX_ERROR( m_pLogger, "Error executing RAS hangup.  Error code:  " << dwRet << "." );
			}

			THROW_RUNTIME_EXCEPTION( dwRet );
		}

		// According to MSDN documentation, should wait for it to shutdown by calling RasGetConnectStatus
		// until it returns ERROR_INVALID_HANDLE.
		// We'll use a maximum time of 30 seconds.
		time_t timeStart = time(&timeStart);
		time_t timeNow;

		bool bDisconnected = false;

		bool bLogOnce = false;
		while( !bDisconnected &&
				(time(&timeNow) < ( timeStart + 30 )) )
		{
			if( m_pLogger )
			{
				if( !bLogOnce )
				{
					LOG4CXX_DEBUG( m_pLogger, "RAS hangup command invoked.  Waiting for completion.");
					bLogOnce = true;
				}
			}


			Sleep( 10 );

			RASCONNSTATUS strStatus;
			memset( &strStatus, 0, sizeof(strStatus) );
			strStatus.dwSize = sizeof(strStatus);

			DWORD dwStatusRet = RasGetConnectStatus( m_hRASConnection, &strStatus );

			if( ERROR_INVALID_HANDLE == dwStatusRet )
			{
				bDisconnected = true;
				
				if( m_pLogger )
				{
					LOG4CXX_INFO( m_pLogger, "RAS hangup complete.");
				}
			}
		}

		if( !bDisconnected )
		{
			// Try it again.  Sometimes the first connection needs two hangup attempts.
			dwRet = RasHangUp( m_hRASConnection );

			if( 0 != dwRet )
			{
				if( m_pLogger )
				{
					LOG4CXX_WARN( m_pLogger, "RAS hangup not confirmed.");
				}
			}
		}
		
		m_hRASConnection = NULL;
	}
	else
	{
		if( m_pLogger )
		{
			LOG4CXX_DEBUG( m_pLogger, "RAS Hangup command invoked.  No current handle to a RAS connection is held.  Ignoring hangup request.")
		}
	}
}

bool 
CEMSRAS::IsConnected()
{
	bool bRet = false;

	_GetConnectionHandle();

	if( NULL != m_hRASConnection )
	{
		RASCONNSTATUS strStatus;
		memset( &strStatus, 0, sizeof(strStatus) );
		strStatus.dwSize = sizeof(strStatus);

		DWORD dwRet = RasGetConnectStatus( m_hRASConnection, &strStatus );

		m_hRASConnection = NULL;

		if( 0 != dwRet )
		{
			THROW_RUNTIME_EXCEPTION( HRESULT_FROM_WIN32( dwRet ) );
		}

		if( RASCS_Connected == strStatus.rasconnstate )
			bRet = true;
	
	}

	return bRet;
}

std::string 
CEMSRAS::GetStatus()
{
	std::string oszRet = "Disconnected";

	_GetConnectionHandle();

	if( NULL != m_hRASConnection )
	{
		RASCONNSTATUS strStatus;
		memset( &strStatus, 0, sizeof(strStatus) );
		strStatus.dwSize = sizeof(strStatus);

		DWORD dwRet = RasGetConnectStatus( m_hRASConnection, &strStatus );

		m_hRASConnection = NULL;

		if( 0 != dwRet )
		{
			if( m_pLogger )
			{
				LOG4CXX_ERROR( m_pLogger, "Failed to retrieve RAS connection status.  Error code:  " << dwRet << "." );
			}

			THROW_RUNTIME_EXCEPTION( dwRet );
		}

		switch( strStatus.rasconnstate )
		{
			case RASCS_OpenPort:
				oszRet = "The communication port is about to be opened.";
				break;
			case RASCS_PortOpened:
				oszRet = "The communication port has been opened successfully.";
				break;
			case RASCS_ConnectDevice:
				oszRet = "A device is about to be connected.";
				break;
			case RASCS_DeviceConnected:
				oszRet = "A device has connected successfully.";
				break;
			case RASCS_AllDevicesConnected:
				oszRet = "All devices in the device chain have successfully connected. At this point, the physical link is established.";
				break;
			case RASCS_Authenticate:
				oszRet = "The authentication process is starting. Remote access does not allow the remote client to generate any traffic on the LAN until authentication has been successfully completed.";
				break;
			case RASCS_AuthNotify:
				oszRet = "An authentication event has occurred.";
				break;
			case RASCS_AuthRetry:
				oszRet = "The client has requested another validation attempt with a new user name/password/domain.";
				break;
			case RASCS_AuthCallback:
				oszRet = "he remote access server has requested a callback number.";
				break;
			case RASCS_AuthChangePassword:
				oszRet = "The client has requested to change the password on the account.";
				break;
			case RASCS_AuthProject:
				oszRet = "The projection phase is starting.";
				break;
			case RASCS_AuthLinkSpeed:
				oszRet = "The link-speed calculation phase is starting.";
				break;
			case RASCS_AuthAck:
				oszRet = "An authentication request is being acknowledged.";
				break;
			case RASCS_ReAuthenticate:
				oszRet = "Reauthentication (after callback) is starting.";
				break;
			case RASCS_Authenticated:
				oszRet = "The client has successfully completed authentication.";
				break;
			case RASCS_PrepareForCallback:
				oszRet = "The line is about to disconnect in preparation for callback.";
				break;
			case RASCS_WaitForModemReset:
				oszRet = "The client is delaying in order to give the modem time to reset itself in preparation for callback.";
				break;
			case RASCS_WaitForCallback:
				oszRet = "The client is waiting for an incoming call from the remote access server.";
				break;
			case RASCS_Projected:
				oszRet = "Projection result information is available. ";
				break;
#if (WINVER >= 0x400) 
			case RASCS_StartAuthentication:    // Windows 95 only 
				oszRet = "User authentication is being initiated or retried.";
				break;
			case RASCS_CallbackComplete:       // Windows 95 only 
				oszRet = "The client has been called back and is about to resume authentication.";
				break;
			case RASCS_LogonNetwork:           // Windows 95 only 
				oszRet = "The client is logging on to the network.";
				break;
#endif 
			case RASCS_SubEntryConnected:
				oszRet = "Dialing a multilink phone-book entry.  A subentry has been connected during the dialing process.";
				break;
			case RASCS_SubEntryDisconnected:
				oszRet = "Dialing a multilink phone-book entry.  A subentry has been disconnected during the dialing process.";
				break;
			case RASCS_PAUSED:
				oszRet = "Paused";
				break;
			case RASCS_RetryAuthentication:
				oszRet = "In retry authentication state supported by RASPHONE.EXE.";
				break;
			case RASCS_CallbackSetByCaller:
				oszRet = "In callback state supported by RASPHONE.EXE";
				break;
			case RASCS_PasswordExpired:
				oszRet = "In change password state supported by RASPHONE.EXE.";
				break;
#if (WINVER >= 0x500)
			case RASCS_InvokeEapUI:
				oszRet = "In paused state for custom authentication UI";
				break;
#endif
			case RASCS_Connected:
				oszRet = "Connected";
				break;
			case RASCS_Disconnected:
				oszRet = "Disconnected";
				break;
			default:
				oszRet = "Unrecognized state.";
				break;
		}
	}
	else
	{
		if( m_pLogger )
		{
			LOG4CXX_DEBUG( m_pLogger, "RAS status requested, but no current handle to an open connection.");
		}
	}

	if( m_pLogger )
	{
		LOG4CXX_DEBUG( m_pLogger, "Current RAS state:  " << oszRet.c_str() << "." );
	}

	return oszRet;
}

RASDIALPARAMS 
CEMSRAS::_GetDialParams()
{
	RASDIALPARAMS strRet;
	memset( &strRet, 0, sizeof(strRet) );
	strRet.dwSize = sizeof(strRet);

	if( !m_oszName.empty() )
	{
#ifdef UNICODE
		wcsncpy( strRet.szEntryName, CEMSConversionUtil::ConvertToString( m_oszName.c_str() ).c_str(), RAS_MaxEntryName );
#else
		strncpy( strRet.szEntryName, m_oszName.c_str(), RAS_MaxEntryName );
#endif

		BOOL bPwdSaved = FALSE;
		DWORD dwRet = RasGetEntryDialParams( m_oszPhoneBook.empty() ? NULL : m_oszPhoneBook.c_str(), &strRet, &bPwdSaved );

		if( 0 != dwRet )
		{
			THROW_RUNTIME_EXCEPTION(dwRet);
		}
	}

	return strRet;
}

RASENTRY
CEMSRAS::_GetEntryProperties()
{
	RASENTRY strRet;
	memset( &strRet, 0, sizeof(strRet) );
	strRet.dwSize = sizeof(strRet);

	if( !m_oszName.empty() )
	{
		BOOL bPwdSaved = FALSE;
		DWORD dwRet = RasGetEntryProperties( m_oszPhoneBook.empty() ? NULL : m_oszPhoneBook.c_str(),
											m_oszName.c_str(),
											&strRet,
											&strRet.dwSize,
											NULL,
											NULL );

		if( 0 != dwRet )
		{
			THROW_RUNTIME_EXCEPTION( dwRet );
		}

		if( (strRet.dwfOptions & RASEO_RemoteDefaultGateway) == RASEO_RemoteDefaultGateway )
		{
			if( m_pLogger )
			{
				LOG4CXX_DEBUG( m_pLogger, "Routing will be through dial-up adapter.");
			}
		}
		else
		{
			if( m_pLogger )
			{
				LOG4CXX_INFO( m_pLogger, "Default route not modified.");
			}
		}
	}

	return strRet;
}

void
CEMSRAS::_ForceDialAll()
{
	RASENTRY strRAS = _GetEntryProperties();
	//strRAS.dwDialMode = RASEDM_DialAll;
	strRAS.dwfOptions ^= RASEO_RemoteDefaultGateway;

	DWORD dwRet = RasSetEntryProperties( m_oszPhoneBook.empty() ? NULL : m_oszPhoneBook.c_str(),
											m_oszName.c_str(),
											&strRAS,
											sizeof(strRAS),
											NULL,
											NULL );

	if( 0 != dwRet )
	{
		if( m_pLogger )
		{
			LOG4CXX_ERROR( m_pLogger, "Error setting RAS entry properties for " << m_oszName.c_str() << ".  Error code:  "  << dwRet );
		}
	}

	_GetEntryProperties();
}


void 
CEMSRAS::_GetConnectionHandle()
{
	if( NULL == m_hRASConnection )
	{
		// Don't have a handle yet.  This probably means that we haven't dialed.  Still can get the handle if the
		// connection is open.  It may have been opened via another mechanism (e.g., the RAS control panel).

		if( !m_oszName.empty() )
		{
			DWORD dwCb = sizeof(RASCONN);
			DWORD dwErr = ERROR_SUCCESS;
			DWORD dwRetries = 5;
			DWORD dwEntries = 0;
			RASCONN* lpRasEntryName = NULL;

			//
			// Loop through in case the information from RAS changes between calls.
			//
			while (dwRetries--)
			{
				//
				// If the memory is allocated, free it.
				//
				if (NULL != lpRasEntryName)
				{
					HeapFree(GetProcessHeap(), 0, lpRasEntryName);
					lpRasEntryName = NULL;
				}
				//
				// Allocate the size need for the RAS structure.
				//
				lpRasEntryName = (RASCONN*) HeapAlloc(GetProcessHeap(), 0, dwCb);
				if (NULL == lpRasEntryName)
				{
					dwErr = ERROR_NOT_ENOUGH_MEMORY;
					break;
				}
				//
				// Set the structure size for version checking purposes.
				//
				lpRasEntryName->dwSize = sizeof(RASCONN);
				//
				// Call the RAS API, bail on the loop if we are successful or an unknown
				// error occurs.
				//
				dwErr = RasEnumConnections	(
							lpRasEntryName,
							&dwCb,
							&dwEntries);
				if (ERROR_BUFFER_TOO_SMALL != dwErr)
				{
					break;
				}
			}
		   
			//
			// In the success case print the names of the entries.
			//
			if (ERROR_SUCCESS == dwErr)
			{
				if( m_pLogger )
				{
					LOG4CXX_INFO( m_pLogger, "Found " << dwEntries << " RAS connections.");
				}

				bool bFound = false;
				for (int i = 0; i < dwEntries && !bFound; i++)
				{
					if( m_pLogger )
					{
						LOG4CXX_DEBUG( m_pLogger, "Found RAS connection:  " << lpRasEntryName[i].szEntryName << "." );
					}

					if( 0 == stricmp( m_oszName.c_str(), lpRasEntryName[i].szEntryName) )
					{
						bFound = true;
						m_hRASConnection = lpRasEntryName[i].hrasconn;
						LOG4CXX_INFO( m_pLogger, "Found matching RAS connection:"  << lpRasEntryName[i].szEntryName << "." );

					}
				}
			}
			else
			{
				if( m_pLogger )
				{
					LOG4CXX_WARN( m_pLogger, "RasEnumConnections failed: Error = " <<  dwErr );
				}
			}
			//
			// Free the memory if necessary.
			//
			if (NULL != lpRasEntryName)
			{
				HeapFree(GetProcessHeap(), 0, lpRasEntryName);
				lpRasEntryName = NULL;
			}
		}
	}
}