//! @file residual406BinStrm.h
//! Header file for the CEMSResidualBinStrm declaration.

#ifndef __RESIDUAL_BIN_STRM_H__
#define __RESIDUAL_BIN_STRM_H__

//! @class CEMSResidualBinStrm
//! Class used for reading and writing a binary stream containing Residual
//! data records.
class CEMSResidualBinStrm : public CEMSBinMsgBody
{
	public:
		CEMSResidualBinStrm();

		CEMSResidualBinStrm( const CEMSResidualBinStrm& residualStrm );

		virtual ~CEMSResidualBinStrm();

		virtual EMSVARIANTRECORD* ReadNext();

		virtual void WriteRecord( const EMSVARIANTRECORD& record );

		EMSVARIANTRECORD2* ReadNext2();

		void WriteRecord2( const EMSVARIANTRECORD2& record );
	
};

#endif // __RESIDUAL_BIN_STRM_H__