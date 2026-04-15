/********************************************************************
*	Module:			EMSAntTime.hpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	 
*
*				This class adds  -  > operators and GetDate() to EMSTime class
*					 
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
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

	Rev	Date			Auth			Changes
	===	====			=============	=======

	0.0	2001/08/03		Igor Zabarsky	start

********************************************************************/

#if !defined(AFX_EMSANTTIME_H__4CD84BE6_85B7_11D5_85CD_00A0C93DD1BA__INCLUDED_)
#define AFX_EMSANTTIME_H__4CD84BE6_85B7_11D5_85CD_00A0C93DD1BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
const int		c_nLeapYearDaysInMonth[12] 
						= { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

const int		c_nNonLeapYearDaysInMonth[12] 
						= { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

const char	Monthes[][4] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug",
							"Sep","Oct","Nov","Dec"};

#include "emstime.h"
class CEMSAntTime : public CEMSTime  
{
public:
	CEMSAntTime();
	CEMSAntTime(EMSTIMEFIELDS fields):
		CEMSTime(fields.nYear, fields.nMonth, fields.nDay, fields.nHour,
			fields.nMinute, fields.nSecond, fields.lNanosecond){}
	CEMSAntTime( EMSTIME emsTime ):CEMSTime(emsTime){}
	CEMSAntTime( time_t unixTime ):CEMSTime(unixTime){}
	CEMSAntTime( int nYear, double dDays ):CEMSTime(nYear,dDays){}
	CEMSAntTime( int nYear, int nMonth=1, int nDay=1, int nHour=0, int nMinute=0, 
		int nSecond=0, long lNanoseconds=0 ):CEMSTime(nYear, nMonth, nDay, nHour,
		nMinute, nSecond, lNanoseconds){}
	
	CHAR* GetDate();
	CHAR* GetTimeData();
	operator EMSTIMEFIELDS() const;
	EMSTIMEFIELDS operator - (const CEMSAntTime SubTime) const;
	bool operator >(const CEMSAntTime& time) const;
	virtual ~CEMSAntTime();

protected:

	CHAR			szDate[256];
	CHAR			szTime[256];

	void _ExtractMonth(EMSTIMEFIELDS& result) const
	{
		result.nYear--;
		result.nMonth += 12;
	}
	void _ExtractDay(EMSTIMEFIELDS& result,const CEMSAntTime& oper1) const
	{
		if(result.nMonth-- < 0)
			_ExtractMonth(result);
		CEMSAntTime TempTime(result.nYear,result.nMonth,result.nDay,result.nHour,
								result.nMinute,result.nSecond);

		result.nDay += (_IsLeapYear(((EMSTIMEFIELDS)TempTime).nYear)) ? 
			c_nLeapYearDaysInMonth[((EMSTIMEFIELDS)TempTime).nMonth-1]:
			c_nNonLeapYearDaysInMonth[((EMSTIMEFIELDS)TempTime).nMonth-1];
	}

	void _ExtractHour(EMSTIMEFIELDS& result,const CEMSAntTime& oper1) const
	{
		if(result.nDay-- < 0)
			_ExtractDay(result,oper1);
		result.nHour += 24; 
	}

	void _ExtractMinute(EMSTIMEFIELDS& result,const CEMSAntTime& oper1) const
	{
		if(result.nHour-- < 0)
			_ExtractHour(result,oper1);
		result.nMinute += 60; 
	}

	void _ExtractSecond(EMSTIMEFIELDS& result,const CEMSAntTime& oper1) const
	{
		if(result.nMinute-- < 0)
			_ExtractMinute(result,oper1);
		result.nSecond += 60; 
	}

};

#endif // !defined(AFX_EMSANTTIME_H__4CD84BE6_85B7_11D5_85CD_00A0C93DD1BA__INCLUDED_)
