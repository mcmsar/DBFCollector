//! @file LogMsgParam.h
//! Header file for the CEMSLogMsgParam class declaration.

#ifndef __LOG_MSG_PARAM_H__
#define __LOG_MSG_PARAM_H__

#include "emstypes.h"	// must precede tchar.h in order to compile on VMS.
#include <tchar.h>
#include "emstime.h"

const long clMaxMsgSize = 255;

//! @class CEMSLogMsgParam
//! This class is used for creating a string of substitution
//! parameters for a log message.
class CEMSLogMsgParam
{
	public:
		CEMSLogMsgParam( short sCapacity =0 );
		CEMSLogMsgParam( const CEMSLogMsgParam& logMsg );
		virtual ~CEMSLogMsgParam();

		//! @fn CEMSLogMsgParam& operator+=( const TCHAR* szString )
		//! Concatenate the input string to the list of parameters.
		CEMSLogMsgParam& operator+=( const TCHAR* szString );

		//! @fn CEMSLogMsgParam& operator+=( const unsigned long culValue )
		//! Concatenate the input value to the list of parameters.
		CEMSLogMsgParam& operator+=( const unsigned long culValue );

		//! @fn operator const TCHAR* () const
		//! Extract the string representing the set of parameters.
		operator const TCHAR* () const { return Get(); }

		//! @fn void Add( const TCHAR* cszString )
		//! Concatenate the input string to the list of parameters.
		void Add( const TCHAR* cszString );

		//! @fn void Add( const unsigned long culValue )
		//! Concatenate the input value to the list of parameters.
		void Add( const unsigned long culValue );

		//! @fn void AddDouble( const double cdValue )
		//! Concatenate the input value to the list of parameters.
		void AddDouble( const double cdValue );

		//! @fn void AddX( const unsigned long culValue )
		//! Concatenate the input value to the list of parameters with hex formatting
		void AddX( const unsigned long culValue );

		//! @fn void Add64( const __int64 i64Value )
		//! Concatenate the input value to the list of parameters
		void Add64( const __int64 i64Value );

		//! @fn void AddBeaconID( const __int64 i64BeaconID )
		//! Concatenate a beacon ID as per OI.
		//! That is: hex, split into groups of 5 numbers
		void AddBeaconID( const __int64 i64BeaconID );

		//! @fn void AddTimestamp( const EMSTIME ctimestamp )
		//! Concatenate a timestamp as Year JulianDay hh:mm:ss.sss
		void AddTimestamp( const EMSTIME ctimestamp );

		//! @fn const TCHAR* Get() const
		//! Extract the string representing the set of parameters.
		const TCHAR* Get() const { return m_szString; }

		//! @fn unsigned long GetLength()
		//! Get the length of the string holding the parameter list.
		unsigned long GetLength() { return m_lLength; }

		//! @fn void AddString( const wchar_t* cwszParam )
		//! Add a wide character string parameter to the list.
		void AddString( const wchar_t* cwszParam );

		//! @fn wchar_t** GetParams()
		//! Returns a parameter array
		const wchar_t** GetParams() { return (const wchar_t** )m_awszParams; }
		//! @fn short GetCount()
		//! Returns the number of parameters
		short GetCount() { return m_sCount; }
		//! @fn void SetCapacity()
		//! Set the maximum number of parameters that can be specified
		void SetCapacity( short sCapacity );

		CEMSLogMsgParam& operator=( const CEMSLogMsgParam& oRHS );

		//! Clear the class's content.
		void Clear();

	private:
		bool _IsSpace( long lLen );

		void _Add( const TCHAR* cszString );
		void _AddToArray( const wchar_t* wsz );
		void _ReleaseArray();
		void _CopyParams( const CEMSLogMsgParam& msgParam );


	private:
		long	m_lLength;
		TCHAR	m_szString[clMaxMsgSize+1];

		wchar_t**	m_awszParams;
		short		m_sCount;
		short		m_sCapacity;
};

#endif // __LOG_MSG_PARAM_H__
