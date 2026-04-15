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
	 2    Common    1.1         11/02/2005 4:16:30 PM  Jason Bass      Added new
	      constructor.
	 1    Common    1.0         10/02/2005 2:38:32 PM  Jason Bass      
	$
********************************************************************/

#ifndef __RECORD_META_DATA_H__
#define __RECORD_META_DATA_H__

#include "aobjbase.h"
#include "dal.h"
#include <string>

class CEMSRecordMetaData : public CApiObjBase
{
	public:
		CEMSRecordMetaData();
		CEMSRecordMetaData( const CEMSRecordMetaData& x );
		CEMSRecordMetaData( const ULONG culFields, const EMSFIELDDESCRIPTOR* caDescriptors );
		virtual ~CEMSRecordMetaData();

		void Set( const ULONG culFields, const EMSFIELDDESCRIPTOR* caDescriptors );

		const EMSFIELDDESCRIPTOR* GetDescriptorPtr( const ULONG culIndex );
		ULONG GetNumberFields() { return m_ulFields; }

		long GetSize( const ULONG culIndex );
		std::wstring GetName( const ULONG culIndex );

		long GetIndex( const wchar_t* cwszColumn );

		void AllocateCopy( ULONG& ulFields, EMSFIELDDESCRIPTOR*& aFields );

	private:
		void _Set(  const ULONG culFields, const EMSFIELDDESCRIPTOR* caDescriptors );
		void _Clear();
		void _AllocateCopy
			(	const ULONG					culOrigFields,
				const EMSFIELDDESCRIPTOR*	caOrigFields,
				ULONG&						ulFields, 
				EMSFIELDDESCRIPTOR*&		aFields );

	private:
		ULONG m_ulFields;
		EMSFIELDDESCRIPTOR* m_aDescriptors;
};


#endif