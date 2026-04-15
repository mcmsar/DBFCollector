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

#pragma warning(disable:4786)

#include "sarsattextaccessor.h"
#include "emsexcpt.h"
#include <math.h>
#include "emsclock.h"
#include "emstimehelper.h"


const char* CEMSSarsatTxtAccessor::ms_cszNameFmt = "%-24.24s\n";
const char* CEMSSarsatTxtAccessor::ms_cszLine1NoCheckSum = "%1d %5d%1c %02d%03d%3.3s %014.8lf %s %s %s %1d %4d ";
const char* CEMSSarsatTxtAccessor::ms_cszLine1 = "%s\n";
const char* CEMSSarsatTxtAccessor::ms_cszFirstTimeDerivative1Fmt = "%.8f";
const char* CEMSSarsatTxtAccessor::ms_cszFirstTimeDerivative2AFmt = "%+5e";
const char* CEMSSarsatTxtAccessor::ms_cszFirstTimeDerivative2BFmt = "%s%05.5d%+01d";

const char* CEMSSarsatTxtAccessor::ms_cszLine2NoCheckSum = "%1d %5d %8.4f %8.4f %7.7s %8.4f %8.4f %11.8f%5d ";
const char* CEMSSarsatTxtAccessor::ms_cszLine2 = "%s\n";

const char* CEMSSarsatTxtAccessor::ms_cszTimeDerivative0 = " 00000-0";

CEMSSarsatTxtAccessor::CEMSSarsatTxtAccessor()
{
}

CEMSSarsatTxtAccessor::CEMSSarsatTxtAccessor( const CEMSSarsatTxtAccessor& x ) :
								m_owszFileName( x.m_owszFileName ),
								m_omapTLEs( x.m_omapTLEs )
{
}

CEMSSarsatTxtAccessor::~CEMSSarsatTxtAccessor()
{
}

void 
CEMSSarsatTxtAccessor::Load( const wchar_t* cwszSrcFile )
{
	if( cwszSrcFile )
	{
		m_owszFileName = cwszSrcFile;

		_Load();
	}
}

void 
CEMSSarsatTxtAccessor::Save( const wchar_t* cwszDestFile )
{
	if( cwszDestFile )
	{
		m_owszFileName = cwszDestFile;
	}

	_Save();
}

bool
CEMSSarsatTxtAccessor::GetByNoradID( const ULONG culNoradID, NORADTLE& rData )
{
	bool bRet = false;

	if( m_omapTLEs.IsInMap( culNoradID ) )
	{
		rData = m_omapTLEs.Get( culNoradID );

		bRet = true;
	}

	return bRet;

}

bool
CEMSSarsatTxtAccessor::GetBySatID( const ULONG culSatID, NORADTLE& rData )
{
	return false;
}

void 
CEMSSarsatTxtAccessor::Add( const NORADTLE cstrTLE )
{
	// Overwrite if necessary.
	if( m_omapTLEs.IsInMap( cstrTLE.iNoradNumber ) )
	{
		int iNoradNumber = cstrTLE.iNoradNumber;
		m_omapTLEs.Remove( iNoradNumber );
	}

	m_omapTLEs.Add( cstrTLE.iNoradNumber, cstrTLE );
}

