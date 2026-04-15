/*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
*										All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

#pragma warning(disable:4786)	// disable compiler warning for STL debug symbol size.

#include "emsrecordset.h"

#include "emsexcpt.h"
#include "convutility.h"
#include "dalmsgs.h"
#include "emsadohelper.h"
#include "emsconnection.h"

CEMSRecordset::CEMSRecordset() : m_spRs(0), m_eCursorType(adOpenForwardOnly), m_aFieldDescriptor(0),
									m_eLockType( adLockReadOnly ), m_lOptions(adCmdText),
									m_ulFields(0), m_ulRecordSize(0), m_pConn(0)
{
}

CEMSRecordset::CEMSRecordset( const CEMSRecordset& x ) : m_spRs(x.m_spRs), m_eCursorType(x.m_eCursorType), 
									m_eLockType( x.m_eLockType ), m_lOptions(x.m_lOptions),
									m_aFieldDescriptor(0), m_ulFields(0), m_ulRecordSize(0),
									m_pConn( x.m_pConn )
{
	// Don't copy the field description array.

	if( m_pConn )
		m_pConn->AddRef();
}

CEMSRecordset::~CEMSRecordset()
{
	if( m_aFieldDescriptor )
	{
		delete[] m_aFieldDescriptor;
		m_aFieldDescriptor = 0;
	}

	if( NULL != m_spRs )
	{
		try
		{
			if( adStateClosed != m_spRs->GetState() )
			{
				if( !IsEOF() && !IsBOF() )
				{
					EditModeEnum eMode = m_spRs->GetEditMode();

					if( adEditInProgress == eMode ||
						adEditAdd == eMode )
						m_spRs->CancelUpdate();
				}

				m_spRs->Close();
			}
		}
		catch( _com_error& e )
		{
			_HandleException( e, m_spRs );
		}
		catch( ... )
		{
			THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
		}
	}

	if( m_pConn )
	{
		m_pConn->Release();
		m_pConn = NULL;
	}
}

long 
CEMSRecordset::GetNumRecords()
{
	long lRet = 0;

	_RecordsetPtr spRs = _GetRsPtr();

	if( 0 == spRs )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		lRet = spRs->RecordCount;

	}
	catch( _com_error& e )
	{
		_HandleException( e, spRs );
	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return lRet;
}


void 
CEMSRecordset::MoveFirst()
{
	_RecordsetPtr spRs = _GetRsPtr();

	if( 0 == spRs )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		if( !IsEOF() && !IsBOF() )
		{
			EMS_RESULT hr = spRs->MoveFirst();

			if( FAILED(hr) ) 
			{
				THROW_RUNTIME_EXCEPTION( hr );
			}
		}

	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, spRs );
	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}


void 
CEMSRecordset::MoveNext()
{
	_RecordsetPtr spRs = _GetRsPtr();

	if( 0 == spRs )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		EMS_RESULT hr = spRs->MoveNext();

		if( FAILED(hr) ) 
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, spRs );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

void 
CEMSRecordset::MovePrevious()
{
	_RecordsetPtr spRs = _GetRsPtr();

	if( 0 == spRs )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		EMS_RESULT hr = spRs->MovePrevious();

		if( FAILED(hr) ) 
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, spRs );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

void 
CEMSRecordset::MoveLast()
{
	_RecordsetPtr spRs = _GetRsPtr();

	if( 0 == spRs )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		EMS_RESULT hr = spRs->MoveLast();

		if( FAILED(hr) ) 
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, spRs );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

bool 
CEMSRecordset::IsBOF()
{
	bool bRet = false;

	_RecordsetPtr spRs = _GetRsPtr();

	if( 0 == spRs )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		VARIANT_BOOL bBOF = spRs->BOF;

		if( VARIANT_TRUE == bBOF )
		{
			bRet = true;
		}
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, spRs );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return bRet;
}

bool 
CEMSRecordset::IsEOF()
{
	bool bRet = false;

	_RecordsetPtr spRs = _GetRsPtr();

	if( 0 == spRs )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		VARIANT_BOOL bEOF = spRs->EndOfFile;

		if( VARIANT_TRUE == bEOF )
		{
			bRet = true;
		}
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, spRs );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return bRet;
}

void
CEMSRecordset::GetDescription( unsigned long& ulDescriptors, EMSFIELDDESCRIPTOR*& aDescriptor,
								unsigned long& ulRecSize )
{
	ulDescriptors = 0;
	aDescriptor = 0;
	ulRecSize = 0;

	_InitDescription();

	if( m_ulFields > 0 )
	{
		// Make a copy.

		if( !m_aFieldDescriptor )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		ulDescriptors = m_ulFields;
#ifdef WIN32
		aDescriptor = reinterpret_cast<EMSFIELDDESCRIPTOR*>( CoTaskMemAlloc( ulDescriptors*sizeof(EMSFIELDDESCRIPTOR) ));
#else
		aDescriptor = new EMSFIELDDESCRIPTOR[ ulDescriptors ];
#endif

		if( !aDescriptor )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memcpy( aDescriptor, m_aFieldDescriptor, ulDescriptors*sizeof(EMSFIELDDESCRIPTOR) );

		ulRecSize = m_ulRecordSize;
	}

}

void 
CEMSRecordset::_InitDescription()
{
	_RecordsetPtr spRs;

	try
	{
		if( !m_aFieldDescriptor )
		{
			spRs = _GetRsPtr();

			if( 0 == spRs )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			m_ulFields = spRs->Fields->Count;

			if( m_ulFields )
			{
		
				m_aFieldDescriptor = new EMSFIELDDESCRIPTOR[ m_ulFields ];

				if( !m_aFieldDescriptor )
				{
					THROW_NOMEMORY_EXCEPTION();
				}

				memset( m_aFieldDescriptor, 0, m_ulFields*sizeof(EMSFIELDDESCRIPTOR) );

				for( unsigned long l = 0; l < m_ulFields; l++ )
				{
					FieldPtr spField = spRs->Fields->Item[ (long) l ];

					// Convert the ADO type enumerator to an EMS type enumerator.
					m_aFieldDescriptor[l].eType = m_adoHelper.GetEMSDataType( spField->GetType() );

					// Get the size (in bytes) of the field.
					m_aFieldDescriptor[l].lSize = m_adoHelper.GetEMSDataSize( m_aFieldDescriptor[l].eType );

					if( s_clVariableSize == m_aFieldDescriptor[l].lSize )
					{
						// It's a variable size field or an array.  Get it from the provider.
						// Use DefinedSize rather than ActualSize because we want this to be constant
						// across all records.
						m_aFieldDescriptor[l].lSize = spField->DefinedSize;
					}

					// Get the field name.
					wcsncpy( m_aFieldDescriptor[l].wszName, spField->Name, MAX_FIELD_NAME );

					// Add to total record size tally.
					m_ulRecordSize += m_aFieldDescriptor[l].lSize;

				}
			}
		}
	}
	catch( CEMSException& e )
	{
		if( m_aFieldDescriptor )
		{
			delete[] m_aFieldDescriptor;
			m_aFieldDescriptor = 0;
		}

		throw e;
	}
	catch( _com_error& e )
	{
		if( m_aFieldDescriptor )
		{
			delete[] m_aFieldDescriptor;
			m_aFieldDescriptor = 0;
		}

		_HandleException( e, spRs );

	}
	catch( ... )
	{
		if( m_aFieldDescriptor )
		{
			delete[] m_aFieldDescriptor;
			m_aFieldDescriptor = 0;
		}

		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

}

bool 
CEMSRecordset::GetData( const unsigned long culRecords, unsigned long& ulBytes, unsigned char*& abyData )
{
	bool bRet = true;
	ulBytes = 0;
	abyData = 0;
	
	unsigned char* abyRec = 0;

	try
	{
		// Iterate through the records.
		
		//MoveFirst();

		long lRecordsRead = 0;
		bool bEof = IsEOF();

		while( !bEof && (lRecordsRead < culRecords) )
		{
			// Convert the record into a byte array.
			unsigned long ulRecSize = 0;
			_ConvertRecord( ulRecSize, abyRec );

			_AppendRecord( ulRecSize, abyRec, ulBytes, abyData );

			delete[] abyRec;
			abyRec = 0;

			MoveNext();

			bEof = IsEOF();
			bRet = bEof ? false : true;

			lRecordsRead++;

		}

	}
	catch( CEMSException& e )
	{

		if( abyRec )
		{
			delete[] abyRec;
			abyRec = 0;
		}

		throw e;
	}
	catch( _com_error& e )
	{
		if( abyRec )
		{
			delete[] abyRec;
			abyRec = 0;
		}

		std::wstring wszErrMsg;

		wszErrMsg.append( CEMSConversionUtil::HexULongToStringW( e.Error() ) );
		
		if( e.Description().length() > 0 )
		{
			wszErrMsg.append( L" - " );
			wszErrMsg.append( e.Description() );
		}

		CEMSLogMsgParam logParam;

#if defined(UNICODE) || defined(UNICODE)
		logParam += wszErrMsg.c_str();
#else
		logParam += CEMSConversionUtil::ConvertToString( wszErrMsg.c_str() ).c_str();
#endif
		throw CEMSException( EMS_DAL_ADO_ERROR, logParam );

	}
	catch( ... )
	{
		if( abyRec )
		{
			delete[] abyRec;
			abyRec = 0;
		}

		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return bRet;
}

void 
CEMSRecordset::Save( const wchar_t* cwszFileSpec )
{
	THROW_RUNTIME_EXCEPTION( EMS_NOT_IMPLEMENTED );
}

void 
CEMSRecordset::Load( const wchar_t* cwszFileSpec )
{
	THROW_RUNTIME_EXCEPTION( EMS_NOT_IMPLEMENTED );
}

void 
CEMSRecordset::Open( const wchar_t* cwszCon, const wchar_t* cwszSQL, const bool cbAsync )
{
	_RecordsetPtr spRs = _GetRsPtr();

	if( 0 == spRs )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		// Always use a server-side cursor.
		spRs->CursorLocation = adUseServer;

		long lOptions = m_lOptions;

		if( cbAsync )
			lOptions = lOptions | adAsyncExecute;

		_variant_t vConn;

		if( m_pConn )
		{
			vConn.vt = VT_DISPATCH;
			vConn.pdispVal = m_pConn->Get();
		}
		else
		{
			vConn = cwszCon;
		}

		EMS_RESULT hr = spRs->Open( cwszSQL, vConn, m_eCursorType,
						m_eLockType, lOptions );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION(hr);
		}
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, spRs );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

void 
CEMSRecordset::OpenForUpdate( const wchar_t* cwszCon, const wchar_t* cwszSQL, const bool cbAsync)
{
	m_eLockType = adLockOptimistic;
	Open( cwszCon, cwszSQL, cbAsync );
}

void 
CEMSRecordset::OpenForUpdateClientSide( const wchar_t* cwszCon, 
									    const wchar_t* cwszSQL, 
										const bool cbAsync /*= false */ )
{
	_RecordsetPtr spRs = _GetRsPtr();

	if( 0 == spRs )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		spRs->CursorLocation = adUseClient;
		spRs->LockType = adLockOptimistic;
		spRs->CursorType = adOpenStatic;

		long lOptions = m_lOptions;

		if( cbAsync )
			lOptions = lOptions | adAsyncExecute;

		_variant_t vConn;

		if( m_pConn )
		{
			vConn.vt = VT_DISPATCH;
			vConn.pdispVal = m_pConn->Get();
		}
		else
		{
			vConn = cwszCon;
		}

		EMS_RESULT hr = spRs->Open( cwszSQL, vConn, m_eCursorType,
						m_eLockType, lOptions );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION(hr);
		}
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, spRs );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

