#include <windows.h>
#include <tchar.h>
#include <io.h>

#define EMS_USE_DECIMAL_FORM TRUE
// use -75.750 rather than 75 45.02 W

#include <math.h>
#include "emsinifile.h"
#include "emsconfg.h"

extern HMODULE g_hDLLModule;

const TCHAR c_szINIField[] = TEXT("inifile");

CEMSIniFile::CEMSIniFile() :
   m_lpszINIFile( 0 ),
   m_lpszComponentName( 0 )
{
}

CEMSIniFile::~CEMSIniFile()
{
   Reset();
}

void
CEMSIniFile::Reset()
{
   if ( m_lpszINIFile )
   {
	   delete [ ] m_lpszINIFile;
	   m_lpszINIFile = 0;
   }
}

EMS_RESULT
CEMSIniFile::SetIniFileName()
{
	EMS_RESULT hr = EMS_FALSE;
	CEMSRegistryConfig reg;
	TCHAR szFile[ 256 ]="";

	reg.SetComponentName( m_lpszComponentName );

	if ( reg.OpenKey( ) )
	{
		reg.QueryValue( c_szINIField, szFile, sizeof( szFile ) / sizeof( szFile[0] ) );

		reg.CloseKey( );
	}

	if ( szFile[0] == 0 )	// entry not found in the registry, so set it up
	{
		TCHAR szPath[256];

		if ( reg.FindFile( szPath, sizeof( szPath ) / sizeof( szPath[0] ),
				(HANDLE)g_hDLLModule, m_lpszINIFileName ) == EMS_OK )
		{
			wsprintf( szFile, TEXT("%s%s"), szPath, m_lpszINIFileName );

			if ( reg.CreateKey( ) )
			{
				reg.SetValue( c_szINIField, szFile );
				reg.CloseKey();
			}
		}
	}

	if ( szFile[0] )
	{
		if ( _access( szFile, 0 ) == 0 )
		{
			m_lpszINIFile = new TCHAR[ lstrlen( szFile ) + 1 ];

			if ( m_lpszINIFile )
			{
				lstrcpy( m_lpszINIFile, szFile );

				hr = EMS_OK;				
			}
		}
	}
	
	return hr;
}

BOOL
CEMSIniFile::_GetYesNo( LPCTSTR     lpcszSection,
                        LPCTSTR     lpcszLeftSide,
                        BOOL        bDefault )
{
   TCHAR szResult[256];
   DWORD dwCount = 0;

   dwCount = GetPrivateProfileString( lpcszSection, lpcszLeftSide, TEXT(""),
				   szResult, sizeof( szResult ) / sizeof( TCHAR ),	m_lpszINIFile );

   if ( dwCount && szResult[0] )
   {
	   return ( (lstrcmpi( szResult, TEXT("yes") ) == 0 ) ? TRUE : FALSE);
   }
   return bDefault;
}

void
CEMSIniFile::_GetYesNo( BOOL&    bVal, 
                        LPCTSTR  lpcszSection, 
                        LPCTSTR  lpcszLeftSide,
                        BOOL     bUseDefaultValue, 
                        BOOL     bDefaultValue )
{
   TCHAR szResult[256];
   DWORD dwCount = 0;

   dwCount = GetPrivateProfileString( lpcszSection, lpcszLeftSide, TEXT(""),
			      szResult, sizeof( szResult ) / sizeof( TCHAR ),	m_lpszINIFile );

   if ( dwCount && szResult[0] )
   {
      bVal = ((lstrcmpi( szResult, TEXT("yes") ) == 0 ) ? TRUE : FALSE);
   }
   else if ( bUseDefaultValue )
   {
      bVal = bDefaultValue;
   }
}

int
CEMSIniFile::_GetInteger(  LPCTSTR  lpcszSection,
                           LPCTSTR  lpcszLeftSide,
                           int      iDefault )
{
   TCHAR szResult[256];
   DWORD dwCount = 0;

   dwCount = GetPrivateProfileString( lpcszSection, lpcszLeftSide, TEXT(""),
				   szResult, sizeof( szResult ) / sizeof( TCHAR ),	m_lpszINIFile );

   if ( dwCount && szResult[0] )
   {
	   return ( atoi( szResult ) );
   }
   return iDefault;
}

