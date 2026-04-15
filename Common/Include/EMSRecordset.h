/*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
*										All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#ifndef __EMS_RECORDSET_H__
#define __EMS_RECORDSET_H__

#include "aobjbase.h"
#include "dal.h"
#include "emsadohelper.h"

#define _USEADO
#ifdef _USEADO
#pragma warning(push)
#pragma warning(disable:4146)
#import <msado15.dll> named_guids, rename("EOF", "EndOfFile" )
#pragma warning(pop)
using namespace ADODB;
#endif

#include <string>

class CEMSConnection;

class CEMSRecordset : public CApiObjBase
{	
	public:
		CEMSRecordset();
		CEMSRecordset( const CEMSRecordset& x );
		~CEMSRecordset();

		long GetNumRecords();
		void MoveFirst();
		void MoveNext();
		void MovePrevious();
		void MoveLast();
		bool IsBOF();
		bool IsEOF();
		void GetDescription( unsigned long& ulDescriptors, EMSFIELDDESCRIPTOR*& aDescriptor,
								unsigned long& ulRecs );
		bool GetData( const unsigned long culRecords, unsigned long& ulBytes, unsigned char*& abyData );
		void Save( const wchar_t* cwszFileSpec );
		void Load( const wchar_t* cwszFileSpec );
		void Open( const wchar_t* cwszCon, const wchar_t* cwszSQL, const bool cbAsync = false );
		void OpenForUpdate( const wchar_t* cwszCon, const wchar_t* cwszSQL, const bool cbAsync = false );
		
		void OpenForUpdateClientSide( const wchar_t* cwszCon, 
			                          const wchar_t* cwszSQL, 
									  const bool cbAsync = false );

		unsigned long GetRecordsize();
		EMSDBOBJECTSTATE GetState();
		void Cancel();
		void Update();
		
		//! Note that only values of DBAFFECT_CURRENT and DBAFFECT_GROUP are allowed for
		//! ceAffect.
		void Delete( const EMSDBAFFECTS ceAffect = DBAFFECT_CURRENT);
		
		void AddNew( const wchar_t* cwszConn, const wchar_t* cwszTableName );
		
		//! This method uses a static cursor so that the client gets updates from the database.  This
		//! is useful when the table has an auto increment type column and we want to immediately retrieve
		//! the value of that column.
		void AddNewEx( const wchar_t* cwszConn, const wchar_t* cwszTableName );

		void SetConnection( CEMSConnection* pConn );
		void Resynch();

		short GetShortValue( const long clIndex );
		short GetShortValue( const wchar_t* cwszFldName );
		unsigned short GetUShortValue( const long clIndex );
		unsigned short GetUShortValue( const wchar_t* cwszFldName );
		long GetLongValue( const long clIndex );
		long GetLongValue( const wchar_t* cwszFldName );
		unsigned long GetULongValue( const long clIndex );
		unsigned long GetULongValue( const wchar_t* cwszFldName );
		__int64 GetI64Value( const long clIndex );
		__int64 GetI64Value( const wchar_t* cwszFldName );
		unsigned __int64 GetUI64Value( const long clIndex );
		unsigned __int64 GetUI64Value( const wchar_t* cwszFldName );
		std::wstring GetWideStringValue( const long clIndex ); 
		std::wstring GetWideStringValue( const wchar_t* cwszFldName );
		std::string GetStringValue( const long clIndex );
		std::string GetStringValue( const wchar_t* cwszFldName );
		void GetBinaryValue( const long clIndex, unsigned long& ulBytes, unsigned char*& abyData );
		void GetBinaryValue( const wchar_t* cwszFldName, unsigned long& ulBytes, unsigned char*& abyData );
		void GetFixedBinaryValue( const long clIndex, const unsigned long culSize, unsigned char* abyData );
		void GetFixedBinaryValue( const wchar_t* cwszFldName, const unsigned long culSize, unsigned char* abyData );
		float GetFloatValue( const long clIndex );
		float GetFloatValue( const wchar_t* cwszFldName );
		double GetDoubleValue( const long clIndex );
		double GetDoubleValue( const wchar_t* cwszFldName );
		char GetByteValue( const long clIndex );
		char GetByteValue( const wchar_t* cwszFldName );
		unsigned char GetUByteValue( const long clIndex );
		unsigned char GetUByteValue( const wchar_t* cwszFldName );
		bool GetBooleanValue( const long clIndex );
		bool GetBooleanValue( const wchar_t* cwszFldName );
		EMSTIME GetDateTime( const long clIndex );
		EMSTIME GetDateTime( const wchar_t* cwszFldName );

		void AddField( const wchar_t* cwszFieldname, const EMSDBFLDTYPE ceDataType, const ULONG culFieldSize = 0 );
		void SetValue( const wchar_t* cwszFieldname, const wchar_t* cwszValue );
		void SetValue( const wchar_t* cwszFieldname, const short csValue );
		void SetValue( const wchar_t* cwszFieldname, const EMSTIME ctimeValue );
		void SetValue( const wchar_t* cwszFieldName, const char ccValue );
		void SetValue( const wchar_t* cwszFieldName, const BYTE cbyValue );
		void SetValue( const wchar_t* cwszFieldName, const double cdValue );
		void SetValue( const wchar_t* cwszFieldName, const ULONG culValue );
		void SetValue( const wchar_t* cwszFieldName, const unsigned __int64 cui64Value );
		
		bool HasField( const wchar_t* cwszFieldname );

	private:
		_RecordsetPtr	_GetRsPtr();

		FieldPtr		_GetFieldPtr( const long clIndex);
		FieldPtr		_GetFieldPtr( const wchar_t* cwszFldName );

		void			_InitDescription();

		void			_ConvertRecord( unsigned long& ulBytes, unsigned char*& abyRec );

		void			_AppendRecord( const long clRecSize, const unsigned char* cabyRecord,
										unsigned long& ulBytes, unsigned char*& abyRecordset );	

		bool			_FilterAlarm( const HRESULT chrErrorCode );

		bool			_IsWarning( const HRESULT chrErrorCode );

		void			_SetValue( const wchar_t* cwszFieldName, const _variant_t cvValue );

		void			_HandleException( const _com_error& croExcpt, const _RecordsetPtr& crspRs );

	private:	// data
		_RecordsetPtr		m_spRs;
		
		CursorTypeEnum		m_eCursorType;
		LockTypeEnum		m_eLockType;
		long				m_lOptions;

		CEMSADOHelper		m_adoHelper;

		unsigned long		m_ulRecordSize;
		unsigned long		m_ulFields;
		EMSFIELDDESCRIPTOR*	m_aFieldDescriptor;

		CEMSConnection*		m_pConn;
};

#endif	// __EMS_RECORDSET_H__