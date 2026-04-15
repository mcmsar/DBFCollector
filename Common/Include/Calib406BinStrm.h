//! @file Calib406BinStrm.h
//! Header file for the CEMSCalib046BinStrm declaration.

#ifndef __CALIB406_BIN_STRM_H__
#define __CALIB406_BIN_STRM_H__

//! @class CEMSCalib046BinStrm
//! Class used for reading and writing a binary stream containing calibrated 406
//! data records.
class CEMSCalib406BinStrm : public CEMSBinMsgBody
{
	public:
		CEMSCalib406BinStrm();

		CEMSCalib406BinStrm( const CEMSCalib406BinStrm& calib406Strm );

		virtual ~CEMSCalib406BinStrm();

		virtual EMSVARIANTRECORD* ReadNext();

		virtual void WriteRecord( const EMSVARIANTRECORD& record );

		EMSVARIANTRECORD2* ReadNext2();

		void WriteRecord2( const EMSVARIANTRECORD2& record );
	
};

#endif // __LOC_BIN_STRM_H__