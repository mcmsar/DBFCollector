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

#ifndef __DC_CONTROL_SUMMARY_H__
#define __DC_CONTROL_SUMMARY_H__

//! Summary of control parameters for one channel of a DC.
class __declspec(dllexport) CEMSDCControlSummary
{
	public:
		typedef enum eDataChange
		{
			EMS_DC_EVT_UNK = 0,
			EMS_DC_EVT_SAT = 1,
			EMS_DC_EVT_INPUTID = 2,
			EMS_DC_EVT_START = 3,
			EMS_DC_EVT_STOP = 4,
			EMS_DC_EVT_LAST = EMS_DC_EVT_STOP
		} EMSDCDATACHANGE;
		
	public:
		CEMSDCControlSummary() : m_ulSatID(0), m_ulFlags(0), m_ulBandwidth(0),
								m_ulInputDataID(0), m_ulADBoardID(0),
								m_ulADChannelID(0), m_eEvt( EMS_DC_EVT_UNK ),
								m_lRefCount(1) {}
		
		CEMSDCControlSummary( const CEMSDCControlSummary& x ) :
								m_ulSatID(x.m_ulSatID), m_ulFlags(x.m_ulFlags), 
								m_ulBandwidth(x.m_ulBandwidth),
								m_ulInputDataID(x.m_ulInputDataID), 
								m_ulADBoardID(x.m_ulADBoardID),
								m_ulADChannelID(x.m_ulADChannelID), 
								m_eEvt(x.m_eEvt),
								m_lRefCount(1) {}
		
		~CEMSDCControlSummary() {}

		void SetSatID( const ULONG culSatID ) { m_ulSatID = culSatID; }
		ULONG GetSatID() const { return m_ulSatID; }

		void SetFlags( const ULONG culFlags ) { m_ulFlags = culFlags; }
		ULONG GetFlags() const { return m_ulFlags; }

		void SetBandwidth( const ULONG culBandwidth ) { m_ulBandwidth = culBandwidth; }
		ULONG GetBandwidth() const { return m_ulBandwidth; }

		void SetInputDataID( const ULONG culInputDataID ) { m_ulInputDataID = culInputDataID; }
		ULONG GetInputDataID() const { return m_ulInputDataID; }

		void SetADBoardID( const ULONG culADBoardID ) { m_ulADBoardID = culADBoardID; }
		ULONG GetADBoardID() const { return m_ulADBoardID; }

		void SetADChannelID( const ULONG culADChannelID ) { m_ulADChannelID = culADChannelID; }
		ULONG GetADChannelID() const { return m_ulADChannelID; }

		void SetEventType( const EMSDCDATACHANGE ceEvt ) { m_eEvt = ceEvt; }
		EMSDCDATACHANGE GetEventType() const { return m_eEvt; }

		ULONG AddRef() { return InterlockedIncrement((LONG*)&m_lRefCount); }

		ULONG Release();

	private:
		ULONG				m_ulSatID;
		ULONG				m_ulFlags;
		ULONG				m_ulBandwidth;
		ULONG				m_ulInputDataID;
		ULONG				m_ulADBoardID;
		ULONG				m_ulADChannelID;
		EMSDCDATACHANGE		m_eEvt;

		LONG				m_lRefCount;
};

inline
ULONG CEMSDCControlSummary::Release()
{
	ULONG ulRef = InterlockedDecrement((LONG*)&m_lRefCount); 
	
	if( 0 == ulRef )
		delete this;

	return ulRef;
}

#endif