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

#ifndef __DAL_CLIENT_H__
#define __DAL_CLIENT_H__

#include "aobjbase.h"

#include "dal.h"

//! @class CEMSDALClient
//! Client class for accessing the DAL service.
class CEMSDALClient : public CApiObjBase
{
	public:
		CEMSDALClient();
		CEMSDALClient( const CEMSDALClient& x );
		~CEMSDALClient();

		//! @fn void GetData( EMSDALCACHEID* pCacheID, const ULONG culMaxRecords, const bool cbReturnDescriptor, const wchar_t* wszConnection, const wchar_t* cwszSQL, bool* pbCacheOverflowed, ULONG* pulTotalRecords, ULONG* pulRecordSize,	ULONG* pulFields, EMSFIELDDESCRIPTOR** paFields, ULONG* pulDataSize, unsigned char** pabyData )
		//! This method is a proxy for IEMSDAL::GetData().
		//! The caller must release the output only parameters (the rest are in or in/out and
		//! are caller allocated).
		//!	@param paFields Pointer to an array of field descriptors.  The array must be released.  For a Windows build, use CoTaskMemFree().
		//!	@param pabyData Pointer to an array of binary data.  The array must be released.  For a Windows build, use CoTaskMemFree().
		void GetData( EMSDALCACHEID* pCacheID, const ULONG culMaxRecords,
						const bool cbReturnDescriptor, const wchar_t* wszConnection,
						const wchar_t* cwszSQL, bool* pbCacheOverflowed, 
						ULONG* pulTotalRecords, ULONG* pulRecordSize,
						ULONG* pulFields, EMSFIELDDESCRIPTOR** paFields, 
						ULONG* pulDataSize, unsigned char** pabyData );

	private:
		IEMSDALVariable* _Connect();

};

#endif