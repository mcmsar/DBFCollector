/********************************************************************
*	Module:			Configuration.cpp
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
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
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

	0.0	2003Oct29		CH		First draft

********************************************************************/
#pragma warning(disable:4786)	// Disable warning messages for stl debug symbol size.
#include <assert.h>

#include "IConfigManager.h"
#include "Configuration.h"
#include "emserror.h"
#include "emsexcpt.h" 			// CEMSException

BOOL CEMSConfiguration::ms_bInitialized = FALSE;
CEMSCriticalSection CEMSConfiguration::ms_csConfigInit;
CEMSCriticalSection CEMSConfiguration::ms_csConfigCache;
IEMSConfigurationManager* CEMSConfiguration::ms_pConfigMgr = NULL;

CEMSConfiguration::CEMSConfiguration()
{
}

CEMSConfiguration::CEMSConfiguration( const CEMSConfiguration& x )
{
}

CEMSConfiguration::~CEMSConfiguration()
{
	if( ms_pConfigMgr )
	{
		ms_pConfigMgr->Release();
	}
	ms_pConfigMgr = NULL;
}

void
CEMSConfiguration::InitManager( CEMSConfiguration* pDerivedConfig )
{
	if( !ms_bInitialized )
	{
		ms_csConfigInit.Enter();

		try
		{
			if( !ms_bInitialized )
			{
				if( !ms_pConfigMgr )
				{
					EMS_RESULT hr = CoCreateInstance( CLSID_EMSConfigurationManager, 0, CLSCTX_ALL, 
													IID_IEMSConfigurationManager, (void**) &ms_pConfigMgr);

					if ( FAILED(hr) )	THROW_RUNTIME_EXCEPTION( hr );
				}
				// Load Cached Data
				pDerivedConfig->_LoadCache();
				ms_bInitialized = TRUE;
			}
		}
		catch( ... )
		{
			ms_csConfigInit.Leave();
			throw;
		}

		ms_csConfigInit.Leave();
	}
}

void
CEMSConfiguration::ShutdownManager( void )
{
	if( ms_bInitialized )
	{
		ms_csConfigInit.Enter();

		try
		{
			if( ms_bInitialized )
			{
				if( ms_pConfigMgr )
				{
					ms_pConfigMgr->Release();
				}
				ms_pConfigMgr = NULL;
				ms_bInitialized = FALSE;
			}
		}
		catch( ... )
		{
			ms_csConfigInit.Leave();
			throw;
		}

		ms_csConfigInit.Leave();
	}
}

void
CEMSConfiguration::_LoadCache( void )
{
	_LockCache();
	try
	{
		_DoLoadCache();
	}
	catch( ... )
	{
		_UnlockCache();
		throw;
	}
	_UnlockCache();
}

void
CEMSConfiguration::_GetString(	const wchar_t* cwszGroupType, 
								const wchar_t* cwszGroupID, 
								const wchar_t* cwszKey, 
								wstring &wszValue )
{
	// Should only be called through pointer grabbed via GetConfigurationMgr()
	assert( ms_pConfigMgr );
	assert( cwszKey && wcslen(cwszKey) > 0 );

	EMS_RESULT  hr             = EMS_OK;
	EMSVARITYPE varData;

	memset( &varData, 0, sizeof(varData) );

	hr = ms_pConfigMgr->Get( cwszGroupType, cwszGroupID, cwszKey, &varData );
	if ( SUCCEEDED(hr) )
	{
	   if ( EMSVARITYPE_DATATYPE_STRING == varData.dataType && varData.pwcsVal )
	   {
			wszValue.assign( varData.pwcsVal );
			CoTaskMemFree( varData.pwcsVal );
	   }
	   else
	   {
		   hr = EMS_UNKNOWN_ERROR;
	   }
	}
	if ( FAILED(hr) )	THROW_RUNTIME_EXCEPTION( hr );
}

void
CEMSConfiguration::_GetBoolean(const wchar_t* cwszGroupType, 
							   const wchar_t* cwszGroupID, 
							   const wchar_t* cwszKey, 
							   boolean &bValue )
{
	// Should only be called through pointer grabbed via GetConfigurationMgr()
	assert( ms_pConfigMgr );
	assert( cwszKey && wcslen(cwszKey) > 0 );

	EMS_RESULT  hr             = EMS_OK;
	EMSVARITYPE varData;

	memset( &varData, 0, sizeof(varData) );

	hr = ms_pConfigMgr->Get( cwszGroupType, cwszGroupID, cwszKey, &varData );
	if ( SUCCEEDED(hr) )
	{
	   if ( EMSVARITYPE_DATATYPE_BOOL == varData.dataType )
	   {
			bValue = varData.bVal;
	   }
	   else
	   {
		   hr = EMS_UNKNOWN_ERROR;
	   }
	}
	if ( FAILED(hr) )	THROW_RUNTIME_EXCEPTION( hr );
}

void
CEMSConfiguration::_GetULong(	const wchar_t* cwszGroupType, 
								const wchar_t* cwszGroupID, 
								const wchar_t* cwszKey, 
								unsigned long &ulValue )
{
	// Should only be called through pointer grabbed via GetConfigurationMgr()
	assert( ms_pConfigMgr );
	assert( cwszKey && wcslen(cwszKey) > 0 );

	EMS_RESULT  hr             = EMS_OK;
	EMSVARITYPE varData;

	memset( &varData, 0, sizeof(varData) );

	hr = ms_pConfigMgr->Get( cwszGroupType, cwszGroupID, cwszKey, &varData );
	if ( SUCCEEDED(hr) )
	{
	   if ( EMSVARITYPE_DATATYPE_UINT == varData.dataType )
	   {
			ulValue = varData.uiVal;
	   }
	   else
	   {
		   hr = EMS_UNKNOWN_ERROR;
	   }
	}
	if ( FAILED(hr) )	THROW_RUNTIME_EXCEPTION( hr );
}

unsigned long
CEMSConfiguration::_IncrementCachedULong(	const wchar_t* cwszGroupType, 
											const wchar_t* cwszGroupID, 
											const wchar_t* cwszKey,
											const unsigned long culMax )
{
	unsigned long ulIncrementedValue = 0L;

	_LockCache();

    try
    {
	    _GetULong( cwszGroupType, cwszGroupID, cwszKey, ulIncrementedValue );

	    ulIncrementedValue++;
	    if ( ulIncrementedValue >= culMax )
	    {
		    ulIncrementedValue = 1;
	    }

	    _SetULong( cwszGroupType, cwszGroupID, cwszKey, ulIncrementedValue );

    	_UnlockCache();
    }

    catch( ... )
    {
    	_UnlockCache();
        throw;
    }

	return ulIncrementedValue;
}

void
CEMSConfiguration::_SetULong(	const wchar_t* cwszGroupType, 
								const wchar_t* cwszGroupID, 
								const wchar_t* cwszKey, 
								const unsigned long culValue )
{
	// Should only be called through pointer grabbed via GetConfigurationMgr()
	assert( ms_pConfigMgr );
	assert( cwszKey && wcslen(cwszKey) > 0 );

	EMS_RESULT  hr             = EMS_OK;
	EMSVARITYPE varData;

	memset( &varData, 0, sizeof(varData) );

	varData.dataType = EMSVARITYPE_DATATYPE_UINT;
	varData.uiVal = culValue;

	hr = ms_pConfigMgr->Set( cwszGroupType, cwszGroupID, cwszKey, varData );
	if ( FAILED(hr) )	THROW_RUNTIME_EXCEPTION( hr );
}

