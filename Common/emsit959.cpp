/********************************************************************
*	Module:			emsit959.cpp
*	Description:	Implementation of CEMSSit915  Class
*					(Health Status Narrative)
*						
*********************************************************************
*	              Copyright (c) 2009 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
#include <stdio.h>

#include "sitfield.h"
#include "emsit959.h"

const TCHAR c_szSitHdrFmt[ ] = TEXT("/%03d/%04d/%s");

// /Report Time/09 014 1353/3180 
const TCHAR c_szSitLineFmt1[ ] = TEXT("/Report Time/%s/%04d");
// /Report Period/005
const TCHAR c_szSitLineFmt2[ ] = TEXT("/Report Period/%03d");
// /Warnings/001
const TCHAR c_szSitLineFmt3[ ] = TEXT("/Warnings/%03d");
// /Alarms/000
const TCHAR c_szSitLineFmt4[ ] = TEXT("/Alarms/%03d");
// /Detection Groups/03
const TCHAR c_szSitLineFmt5[ ] = TEXT("/Detection Groups/%02d");
// /Detection/001/302/0024/09 014 1350     (repeated)
const TCHAR c_szSitLineFmtDetection[ ] = TEXT("/Detection/%03d/%03d/%04d/%s");

CEMSSit959A::CEMSSit959A() :
	m_ulDetectRecCount(0),
	m_paDetectionRecords(0)
{
	SetSitNumber(959);
	SetSitCode(0x959A);
	memset( &m_status, 0, sizeof(m_status) );
}

CEMSSit959A::~CEMSSit959A()
{
	Reset();
}

void CEMSSit959A::Reset( void )
{
	SetSitNumber(959);
	SetSitCode(0x959A);
	_resetStatus();
}

void CEMSSit959A::_resetStatus( void )
{
	memset( &m_status, 0, sizeof(m_status) );

	if ( m_paDetectionRecords )
	{
		delete[] m_paDetectionRecords;
		m_paDetectionRecords = 0;
	}
	m_ulDetectRecCount = 0;
}

EMS_RESULT CEMSSit959A::SetHealthStatus( 
					const EMSHEALTHSTATUS cStatus,
					const unsigned long culRecCount,
					const EMSHEALTHDETECTIONS* caDetectionRecords )
{
	if ( culRecCount && !caDetectionRecords ) return EMS_BAD_PARAM;

	EMS_RESULT hr = EMS_OK;

	_resetStatus();

	m_status = cStatus;
	if ( culRecCount && caDetectionRecords )
	{
		m_paDetectionRecords = new EMSHEALTHDETECTIONS[ culRecCount ];
		if ( m_paDetectionRecords )
		{
			memcpy( m_paDetectionRecords, caDetectionRecords, culRecCount*sizeof(EMSHEALTHDETECTIONS) );
			m_ulDetectRecCount = culRecCount;
		}
		else
			hr = EMS_NO_MEMORY;
	}
	return hr;
}

EMS_RESULT CEMSSit959A::GenerateSitBody( IEMSSeqStream *lpStream )
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		CEMSSitMsgField msgField;

		TCHAR szBuffer[ 256 ];
		
		// Report Time and LUT ID
		wsprintf( szBuffer, c_szSitLineFmt1, 
							msgField.TextMF14( m_status.timestamp ),
							m_status.ulLutID );
		hr = WriteLine( lpStream, szBuffer );

		// Report period
		wsprintf( szBuffer, c_szSitLineFmt2, m_status.ulReportPeriod );
		hr = WriteLine( lpStream, szBuffer );

		// Warning Count
		wsprintf( szBuffer, c_szSitLineFmt3, m_status.wWarningCount );
		hr = WriteLine( lpStream, szBuffer );

		// Alarm Count
		wsprintf( szBuffer, c_szSitLineFmt4, m_status.wAlarmCount );
		hr = WriteLine( lpStream, szBuffer );

		// #detections
		wsprintf( szBuffer, c_szSitLineFmt5, m_ulDetectRecCount );
		hr = WriteLine( lpStream, szBuffer );

		for ( int i=0; i<m_ulDetectRecCount && SUCCEEDED(hr); i++ )
		{
			wsprintf( szBuffer, c_szSitLineFmtDetection, 
				m_paDetectionRecords[i].ulFPID, 
				m_paDetectionRecords[i].ulSatID, 
				m_paDetectionRecords[i].wDetectionCount,		
				msgField.TextMF14( m_paDetectionRecords[i].timeLastDetection ) );
			hr = WriteLine( lpStream, szBuffer );
		}
	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

EMS_RESULT CEMSSit959A::GenerateSitHeader( IEMSSeqStream *lpStream)
{
	EMS_RESULT hr = EMS_OK;

	if ( lpStream )
	{
		TCHAR szBuffer[ 256 ];

		wsprintf( szBuffer, c_szSitHdrFmt, 
						GetSitNumber(), 
						GetSitDestination(),
						GetSitCodeStr() );

		hr = WriteLine( lpStream, szBuffer );

	}
	else
		hr = EMS_INVALID_STREAM;

	return hr;
}