void
CEMSIniFile::_GetInteger(  int&     iVal, 
                           LPCTSTR  lpcszSection,
                           LPCTSTR  lpcszLeftSide,
                           BOOL     bUseDefaultValue,
                           int      iDefaultValue )
{
   TCHAR szResult[256];
   DWORD dwCount = 0;

   dwCount = GetPrivateProfileString( lpcszSection, lpcszLeftSide, TEXT(""),
		         szResult, sizeof( szResult ) / sizeof( TCHAR ),	m_lpszINIFile );

   if ( dwCount && szResult[0] )
   {
      iVal = atoi( szResult );
   }
   else if ( bUseDefaultValue )
   {
      iVal = iDefaultValue;
   }
}

long
CEMSIniFile::_GetLong(	LPCTSTR lpcszSection,
						LPCTSTR lpcszLeftSide,
						long	lDefault )
{
   TCHAR szResult[256];
   DWORD dwCount = 0;

   dwCount = GetPrivateProfileString( lpcszSection, lpcszLeftSide, TEXT(""),
				   szResult, sizeof( szResult ) / sizeof( TCHAR ),	m_lpszINIFile );

   if ( dwCount && szResult[0] )
   {
	   return ( _ttol( szResult ) );
   }
   return lDefault;
}

void
CEMSIniFile::_GetLong(  long&    lVal, 
                        LPCTSTR  lpcszSection, 
                        LPCTSTR  lpcszLeftSide,
                        BOOL     bUseDefaultValue, 
                        long     lDefaultValue )
{
   TCHAR szResult[256];
   DWORD dwCount = 0;

   dwCount = GetPrivateProfileString( lpcszSection, lpcszLeftSide, TEXT(""),
			      szResult, sizeof( szResult ) / sizeof( TCHAR ),	m_lpszINIFile );

   if ( dwCount && szResult[0] )
   {
      lVal = _ttol( szResult );
   }
   else if ( bUseDefaultValue )
   {
      lVal = lDefaultValue;
   }
}

unsigned long
CEMSIniFile::_GetULong( LPCTSTR lpcszSection,
					    LPCTSTR lpcszLeftSide,
						unsigned long ulDefault )
{
   TCHAR szResult[256];
   DWORD dwCount = 0;

   dwCount = GetPrivateProfileString( lpcszSection, lpcszLeftSide, TEXT(""),
				   szResult, sizeof( szResult ) / sizeof( TCHAR ),	m_lpszINIFile );

   if ( dwCount && szResult[0] )
   {
	   TCHAR* szStop = 0;
	   return ( _tcstoul( szResult, &szStop, 10 ) );
   }
   return ulDefault;
}

void
CEMSIniFile::_GetULong( unsigned long&    ulVal, 
                        LPCTSTR           lpcszSection, 
                        LPCTSTR           lpcszLeftSide,
                        BOOL              bUseDefaultValue, 
                        unsigned long     ulDefaultValue )
{
   TCHAR szResult[256];
   DWORD dwCount = 0;

   dwCount = GetPrivateProfileString( lpcszSection, lpcszLeftSide, TEXT(""),
			      szResult, sizeof( szResult ) / sizeof( TCHAR ),	m_lpszINIFile );

   if ( dwCount && szResult[0] )
   {
      TCHAR* szStop = 0;
      ulVal = _tcstoul( szResult, &szStop, 10 );
   }
   else if ( bUseDefaultValue )
   {
      ulVal = ulDefaultValue;
   }
}

double
CEMSIniFile::_GetDouble(   LPCTSTR  lpcszSection,
                           LPCTSTR  lpcszLeftSide,
                           double   dDefault )
{
   TCHAR szResult[256];
   DWORD dwCount = 0;

   dwCount = GetPrivateProfileString( lpcszSection, lpcszLeftSide, TEXT(""),
				   szResult, sizeof( szResult ) / sizeof( TCHAR ),	m_lpszINIFile );

   if ( dwCount && szResult[0] )
   {
      return ( atof( szResult ) );
   }
   return dDefault;
}

