//---------------------------------------------------------------------------
#ifndef TSARTimeH
#define TSARTimeH
//---------------------------------------------------------------------------
#include <vcl.h>

typedef struct _SARTIME
{
    short Year;
    short Month;
    short DayOfWeek;
    short DayOfYear;
    short Day;
    short Hour;
    short Minute;
    short Second;
    long  Fraction;
} SARTIME, *PSARTIME, *LPSARTIME;

class _export TSARTime
{
public:
    union
    {
        FILETIME    FTime1601;
        __int64     ITime1601;
    };
                    TSARTime( void );
    TSARTime&       NowUTC( void );
    __int64         SecondsToFileTime( const long Seconds );
    long            FileTimeToSeconds( const __int64 FileTime );
    AnsiString      JulianDay( void );
    AnsiString      SpanDir( void );
    AnsiString      CSFormat( void );
    AnsiString      InterBaseFormat( void );
                    operator TDateTime();
                    operator long();
                    operator __int64();
                    operator FILETIME();
                    operator SYSTEMTIME();
                    operator SARTIME();
                    operator AnsiString();
    TSARTime&       operator = (TDateTime DateTimeFormat);
    TSARTime&       operator = (double Time1970Format);
    TSARTime&       operator = (long Time1970Format);
    TSARTime&       operator = (__int64 Time1601Format);
    TSARTime&       operator = (FILETIME FileTimeFormat);
    TSARTime&       operator = (SYSTEMTIME SystemTimeFormat);
    TSARTime&       operator = (SARTIME SarTimeFormat);
    TSARTime&       operator = (AnsiString DateString);
    TSARTime&       operator + (TSARTime SARTime);
    TSARTime&       operator + (__int64 Time1601Format);
    TSARTime&       operator + (long Time1970Format);
    TSARTime&       operator ++ ();
    TSARTime&       operator - (TSARTime SARTime);
    TSARTime&       operator - (__int64 Time1601Format);
    TSARTime&       operator - (long Time1970Format);
    TSARTime&       operator -- ();
};

#endif
