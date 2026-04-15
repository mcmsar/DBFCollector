/********************************************************************
*	Module:			ESecDesc.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description:	Implementation of CEMSSecurityDescriptor class 	
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	
*					
*
*********************************************************************
*	              Copyright (c) 2001 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2001/07/5	rvw	start

********************************************************************/
#include "esecdesc.h"

CEMSSecurityDescriptor::CEMSSecurityDescriptor()
{
	m_lpSD = 0;
	m_lpOwner = 0;
	m_lpGroup = 0;
}

CEMSSecurityDescriptor::~CEMSSecurityDescriptor()
{
	if ( m_lpSD )
	{
		delete m_lpSD;
		m_lpSD = 0;
	}

	if ( m_lpOwner )
	{
		delete m_lpOwner;
		m_lpOwner = 0;
	}

	if ( m_lpGroup )
	{
		delete m_lpGroup;
		m_lpGroup = 0;
	}
}

DWORD CEMSSecurityDescriptor::_GetTokenInfoSize( HANDLE hToken, int nTokenInfoType )
{
	DWORD dwSize = 0;

	if ( hToken )
	{
		if ( !GetTokenInformation( hToken, 
				(TOKEN_INFORMATION_CLASS)nTokenInfoType, 0, 0, &dwSize ) )
		{
			if ( GetLastError() != ERROR_INSUFFICIENT_BUFFER )
				dwSize = 0;
		}
	}	

	return dwSize;
}

EMS_RESULT CEMSSecurityDescriptor::_GetTokenInfo( HANDLE hToken, int nTokenInfoType, LPVOID *lplpTokenInfo )
{
	EMS_RESULT hr = EMS_FALSE;

	if ( lplpTokenInfo )
	{
		DWORD dwSize = 0;

		*lplpTokenInfo = 0;

		dwSize = _GetTokenInfoSize( hToken, nTokenInfoType ); 

		if ( dwSize )
		{
			*lplpTokenInfo = (LPVOID)new BYTE[ dwSize ];

			if ( *lplpTokenInfo )
			{
				if ( GetTokenInformation( hToken, 
						(TOKEN_INFORMATION_CLASS)nTokenInfoType,
						*lplpTokenInfo, dwSize, &dwSize ) )
				{
					hr = EMS_OK;
				}
				else
				{
					hr = HRESULT_FROM_WIN32( GetLastError() );
				}
			}
		}
	}

	return hr;
}

EMS_RESULT CEMSSecurityDescriptor::_CopySid( PSID *lplpNewSid, PSID lpOldSid )
{
	EMS_RESULT hr = EMS_FALSE;

	if ( lplpNewSid )
	{
		*lplpNewSid = 0;

		if ( lpOldSid && IsValidSid( lpOldSid ) )
		{
			DWORD dwSize = GetLengthSid( lpOldSid );

			if ( dwSize )
			{
				*lplpNewSid = (PSID)new BYTE[ dwSize ];

				if ( *lplpNewSid )
				{
					if ( CopySid( dwSize, *lplpNewSid, lpOldSid ) )
						hr = EMS_OK;
					else
						hr = HRESULT_FROM_WIN32( GetLastError() );
				}
			}
		}
	}

	return hr;
}

EMS_RESULT CEMSSecurityDescriptor::_GetTokenSids( HANDLE hToken, PSID *lplpUserSid, PSID *lplpGroupSid )
{
	EMS_RESULT hr = EMS_FALSE;

	if ( hToken )
	{
		PTOKEN_USER lpTokenUser = 0;
		PTOKEN_PRIMARY_GROUP lpTokenGroup = 0;

		hr = _GetTokenInfo( hToken, TokenUser, (LPVOID *)&lpTokenUser );

		if ( ( hr == EMS_OK ) && lpTokenUser )
		{
			hr = _CopySid( lplpUserSid, lpTokenUser->User.Sid );

			delete lpTokenUser;
			lpTokenUser = 0;
		}

		hr = _GetTokenInfo( hToken, TokenPrimaryGroup, (LPVOID *)&lpTokenGroup );

		if ( ( hr == EMS_OK ) && lpTokenGroup )
		{
			hr = _CopySid( lplpGroupSid, lpTokenGroup->PrimaryGroup );

			delete lpTokenGroup;
			lpTokenGroup = 0;
		}
	}

	return hr;
}


EMS_RESULT CEMSSecurityDescriptor::_GetThreadSids( PSID *lplpUserSid, PSID *lplpGroupSid )
{
	EMS_RESULT hr = EMS_FALSE;
	HANDLE hToken = 0;

	if ( lplpUserSid )
		*lplpUserSid = 0;

	if ( lplpGroupSid )
		*lplpGroupSid = 0;

	if ( OpenThreadToken( GetCurrentThread(), TOKEN_QUERY, FALSE, &hToken ) )
	{
		hr = _GetTokenSids( hToken, lplpUserSid, lplpGroupSid );

		CloseHandle( hToken );
	}
	else
		hr = HRESULT_FROM_WIN32( GetLastError() );
	
	return hr;
}