void
CEMSIniFile::_GetDouble(   double&     dVal, 
                           LPCTSTR     lpcszSection, 
                           LPCTSTR     lpcszLeftSide,
                           BOOL        bUseDefaultValue, 
                           double      dDefaultValue )
{
   TCHAR szResult[256];
   DWORD dwCount = 0;

   dwCount = GetPrivateProfileString( lpcszSection, lpcszLeftSide, TEXT(""),
			      szResult, sizeof( szResult ) / sizeof( TCHAR ),	m_lpszINIFile );

   if ( dwCount && szResult[0] )
   {
      dVal = atof( szResult );
   }
   else if ( bUseDefaultValue )
   {
      dVal = dDefaultValue;
   }
}

float
CEMSIniFile::_GetFloat( LPCTSTR  lpcszSection,
                        LPCTSTR  lpcszLeftSide,
                        float    fDefault )
{
   TCHAR szResult[256];
   DWORD dwCount = 0;

   dwCount = GetPrivateProfileString( lpcszSection, lpcszLeftSide, TEXT(""),
				   szResult, sizeof( szResult ) / sizeof( TCHAR ),	m_lpszINIFile );

   if ( dwCount && szResult[0] )
   {
      return static_cast<float>( atof( szResult ) );
   }
   return fDefault;
}

void
CEMSIniFile::_GetFloat( float&      fVal,
                        LPCTSTR     lpcszSection, 
                        LPCTSTR     lpcszLeftSide,
                        BOOL        bUseDefaultValue, 
                        float       fDefaultValue )
{
   TCHAR szResult[256];
   DWORD dwCount = 0;

   dwCount = GetPrivateProfileString( lpcszSection, lpcszLeftSide, TEXT(""),
			      szResult, sizeof( szResult ) / sizeof( TCHAR ),	m_lpszINIFile );

   if ( dwCount && szResult[0] )
   {
      fVal = static_cast<float>( atof( szResult ) );
   }
   else if ( bUseDefaultValue )
   {
      fVal = fDefaultValue;
   }
}

INT64
CEMSIniFile::_GetINT64( LPCTSTR  lpcszSection, 
                        LPCTSTR  lpcszLeftSide,
                        INT64    i64Default )
{
   TCHAR szResult[256];
   DWORD dwCount = 0;

   dwCount = GetPrivateProfileString( lpcszSection, lpcszLeftSide, TEXT(""),
			      szResult, sizeof( szResult ) / sizeof( TCHAR ),	m_lpszINIFile );

   if ( dwCount && szResult[0] )
   {
      return ( _atoi64( szResult ) );
   }
   return i64Default;
}

void
CEMSIniFile::_GetINT64( INT64&      i64Val, 
                        LPCTSTR     lpcszSection, 
                        LPCTSTR     lpcszLeftSide,
                        BOOL        bUseDefaultValue, 
                        INT64       i64DefaultValue )
{
   TCHAR szResult[256];
   DWORD dwCount = 0;

   dwCount = GetPrivateProfileString( lpcszSection, lpcszLeftSide, TEXT(""),
		         szResult, sizeof( szResult ) / sizeof( TCHAR ),	m_lpszINIFile );

   if ( dwCount && szResult[0] )
   {
      i64Val = _atoi64( szResult );
   }
   else if ( bUseDefaultValue )
   {
      i64Val = i64DefaultValue;
   }
}

void
CEMSIniFile::_GetListDouble2( LPCTSTR     lpcszSection,     // in
                              LPCTSTR     lpcszLeftSide,    // in
                              double*     pdVal1,           // out
                              double*     pdVal2,           // out
                              LPCTSTR     lpcszDefault )    // in
{
   TCHAR szResult[256];
   DWORD dwCount = 0;

   dwCount = GetPrivateProfileString( lpcszSection, lpcszLeftSide, lpcszDefault,
			      szResult, sizeof( szResult ) / sizeof( TCHAR ),	m_lpszINIFile );

   if ( dwCount && szResult[0] )
   {
      char* pszString   = 0;
      char* pszSeps     = ",;\n";
      
      pszString = strtok( szResult, pszSeps );
      if ( pszString )
      {
         *pdVal1 = atof( pszString );

         pszString = strtok( 0, pszSeps );                                       
         if ( pszString )
         {
            *pdVal2 = atof( pszString );
         }
      }
   }
}

