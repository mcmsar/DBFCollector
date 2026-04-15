//! @file Comb406BinStrm.h
//! Header file for the CEMSComb406BinStrm declaration.

#ifndef __COMB406_BIN_STRM_H__
#define __COMB406_BIN_STRM_H__

//! @class CEMSComb406BinStrm
//! Class used for reading and writing a binary stream containing Combined 406
//! data records.
class CEMSComb406BinStrm : public CEMSBinMsgBody
{
	public:
		CEMSComb406BinStrm();

		CEMSComb406BinStrm( const CEMSComb406BinStrm& comb406Strm );

		virtual ~CEMSComb406BinStrm();

		virtual EMSVARIANTRECORD* ReadNext();

		virtual void WriteRecord( const EMSVARIANTRECORD& record );

		EMSVARIANTRECORD2* ReadNext2();

		void WriteRecord2( const EMSVARIANTRECORD2& record );
	
};

#endif // __COMB406_BIN_STRM_H__