/********************************************************************
*	Module:			emstime.cpp 
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	
*						
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

#ifdef WIN32
#include <windows.h>
#endif
#include <memory.h>
#include "emstime.h"

const long		c_lNanoseconds		  	= 1000000000;

const INT64	c_i64NanosecondsPerMinute = (INT64)60 * (INT64)c_lNanoseconds;
const INT64	c_i64NanosecondsPerHour = (INT64)60 * c_i64NanosecondsPerMinute; 
const INT64 	c_i64NanosecondsPerDay = (INT64)24 * c_i64NanosecondsPerHour;

const double	c_dSecondsPerMinute 	= (double)60;
const double	c_dMinutesPerHour		= (double)60;
const double	c_dHoursPerDay			= (double)24;
const double	c_dNanoseconds			= (double)1000000000;
const double	c_dNanosecondsPerDay 	= c_dNanoseconds * c_dHoursPerDay 
							* c_dMinutesPerHour * c_dSecondsPerMinute;
const double	c_dMinutesPerDay		= ( double )1440.0;
const int		c_nMinimumYear			= 1970;
const int		c_nMaximumYear			= 1970+500;	// check this

const int		c_nLeapYearDaysInMonth[12] 
						= { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

const int		c_nNonLeapYearDaysInMonth[12] 
						= { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

const int		c_nLeapYearDayTable[12] 
						= { 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 };

const int		c_nNonLeapYearDayTable[12] 
						= { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

CEMSTime::CEMSTime( )
{
////	m_time.fileTime.dwMajor = m_time.fileTime.dwMinor = 0;
	m_time.intTime = 0;
}

CEMSTime::CEMSTime( EMSTIME emsTime )
{
	m_time = emsTime;
}

/* Deprecated
CEMSTime::CEMSTime( time_t unixTime )
{
	SetTime( unixTime );
}
*/

CEMSTime::CEMSTime( int nYear, double dDays )
{
	SetTime( nYear, dDays );
}

CEMSTime::CEMSTime( int nYear, int nMonth, int nDay, int nHour, int nMinute, int nSecond, long lNanosecond )
{
	SetTime( nYear, nMonth, nDay, nHour, nMinute, nSecond, lNanosecond );
}

CEMSTime::~CEMSTime()
{
}

BOOL CEMSTime::SetTimeSeconds( time_t unixTime )
{
	INT64 i64UnixTime = unixTime;
	INT64 i64Nanoseconds = c_lNanoseconds;
	m_time.intTime = unixTime*i64Nanoseconds;

	return TRUE;
}

BOOL CEMSTime::SetTimeNano( INT64 i64Time )
{
	m_time.intTime = i64Time;

	return TRUE;
}

BOOL CEMSTime::SetTime( DWORD dwMajor, DWORD dwMinor )
{
////	m_time.fileTime.dwMajor = dwMajor;
////	m_time.fileTime.dwMinor = dwMinor;
	m_time.intTime = ((__int64)dwMajor << 32) + dwMinor;

	return TRUE;
}

/********************************************************************
*		SetTime( nYear, dDays )
*
*				Sets the date using the year number and the number of
*				days ( NOT the Julian Day Number ).
********************************************************************/

BOOL CEMSTime::SetTime( int nYear, double dDays )
{
	BOOL bOK = FALSE;

	m_time.intTime = 0;

	if ( _IsValidYear( nYear ) )
	{
		INT64 i64Days;

		for ( int i = c_nMinimumYear; i < nYear; i++ )
		{
			m_time.intTime += _UnitsThisYear( i );
		}

		i64Days = (INT64)dDays;		// add the integer number of days
		
		m_time.intTime += i64Days * c_i64NanosecondsPerDay;

		dDays -= (double)i64Days;	// now add the fractional days

		m_time.intTime += (INT64)(dDays * c_dNanosecondsPerDay ); 
	
		bOK = TRUE;
	}

	return bOK;
}

