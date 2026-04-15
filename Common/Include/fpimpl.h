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

#ifndef __FPIMPL_H__
#define __FPIMPL_H__

#include "fp.h"
#include "fpconfig.h"
#include "pointermap.h"
#include "fpcontroller.h"

class CEMSPairSchedule;
class CEMSCCInputDataThread;

//! Base Front End Processor (FP) implementation.
class CEMSFPImpl : public CApiObjBase
{
	public:
		CEMSFPImpl();
		CEMSFPImpl( const CEMSFPImpl& x );
		virtual ~CEMSFPImpl();

		void Restart();

		void Reboot( const bool cbForce );

		void Start();

		void Stop();

		void Idle();
		
		void SetSchedule( const ULONG culPair, const ULONG culPasses, const EMSSATTRACKRECORD* caPasses );

		void GetSchedule( const ULONG culPair, ULONG& rulPasses, EMSSATTRACKRECORD*& raPasses );

		void GetList( ULONG& rulPairs, EMSANTDATAPAIR*& raAntPairs );

		void SetOrbits( const ULONG culTLEs, const EMSTLERECORD* castrTLE );

		void GetOrbits( ULONG& rulTLEs, EMSTLERECORD*& rastrTLEs );

		void SetProperty( const wchar_t* cwszKey, const wchar_t* cwszValue );

		std::wstring GetProperty( const wchar_t* cwszKey );

		void SetConfiguration( const wchar_t* cwszConfigString );

		std::wstring GetConfiguration();

	private:
		void	_DistributeTLEs();
		ULONG	_GetAntennaID( const ULONG culPair );
		ULONG	_GetDSID( const ULONG culPair );

		void _LoadSchedules();
		void _SaveSchedules();

		bool _IsValidPairID( const ULONG culPairID );

	protected:
		CEMSFPConfig	m_oConfig;
		CEMSPointerMap<const ULONG,CEMSPairSchedule> m_omapSchedules;
		CEMSFPController m_oController;

	private:
		static const wchar_t* ms_cwszFileNameFmt;
		static const wchar_t* ms_cwszFileNameExt;
		static const ULONG ms_culCCCmdDelay;

	private:
		EMSTLERECORD*	m_aTLEs;
		ULONG			m_ulTLEs;
		bool			m_bSchedLoaded;
		CEMSCCInputDataThread*	m_pCC;
		
		typedef enum tagCmd
		{
			CMD_UNKNOWN = 0,
			CMD_START = 1,
			CMD_STOP = 2,
			CMD_IDLE = 3
		} EMSFPCMD;

		EMSFPCMD m_eLastCmd;

};

#endif