#include "emserror.h"
#include "emstime.h"
//#include "emstypes.h"

class CEMSIniFile
{
public:
   CEMSIniFile();
   ~CEMSIniFile();
   void Reset();

   EMS_RESULT  SetIniFileName( void );
	LPCTSTR     GetINIFileName( void ) { return (LPCTSTR)m_lpszINIFile; }

protected:
	EMSTIME  _GetTime( LPCTSTR lpcszSection, LPCTSTR lpcszKey );
//   void     _GetTime( EMSTIME&, LPCTSTR lpcszSection, LPCTSTR lpcszKey );

	LPCTSTR  _GetTextMonth( int nMonth );

	EMSTIMEFIELDS  _GetTimeOfDay( LPCTSTR lpcszSection, LPCTSTR lpcszKey );
//   void           _GetTimeOfDay( EMSTIMEFIELDS&, LPCTSTR lpcszSection, LPCTSTR lpcszKey );

   BOOL     _GetYesNo( LPCTSTR, LPCTSTR, BOOL = FALSE );
   void     _GetYesNo( BOOL&, LPCTSTR, LPCTSTR, BOOL = FALSE , BOOL = FALSE );

   int      _GetInteger( LPCTSTR, LPCTSTR, int = 0 );
   void     _GetInteger( int&, LPCTSTR, LPCTSTR, BOOL = FALSE, int = 0 );

   long		_GetLong( LPCTSTR, LPCTSTR, long = 0 );
   void     _GetLong( long&, LPCTSTR, LPCTSTR, BOOL=FALSE, long = 0 );

   unsigned long	_GetULong( LPCTSTR,	LPCTSTR, unsigned long = 0);
   void           _GetULong( unsigned long&, LPCTSTR, LPCTSTR, BOOL=FALSE, unsigned long = 0);
   
   double   _GetDouble( LPCTSTR, LPCTSTR, double = 0 );
   void     _GetDouble( double&, LPCTSTR, LPCTSTR, BOOL=FALSE, double = 0 );
   
   float    _GetFloat( LPCTSTR, LPCTSTR, float = 0 );
   void     _GetFloat( float&, LPCTSTR, LPCTSTR, BOOL=FALSE, float = 0 );
   
   INT64    _GetINT64( LPCTSTR, LPCTSTR, INT64 = 0 );
   void     _GetINT64( INT64&, LPCTSTR, LPCTSTR, BOOL=FALSE, INT64 = 0 );
   
   void     _GetListDouble2(  LPCTSTR  lpcszSection,     // in
                              LPCTSTR  lpcszLeftSide,    // in
                              double*  pdVal1,           // out
                              double*  pdVal2,           // out
                              LPCTSTR  lpcszDefault = "" );   // in

   void _GetListDouble4(   LPCTSTR  lpcszSection,     // in
                           LPCTSTR  lpcszLeftSide,    // in
                           double*  pdVal1,           // out
                           double*  pdVal2,           // out
                           double*  pdVal3,           // out
                           double*  pdVal4,           // out
                           LPCTSTR  lpcszDefault = "" );   // in

   void _GetRangeDouble(   LPCTSTR  lpcszSection,           // in
                           LPCTSTR  lpcszLeftSide,          // in
                           double*  pdMinVal,               // out
                           double*  pdMaxVal,               // out
                           BOOL     bUseDefaults = FALSE,    // in
                           double   dDefaultMinVal = 0,     // in
                           double   dDefaultMaxVal = 0 );   // in

   void _GetRangeFloat( LPCTSTR  lpcszSection,           // in
                        LPCTSTR  lpcszLeftSide,          // in
                        float*   pfMinVal,               // out
                        float*   pfMaxVal,               // out
                        BOOL     bUseDefaults = FALSE,   // in
                        float    fDefaultMinVal = 0,     // in
                        float    fDefaultMaxVal = 0 );   // in

   void _GetRangeInteger(  LPCTSTR  lpcszSection,           // in
                           LPCTSTR  lpcszLeftSide,          // in
                           int*     piMinVal,               // out
                           int*     piMaxVal,               // out
                           BOOL     bUseDefaults = FALSE,   // in
                           int      iDefaultMinVal = 0,     // in
                           int      iDefaultMaxVal = 0 );   // in

   void _GetRangeByte(	LPCTSTR  lpcszSection,           // in
                        LPCTSTR  lpcszLeftSide,          // in
                        BYTE*    pbyMinVal,              // out
                        BYTE*    pbyMaxVal,              // out
                        BOOL     bUseDefaults = FALSE,   // in
                        BYTE     byDefaultMinVal = 0,    // in
                        BYTE     byDefaultMaxVal = 0 );  // in

   void _GetString(  LPCTSTR  lpcszSection,
                     LPCTSTR  lpcszLeftSide,
                     LPSTR  lpcszBuf,               // out: retrieved string
                     int      nBufSize,               // in: size of lpcszBuf buffer
                     LPCTSTR  lpcszDefault = "" );   // in

   EMSDEGREES _GetDegrees( const LPCTSTR  lpcszSection, 
                           const LPCTSTR  lpcszLeftSide,
                           const LPCTSTR  lpcszDefault );

   BYTE    _GetByte( LPCTSTR, LPCTSTR, BYTE = 0 );
   void    _GetByte( BYTE&, LPCTSTR, LPCTSTR, BOOL=FALSE, BYTE = 0 );

   EMSDEGREES  _ConvertToDegrees( LPCTSTR lpcszValue );
   DWORD       _HexStringToDWORD( LPCTSTR  pszHexString );

protected:
   LPTSTR      m_lpszINIFile;
   LPTSTR      m_lpszINIFileName;
   LPTSTR      m_lpszComponentName;
};


