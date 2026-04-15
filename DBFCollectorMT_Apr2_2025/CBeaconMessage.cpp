
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

//---------------------------------------------------------------------------
#include <math.h>
#include <stdio.h>


#include "CBeaconMessage.h"
#include "CBeaconID.h"
#include "HexUtilis.h"

//---------------------------------------------------------------------------
CBeaconMessage::CBeaconMessage( void )
{
    int ByteIdx;

    ByteIdx = 0;
    while( ByteIdx < sizeof(Message) )
        Message[ByteIdx++] = 0;
}

CBeaconMessage::CBeaconMessage( const char* cMessage, int iSize )
{
	if( iSize == 36 )
	{
		HexRead( (char*)cMessage, Message, 36);
	}
	else if( iSize == 18 )
	{
		memcpy( Message, cMessage, iSize );
	}
	else
	{
		memset( Message, 0, sizeof(Message) );
	}
}

CBeaconMessage::CBeaconMessage( const BYTE* cMessage )
{
	memcpy( Message, cMessage, 18 );
}

bool CBeaconMessage::Bit( const int Pos )
{
    int     ByteIdx, BitIdx;

    ByteIdx = 0;
    BitIdx = Pos;

    while( BitIdx > 8 )
    {
        BitIdx -= 8;
        ByteIdx++;
    }
    BitIdx = 8 - BitIdx;

    return (Message[ByteIdx] >> BitIdx) & 1;
}

int CBeaconMessage::Bits( const int Start, const int End )
{
    int     Value = 0;

    for( int i = Start; i <= End; i++ )
    {
        Value <<= 1;
        if( Bit( i ) )
        {
            Value++;
        }
    }

    return Value;
}

int CBeaconMessage::NibbleAlignedBits( const int Start, const int End )
{
    int shift = 4 - ((End - Start + 1) % 4);
    if (shift == 4) shift = 0;
    return Bits(Start, End) << shift;
}

//AnsiString CBeaconMsg::MBaudot( const int Start, const int End, const int CharSize )
char* CBeaconMessage::MBaudot( const int Start, const int End, const int CharSize )
{
    const char  MBaudotChar[] =
        "?5?9??????4?80??3????6?/-2??71???T?O HNM?LRGIPCVEZDBSYFXAWJ?UQK?";
    int         Pos = Start;
//    AnsiString  Buffer = "";
//    AnsiString  TestChar;
	static char  Buffer[128] = "";
    char  TestChar[128];


    if( CharSize == 5 )
    {
        // Decode the specified bits assuming a shortened Baudot Code
        // ( 5 bits only with the sixth bit assumed and set to 1 )
        while( Pos <= End )
        {
//            TestChar = MBaudotChar[Bits( Pos, Pos + 4 )+ 0x20];
			strcpy( TestChar, &MBaudotChar[Bits( Pos, Pos + 4 )+ 0x20] );
   
            if( End-Pos < CharSize && TestChar == "?") // Test last character size
//                Buffer += " ";
                strcat( Buffer, " " );
   
            else
//                Buffer += TestChar;
			    strcat( Buffer, TestChar );
            Pos += 5;
        }
    }
    else
    {
        // Decode the specified bits assuming a 6 bit Baudot Code
        while( Pos <= End )
        {
//            TestChar = MBaudotChar[Bits( Pos, Pos + 5 )];
			strcpy( TestChar, &MBaudotChar[Bits( Pos, Pos + 5 )] );

            if( End-Pos < CharSize && TestChar == "?")  // Test last character size
//                Buffer += " ";
			    strcat( Buffer, " " );
            else
//                Buffer += TestChar;
			    strcat( Buffer, TestChar );
            Pos += 6;
        }
    }

	return Buffer;
}

//CBeaconID CBeaconMsg::BeaconID( void )
__int64 CBeaconMessage::BeaconID( void )
{
    CBeaconID   Hex15;

    *(Hex15.High()) = Bits( 26, 53 );
    *(Hex15.Low()) = Bits( 54, 85 );

    return Hex15.i64;
}

void CBeaconMessage::Fill( float *f144 )
{
    float *ptr = f144;

    for( int i = 0; i < 18; i++ )
    {
        Message[i] = 0;
        for( int j = 0; j < 8; j++ )
        {
            Message[i] <<= 1;
            if( *ptr > 0 )
            {
                Message[i]++;
            }
            ptr++;
        }
    }
}

//AnsiString CBeaconMsg::Hex30( void )
char* CBeaconMessage::Hex30( void )
{
    return HexString( &Message[3], 30 );
}

//AnsiString CBeaconMsg::Hex36( void )
char* CBeaconMessage::Hex36( void )
{
    return HexString( Message, 36 );
}

void 
CBeaconMessage::GetHexString( char* hexMsg )
{
	if( hexMsg )
	{
		unsigned char   *ptr;
		char            TmpStr[4];

		ptr = (unsigned char *)Message;

		for( int i = 0; i < 36; i += 2 )
		{
			sprintf ( TmpStr, "%02x", *(ptr++) );
			strcat ( hexMsg, TmpStr );
		}
	}
}


