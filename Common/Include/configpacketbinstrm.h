//! @file configPacketBinStrm.h
//! Header file for the CEMSConfigBinStrm declaration.

#ifndef __CONFIGPACKET_BIN_STRM_H__
#define __CONFIGPACKET_BIN_STRM_H__

//! @class CEMSConfigPacketBinStrm
//! Class used for reading and writing a binary stream containing configuration
//! data "packets"
class CEMSConfigPacketBinStrm : public CEMSBinMsgBody
{
	public:
		CEMSConfigPacketBinStrm();

		CEMSConfigPacketBinStrm( const CEMSConfigPacketBinStrm& configPktStrm );

		virtual ~CEMSConfigPacketBinStrm();

		virtual EMSVARIANTRECORD* ReadNext();

		virtual void WriteRecord( const EMSVARIANTRECORD& record );
	
		EMSVARIANTRECORD2* ReadNext2();

		void WriteRecord2( const EMSVARIANTRECORD2& record );
};

#endif // __CONFIGPACKET_BIN_STRM_H__