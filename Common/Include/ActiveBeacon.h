/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
********************************************************************************/


#ifndef __ACTIVE_BEACON_H__
#define __ACTIVE_BEACON_H__

#include "configurationaccessor.h"
#include "binarycontainer.h"
#include "objectlist.h"
#include "ABLData.h"
#include <string>
#include <iostream>



//static const wchar_t* gs_cwszABNS = L"xmlns='urn:activeBeacon'";
static const wchar_t* gs_cwszActBcnNS = L"xmlns:ns2='urn:common' xmlns:ns3='urn:activeBeacon'";
//static const wchar_t* gs_cwszActBcnNSURI = L"urn:activeBeacon";

class ActiveBeacon
{
	public:
		ActiveBeacon();
		ActiveBeacon( const ActiveBeacon& x );
		virtual ~ActiveBeacon();

		ULONG GetActualActiveBcnCount() { return m_olstActiveBeacon.Count(); }

		EMSABLData	GetActiveBeaconRec();
		EMS_RESULT	ParseActiveBeaconXML( CEMSSitTokenizer *lpTokenizer );

	protected:
		CEMSObjectList<EMSABLData> m_olstActiveBeacon;

	private:
		EMS_RESULT _GetSatIds();
		EMS_RESULT _GetLutIds();

		CEMSConfigurationAccessor	m_oAccessor;
		EMSABLData					m_ABLDataRec;

		static const wchar_t* ms_cwszGeneratedByLutId;
		static const wchar_t* ms_cwszBeaconId;
		static const wchar_t* ms_cwszBcnMsg36Hex;
		static const wchar_t* ms_cwszCountryCode;

		static const wchar_t* ms_cwszAvgLocLocationNode;
		static const wchar_t* ms_cwszAltitude;
		static const wchar_t* ms_cwszLatitude;
		static const wchar_t* ms_cwszLongitude;

		static const wchar_t* ms_cwszAvgLocErrEllipseNode;
		static const wchar_t* ms_cwszHeading;	//
		static const wchar_t* ms_cwszMajorRadius;	//
		static const wchar_t* ms_cwszMinorRadius;	//
		static const wchar_t* ms_cwszRadius;	//

		static const wchar_t* ms_cwszAvgLocation;	//
		static const wchar_t* ms_cwszQualityFactor;	//

		static const wchar_t* ms_cwszNumToaFoaMeasurements;
		static const wchar_t* ms_cwszFirstDetectionTime;	//
		static const wchar_t* ms_cwszLastDetectionTime;		//

		static const wchar_t* ms_cwszAvgCnr;	//
		static const wchar_t* ms_cwszFrequency;	//

		static const wchar_t* ms_cwszSatIds;	//
		static const wchar_t* ms_cwszAntennaIds;	//

};

#endif

