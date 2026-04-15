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

	$Log:
	$
********************************************************************/

#ifndef __SPL_ERROR_HANDLER_H__
#define __SPL_ERROR_HANDLER_H__

#include "criticalsection.h"
#include "sigproc.h"
#include <string>

//! Used to intercept SPL errors and provide custom handling.
class CEMSSPLErrorHandler
{
	public:
		~CEMSSPLErrorHandler();

		//! Get a pointer to the single instance of the error handler.
		static CEMSSPLErrorHandler* GetInstance();

		//! Activate the error handler.
		void Activate();

		//! Deactivate the error handler.
		void Deactivate();

		//! Call this to have the exception handler throw an exception or not.  By default, it will
		//! throw an exception.
		void SetThrowException( const bool cbThrow = true ) { m_bThrowException = cbThrow; }

		//! Determine whether configured to thrown an exception.
		bool GetThrowException() { return m_bThrowException; }

		//! Deactivates and releases any resources used by the error handler.
		static void Shutdown();

		//! Convert a status value to text for output.
		std::wstring GetStatusText( const EMSSIGPROCSTATUS cstatValue );

	protected:
		CEMSSPLErrorHandler();

	private:
		static CEMSCriticalSection	m_ocsInstance;
		bool						m_bThrowException;
		static CEMSSPLErrorHandler*	ms_pHandler;
};


#endif // __SPL_ERROR_HANDLER_H__