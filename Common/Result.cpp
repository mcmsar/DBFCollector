/*********************************************************************
*	              Copyright (c) 2004 by EMS Technologies, Inc.,
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


#include "result.h"
#include "messagetableaccessor.h"

CEMSResult::CEMSResult() : m_hrCode(EMS_OK), m_pException(0)
{
}

CEMSResult::CEMSResult( const CEMSResult& x ) : m_hrCode( x.m_hrCode ), m_wszMessage( x.m_wszMessage ),
												m_pException(0)
{
	if( x.m_pException )
		SetException( *(x.m_pException) );
}

CEMSResult::~CEMSResult()
{
	if( m_pException )
	{
		delete m_pException;
		m_pException = 0;
	}
}

EMS_RESULT 
CEMSResult::GetResultCode() 
{
	EMS_RESULT hr = m_hrCode;

	if( m_pException )
	{
		hr = m_pException->GetErrCode();
	}

	return hr;
}

void 
CEMSResult::SetResultMessage( const wchar_t* cwszMessage )
{
	if( cwszMessage )
	{
		m_wszMessage = cwszMessage;
	}
}

std::wstring 
CEMSResult::GetResultMessage()
{
	std::wstring wszRet;

	CEMSMessageTableAccessor oMsgTable;

	if( !m_wszMessage.empty() )
	{
		wszRet = m_wszMessage;
	}
	else if( m_pException )
	{
		wszRet = oMsgTable.GetMessage( m_pException->GetErrCode(), m_pException->GetParam() );
	}
	else
	{
		wszRet = oMsgTable.GetMessage( m_hrCode );
	}

	return wszRet;

}

void 
CEMSResult::SetException( CEMSException& oEx )
{
	if( m_pException )
	{
		delete m_pException;
		m_pException = 0;
	}

	m_pException = new CEMSException( oEx );
}
