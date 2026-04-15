//---------------------------------------------------------------------------
#ifndef TBeaconIDH
#define TBeaconIDH
//---------------------------------------------------------------------------
#include <vcl.h>

class _export TBeaconID
{
public:
    __int64     i64;

                TBeaconID( void );
    long        *High( void );
    long        *Low( void );
    AnsiString  Hex( void );
    AnsiString  Match( void );
    void        operator = (AnsiString HexID);
};

#endif
