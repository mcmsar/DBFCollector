/*********************************************************************
*	              Copyright (c) 2009 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
#include <initguid.h>
#include "emsgpsconvert.h"
#include "EMSEXCPT.h"
#include "iconfigmanager.h"
#include "JavadIf.h"
#include "EMSCONFG.h"
#include "ccbootstrap.h"
#include "ClocksConfig.h"
#include "meosysclient.h"
#include "messages.h"

//#define INIT_GUID
//#include <initguid.h>
#include "ConfigManagerProxyClsid.h"

const wchar_t *c_wszKeyLeapSeconds = L"LeapSeconds";
const TCHAR c_szComponent[]	= TEXT("OrbitManager");

bool CEMSGPSConvert::m_bHaveAdjustment = false;
int CEMSGPSConvert::m_iLeapSecondAdjustment = -16; // valid as of 2012

int CEMSGPSConvert::_GetLeapSecondAdjustment( const bool cbFromGNSS )
{
    EMS_RESULT  hr = EMS_OK;
	WORD		wLeapSeconds;
	IEMSJavadInterface	*lpJavInterface = NULL;
	MEOSystemClient		oMeoSysClient;
	LPConfig*			pLPConf = NULL;
	EMSClocksConfig*	pClocksConfig = NULL;

	try
	{
		if ( m_bHaveAdjustment == false )
		{
			char	szGnssType[ 64 ];

			if ( cbFromGNSS == true )
			{
				pLPConf = oMeoSysClient.getLPById( CCBootstrap::GetThisSubsystemId() );

				if( pLPConf )
				{
					memset( szGnssType, 0, sizeof(szGnssType) );
					strcpy( szGnssType, pLPConf->GetGNSSType().c_str() );
		
					delete pLPConf;
					pLPConf = NULL;
				}

				if ( strcmp(szGnssType, "Javad") == 0  )
				{
					hr = CoCreateInstance( CLSID_EMSJavadInterface, 0, CLSCTX_ALL,
											IID_IEMSJavadInterface, (LPVOID*)&lpJavInterface );
					if ( (hr == EMS_OK) && (NULL != lpJavInterface) )
					{
						hr = lpJavInterface->Open( 0 );
						if ( hr == EMS_OK )
						{
							hr = lpJavInterface->GetLeapSeconds( &wLeapSeconds );
							if ( hr == EMS_OK )
							{
								m_iLeapSecondAdjustment = 0 - wLeapSeconds;
								m_bHaveAdjustment = true;
							}
						}
						lpJavInterface->Close();
						lpJavInterface->Release();
						lpJavInterface = NULL;
					}
				}
			}

			// If we can't get it from Javad, try config file.
			if ( m_bHaveAdjustment == false )
			{
				pClocksConfig = oMeoSysClient.getClocksConfig();
				if( pClocksConfig )
				{
					m_iLeapSecondAdjustment = 0 - pClocksConfig->GetLeapSeconds();
					m_bHaveAdjustment = true;
					delete pClocksConfig;
					pClocksConfig = NULL;
				}
				else
				{
					throw CEMSException(__LINE__, __FILE__, EMS_CM_NO_DATA );
				}
			}
		}
	}
	catch( ... )
	{
		if ( pLPConf )
		{
			delete pLPConf;
			pLPConf = NULL;
		}
		if ( pClocksConfig )
		{
			delete pClocksConfig;
			pClocksConfig = NULL;
		}
		if ( lpJavInterface )
		{
			lpJavInterface->Release();
			lpJavInterface = NULL;
		}
		throw;
	}

	return m_iLeapSecondAdjustment;
}

EMSTIME CEMSGPSConvert::ConvertGPSTIMEtoEMSTIME( const double cdSeconds, const short csWeeknum,
												 const bool bFromGNSS )
{
	EMSTIME time;
	CEMSTime T;
	int nWeek = csWeeknum % 1024;

	// GPS time rollover at 99/08/22 00:00:00 UTC 
	T.SetTime( 1999, 8, 22, 00, 00, 00, 0 );

	// Adjust this to account for leap seconds
	T.AddSeconds( _GetLeapSecondAdjustment(bFromGNSS) );

	T.AddDays( (double) nWeek * 7 );
	
	time = T.AddSeconds( cdSeconds );

	return time;
}

int CEMSGPSConvert::GetLeapSeconds( const bool bFromGNSS )
{
	int iLeapSeconds;

	iLeapSeconds = _GetLeapSecondAdjustment(bFromGNSS);

	return iLeapSeconds;
}
