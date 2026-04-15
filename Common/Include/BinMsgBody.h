//! @file BinMsgBody.h
//! Header file for the CEMSBinMsgBody class declaration.

#ifndef __BIN_MSG_BODY_H__
#define __BIN_MSG_BODY_H__

interface IEMSSeqStream;

//! @class CEMSBinMsgBody
//! Base class that provides a common interface to the body/data portion of a binary
//! message file.
class CEMSBinMsgBody : public CApiObjBase, public IEMSMsgBody3
{
	public:
		CEMSBinMsgBody();
		CEMSBinMsgBody( const CEMSBinMsgBody& binMsgBody );
		virtual ~CEMSBinMsgBody();

		//! @fn void SetStream( IEMSSeqStream* pStrm )
		//! Set a pointer to an open stream.
		void SetStream( IEMSSeqStream* pStrm );

		// Read method for 3rd generation version of EMSVARIANTRECORD.
		virtual EMSVARIANTRECORD3* ReadNext3();

		// Write method for 3rd generation version of EMSVARIANTRECORD.
		virtual void WriteRecord3( const EMSVARIANTRECORD3& record );
	protected:
		IEMSSeqStream* m_pStrm;
};

#endif // __BIN_MSG_BODY_H__