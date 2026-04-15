#include "emsdberrorreporter.h"
#include <tchar.h>
#include <stdio.h>
#include "dbsmsgs.h"

CEMSDBErrorReporter::CEMSDBErrorReporter( TCHAR* szRecordName )
{
	if( szRecordName )
		_tcsncpy( m_lpszRecordName, szRecordName, 31 );
}

void
CEMSDBErrorReporter::ReportError( EMS_RESULT hr )
{
	TCHAR szErrorCode[256];
	LPCTSTR lpcszStrs[2] =  { szErrorCode, m_lpszRecordName };

	_sntprintf( szErrorCode, 255, _T("%08lx"), hr );

	m_logEvent.ReportEvent( EMSLogMsgAlarm, EMS_DBS_ERROR, EMSLOGCAT_Database, 2, lpcszStrs );
}

EMS_RESULT
CEMSDBErrorReporter::ReportException( _com_error& e )
{
	EMS_RESULT hr = e.Error();

	TCHAR szErrorCode[256];
	TCHAR szDescription[256];
	TCHAR szSource[256];
	LPCTSTR lpcszStrs[4] =  { m_lpszRecordName, szErrorCode, szDescription, szSource };

	_sntprintf( szErrorCode, 255, _T("%08lx"), hr );
	_sntprintf( szDescription, 255, _T("%S"), (wchar_t*) e.Description() );
	_sntprintf( szSource, 255, _T("%S"), (wchar_t*) e.Source() );

	m_logEvent.ReportEvent( EMSLogMsgAlarm, EMS_DBS_ADO_EXCEPTION, EMSLOGCAT_Database, 4, lpcszStrs );

	return hr;
}

void
CEMSDBErrorReporter::ReportSQL( wchar_t* szSQL )
{
	if( szSQL )
	{
		if( wcslen( szSQL ) )
		{
			TCHAR szSQLBuffer[1024];
			LPCTSTR lpcszStrs[1] = { szSQLBuffer };

			_sntprintf( szSQLBuffer, 1023, _T("%S"), szSQL );

			m_logEvent.ReportEvent( EMSLogMsgAlarm, EMS_DBS_SQL, EMSLOGCAT_Database, 1, lpcszStrs );
		}
	}
}