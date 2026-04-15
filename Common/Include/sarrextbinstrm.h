//! @file sarrextBinStrm.h
//! Header file for the CEMSSarrExtBinStrm declaration.

#ifndef __SARREXT_BIN_STRM_H__
#define __SARREXT_BIN_STRM_H__

//! @class CEMSSarrExtBinStrm
//! Class used for reading and writing a binary stream containing SARR
//! Extended data records.
class CEMSSarrExtBinStrm : public CEMSBinMsgBody
{
	public:
		CEMSSarrExtBinStrm();

		CEMSSarrExtBinStrm( const CEMSSarrExtBinStrm& sarrStrm );

		virtual ~CEMSSarrExtBinStrm();

		virtual EMSVARIANTRECORD* ReadNext();

		virtual void WriteRecord( const EMSVARIANTRECORD& record );

		EMSVARIANTRECORD2* ReadNext2();

		void WriteRecord2( const EMSVARIANTRECORD2& record );
	
};

#endif // __SARREXT_BIN_STRM_H__