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

#ifndef __RESULT_H__
#define __RESULT_H__

#include "aobjbase.h"
#include "emsexcpt.h"
#include <string>

//! @class CEMSResult
//! This class is used to encapsulate method call results for 
//! return to a caller.
class CEMSResult : public CApiObjBase
{
	public:
		CEMSResult();
		CEMSResult( const CEMSResult& x );
		virtual ~CEMSResult();

		//! @fn void SetErrorCode( const EMS_RESULT chrCode )
		//! Store a result code.
		void SetResultCode( const EMS_RESULT chrCode ) { m_hrCode = chrCode; }

		//! @fn EMS_RESULT GetResultCode()
		//! Retrieve a result code.
		EMS_RESULT GetResultCode();

		//! @fn void SetResultMessage( const wchar_t* cwszMessage )
		//! Store a message string.
		void SetResultMessage( const wchar_t* cwszMessage );

		//! @fn std::wstring GetResultMessage()
		//! Retrieve a message string.  If necessary, the string
		//! will be constructed from a stored CEMSException object.
		std::wstring GetResultMessage();

		//! @fn void SetException( CEMSException& oEx )
		//! Store an exception.
		void SetException( CEMSException& oEx );

	private:
		EMS_RESULT		m_hrCode;
		std::wstring	m_wszMessage;
		CEMSException*	m_pException;

};

#endif