/*********************************************************************
*	              Copyright (c) 2006 by EMS Technologies, Inc.,
*										All rights reserved
*	This program is unpublished software and contains the trade secrets
*	and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	$Log:
	$
********************************************************************/

#include "tle.h"
#include "emstime.h"
#include "emsexcpt.h"
#include "convutility.h"
#include <math.h>
#include "ccbootstrap.h"
#include "satclient.h"

const char* CEMSTLE::ms_cszTLELine1Fmt = "%s";
const char* CEMSTLE::ms_cszTLELine2Fmt = "1 %05dU %05d%C   %02.2d%03.3d.%08.8d %C.%08d %C%05d-%01d %C%05d-%01d 0 %4d";
const char* CEMSTLE::ms_cszTLELine3Fmt = "2 %05d %8.4f %8.4f %07d %8.4f %8.4f %11.8f%5d";

const int CEMSTLE::ms_ciMaxNameLength = 24;		// according to spec.
const int CEMSTLE::ms_ciMaxLineLength = 255;

const wchar_t* CEMSTLE::ms_cwszNoradName = L"satellite[@id=%d]/noradname";
const wchar_t* CEMSTLE::ms_cwszNoradNumber = L"satellite[@id=%d]/noradid";


CEMSTLE::CEMSTLE()
{
	memset( &m_strTLE, 0, sizeof(m_strTLE) );
}

CEMSTLE::CEMSTLE( const CEMSTLE& x ) : m_strTLE( x.m_strTLE )
{
}

CEMSTLE::~CEMSTLE()
{
}

void 
CEMSTLE::Set( const EMSTLERECORD cstrTLE )
{
	m_strTLE = cstrTLE;
}

void 
CEMSTLE::SetSatelliteMapping( const wchar_t* cwszSatMap )
{
	if( cwszSatMap )
	{
		m_oSatMapping.SetSource( cwszSatMap );
	}
}

std::string 
CEMSTLE::GetAsString()
{
	std::string oszRet;

	// Line 1
	oszRet += _GetLine1();

	// Line 2
	oszRet.append(";");
	oszRet += _GetLine2();

	// Line 3
	oszRet.append(";");
	oszRet += _GetLine3();

	return oszRet;
}

std::string 
CEMSTLE::GetAsString2()
{
	std::string oszRet;

	// Line 1
	oszRet += _GetLine1();

	// Line 2
	oszRet.append("\r\n");
	oszRet += _GetLine2();

	// Line 3
	oszRet.append("\r\n");
	oszRet += _GetLine3();

	return oszRet;
}

std::string 
CEMSTLE::GetNoradName()
{
	return _GetSatelliteName();
}

std::string
CEMSTLE::_GetLine1()
{
	std::string oszRet;

	// Line 1
	char szLine1[ ms_ciMaxNameLength + 1 ];
	memset( szLine1, 0, ( ms_ciMaxNameLength + 1)*sizeof(char) );
	_snprintf( szLine1, 24, ms_cszTLELine1Fmt, _GetSatelliteName().c_str() );

	oszRet = szLine1;

	return oszRet;
}

