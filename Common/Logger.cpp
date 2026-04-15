/******************************************************************** 
*	Module:			logger.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	
*						
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2001 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	01/08/08		rvw	start

********************************************************************/
#include "logger.h"
#include "leodefns.h"

#include "debugwin.h"
static CDebugWin debugWin;
static char szDebug[256];

CEMSLogger::CEMSLogger( LPCTSTR lpcszTaskName )
{
	m_bUseDiskFile = FALSE;

	m_lpszTaskName = 0;

	_SetTaskName( lpcszTaskName );

	m_bInitialized = FALSE;

	m_lpPipeline = 0;

	m_lpLogSrc = 0;

	m_lpMaintLogSrc = 0;
}

CEMSLogger::~CEMSLogger( void )
{ 
	Reset();

	if ( m_lpszTaskName )
	{
		delete m_lpszTaskName;
		m_lpszTaskName = 0;
	}
}
	
EMS_RESULT CEMSLogger::Initialize( LPCTSTR lpcszTaskName )
{
	EMS_RESULT hr = EMS_OK;

	if ( !m_bInitialized )
	{
		if ( lpcszTaskName && *lpcszTaskName )
			_SetTaskName( lpcszTaskName );

		hr = CoCreateInstance( CLSID_EMSDataPipeline, 0, CLSCTX_ALL, 
								IID_IEMSDataPipeline, (LPVOID*)&m_lpPipeline );

		if ( hr == EMS_OK )
		{
			m_lpLogSrc = new CEMSPacketSource( LEO_LOG_DATA, EMS_MAX_LOG_MSG_LENGTH );

			if ( m_lpLogSrc )
			{
				hr = m_lpPipeline->RegisterSource( m_lpLogSrc );

				if ( hr == EMS_OK )
				{
					m_lpMaintLogSrc = new CEMSPacketSource( LEO_MAINT_LOG_DATA, EMS_MAX_LOG_MSG_LENGTH );

					if ( m_lpMaintLogSrc )
					{
						hr = m_lpPipeline->RegisterSource( m_lpMaintLogSrc );
					}
					else
						hr = EMS_NO_MEMORY;
				}
			}
			else
				hr = EMS_NO_MEMORY;
		}

		m_bInitialized = ( hr == EMS_OK );
	}

	return hr;
}

EMS_RESULT CEMSLogger::Reset( void )
{
	if ( m_lpPipeline )
	{
		if ( m_lpLogSrc )
		{
			m_lpPipeline->UnRegisterSource( m_lpLogSrc );
			m_lpLogSrc->Release();
			m_lpLogSrc = 0;
		}

		if ( m_lpMaintLogSrc )
		{
			m_lpPipeline->UnRegisterSource( m_lpMaintLogSrc );
			m_lpMaintLogSrc->Release();
			m_lpMaintLogSrc = 0;
		}
		
		m_lpPipeline->Release();

		m_lpPipeline = 0;
	}

	return EMS_OK;
}

int CEMSLogger::OutputMessage( EMSLOGMSGTYPE msgType, LPCTSTR lpcszMessage ) 
{ 
	if ( !m_bInitialized )
		Initialize();

	debugWin.OutputMsg( (LPVOID)lpcszMessage );

	return 0; 
}

int CEMSLogger::_SetTaskName( LPCTSTR lpcszTaskName )
{
	int nLength = 0;

	if ( m_lpszTaskName )
	{
		delete m_lpszTaskName;
		m_lpszTaskName = 0;
	}

	if ( lpcszTaskName && *lpcszTaskName )
	{
		m_lpszTaskName = new TCHAR[ lstrlen( lpcszTaskName ) + 1 ];

		if ( m_lpszTaskName )
		{
			lstrcpy( m_lpszTaskName, lpcszTaskName );

			nLength = lstrlen( m_lpszTaskName );
		}
	}

	return nLength;
}
