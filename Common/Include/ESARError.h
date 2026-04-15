//---------------------------------------------------------------------------
#ifndef ESARErrorH
#define ESARErrorH
//---------------------------------------------------------------------------
#include <vcl.h>

class _export ESARError
{
public:
    AnsiString      Message;

    ESARError( void );
    ESARError( const AnsiString Msg );
};

class _export ESARIBError : public ESARError
{
private:
    AnsiString      SQLMessage;
public:
    ESARIBError( const AnsiString Msg );
    ESARIBError( int *APIError );

    int             SQLCode;
};

class _export ESARConfigError : public ESARError
{
public:
    ESARConfigError( const AnsiString Msg );
};

class _export ESARTaskError : public ESARError
{
public:
    ESARTaskError( const AnsiString Msg );
};

#endif
