/*********************************************************************
*	Copyright (c) 2004 by EMS Technologies, Inc.,
*	All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log$
********************************************************************/

#ifndef __GUI_UTILITIES_H__
#define __GUI_UTILITIES_H__

#include "messagetableaccessor.h"
#include "emsexcpt.h"

class CEMSGUIUtilities
{
	public:
		CEMSGUIUtilities( const EMS_RESULT cMsgIDDefault, const EMS_RESULT cMsgIDDialogTitle = 0 );
		CEMSGUIUtilities( const CEMSGUIUtilities& x );
		virtual ~CEMSGUIUtilities();

		void HandleError( HRESULT hr, CEMSLogMsgParam* pParam = NULL );
		void HandleException( CEMSException& e );
		void HandleException();
		std::wstring GetMessageText( const EMS_RESULT cMsgID );
		std::wstring GetDialogBoxTitle();
		std::wstring GetDisplayMessageText( const EMS_RESULT cMsgID );

	private:
		void _DisplayErrorMessage( const wchar_t* cwszErrorMsg );

	private:
		CEMSMessageTableAccessor m_oMsgTable;
		EMS_RESULT m_MsgIDDefault;
		EMS_RESULT m_MsgIDDialogTitle;
};

#endif
