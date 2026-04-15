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

#include "antdspair.h"
#include "emsexcpt.h"
#include "emsclock.h"
#include "fileutility.h"

#include <initguid.h>
#include "emsfstrm.h"


CEMSPairSchedule::CEMSPairSchedule() : m_ulPairID(0), m_ulAntennaID(0), m_ulDSID(0),
										m_ulPasses(0), m_aPasses(NULL)
{
}

CEMSPairSchedule::CEMSPairSchedule( const ULONG culPairID, const ULONG culAntID, const ULONG culDSID,
								   const ULONG culPasses, 
								   const EMSSATTRACKRECORD* caPasses ) : m_ulPairID( culPairID ),
																	m_ulAntennaID( culAntID ),
																	m_ulDSID( culDSID ),
																	m_ulPasses( 0 ),
																	m_aPasses( NULL )
{
	_SetSchedule( culPasses, caPasses );
}

CEMSPairSchedule::CEMSPairSchedule( const CEMSPairSchedule& x ) : m_ulPairID( x.m_ulPairID ),
															m_ulAntennaID( x.m_ulAntennaID ),
															m_ulDSID( x.m_ulDSID ),
															m_ulPasses(0), m_aPasses(NULL)
{
	_SetSchedule( x.m_ulPasses, x.m_aPasses );
}

CEMSPairSchedule::~CEMSPairSchedule()
{
	if( m_aPasses )
	{
		delete[] m_aPasses;
		m_aPasses = NULL;
	}
}

EMSSATTRACKRECORD* 
CEMSPairSchedule::GetPasses() const
{
	EMSSATTRACKRECORD* aRet = NULL;
	
	if( m_ulPasses > 0 &&
		m_aPasses )
	{
		aRet = new EMSSATTRACKRECORD[ m_ulPasses ];

		if( !aRet )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memcpy( aRet, m_aPasses, m_ulPasses*sizeof(EMSSATTRACKRECORD) );
	}

	return aRet;
}

EMSSATTRACKRECORD* 
CEMSPairSchedule::GetCurrentPass() const
{
	EMSSATTRACKRECORD* pRet = NULL;

	if( m_ulPasses > 0 &&
		m_aPasses )
	{
		EMSTIME timeNow = CEMSSystemClock::GetTime();

		// Iterate through the array looking for a pass that has an AOS less than now and an LOS
		// greater than now.
		for( ULONG l = 0; l < m_ulPasses && !pRet; l++ )
		{
			if( m_aPasses[l].track.PassInfo.timeAOS.intTime < timeNow.intTime &&
				m_aPasses[l].track.PassInfo.timeLOS.intTime > timeNow.intTime &&
				(EMS_PASSFLAG_PROCESS == ( EMS_PASSFLAG_PROCESS & m_aPasses[l].track.PassInfo.ulFlags ) ) &&
				!(EMS_PASSFLAG_SKIP == ( EMS_PASSFLAG_SKIP & m_aPasses[l].track.PassInfo.ulFlags ) ) )
			{
				pRet = new EMSSATTRACKRECORD;

				if( !pRet )
				{
					THROW_NOMEMORY_EXCEPTION();
				}

				memcpy( pRet, &m_aPasses[l], sizeof(EMSSATTRACKRECORD) );
			}
		}
	}

	return pRet;
}

int 
CEMSPairSchedule::IsInSchedule( const EMSSATTRACKRECORD& crstrPass )
{
	int iRet = 0;

	// Linear search.  Could get costly with large numbers of records.
	if( m_aPasses )
	{
		bool bStop = false;
		for( ULONG l = 0; l < m_ulPasses && !bStop; l++ )
		{
			if( 0 == memcmp( &(m_aPasses[l]), &crstrPass, sizeof(EMSSATTRACKRECORD) ) )
			{
				bStop = true;
				iRet = 2;
			}
		}

		if( 0 == iRet )
		{
			EMSTIME timeNow = CEMSSystemClock::GetTime();

			for( ULONG l = 0; l < m_ulPasses && (0 == iRet); l++ )
			{
				if( m_aPasses[l].track.PassInfo.timeAOS.intTime <= timeNow.intTime &&
				m_aPasses[l].track.PassInfo.timeLOS.intTime >= timeNow.intTime &&
				(EMS_PASSFLAG_PROCESS == ( EMS_PASSFLAG_PROCESS & m_aPasses[l].track.PassInfo.ulFlags ) ) &&
				!(EMS_PASSFLAG_SKIP == ( EMS_PASSFLAG_SKIP & m_aPasses[l].track.PassInfo.ulFlags ) ) &&
				m_aPasses[l].track.PassInfo.ulSatelliteID == crstrPass.track.PassInfo.ulSatelliteID )
				{
					iRet = 1; // same pass but different aos/los
				}
			}
		}
	}

	return iRet;
}

