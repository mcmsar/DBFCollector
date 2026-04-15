#include "igateway.h"
#include "aobjbase.h"
#include "emsmstrm.h"
#include "imsgbody.h"
#include "binmsgbody.h"
#include "sarrextbinstrm.h"

#include "emserror.h"
#include "emsexcpt.h"

CEMSSarrExtBinStrm::CEMSSarrExtBinStrm()
{
}

CEMSSarrExtBinStrm::CEMSSarrExtBinStrm( const CEMSSarrExtBinStrm& sarrStrm )
{
}

CEMSSarrExtBinStrm::~CEMSSarrExtBinStrm()
{
}

EMSVARIANTRECORD*
CEMSSarrExtBinStrm::ReadNext()
{
	throw CEMSException( EMS_NOT_IMPLEMENTED );
}

void
CEMSSarrExtBinStrm::WriteRecord( const EMSVARIANTRECORD& record )
{
	throw CEMSException( EMS_NOT_IMPLEMENTED );
}

EMSVARIANTRECORD2*
CEMSSarrExtBinStrm::ReadNext2()
{
	EMSVARIANTRECORD2* pRecord = 0;

	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		
		EMSSARRDATAEX sarr;
		memset( &sarr, 0, sizeof(EMSSARRDATAEX) );

		unsigned long ulRead = 0;
		EMS_RESULT hr = m_pStrm->Read( (unsigned char*) &sarr, sizeof(EMSSARRDATAEX), &ulRead );

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

		    pRecord->eType = EMSRT_SARR_EXT;
		    memcpy( &(pRecord->data.sarrext), &sarr, sizeof(EMSSARRDATAEX) );
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
CEMSSarrExtBinStrm::WriteRecord2( const EMSVARIANTRECORD2& record )
{
	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	unsigned long ulWritten = 0;
	EMS_RESULT hr = m_pStrm->Write( (unsigned char*) &(record.data.sarrext), sizeof(EMSSARRDATAEX), &ulWritten );

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION( hr );
	}
}