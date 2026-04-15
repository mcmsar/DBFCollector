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

#ifndef __COM_ERROR_HANDLER_H__
#define __COM_ERROR_HANDLER_H__

#include "emsexcpt.h"
#include "messagetableaccessor.h"
#include <string>

//! @class CEMSCOMErrorHandler
//! This class is used to manage COM errors.  
class CEMSCOMErrorHandler
{
	public:
		CEMSCOMErrorHandler();
		CEMSCOMErrorHandler( const CEMSCOMErrorHandler& x );
		virtual ~CEMSCOMErrorHandler();

		//! @fn void SetErrorInfo( CEMSException& oException )
		//! Store COM error information (in the form of an error message) on the thread based on the input exception.
		void SetErrorInfo( CEMSException& oException );

		//! @fn void SetErrorInfo( const EMS_RESULT chrError )
		//! Not implemented
		void SetErrorInfo( const EMS_RESULT chrError );

		//! @fn std::wstring GetErrorInfoFromThread()
		//! Reads error information (in the form of an error message) associated with the thread.
		//! Note that calling this method clears the error object on the associated thread.
		//! Call SetErrorInfo( const wchar_t* cwszErrorInfo ) to reset the error object.
		std::wstring GetErrorInfoFromThread();

		//! @fn void SetErrorInfo( const wchar_t* cwszErrorInfo )
		//! Store COM error information (in the form of an error message) on the thread based on the input message string.
		void SetErrorInfo( const wchar_t* cwszErrorInfo );

	private:
		std::wstring	_GetErrorMessage( CEMSException& oException );
//		HANDLE			_LoadMessageTable();
//		void			_UnloadMessageTable( HANDLE& hMsgTableDLL );
//		std::wstring	_GetMessageFilePath();
//		LPTSTR*			_GetParameterArray( CEMSLogMsgParam& oMsgParams );

	private:
//		std::wstring	m_wszMessageFilePath;

		CEMSMessageTableAccessor	m_oMsgTable;
};

#endif

