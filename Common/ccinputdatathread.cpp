/*********************************************************************
*	              Copyright (c) 2009 by EMS Technologies, Inc.,
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

#include "ccinputdatathread.h"
#include "pksource.h"
#include "leodefns.h"
#include "criticalsection.h"

CEMSCCInputDataThread::CEMSCCInputDataThread() : m_hrLast(EMS_OK), m_ulDelay(0)
{
	memset( &m_strCMD, 0, sizeof(m_strCMD) );
}

CEMSCCInputDataThread::~CEMSCCInputDataThread()
{
	stop();
}

void 
CEMSCCInputDataThread::Run( const EMSCCSPEC& crstrCMD, const ULONG culDelay )
{
	memset( &m_strCMD, 0, sizeof(m_strCMD) );
	m_strCMD = crstrCMD;
	m_ulDelay = culDelay;
	run();
}

void 
CEMSCCInputDataThread::run()
{
	CEMSPacketSource* pSrc = NULL;
	IEMSDataPipeline* pPipe = NULL;

	CEMSCriticalSection cs;

	try
	{
		cs.Enter();

		Sleep( m_ulDelay );

		m_hrLast = EMS_OK;

		m_hrLast = CoCreateInstance( CLSID_EMSDataPipeline, 0, CLSCTX_ALL, IID_IEMSDataPipeline, (LPVOID*)&pPipe );
    
		if( SUCCEEDED(m_hrLast) && NULL != pPipe )
		{
			pSrc = new CEMSPacketSource( LUT_CC_DATA, sizeof(EMSCCSPEC) );
			if( NULL == pSrc )
				m_hrLast = EMS_NO_MEMORY;
			else
			{
				m_hrLast = pPipe->RegisterSource( pSrc );
			}
		}

		if( SUCCEEDED(m_hrLast) )
		{
			ULONG ulWritten = 0;
			m_hrLast = pSrc->Write( (const BYTE*) &m_strCMD, sizeof(m_strCMD), &ulWritten );
		}
	}
	catch( ... )
	{
		m_hrLast = EMS_EXCEPTION;
	}

	if( pPipe )
	{
		if( pSrc )
		{
			pPipe->UnRegisterSource( pSrc );
		}

		pPipe->Release();
		pPipe = NULL;
	}

	if( pSrc )
	{
		pSrc->Release();
		pSrc = NULL;
	}

	cs.Leave();


}