/*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log$
********************************************************************/

#include "igateway.h"
#include "aobjbase.h"
#include "emsmstrm.h"
#include "imsgbody.h"
#include "binmsgbody.h"
#include "calib406exbinstrm.h"

#include "emserror.h"
#include "emsexcpt.h"

CEMSCalib406ExBinStrm::CEMSCalib406ExBinStrm()
{
}

CEMSCalib406ExBinStrm::CEMSCalib406ExBinStrm( const CEMSCalib406ExBinStrm& calib406Strm )
{
}

CEMSCalib406ExBinStrm::~CEMSCalib406ExBinStrm()
{
}

EMSVARIANTRECORD*
CEMSCalib406ExBinStrm::ReadNext()
{
	THROW_RUNTIME_EXCEPTION( EMS_UNSUPPORTED );
}

void
CEMSCalib406ExBinStrm::WriteRecord( const EMSVARIANTRECORD& record )
{
	THROW_RUNTIME_EXCEPTION( EMS_UNSUPPORTED );
}

EMSVARIANTRECORD2*
CEMSCalib406ExBinStrm::ReadNext2()
{
	EMSVARIANTRECORD2* pRecord = 0;

	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		
		EMSCALIB406DATAEXT beacon;
		memset( &beacon, 0, sizeof(EMSCALIB406DATAEXT) );

		unsigned long ulRead = 0;
		EMS_RESULT hr = m_pStrm->Read( (unsigned char*) &beacon, sizeof(EMSCALIB406DATAEXT), &ulRead );

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

		    pRecord->eType = EMSRT_CALIB406_EXT;
		    memcpy( &(pRecord->data.calib406ext), &beacon, sizeof(EMSCALIB406DATAEXT) );
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
CEMSCalib406ExBinStrm::WriteRecord2( const EMSVARIANTRECORD2& record )
{
	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	unsigned long ulWritten = 0;
	EMS_RESULT hr = m_pStrm->Write( (unsigned char*) &(record.data.calib406ext), sizeof(EMSCALIB406DATAEXT), &ulWritten );

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION( hr );
	}
}
