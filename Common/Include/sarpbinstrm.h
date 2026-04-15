//! @file sarpBinStrm.h
//! Header file for the CEMSSarpBinStrm declaration.

#ifndef __SARP_BIN_STRM_H__
#define __SARP_BIN_STRM_H__

//! @class CEMSSarpBinStrm
//! Class used for reading and writing a binary stream containing SARP
//! data records.
class CEMSSarpBinStrm : public CEMSBinMsgBody
{
	public:
		CEMSSarpBinStrm();

		CEMSSarpBinStrm( const CEMSSarpBinStrm& sarpStrm );

		virtual ~CEMSSarpBinStrm();

		virtual EMSVARIANTRECORD* ReadNext();

		virtual void WriteRecord( const EMSVARIANTRECORD& record );

		EMSVARIANTRECORD2* ReadNext2();

		void WriteRecord2( const EMSVARIANTRECORD2& record );
	
};

#endif // __SARP_BIN_STRM_H__