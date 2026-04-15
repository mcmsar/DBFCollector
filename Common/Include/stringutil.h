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

#ifndef __STRING_UTIL_H__
#define __STRING_UTIL_H__

class CEMSStringUtil
{
	public:
		CEMSStringUtil() {}
		CEMSStringUtil( const CEMSStringUtil& x ) {}
		~CEMSStringUtil() {}
		
		static char* Copy( const char* cszString );
};

#endif