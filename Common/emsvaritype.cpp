#include <emsvaritype.h>
#include <emstime.h>
#include <wchar.h>

/*
#define  CASTVARITYPE( type )                                                          \
{                                                                                      \
   switch ( dataType )                                                                 \
   {                                                                                   \
   case EMSVARITYPE_DATATYPE_BOOL         :     return static_cast<type>( bVal );      \
   case EMSVARITYPE_DATATYPE_STRING       :     return static_cast<type>( pwcsVal );   \
   case EMSVARITYPE_DATATYPE_TIME         :     return static_cast<type>( tmVal );     \
   case EMSVARITYPE_DATATYPE_BIGINT       :     return static_cast<type>( i64Val );    \
   case EMSVARITYPE_DATATYPE_INT          :     return static_cast<type>( iVal );      \
   case EMSVARITYPE_DATATYPE_INTRANGE     :     return static_cast<type>( iVal );      \
   case EMSVARITYPE_DATATYPE_UINT         :     return static_cast<type>( uiVal );     \
   case EMSVARITYPE_DATATYPE_UINTRANGE    :     return static_cast<type>( uiVal );     \
   case EMSVARITYPE_DATATYPE_DOUBLE       :     return static_cast<type>( dVal );      \
   case EMSVARITYPE_DATATYPE_DOUBLERANGE  :     return static_cast<type>( dVal );      \
   case EMSVARITYPE_DATATYPE_FLOAT        :     return static_cast<type>( fVal );      \
   case EMSVARITYPE_DATATYPE_FLOATRANGE   :     return static_cast<type>( fVal );      \
   default:                                                                            \
      break;                                                                           \
   }                                                                                   \
}
*/

#define  CASTVARITYPE( type )                                                       \
{                                                                                   \
   switch ( dataType )                                                              \
   {                                                                                \
   case EMSVARITYPE_DATATYPE_BOOL         :  return static_cast<type>( bVal );      \
   case EMSVARITYPE_DATATYPE_BIGINT       :  return static_cast<type>( i64Val );    \
   case EMSVARITYPE_DATATYPE_TIME         :  return static_cast<type>( tmVal.intTime ); \
   case EMSVARITYPE_DATATYPE_INT          :  return static_cast<type>( iVal );      \
   case EMSVARITYPE_DATATYPE_INTRANGE     :  return static_cast<type>( iVal );      \
   case EMSVARITYPE_DATATYPE_UINT         :  return static_cast<type>( uiVal );     \
   case EMSVARITYPE_DATATYPE_UINTRANGE    :  return static_cast<type>( uiVal );     \
   case EMSVARITYPE_DATATYPE_DOUBLE       :  return static_cast<type>( dVal );      \
   case EMSVARITYPE_DATATYPE_DOUBLERANGE  :  return static_cast<type>( dVal );      \
   case EMSVARITYPE_DATATYPE_FLOAT        :  return static_cast<type>( fVal );      \
   case EMSVARITYPE_DATATYPE_FLOATRANGE   :  return static_cast<type>( fVal );      \
   default                                :  return static_cast<type>( 0 );         \
   }                                                                                \
}

_emsvaritype_t::_emsvaritype_t()
{
   memset( this, 0, sizeof(*this) );
   dataType = EMSVARITYPE_DATATYPE_UNINITIALIZED;
}

_emsvaritype_t::_emsvaritype_t( const EMSVARITYPE& varSrc )
{
   memset( this, 0, sizeof(*this) );
   dataType = EMSVARITYPE_DATATYPE_UNINITIALIZED;
   *this = varSrc;
}

_emsvaritype_t::_emsvaritype_t( const EMSVARITYPE* pSrc )
{
   memset( this, 0, sizeof(*this) );
   dataType = EMSVARITYPE_DATATYPE_UNINITIALIZED;
   if ( pSrc )
   {
      *this = pSrc;
   }
}

_emsvaritype_t::_emsvaritype_t( const _emsvaritype_t& varSrc )
{
   memset( this, 0, sizeof(*this) );
   dataType = EMSVARITYPE_DATATYPE_UNINITIALIZED;
   *this = varSrc;
}