void
CEMSIniFile::_GetListDouble4( LPCTSTR  lpcszSection,     // in
                              LPCTSTR  lpcszLeftSide,    // in
                              double*  pdVal1,           // out
                              double*  pdVal2,           // out
                              double*  pdVal3,           // out
                              double*  pdVal4,           // out
                              LPCTSTR  lpcszDefault )    // in
{
   TCHAR szResult[256];
   DWORD dwCount = 0;

   dwCount = GetPrivateProfileString( lpcszSection, lpcszLeftSide, lpcszDefault,
			      szResult, sizeof( szResult ) / sizeof( TCHAR ),	m_lpszINIFile );

   if ( dwCount && szResult[0] )
   {
      char*    pszString   = 0;
      char*    pszSeps     = ",;\n";
      double*  pdVal[4]    = { pdVal1, pdVal2, pdVal3, pdVal4 };
      
      pszString = strtok( szResult, pszSeps );
      for ( int ii = 0; (ii < 4) && ( 0 != pszString); ii++ )
      {
         *(pdVal[ii]) = atof( pszString );

         pszString = strtok( 0, pszSeps );
      }
   }
}

void
CEMSIniFile::_GetRangeDouble( LPCTSTR  lpcszSection,     // in
                              LPCTSTR  lpcszLeftSide,    // in
                              double*  pdMinVal,         // out
                              double*  pdMaxVal,         // out
                              BOOL     bUseDefaults,     // in
                              double   dDefaultMinVal,   // in
                              double   dDefaultMaxVal )  // in
{
   TCHAR szResult[256];
   DWORD dwCount = 0;

   dwCount = GetPrivateProfileString( lpcszSection, lpcszLeftSide, TEXT(""),
			      szResult, sizeof( szResult ) / sizeof( TCHAR ),	m_lpszINIFile );

   if ( dwCount && szResult[0] )
   {
      char* pszString   = 0;
      char* pszSeps     = ":\n";
      
      pszString = strtok( szResult, pszSeps );
      if ( pszString )
      {
         *pdMinVal = atof( pszString );

         pszString = strtok( 0, pszSeps );                                       
         if ( pszString )
         {
            *pdMaxVal = atof( pszString );
         }
      }
   }
   else if ( bUseDefaults )
   {
      *pdMinVal = dDefaultMinVal;
      *pdMaxVal = dDefaultMaxVal;
   }
}

void
CEMSIniFile::_GetRangeFloat(  LPCTSTR  lpcszSection,     // in
                              LPCTSTR  lpcszLeftSide,    // in
                              float*   pdMinVal,         // out
                              float*   pdMaxVal,         // out
                              BOOL     bUseDefaults,     // in
                              float    fDefaultMinVal,   // in
                              float    fDefaultMaxVal )  // in
{
   TCHAR szResult[256];
   DWORD dwCount = 0;

   dwCount = GetPrivateProfileString( lpcszSection, lpcszLeftSide, TEXT(""),
			      szResult, sizeof( szResult ) / sizeof( TCHAR ),	m_lpszINIFile );

   if ( dwCount && szResult[0] )
   {
      char* pszString   = 0;
      char* pszSeps     = ":\n";
      
      pszString = strtok( szResult, pszSeps );
      if ( pszString )
      {
         *pdMinVal = static_cast<float>( atof( pszString ) );

         pszString = strtok( 0, pszSeps );                                       
         if ( pszString )
         {
            *pdMaxVal = static_cast<float>( atof( pszString ) );
         }
      }
   }
   else if ( bUseDefaults )
   {
      *pdMinVal = fDefaultMinVal;
      *pdMaxVal = fDefaultMaxVal;
   }
}

