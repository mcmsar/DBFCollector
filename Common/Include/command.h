/*********************************************************************
*	Copyright (c) 2011 by EMS Technologies, Inc.,
*					All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be
*	reproduced in whole or in part, in any form or by any means whatsoever
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <string> 

#include "objectmap.h"


class CEMSCommand : public CApiObjBase
{
	public:
		CEMSCommand();
		CEMSCommand( const CEMSCommand& x );
		virtual ~CEMSCommand();

	public:
		/**
		* Command is input as a string in the form:  cmd=<somecommand>,<paramName1>=<somevalue>,<paramName2>=<anothervalue>
		* E.g., cmd=locate.setDuration,duration=1000
		*/
		void Set( const std::string& cmdString );

		std::string GetCmd();
		std::string GetParamValue( const std::string& paramKey );
		CEMSObjectMap<std::string,std::string> GetParamList();

	private:
		void processToken( const std::string& token );

	private:
		std::string m_Cmd;
		CEMSObjectMap<std::string,std::string> m_Params;

};


#endif