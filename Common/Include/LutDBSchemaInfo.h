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

#ifndef __LUT_DB_SCHEMA_INFO_H__
#define __LUT_DB_SCHEMA_INFO_H__

#include <string>
#include "emsdbfieldnames.h"

//! @class CEMSLUTDBSchemaInfo
//! This class provides access to LUT Database schema information.
class CEMSLUTDBSchemaInfo
{
	public:
		CEMSLUTDBSchemaInfo();
		CEMSLUTDBSchemaInfo( const CEMSLUTDBSchemaInfo& x );
		~CEMSLUTDBSchemaInfo();

		static std::wstring GetTableName( const EMSRECORDTYPE ceType, const EMSDBVERSION cVersion );

	private:
};

#endif