void
CEMSIniFile::_GetRangeInteger(   LPCTSTR  lpcszSection,     // in
                                 LPCTSTR  lpcszLeftSide,    // in
                                 int*     piMinVal,         // out
                                 int*     piMaxVal,         // out
                                 BOOL     bUseDefaults,     // in
                                 int      iDefaultMinVal,   // in
                                 int      iDefaultMaxVal )  // in
{
   TCHAR szResult[256];
   DWORD dwCount = 0;

   dwCount = GetPrivateProfileString( lpcszSection, lpcszLeftSide, TEXT(""),
			      szResult, sizeof( szResult ) / sizeof( TCHAR ),	m_lpszINIFile );

   if ( dwCount && szResult[0] )
   {
      char* pszString   = 0;
      char* pszSeps     = ":\n";
      
      pszString = strtok( szResult, pszSeps );
      if ( pszString )
      {
         *piMinVal = atoi( pszString );

         pszString = strtok( 0, pszSeps );                                       
         if ( pszString )
         {
            *piMaxVal = atoi( pszString );
         }
      }
   }
   else if ( bUseDefaults )
   {
      *piMinVal = iDefaultMinVal;
      *piMaxVal = iDefaultMaxVal;
   }
}

void
CEMSIniFile::_GetRangeByte(   LPCTSTR  lpcszSection,     // in
                              LPCTSTR  lpcszLeftSide,    // in
                              BYTE*    pbyMinVal,        // out
                              BYTE*    pbyMaxVal,        // out
                              BOOL     bUseDefaults,     // in
                              BYTE     byDefaultMinVal,  // in
                              BYTE     byDefaultMaxVal ) // in
{
   TCHAR szResult[256];
   DWORD dwCount = 0;

   dwCount = GetPrivateProfileString( lpcszSection, lpcszLeftSide, TEXT(""),
			      szResult, sizeof( szResult ) / sizeof( TCHAR ),	m_lpszINIFile );

   if ( dwCount && szResult[0] )
   {
      char* pszString   = 0;
      char* pszSeps     = ":\n";
      
      pszString = strtok( szResult, pszSeps );
      if ( pszString )
      {
         *pbyMinVal = static_cast<BYTE>( _ttoi( pszString ) );

         pszString = strtok( 0, pszSeps );                                       
         if ( pszString )
         {
			   *pbyMaxVal = static_cast<BYTE>( _ttoi( pszString ) );
         }
      }
   }
   else if ( bUseDefaults )
   {
      *pbyMinVal = byDefaultMinVal;
      *pbyMaxVal = byDefaultMaxVal;
   }
}

void
CEMSIniFile::_GetString(   LPCTSTR  lpcszSection,
                           LPCTSTR  lpcszLeftSide,
                           LPSTR    lpcszBuf,         // out: retrieved string
                           int      nBufSize,         // in: size of lpcszBuf buffer
                           LPCTSTR  lpcszDefault )    // in
{
   TCHAR szResult[256];
   DWORD dwCount = 0;

   dwCount = GetPrivateProfileString( lpcszSection, lpcszLeftSide, lpcszDefault,
				   szResult, sizeof( szResult ) / sizeof( TCHAR ),	m_lpszINIFile );

   if ( dwCount && szResult[0] )
   {
      lstrcpyn( lpcszBuf, szResult, nBufSize );
   }
   else
   {
      lstrcpyn( lpcszBuf, lpcszDefault, nBufSize );
   }
}

EMSTIME
CEMSIniFile::_GetTime(  LPCTSTR     lpcszSection, 
                        LPCTSTR     lpcszKey )
{
   // expected time format is "yy ddd hhmm ss.ssssss"

	DWORD       dwCount = 0;
	TCHAR       szResult[ 256 ];
	CEMSTime    timeTemp;

   int      nYear       = 0;
   int      nHours      = 0;
   int      nMinutes    = 0;
   double   dSeconds    = 0.0;
   double   dJulianDay  = 0.0;

	dwCount = GetPrivateProfileString( lpcszSection, lpcszKey, TEXT("0"),
		szResult, sizeof( szResult ) / sizeof( TCHAR ),	m_lpszINIFile );

	if ( dwCount && szResult[0] )
	{
		TCHAR*         lpszToken = 0;

		lpszToken = _tcstok( szResult, TEXT(" ") );        // get year

		if ( lpszToken )
		{
         nYear = atoi( lpszToken );

         nYear += ( nYear >= 80 ) ? 1900 : 2000;         // year 2080 bug

   		lpszToken = _tcstok( 0, TEXT(" ") );            // get year day (aka Julian day)

   		if ( lpszToken )
   		{
            dJulianDay = atof( lpszToken );

            timeTemp.SetTime( nYear, dJulianDay - 1 );

      		lpszToken = _tcstok( 0, TEXT(" ") );         // get hhmm

      		if ( lpszToken )
            {
               nHours    =  (lpszToken[0] - '0') * 10;   // get h___
               nHours   +=  (lpszToken[1] - '0');        // get _h__
               timeTemp.AddHours( nHours );

               nMinutes  =  (lpszToken[2] - '0') * 10;   // get __m_
               nMinutes +=  (lpszToken[3] - '0');        // get ___m
               timeTemp.AddMinutes( nMinutes );

         		lpszToken = _tcstok( 0, TEXT(" ") );      // get ss.ssssss

         		if ( lpszToken )
               {
                  dSeconds = atof( lpszToken );
                  timeTemp.AddSeconds( dSeconds );
               }
            }
         }
		}
	}
	return timeTemp;
}

