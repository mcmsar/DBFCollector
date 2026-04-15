/*********************************************************************
*	              Copyright (c) 2007 by EMS Technologies, Inc.,
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

#ifndef __BRRECORDS_H__
#define __BRRECORDS_H__

#include "aobjbase.h"
#include "configurationaccessor.h"
#include "pointerlist.h"
#include <string>

class CEMSBRRecord;

//! Represents a set of Beacon Registry records.
class CEMSBRRecords : public CApiObjBase
{
	public:
		CEMSBRRecords();
		//! Create a new instance from a set of records in XML format defined by the C/S IRDB.
		CEMSBRRecords( const wchar_t* cwszRecord );
		CEMSBRRecords( const CEMSBRRecords& x );
		~CEMSBRRecords();

		//! Input a set of records in XML format defined by the C/S IRDB.
		void Set( const wchar_t* cwszRecord );

		//! Retrieve a set of records in XML format defined by the C/S IRDB.
		std::wstring Get();

		//! Retrieve the number of records.
		ULONG GetCount();

		//! Add a Beacon Registry record.
		void Add( const CEMSBRRecord& croBR );

		CEMSPointerList<CEMSBRRecord> GetRecords();

	public:
		static const wchar_t* ms_cwszRoot;
		static const wchar_t* ms_cwszRootElement;

	private:
		CEMSConfigurationAccessor m_oConfig;
};

#endif