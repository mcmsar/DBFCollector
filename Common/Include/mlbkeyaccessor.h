/*********************************************************************
*	              Copyright (c) 2008 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:$
********************************************************************/

#ifndef __MLB_KEY_ACCESSOR_H__
#define __MLB_KEY_ACCESSOR_H__

#include "emstypes.h"
#include "objectmap.h"
#include "criticalsection.h"
#include <string>

//! Accessor for MLB keys.
class CEMSMLBKeyAccessor
{
	public:
		CEMSMLBKeyAccessor();
		CEMSMLBKeyAccessor( const CEMSMLBKeyAccessor& x );
		~CEMSMLBKeyAccessor();

		//! Set the path to the key file and the password needed to decrpyt the file.
		void Init( const char* cszKeyFile, const char* cszPwd );

		//! Retrieve the lat/long keys for the given beacon id.  Returns true if the keys were found, and 
		//! false otherwise.
		bool GetKeys( const INT64 ci64BeaconID, int& riLatKey, int& riLongKey );

	private:
		void _LoadMap();

	private:
		static const wchar_t* ms_cwszBeacon;
		static const wchar_t* ms_cwszID;
		static const wchar_t* ms_cwszLat;
		static const wchar_t* ms_cwszLong;

	private:
		std::string m_oszKeyFile;
		std::string m_oszPwd;

		CEMSCriticalSection m_ocsMapLoad;

		typedef struct tagLatLongPair
		{
			int iLat;
			int iLong;
		} LATLONGPAIR;

		CEMSObjectMap<INT64,LATLONGPAIR> m_omapKeys;

		bool m_bLoadAttempted;
};

#endif