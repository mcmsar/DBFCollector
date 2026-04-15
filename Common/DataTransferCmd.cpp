
#include "datatransfercmd.h"

#include "emserror.h"
#include "emsexcpt.h"
#include "commandformats.h"
#include "pksink.h"
#include "convutility.h"

CEMSDTCmd::CEMSDTCmd() : m_ulUploadTarget(0), m_eRecType(EMSRT_UNKNOWN), m_ulMaxPackageSize(0)
{
}

CEMSDTCmd::CEMSDTCmd( const CEMSDTCmd& x )
{
	m_ulUploadTarget = x.m_ulUploadTarget;

	m_eRecType = x.m_eRecType;

	m_ulMaxPackageSize = x.m_ulMaxPackageSize;

	if( !x.m_wszWhere.empty() )
	{
		SetWhereClause( x.m_wszWhere.c_str() );
	}
}

CEMSDTCmd::~CEMSDTCmd()
{
}


EMSDATATRANSFERCOMMANDSTRUCTURE
CEMSDTCmd::Serialize() const
{
	EMSDATATRANSFERCOMMANDSTRUCTURE cmd;
	memset( &cmd, 0, sizeof(EMSDATATRANSFERCOMMANDSTRUCTURE) );

	cmd.eRecType = m_eRecType;
	cmd.ulMaxPackageSize = m_ulMaxPackageSize;
	cmd.ulUploadTarget = m_ulUploadTarget;
	wcsncpy( cmd.wszWhere, m_wszWhere.c_str(), MAX_XFERWHERE_LEN );

	return cmd;
}

void 
CEMSDTCmd::Deserialize( CEMSPacketSink* pCmdDataSink )
{
	if( !pCmdDataSink )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}
	EMSDATATRANSFERCOMMANDSTRUCTURE cmd;
	memset( &cmd, 0, sizeof(EMSDATATRANSFERCOMMANDSTRUCTURE) );

	unsigned long ulRead = 0;
	EMS_RESULT	hr = pCmdDataSink->Read( (LPBYTE) &cmd, sizeof(EMSDATATRANSFERCOMMANDSTRUCTURE), &ulRead );
	if ( FAILED(hr) ) THROW_RUNTIME_EXCEPTION(hr);

	// Copy values into our member variables
	m_ulUploadTarget = cmd.ulUploadTarget;
	m_eRecType = cmd.eRecType;
	m_ulMaxPackageSize = cmd.ulMaxPackageSize;
	m_wszWhere = cmd.wszWhere;
}