unsigned long
CEMSRecordset::GetRecordsize()
{
	_InitDescription();

	return m_ulRecordSize;
}

EMSDBOBJECTSTATE 
CEMSRecordset::GetState()
{
	EMSDBOBJECTSTATE eRet = DBOBJ_STATE_UNKNOWN;

	_RecordsetPtr spRs = _GetRsPtr();

	if( 0 == spRs )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		ObjectStateEnum eAdoState = (ObjectStateEnum) spRs->State;

		eRet = m_adoHelper.GetEMSObjectState( eAdoState );

	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, spRs );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return eRet;
}

void 
CEMSRecordset::Cancel()
{
	_RecordsetPtr spRs = _GetRsPtr();

	if( 0 == spRs )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		EMS_RESULT hr = spRs->Cancel();

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, spRs );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

}

void 
CEMSRecordset::Update()
{
	_RecordsetPtr spRs = _GetRsPtr();

	if( 0 == spRs )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		EMS_RESULT hr = spRs->Update();

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}

	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, spRs );
	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

void 
CEMSRecordset::Delete( const EMSDBAFFECTS ceAffect )
{
	_RecordsetPtr spRs = _GetRsPtr();

	if( 0 == spRs )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		// Make sure there is a current record.  Otherwise, the Delete call results in an exception.
		if( !IsEOF() && !IsBOF() )
		{
			EMS_RESULT hr = spRs->Delete( CEMSADOHelper::GetADOAffectType( ceAffect ) );

			if( FAILED(hr) )
			{
				THROW_RUNTIME_EXCEPTION( hr );
			}
		}

	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, spRs );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

