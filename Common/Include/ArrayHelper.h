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

#ifndef __ARRAY_HELPER_H__
#define __ARRAY_HELPER_H__

#include "emstypes.h"

//! Utility class for working with arrays.
class CEMSArrayHelper
{
	public:
		CEMSArrayHelper() {}
		CEMSArrayHelper( const CEMSArrayHelper& x ) {}
		virtual ~CEMSArrayHelper() {}

		static void Concatenate( BYTE*& abyData, DWORD& dwDataSize, 
						const BYTE* cabyNewData, const DWORD cdwNewDataSize ); 

};

#endif