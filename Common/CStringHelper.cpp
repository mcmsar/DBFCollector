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

#include "cstringhelper.h"
#include "convutility.h"

CString 
CEMSCStringHelper::ConvertToCString( const DWORD cdwValue )
{
	CString oszValue = CEMSConversionUtil::ConvertToString( cdwValue ).c_str();

	return oszValue;
}

CString 
CEMSCStringHelper::ConvertToCString( const EMSTIME ctimeValue )
{
	CString oszValue = CEMSConversionUtil::ConvertToDateTimeHiResStringW( ctimeValue ).c_str();

	return oszValue;
}

CString 
CEMSCStringHelper::ConvertToCString( const double cdValue )
{
	CString oszValue = CEMSConversionUtil::ConvertToString( cdValue ).c_str();

	return oszValue;
}