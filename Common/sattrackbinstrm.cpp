#include "igateway.h"
#include "aobjbase.h"
#include "emsmstrm.h"
#include "imsgbody.h"
#include "binmsgbody.h"
#include "sattrackbinstrm.h"

#include "emserror.h"
#include "emsexcpt.h"

CEMSSatTrackBinStrm::CEMSSatTrackBinStrm()
{
}

CEMSSatTrackBinStrm::CEMSSatTrackBinStrm( const CEMSSatTrackBinStrm& sattrackStrm )
{
}

CEMSSatTrackBinStrm::~CEMSSatTrackBinStrm()
{
}

EMSVARIANTRECORD*
CEMSSatTrackBinStrm::ReadNext()
{
	EMSVARIANTRECORD* pRecord = 0;

	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		
		EMSSATTRACKRECORD sattrack;
		memset( &sattrack, 0, sizeof(EMSSATTRACKRECORD) );

		unsigned long ulRead = 0;
		EMS_RESULT hr = m_pStrm->Read( (unsigned char*) &sattrack, sizeof(EMSSATTRACKRECORD), &ulRead );

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

		    pRecord->eType = EMSRT_SAT_TRACK;
		    memcpy( &(pRecord->data.satTrack), &sattrack, sizeof(EMSSATTRACKRECORD) );
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
CEMSSatTrackBinStrm::WriteRecord( const EMSVARIANTRECORD& record )
{
	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	unsigned long ulWritten = 0;
	EMS_RESULT hr = m_pStrm->Write( (unsigned char*) &(record.data.satTrack), sizeof(EMSSATTRACKRECORD), &ulWritten );

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION( hr );
	}
}

EMSVARIANTRECORD2*
CEMSSatTrackBinStrm::ReadNext2()
{
	EMSVARIANTRECORD2* pRecord = 0;

	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		
		EMSSATTRACKRECORD sattrack;
		memset( &sattrack, 0, sizeof(EMSSATTRACKRECORD) );

		unsigned long ulRead = 0;
		EMS_RESULT hr = m_pStrm->Read( (unsigned char*) &sattrack, sizeof(EMSSATTRACKRECORD), &ulRead );

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

		    pRecord->eType = EMSRT_SAT_TRACK;
		    memcpy( &(pRecord->data.satTrack), &sattrack, sizeof(EMSSATTRACKRECORD) );
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
CEMSSatTrackBinStrm::WriteRecord2( const EMSVARIANTRECORD2& record )
{
	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	unsigned long ulWritten = 0;
	EMS_RESULT hr = m_pStrm->Write( (unsigned char*) &(record.data.satTrack), sizeof(EMSSATTRACKRECORD), &ulWritten );

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION( hr );
	}
}