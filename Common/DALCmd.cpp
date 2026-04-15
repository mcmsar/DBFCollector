/*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
*										All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#include "dalcmd.h"

#include "emserror.h"
#include "emsexcpt.h"
#include "commandformats.h"
#include "ecmdproc.h"
#include "convutility.h"

CEMSDALCmd::CEMSDALCmd() : m_cacheID(0), m_ulMax(0), m_bDesc(true), 
							m_eType(DALCMD_UNKNOWN)
{
}

CEMSDALCmd::CEMSDALCmd( const CEMSDALCmd& x ) : m_cacheID(0), m_ulMax(0), m_bDesc(true), 
							m_eType(DALCMD_UNKNOWN)
{
}

CEMSDALCmd::~CEMSDALCmd()
{
}

EMSDALCOMMANDSTRUCTURE
CEMSDALCmd::Serialize( const EMSDALCOMMAND ceCmdType )
{
	SetCommandType( ceCmdType );

	EMSDALCOMMANDSTRUCTURE cmdRet;
	memset( &cmdRet, 0, sizeof( EMSDALCOMMANDSTRUCTURE ) );
	
	cmdRet.bDesc = GetReturnDescriptor();
	cmdRet.cacheID = GetCacheID();
	cmdRet.ulMax = GetMaxRecords();
	cmdRet.eType = GetCommandType();
	wcsncpy( cmdRet.wszCon, GetConnection().c_str(), MAX_CONNECTION_STRING_SIZE );
	wcsncpy( cmdRet.wszOutputFile, GetOutputFile().c_str(), MAX_OUTPUT_FILENAME );
	wcsncpy( cmdRet.wszQuery, GetQuery().c_str(), MAX_QUERY_LENGTH );

	return cmdRet;
}

void 
CEMSDALCmd::Deserialize( const EMSDALCOMMANDSTRUCTURE* cpCmdDAL )
{
	if( !cpCmdDAL )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	SetReturnDescriptor( cpCmdDAL->bDesc );
	SetCacheID( cpCmdDAL->cacheID );
	SetMaxRecords( cpCmdDAL->ulMax );
	SetConnection( cpCmdDAL->wszCon );
	SetOutputFile( cpCmdDAL->wszOutputFile );
	SetQuery( cpCmdDAL->wszQuery );
	SetCommandType( cpCmdDAL->eType );
}
