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

#include "CollectionObject.h"
#include "emserror.h"
#include <stdio.h>
#include "emsclock.h"				// CEMSSystemClock
//#include "EMSQueue.h"

//snl
//#define BUFF_SIZE 38400000
#define BUFF_SIZE 128000000
#define BUFF_SIZE_PLUS_TIME 128000008 //one second at 1M samples + sizeof(EMSTIME).

//snl
//const int DATA_PROCESSOR_COUNT	= 16;
//const int DATA_PROCESSOR_COUNT	= 8;
//const int DATA_PROCESSOR_COUNT	= 9;
//const int DATA_PROCESSOR_COUNT	= 15;
//const int DATA_PROCESSOR_COUNT	= 24;	//snl feb1,2021 
//const int DATA_PROCESSOR_COUNT	= 24;	//snl feb1,2021 
const int DATA_PROCESSOR_COUNT	= 24;	//snl feb1,2021 

//const int DATA_PROCESSOR_COUNT	= 2;

//const int DATA_PROCESSOR_COUNT	= 1;
//const int DATA_PROCESSOR_COUNT	= 32;

//#include "C:\Program Files (x86)\Visual Leak Detector\include\vld.h"
//end snl
CEMSCollectionObject::CEMSCollectionObject() : m_bRunning(false), m_bInitialized(false),
//                                       m_hEvent(NULL), m_ulCntBuffObjects(20),
                                       //m_hEvent(NULL), m_ulCntBuffObjects(80),
										m_hEvent(NULL), m_ulCntBuffObjects(100),
										//m_hEvent(NULL), m_ulCntBuffObjects(200),

									   m_ulBuffSize(BUFF_SIZE_PLUS_TIME), m_aMainBuff(NULL)
{
	m_pADBoard = NULL;
	m_pDataProcessor = NULL;
	m_pDataProcessor1 = NULL;
	m_pDataProcessor2 = NULL;

	m_LastBuffTime.intTime = 0L;

	m_oDBFpass.Initialize(1);
}

CEMSCollectionObject::CEMSCollectionObject( const CEMSCollectionObject& x )
{
}

CEMSCollectionObject::~CEMSCollectionObject()
{
	Reset();
	//delete m_pDBFBeamVectorCalculator;
}

void 
CEMSCollectionObject::Reset()
{
	//m_oCS.Enter();

	Stop();

	Sleep(1000);

	if( m_pDataProcessor )
	{
		delete m_pDataProcessor;
		m_pDataProcessor = NULL;
	}

	if( m_pDataProcessor1 )
	{
		delete m_pDataProcessor1;
		m_pDataProcessor1 = NULL;
	}

	if( m_pDataProcessor2 )
	{
		delete m_pDataProcessor2;
		m_pDataProcessor2 = NULL;
	}

	m_bRunning = false;

	try
	{
		if( m_aMainBuff )
		{
			delete[] m_aMainBuff;
			m_aMainBuff = NULL;
		}
		//m_oCS.Leave();
	}
	catch( ... )
	{
		m_oCS.Leave();
		throw;
	}
	
}

bool
CEMSCollectionObject::Initialize( ULONG ulBuffSize, ULONG ulCntBuffObjects )
{
//	m_ulCntBuffObjects = ulCntBuffObjects;
//	m_ulBuffSize = ulBuffSize;
	_Initialize();
	return m_bInitialized;
}


