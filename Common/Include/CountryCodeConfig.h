/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
********************************************************************************/


#ifndef __LUT_CONFIG_CL_H__
#define __LUT_CONFIG_CL_H__

#include <string>
using namespace std;

class __declspec(dllexport)  CountryCodeConfig
{
	public:
		CountryCodeConfig();
		CountryCodeConfig( const CountryCodeConfig& x );
		virtual ~CountryCodeConfig();

		string GetID() { return m_szID; }
		void   SetID( const string& rszID ) { m_szID = rszID; }

		string GetName() { return m_szName; }
		void   SetName( const string& rszName ) { m_szName = rszName; }

		string GetShortName() { return m_szShortName; }
		void   SetShortName( const string& rszShortName ) { m_szShortName = rszShortName; }

	private:

	private:
		string        m_szID;

		string        m_szName;
		string        m_szShortName;
};

#endif

