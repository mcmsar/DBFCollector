#include "igateway.h"
#include "aobjbase.h"
#include "emsmstrm.h"
#include "imsgbody.h"
#include "binmsgbody.h"
#include "residualbinstrm.h"

#include "emserror.h"
#include "emsexcpt.h"

CEMSResidualBinStrm::CEMSResidualBinStrm()
{
}

CEMSResidualBinStrm::CEMSResidualBinStrm( const CEMSResidualBinStrm& residualStrm )
{
}

CEMSResidualBinStrm::~CEMSResidualBinStrm()
{
}

EMSVARIANTRECORD*
CEMSResidualBinStrm::ReadNext()
{
	EMSVARIANTRECORD* pRecord = 0;

	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		
		EMSRESIDUALDATA residual;
		memset( &residual, 0, sizeof(EMSRESIDUALDATA) );

		unsigned long ulRead = 0;
		EMS_RESULT hr = m_pStrm->Read( (unsigned char*) &residual, sizeof(EMSRESIDUALDATA), &ulRead );

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

		    pRecord->eType = EMSRT_RESIDUAL;
		    memcpy( &(pRecord->data.residual), &residual, sizeof(EMSRESIDUALDATA) );
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
CEMSResidualBinStrm::WriteRecord( const EMSVARIANTRECORD& record )
{
	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	unsigned long ulWritten = 0;
	EMS_RESULT hr = m_pStrm->Write( (unsigned char*) &(record.data.residual), sizeof(EMSRESIDUALDATA), &ulWritten );

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION( hr );
	}
}

EMSVARIANTRECORD2*
CEMSResidualBinStrm::ReadNext2()
{
	EMSVARIANTRECORD2* pRecord = 0;

	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		
		EMSRESIDUALDATA residual;
		memset( &residual, 0, sizeof(EMSRESIDUALDATA) );

		unsigned long ulRead = 0;
		EMS_RESULT hr = m_pStrm->Read( (unsigned char*) &residual, sizeof(EMSRESIDUALDATA), &ulRead );

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

		    pRecord->eType = EMSRT_RESIDUAL;
		    memcpy( &(pRecord->data.residual), &residual, sizeof(EMSRESIDUALDATA) );
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
CEMSResidualBinStrm::WriteRecord2( const EMSVARIANTRECORD2& record )
{
	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	unsigned long ulWritten = 0;
	EMS_RESULT hr = m_pStrm->Write( (unsigned char*) &(record.data.residual), sizeof(EMSRESIDUALDATA), &ulWritten );

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION( hr );
	}
}