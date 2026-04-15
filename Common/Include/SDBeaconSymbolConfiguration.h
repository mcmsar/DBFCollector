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

#ifndef __SD_BEACON_SYMBOL_CONFIG_H__
#define __SD_BEACON_SYMBOL_CONFIG_H__

#include "aobjbase.h"
#include <string>

class CEMSSDBeaconSymbolConfig : public CApiObjBase
{
	public:
		CEMSSDBeaconSymbolConfig( const wchar_t* cwszASideBmp, const wchar_t* cwszBSideBmp, 
									const int ciPointSize ) : m_wszSideA( cwszASideBmp ), 
															  m_wszSideB( cwszBSideBmp ), 
															  m_iPointSize( ciPointSize ) {}
		CEMSSDBeaconSymbolConfig() : m_iPointSize(0) {}

		CEMSSDBeaconSymbolConfig( const CEMSSDBeaconSymbolConfig& x ) : m_wszSideA( x.m_wszSideA ), 
																	m_wszSideB( x.m_wszSideA ), 
																	m_iPointSize( x.m_iPointSize ) {}
		~CEMSSDBeaconSymbolConfig() {}

		std::wstring GetSideABitmap() { return m_wszSideA; }

		std::wstring GetSideBBitmap() { return m_wszSideB; }

		int GetPointSize() { return m_iPointSize; }


	private:
		std::wstring m_wszSideA;
		std::wstring m_wszSideB;
		int m_iPointSize;

};

#endif