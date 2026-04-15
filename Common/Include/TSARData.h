//---------------------------------------------------------------------------
#ifndef TSARDataH
#define TSARDataH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <db.hpp>
#include "TSARTime.h"

// SAR Data Object Base Class
class _export TSARData
{
public:
    TSARData( void );

    AnsiString      DatabaseCode, TableName;
    TSARTime        *SpanKey;

    virtual void    SetFields( TFieldDefs *pNewFields ) = 0;
    virtual void    SetIndices( TIndexDefs *pNewIndices );
    virtual void    operator <<( TFields *pIn ) = 0;
    virtual void    operator >>( TFields *pOut ) = 0;
        virtual ~TSARData();

protected:
    // Interbase API
    TFieldDefs  *pFields;
    TIndexDefs  *pIndices;

    // Child object definition routines
    void        DefineField( AnsiString Name, TFieldType Type );
    void        DefineField( AnsiString Name, TFieldType Type, int Size );
    void        DefineIndex( AnsiString IndexName, AnsiString Columns );
    void        DefineDescIndex( AnsiString IndexName, AnsiString Columns );

    // Array input and output routines (use with Blob fields)
    void        GetArray( void *Buffer, const AnsiString FieldName,
                          const int Size, TFields *pIn );
    void        PutArray( const void *Buffer, const AnsiString FieldName,
                          const int Size, TFields *pOut );
};

#endif
