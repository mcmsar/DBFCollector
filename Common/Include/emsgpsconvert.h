/*********************************************************************
*	              Copyright (c) 2009 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
#ifndef INC_EMSGPSCONVERT
#define INC_EMSGPSCONVERT

#include "emstime.h"

class CEMSGPSConvert
{
public:

	CEMSGPSConvert() {}
	~CEMSGPSConvert() {}

	static EMSTIME ConvertGPSTIMEtoEMSTIME( const double cdSeconds, 
											const short csWeeknum,
											const bool cbFromGNSS = false );
	static int GetLeapSeconds( const bool bFromGNSS = false );

private: // methods
	static int		_GetLeapSecondAdjustment( const bool cbFromGNSS );
	
private: // data
	static int			m_iLeapSecondAdjustment;
	static bool			m_bHaveAdjustment;
};

//private: // constants

#endif // INC_EMSGPSCONVERT