void
CEMSSarsatTxtAccessor::_Load()
{
	if ( !m_owszFileName.empty() )
	{
		FILE *pFile = _wfopen( m_owszFileName.c_str(), L"rt" );

		if ( pFile )
		{
			char szLine1[256], szLine2[256], szSatelliteName[256];
			int i, nNoradNumber, nElementNumber=0;

			while ( !feof( pFile ) )
			{
				NORADTLE orbitData;
				memset( &orbitData, 0, sizeof(NORADTLE) );

				if ( fgets( szSatelliteName, sizeof( szSatelliteName ), pFile ) )
				{	
					if ( fgets( szLine1, sizeof( szLine1 ), pFile ) )
					{	
						TCHAR cCheck1 = _CalcChecksum( szLine1 );

						if ( ( lstrlen( szLine1 ) > 68 ) && ( cCheck1 == szLine1[68] ) )
						{
							if ( fgets( szLine2, sizeof( szLine2 ), pFile ) )
							{	// line 2
								TCHAR cCheck2 = _CalcChecksum( szLine2 );

								if ( ( lstrlen( szLine2 ) > 68 ) && ( cCheck2 == szLine2[68] ) )
								{
//									memset( &tleData, 0, sizeof( tleData ) );
														
									for (i = 18; i < 32; i++)
									{
										if (szLine1[i] == ' ')
											szLine1[i] = '0';	/* No blank between year and days */
									}

									sscanf( &szLine1[7], "%1c", &orbitData.sClassification );
									sscanf( &szLine1[9], "%2d", &orbitData.iLaunchYear);
									sscanf( &szLine1[11], "%3d", &orbitData.iLaunchNumber);
									sscanf( &szLine1[14], "%3c", &orbitData.asLaunchPiece[0]);

									sscanf (&szLine1[18], "%14lf", &orbitData.dEpoch);

									sscanf (&szLine1[33], "%10lf",  &orbitData.dTimeDerivative1);

									sscanf (&szLine1[44], "%6lf",   &orbitData.dTimeDerivative2);  
									orbitData.dTimeDerivative2 /= 100000.0;

									int nExp = 0;

									sscanf (&szLine1[50], "%2d",   &nExp  );

									if ( nExp != 0 )
										orbitData.dTimeDerivative2 *= pow( 10.0 , nExp );

									sscanf (&szLine1[53], "%6lf",   &orbitData.dBStar ); 
									orbitData.dBStar  /= 100000.0;

									sscanf (&szLine1[59], "%2d",   &nExp );

									if ( nExp != 0 )
										orbitData.dBStar *= pow( 10.0 , nExp );

									for ( i = 64; i < 68; i++ )
									{
										if (szLine1[i] == ' ')
  										szLine1[i] = '0';  /* No blank at the beginning of orbit number */
									}
									sscanf( &szLine1[64], "%4d", &nElementNumber );

									szLine2[25] = '.';	/* Decimal point for eccentricity */

									for ( i = 63; i < 68; i++ )
									{
										if (szLine2[i] == ' ')
  										szLine2[i] = '0';  /* No blank at the beginning of orbit number */
									}
									sscanf (&szLine2[ 2], "%5d",	&nNoradNumber );
									sscanf (&szLine2[ 8], "%8lf",   &orbitData.dInclination );
									sscanf (&szLine2[17], "%8lf",   &orbitData.dRightAscension);
									sscanf (&szLine2[25], "%8lf",   &orbitData.dEccentricity );
									sscanf (&szLine2[34], "%8lf",   &orbitData.dArgPerigee );
									sscanf (&szLine2[43], "%8lf",   &orbitData.dMeanAnomoly );
									sscanf (&szLine2[52], "%11lf",  &orbitData.dMeanMotion );
									sscanf (&szLine2[63], "%5d",	&orbitData.iRevolutionNumber );


									_RemoveTrailingUnprintables( szSatelliteName );

									orbitData.iElementNumber = nElementNumber;
									orbitData.iNoradNumber = nNoradNumber;

									strncpy( orbitData.szName, szSatelliteName,
																	32 );

									m_omapTLEs.Add( nNoradNumber, orbitData );

								}
								else
									THROW_RUNTIME_EXCEPTION( EMS_ORBIT_BAD_DATA );
							}
						}
					}
				}
			}

			fclose( pFile );
		}
		else
			THROW_RUNTIME_EXCEPTION(  EMS_ORBIT_NO_DATA );
	}
}

