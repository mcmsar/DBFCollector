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

#ifndef __SOCKET_ADDRESS_H__
#define __SOCKET_ADDRESS_H__

#include "aobjbase.h"
#include <string>

//! Holds a socket address.
class CEMSSocketAddress : public CApiObjBase
{
	public:
		typedef enum tagAddressFamily
		{
			EMSADDRFAMILY_UNKNOWN = 0,
			EMSADDRFAMILY_INET = 1
		} EMSADDRFAMILY;

		CEMSSocketAddress() : m_eFamily( EMSADDRFAMILY_UNKNOWN ), m_usPort(0) {}

		CEMSSocketAddress( const EMSADDRFAMILY ceFamily, const char* cszIP, const unsigned short cusPort ) :
											m_eFamily( ceFamily), m_oszIP( cszIP ), m_usPort( cusPort ) {}

		CEMSSocketAddress( const CEMSSocketAddress& x ) :
											m_eFamily( x.m_eFamily), m_oszIP( x.m_oszIP ), 
											m_usPort( x.m_usPort ) {}

		virtual ~CEMSSocketAddress() {}

		void SetFamily( const EMSADDRFAMILY ceFamily ) { m_eFamily = ceFamily; }
		EMSADDRFAMILY GetFamily() const { return m_eFamily; }

		void SetIP( const char* cszIP ) { if( cszIP ) m_oszIP = cszIP; }
		std::string GetIP() const { return m_oszIP; }

		void SetPort( const unsigned short cusPort ) { m_usPort = cusPort; }
		unsigned short GetPort() const { return m_usPort; }

		bool operator==( const CEMSSocketAddress& croRHS ) 
		{ 
			if( (m_eFamily==croRHS.m_eFamily) && 
				(0==m_oszIP.compare(croRHS.m_oszIP)) && 
				(m_usPort==croRHS.m_usPort) ) 
				return true; 
			else 
				return false; 
		}

		bool operator!=( const CEMSSocketAddress& croRHS )
		{
			return !(*this==croRHS);
		}

	public:

	private:
		EMSADDRFAMILY	m_eFamily;
		std::string		m_oszIP;
		unsigned short	m_usPort;
};

#endif