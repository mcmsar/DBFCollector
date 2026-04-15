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

#ifndef __TLE_H__
#define __TLE_H__

#include "emstle.h"
#include "configurationaccessor.h"
#include <string>

class CEMSTLE
{
	public:
		CEMSTLE();
		CEMSTLE( const CEMSTLE& x );
		~CEMSTLE();

		//! Input the TLE.
		void Set( const EMSTLERECORD cstrTLE );

		//! Input an xml string containing satellite id to NORAD SATCAT name and ID.  XML format is:
		//!		<satmap>
		//!			<satellite id='7'>
		//!				<noradname>NOAA 17</noradname>
		//!				<noradid>28564</noradid>
		//!			</satellite>
		//!		</satmap>
		void SetSatelliteMapping( const wchar_t* cwszSatMap );

		//! Return the TLE in the form of a string with line breaks replaced by semicolons (;).
		std::string GetAsString();

		//! Return the TLE in the form of a string with line breaks.
		std::string GetAsString2();

		//! Get the NORAD name of the satellite spec'd in the TLE.
		std::string GetNoradName();

	private:	// methods
		std::string _GetLine1();
		std::string _GetLine2();
		std::string _GetLine3();
		int _GetCheckSum(char* pszBuffer);
		void _CorrectRange( double* pdValue );
		std::string _GetSatelliteName();
		int _GetNoradNumber();
		int _GetElementNumber();

	private:	// constants
		static const char* ms_cszTLELine1Fmt;
		static const char* ms_cszTLELine2Fmt;
		static const char* ms_cszTLELine3Fmt;
		static const int ms_ciMaxNameLength;
		static const int ms_ciMaxLineLength;
		static const wchar_t* ms_cwszNoradName;
		static const wchar_t* ms_cwszNoradNumber;

	private:	// data
		EMSTLERECORD				m_strTLE;
		CEMSConfigurationAccessor	m_oSatMapping;

};

#endif