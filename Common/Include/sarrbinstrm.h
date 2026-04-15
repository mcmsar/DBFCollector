//! @file sarrBinStrm.h
//! Header file for the CEMSSarrBinStrm declaration.

#ifndef __SARR_BIN_STRM_H__
#define __SARR_BIN_STRM_H__

//! @class CEMSSarrBinStrm
//! Class used for reading and writing a binary stream containing SARR
//! data records.
class CEMSSarrBinStrm : public CEMSBinMsgBody
{
	public:
		CEMSSarrBinStrm();

		CEMSSarrBinStrm( const CEMSSarrBinStrm& sarrStrm );

		virtual ~CEMSSarrBinStrm();

		virtual EMSVARIANTRECORD* ReadNext();

		virtual void WriteRecord( const EMSVARIANTRECORD& record );

		EMSVARIANTRECORD2* ReadNext2();

		void WriteRecord2( const EMSVARIANTRECORD2& record );
	
};

#endif // __SARR_BIN_STRM_H__