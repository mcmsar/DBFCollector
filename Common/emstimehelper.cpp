/*********************************************************************
*	              Copyright (c) 2010 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#include "emstimehelper.h"


EMSTIME 
CEMSTimeHelper::ConvertEpochTime( const double cdEpochTime )
{
	CEMSTime oEpochTime;
	int nYear = (int) (cdEpochTime / 1000.0);	// year is YYddd.ddddd

	double dDays = cdEpochTime - (double)nYear * 1000.0;	// remove year encoding

	if (( nYear >= 57 ) && ( nYear <= 99 ))
		nYear += 1900;
	else
		nYear += 2000;

	dDays -= 1.0;		// want the number of days NOT the Julian Day

	oEpochTime.SetTime( nYear, dDays );	// set using year and days

	return oEpochTime;
}
