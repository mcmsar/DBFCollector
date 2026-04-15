//! @file CBCBinStrm.h
//! Header file for the CEMSCBCBinStrm declaration.

#ifndef __CBC_BIN_STRM_H__
#define __CBC_BIN_STRM_H__

//! @class CEMSCBCBinStrm
//! Class used for reading and writing a binary stream containing Raw CBC
//! data records.
class CEMSCBCBinStrm : public CEMSBinMsgBody
{
	public:
		CEMSCBCBinStrm();

		CEMSCBCBinStrm( const CEMSCBCBinStrm& cbcStrm );

		virtual ~CEMSCBCBinStrm();

		virtual EMSVARIANTRECORD* ReadNext();

		virtual void WriteRecord( const EMSVARIANTRECORD& record );

		EMSVARIANTRECORD2* ReadNext2();

		void WriteRecord2( const EMSVARIANTRECORD2& record );
	
};

#endif // __CBC_BIN_STRM_H__