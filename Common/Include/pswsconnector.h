/*********************************************************************
*	              Copyright (c) 2011 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef __PS_WS_CONNECTOR_H__
#define __PS_WS_CONNECTOR_H__

#include "criticalsection.h"
#include "emstrack.h"
#include "objectset.h"

class __declspec(dllexport) IEMSConnectorIF
{
	public:
		virtual void OnSetAutomatic() = 0;
		virtual void OnSetManual( const int ciRecs, const EMSSATTRACKRECORD2* caTracks ) = 0;
		virtual void OnSetDuration( const long clDurationDays ) = 0;
		virtual void OnSetMinElevation( const double cdMin ) = 0;
};

class __declspec(dllexport) IEMSCallbackRegistration
{
	public:
		virtual void RegisterCallback( IEMSConnectorIF* pCallback ) = 0;
		virtual void UnRegisterCallback( IEMSConnectorIF* pCallback ) = 0;
};

class __declspec(dllexport) CEMSConnector : public IEMSConnectorIF, public IEMSCallbackRegistration
{
	public:
		virtual ~CEMSConnector();

		void OnSetAutomatic();
		void OnSetManual( const int ciRecs, const EMSSATTRACKRECORD2* caTracks );
		void OnSetDuration( const long clDurationDays );
		void OnSetMinElevation( const double cdMin );

		void RegisterCallback( IEMSConnectorIF* pCallback );
		void UnRegisterCallback( IEMSConnectorIF* pCallback );

		static IEMSConnectorIF* GetConnector();
		static IEMSCallbackRegistration* GetCallbackRegistration();

	private:
		CEMSConnector();

		

	private:
		static CEMSConnector ms_Connector; 

		CEMSObjectSet<IEMSConnectorIF*> m_setCallbacks;

		CEMSCriticalSection m_cs;
};


#endif