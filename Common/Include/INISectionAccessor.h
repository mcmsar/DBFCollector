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

#ifndef __INI_SECTION_ACCESSOR_H__
#define __INI_SECTION_ACCESSOR_H__

#include <string>
#include "objectmap.h"

//! Used to hold all key/value pairs for a .ini section, allowing modification and
//! addition of values.
class CEMSINISectionAccessor
{
	public:
		CEMSINISectionAccessor();
		CEMSINISectionAccessor( const CEMSINISectionAccessor& x );
		~CEMSINISectionAccessor();

		//! Set the .ini section name.
		void SetSection( const wchar_t* cwszSection, const wchar_t* cwszSectionID = 0 );

		//! Convert the contained list of key/value pairs into a byte stream that can be
		//! passed to the Win32 WritePrivateProfileSection function.
		void Serialize( BYTE*& rabyBuf, ULONG& rulBufSize );

		//! Convert a stream of bytes returned from a Win32 GetPrivateProfileSection call into
		//! a set of key/value pairs.
		void Deserialize( const BYTE* cabyData, const ULONG culSize );

		//! Add a new key or overwrite existing.
		void AddKey( const wchar_t* cwszKey, const wchar_t* cwszKeyValue );
		
		std::wstring GetSectionID() { return m_owszSectionID; }

		std::wstring GetSection() { return m_owszSection; }

	private:
		std::wstring m_owszSection;
		std::wstring m_owszSectionID;
		CEMSObjectMap<std::wstring,std::wstring> m_omapKeyValues;
};

#endif