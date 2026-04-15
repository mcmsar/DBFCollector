/********************************************************************
*	Module:			EMSAntTime.cpp
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	 
*
*				This class adds operator - and > to EMSTime class
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

//#include "stdafx.h"
//#include "mfc test antenna.h"
#include "EMSAntTime.h"
#include <string.h>
#include <stdio.h>
//#include <Winbase.h>
/*
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
*/
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEMSAntTime::CEMSAntTime()
{
}

EMSTIMEFIELDS CEMSAntTime::operator - (const CEMSAntTime SubTime) const
{
	EMSTIMEFIELDS result ;
	CEMSAntTime oper1 = *this ;
	CEMSAntTime oper2 = SubTime ;

	memset(&result,0,sizeof(result));

	result.nYear = ((EMSTIMEFIELDS)oper1).nYear - ((EMSTIMEFIELDS)oper2).nYear;

	if(((EMSTIMEFIELDS)oper1).nMonth < ((EMSTIMEFIELDS)oper2).nMonth)
		_ExtractMonth(result);
	result.nMonth += ((EMSTIMEFIELDS)oper1).nMonth - ((EMSTIMEFIELDS)oper2).nMonth;

	if(((EMSTIMEFIELDS)oper1).nDay < ((EMSTIMEFIELDS)oper2).nDay)
		_ExtractDay(result,oper1);
	result.nDay += ((EMSTIMEFIELDS)oper1).nDay - ((EMSTIMEFIELDS)oper2).nDay;

	if(((EMSTIMEFIELDS)oper1).nHour < ((EMSTIMEFIELDS)oper2).nHour)
		_ExtractHour(result,oper1);
	result.nHour += ((EMSTIMEFIELDS)oper1).nHour - ((EMSTIMEFIELDS)oper2).nHour;

	if(((EMSTIMEFIELDS)oper1).nMinute < ((EMSTIMEFIELDS)oper2).nMinute)
		_ExtractMinute(result,oper1);
	result.nMinute += ((EMSTIMEFIELDS)oper1).nMinute - ((EMSTIMEFIELDS)oper2).nMinute;

	if(((EMSTIMEFIELDS)oper1).nSecond < ((EMSTIMEFIELDS)oper2).nSecond)
		_ExtractSecond(result,oper1);
	result.nSecond += ((EMSTIMEFIELDS)oper1).nSecond - ((EMSTIMEFIELDS)oper2).nSecond;

	if(result.nSecond < 0)
		_ExtractSecond(result,oper1);
	if(result.nMinute < 0)
		_ExtractMinute(result,oper1);
	if(result.nHour < 0)
		_ExtractHour(result,oper1);
	if(result.nDay < 0)
		_ExtractDay(result,oper1);
	if(result.nMonth < 0)
		_ExtractMonth(result);

	return result;

}

bool CEMSAntTime::operator >(const CEMSAntTime& time) const
{
	EMSTIMEFIELDS oper1 = *this;
	EMSTIMEFIELDS oper2 = time;

	if(oper1.nYear > oper2.nYear)
		return true;
	
	if(oper1.nMonth > oper2.nMonth)
		return true;
	
	if(oper1.nDay > oper2.nDay)
		return true;
	
	if(oper1.nHour > oper2.nHour)
		return true;
	
	if(oper1.nMinute > oper2.nMinute)
		return true;
	
	if(oper1.nSecond > oper2.nSecond)
		return true;
	
	if(oper1.lNanosecond > oper2.lNanosecond)
		return true;
	
	return false;
}

CEMSAntTime::operator EMSTIMEFIELDS() const
{
	EMSTIMEFIELDS result;

	GetTime(&result);

	return result;
}

CHAR* CEMSAntTime::GetTimeData()
{
	EMSTIMEFIELDS	result = *this;

	sprintf(szTime,"%d:%d:%d",result.nHour,result.nMinute,result.nSecond);

	return szTime;
}

CHAR* CEMSAntTime::GetDate()
{
	EMSTIMEFIELDS	result = *this;

	sprintf(szDate,"%s %d, %d",Monthes[result.nMonth - 1],result.nDay,result.nYear);

	return szDate;
}

CEMSAntTime::~CEMSAntTime()
{

}
