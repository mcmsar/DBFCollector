#include "commandlinehelper.h"
#include "emstime.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

CEMSCommandLineHelper::CEMSCommandLineHelper()
{
}

CEMSCommandLineHelper::CEMSCommandLineHelper( const CEMSCommandLineHelper& x )
{
}

CEMSCommandLineHelper::~CEMSCommandLineHelper()
{
}

bool 
CEMSCommandLineHelper::ParseDateTime( char* szParam, CEMSTime* pTime )
{
	bool bRet = true;

	if( !szParam || !pTime )
	{
		bRet = FALSE;
	}

	if( bRet )
	{
		char* szToken = strtok( szParam, ":" );

		long lElement = 0;

		int iYear = 0;
		int iJulianDay = 0;
		int iHour = 0;
		int iMinute = 0;
		int iSecond = 0;

		while( szToken )
		{
			switch( lElement )
			{
			case 0:	// YYYY
				iYear = atoi( szToken );
				break;
			case 1: // DDD
				iJulianDay = atoi( szToken );
				break;
			case 2:	// HH
				iHour = atoi( szToken );
				break;
			case 3:	// MM
				iMinute = atoi( szToken );
				break;
			case 4:	// SS
				iSecond = atoi( szToken );
				break;
			default:
				break;

			}

			szToken = strtok( 0, ":" );
			lElement++;
		}

		bRet = (TRUE == pTime->SetTime( iYear, iJulianDay, iHour, iMinute, iSecond, 0L )) ? true : false;
	}
	
	return bRet;
}

bool 
CEMSCommandLineHelper::ParseDateTimeStd( char* szParam, CEMSTime* pTime )
{
	bool bRet = true;

	if( !szParam || !pTime )
	{
		bRet = FALSE;
	}

	if( bRet )
	{
		char* szToken = strtok( szParam, ":" );

		long lElement = 0;

		int iYear = 0;
		int iMonth = 0;
		int iDay = 0;
		int iHour = 0;
		int iMinute = 0;
		int iSecond = 0;

		while( szToken )
		{
			switch( lElement )
			{
			case 0:	// YYYY
				iYear = atoi( szToken );
				break;
			case 1: // MM
				iMonth = atoi( szToken );
				break;
			case 2: // DD
				iDay = atoi( szToken );
				break;
			case 3:	// HH
				iHour = atoi( szToken );
				break;
			case 4:	// MM
				iMinute = atoi( szToken );
				break;
			case 5:	// SS
				iSecond = atoi( szToken );
				break;
			default:
				break;

			}

			szToken = strtok( 0, ":" );
			lElement++;
		}

		bRet = (TRUE == pTime->SetTime( iYear, iMonth, iDay, iHour, iMinute, iSecond, 0L )) ? true : false;
	}
	
	return bRet;
}

__int64
CEMSCommandLineHelper::ParseBeaconID( char* szBeaconID )
{
	__int64 i64BeaconID = 0;
	
	if( szBeaconID )
	{
		sscanf( szBeaconID, "%I64x", &i64BeaconID );
	}

	return i64BeaconID;
}

bool 
CEMSCommandLineHelper::GetFileList( char* szList, char**& aszFiles, long& lNumFiles )
{
	bool bRet = true;

	aszFiles = 0;
	lNumFiles = 0;

	if( !szList || !strlen(szList) )
	{
		bRet = false;
	}

	if( bRet )
	{
		FILE* fpList = fopen( szList, "r" );

		if( fpList )
		{
			char szFileName[_MAX_PATH+1];

			char* szResult = fgets( szFileName, _MAX_PATH, fpList );

			// Read it once to get a count.
			while( szResult )
			{
				lNumFiles++;

				szResult = fgets( szFileName, _MAX_PATH, fpList );
			}

			// Now allocate the array.
			aszFiles = new char*[ lNumFiles ];

			if( aszFiles )
			{	
				fclose( fpList );
				fpList = fopen( szList, "r" );

				long lCurr = 0;
				char* szResult = fgets( szFileName, _MAX_PATH, fpList );
				while( szResult )
				{
					aszFiles[lCurr] = new char[_MAX_PATH+1];
					memset( aszFiles[lCurr], 0, _MAX_PATH+1 );

					strcpy( aszFiles[lCurr], szFileName );

					long lStrLen = strlen(aszFiles[lCurr]);
					if( '\n' == aszFiles[lCurr][lStrLen-1] )
						aszFiles[lCurr][lStrLen-1] = '\0';


					szResult = fgets( szFileName, _MAX_PATH, fpList );
					lCurr++;
				}
				
			}
			else
			{
				bRet = false;
			}

			if( fpList )
			{
				fclose( fpList );
				fpList = 0;
			}
		}
	}

	return bRet;
}