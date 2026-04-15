//! @file AudioRiffBinStrm.h
//! Header file for the CEMSAudioRiffBinStrm declaration.

#ifndef __AUDIORIFF_BIN_STRM_H__
#define __AUDIORIFF_BIN_STRM_H__

//! @class CEMSAudioRiff6BinStrm
//! Class used for reading and writing a binary stream containing audio riff
//! data records.
class CEMSAudioRiffBinStrm : public CEMSBinMsgBody
{
	public:
		CEMSAudioRiffBinStrm();

		CEMSAudioRiffBinStrm( const CEMSAudioRiffBinStrm& audioRiffStrm );

		virtual ~CEMSAudioRiffBinStrm();

		virtual EMSVARIANTRECORD* ReadNext();

		virtual void WriteRecord( const EMSVARIANTRECORD& record );

		EMSVARIANTRECORD2* ReadNext2();

		void WriteRecord2( const EMSVARIANTRECORD2& record );
	
};

#endif // __AUDIORIFF_BIN_STRM_H__