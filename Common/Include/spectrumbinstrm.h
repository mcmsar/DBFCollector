//! @file spectrumBinStrm.h
//! Header file for the CEMSSpectrumBinStrm declaration.

#ifndef __SPECTRUM_BIN_STRM_H__
#define __SPECTRUM_BIN_STRM_H__

//! @class CEMSSpectrumBinStrm
//! Class used for reading and writing a binary stream containing Spectrum
//! data records.
class CEMSSpectrumBinStrm : public CEMSBinMsgBody
{
	public:
		CEMSSpectrumBinStrm();

		CEMSSpectrumBinStrm( const CEMSSpectrumBinStrm& spectrumStrm );

		virtual ~CEMSSpectrumBinStrm();

		virtual EMSVARIANTRECORD* ReadNext();

		virtual void WriteRecord( const EMSVARIANTRECORD& record );

		EMSVARIANTRECORD2* ReadNext2();

		void WriteRecord2( const EMSVARIANTRECORD2& record );
	
};

#endif // __SPECTRUM_BIN_STRM_H__