/*********************************************************************
*	              Copyright (c) 2005 by EMS Technologies, Inc.,
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


#include "EMSPlugInLoader.h"
#include "emsexcpt.h"

CEMSPlugInLoader::CEMSPlugInLoader()
{

}

CEMSPlugInLoader::~CEMSPlugInLoader()
{

}

HRESULT 
CEMSPlugInLoader::LoadPlugIn( const wchar_t* cwszClassID, LPUNKNOWN& pIUnknown )
{
	HRESULT hr = EMS_OK;
	pIUnknown = 0;
	wchar_t*  wszClsid = 0;

	try
	{
		CLSID clsidRet = CLSID_NULL;

		if( cwszClassID && wcslen(cwszClassID) > 0 )
		{
			wszClsid = new wchar_t[ wcslen(cwszClassID) + 1 ];

			if( !wszClsid )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			memset( wszClsid, 0, ( wcslen(cwszClassID) + 1 )*sizeof(wchar_t) );

			wcsncpy( wszClsid, cwszClassID, wcslen(cwszClassID) );

			CLSIDFromString( wszClsid, &clsidRet );

			delete[] wszClsid;
			wszClsid = 0;
		}

		if( !InlineIsEqualGUID( clsidRet, CLSID_NULL ) )
		{
			hr = CoCreateInstance( clsidRet, 0, CLSCTX_ALL, IID_IUnknown, (void**) &pIUnknown );
		}
	}
	catch( ... )
	{
		if( wszClsid )
		{
			delete[] wszClsid;
			wszClsid = 0;
		}

		throw;
	}

	return hr;
}