_emsvaritype_t::_emsvaritype_t(  EMSVARITYPE&   varSrc, 
                                 bool           fCopy )
{
   memset( this, 0, sizeof(*this) );
   dataType = EMSVARITYPE_DATATYPE_UNINITIALIZED;

   if ( fCopy )
   {
      *this = varSrc;
   }
   else
   {
      Attach( varSrc );
   }
}

_emsvaritype_t::_emsvaritype_t( bool bSrc )
{
   dataType = EMSVARITYPE_DATATYPE_BOOL;
   bVal     = bSrc ? TRUE : FALSE;
}

_emsvaritype_t::_emsvaritype_t( const wchar_t* pSrc )
{
   if ( pSrc )
   {
      dataType = EMSVARITYPE_DATATYPE_STRING;

      pwcsVal = new wchar_t[wcslen(pSrc) + 1];
      wcscpy( pwcsVal, pSrc );
   }
}

_emsvaritype_t::_emsvaritype_t( const char* pSrc )
{
   if ( pSrc )
   {
      dataType = EMSVARITYPE_DATATYPE_STRING;

      pwcsVal = new wchar_t[strlen(pSrc) + 1];
      mbstowcs( pwcsVal, pSrc, strlen( pSrc ) + 1 );
   }
}

_emsvaritype_t::_emsvaritype_t( const EMSTIME &tmSrc )
{
   dataType = EMSVARITYPE_DATATYPE_TIME;
   tmVal    = tmSrc;
}

/*
if ( EMSVARITYPE_DATATYPE_STRING == vtSrc )
{
   dataType = EMSVARITYPE_DATATYPE_STRING;

   short len   = wcslen(L"yy ddd hhmm ss.sssssss");
   pwcsVal     = new wchar_t[len + 1];

   CEMSTime       timeTemp( tmSrc );
   EMSTIMEFIELDS  timeFields;
   double         dSeconds = 0.0;

   timeTemp.GetTime( &timeFields );

   dSeconds = (double)timeFields.nSecond;

   dSeconds += ( (double)timeFields.lNanosecond / 1000000000.0 );

   _snwprintf( pwcsVal, len, L"%02i %03i %02i%02i %09.6lf",
      (timeFields.nYear - 2000), timeFields.nJulianDay,
      timeFields.nHour, timeFields.nMinute, dSeconds );
}
*/

_emsvaritype_t::_emsvaritype_t( const INT64 &i64Src )
{
   dataType = EMSVARITYPE_DATATYPE_BIGINT;
   i64Val   = i64Src;
}

/*
if ( EMSVARITYPE_DATATYPE_STRING == vtSrc )
{
   dataType = EMSVARITYPE_DATATYPE_STRING;

   short len   = wcslen(L"-9,223,372,036,854,775,808");    // max number length
   pwcsVal     = new wchar_t[len + 1];

   _snwprintf( pwcsVal, len, L"%I64i", i64Src );
}
*/

_emsvaritype_t::_emsvaritype_t(  int                     iSrc,
                                 EMSVARITYPE_DATATYPE    vtSrc )
{
   if ( EMSVARITYPE_DATATYPE_BOOL == vtSrc )
   {
      dataType = EMSVARITYPE_DATATYPE_BOOL;
      bVal     = (( 0 == iSrc ) ? FALSE : TRUE);
   }
   else
   {
      dataType = EMSVARITYPE_DATATYPE_INT;
      iVal     = iSrc;
   }
}

/*
if ( EMSVARITYPE_DATATYPE_STRING == vtSrc )
{
   dataType = EMSVARITYPE_DATATYPE_STRING;

   short len   = wcslen(L"-2,147,483,648");    // max number length
   pwcsVal     = new wchar_t[len + 1];

   _snwprintf( pwcsVal, len, L"%i", i64Src );
}
*/

_emsvaritype_t::_emsvaritype_t(  unsigned int            uiSrc,
                                 EMSVARITYPE_DATATYPE    vtSrc )
{
   if ( EMSVARITYPE_DATATYPE_BOOL == vtSrc )
   {
      dataType = EMSVARITYPE_DATATYPE_BOOL;
      bVal     = (( 0 == uiSrc ) ? FALSE : TRUE);
   }
   else
   {
      dataType = EMSVARITYPE_DATATYPE_UINT;
      uiVal    = uiSrc;
   }
}