BOOL CEMSTime::SetTime( LPEMSTIMEFIELDS lpTimeFields )
{
	BOOL bOK = FALSE;

	if ( lpTimeFields)
	{
		bOK = SetTime( lpTimeFields->nYear, lpTimeFields->nMonth, lpTimeFields->nDay,
					lpTimeFields->nHour, lpTimeFields->nMinute, lpTimeFields->nSecond,
					lpTimeFields->lNanosecond );
	}
	else
		m_time.intTime = 0;

	return bOK;
}

BOOL CEMSTime::SetTime( int nYear, int nMonth, int nDay, int nHour, int nMinute, int nSecond, long lNanoseconds )
{
	BOOL bOK = FALSE;

	m_time.intTime = 0;

	if ( _IsValidYear( nYear ) && _IsValidMonth( nMonth ) && 
			_IsValidDay( nYear, nMonth, nDay ) && _IsValidHour( nHour ) && 
			_IsValidMinute( nMinute ) && _IsValidSecond( nSecond ) )
	{
		int nDayOfYear = _DayOfYear( nYear, nMonth, nDay );

		for ( int i = c_nMinimumYear; i < nYear; i++ )
		{
			m_time.intTime += _UnitsThisYear( i );
		}

		if ( nDayOfYear > 1)
			m_time.intTime += (INT64)(nDayOfYear - 1) * c_i64NanosecondsPerDay;

		if ( nHour )
			m_time.intTime += (INT64)nHour * c_i64NanosecondsPerHour;

		if ( nMinute )
			m_time.intTime += (INT64)nMinute * c_i64NanosecondsPerMinute;

		if ( nSecond )
			m_time.intTime += (INT64)nSecond * (INT64)c_lNanoseconds;

		if ( lNanoseconds )
			m_time.intTime += lNanoseconds;

		bOK = TRUE;
	}

	return bOK;
}

BOOL CEMSTime::SetTime( int nYear, int nJulianDay, int nHour, int nMinute, int nSecond, long lNanoseconds )
{
	BOOL bOK = FALSE;

	m_time.intTime = 0;

	if ( _IsValidYear( nYear ) && _IsValidJulianDay( nYear, nJulianDay ) &&
			_IsValidHour( nHour ) && _IsValidMinute( nMinute ) &&
			_IsValidSecond( nSecond ) )
	{
		for ( int i = c_nMinimumYear; i < nYear; i++ )
		{
			m_time.intTime += _UnitsThisYear( i );
		}

		if ( nJulianDay > 1)
			m_time.intTime += (INT64)(nJulianDay - 1) * c_i64NanosecondsPerDay;

		if ( nHour )
			m_time.intTime += (INT64)nHour * c_i64NanosecondsPerHour;

		if ( nMinute )
			m_time.intTime += (INT64)nMinute * c_i64NanosecondsPerMinute;

		if ( nSecond )
			m_time.intTime += (INT64)nSecond * (INT64)c_lNanoseconds;

		if ( lNanoseconds )
			m_time.intTime += lNanoseconds;

		bOK = TRUE;
	}
	
	return bOK;
}

/** Deprecated
CEMSTime::operator time_t() const
{
	INT64 i64Temp = m_time.intTime / c_lNanoseconds;

	return (time_t)i64Temp;
}
*/

INT64 CEMSTime::NanosecondsFromMidnight( void ) const
{
	INT64 i64Nanoseconds = 0;
	EMSTIMEFIELDS timeFields;

	GetTime( &timeFields );

	i64Nanoseconds = (INT64)timeFields.nHour * c_i64NanosecondsPerHour;

	i64Nanoseconds += (INT64)timeFields.nMinute * c_i64NanosecondsPerMinute;

	i64Nanoseconds += (INT64)timeFields.nSecond * (INT64)c_lNanoseconds;

	i64Nanoseconds += timeFields.lNanosecond; 

	return i64Nanoseconds;
}

double CEMSTime::SecondsFromMidnight( void ) const
{
	return (double)NanosecondsFromMidnight() / c_dNanoseconds;
}

double CEMSTime::MinutesDifferent( EMSTIME fromTime ) const
{
	return SecondsDifferent( fromTime ) / c_dSecondsPerMinute;
}

double CEMSTime::SecondsDifferent( EMSTIME fromTime ) const
{
	INT64 i64Temp = fromTime.intTime - m_time.intTime;	// i.e. difference in nanoseconds

	double dSeconds = (double)i64Temp;

	dSeconds /= c_dNanoseconds;

	return dSeconds;
}

