
#include "daccmd.h"

#include "emserror.h"
#include "emsexcpt.h"
#include "commandformats.h"
#include "ecmdproc.h"
#include "convutility.h"
#include "gwaymsgs.h"

CEMSDACCmd::CEMSDACCmd() : m_ulLuts(0), m_aulLuts(0), m_ulDataTypes(0), m_aDataTypes(0), 
							m_wszURL(0), m_eType(DACCMD_UNKNOWN)
{
	m_timeStart.intTime = 0;
	m_timeEnd.intTime = 0;
}

CEMSDACCmd::CEMSDACCmd( const CEMSDACCmd& x )
{
	m_ulLuts = x.m_ulLuts;

	if( m_ulLuts > 0 )
	{
		m_aulLuts = new unsigned long[ m_ulLuts ];

		if( !m_aulLuts )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memcpy( m_aulLuts, x.m_aulLuts, m_ulLuts*sizeof(unsigned long) );
	}
	else
	{
		m_aulLuts = 0;
	}

	m_ulDataTypes = x.m_ulDataTypes;

	if( m_ulDataTypes > 0 )
	{
		m_aDataTypes = new EMSRECORDTYPE[ m_ulDataTypes ];

		if( !m_aDataTypes )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memcpy( m_aDataTypes, x.m_aDataTypes, m_ulDataTypes*sizeof(EMSRECORDTYPE) );
	}
	else
	{
		m_aDataTypes = 0;
	}

	if( x.m_wszURL && (wcslen(x.m_wszURL) > 0) )
	{
		m_wszURL = new wchar_t[ wcslen(x.m_wszURL) + 1 ];

		if( !m_wszURL )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( m_wszURL, 0, (wcslen(x.m_wszURL) + 1)*sizeof(wchar_t) );

		wcscpy( m_wszURL, x.m_wszURL );
	}

}

CEMSDACCmd::~CEMSDACCmd()
{
	if( m_aulLuts )
	{
		delete[] m_aulLuts;
		m_aulLuts = 0;
	}

	if( m_aDataTypes )
	{
		delete[] m_aDataTypes;
		m_aDataTypes = 0;
	}

	if( m_wszURL )
	{
		delete[] m_wszURL;
		m_wszURL = 0;
	}

}

void
CEMSDACCmd::SetLuts( const unsigned long culLuts, const unsigned long* caulLutIDs )
{
	if( !caulLutIDs )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	if( m_aulLuts )
	{
		delete[] m_aulLuts;
		m_aulLuts = 0;
	}

	m_aulLuts = new unsigned long[ culLuts ];

	if( !m_aulLuts )
	{
		THROW_NOMEMORY_EXCEPTION();
	}

	m_ulLuts = culLuts;

	for( unsigned long l = 0; l < culLuts; l++ )
	{
		m_aulLuts[l] = caulLutIDs[l];
	}
}

void 
CEMSDACCmd::GetLuts( unsigned long& ulLuts, unsigned long*& aulLutIDs ) const
{
	aulLutIDs = 0;
	ulLuts = 0;

	if( m_aulLuts && (m_ulLuts > 0) )
	{
		aulLutIDs = new unsigned long[ m_ulLuts ];

		if( !aulLutIDs )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		ulLuts = m_ulLuts;

		for( unsigned long l = 0; l < ulLuts; l++ )
		{
			aulLutIDs[l] = m_aulLuts[l];
		}
	}
}

void 
CEMSDACCmd::SetDataTypes( const unsigned long culDataTypes, const EMSRECORDTYPE* caeRecTypes )
{
	if( !caeRecTypes )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	if( m_aDataTypes )
	{
		delete[] m_aDataTypes;
		m_aDataTypes = 0;
	}

	m_aDataTypes = new EMSRECORDTYPE[ culDataTypes ];

	if( !m_aDataTypes )
	{
		THROW_NOMEMORY_EXCEPTION();
	}

	m_ulDataTypes = culDataTypes;

	for( unsigned long l = 0; l < culDataTypes; l++ )
	{
		m_aDataTypes[l] = caeRecTypes[l];
	}
}

void 
CEMSDACCmd::GetDataTypes( unsigned long& ulDataTypes, EMSRECORDTYPE*& aeRecTypes ) const
{
	aeRecTypes = 0;
	ulDataTypes = 0;

	if( m_aDataTypes && (m_ulDataTypes > 0) )
	{
		aeRecTypes = new EMSRECORDTYPE[ m_ulDataTypes ];

		if( !aeRecTypes )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		ulDataTypes = m_ulDataTypes;

		for( unsigned long l = 0; l < ulDataTypes; l++ )
		{
			aeRecTypes[l] = m_aDataTypes[l];
		}
	}
}

