#ifndef __BCNMSGDECODEBASE_H
#define __BCNMSGDECODEBASE_H

#include <assert.h>
#include "CBcnMsgDecodeBase.h"

interface IEMSBeaconDecoder;

class CBcnMsgDecode : public CBcnMsgDecodeBase
{
public:
	CBcnMsgDecode();
	CBcnMsgDecode( const CBcnMsgDecode& x ) { assert( false ); } // Copy constructor not supported
	~CBcnMsgDecode();

private:

	virtual void _DecodeLocation( CBeaconMessage& cbcnmsg );
	
	bool _InitWebServiceConnection();

	IEMSBeaconDecoder*		m_pDecoderWS;
};

#endif
