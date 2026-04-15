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

#include "iphelper.h"
#include "convutility.h"
#include <winsock2.h>
#include <iphlpapi.h>

CEMSIPHelper::CEMSIPHelper()
{
}

CEMSIPHelper::CEMSIPHelper( const CEMSIPHelper& x)
{
}

CEMSIPHelper::~CEMSIPHelper()
{
}

std::string 
CEMSIPHelper::GetIPAddress( const char* cszAdapter )
{
	std::string oszRet;
	
	if( cszAdapter )
	{
		std::wstring owszAdapter = CEMSConversionUtil::ConvertToString( cszAdapter );

		// This code is taken from the MSDN docs example for the GetAdaptersAddresses function.

		PIP_ADAPTER_ADDRESSES AdapterAddresses = NULL;
		ULONG ulOutBufferLength = 0;
		ULONG ulRetVal = 0, i;    
	    
		// The size of the buffer can be different 
		// between consecutive API calls.
		// In most cases, i < 2 is sufficient;
		// One call to get the size and one call to get the actual parameters.
		// But if one more interface is added or addresses are added, 
		// the call again fails with BUFFER_OVERFLOW. 
		// So the number is picked slightly greater than 2. 
		// We use i <5 in the example
		for (i = 0; i < 5; i++) 
		{
			ulRetVal = 	GetAdaptersAddresses( AF_INET, 0, NULL, AdapterAddresses, &ulOutBufferLength);
	        
			if (ulRetVal != ERROR_BUFFER_OVERFLOW) {
				break;
			}

			if (AdapterAddresses != NULL) 
			{
				HeapFree(GetProcessHeap(), 0, AdapterAddresses );
				AdapterAddresses = NULL;
			}
	        
			AdapterAddresses = (PIP_ADAPTER_ADDRESSES) HeapAlloc(GetProcessHeap(), 0, ulOutBufferLength);
			if (AdapterAddresses == NULL) 
			{
				ulRetVal = GetLastError();
				break;
			}
		}

		if( ulRetVal == NO_ERROR ) 
		{
			// If successful, output some information from the data we received
			PIP_ADAPTER_ADDRESSES AdapterList = AdapterAddresses;
			while(AdapterList && oszRet.empty() ) 
			{
				if( 0 == wcsicmp( owszAdapter.c_str(), AdapterList->FriendlyName ) )
				{
					// We're assuming here that what we want is the first of a possible list of
					// IP addresses of type "UNICAST".
					oszRet = GetIP( *AdapterList->FirstUnicastAddress->Address.lpSockaddr );
				}

				AdapterList = AdapterList->Next;
			}
		}
		else 
		{ 
			LPVOID MsgBuf;
			    
			if (FormatMessage( 
				FORMAT_MESSAGE_ALLOCATE_BUFFER | 
				FORMAT_MESSAGE_FROM_SYSTEM | 
				FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				ulRetVal,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
				(LPTSTR) &MsgBuf,
				0,
				NULL )) 
			{
				//LOG4CXX_ERROR( m_pLogger, "Error occurred while enumerating network adpaters:  " << (char*) MsgBuf << "." );
				LocalFree(MsgBuf);
			}
			else
			{
				//LOG4CXX_ERROR( m_pLogger, "Error occurred while enumerating network adpaters.");
			}
		}  

		if (AdapterAddresses != NULL) 
		{
			HeapFree(GetProcessHeap(), 0, AdapterAddresses );
			AdapterAddresses = NULL;
		}
	}

	return oszRet;
}

std::string 
CEMSIPHelper::GetIP( const struct sockaddr cstrAddr )
{
	std::string oszRet;

	// NOTE:  Assuming an IPv4 address here.
	oszRet = inet_ntoa( *((in_addr*) &cstrAddr.sa_data[2]) );

	return oszRet;
}