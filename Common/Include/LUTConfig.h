/*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef __LUT_CONFIG_H__
#define __LUT_CONFIG_H__

#include "cacheconfig.h"
#include "igateway.h"
#include "gatewaytypes.h"
#include "emslinfo.h"
#include <map>
#include <string>

interface IEMSConfigurationManager;

//! @class CEMSLutConfig
//! Stores LUT configuration information.
class CEMSLutConfig : public CEMSCacheConfig
{
	public:
		CEMSLutConfig();
		CEMSLutConfig( const CEMSLutConfig& x );
		~CEMSLutConfig();

		inline void SetID( const unsigned long culID ) { m_ulID = culID; }
		inline unsigned long GetID() { return m_ulID; }

		void SetShortName( const wchar_t* cwszName );
		wchar_t* GetShortName();

		inline void SetLocality( const EMSDEPLOYMENTINDICATOR ceLocality ) { m_eLocality = ceLocality; }
		inline EMSDEPLOYMENTINDICATOR GetLocality() { return m_eLocality; }

		void SetResource( const EMSRESOURCEIDENTIFIER ceResource, const bool cbEnabled );
		bool GetResource( const EMSRESOURCEIDENTIFIER ceResource );

		void SetAsCommand( const EMSRESOURCEIDENTIFIER ceResource, const bool cbEnabled );
		bool GetAsCommand( const EMSRESOURCEIDENTIFIER ceResource );

		void SetTranslationTable( const wchar_t* cwszTable );
		wchar_t* GetTranslationTable();

		void SetLatitude( const double cdValue ) { m_location.degLatitude = cdValue; }
		void SetLongitude( const double cdValue) { m_location.degLongitude = cdValue; }
		void SetAltitude( const double cdValue ) { m_location.fAltitude = cdValue; }
		EMSLOCATION GetLocation() { return m_location; }

		void SetLutType( EMSLUTTYPECODE ceLutType ) { m_eLutType = ceLutType; }
		void SetLutType( std::wstring& wstrLutType );
		EMSLUTTYPECODE GetLutType() { return m_eLutType; }

		void Populate( const unsigned long culID, IEMSConfigurationManager* pConfig );
		
	private:	// methods

	private:	// data
		unsigned long							m_ulID;
		wchar_t*								m_wszShortName;
		EMSDEPLOYMENTINDICATOR					m_eLocality;
		std::map<EMSRESOURCEIDENTIFIER,bool>	m_mapResources;
		std::map<EMSRESOURCEIDENTIFIER,bool>	m_mapCommands;
		wchar_t*								m_wszTransTable;
		EMSLOCATION								m_location;
		EMSLUTTYPECODE							m_eLutType;

};

#endif // __LUT_CONFIG_H__

	