EMSTIMEFIELDS
CEMSIniFile::_GetTimeOfDay(   LPCTSTR     lpcszSection, 
                              LPCTSTR     lpcszKey )
{
	DWORD          dwCount = 0;
	TCHAR          szResult[ 256 ];
   EMSTIMEFIELDS  timeTemp;

   memset( &timeTemp, 0, sizeof(timeTemp) );

	dwCount = GetPrivateProfileString( lpcszSection, lpcszKey, TEXT(""),
		szResult, sizeof( szResult ) / sizeof( TCHAR ),	m_lpszINIFile );

	if ( dwCount && szResult[0] )
	{
      char* pszString   = 0;
      char* pszSeps     = ":\n";

      pszString = strtok( szResult, pszSeps );

      if ( pszString )
      {
         timeTemp.nHour = atoi( pszString );

         pszString = strtok( 0, pszSeps );
         if ( pszString )
         {
            timeTemp.nMinute = atoi( pszString );

            pszString = strtok( 0, pszSeps );
            if ( pszString )
            {
               timeTemp.nSecond = atoi( pszString );
            }
         }
      }
   }
	return timeTemp;
}

LPCTSTR
CEMSIniFile::_GetTextMonth( int nMonth )
{
	switch ( nMonth )
	{
		case 1: return TEXT("JAN"); break;
		case 2: return TEXT("FEB"); break;
		case 3: return TEXT("MAR"); break;
		case 4: return TEXT("APR"); break;
		case 5: return TEXT("MAY"); break;
		case 6: return TEXT("JUN"); break;
		case 7: return TEXT("JUL"); break;
		case 8: return TEXT("AUG"); break;
		case 9: return TEXT("SEP"); break;
		case 10: return TEXT("OCT"); break;
		case 11: return TEXT("NOV"); break;
		case 12: return TEXT("DEC"); break;
		default:	return 0;				break;
	}
}

EMSDEGREES
CEMSIniFile::_GetDegrees(  const LPCTSTR  lpcszSection, 
                           const LPCTSTR  lpcszLeftSide,
                           const LPCTSTR  lpcszDefault )
{
   TCHAR szResult[256];
   DWORD dwCount = 0;

   dwCount = GetPrivateProfileString( lpcszSection, lpcszLeftSide, lpcszDefault,
			      szResult, sizeof( szResult ) / sizeof( TCHAR ),	m_lpszINIFile );

   if ( dwCount && szResult[0] )
   {
      return _ConvertToDegrees( szResult );

   }
   return 0;
}

BYTE
CEMSIniFile::_GetByte(  LPCTSTR  lpcszSection,
                        LPCTSTR  lpcszLeftSide,
                        BYTE     byDefault )
{
	long byRet = byDefault;

   TCHAR szResult[256];
   DWORD dwCount = 0;

   dwCount = GetPrivateProfileString( lpcszSection, lpcszLeftSide, TEXT(""),
				   szResult, sizeof( szResult ) / sizeof( TCHAR ),	m_lpszINIFile );

   if ( dwCount && szResult[0] )
   {
	   byRet = atol( szResult );
   }
   return static_cast<BYTE>( byRet );
}

