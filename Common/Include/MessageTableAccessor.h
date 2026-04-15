/*********************************************************************
*	Copyright (c) 2004-2005 by EMS Technologies, Inc.,
*					All rights reserved
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

#ifndef __MESSAGE_TABLE_ACCESSOR_H__
#define __MESSAGE_TABLE_ACCESSOR_H__

#include "LangResources.h"

class CEMSMessageTableAccessor : public CEMSLangResources
{
	public:
		CEMSMessageTableAccessor();
		CEMSMessageTableAccessor( const CEMSMessageTableAccessor& x );
		~CEMSMessageTableAccessor();

		std::wstring GetMessage( const ULONG culMsgID );
		std::wstring GetMessage( const ULONG culMsgID, CEMSLogMsgParam& oLogParam );
};

#endif