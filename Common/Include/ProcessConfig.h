/*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef __PROCESS_CONFIG_H__
#define __PROCESS_CONFIG_H__

#include "cacheconfig.h"
#include "igateway.h"

interface IEMSConfigurationManager;

//! @class CEMSProcessConfig
//! Stores Process Control configuration information.
class CEMSProcessConfig : public CEMSCacheConfig
{
	public:
		CEMSProcessConfig();
		CEMSProcessConfig( const CEMSProcessConfig& x );
		~CEMSProcessConfig();

		void SetSITOutDirectory( const wchar_t* cwszDir );
		wchar_t* GetSITOutDirectory();

		void SetSITUndeliveredDirectory( const wchar_t* cwszDir );
		wchar_t* GetSITUndeliveredDirectory();

		void SetProcessingDirectory( const wchar_t* cwszDir );
		wchar_t* GetProcessingDirectory();

		void SetProcessedBinaryDirectory( const wchar_t* cwszDir );
		wchar_t* GetProcessedBinaryDirectory();

		inline void SetSerializedMode( const bool cbSerialized ) { m_bSerializedMode = cbSerialized; }
		inline bool GetSerializedMode( ) { return m_bSerializedMode; }

		inline void SetCommandTimeout( const long clSeconds ) { m_lCmdTimeout = clSeconds; }
		inline long GetCommandTimeout( ) { return m_lCmdTimeout; }

		inline void SetSitGtwyPassThrough( const bool cbSitPassThrough ) { m_bSitPassThrough = cbSitPassThrough; }
		inline bool GetSitGtwyPassThrough() { return m_bSitPassThrough; }

		inline void SetThisLutID( const unsigned long culLutID ) { m_ulThisLutID = culLutID; }
		inline unsigned long GetThisLutID() { return m_ulThisLutID; }

		inline void SetSOAPPort( const int ciPort ) { m_iSOAPPort = ciPort; }
		inline int GetSOAPPort() { return m_iSOAPPort; }

		inline void SetSOAPBackLogSize( const int ciBackLog ) { m_iMaxBackLog = ciBackLog; }
		inline int GetSOAPBackLogSize() { return m_iMaxBackLog; }

		inline void SetNumSOAPHandlerThreads( const long clThreads ) { m_lHandlerThreads = clThreads; }
		inline long GetNumSOAPHandlerThreads() { return m_lHandlerThreads; }

		void Populate( IEMSConfigurationManager* pConfig );
		
	private:	// methods

	private:	// data
		wchar_t* m_wszSITOutDir;
		wchar_t* m_wszSITUndeliveredDir;
		wchar_t* m_wszProcessingDir;
		wchar_t* m_wszBinaryProcessedDir;
		bool	m_bSerializedMode;
		long	m_lCmdTimeout;
		bool	m_bSitPassThrough;
		unsigned long	m_ulThisLutID;
		int		m_iSOAPPort;
		int		m_iMaxBackLog;
		long	m_lHandlerThreads;

};

#endif // __PROCESS_CONFIG_H__

	