void 
CEMSDACCmd::SetSourceURL( const wchar_t* cwszSrcURL )
{
	if( !cwszSrcURL )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	if( m_wszURL )
	{
		delete[] m_wszURL;
		m_wszURL = 0;
	}

	long lLen = wcslen( cwszSrcURL );

	if( lLen > 0 )
	{
		m_wszURL = new wchar_t[ lLen + 1 ];

		if( ! m_wszURL )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( m_wszURL, 0, (lLen+1)*sizeof(wchar_t) );
		
		wcscpy( m_wszURL, cwszSrcURL );
	}
}

wchar_t* 
CEMSDACCmd::GetSourceURL() const
{
	wchar_t* wszRet = 0;

	if( !m_wszURL || ( wcslen(m_wszURL) < 1 ) )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	long lLen = wcslen( m_wszURL );

	wszRet = new wchar_t[ lLen + 1 ];

	if( !wszRet )
	{
		THROW_NOMEMORY_EXCEPTION();
	}

	memset( wszRet, 0, (lLen+1)*sizeof(wchar_t) );

	wcscpy( wszRet, m_wszURL );

	return wszRet;
}

TCHAR* 
CEMSDACCmd::Serialize( const EMSDACCOMMAND ceCmdType ) const
{
	long lChars = EMS_PIPE_MAX_COMMAND_LENGTH / sizeof(TCHAR);
	TCHAR* szCmd = 0;

	try
	{
		szCmd = new TCHAR[lChars+1];
		
		if( !szCmd )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( szCmd, 0, (lChars+1)*sizeof(TCHAR) );

		switch( ceCmdType )
		{
			case DACCMD_RECOVER:
				{
					// Convert the LutIDs into a string.
#if defined(UNICODE) || defined(_UNICODE)
					wstring szLutIDs;
#else
					string szLutIDs;
#endif
					for( unsigned long l = 0; l < m_ulLuts; l++ )
					{
						if( l > MAX_LUTS_FOR_MANUAL_RECOVERY )
						{
							CEMSLogMsgParam param;
							param += MAX_LUTS_FOR_MANUAL_RECOVERY;

							throw CEMSException( EMS_GWAY_MAN_RECOVERY_TOO_MANY_LUTS, param );
						}

						if( 0 != l )
							szLutIDs += LUT_SEPARATOR;

						// Six digit max for the LUT ID.
						TCHAR szLutID[6];
						memset( szLutID, 0, 6*sizeof(TCHAR) );

						_ultot( m_aulLuts[l], szLutID, 10 );

						szLutIDs.append( szLutID );
					}

#if defined(UNICODE) || defined(_UNICODE)
					wstring szDataTypes;
#else
					string szDataTypes;
#endif

					for( long l = 0; l < m_ulDataTypes; l++ )
					{
						if( l > MAX_DATATYPES_FOR_MANUAL_RECOVER )
						{
							CEMSLogMsgParam param;
							param += MAX_DATATYPES_FOR_MANUAL_RECOVER;

							throw CEMSException( EMS_GWAY_MAN_RECOVERY_TOO_MANY_DATATYPES, param );
						}

						if( 0 != l )
							szDataTypes += DATATYPE_SEPARATOR;

						// Six digit max data types.
						TCHAR szDataType[6];
						memset( szDataType, 0, 6*sizeof(TCHAR) );

						_ltot( m_aDataTypes[l], szDataType, 10 );

						szDataTypes.append( szDataType );
					}

					int iRet = 0;
#if defined(UNICODE) || defined(_UNICODE)
					iRet = _sntprintf( szCmd, lChars, cszRecoverDataCmdFmt, CEMSConversionUtil::ConvertToString( szLutIDs.c_str() ).c_str(), 
												CEMSConversionUtil::ConvertToString( szDataTypes.c_str()).c_str(), 
												GetStartTime(), GetEndTime() );
#else
					iRet = _sntprintf( szCmd, lChars, cszRecoverDataCmdFmt, szLutIDs.c_str(), 
											szDataTypes.c_str(), GetStartTime(), GetEndTime() );
#endif

					if( iRet < 1 )
					{
						THROW_RUNTIME_EXCEPTION( EMS_GWAY_PIPE_CMD_LENGTH_EXCEEDED );
					}
				}
				break;
			case DACCMD_SEND:
				{
					int iRet = 0;

#if defined(UNICODE) || defined(_UNICODE)
					iRet = _sntprintf( szCmd, lChars, cszSendDataCmdFmt, m_wszURL );
#else
					iRet = _sntprintf( szCmd, lChars, cszSendDataCmdFmt, 
									CEMSConversionUtil::ConvertToString( m_wszURL).c_str() );
#endif
					if( iRet < 1 )
					{
						THROW_RUNTIME_EXCEPTION( EMS_GWAY_PIPE_CMD_LENGTH_EXCEEDED );
					}
				}
				break;
			default:
				THROW_RUNTIME_EXCEPTION( EMS_INVALID_CMD ); 
		}
	}
	catch( ... )
	{
		if( szCmd )
		{
			delete[] szCmd;
			szCmd = 0;
		}

		throw;
	}

	return szCmd;
}

