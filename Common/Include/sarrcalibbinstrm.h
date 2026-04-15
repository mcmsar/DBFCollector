//! @file sarrcalibBinStrm.h
//! Header file for the CEMSSarrCalibBinStrm declaration.

#ifndef __SARRCALIB_BIN_STRM_H__
#define __SARRCALIB_BIN_STRM_H__

//! @class CEMSSarrCalibBinStrm
//! Class used for reading and writing a binary stream containing SARR calib
//! data records.
class CEMSSarrCalibBinStrm : public CEMSBinMsgBody
{
	public:
		CEMSSarrCalibBinStrm();

		CEMSSarrCalibBinStrm( const CEMSSarrCalibBinStrm& sarrcalibStrm );

		virtual ~CEMSSarrCalibBinStrm();

		virtual EMSVARIANTRECORD* ReadNext();

		virtual void WriteRecord( const EMSVARIANTRECORD& record );

		EMSVARIANTRECORD2* ReadNext2();

		void WriteRecord2( const EMSVARIANTRECORD2& record );
	
};

#endif // __SARRCALIB_BIN_STRM_H__