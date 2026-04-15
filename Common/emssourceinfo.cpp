#include "emssourceinfo.h"
#include "emserror.h"
#include <stdio.h>
#include <tchar.h>

CEMSSourceInfo::CEMSSourceInfo() : m_pSiteInfo(0), m_ulOIID(0), m_ulSiteID(0)
{
	memset( m_szOIName, 0, (_MAX_PATH+1)*sizeof(char) );
}

CEMSSourceInfo::CEMSSourceInfo( CEMSSourceInfo& oInfo ) : m_pSiteInfo(0), m_ulOIID(0), m_ulSiteID(0)
{
	memset( m_szOIName, 0, (_MAX_PATH+1)*sizeof(char) );

	m_ulSiteID = oInfo.m_ulSiteID;
	m_ulOIID = oInfo.m_ulOIID;
	strcpy( m_szOIName, oInfo.m_szOIName );
	m_pSiteInfo = oInfo.m_pSiteInfo;

	if( m_pSiteInfo )
		m_pSiteInfo->AddRef();
}

CEMSSourceInfo::~CEMSSourceInfo()
{
	if( m_pSiteInfo )
	{
		m_pSiteInfo->Release();
		m_pSiteInfo = 0;
	}
}

EMS_RESULT
CEMSSourceInfo::Init()
{
	EMS_RESULT hr = _InitSiteInfo();

	if( SUCCEEDED(hr) )
	{
		// Get the site id.
		hr = m_pSiteInfo->GetLutID( &m_ulSiteID );

		if( SUCCEEDED(hr) )
		{
			// Get the OI id.
			if( m_ulSiteID >= 9000 )
			{
				m_ulOIID = m_ulSiteID;
			}
			else
			{
				char szSiteID[5];
				memset( szSiteID, 0, 5*sizeof(char) );

				_stprintf( szSiteID, "%d", m_ulSiteID );

				if( 4 == strlen(szSiteID) )
				{
					// Just change the first character to a '9'.
					szSiteID[0] = TEXT('9');

					m_ulOIID = strtoul( szSiteID, 0, 10 );
				}
				else
				{
					hr = EMS_UNKNOWN_ERROR;
				}
			}
		}

		if( SUCCEEDED(hr) )
		{
			// Get the short name for the OI.
			EMSSOURCEINFO aSourceInfo[EMS_MAX_SOURCES];
			memset( aSourceInfo, 0, EMS_MAX_SOURCES*sizeof(EMSSOURCEINFO) );

			ULONG ulNumber = 0;
			hr = m_pSiteInfo->GetSourcesInfo( aSourceInfo, EMS_MAX_SOURCES, &ulNumber );

			BOOL bFound = FALSE;
			for( ULONG i = 0; i < ulNumber && !bFound; i++ )
			{
				if( aSourceInfo[i].ulID == m_ulOIID )
				{
					bFound = TRUE;
					strncpy( m_szOIName, (char*) aSourceInfo[i].szShortName, _MAX_PATH );
				}
			}
		}
	}

	return hr;
}

ULONG
CEMSSourceInfo::GetNextMsgNumber( ULONG ulDestID )
{
	ULONG ulRet = 0;

	EMS_RESULT hr = _InitSiteInfo();

	if( SUCCEEDED(hr) )
	{
		// Get the route info.
		EMSDESTINATIONINFO aDestInfo[EMS_MAX_DESTINATIONS];
		memset( aDestInfo, 0, EMS_MAX_DESTINATIONS*sizeof(EMSDESTINATIONINFO) );

		ULONG ulNumber = 0;
		hr = m_pSiteInfo->GetDestinationsInfo( aDestInfo, EMS_MAX_DESTINATIONS, &ulNumber );

		BOOL bFound = FALSE;
		for( ULONG i = 0; i < ulNumber && !bFound; i++ )
		{
			if( aDestInfo[i].ulID == ulDestID )
			{
				bFound = TRUE;
				ulRet = aDestInfo[i].ulSeqNumber;

				ulRet++;
				// Increment the number in the config.
				hr = m_pSiteInfo->SetSentMsgNumber( (BYTE*) aDestInfo[i].szShortName, ulRet );
			}
		}
	}

	if( FAILED(hr) )
	{
		ulRet = -1;
	}

	return ulRet;

}

EMS_RESULT
CEMSSourceInfo::_InitSiteInfo()
{
	EMS_RESULT hr = EMS_OK;

	if( !m_pSiteInfo )
	{
		hr = CoCreateInstance( CLSID_EMSLutInfo, 0, CLSCTX_ALL, IID_IEMSSiteInfo, (void**) &m_pSiteInfo );
	}

	return hr;

}

