/********************************************************************
*	              Copyright (c) 2011 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef __GLO_SATID_LOOKUP_H__
#define __GLO_SATID_LOOKUP_H__

#include "configurationaccessor.h"

class CEMSGloSatIDLookup
{
	public:
		CEMSGloSatIDLookup();
		CEMSGloSatIDLookup( const CEMSGloSatIDLookup& x );
		~CEMSGloSatIDLookup();

		void Init( const wchar_t* cwszLookupFile );

		ULONG GetSatID( const long clChannel, const long clSlot );

		ULONG GetSatID( const ULONG culNoradNumber );

	private:
		ULONG _DoLookup( const wchar_t* cwszQuery );

	private:
		static const wchar_t* cwszLookupByChannelSlot;
		static const wchar_t* cwszLookupByNoradNum;

	private:
		CEMSConfigurationAccessor m_oTable;
};

#endif