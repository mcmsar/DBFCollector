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

#ifndef __TEXT_FILE_READER_H__
#define __TEXT_FILE_READER_H__

#include <string>

class CEMSTextFileReader
{
	public:
		CEMSTextFileReader();
		CEMSTextFileReader( const CEMSTextFileReader& x );
		~CEMSTextFileReader();

		std::wstring ReadAll( const wchar_t* cwszFileSpec );
		std::wstring ReadAllShared( const wchar_t* cwszFileSpec );

	private:
};

#endif