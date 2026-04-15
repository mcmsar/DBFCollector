#include "igateway.h"
#include "aobjbase.h"
#include "emsmstrm.h"
#include "imsgbody.h"
#include "binmsgbody.h"
#include "calibcbcbinstrm.h"

#include "emserror.h"
#include "emsexcpt.h"

CEMSCalibCBCBinStrm::CEMSCalibCBCBinStrm()
{
}

CEMSCalibCBCBinStrm::CEMSCalibCBCBinStrm( const CEMSCalibCBCBinStrm& calibcbcStrm )
{
}

CEMSCalibCBCBinStrm::~CEMSCalibCBCBinStrm()
{
}

EMSVARIANTRECORD*
CEMSCalibCBCBinStrm::ReadNext()
{
	EMSVARIANTRECORD* pRecord = 0;

	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		
		EMSCBCOUTPUTDATA calibCBC;
		memset( &calibCBC, 0, sizeof(EMSCBCOUTPUTDATA) );

		unsigned long ulRead = 0;
		EMS_RESULT hr = m_pStrm->Read( (unsigned char*) &calibCBC, sizeof(EMSCBCOUTPUTDATA), &ulRead );

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

		    pRecord->eType = EMSRT_CALIBCBC;
		    memcpy( &(pRecord->data.calibCBC), &calibCBC, sizeof(EMSCBCOUTPUTDATA) );
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
CEMSCalibCBCBinStrm::WriteRecord( const EMSVARIANTRECORD& record )
{
	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	unsigned long ulWritten = 0;
	EMS_RESULT hr = m_pStrm->Write( (unsigned char*) &(record.data.calibCBC), sizeof(EMSCBCOUTPUTDATA), &ulWritten );

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION( hr );
	}
}

EMSVARIANTRECORD2*
CEMSCalibCBCBinStrm::ReadNext2()
{
	EMSVARIANTRECORD2* pRecord = 0;

	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		
		EMSCBCOUTPUTDATA calibCBC;
		memset( &calibCBC, 0, sizeof(EMSCBCOUTPUTDATA) );

		unsigned long ulRead = 0;
		EMS_RESULT hr = m_pStrm->Read( (unsigned char*) &calibCBC, sizeof(EMSCBCOUTPUTDATA), &ulRead );

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

		    pRecord->eType = EMSRT_CALIBCBC;
		    memcpy( &(pRecord->data.calibCBC), &calibCBC, sizeof(EMSCBCOUTPUTDATA) );
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
CEMSCalibCBCBinStrm::WriteRecord2( const EMSVARIANTRECORD2& record )
{
	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	unsigned long ulWritten = 0;
	EMS_RESULT hr = m_pStrm->Write( (unsigned char*) &(record.data.calibCBC), sizeof(EMSCBCOUTPUTDATA), &ulWritten );

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION( hr );
	}
}