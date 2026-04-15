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
#pragma warning(disable:4786)

#include "passschedcsv.h"
#include "csvfile.h"
#include "convutility.h"
#include "emstime.h"

CEMSPassSchedCSV::CEMSPassSchedCSV()
{
}

CEMSPassSchedCSV::CEMSPassSchedCSV( const CEMSPassSchedCSV& x )
{
}

ULONG 
CEMSPassSchedCSV::Read( const wchar_t* cwszFile, const ULONG culMaxRecords, 
						EMSSATTRACKRECORD* aPasses)
{
	ULONG ulRet = 0;

	if( culMaxRecords > 0 &&
		aPasses )
	{
		CEMSCSVFile oFile;

		oFile.Open( cwszFile );
		oFile.ReadHeader( 1, true, 0 );

		int iValues = 0;
		while( ( 0 < (iValues = oFile.ReadLine() ) ) && 
				ulRet < culMaxRecords )
		{
			std::string oszStatusValue = oFile.GetValueA( L"Status" );

			if( 0 == oszStatusValue.compare( "Process" ) )
			{
				aPasses[ulRet].track.PassInfo.ulFlags |= EMS_PASSFLAG_PROCESS;
			}
			else if( 0 == oszStatusValue.compare( "Suppress" ) )
			{
				aPasses[ulRet].track.PassInfo.ulFlags |= EMS_PASSFLAG_SUPPRESS;
			}

			// Process it.
			aPasses[ulRet].track.PassInfo.ulSatelliteID = CEMSConversionUtil::ConvertToULong( oFile.GetValue( L"Satellite ID" ).c_str() );
			aPasses[ulRet].track.PassInfo.ulOrbitNumber = CEMSConversionUtil::ConvertToULong( oFile.GetValue( L"Pass #" ).c_str() );

			EMSTIME timeStart = _ParseDateTime( oFile.GetValueA( L"AOS Time" ).c_str() );
			aPasses[ulRet].track.PassInfo.timeAOS = timeStart;
			aPasses[ulRet].track.actualStartTime = timeStart;

			EMSTIME timeEnd = _ParseDateTime( oFile.GetValueA( L"LOS Time" ).c_str() );
			aPasses[ulRet].track.PassInfo.timeLOS = timeEnd;
			aPasses[ulRet].track.actualEndTime = timeEnd;

			ulRet++;

		}
	}

	return ulRet;
}

EMSTIME
CEMSPassSchedCSV::_ParseDateTime( const char* cszDateTime )
{
	EMSTIME timeRet;
	timeRet.intTime = 0;

	if( cszDateTime )
	{
		std::string oszDateTime( cszDateTime );

		// Fields are fixed size:  YYYY/DDD HH:MM:SS

		// Year -- 4 digits
		std::string oszYear = oszDateTime.substr( 0, 4 );

		// Julian Day
		std::string oszJulian = oszDateTime.substr( 5, 3 );

		// Hour
		std::string oszHour = oszDateTime.substr( 9, 2 );

		// Minute
		std::string oszMinute = oszDateTime.substr( 12, 2 );

		// Second
		std::string oszSecond = oszDateTime.substr( 15, 2 );

		CEMSTime oTime;
		int iRet = 0;
		oTime.SetTime(	atoi( oszYear.c_str() ), 
						atoi( oszJulian.c_str() ),
						atoi( oszHour.c_str() ),
						atoi( oszMinute.c_str() ),
						atoi( oszSecond.c_str() ),
						(long) 0 );

		timeRet = oTime;

	}

	return timeRet;
}