//---------------------------------------------------------------------------
#ifndef CountryCodesH
#define CountryCodesH
//---------------------------------------------------------------------------
#include <vcl.h>

#include "TCountryCdData.h"

bool __export TranslateCountryCode( int CCNum, TCountryCdData *cc,
                                    AnsiString& CCShort, AnsiString& CCLong );
#endif