CBeaconMessage CBeaconMessage::PDF1( void )
{
    CBeaconMessage PDF1Mask;

    HexRead( "000000FFFFFFFFFFFFFFF800000000000000", PDF1Mask.Message, 36);
    return *this & PDF1Mask;
}


CBeaconMessage CBeaconMessage::PDF2( void )
{
    CBeaconMessage PDF2Mask;

    HexRead( "000000000000000000000000007FFFFFF000", PDF2Mask.Message, 36);
    return *this & PDF2Mask;
}

void CBeaconMessage::ZeroFillExtended( void )
{
    CBeaconMessage ZeroFillMask;

    HexRead( "FFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000", ZeroFillMask.Message, 36);
    *this &= ZeroFillMask;
}

void CBeaconMessage::OneFillExtended( void )
{
    CBeaconMessage OneFillMask;

    HexRead( "0000000000000000000000000000FFFFFFFF", OneFillMask.Message, 36);
    *this |= OneFillMask;
}

void 
CBeaconMessage::GetBcnMessage( BYTE* cMsg )
{
	if( cMsg )
	{
		memcpy( cMsg, Message, sizeof(Message) );
	}
}

bool
CBeaconMessage::IsEmptyBcnMessage()
{
	const unsigned char   caZeroMessage[18] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	return ( 0 == memcmp( Message, caZeroMessage, sizeof(caZeroMessage) ) );
}

CBeaconMessage& CBeaconMessage::operator&=( const CBeaconMessage& Msg )
{
    *this = *this & Msg;
    return *this;
}

CBeaconMessage CBeaconMessage::operator&( const CBeaconMessage& Msg )
{
    CBeaconMessage Temp;

    for ( int i = 0; i < 18; i++ )
    {
        Temp.Message[i] = Message[i] & Msg.Message[i];
    }

    return Temp;
}

CBeaconMessage& CBeaconMessage::operator|=( const CBeaconMessage& Msg )
{
    *this = *this | Msg;
    return *this;
}

CBeaconMessage CBeaconMessage::operator|( const CBeaconMessage& Msg )
{
    CBeaconMessage Temp;

    for ( int i = 0; i < 18; i++ )
    {
        Temp.Message[i] = Message[i] | Msg.Message[i];
    }

    return Temp;
}

bool CBeaconMessage::operator==( const CBeaconMessage& Msg )
{
    for ( int i = 0; i < 18; i++ )
    {
        if ( Message[i] != Msg.Message[i] ) return false;
    }

    return true;
}

std::string 
CBeaconMessage::ConvertToHexString( __int64 i64Value )
{
	std::string szRet;

	char szValue[ 34 ];
	memset( szValue, 0, 34*sizeof(char) );

	_ui64toa( i64Value, szValue, 16 );

	for( int i = 0; i < 34; i++ )
	{
		szValue[i] = toupper( szValue[i] );
		if( szValue[i] ==  ' ' )
		{
			szValue[i] = '0';
		}
	}

	szRet = szValue;

	return szRet;
}


INT64 
CBeaconMessage::getBCH1( INT64 i64BeaconID, bool Flag )
{

	UINT64 BCHcode = 0;
	BYTE   msg[82];
	BYTE   pg[22] = {1,0,0,1,1,0,1,1,0,1,1,0,0,1,1,1,1,0,0,0,1,1};
	BYTE   code[22];


	// Reverse the bits in the beacon ID
	memset(&msg[0], 0, sizeof(BYTE)*82);
	memset(&code[0], 0, sizeof(BYTE)*22);

	if (Flag) msg[0] = 1;
	for( int i = 1; i < 61; i++ )
	{
		if ( get_bit( i64BeaconID, 60 - i ) )
		{
			msg[i] = 1;
		}
	}

	memcpy(&code[0], &msg[0], sizeof(BYTE)*22);

	for( int i = 0; i < 61; i++ )
	{
		
		if ( code[0] == 1 )
		{
			for( int j = 0; j < 22; j++ )
			{
				if ( code[j]== pg[j] )
					code[j] = 0;
				else
					code[j] = 1;
			}
		}
		for( int j = 0; j < 21; j++ )
		{
			code[j] = code[j+1];
		}
		code[21] = msg[i+22];
	}

	memcpy( &msg[61],&code[0], sizeof(BYTE)*21 );

	BCHcode = 0;

	for ( int j = 0; j < 21; j++ )
	{
		BCHcode += code[j];
		BCHcode *= 2;
	
	}

	memset( &Message[3], 0, sizeof(BYTE)*10 );
	for ( int j = 0; j < 80; j++ )
	{
		int indx = j/8 + 3;
		Message[indx] += msg[j];

		if ( j%8 < 7 ) Message[indx] *= 2;
	}
	Message[13] &= 0x3F;
	Message[13] += (msg[80]<<7) + (msg[81]<<6);
	
	return BCHcode;
}

bool 
CBeaconMessage::get_bit(INT64 val, int position)
{
    UINT64 k = pow(2.0,position);
	UINT64 j = val & k;
	return ( j > 0 ); 
}



