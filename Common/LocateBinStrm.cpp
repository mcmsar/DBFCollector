
#include "igateway.h"
#include "aobjbase.h"
#include "emsmstrm.h"
#include "imsgbody.h"
#include "binmsgbody.h"
#include "locatebinstrm.h"

#include "emserror.h"
#include "emsexcpt.h"

CEMSLocateBinStrm::CEMSLocateBinStrm()
{
}

CEMSLocateBinStrm::CEMSLocateBinStrm( const CEMSLocateBinStrm& locStrm )
{
}

CEMSLocateBinStrm::~CEMSLocateBinStrm()
{
}

EMSVARIANTRECORD*
CEMSLocateBinStrm::ReadNext( )
{
	EMSVARIANTRECORD* pRecord = NULL;

	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		EMSLOCATE locate;
		memset( &locate, 0, sizeof(EMSLOCATE) );

		unsigned long ulRead = 0;
		EMS_RESULT hr = m_pStrm->Read( (unsigned char*) &locate, sizeof(EMSLOCATE), &ulRead );

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
		    pRecord->eType = EMSRT_LOCATE;
		    memcpy( &(pRecord->data.locate), &locate, sizeof(EMSLOCATE) );
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
CEMSLocateBinStrm::WriteRecord( const EMSVARIANTRECORD& record )
{
	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	unsigned long ulWritten = 0;
	EMS_RESULT hr = m_pStrm->Write( (unsigned char*) &(record.data.locate), sizeof(EMSLOCATE), &ulWritten );

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION( hr );
	}
}

EMSVARIANTRECORD2*
CEMSLocateBinStrm::ReadNext2( )
{
	EMSVARIANTRECORD2* pRecord = NULL;

	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		EMSLOCATE locate;
		memset( &locate, 0, sizeof(EMSLOCATE) );

		unsigned long ulRead = 0;
		EMS_RESULT hr = m_pStrm->Read( (unsigned char*) &locate, sizeof(EMSLOCATE), &ulRead );

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
		    pRecord->eType = EMSRT_LOCATE;
		    memcpy( &(pRecord->data.locate), &locate, sizeof(EMSLOCATE) );
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
CEMSLocateBinStrm::WriteRecord2( const EMSVARIANTRECORD2& record )
{
	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	unsigned long ulWritten = 0;
	EMS_RESULT hr = m_pStrm->Write( (unsigned char*) &(record.data.locate), sizeof(EMSLOCATE), &ulWritten );

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION( hr );
	}
}