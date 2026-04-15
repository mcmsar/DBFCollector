//! @file sarpcalibBinStrm.h
//! Header file for the CEMSSarpCalibBinStrm declaration.

#ifndef __SARPCALIB_BIN_STRM_H__
#define __SARPCALIB_BIN_STRM_H__

//! @class CEMSSarpCalibBinStrm
//! Class used for reading and writing a binary stream containing SARP calib
//! data records.
class CEMSSarpCalibBinStrm : public CEMSBinMsgBody
{
	public:
		CEMSSarpCalibBinStrm();

		CEMSSarpCalibBinStrm( const CEMSSarpCalibBinStrm& sarpcalibStrm );

		virtual ~CEMSSarpCalibBinStrm();

		virtual EMSVARIANTRECORD* ReadNext();

		virtual void WriteRecord( const EMSVARIANTRECORD& record );

		EMSVARIANTRECORD2* ReadNext2();

		void WriteRecord2( const EMSVARIANTRECORD2& record );
	
};

#endif // __SARPCALIB_BIN_STRM_H__