INT64 CEMSTime::NanosecondsDifferent( EMSTIME fromTime ) const
{
	return fromTime.intTime - m_time.intTime;
}


double CEMSTime::DaysDifferent( EMSTIME fromTime ) const
{
	INT64 i64Temp = fromTime.intTime - m_time.intTime;	// i.e. difference in nanoseconds

	return ( (double)i64Temp ) / c_dNanosecondsPerDay;
}

time_t CEMSTime::GetTimeSeconds() const
{
	INT64 i64Temp = m_time.intTime / c_lNanoseconds;

	return (time_t)i64Temp;
}

BOOL CEMSTime::_IsValidHour( int nHour ) const
{
	return ( ( nHour >= 0 ) && ( nHour <= 23 ) );
}

BOOL CEMSTime::_IsValidMinute( int nMinute ) const
{
	return ( ( nMinute >= 0 ) && ( nMinute <= 59 ) );
}

BOOL CEMSTime::_IsValidSecond( int nSecond ) const
{
	return ( ( nSecond >= 0 ) && ( nSecond <= 59 ) );
}

BOOL CEMSTime::_IsValidYear( int nYear ) const
{
	return ( ( nYear >= c_nMinimumYear ) && ( nYear <= c_nMaximumYear ) );
}

BOOL CEMSTime::_IsValidMonth( int nMonth ) const
{
	return ( ( nMonth >= 1 ) && ( nMonth <= 12 ) );
}

BOOL CEMSTime::_IsValidDay( int nYear, int nMonth, int nDay ) const
{
	BOOL bValid = _IsValidYear( nYear ) && _IsValidMonth( nMonth );

	if ( bValid )
	{
		int nMax = 0;

		if ( _IsLeapYear( nYear ) )
			nMax = c_nLeapYearDaysInMonth[ nMonth - 1 ];
		else
			nMax = c_nNonLeapYearDaysInMonth[ nMonth - 1 ];

		bValid = (( nDay >= 1 ) && ( nDay <= nMax ));
	}

	return bValid;
}

BOOL CEMSTime::_IsValidJulianDay( int nYear, int nJulianDay ) const
{
	BOOL bValid = _IsValidYear( nYear );

	if( bValid )
	{
		if( _IsLeapYear( nYear ) )
		{
			bValid = nJulianDay <= ( c_nLeapYearDayTable[11] + c_nLeapYearDaysInMonth[11] );
		}
		else
		{
			bValid = nJulianDay <= ( c_nNonLeapYearDayTable[11] + c_nNonLeapYearDaysInMonth[11] );
		}
	}

	return bValid;
}

BOOL CEMSTime::IsLeapYear( void )
{
	INT64 i64Count = m_time.intTime;
	int nYear = c_nMinimumYear;

	while ( i64Count >= _UnitsThisYear( nYear ) )
	{
		i64Count -= _UnitsThisYear( nYear++ );
	}
	return _IsLeapYear( nYear );	
}

BOOL CEMSTime::_IsLeapYear( int nYear ) const
{
	return ( nYear % 4 == 0 && nYear % 100 != 0 || nYear % 400 == 0 );
}

int CEMSTime::_DayOfYear( int nYear, int nMonth, int nDay ) const
{
	int nDayOfYear = nDay;

	if ( _IsLeapYear( nYear ) )
		nDayOfYear += c_nLeapYearDayTable[ nMonth - 1 ];
	else
		nDayOfYear += c_nNonLeapYearDayTable[ nMonth - 1 ];

	return nDayOfYear;
}

