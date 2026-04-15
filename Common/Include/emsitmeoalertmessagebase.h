/*********************************************************************
* Copyright (c) 2011 by EMS Technologies, Inc.,
* All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef __SIT_MEO_ALERT_MESSAGE_BASE_H__
#define __SIT_MEO_ALERT_MESSAGE_BASE_H__

#include "emssit.h"
#include "pointerlist.h"
#include "locate.h"
#include "burstdata.h"

#define EMSMEOALERTSIT_MAX_SIT_LINE_LENGTH 350

class CEMSSitMEOAlertMessageBase : public CEMSSitMessageBase
{
	public:
		CEMSSitMEOAlertMessageBase();
		CEMSSitMEOAlertMessageBase( const CEMSSitMEOAlertMessageBase& x );
		virtual ~CEMSSitMEOAlertMessageBase();

		void SetBeaconID( const INT64 ci64BeaconID ) { m_i64BeaconID = ci64BeaconID; }
		INT64 GetBeaconID() const { return m_i64BeaconID; }

		void SetLutID( const ULONG culLutID ) { m_ulLutID = culLutID; }
		ULONG GetLutID() const { return m_ulLutID; }

		void SetBurstData( const CEMSPointerList<CEMSBurstData>& crBurstData ) { m_lstBurstData = crBurstData; }
		CEMSPointerList<CEMSBurstData> GetBurstData() const { return m_lstBurstData; }

		ULONG GetMaxBursts() const { return 99; }

		virtual EMS_RESULT GenerateSitHeader( IEMSSeqStream *lpStream);
		virtual EMS_RESULT GenerateSitBody( IEMSSeqStream *lpStream );
		virtual void Reset( void );

	protected:
		void _GetEncodedLatLong( const BYTE cBeaconMsg[18], double& rdLat, double& rdLong );
		void _GetSolutionLine( const EMSLOCATE& crLocate, TCHAR* szLine, const int ciMaxBuffer );

		virtual int _GetMaxSitLineLength() { return EMSMEOALERTSIT_MAX_SIT_LINE_LENGTH; }

		virtual EMS_RESULT _WriteFinalSolution( IEMSSeqStream* lpStream ) { return EMS_OK; }

	private:
		INT64 m_i64BeaconID;
		ULONG m_ulLutID;
		CEMSPointerList<CEMSBurstData> m_lstBurstData;

};

#endif