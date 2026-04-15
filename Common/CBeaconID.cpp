//---------------------------------------------------------------------------
#include <stdio.h> // req'd for debug only
#include <string.h>
#include "HexUtilis.h"
#include "CBeaconID.h"


//---------------------------------------------------------------------------
CBeaconID::CBeaconID( void )
{
    i64 = 0;
}

long *CBeaconID::High( void )
{
    return ((long *)&i64) + 1;
}

long *CBeaconID::Low( void )
{
    return (long *)&i64;
}

//AnsiString TBeaconID::Hex( void )
char* CBeaconID::Hex( void )
{
//    return IntToHex( (int)(0x0FFFFFFF & (long)(i64>>32)), 7 ) +
//           IntToHex( (int)(0xFFFFFFFF & (long) i64     ), 8 );
	int intTmp = (int)(0x0FFFFFFF & (long)(i64>>32)) +
		         (int)(0xFFFFFFFF & (long) i64     );
	static char charTmp[18];

	sprintf ( charTmp, "%x", intTmp );

    return charTmp;
}

//AnsiString TBeaconID::Match( void )
char* CBeaconID::Match( void )
{
//    return "(BeaconID1 = " + IntToStr( (int)(0x0FFFFFFF & (long)(i64>>32)) ) +
//           " AND " +
//           "BeaconID2 = " + IntToStr( (int)0xFFFFFFFF & (long)i64 ) + ")";
	int intTmp1, intTmp2;
	static char charTmp[25];

	intTmp1 = (int)(0x0FFFFFFF & (long)(i64>>32));
	intTmp2 = (int) 0xFFFFFFFF & (long)i64;

	sprintf ( charTmp, "%s%s%s%s%s", "(BeaconID1 = ", intTmp1, " AND ", 
		"BeaconID2 = ", intTmp2 );

    return charTmp;

}

//void TBeaconID::operator = (AnsiString HexID)
void CBeaconID::operator = (char* HexID)
{
//    if( HexID.Length() != 15 )
	if( strlen (HexID) != 15 )
    {
//        throw EConvertError( "Beacon ID must be 15 characters." );
		//???????????? EMS_RESULT hr = ?
    }

    i64 = 0;
    for( int i = 1; i < 16; i++ )
    {
        i64 <<= 4;
        i64 += HexChar( HexID[i] );
    }
}


