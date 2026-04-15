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

#include "fpconnection.h"
#include "emsexcpt.h"

#include <initguid.h>
#include "fp.h"
#include "wsclient.h"

// {6AD1E7F2-BC7B-4055-9B09-F187F607780B}
DEFINE_GUID(CLSID_EMSFPProxy, 0x6ad1e7f2, 0xbc7b, 0x4055, 0x9b, 0x9, 0xf1, 0x87, 0xf6, 0x7, 0x78, 0xb);

CEMSFPConnection::CEMSFPConnection() : CApiObjBase( TEXT("CEMSFPConnection") ), m_pFP( NULL )
{
}

CEMSFPConnection::CEMSFPConnection( const wchar_t* cwszURL, const wchar_t* cwszUser, const wchar_t* cwszPwd )  : 
					CApiObjBase( TEXT("CEMSFPConnection") ), m_pFP( NULL ), m_owszURL( cwszURL ), m_owszUser( cwszUser ),
					m_owszPwd( cwszPwd )
{
}

CEMSFPConnection::CEMSFPConnection( const CEMSFPConnection& x ) : CApiObjBase( TEXT("CEMSFPConnection") ), m_pFP( x.m_pFP ), 
					m_owszURL( x.m_owszURL ), m_owszUser( x.m_owszUser ), m_owszPwd( x.m_owszPwd )
{
	if( m_pFP )
		m_pFP->AddRef();
}

CEMSFPConnection::~CEMSFPConnection()
{
	if( m_pFP )
	{
		m_pFP->Release();
		m_pFP = NULL;
	}
}

void 
CEMSFPConnection::SetOrbits( const ULONG culOrbits, const EMSTLERECORD* caTLEs )
{
	IEMSFP* pFP = NULL;

	try
	{
		pFP = _GetFP();

		if( !pFP )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		EMS_RESULT hr = pFP->SetOrbits( culOrbits, caTLEs );

		if( EMS_OK != hr )
		{
			THROW_RUNTIME_EXCEPTION(hr);
		}

		pFP->Release();
		pFP = NULL;
	}
	catch( ... )
	{
		if( pFP )
		{
			pFP->Release();
			pFP = NULL;
		}

		throw;
	}
}

void 
CEMSFPConnection::Restart()
{
	IEMSFP* pFP = NULL;

	try
	{
		pFP = _GetFP();

		if( !pFP )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		EMS_RESULT hr = pFP->Restart();

		if( EMS_OK != hr )
		{
			THROW_RUNTIME_EXCEPTION(hr);
		}

		pFP->Release();
		pFP = NULL;
	}
	catch( ... )
	{
		if( pFP )
		{
			pFP->Release();
			pFP = NULL;
		}

		throw;
	}
}

void 
CEMSFPConnection::Reboot( const BOOL cbForce )
{
	IEMSFP* pFP = NULL;

	try
	{
		pFP = _GetFP();

		if( !pFP )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		EMS_RESULT hr = pFP->Reboot( cbForce );

		if( EMS_OK != hr )
		{
			THROW_RUNTIME_EXCEPTION(hr);
		}

		pFP->Release();
		pFP = NULL;
	}
	catch( ... )
	{
		if( pFP )
		{
			pFP->Release();
			pFP = NULL;
		}

		throw;
	}
}

IEMSFP* 
CEMSFPConnection::_GetFP()
{
	IEMSFP* pRet = NULL;
	IEMSWSClient* pWSClient = NULL;

	if( !m_pFP )
	{
		EMS_RESULT hr = CoCreateInstance( CLSID_EMSFPProxy, NULL, CLSCTX_ALL, IID_IEMSWSClient, (void**) &pWSClient );

		if( EMS_OK != hr )
		{
			THROW_RUNTIME_EXCEPTION(hr);
		}

		hr = pWSClient->SetURL( m_owszURL.c_str() );

		if( EMS_OK != hr )
		{
			THROW_RUNTIME_EXCEPTION(hr);
		}

		hr = pWSClient->SetUsername( m_owszUser.c_str() );

		if( EMS_OK != hr )
		{
			THROW_RUNTIME_EXCEPTION(hr);
		}

		hr = pWSClient->SetPassword( m_owszPwd.c_str() );

		if( EMS_OK != hr )
		{
			THROW_RUNTIME_EXCEPTION(hr);
		}

		hr = pWSClient->QueryInterface( IID_IEMSFP, (void**) &m_pFP );

		if( EMS_OK != hr )
		{
			THROW_RUNTIME_EXCEPTION(hr);
		}
	}

	pRet = m_pFP;
	pRet->AddRef();

	return pRet;
}