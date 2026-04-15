//! @file tleBinStrm.h
//! Header file for the CEMSTLEBinStrm declaration.

#ifndef __TLE_BIN_STRM_H__
#define __TLE_BIN_STRM_H__

//! @class CEMSTLEBinStrm
//! Class used for reading and writing a binary stream containing TLE
//! data records.
class CEMSTLEBinStrm : public CEMSBinMsgBody
{
	public:
		CEMSTLEBinStrm();

		CEMSTLEBinStrm( const CEMSTLEBinStrm& tleStrm );

		virtual ~CEMSTLEBinStrm();

		virtual EMSVARIANTRECORD* ReadNext();

		virtual void WriteRecord( const EMSVARIANTRECORD& record );

		EMSVARIANTRECORD2* ReadNext2();

		void WriteRecord2( const EMSVARIANTRECORD2& record );
};

#endif // __TLE_BIN_STRM_H__