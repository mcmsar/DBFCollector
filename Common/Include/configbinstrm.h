//! @file configBinStrm.h
//! Header file for the CEMSConfigBinStrm declaration.

#ifndef __CONFIG_BIN_STRM_H__
#define __CONFIG_BIN_STRM_H__

//! @class CEMSConfigBinStrm
//! Class used for reading and writing a binary stream containing configuration
//! data records.
class CEMSConfigBinStrm : public CEMSBinMsgBody
{
	public:
		CEMSConfigBinStrm();

		CEMSConfigBinStrm( const CEMSConfigBinStrm& configStrm );

		virtual ~CEMSConfigBinStrm();

		virtual EMSVARIANTRECORD* ReadNext();

		virtual void WriteRecord( const EMSVARIANTRECORD& record );
	
		EMSVARIANTRECORD2* ReadNext2();

		void WriteRecord2( const EMSVARIANTRECORD2& record );
};

#endif // __CONFIG_BIN_STRM_H__