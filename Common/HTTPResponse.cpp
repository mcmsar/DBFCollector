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

	$Log$
********************************************************************/

#include "httpresponse.h"
#include "emsexcpt.h"
#include "convutility.h"

CEMSHTTPResponse::CEMSHTTPResponse() : CApiObjBase( TEXT("CEMSHTTPResponse") ),
								m_ulBytes(0), m_abyData(0)
{
}

CEMSHTTPResponse::CEMSHTTPResponse( const CEMSHTTPResponse& x ) :
								CApiObjBase( TEXT("CEMSHTTPResponse") ),
								m_ulBytes(0), m_abyData(0)
{
	SetResponse( x.m_ulBytes, x.m_abyData );
}

CEMSHTTPResponse::~CEMSHTTPResponse()
{
	if( m_abyData )
	{
		delete[] m_abyData;
		m_abyData = 0;
	}
}

void 
CEMSHTTPResponse::SetResponse( const ULONG culBytes, const BYTE* cabyData )
{
	if( culBytes > 0 )
	{
		m_ulBytes = culBytes;

		m_abyData = new BYTE[ m_ulBytes ];

		if( !m_abyData )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( m_abyData, 0, m_ulBytes );

		if( m_abyData )
			memcpy( m_abyData, cabyData, m_ulBytes );
	}
}

std::wstring 
CEMSHTTPResponse::GetResponseAsString()
{
	std::wstring owszRet;

	if( m_abyData )
	{
		owszRet = CEMSConversionUtil::ConvertToString( m_ulBytes, m_abyData );	
	}


	return owszRet;
}

void 
CEMSHTTPResponse::GetResponse( ULONG& rulBytes, BYTE*& rabyData )
{
	if( m_ulBytes > 0 )
	{
		rulBytes = m_ulBytes;

		rabyData = new BYTE[ rulBytes ];

		if( !rabyData )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( rabyData, 0, rulBytes );

		memcpy( rabyData, m_abyData, rulBytes );
	}
}