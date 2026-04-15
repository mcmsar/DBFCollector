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

#include "EMSGSDataBufMgr.h"
#include "emserror.h"

#include "emsclock.h"				// CEMSSystemClock

//#define BUFF_SIZE 38400000
#define BUFF_SIZE 64000000
#define BUFF_SIZE_PLUS_TIME 64000008

const long cMainTimeIndex = BUFF_SIZE * 2 - 1;

const CEMSSystemClock c_sysClock;

CEMSGSDataBufMgr::CEMSGSDataBufMgr() : m_bRunning(false), m_bInitialized(false),m_bOverlapOn(true),
                                       m_hEvent(NULL), m_ulCntBuffObjects(10),
									   m_ulBuffSize(BUFF_SIZE), m_aMainBuff(NULL)
{
}

CEMSGSDataBufMgr::CEMSGSDataBufMgr( const CEMSGSDataBufMgr& x )
{
}

CEMSGSDataBufMgr::~CEMSGSDataBufMgr()
{
	Reset();
}

void 
CEMSGSDataBufMgr::Reset()
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

void
CEMSGSDataBufMgr::Initialize( ULONG ulBuffSize, ULONG ulCntBuffObjects )
{
	//m_ulCntBuffObjects = ulCntBuffObjects;
	m_ulBuffSize = ulBuffSize;
	_Initialize();
}


void
CEMSGSDataBufMgr::_Initialize()
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
	}
}