void CEMSTime::GetTime( LPEMSTIMEFIELDS lpTimeFields ) const
{
	if ( lpTimeFields )
	{
		INT64 i64Count = m_time.intTime;
		EMSTIMEFIELDS timeFields;

		memset( &timeFields, 0, sizeof( timeFields ) );

		timeFields.nYear = c_nMinimumYear;
		timeFields.nMonth = 1;
		timeFields.nDay = 1;

		while ( i64Count >= _UnitsThisYear( timeFields.nYear ) )
		{
			i64Count -= _UnitsThisYear( timeFields.nYear++ );
		}

		while ( i64Count >= _UnitsThisMonth( timeFields.nYear, timeFields.nMonth ) )
		{
			i64Count -= _UnitsThisMonth( timeFields.nYear, timeFields.nMonth++ );
		}

		timeFields.nDay = (int)( i64Count / c_i64NanosecondsPerDay ) + 1;

		i64Count -= ( (INT64)(timeFields.nDay - 1) * c_i64NanosecondsPerDay );
		
		timeFields.nHour = (int)(i64Count / c_i64NanosecondsPerHour);

		i64Count -= ( (INT64)timeFields.nHour * c_i64NanosecondsPerHour );
			
		timeFields.nMinute = (int)(i64Count / c_i64NanosecondsPerMinute);

		i64Count -= ( (INT64)timeFields.nMinute * c_i64NanosecondsPerMinute );

		timeFields.nSecond = (int)(i64Count / c_lNanoseconds);

		i64Count -= ( (INT64)timeFields.nSecond * c_lNanoseconds );

		timeFields.lNanosecond = (long)i64Count;

		timeFields.nDayOfWeek = _DayOfWeek( timeFields.nYear, timeFields.nMonth,
												timeFields.nDay );

		timeFields.nJulianDay = _DayOfYear( timeFields.nYear, timeFields.nMonth, 
												timeFields.nDay );

		*lpTimeFields = timeFields;
	}
}

INT64 CEMSTime::_UnitsThisYear( int nYear ) const
{
	INT64 i64Temp = ( _IsLeapYear( nYear ) ) ? 366 : 365;

	return i64Temp * c_i64NanosecondsPerDay;
}

INT64 CEMSTime::_UnitsThisMonth( int nYear, int nMonth ) const
{
	INT64 i64Temp = ( _IsLeapYear( nYear ) ) ? c_nLeapYearDaysInMonth[ nMonth-1 ] :
										c_nNonLeapYearDaysInMonth[ nMonth-1 ]; 
	return i64Temp * c_i64NanosecondsPerDay;
}

// using Zeller's Congruence calculation
//
int	CEMSTime::_DayOfWeek( int nYear, int nMonth, int nDay ) const
{
	int nDayOfWeek = 0; 

	if	( nMonth > 2 )			// Want March to be the first month
		nMonth -= 2;
	else
	{
		nMonth += 10;
		nYear--;
	}

	nDayOfWeek = ((13 * nMonth - 1) / 5) + nDay + ( nYear % 100 ) +
				(( nYear % 100 ) / 4) + ((nYear /100 ) / 4 ) - 2 *
				( nYear / 100 ) + 77 ;

	nDayOfWeek = nDayOfWeek - 7 * ( nDayOfWeek / 7 );

	return nDayOfWeek;
}

double CEMSTime::JulianDayOfTheYear( void ) const
{
	double dJulianDay = 0.0;
	EMSTIMEFIELDS timeFields;

	GetTime( &timeFields );

	dJulianDay = (double)timeFields.nJulianDay;
	dJulianDay += (double)timeFields.nHour / 24.0;
	dJulianDay += (double)timeFields.nMinute / ( 24.0 * 60.0 );
	dJulianDay += (double)timeFields.nSecond / ( 24.0 * 60.0 * 60.0 );
	dJulianDay += (double)timeFields.lNanosecond / c_dNanosecondsPerDay;

	return dJulianDay;
}

double CEMSTime::JulianDate( void ) const
{
	double dJulianDate = 0.0;
	EMSTIMEFIELDS timeFields;
	long lA, lB;

	GetTime( &timeFields );

	timeFields.nYear--;
	lA = timeFields.nYear / 100;
	lB = 2 - lA + ( lA / 4 );
	dJulianDate = (double)(long) ( 365.25 * (double)timeFields.nYear ) +
						(double)(long)( 30.6001 * 14.0 ) + 1720994.5 + (double)lB;

	dJulianDate += (double)timeFields.nJulianDay;
	dJulianDate += (double)timeFields.nHour / 24.0;
	dJulianDate += (double)timeFields.nMinute / ( 24.0 * 60.0 );
	dJulianDate += (double)timeFields.nSecond / ( 24.0 * 60.0 * 60.0 );
	dJulianDate += (double)timeFields.lNanosecond / c_dNanosecondsPerDay;

	return dJulianDate;
}