void
CEMSCollectionObject::_Initialize()
{
	if( !m_bInitialized )
	{
		m_oCS.Enter();
		CEMSRawBuffObj* pRawBuff = NULL;
		try
		{
			m_lstFreeBuffObjs.Clear();
			m_lstUsedBuffObjs.Clear();

			for( ULONG l = 0; l < m_ulCntBuffObjects; l++ )
			{
				pRawBuff = new CEMSRawBuffObj();
				if( pRawBuff )
				{
					pRawBuff->Initialize( m_ulBuffSize );
					m_lstFreeBuffObjs.Add(pRawBuff);
					pRawBuff->Release();
					pRawBuff = NULL;
				}
				// else memory error
			}
			//m_pDBFBeamVectorCalculator = new CDBFBeamVectorCalculator(m_qDBFBeamVectors);

			m_bInitialized = true;
			m_oCS.Leave();

		}
		catch(...)
		{
			m_oCS.Leave();
			if( pRawBuff )
			{
				pRawBuff->Release();
				pRawBuff = NULL;
			}
			throw;
		}

		m_aMainBuff = new unsigned char[BUFF_SIZE_PLUS_TIME];

		if( m_aMainBuff && !m_pADBoard )
	{
			EMS_RESULT hr = CoCreateInstance( CLSID_EMSADBoard, NULL, CLSCTX_ALL,
								              IID_IEMSADBoard, (void**) &m_pADBoard );

		//EMS_RESULT hr = CoCreateInstance( CLSID_EMSADBoard, NULL, CLSCTX_ALL,
		//						              IID_IEMSADBoard_DEBUG, (void**) &m_pADBoard );
			/*EMS_RESULT hr = CoCreateInstance( CLSID_EMSADBoard_DEBUG, NULL, CLSCTX_ALL,
								              IID_IEMSADBoard_DEBUG, (void**) &m_pADBoard );
*/
			if( EMS_OK != hr || m_pADBoard == NULL)
			{
				// error
				m_bInitialized = false;
			}
			else
			{
				m_pADBoard->SetTransferBuffer( (short*)m_aMainBuff );

				//DWORD dwSampleRate = 1000000;
				DWORD dwSampleRate = 500000;
				
				DWORD dwSampleSize = dwSampleRate * 32;
				//DWORD dwSampleSize = dwSampleRate * 64; //2 seconds
				DWORD dwBufferSize = 128000008;//BUFF_SIZE_PLUS_TIME;

				
				printf("pADBoard Initialize - Sample Rate: %d, Buffer Size: %d\n", dwSampleRate, dwBufferSize);

				hr = m_pADBoard->Init(dwBufferSize, dwSampleSize, dwSampleRate);
				if( EMS_OK == hr )
				{
					m_bInitialized = true;
					
					//std::cout << "GetVersionInfoA: "<< m_pADBoard->GetVersionInfoA(version, model, max, length)<< std::endl;
					//std::cout << "GetVersionInfoW:: "<< m_pADBoard->GetVersionInfoW() << std::endl;
					//std::cout << "sample rate: " << dwSampleRate << std::endl;
				}
				else
				{
					m_bInitialized = false;
				}
			}

			m_hEvent = _CreateEvent( "EvDataReadyX" );
		}
		//snl
		for( int i = 0; i < DATA_PROCESSOR_COUNT;i++ )
		{
			//CEMSDataProcessor *pRec = new CEMSDataProcessor( m_lstFreeBuffObjs, m_qDBFBeamVectors, m_pDBFBeamVectorCalculator );
			CEMSDataProcessor *pRec = new CEMSDataProcessor( m_lstFreeBuffObjs, m_qDBFBeamVectors ); //, m_pDBFBeamVectorCalculator );
			m_qDataProcessor.Add(pRec  );
			pRec->Release();
			pRec = 0;
		}
		//m_pDBFBeamVectorCalculator->Initialize();
		//m_pDBFBeamVectorCalculator->Start();
		if(!m_pDataProcessor)
		{
			//snl changes
			/*m_pDataProcessor = */GetFirstProcessor();
			//m_pDataProcessor = GetNextProcessor();

			//end snl
			//m_pDataProcessor = new CEMSDataProcessor();
			/*if( m_pDataProcessor )
			{
				m_pNextDataProcessor = m_pDataProcessor;
				m_pDataProcessor->Initialize();
			}*/
		}
		/*if(!m_pDataProcessor1)
		{
			m_pDataProcessor1 = new CEMSDataProcessor();
			if( m_pDataProcessor1 )
			{
				m_pDataProcessor1->Initialize();
			}
		}
		if(!m_pDataProcessor2)
		{
			m_pDataProcessor2 = new CEMSDataProcessor();
			if( m_pDataProcessor2 )
			{
				m_pDataProcessor2->Initialize();
			}
		}*/
	}
}
//snl test
int nCount = 0;
#include <sstream>
#include <iostream>
//snl test end
void
CEMSCollectionObject::_ProcessBuffData()
{
	const CEMSSystemClock c_sysClock;
	EMSTIME bufferTime = c_sysClock.GetTime();

	m_oCS.Enter();
	if( m_pADBoard )
		m_pADBoard->LockBuffer(true);

	CEMSRawBuffObj* pRawBuff = NULL;
	try
	{
		if( m_lstFreeBuffObjs.Count() == 0 )
		{
			Sleep(200);
			_FillOutputBuffer();
		}

		if( m_lstFreeBuffObjs.Count() > 0 )
		{

			m_lstFreeBuffObjs.MoveFirst();
			pRawBuff = m_lstFreeBuffObjs.GetNext();
			if( pRawBuff )
			{
				if( bufferTime.intTime <= m_LastBuffTime.intTime )
				{
					bufferTime.intTime = m_LastBuffTime.intTime + 1;
				}

				m_LastBuffTime.intTime = bufferTime.intTime;

				pRawBuff->SetBuffTime(bufferTime);
				pRawBuff->SetPassRecs( m_oDBFpass.GetPassSchedule(bufferTime) );
				m_lstFreeBuffObjs.RemoveCurrent();
				pRawBuff->SetBuffData( m_aMainBuff, m_ulBuffSize );
				m_lstUsedBuffObjs.Add( pRawBuff );
				pRawBuff->Release();
				////test snl
				/*std::ostringstream str;

				str << " Collection object Process  # "<< ++nCount << std::endl; 
				
				OutputDebugString( str.str().c_str() );*/
				if( m_lstUsedBuffObjs.Count() > 4 )
				{

					_FillOutputBuffer();
				}
			}
		}
		else
		{
			// error
			printf("\nCEMSCollectionObject::_ProcessBuffData() --> Need more buffer objects!!!!");
			//OutputDebugString( "\nCEMSCollectionObject::_ProcessBuffData() --> Need more buffer objects!!!!");
			_FillOutputBuffer();
		}
		if( m_pADBoard )
			m_pADBoard->UnlockBuffer();
		m_oCS.Leave();
	}
	catch(...)
	{
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
CEMSCollectionObject::_SetNextDP()
{
	//testing...snl..tbr
	m_pNextDataProcessor = m_pDataProcessor;
	return;
	//end testing
	if(m_pDataProcessor == m_pNextDataProcessor)
	{
		m_pNextDataProcessor = m_pDataProcessor1;
	}
	else if(m_pDataProcessor1 == m_pNextDataProcessor)
	{
		m_pNextDataProcessor = m_pDataProcessor2;
	}
	else
	{
		m_pNextDataProcessor = m_pDataProcessor;
	}
}

void 
CEMSCollectionObject::_FillOutputBuffer()
{
	m_oCS.Enter();

	CEMSRawBuffObj* pRawBuff = NULL;
	static BOOL bInitializeProc = false;
	try
	{
		//if( m_pNextDataProcessor )
		{

			if( m_lstUsedBuffObjs.Count() > 0 )
			{

				m_lstUsedBuffObjs.MoveFirst();
				while( (pRawBuff = m_lstUsedBuffObjs.GetNext()) != NULL )
				{

					//m_pNextDataProcessor->AddBuffObj(pRawBuff);
					//GetFirstProcessor()->AddBuffObj(pRawBuff);
					CEMSDataProcessor *pNext = GetNextProcessor();
					if( pNext && bInitializeProc == false )
					{
						pNext->Initialize();
						pNext->Start();
					}
					if( pNext == NULL )
					{
						bInitializeProc = true;
						/*pNext =*/ GetFirstProcessor();
						pNext = GetNextProcessor();
					}
					pNext->AddBuffObj(pRawBuff);
					m_lstUsedBuffObjs.RemoveCurrent();
					pRawBuff->Release();
					pRawBuff = NULL;
					pNext->Release();
					pNext = NULL;
				}
			}

			//m_pNextDataProcessor->GetFreeBuffObjs(m_lstFreeBuffObjs);
			//GetFirstProcessor()->GetFreeBuffObjs(m_lstFreeBuffObjs);
			//_SetNextDP();
		}
		//else
		//{
		//	int x = 1;//error
		//}
		//m_oCS.Leave();

	}
	catch(...)
	{
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
CEMSCollectionObject::Start()
{
	if(!m_bInitialized)
	{
		_Initialize();
	}
	m_bRunning = true;
	start();
}

void
CEMSCollectionObject::Stop()
{
	SetEvent(m_hStopEvent);
	{
		m_bRunning = false;
		if( m_pADBoard )
			m_pADBoard->Stop();
		if( m_pDataProcessor )
			m_pDataProcessor->Stop();
		if( m_pDataProcessor1 )
			m_pDataProcessor1->Stop();
		if( m_pDataProcessor2 )
			m_pDataProcessor2->Stop();
		CEMSDataProcessor *pList = NULL;
		m_qDataProcessor.MoveFirst();

		while( pList = m_qDataProcessor.GetNext() )
		{
			if( pList )
				pList->Stop();
			pList->Release();
			pList = NULL;
		}
		
	}
	//stop();
}

void
CEMSCollectionObject::run()
{
	if( m_bInitialized )
	{
		EMS_RESULT hr = EMS_OK;
		

		HANDLE hEvent[2];

		hEvent[0] = m_hStopEvent;
		hEvent[1] = m_hEvent; //filler event

		DWORD dwTimeout = 400;
		DWORD dwEventCount = 2;

		ULONG iCounterOneSecond = 1;

		const CEMSSystemClock c_sysClock;

		EMSTIME timeStart;

		double dTDiff = 0.0;

		timeStart = c_sysClock.GetTime();

		//unsigned char   aInBuff[16000000];

		if( m_pADBoard )
		{
			m_pADBoard->Start();
		}
		else
		{
			//error
			m_bRunning = false;
		}

		if( m_pDataProcessor )
		{
			m_pDataProcessor->Start();
			//commented for testing..tbr..snl
			/*m_pDataProcessor1->Start();
			m_pDataProcessor2->Start();*/
		}
		else
		{
			//error
			//m_bRunning = false;
		}

		time_t my_time = time(NULL);
		printf("Initial checks complete - %s", ctime(&my_time));
		
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
							fprintf(m_exitFile, "made it to CEMSCollectionObject!\n");
							fprintf(m_exitFile, "hr: %d", hr);
							fflush(m_exitFile);
							fclose(m_exitFile);
							//stop
							m_bRunning = false;
							m_pADBoard->Stop();
							if( m_pDataProcessor )
								m_pDataProcessor->Stop();
							if( m_pDataProcessor1)
								m_pDataProcessor1->Stop();
							if( m_pDataProcessor2 )
								m_pDataProcessor2->Stop();
						}
						break;
					case WAIT_OBJECT_0 + 1:
						{
							int x  = 5;
							CEMSTime oCurrent(c_sysClock.GetTime());

							dTDiff = oCurrent.SecondsDifferent(timeStart);
//							printf("\nCEMSCollectionObject::run() One Second RAW data, number: %d, timeDiff: %f", iCounterOneSecond++, -dTDiff ); 

							_ProcessBuffData();
							//Sleep(400);
							//memmove(aInBuff, (void*)m_aSharedBuff, 16000000);
//							AddBuffData(aInBuff, 16000000 );
//							ResetEvent(m_hEvent);
						}
						break;
					default:
						{
							//snl test
							//_ProcessBuffData();
							_FillOutputBuffer();
						}
						break;
				}
			}
			catch( ... )
			{
				m_exitFile  = fopen( "C:\\exitFile.txt", "wt");
				fprintf(m_exitFile, "made it to CEMSCollectionObject catch any!\n");
				fprintf(m_exitFile, "hr: %d", hr);
				fflush(m_exitFile);
				fclose(m_exitFile);
				// a error occured, log it and stop the thread.
				m_bRunning = false;
			}
		}

		m_bRunning = false;
		m_bInitialized = false;
	}
}

