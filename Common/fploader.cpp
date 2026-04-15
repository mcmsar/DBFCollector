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

#include "fploader.h"
#include "emspluginloader.h"
#include "emsexcpt.h"

#include <initguid.h>
#include "wsclient.h"
#include "configure.h"
#include "fpmsgs.h"
#include "loghelper.h"

IEMSDataCollector* 
CEMSFPLoader::LoadDatastreamProxy( const ULONG culPair, CEMSFPConfig& roConfig )
{
	IEMSDataCollector* pRet = NULL;
	IUnknown* pUnk = NULL;
	IEMSWSClient* pWSClient = NULL;
	IEMSConfigure* pConfig = NULL;

	try
	{

		std::wstring owszClsid = roConfig.GetDSProxyClassID( culPair );

		if( owszClsid.empty() )
		{
			CEMSLogMsgParam oParam;
			oParam.Add( culPair );

			throw CEMSException( EMS_FP_NO_DS_PROXY_CLASSID, oParam );
		}

		EMS_RESULT hr = CEMSPlugInLoader::LoadPlugIn( owszClsid.c_str(), pUnk );

		if( EMS_OK != hr )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		hr = pUnk->QueryInterface( IID_IEMSWSClient, (void**) &pWSClient );

		if( EMS_OK != hr )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		pUnk->Release();
		pUnk = NULL;

		std::wstring owszURL = roConfig.GetDSWSURL( culPair );
		std::wstring owszUser = roConfig.GetDSWSUser( culPair );
		std::wstring owszPwd = roConfig.GetDSWSPassword( culPair );

		hr = pWSClient->SetURL( owszURL.c_str() );

		if( EMS_OK != hr )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		hr = pWSClient->SetUsername( owszUser.c_str() );

		if( EMS_OK != hr )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		hr = pWSClient->SetPassword( owszPwd.c_str() );

		if( EMS_OK != hr )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		hr = pWSClient->QueryInterface( IID_IEMSDataCollector, (void**) &pRet );

		if( EMS_OK != hr )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

		pWSClient->Release();
		pWSClient = NULL;

		std::wstring owszConfig = roConfig.GetDSConfig( roConfig.GetDSID( culPair ) );
		if( !owszConfig.empty() )
		{
			hr = pRet->QueryInterface( IID_IEMSConfigure, (void**) &pConfig );

			if( EMS_OK != hr )
			{
				THROW_RUNTIME_EXCEPTION( hr );
			}

			hr = pConfig->SetConfig( owszConfig.c_str() );

			if( EMS_OK != hr )
			{
				THROW_RUNTIME_EXCEPTION( hr );
			}

			pConfig->Release();
			pConfig = NULL;
		}
	}
	catch( ... )
	{
		if( pWSClient )
		{
			pWSClient->Release();
			pWSClient = NULL;
		}

		if( pUnk )
		{
			pUnk->Release();
			pUnk = NULL;
		}

		if( pRet )
		{
			pRet->Release();
			pRet = NULL;
		}

		if( pConfig )
		{
			pConfig->Release();
			pConfig = NULL;
		}

		throw;
	}

	return pRet;
}

IEMSAntenna* 
CEMSFPLoader::LoadAntennaProxy( const ULONG culPair, CEMSFPConfig& roConfig )
{
	IEMSAntenna* pRet = NULL;

	try
	{
		ULONG ulAntennaID = roConfig.GetAntennaID( culPair );

		// Specification of an antenna ID is optional since this may be an EMS GEO Antenna, which
		// has no antenna controller.
		if( 0 != ulAntennaID )
		{
			pRet = LoadAntennaProxyByID( ulAntennaID, roConfig );
		}

	}
	catch( ... )
	{
		if( pRet )
		{
			pRet->Release();
			pRet = NULL;
		}

		throw;
	}

	return pRet;
}

IEMSAntenna* 
CEMSFPLoader::LoadAntennaProxyByID( const ULONG culAntennaID, CEMSFPConfig& roConfig )
{
	IEMSAntenna* pRet = NULL;
	IUnknown* pUnk = NULL;
	IEMSWSClient* pWSClient = NULL;
	IEMSConfigure* pConfig = NULL;

	try
	{
		std::wstring owszClsid = roConfig.GetAntennaProxyClassID( culAntennaID );

		if( owszClsid.empty() )	// There may be no antenna controller for this FP.  Controller may by external or it may be a non-tracking antenna.
		{
			CEMSLogMsgParam oParam;
			oParam.Add( culAntennaID );
			CEMSLogHelper::LogMsg( EMSLogMsgInfo, EMS_FP_NO_ANTENNA_PROXY_CLASSID, oParam );
		}
		else
		{

			EMS_RESULT hr = CEMSPlugInLoader::LoadPlugIn( owszClsid.c_str(), pUnk );

			if( EMS_OK != hr )
			{
				THROW_RUNTIME_EXCEPTION( hr );
			}

			hr = pUnk->QueryInterface( IID_IEMSWSClient, (void**) &pWSClient );

			if( EMS_OK != hr )
			{
				THROW_RUNTIME_EXCEPTION( hr );
			}

			pUnk->Release();
			pUnk = NULL;

			std::wstring owszURL = roConfig.GetAntennaWSURL( culAntennaID );
			std::wstring owszUser = roConfig.GetAntennaWSUser( culAntennaID );
			std::wstring owszPwd = roConfig.GetAntennaWSPassword( culAntennaID );
		
			hr = pWSClient->SetURL( owszURL.c_str() );

			if( EMS_OK != hr )
			{
				THROW_RUNTIME_EXCEPTION( hr );
			}

			hr = pWSClient->SetUsername( owszUser.c_str() );

			if( EMS_OK != hr )
			{
				THROW_RUNTIME_EXCEPTION( hr );
			}

			hr = pWSClient->SetPassword( owszPwd.c_str() );

			if( EMS_OK != hr )
			{
				THROW_RUNTIME_EXCEPTION( hr );
			}

			hr = pWSClient->QueryInterface( IID_IEMSAntenna, (void**) &pRet );

			if( EMS_OK != hr )
			{
				THROW_RUNTIME_EXCEPTION( hr );
			}

			pWSClient->Release();
			pWSClient = NULL;

			std::wstring owszConfig = roConfig.GetAntennaConfig( culAntennaID );
			if( !owszConfig.empty() )
			{
				hr = pRet->QueryInterface( IID_IEMSConfigure, (void**) &pConfig );

				if( EMS_OK != hr )
				{
					THROW_RUNTIME_EXCEPTION( hr );
				}

				hr = pConfig->SetConfig( owszConfig.c_str() );

				if( EMS_OK != hr )
				{
					THROW_RUNTIME_EXCEPTION( hr );
				}

				pConfig->Release();
				pConfig = NULL;
			}
		}
	}
	catch( ... )
	{
		if( pWSClient )
		{
			pWSClient->Release();
			pWSClient = NULL;
		}

		if( pUnk )
		{
			pUnk->Release();
			pUnk = NULL;
		}

		if( pRet )
		{
			pRet->Release();
			pRet = NULL;
		}

		if( pConfig )
		{
			pConfig->Release();
			pConfig = NULL;
		}

		throw;
	}

	return pRet;
}