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
#pragma warning(disable:4786)

#include "fpimpl.h"
#include "antdspair.h"
#include "emsexcpt.h"
#include "fploader.h"
#include "fpmsgs.h"
#include "directorymonitor.h"
#include "loghelper.h"
#include "ccinputdatathread.h"
#include "emscc.h"

const wchar_t* CEMSFPImpl::ms_cwszFileNameFmt = L"fpsched_%d%s";
const wchar_t* CEMSFPImpl::ms_cwszFileNameExt = L".dat";

// Delay in sending command to the CC.  This is to allow the WS response to get out before a restart type command
// is executed.
const ULONG CEMSFPImpl::ms_culCCCmdDelay = 10000;

CEMSFPImpl::CEMSFPImpl() : 
							CApiObjBase(TEXT("CEMSFPImpl")), 
							m_aTLEs(NULL), 
							m_ulTLEs(0), 
							m_bSchedLoaded(false),
							m_pCC(NULL),
							m_eLastCmd( CMD_UNKNOWN )
{
	m_pCC = new CEMSCCInputDataThread();

	if( !m_pCC )
	{
		THROW_NOMEMORY_EXCEPTION();
	}
}

CEMSFPImpl::CEMSFPImpl( const CEMSFPImpl& x ) : 
											CApiObjBase(TEXT("CEMSFPImpl")),
											m_oConfig( x.m_oConfig ), 
											m_omapSchedules( x.m_omapSchedules ),
											m_aTLEs(NULL), m_ulTLEs(0),
											m_oController( x.m_oController ),
											m_bSchedLoaded( x.m_bSchedLoaded ),
											m_pCC(x.m_pCC),
											m_eLastCmd(x.m_eLastCmd)
{
	if( m_pCC )
		m_pCC->AddRef();

	SetOrbits( x.m_ulTLEs, x.m_aTLEs );
}

CEMSFPImpl::~CEMSFPImpl()
{
	if( m_aTLEs )
	{
		delete[] m_aTLEs;
		m_aTLEs = NULL;
	}

	if( m_pCC )
	{
		m_pCC->Release();
		m_pCC = NULL;
	}

	_SaveSchedules();
}

void 
CEMSFPImpl::Restart()
{
	//! Restart the FP s/w.
	CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_RESTART_COMMAND_RECEIVED );

	if( !m_pCC )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}
		
	EMSCCSPEC cmdCC;
	memset( &cmdCC, 0, sizeof(cmdCC) );

	cmdCC.eCmdType = CMD_OPCMD;
	cmdCC.exData.cmdOp.eCmdType = OPCMD_RESTART_WARM;
	m_pCC->Run( cmdCC, ms_culCCCmdDelay );
}

void 
CEMSFPImpl::Reboot( const bool cbForce )
{
	// Reboot the FP.
	CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_REBOOT_COMMAND_RECEIVED );

	if( !m_pCC )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}


	EMSCCSPEC cmdCC;
	memset( &cmdCC, 0, sizeof(cmdCC) );

	cmdCC.eCmdType = CMD_OPCMD;
	cmdCC.exData.cmdOp.eCmdType = OPCMD_RESTART_COLD;
	m_pCC->Run( cmdCC, ms_culCCCmdDelay );

}

void 
CEMSFPImpl::Start()
{
	// This could be called repeatedly by a controller service.  Prevent repetitive log messages.
	if( CMD_START != m_eLastCmd )
	{
		CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_START_COMMAND_RECEIVED );
	}

	// Start the FP controller.
	if( !m_oController.IsRunning() )
	{
		m_oController.SetConfiguration( m_oConfig );
		m_oController.SetSchedule( m_omapSchedules );
		m_oController.Start();
	}

	m_eLastCmd = CMD_START;

}

void 
CEMSFPImpl::Stop()
{
	// This could be called repeatedly by a controller service.  Prevent repetitive log messages.
	if( CMD_STOP != m_eLastCmd )
	{
		CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_STOP_COMMAND_RECEIVED );
	}

	m_oController.Stop();

	m_eLastCmd = CMD_STOP;

}

void 
CEMSFPImpl::Idle()
{
	if( CMD_IDLE != m_eLastCmd )
	{
		CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_IDLE_COMMAND_RECEIVED );
	}

	m_oController.Idle();

	m_eLastCmd = CMD_IDLE;

}

