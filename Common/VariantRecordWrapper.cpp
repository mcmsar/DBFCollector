/********************************************************************
*
*		Copyright (c) 2004 by EMS Technologies, Inc.,
*							All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#include "variantrecordwrapper.h"
#include "convutility.h"
#include "emsexcpt.h"

bool
_Is_EMSVARIANTRECORD_Type( const EMSRECORDTYPE ceType ) 
{
	bool bRet = false;
	switch ( ceType )
	{
		case EMSRT_ANTENNA:
		case EMSRT_CALIBCBC_STATS:
		case EMSRT_COLLECTOR:
		case EMSRT_COMB406_STATS:
		case EMSRT_COMMS_STATS:
		case EMSRT_GEO_CALIB406_STATS:
		case EMSRT_GEO_STATS:
		case EMSRT_LEO_CALIB406_STATS:
		case EMSRT_LOCATE_STATS:
		case EMSRT_ORBIT_STATS:
		case EMSRT_PASS_STATS:
		case EMSRT_SARR_CALIB_STATS:
		case EMSRT_SARP_CALIB_STATS:
		case EMSRT_SENSOR:
		case EMSRT_WIDEBAND_STATS:
		case EMSRT_CALIB406:
		case EMSRT_CALIBCBC:
		case EMSRT_CBC:
		case EMSRT_COMB406:
		case EMSRT_CONFIG:
		case EMSRT_LOCATE:
		case EMSRT_LOG:
		case EMSRT_ORBIT:
		case EMSRT_RESIDUAL:
		case EMSRT_SARP_CALIB:
		case EMSRT_SARP:
		case EMSRT_SARR_CALIB:
		case EMSRT_SARR:
		case EMSRT_SAT_TRACK:
		case EMSRT_SPECTRUM:
		case EMSRT_MANOEUVRE:
		case EMSRT_AUDIO:
		case EMSRT_STAT_SUMMARY:
		case EMSRT_LUT_STATUS:
			bRet = true;
			break;
		default:
			bRet = false;
			break;
	}
	return bRet;
}


bool
_Is_EMSVARIANTRECORD2_Type( const EMSRECORDTYPE ceType )
{
	bool bRet = false;
	switch ( ceType )
	{
		case EMSRT_SARR_EXT:
		case EMSRT_CALIB406_EXT:
		case EMSRT_CALIB406_2:
			bRet = true;
			break;
		default:
			bRet = false;
			break;
	}
	return bRet;
}

bool
_Is_EMSVARIANTRECORD3_Type( const EMSRECORDTYPE ceType )
{
	bool bRet = false;
	switch ( ceType )
	{
		case EMSRT_ABL_DATA:
		case EMSRT_HEALTH_STATUS:
		case EMSRT_HEALTH_DETECTIONS:
		case EMSRT_BEACON_ADVISORY:
			bRet = true;
			break;
		default:
			bRet = false;
			break;
	}
	return bRet;
}


CEMSVariantRecord::CEMSVariantRecord()
{
	memset( &m_record, 0, sizeof(EMSVARIANTRECORD) );
}

CEMSVariantRecord::CEMSVariantRecord( const EMSVARIANTRECORD& record )
{
	memcpy( &m_record, &record, sizeof(EMSVARIANTRECORD) );
}

CEMSVariantRecord::CEMSVariantRecord( const CEMSVariantRecord& x )
{
	memcpy( &m_record, &x.m_record, sizeof(EMSVARIANTRECORD) );
}

CEMSVariantRecord::~CEMSVariantRecord()
{
}

EMSTIME
CEMSVariantRecord::GetRecordTimestamp()
{
	EMSTIME timeRet;
	timeRet.intTime = 0;

	switch( m_record.eType )
	{
		case EMSRT_ANTENNA:
		case EMSRT_CALIBCBC_STATS:
		case EMSRT_COLLECTOR:
		case EMSRT_COMB406_STATS:
		case EMSRT_COMMS_STATS:
		case EMSRT_GEO_CALIB406_STATS:
		case EMSRT_GEO_STATS:
		case EMSRT_LEO_CALIB406_STATS:
		case EMSRT_LOCATE_STATS:
		case EMSRT_ORBIT_STATS:
		case EMSRT_PASS_STATS:
		case EMSRT_SARR_CALIB_STATS:
		case EMSRT_SARP_CALIB_STATS:
		case EMSRT_SENSOR:
		case EMSRT_WIDEBAND_STATS:
		case EMSRT_LUT_STATUS:
			timeRet = m_record.data.status.timeTag;
			break;
		case EMSRT_CALIB406:
			timeRet = m_record.data.calib406.hdr.id.time;
			break;
		case EMSRT_CALIBCBC:
			timeRet = m_record.data.calibCBC.hdr.id.time;
			break;
		case EMSRT_CBC:
			timeRet = m_record.data.rawCBC.hdr.id.time;
			break;
		case EMSRT_COMB406:
			timeRet = m_record.data.combine406.hdr.id.time;
			break;
		case EMSRT_CONFIG:
			timeRet = m_record.data.config.rec.timeModified;
			break;
		case EMSRT_LOCATE:
			timeRet = m_record.data.locate.time;
			break;
		case EMSRT_LOG:
			timeRet = m_record.data.log.time;
			break;
		case EMSRT_ORBIT:
			timeRet = m_record.data.tle.time;
			break;
		case EMSRT_RESIDUAL:
			timeRet = m_record.data.residual.hdr.id.time;
			break;
		case EMSRT_SARP_CALIB:
			timeRet = m_record.data.sarpcalib.hdr.time;
			break;
		case EMSRT_SARP:
			timeRet = m_record.data.sarp.hdr.id.time;
			break;
		case EMSRT_SARR_CALIB:
			timeRet = m_record.data.sarrcalib.hdr.time;
			break;
		case EMSRT_SARR:
			timeRet = m_record.data.sarr.hdr.id.time;
			break;
		case EMSRT_SAT_TRACK:
			timeRet = m_record.data.satTrack.timeSched;
			break;
		case EMSRT_SPECTRUM:
			timeRet = m_record.data.spectrum.id.time;
			break;
		case EMSRT_MANOEUVRE:
			timeRet = m_record.data.manoeuvre.startTime;
			break;
		case EMSRT_AUDIO:
			timeRet = m_record.data.audio.riffHdr.audioHdr.dataID.id.time;
			break;
		case EMSRT_STAT_SUMMARY:
			timeRet = m_record.data.statsummary.time;
			break;
	}

	return timeRet;
}

void 
CEMSVariantRecord::GetRecordData( unsigned long& ulBufSize, unsigned char*& abyBuf )
{
	ulBufSize = 0;
	abyBuf = 0;

	switch( m_record.eType )
	{
		case EMSRT_ANTENNA:
		case EMSRT_CALIBCBC_STATS:
		case EMSRT_COLLECTOR:
		case EMSRT_COMB406_STATS:
		case EMSRT_COMMS_STATS:
		case EMSRT_GEO_CALIB406_STATS:
		case EMSRT_GEO_STATS:
		case EMSRT_LEO_CALIB406_STATS:
		case EMSRT_LOCATE_STATS:
		case EMSRT_ORBIT_STATS:
		case EMSRT_PASS_STATS:
		case EMSRT_SARR_CALIB_STATS:
		case EMSRT_SARP_CALIB_STATS:
		case EMSRT_SENSOR:
		case EMSRT_WIDEBAND_STATS:
		case EMSRT_LUT_STATUS:
			_AllocBuffer( sizeof(EMSLEOSTATUSUPDATE), ulBufSize, abyBuf );
			memcpy( abyBuf, &m_record.data.status, ulBufSize );
			break;
		case EMSRT_CALIB406:
			_AllocBuffer( sizeof(EMSCALIB406DATA), ulBufSize, abyBuf );
			memcpy( abyBuf, &m_record.data.calib406, ulBufSize );
			break;
		case EMSRT_CALIBCBC:
			_AllocBuffer( sizeof(EMSCBCOUTPUTDATA), ulBufSize, abyBuf );
			memcpy( abyBuf, &m_record.data.calibCBC, ulBufSize );
			break;
		case EMSRT_CBC:
			_AllocBuffer( sizeof(EMSCBCDATA), ulBufSize, abyBuf );
			memcpy( abyBuf, &m_record.data.rawCBC, ulBufSize );
			break;
		case EMSRT_COMB406:
			_AllocBuffer( sizeof(EMSCOMBINE406DATA), ulBufSize, abyBuf );
			memcpy( abyBuf, &m_record.data.combine406, ulBufSize );
			break;
		case EMSRT_CONFIG:
			_AllocBuffer( sizeof(EMSCONFIGPACKET), ulBufSize, abyBuf );
			memcpy( abyBuf, &m_record.data.config, ulBufSize );
			break;
		case EMSRT_LOCATE:
			_AllocBuffer( sizeof(EMSLOCATE), ulBufSize, abyBuf );
			memcpy( abyBuf, &m_record.data.locate, ulBufSize );
			break;
		case EMSRT_LOG:
			_AllocBuffer( sizeof(EMSLOGDATA), ulBufSize, abyBuf );
			memcpy( abyBuf, &m_record.data.log, ulBufSize );
			break;
		case EMSRT_ORBIT:
			_AllocBuffer( sizeof(EMSTLERECORD), ulBufSize, abyBuf );
			memcpy( abyBuf, &m_record.data.tle, ulBufSize );
			break;
		case EMSRT_RESIDUAL:
			_AllocBuffer( sizeof(EMSRESIDUALDATA), ulBufSize, abyBuf );
			memcpy( abyBuf, &m_record.data.residual, ulBufSize );
			break;
		case EMSRT_SARP_CALIB:
			_AllocBuffer( sizeof(EMSSARPCALIBDATA), ulBufSize, abyBuf );
			memcpy( abyBuf, &m_record.data.sarpcalib, ulBufSize );
			break;
		case EMSRT_SARP:
			_AllocBuffer( sizeof(EMSSARPDATA), ulBufSize, abyBuf );
			memcpy( abyBuf, &m_record.data.sarp, ulBufSize );
			break;
		case EMSRT_SARR_CALIB:
			_AllocBuffer( sizeof(EMSSARRCALIBDATA), ulBufSize, abyBuf );
			memcpy( abyBuf, &m_record.data.sarrcalib, ulBufSize );
			break;
		case EMSRT_SARR:
			_AllocBuffer( sizeof(EMSSARRDATA), ulBufSize, abyBuf );
			memcpy( abyBuf, &m_record.data.sarr, ulBufSize );
			break;
		case EMSRT_SAT_TRACK:
			_AllocBuffer( sizeof(EMSSATTRACKRECORD), ulBufSize, abyBuf );
			memcpy( abyBuf, &m_record.data.satTrack, ulBufSize );
			break;
		case EMSRT_SPECTRUM:
			_AllocBuffer( sizeof(EMSSPECTRUM), ulBufSize, abyBuf );
			memcpy( abyBuf, &m_record.data.spectrum, ulBufSize );
			break;
		case EMSRT_MANOEUVRE:
			_AllocBuffer( sizeof(EMSMANOEUVREDATA), ulBufSize, abyBuf );
			memcpy( abyBuf, &m_record.data.manoeuvre, ulBufSize );
			break;
		case EMSRT_AUDIO:
			_AllocBuffer( sizeof(EMSAUDIODATARECORD_RIFF), ulBufSize, abyBuf );
			memcpy( abyBuf, &m_record.data.audio, ulBufSize );
			break;
		case EMSRT_STAT_SUMMARY:
			_AllocBuffer( sizeof(EMSALARMDATAEX), ulBufSize, abyBuf );
			memcpy( abyBuf, &m_record.data.statsummary, ulBufSize );
			break;
	}
}

unsigned long 
CEMSVariantRecord::GetRecordSize()
{
	unsigned long ulSize = 0;

	switch( m_record.eType )
	{
		case EMSRT_ANTENNA:
		case EMSRT_CALIBCBC_STATS:
		case EMSRT_COLLECTOR:
		case EMSRT_COMB406_STATS:
		case EMSRT_COMMS_STATS:
		case EMSRT_GEO_CALIB406_STATS:
		case EMSRT_GEO_STATS:
		case EMSRT_LEO_CALIB406_STATS:
		case EMSRT_LOCATE_STATS:
		case EMSRT_ORBIT_STATS:
		case EMSRT_PASS_STATS:
		case EMSRT_SARR_CALIB_STATS:
		case EMSRT_SARP_CALIB_STATS:
		case EMSRT_SENSOR:
		case EMSRT_WIDEBAND_STATS:
		case EMSRT_LUT_STATUS:
			ulSize = sizeof(EMSLEOSTATUSUPDATE);
			break;
		case EMSRT_CALIB406:
			ulSize = sizeof(EMSCALIB406DATA);
			break;
		case EMSRT_CALIBCBC:
			ulSize = sizeof(EMSCBCOUTPUTDATA);
			break;
		case EMSRT_CBC:
			ulSize = sizeof(EMSCBCDATA);
			break;
		case EMSRT_COMB406:
			ulSize = sizeof(EMSCOMBINE406DATA );
			break;
		case EMSRT_CONFIG:
			ulSize = sizeof(EMSCONFIGPACKET);
			break;
		case EMSRT_LOCATE:
			ulSize = sizeof(EMSLOCATE);
			break;
		case EMSRT_LOG:
			ulSize = sizeof(EMSLOGDATA);
			break;
		case EMSRT_ORBIT:
			ulSize = sizeof(EMSTLERECORD);
			break;
		case EMSRT_RESIDUAL:
			ulSize = sizeof(EMSRESIDUALDATA);
			break;
		case EMSRT_SARP_CALIB:
			ulSize = sizeof(EMSSARPCALIBDATA);
			break;
		case EMSRT_SARP:
			ulSize = sizeof(EMSSARPDATA);
			break;
		case EMSRT_SARR_CALIB:
			ulSize = sizeof(EMSSARRCALIBDATA);
			break;
		case EMSRT_SARR:
			ulSize = sizeof(EMSSARRDATA);
			break;
		case EMSRT_SAT_TRACK:
			ulSize = sizeof(EMSSATTRACKRECORD);
			break;
		case EMSRT_SPECTRUM:
			ulSize = sizeof(EMSSPECTRUM);
			break;
		case EMSRT_MANOEUVRE:
			ulSize = sizeof(EMSMANOEUVREDATA);
			break;
		case EMSRT_AUDIO:
			ulSize = sizeof(EMSAUDIODATARECORD_RIFF);
			break;
		case EMSRT_STAT_SUMMARY:
			ulSize = sizeof(EMSALARMDATAEX);
			break;
	}

	return ulSize;
}

void 
CEMSVariantRecord::_AllocBuffer( const unsigned long culSizeToAllocate, unsigned long& ulAllocated, 
								unsigned char*& abyBuffer )
{
	abyBuffer = 0;
	ulAllocated = 0;

	if( culSizeToAllocate > 0 )
	{
		abyBuffer = new unsigned char[ culSizeToAllocate ];

		if( !abyBuffer )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( abyBuffer, 0, culSizeToAllocate*sizeof(unsigned char) );

		ulAllocated = culSizeToAllocate;

	}
}

void 
CEMSVariantRecord::Convert( const ULONG culRecs, const EMSVARIANTRECORD* caRecs, 
								ULONG* pulRecs, EMSVARIANTRECORD2** paRecs )
{
	if( culRecs > 0 &&
		caRecs )
	{
		try
		{
#ifdef WIN32
			*paRecs = reinterpret_cast<EMSVARIANTRECORD2*>( CoTaskMemAlloc( culRecs*sizeof(EMSVARIANTRECORD2) ) );
#else
			*paRecs = new EMSVARIANTRECORD2[ culRecs ];
#endif

			if( !*paRecs )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			memset( *paRecs, 0, culRecs*sizeof(EMSVARIANTRECORD2) );

			for( ULONG l = 0; l < culRecs; l++ )
			{
				(*paRecs)[l].eType = caRecs[l].eType;

				switch( caRecs[l].eType )
				{
					case EMSRT_ANTENNA:  
					case EMSRT_CALIBCBC_STATS:
					case EMSRT_COLLECTOR:
					case EMSRT_COMB406_STATS:
					case EMSRT_COMMS_STATS:
					case EMSRT_GEO_CALIB406_STATS:
					case EMSRT_GEO_STATS:
					case EMSRT_LEO_CALIB406_STATS:
					case EMSRT_LOCATE_STATS:
					case EMSRT_ORBIT_STATS:
					case EMSRT_PASS_STATS:
					case EMSRT_SARR_CALIB_STATS:
					case EMSRT_SARP_CALIB_STATS:
					case EMSRT_SARP_CALIB_STATS_124:
					case EMSRT_SENSOR:
					case EMSRT_WIDEBAND_STATS:
					case EMSRT_LUT_STATUS:
						(*paRecs)[l].data.status = caRecs[l].data.status;
						break;
					case EMSRT_CALIB406:
						(*paRecs)[l].data.calib406 = caRecs[l].data.calib406;
						break;
					case EMSRT_CALIBCBC:
						(*paRecs)[l].data.calibCBC = caRecs[l].data.calibCBC;
						break;
					case EMSRT_CBC:
						(*paRecs)[l].data.rawCBC = caRecs[l].data.rawCBC;
						break;
					case EMSRT_COMB406:
						(*paRecs)[l].data.combine406 = caRecs[l].data.combine406;
						break;
					case EMSRT_CONFIG:
						(*paRecs)[l].data.config = caRecs[l].data.config;
						break;
					case EMSRT_LOCATE:
					case  EMSRT_LOCATE_124:
						(*paRecs)[l].data.locate = caRecs[l].data.locate;
						break;
					case EMSRT_LOG:
						(*paRecs)[l].data.log = caRecs[l].data.log;
						break;
					case EMSRT_ORBIT:
						(*paRecs)[l].data.tle = caRecs[l].data.tle;
						break;
					case EMSRT_RESIDUAL:
						(*paRecs)[l].data.residual = caRecs[l].data.residual;
						break;
					case EMSRT_SARP_CALIB:
					case EMSRT_SARP_CALIB_124:
						(*paRecs)[l].data.sarpcalib = caRecs[l].data.sarpcalib;
						break;
					case EMSRT_SARP:
						(*paRecs)[l].data.sarp = caRecs[l].data.sarp;
						break;
					case EMSRT_SARR_CALIB:
						(*paRecs)[l].data.sarrcalib = caRecs[l].data.sarrcalib;
						break;
					case EMSRT_SARR:
					case EMSRT_SARR_124:
						(*paRecs)[l].data.sarr = caRecs[l].data.sarr;
						break;
					case EMSRT_SAT_TRACK:
						(*paRecs)[l].data.satTrack = caRecs[l].data.satTrack;
						break;
					case EMSRT_SPECTRUM:
						(*paRecs)[l].data.spectrum = caRecs[l].data.spectrum;
						break;
					case EMSRT_MANOEUVRE:
						(*paRecs)[l].data.manoeuvre = caRecs[l].data.manoeuvre;
						break;
					case EMSRT_AUDIO:
						(*paRecs)[l].data.audio = caRecs[l].data.audio;
						break;
					case EMSRT_STAT_SUMMARY:
						(*paRecs)[l].data.statsummary = caRecs[l].data.statsummary;
						break;
					default:
						THROW_INVALID_ARG_EXCEPTION();
						break;
				}

				(*pulRecs)++;
			}
		}
		catch( ... )
		{
#ifdef WIN32
			CoTaskMemFree( *paRecs );
#else
			delete[] *paRecs;
#endif
			*paRecs = 0;
			throw;
		}

	}
}

void 
CEMSVariantRecord::Convert( const ULONG culRecs, const EMSVARIANTRECORD2* caRecs, 
								ULONG& rulRecs, EMSVARIANTRECORD*& raRecs)
{
	if( culRecs > 0 &&
		caRecs )
	{
		try
		{
#ifdef WIN32
			raRecs = reinterpret_cast<EMSVARIANTRECORD*>( CoTaskMemAlloc( culRecs*sizeof(EMSVARIANTRECORD) ) );
#else
			raRecs = new EMSVARIANTRECORD[ culRecs ];
#endif

			if( !raRecs )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			memset( raRecs, 0, culRecs*sizeof(EMSVARIANTRECORD) );

			for( ULONG l = 0; l < culRecs; l++ )
			{
				raRecs[l].eType = caRecs[l].eType;

				switch( caRecs[l].eType )
				{
					case EMSRT_ANTENNA:  
					case EMSRT_CALIBCBC_STATS:
					case EMSRT_COLLECTOR:
					case EMSRT_COMB406_STATS:
					case EMSRT_COMMS_STATS:
					case EMSRT_GEO_CALIB406_STATS:
					case EMSRT_GEO_STATS:
					case EMSRT_LEO_CALIB406_STATS:
					case EMSRT_LOCATE_STATS:
					case EMSRT_ORBIT_STATS:
					case EMSRT_PASS_STATS:
					case EMSRT_SARR_CALIB_STATS:
					case EMSRT_SARP_CALIB_STATS:
					case EMSRT_SARP_CALIB_STATS_124:
					case EMSRT_SENSOR:
					case EMSRT_WIDEBAND_STATS:
					case EMSRT_LUT_STATUS:
						raRecs[l].data.status = caRecs[l].data.status;
						break;
					case EMSRT_CALIB406:
						raRecs[l].data.calib406 = caRecs[l].data.calib406;
						break;
					case EMSRT_CALIBCBC:
						raRecs[l].data.calibCBC = caRecs[l].data.calibCBC;
						break;
					case EMSRT_CBC:
						raRecs[l].data.rawCBC = caRecs[l].data.rawCBC;
						break;
					case EMSRT_COMB406:
						raRecs[l].data.combine406 = caRecs[l].data.combine406;
						break;
					case EMSRT_CONFIG:
						raRecs[l].data.config = caRecs[l].data.config;
						break;
					case EMSRT_LOCATE:
					case  EMSRT_LOCATE_124:
						raRecs[l].data.locate = caRecs[l].data.locate;
						break;
					case EMSRT_LOG:
						raRecs[l].data.log = caRecs[l].data.log;
						break;
					case EMSRT_ORBIT:
						raRecs[l].data.tle = caRecs[l].data.tle;
						break;
					case EMSRT_RESIDUAL:
						raRecs[l].data.residual = caRecs[l].data.residual;
						break;
					case EMSRT_SARP_CALIB:
					case EMSRT_SARP_CALIB_124:
						raRecs[l].data.sarpcalib = caRecs[l].data.sarpcalib;
						break;
					case EMSRT_SARP:
						raRecs[l].data.sarp = caRecs[l].data.sarp;
						break;
					case EMSRT_SARR_CALIB:
						raRecs[l].data.sarrcalib = caRecs[l].data.sarrcalib;
						break;
					case EMSRT_SARR:
					case EMSRT_SARR_124:
						raRecs[l].data.sarr = caRecs[l].data.sarr;
						break;
					case EMSRT_SAT_TRACK:
						raRecs[l].data.satTrack = caRecs[l].data.satTrack;
						break;
					case EMSRT_SPECTRUM:
						raRecs[l].data.spectrum = caRecs[l].data.spectrum;
						break;
					case EMSRT_MANOEUVRE:
						raRecs[l].data.manoeuvre = caRecs[l].data.manoeuvre;
						break;
					case EMSRT_AUDIO:
						raRecs[l].data.audio = caRecs[l].data.audio;
						break;
					case EMSRT_STAT_SUMMARY:
						raRecs[l].data.statsummary = caRecs[l].data.statsummary;
						break;
					case EMSRT_SARR_EXT:
						raRecs[l].data.sarr = caRecs[l].data.sarrext.sarrData;
						break;
					case EMSRT_CALIB406_EXT:
						raRecs[l].eType = EMSRT_CALIB406;
						raRecs[l].data.calib406.hdr = caRecs[l].data.calib406ext.calib406.hdr;
						raRecs[l].data.calib406.ulPassID = caRecs[l].data.calib406ext.calib406.ulPassID;
						raRecs[l].data.calib406.i64BeaconID = caRecs[l].data.calib406ext.calib406.i64BeaconID;
						raRecs[l].data.calib406.timeMsg = caRecs[l].data.calib406ext.calib406.timeMsg;
						raRecs[l].data.calib406.i64TimeOffset = caRecs[l].data.calib406ext.calib406.i64TimeOffset;
						raRecs[l].data.calib406.wStatus = caRecs[l].data.calib406ext.calib406.wStatus;
						raRecs[l].data.calib406.wDuplicateMsgCount = caRecs[l].data.calib406ext.calib406.wDuplicateMsgCount;
						raRecs[l].data.calib406.dFrequency = caRecs[l].data.calib406ext.calib406.dFrequency;
						raRecs[l].data.calib406.fFreqOffset = (float) caRecs[l].data.calib406ext.calib406.dFreqOffset;
						raRecs[l].data.calib406.fCarrierPower = (float) caRecs[l].data.calib406ext.calib406.dCarrierPower;
						raRecs[l].data.calib406.wBitErrorField1 = caRecs[l].data.calib406ext.calib406.wBitErrorField1;
						raRecs[l].data.calib406.wBitErrorField2 = caRecs[l].data.calib406ext.calib406.wBitErrorField2;
						raRecs[l].data.calib406.wBitErrorFrameSynch = caRecs[l].data.calib406ext.calib406.wBitErrorFrameSynch;
						memcpy( raRecs[l].data.calib406.cBeaconMsg, 
								caRecs[l].data.calib406ext.calib406.cBeaconMsg, 
								sizeof(caRecs[l].data.calib406ext.calib406.cBeaconMsg) );
						break;
					default:
						THROW_INVALID_ARG_EXCEPTION();
						break;
				}

				rulRecs++;
			}
		}
		catch( ... )
		{
#ifdef WIN32
			CoTaskMemFree( raRecs );
#else
			delete[] raRecs;
#endif
			raRecs = 0;
			throw;
		}

	}
}

wstring
CEMSVariantRecord::GetRecordTypeString( const EMSRECORDTYPE ceType )
{
	wstring wszType;

	switch ( ceType )
	{
	case EMSRT_ANTENNA:
		wszType = L"Antenna";
		break;
	case EMSRT_CALIB406:
		wszType = L"Calib406";
		break;
	case EMSRT_CALIBCBC:
		wszType = L"CalibCBC";
		break;
	case EMSRT_CALIBCBC_STATS:
		wszType = L"CalibCBC Stats";
		break;
	case EMSRT_CBC:
		wszType = L"CBC";
		break;
	case EMSRT_COLLECTOR:
		wszType = L"Collector";
		break;
	case EMSRT_COMB406:
		wszType = L"Comb406";
		break;
	case EMSRT_COMB406_STATS:
		wszType = L"Comb406 Stats";
		break;
	case EMSRT_COMMS_STATS:
		wszType = L"Comms Stats";
		break;
	case EMSRT_CONFIG:
		wszType = L"Config";
		break;
	case EMSRT_GEO_CALIB406_STATS:
		wszType = L"GEO Calib406 Stats";
		break;
	case EMSRT_GEO_STATS:
		wszType = L"Geo Stats";
		break;
	case EMSRT_LEO_CALIB406_STATS:
		wszType = L"LEO Calib406 Stats";
		break;
	case EMSRT_LOCATE:
		wszType = L"Locate";
		break;
	case EMSRT_LOCATE_STATS:
		wszType = L"Locate Stats";
		break;
	case EMSRT_LOG:
		wszType = L"Log";
		break;
	case EMSRT_ORBIT:
		wszType = L"Orbit";
		break;
	case EMSRT_ORBIT_STATS:
		wszType = L"Orbit Stats";
		break;
	case EMSRT_PASS_STATS:
		wszType = L"Pass Stats";
		break;
	case EMSRT_RESIDUAL:
		wszType = L"Residual";
		break;
	case EMSRT_SARP_CALIB:
		wszType = L"SARP Calib";
		break;
	case EMSRT_SARP_CALIB_STATS:
		wszType = L"SARP Calib Stats";
		break;
	case EMSRT_SARP:
		wszType = L"SARP";
		break;
	case EMSRT_SARR_CALIB:
		wszType = L"SARR Calib";
		break;
	case EMSRT_SARR_CALIB_STATS:
		wszType = L"Calib Stats";
		break;
	case EMSRT_SARR:
		wszType = L"SARR";
		break;
	case EMSRT_SAT_TRACK:
		wszType = L"Sat Track";
		break;
	case EMSRT_SENSOR:
		wszType = L"Sensor";
		break;
	case EMSRT_SPECTRUM:
		wszType = L"Spectrum";
		break;
	case EMSRT_STAT_SUMMARY:
		wszType = L"Status Summary";
		break;
	case EMSRT_WIDEBAND_STATS:
		wszType = L"Wideband Stats";
		break;
	case EMSRT_LUT_STATUS:
		wszType = L"Lut State";
		break;
	case EMSRT_AUDIO:
		wszType = L"Audio";
		break;
	case EMSRT_MANOEUVRE:
		wszType = L"Manoeuvre";
		break;
	case EMSRT_SARP_CALIB_124:
		wszType = L"SARP Calib 124";
		break;
	case EMSRT_SARP_CALIB_STATS_124:
		wszType = L"SARP Calib Stats 124";
		break;
	case EMSRT_SARR_124:
		wszType = L"SARR 124";
		break;
	case EMSRT_LOCATE_124:
		wszType = L"Locate 124";
		break;
	case EMSRT_SARR_EXT:
		wszType = L"Extended SARR";
		break;
	case EMSRT_CALIB406_EXT:
		wszType = L"Extended Calib406";
		break;
	case EMSRT_CALIB406_2:
		wszType = L"Calib406-2";
		break;
	case EMSRT_UNKNOWN:
	default:
		// Simply return the numeric value for the type
		wszType = CEMSConversionUtil::ConvertToString( (const long )ceType );
		break;
    }

	return wszType;
}

CEMSVariantRecord2::CEMSVariantRecord2()
{
	memset( &m_record2, 0, sizeof(EMSVARIANTRECORD2) );
}

CEMSVariantRecord2::CEMSVariantRecord2( const EMSVARIANTRECORD2& crecord2 )
{
	memcpy( &m_record2, &crecord2, sizeof(EMSVARIANTRECORD2) );
}

CEMSVariantRecord2::CEMSVariantRecord2( const CEMSVariantRecord2& x )
{
	memcpy( &m_record2, &x.m_record2, sizeof(EMSVARIANTRECORD2) );
}

CEMSVariantRecord2::CEMSVariantRecord2( const EMSRECORDTYPE ceType, const BYTE* cabyData, 
									   const ULONG culBufferSize )
{
	memset( &m_record2, 0, sizeof(EMSVARIANTRECORD2) );
	SetData( ceType, cabyData, culBufferSize );
}

CEMSVariantRecord2::~CEMSVariantRecord2()
{
}

EMSTIME
CEMSVariantRecord2::GetRecordTimestamp()
{
	EMSTIME timeRet;
	timeRet.intTime = 0;

	switch( m_record2.eType )
	{
		case EMSRT_SARR_EXT:
			timeRet = m_record2.data.sarrext.sarrData.hdr.id.time;
			break;
		case EMSRT_CALIB406_EXT:
			timeRet = m_record2.data.calib406ext.calib406.hdr.id.time;
			break;
		case EMSRT_CALIB406_2:
			timeRet = m_record2.data.calib406_2.hdr.id.time;
			break;
		default:
			if ( _Is_EMSVARIANTRECORD_Type( m_record2.eType ) )
			{
				// remaining types are handled by CEMSVariantRecord
				CEMSVariantRecord	oVarRecord( _getOlderRecord() );
				timeRet = oVarRecord.GetRecordTimestamp();
			}
			break;
	}

	return timeRet;
}

void
CEMSVariantRecord2::SetData( const EMSRECORDTYPE ceType, const BYTE* cabyData, const ULONG culBufferSize )
{
	// Validate the data size.
	if( culBufferSize != CEMSVariantRecord2::GetRecordSize( ceType ) )
	{
		THROW_RUNTIME_EXCEPTION( EMS_DATA_INVALID );
	}

	m_record2.eType = ceType;
	memcpy( &m_record2.data, cabyData, culBufferSize );
}

bool
CEMSVariantRecord2::IsStatusRecordType( const EMSRECORDTYPE ceType )
{
	bool bStatusType = false;
	switch( ceType )
	{
		case EMSRT_ANTENNA:
		case EMSRT_CALIBCBC_STATS:
		case EMSRT_COLLECTOR:
		case EMSRT_COMB406_STATS:
		case EMSRT_COMMS_STATS:
		case EMSRT_GEO_CALIB406_STATS:
		case EMSRT_GEO_STATS:
		case EMSRT_LEO_CALIB406_STATS:
		case EMSRT_LOCATE_STATS:
		case EMSRT_ORBIT_STATS:
		case EMSRT_PASS_STATS:
		case EMSRT_SARR_CALIB_STATS:
		case EMSRT_SARP_CALIB_STATS:
		case EMSRT_SENSOR:
		case EMSRT_WIDEBAND_STATS:
		case EMSRT_LUT_STATUS:
			bStatusType = true;
			break;
		default:
			bStatusType = false;
	}
	return bStatusType;
}

EMSRECORDTYPE
CEMSVariantRecord2::GetVariantRecordType( const EMSLEOSTATUSTYPE ceStatusType )
{
	EMSRECORDTYPE eType = EMSRT_UNKNOWN;
	switch( ceStatusType )
	{
		case EMSAntennaStatus:
			eType = EMSRT_ANTENNA;
			break;
		case EMSCalibrateCBCStatus:
			eType = EMSRT_CALIBCBC_STATS;
			break;
		case EMSCollectorStatus:
			eType = EMSRT_COLLECTOR;
			break;
		case EMSCombine406Status:
			eType = EMSRT_COMB406_STATS;
			break;
		case EMSCommsStatus:
			eType = EMSRT_COMMS_STATS;
			break;
		case EMSGeoCalib406Status:
			eType = EMSRT_GEO_CALIB406_STATS;
			break;
		case EMSGeoSummary:
			eType = EMSRT_GEO_STATS;
			break;
		case EMSCalibrate406Status:
			eType = EMSRT_LEO_CALIB406_STATS;
			break;
		case EMSLocationStatus:
			eType = EMSRT_LOCATE_STATS;
			break;
		case EMSOrbitDetermineStatus:
			eType = EMSRT_ORBIT_STATS;
			break;
		case EMSPassSummaryStatus:
			eType = EMSRT_PASS_STATS;
			break;
		case EMSCalibrateSarrStatus:
			eType = EMSRT_SARR_CALIB_STATS;
			break;
		case EMSTCalStatus:
			eType = EMSRT_SARP_CALIB_STATS;
			break;
		case EMSSensorStatusEx: 
		case EMSSensorStatus: // this appears to be deprecated
			eType = EMSRT_SENSOR;
			break;
		case EMSWidebandStatus:
			eType = EMSRT_WIDEBAND_STATS;
			break;
		case EMSLutStatus:
			eType = EMSRT_LUT_STATUS;
			break;
		case EMSEnvironStatus: // does not map to an EMSRT type
		default:
			break;
	}
	return eType;
}

EMSLEOSTATUSTYPE
CEMSVariantRecord2::GetStatusRecordType( const EMSRECORDTYPE ceType )
{
	EMSLEOSTATUSTYPE eStatusType;
	memset( &eStatusType, 0, sizeof(eStatusType) );

	switch( ceType )
	{
		case EMSRT_ANTENNA:
			eStatusType = EMSAntennaStatus;
			break;
		case EMSRT_CALIBCBC_STATS:
			eStatusType = EMSCalibrateCBCStatus;
			break;
		case EMSRT_COLLECTOR:
			eStatusType = EMSCollectorStatus;
			break;
		case EMSRT_COMB406_STATS:
			eStatusType = EMSCombine406Status;
			break;
		case EMSRT_COMMS_STATS:
			eStatusType = EMSCommsStatus;
			break;
		case EMSRT_GEO_CALIB406_STATS:
			eStatusType = EMSGeoCalib406Status;
			break;
		case EMSRT_GEO_STATS:
			eStatusType = EMSGeoSummary;
			break;
		case EMSRT_LEO_CALIB406_STATS:
			eStatusType = EMSCalibrate406Status;
			break;
		case EMSRT_LOCATE_STATS:
			eStatusType = EMSLocationStatus;
			break;
		case EMSRT_ORBIT_STATS:
			eStatusType = EMSOrbitDetermineStatus;
			break;
		case EMSRT_PASS_STATS:
			eStatusType = EMSPassSummaryStatus;
			break;
		case EMSRT_SARR_CALIB_STATS:
			eStatusType = EMSCalibrateSarrStatus;
			break;
		case EMSRT_SARP_CALIB_STATS:
			eStatusType = EMSTCalStatus;
			break;
		case EMSRT_SENSOR:
			eStatusType = EMSSensorStatusEx; 
			break;
		case EMSRT_WIDEBAND_STATS:
			eStatusType = EMSWidebandStatus;
			break;
		case EMSRT_LUT_STATUS:
			eStatusType = EMSLutStatus;
		// EMSEnvironStatus doesn't map to an EMSRT type
		// EMSSensorStatus appears to have been replaced by EMSSensorStatusEx
		default:
			break;
	}

	return eStatusType;
}

unsigned long 
CEMSVariantRecord2::GetRecordSize( const EMSRECORDTYPE ceType )
{
	unsigned long ulSize = 0;

	switch( ceType )
	{
		case EMSRT_ANTENNA:
		case EMSRT_CALIBCBC_STATS:
		case EMSRT_COLLECTOR:
		case EMSRT_COMB406_STATS:
		case EMSRT_COMMS_STATS:
		case EMSRT_GEO_CALIB406_STATS:
		case EMSRT_GEO_STATS:
		case EMSRT_LEO_CALIB406_STATS:
		case EMSRT_LOCATE_STATS:
		case EMSRT_ORBIT_STATS:
		case EMSRT_PASS_STATS:
		case EMSRT_SARR_CALIB_STATS:
		case EMSRT_SARP_CALIB_STATS:
		case EMSRT_SENSOR:
		case EMSRT_WIDEBAND_STATS:
		case EMSRT_LUT_STATUS:
			ulSize = sizeof(EMSLEOSTATUSUPDATE);
			break;
		case EMSRT_CALIB406:
			ulSize = sizeof(EMSCALIB406DATA);
			break;
		case EMSRT_CALIBCBC:
			ulSize = sizeof(EMSCBCOUTPUTDATA);
			break;
		case EMSRT_CBC:
			ulSize = sizeof(EMSCBCDATA);
			break;
		case EMSRT_COMB406:
			ulSize = sizeof(EMSCOMBINE406DATA );
			break;
		case EMSRT_CONFIG:
			ulSize = sizeof(EMSCONFIGPACKET);
			break;
		case EMSRT_LOCATE:
			ulSize = sizeof(EMSLOCATE);
			break;
		case EMSRT_LOG:
			ulSize = sizeof(EMSLOGDATA);
			break;
		case EMSRT_ORBIT:
			ulSize = sizeof(EMSTLERECORD);
			break;
		case EMSRT_RESIDUAL:
			ulSize = sizeof(EMSRESIDUALDATA);
			break;
		case EMSRT_SARP_CALIB:
			ulSize = sizeof(EMSSARPCALIBDATA);
			break;
		case EMSRT_SARP:
			ulSize = sizeof(EMSSARPDATA);
			break;
		case EMSRT_SARR_CALIB:
			ulSize = sizeof(EMSSARRCALIBDATA);
			break;
		case EMSRT_SARR:
			ulSize = sizeof(EMSSARRDATA);
			break;
		case EMSRT_SAT_TRACK:
			ulSize = sizeof(EMSSATTRACKRECORD);
			break;
		case EMSRT_SPECTRUM:
			ulSize = sizeof(EMSSPECTRUM);
			break;
		case EMSRT_MANOEUVRE:
			ulSize = sizeof(EMSMANOEUVREDATA);
			break;
		case EMSRT_AUDIO:
			ulSize = sizeof(EMSAUDIODATARECORD_RIFF);
			break;
		case EMSRT_STAT_SUMMARY:
			ulSize = sizeof(EMSALARMDATAEX);
			break;
		case EMSRT_SARR_EXT:
			ulSize = sizeof(EMSSARRDATAEX);
			break;
		case EMSRT_CALIB406_EXT:
			ulSize = sizeof(EMSCALIB406DATAEXT);
			break;
		case EMSRT_CALIB406_2:
			ulSize = sizeof(EMSCALIB406DATA2);
			break;
	}

	return ulSize;
}

EMSVARIANTRECORD
CEMSVariantRecord2::_getOlderRecord()
{
	EMSVARIANTRECORD	recOld;
	memset( &recOld, 0, sizeof(recOld) );

	recOld.eType = m_record2.eType;
	switch( m_record2.eType )
	{
		case EMSRT_CALIB406:
			recOld.data.calib406 = m_record2.data.calib406;
			break;
		case EMSRT_LOCATE:
		case EMSRT_LOCATE_124:
			recOld.data.locate = m_record2.data.locate;
			break;
        case EMSRT_CBC:
            recOld.data.rawCBC = m_record2.data.rawCBC;
            break;
        case EMSRT_LOG:
            recOld.data.log = m_record2.data.log;
            break;
        case EMSRT_SPECTRUM:
            recOld.data.spectrum = m_record2.data.spectrum;
            break;
        case EMSRT_ANTENNA:
        case EMSRT_CALIBCBC_STATS:
        case EMSRT_COLLECTOR:
        case EMSRT_COMB406_STATS:
        case EMSRT_COMMS_STATS:
        case EMSRT_GEO_CALIB406_STATS:
        case EMSRT_GEO_STATS:
        case EMSRT_LEO_CALIB406_STATS:
        case EMSRT_LOCATE_STATS:
        case EMSRT_ORBIT_STATS:
        case EMSRT_PASS_STATS:
        case EMSRT_SARP_CALIB_STATS:
		case EMSRT_SARP_CALIB_STATS_124:
        case EMSRT_SARR_CALIB_STATS:
        case EMSRT_SENSOR:
		case EMSRT_WIDEBAND_STATS:
		case EMSRT_LUT_STATUS:
            recOld.data.status = m_record2.data.status;
            break;
        case EMSRT_STAT_SUMMARY:
			recOld.data.statsummary = m_record2.data.statsummary;
			break;
        case EMSRT_ORBIT:
            recOld.data.tle = m_record2.data.tle;
            break;
        case EMSRT_SARP_CALIB:
		case EMSRT_SARP_CALIB_124:
            recOld.data.sarpcalib = m_record2.data.sarpcalib;
            break;
        case EMSRT_SARP:
            recOld.data.sarp = m_record2.data.sarp;
            break;
        case EMSRT_SARR_CALIB:
            recOld.data.sarrcalib = m_record2.data.sarrcalib;
            break;
        case EMSRT_SARR:
		case EMSRT_SARR_124:
            recOld.data.sarr = m_record2.data.sarr;
            break;
        case EMSRT_SAT_TRACK:
            recOld.data.satTrack = m_record2.data.satTrack;
            break;
        case EMSRT_CALIBCBC:
            recOld.data.calibCBC = m_record2.data.calibCBC;
            break;
        case EMSRT_COMB406:
            recOld.data.combine406 = m_record2.data.combine406;
            break;
        case EMSRT_CONFIG:
            recOld.data.config = m_record2.data.config;
            break;
        case EMSRT_RESIDUAL:
            recOld.data.residual = m_record2.data.residual;
            break;
		case EMSRT_AUDIO:
			recOld.data.audio = m_record2.data.audio;
			break;
		default:
			// Type doesn't exist in the old record
			recOld.eType = EMSRT_UNKNOWN;
			break;
	}

	return recOld;
}


/////////////////////////////////////////////////////////
CEMSVariantRecord3::CEMSVariantRecord3()
{
	memset( &m_record3, 0, sizeof(EMSVARIANTRECORD3) );
}

CEMSVariantRecord3::CEMSVariantRecord3( const EMSVARIANTRECORD3& crecord3 )
{
	memcpy( &m_record3, &crecord3, sizeof(EMSVARIANTRECORD3) );
}

CEMSVariantRecord3::CEMSVariantRecord3( const CEMSVariantRecord3& x )
{
	memcpy( &m_record3, &x.m_record3, sizeof(EMSVARIANTRECORD3) );
}

CEMSVariantRecord3::CEMSVariantRecord3( const EMSRECORDTYPE ceType, const BYTE* cabyData, 
									   const ULONG culBufferSize )
{
	memset( &m_record3, 0, sizeof(EMSVARIANTRECORD3) );
	SetData( ceType, cabyData, culBufferSize );
}

CEMSVariantRecord3::~CEMSVariantRecord3()
{
}

EMSTIME
CEMSVariantRecord3::GetRecordTimestamp()
{
	EMSTIME timeRet;
	timeRet.intTime = 0;

	switch( m_record3.eType )
	{
		case EMSRT_ABL_DATA:
			timeRet = m_record3.data.abl.Id.timestamp;
			break;
		case EMSRT_HEALTH_STATUS:
			timeRet = m_record3.data.healthstatus.timestamp;
			break;
		case EMSRT_HEALTH_DETECTIONS:
			timeRet = m_record3.data.healthdetections.timestamp;
			break;
		case EMSRT_BEACON_ADVISORY:
			timeRet = m_record3.data.beaconadvisory.timestamp;
			break;
		default:
			if ( _Is_EMSVARIANTRECORD2_Type( m_record3.eType ) || _Is_EMSVARIANTRECORD_Type( m_record3.eType ))
			{
				// remaining types are handled by CEMSVariantRecord2
				CEMSVariantRecord2	oVarRecord2( _getOlderRecord() );
				timeRet = oVarRecord2.GetRecordTimestamp();
			}
			break;
	}

	return timeRet;
}

void
CEMSVariantRecord3::SetData( const EMSRECORDTYPE ceType, const BYTE* cabyData, const ULONG culBufferSize )
{
	// Validate the data size.
	if( culBufferSize != CEMSVariantRecord3::GetRecordSize( ceType ) )
	{
		THROW_RUNTIME_EXCEPTION( EMS_DATA_INVALID );
	}

	m_record3.eType = ceType;
	memcpy( &m_record3.data, cabyData, culBufferSize );
}

bool
CEMSVariantRecord3::IsStatusRecordType( const EMSRECORDTYPE ceType )
{
	bool bStatusType = false;
	switch( ceType )
	{
		case EMSRT_ANTENNA:
		case EMSRT_CALIBCBC_STATS:
		case EMSRT_COLLECTOR:
		case EMSRT_COMB406_STATS:
		case EMSRT_COMMS_STATS:
		case EMSRT_GEO_CALIB406_STATS:
		case EMSRT_GEO_STATS:
		case EMSRT_LEO_CALIB406_STATS:
		case EMSRT_LOCATE_STATS:
		case EMSRT_ORBIT_STATS:
		case EMSRT_PASS_STATS:
		case EMSRT_SARR_CALIB_STATS:
		case EMSRT_SARP_CALIB_STATS:
		case EMSRT_SENSOR:
		case EMSRT_WIDEBAND_STATS:
		case EMSRT_LUT_STATUS:
			bStatusType = true;
			break;
		default:
			bStatusType = false;
	}
	return bStatusType;
}

EMSRECORDTYPE
CEMSVariantRecord3::GetVariantRecordType( const EMSLEOSTATUSTYPE ceStatusType )
{
	EMSRECORDTYPE eType = EMSRT_UNKNOWN;
	switch( ceStatusType )
	{
		case EMSAntennaStatus:
			eType = EMSRT_ANTENNA;
			break;
		case EMSCalibrateCBCStatus:
			eType = EMSRT_CALIBCBC_STATS;
			break;
		case EMSCollectorStatus:
			eType = EMSRT_COLLECTOR;
			break;
		case EMSCombine406Status:
			eType = EMSRT_COMB406_STATS;
			break;
		case EMSCommsStatus:
			eType = EMSRT_COMMS_STATS;
			break;
		case EMSGeoCalib406Status:
			eType = EMSRT_GEO_CALIB406_STATS;
			break;
		case EMSGeoSummary:
			eType = EMSRT_GEO_STATS;
			break;
		case EMSCalibrate406Status:
			eType = EMSRT_LEO_CALIB406_STATS;
			break;
		case EMSLocationStatus:
			eType = EMSRT_LOCATE_STATS;
			break;
		case EMSOrbitDetermineStatus:
			eType = EMSRT_ORBIT_STATS;
			break;
		case EMSPassSummaryStatus:
			eType = EMSRT_PASS_STATS;
			break;
		case EMSCalibrateSarrStatus:
			eType = EMSRT_SARR_CALIB_STATS;
			break;
		case EMSTCalStatus:
			eType = EMSRT_SARP_CALIB_STATS;
			break;
		case EMSSensorStatusEx: 
		case EMSSensorStatus: // this appears to be deprecated
			eType = EMSRT_SENSOR;
			break;
		case EMSWidebandStatus:
			eType = EMSRT_WIDEBAND_STATS;
			break;
		case EMSLutStatus:
			eType = EMSRT_LUT_STATUS;
			break;
		case EMSEnvironStatus: // does not map to an EMSRT type
		default:
			break;
	}
	return eType;
}

EMSLEOSTATUSTYPE
CEMSVariantRecord3::GetStatusRecordType( const EMSRECORDTYPE ceType )
{
	EMSLEOSTATUSTYPE eStatusType;
	memset( &eStatusType, 0, sizeof(eStatusType) );

	switch( ceType )
	{
		case EMSRT_ANTENNA:
			eStatusType = EMSAntennaStatus;
			break;
		case EMSRT_CALIBCBC_STATS:
			eStatusType = EMSCalibrateCBCStatus;
			break;
		case EMSRT_COLLECTOR:
			eStatusType = EMSCollectorStatus;
			break;
		case EMSRT_COMB406_STATS:
			eStatusType = EMSCombine406Status;
			break;
		case EMSRT_COMMS_STATS:
			eStatusType = EMSCommsStatus;
			break;
		case EMSRT_GEO_CALIB406_STATS:
			eStatusType = EMSGeoCalib406Status;
			break;
		case EMSRT_GEO_STATS:
			eStatusType = EMSGeoSummary;
			break;
		case EMSRT_LEO_CALIB406_STATS:
			eStatusType = EMSCalibrate406Status;
			break;
		case EMSRT_LOCATE_STATS:
			eStatusType = EMSLocationStatus;
			break;
		case EMSRT_ORBIT_STATS:
			eStatusType = EMSOrbitDetermineStatus;
			break;
		case EMSRT_PASS_STATS:
			eStatusType = EMSPassSummaryStatus;
			break;
		case EMSRT_SARR_CALIB_STATS:
			eStatusType = EMSCalibrateSarrStatus;
			break;
		case EMSRT_SARP_CALIB_STATS:
			eStatusType = EMSTCalStatus;
			break;
		case EMSRT_SENSOR:
			eStatusType = EMSSensorStatusEx; 
			break;
		case EMSRT_WIDEBAND_STATS:
			eStatusType = EMSWidebandStatus;
			break;
		case EMSRT_LUT_STATUS:
			eStatusType = EMSLutStatus;
		// EMSEnvironStatus doesn't map to an EMSRT type
		// EMSSensorStatus appears to have been replaced by EMSSensorStatusEx
		default:
			break;
	}

	return eStatusType;
}

unsigned long 
CEMSVariantRecord3::GetRecordSize( const EMSRECORDTYPE ceType )
{
	unsigned long ulSize = 0;

	switch( ceType )
	{
		case EMSRT_ANTENNA:
		case EMSRT_CALIBCBC_STATS:
		case EMSRT_COLLECTOR:
		case EMSRT_COMB406_STATS:
		case EMSRT_COMMS_STATS:
		case EMSRT_GEO_CALIB406_STATS:
		case EMSRT_GEO_STATS:
		case EMSRT_LEO_CALIB406_STATS:
		case EMSRT_LOCATE_STATS:
		case EMSRT_ORBIT_STATS:
		case EMSRT_PASS_STATS:
		case EMSRT_SARR_CALIB_STATS:
		case EMSRT_SARP_CALIB_STATS:
		case EMSRT_SENSOR:
		case EMSRT_WIDEBAND_STATS:
		case EMSRT_LUT_STATUS:
			ulSize = sizeof(EMSLEOSTATUSUPDATE);
			break;
		case EMSRT_CALIB406:
			ulSize = sizeof(EMSCALIB406DATA);
			break;
		case EMSRT_CALIBCBC:
			ulSize = sizeof(EMSCBCOUTPUTDATA);
			break;
		case EMSRT_CBC:
			ulSize = sizeof(EMSCBCDATA);
			break;
		case EMSRT_COMB406:
			ulSize = sizeof(EMSCOMBINE406DATA );
			break;
		case EMSRT_CONFIG:
			ulSize = sizeof(EMSCONFIGPACKET);
			break;
		case EMSRT_LOCATE:
			ulSize = sizeof(EMSLOCATE);
			break;
		case EMSRT_LOG:
			ulSize = sizeof(EMSLOGDATA);
			break;
		case EMSRT_ORBIT:
			ulSize = sizeof(EMSTLERECORD);
			break;
		case EMSRT_RESIDUAL:
			ulSize = sizeof(EMSRESIDUALDATA);
			break;
		case EMSRT_SARP_CALIB:
			ulSize = sizeof(EMSSARPCALIBDATA);
			break;
		case EMSRT_SARP:
			ulSize = sizeof(EMSSARPDATA);
			break;
		case EMSRT_SARR_CALIB:
			ulSize = sizeof(EMSSARRCALIBDATA);
			break;
		case EMSRT_SARR:
			ulSize = sizeof(EMSSARRDATA);
			break;
		case EMSRT_SAT_TRACK:
			ulSize = sizeof(EMSSATTRACKRECORD);
			break;
		case EMSRT_SPECTRUM:
			ulSize = sizeof(EMSSPECTRUM);
			break;
		case EMSRT_MANOEUVRE:
			ulSize = sizeof(EMSMANOEUVREDATA);
			break;
		case EMSRT_AUDIO:
			ulSize = sizeof(EMSAUDIODATARECORD_RIFF);
			break;
		case EMSRT_STAT_SUMMARY:
			ulSize = sizeof(EMSALARMDATAEX);
			break;
		case EMSRT_SARR_EXT:
			ulSize = sizeof(EMSSARRDATAEX);
			break;
		case EMSRT_CALIB406_EXT:
			ulSize = sizeof(EMSCALIB406DATAEXT);
			break;
		case EMSRT_CALIB406_2:
			ulSize = sizeof(EMSCALIB406DATA2);
			break;
		case EMSRT_ABL_DATA:
			ulSize = sizeof(EMSABLData);
			break;
		case EMSRT_HEALTH_STATUS:
			ulSize = sizeof(EMSHEALTHSTATUS);
			break;
		case EMSRT_HEALTH_DETECTIONS:
			ulSize = sizeof(EMSHEALTHDETECTIONS);
			break;
		case EMSRT_BEACON_ADVISORY:
			ulSize = sizeof(EMS_BEACON_ADVISORY);
			break;
	}

	return ulSize;
}

EMSVARIANTRECORD2
CEMSVariantRecord3::_getOlderRecord()
{
	EMSVARIANTRECORD2	recOld;
	memset( &recOld, 0, sizeof(recOld) );

	recOld.eType = m_record3.eType;
	switch( m_record3.eType )
	{
		case EMSRT_CALIB406:
			recOld.data.calib406 = m_record3.data.calib406;
			break;
		case EMSRT_LOCATE:
		case EMSRT_LOCATE_124:
			recOld.data.locate = m_record3.data.locate;
			break;
        case EMSRT_CBC:
            recOld.data.rawCBC = m_record3.data.rawCBC;
            break;
        case EMSRT_LOG:
            recOld.data.log = m_record3.data.log;
            break;
        case EMSRT_SPECTRUM:
            recOld.data.spectrum = m_record3.data.spectrum;
            break;
        case EMSRT_ANTENNA:
        case EMSRT_CALIBCBC_STATS:
        case EMSRT_COLLECTOR:
        case EMSRT_COMB406_STATS:
        case EMSRT_COMMS_STATS:
        case EMSRT_GEO_CALIB406_STATS:
        case EMSRT_GEO_STATS:
        case EMSRT_LEO_CALIB406_STATS:
        case EMSRT_LOCATE_STATS:
        case EMSRT_ORBIT_STATS:
        case EMSRT_PASS_STATS:
        case EMSRT_SARP_CALIB_STATS:
		case EMSRT_SARP_CALIB_STATS_124:
        case EMSRT_SARR_CALIB_STATS:
        case EMSRT_SENSOR:
		case EMSRT_WIDEBAND_STATS:
		case EMSRT_LUT_STATUS:
            recOld.data.status = m_record3.data.status;
            break;
        case EMSRT_STAT_SUMMARY:
			recOld.data.statsummary = m_record3.data.statsummary;
			break;
        case EMSRT_ORBIT:
            recOld.data.tle = m_record3.data.tle;
            break;
        case EMSRT_SARP_CALIB:
		case EMSRT_SARP_CALIB_124:
            recOld.data.sarpcalib = m_record3.data.sarpcalib;
            break;
        case EMSRT_SARP:
            recOld.data.sarp = m_record3.data.sarp;
            break;
        case EMSRT_SARR_CALIB:
            recOld.data.sarrcalib = m_record3.data.sarrcalib;
            break;
        case EMSRT_SARR:
		case EMSRT_SARR_124:
            recOld.data.sarr = m_record3.data.sarr;
            break;
        case EMSRT_SAT_TRACK:
            recOld.data.satTrack = m_record3.data.satTrack;
            break;
        case EMSRT_CALIBCBC:
            recOld.data.calibCBC = m_record3.data.calibCBC;
            break;
        case EMSRT_COMB406:
            recOld.data.combine406 = m_record3.data.combine406;
            break;
        case EMSRT_CONFIG:
            recOld.data.config = m_record3.data.config;
            break;
        case EMSRT_RESIDUAL:
            recOld.data.residual = m_record3.data.residual;
            break;
		case EMSRT_AUDIO:
			recOld.data.audio = m_record3.data.audio;
			break;
		case EMSRT_SARR_EXT:
			recOld.data.sarrext = m_record3.data.sarrext;
			break;
		case EMSRT_CALIB406_EXT:
			recOld.data.calib406ext = m_record3.data.calib406ext;
			break;
		case EMSRT_CALIB406_2:
			recOld.data.calib406_2 = m_record3.data.calib406_2;
			break;
		default:
			// Type doesn't exist in the old record
			recOld.eType = EMSRT_UNKNOWN;
			break;
	}

	return recOld;
}

void 
CEMSVariantRecord3::GetVarRecord2( EMSVARIANTRECORD2& Record2 )
{
	Record2 = _getOlderRecord();
}


void
CEMSVariantRecord3::SetData( const EMSVARIANTRECORD2& cRecord2 )
{
	switch( cRecord2.eType )
	{
		case EMSRT_CALIB406:
			m_record3.data.calib406 = cRecord2.data.calib406;
			break;
		case EMSRT_LOCATE:
		case EMSRT_LOCATE_124:
			m_record3.data.locate = cRecord2.data.locate;
			break;
        case EMSRT_CBC:
            m_record3.data.rawCBC = cRecord2.data.rawCBC;
            break;
        case EMSRT_LOG:
            m_record3.data.log = cRecord2.data.log;
            break;
        case EMSRT_SPECTRUM:
            m_record3.data.spectrum = cRecord2.data.spectrum;
            break;
        case EMSRT_ANTENNA:
        case EMSRT_CALIBCBC_STATS:
        case EMSRT_COLLECTOR:
        case EMSRT_COMB406_STATS:
        case EMSRT_COMMS_STATS:
        case EMSRT_GEO_CALIB406_STATS:
        case EMSRT_GEO_STATS:
        case EMSRT_LEO_CALIB406_STATS:
        case EMSRT_LOCATE_STATS:
        case EMSRT_ORBIT_STATS:
        case EMSRT_PASS_STATS:
        case EMSRT_SARP_CALIB_STATS:
		case EMSRT_SARP_CALIB_STATS_124:
        case EMSRT_SARR_CALIB_STATS:
        case EMSRT_SENSOR:
		case EMSRT_WIDEBAND_STATS:
		case EMSRT_LUT_STATUS:
            m_record3.data.status = cRecord2.data.status;
            break;
        case EMSRT_STAT_SUMMARY:
			m_record3.data.statsummary = cRecord2.data.statsummary;
			break;
        case EMSRT_ORBIT:
            m_record3.data.tle = cRecord2.data.tle;
            break;
        case EMSRT_SARP_CALIB:
		case EMSRT_SARP_CALIB_124:
            m_record3.data.sarpcalib = cRecord2.data.sarpcalib;
            break;
        case EMSRT_SARP:
            m_record3.data.sarp = cRecord2.data.sarp;
            break;
        case EMSRT_SARR_CALIB:
            m_record3.data.sarrcalib = cRecord2.data.sarrcalib;
            break;
        case EMSRT_SARR:
		case EMSRT_SARR_124:
            m_record3.data.sarr = cRecord2.data.sarr;
            break;
        case EMSRT_SAT_TRACK:
            m_record3.data.satTrack = cRecord2.data.satTrack;
            break;
        case EMSRT_CALIBCBC:
            m_record3.data.calibCBC = cRecord2.data.calibCBC;
            break;
        case EMSRT_COMB406:
            m_record3.data.combine406 = cRecord2.data.combine406;
            break;
        case EMSRT_CONFIG:
            m_record3.data.config = cRecord2.data.config;
            break;
        case EMSRT_RESIDUAL:
            m_record3.data.residual = cRecord2.data.residual;
            break;
		case EMSRT_AUDIO:
			m_record3.data.audio = cRecord2.data.audio;
			break;
		case EMSRT_SARR_EXT:
			m_record3.data.sarrext = cRecord2.data.sarrext;
			break;
		case EMSRT_CALIB406_EXT:
			m_record3.data.calib406ext = cRecord2.data.calib406ext;
			break;
		case EMSRT_CALIB406_2:
			m_record3.data.calib406_2 = cRecord2.data.calib406_2;
			break;
		default:
			// Type doesn't exist in the old record
			m_record3.eType = EMSRT_UNKNOWN;
			break;
	}
}

