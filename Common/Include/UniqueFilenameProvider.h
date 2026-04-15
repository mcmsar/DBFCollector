/*********************************************************************
*	              Copyright (c) 2004 by EMS Technologies, Inc.,
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

#ifndef __UNIQUE_FILENAME_PROVIDER_H__
#define __UNIQUE_FILENAME_PROVIDER_H__

#include <string>

//! This class can be used to obtain unique filenames.  File names are guaranteed to be
//! unique within a single process.
class CEMSUniqueFileNameProvider
{
	public:
		CEMSUniqueFileNameProvider() {}
		CEMSUniqueFileNameProvider( const CEMSUniqueFileNameProvider& x ) {}
		~CEMSUniqueFileNameProvider() {}

		//! Retrieve a unique filename of the form:
		//! cwszDir\cwszPrefix_<timestamp>
		//! Both parameters are optional and can be NULL.
		static std::wstring GetUniqueFileName( const wchar_t* cwszDir, const wchar_t* cwszPrefix );

		//! Retrieve a unique filename of the form:
		//! cszDir\cszPrefix_<timestamp>
		//! Both parameters are optional and can be NULL.
		static std::string GetUniqueFileName( const char* cszDir, const char* cszPrefix );
};

#endif