void 
CEMSSarsatTxtAccessor::_Save()
{
	if( !m_owszFileName.empty() )
	{
		FILE *pFile = _wfopen( m_owszFileName.c_str(), L"wt" );

		if ( pFile )
		{
			m_omapTLEs.MoveFirst();

			for( ULONG l = 0; l < m_omapTLEs.Count(); l++ )
			{
				NORADTLE orbitData = m_omapTLEs.GetNext();

				char szLine1[256], szLine2[256];

				fprintf( pFile, ms_cszNameFmt, orbitData.szName );

				sprintf( szLine1, ms_cszLine1NoCheckSum, 
							1, 
							orbitData.iNoradNumber,
							orbitData.sClassification,
							orbitData.iLaunchYear,
							orbitData.iLaunchNumber,
							orbitData.asLaunchPiece,
							orbitData.dEpoch,
							_FmtTimeDerivative1Output( orbitData.dTimeDerivative1 ).c_str(),
							_FmtTimeDerivative2Output( orbitData.dTimeDerivative2 ).c_str(),
							_FmtTimeDerivative2Output( orbitData.dBStar ).c_str(),
							orbitData.iEphemerisType,
							orbitData.iElementNumber);

				szLine1[68] = _CalcChecksum( szLine1 );

				fprintf( pFile, ms_cszLine1, szLine1 );

				sprintf( szLine2, ms_cszLine2NoCheckSum,
							2,
							orbitData.iNoradNumber,
							orbitData.dInclination,
							orbitData.dRightAscension,
							_ExtractDecimalPortion( orbitData.dEccentricity ).c_str(),
							orbitData.dArgPerigee,
							orbitData.dMeanAnomoly,
							orbitData.dMeanMotion,
							orbitData.iRevolutionNumber );

				szLine2[68] = _CalcChecksum( szLine2 );

				fprintf( pFile, ms_cszLine2, szLine2 );

			}

			fclose( pFile );
		}
		else
			THROW_RUNTIME_EXCEPTION(  EMS_ORBIT_NO_DATA );
	}
}

int
CEMSSarsatTxtAccessor::_RemoveTrailingUnprintables( char* szText )
{
	int nLength = ( szText ) ? lstrlen( szText ) : 0;

	while (( nLength > 0 ) && ( szText[nLength-1] <= 32 ) )
	{
		szText[ --nLength ] = 0;
	}

	return nLength;
}

char
CEMSSarsatTxtAccessor::_CalcChecksum( const char* cszBuffer )
{
	char cCheckDigit = 0;

	if ( cszBuffer && *cszBuffer )
	{
		int nLength = strlen( cszBuffer );

		if ( nLength >= 68 )
		{
			int nCounter = 0;

			for ( int i = 0; i < 68; i++ )
			{
				switch ( cszBuffer[i] )
				{
					case '0': nCounter += 0; break;
					case '1': nCounter += 1; break;
					case '2': nCounter += 2; break;
					case '3': nCounter += 3; break;
					case '4': nCounter += 4; break;
					case '5': nCounter += 5; break;
					case '6': nCounter += 6; break;
					case '7': nCounter += 7; break;
					case '8': nCounter += 8; break;
					case '9': nCounter += 9; break;
					case '-': nCounter += 1; break;
					default: break;
				}
			}
			if ( nCounter )
				cCheckDigit = ( nCounter % 10 ) + '0';
		}
	}

	return cCheckDigit;
}

std::string
CEMSSarsatTxtAccessor::_FmtTimeDerivative1Output( const double cdValue )
{
	std::string szRet;

	char szField[ 9 ];
	memset( szField, 0, 9*sizeof(char) );

	sprintf( szField, ms_cszFirstTimeDerivative1Fmt, cdValue );

	// The output format is +.NNNNNNNN
	if( cdValue < 0.0 )
	{
		// Take out the leading zero.
		strcpy( szField, &szField[1] );
		szField[0] = '-';
	}
	else
	{
		szField[0] = ' ';
	}
	
	szRet = szField;

	return szRet;

}

