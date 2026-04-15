//---------------------------------------------------------------------------
#ifndef TBeaconIDH
#define TBeaconIDH
//---------------------------------------------------------------------------

class CBeaconID
{
public:
    __int64     i64;

                CBeaconID( void );
    long        *High( void );
    long        *Low( void );
//    AnsiString  Hex( void );
//    AnsiString  Match( void );
//    void        operator = (AnsiString HexID);
    char*       Hex( void );
    char*       Match( void );
    void        operator = (char *HexID);

};

#endif