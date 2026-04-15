
#include "gatewaycmd.h"
#include "emserror.h"
#include "emsexcpt.h"
#include "emspipe.h"
#include "ecmdproc.h"
#include "cmdsrc.h"	
#include "gwaymsgs.h"
#include <stdio.h>
#include "leodefns.h"

CEMSGatewayCmd::CEMSGatewayCmd() : m_eRespType(GTWY_RESP_UKNOWN ), m_hrStatus(EMS_OK), m_ulSessionID(0),
									m_pCmdSrc(0), m_pCmdChannel(0), m_ulTotalRecords(0), m_ulRecordSize(0),
									m_bOverflow(false), m_cacheID(NULLDALCACHEID)
{
}

CEMSGatewayCmd::CEMSGatewayCmd( const CEMSGatewayCmd& x ) : m_eRespType(GTWY_RESP_UKNOWN ), m_hrStatus(EMS_OK), 
															m_ulSessionID(0), m_pCmdSrc(0), m_pCmdChannel(0),
															m_ulTotalRecords(0), m_ulRecordSize(0),
															m_bOverflow(false), m_cacheID(NULLDALCACHEID)
{
	m_eRespType = x.m_eRespType;
	m_hrStatus = x.m_hrStatus;
	m_ulSessionID = x.m_ulSessionID;

	m_ulTotalRecords = x.m_ulTotalRecords;
	m_ulRecordSize = x.m_ulRecordSize;
	m_bOverflow = x.m_bOverflow;
	m_cacheID = x.m_cacheID;

}

CEMSGatewayCmd::~CEMSGatewayCmd()
{
	if( m_pCmdChannel )
	{
		if( m_pCmdSrc )
		{
			m_pCmdChannel->UnRegisterSource( m_pCmdSrc );
		}

		m_pCmdChannel->Release();
		m_pCmdChannel = 0;
	}

	if( m_pCmdSrc )
	{
		m_pCmdSrc->Release();
		m_pCmdSrc = 0;
	}
}

