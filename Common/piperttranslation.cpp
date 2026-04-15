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

#include "piperttranslation.h"
#include "leodefns.h"

typedef struct tagPipeRTTranslation
{
	EMSRECORDTYPE eType;
	BYTE byChannel;
} EMSPIPERTTRANS;

static const EMSPIPERTTRANS gs_castrPipeRTTranslation[] =	{	{EMSRT_UNKNOWN, 0 },
																{EMSRT_ANTENNA, LEO_ANTENNA_DATA},
																{EMSRT_CALIB406, LEO_CALIBRATE_406_DATA},
																{EMSRT_CALIBCBC_STATS, LEO_STATUS_DATA},
																{EMSRT_CBC, LEO_CBC_DATA},
																{EMSRT_COLLECTOR, LEO_STATUS_DATA},
																{EMSRT_COMB406_STATS, LEO_STATUS_DATA},
																{EMSRT_COMMS_STATS, LEO_STATUS_DATA},
																{EMSRT_GEO_CALIB406_STATS, LEO_STATUS_DATA},
																{EMSRT_GEO_STATS, LEO_STATUS_DATA},
																{EMSRT_LEO_CALIB406_STATS, LEO_STATUS_DATA},
																{EMSRT_LOCATE, LEO_LOCATE_DATA},
																{EMSRT_LOCATE_STATS, LEO_STATUS_DATA},
																{EMSRT_LOG, LEO_LOG_DATA},
																{EMSRT_ORBIT, LEO_TLE_DATA},
																{EMSRT_ORBIT_STATS, LEO_STATUS_DATA},
																{EMSRT_PASS_STATS, LEO_STATUS_DATA},
																{EMSRT_SARP_CALIB, LEO_SARP_CALIB_DATA},
																{EMSRT_SARP_CALIB_STATS, LEO_STATUS_DATA},
																{EMSRT_SARP, LEO_SARP_DATA},
																{EMSRT_SARR_CALIB, LEO_SARR_CALIB_DATA},
																{EMSRT_SARR_CALIB_STATS, LEO_STATUS_DATA},
																{EMSRT_SARR, LEO_SARR_DATA},
																{EMSRT_SAT_TRACK, LEO_SAT_TRACK_PASS_DATA},
																{EMSRT_SENSOR, LEO_STATUS_DATA},
																{EMSRT_SPECTRUM, LEO_SPECTRUM_DATA},
																{EMSRT_STAT_SUMMARY, LEO_ALARM_DATA},
																{EMSRT_WIDEBAND_STATS, LEO_STATUS_DATA},
																{EMSRT_AUDIO, LUT_AUDIO_DATA_RIFF},
																{EMSRT_MANOEUVRE, 0},
																{EMSRT_SARP_CALIB_124, 0},
																{EMSRT_SARP_CALIB_STATS_124, LEO_STATUS_DATA},
																{EMSRT_SARR_124, 0},
																{EMSRT_LOCATE_124, 0},
																{EMSRT_SARR_EXT, LUT_SARREXT_DATA},
																{EMSRT_CALIB406_EXT, LEO_CALIBRATE_406EX_DATA},
																{EMSRT_CALIB406_2, LEO_CALIBRATE_406_2_DATA},
																{EMSRT_COMB406, LEO_COMBINE_406_DATA},
																{EMSRT_CONFIG, LUT_CONFIG_DATA},
																{EMSRT_CALIBCBC, LEO_CBC_OUTPUT_DATA},
																{EMSRT_BEACON_ADVISORY, LUT_BEACON_ADVISORY_DATA},
																{EMSRT_LAST, 0},
															};

CEMSRTToPipeTranslator::CEMSRTToPipeTranslator()
{
}

CEMSRTToPipeTranslator::~CEMSRTToPipeTranslator()
{
}

BYTE 
CEMSRTToPipeTranslator::Translate( const EMSRECORDTYPE ceType )
{
	BYTE byRet = 0;

	for( ULONG l = 0; (l < EMSRT_LAST + 1) && ( 0 == byRet ); l++ )
	{
		if( ceType == gs_castrPipeRTTranslation[l].eType )
		{
			byRet = gs_castrPipeRTTranslation[l].byChannel;
		}
	}

	return byRet;
}