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

#ifndef __WSHOST_600_H__
#define __WSHOST_600_H__

#include "wshostEx.h"
#include "loggrcat.h"
#include <initguid.h>

// {DB8D92D4-F319-43e6-832C-679CD163FDC5}
DEFINE_GUID(APPID_WSHost600, 
0xdb8d92d4, 0xf319, 0x43e6, 0x83, 0x2c, 0x67, 0x9c, 0xd1, 0x63, 0xfd, 0xc5);


//! Host (Windows Service) class for OCC600 Web Service.
class CEMS600WSHost : public CEMSWSHostEx
{
	public:
		CEMS600WSHost() {/* SetParent(L"CEMS600WSHost");*/ }
		virtual ~CEMS600WSHost() {}

		static const wchar_t* GetServiceName() { return L"EMS600WSHost"; }
		virtual const wchar_t* GetComponent() { return L"WSHost600"; }
		virtual const TCHAR* GetService() { return TEXT("EMS600WSHost"); }

	private:
		virtual const CLSID* _GetAppID() { return &APPID_WSHost600; }
		virtual const USHORT _GetLoggerCategory() { return -1; } //To be fixed...

};

#endif