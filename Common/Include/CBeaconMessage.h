/*********************************************************************
*	              Copyright (c) 2005 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:
	$
********************************************************************/


#ifndef INC_CBEACONMESSAGE
#define INC_CBEACONMESSAGE

#include "emstypes.h"
#include <string>

//! @class CBeaconMessage
//! This class deals with beacons messages.
class CBeaconMessage
{
public:
	CBeaconMessage( void );
	CBeaconMessage( const char* cMessage, int iSize = 18 );
	CBeaconMessage( const BYTE* cMessage );
	
	unsigned char   Message[18];


	//! @fn bool Bit( const int Pos )
	//! Gets the bit at certain position.
	//! @param const int Pos
	//! specifies the position of queried bit.
	bool            Bit( const int Pos );
    int             Bits( const int Start, const int End );
    int             NibbleAlignedBits( const int Start, const int End );
//    AnsiString      MBaudot( const int Start, const int End, const int CharSize = 6 );
	char*           MBaudot( const int Start, const int End, const int CharSize = 6 );
//    TBaconID        BeaconID( void );
	__int64         BeaconID( void );
    void            Fill( float *f144 );

//    AnsiString      Hex30( void );
//    AnsiString      Hex36( void );
	char*           Hex30( void );
    char*           Hex36( void );

	//! @fn void GetHexString( char* hexMsg )
	//! This function converts the beacon message of this object to HexString 
	//! @param char* hexMsg
	//! A pointer to an allocated string.
	void  GetHexString( char* hexMsg );

    CBeaconMessage      PDF1( void );
    CBeaconMessage      PDF2( void );
    void            ZeroFillExtended( void );
    void            OneFillExtended( void );
    
	//! @fn void GetBcnMessage( BYTE* cMsg )
	//! This function returns the beacon message of this object.
	//! @param BYTE* cMsg
	//! A pointer to an allocated byte array.
	void  GetBcnMessage( BYTE* cMsg );

	bool  IsEmptyBcnMessage();

	CBeaconMessage&     operator&=( const CBeaconMessage& Msg );
    CBeaconMessage      operator&( const CBeaconMessage& Msg );
    CBeaconMessage&     operator|=( const CBeaconMessage& Msg );
    CBeaconMessage      operator|( const CBeaconMessage& Msg );
    bool            operator==( const CBeaconMessage& Msg );

	static std::string ConvertToHexString( __int64 i64Value );

	INT64 getBCH1( INT64 i64BeaconID, bool Flag );
	bool get_bit(INT64 val, int position);
};

#endif // INC_CBEACONMESSAGE