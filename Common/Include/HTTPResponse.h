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

#ifndef __HTTP_RESPONSE_H__
#define __HTTP_RESPONSE_H__

#include "aobjbase.h"
#include <string>

class CEMSHTTPResponse : public CApiObjBase
{
	public:
		CEMSHTTPResponse();
		CEMSHTTPResponse( const CEMSHTTPResponse& x );
		~CEMSHTTPResponse();

		//! Store response data.
		void SetResponse( const ULONG culBytes, const BYTE* cabyData );

		//! Retrieve response data as a string.
		std::wstring GetResponseAsString();

		//! Retrieve raw response data.  The caller must delete the returned data array.
		void GetResponse( ULONG& rulBytes, BYTE*& rabyData );

	private:
		ULONG	m_ulBytes;
		BYTE*	m_abyData;

};

#endif