void 
CEMSDACCmd::Deserialize( CEMSCommandProcessor* pCmdProcessor )
{
	if( !pCmdProcessor )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	// Parse it
	pCmdProcessor->ParseCommand();
	pCmdProcessor->GetCmdLine();

	if( pCmdProcessor->IsCommand( TEXT("Rec") ) )
	{
		m_eType = DACCMD_RECOVER;

		TCHAR szLuts[1024];
		memset( szLuts, 0, 1024*sizeof(TCHAR) );
		pCmdProcessor->TextParam( TEXT("luts"), szLuts, 
					sizeof( szLuts ) / sizeof( szLuts[ 0 ] ) );

		_SetLuts( szLuts );

		TCHAR szDataTypes[1024];
		memset( szDataTypes, 0, 1024*sizeof(TCHAR) );
		pCmdProcessor->TextParam( TEXT("data"), szDataTypes, 
					sizeof( szDataTypes ) / sizeof( szDataTypes[ 0 ] ) );

		_SetDataTypes( szDataTypes );

		TCHAR szStart[64];
		memset( szStart, 0, 64*sizeof(TCHAR) );
		pCmdProcessor->TextParam( TEXT("start"), szStart, 
					sizeof( szStart ) / sizeof( szStart[ 0 ] ) );

		EMSTIME time;
		time.intTime = _ttoi64(szStart);
		SetStartTime( time  );

		TCHAR szEnd[64];
		memset( szEnd, 0, 64*sizeof(TCHAR) );
		pCmdProcessor->TextParam( TEXT("end"), szEnd, 
					sizeof( szEnd ) / sizeof( szEnd[ 0 ] ) );

		time.intTime = _ttoi64(szEnd);
		SetEndTime( time );
	}
	else if( pCmdProcessor->IsCommand( TEXT("SendData") ) )
	{
		m_eType = DACCMD_SEND;

		TCHAR szSource[1024];
		memset( szSource, 0, 1024*sizeof(TCHAR) );
		pCmdProcessor->TextParam( TEXT("src"), szSource, 
					sizeof( szSource ) / sizeof( szSource[ 0 ] ) );

#if defined(UNICODE) || defined(_UNICODE)
		SetSourceURL( szSource );
#else
		SetSourceURL( CEMSConversionUtil::ConvertToString( szSource ).c_str() );
#endif
	}
	else
	{
		THROW_RUNTIME_EXCEPTION( EMS_INVALID_CMD );
	}
}

void
CEMSDACCmd::_SetLuts( TCHAR* szLuts )
{
	if( !szLuts )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	TCHAR* szTok = _tcstok( szLuts, LUT_SEPARATOR );

	while( szTok )
	{
		unsigned long* aulTemp = new unsigned long[ m_ulLuts + 1 ];

		for( unsigned long l = 0; l < m_ulLuts; l++ )
		{
			aulTemp[l] = m_aulLuts[l];
		}

		aulTemp[ m_ulLuts ] = _ttol( szTok );

		if( m_aulLuts )
		{
			delete[] m_aulLuts;
			m_aulLuts = 0;
		}

		m_aulLuts = aulTemp;
		m_ulLuts++;

		szTok = _tcstok( 0, LUT_SEPARATOR );
	}

}

void
CEMSDACCmd::_SetDataTypes( TCHAR* szDataTypes )
{
	if( !szDataTypes )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	TCHAR* szTok = _tcstok( szDataTypes, DATATYPE_SEPARATOR );

	while( szTok )
	{
		EMSRECORDTYPE* aulTemp = new EMSRECORDTYPE[ m_ulDataTypes + 1 ];

		for( unsigned long l = 0; l < m_ulDataTypes; l++ )
		{
			aulTemp[l] = m_aDataTypes[l];
		}

		aulTemp[ m_ulDataTypes ] = static_cast<EMSRECORDTYPE>( _ttol( szTok ) );

		if( m_aDataTypes )
		{
			delete[] m_aDataTypes;
			m_aDataTypes = 0;
		}

		m_aDataTypes = aulTemp;
		m_ulDataTypes++;

		szTok = _tcstok( 0, DATATYPE_SEPARATOR );
	}

}