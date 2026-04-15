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

#ifndef __DIRECTORY_READER_THREAD_H__
#define __DIRECTORY_READER_THREAD_H__

//! @class CEMSDirectoryReaderThread
//! A class that spawns a thread to get a listing of the files in a directory.
class CEMSDirectoryReaderThread : public CEMSThread
{
	public:
		CEMSDirectoryReaderThread();
		CEMSDirectoryReaderThread( const CEMSDirectoryReaderThread& x );
		virtual ~CEMSDirectoryReaderThread();

		void SetDirectory( const wchar_t* cwszDirectory );
};