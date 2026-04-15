/*********************************************************************
*	Copyright (c) 2011 by EMS Technologies, Inc.,
*					All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be
*	reproduced in whole or in part, in any form or by any means whatsoever
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef __SOLUTION_H__
#define __SOLUTION_H__

#include "calib406ext.h"
#include "locate.h"
#include "pointerlist.h"
#include "configurationaccessor.h"
#include "aobjbase.h"
#include <string>

class CEMSBurstData;

class CEMSSolution : public CApiObjBase
{
	public:
		CEMSSolution();
		CEMSSolution( const CEMSSolution& x );
		virtual ~CEMSSolution();

		void Deserialize( const char* cszRec );
		std::string Serialize();

		void SetLutID( const ULONG culLutID ) { m_ulLutID = culLutID; }
		ULONG GetLutID() const { return m_ulLutID; }

		void SetBeaconID( const INT64 ci64BeaconID )  { m_i64BeaconID = ci64BeaconID; }
		INT64 GetBeaconID() const { return m_i64BeaconID; }

		void AddBurstData( CEMSBurstData* pBurst );
		CEMSPointerList<CEMSBurstData> GetBurstData() const { return m_burstData; }

		void SetFinalSolution( const EMSLOCATE& crLocate ) { m_finalSolution = crLocate; }
		EMSLOCATE GetFinalSolution() const { return m_finalSolution; }

		bool IsDetectOnly() const;

		void Reset();

	private:
		void _SerializeBurstData( CEMSConfigurationAccessor& rModel  ) ;
		void _SerializeFinalSolution( CEMSConfigurationAccessor& rModel  );
		void _DeserializeBurstData( CEMSConfigurationAccessor& rModel  );
		void _DeserializeFinalSolution( CEMSConfigurationAccessor& rModel );
		std::wstring _PrependAt( const wchar_t* cwszAttr ) ;

	private:
		static const wchar_t* LUTID_ATTR;
		static const wchar_t* BEACONID_ATTR;
		static const wchar_t* ITERATIONS_ATTR;
		static const wchar_t* START_TIME_ATTR;
		static const wchar_t* END_TIME_ATTR;
		static const wchar_t* TYPE_ATTR;
		static const wchar_t* POWER_ATTR;
		static const wchar_t* MSG406_ATTR;
		static const wchar_t* RADIUS_ERR_ELLIPSE_ATTR;
		static const wchar_t* LAT_ATTR;
		static const wchar_t* LNG_ATTR;
		static const wchar_t* ALT_ATTR;

		static const wchar_t* MODE_ATTR;
		static const wchar_t* DETECT_ONLY_ATTR;
		static const wchar_t* COUNTRY_CODE_ATTR;

		static const wchar_t* SOLUTION_ELEMENT;
		static const wchar_t* POSITION_ELEMENT;
		static const wchar_t* ENCODED_ELEMENT;

		static const wchar_t* BURST_DATA_ELEMENT;
		
		static const wchar_t* MODE_NORMAL;
		static const wchar_t* MODE_TEST;


		static const wchar_t* PROCESS_TIME_ATTR;
		static const wchar_t* POSITION_ERROR_ATTR;
		static const wchar_t* CONFIDENCE_ATTR;
		static const wchar_t* TX_FREQUENCY_ATTR;
		static const wchar_t* MAJOR_AXIS_ERR_ELLIPSE_ATTR;
		static const wchar_t* MINOR_AXIS_ERR_ELLIPSE_ATTR;
		static const wchar_t* HEADING_ERR_ELLIPSE_ATTR;
		static const wchar_t* FOA_RMS_ATTR;
		static const wchar_t* TOA_RMS_ATTR;
		static const wchar_t* NUM_MSG_ATTR;
		static const wchar_t* NUM_TOA_MSG_USED_ATTR;
		static const wchar_t* NUM_FOA_MSG_USED_ATTR;
		static const wchar_t* NUM_BURSTS_ATTR;
		static const wchar_t* HDOP_ATTR;
		
	private:
		ULONG m_ulLutID;
		INT64 m_i64BeaconID;

		CEMSPointerList<CEMSBurstData> m_burstData;
		EMSLOCATE m_finalSolution;
		
};

#endif