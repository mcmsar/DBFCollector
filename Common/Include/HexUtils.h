//---------------------------------------------------------------------------
#ifndef HexUtilsH
#define HexUtilsH
//---------------------------------------------------------------------------
#include <vcl.h>

int __export HexChar( char Value );
void __export HexRead( AnsiString Hex, void *Buffer, int Length );
int __export HexReadInt( AnsiString Hex );
AnsiString __export HexString( void *Buffer, int Length );

#endif