_emsvaritype_t::_emsvaritype_t( float fltSrc )
{
   dataType = EMSVARITYPE_DATATYPE_FLOAT;
   fVal     = fltSrc;
}

_emsvaritype_t::_emsvaritype_t( double dblSrc )
{
   dataType = EMSVARITYPE_DATATYPE_DOUBLE;
   dVal     = dblSrc;
}

_emsvaritype_t::_emsvaritype_t(  short                   sSrc,
                                 EMSVARITYPE_DATATYPE    vtSrc )
{
   if ( EMSVARITYPE_DATATYPE_BOOL == vtSrc )
   {
      dataType = EMSVARITYPE_DATATYPE_BOOL;
      bVal     = (( 0 == sSrc ) ? FALSE : TRUE);
   }
   else
   {
      dataType = EMSVARITYPE_DATATYPE_INT;
      iVal     = sSrc;
   }
}

_emsvaritype_t::_emsvaritype_t(  unsigned short          sSrc,
                                 EMSVARITYPE_DATATYPE    vtSrc )
{
   if ( EMSVARITYPE_DATATYPE_BOOL == vtSrc )
   {
      dataType = EMSVARITYPE_DATATYPE_BOOL;
      bVal     = (( 0 == sSrc ) ? FALSE : TRUE);
   }
   else
   {
      dataType = EMSVARITYPE_DATATYPE_UINT;
      uiVal     = sSrc;
   }
}

_emsvaritype_t::_emsvaritype_t(  long                    lSrc,
                                 EMSVARITYPE_DATATYPE    vtSrc )
{
   if ( EMSVARITYPE_DATATYPE_BOOL == vtSrc )
   {
      dataType = EMSVARITYPE_DATATYPE_BOOL;
      bVal     = (( 0 == lSrc ) ? FALSE : TRUE);
   }
   else
   {
      dataType = EMSVARITYPE_DATATYPE_INT;
      iVal     = lSrc;
   }
}

_emsvaritype_t::_emsvaritype_t(  unsigned long           lSrc,
                                 EMSVARITYPE_DATATYPE    vtSrc )
{
   if ( EMSVARITYPE_DATATYPE_BOOL == vtSrc )
   {
      dataType = EMSVARITYPE_DATATYPE_BOOL;
      bVal     = (( 0 == lSrc ) ? FALSE : TRUE);
   }
   else
   {
      dataType = EMSVARITYPE_DATATYPE_UINT;
      uiVal     = lSrc;
   }
}

_emsvaritype_t::_emsvaritype_t(  BYTE                    bSrc,
                                 EMSVARITYPE_DATATYPE    vtSrc )
{
   if ( EMSVARITYPE_DATATYPE_BOOL == vtSrc )
   {
      dataType = EMSVARITYPE_DATATYPE_BOOL;
      bVal     = (( 0 == bSrc ) ? FALSE : TRUE);
   }
   else
   {
     dataType = EMSVARITYPE_DATATYPE_INT;
     iVal     = bSrc;
   }
}

// Destructor
//

_emsvaritype_t::~_emsvaritype_t()
{
   Clear();
}

// Extractors
//