TCHAR* 
CEMSGatewayCmd::SerializeResponse() const
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

		switch( m_eRespType )
		{
			case GTWY_RESP_LPC_INIT_DATA_DONE:
				_stprintf( szCmd, cszGtwyCmdLPCInitDataEnd, m_hrStatus, m_ulSessionID );
				break;
			case GTWY_RESP_LPC_PROCESS406_DATA_DONE:
				_stprintf( szCmd, cszGtwyCmdLPCProcess406DataEnd, m_hrStatus );
				break;
			case GTWY_RESP_LPC_GET_FILENAMES_DONE:
				_stprintf( szCmd, cszGtwyCmdLPCGetFilenamesDataEnd, m_hrStatus );
				break;
			case GTWY_RESP_GENERIC:
				_stprintf( szCmd, cszGtwyCmdGenericDataEnd, m_hrStatus );
				break;
			default:
				THROW_RUNTIME_EXCEPTION( EMS_GWAY_UNKNOWN_RESPONSE );
				break;
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
CEMSGatewayCmd::SendResponse()
{
	long lChars = EMS_PIPE_MAX_COMMAND_LENGTH / sizeof(TCHAR);
	TCHAR* szCmd = 0;

	CEMSCommandSource* pCmdSrc = 0;

	try
	{
		szCmd = new TCHAR[lChars+1];
		
		if( !szCmd )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( szCmd, 0, (lChars+1)*sizeof(TCHAR) );

		switch( m_eRespType )
		{
			case GTWY_RESP_GENERIC:
				_stprintf( szCmd, cszGtwyCmdGenericDataEnd, m_hrStatus );
				break;
			case GTWY_RESP_DAL_GET:
				_stprintf( szCmd, cszGtwyCmdDALGetEnd, m_hrStatus, m_cacheID, m_ulTotalRecords, 
							m_ulRecordSize, m_bOverflow ? 1 : 0 );
				break;
			default:
				THROW_RUNTIME_EXCEPTION( EMS_GWAY_UNKNOWN_RESPONSE );
				break;
		}

		pCmdSrc = _GetCommandSource();

		if( !pCmdSrc )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		unsigned long ulLen = _tcslen( szCmd ) + 1;

		unsigned long ulWritten = 0;
		EMS_RESULT hr = pCmdSrc->Write( LUT_GATEWAY_COMMANDS, (const unsigned char*) szCmd, 
										ulLen, &ulWritten );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		if( ulWritten < ulLen )
		{
			THROW_IO_EXCEPTION();
		}

		pCmdSrc->Release();
		pCmdSrc = 0;

		delete[] szCmd;
		szCmd = 0;
		
	}
	catch( ... )
	{
		if( szCmd )
		{
			delete[] szCmd;
			szCmd = 0;
		}

		if( pCmdSrc )
		{
			pCmdSrc->Release();
			pCmdSrc = 0;
		}

		throw;
	}
}
		
void 
CEMSGatewayCmd::DeserializeResponse( CEMSCommandProcessor* pCmdProcessor )
{
	if( !pCmdProcessor )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	// Parse it
	pCmdProcessor->ParseCommand();
	pCmdProcessor->GetCmdLine();

	if( pCmdProcessor->IsCommand( TEXT("LPCInitDataEnd") ) )
	{
		m_eRespType = GTWY_RESP_LPC_INIT_DATA_DONE;

		m_ulSessionID = pCmdProcessor->LongParam( TEXT("session") );

		m_hrStatus = pCmdProcessor->LongParam( TEXT("status") );
	}
	else if( pCmdProcessor->IsCommand( TEXT("LPCProcess406DataEnd") ) )
	{
		m_eRespType = GTWY_RESP_LPC_PROCESS406_DATA_DONE;

		m_hrStatus = pCmdProcessor->LongParam( TEXT("status") );
	}
	else if( pCmdProcessor->IsCommand( TEXT("LPCGetFilenamesDataEnd") ) )
	{
		m_eRespType = GTWY_RESP_LPC_GET_FILENAMES_DONE;

		m_hrStatus = pCmdProcessor->LongParam( TEXT("status") );
	}
	else if( pCmdProcessor->IsCommand( TEXT("DataEnd") ) )
	{
		m_eRespType = GTWY_RESP_GENERIC;

		m_hrStatus = pCmdProcessor->LongParam( TEXT("status") );
	}
	else if( pCmdProcessor->IsCommand( TEXT("DALGetEnd") ) )
	{
		m_eRespType = GTWY_RESP_DAL_GET;

		m_hrStatus = pCmdProcessor->LongParam( TEXT("status") );

		m_cacheID = pCmdProcessor->LongParam( TEXT("cache") );

		m_ulTotalRecords = pCmdProcessor->LongParam( TEXT("total") );

		m_ulRecordSize = pCmdProcessor->LongParam( TEXT("size") );

		m_bOverflow = ( 1 == pCmdProcessor->LongParam( TEXT("overflow") ) ) ? true : false;
	}
}

CEMSCommandSource*
CEMSGatewayCmd::_GetCommandSource()
{
	CEMSCommandSource*	pCmdSrc = 0;
	IEMSCommandChannel* pCmdChannel = 0;

	try
	{
		if( !m_pCmdSrc )
		{
			// Source for commands to be sent to the Gateway
			m_pCmdSrc = new CEMSCommandSource( 0, EMS_PIPE_MAX_COMMAND_LENGTH );
			
			if ( !m_pCmdSrc ) 
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			pCmdChannel = _GetCommandChannel();

			if( !pCmdChannel )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			EMS_RESULT hr = pCmdChannel->RegisterSource( m_pCmdSrc );
			
			if ( FAILED(hr) )
			{
				THROW_RUNTIME_EXCEPTION( hr );
			}

			pCmdChannel->Release();
			pCmdChannel = 0;
		}

		pCmdSrc = m_pCmdSrc;
		pCmdSrc->AddRef();
	}
	catch( ... )
	{
		if( pCmdChannel )
		{
			if( m_pCmdSrc )
			{
				pCmdChannel->UnRegisterSource( m_pCmdSrc );
			}

			pCmdChannel->Release();
			pCmdChannel = 0;
		}

		if( m_pCmdSrc )
		{
			m_pCmdSrc->Release();
			m_pCmdSrc = 0;
		}

		if( pCmdSrc )
		{
			pCmdSrc->Release();
			pCmdSrc = 0;
		}

		throw;
	}

	return pCmdSrc;

}

IEMSCommandChannel*	
CEMSGatewayCmd::_GetCommandChannel()
{
	IEMSCommandChannel* pCmdChannel = 0;

	try
	{
		if( !m_pCmdChannel )
		{
			// Command pipeline
			EMS_RESULT hr = CoCreateInstance( CLSID_EMSDataPipeline, 0, CLSCTX_LOCAL_SERVER,
								IID_IEMSCommandChannel, (LPVOID*)&m_pCmdChannel );
			if ( FAILED(hr) )
			{
				THROW_RUNTIME_EXCEPTION( hr );
			}
		}


		pCmdChannel = m_pCmdChannel;
		pCmdChannel->AddRef();
	}
	catch( ... )
	{
		if( m_pCmdChannel )
		{
			m_pCmdChannel->Release();
			m_pCmdChannel = 0;
		}

		if( pCmdChannel )
		{
			pCmdChannel->Release();
			pCmdChannel = 0;
		}

		throw;
	}

	return pCmdChannel;
}