std::string
CEMSSarsatTxtAccessor::_FmtTimeDerivative2Output( const double cdValue )
{
	std::string oszRet;

	if( cdValue != 0.0 )
	{
		char szField[ 32 ];
		memset( szField, 0, 32*sizeof(char) );

		sprintf( szField, ms_cszFirstTimeDerivative2AFmt, cdValue );

		char* szPrefix = " ";

		// The output format is +NNNNN-N
		if( cdValue < 0.0 )
		{
			szPrefix = "-";
		}

		std::string szTemp( szField );

		// Skip over the first decimal and grab up to the "e".
		std::string::size_type iStart = szTemp.find( "." );
		
		if( std::string::npos == iStart )
		{
			THROW_RUNTIME_EXCEPTION( EMS_SYNTAX_ERROR );
		}

		// Skip over sign and get the digits preceding the decimal point.
		std::string oszPreDecimal = szTemp.substr( 1, iStart - 1 );

		std::string::size_type iEnd = szTemp.find( "e" );

		if( std::string::npos == iEnd )
		{
			THROW_RUNTIME_EXCEPTION( EMS_SYNTAX_ERROR );
		}

		std::string oszPart1 = oszPreDecimal;
		oszPart1.append( szTemp.substr( iStart + 1, ( iEnd - 1 ) - iStart ) );
		int iPart1 = atoi( oszPart1.c_str() );

		// Now get the exponent.
		std::string oszExp = szTemp.substr( iEnd + 1 );
		int iExponent = atoi( oszExp.c_str() );

		sprintf( szField, ms_cszFirstTimeDerivative2BFmt, szPrefix, iPart1/100, iExponent + 1 );

		oszRet = szField;
	}
	else
	{
		oszRet = ms_cszTimeDerivative0;
	}
	
	return oszRet;

}

std::string
CEMSSarsatTxtAccessor::_ExtractDecimalPortion( const double cdValue )
{
	std::string oszRet;

	char szTemp[32];
	memset( szTemp, 0, 32*sizeof(char) );

	sprintf( szTemp, "%.10f", cdValue );

	std::string oszTemp( szTemp );

	std::string::size_type iPos = oszTemp.find( "." );

	if( std::string::npos == iPos )
	{
		THROW_RUNTIME_EXCEPTION( EMS_SYNTAX_ERROR );
	}

	oszRet = oszTemp.substr( iPos + 1 );

	return oszRet;
}

void
CEMSSarsatTxtAccessor::_ConvertNORADTLEtoEMSTLEDATA2( NORADTLE rNoradTLE, EMSTLEDATA2& rEMSTLEdata2 )
{
	CEMSSystemClock oClock;
	
	rEMSTLEdata2.tle.timeEpoch = CEMSTimeHelper::ConvertEpochTime(rNoradTLE.dEpoch);
	rEMSTLEdata2.tle.fXndt2o	= rNoradTLE.dTimeDerivative1;
	rEMSTLEdata2.tle.fXndd6o	= rNoradTLE.dTimeDerivative2;
	rEMSTLEdata2.tle.fBStar	= rNoradTLE.dBStar;
	rEMSTLEdata2.tle.elem.var.fInclination	= 	rNoradTLE.dInclination;
	rEMSTLEdata2.tle.elem.var.fRightAscNode	= 	rNoradTLE.dRightAscension;
	rEMSTLEdata2.tle.elem.var.fEccentricity	= 	rNoradTLE.dEccentricity;
	rEMSTLEdata2.tle.elem.var.fArgPerigee		=	rNoradTLE.dArgPerigee;
	rEMSTLEdata2.tle.elem.var.fMeanAnomaly	= 	rNoradTLE.dMeanAnomoly;
	rEMSTLEdata2.tle.elem.var.fMeanMotion		= 	rNoradTLE.dMeanMotion;
	rEMSTLEdata2.tle.nOrbitNumber = 	rNoradTLE.iRevolutionNumber;
	rEMSTLEdata2.timeEffective	=	rEMSTLEdata2.tle.timeEpoch;
	rEMSTLEdata2.timeModified	=	oClock.GetTime();
}

void
CEMSSarsatTxtAccessor::GetTLE2List( CEMSObjectMap<int, EMSTLEDATA2>& romapTLE2 )
{
	EMSTLEDATA2 emsTLEdata2;
	
	m_omapTLEs.MoveFirst();

	for( ULONG l = 0; l < m_omapTLEs.Count(); l++ )
	{
		int iNoradID = 0;
		memset( &emsTLEdata2, 0, sizeof( EMSTLEDATA2 ) );
		NORADTLE orbitData;
		m_omapTLEs.GetNext( iNoradID, orbitData );

		_ConvertNORADTLEtoEMSTLEDATA2( orbitData, emsTLEdata2 );
		
		romapTLE2.Add( iNoradID, emsTLEdata2 );
	}

}
