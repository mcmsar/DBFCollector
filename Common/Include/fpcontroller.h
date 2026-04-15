/*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
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

#ifndef __FP_CONTROLLER_H__
#define __FP_CONTROLLER_H__

#include "emsthread.h"
#include "fpconfig.h"
#include "pointermap.h"
#include "objectmap.h"
#include "antdspair.h"
#include "criticalsection.h"
#include "AntennaSensors.h"

interface IEMSAntenna;
interface IEMSAntenna2;
interface IEMSDataCollector;
interface IEMSStatusBroadcaster;

typedef 
enum fpControllerState
{
	EMSSTATE_TRACKING = 0,
	EMSSTATE_STOPPED = 1,
	EMSSTATE_IDLE = 2,
	EMSSTATE_UN_INITIALIZED = 3
}	EMSFPCONTROLLER_STATE;


class CEMSFPController : public CEMSThread
{
	public:
		CEMSFPController();
		~CEMSFPController();

		void SetConfiguration( CEMSFPConfig& roConfig );

		void SetSchedule( CEMSPointerMap<const ULONG,CEMSPairSchedule>& romapSchedules );

		void Start();

		void Stop();

		void Idle();

		bool IsRunning() const { return (EMSSTATE_TRACKING == m_eState); }
		bool IsThreadRunning() const { return m_bIsRunning; }

	protected:
		void run();

	private:
		void _CheckActive();
		void _CheckNew();
		void _StopPass( const ULONG culPairID, const bool cbCollectorOnly );
		void _StartPass( const CEMSPairSchedule* cpPair, const EMSSATTRACKRECORD* cpPass );
		ULONG _GetADBoardID( const ULONG culDSID );
		ULONG _GetChannelID( const ULONG culDSID );
		ULONG _GetAntennaID( const ULONG culPairID );
		IEMSDataCollector* _GetDataCollector( const ULONG culPair );
		IEMSAntenna* _GetAntennaControl( const ULONG culPair );
		IEMSAntenna2* _GetAntennaControlEx( const ULONG culAntennaID );
		void _StopActive();
		int _IsInSchedule( const ULONG culPairID, const EMSSATTRACKRECORD& crstrPass );
		void _LogSchedule();
		void _CheckStatusUpdates();
		void _UpdateStatus();
		void _UpdateFPCollectorStatus();
		void _UpdateEnvironmentReadings( const ULONG ulAntID );

		bool _GetStopCollectorOnly( const ULONG culPairID );
		
		ULONG _GetSatID( const ULONG ulAntID );
		void _MoveToStow();
		void _InitializeAntennaSensors();


	private:
		static const ULONG ms_culTimeout;
		static const int ms_ciStatusUpdateInterval;
		static const int ms_ciEnvReadingsUpdateInterval;
		static const ULONG ms_culACU_TEMP_ID;
		static const ULONG ms_culOUTSIDE_TEMP_ID;
		static const ULONG ms_culRADOME_TEMP_ID;
		static const ULONG ms_culLNC_TEMP_ID;
		static const ULONG ms_culMOTOR_TEMP_ID;
		static const ULONG ms_culACU_HUMIDITY_ID;
		static const std::string ms_szEnvMeasTopicName;

	private:
		CEMSFPConfig m_oConfig;
		CEMSCriticalSection m_ocsConfig;
		CEMSPointerMap<const ULONG,CEMSPairSchedule> m_omapSchedules;
		CEMSCriticalSection m_ocsSchedule;
		IEMSStatusBroadcaster* m_pStatusBroadcast;
		bool m_bIsRunning;
		EMSTIME  m_tmLastStatusUpdate;
		EMSTIME  m_tmLastEnvReadingsUpdate;
		int      m_iStatusUpdateInterval;
		std::wstring m_wszFPCollectorErrorMsg;
		std::string m_szMQUrl;

		EMSFPCONTROLLER_STATE m_eState;

		AntennaSensors        m_AntSensors;

		CEMSObjectMap<const ULONG,EMSSATTRACKRECORD>	m_omapActivePasses;
};

#endif