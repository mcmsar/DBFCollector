//! @file BinaryStream.h
//! This file contains the declaration of the CEMSBinaryStream class.

#ifndef __BINARY_STREAM_H__
#define __BINARY_STREAM_H__

#include "aobjbase.h"
#include "imsgbody.h"
#include "URLHandler.h"

class CApiObjBase;
class CEMSBinMsgBody;

typedef struct tagBinaryStrmHeader
{
	char szEMSString[64];
	EMSTRIGGER trigger;
	EMSTIME timeCreation;
	EMSTIME timeModified;
	EMSTIME timeProcessed;
	unsigned long ulSourceID;
	unsigned long ulDestID;
	EMSGATEWAYTOKEN secToken;
	EMSRECORDTYPE eRecType;
	unsigned short usDataVersion;
	unsigned long ulRecordCount;
	unsigned long ulSessionID;
	wchar_t wszStreamName[128];
	// The following are used if this is a "circular" stream.
	// They are maintained by the CEMSRandBinaryStream derived class.
	unsigned long ulWriteOffset;
	unsigned long ulMaxRecords;
} EMSBINARYSTRMHEADER;

//! @class CEMSBinaryStream
//! The base class used for reading/writing binary data from and to a stream.
//! Intended use is as either a reader or writer for sequential access
//! Either:
//!		GetHeader(), ReadNext(), ReadNext(), ReadNext() ...
//! Or
//!		SetHeader(), WriteRecord(), WriteRecord(), .... 
class CEMSBinaryStream : public CApiObjBase, IEMSMsgBody2
{
	public:
		CEMSBinaryStream();
		CEMSBinaryStream( const CEMSBinaryStream& binStream );

		virtual ~CEMSBinaryStream();

		void SetSourceURL( const wchar_t* wszURL );
		void SetSourceURL( const unsigned long culBytes, const unsigned char* cabyURL );

		wchar_t* GetSourceURL();
		const wchar_t* GetSpec();

		void SetHeader( EMSBINARYSTRMHEADER header );
	
		EMSBINARYSTRMHEADER GetHeader();

		//! @fn EMSVARIANTRECORD* ReadNext()
		//! Reads the next record in the stream.  The caller must delete the returned pointer.
		EMSVARIANTRECORD* ReadNext();
		//! @fn void WriteRecord( const EMSVARIANTRECORD& record );
		//! Write a single record to the end of the stream
		void WriteRecord( const EMSVARIANTRECORD& record );

		static const char* GetEMSString() { return ms_cszEMSIdentifier; }

		void Close();

		std::wstring GetSource() { return m_urlHandler.GetSource(); }
		std::wstring GetDestination() { return m_urlHandler.GetDestination(); }

		// Read method for second generation version of EMSVARIANTRECORD.
		EMSVARIANTRECORD2* ReadNext2();

		// Write method for second generation version of EMSVARIANTRECORD.
		void WriteRecord2( const EMSVARIANTRECORD2& record );

		//! Get the contents of the stream in byte array format.
		void Get( BYTE*& rabyData, ULONG& rulBytes );

		//! Modify the header without changing the body of the file.
		void UpdateHeader( const EMSBINARYSTRMHEADER& crstrHeader );

	protected:
		CEMSBinMsgBody* _AllocMsgBody();

		// get stream, positioned at the end of the file
		IEMSSeqStream* _GetStream( const bool cbWriteable = false ); 

		//! Get stream, positioned at the beginning of the file.
		IEMSSeqStream* _GetStreamStart( const bool cbWriteable = false ); 

		CEMSURLHandler m_urlHandler;
		IEMSSeqStream* m_pStrm;

		bool m_bHeaderRead;
		EMSBINARYSTRMHEADER m_Header;

		// Local copies of information held in the header
		EMSRECORDTYPE m_eType;

		// To be used to populate the EMSString in the header
		static const char* ms_cszEMSIdentifier;
};

#endif // __BINARY_STREAM_H__