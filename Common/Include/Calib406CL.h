/*******************************************************************************
*	Copyright (c) 2013 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
********************************************************************************/


#ifndef __CALIB406_CL_H__
#define __CALIB406_CL_H__

#include "emstypes.h"
#include "CALIB406EXT.h"
#include <string>
#include <list>
using namespace std;

class __declspec(dllexport)  Calib406
{
	public:
		Calib406();
		Calib406( const Calib406& x );
		virtual ~Calib406();

		void Get(EMSCALIB406DATAEXT& rstr406);

		EMSTIME GetTime() { return m_time; }
		void SetTime( const EMSTIME cTime ) { m_time = cTime; }

		WORD GetType() { return m_wType; }
		void SetType( const WORD cwType ) { m_wType = cwType; }

		unsigned long  GetSatId() { return m_ulSatId; }
		void SetSatId( const unsigned long culSatId ) { m_ulSatId = culSatId; }

		unsigned long  GetLutId() { return m_ulLutId; }
		void SetLutId( const unsigned long culLutId ) { m_ulLutId = culLutId; }

		WORD GetAntennaID() { return m_wAntennaID; }
		void SetAntennaId( const WORD cwAntennaID ) { m_wAntennaID = cwAntennaID; }

		INT64 GetBeaconID() { return m_i64BeaconID; }
		void SetBeaconID( const INT64 ci64BeaconID ) { m_i64BeaconID = ci64BeaconID; }

		BYTE* GetBeaconMsg() { return m_cBeaconMsg; }
		void SetBeaconMsg( const BYTE* cBeaconMsg ) { memcpy( m_cBeaconMsg, cBeaconMsg, 18 ); }

		EMSTIME GetTimeMsg() { return m_timeMsg; }
		void SetTimeMsg( const EMSTIME ctimeMsg ) { m_timeMsg = ctimeMsg; }

		INT64 GetTimeOffset() { return m_i64TimeOffset; }
		void SetTimeOffset( const INT64 ci64TimeOffset ) { m_i64TimeOffset = ci64TimeOffset; }

		double GetFrequency() { return m_dFrequency; }
		void SetFrequency( const double cdFrequency ) { m_dFrequency = cdFrequency; }

		double GetFreqOffset() { return m_dFreqOffset; }
		void SetFreqOffset( const double cdFreqOffset ) { m_dFreqOffset = cdFreqOffset; }

		DWORD GetDataFlags() { return m_dwDataFlags; }
		void SetDataFlags( const DWORD cdwDataFlags ) { m_dwDataFlags = cdwDataFlags; }

		double GetCarrierPower() { return m_dCarrierPower; }
		void SetCarrierPower( const double cdCarrierPower ) { m_dCarrierPower = cdCarrierPower; }

		double GetBitRate() { return m_dBitRate; }
		void SetBitRate( const double cdBitRate ) { m_dBitRate = cdBitRate; }

		DWORD GetResolutionFlags() { return m_dwResolutionFlags; }
		void SetResolutionFlags( const DWORD cdwResolutionFlags ) { m_dwResolutionFlags = cdwResolutionFlags; }

		EMSVECTORD GetRadiusCoord() { return m_RadiusCoord; }
		void SetRadiusCoord( const EMSVECTORD cRadiusCoord ) { m_RadiusCoord = cRadiusCoord; }

		EMSVECTORD GetVelocityCoord() { return m_VelocityCoord; }
		void SetVelocityCoord( const EMSVECTORD cVelocityCoord ) { m_VelocityCoord = cVelocityCoord; }

		WORD GetBitErrorField1() {return m_wBitErrorField1;}
		void SetBitErrorField1( WORD wBitErrorField1 ) {m_wBitErrorField1 = wBitErrorField1; }

		WORD GetBitErrorField2() {return m_wBitErrorField2;}
		void SetBitErrorField2( WORD wBitErrorField2 ) {m_wBitErrorField2 = wBitErrorField2; }

		WORD GetBitErrorFrameSynch() {return m_wBitErrorFrameSynch;}
		void SetBitErrorFrameSynch( WORD wBitErrorFrameSynch ) {m_wBitErrorFrameSynch = wBitErrorFrameSynch; }

		DWORD GetReserve0() {return m_dwReserve0;}
		void SetReserve0( DWORD dwReserve0 ) {m_dwReserve0 = dwReserve0; }
	private:

	private:
		EMSTIME			m_time;
		WORD			m_wType;
		unsigned long	m_ulSatId;
		unsigned long	m_ulLutId;
		WORD			m_wAntennaID;
		INT64			m_i64BeaconID;
		BYTE			m_cBeaconMsg[ 18 ];
		EMSTIME			m_timeMsg;
		INT64			m_i64TimeOffset;
		double			m_dFrequency;
		double			m_dFreqOffset;
		DWORD			m_dwResolutionFlags;
		double			m_dCarrierPower;
		double			m_dBitRate;
		DWORD			m_dwDataFlags;
		WORD            m_wBitErrorField1;
		WORD            m_wBitErrorField2;
		WORD            m_wBitErrorFrameSynch;
		DWORD			m_dwReserve0;

		EMSVECTORD		m_RadiusCoord;
		EMSVECTORD		m_VelocityCoord;

};

#endif  // __CALIB406_CL_H__

