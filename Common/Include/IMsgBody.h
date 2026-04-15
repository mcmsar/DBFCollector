//! @file IMsgBody.h
//! Header file for the IEMSMsgBody interface/abstract class declaration.

#ifndef __IMSG_BODY_H__
#define __IMSG_BODY_H__

//! @class IEMSMsgBody
//! Interface declaration for classes that read binary message/data files.
class IEMSMsgBody
{
	public:
		IEMSMsgBody() {}
		IEMSMsgBody( const IEMSMsgBody& msgBody ) {}
		~IEMSMsgBody() {}

		//! @fn virtual EMSVARIANTRECORD* ReadNext()
		//! Reads the next record in the stream.  The caller must delete the returned pointer.
		virtual EMSVARIANTRECORD* ReadNext() = 0;

		//! @fn virtual void WriteRecord( EMSVARIANTRECORD& record )
		//! Writes a record to the end of the currently open stream.
		virtual void WriteRecord( const EMSVARIANTRECORD& record ) = 0;
};

//! Second generation IEMSMsgBody interface.
class IEMSMsgBody2 : public IEMSMsgBody
{
	public:
		IEMSMsgBody2() {}
		IEMSMsgBody2( const IEMSMsgBody2& msgBody ) {}
		~IEMSMsgBody2() {}

		// Read method for second generation version of EMSVARIANTRECORD.
		virtual EMSVARIANTRECORD2* ReadNext2() = 0;

		// Write method for second generation version of EMSVARIANTRECORD.
		virtual void WriteRecord2( const EMSVARIANTRECORD2& record ) = 0;
};

//! 3rd generation IEMSMsgBody interface.
class IEMSMsgBody3 : public IEMSMsgBody2
{
	public:
		IEMSMsgBody3() {}
		IEMSMsgBody3( const IEMSMsgBody3& msgBody ) {}
		~IEMSMsgBody3() {}

		// Read method for 3rd generation version of EMSVARIANTRECORD.
		virtual EMSVARIANTRECORD3* ReadNext3() = 0;

		// Write method for 3rd generation version of EMSVARIANTRECORD.
		virtual void WriteRecord3( const EMSVARIANTRECORD3& record ) = 0;
};

#endif // __IMSG_BODY_H__