void 
CEMSRecordset::AddNew( const wchar_t* cwszCon, const wchar_t* cwszTableName )
{
	_RecordsetPtr spRs = _GetRsPtr();

	if( 0 == spRs )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		// Always use a server-side cursor.
		spRs->CursorLocation = adUseServer;

		_variant_t vConn;

		if( m_pConn )
		{
			vConn.vt = VT_DISPATCH;
			vConn.pdispVal = m_pConn->Get();
		}
		else
		{
			vConn = cwszCon;
		}

		_variant_t vTable = _bstr_t( cwszTableName );

		spRs->Open( vTable, vConn, adOpenKeyset, adLockOptimistic, adCmdTable );
		spRs->AddNew();

	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, spRs );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

void 
CEMSRecordset::AddNewEx( const wchar_t* cwszCon, const wchar_t* cwszTableName )
{
	_RecordsetPtr spRs = _GetRsPtr();

	if( 0 == spRs )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		// Use a client-side cursor.
		spRs->CursorLocation = adUseClient;
		spRs->LockType = adLockOptimistic;
		spRs->CursorType = adOpenStatic;

		_variant_t vConn;

		if( m_pConn )
		{
			vConn.vt = VT_DISPATCH;
			vConn.pdispVal = m_pConn->Get();
		}
		else
		{
			vConn = cwszCon;
		}

		_variant_t vTable = _bstr_t( cwszTableName );

		spRs->Open( vTable, vConn, adOpenKeyset, adLockOptimistic, adCmdTable );
		spRs->AddNew();

	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, spRs );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

void 
CEMSRecordset::SetConnection( CEMSConnection* pConn )
{
	if( m_pConn )
	{
		m_pConn->Release();
		m_pConn = NULL;
	}

	m_pConn = pConn;

	if( m_pConn )
		m_pConn->AddRef();
}

void 
CEMSRecordset::Resynch()
{
	_RecordsetPtr spRs = _GetRsPtr();

	if( 0 == spRs )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		spRs->Resync( adAffectAll, adResyncAllValues);
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, spRs );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

short 
CEMSRecordset::GetShortValue( const long clIndex )
{
	short sRet = 0;

	FieldPtr spField = _GetFieldPtr( clIndex );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();


		// The provider sometime returns a different type in the GetValue call than
		// it does on the GetType call.  So, force it to be honest.
		vValue.ChangeType( VT_I2 );

//		if(  VT_I2 != vValue.vt )
//		{
//			THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_TYPE_UNEXPECTED );
//		}

		sRet = vValue.iVal;
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return sRet;
}

short 
CEMSRecordset::GetShortValue( const wchar_t* cwszFldName )
{
	short sRet = 0;

	FieldPtr spField = _GetFieldPtr( cwszFldName );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();

		// The provider sometime returns a different type in the GetValue call than
		// it does on the GetType call.  So, force it to be honest.
		vValue.ChangeType( VT_I2 );

//		if(  VT_I2 != vValue.vt )
//		{
//			THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_TYPE_UNEXPECTED );
//		}

		sRet = vValue.iVal;
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );
	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return sRet;
}

unsigned short 
CEMSRecordset::GetUShortValue( const long clIndex )
{
	unsigned short usRet = 0;

	FieldPtr spField = _GetFieldPtr( clIndex );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();

		// The provider sometime returns a different type in the GetValue call than
		// it does on the GetType call.  So, force it to be honest.
		vValue.ChangeType( VT_UI2 );

//		if(  VT_UI2 != vValue.vt )
//		{
//			THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_TYPE_UNEXPECTED );
//		}

		usRet = vValue.uiVal;
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );
	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return usRet;
}

unsigned short 
CEMSRecordset::GetUShortValue( const wchar_t* cwszFldName )
{
	unsigned short usRet = 0;

	FieldPtr spField = _GetFieldPtr( cwszFldName );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();

		// The provider sometime returns a different type in the GetValue call than
		// it does on the GetType call.  So, force it to be honest.
		vValue.ChangeType( VT_UI2 );

//		if(  VT_UI2 != vValue.vt )
//		{
//			THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_TYPE_UNEXPECTED );
//		}

		usRet = vValue.uiVal;
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return usRet;
}

long 
CEMSRecordset::GetLongValue( const long clIndex )
{
	long lRet = 0;

	FieldPtr spField = _GetFieldPtr( clIndex );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();

		// The provider sometime returns a different type in the GetValue call than
		// it does on the GetType call.  So, force it to be honest.
		vValue.ChangeType( VT_I4 );

//		if(  VT_I4 != vValue.vt )
//		{
//			THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_TYPE_UNEXPECTED );
//		}

		lRet = vValue.lVal;
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return lRet;
}

long 
CEMSRecordset::GetLongValue( const wchar_t* cwszFldName )
{
	long lRet = 0;

	FieldPtr spField = _GetFieldPtr( cwszFldName );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();

		// The provider sometime returns a different type in the GetValue call than
		// it does on the GetType call.  So, force it to be honest.
		vValue.ChangeType( VT_I4 );

//		if(  VT_I4 != vValue.vt )
//		{
//			THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_TYPE_UNEXPECTED );
//		}

		lRet = vValue.lVal;
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return lRet;
}

