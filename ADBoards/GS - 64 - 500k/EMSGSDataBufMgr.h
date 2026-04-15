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

#ifndef __GS_DATA_BUFF_MGR_H__
#define __GS_DATA_BUFF_MGR_H__


#include "emsthread.h"
#include "criticalsection.h"
#include "GSRawBuffer.h"
#include "pointerlist.h"


class CEMSGSDataBufMgr : public CEMSThread
{
	public:
		CEMSGSDataBufMgr();
		CEMSGSDataBufMgr( const CEMSGSDataBufMgr& x );
		virtual ~CEMSGSDataBufMgr();

		void Start();

		void Stop();

		void Reset();

		void LockBuffer( BOOL bWait );

		void UnlockBuffer( );

		void SetMainBuffEvent( HANDLE hEvent ) {m_hEvent = hEvent;};

		void Initialize( ULONG ulBuffSize, ULONG ulCntBuffObjects );

		void AddBuffData( const unsigned char* aData, ULONG ulSize );

		void SetSharedBuffEvent( HANDLE hSharedBuff ) { m_hSharedBuff = hSharedBuff;};

		void SetSharedBuff( unsigned char* aData ) {m_aSharedBuff = aData;}
		
		void SetMainBuff( unsigned char* aData ) {m_aMainBuff = aData;}


	protected:
		virtual void run();

	private:
		void _Initialize();
		void _FillOutputBuffer();

		unsigned long _ReduceBuffer( unsigned long *pInput, unsigned long length);

	private:
		bool        m_bRunning;
		bool        m_bInitialized;
		bool        m_bOverlapOn;

		ULONG       m_ulBuffSize;
		ULONG       m_ulCntBuffObjects;

		unsigned char*     m_aMainBuff;
		unsigned char*     m_aSharedBuff;

		HANDLE			   m_hEvent;
		HANDLE			   m_hSharedBuff;


		CEMSCriticalSection		m_oCS;
		CEMSCriticalSection		m_oCSMainBuff;

		CEMSPointerList<CEMSRawBuffObj>     m_lstFreeBuffObjs;
		CEMSPointerList<CEMSRawBuffObj>     m_lstUsedBuffObjs;

};

#endif