void
CEMSPairSchedule::Serialize( const wchar_t* cwszOutput )
{
	CEMSFileStream* pStrm = NULL;

	try
	{
		pStrm = new CEMSFileStream();

		if( !pStrm )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		if( CEMSFileUtility::DoesFileExist( cwszOutput ) )
		{
			CEMSFileUtility::Delete( cwszOutput );
		}

		EMS_RESULT hr = pStrm->OpenFileW( cwszOutput );

		if( EMS_OK != hr )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		ULONG ulWritten = 0;

		hr = pStrm->Write( (const BYTE*) &m_ulPairID, sizeof(m_ulPairID), &ulWritten );

		if( EMS_OK != hr )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		hr = pStrm->Write( (const BYTE*) &m_ulAntennaID, sizeof(m_ulAntennaID), &ulWritten );

		if( EMS_OK != hr )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		hr = pStrm->Write( (const BYTE*) &m_ulDSID, sizeof(m_ulDSID), &ulWritten );

		if( EMS_OK != hr )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		hr = pStrm->Write( (const BYTE*) &m_ulPasses, sizeof(m_ulPasses), &ulWritten );

		if( EMS_OK != hr )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		for( ULONG l = 0; l < m_ulPasses && m_aPasses; l++ )
		{
			hr = pStrm->Write( (const BYTE*) &m_aPasses[l], sizeof(m_aPasses[l]), &ulWritten );

			if( EMS_OK != hr )
			{
				THROW_RUNTIME_EXCEPTION( hr );
			}
		}

		pStrm->Release();
		pStrm = NULL;
	}
	catch( ... )
	{
		if( pStrm )
		{
			pStrm->Release();
			pStrm = NULL;
		}


		throw;
	}
}

void 
CEMSPairSchedule::Deserialize( const wchar_t* cwszInput )
{
	CEMSFileStream* pStrm = NULL;

	try
	{
		pStrm = new CEMSFileStream();

		if( !pStrm )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		EMS_RESULT hr = pStrm->OpenFileW( cwszInput, FALSE );

		if( EMS_OK != hr )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		ULONG ulRead = 0;

		hr = pStrm->Read( (BYTE*) &m_ulPairID, sizeof(m_ulPairID), &ulRead );

		if( EMS_OK != hr )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		hr = pStrm->Read( (BYTE*) &m_ulAntennaID, sizeof(m_ulAntennaID), &ulRead );

		if( EMS_OK != hr )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		hr = pStrm->Read( (BYTE*) &m_ulDSID, sizeof(m_ulDSID), &ulRead );

		if( EMS_OK != hr )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		hr = pStrm->Read( (BYTE*) &m_ulPasses, sizeof(m_ulPasses), &ulRead );

		if( EMS_OK != hr )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		if( m_aPasses )
		{
			delete[] m_aPasses;
			m_aPasses = NULL;
		}

		if( m_ulPasses > 0 )
		{
			m_aPasses = new EMSSATTRACKRECORD[ m_ulPasses ];

			if( !m_aPasses )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			memset( m_aPasses, 0, m_ulPasses*sizeof(EMSSATTRACKRECORD) );

			for( ULONG l = 0; l < m_ulPasses && m_aPasses; l++ )
			{
				hr = pStrm->Read( (BYTE*) &m_aPasses[l], sizeof(m_aPasses[l]), &ulRead );

				if( EMS_OK != hr )
				{
					THROW_RUNTIME_EXCEPTION( hr );
				}
			}
		}

		pStrm->Release();
		pStrm = NULL;
	}
	catch( ... )
	{
		if( pStrm )
		{
			pStrm->Release();
			pStrm = NULL;
		}


		throw;
	}
}

void 
CEMSPairSchedule::_SetSchedule( const ULONG culPasses, const EMSSATTRACKRECORD* caPasses )
{
	if( culPasses > 0 &&
		caPasses )
	{
		if( m_aPasses )
		{
			delete[] m_aPasses;
			m_aPasses = NULL;
		}

		m_aPasses = new EMSSATTRACKRECORD[ culPasses ];

		if( !m_aPasses )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memcpy( m_aPasses, caPasses, culPasses*sizeof(EMSSATTRACKRECORD) );

		m_ulPasses = culPasses;
	}
}