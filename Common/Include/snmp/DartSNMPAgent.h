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

#ifndef __DARTSNMP_AGENT_H__
#define __DARTSNMP_AGENT_H__

#include "snmp/snmpagent.h"
#include "powertcp/snmp tool/iagent.h"
#include "aobjbase.h"
#include "loghelper.h"


//! Wrapper around the DART PowerTCP SNMP agent component.  Note that this class
//! requires a Windows Message Pump.
class CEMSDartSNMPAgent : public CApiObjBase,  
						public IEMSSNMPAgent, 
						protected IAgent
{
	public:
		CEMSDartSNMPAgent();
		CEMSDartSNMPAgent( const CEMSDartSNMPAgent& x );
		virtual ~CEMSDartSNMPAgent();

		//! Allocate a socket for sending and receiving datagrams.
		virtual void Open( const long clPort = 0, const wchar_t* cwszAddress = 0 );

		//! Release system connection resources.
		virtual void Close();

		//! Load and compile the given list of MIB files.
		virtual void CompileMIBs( const long clNumMIBs, const wchar_t** cawszMIBs );

		//! Set the value of a managed variable.
		virtual void SetVariable( const wchar_t* cwszVariable, const wchar_t* cwszValue );

		//! Get the value of a managed variable.
		virtual std::wstring GetVariable( const wchar_t* cwszVariable );

		virtual void AddVariable( const wchar_t* cwszVariable );

		BOOL SetReq;
		void __stdcall Agent_Request(); 
		void __stdcall Agent_Response();  

		void HandleGetNext();

	private:
		void _CopyVariable(DartSnmp::ISnmpVariablePtr oldVar, DartSnmp::ISnmpVariablePtr newVar);

	private:
		long			m_lPort;
		std::wstring	m_owszAddress;

};

#endif