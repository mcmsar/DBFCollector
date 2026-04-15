#include "igateway.h"
#include "aobjbase.h"
#include "emsmstrm.h"
#include "imsgbody.h"
#include "binmsgbody.h"
#include "configpacketbinstrm.h"

#include "emserror.h"
#include "emsexcpt.h"

CEMSConfigPacketBinStrm::CEMSConfigPacketBinStrm()
{
}

CEMSConfigPacketBinStrm::CEMSConfigPacketBinStrm( const CEMSConfigPacketBinStrm& configPktStrm )
{
}

CEMSConfigPacketBinStrm::~CEMSConfigPacketBinStrm()
{
}

EMSVARIANTRECORD*
CEMSConfigPacketBinStrm::ReadNext()

{
	THROW_RUNTIME_EXCEPTION( EMS_UNSUPPORTED );
}

void
CEMSConfigPacketBinStrm::WriteRecord( const EMSVARIANTRECORD& record )
{
	THROW_RUNTIME_EXCEPTION( EMS_UNSUPPORTED );
}

EMSVARIANTRECORD2*
CEMSConfigPacketBinStrm::ReadNext2()
{
	EMSVARIANTRECORD2* pRecord = 0;

	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		
		EMSCONFIGPACKET config;
		memset( &config, 0, sizeof(config) );

		unsigned long ulRead = 0;
		EMS_RESULT hr = m_pStrm->Read( (unsigned char*) &config, sizeof(config), &ulRead );

        if( EMS_EOF == hr )
        {
        }
        else if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}
        else
        {
		    pRecord = new EMSVARIANTRECORD2;

		    if( !pRecord )
		    {
			    THROW_NOMEMORY_EXCEPTION();
		    }

		    pRecord->eType = EMSRT_CONFIGPACKET;
		    pRecord->data.configPacket = config;
        }
	}
	catch( ... )
	{
		if( pRecord )
		{
			delete pRecord;
			pRecord = 0;
		}

		throw;
	}

	return pRecord;
}

void
CEMSConfigPacketBinStrm::WriteRecord2( const EMSVARIANTRECORD2& record )
{
	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	unsigned long ulWritten = 0;
	EMS_RESULT hr = m_pStrm->Write( (unsigned char*) &(record.data.configPacket), sizeof(record.data.configPacket), &ulWritten );

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION( hr );
	}
}
