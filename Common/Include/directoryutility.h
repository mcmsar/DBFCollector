/****************************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of EMS Technologies, Inc.
*
****************************************************************************/

/****************************************************************************

  Revision Record

	$Log:
	$
****************************************************************************/

#ifndef __DIRECTORY_UTILITY_H__
#define __DIRECTORY_UTILITY_H__

#include <wchar.h>

class CEMSDirectoryUtility
{
	public:
		CEMSDirectoryUtility();
		CEMSDirectoryUtility( const CEMSDirectoryUtility& x );
		~CEMSDirectoryUtility();

		//! Returns true if the copy was performed.
		static bool Copy( const wchar_t* cwszSrc, const wchar_t* cwszDest );

		//! Creates the full directory path, if it doesn't already exist.
		static void CreateDirPath( const wchar_t* cwszDirPath );

		//! Delete the directory and all of its contents.
		static bool Delete( const wchar_t* cwszDir );

};

#endif