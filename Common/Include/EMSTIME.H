/********************************************************************
*	Module:			emstime.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:	The basic unit of time is nanoseconds counted from 
*					1970 January 1, and stored as a 64-bit integer.
*
*********************************************************************
*	              Copyright (c) 2001 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2001/03/22	rvw	start

********************************************************************/

#ifndef INC_EMSTIME
#define INC_EMSTIME

#include "emstypes.h"
#include <time.h>

// Note: nDayOfWeek is 0 ( Sunday ) -> 6 ( Saturday )

typedef struct _tagEMSTIMEFIELDS
{
	int	nYear;
	int	nMonth;
	int	nDay;
	int	nHour;
	int	nMinute;
	int	nSecond;
	long	lNanosecond;
	int	nDayOfWeek;
	int	nJulianDay;
} EMSTIMEFIELDS, FAR *LPEMSTIMEFIELDS;

class CEMSTime
{
public:
	CEMSTime();
	CEMSTime( EMSTIME time );
	CEMSTime( int nYear, double dDays );
	CEMSTime( int nYear, int nMonth=1, int nDay=1, int nHour=0, int nMinute=0, int nSecond=0, long lNanoseconds=0 );
	~CEMSTime();

	BOOL SetTimeSeconds( time_t unixTime );
	BOOL SetTimeNano( INT64 i64Time );
	BOOL SetTime( DWORD dwMajor, DWORD dwMinor );
	BOOL SetTime( int nYear, double dDays );
	BOOL SetTime( LPEMSTIMEFIELDS lpTimeFields );
	inline BOOL SetTime( void ) { return SetTime( 0, 0 ); }
	inline BOOL ResetTime( void ) { return SetTime( 0, 0 ); }
	BOOL SetTime( int nYear, int nMonth, int nDay, int nHour, int nMinute, int nSecond, long lNanoseconds );
	BOOL SetTime( int nYear, int nJulianDay, int nHour, int nMinute, int nSecond, long lNanoseconds );
	inline BOOL SetTime( EMSTIME emsTime ) { m_time = emsTime; return TRUE; }
	inline BOOL SetTime( CEMSTime emsTime ) { return SetTime( (EMSTIME)emsTime ); }

	BOOL IsLeapYear( void );

	EMSTIME AddNanoseconds( long lNanoseconds );
	EMSTIME AddSeconds( int nSeconds );
	EMSTIME AddSeconds( double dSeconds );
	EMSTIME AddMinutes( int nMinutes );
	EMSTIME AddMinutes( double dMinutes );
	EMSTIME AddHours( int nHours );
	EMSTIME AddHours( double dHours );
	EMSTIME AddDays( int nDays );
	EMSTIME AddDays( double dDays );

	EMSTIME AtZeroHour( void ) const;

	INT64 Compare( EMSTIME emsTime ) const;

	double JulianDate( void ) const;
	double JulianDayOfTheYear( void ) const;

	inline operator EMSTIME() const { return m_time; }

	double DaysDifferent( EMSTIME fromTime ) const;
	double MinutesDifferent( EMSTIME fromTime ) const;
	double SecondsDifferent( EMSTIME fromTime ) const;
	INT64 NanosecondsDifferent( EMSTIME fromTime ) const;

	INT64 NanosecondsFromMidnight( void ) const;
	double SecondsFromMidnight( void ) const;

	void GetTime( LPEMSTIMEFIELDS lpTimeFields ) const;

//// 	inline DWORD Major(void) { return m_time.fileTime.dwMajor; }
////	inline DWORD Minor(void) { return m_time.fileTime.dwMinor; }
 	inline DWORD Major(void) { return (DWORD)(m_time.intTime >> 32); }
	inline DWORD Minor(void) { return (DWORD)(m_time.intTime); }

	inline BOOL IsZero( void ) { return ( m_time.intTime == 0 ); } 

	bool operator<( const CEMSTime& croTime2 );
	bool operator<( const EMSTIME& crstrTime2 );
	bool operator<=( const CEMSTime& croTime2 );
	bool operator<=( const EMSTIME& crstrTime2 );
	bool operator>( const CEMSTime& croTime2 );
	bool operator>( const EMSTIME& crstrTime2 );
	bool operator>=( const CEMSTime& croTime2 );
	bool operator>=( const EMSTIME& crstrTime2 );

	INT64 GetTimeNano() const { return m_time.intTime; }
	time_t GetTimeSeconds() const;

protected: // methods
	BOOL _IsValidYear( int nYear ) const;
	BOOL _IsValidMonth( int nMonth ) const;
	BOOL _IsValidHour( int nHour ) const;
	BOOL _IsValidMinute( int nMinute ) const;
	BOOL _IsValidSecond( int nSecond ) const;
	BOOL _IsValidDay( int nYear, int nMonth, int nDay ) const;
	BOOL _IsValidJulianDay( int nYear, int nJulianDay ) const;
	BOOL _IsLeapYear( int nYear ) const;
	int _DayOfYear( int nYear, int nMonth, int nDay ) const;
	INT64 _UnitsThisYear( int nYear ) const;
	INT64 _UnitsThisMonth( int nYear, int nMonth ) const;
	int	_DayOfWeek( int nYear, int nMonth, int nDay ) const;

private:	// data
	EMSTIME m_time;
};


#endif // INC_EMSTIME
