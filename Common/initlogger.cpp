/*********************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
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

#include "initlogger.h"
#include "logclient.h"

#include <initguid.h>
#include "leosite.h"

static bool g_cbLoggerInit = false;

void InitLogger( const wchar_t* cwszLoggerName, const ULONG culLoggerCat, const wchar_t* cwszRegValueName )
{
	if( !g_cbLoggerInit )
	{
		g_cbLoggerInit = true;

		CEMSLogClient oLogger;

		// Use the INI file specified in the registry
		// Note that this calls InitializeDefault()
		oLogger.InitializeFromRegistry( cwszRegValueName );

		IEMSSiteInfo* pSite = NULL;

		// If the CM is available then get the LUT ID and inform the logger of it.
		EMS_RESULT hr = CoCreateInstance( CLSID_EMSSiteInfo, NULL, CLSCTX_ALL, 
									IID_IEMSSiteInfo, (void**) &pSite );

		ULONG ulLutID = 0;

		if( EMS_OK == hr &&
			pSite )
		{
			hr = pSite->GetLutID( &ulLutID );

			pSite->Release();
			pSite = NULL;
		}

		oLogger.InitializeProcess( cwszLoggerName, culLoggerCat, ulLutID );
	}
}

void StopLogger()
{
	if( g_cbLoggerInit )
	{
		CEMSLogClient oLogger;
		oLogger.Shutdown();
	}
}