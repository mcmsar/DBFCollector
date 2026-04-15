/*********************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
*										All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#include "emstypes.h"

#ifndef __CEMSCOMINATIONS_H__
#define __CEMSCOMINATIONS_H__

class CEMSCOMINATIONS
{
	public:
		CEMSCOMINATIONS();
		CEMSCOMINATIONS( const CEMSCOMINATIONS& x );
		virtual ~CEMSCOMINATIONS();

		ULONG NchooseK( ULONG N, ULONG K );
		ULONG GetCombinations( ULONG N, ULONG K, ULONG **lpCombinations, ULONG ulRowCount, ULONG ulColCount );
};

#endif
