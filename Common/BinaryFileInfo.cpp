#pragma warning(disable:4786)

#include "binaryfileinfo.h"
#include "convutility.h"
#include "emstime.h"
#include "recordtypestringtable.h"
#include "emsexcpt.h"

const wchar_t* cwszSummaryFmt = L"\n\nFilename=%s\nCreation Time=%s\nModified Time=%s"\
	L"\nProcessed Time=%s\nSource ID=%d\nDestination ID=%d\nSecurity Token=%s\nRecord Type=%s"\
	L"\nData Version= %d\nRecord Count=%d\nSession ID=%d";

// Time format:  YYYY:MM:DD(DDD Julian):HH:MM:SS:nS
const wchar_t* cwszTimeFmt = L"%04d:%02d:%02d(%03dJ):%02d:%02d:%02d:%d";

const long EMS_BINARY_FILE_SUMMARY_SIZE = 512;
const long EMS_MAX_TIME_STRING_LENGTH = 64;

CEMSBinaryFileInfo::CEMSBinaryFileInfo()
{
}

CEMSBinaryFileInfo::CEMSBinaryFileInfo( const CEMSBinaryFileInfo& x )
{
	m_binStrm = x.m_binStrm;
	m_lstwszFiles = x.m_lstwszFiles;
	m_itCurrent = x.m_itCurrent;
}

CEMSBinaryFileInfo::~CEMSBinaryFileInfo()
{
}

void 
CEMSBinaryFileInfo::SetFileSpecs( const unsigned long culFiles, const char** caszFiles )
{
	for( unsigned long l = 0; l < culFiles; l++ )
	{
		m_lstwszFiles.push_back( CEMSConversionUtil::ConvertToString( caszFiles[l] ) );
	}

	MoveFirst();
}

void 
CEMSBinaryFileInfo::SetFileSpecs( const unsigned long culFiles, const wchar_t** cawszFiles )
{
	for( unsigned long l = 0; l < culFiles; l++ )
	{
		m_lstwszFiles.push_back( std::wstring( cawszFiles[l] ) );
	}

	MoveFirst();
}

bool 
CEMSBinaryFileInfo::MoveFirst()
{
	bool bRet = true;

	m_itCurrent = m_lstwszFiles.begin();

	if( m_lstwszFiles.end() != m_itCurrent )
	{
		_OpenCurrent();
	}
	else
		bRet = false;

	return bRet;
}
	
bool 
CEMSBinaryFileInfo::MoveNext()
{
	bool bRet = true;

	std::list<std::wstring>::iterator itTemp = m_itCurrent;
	itTemp++;

	if( m_lstwszFiles.end() == itTemp )
	{
		bRet = false;
	}
	else
		m_itCurrent++;

	_OpenCurrent();

	return bRet;
}

std::wstring 
CEMSBinaryFileInfo::GetSummary()
{
	std::wstring wszRet;

	wchar_t wszSummary[ EMS_BINARY_FILE_SUMMARY_SIZE + 1 ];

	
	std::wstring wszTimeCreation = _GetCreationTime();
	std::wstring wszTimeModified = _GetModifiedTime();
	std::wstring wszTimeProcessed = _GetProcessedTime();
	std::wstring wszSecurityToken = _GetSecurityToken();
	std::wstring wszRecordType = _GetRecordType();

	swprintf( wszSummary, cwszSummaryFmt, (*m_itCurrent).c_str(), wszTimeCreation.c_str(),
											wszTimeModified.c_str(), wszTimeProcessed.c_str(),
											m_binStrm.GetHeader().ulSourceID, m_binStrm.GetHeader().ulDestID,
											wszSecurityToken.c_str(), wszRecordType.c_str(), 
											m_binStrm.GetHeader().usDataVersion, m_binStrm.GetHeader().ulRecordCount,
											m_binStrm.GetHeader().ulSessionID );
							
	wszRet = wszSummary;

	return wszRet;
}

