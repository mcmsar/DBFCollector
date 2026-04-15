#include "igateway.h"
#include "aobjbase.h"
#include "emsmstrm.h"
#include "imsgbody.h"
#include "binmsgbody.h"
#include "sarpcalibbinstrm.h"

#include "emserror.h"
#include "emsexcpt.h"

CEMSSarpCalibBinStrm::CEMSSarpCalibBinStrm()
{
}

CEMSSarpCalibBinStrm::CEMSSarpCalibBinStrm( const CEMSSarpCalibBinStrm& sarpcalibStrm )
{
}

CEMSSarpCalibBinStrm::~CEMSSarpCalibBinStrm()
{
}

EMSVARIANTRECORD*
CEMSSarpCalibBinStrm::ReadNext()
{
	EMSVARIANTRECORD* pRecord = 0;

	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		
		EMSSARPCALIBDATA sarpcalib;
		memset( &sarpcalib, 0, sizeof(EMSSARPCALIBDATA) );

		unsigned long ulRead = 0;
		EMS_RESULT hr = m_pStrm->Read( (unsigned char*) &sarpcalib, sizeof(EMSSARPCALIBDATA), &ulRead );

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

		    pRecord->eType = EMSRT_SARP_CALIB;
		    memcpy( &(pRecord->data.sarpcalib), &sarpcalib, sizeof(EMSSARPCALIBDATA) );
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
CEMSSarpCalibBinStrm::WriteRecord( const EMSVARIANTRECORD& record )
{
	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	unsigned long ulWritten = 0;
	EMS_RESULT hr = m_pStrm->Write( (unsigned char*) &(record.data.sarpcalib), sizeof(EMSSARPCALIBDATA), &ulWritten );

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION( hr );
	}
}

EMSVARIANTRECORD2*
CEMSSarpCalibBinStrm::ReadNext2()
{
	EMSVARIANTRECORD2* pRecord = 0;

	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		
		EMSSARPCALIBDATA sarpcalib;
		memset( &sarpcalib, 0, sizeof(EMSSARPCALIBDATA) );

		unsigned long ulRead = 0;
		EMS_RESULT hr = m_pStrm->Read( (unsigned char*) &sarpcalib, sizeof(EMSSARPCALIBDATA), &ulRead );

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

		    pRecord->eType = EMSRT_SARP_CALIB;
		    memcpy( &(pRecord->data.sarpcalib), &sarpcalib, sizeof(EMSSARPCALIBDATA) );
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
CEMSSarpCalibBinStrm::WriteRecord2( const EMSVARIANTRECORD2& record )
{
	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	unsigned long ulWritten = 0;
	EMS_RESULT hr = m_pStrm->Write( (unsigned char*) &(record.data.sarpcalib), sizeof(EMSSARPCALIBDATA), &ulWritten );

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION( hr );
	}
}