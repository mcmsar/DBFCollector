#ifndef EMSBCH_H
#define EMSBCH_H

#include "EMSTYPES.h"
#include "EMSBEACONDFNS.h"

class CBCHCoder
{
public:
    static ULONG CheckPDF1( BYTE abyBcnMsg[EMSBeaconDefs::LENGTH_BYTE_BEACONMSG] );
    static ULONG CorrectPDF1( BYTE abyBcnMsg[EMSBeaconDefs::LENGTH_BYTE_BEACONMSG] );

    static ULONG CheckPDF2( BYTE abyBcnMsg[EMSBeaconDefs::LENGTH_BYTE_BEACONMSG] );
    static ULONG CorrectPDF2( BYTE abyBcnMsg[EMSBeaconDefs::LENGTH_BYTE_BEACONMSG] );
};

#endif