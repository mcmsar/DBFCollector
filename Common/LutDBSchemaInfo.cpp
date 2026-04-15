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

#include "lutdbschemainfo.h"

CEMSLUTDBSchemaInfo::CEMSLUTDBSchemaInfo()
{
}

CEMSLUTDBSchemaInfo::CEMSLUTDBSchemaInfo( const CEMSLUTDBSchemaInfo& x )
{
}

CEMSLUTDBSchemaInfo::~CEMSLUTDBSchemaInfo()
{
}


std::wstring 
CEMSLUTDBSchemaInfo::GetTableName( const EMSRECORDTYPE ceType, const EMSDBVERSION cVersion )
{
	std::wstring wszRet;

	long lIndex = 0;

	while( ( EMSRT_UNKNOWN != s_caDataTypeTableMapping[lIndex].eRecType ) &&
			wszRet.empty() )
	{
		if( ( ceType == s_caDataTypeTableMapping[lIndex].eRecType ) &&
			( cVersion == s_caDataTypeTableMapping[lIndex].version ) )
		{
			wszRet = s_caDataTypeTableMapping[lIndex].wszTableName;
		}

		lIndex++;
	}

	return wszRet;
}
