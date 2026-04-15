/*********************************************************************
*	              Copyright (c) 2011 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
#pragma warning(disable:4786)

#include "pswsconnector.h"

CEMSConnector CEMSConnector::ms_Connector;

CEMSConnector::CEMSConnector()
{
}

CEMSConnector::~CEMSConnector()
{
}

void 
CEMSConnector::OnSetAutomatic()
{
	// Dispatch to call registered callbacks.
	try
	{
		m_cs.Enter();

		m_setCallbacks.MoveFirst();

		ULONG ulCallbacks = m_setCallbacks.Count();

		for( ULONG l = 0; l < ulCallbacks; l++ )
		{
			IEMSConnectorIF* pCallback = m_setCallbacks.GetNext();

			if( pCallback )
				pCallback->OnSetAutomatic();
		}



		m_cs.Leave();

	}
	catch( ... )
	{
		m_cs.Leave();
	}

	
}

void 
CEMSConnector::OnSetManual( const int ciRecs, const EMSSATTRACKRECORD2* caTracks )
{
	// Dispatch to call registered callbacks.
	try
	{
		m_cs.Enter();

		m_setCallbacks.MoveFirst();

		ULONG ulCallbacks = m_setCallbacks.Count();

		for( ULONG l = 0; l < ulCallbacks; l++ )
		{
			IEMSConnectorIF* pCallback = m_setCallbacks.GetNext();

			if( pCallback )
				pCallback->OnSetManual( ciRecs, caTracks );
		}



		m_cs.Leave();

	}
	catch( ... )
	{
		m_cs.Leave();
	}
}

void 
CEMSConnector::OnSetDuration( const long clDurationDays )
{
	// Dispatch to call registered callbacks.
	try
	{
		m_cs.Enter();

		m_setCallbacks.MoveFirst();

		ULONG ulCallbacks = m_setCallbacks.Count();

		for( ULONG l = 0; l < ulCallbacks; l++ )
		{
			IEMSConnectorIF* pCallback = m_setCallbacks.GetNext();

			if( pCallback )
				pCallback->OnSetDuration( clDurationDays );
		}



		m_cs.Leave();

	}
	catch( ... )
	{
		m_cs.Leave();
	}
}

void 
CEMSConnector::OnSetMinElevation( const double cdMin )
{
	// Dispatch to call registered callbacks.
	try
	{
		m_cs.Enter();

		m_setCallbacks.MoveFirst();

		ULONG ulCallbacks = m_setCallbacks.Count();

		for( ULONG l = 0; l < ulCallbacks; l++ )
		{
			IEMSConnectorIF* pCallback = m_setCallbacks.GetNext();

			if( pCallback )
				pCallback->OnSetMinElevation( cdMin );
		}



		m_cs.Leave();

	}
	catch( ... )
	{
		m_cs.Leave();
	}
}

IEMSConnectorIF* 
CEMSConnector::GetConnector()
{
	return (IEMSConnectorIF*) &ms_Connector;
}

IEMSCallbackRegistration* 
CEMSConnector::GetCallbackRegistration()
{
	return (IEMSCallbackRegistration*) &ms_Connector;
}

void 
CEMSConnector::RegisterCallback( IEMSConnectorIF* pCallback )
{
	try
	{
		m_cs.Enter();

		ms_Connector.m_setCallbacks.Add(pCallback);

		m_cs.Leave();

	}
	catch( ... )
	{
		m_cs.Leave();
	}
}

void 
CEMSConnector::UnRegisterCallback( IEMSConnectorIF* pCallback )
{
	try
	{
		m_cs.Enter();

		ms_Connector.m_setCallbacks.Remove(pCallback);

		m_cs.Leave();

	}
	catch( ... )
	{
		m_cs.Leave();
	}
}


