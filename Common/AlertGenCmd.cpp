
#include "alertgencmd.h"

#include "emserror.h"
#include "emsexcpt.h"
#include "commandformats.h"
#include "ecmdproc.h"
#include "convutility.h"

CEMSAlertGenCmd::CEMSAlertGenCmd() :m_eType( ALERTGENCMD_UNKNOWN )
{
	memset( &m_dataAlert, 0, sizeof(EMSCMDGENALERT) );
}

CEMSAlertGenCmd::CEMSAlertGenCmd( const CEMSAlertGenCmd& x ) : m_eType( ALERTGENCMD_UNKNOWN )
{
	memcpy( &m_dataAlert, &(x.m_dataAlert), sizeof(EMSCMDGENALERT) );
}

CEMSAlertGenCmd::~CEMSAlertGenCmd()
{
}

void
CEMSAlertGenCmd::SetDestinations( const unsigned long culDests, const unsigned long* caulDests )
{
	if( !caulDests )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	if( (culDests > MAX_DESTINATIONS) || ( culDests < 1)  )
	{
		THROW_INVALID_ARG_EXCEPTION();
	}

	for( unsigned long l = 0; l < culDests; l++ )
	{
		m_dataAlert.aulDestinationIDs[l] = caulDests[l];
	}

	m_dataAlert.ulNumDestinations = culDests;

	m_eType = ALERTGENCMD_GENERATE;
}

void
CEMSAlertGenCmd::GetDestinations( unsigned long& ulDests, unsigned long*& aulDests ) const
{
	ulDests = 0;
	aulDests = 0;

	if( m_dataAlert.ulNumDestinations > 0 )
	{
		aulDests = new unsigned long[ m_dataAlert.ulNumDestinations ];

		if( !aulDests )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		ulDests = m_dataAlert.ulNumDestinations;

		for( unsigned long l = 0; l < ulDests; l++ )
		{
			aulDests[l] = m_dataAlert.aulDestinationIDs[l];
		}
	}
}

void 
CEMSAlertGenCmd::SetLocations( const unsigned long culLocations, const EMSLOCATIONKEY* caLocations )
{
	if( !caLocations )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	if( ( culLocations > MAX_LOCATION_KEYS ) || ( culLocations < 1 ) )
	{
		THROW_INVALID_ARG_EXCEPTION();
	}

	for( unsigned long l = 0; l < culLocations; l++ )
	{
		m_dataAlert.locationKey[l] = caLocations[l];
	}

	m_dataAlert.ulNumLocationsKeys = culLocations;

	m_eType = ALERTGENCMD_GENERATE;
}

void 
CEMSAlertGenCmd::GetLocations( unsigned long& ulLocations, EMSLOCATIONKEY*& aLocations ) const
{
	ulLocations = 0;
	aLocations = 0;

	if( m_dataAlert.ulNumLocationsKeys > 0 )
	{
		aLocations = new EMSLOCATIONKEY[ m_dataAlert.ulNumLocationsKeys ];

		if( !aLocations )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		ulLocations = m_dataAlert.ulNumLocationsKeys;

		for( unsigned long l = 0; l < ulLocations; l++ )
		{
			aLocations[l] = m_dataAlert.locationKey[l];
		}
	}
}

void 
CEMSAlertGenCmd::SetUserID( unsigned char szUser[ EMS_MAX_USER_NAME ] )
{
	memcpy( m_dataAlert.szUserID, szUser, EMS_MAX_USER_NAME*sizeof(unsigned char) );
}

void 
CEMSAlertGenCmd::GetUserID( unsigned char szUser[ EMS_MAX_USER_NAME ] )
{
	memcpy( szUser, m_dataAlert.szUserID, EMS_MAX_USER_NAME*sizeof(unsigned char) );
}

EMSCMDGENALERT 
CEMSAlertGenCmd::GetCommand()
{
	return m_dataAlert;
}