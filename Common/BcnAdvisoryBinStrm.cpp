/*********************************************************************
*	              Copyright (c) 2010 by EMS Technologies, Inc.,
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
#include "bcnadvisorybinstrm.h"

#include "emserror.h"
#include "emsexcpt.h"

CEMSBcnAdvisoryBinStrm::CEMSBcnAdvisoryBinStrm()
{
}

CEMSBcnAdvisoryBinStrm::CEMSBcnAdvisoryBinStrm( const CEMSBcnAdvisoryBinStrm& bcnAdvStrm )
{
}

CEMSBcnAdvisoryBinStrm::~CEMSBcnAdvisoryBinStrm()
{
}

EMSVARIANTRECORD*
CEMSBcnAdvisoryBinStrm::ReadNext()
{
	THROW_RUNTIME_EXCEPTION( EMS_UNSUPPORTED );
}

void
CEMSBcnAdvisoryBinStrm::WriteRecord( const EMSVARIANTRECORD& record )
{
	THROW_RUNTIME_EXCEPTION( EMS_UNSUPPORTED );
}

EMSVARIANTRECORD2*
CEMSBcnAdvisoryBinStrm::ReadNext2()
{
	THROW_RUNTIME_EXCEPTION( EMS_UNSUPPORTED );
}

void
CEMSBcnAdvisoryBinStrm::WriteRecord2( const EMSVARIANTRECORD2& record )
{
	THROW_RUNTIME_EXCEPTION( EMS_UNSUPPORTED );
}

EMSVARIANTRECORD3*
CEMSBcnAdvisoryBinStrm::ReadNext3()
{
	EMSVARIANTRECORD3* pRecord = 0;

	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	try
	{
		
		EMS_BEACON_ADVISORY beaconAdvisory;
		memset( &beaconAdvisory, 0, sizeof(EMS_BEACON_ADVISORY) );

		unsigned long ulRead = 0;
		EMS_RESULT hr = m_pStrm->Read( (unsigned char*) &beaconAdvisory, sizeof(EMS_BEACON_ADVISORY), &ulRead );

        if( EMS_EOF == hr )
        {
        }
        else if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}
        else
        {
		    pRecord = new EMSVARIANTRECORD3;

		    if( !pRecord )
		    {
			    THROW_NOMEMORY_EXCEPTION();
		    }

		    pRecord->eType = EMSRT_BEACON_ADVISORY;
		    memcpy( &(pRecord->data.beaconadvisory), &beaconAdvisory, sizeof(EMS_BEACON_ADVISORY) );
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
CEMSBcnAdvisoryBinStrm::WriteRecord3( const EMSVARIANTRECORD3& record )
{
	if( !m_pStrm )
	{
		THROW_RUNTIME_EXCEPTION( EMS_NOT_INITIALIZED );
	}

	unsigned long ulWritten = 0;
	EMS_RESULT hr = m_pStrm->Write( (unsigned char*) &(record.data.beaconadvisory), sizeof(EMS_BEACON_ADVISORY), &ulWritten );

	if( FAILED(hr) )
	{
		THROW_RUNTIME_EXCEPTION( hr );
	}
}