void
CEMSGSDataBufMgr::AddBuffData( const unsigned char* aData, ULONG ulSize )
{
	EMSTIME tmBuff = c_sysClock.GetTime();
	m_oCS.Enter();

	CEMSRawBuffObj* pRawBuff = NULL;
	try
	{
//		if( m_lstFreeBuffObjs.Count() == 0 )
		{
//			_FillOutputBuffer();
		}

		if( m_lstFreeBuffObjs.Count() > 0 )
		{
			m_lstFreeBuffObjs.MoveFirst();
			pRawBuff = m_lstFreeBuffObjs.GetNext();
			if( pRawBuff )
			{
				m_lstFreeBuffObjs.RemoveCurrent();
				pRawBuff->SetBuffData( aData, ulSize );
				pRawBuff->SetBuffTime(tmBuff);
				m_lstUsedBuffObjs.Add( pRawBuff );
				pRawBuff->Release();

				if( m_lstUsedBuffObjs.Count() > 4 )
				{
					_FillOutputBuffer();
				}
			}
		}
		else
		{
			// error
			printf("\nCEMSGSDataBufMgr::AddBuffData() --> Need more buffer objects!!!!");
			OutputDebugString("\nCEMSGSDataBufMgr::AddBuffData() --> Need more buffer objects!!!!");

			_FillOutputBuffer();
		}

		_FillOutputBuffer();
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
CEMSGSDataBufMgr::_FillOutputBuffer()
{
	static int ms_iSeqNum = 1;
	m_oCS.Enter();

	CEMSRawBuffObj* pRawBuff = NULL;
	try
	{
		while( m_lstUsedBuffObjs.Count() >= 2 ) //each 2 buffers is one second
		{
			LockBuffer(true);
			EMSTIME tmBuff;
			tmBuff.intTime = 0L;
			ULONG ulHalfBuff = (ULONG)(m_ulBuffSize/2);
//			ULONG ulHalfBuff = 32000000;
			m_lstUsedBuffObjs.MoveFirst();
			pRawBuff = m_lstUsedBuffObjs.GetNext();
			if( pRawBuff )
			{
				m_lstUsedBuffObjs.RemoveCurrent();
				m_lstFreeBuffObjs.Add( pRawBuff );

				pRawBuff->GetBuffData(m_aMainBuff, BUFF_SIZE );

				pRawBuff->Release();
				pRawBuff = NULL;
			}

			// the second half
			pRawBuff = m_lstUsedBuffObjs.GetNext();
			if( pRawBuff )
			{
				if(!m_bOverlapOn)
				{
					m_lstUsedBuffObjs.RemoveCurrent();
					m_lstFreeBuffObjs.Add( pRawBuff );
				}

				// don't remove.
				pRawBuff->GetBuffData( (m_aMainBuff + BUFF_SIZE), BUFF_SIZE );
				tmBuff = pRawBuff->GetBuffTime();
				pRawBuff->Release();
				pRawBuff = NULL;
			}

			INT64* pTM = (INT64*)&(m_aMainBuff[cMainTimeIndex]);
			(*pTM) = tmBuff.intTime;

//			printf("\n one second data, number: %d, Objec count = %d", ms_iSeqNum++, m_lstUsedBuffObjs.Count() ); 
			UnlockBuffer();

			SetEvent(m_hEvent);
		}

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
CEMSGSDataBufMgr::Start()
{
	if(!m_bInitialized)
	{
		_Initialize();
	}
	start();
}

unsigned long 
CEMSGSDataBufMgr::_ReduceBuffer( unsigned long *pInput, unsigned long length)
{
	unsigned long j = 0;
	unsigned long i = 0;
	unsigned long k = 0;
	unsigned char *pBuffer = (unsigned char*)pInput;
//	U16 *pBuffer = (U16*)pInput;
	for( i=0; i<4*length; i=i+4 )
	{
		k = (i/4)%32;
//		if( (k < 16 || k == 23) && (k!=7) )
		if( k < 16  )
		{
			pBuffer[j++] = pBuffer[i];
			pBuffer[j++] = pBuffer[i+1];
		}
	}
	return j;
};


void
CEMSGSDataBufMgr::run()
{
	if( m_bInitialized && m_aMainBuff )
	{
		EMS_RESULT hr = EMS_OK;
		m_bRunning = true;

		HANDLE hEvent[2];

		hEvent[0] = m_hStopEvent;
		hEvent[1] = m_hSharedBuff; //filler event

		DWORD dwTimeout = 100;
		DWORD dwEventCount = 2;
		ULONG ulBuffSize = BUFF_SIZE;

		char fName[256];
		EMSTIME timeBuffer;
		const CEMSSystemClock c_sysClock;
		FILE *halfSecFile = 0;


		unsigned char*   aInBuff = new unsigned char[BUFF_SIZE];

		if( !aInBuff )
		{
			// error.
			return;
		}

		/*for(int i = 0; i <= 2; i++){
			memmove(aInBuff, (void*)m_aSharedBuff, BUFF_SIZE);
			AddBuffData(aInBuff, ulBuffSize );
		}*/

		while( m_bRunning )
		{
			
			try
			{
				hr = WaitForMultipleObjects( dwEventCount, hEvent, FALSE, dwTimeout ); // Wait for the interrupt
				switch(hr)	
				 {						
					case WAIT_OBJECT_0:	
						{
							//stop
							m_bRunning = false;
						}
						break;
					case WAIT_OBJECT_0 + 1:
						{
							memmove(aInBuff, (void*)m_aSharedBuff, BUFF_SIZE);
							//ResetEvent(m_hSharedBuff);
//							printf("\n_ReduceBuffer()");

//							ulBuffSize = _ReduceBuffer( (unsigned long*)aInBuff, (unsigned long)(BUFF_SIZE/4));

							AddBuffData(aInBuff, ulBuffSize );
							/*{
								timeBuffer = c_sysClock.GetTime();
								memset(fName,0, sizeof(fName));
								sprintf(fName,"C:\\WaveOutput\\DBF_%I64d.bin", timeBuffer.intTime);
								halfSecFile = fopen(fName,"w+b");
								if( halfSecFile != NULL )
								{
									ULONG ulBytesWritten = fwrite(aInBuff, 1, ulBuffSize, halfSecFile);
									fclose( halfSecFile );
								}



							}*/
						}
						break;
					default:
						{
							_FillOutputBuffer();
						}
						break;
				}
			}
			catch( ... )
			{
				// a error occured, log it and stop the thread.
				m_bRunning = false;
			}
		}

		delete[] aInBuff;
		aInBuff = NULL;

		m_bRunning = false;
	}
}

void
CEMSGSDataBufMgr::LockBuffer( BOOL bWait )
{
	m_oCSMainBuff.Enter();
}


void
CEMSGSDataBufMgr::UnlockBuffer( )
{
	m_oCSMainBuff.Leave();
}


void 
CEMSGSDataBufMgr::Stop()
{
//	stop();
	m_bRunning = false;
}
