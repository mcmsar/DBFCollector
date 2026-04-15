/*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
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
#pragma warning(disable:4786)

#include "dahcalib406ext.h"
#include "sqlbuilder.h"
#include "lutdbschemainfo.h"
#include "convutility.h"


CEMSDAHCalib406Ext::CEMSDAHCalib406Ext()
{
}

CEMSDAHCalib406Ext::CEMSDAHCalib406Ext( const CEMSDAHCalib406Ext& x )
{
}

CEMSDAHCalib406Ext::~CEMSDAHCalib406Ext()
{
}

CEMSPointerList<CEMSRawDataRecordReader> 
CEMSDAHCalib406Ext::Get( const ULONG culColumns, const wchar_t** cawszColumns, const ULONG culLutID,
						const EMSTIME ctimeStart, const EMSTIME ctimeEnd, const bool cbDistinct )
{
	CEMSPointerList<CEMSRawDataRecordReader> olstRet;


	if( culColumns &&
		cawszColumns )
	{
		CSQLBuilder oSQLBuilder;

		if( cbDistinct )
		{
			oSQLBuilder.AddSelectDistinctColumns( culColumns, cawszColumns );
		}
		else
		{
			oSQLBuilder.AddSelectColumns( culColumns, cawszColumns );
		}

		oSQLBuilder.AddFrom();
		oSQLBuilder.AddTable( CEMSLUTDBSchemaInfo::GetTableName( EMSRT_CALIB406_EXT, EMSDBVERSION_LEO_20 ).c_str() );

		bool bConditionAdded = false;

		if( 0 != culLutID )
		{
			if( !bConditionAdded )
				oSQLBuilder.AddWhere();

			oSQLBuilder += cwszLutID;
			oSQLBuilder.AddEQ();
			oSQLBuilder += CEMSConversionUtil::ConvertToString( culLutID ).c_str();

			bConditionAdded = true;
		}

		if( 0 != ctimeEnd.intTime )
		{
			if( !bConditionAdded )
				oSQLBuilder.AddWhere();

			if( bConditionAdded )
				oSQLBuilder.AddAnd();

			oSQLBuilder += cwszCalib406TimeMsg;
			oSQLBuilder.AddLE();
			oSQLBuilder += CEMSConversionUtil::ConvertToString( ctimeEnd.intTime ).c_str();

			bConditionAdded = true;
		}

		if( 0 != ctimeStart.intTime )
		{
			if( !bConditionAdded )
				oSQLBuilder.AddWhere();

			if( bConditionAdded )
				oSQLBuilder.AddAnd();

			oSQLBuilder += cwszCalib406TimeMsg;
			oSQLBuilder.AddGE();
			oSQLBuilder += CEMSConversionUtil::ConvertToString( ctimeStart.intTime ).c_str();

			bConditionAdded = true;
		}

		std::wstring owszSQL = oSQLBuilder;
		
		olstRet = _GetData( 0, owszSQL.c_str() );
	}

	return olstRet;
	
}
