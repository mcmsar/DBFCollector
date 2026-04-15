
#include "igateway.h"
#include "aobjbase.h"
#include "emsmstrm.h"
#include "imsgbody.h"
#include "binmsgbody.h"
#include "AudioRiffbinstrm.h"

#include "emserror.h"
#include "emsexcpt.h"

CEMSAudioRiffBinStrm::CEMSAudioRiffBinStrm()
{
}

CEMSAudioRiffBinStrm::CEMSAudioRiffBinStrm( const CEMSAudioRiffBinStrm& audioRiffStrm )
{
}

CEMSAudioRiffBinStrm::~CEMSAudioRiffBinStrm()
{
}

EMSVARIANTRECORD*
CEMSAudioRiffBinStrm::ReadNext()
{
	EMSVARIANTRECORD* pRecord = 0;

	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		
		EMSAUDIODATARECORD_RIFF audioriff;
		memset( &audioriff, 0, sizeof(EMSAUDIODATARECORD_RIFF) );

		unsigned long ulRead = 0;
		EMS_RESULT hr = m_pStrm->Read( (unsigned char*) &audioriff, sizeof(EMSAUDIODATARECORD_RIFF), &ulRead );

        if( EMS_EOF == hr )
        {
        }
        else if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}
        else
        {
		    pRecord = new EMSVARIANTRECORD;

		    if( !pRecord )
		    {
			    THROW_NOMEMORY_EXCEPTION();
		    }

		    pRecord->eType = EMSRT_AUDIO;
		    memcpy( &(pRecord->data.audio), &audioriff, sizeof(EMSAUDIODATARECORD_RIFF) );
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
CEMSAudioRiffBinStrm::WriteRecord( const EMSVARIANTRECORD& record )
{
	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	unsigned long ulWritten = 0;
	EMS_RESULT hr = m_pStrm->Write( (unsigned char*) &(record.data.audio), sizeof(EMSAUDIODATARECORD_RIFF), &ulWritten );

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION( hr );
	}
}

EMSVARIANTRECORD2* 
CEMSAudioRiffBinStrm::ReadNext2()
{
	EMSVARIANTRECORD2* pRecord = 0;

	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		
		EMSAUDIODATARECORD_RIFF audioriff;
		memset( &audioriff, 0, sizeof(EMSAUDIODATARECORD_RIFF) );

		unsigned long ulRead = 0;
		EMS_RESULT hr = m_pStrm->Read( (unsigned char*) &audioriff, sizeof(EMSAUDIODATARECORD_RIFF), &ulRead );

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

		    pRecord->eType = EMSRT_AUDIO;
		    memcpy( &(pRecord->data.audio), &audioriff, sizeof(EMSAUDIODATARECORD_RIFF) );
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
CEMSAudioRiffBinStrm::WriteRecord2( const EMSVARIANTRECORD2& record )
{
	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	unsigned long ulWritten = 0;
	EMS_RESULT hr = m_pStrm->Write( (unsigned char*) &(record.data.audio), sizeof(EMSAUDIODATARECORD_RIFF), &ulWritten );

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION( hr );
	}
}