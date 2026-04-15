/*******************************************************************************
*	Copyright (c) 2012 by Honeywell International, Inc., All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
*	reproduced in whole or in part, in any form or by any means whatsoever 
*	without the express written permission of Honeywell International, Inc.
*
********************************************************************************/

#ifndef __BINARY_CONTAINER_H__
#define __BINARY_CONTAINER_H__

#include "aobjbase.h"

//!
// Wraps a byte array (binary) in an object container.
class BinaryContainer : public CApiObjBase
{
	public:
		BinaryContainer();
		BinaryContainer( const BYTE* cBuffer, const int ciSize );
		BinaryContainer( const BinaryContainer& e );
		virtual ~BinaryContainer();

		void Set( const BYTE* cBuffer, const int ciSize );
		int GetSize() const { return m_iSize; }
		const BYTE* GetBuffer() const { return m_buffer; }

	private:
		void _Clear();

	private:
		BYTE* m_buffer;
		int m_iSize;
};

#endif