_emsvaritype_t::operator EMSTIME() const
{
   if (  ( EMSVARITYPE_DATATYPE_TIME == dataType )
      && pwcsVal
      )
   {
      return tmVal;
   }
   else
   {
      EMSTIME tmTemp;
      memset( &tmTemp, 0, sizeof(tmTemp) );

      if ( EMSVARITYPE_DATATYPE_STRING == dataType )
      {
         if ( pwcsVal )
         {
            CEMSTime       timeTemp;
            int            nYear       = 0;
            double         dJulianDay  = 0.0;
            int            nHours      = 0;
            int            nMinutes    = 0;
            double         dSeconds    = 0.0;

            wchar_t* pwcsValueCopy  = new wchar_t[wcslen(pwcsVal) + 1];
            wchar_t* pwcsToken      = 0;

            wcscpy( pwcsValueCopy, pwcsVal );

            pwcsToken = wcstok( pwcsValueCopy, L" " );

            // expected input: "yy ddd hhmm ss.sssssss"
            if ( pwcsToken )
            {
               nYear = _wtoi( pwcsToken );

               nYear += ( nYear >= 80 ) ? 1900 : 2000;   // year 2080 bug

               pwcsToken = wcstok( 0, L" " );      // get year day (aka Julian day)

               if ( pwcsToken )
               {
                  dJulianDay = wcstod( pwcsToken, 0 );

                  timeTemp.SetTime( nYear, dJulianDay - 1 );

                  pwcsToken = wcstok( 0, L" " );                        // get hhmm

                  if (  pwcsToken
                     && ( wcslen( pwcsToken ) == 4 )
                     )
                  {
                     if (  iswdigit( pwcsToken[0] )
                        && iswdigit( pwcsToken[1] )
                        && iswdigit( pwcsToken[2] )
                        && iswdigit( pwcsToken[3] )
                        )
                     {
                        nHours =  (pwcsToken[0] - L'0') * 10;     // get h___
                        nHours += (pwcsToken[1] - L'0');       // get _h__
                        timeTemp.AddHours( nHours );

                        nMinutes =  (pwcsToken[2] - L'0') * 10;  // get __m_
                        nMinutes += (pwcsToken[3] - L'0');       // get ___m
                        timeTemp.AddMinutes( nMinutes );
                     }

                     pwcsToken = wcstok( 0, L" " );                     // get ss.ssssss

                     if ( pwcsToken )
                     {
                        dSeconds = wcstod( pwcsToken, 0 );
                        timeTemp.AddSeconds( dSeconds );
                     }
                  }
               }
            }
            delete[] pwcsValueCopy;
            tmTemp = timeTemp;
         }
      }
      return tmTemp;
   }
}

_emsvaritype_t::operator INT64() const
{
   if (  ( EMSVARITYPE_DATATYPE_STRING == dataType )
      && pwcsVal
      )
   {
/*
      INT64 i64TempVal  = 0;
      short clen        = wcslen( pwcsVal ) - 1;
      short shift       = 0;

      while ( ( clen >= 0 ) && iswxdigit( pwcsVal[clen] ) )
      {
         i64TempVal += 
      }
*/
      return _wtoi64( pwcsVal );
   }
   else
   {
      CASTVARITYPE( INT64 );
   }
}

_emsvaritype_t::operator int() const
{
   if (  ( EMSVARITYPE_DATATYPE_STRING == dataType )
      && pwcsVal
      )
   {
      return  wcstol( pwcsVal, 0, 0 );
   }
   else
   {
      CASTVARITYPE( int );
   }
}

_emsvaritype_t::operator unsigned int() const
{
   if (  ( EMSVARITYPE_DATATYPE_STRING == dataType )
      && pwcsVal
      )
   {
      return wcstoul( pwcsVal, 0, 0 );
   }
   else
   {
      CASTVARITYPE( unsigned int );
   }
}

_emsvaritype_t::operator float() const
{
   if (  ( EMSVARITYPE_DATATYPE_STRING == dataType )
      && pwcsVal
      )
   {
      return static_cast<float>( wcstod( pwcsVal, 0 ) );
   }
   else
   {
      CASTVARITYPE( float );
   }
}

_emsvaritype_t::operator double() const
{
   if (  ( EMSVARITYPE_DATATYPE_STRING == dataType )
      && pwcsVal
      )
   {
      return wcstod( pwcsVal, 0 );
   }
   else
   {
      CASTVARITYPE( double );
   }
}

_emsvaritype_t::operator const wchar_t*() const
{
   if ( EMSVARITYPE_DATATYPE_STRING == dataType )
   {
      if ( pwcsVal )
      {
/*
         wchar_t* pwcsTemp = new wchar_t[wcslen(pwcsVal) + 1];
         wcscpy( pwcsTemp, pwcsVal );
         return pwcsTemp;
*/
         return pwcsVal;
      }
      else
      {
         return 0;
      }
   }
   return 0;
}

_emsvaritype_t::operator wchar_t*() const
{
   if ( EMSVARITYPE_DATATYPE_STRING == dataType )
   {
      if ( pwcsVal )
      {
         wchar_t* pwcsTemp = new wchar_t[wcslen(pwcsVal) + 1];
         wcscpy( pwcsTemp, pwcsVal );
         return pwcsTemp;
      }
      else
      {
         return 0;
      }
   }
   return 0;
}

