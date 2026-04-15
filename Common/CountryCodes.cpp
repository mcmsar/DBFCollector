//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>
#pragma hdrstop

#include "CountryCodes.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

bool TranslateCountryCode( int CCNum, TCountryCdData *cc,
                           AnsiString& CCShort, AnsiString& CCLong )
{
    if( cc )
    {
        for( int i = 0; cc[i].CCNum != 999; i++ )
        {
            if( cc[i].CCNum == CCNum )
            {
                CCShort = cc[i].CCText;
                CCLong = cc[i].CCFullText;
                return true;
            }
        }
    }

    CCShort = IntToStr(CCNum);
    CCLong  = "UNKNOWN";
    return false;
}