void
CEMSCollectionObject::LockBuffer( BOOL bWait )
{
	m_oCSMainBuff.Enter();
}


void
CEMSCollectionObject::UnlockBuffer( )
{
	m_oCSMainBuff.Leave();
}

HANDLE 
CEMSCollectionObject::_CreateEvent( LPCTSTR lpcszSignalName )
{
	EMS_RESULT hr = EMS_OK;
	HANDLE hEvent = INVALID_HANDLE_VALUE;

	if( lpcszSignalName && *lpcszSignalName )
	{
		SECURITY_ATTRIBUTES attr;         // security attributes
		SECURITY_DESCRIPTOR sd;

		InitializeSecurityDescriptor( &sd, SECURITY_DESCRIPTOR_REVISION );

		SetSecurityDescriptorDacl( &sd, TRUE, 0, FALSE );

		memset( (void *)&attr, 0, sizeof( attr ) );
		attr.nLength              = sizeof( SECURITY_ATTRIBUTES );
		attr.lpSecurityDescriptor = &sd;
		attr.bInheritHandle       = TRUE;

		hEvent = CreateEvent( &attr, false, false, lpcszSignalName );

		if( !hEvent || ( INVALID_HANDLE_VALUE == hEvent ) )
		{
			hEvent = OpenEvent( EVENT_ALL_ACCESS, false, lpcszSignalName );
		}

		if( !hEvent )
		{
			hEvent = INVALID_HANDLE_VALUE;
		}
	}
	return hEvent;
}
