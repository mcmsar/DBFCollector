/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
*
********************************************************************************/

#ifndef __PIPE_MQ_ADAPTOR_CONFIG_H__
#define __PIPE_MQ_ADAPTOR_CONFIG_H__

#include <string>
#include "emstypes.h"
#include "msgtype.h"
#include "direction.h"
#include "aobjbase.h"
#include <list>

#include <string>
using namespace std;

class __declspec(dllexport) PipeMQAdaptorConfig
{
	public:
		PipeMQAdaptorConfig();
		PipeMQAdaptorConfig( const PipeMQAdaptorConfig& x );
		virtual ~PipeMQAdaptorConfig();

		void SetName( const std::string name ) { m_mappingName = name; }
		std::string GetName() const { return m_mappingName; }

		void SetDirection( const DIRECTION_TYPE ceDirection ) { m_eDirection = ceDirection; }
		DIRECTION_TYPE GetDirection() const { return m_eDirection; }

		void SetFilteredSubsystems( const std::list<ULONG>& filterList ) { m_lstFiltered = filterList; }
		std::list<ULONG> GetFilteredSubSystems() const { return m_lstFiltered; }

		void SetMapToType( const std::string type ) { m_MapToType = type; }
		std::string GetMapToType() const { return m_MapToType; }

		void SetMQName( const std::string name ) { m_MQName = name; }
		std::string GetMQName() const { return m_MQName; }

		void SetMQUrl( const std::string url ) { m_MQUrl = url; }
		std::string GetMQUrl() const { return m_MQUrl; }

		void SetPipeChannel( const BYTE cId ) { m_cPipeChannel = cId; }
		BYTE GetPipeChannel() const { return m_cPipeChannel; }

	    void SetRecordSize( const ULONG culSize ) { m_ulRecordSize = culSize; }
		ULONG GetRecordSize() const { return m_ulRecordSize; }

		void SetDestType( const MSGTYPE ceType ) { m_eDestType = ceType; }
		MSGTYPE GetDestType() const { return m_eDestType; }

		void SetSrcType( const MSGTYPE ceType ) { m_eSrcType = ceType; }
		MSGTYPE GetSrcType() const { return m_eSrcType; }

		void SetPersistent( const bool cbValue ) { m_bPersistent = cbValue; }
		bool IsPersistent() const { return m_bPersistent; }

	    void SetNbRecords( const ULONG culNbRecords ) { m_ulNbRecords = culNbRecords; }
		ULONG GetNbRecords() const { return m_ulNbRecords; }

	    void SetTimeInterval( const ULONG culTimeInterval ) { m_ulTimeInterval = culTimeInterval; }
		ULONG GetTimeInterval() const { return m_ulTimeInterval; }

	private:
		std::string m_mappingName;
		DIRECTION_TYPE m_eDirection;
		std::list<ULONG> m_lstFiltered;
		std::string m_MapToType;
		std::string m_MQName;
		std::string m_MQUrl;
		BYTE m_cPipeChannel;
		ULONG m_ulRecordSize;
		MSGTYPE m_eDestType;
		MSGTYPE m_eSrcType;
		bool m_bPersistent;
		ULONG m_ulNbRecords;
		ULONG m_ulTimeInterval;
};

class __declspec(dllexport) BridgeConfig
{
	public:
		BridgeConfig();
		BridgeConfig( const BridgeConfig& x );
		virtual ~BridgeConfig();

		void SetBridgeMappingListID( const std::string bridgeMappingListID ) { m_BridgeMappingListID = bridgeMappingListID; }
		std::string GetBridgeMappingListID() const { return m_BridgeMappingListID; }

		void SetPipeMQAdaptorConfigs( const list<PipeMQAdaptorConfig>& pipeMQAdaptorConfigList ) { m_lstPipeMQAdaptorConfig = pipeMQAdaptorConfigList; }
		list<PipeMQAdaptorConfig> GetPipeMQAdaptorConfigs() { return m_lstPipeMQAdaptorConfig; }

	private:
		std::string m_BridgeMappingListID;
		list<PipeMQAdaptorConfig> m_lstPipeMQAdaptorConfig;
};

#endif //__PIPE_MQ_ADAPTOR_CONFIG_H__