void 
CEMSFPImpl::SetSchedule( const ULONG culPairID, const ULONG culPasses, const EMSSATTRACKRECORD* caPasses )
{
	CEMSLogMsgParam oParam;
	oParam.Add( culPairID );
	CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_SETSCHEDULE_COMMAND_RECEIVED, oParam );

	if( !_IsValidPairID( culPairID ) )
	{
		CEMSLogMsgParam oParam;
		oParam.Add( culPairID );

		throw CEMSException( EMS_FP_SET_SCHED_INVALID_PAIR_ID, oParam );
	}

	// Remove it if it already exists.
	m_omapSchedules.Remove( culPairID );

	CEMSPairSchedule* pPair = new CEMSPairSchedule( culPairID, _GetAntennaID( culPairID), 
									_GetDSID( culPairID ), culPasses, caPasses );

	if( !pPair )
	{
		THROW_NOMEMORY_EXCEPTION();
	}

	m_omapSchedules.Add( culPairID, pPair );

	// Apply the new schedule immediately.
	m_oController.SetSchedule( m_omapSchedules );

	pPair->Release();
	pPair = NULL;
}

void 
CEMSFPImpl::GetSchedule( const ULONG culPair, ULONG& rulPasses, EMSSATTRACKRECORD*& raPasses )
{
	CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_GETSCHEDULE_COMMAND_RECEIVED );

	CEMSPairSchedule* pPair = NULL;

	try
	{
		pPair = m_omapSchedules.Get( culPair );

		if( pPair )
		{
			rulPasses = pPair->GetNumPasses();
			raPasses = pPair->GetPasses();

			pPair->Release();
			pPair = NULL;
		}
	}
	catch( ... )
	{
		if( pPair )
		{
			pPair->Release();
			pPair = NULL;
		}

		throw;
	}
}

void 
CEMSFPImpl::GetList( ULONG& rulPairs, EMSANTDATAPAIR*& raAntPairs )
{
	CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_GETLIST_COMMAND_RECEIVED );

	m_oConfig.GetList( rulPairs, raAntPairs );
}

void 
CEMSFPImpl::SetOrbits( const ULONG culTLEs, const EMSTLERECORD* castrTLE )
{
	CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_SETORBITS_COMMAND_RECEIVED );

	if( culTLEs > 0 &&
		castrTLE )
	{
		if( m_aTLEs )
		{
			delete[] m_aTLEs;
			m_aTLEs = NULL;
		}

		m_ulTLEs = culTLEs;

		m_aTLEs = new EMSTLERECORD[ m_ulTLEs ];

		if( !m_aTLEs )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memcpy( m_aTLEs, castrTLE, m_ulTLEs*sizeof(EMSTLERECORD) );

		_DistributeTLEs();
	}
}

void 
CEMSFPImpl::GetOrbits( ULONG& rulTLEs, EMSTLERECORD*& rastrTLEs )
{
	CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_GETORBITS_COMMAND_RECEIVED );

	if( m_ulTLEs > 0 &&
		m_aTLEs )
	{
		rulTLEs = m_ulTLEs;

		rastrTLEs = new EMSTLERECORD[ rulTLEs ];

		if( !rastrTLEs )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memcpy( rastrTLEs, m_aTLEs, rulTLEs*sizeof(EMSTLERECORD) );
	}
}

void 
CEMSFPImpl::SetProperty( const wchar_t* cwszKey, const wchar_t* cwszValue )
{
	CEMSLogMsgParam oParam;
	oParam.AddString( cwszKey );
	oParam.AddString( cwszValue );
	CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_SETPROPERTY_COMMAND_RECEIVED, oParam );

	m_oConfig.SetProperty( cwszKey, cwszValue );
}

std::wstring 
CEMSFPImpl::GetProperty( const wchar_t* cwszKey )
{
	CEMSLogMsgParam oParam;
	oParam.AddString( cwszKey );
	CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_GETPROPERTY_COMMAND_RECEIVED, oParam );

	return m_oConfig.GetProperty( cwszKey );
}

void 
CEMSFPImpl::SetConfiguration( const wchar_t* cwszConfigString )
{
	CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_SETCONFIG_COMMAND_RECEIVED );

	m_oConfig.SetConfiguration( cwszConfigString );
	
	// Load the schedule, but only once.
	if( !m_bSchedLoaded )
	{
		m_bSchedLoaded = true;	// Set this flag before attempting, because even the attempt to read should be considered a load.
		_LoadSchedules();
	}
}

std::wstring 
CEMSFPImpl::GetConfiguration()
{
	CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_GETCONFIG_COMMAND_RECEIVED );

	return m_oConfig.GetConfiguration();
}

