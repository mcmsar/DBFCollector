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

#ifndef __FP_CONFIG_H__
#define __FP_CONFIG_H__

#include "configurationaccessor.h"
#include "fp.h"

class CEMSFPConfig
{
	public:
		CEMSFPConfig();
		CEMSFPConfig( const CEMSFPConfig& x );
		~CEMSFPConfig();

		void SetConfiguration( const wchar_t* cwszConfigString );

		std::wstring GetConfiguration();

		void SetProperty( const wchar_t* cwszKey, const wchar_t* cwszValue );

		std::wstring GetProperty( const wchar_t* cwszKey );

		void GetList( ULONG& rulPairs, EMSANTDATAPAIR*& raAntPairs );

		ULONG GetAntennaID( const ULONG culPair );

		ULONG GetDSID( const ULONG culPair );

		ULONG GetADBoardID( const ULONG culDSID );

		ULONG GetChannelID( const ULONG culDSID );

		ULONG GetLutID();

		int GetAntennaStatusCheckInterval();

		std::wstring GetDSProxyClassID( const ULONG culPair );

		std::wstring GetDSWSURL( const ULONG culPair );

		std::wstring GetDSWSUser( const ULONG culPair );

		std::wstring GetDSWSPassword( const ULONG culPair );

		std::wstring GetAntennaProxyClassID( const ULONG culAntennaID );

		std::wstring GetAntennaWSURL( const ULONG culAntennaID );

		std::wstring GetAntennaWSUser( const ULONG culAntennaID );

		std::wstring GetAntennaWSPassword( const ULONG culAntennaID );

		CEMSObjectList<ULONG> GetAntennaIDs();
		CEMSObjectList<ULONG> GetAntennaControllers();
		CEMSObjectList<ULONG> GetAntennaIDs( const ULONG culAntController );

		std::wstring GetAntennaConfig( const ULONG culAntennaID );

		std::wstring GetDSConfig( const ULONG culDSID );

		std::wstring GetScheduleFolder();

		bool DoesPairExist( const ULONG culPairID );

		void VerifyConfig();

	private:
		void  _GetListEx( ULONG& rulPairs, EMSANTDATAPAIR*& raAntPairs );
		ULONG _GetAntennaIDEx( const ULONG culPair );
		ULONG _GetDSIDEx( const ULONG culPair );
		ULONG _GetADBoardIDEx( const ULONG culDSID );
		ULONG _GetChannelIDEx( const ULONG culDSID );
		ULONG _GetLutIDEx();
		int   _GetAntennaStatusCheckIntervalEx();
		std::wstring _GetDSProxyClassIDEx( const ULONG culPair );
		std::wstring _GetDSWSURLEx( const ULONG culPair );
		std::wstring _GetDSWSUserEx( const ULONG culPair );
		std::wstring _GetDSWSPasswordEx( const ULONG culPair );
		std::wstring _GetAntennaProxyClassIDEx( const ULONG culAntennaID );
		std::wstring _GetAntennaWSURLEx( const ULONG culAntennaID );
		std::wstring _GetAntennaWSUserEx( const ULONG culAntennaID );
		std::wstring _GetAntennaWSPasswordEx( const ULONG culAntennaID );
		CEMSObjectList<ULONG> _GetAntennaIDsEx();
		CEMSObjectList<ULONG> _GetAntennaControllersEx();
		CEMSObjectList<ULONG> _GetAntennaIDsEx( const ULONG culAntController );
		std::wstring _GetAntennaConfigEx( const ULONG culAntennaID );
		std::wstring _GetDSConfigEx( const ULONG culDSID );
		std::wstring _GetScheduleFolderEx();
		bool _DoesPairExistEx( const ULONG culPairID );

		void _GetPairsList( CEMSConfigurationAccessor& roConfig, ULONG& rulPairs, EMSANTDATAPAIR*& raAntPairs );

		std::wstring _GetPairsXMLConfig();
		std::wstring _GetDataStreamXMLConfig();
		std::string _GetAntennaComponent();
		std::wstring _GetAntControllerXMLConfig();

	private:
		static const wchar_t* ms_cwszPairIDs;
		static const wchar_t* ms_cwszPair;
		static const wchar_t* ms_cwszID;
		static const wchar_t* ms_cwszPairAntenna;
		static const wchar_t* ms_cwszPairDS;
		static const wchar_t* ms_cwszDataStreamID;
		static const wchar_t* ms_cwszAntennaID;
		static const wchar_t* ms_cwszADBoardID;
		static const wchar_t* ms_cwszChannelID;
		static const wchar_t* ms_cwszDSProxyClassID;
		static const wchar_t* ms_cwszDSProxyWSURL;
		static const wchar_t* ms_cwszDSProxyWSUser;
		static const wchar_t* ms_cwszDSProxyWSPwd;
		static const wchar_t* ms_cwszAntennaProxyClassID;
		static const wchar_t* ms_cwszAntennaProxyWSURL;
		static const wchar_t* ms_cwszAntennaProxyWSUser;
		static const wchar_t* ms_cwszAntennaProxyWSPwd;
		static const wchar_t* ms_cwszAntenna;
		static const wchar_t* ms_cwszAntennaConfig;
		static const wchar_t* ms_cwszDSConfig;
		static const wchar_t* ms_cwszSatellites;
		static const wchar_t* ms_cwszScheduleFolder;
		static const wchar_t* ms_cwszLutID;
		static const wchar_t* ms_cwszAntennas;
		static const wchar_t* ms_cwszAntennaStatusCheckInterval;

	private:
		bool m_bUseConfigWS;
		CEMSConfigurationAccessor	m_oConfig;
		
};

#endif