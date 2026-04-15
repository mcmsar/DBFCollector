#include "igateway.h"
#include "aobjbase.h"
#include "emsmstrm.h"
#include "imsgbody.h"
#include "binmsgbody.h"
#include "tlebinstrm.h"

#include "emserror.h"
#include "emsexcpt.h"

CEMSTLEBinStrm::CEMSTLEBinStrm()
{
}

CEMSTLEBinStrm::CEMSTLEBinStrm( const CEMSTLEBinStrm& tleStrm )
{
}

CEMSTLEBinStrm::~CEMSTLEBinStrm()
{
}

EMSVARIANTRECORD*
CEMSTLEBinStrm::ReadNext()
{
	EMSVARIANTRECORD* pRecord = 0;

	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		
		EMSTLERECORD tle;
		memset( &tle, 0, sizeof(EMSTLERECORD) );

		unsigned long ulRead = 0;
		EMS_RESULT hr = m_pStrm->Read( (unsigned char*) &tle, sizeof(EMSTLERECORD), &ulRead );

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

		    pRecord->eType = EMSRT_ORBIT;
		    memcpy( &(pRecord->data.tle), &tle, sizeof(EMSTLERECORD) );
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
CEMSTLEBinStrm::WriteRecord( const EMSVARIANTRECORD& record )
{
	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	unsigned long ulWritten = 0;
	EMS_RESULT hr = m_pStrm->Write( (unsigned char*) &(record.data.tle), sizeof(EMSTLERECORD), &ulWritten );

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION( hr );
	}
}

EMSVARIANTRECORD2*
CEMSTLEBinStrm::ReadNext2()
{
	EMSVARIANTRECORD2* pRecord = 0;

	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		
		EMSTLERECORD tle;
		memset( &tle, 0, sizeof(EMSTLERECORD) );

		unsigned long ulRead = 0;
		EMS_RESULT hr = m_pStrm->Read( (unsigned char*) &tle, sizeof(EMSTLERECORD), &ulRead );

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

		    pRecord->eType = EMSRT_ORBIT;
		    memcpy( &(pRecord->data.tle), &tle, sizeof(EMSTLERECORD) );
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
CEMSTLEBinStrm::WriteRecord2( const EMSVARIANTRECORD2& record )
{
	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	unsigned long ulWritten = 0;
	EMS_RESULT hr = m_pStrm->Write( (unsigned char*) &(record.data.tle), sizeof(EMSTLERECORD), &ulWritten );

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION( hr );
	}
}