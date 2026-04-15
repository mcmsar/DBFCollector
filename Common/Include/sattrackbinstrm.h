//! @file sattrackBinStrm.h
//! Header file for the CEMSSatTrackBinStrm declaration.

#ifndef __SAT_TRACK_BIN_STRM_H__
#define __SAT_TRACK_BIN_STRM_H__

//! @class CEMSSatTrackBinStrm
//! Class used for reading and writing a binary stream containing Satellite track
//! data records.
class CEMSSatTrackBinStrm : public CEMSBinMsgBody
{
	public:
		CEMSSatTrackBinStrm();

		CEMSSatTrackBinStrm( const CEMSSatTrackBinStrm& sattrackStrm );

		virtual ~CEMSSatTrackBinStrm();

		virtual EMSVARIANTRECORD* ReadNext();

		virtual void WriteRecord( const EMSVARIANTRECORD& record );

		EMSVARIANTRECORD2* ReadNext2();

		void WriteRecord2( const EMSVARIANTRECORD2& record );
	
};

#endif // __SAT_TRACK_BIN_STRM_H__