void 
CEMSBinaryFileInfo::GetData( unsigned long* plRecords, EMSVARIANTRECORD**& apData )
{
	if( !plRecords )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	*plRecords = 0;

	try
	{

		if( m_binStrm.GetHeader().ulRecordCount > 0 )
		{
			apData = new EMSVARIANTRECORD*[m_binStrm.GetHeader().ulRecordCount];

			if( !apData )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			memset( apData, 0, m_binStrm.GetHeader().ulRecordCount*sizeof(EMSVARIANTRECORD*) );

			EMSVARIANTRECORD* pRec = m_binStrm.ReadNext();

			while( pRec )
			{
				apData[(*plRecords)] = pRec;
				(*plRecords)++;

				pRec = m_binStrm.ReadNext();
			}
		}
	}
	catch( ... )
	{
		if( apData )
		{
			for( long l = 0; l < *plRecords; l++ )
			{
				if( apData[l] )
				{
					delete apData[l];
					apData[l] = 0;
				}
			}

			delete[] apData;
			apData = 0;
		}

		throw;
	}

}

void 
CEMSBinaryFileInfo::GetData2( unsigned long* plRecords, EMSVARIANTRECORD2**& apData )
{
	if( !plRecords )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	*plRecords = 0;

	try
	{

		if( m_binStrm.GetHeader().ulRecordCount > 0 )
		{
			apData = new EMSVARIANTRECORD2*[m_binStrm.GetHeader().ulRecordCount];

			if( !apData )
			{
				THROW_NULL_POINTER_EXCEPTION();
			}

			memset( apData, 0, m_binStrm.GetHeader().ulRecordCount*sizeof(EMSVARIANTRECORD2*) );

			EMSVARIANTRECORD2* pRec = m_binStrm.ReadNext2();

			while( pRec )
			{
				apData[(*plRecords)] = pRec;
				(*plRecords)++;

				pRec = m_binStrm.ReadNext2();
			}
		}
	}
	catch( ... )
	{
		if( apData )
		{
			for( long l = 0; l < *plRecords; l++ )
			{
				if( apData[l] )
				{
					delete apData[l];
					apData[l] = 0;
				}
			}

			delete[] apData;
			apData = 0;
		}

		throw;
	}

}

void
CEMSBinaryFileInfo::_OpenCurrent()
{
	m_binStrm.Close();

	if( m_lstwszFiles.end() != m_itCurrent )
		m_binStrm.SetSourceURL( (*m_itCurrent).c_str() );
}

std::wstring	
CEMSBinaryFileInfo::_GetCreationTime()
{
	CEMSTime time( m_binStrm.GetHeader().timeCreation );

	return _FormatTime( &time );
}

std::wstring	
CEMSBinaryFileInfo::_GetModifiedTime()
{
	CEMSTime time( m_binStrm.GetHeader().timeModified );

	return _FormatTime( &time );
}

std::wstring	
CEMSBinaryFileInfo::_GetProcessedTime()
{
	CEMSTime time( m_binStrm.GetHeader().timeProcessed );

	return _FormatTime( &time );
}

std::wstring	
CEMSBinaryFileInfo::_GetSecurityToken()
{
	return CEMSConversionUtil::ConvertToString( (long) 64, (unsigned char*) m_binStrm.GetHeader().secToken.cToken );
}
		
std::wstring	
CEMSBinaryFileInfo::_GetRecordType()
{
	std::wstring wszRet;

	long l = 0;
	bool bFound = false;

	while( (EMSRT_LAST != caRTToStringTable[l].eRT) && !bFound )
	{
		if( caRTToStringTable[l].eRT ==  m_binStrm.GetHeader().eRecType )
		{
			wszRet = caRTToStringTable[l].wszString;
			bFound = true;
		}
		else
			l++;
	}

	if( !bFound )
	{
		wszRet = L"Not found";
	}

	return wszRet;
}
		
std::wstring	
CEMSBinaryFileInfo::_FormatTime( const CEMSTime* cpTime )
{
	std::wstring wszRet;

	EMSTIMEFIELDS timeFields;
	memset( &timeFields, 0, sizeof(EMSTIMEFIELDS) );

	if( cpTime )
	{
		cpTime->GetTime( &timeFields );

		wchar_t wszTime[ EMS_MAX_TIME_STRING_LENGTH + 1 ];
		memset( wszTime, 0, (EMS_MAX_TIME_STRING_LENGTH+1)*sizeof(wchar_t) );

		swprintf( wszTime, cwszTimeFmt, timeFields.nYear, timeFields.nMonth, timeFields.nDay,
										timeFields.nJulianDay, timeFields.nHour, timeFields.nMinute,
										timeFields.nSecond, timeFields.lNanosecond );

		wszRet = wszTime;
	}

	return wszRet;
}