EMS_RESULT CEMSSecurityDescriptor::_GetProcessSids( PSID *lplpUserSid, PSID *lplpGroupSid )
{
	EMS_RESULT hr = EMS_FALSE;
	HANDLE hToken = 0;

	if ( lplpUserSid )
		*lplpUserSid = 0;

	if ( lplpGroupSid )
		*lplpGroupSid = 0;

	if ( OpenProcessToken( GetCurrentProcess(), TOKEN_QUERY, &hToken ) )
	{
		hr = _GetTokenSids( hToken, lplpUserSid, lplpGroupSid );

		CloseHandle( hToken );
	}
	else
		hr = HRESULT_FROM_WIN32( GetLastError() );
	
	return hr;
}

EMS_RESULT CEMSSecurityDescriptor::Initialize( void )
{
	EMS_RESULT hr = EMS_OK;

	if ( m_lpSD )
	{
		delete m_lpSD;
		m_lpSD = 0;
	}

	if ( m_lpOwner )
	{
		delete m_lpOwner;
		m_lpOwner = 0;
	}

	if ( m_lpGroup )
	{
		delete m_lpGroup;
		m_lpGroup = 0;
	}

	m_lpSD = new SECURITY_DESCRIPTOR;

	if ( m_lpSD )
	{
		if ( !InitializeSecurityDescriptor( m_lpSD, SECURITY_DESCRIPTOR_REVISION ) )
		{
			hr = HRESULT_FROM_WIN32( GetLastError() );

			delete m_lpSD;

			m_lpSD = 0;
		}
		else
		{
			// set the DACL to allow EVERYONE
			SetSecurityDescriptorDacl( m_lpSD, TRUE, 0, FALSE );
		}
	}
	else
		hr = EMS_NO_MEMORY;
	
	return hr;
}

EMS_RESULT CEMSSecurityDescriptor::InitializeFromThreadToken( void )
{
	EMS_RESULT hr = Initialize();

	if ( hr == EMS_OK )
	{
		PSID lpUserSid = 0, lpGroupSid = 0;

		hr = _GetThreadSids( &lpUserSid, &lpGroupSid );

		if ( HRESULT_CODE(hr) == ERROR_NO_TOKEN ) // && bRevertToProcessToken
		{
			hr = _GetProcessSids( &lpUserSid, &lpGroupSid );
		}

		if ( hr == EMS_OK )
		{
			hr = SetOwner( lpUserSid );

			if ( hr == EMS_OK )
				hr = SetGroup( lpGroupSid );
		}

		if ( lpUserSid )
		{
			delete lpUserSid;
			lpUserSid = 0;
		}

		if ( lpGroupSid )
		{
			delete lpGroupSid;
			lpGroupSid = 0;
		}
	}
	
	return hr;
}

EMS_RESULT CEMSSecurityDescriptor::SetOwner( PSID lpOwner )
{
	EMS_RESULT hr = EMS_FALSE;

	if ( m_lpSD )
	{
		if ( SetSecurityDescriptorOwner( m_lpSD, 0, FALSE ) )
			hr = EMS_OK;
		else
			hr = HRESULT_FROM_WIN32( GetLastError() );

		if ( hr == EMS_OK ) 
		{
			if ( m_lpOwner )
			{
				delete m_lpOwner;
				m_lpOwner = 0;
			}

			if ( lpOwner )
			{
				hr = _CopySid( &m_lpOwner, lpOwner );

				if ( hr == EMS_OK )
				{
					if ( !SetSecurityDescriptorOwner( m_lpSD, m_lpOwner, FALSE ) )
					{
						hr = HRESULT_FROM_WIN32( GetLastError( ) );

						delete m_lpOwner;

						m_lpOwner = 0;
					}
				}
			}
		}
	}

	return hr;
}

EMS_RESULT CEMSSecurityDescriptor::SetGroup( PSID lpGroup )
{
	EMS_RESULT hr = EMS_FALSE;

	if ( m_lpSD )
	{
		if ( SetSecurityDescriptorGroup( m_lpSD, 0, FALSE ) )
			hr = EMS_OK;
		else
			hr = HRESULT_FROM_WIN32( GetLastError() );

		if ( hr == EMS_OK ) 
		{
			if ( m_lpGroup )
			{
				delete m_lpGroup;
				m_lpGroup = 0;
			}

			if ( lpGroup )
			{
				hr = _CopySid( &m_lpGroup, lpGroup );

				if ( hr == EMS_OK )
				{
					if ( !SetSecurityDescriptorGroup( m_lpSD, m_lpGroup, FALSE ) )
					{
						hr = HRESULT_FROM_WIN32( GetLastError( ) );

						delete m_lpGroup;

						m_lpGroup = 0;
					}
				}
			}
		}
	}
	return hr;
}

