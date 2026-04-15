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

#ifndef __SARSAT_TEXT_ACCESSOR_H__
#define __SARSAT_TEXT_ACCESSOR_H__

#include "objectmap.h"
#include "emsorbit.h"
#include <string>

//#define EMS_MAX_SAT_NAME_LENGTH (32)


//! Reads/writes the sarsat.txt file.
class CEMSSarsatTxtAccessor
{
	public:
		CEMSSarsatTxtAccessor();
		CEMSSarsatTxtAccessor( const CEMSSarsatTxtAccessor& x );
		~CEMSSarsatTxtAccessor();

	public:
		typedef struct _tagNORADTLE
		{
			int			iNoradNumber;
			char		szName[ 32 ];
			int			iElementNumber;
			char		sClassification;
			int			iLaunchYear;
			int			iLaunchNumber;
			char		asLaunchPiece[3];
			double		dEpoch;
			double		dTimeDerivative1;
			double		dTimeDerivative2;
			double		dBStar;
			int			iEphemerisType;
			double		dInclination;
			double		dRightAscension;
			double		dEccentricity;
			double		dArgPerigee;
			double		dMeanAnomoly;
			double		dMeanMotion;
			int			iRevolutionNumber;
		} NORADTLE;

	public:
		//! Load the class from a sarsat.txt file.		
		void Load( const wchar_t* cwszSrcFile );

		//! Write the class data out to a sarsat.txt file.  If no output file path is specified then
		//! overwrite the loaded file or fail if no file was loaded previously.
		void Save( const wchar_t* cwszDestFile = 0 );

		//! Retrieve TLE data by Norad ID.
		bool GetByNoradID( const ULONG culNoradID, NORADTLE& rData );

		//! Not implemented.
		bool GetBySatID( const ULONG culSatID, NORADTLE& rData  );

		//! Add a new entry.
		void Add( const NORADTLE cstrTLE );

		void GetTLE2List( CEMSObjectMap<int, EMSTLEDATA2>& rmapTLE2 );
	

	private:
		void _Load();
		void _Save();
		int _RemoveTrailingUnprintables( char* szText );
		char _CalcChecksum( const char* cszBuffer );
		std::string _FmtTimeDerivative1Output( const double cdValue );
		std::string _FmtTimeDerivative2Output( const double cdValue );
		std::string _ExtractDecimalPortion( const double cdValue );
		void _CreateSarsatEntry();
		void _ConvertNORADTLEtoEMSTLEDATA2( NORADTLE rNoradTLE, EMSTLEDATA2& rEMSTLEdata2 );

	private:
		static const char* ms_cszNameFmt;
		static const char* ms_cszLine1NoCheckSum;
		static const char* ms_cszLine2NoCheckSum;
		static const char* ms_cszLine1;
		static const char* ms_cszLine2;
		static const char* ms_cszFirstTimeDerivative1Fmt;
		static const char* ms_cszFirstTimeDerivative2AFmt;
		static const char* ms_cszFirstTimeDerivative2BFmt;
		static const char* ms_cszTimeDerivative0;

	private:
		std::wstring m_owszFileName;

		// Map of TLES, keyed by NORAD ID.
		CEMSObjectMap<int,NORADTLE> m_omapTLEs;

};

#endif