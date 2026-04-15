
#ifndef __EMSDBERRORREPORTER_H__
#define __EMSDBERRORREPORTER_H__

#include <comdef.h>
#include "logevent.h"

class CEMSDBErrorReporter
{
public:
	CEMSDBErrorReporter( TCHAR* szRecordName );
	~CEMSDBErrorReporter() {}

	void ReportError( EMS_RESULT hr );
	EMS_RESULT ReportException( _com_error& e );
	void ReportSQL( wchar_t* szSQL );

private:
	CEMSLogEvent m_logEvent;
	TCHAR m_lpszRecordName[32];
};


#endif // EMSDBERRORREPORTER_H__