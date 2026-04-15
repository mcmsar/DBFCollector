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

#ifndef __LINGER_H__
#define __LINGER_H__

#include <string>

//! Maintains information about a specific socket that specifies how that socket should behave 
//! when data is queued to be sent and the closesocket function is called on the socket.
class CEMSLinger
{
	public:
		CEMSLinger() : m_usOnOff(0), m_usLinger(0) {}

		CEMSLinger( const CEMSLinger& x ) : m_usOnOff( x.m_usOnOff ), m_usLinger( x.m_usLinger ) {}

		CEMSLinger( const unsigned short cusOnOff, const unsigned short cusLinger ) : m_usOnOff( cusOnOff ), m_usLinger( cusLinger ) {}

		~CEMSLinger() {}

		void SetOnOff( const unsigned short cusValue ) { m_usOnOff = cusValue; }

		unsigned short GetOnOff() { return m_usOnOff; }

		void SetLinger( const unsigned short cusValue ) { m_usLinger = cusValue; }

		unsigned short GetLinger() { return m_usLinger; }

#ifndef _NO_XML_
		//! Output data contents as an XML string of the form:
		//!		<Linger>
		//!			<OnOff></OnOff>
		//!			<Timeout></Timeout>
		//!		<Linger>
		std::string Serialize();

		//! Reconstitute member data from XML string.
		void Deserialize( const char* cwszData );
#endif

	private:
		//! Non-zero to enable linger.
		unsigned short m_usOnOff;

		//! Desired timeout in seconds.
		unsigned short m_usLinger;

	private:
		static const wchar_t* ms_cwszOnOff;
		static const wchar_t* ms_cwszTimeout;

};

#endif