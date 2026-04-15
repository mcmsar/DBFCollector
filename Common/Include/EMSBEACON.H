#ifndef EMSBEACONMSG_H
#define EMSBEACONMSG_H

#include "EMSBeaconBase.h"

// The following class supports encrypted beacons
class CBeaconMsg : public CBeaconMsgBase
{
public:
    CBeaconMsg();
    CBeaconMsg( const CBeaconMsg &x );
    CBeaconMsg( const CBeaconMsgBase &x );
    CBeaconMsg( const CBeaconID2 &rBeaconID );

	// The following constructor is deprecated and will be removed in a future software release.
	// Instead use CBeaconMsg() followed by a call to Set( Msg[] ...)
    CBeaconMsg( const BYTE Msg[],
                ULONG ulSrcOffset = 0,                      // bit to start copying from Msg
                ULONG ulDestOffset = 0,                     // bit to start copying Msg into
                ULONG ulLength = EMSBeaconDefs::LENGTH_BIT_BEACONMSG );

    virtual ~CBeaconMsg();

	virtual CBeaconID2		getBeaconID();

	// assignment operators
	CBeaconMsg &operator= ( const CBeaconMsg &rBeaconMsg );

private:
};

#endif