EMSTIME CEMSTime::AtZeroHour( void ) const
{
	EMSTIMEFIELDS timeFields;
	CEMSTime tempTime;

	GetTime( &timeFields );

	tempTime.SetTime( timeFields.nYear, timeFields.nMonth, timeFields.nDay, 0, 0, 0, 0L );

	return tempTime;
}

EMSTIME CEMSTime::AddNanoseconds( long lNanoseconds )
{
	m_time.intTime += lNanoseconds;
	return m_time;
}

EMSTIME CEMSTime::AddSeconds( double dSeconds )
{
	m_time.intTime += (INT64)( dSeconds * c_dNanoseconds );
	return m_time;
}

EMSTIME CEMSTime::AddSeconds( int nSeconds )
{
	m_time.intTime += (INT64)nSeconds * (INT64)c_lNanoseconds;
	return m_time;
}

EMSTIME CEMSTime::AddMinutes( double dMinutes )
{
	m_time.intTime += (INT64)( 60.0 * dMinutes * c_dNanoseconds );
	return m_time;
}

EMSTIME CEMSTime::AddMinutes( int nMinutes )
{
	m_time.intTime += c_i64NanosecondsPerMinute * (INT64)nMinutes;
	return m_time;
}

EMSTIME CEMSTime::AddHours( double dHours )
{
	INT64 i64Nanoseconds = (INT64)(dHours * c_dNanoseconds);

	m_time.intTime += i64Nanoseconds * 3600;
	return m_time;
}

EMSTIME CEMSTime::AddHours( int nHours )
{
	m_time.intTime += c_i64NanosecondsPerHour * (INT64)nHours;
	return m_time;
}

EMSTIME CEMSTime::AddDays( int nDays )
{
	return AddHours( nDays * 24 );
}

EMSTIME CEMSTime::AddDays( double dDays )
{
	return AddHours( dDays * (double)24.0 );
}


INT64 CEMSTime::Compare( EMSTIME emsTime ) const
{	
	return ( emsTime.intTime - m_time.intTime );
}

bool 
CEMSTime::operator<( const CEMSTime& croTime2 )
{
	bool bRet = false;

	if( (m_time.intTime - croTime2.m_time.intTime) < 0 )
		bRet = true;

	return bRet;
}

bool 
CEMSTime::operator<( const EMSTIME& crstrTime2 )
{
	bool bRet = false;

	if( (m_time.intTime - crstrTime2.intTime) < 0 )
		bRet = true;

	return bRet;
}

bool 
CEMSTime::operator<=( const CEMSTime& croTime2 )
{
	bool bRet = false;

	if( (m_time.intTime - croTime2.m_time.intTime) <= 0 )
		bRet = true;

	return bRet;
}

bool 
CEMSTime::operator<=( const EMSTIME& cstrTime2 )
{
	bool bRet = false;

	if( (m_time.intTime - cstrTime2.intTime) <= 0 )
		bRet = true;

	return bRet;
}

bool 
CEMSTime::operator>( const CEMSTime& croTime2 )
{
	bool bRet = false;

	if( (m_time.intTime - croTime2.m_time.intTime) > 0 )
		bRet = true;

	return bRet;
}

bool 
CEMSTime::operator>( const EMSTIME& cstrTime2 )
{
	bool bRet = false;

	if( (m_time.intTime - cstrTime2.intTime) > 0 )
		bRet = true;

	return bRet;
}

bool 
CEMSTime::operator>=( const CEMSTime& croTime2 )
{
	bool bRet = false;

	if( (m_time.intTime - croTime2.m_time.intTime) >= 0 )
		bRet = true;

	return bRet;
}

bool 
CEMSTime::operator>=( const EMSTIME& cstrTime2 )
{
	bool bRet = false;

	if( (m_time.intTime - cstrTime2.intTime) >= 0 )
		bRet = true;

	return bRet;
}