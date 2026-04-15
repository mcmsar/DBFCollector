//---------------------------------------------------------------------------
#ifndef TCountryCdDataH
#define TCountryCdDataH
//---------------------------------------------------------------------------
#include "TSARData.h"

class __export TCountryCdData : public TSARData
{
public:
    TCountryCdData( void );

    void            SetFields( TFieldDefs *pNewFields );
    void            SetIndices( TIndexDefs *pNewIndices );
    void            operator <<( TFields *pIn );
    void            operator >>( TFields *pOut );

    unsigned short  CCNum;           // Country Code Number
    AnsiString      CCText;          // Country Name
    AnsiString      CCFullText;      // Country Description
};

#endif