_emsvaritype_t::operator const char*() const
{
#pragma message("!!!!!!!!!!!!!!!!!!!!!!!!!!!_emsvaritype_t::operator const char*() return mem? !!!!!!!!!!!!!!!!!!!!!!!")
   if ( EMSVARITYPE_DATATYPE_STRING == dataType )
   {
      if ( pwcsVal )
      {
         char* pszTemp = new char[wcslen(pwcsVal) + 1];
         wcstombs( pszTemp, pwcsVal, wcslen(pwcsVal) + 1 );
         return pszTemp;
      }
      else
      {
         return 0;
      }
   }
   return 0;
}

_emsvaritype_t::operator bool() const
{
   if ( EMSVARITYPE_DATATYPE_STRING == dataType )
   {
      return ( 0 != pwcsVal );
   }
   else
   {
//    CASTVARITYPE( bool );
      return ( 0 != static_cast<unsigned int>( *this ) );
   }
}

_emsvaritype_t::operator short() const
{
   CASTVARITYPE( short );
}

_emsvaritype_t::operator unsigned short() const
{
   return static_cast<unsigned int>( *this );
}


_emsvaritype_t::operator long() const
{
   CASTVARITYPE( long );
}

_emsvaritype_t::operator unsigned long() const
{
   return static_cast<unsigned int>( *this );
}

_emsvaritype_t::operator BYTE() const
{
   CASTVARITYPE( BYTE );
}

// Assignment operations
//

_emsvaritype_t&
_emsvaritype_t::operator=( const EMSVARITYPE& varSrc )
{
   Clear();

   if ( EMSVARITYPE_DATATYPE_STRING == varSrc.dataType )
   {
      if ( varSrc.pwcsVal )
      {
         pwcsVal = new wchar_t[wcslen(varSrc.pwcsVal) + 1];
         wcscpy( pwcsVal, varSrc.pwcsVal );
         dataType = EMSVARITYPE_DATATYPE_STRING;
      }
   }
   else
   {
      memcpy( this, &varSrc, sizeof(*this) );
   }
   return *this;
}

_emsvaritype_t&
_emsvaritype_t::operator=( const EMSVARITYPE* pSrc )
{
   if ( pSrc )
   {
      return (*this = *pSrc);
   }
   Clear();
   return *this;
}

_emsvaritype_t&
_emsvaritype_t::operator=( const _emsvaritype_t& varSrc )
{
   Clear();

   if ( EMSVARITYPE_DATATYPE_STRING == varSrc.dataType )
   {
      if ( varSrc.pwcsVal )
      {
         pwcsVal = new wchar_t[wcslen(varSrc.pwcsVal) + 1];
		 if( pwcsVal )
		 {
			 wcscpy( pwcsVal, varSrc.pwcsVal );
			 dataType = EMSVARITYPE_DATATYPE_STRING;
		 }
      }
   }
   else
   {
      memcpy( this, &varSrc, sizeof(*this) );
   }
   return *this;
}

_emsvaritype_t&
_emsvaritype_t::operator=( EMSTIME tmSrc )
{
   Clear();

   dataType = EMSVARITYPE_DATATYPE_TIME;
   tmVal    = tmSrc;

   return *this;
}

_emsvaritype_t&
_emsvaritype_t::operator=( INT64 i64Src )
{
   Clear();

   dataType = EMSVARITYPE_DATATYPE_BIGINT;
   i64Val   = i64Src;

   return *this;
}

_emsvaritype_t&
_emsvaritype_t::operator=( int iSrc )
{
   Clear();

   dataType = EMSVARITYPE_DATATYPE_INT;
   iVal     = iSrc;

   return *this;
}

_emsvaritype_t&
_emsvaritype_t::operator=( unsigned int uiSrc )
{
   Clear();

   dataType = EMSVARITYPE_DATATYPE_UINT;
   uiVal    = uiSrc;

   return *this;
}

_emsvaritype_t&
_emsvaritype_t::operator=( short sSrc )
{
   Clear();

   dataType = EMSVARITYPE_DATATYPE_INT;
   iVal     = sSrc;

   return *this;
}

_emsvaritype_t&
_emsvaritype_t::operator=( unsigned short sSrc )
{
   Clear();

   dataType = EMSVARITYPE_DATATYPE_UINT;
   uiVal    = sSrc;

   return *this;
}

