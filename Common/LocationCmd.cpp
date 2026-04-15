
#include "locationcmd.h"

#include "emserror.h"
#include "emsexcpt.h"
#include "commandformats.h"
#include "pksink.h"
#include "convutility.h"

// Default to LEO_ONLY
CEMSLocationCmd::CEMSLocationCmd() :	m_ulKeyCount(0), 
										m_eType(LOCCMD_UNKNOWN), 
										m_eProcessingMode(EMS_MANUAL_MODE_LEO_ONLY)
{
}

CEMSLocationCmd::CEMSLocationCmd( const CEMSLocationCmd& x ) :  
										m_ulKeyCount(0), 
										m_eType(LOCCMD_UNKNOWN), 
										m_eProcessingMode(EMS_MANUAL_MODE_UNKNOWN)
{
	m_eType = x.m_eType;
	m_ulSessionID = x.m_ulSessionID;
	m_ulKeyCount = x.m_ulKeyCount;
	m_eProcessingMode = x.m_eProcessingMode;

	if( !x.m_wszWhereKeys.empty() )
	{
		SetWhereClause( x.m_wszWhereKeys.c_str() );
	}

	if( !x.m_wszControlFile.empty() )
	{
		SetControlFile( x.m_wszControlFile.c_str() );
	}
}

CEMSLocationCmd::~CEMSLocationCmd()
{
}

void
CEMSLocationCmd::SetKeys( const unsigned long culKeys, const unsigned long* caulKeys )
{
	string	szKeyList;

	if( !caulKeys )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	m_ulKeyCount = culKeys;

	for( unsigned long li = 0; li < culKeys; li++ )
	{
		if( 0 != li )
		{
			m_wszWhereKeys.append( L"," );
		}

		// No longer than 16 digit key
		wchar_t wszKey[ 16 ];
		memset( wszKey, 0, 16*sizeof(wchar_t) );
		_ltow( caulKeys[li], wszKey, 10 );

		m_wszWhereKeys.append( wszKey );
	}
}

void 
CEMSLocationCmd::GetKeys( unsigned long& ulKeys, unsigned long*& aulKeys ) const
{
	aulKeys = 0;
	ulKeys = 0;

	if( m_ulKeyCount > 0 )
	{
		aulKeys = new unsigned long[ m_ulKeyCount ];
		if( !aulKeys )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		long		lLen = wcslen(m_wszWhereKeys.c_str());
		wchar_t*	wszTmp = new wchar_t[lLen+1];
		if( !wszTmp )
		{
			THROW_NOMEMORY_EXCEPTION();
		}
		wcsncpy( wszTmp, m_wszWhereKeys.c_str(), lLen );

		wchar_t		seps[]   = L",";
		wchar_t*	token = wcstok( wszTmp, seps );
		int			ik=0;
		while( token != NULL )
		{
			// Save this one
			aulKeys[ik] = _wtol( token );
			ik++;
			// and get the next
			token = wcstok( NULL, seps );
		}
		if ( ik != m_ulKeyCount )
		{
			// mismatched arguments!!
			delete[] aulKeys;
			aulKeys = NULL;
			THROW_RUNTIME_EXCEPTION( EMS_BAD_PARAM );
		}

		ulKeys = m_ulKeyCount;
	}
}


EMSLOCATECOMMANDSTRUCTURE 
CEMSLocationCmd::Serialize( const EMSLOCATECOMMAND ceCmdType )
{

	EMSLOCATECOMMANDSTRUCTURE cmd;
	memset( &cmd, 0, sizeof(EMSLOCATECOMMANDSTRUCTURE) );

	cmd.eType = m_eType = ceCmdType;

	switch( ceCmdType )
	{
		case LOCCMD_INIT:
			{
				if( m_wszWhereKeys.empty() )
				{
					// missing parameter! aaa
					THROW_NULL_POINTER_EXCEPTION();
				}
				wcsncpy( cmd.wszWhereKeys, m_wszWhereKeys.c_str(), MAX_WHEREKEYS_LEN );
				cmd.eProcessingMode = m_eProcessingMode;
			}
			break;
		case LOCCMD_REMOVE:
			{
				if( m_wszWhereKeys.empty() )
				{
					// missing parameter! aaa
					THROW_NULL_POINTER_EXCEPTION();
				}
				cmd.ulSessionID = m_ulSessionID;
				cmd.ulKeyCount = m_ulKeyCount;
				wcsncpy( cmd.wszWhereKeys, m_wszWhereKeys.c_str(), MAX_WHEREKEYS_LEN );
			}
			break;
		case LOCCMD_PROCESS:
			{
				cmd.ulSessionID = m_ulSessionID;
				if( m_wszControlFile.empty() )
				{
					// missing parameter! aaa
					THROW_NULL_POINTER_EXCEPTION();
				}
				wcsncpy( cmd.wszControlFile, m_wszControlFile.c_str(), MAX_CONTROLFILE_LEN );
			}
			break;
		case LOCCMD_CANCEL:
			{
				cmd.ulSessionID = m_ulSessionID;
			}
			break;
		case LOCCMD_GET_CONTROL_FILENAMES:
			{
				// no parameters
			}
			break;
		default:
			THROW_RUNTIME_EXCEPTION( EMS_INVALID_CMD ); 
	}
	return cmd;
}

void 
CEMSLocationCmd::Deserialize( CEMSPacketSink* pCmdDataSink )
{
	if( !pCmdDataSink )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	EMSLOCATECOMMANDSTRUCTURE  cmd;
	memset( &cmd, 0, sizeof( EMSLOCATECOMMANDSTRUCTURE  ) );

	unsigned long ulRead = 0;
	EMS_RESULT	hr = pCmdDataSink->Read( (LPBYTE) &cmd, sizeof(EMSLOCATECOMMANDSTRUCTURE), &ulRead );
	if ( FAILED(hr) ) THROW_RUNTIME_EXCEPTION(hr);


	// Copy values into our member variables
	m_wszWhereKeys = cmd.wszWhereKeys;
	m_eProcessingMode = cmd.eProcessingMode;
	m_ulSessionID = cmd.ulSessionID;
	m_eType = cmd.eType;
	m_ulKeyCount = cmd.ulKeyCount;
	m_wszControlFile = cmd.wszControlFile;

}

