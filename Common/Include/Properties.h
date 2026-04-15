/*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log$
********************************************************************/

#ifndef __PROPERTIES_H__
#define __PROPERTIES_H__

class IEMSProperties
{
	public:
		IEMSProperties() {}
		virtual ~IEMSProperties() {}

		virtual ULONG GetPropULong( const wchar_t* cwszProp ) = 0;
		virtual void SetProp( const wchar_t* cwszProp, const ULONG culValue ) = 0;
};

#endif