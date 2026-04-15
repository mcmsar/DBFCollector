//! @file LocateBinStrm.h
//! Header file for the CEMSLocateBinStrm declaration.

#ifndef __LOC_BIN_STRM_H__
#define __LOC_BIN_STRM_H__

//! @class CEMSLocateBinStrm
//! Class used for reading and writing a binary stream containing locate
//! data records.
class CEMSLocateBinStrm : public CEMSBinMsgBody
{
	public:
		CEMSLocateBinStrm();

		CEMSLocateBinStrm( const CEMSLocateBinStrm& locStrm );

		virtual ~CEMSLocateBinStrm();

		virtual EMSVARIANTRECORD* ReadNext();

		virtual void WriteRecord( const EMSVARIANTRECORD& record );

		EMSVARIANTRECORD2* ReadNext2();

		void WriteRecord2( const EMSVARIANTRECORD2& record );
	
};

#endif // __LOC_BIN_STRM_H__