void
CEMSIniFile::_GetByte(  BYTE&       byVal,
                        LPCTSTR     lpcszSection, 
                        LPCTSTR     lpcszLeftSide,
                        BOOL        bUseDefaultValue, 
                        BYTE        byDefaultValue )
{
   TCHAR szResult[256];
   DWORD dwCount = 0;

   dwCount = GetPrivateProfileString( lpcszSection, lpcszLeftSide, TEXT(""),
			      szResult, sizeof( szResult ) / sizeof( TCHAR ),	m_lpszINIFile );

   if ( dwCount && szResult[0] )
   {
      byVal = static_cast<BYTE>( atol( szResult ) );
   }
   else if ( bUseDefaultValue )
   {
      byVal = byDefaultValue;
   }
}

EMSDEGREES
CEMSIniFile::_ConvertToDegrees( LPCTSTR lpcszValue )
{
	EMSDEGREES degrees = 0.0;

#ifdef EMS_USE_DECIMAL_FORM

	degrees = atof( lpcszValue );

#elif
	TCHAR szTemp[64], *lpszToken=0;
	int nCount = 0;

	lstrcpyn( szTemp, lpcszValue, sizeof( szTemp ) / sizeof( TCHAR ) );
	
	lpszToken = _tcstok( szTemp , TEXT(" ") );

	while ( lpszToken )
	{
		switch ( nCount++ )
		{
			case 0: // Degrees
				degrees = atof( lpszToken );
				break;

			case 1: // Minutes
				degrees += atof( lpszToken ) / 60.0;
				break;

			case 2: // NESW
				switch ( _totupper( *lpszToken ) )
				{
					case 'S':
					case 'W':
						degrees = -degrees;
						break;

					case 'N':
					case 'E':
						break;
				}
				break;
		}
		lpszToken = _tcstok( 0 , TEXT(" ") );
	}

#endif

	return degrees;
}

DWORD
CEMSIniFile::_HexStringToDWORD( LPCTSTR  pszHexString )
{
   DWORD dwHexVal = 0;
   if ( pszHexString )
   {
      LPCTSTR  szHexDigit = pszHexString + (strlen( pszHexString ) - 1 );
      bool     bDone = false;

      for ( int ii = 0; !bDone; ii++, szHexDigit-- )
      {
         switch ( *szHexDigit )
         {
         case '0': break;
         case '1': dwHexVal += (0x01 * (DWORD)pow( 16 , ii ) ); break;
         case '2': dwHexVal += (0x02 * (DWORD)pow( 16 , ii ) ); break;
         case '3': dwHexVal += (0x03 * (DWORD)pow( 16 , ii ) ); break;
         case '4': dwHexVal += (0x04 * (DWORD)pow( 16 , ii ) ); break;
         case '5': dwHexVal += (0x05 * (DWORD)pow( 16 , ii ) ); break;
         case '6': dwHexVal += (0x06 * (DWORD)pow( 16 , ii ) ); break;
         case '7': dwHexVal += (0x07 * (DWORD)pow( 16 , ii ) ); break;
         case '8': dwHexVal += (0x08 * (DWORD)pow( 16 , ii ) ); break;
         case '9': dwHexVal += (0x09 * (DWORD)pow( 16 , ii ) ); break;
         case 'A':
         case 'a': dwHexVal += (0x0a * (DWORD)pow( 16, ii ) ); break;
         case 'B':
         case 'b': dwHexVal += (0x0b * (DWORD)pow( 16, ii ) ); break;
         case 'C':
         case 'c': dwHexVal += (0x0c * (DWORD)pow( 16, ii ) ); break;
         case 'D':
         case 'd': dwHexVal += (0x0d * (DWORD)pow( 16, ii ) ); break;
         case 'E':
         case 'e': dwHexVal += (0x0e * (DWORD)pow( 16, ii ) ); break;
         case 'F':
         case 'f': dwHexVal += (0x0f * (DWORD)pow( 16, ii ) ); break;
         default:  bDone = true; break;
         }
         if ( pszHexString == szHexDigit )
         {
            bDone = true;
         }
      }
   }
   return dwHexVal;
}

