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

#ifndef __CSTRING_HELPER_H__
#define __CSTRING_HELPER_H__

#include <afx.h>
#include "emstypes.h"

//! Helper class for using MFC CString with EMS data types.
class CEMSCStringHelper
{
	public:
		CEMSCStringHelper() {}
		CEMSCStringHelper( const CEMSCStringHelper& x ) {}
		~CEMSCStringHelper() {}

		static CString ConvertToCString( const DWORD cdwValue );
		static CString ConvertToCString( const EMSTIME ctimeValue );
		static CString ConvertToCString( const double cdValue );
};

#endif