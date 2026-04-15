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

#include "stringutil.h"
#include <string.h>
#include <stdio.h>

char*
CEMSStringUtil::Copy( const char* cszString )
{
	char* szRet = NULL;
	size_t lLen = 0;
	if( cszString && ( lLen = strlen(cszString) ) )
	{
		szRet = new char[ lLen + 1 ];
		sprintf( szRet, "%s", cszString );
	}

	return szRet;
}