unsigned long 
CEMSRecordset::GetULongValue( const long clIndex )
{
	unsigned long ulRet = 0;

	FieldPtr spField = _GetFieldPtr( clIndex );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();

		// The provider sometime returns a different type in the GetValue call than
		// it does on the GetType call.  So, force it to be honest.
		vValue.ChangeType( VT_UI4 );

//		if(  VT_UI4 != vValue.vt )
//		{
//			THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_TYPE_UNEXPECTED );
//		}

		ulRet = vValue.ulVal;
		
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return ulRet;
}

unsigned long 
CEMSRecordset::GetULongValue( const wchar_t* cwszFldName )
{
	unsigned long ulRet = 0;

	FieldPtr spField = _GetFieldPtr( cwszFldName );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();

		// The provider sometime returns a different type in the GetValue call than
		// it does on the GetType call.  So, force it to be honest.
		vValue.ChangeType( VT_UI4 );

//		if(  VT_UI4 != vValue.vt )
//		{
//			THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_TYPE_UNEXPECTED );
//		}

		ulRet = vValue.ulVal;
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return ulRet;
}

__int64 
CEMSRecordset::GetI64Value( const long clIndex )
{
	__int64 i64Ret = 0;

	FieldPtr spField = _GetFieldPtr( clIndex );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();

		// The provider sometime returns a different type in the GetValue call than
		// it does on the GetType call.  So, force it to be honest.
		vValue.ChangeType( VT_DECIMAL );

//		if(  VT_I8 != vValue.vt )
//		{
//			THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_TYPE_UNEXPECTED );
//		}

		i64Ret = vValue.llVal;
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return i64Ret;
}

__int64 
CEMSRecordset::GetI64Value( const wchar_t* cwszFldName )
{
	__int64 i64Ret = 0;

	FieldPtr spField = _GetFieldPtr( cwszFldName );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();

		// The provider sometime returns a different type in the GetValue call than
		// it does on the GetType call.  So, force it to be honest.
		vValue.ChangeType( VT_DECIMAL );

//		if(  VT_I8 != vValue.vt )
//		{
//			THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_TYPE_UNEXPECTED );
//		}

		i64Ret = vValue.llVal;
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return i64Ret;
}

unsigned __int64 
CEMSRecordset::GetUI64Value( const long clIndex )
{
	unsigned __int64 ui64Ret = 0;

	FieldPtr spField = _GetFieldPtr( clIndex );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();

		// The provider sometime returns a different type in the GetValue call than
		// it does on the GetType call.  So, force it to be honest.
		vValue.ChangeType( VT_DECIMAL );

//		if(  VT_UI8 != vValue.vt && VT_DECIMAL != vValue.vt)
//		{
//			THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_TYPE_UNEXPECTED );
//		}

		ui64Ret = vValue.ullVal;
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return ui64Ret;
}

unsigned __int64 
CEMSRecordset::GetUI64Value( const wchar_t* cwszFldName )
{
	unsigned __int64 ui64Ret = 0;

	FieldPtr spField = _GetFieldPtr( cwszFldName );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();

		// The provider sometime returns a different type in the GetValue call than
		// it does on the GetType call.  So, force it to be honest.
		vValue.ChangeType( VT_DECIMAL );

//		if(  VT_UI8 != vValue.vt )
//		{
//			THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_TYPE_UNEXPECTED );
//		}

		ui64Ret = vValue.ullVal;
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return ui64Ret;
}

std::wstring 
CEMSRecordset::GetWideStringValue( const long clIndex )
{
	std::wstring wszRet;

	FieldPtr spField = _GetFieldPtr( clIndex );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();

		if( vValue.vt != VT_EMPTY  &&
			vValue.vt != VT_NULL )
		{

			// The provider sometime returns a different type in the GetValue call than
			// it does on the GetType call.  So, force it to be honest.
			vValue.ChangeType( VT_BSTR );

		
			if(  VT_BSTR != vValue.vt )
			{
				THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_TYPE_UNEXPECTED );
			}

			wszRet = vValue.bstrVal;
		}
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );
	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return wszRet;
}

std::wstring 
CEMSRecordset::GetWideStringValue( const wchar_t* cwszFldName )
{
	std::wstring wszRet;

	FieldPtr spField = _GetFieldPtr( cwszFldName );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();

		if( vValue.vt != VT_EMPTY  &&
			vValue.vt != VT_NULL )
		{
			// The provider sometime returns a different type in the GetValue call than
			// it does on the GetType call.  So, force it to be honest.
			vValue.ChangeType( VT_BSTR );

			if(  VT_BSTR != vValue.vt )
			{
				THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_TYPE_UNEXPECTED );
			}

			wszRet = vValue.bstrVal;
		}
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return wszRet;
}

std::string 
CEMSRecordset::GetStringValue( const long clIndex )
{
	std::string szRet;

	FieldPtr spField = _GetFieldPtr( clIndex );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();

		if( vValue.vt != VT_EMPTY  &&
			vValue.vt != VT_NULL )
		{
			// The provider sometime returns a different type in the GetValue call than
			// it does on the GetType call.  So, force it to be honest.
			vValue.ChangeType( VT_BSTR );

			if(  VT_BSTR != vValue.vt )
			{
				THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_TYPE_UNEXPECTED );
			}

			szRet = CEMSConversionUtil::ConvertToString( vValue.bstrVal );
		}
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return szRet;
}

std::string 
CEMSRecordset::GetStringValue( const wchar_t* cwszFldName )
{
	std::string szRet;

	FieldPtr spField = _GetFieldPtr( cwszFldName );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();

		if( vValue.vt != VT_EMPTY  &&
			vValue.vt != VT_NULL )
		{
			// The provider sometime returns a different type in the GetValue call than
			// it does on the GetType call.  So, force it to be honest.
			vValue.ChangeType( VT_BSTR );

			if(  VT_BSTR != vValue.vt )
			{
				THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_TYPE_UNEXPECTED );
			}

			szRet = CEMSConversionUtil::ConvertToString( vValue.bstrVal ).c_str();
		}
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return szRet;
}

