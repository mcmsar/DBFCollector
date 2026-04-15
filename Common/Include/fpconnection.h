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

#ifndef __FP_CONNECTION_H__
#define __FP_CONNECTION_H__

#include "aobjbase.h"
#include "emstle.h"
#include <string>

interface IEMSFP;

class CEMSFPConnection : public CApiObjBase
{
	public:
		CEMSFPConnection();
		CEMSFPConnection( const wchar_t* cwszURL, const wchar_t* cwszUser, const wchar_t* cwszPwd );
		CEMSFPConnection( const CEMSFPConnection& x );
		~CEMSFPConnection();

		void SetURL( const wchar_t* cwszURL ) { m_owszURL = cwszURL; }
		std::wstring GetURL() const { return m_owszURL; }

		void SetUser( const wchar_t* cwszUser ) { m_owszUser = cwszUser; }
		std::wstring GetUser() const { return m_owszUser; }

		void SetPwd( const wchar_t* cwszPwd ) { m_owszPwd = cwszPwd; }
		std::wstring GetPwd() const { return m_owszPwd; }

		void SetOrbits( const ULONG culOrbits, const EMSTLERECORD* caTLEs );
		
		void Restart();
		
		void Reboot( const BOOL cbForce );

	private:
		IEMSFP* _GetFP();

	private:
		std::wstring m_owszURL;
		std::wstring m_owszUser;
		std::wstring m_owszPwd;

		IEMSFP* m_pFP;

};

#endif