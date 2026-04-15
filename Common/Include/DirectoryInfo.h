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

#ifndef __DIRECTORY_INFO_H__
#define __DIRECTORY_INFO_H__

#include <string>

const unsigned long MAX_BUFFER = 4096;

#ifdef WIN32	// Using Windows API for handles, OVERLAPPED structure
#include <windows.h>

//! @class CEMSDirectoryInfo Used to store directory information
//! for use when monitoring a directory for changes.
class CEMSDirectoryInfo
{
	public:
		CEMSDirectoryInfo();
		~CEMSDirectoryInfo() { Clear(); }

		void SetHandle( const HANDLE chDir ) { m_hDir = chDir; }
		HANDLE GetHandle() { return m_hDir; }

		void SetDirName( const wchar_t* cwszDirName ) { m_wszDirName = cwszDirName; }
		std::wstring GetDirName() { return m_wszDirName; }

		ULONG GetMaxBuffer() { return MAX_BUFFER; };

		// Returning these pointers is bad C++ form, but we're really using the class as a structure in a C call.

		char* GetBuffer() { return m_byBuffer; }

		ULONG* GetBufferLengthPointer() { return &m_ulBufferLength; }

		OVERLAPPED* GetOverLappedPointer() { return &m_strOverLapped; }

		void Clear();

	private:
		HANDLE			m_hDir;
		std::wstring	m_wszDirName;
		char			m_byBuffer[MAX_BUFFER];
		ULONG			m_ulBufferLength;
		OVERLAPPED		m_strOverLapped;
};

#endif

#endif