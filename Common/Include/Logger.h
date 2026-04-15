#ifndef INC_LOGGER
#define INC_LOGGER

#include "emspipe.h"
#include "emserror.h"

#include "pksource.h"

#define EMS_MAX_LOG_MSG_LENGTH	( 256 )

// System Message Types
typedef const enum
{
  LogMsgTrace = 0, 
	LogMsgDebug = 1, 
	LogMsgData = 2, 
	LogMsgInfo = 3, 
	LogMsgWarn = 4,
  LogMsgAlarm = 5, 
	LogMsgComms = 6, 
	LogMsgState = 7, 
	LogMsgFatal = 8
} EMSLOGMSGTYPE;

class CEMSLogger
{
public:
	CEMSLogger( LPCTSTR lpcszTaskName=0 );
	~CEMSLogger( void );
	
	EMS_RESULT Initialize( LPCTSTR lpcszTaskName=0 );
	EMS_RESULT Reset( void );
	int OutputMessage( EMSLOGMSGTYPE msgType, LPCTSTR lpcszMessage );

private: // methods
	int _SetTaskName( LPCTSTR lpcszTaskName );

private: // data
	LPTSTR	m_lpszTaskName;
	BOOL		m_bInitialized;
	IEMSDataPipeline *m_lpPipeline;
	CEMSPacketSource *m_lpLogSrc;
	CEMSPacketSource *m_lpMaintLogSrc;
	BOOL		m_bUseDiskFile;
};

#endif // INC_LOGGER

