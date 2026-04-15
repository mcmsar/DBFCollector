/*********************************************************************
*	              Copyright (c) 2004 by EMS Technologies, Inc.,
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

#ifndef __ROUTE_DESCRIPTION_H__
#define __ROUTE_DESCRIPTION_H__

#include "aobjbase.h"
#include <string>

class CEMSRouteDescription : public CApiObjBase
{
	public:
		CEMSRouteDescription();
		CEMSRouteDescription( const CEMSRouteDescription& x );
		~CEMSRouteDescription();

		//! @fn void SetRouteID( const wchar_t* cwszRouteID )
		//! Store the route identifier;
		void SetRouteID( const wchar_t* cwszRouteID );

		//! @fn std::wstring GetRouteID() const
		//! Retrieve the route identifier.
		std::wstring GetRouteID() const;

		//! @fn void SetSourceID( const ULONG culSourceID )
		//! Store the source LUT Identifier.
		void SetSourceID( const ULONG culSourceID );

		//! @fn ULONG GetSourceID() const
		//! Retrieve the source LUT Identifier.
		ULONG GetSourceID() const;

		//! @fn void SetSourceAlias( const wchar_t* cwszAlias )
		//! Store the source alias.
		void SetSourceAlias( const wchar_t* cwszAlias );

		//! @fn std::wstring GetSourceAlias() const
		//! Retrieve the source alias.
		std::wstring GetSourceAlias() const;

		//! @fn void SetDestinationID( const ULONG culDestID )
		//! Store the destination LUT Identifier.
		void SetDestinationID( const ULONG culDestID );

		//! @fn ULONG GetDestinationID() const
		//! Retrieve the destination LUT Identifier.
		ULONG GetDestinationID() const;

		//! @fn void SetDestinationAlias( const wchar_t* cwszAlias )
		//! Store the destination alias.
		void SetDestinationAlias( const wchar_t* cwszAlias );

		//! @fn std::wstring GetDestinationAlias() const
		//! Retrieve the destination alias.
		std::wstring GetDestinationAlias() const;

	private:
		std::wstring	m_wszRouteID;
		ULONG			m_ulSourceID;
		std::wstring	m_wszSourceAlias;
		ULONG			m_ulDestID;
		std::wstring	m_wszDestAlias;
};

#endif