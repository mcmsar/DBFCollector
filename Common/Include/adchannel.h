/*********************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
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

#ifndef __AD_CHANNEL_H__
#define __AD_CHANNEL_H__

#include "aobjbase.h"
#include "channelprocessor.h"
#include "pointerqueue.h"
#include "logclient.h"
#include "leostats.h"
#include "emsadboard.h"

class CEMSWaveEx;

//! Manages reading raw data from a single channel of an A/D board and processing of the
//! data to produce a .wav output.
class CEMSADChannel : public CApiObjBase
{
	public:
		CEMSADChannel();
		CEMSADChannel( const CEMSADChannel& x );
		~CEMSADChannel();

		void InitProcessor( const wchar_t* cwszConfigFile ) { m_oChannelProcessor.Init( cwszConfigFile ); }

		void SetBufferLen( const ULONG culBufferLen );

		void SetLutID( const ULONG culLutID ) { m_ulLutID = culLutID; }

		void SetSatID( const ULONG culSatID ) { m_ulSatID = culSatID; }

		ULONG GetSatID() const { return m_ulSatID; }

		void SetAntennaID( const ULONG culAntID ) { m_ulAntennaID = culAntID; }

		ULONG GetAntennaID() const { return m_ulAntennaID; }

		void SetADBoardProperties( const DWORD cdwBufferSize, const DWORD cdwSampleSize, const DWORD cdwSampleRate );

		void SetProcessFlags( const ULONG culFlags );

		void Start( );

		void Stop();

		void SetSource( const int ciADBoardNo, const int ciChannelNo, LPEMSADBOARD pADBoard );

		ULONG GetADBoardID() const { return m_iADBoardNo; }

		ULONG GetADChannelID() const { return m_iChannelNo; }

		HANDLE GetDataReadyHandle( const ULONG culBoardID );

		//! Returns true if a buffer was ready and processed.
		bool ProcessBuffer();

		CEMSWaveEx* GetNextWave();

		EMSCOLLECTORINFO GetStatusInfo() const { return m_statusInfo; }

		bool IsRunning() const { return m_bIsRunning; }

	private:
		void _SaveStats( const TDataExport* cpData );
		void _AllocateBuffer( const ULONG culLen );
		void _ReleaseBuffer();
		void _ResetCounters();
		CEMSWaveEx* _GenerateWave(	const EMSTIME ctimeBuffer, const ULONG culSampleRate, 
									const bool cbGoodMarkerBit,	const float cfAGCMean, 
									const float cfAGCRMS, const ULONG culSize, const BYTE* cpData );
		void _ReleaseBoard();

	private:
		LPEMSADBOARD					m_pBoard;
		USHORT*							m_ausBuffer;
		ULONG							m_ulBufferLen;
		ULONG							m_ulDmaOffset;
		bool							m_bIsRunning;
		int								m_iChannelNo;
		int								m_iADBoardNo;
		CEMSChannelProcessor			m_oChannelProcessor;
		CEMSPointerQueue<CEMSWaveEx>	m_oqueueWave;
		CEMSLogClient					m_oLogger;
		ULONG							m_ulLutID;
		ULONG							m_ulSatID;
		ULONG							m_ulAntennaID;
		ULONG							m_ulProcessFlags;
		EMSCOLLECTORINFO				m_statusInfo;
		INT64							m_i64Dropouts;
		INT64							m_i64LastBlockCount;
		DWORD							m_dwADBoardBufferSize;
		DWORD							m_dwADBoardSampleSize;
		DWORD							m_dwADBoardSampleRate;
		HANDLE							m_hBoardEvent;
		std::wstring					m_owszBoardEventName;
		TDataExport*					m_pData;
};

#endif