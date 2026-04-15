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

#include "snmp/dartsnmpagent.h"
#include "emsexcpt.h"
#include "EMSErrorMsgs.h"
#include "loghelper.h"

CEMSDartSNMPAgent::CEMSDartSNMPAgent() : m_lPort(0)
{
	if ( !Create( "1550-2-631-454037:15212745" ) ) THROW_RUNTIME_EXCEPTION( EMS_SNMP_CREATEFAILED );

	SetReq = FALSE;
}

CEMSDartSNMPAgent::CEMSDartSNMPAgent( const CEMSDartSNMPAgent& x ) :  
										m_lPort( x.m_lPort ), m_owszAddress( x.m_owszAddress )
{
}

CEMSDartSNMPAgent::~CEMSDartSNMPAgent()
{
}

void 
CEMSDartSNMPAgent::Open( const long clPort, const wchar_t* cwszAddress )
{
	if ( pAgent )
	{
		m_lPort = clPort;
		m_owszAddress = cwszAddress;

		EMS_RESULT hr = pAgent->Open( m_lPort, m_owszAddress.c_str() );
		if ( FAILED(hr) ) THROW_RUNTIME_EXCEPTION( hr );

		pAgent->Auto = true;
	}
}

void 
CEMSDartSNMPAgent::Close()
{
	if ( pAgent )
	{
		EMS_RESULT hr = pAgent->Close();
		if ( FAILED(hr) ) THROW_RUNTIME_EXCEPTION( hr );
	}
}

void 
CEMSDartSNMPAgent::CompileMIBs( const long clNumMIBs, const wchar_t** cawszMIBs )
{
	if ( pAgent )
	{
		EMS_RESULT hr = EMS_OK;

		if( ( clNumMIBs > 0 ) && cawszMIBs )
		{
			// First, copy the array of strings into a DartStrings object.
			DartSnmp::IDartStringsPtr dartstringsMIBs;
			hr = dartstringsMIBs.CreateInstance( DartSnmp::CLSID_DartStrings );

			for( long l = 0; l < clNumMIBs; l++ )
			{
				if( cawszMIBs[l] )
				{
					_bstr_t bszValue = cawszMIBs[l];

					hr = dartstringsMIBs->Add( bszValue,l );
				}
			}

			hr = pAgent->Mib->Compile( dartstringsMIBs );
			if ( FAILED(hr) ) THROW_RUNTIME_EXCEPTION( hr );
		}
	}
}

void 
CEMSDartSNMPAgent::AddVariable( const wchar_t* cwszVariable )
{
	if ( pAgent )
	{
		if ( cwszVariable )
		{
			_bstr_t bszVariable = cwszVariable;

			// Add variables to the Agent that can be queried by manager applications
			// This agent has 6 from the System Group
			DartSnmp::ISnmpVariablesPtr pItem = pAgent->Mib->Variables->Item( bszVariable );
		}
	}
}

void 
CEMSDartSNMPAgent::SetVariable( const wchar_t* cwszVariable, const wchar_t* cwszValue )
{
	if ( pAgent )
	{
		if ( cwszVariable )
		{
			_bstr_t bszValue = cwszValue;

			pAgent->Mib->Variables->Item( cwszVariable )->Value = bszValue;
		}
	}
}

std::wstring 
CEMSDartSNMPAgent::GetVariable( const wchar_t* cwszVariable )
{
	std::wstring owszRet;

	if ( pAgent )
	{
		if ( cwszVariable )
		{
			owszRet = (const wchar_t*) pAgent->Mib->Variables->Item( cwszVariable )->Value;
		}
	}

	return owszRet;
}

void __stdcall CEMSDartSNMPAgent::Agent_Request()
{
	if ( pAgent )
	{
		// Fires when request comes in. Get and Set Responses are handled automatically

		// Update Value of sysUpTime
		//    SetVariableLong("sysUpTime", (GetTickCount() - m_StartTick) / 10);

		if((pAgent->Message->Type == DartSnmp::snmpSet1) || (pAgent->Message->Type == DartSnmp::snmpSet2)) 
			SetReq = TRUE;

		if((pAgent->Message->Type == DartSnmp::snmpGetNext1) || (pAgent->Message->Type == DartSnmp::snmpGetNext2)) 
		{
			HandleGetNext();
		}
	}
}
 
void __stdcall CEMSDartSNMPAgent::Agent_Response()
{
    if(SetReq)
	{
		SetReq = FALSE;
	}
}

void CEMSDartSNMPAgent::HandleGetNext()
{
	if ( pAgent )
	{
		DartSnmp::ISnmpVariablePtr v;

		_variant_t vValue( (long) 1 );

		DartSnmp::ISnmpVariablePtr MessageVar = pAgent->Message->Variables->Item(vValue);
		
		// Respond with next variable
		try
		{
			v.CreateInstance("Dart.SnmpVariable");
			_CopyVariable(pAgent->Mib->Variables->GetNext(MessageVar->Oid), v);
			pAgent->Message->Variables->Clear();
			pAgent->Message->Variables->Add(v);
		}
		catch(_com_error e)
		{
			// If there was no error copying the variable,
			// then we have reached the end of the table
			MessageVar->Exception = DartSnmp::snmpEndOfMibView;
			pAgent->Message->Exception = DartSnmp::snmpNoSuchName;
			pAgent->Message->ExceptionIndex = 1;
		}

		try
		{
			pAgent->Message->Type = DartSnmp::snmpResponse1;
			pAgent->Send();
		}
		catch(...)
		{
		}
	}
}

void CEMSDartSNMPAgent::_CopyVariable(DartSnmp::ISnmpVariablePtr oldVar, DartSnmp::ISnmpVariablePtr newVar)
{
	if ( pAgent ) 
	{

		// Copy a Variable to a New Variable
		newVar->Oid = oldVar->Oid;
		newVar->Type = oldVar->Type;
		newVar->Value = oldVar->Value;
    
		// If non-table variable, add ".0" indicating an instance
		// (Auto = True does this automatically for Sets and Gets, but not for GetNexts)
		// This agent only implements variables in the System Group
/*	
		std::wstring owszOid = (char *)newVar->Oid;
		if(Oid.Left(13) == "1.3.6.1.2.1.1")
			Oid += ".0";
*/
		std::string oszOID = (char *)newVar->Oid;
		if( 0 == strnicmp( oszOID.c_str(), "1.3.6.1.2.1.1", 13 ) )
			oszOID.append( ".0" );

		newVar->Oid = _bstr_t(oszOID.c_str());
	}
}
