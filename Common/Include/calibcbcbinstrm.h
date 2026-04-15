//! @file calibCBCBinStrm.h
//! Header file for the CEMSCalibCBCBinStrm declaration.

#ifndef __CALIB_CBC_BIN_STRM_H__
#define __CALIB_CBC_BIN_STRM_H__

//! @class CEMSCalibCBCBinStrm
//! Class used for reading and writing a binary stream containing Calib CBC
//! data records.
class CEMSCalibCBCBinStrm : public CEMSBinMsgBody
{
	public:
		CEMSCalibCBCBinStrm();

		CEMSCalibCBCBinStrm( const CEMSCalibCBCBinStrm& calibcbcStrm );

		virtual ~CEMSCalibCBCBinStrm();

		virtual EMSVARIANTRECORD* ReadNext();

		virtual void WriteRecord( const EMSVARIANTRECORD& record );

		EMSVARIANTRECORD2* ReadNext2();

		void WriteRecord2( const EMSVARIANTRECORD2& record );
	
};

#endif // __CALIB_CBC_BIN_STRM_H__