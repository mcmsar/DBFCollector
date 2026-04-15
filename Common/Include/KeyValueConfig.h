/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
********************************************************************************/


#ifndef __KEY_VALUE_CONFIG_H__
#define __KEY_VALUE_CONFIG_H__

#include <string>
using namespace std;



class __declspec(dllexport) KeyValueItem
{
	public:
		KeyValueItem();
		KeyValueItem( const KeyValueItem& x );
		virtual ~KeyValueItem();

		string GetID() { return m_szID; }
		void   SetID( const string& rszID ) { m_szID = rszID; }

		string GetDescription() { return m_szDescription; }
		void   SetDescription( const string& rszDesc ) {m_szDescription = rszDesc; }

		double GetValue() { return m_dValue;}
		void   SetValue( const double cdValue ) {m_dValue = cdValue;}

	private:
		string   m_szID;
		string   m_szDescription;
		double   m_dValue;
};

//
//class __declspec(dllexport)  KeyValueItemsConfig
//{
//	public:
//		KeyValueItemsConfig();
//		KeyValueItemsConfig( const KeyValueItemsConfig& x );
//		virtual ~KeyValueItemsConfig();
//
//		list<KeyValueItem> GetKeyValueItems(){ return m_lstItems ;}
//		void               SetKeyValueItems( list<KeyValueItem>& rolstItems ){ m_lstItems = rolstItems;}
//
//	protected:
//		list<KeyValueItem> m_lstItems;
//};

#endif

