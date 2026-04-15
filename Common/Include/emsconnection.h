/****************************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of EMS Technologies, Inc.
*
****************************************************************************/

/****************************************************************************

  Revision Record

	$Log:
	$
****************************************************************************/


#ifndef __EMS_CONNECTION_H__
#define __EMS_CONNECTION_H__

#include "aobjbase.h"
//#include "dal.h"
//#include "emsadohelper.h"

#define _USEADO
#ifdef _USEADO
#pragma warning(push)
#pragma warning(disable:4146)
#import <msado15.dll> named_guids, rename("EOF", "EndOfFile" )
#pragma warning(pop)
using namespace ADODB;
#endif

#include <string>

//! A database connection class.
class CEMSConnection : public CApiObjBase
{	
	public:
		CEMSConnection();
		CEMSConnection( const wchar_t* cwszCon );
		CEMSConnection( const CEMSConnection& x );
		~CEMSConnection();

		void Open( const wchar_t* cwszConString );
		void Close();
		void BeginTrans();
		void CommitTrans();
		void RollbackTrans();
		std::wstring GetProvider();
		ULONG Execute( const wchar_t* cwszCmd );

		// Caller must release.
		IDispatch* Get();

		
	private:
		_ConnectionPtr	_GetConPtr();
		void			_HandleException( const _com_error& croExcpt, const _ConnectionPtr& crspConn );
		bool			_FilterAlarm( const HRESULT chrErrorCode );
		bool			_IsWarning( const HRESULT chrErrorCode );

	private:	// data
		_ConnectionPtr		m_spConn;
		
};

#endif	// __EMS_CONNECTION_H__