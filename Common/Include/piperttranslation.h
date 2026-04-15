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

#ifndef __PIPELINE_RT_TRANSLATION_H__
#define __PIPELINE_RT_TRANSLATION_H__

#include "dal.h"

//! Translates record types to pipeline channels.
class CEMSRTToPipeTranslator
{
	public:
		CEMSRTToPipeTranslator();
		~CEMSRTToPipeTranslator();

		static BYTE Translate( const EMSRECORDTYPE ceType );

};

#endif