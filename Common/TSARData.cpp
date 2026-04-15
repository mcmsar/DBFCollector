//---------------------------------------------------------------------------
#include <vcl.h>
#include <alloc.h>
#pragma hdrstop

#include "TSARData.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)

TSARData::TSARData( void )
{
    // Initialize InterBase API components
    pFields = NULL;
    pIndices = NULL;
}
//---------------------------------------------------------------------------
void TSARData::SetIndices( TIndexDefs *pNewIndices )
{
    // This function should be overridden by the child class, if necessary
}
//---------------------------------------------------------------------------
void TSARData::DefineField( AnsiString Name, TFieldType Type )
{
    DefineField( Name, Type, 0 );
}
//---------------------------------------------------------------------------
void TSARData::DefineField( AnsiString Name, TFieldType Type, int Size )
{
    TFieldDef *pField = pFields->AddFieldDef();

    pField->Name = Name;
    pField->DataType = Type;
    if( Size != 0 ) pField->Size = Size;
}
//---------------------------------------------------------------------------
void TSARData::DefineIndex( AnsiString IndexName, AnsiString Columns )
{
    TIndexDef *pIndex = pIndices->AddIndexDef();

    pIndex->Name = IndexName;
    pIndex->Fields = Columns;
    pIndex->Options.Clear();
}
//---------------------------------------------------------------------------
void TSARData::DefineDescIndex( AnsiString IndexName, AnsiString Columns )
{
    TIndexDef *pIndex = pIndices->AddIndexDef();

    pIndex->Name = IndexName;
    pIndex->Fields = Columns;
    pIndex->Options = TIndexOptions() << ixDescending;
}
//---------------------------------------------------------------------------
void TSARData::GetArray( void *Buffer, const AnsiString FieldName,
                         const int Size, TFields *pIn )
{
    AnsiString TempString;

    TempString.SetLength( Size );
    if ( !pIn->FieldByName( FieldName )->IsNull )
    {
        TempString = pIn->FieldByName( FieldName )->Value;
        memcpy( Buffer, TempString.data(), Size );
    }
    else
    {
        memset( Buffer, 0, Size );
    }
}
//---------------------------------------------------------------------------
void TSARData::PutArray( const void *Buffer, const AnsiString FieldName,
                         const int Size, TFields *pOut )
{
    char *TempPtr;
    AnsiString TempString;

    TempPtr = (char*)Buffer;
    TempString.SetLength( Size );
    for( int i = 0; i < Size; i++ )
        TempString[i+1] = TempPtr[i];
    pOut->FieldByName( FieldName )->Value = TempString;
}
//---------------------------------------------------------------------------


TSARData::~TSARData()
{
    //delete SpanKey;
    //delete pFields;
    //delete pIndices;
}

