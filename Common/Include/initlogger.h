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

#ifndef __INIT_LOGGER_H__
#define __INIT_LOGGER_H__

#include "emstypes.h"
#include <wchar.h>

void InitLogger( const wchar_t* cwszLoggerName, const ULONG culLoggerCat, const wchar_t* cwszRegValueName = NULL );
void StopLogger();

#endif