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

#ifndef __GS_DATA_COL_H__
#define __GS_DATA_COL_H__

#include <windows.h>
#include <winbase.h>
#include "tools.h"
#include "18AI32SSeintface.h"
//#include "66-AI64SSCintface.h"
#include "emsthread.h"
#include "criticalsection.h"

class CEMSGSDataCollection : public CEMSThread
{
	public:
		CEMSGSDataCollection();
		CEMSGSDataCollection( const CEMSGSDataCollection& x );
		virtual ~CEMSGSDataCollection();

		void Start();
		
		void Stop();

		void Reset();

		void SetSampleConfig(DWORD dwSampleSize, DWORD dwSampleRate)
		{ m_dwSampleRate = dwSampleRate; m_dwSampleSize = dwSampleSize; }

		void SetMainBuffEvent( HANDLE hMainBuff ) { m_hMainBuff = hMainBuff;};

		void SetMainBuff( unsigned char* aData ) { m_aMainBuff = aData;}

		void SetSharedBuffEvent( HANDLE hSharedBuff ) { m_hSharedBuff = hSharedBuff;};

		void SetSharedBuff( unsigned char* aData ) { m_aSharedBuff = aData;}


	protected:
		virtual void run();
		void  _Set_vRange(double range, unsigned unipolar);

	private:
		void _Initialize();

	private:
		bool        m_bRunning;
		bool        m_bInitialized;
		int         m_iNumChan;
		DWORD		m_dwSampleRate;
		DWORD		m_dwSampleSize;
		DWORD		m_dwMainBuffSize;

		unsigned char*     m_aMainBuff;
		unsigned char*     m_aSharedBuff;
		unsigned long      m_blk1_allocated;
		unsigned long      m_blk2_allocated;

		HANDLE			   m_hMainBuff;
		HANDLE			   m_hSharedBuff;
		HANDLE			   m_hGSEvent;
		GS_NOTIFY_OBJECT   m_GSEvent;


		GS_DMA_DESCRIPTOR  m_DmaSetup;
		GS_PHYSICAL_MEM    m_Block1;
		GS_PHYSICAL_MEM    m_Block2;
		GS_NOTIFY_OBJECT event;
		CEMSCriticalSection		m_oCS;
};

#endif