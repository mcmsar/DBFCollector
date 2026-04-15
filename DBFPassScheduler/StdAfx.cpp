// stdafx.cpp : source file that includes just the standard includes
//	DBFPassScheduler.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include <stdexcept>
// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
namespace std
{
    class _String_base
    { 
    public:
        static void __cdecl _Xlen(void) ; 
        static void __cdecl _Xran(void) ; 
    };
};

void __cdecl std::_String_base::_Xlen(void) 
{   // report a length_error
_Xlength_error("string too long");
}
void __cdecl std::_String_base::_Xran(void) 
{   // report an out_of_range error
_Xout_of_range("invalid string position");
}