void 
CEMSRecordset::GetBinaryValue( const long clIndex, unsigned long& ulBytes, unsigned char*& abyData )
{
	ulBytes = 0;
	abyData = 0;

	FieldPtr spField = _GetFieldPtr( clIndex );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();

		if(  VT_ARRAY != (vValue.vt & VT_ARRAY) )
		{
			THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_TYPE_UNEXPECTED );
		}

		// Assuming a one-dimensional byte array.
		//ulBytes = vValue.parray->rgsabound[0].cElements;
		ulBytes = spField->ActualSize;

		abyData = new unsigned char[ ulBytes ];

		if( !abyData )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( abyData, 0, ulBytes*sizeof(unsigned char) );

		memcpy( abyData, vValue.parray->pvData, ulBytes*sizeof(unsigned char) );
		
	}
	catch( CEMSException& e )
	{
		if( abyData )
		{
			delete[] abyData;
			abyData = 0;
		}

		ulBytes = 0;

		throw e;
	}
	catch( _com_error& e )
	{
		if( abyData )
		{
			delete[] abyData;
			abyData = 0;
		}

		ulBytes = 0;

		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		if( abyData )
		{
			delete[] abyData;
			abyData = 0;
		}

		ulBytes = 0;

		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

void 
CEMSRecordset::GetBinaryValue( const wchar_t* cwszFldName, unsigned long& ulBytes, 
								unsigned char*& abyData )
{
	ulBytes = 0;
	abyData = 0;

	FieldPtr spField = _GetFieldPtr( cwszFldName );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();

		if(  VT_ARRAY != (vValue.vt & VT_ARRAY) )
		{
			THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_TYPE_UNEXPECTED );
		}

		// Assuming a one-dimensional byte array.
		//ulBytes = vValue.parray->cbElements;
		ulBytes = spField->ActualSize;

		abyData = new unsigned char[ ulBytes ];

		if( !abyData )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( abyData, 0, ulBytes*sizeof(unsigned char) );

		memcpy( abyData, vValue.parray->pvData, ulBytes*sizeof(unsigned char) );
		
	}
	catch( CEMSException& e )
	{
		if( abyData )
		{
			delete[] abyData;
			abyData = 0;
		}

		ulBytes = 0;

		throw e;
	}
	catch( _com_error& e )
	{
		if( abyData )
		{
			delete[] abyData;
			abyData = 0;
		}

		ulBytes = 0;

		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		if( abyData )
		{
			delete[] abyData;
			abyData = 0;
		}

		ulBytes = 0;

		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

void 
CEMSRecordset::GetFixedBinaryValue( const long clIndex, const unsigned long culSize, unsigned char* abyData )
{
	FieldPtr spField = _GetFieldPtr( clIndex );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();

		if(  VT_ARRAY != (vValue.vt & VT_ARRAY) )
		{
			THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_TYPE_UNEXPECTED );
		}

		// Assuming a one-dimensional byte array.
		//unsigned long ulBytes = vValue.parray->cbElements;
		unsigned long ulBytes = spField->ActualSize;

		// Clear the input array.
		memset( abyData, 0, culSize*sizeof(unsigned char) );

		unsigned long ulSize = (ulBytes < culSize) ? ulBytes : culSize;

		memcpy( abyData, vValue.parray->pvData, ulSize*sizeof(unsigned char) );
		
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

void 
CEMSRecordset::GetFixedBinaryValue( const wchar_t* cwszFldName, const unsigned long culSize, 
								   unsigned char* abyData )
{
	FieldPtr spField = _GetFieldPtr( cwszFldName );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();

		if(  VT_ARRAY != (vValue.vt & VT_ARRAY) )
		{
			THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_TYPE_UNEXPECTED );
		}

		// Assuming a one-dimensional byte array.
		//unsigned long ulBytes = vValue.parray->cbElements;
		unsigned long ulBytes = spField->ActualSize;

		// Clear the input array.
		memset( abyData, 0, culSize*sizeof(unsigned char) );

		unsigned long ulSize = (ulBytes < culSize) ? ulBytes : culSize;

		memcpy( abyData, vValue.parray->pvData, ulSize*sizeof(unsigned char) );
		
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

float 
CEMSRecordset::GetFloatValue( const long clIndex )
{
	float fRet = 0.0;

	FieldPtr spField = _GetFieldPtr( clIndex );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();

		// The provider sometime returns a different type in the GetValue call than
		// it does on the GetType call.  So, force it to be honest.
		if( VT_NULL != vValue.vt )
		{
			vValue.ChangeType( VT_R4 );

			if(  VT_R4 != vValue.vt )
			{
				THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_TYPE_UNEXPECTED );
			}

			fRet = vValue.fltVal;
		}
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return fRet;
}

float 
CEMSRecordset::GetFloatValue( const wchar_t* cwszFldName )
{
	float fRet = 0.0;

	FieldPtr spField = _GetFieldPtr( cwszFldName );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();

		// The provider sometime returns a different type in the GetValue call than
		// it does on the GetType call.  So, force it to be honest.
		if( VT_NULL != vValue.vt )
		{
			vValue.ChangeType( VT_R4 );

			if(  VT_R4 != vValue.vt )
			{
				THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_TYPE_UNEXPECTED );
			}

			fRet = vValue.fltVal;
		}
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return fRet;
}

double 
CEMSRecordset::GetDoubleValue( const long clIndex )
{
	double dRet = 0.0;

	FieldPtr spField = _GetFieldPtr( clIndex );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();

		// The provider sometime returns a different type in the GetValue call than
		// it does on the GetType call.  So, force it to be honest.
		if( VT_NULL != vValue.vt )
		{
			vValue.ChangeType( VT_R8 );
			dRet = vValue.dblVal;
		}

	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return dRet;
}

double 
CEMSRecordset::GetDoubleValue( const wchar_t* cwszFldName )
{
	double dRet = 0.0;

	FieldPtr spField = _GetFieldPtr( cwszFldName );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();

		// The provider sometime returns a different type in the GetValue call than
		// it does on the GetType call.  So, force it to be honest.
		if( VT_NULL != vValue.vt )
		{
			vValue.ChangeType( VT_R8 );
			dRet = vValue.dblVal;
		}
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return dRet;
}

