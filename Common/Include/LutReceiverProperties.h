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

#ifndef __LUTRECEIVER_PROPERTIES_H__
#define __LUTRECEIVER_PROPERTIES_H__

#include "emstypes.h"

class CEMSLutReceiverProperties
{
	public:
		CEMSLutReceiverProperties();
		CEMSLutReceiverProperties( const CEMSLutReceiverProperties& x );
		~CEMSLutReceiverProperties();

		static bool RequiresSpectrumInversion( const ULONG culLutID );

	public:	// constants
};

#endif