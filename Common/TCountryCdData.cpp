//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "..\Database\TCountryCdData.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

TCountryCdData::TCountryCdData( void )
{
    // Set database information
    DatabaseCode = "Config";
    TableName = "CountryCodes";
    SpanKey = NULL;
}

void TCountryCdData::SetFields( TFieldDefs *pNewFields )
{
    pFields = pNewFields;
    DefineField( "CCNum", ftWord );
    DefineField( "CCText", ftString, 3 );
    DefineField( "CCFullText", ftString, 10 );
}

void TCountryCdData::SetIndices( TIndexDefs *pNewIndices )
{
    pIndices = pNewIndices;
    DefineIndex( "CCNumA", "CCNum");
    DefineDescIndex( "CCNumD", "CCNum" );
}

void TCountryCdData::operator <<( TFields *pIn )
{
    TField *Field;

    Field = pIn->FieldByName( "CCNum" );
    CCNum = Field->IsNull ? 0 : Field->Value;
    Field = pIn->FieldByName( "CCText" );
    CCText = Field->IsNull ? (AnsiString)"" : (AnsiString)Field->Value;
    Field = pIn->FieldByName( "CCFullText" );
    CCFullText = Field->IsNull ? (AnsiString)"" : (AnsiString)Field->Value;
}

void TCountryCdData::operator >>( TFields *pOut )
{
    pOut->FieldByName( "CCNum" )->Value = CCNum;
    pOut->FieldByName( "CCText" )->Value = CCText;
    pOut->FieldByName( "CCFullText" )->Value = CCFullText;
}

