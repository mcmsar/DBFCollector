
#ifndef __BINARY_FILE_INFO_H__
#define __BINARY_FILE_INFO_H__

#include "igateway.h"
#include "dal.h"
#include "binarystream.h"
#include <string>
#include <list>

class CEMSTime;

class CEMSBinaryFileInfo
{
	public:
		CEMSBinaryFileInfo();
		CEMSBinaryFileInfo( const CEMSBinaryFileInfo& x );
		~CEMSBinaryFileInfo();

	public:
		void SetFileSpecs( const unsigned long culFiles, const char** caszFiles );
		void SetFileSpecs( const unsigned long culFiles, const wchar_t** cawszFiles );
		void SetFileSpecs( std::list<std::wstring> lstwszFiles ) { m_lstwszFiles = lstwszFiles; MoveFirst(); }
		void GetData( unsigned long* plRecords, EMSVARIANTRECORD**& apData );
		void GetData2( unsigned long* plRecords, EMSVARIANTRECORD2**& apData );

		bool MoveFirst();
		bool MoveNext();

		std::wstring GetSummary();

	private:
		void			_OpenCurrent();
		std::wstring	_GetCreationTime();
		std::wstring	_GetModifiedTime();
		std::wstring	_GetProcessedTime();
		std::wstring	_GetSecurityToken();
		std::wstring	_GetRecordType();
		std::wstring	_FormatTime( const CEMSTime* cpTime );
		
	private:	// data
		CEMSBinaryStream					m_binStrm;
		std::list<std::wstring>				m_lstwszFiles;
		std::list<std::wstring>::iterator	m_itCurrent;
};

#endif