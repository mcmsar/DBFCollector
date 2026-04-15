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

#ifndef __EMSPLUGIN_LOADER_H__
#define __EMSPLUGIN_LOADER_H__

#include "aobjbase.h"
#include "Unknwn.h"


//! @class CEMSPlugInLoader
//! Implementation of Plug-in loader. The object of this class
//! loads any plug-in using the class id of the plug-in.
class CEMSPlugInLoader : public CApiObjBase  
{
public:
	CEMSPlugInLoader();
	virtual ~CEMSPlugInLoader();

	//! @fn HRESULT LoadPlugIn( const wchar_t* cwszClassID, LPUNKNOWN& pIUnknown )
	//! Calls CoCreateInstance to load the plug-in and returns a pointer to COM object (UNKNOWN),
	//! if CoCreateInstance fails, this function returns the error.
	//! @param const wchar_t* cwszClassID
	//! The class id (in string format).
	//! @param LPUNKNOWN& pIUnknown
	//! A pointer to the plug-in interface.
	static HRESULT LoadPlugIn( const wchar_t* cwszClassID, LPUNKNOWN& pIUnknown );
};

#endif
