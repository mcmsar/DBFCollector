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
#ifndef __RAW_DATA_RECORD_H__
#define __RAW_DATA_RECORD_H__

#include "aobjbase.h"

//! @class CEMSRawDataRecord
//! A container class for a data record in raw binary array format.
class CEMSRawDataRecord : public CApiObjBase
{
	public:
		CEMSRawDataRecord();
		CEMSRawDataRecord( const ULONG culBufferSize, const unsigned char* cabyData );
		CEMSRawDataRecord( const CEMSRawDataRecord& x );
		virtual ~CEMSRawDataRecord();

		//! @fn void Set( const ULONG culBufferSize, const unsigned char* cabyData )
		//! Store the specified data.
		void Set( const ULONG culBufferSize, const unsigned char* cabyData );

		//! @fn ULONG GetBufferSize()
		//! Retrieves the size of the buffer.
		ULONG GetBufferSize() { return m_ulBufferSize; }

		//! @fn const unsigned char* GetPointerToBuffer()
		//! Retrieves a pointer to the contained buffer.
		const unsigned char* GetPointerToBuffer() { return m_abyRawData; }

		//! @fn unsigned char* GetData()
		//! Retrieves a copy of the buffer.  The caller must delete[] the 
		//! returned array.
		unsigned char* GetData();

	private:
		void _Copy( const ULONG culBufferSize, const unsigned char* cabyData );
		void _Clear();

	private:
		ULONG m_ulBufferSize;
		unsigned char* m_abyRawData;
};

#endif
