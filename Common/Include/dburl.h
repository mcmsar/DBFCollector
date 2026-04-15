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

#ifndef __DBURL_H__
#define __DBURL_H__

#include "emsurl.h"

//! Access members of an URL based on the db (database) scheme.
class CEMSDBURL : public CEMSURL
{
	public:
		CEMSDBURL();
		CEMSDBURL( const CEMSDBURL& x );
		CEMSDBURL( const wchar_t* cwszURL );
		virtual ~CEMSDBURL();

		//! Set the SQL string.
		void SetSQL( const wchar_t* cwszSQL );

		//! Get the SQL string.
		std::wstring GetSQL();

		//! Set the connection string.  A NULL or empty string will cause the default connection
		//! name to be used.
		void SetConnection( const wchar_t* cwszCon );

		//! Get the database connection string.
		std::wstring GetConnection();

		//! Set the chunk size for retrieval.
		void SetChunkSize( const ULONG culChunkSize );

		//! Get the size of each data chunk retrieved in a single call to the source.
		ULONG GetChunkSize();

		//! Set the maximum size of the local buffer.
		void SetMaxBufferSize( const ULONG culMaxSize );

		//! Get the maximum size of the buffer to use
		ULONG GetMaxBufferSize();

		//! Get the name of the table to be tested for new data if this URL points at an
		//! active resource.
		std::wstring GetActiveTable();

		//! Get the name of the column to be tested for new data if this URL points at an
		//! active resource.
		std::wstring GetActiveColumn();
		
		//! Get the query critieria to use while testing for new data if this URL points at an
		//! active resource.
		std::wstring GetActiveCriteria();

		//! Get the period between tests for new data if this URL points at an
		//! active resource.
		ULONG GetActiveTestPeriod();


	private:
		static const wchar_t* ms_cwszMaxRecordsParam;
		static const wchar_t* ms_cwszMaxBufferParam;
		static const wchar_t* ms_cwszSQLParam;
		static const wchar_t* ms_cwszDefaultConnection;
		static const wchar_t* ms_cwszActiveParam;
};

#endif