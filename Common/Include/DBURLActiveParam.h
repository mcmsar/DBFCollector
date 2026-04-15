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

#ifndef __DB_URL_ACTIVE_PARAM_H__
#define __DB_URL_ACTIVE_PARAM_H__

#include "aobjbase.h"
#include <string>

//! @class CEMSDBURLActiveParam
//! Encapsulates the Active Parameter portion of a Database URL Query.
class CEMSDBURLActiveParam : public CApiObjBase
{
	public:
		CEMSDBURLActiveParam();
		CEMSDBURLActiveParam( const CEMSDBURLActiveParam& x );
		~CEMSDBURLActiveParam();

		//! @fn void Set( const wchar_t* cwszActiveParam )
		//! Set the active parameter string.
		void Set( const wchar_t* cwszActiveParam );

		//! @fn std::wstring Get()
		//! Get the active parameter string.
		std::wstring Get();

		//! @fn std::wstring GetTable()
		//! Get the table name element from the active parameter string.
		std::wstring GetTable() { return m_owszTable; }

		//! @fn void SetTable( const wchar_t* cwszTable )
		//! Set the table name element of the active parameter string.
		void SetTable( const wchar_t* cwszTable ) { if( cwszTable ) m_owszTable = cwszTable; }
		
		//! @fn std::wstring GetColumn()
		//! Get the column name of the active parameter string.
		std::wstring GetColumn() { return m_owszColumn; }

		//! @fn void SetColumn( const wchar_t* cwszColumn )
		//! Set the column name of the active parameter string.
		void SetColumn( const wchar_t* cwszColumn ) { if( cwszColumn ) m_owszColumn = cwszColumn; }

		//! @fn std::wstring GetCriteria()
		//! Get the criteria parameter of the active parameter string.
		std::wstring GetCriteria() { return m_owszCriteria; }

		//! @fn void SetCriteria( const wchar_t* cwszCriteria )
		//! Set the criteria portion of the active parameter string.
		void SetCriteria( const wchar_t* cwszCriteria ) { if( cwszCriteria ) m_owszCriteria = cwszCriteria; }

		//! @fn ULONG GetPeriod()
		//! Get the period from the active parameter
		ULONG GetPeriod() { return m_ulPeriod; }

		//! @fn void SetPeriod( const ULONG culPeriod )
		//! Set the period for the active parameter.
		void SetPeriod( const ULONG culPeriod ) { m_ulPeriod = culPeriod; }

	private:
		void _Parse();
		void _Generate();
		void _Clear();

	private:
		std::wstring m_owszParam;

		std::wstring m_owszTable;
		std::wstring m_owszColumn;
		std::wstring m_owszCriteria;
		ULONG m_ulPeriod;

	private:
		static const wchar_t* ms_cwszActiveParamSep;
		static const wchar_t* ms_cwszActiveParamEquals;
};

#endif