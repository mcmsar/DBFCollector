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


#ifndef __SUPPORTED_URL_SCHEMES_H__
#define __SUPPORTED_URL_SCHEMES_H__

#include <wchar.h>

//! Enumerates strings specifying the URL Schemes supported.
class CEMSSupportedURLSchemes
{
	public:
		CEMSSupportedURLSchemes();
		~CEMSSupportedURLSchemes();

		static const wchar_t* DB;
		static const wchar_t* FILE;
		static const wchar_t* PIPE;
	
};

#endif