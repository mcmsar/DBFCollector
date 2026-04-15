
#ifndef __COMMAND_LINE_HELPER_H__
#define __COMMAND_LINE_HELPER_H__

class CEMSTime;

//! @class CEMSCommandLineHelper
//! Class with methods that can be used in a command line utility application.
class CEMSCommandLineHelper
{
	public:
		CEMSCommandLineHelper();
		CEMSCommandLineHelper( const CEMSCommandLineHelper& x );
		~CEMSCommandLineHelper();

		//! @fn bool ParseDateTime( char* szParam, CEMSTime* pTime )
		//! Takes a date string in the format YY:DDD:HH:MM:SS and converts it into an 
		//! EMS Time.
		bool ParseDateTime( char* szParam, CEMSTime* pTime );

		//! Takes a date string in the format YY:MM:DD:HH:MM:SS and converts it into an 
		//! EMS Time.
		bool ParseDateTimeStd( char* szParam, CEMSTime* pTime );

		//! @fn __int64 ParseBeaconID( char* szBeaconID )
		//! Converts a Hex format beacon id from a string into an __int64 decimal.
		__int64 ParseBeaconID( char* szBeaconID );

		//! @fn bool GetFileList( char* szList, char**& aszFiles, long& lNumFiles )
		//! Read a list of file paths from a file.  The input file format is one
		//! file path per line.
		bool GetFileList( char* szList, char**& aszFiles, long& lNumFiles );
};

#endif