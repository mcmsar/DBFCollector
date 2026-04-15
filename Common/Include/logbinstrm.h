//! @file logBinStrm.h
//! Header file for the CEMSLogBinStrm declaration.

#ifndef __LOG_BIN_STRM_H__
#define __LOG_BIN_STRM_H__

//! @class CEMSLogBinStrm
//! Class used for reading and writing a binary stream containing Log
//! data records.
class CEMSLogBinStrm : public CEMSBinMsgBody
{
	public:
		CEMSLogBinStrm();

		CEMSLogBinStrm( const CEMSLogBinStrm& logStrm );

		virtual ~CEMSLogBinStrm();

		virtual EMSVARIANTRECORD* ReadNext();

		virtual void WriteRecord( const EMSVARIANTRECORD& record );

		EMSVARIANTRECORD2* ReadNext2();

		void WriteRecord2( const EMSVARIANTRECORD2& record );
	
};

#endif // __LOG_BIN_STRM_H__