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

#ifndef __UNIQUE_TIME_PROVIDER_H__
#define __UNIQUE_TIME_PROVIDER_H__

#include "criticalsection.h"
#include "emstime.h"

//! This class provides unique timestamps by adding nanoseconds to the current clock time until
//! a time different from the last one provided is calculated.  It is thread-safe.  That is,
//! multiple threads can call it and each be guaranteed a unique value.
class CEMSUniqueTimeProvider
{
	public:
		~CEMSUniqueTimeProvider();

		//! Get a pointer to a static instance of the class.  The caller should not attempt to
		//! release or delete the returned pointer as the object is stack allocated.
		static CEMSUniqueTimeProvider* GetInstance();

		//! Retrieve a unique time.
		EMSTIME GetTime();

	protected:
		CEMSUniqueTimeProvider();

	private:
		static CEMSUniqueTimeProvider ms_oTP;
		EMSTIME m_timeLast;
		CEMSCriticalSection m_ocsTP;

};

#endif