std::string
CEMSTLE::_GetLine2()
{
	std::string oszRet;

	CEMSTime oTmpTime;
	oTmpTime.SetTime(m_strTLE.timeEpoch);

	EMSTIMEFIELDS timeFields;
	oTmpTime.GetTime(&timeFields);

	ULONG ulYear = timeFields.nYear - (timeFields.nYear/100)*100;

	//Get fraction of the day
	const double	c_dSecondsPerMinute 	= (double)60;
	const double	c_dMinutesPerHour		= (double)60;
	const double	c_dHoursPerDay			= (double)24;
	const double	c_dNanoseconds			= (double)1000000000;
	const double	c_dNanosecondsPerDay 	= c_dNanoseconds * c_dHoursPerDay 
								* c_dMinutesPerHour * c_dSecondsPerMinute;

	double dDay = (((timeFields.nHour * c_dMinutesPerHour * c_dSecondsPerMinute) +  (timeFields.nMinute * c_dSecondsPerMinute) + 
					(timeFields.nSecond)) * c_dNanoseconds ) + timeFields.lNanosecond;

	ULONG ulFractDay = (ULONG) ((dDay/c_dNanosecondsPerDay) * 100000000);

	LONG lDMM1 = (LONG) ((double) m_strTLE.fXndt2o * (double) 100000000);

	//Format DMM2
	char szDMM2[20];
	memset( szDMM2, 0, 20*sizeof(char) );
	sprintf(szDMM2, "%09.5E", m_strTLE.fXndd6o);

	char* pszDMM2Exp = NULL;
    if( m_strTLE.fXndd6o < 1.0 && 0.0 != m_strTLE.fXndd6o )
        pszDMM2Exp = strrchr( szDMM2, '-' );
    else
        pszDMM2Exp = strrchr( szDMM2, '+' );

    pszDMM2Exp++;

	ULONG ulDMM2Exp = atoi( pszDMM2Exp );
	
	LONG lDMM2 = (LONG) ((m_strTLE.fXndd6o * pow((float)10, (int)ulDMM2Exp)) * 10000);

	if (ulDMM2Exp >= 1)
	{
		ulDMM2Exp = ulDMM2Exp - 1;
	}
	else
	{
		ulDMM2Exp = 0;
	}
	
	//Format Bstar
	char szBStar[20];
	memset( szBStar, 0, 20*sizeof(char) );
	sprintf(szBStar, "%09.5E", m_strTLE.fBStar);

	char* pszBStarExp = NULL;
    if( m_strTLE.fBStar < 1.0 && 0.0 != m_strTLE.fBStar )
        pszBStarExp = strrchr( szBStar, '-' );
    else
        pszBStarExp = strrchr( szBStar, '+' );

    pszBStarExp++;

	ULONG ulBStarExp = atoi(pszBStarExp);

	LONG lBStar = (LONG) ((m_strTLE.fBStar * pow((double)10, (double)ulBStarExp)) * 10000);
	if (ulBStarExp >= 1)
	{
		ulBStarExp = ulBStarExp - 1;
	}
	else
	{
		ulBStarExp = 0;
	}
		
	char szBuffer[ ms_ciMaxLineLength + 1 ];
	memset( szBuffer, 0, (ms_ciMaxLineLength + 1)*sizeof(char) );

	_snprintf( szBuffer, ms_ciMaxLineLength, ms_cszTLELine2Fmt,
						_GetNoradNumber(),
						0,
						'A',
						ulYear,
						timeFields.nJulianDay,
						ulFractDay,
                        lDMM1 < 0 ? '-' : ' ',
                        lDMM1 < 0 ? -lDMM1 : lDMM1,
                        lDMM2 < 0 ? '-' : ' ',
                        lDMM2 < 0 ? -lDMM2 : lDMM2,
						ulDMM2Exp,
                        lBStar < 0 ? '-' : ' ',
						lBStar < 0 ? -lBStar : lBStar,
						ulBStarExp,
						_GetElementNumber() );

	int iCheckSum = _GetCheckSum(szBuffer);

	char szBufferWithCheckSum[ ms_ciMaxLineLength + 1 ];
	memset( szBufferWithCheckSum, 0, (ms_ciMaxLineLength + 1)*sizeof(char) );

	_snprintf( szBufferWithCheckSum, ms_ciMaxLineLength, "%s%01d", szBuffer, iCheckSum );

	oszRet = szBufferWithCheckSum;

	return oszRet;
}

