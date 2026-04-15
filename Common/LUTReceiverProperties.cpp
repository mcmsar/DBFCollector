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

#include "LutReceiverProperties.h"


bool 
CEMSLutReceiverProperties::RequiresSpectrumInversion( const ULONG culLutID )
{
	bool bRet = false;

// Assume all LUTs perform spectrum inversion if required
//	if( culLutID == 3669 ) 
	{
		bRet = true;
	}

	return bRet;
}

