#include "assert.h"
#include "emserror.h"
#include "CriticalSection.h"
#include "convutility.h"

#include "EMSBeacon.h"

#define INITGUID			
#include <initguid.h>
#include "bdwsclientclsid.h"
#include "BeaconDecoder.h"

CBeaconMsg::CBeaconMsg()
{
	
}

CBeaconMsg::CBeaconMsg( const CBeaconMsgBase &x ) 
: CBeaconMsgBase(x)
{
	
}

CBeaconMsg::CBeaconMsg( const CBeaconMsg &x ) 
: CBeaconMsgBase(x)
{
	
}

// The following constructor is deprecated and will be removed in a future software release.
// Instead use CBeaconMsg() followed by a call to Set( Msg[] ...)
CBeaconMsg::CBeaconMsg(	const BYTE Msg[],
			ULONG ulSrcOffset,                      // bit to start copying from Msg
			ULONG ulDestOffset,                     // bit to start copying Msg into
			ULONG ulNumBits )						// # bits
: CBeaconMsgBase( Msg, ulSrcOffset, ulDestOffset, ulNumBits )
{
	
}
// end deprecated

CBeaconMsg::CBeaconMsg( const CBeaconID2 &rBeaconID ) 
: CBeaconMsgBase( rBeaconID )
{
	
}

CBeaconMsg::~CBeaconMsg()
{
	
}

CBeaconID2 
CBeaconMsg::getBeaconID(  )
{
	EMS_RESULT	hr = EMS_OK;
	bool		bHaveValue = false;
	CBeaconID2	oReturnBeaconID;

	if ( !bHaveValue )
	{
		// Defer to the the base class implementation
		oReturnBeaconID = CBeaconMsgBase::getBeaconID();
	}

	return oReturnBeaconID;
}


CBeaconMsg & CBeaconMsg::operator = ( const CBeaconMsg &rBeaconMsg )
{
    if( this != &rBeaconMsg )
    {
		CBeaconMsgBase::operator=(rBeaconMsg);
	}
	return *this;
}
