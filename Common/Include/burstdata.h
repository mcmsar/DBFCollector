/*********************************************************************
*	Copyright (c) 2011 by EMS Technologies, Inc.,
*					All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be
*	reproduced in whole or in part, in any form or by any means whatsoever
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef __BURST_DATA_H__
#define __BURST_DATA_H__

#include "calib406ext.h"
#include "locate.h"
#include "objectlist.h"
#include "aobjbase.h"
#include "configurationaccessor.h"

class CEMSBurstData : public CApiObjBase
{
	public:
		CEMSBurstData();
		CEMSBurstData( const CEMSBurstData& x );
		virtual ~CEMSBurstData();

		void SetTxTime( const EMSTIME ctimeTx ) { m_timeTx = ctimeTx; }
		EMSTIME GetTxTime() const { return m_timeTx; }


		void AddBurstMeasurement( const EMSCALIB406DATAEXT& crBurst ) { m_burstData.Add( crBurst ); }
		CEMSObjectList<EMSCALIB406DATAEXT> GetBurstMeasurements() const { return m_burstData; }
		
		void SetBurstSolution( const EMSLOCATE& crLocate ) { m_solution = crLocate; }
		EMSLOCATE GetBurstSolution() const { return m_solution; };

		bool IsDetectOnly() const;

		void Serialize( CEMSConfigurationAccessor& rModel );
		void Deserialize( CEMSConfigurationAccessor& rModel );

		void Reset();

	private:
		std::wstring _PrependAt( const wchar_t* cwszAttr ) ;

	private:
		static const wchar_t* BURST_DATA_ELEMENT;
		static const wchar_t* TXTIME_ATTR;
		static const wchar_t* BURST_ELEMENT;
		static const wchar_t* LUTID_ATTR;
		static const wchar_t* MSG406_ATTR;
		static const wchar_t* UPLINK_TOA_ATTR;
		static const wchar_t* TIME_OFFSET_ATTR;
		static const wchar_t* UPLINK_FOA_ATTR;
		static const wchar_t* FREQ_OFFSET_ATTR;
		static const wchar_t* CNR_ATTR;
		static const wchar_t* TOA_ATTR;
		static const wchar_t* FOA_ATTR;
		static const wchar_t* BIT_ERR1_ATTR;
		static const wchar_t* BIT_ERR2_ATTR;
		static const wchar_t* BIT_ERRFS_ATTR;
		static const wchar_t* BIT_RATE_ATTR;
		static const wchar_t* RAW_MSG_ATTR;
		static const wchar_t* CORRECTED_MSG_ATTR;
		static const wchar_t* SAT_ELEMENT;
		static const wchar_t* SATID_ATTR;
		static const wchar_t* SAT_EPOCH_ATTR;
		static const wchar_t* POS_VEC_ELEMENT;
		static const wchar_t* X_ATTR;
		static const wchar_t* Y_ATTR;
		static const wchar_t* Z_ATTR;
		static const wchar_t* VEL_VEC_ELEMENT;
		static const wchar_t* ANT_ELEMENT;
		static const wchar_t* ANTID_ATTR;
		static const wchar_t* ANT_AZ_ATTR;
		static const wchar_t* ANT_EL_ATTR;
		static const wchar_t* ENCODED_ELEMENT;
		static const wchar_t* LAT_ATTR;
		static const wchar_t* LNG_ATTR;
		static const wchar_t* SOLUTION_ELEMENT;
		static const wchar_t* ITERATIONS_ATTR;
		static const wchar_t* START_TIME_ATTR;
		static const wchar_t* END_TIME_ATTR;
		static const wchar_t* POSITION_ELEMENT;
		static const wchar_t* ALT_ATTR;
		static const wchar_t* POWER_ATTR;
		static const wchar_t* RADIUS_ERR_ELLIPSE_ATTR;
		static const wchar_t* TYPE_ATTR;

		static const wchar_t* MODE_ATTR;
		static const wchar_t* DETECT_ONLY_ATTR;
		static const wchar_t* COUNTRY_CODE_ATTR;

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
		EMSTIME m_timeTx;
		CEMSObjectList<EMSCALIB406DATAEXT> m_burstData;
		EMSLOCATE m_solution;
};

#endif