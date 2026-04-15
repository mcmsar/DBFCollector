/*********************************************************************
*	              Copyright (c) 2005 by EMS Technologies, Inc.,
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

#include "include/dburlactiveparam.h"
#include "databaseresourcemsgs.h"
#include "emsexcpt.h"
#include "convutility.h"
#include <sstream>

const wchar_t* CEMSDBURLActiveParam::ms_cwszActiveParamSep = L".";
const wchar_t* CEMSDBURLActiveParam::ms_cwszActiveParamEquals = L"=";

CEMSDBURLActiveParam::CEMSDBURLActiveParam() : m_ulPeriod(0)
{
}

CEMSDBURLActiveParam::CEMSDBURLActiveParam( const CEMSDBURLActiveParam& x ) : m_owszParam( x.m_owszParam ),
															m_owszTable( x.m_owszTable ),
															m_owszColumn( x.m_owszColumn ),
															m_owszCriteria( x.m_owszCriteria ),
															m_ulPeriod( x.m_ulPeriod )
{
}

CEMSDBURLActiveParam::~CEMSDBURLActiveParam()
{
}

void 
CEMSDBURLActiveParam::Set( const wchar_t* cwszActiveParam )
{
	if( cwszActiveParam )
	{
		m_owszParam = cwszActiveParam;

		_Parse();
	}
}

std::wstring 
CEMSDBURLActiveParam::Get()
{
	_Generate();

	return m_owszParam;
}

void
CEMSDBURLActiveParam::_Parse()
{
	_Clear();

	// Active settings are of the form active=Table.Column.Period[.Criteria] where data in [] are optional.
	std::wstring::size_type iStart = m_owszParam.find( ms_cwszActiveParamEquals );
	if( m_owszParam.npos == iStart )
	{
		CEMSLogMsgParam oParam;
		oParam.AddString( m_owszParam.c_str() );

		throw CEMSException( EMS_DBRES_ACTIVE_PARAM_PARSE_FAILURE, oParam );
	}

	iStart += wcslen( ms_cwszActiveParamEquals );

	std::wstring::size_type iFirstSep = m_owszParam.find( ms_cwszActiveParamSep, iStart );

	if( m_owszParam.npos == iFirstSep )
	{
		CEMSLogMsgParam oParam;
		oParam.AddString( m_owszParam.c_str() );

		throw CEMSException( EMS_DBRES_ACTIVE_PARAM_PARSE_FAILURE, oParam );
	}

	m_owszTable = m_owszParam.substr( iStart, iFirstSep - iStart );
	
	std::wstring::size_type iSecondSep = m_owszParam.find( ms_cwszActiveParamSep, iFirstSep + wcslen(ms_cwszActiveParamSep) );

	if( m_owszParam.npos == iSecondSep )
	{
		CEMSLogMsgParam oParam;
		oParam.AddString( m_owszParam.c_str() );

		throw CEMSException( EMS_DBRES_ACTIVE_PARAM_NO_COLUMN, oParam );
	}

	m_owszColumn = m_owszParam.substr( iFirstSep + + wcslen(ms_cwszActiveParamSep), iSecondSep - iFirstSep - wcslen(ms_cwszActiveParamSep));

	std::wstring::size_type iThirdSep = m_owszParam.find( ms_cwszActiveParamSep, iSecondSep + + wcslen(ms_cwszActiveParamSep) );

	if( m_owszParam.npos != iThirdSep )
	{
		m_ulPeriod = CEMSConversionUtil::ConvertToULong( m_owszParam.substr( iSecondSep + wcslen(ms_cwszActiveParamSep), iThirdSep ).c_str() );

		m_owszCriteria = m_owszParam.substr( iThirdSep + wcslen(ms_cwszActiveParamSep), m_owszParam.length() - iThirdSep - wcslen(ms_cwszActiveParamSep) );

	}
	else
	{
		m_ulPeriod = CEMSConversionUtil::ConvertToULong( m_owszParam.substr( iSecondSep + wcslen(ms_cwszActiveParamSep), m_owszParam.length() - iSecondSep - wcslen(ms_cwszActiveParamSep) ).c_str() );
	}

	if( 0 == m_ulPeriod )
	{
		CEMSLogMsgParam oParam;
		oParam.AddString( m_owszParam.c_str() );

		throw CEMSException( EMS_DBRES_ACTIVE_PARAM_NO_PERIOD, oParam );
	}
}

void
CEMSDBURLActiveParam::_Generate()
{
	std::wstringstream wstrmBuf;

	wstrmBuf << m_owszTable << ms_cwszActiveParamSep << 
			m_owszColumn << ms_cwszActiveParamSep << m_ulPeriod;

	if( !m_owszCriteria.empty() )
	{
		wstrmBuf << m_owszCriteria;
	}

	m_owszParam = wstrmBuf.str();
}

void
CEMSDBURLActiveParam::_Clear()
{
	m_owszTable.erase();
	m_owszColumn.erase();
	m_owszCriteria.erase();
	m_ulPeriod = 0;
}