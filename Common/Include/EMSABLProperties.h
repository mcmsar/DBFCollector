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

#ifndef __ABL_PROPERTIES_H__
#define __ABL_PROPERTIES_H__

#include "ablobject.h"
#include "logclient.h"
#include "AOBJBASE.H"
#include <list>
#include "emserror.h"

//! @class CABLProperties
//! This class represents the filter parameters and config parameters
//! of the ABL Core Module

class CEMSABLProperties :	public CApiObjBase  
{			
	public:
		CEMSABLProperties();
		CEMSABLProperties( const EMSABLProperties& cConfig );
		CEMSABLProperties( const CEMSABLProperties& x );
		~CEMSABLProperties();

		void SetProperties( const EMSABLProperties& cABLProperties );
		void GetProperties( EMSABLProperties& ablProperties )
		{ 
			memcpy( &ablProperties, &m_ABLProperiesData, sizeof( EMSABLProperties ) ); 
		}

		EMS_RESULT InitXml( const wchar_t* cwszXMLString );
		
		bool IsMatchingProperties( EMSLOCATE* pLocate );

		EMSABLProperties GetConfig();
		void GetConfigSats( std::list<ULONG>& lstSats );
		void GetConfigLuts( std::list<ULONG>& lstLuts);
		void GetConfigBeacons( std::list<INT64>& lstBeacons );
		void GetConfigCCids( std::list<int>& lstCCids );
		void GetConfigLocTypes( std::list<EMSLOCATETYPE>& lstLocTypes );
		void GetConfigProtTypes( std::list<int>& lstProtTypes );
		BOOL IsShortMessage() { return m_ABLProperiesData.bIsShortMessage; }

		ULONG GetMinLocatesPerAB() { return m_ABLProperiesData.ulMinRawDataPerAB; }
		ULONG GetMaxCapacity() { return m_ABLProperiesData.ulMaxCapacity; }

		ULONG GetABLID() { return m_ABLProperiesData.ulABLID;}

		double GetRadius(){ return m_ABLProperiesData.dLocationRadius;}
		double GetFloatRate(){ return m_ABLProperiesData.dFloatRate;}
		double GetOrbDetError(){ return m_ABLProperiesData.dOrbDetError;}
		double GetSDEL(){ return m_ABLProperiesData.dSDEL;}

		double GetABAgeout(){ return m_ABLProperiesData.dABAgeout;}
		BOOL   GetForceUpdate(){ return m_ABLProperiesData.bForceUpdateAlerts;}
		BOOL   GetIgnoreConfRules(){ return m_ABLProperiesData.bIgnoreConfRules;}
		double GetSubstituteTimeWindow(){ return m_ABLProperiesData.dSubstituteTimeWindow;} 
		double GetMsgMaxInterval(){ return m_ABLProperiesData.dMsgMaxInterval;}
		int    GetMaxSubstituteFSErrors(){ return m_ABLProperiesData.iMaxSubstituteFSErrors;}
		int    GetMaxSubstitutePDF1Errors(){ return m_ABLProperiesData.iMaxSubstitutePDF1Errors;}
		int    GetMaxSubstitutePDF2Errors(){ return m_ABLProperiesData.iMaxSubstitutePDF2Errors;}
		int    GetMinTotalSatsNum(){ return m_ABLProperiesData.iMinTotalSatsNum;}
		int    GetMinGEOSatsNum(){ return m_ABLProperiesData.iMinGEOSatsNum;}
		int    GetMinLEOSatsNum(){ return m_ABLProperiesData.iMinLEOSatsNum;}
		int    GetMinMEOSatsNum(){ return m_ABLProperiesData.iMinMEOSatsNum;}
		double GetMinTimeBtwnBursts(){ return m_ABLProperiesData.dMinTimeBtwnBursts;}
		double GetMaxTimeStdDev(){ return m_ABLProperiesData.dMaxTimeStdDev;}
		double GetMaxFreqStdDev(){ return m_ABLProperiesData.dMaxFreqStdDev;}
		double GetMaxHDOP(){ return m_ABLProperiesData.dMaxHDOP;}
		double GetLcnProximityThreshold(){ return m_ABLProperiesData.dLcnProximityThreshold;}

	protected:
		bool _MatchLutID( ULONG ulLutID );
		bool _MatchSatID( BYTE* abSatIDs, int iSize );
		bool _MatchLocationType( WORD wType );
		bool _MatchBeaconID( INT64 i64BeaconID );
		bool _MatchCountryCode( EMSLOCATE* pLocate );
		bool _MatchProtocolType( EMSLOCATE* pLocate );
		bool _MatchMsgLength( EMSLOCATE* pLocate );
		bool _WithinLcnRadius( EMSLOCATE* pLocate );

	private:
		EMS_RESULT _ParseLUTS( const wchar_t* cwszXMLString );
		EMS_RESULT _ParseSATS( const wchar_t* cwszXMLString );
		EMS_RESULT _ParseLcnTypes( const wchar_t* cwszXMLString );
		EMS_RESULT _ParseBeacons( const wchar_t* cwszXMLString );
		EMS_RESULT _ParseCC( const wchar_t* cwszXMLString );
		EMS_RESULT _ParseProtocols( const wchar_t* cwszXMLString );

	private:
		EMSABLProperties		m_ABLProperiesData;

		static const wchar_t* ms_cwszID;

		static const wchar_t* ms_cwszLUTS;
		static const wchar_t* ms_cwszLUT;

		static const wchar_t* ms_cwszSATS;
		static const wchar_t* ms_cwszSAT;

		static const wchar_t* ms_cwszLocationTypes;
		static const wchar_t* ms_cwszLocationType;

		static const wchar_t* ms_cwszBeacons;
		static const wchar_t* ms_cwszBeacon;

		static const wchar_t* ms_cwszCountryCodes;
		static const wchar_t* ms_cwszCountryCode;
		static const wchar_t* ms_cwszCode;

		static const wchar_t* ms_cwszProtocols;
		static const wchar_t* ms_cwszProtocol;
		static const wchar_t* ms_cwszType;

		static const wchar_t* ms_cwszEnabled;
		static const wchar_t* ms_cwszShortMessage;
		static const wchar_t* ms_cwszMaxCapacity;
		static const wchar_t* ms_cwszMinRawDataPerAB;
		static const wchar_t* ms_cwszLUTID;
		static const wchar_t* ms_cwszLocationRadius;
		static const wchar_t* ms_cwszOrbDetError;
		static const wchar_t* ms_cwszSDEL;
		static const wchar_t* ms_cwszLocationLatitude;
		static const wchar_t* ms_cwszLocationLongitude;
		static const wchar_t* ms_cwszLocationAltitude;
		static const wchar_t* ms_cwszFloatRate;
};

#endif