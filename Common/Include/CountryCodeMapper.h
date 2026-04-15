/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
********************************************************************************/

#ifndef __COUNTRYCODE_MAPPER_H__
#define __COUNTRYCODE_MAPPER_H__

#include <string>
#include "CountryCodeclient.h"
#include <list>

using namespace std;

class EMSCountryCodeMapper
{
public:
 
	static list<CountryCodeConfig*> Map( const auto_ptr<meoconfig::ccodes> pCCodesConfig );
	static CountryCodeConfig* Map( const auto_ptr<meoconfig::ccode> pCCodeConfig );

private:

};
    
#endif // __COUNTRYCODE_MAPPER_H__