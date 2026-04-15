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

#ifndef __IP_HELPER_H__
#define __IP_HELPER_H__

#include <string>

//! Helper class for IP and Network connection related functions.
class CEMSIPHelper
{
	public:
		CEMSIPHelper();
		CEMSIPHelper( const CEMSIPHelper& x);
		~CEMSIPHelper();
		
		//! Get the IP address associated with the given adapter name.
		static std::string GetIPAddress( const char* cszAdapter );

		//! Extract the IP address and convert it to a dot notation string.
		static std::string GetIP( const struct sockaddr cstrAddr );
};

#endif