char 
CEMSRecordset::GetByteValue( const long clIndex )
{
	char byRet = 0;

	FieldPtr spField = _GetFieldPtr( clIndex );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();

		// The provider sometime returns a different type in the GetValue call than
		// it does on the GetType call.  So, force it to be honest.
		vValue.ChangeType( VT_I1 );

//		if(  VT_I1 != vValue.vt )
//		{
//			THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_TYPE_UNEXPECTED );
//		}

		byRet = vValue.cVal;
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return byRet;
}

char 
CEMSRecordset::GetByteValue( const wchar_t* cwszFldName )
{
	char byRet = 0;

	FieldPtr spField = _GetFieldPtr( cwszFldName );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();

		// The provider sometime returns a different type in the GetValue call than
		// it does on the GetType call.  So, force it to be honest.
		vValue.ChangeType( VT_I1 );

//		if(  VT_I1 != vValue.vt )
//		{
//			THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_TYPE_UNEXPECTED );
//		}

		byRet = vValue.cVal;
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return byRet;
}

unsigned char 
CEMSRecordset::GetUByteValue( const long clIndex )
{
	unsigned char byRet = 0;

	FieldPtr spField = _GetFieldPtr( clIndex );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();

		// The provider sometime returns a different type in the GetValue call than
		// it does on the GetType call.  So, force it to be honest.
		vValue.ChangeType( VT_UI1 );

//		if(  VT_UI1 != vValue.vt )
//		{
//			THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_TYPE_UNEXPECTED );
//		}

		byRet = vValue.bVal;
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return byRet;
}

unsigned char 
CEMSRecordset::GetUByteValue( const wchar_t* cwszFldName )
{
	unsigned char byRet = 0;

	FieldPtr spField = _GetFieldPtr( cwszFldName );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();

		// The provider sometime returns a different type in the GetValue call than
		// it does on the GetType call.  So, force it to be honest.
		vValue.ChangeType( VT_UI1 );

//		if(  VT_UI1 != vValue.vt )
//		{
//			THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_TYPE_UNEXPECTED );
//		}

		byRet = vValue.bVal;
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return byRet;
}

bool
CEMSRecordset::GetBooleanValue( const long clIndex )
{
	bool bRet = false;

	FieldPtr spField = _GetFieldPtr( clIndex );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();

		// The provider sometime returns a different type in the GetValue call than
		// it does on the GetType call.  So, force it to be honest.
		vValue.ChangeType( VT_BOOL );

		bRet = (VARIANT_TRUE == vValue.boolVal) ? true : false;
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return bRet;
}

bool 
CEMSRecordset::GetBooleanValue( const wchar_t* cwszFldName )
{
	bool bRet = 0;

	FieldPtr spField = _GetFieldPtr( cwszFldName );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();

		// The provider sometime returns a different type in the GetValue call than
		// it does on the GetType call.  So, force it to be honest.
		vValue.ChangeType( VT_BOOL );

		bRet = (VARIANT_TRUE == vValue.boolVal) ? true : false;
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return bRet;
}

EMSTIME 
CEMSRecordset::GetDateTime( const long clIndex )
{
	EMSTIME timeRet;
	timeRet.intTime = 0;

	FieldPtr spField = _GetFieldPtr( clIndex );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();

		// The provider sometime returns a different type in the GetValue call than
		// it does on the GetType call.  So, force it to be honest.
		vValue.ChangeType( VT_DATE );

		timeRet = m_adoHelper.GetEMSTime( vValue );
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return timeRet;
}

EMSTIME 
CEMSRecordset::GetDateTime( const wchar_t* cwszFldName )
{
	EMSTIME timeRet;
	timeRet.intTime = 0;

	FieldPtr spField = _GetFieldPtr( cwszFldName );

	if( 0 == spField )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		_variant_t vValue =  spField->GetValue();

		// The provider sometime returns a different type in the GetValue call than
		// it does on the GetType call.  So, force it to be honest.
		vValue.ChangeType( VT_DATE );

		timeRet = m_adoHelper.GetEMSTime( vValue );
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return timeRet;
}

