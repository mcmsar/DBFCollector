//! @file statusBinStrm.h
//! Header file for the CEMSStatusBinStrm declaration.

#ifndef __STATUS_BIN_STRM_H__
#define __STATUS_BIN_STRM_H__

//! @class CEMSStatusBinStrm
//! Class used for reading and writing a binary stream containing Status
//! data records.
class CEMSStatusBinStrm : public CEMSBinMsgBody
{
	public:
		CEMSStatusBinStrm();

		CEMSStatusBinStrm( const CEMSStatusBinStrm& statusStrm );

		virtual ~CEMSStatusBinStrm();

		virtual EMSVARIANTRECORD* ReadNext();

		virtual void WriteRecord( const EMSVARIANTRECORD& record );
	
		EMSVARIANTRECORD2* ReadNext2();

		void WriteRecord2( const EMSVARIANTRECORD2& record );
};

#endif // __STATUS_BIN_STRM_H__