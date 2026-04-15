/*********************************************************************
*	Copyright (c) 2011 by EMS Technologies, Inc.,
*					All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be
*	reproduced in whole or in part, in any form or by any means whatsoever
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#include "command.h"

CEMSCommand::CEMSCommand() : CApiObjBase(TEXT("CEMSCommand"))
{
}

CEMSCommand::CEMSCommand( const CEMSCommand& x ) : CApiObjBase(TEXT("CEMSCommand")),
												m_Cmd(x.m_Cmd), m_Params(x.m_Params)
{
}

CEMSCommand::~CEMSCommand()
{
}

void 
CEMSCommand::Set( const std::string& cmdString )
{
	if( !cmdString.empty() )
	{
		int len = cmdString.length();

		if( len > 0 )
		{
			std::string::size_type idxLastComma = 0;
			bool bMore = true;
			while( bMore )
			{
				std::string::size_type idxComma = cmdString.find(",", idxLastComma + 1 );

				if( std::string::npos != idxComma )
				{
					std::string token = cmdString.substr( idxLastComma, idxComma - idxLastComma);

					processToken( token );
				}
				else
				{
					// Anything else?
					if( idxLastComma < cmdString.length() -1 )
					{
						std::string token = cmdString.substr( idxLastComma, cmdString.length() - idxLastComma );
						processToken(token);
					}

					bMore = false;
				}

				idxLastComma = idxComma;
				idxLastComma++;	// skip past the "," separator
			}
		}
	}
}

std::string 
CEMSCommand::GetCmd()
{
	return m_Cmd;
}

std::string 
CEMSCommand::GetParamValue( const std::string& paramKey )
{
	return m_Params.Get(paramKey);
}

CEMSObjectMap<std::string,std::string> 
CEMSCommand::GetParamList()
{
	return m_Params;
}

void 
CEMSCommand::processToken( const std::string& token )
{
	if( !token.empty() )
	{
		// The token should bein the format:  LHS=RHS
		std::string::size_type idxEquals = token.find("=");

		if( std::string::npos != idxEquals )
		{
			std::string lhs = token.substr(0, idxEquals);

			std::string rhs = token.substr(idxEquals+1, token.length() - (idxEquals+1));

			if( !lhs.empty() && !rhs.empty() )
			{
				if( lhs.compare("cmd") == 0 )
				{
					m_Cmd = rhs;
				}
				else
				{
					m_Params.Add(lhs, rhs);
				}
			}
		}
	}
}