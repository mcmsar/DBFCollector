/*********************************************************************
*	Copyright (c) 2011 by EMS Technologies, Inc.,
*					All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be
*	reproduced in whole or in part, in any form or by any means whatsoever
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef __JLOG_H__
#define __JLOG_H__

#include <string> 
#include "objectmap.h"

class CEMSjLog : public CApiObjBase
{
	public:
		CEMSjLog();
		CEMSjLog( const CEMSjLog& x );
		virtual ~CEMSjLog();

	public:
		void Set( const std::string& logString );

		std::string GetLog();

	private:
		void processToken( const std::string& token );

	private:
		std::string m_Log;

};


#endif