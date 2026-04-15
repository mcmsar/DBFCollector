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

	$Log$
********************************************************************/

#ifndef __GATEWAY_HELPER_H__
#define __GATEWAY_HELPER_H__

#include "aobjbase.h"
#include "igateway.h"

class CEMSGatewayHelper : public CApiObjBase
{
	public:
		CEMSGatewayHelper();
		CEMSGatewayHelper( const CEMSGatewayHelper& x );
		virtual ~CEMSGatewayHelper();

		void SetCallerID( const ULONG culCallerID ) { m_ulCallerID = culCallerID; }

		//! @fn void GetData( ULONG ulDestID, EMSDALCACHEID* pCacheID, const ULONG culMaxRecords, const bool cbReturnDescriptor, const wchar_t* wszConnection, const wchar_t* cwszSQL, bool* pbCacheOverflowed, ULONG* pulTotalRecords, ULONG* pulRecordSize,	ULONG* pulFields, EMSFIELDDESCRIPTOR** paFields, ULONG* pulDataSize, unsigned char** pabyData )
		//! This method is a proxy for IEMSDALGtwy::GetData().  The Gateway connection call
		//! is included.  The caller must release the output only parameters (the rest are in or in/out and
		//! are caller allocated).
		//!	@param paFields Pointer to an array of field descriptors.  The array must be released.  For a Windows build, use CoTaskMemFree().
		//!	@param pabyData Pointer to an array of binary data.  The array must be released.  For a Windows build, use CoTaskMemFree().
		void GetData( ULONG ulDestID, EMSDALCACHEID* pCacheID, const ULONG culMaxRecords,
						const bool cbReturnDescriptor, const wchar_t* wszConnection,
						const wchar_t* cwszSQL, bool* pbCacheOverflowed, 
						ULONG* pulTotalRecords, ULONG* pulRecordSize,
						ULONG* pulFields, EMSFIELDDESCRIPTOR** paFields, 
						ULONG* pulDataSize, unsigned char** pabyData );

	protected:
		void _GetSecurityToken( const ULONG culSrcID, const ULONG culDestID, EMSGATEWAYTOKEN& secToken );
		IEMSGatewayConnection* _Connect();
		ULONG _GetCallerID() { return m_ulCallerID; }

	private:
		ULONG	m_ulCallerID;
};

#endif