void 
CEMSFPImpl::_DistributeTLEs()
{
	IEMSAntenna* pAnt = NULL;

	try
	{
		// Send the TLEs to all known antenna controllers.
		CEMSObjectList<ULONG> olstAntennaIDs = m_oConfig.GetAntennaIDs();

		ULONG ulAntennas = olstAntennaIDs.Count();

		for( ULONG l = 0; l < ulAntennas; l++ )
		{
			ULONG ulAntennaID = olstAntennaIDs.GetNext();
			pAnt = CEMSFPLoader::LoadAntennaProxyByID( ulAntennaID, m_oConfig );

			if( pAnt )
			{
				EMS_RESULT hr = pAnt->SetOrbits( m_ulTLEs, m_aTLEs );

				if( EMS_OK != hr )
				{
					CEMSLogMsgParam oParam;
					oParam.AddX( hr );
					oParam.Add( ulAntennaID );
					CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_ANT_SET_ORBITS_FAILED, oParam );
				}
				pAnt->Release();
				pAnt = NULL;
			}
		}
	}
	catch( ... )
	{
		throw;
	}


}

ULONG	
CEMSFPImpl::_GetAntennaID( const ULONG culPair )
{
	return m_oConfig.GetAntennaID( culPair );
}

ULONG	
CEMSFPImpl::_GetDSID( const ULONG culPair )
{
	return m_oConfig.GetDSID( culPair );
}

void 
CEMSFPImpl::_LoadSchedules()
{
	CEMSPairSchedule* pSched = NULL;

	try
	{
		m_omapSchedules.Clear();

		std::wstring owszScheduleFolder = m_oConfig.GetScheduleFolder();

		if( owszScheduleFolder.empty() )
		{
			THROW_RUNTIME_EXCEPTION( EMS_FP_NO_SCHEDULE_FOLDER );
		}

		CEMSLogMsgParam oParam;
		oParam.AddString( owszScheduleFolder.c_str() );
		CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_SCHEDULE_FOLDER_LOAD, oParam );

		CEMSDirectoryMonitor oDirMonitor;
		oDirMonitor.SetDirectory( owszScheduleFolder.c_str() );
		oDirMonitor.SetFileExtension( ms_cwszFileNameExt );
		oDirMonitor.Populate();

		std::wstring owszFile;

		do		
		{
			owszFile = oDirMonitor.Pop();

			if( !owszFile.empty() )
			{
				pSched = new CEMSPairSchedule;

				if( !pSched )
				{
					THROW_NOMEMORY_EXCEPTION();
				}

				CEMSLogMsgParam oParam;
				oParam.AddString( owszFile.c_str() );
				CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_SCHEDULE_FILE_LOAD, oParam );

				pSched->Deserialize( owszFile.c_str() );

				m_omapSchedules.Add( pSched->GetPairID(), pSched );

				pSched->Release();
				pSched = NULL;
			}

		} while( !owszFile.empty() );
	}
	catch( ... )
	{
		if( pSched )
		{
			pSched->Release();
			pSched = NULL;
		}

		throw;
	}
}

void 
CEMSFPImpl::_SaveSchedules()
{
	CEMSPairSchedule* pSched = NULL;

	try
	{
		std::wstring owszScheduleFolder = m_oConfig.GetScheduleFolder();

		if( owszScheduleFolder.empty() )
		{
			THROW_RUNTIME_EXCEPTION( EMS_FP_NO_SCHEDULE_FOLDER );
		}

		CEMSLogMsgParam oParam;
		oParam.AddString( owszScheduleFolder.c_str() );
		CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_SCHEDULE_FOLDER_SAVE, oParam );

		// Go through the schedules, saving each to its own file.
		m_omapSchedules.MoveFirst();

		ULONG ulSchedules = m_omapSchedules.Count();

		for( ULONG l = 0; l < ulSchedules; l++ )
		{
			pSched = m_omapSchedules.GetNext();

			if( !pSched )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			wchar_t wszFileName[ 256 ];
			memset( wszFileName, 0, 256*sizeof(wchar_t) );

			if( 0 > _snwprintf( wszFileName, 255, ms_cwszFileNameFmt, 
														pSched->GetPairID(), 
														ms_cwszFileNameExt ) )
			{
				THROW_RUNTIME_EXCEPTION( EMS_OVERFLOW );
			}

			std::wstring owszPath = owszScheduleFolder;

			if( L'\\' != owszPath.at( owszPath.length() - 1 ) )
			{
				owszPath.append( L"\\" );
			}

			owszPath.append( wszFileName );

			CEMSLogMsgParam oParam;
			oParam.Add( pSched->GetPairID() );
			oParam.AddString( owszPath.c_str() );
			CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_SCHEDULE_FILE_SAVE, oParam );

			pSched->Serialize( owszPath.c_str() );

			pSched->Release();
			pSched = NULL;
		}
	}
	catch( ... )
	{
		if( pSched )
		{
			pSched->Release();
			pSched = NULL;
		}

		throw;
	}
}

bool 
CEMSFPImpl::_IsValidPairID( const ULONG culPairID )
{
	return m_oConfig.DoesPairExist( culPairID );
}