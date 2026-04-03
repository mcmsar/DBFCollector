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

#ifndef __COLLECTION_OBJECT_H__
#define __COLLECTION_OBJECT_H__


#include "emsthread.h"
#include "criticalsection.h"
#include "GSRawBuffer.h"
#include "pointerlist.h"
#include "DataProcessor.h"
#include "emsDBFDataMgr.h"

#define INITGUID
#include <initguid.h>
#include "emsadboard.h"
//snl
//#include "pointerqueue.h"

class CEMSCollectionObject : public CEMSThread
{
	public:
		CEMSCollectionObject();
		CEMSCollectionObject( const CEMSCollectionObject& x );
		virtual ~CEMSCollectionObject();

		void Start();
		void Stop();

		void Reset();

		void LockBuffer( BOOL bWait );

		void UnlockBuffer( );

		void SetEventHandle( HANDLE hEvent ) {m_hEvent = hEvent;};

		bool Initialize( ULONG ulBuffSize, ULONG ulCntBuffObjects );

		bool IsRunning() {return m_bRunning; }

	protected:
		virtual void run();

	private:
		void _Initialize();
		void _FillOutputBuffer();
		HANDLE _CreateEvent( LPCTSTR lpcszSignalName );

		void _ProcessBuffData();

		void _SetNextDP();

	private:
		bool        m_bRunning;
		bool        m_bInitialized;

		ULONG       m_ulBuffSize;
		ULONG       m_ulCntBuffObjects;

		EMSTIME     m_LastBuffTime;

		unsigned char*     m_aMainBuff;
		unsigned char*     m_aSharedBuff;

		HANDLE			   m_hEvent;
		HANDLE			   m_hSharedBuff;

		CEMSDBFDataMgr	   m_oDBFpass;

		IEMSADBoard*	   m_pADBoard;
		CEMSDataProcessor* m_pDataProcessor;
		CEMSDataProcessor* m_pDataProcessor1;
		CEMSDataProcessor* m_pDataProcessor2;
		CEMSDataProcessor* m_pNextDataProcessor;


		CEMSCriticalSection		m_oCS;
		CEMSCriticalSection		m_oCSMainBuff;

		CEMSPointerList<CEMSRawBuffObj>     m_lstFreeBuffObjs;	//available empty buff - static
		CEMSPointerList<CEMSRawBuffObj>     m_lstUsedBuffObjs; //queued in use buff - static
		//snl
		CEMSDataProcessor*	GetNextProcessor()
		{
			return m_qDataProcessor.GetNext();
		}

		void	GetFirstProcessor()
		{
			m_qDataProcessor.MoveFirst();
			//return m_qDataProcessor.GetNext();
		}
private:
	//CEMSPointerQueue<CEMSDataProcessor>	m_qDataProcessor;
	CEMSPointerList<CEMSDataProcessor>	m_qDataProcessor;
	CEMSQueue<DBFTrackingData >			m_qDBFBeamVectors;
	//CDBFBeamVectorCalculator	*m_pDBFBeamVectorCalculator;


};

#endif