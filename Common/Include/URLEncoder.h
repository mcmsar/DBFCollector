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

#ifndef __URL_ENCODER_H__
#define __URL_ENCODER_H__

#include <string>

typedef struct tagEncodingTable
{
	wchar_t wCharacter[2];
	wchar_t wEncodedValue[4];
} EMSENCODINGTABLE;


//! Encodes URL strings by replacing reserved characters with their
//! percent encoded equivalent.  Also decodes by replacing percent encoded
//! values with their decoded equivalent.
class CEMSURLEncoder
{
	public:
		CEMSURLEncoder();
		CEMSURLEncoder( const CEMSURLEncoder& x );
		~CEMSURLEncoder();

		std::wstring Encode( const wchar_t* cwszSrc );

		std::wstring Decode( const wchar_t* cwszSrc );

	private:
		std::wstring _Encode( const wchar_t cwChar );

	private:
		static const EMSENCODINGTABLE ms_caEncoding[];
};

#endif