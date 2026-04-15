/*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
*										All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef __DAL_CMD_H__
#define __DAL_CMD_H__

#include "igateway.h"
#include <string>

class CEMSCommandProcessor;

typedef enum tagDALCmdTypes
{
	DALCMD_UNKNOWN = 0,
	DALCMD_GET_DATA = 1,
	DALCMD_LAST
} EMSDALCOMMAND;

const unsigned long MAX_OUTPUT_FILENAME = 256;
const unsigned long MAX_CONNECTION_STRING_SIZE = 256;
const unsigned long MAX_QUERY_LENGTH = 4096;

typedef struct tagDALCommandStructure
{
	EMSDALCOMMAND eType;
	EMSDALCACHEID cacheID;
	unsigned long ulMax;
	bool bDesc;
	wchar_t wszOutputFile[ MAX_OUTPUT_FILENAME + 1];
	wchar_t wszCon[ MAX_CONNECTION_STRING_SIZE + 1];
	wchar_t wszQuery[ MAX_QUERY_LENGTH + 1 ];

} EMSDALCOMMANDSTRUCTURE;

//! @class CEMSDALCmd
//! This class is used for creating and reading Data Access Layer commands from the 
//! EMSPipeline.
class CEMSDALCmd
{
	public:
		CEMSDALCmd();
		CEMSDALCmd( const CEMSDALCmd& x );
		~CEMSDALCmd();

		inline EMSDALCOMMAND GetCommandType() { return m_eType; }
		inline void SetCommandType( const EMSDALCOMMAND ceType ) { m_eType = ceType; }

		inline void SetCacheID( const EMSDALCACHEID cCacheID ) { m_cacheID = cCacheID; }
		inline EMSDALCACHEID GetCacheID() const { return m_cacheID; }

		inline void SetMaxRecords( const unsigned long culMax ) { m_ulMax = culMax; }
		inline unsigned long GetMaxRecords() const { return m_ulMax; }

		inline void SetReturnDescriptor( const bool cbDesc ) { m_bDesc = cbDesc; }
		inline bool GetReturnDescriptor() const { return m_bDesc; }

		inline void SetOutputFile( const wchar_t* cwszOutputFile ) { m_wszOutputFile = cwszOutputFile; }
		inline std::wstring GetOutputFile() const { return m_wszOutputFile; }

		inline void SetConnection( const wchar_t* cwszConnection ) { m_wszCon = cwszConnection; }
		inline std::wstring GetConnection() const { return m_wszCon; }

		inline void SetQuery( const wchar_t* cwszQuery ) { m_wszQuery = cwszQuery; }
		inline std::wstring GetQuery() const { return m_wszQuery; }

		EMSDALCOMMANDSTRUCTURE Serialize( const EMSDALCOMMAND ceCmdType );
		void Deserialize( const EMSDALCOMMANDSTRUCTURE* cpCmdDAL );

	private:	// methods
		void _SetLuts( TCHAR* szLuts );
		void _SetDataTypes( TCHAR* szDataTypes );

	private:	// data
		EMSDALCACHEID	m_cacheID;
		unsigned long	m_ulMax;
		bool			m_bDesc;
		std::wstring	m_wszOutputFile;
		std::wstring	m_wszCon;
		std::wstring	m_wszQuery;

		EMSDALCOMMAND m_eType;
};


#endif // __DAL_CMD_H__