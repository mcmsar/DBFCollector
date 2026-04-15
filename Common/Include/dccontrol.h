/*********************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
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

#ifndef __DC_CONTROL_H__
#define __DC_CONTROL_H__

#ifdef WIN32
#include <windows.h>
#endif

//! This class is used only to allow communications from the EMSDC_WS.dll to the host service.
class __declspec(dllexport) CEMSDCControl
{
	public:
		~CEMSDCControl();

		static CEMSDCControl* GetInstance();

		void Start( const ULONG culADBoardID, const ULONG culChannelID );

		void Stop( const ULONG culADBoardID, const ULONG culChannelID );
		
		void SetSatelliteID( const ULONG culADBoardID, const ULONG culChannelID,
							const ULONG culSatID, const ULONG culFlags,
							const ULONG culBandwidth );

		void SetInputDataID( const ULONG culADBoardID, const ULONG culChannelID,
							const ULONG culInputDataID );

		ULONG GetSatID() { return m_ulSatID; }

		ULONG GetFlags() { return m_ulFlags; }

		ULONG GetBandwidth() { return m_ulBandwidth; }

		ULONG GetInputDataID() {return m_ulInputDataID; }

		HANDLE GetStartHandle() { return m_hStart; }

		HANDLE GetStopHandle() { return m_hStop; }

		HANDLE GetSatelliteHandle() { return m_hSetSatellite; }

		HANDLE GetInputIDHandle() { return m_hSetInputDataID; }
	
	private:
		CEMSDCControl();

	private:
		static CEMSDCControl ms_oThis;

		ULONG	m_ulSatID;
		ULONG	m_ulFlags;
		ULONG	m_ulBandwidth;
		ULONG	m_ulInputDataID;

		HANDLE	m_hStart;
		HANDLE	m_hStop;
		HANDLE	m_hSetSatellite;
		HANDLE	m_hSetInputDataID;
};

#endif