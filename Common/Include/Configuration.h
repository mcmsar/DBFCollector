//! @file Configuration.h
//! Header file for the CEMSConfiguration class.
/********************************************************************
*	Module:			Configuration.h
*	Process ID:
*	S/W Platforms:
*	H/W Platforms:
*	Compiler:
*	Description: 	
*
*	Usage:
*	Entry Point:
*	Input Files:
*	Output Files:
*	Comments:
*
*********************************************************************
*	              Copyright (c) 2004 by EMS Technologies, Inc.,
*										All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/

/*******************************************************************

  Revision Record

	Rev	Date			Auth	Changes
	===	====			====	=======

	0.0	2003Oct32		CH		First draft

********************************************************************/

#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include <string>
using std::wstring;

#include "criticalsection.h"

interface IEMSConfigurationManager;

//! @class CEMSConfiguration
//! This class is used to access configuration data
class CEMSConfiguration
{
	public: // methods
		CEMSConfiguration::CEMSConfiguration();
		CEMSConfiguration::CEMSConfiguration( const CEMSConfiguration& x );
		CEMSConfiguration::~CEMSConfiguration();


	protected:	// methods
		static void InitManager( CEMSConfiguration* pDerivedConfig );
		// call before CoUninitialize() to prevent exception on release of ms_pConfigMgr
		static void ShutdownManager( void );

		// Add more as required!!
		void _GetString(const wchar_t* cwszGroupType, 
						const wchar_t* cwszGroupID, 
						const wchar_t* cwszKey, 
						wstring &wszValue );
		void _GetBoolean(const wchar_t* cwszGroupType, 
						 const wchar_t* cwszGroupID, 
						 const wchar_t* cwszKey, 
						 boolean &bValue );
		void _GetULong(	const wchar_t* cwszGroupType, 
						const wchar_t* cwszGroupID, 
						const wchar_t* cwszKey, 
						unsigned long &ulValue );
		void _SetULong(	const wchar_t* cwszGroupType, 
						const wchar_t* cwszGroupID, 
						const wchar_t* cwszKey, 
						const unsigned long culValue );

		// For management of cached data
		virtual void _DoLoadCache( void ) = 0;
		unsigned long
		_IncrementCachedULong(	const wchar_t* cwszGroupType, 
								const wchar_t* cwszGroupID, 
								const wchar_t* cwszKey,
								const unsigned long culMax );

		// For management of cached data
		void _LoadCache( void );
		void _LockCache( void ) {ms_csConfigCache.Enter();}
		void _UnlockCache( void ) {ms_csConfigCache.Leave();}

	private:	// methods

	private:	// data
		static BOOL							ms_bInitialized;
		static CEMSCriticalSection			ms_csConfigInit;
		static IEMSConfigurationManager*	ms_pConfigMgr;
		static CEMSCriticalSection			ms_csConfigCache;
};

#endif // __CONFIGURATION_H__
