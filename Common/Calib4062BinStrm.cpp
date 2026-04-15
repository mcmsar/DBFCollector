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

	$Log:
	$
********************************************************************/

#include "igateway.h"
#include "aobjbase.h"
#include "emsmstrm.h"
#include "imsgbody.h"
#include "binmsgbody.h"
#include "calib4062binstrm.h"

#include "emserror.h"
#include "emsexcpt.h"

CEMSCalib4062BinStrm::CEMSCalib4062BinStrm()
{
}

CEMSCalib4062BinStrm::CEMSCalib4062BinStrm( const CEMSCalib4062BinStrm& calib406Strm )
{
}

CEMSCalib4062BinStrm::~CEMSCalib4062BinStrm()
{
}

EMSVARIANTRECORD*
CEMSCalib4062BinStrm::ReadNext()
{
	THROW_RUNTIME_EXCEPTION( EMS_UNSUPPORTED );
}

void
CEMSCalib4062BinStrm::WriteRecord( const EMSVARIANTRECORD& record )
{
	THROW_RUNTIME_EXCEPTION( EMS_UNSUPPORTED );
}

EMSVARIANTRECORD2*
CEMSCalib4062BinStrm::ReadNext2()
{
	EMSVARIANTRECORD2* pRecord = 0;

	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		
		EMSCALIB406DATA2 beacon;
		memset( &beacon, 0, sizeof(EMSCALIB406DATA2) );

		unsigned long ulRead = 0;
		EMS_RESULT hr = m_pStrm->Read( (unsigned char*) &beacon, sizeof(EMSCALIB406DATA2), &ulRead );

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

		    pRecord->eType = EMSRT_CALIB406_2;
		    memcpy( &(pRecord->data.calib406_2), &beacon, sizeof(EMSCALIB406DATA2) );
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
CEMSCalib4062BinStrm::WriteRecord2( const EMSVARIANTRECORD2& record )
{
	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	unsigned long ulWritten = 0;
	EMS_RESULT hr = m_pStrm->Write( (unsigned char*) &(record.data.calib406_2), sizeof(EMSCALIB406DATA2), &ulWritten );

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION( hr );
	}
}
