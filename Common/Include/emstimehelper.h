/*********************************************************************
*	              Copyright (c) 2010 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
#ifndef INC_EMSTIMEHELPER
#define INC_EMSTIMEHELPER

#include "emstime.h"


class CEMSTimeHelper
{
public:

	CEMSTimeHelper() {}
	~CEMSTimeHelper() {}

	static EMSTIME ConvertEpochTime( const double cdEpochTime );
};


#endif // INC_EMSTIMEHELPER