void
CEMSRecordset::AddField( const wchar_t* cwszFieldname, const EMSDBFLDTYPE ceDataType, const ULONG culFieldSize )
{
	_RecordsetPtr spRs;

	try
	{
		spRs = _GetRsPtr();

		if( 0 == spRs )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		CEMSADOHelper oHelper;
		EMS_RESULT hr = spRs->GetFields()->Append( cwszFieldname, 
														oHelper.GetADODataType( ceDataType ), 
														culFieldSize,
														adFldUnspecified );

		if( FAILED( hr ) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, spRs );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

bool
CEMSRecordset::HasField( const wchar_t* cwszFldName )
{
	FieldPtr spField = _GetFieldPtr( cwszFldName );
	return spField? true : false;
}

void 
CEMSRecordset::SetValue( const wchar_t* cwszFieldName, const wchar_t* cwszFieldValue )
{
	if( cwszFieldName && cwszFieldValue && wcslen(cwszFieldValue) )
		_SetValue( cwszFieldName, _variant_t( _bstr_t( cwszFieldValue ) ) );

}

void 
CEMSRecordset::SetValue( const wchar_t* cwszFieldName, const short csValue )
{
	if( cwszFieldName )
		_SetValue( cwszFieldName, _variant_t( csValue ) );
}

void 
CEMSRecordset::SetValue( const wchar_t* cwszFieldName, const EMSTIME ctimeValue )
{
	if( cwszFieldName )
	{
		_SetValue( cwszFieldName, _variant_t( m_adoHelper.GetDate( ctimeValue ) ) );
	}
}

void 
CEMSRecordset::SetValue( const wchar_t* cwszFieldName, const char ccValue )
{
	if( cwszFieldName )
	{
		_variant_t vValue;
		vValue.cVal = ccValue;
		vValue.vt = VT_I1;
		_SetValue( cwszFieldName, vValue );
	}
}

void 
CEMSRecordset::SetValue( const wchar_t* cwszFieldName, const BYTE cbyValue )
{
	if( cwszFieldName )
	{
		_SetValue( cwszFieldName, _variant_t( cbyValue ) );
	}
}

void 
CEMSRecordset::SetValue( const wchar_t* cwszFieldName, const double cdValue )
{
	if( cwszFieldName )
	{
		_SetValue( cwszFieldName, _variant_t( cdValue ) );
	}
}

void 
CEMSRecordset::SetValue( const wchar_t* cwszFieldName, const ULONG culValue )
{
	_variant_t vValue;
	vValue.vt = VT_UI4;
	vValue.ulVal = culValue;
	_SetValue( cwszFieldName, vValue );
}

void 
CEMSRecordset::SetValue( const wchar_t* cwszFieldName, const unsigned __int64 cui64Value )
{
	_variant_t vValue;
	vValue.vt = VT_UI8;
	vValue.ullVal = cui64Value;
	_SetValue( cwszFieldName, vValue );
}

void
CEMSRecordset::_SetValue( const wchar_t* cwszFieldName, const _variant_t cvValue )
{
	try
	{
		if( cwszFieldName &&
			VT_EMPTY != cvValue.vt)
		{
			FieldPtr spFldPtr = _GetFieldPtr( cwszFieldName );

			if( 0 == spFldPtr )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			spFldPtr->PutValue( cvValue );

		}
	}
	catch( CEMSException& e )
	{
		throw e;
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}
}

_RecordsetPtr	
CEMSRecordset::_GetRsPtr()
{
	_RecordsetPtr spRs = 0;

	if( m_spRs == 0 )
	{
		EMS_RESULT hr = m_spRs.CreateInstance( __uuidof(Recordset) );

		if( FAILED(hr) )
		{
			THROW_RUNTIME_EXCEPTION( hr );
		}
	}

	spRs = m_spRs;

	return spRs;

}

FieldPtr
CEMSRecordset::_GetFieldPtr( const long clIndex)
{
	FieldPtr spField = 0;

	_RecordsetPtr spRs = _GetRsPtr();

	if( 0 == spRs )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		spField = spRs->GetFields()->GetItem( _variant_t( clIndex ) );
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return spField;
}


FieldPtr
CEMSRecordset::_GetFieldPtr( const wchar_t* cwszFldName )
{
	FieldPtr spField = 0;

	_RecordsetPtr spRs = _GetRsPtr();

	if( 0 == spRs )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	if( 0 == cwszFldName )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	try
	{
		FieldsPtr spFields = spRs->GetFields();

		if( 0 == spFields )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		try
		{
			spField = spFields->GetItem( cwszFldName );
		}
		catch( ... )
		{
			// If this is a fully qualified column name then try stripping off the table
			// portion of the string.
			std::wstring owszFieldName = cwszFldName;
			std::wstring::size_type iPos = owszFieldName.find( L"." );

			if( std::wstring::npos != iPos &&
				(owszFieldName.length() > (iPos + 2) ) )
			{
				std::wstring owszColumnOnly = owszFieldName.substr( iPos + 1, owszFieldName.length() - 1);

				if( !owszColumnOnly.empty() )
				{
					spField = spFields->GetItem( owszColumnOnly.c_str() );
				}
				else
					throw;
			}
			else
				throw;
		}
	}
	catch( _com_error& e )
	{
		_HandleException( e, _GetRsPtr() );

	}
	catch( ... )
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}

	return spField;
}

void
CEMSRecordset::_ConvertRecord( unsigned long& ulBytes, unsigned char*& abyRec )
{
	abyRec = 0;
	ulBytes = 0;

	_InitDescription();

	if( !m_aFieldDescriptor )
	{
		THROW_RUNTIME_EXCEPTION( EMS_DAL_NO_META_DATA );
	}

	try
	{
		// Allocate the record.  It is only for internal use so "new" okay.
		ulBytes = m_ulRecordSize;

		abyRec = new unsigned char[ ulBytes ];

		if( !abyRec )
		{
			THROW_NOMEMORY_EXCEPTION();
		}

		memset( abyRec, 0, ulBytes*sizeof(unsigned char) );

		unsigned char* pbyData = abyRec;

		// Iterate through the fields.
		for( long l = 0; l < (long) m_ulFields; l++ )
		{
			switch( m_aFieldDescriptor[l].eType )
			{
				case DBFLDTYPE_SHORT:
					{
						short sVal = GetShortValue( l );
						memcpy( pbyData, &sVal, m_aFieldDescriptor[l].lSize );
					}
					break;
				case DBFLDTYPE_USHORT:
					{
						unsigned short usVal = GetUShortValue( l );
						memcpy( pbyData, &usVal, m_aFieldDescriptor[l].lSize );
					}
					break;
				case DBFLDTYPE_LONG:
					{
						long lVal = GetLongValue( l );
						memcpy( pbyData, &lVal, m_aFieldDescriptor[l].lSize );
					}
					break;
				case DBFLDTYPE_ULONG:
					{
						unsigned long ulVal = GetULongValue( l );
						memcpy( pbyData, &ulVal, m_aFieldDescriptor[l].lSize );
					}
					break;
				case DBFLDTYPE_BIGINT:
					{
						__int64 i64Val = GetI64Value( l );
						memcpy( pbyData, &i64Val, m_aFieldDescriptor[l].lSize );
					}
					break;
				case DBFLDTYPE_UBIGINT:
					{
						unsigned __int64 ui64Val = GetUI64Value( l );
						memcpy( pbyData, &ui64Val, m_aFieldDescriptor[l].lSize );
					}
					break;
				case DBFLDTYPE_WSTRING:
					{
						std::wstring wszVal = GetWideStringValue( l );
						memcpy( pbyData, wszVal.c_str(), 
							( (sizeof(wchar_t)*wszVal.length()) >  m_aFieldDescriptor[l].lSize) ? m_aFieldDescriptor[l].lSize : (sizeof(wchar_t)*wszVal.length()) );
					}
					break;
				case DBFLDTYPE_STRING:
					{
						std::string szVal = GetStringValue( l );
						memcpy( pbyData, szVal.c_str(), 
							(szVal.length() > m_aFieldDescriptor[l].lSize) ? m_aFieldDescriptor[l].lSize : szVal.length() );
					}
					break;
				case DBFLDTYPE_BINARY:
				case DBFLDTYPE_LONG_BINARY:
					{
						unsigned char* abyVal = 0;
						unsigned long ulBytes = 0;
						GetBinaryValue( l, ulBytes, abyVal );
					
						if( !abyVal )
						{
							THROW_NULL_POINTER_EXCEPTION();
						}
						
						memcpy( pbyData, abyVal, m_aFieldDescriptor[l].lSize );
						
						delete[] abyVal;
						abyVal = 0;
					}
					break;
				case DBFLDTYPE_FLOAT:
					{
						float fVal = GetFloatValue( l );
						memcpy( pbyData, &fVal, m_aFieldDescriptor[l].lSize );
					}
					break;
				case DBFLDTYPE_DOUBLE:
					{
						double dVal = GetDoubleValue( l );
						memcpy( pbyData, &dVal, m_aFieldDescriptor[l].lSize );
					}
					break;
				case DBFLDTYPE_TINYINT:
					{
						char cVal = GetByteValue( l );
						memcpy( pbyData, &cVal, m_aFieldDescriptor[l].lSize );
					}
					break;
				case DBFLDTYPE_UTINYINT:
					{
						unsigned char byVal = GetUByteValue( l );
						memcpy( pbyData, &byVal, m_aFieldDescriptor[l].lSize );
					}
					break;
				case DBFLDTYPE_BOOLEAN:
					{
						bool bVal = GetBooleanValue( l );
						memcpy( pbyData, &bVal, m_aFieldDescriptor[l].lSize );
					}
					break;
				default:
					THROW_RUNTIME_EXCEPTION( EMS_DAL_UNKOWN_DATATYPE );
			}

			pbyData += m_aFieldDescriptor[l].lSize;
		}
	}
	catch( CEMSException& e )
	{
		if( abyRec )
		{
			delete[] abyRec;
			abyRec = 0;
		}

		throw e;
	}
	catch( _com_error& e )
	{
		if( abyRec )
		{
			delete[] abyRec;
			abyRec = 0;
		}

		std::wstring wszErrMsg;

		wszErrMsg.append( CEMSConversionUtil::HexULongToStringW( e.Error() ) );
		
		if( e.Description().length() > 0 )
		{
			wszErrMsg.append( L" - " );
			wszErrMsg.append( e.Description() );
		}

		CEMSLogMsgParam logParam;

#if defined(UNICODE) || defined(UNICODE)
		logParam += wszErrMsg.c_str();
#else
		logParam += CEMSConversionUtil::ConvertToString( wszErrMsg.c_str() ).c_str();
#endif
		throw CEMSException( EMS_DAL_ADO_ERROR, logParam );

	}
	catch( ... )
	{
		if( abyRec )
		{
			delete[] abyRec;
			abyRec = 0;
		}

		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_EXCEPTION );
	}


}

