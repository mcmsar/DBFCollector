//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>
#pragma hdrstop

#include "HexUtils.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

int HexChar( char Value )
{
    switch( Value )
    {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return Value - '0';
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
            return Value - 'A' + 10;
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
            return Value - 'a' + 10;
        default:
            throw EConvertError( "Invalid character in hexadecimal string." );
    }
}

void HexRead( AnsiString Hex, void *Buffer, int Length )
{
    unsigned char   *ptr;

    ptr = (unsigned char *)Buffer;
    for( int i = 1; i < Length; i += 2 )
    {
        *ptr = (unsigned char)((HexChar( Hex[i] ) << 4) + HexChar( Hex[i+1] ));
        ptr++;
    }
}

int HexReadInt( AnsiString Hex )
{
    int             ReturnValue;
    unsigned char   *ptr;

    ptr = ((unsigned char *)&ReturnValue) + 3;
    for( int i = 1; i < 8; i += 2 )
    {
        *ptr = (unsigned char)((HexChar( Hex[i] ) << 4) + HexChar( Hex[i+1] ));
        ptr--;
    }

    return ReturnValue;
}

AnsiString HexString( void *Buffer, int Length )
{
    unsigned char   *ptr;
    AnsiString      TempString;

    ptr = (unsigned char *)Buffer;
    TempString = "";

    for( int i = 0; i < Length; i += 2 )
    {
        TempString += IntToHex( *(ptr++), 2 );
    }

    return TempString;
}