_emsvaritype_t&
_emsvaritype_t::operator=( long lSrc )
{
   Clear();

   dataType = EMSVARITYPE_DATATYPE_INT;
   iVal     = lSrc;

   return *this;
}

_emsvaritype_t&
_emsvaritype_t::operator=( unsigned long lSrc )
{
   Clear();

   dataType = EMSVARITYPE_DATATYPE_UINT;
   uiVal    = lSrc;

   return *this;
}

_emsvaritype_t&
_emsvaritype_t::operator=( float fltSrc )
{
   Clear();

   dataType = EMSVARITYPE_DATATYPE_FLOAT;
   fVal     = fltSrc;

   return *this;
}

_emsvaritype_t&
_emsvaritype_t::operator=( double dblSrc )
{
   Clear();

   dataType = EMSVARITYPE_DATATYPE_DOUBLE;
   dVal     = dblSrc;

   return *this;
}

_emsvaritype_t&
_emsvaritype_t::operator=( const wchar_t* pSrc )
{
   Clear();

   if ( pSrc )
   {
      dataType = EMSVARITYPE_DATATYPE_STRING;

      pwcsVal = new wchar_t[wcslen( pSrc ) + 1];
      wcscpy( pwcsVal, pSrc );
   }
   return *this;
}

_emsvaritype_t&
_emsvaritype_t::operator=( const char* pSrc )
{
   Clear();

   if ( pSrc )
   {
      dataType = EMSVARITYPE_DATATYPE_STRING;

      pwcsVal = new wchar_t[strlen( pSrc ) + 1];
      mbstowcs( pwcsVal, pSrc, strlen( pSrc ) + 1 );
   }
   return *this;
}

_emsvaritype_t&
_emsvaritype_t::operator=( bool bSrc )
{
   Clear();

   dataType = EMSVARITYPE_DATATYPE_BOOL;
   bVal     = bSrc ? TRUE : FALSE;

   return *this;
}

_emsvaritype_t&
_emsvaritype_t::operator=( BYTE bSrc )
{
   Clear();

   dataType = EMSVARITYPE_DATATYPE_INT;
   iVal     = bSrc;

   return *this;
}

// Comparison operations
//

bool
_emsvaritype_t::operator==( const EMSVARITYPE& varSrc ) const
{
   if ( dataType == varSrc.dataType )
   {
      if ( EMSVARITYPE_DATATYPE_STRING == varSrc.dataType )
      {
         if ( varSrc.pwcsVal )
         {
            return ( 0 == wcscmp( varSrc.pwcsVal, pwcsVal ) );
         }
      }
      else
      {
         return ( 0 == memcmp( this, &varSrc, sizeof(*this) ) );
      }
   }
   return false;
}

bool
_emsvaritype_t::operator==( const EMSVARITYPE* pSrc ) const
{
   if ( pSrc )
   {
      return *this == *pSrc;
   }
   return false;
}

bool
_emsvaritype_t::operator!=( const EMSVARITYPE& varSrc ) const
{
   return !(*this == varSrc);
}

bool
_emsvaritype_t::operator!=( const EMSVARITYPE* pSrc ) const
{
   if ( pSrc )
   {
      return !(*this == *pSrc);
   }
   return false;
}

// Low-level operations
//

void
_emsvaritype_t::Clear()
{
   if (  ( EMSVARITYPE_DATATYPE_STRING == dataType )
      && pwcsVal
      )
   {
      delete [] pwcsVal;
      pwcsVal = 0;
   }
   memset( this, 0, sizeof(*this) );

   dataType = EMSVARITYPE_DATATYPE_UNINITIALIZED;
}

void 
_emsvaritype_t::Attach( EMSVARITYPE& varSrc )
{
#pragma message("!!!!!!!!!!!!!!!!!!!!!!!Attach not supported yet!!!!!!!!!!!!!!")
}

EMSVARITYPE
_emsvaritype_t::Detach()
{
   EMSVARITYPE varTemp = *this;
   return varTemp;
}

void
_emsvaritype_t::ChangeType(         EMSVARITYPE_DATATYPE    vartype, 
                              const _emsvaritype_t*         pSrc )
{
}

void
_emsvaritype_t::SetString( const char* pSrc )
{
}

void
_emsvaritype_t::SetString( const wchar_t* pSrc )
{
}