void
CEMSRecordset::_AppendRecord( const long clRecSize, const unsigned char* cabyRecord,
								unsigned long& ulBytes, unsigned char*& abyRecordset )
{
	if( clRecSize > 0 )
	{
		if( !cabyRecord )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		unsigned char* abyTemp = 0;

		try
		{

			unsigned long ulNewSize = ulBytes + clRecSize;

#ifdef WIN32
			abyTemp = reinterpret_cast<unsigned char*>( CoTaskMemAlloc(  ulNewSize  ) );
#else
			abyTemp = new unsigned char[ ulNewSize ];
#endif

			if( !abyTemp )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			unsigned char* abyStart = abyTemp;

			if( abyRecordset )
			{
				memcpy( abyTemp, abyRecordset, ulBytes );
			
#ifdef WIN32
				CoTaskMemFree( abyRecordset );
#else
				delete[] abyRecordset;
#endif
				abyTemp += ulBytes;
			}

			memcpy( abyTemp, cabyRecord, clRecSize );

			abyRecordset = abyStart;

			ulBytes = ulNewSize;
			
		}
		catch( ... )
		{
			if( abyTemp )
			{
#ifdef WIN32
				CoTaskMemFree( abyTemp );
#else
				delete[] abyTemp;
#endif
				abyTemp = 0;
			}

			throw;
		}
	}
}

bool			
CEMSRecordset::_FilterAlarm( const HRESULT chrErrorCode )
{
	bool bRet = false;

	CEMSADOHelper adoHelper;

	bRet = adoHelper.FilterAlarm( chrErrorCode );

	return bRet;
}

bool			
CEMSRecordset::_IsWarning( const HRESULT chrErrorCode )
{
	bool bRet = false;

	CEMSADOHelper adoHelper;

	bRet = adoHelper.IsWarning( chrErrorCode );

	return bRet;
}

void			
CEMSRecordset::_HandleException( const _com_error& croExcpt, const _RecordsetPtr& crspRs )
{
	std::wstring wszErrMsg;
	wszErrMsg.append( CEMSConversionUtil::HexULongToStringW( croExcpt.Error() ) );
	
	if( croExcpt.Description().length() > 0 )
	{
		wszErrMsg.append( L" - " );
		wszErrMsg.append( croExcpt.Description() );
	}

	if( 0 != crspRs )
	{
		// Get the full set of errors
		_variant_t vConn = crspRs->GetActiveConnection();
		_ConnectionPtr spCon = vConn.pdispVal;

		if( 0 != spCon )
		{

			ErrorsPtr spErrors = spCon->GetErrors();

			long lErrors = spErrors->GetCount();

			
			for( long l = 0; l < lErrors; l++ )
			{
				if( 0 == l )
				{
					wszErrMsg.append(L"  (Error trace:  ");
				}
				else
				{
					wszErrMsg.append(L", ");
				}

				ErrorPtr spError = spErrors->GetItem( l );

				wszErrMsg.append( spError->GetDescription() );
			}

			if( 0 != lErrors )
				wszErrMsg.append( L")" );
		}
	}

	
	CEMSLogMsgParam logParam;

#if defined(UNICODE) || defined(UNICODE)
	logParam += wszErrMsg.c_str();
#else
	logParam += CEMSConversionUtil::ConvertToString( wszErrMsg.c_str() ).c_str();
#endif

	CEMSException oExcept( EMS_DAL_ADO_ERROR, logParam );

	if( _IsWarning( croExcpt.Error() ) )
	{
		oExcept.SetLogAsWarning();
	}
	else if( _FilterAlarm( croExcpt.Error() ) )
	{
		// Don't log as an alarm, but do log an info message.
		oExcept.SetAlarmLogged();		
	}

	throw oExcept;
}