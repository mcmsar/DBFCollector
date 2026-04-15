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

#include "asatools.h"
#include "emsexcpt.h"
#include <stdio.H>
#include <memory.h>

extern "C" 
{
	#include "dbtools.h"


	short _callback ErrorRtn(
		  char far * errorstr )
	{
	   if( errorstr != NULL ) {
			printf( errorstr );
	   }
	   return( 0 );
	}
}


CEMSASATools::CEMSASATools()
{
	a_dbtools_info   strInfo;
	memset( &strInfo, 0, sizeof( a_dbtools_info) );
	strInfo.errorrtn = (MSG_CALLBACK)ErrorRtn;

	if( 0 != DBToolsInit( &strInfo ) )
	{
		throw CEMSException( EMS_UNKNOWN_ERROR );
	}

}

CEMSASATools::~CEMSASATools()
{
	a_dbtools_info   info;
	memset( &info, 0, sizeof( a_dbtools_info) );
	DBToolsFini( &info ) ;
}

void 
CEMSASATools::DBCreate( const char* cszName, const char* cszLogName )
{
	a_create_db strCreateDB;
	memset( &strCreateDB, 0, sizeof(a_create_db) );

	strCreateDB.dbname = cszName;
	strCreateDB.logname = cszName;
	strCreateDB.page_size = 2048;
	strCreateDB.blank_pad = 2;
//    strCreateDB.respect_case  = 1;
//    strCreateDB.encrypt	= 1;
//    strCreateDB.debug = 1; 	// should be FALSE
//    strCreateDB.dbo_avail = 1;    // doesn't do anything
//    strCreateDB.mirrorname_present	= 1;
//    strCreateDB.avoid_view_collisions	= 1;

	if( 0 != ::DBCreate( &strCreateDB ) )
	{
		throw CEMSException( EMS_UNKNOWN_ERROR );
	}
}