/*********************************************************************
*	              Copyright (c) 2005 by EMS Technologies, Inc.,
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

#ifndef __SNMP_AGENT_H__
#define __SNMP_AGENT_H__

#include <string>

class IEMSSNMPAgent
{
	public:
		IEMSSNMPAgent() {}
		virtual ~IEMSSNMPAgent() {}

		//! Allocate a socket for sending and receiving datagrams.
		virtual void Open( const long clPort = 0, const wchar_t* cwszAddress = 0  ) = 0;

		//! Release system connection resources.
		virtual void Close() = 0;

		//! Load and compile the given list of MIB files.
		virtual void CompileMIBs( const long clNumMIBs, const wchar_t** cawszMIBs ) = 0;

		//! Set the value of a managed variable.
		virtual void SetVariable( const wchar_t* cwszVariable, const wchar_t* cwszValue ) = 0;

		//! Get the value of a managed variable.
		virtual std::wstring GetVariable( const wchar_t* cwszVariable ) = 0;

	public:
		// System group object names.
		static const wchar_t* ms_cwszSysDesc;
		static const wchar_t* ms_cwszSysObjectID;
		static const wchar_t* ms_cwszSysContact;
		static const wchar_t* ms_cwszSysName;
		static const wchar_t* ms_cwszSysLocation;
		static const wchar_t* ms_cwszSysUptime;
};

#endif