std::string
CEMSTLE::_GetLine3()
{
	std::string oszRet;

	ULONG ulEccentricity = (ULONG) ( (double)m_strTLE.fEccentricity * 10000000.0 );
			
	_CorrectRange(&m_strTLE.fArgPerigee);
	_CorrectRange(&m_strTLE.fMeanAnomaly);
	_CorrectRange(&m_strTLE.fRightAscNode);

	char szBuffer[ ms_ciMaxLineLength + 1 ];
	memset( szBuffer, 0, (ms_ciMaxLineLength + 1)*sizeof(char) );

	_snprintf( szBuffer, ms_ciMaxLineLength, ms_cszTLELine3Fmt,
						_GetNoradNumber(),
						m_strTLE.fInclination,
						m_strTLE.fRightAscNode,
						ulEccentricity,
						m_strTLE.fArgPerigee,
						m_strTLE.fMeanAnomaly,
						m_strTLE.fMeanMotion,
						m_strTLE.nOrbitNumber );

	int iCheckSum = _GetCheckSum(szBuffer);

	char szBufferWithCheckSum[ ms_ciMaxLineLength + 1 ];
	memset( szBufferWithCheckSum, 0, (ms_ciMaxLineLength + 1)*sizeof(char) );

	_snprintf( szBufferWithCheckSum, ms_ciMaxLineLength, "%s%01d", szBuffer, iCheckSum );

	oszRet = szBufferWithCheckSum;

	return oszRet;
}

int 
CEMSTLE::_GetCheckSum(char* pszBuffer)
{
	if( !pszBuffer )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	char str[2];
	int index = 0;
	int iCheckSum = 0;

	while (pszBuffer[index] != '\0')
	{
		strncpy(str, &pszBuffer[index], 1);

		switch (pszBuffer[index])
		{
			case '-':
			   iCheckSum++;
			   break;
			case '+':
			case '.':
			case ' ':
			   break;
			default:
				iCheckSum = iCheckSum + atoi(str);
				break;
		}
		index++;

	}
	
	return (int) fmod((float)iCheckSum, (float)10);
}

void 
CEMSTLE::_CorrectRange( double* pdValue )
{
	if( !pdValue )
	{
		THROW_NULL_POINTER_EXCEPTION();
	}

	while (*pdValue < 0)
	{
		*pdValue = *pdValue + (double) 360;
	}


	while (*pdValue > 360 )
	{
		*pdValue = *pdValue - (double) 360;
	}

}

std::string 
CEMSTLE::_GetSatelliteName()
{
	wchar_t wszKey[ 128 ];
	memset( wszKey, 0, 128*sizeof(wchar_t) );

	_snwprintf( wszKey, 127, ms_cwszNoradName, m_strTLE.ulSatID );

	if( CCBootstrap::IsMEOSystem() )
	{
		SatClient oSatClient( CCBootstrap::GetConfigServerHost(), CCBootstrap::GetConfigServerPort() );
		string  szSatId = CEMSConversionUtil::ConvertToStringA( m_strTLE.ulSatID );
		SatConfig* pSatConfig = oSatClient.getById( szSatId );
		return ( pSatConfig->GetName() );
	}
	else
	{
		return CEMSConversionUtil::ConvertToString( m_oSatMapping.GetElementValue( wszKey ).c_str() );
	}

}

int 
CEMSTLE::_GetNoradNumber()
{
	wchar_t wszKey[ 128 ];
	memset( wszKey, 0, 128*sizeof(wchar_t) );

	_snwprintf( wszKey, 127, ms_cwszNoradNumber, m_strTLE.ulSatID );

	if( CCBootstrap::IsMEOSystem() )
	{
		SatClient oSatClient( CCBootstrap::GetConfigServerHost(), CCBootstrap::GetConfigServerPort() );
		string  szSatId = CEMSConversionUtil::ConvertToStringA( m_strTLE.ulSatID );
		SatConfig* pSatConfig = oSatClient.getById( szSatId );
		return ( pSatConfig->GetNoradID() );
	}
	else
	{
		return m_oSatMapping.GetElementValueInt( wszKey );
	}
}

int
CEMSTLE::_GetElementNumber()
{
	return 0;
}