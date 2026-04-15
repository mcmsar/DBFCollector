#ifndef __DT_BINARYFILE_H__
#define __DT_BINARYFILE_H__

#include "emspipe.h"
#include "dal.h"
#include "aobjbase.h"
#include <string>
#include "emscommontypes.h"
#include "binarystream.h"	// for EMSBINARYSTRMHEADER

class CEMSFileStream;

//! Manages a binary file of the type used by Data Transfer.
class CEMSDTBinaryFile : public CApiObjBase //, IEMSMsgBody2
{
	public:
		CEMSDTBinaryFile();
		CEMSDTBinaryFile( const CEMSDTBinaryFile& binStream );
		virtual ~CEMSDTBinaryFile();

		void SetFilename( const wchar_t* cwszFilename );
		std::wstring GetFilename();
		
		void SetHeader( EMSBINARYSTRMHEADER header );
		EMSBINARYSTRMHEADER GetHeader();
	
		// Read method for second generation version of EMSVARIANTRECORD.
		EMSVARIANTRECORD3* ReadNext();

		// Write method for second generation version of EMSVARIANTRECORD.
		void WriteRecord( const EMSVARIANTRECORD2& record );

		// Write method for 3rd generation version of EMSVARIANTRECORD.
		void WriteRecord( const EMSVARIANTRECORD3& record );

		//! Get the contents of the stream in byte array format.
		void Get( BYTE*& rabyData, ULONG& rulBytes );

		//! Closes and releases the stream pointer, but maintains the file name member.
		void Close();

		//! Closes and releases the stream pointer and clears the file name member.
		void Reset();

	protected:
		void _IncrementCount();
		CEMSBinMsgBody* _AllocMsgBody( const EMSRECORDTYPE ceType );
		IEMSRandomStream* _GetStream();

	private:
		CEMSFileStream* m_pStrm;
		std::wstring	m_owszFilename;
};

#endif