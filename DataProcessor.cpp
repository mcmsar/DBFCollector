/*********************************************************************
*	              Copyright (c) 2011 by EMS Technologies, Inc.,
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

#include "DataProcessor.h"
#include "emserror.h"


const char  c_szLogFile[] = "C:\\EMSDBFlogger";


int CEMSDataProcessor::ms_iSeqNum = 1;



//CEMSDataProcessor::CEMSDataProcessor(CEMSPointerList<CEMSRawBuffObj>& refList, CEMSQueue<DBFTrackingData >&qDBFBeamVectors,CDBFBeamVectorCalculator *pDBFBeamVect) : m_bRunning(false), 
//	m_bInitialized(false), m_lstFreeBuffObjs(refList)
CEMSDataProcessor::CEMSDataProcessor(CEMSPointerList<CEMSRawBuffObj>& refList, CEMSQueue<DBFTrackingData >&qDBFBeamVectors) : m_bRunning(false), 
	m_bInitialized(false), m_lstFreeBuffObjs(refList)
{
	char szLogFile[256];
	wProcess = 0;

	memset(szLogFile, 0, sizeof(szLogFile) );

	sprintf(szLogFile, "%s_%d.txt", c_szLogFile, ms_iSeqNum++ ); 
	m_lpLogFile = fopen( szLogFile, "at" );
	m_pDBF = new CDigitalBeamFormer(qDBFBeamVectors);
}

CEMSDataProcessor::CEMSDataProcessor( const CEMSDataProcessor& x ) : m_lstFreeBuffObjs( x.m_lstFreeBuffObjs ), 
	m_pDBF( x.m_pDBF ) //, m_pDBFBeamVectorCalculator( x.m_pDBFBeamVectorCalculator)
{
	if( m_lpLogFile )
	{
		fclose( m_lpLogFile );
		m_lpLogFile = NULL;
	}

}

CEMSDataProcessor::~CEMSDataProcessor()
{
	Reset();
	delete m_pDBF;
}

void 
CEMSDataProcessor::Reset()
{
	m_oCS.Enter();

	m_bRunning = false;

	try
	{
/*		if( m_aMainBuff )
		{
			delete[] m_aMainBuff;
			m_aMainBuff = NULL;
		}*/
		m_oCS.Leave();
	}
	catch( ... )
	{
		m_oCS.Leave();
		throw;
	}
	
}

bool
CEMSDataProcessor::Initialize( )
{
	m_bInitialized = true;
	return m_bInitialized;
}



void
CEMSDataProcessor::Start()
{
	if(!m_bInitialized)
	{
		Initialize();
	}
	m_bRunning = true;
	start();
}

void
CEMSDataProcessor::Stop()
{
	SetEvent(m_hStopEvent);
//	stop();
}

void
CEMSDataProcessor::run()
{
	if( m_bInitialized )
	{
		EMS_RESULT hr = EMS_OK;
		

		HANDLE hEvent[2];

		hEvent[0] = m_hStopEvent;
//		hEvent[1] = m_hEvent; //filler event

		DWORD dwTimeout = 400;
		DWORD dwEventCount = 1;

		m_pDBF->Initialize("C:\\Raw\\");

		while( m_bRunning )
		{
			
			FILE* m_exitFile;
			try
			{
				hr = WaitForMultipleObjects( dwEventCount, hEvent, FALSE, dwTimeout ); // Wait for the interrupt
				switch(hr)	
				 {						
					case WAIT_OBJECT_0:
					case WAIT_ABANDONED_0: // Fixes crashing in VS debugger
					case WAIT_ABANDONED_0 + 1:
					case WAIT_FAILED:
						{
							m_exitFile  = fopen( "C:\\exitFile.txt", "wt");
							fprintf(m_exitFile, "made it to CEMSDataProcessor!\n");
							fprintf(m_exitFile, "hr: %d", hr);
							fflush(m_exitFile);
							fclose(m_exitFile);
							//stop
							m_bRunning = false;
						}
						break;
					case WAIT_OBJECT_0 + 1:
						{
							int x  = 5;
							_ProcessData();
						}
						break;
					default:
						{
							_ProcessData();
						}
						break;
				}
			}
			catch( ... )
			{
				m_exitFile  = fopen( "C:\\exitFile.txt", "wt");
				fprintf(m_exitFile, "made it to CEMSDataProcessor catch any!\n");
				fprintf(m_exitFile, "hr: %d", hr);
				fflush(m_exitFile);
				fclose(m_exitFile);
				// a error occured, log it and stop the thread.
				m_bRunning = false;
				if( m_lpLogFile )
				{
					fprintf( m_lpLogFile, "\n::run() --> unknown exception\n" );
					fflush( m_lpLogFile );
				}
			}
		}

		m_bRunning = false;
	}
}

void
CEMSDataProcessor::LockBuffer( BOOL bWait )
{
	m_oCS.Enter();
}


void
CEMSDataProcessor::UnlockBuffer( )
{
	m_oCS.Leave();
}

//snl test
int nProcessorCount = 0;
#include <sstream>
#include <iostream>
//snl test end
void
CEMSDataProcessor::_ProcessData()
{
	m_oCSIncoming.Enter();
	m_oCS.Enter();
	CEMSRawBuffObj* pRawBuff = NULL;
	char szFileName[256];
	

	try
	{
		m_lstIncomingBuffObjs.MoveFirst();
		while( (pRawBuff = m_lstIncomingBuffObjs.GetNext() ) != NULL)
		{
			m_lstUsedBuffObjs.Add(pRawBuff);
			m_lstIncomingBuffObjs.RemoveCurrent();

			pRawBuff->Release();
			pRawBuff = NULL;
		}
		m_oCSIncoming.Leave();

		m_lstUsedBuffObjs.MoveFirst();
		while( (pRawBuff = m_lstUsedBuffObjs.GetNext() ) != NULL)
		{
			memset(szFileName, 0, sizeof(szFileName) );
			sprintf(szFileName,"D:\\RAW\\DBF_%04d.bin", ms_iSeqNum);

			//printf("\n one second data to process number: %d", ms_iSeqNum ); 
			ms_iSeqNum++;
			unsigned char*pBuff = pRawBuff->GetRawData();
			if(EMS_OK == m_pDBF->SetRawData(pBuff/*pRawBuff->GetRawData()*/, pRawBuff->GetBuffSize()) )
			{
				//snl
				//m_pDBFBeamVectorCalculator->SetRawData(pBuff/*pRawBuff->GetRawData()*/, pRawBuff->GetBuffSize(), *(pRawBuff->GetPassRecs()) );
				//m_oDBF.GetPassSchedule(pRawBuff->GetBuffTime());
				
				m_pDBF->SetPassSchedule(pRawBuff->GetPassRecs(), pRawBuff->GetBuffTime());
				
				WORD wProcess = m_pDBF->GetProcess();

				try
				{
					m_pDBF->ProcessAll();
				}
				catch(...)
				{
					//error to log
					if( m_lpLogFile )
					{
						fprintf( m_lpLogFile, "\n::_ProcessData() --> unknown exception\n" );
						fflush( m_lpLogFile );
					}
				}
			}

			_FreeObj( pRawBuff );
			m_lstUsedBuffObjs.RemoveCurrent();
			pRawBuff->Release();
			pRawBuff = NULL;
		}

		m_oCS.Leave();
	}
	catch(...)
	{
		m_oCSIncoming.Leave();
		m_oCS.Leave();
		if( pRawBuff )
		{
			pRawBuff->Release();
			pRawBuff = NULL;
		}
		throw;
	}
}

void
CEMSDataProcessor::_FreeObj( CEMSRawBuffObj* pRawBuff )
{
	if( pRawBuff )
	{
		m_oCSFreeObjs.Enter();
		
		try
		{
			m_lstFreeBuffObjs.Add(pRawBuff);
			m_oCSFreeObjs.Leave();
		}
		catch(...)
		{
			m_oCSFreeObjs.Leave();
			throw;
		}
	}
}

void
CEMSDataProcessor::GetFreeBuffObjs( CEMSPointerList<CEMSRawBuffObj>& lstObj )
{
	CEMSRawBuffObj* pRawBuff = NULL;
	m_oCSFreeObjs.Enter();
		
	try
	{
		m_lstFreeBuffObjs.MoveFirst();

		while( (pRawBuff = m_lstFreeBuffObjs.GetNext() ) != NULL)
		{
			lstObj.Add( pRawBuff );
			pRawBuff->Release();
			pRawBuff = NULL;
		}

		m_lstFreeBuffObjs.Clear();
		m_oCSFreeObjs.Leave();
	}
	catch(...)
	{
		m_oCSFreeObjs.Leave();
		throw;
	}
}

void
CEMSDataProcessor::AddBuffObj( CEMSRawBuffObj* pObj )
{
	if( pObj )
	{
		m_oCSIncoming.Enter();
		
		try
		{
			m_lstIncomingBuffObjs.Add(pObj);
			m_oCSIncoming.Leave();
		}
		catch(...)
		{
			m_oCSIncoming.Leave();
			throw;
		}
	}
}
