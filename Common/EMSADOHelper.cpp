/*********************************************************************
*	              Copyright (c) 2003 by EMS Technologies, Inc.,
*										All rights reserved
* This program is unpublished software and contains the trade secrets
* and confidential information of EMS Technologies, Inc.  It may not be 
* reproduced in whole or in part, in any form or by any means whatsoever 
* without the express written permission of EMS Technologies, Inc.
*
********************************************************************/
#pragma warning(disable:4786)

#include "emsadohelper.h"

#include "dalmsgs.h"
#include "emsexcpt.h"

CEMSADOHelper::CEMSADOHelper()
{
}

CEMSADOHelper::CEMSADOHelper( const CEMSADOHelper& x )
{
}

CEMSADOHelper::~CEMSADOHelper()
{
}

DataTypeEnum 
CEMSADOHelper::GetADODataType( const EMSDBFLDTYPE ceDataType )
{
	DataTypeEnum eRet = adEmpty;

	_LoadEmsToAdoFldTypeTable();

	std::map<EMSDBFLDTYPE,DataTypeEnum>::iterator itFind = m_mapEmsToAdoFldType.find( ceDataType );

	if( itFind != m_mapEmsToAdoFldType.end() )
	{
		eRet = itFind->second;
	}
	else
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_UNKOWN_DATATYPE );
	}

	return eRet;
}

EMSDBFLDTYPE
CEMSADOHelper::GetEMSDataType( const DataTypeEnum ceType )
{
	EMSDBFLDTYPE eRet = DBFLDTYPE_UNKNOWN;

	_LoadAdoToEmsFldTypeTable();

	std::map<DataTypeEnum,EMSDBFLDTYPE>::iterator itFind = m_mapAdoToEmsFldType.find( ceType );

	if( itFind != m_mapAdoToEmsFldType.end() )
	{
		eRet = itFind->second;
	}
	else
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_UNKOWN_DATATYPE );
	}

	return eRet;
}


ParameterDirectionEnum	
CEMSADOHelper::GetADODirectionType( const EMSDBCMDDIRECTIONTYPE ceParamType ) const
{
	ParameterDirectionEnum eRet = adParamUnknown;

	switch( ceParamType )
	{
		case EMS_DBCMD_DIR_TYPE_INPUT:
			eRet = adParamInput;
			break;
		case EMS_DBCMD_DIR_TYPE_OUTPUT:
			eRet = adParamOutput;
			break;
		case EMS_DBCMD_DIR_TYPE_INOUT:
			eRet = adParamInputOutput;
			break;
		case EMS_DBCMD_DIR_TYPE_RETURN:
			eRet = adParamReturnValue;
			break;
	}

	return eRet;
}

void
CEMSADOHelper::ConvertToSafeArray( const unsigned long culBytes, 
									const unsigned char* cabyValue,
									_variant_t& vValue ) const
{
	if( culBytes > 0 )
	{
		
		if( !cabyValue )
		{
			THROW_NULL_POINTER_EXCEPTION();
		}

		SAFEARRAY FAR *psa;
		SAFEARRAYBOUND rgsabound[1];
		rgsabound[0].lLbound = 0;
		rgsabound[0].cElements = culBytes;
		psa = SafeArrayCreate(VT_UI1,1,rgsabound);
		for( long l = 0; l < (long) culBytes; l++)
		{
			//Take BYTE by BYTE and advance Memory Location
			EMS_RESULT hr = SafeArrayPutElement(psa, &l, (void*)(&cabyValue[l]));

			if( FAILED(hr) )
			{
				THROW_RUNTIME_EXCEPTION( hr );
			}
		}

	   vValue.Clear();
	   vValue.vt = VT_ARRAY|VT_UI1;
	   vValue.parray = psa;

	}
}

long
CEMSADOHelper::GetEMSDataSize( const EMSDBFLDTYPE ceType )
{
	long lSize = 0;

	_LoadEMSDataSizes();

	std::map<EMSDBFLDTYPE,long>::iterator itFind = m_mapEmsDataSizes.find( ceType );

	if( itFind != m_mapEmsDataSizes.end() )
	{
		lSize = itFind->second;
	}
	else
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_UNKOWN_DATATYPE );
	}

	return lSize;
}

EMSDBOBJECTSTATE		
CEMSADOHelper::GetEMSObjectState( const ObjectStateEnum ceState )
{
	EMSDBOBJECTSTATE eRet = DBOBJ_STATE_UNKNOWN;

	_LoadAdoToEmsObjectStateTable();

	std::map<ObjectStateEnum,EMSDBOBJECTSTATE>::iterator itFind = m_mapAdoToEmsObjState.find( ceState );

	if( itFind != m_mapAdoToEmsObjState.end() )
	{
		eRet = itFind->second;
	}
	else
	{
		THROW_RUNTIME_EXCEPTION_WITH_MSG( EMS_DAL_UNKOWN_OBJECTSTATE );
	}

	return eRet;
}

bool
CEMSADOHelper::FilterAlarm( const HRESULT crErrorCode )
{
	bool bRet = false;

	long lIndex = 0;

	while( 0 != s_achrFilteredAlarms[lIndex] )
	{
		if( crErrorCode == s_achrFilteredAlarms[lIndex] )
		{
			bRet = true;
			break;
		}

		lIndex++;
	}

	return bRet;
}

bool
CEMSADOHelper::IsWarning( const HRESULT crErrorCode )
{
	bool bRet = false;

	long lIndex = 0;

	while( 0 != s_achrWarnings[lIndex] )
	{
		if( crErrorCode == s_achrWarnings[lIndex] )
		{
			bRet = true;
			break;
		}

		lIndex++;
	}

	return bRet;
}

DATE					
CEMSADOHelper::GetDate( const EMSTIME ctimeValue )
{
	DATE dRet = 0;

	CEMSTime oTime( ctimeValue );

	EMSTIMEFIELDS tmFields;
	oTime.GetTime( &tmFields );

	SYSTEMTIME tmSystem;
	memset( &tmSystem, 0, sizeof(SYSTEMTIME) );

	tmSystem.wYear = tmFields.nYear;
	tmSystem.wMonth = tmFields.nMonth;
	tmSystem.wDay = tmFields.nDay;
	tmSystem.wHour = tmFields.nHour;
	tmSystem.wMinute = tmFields.nMinute;
	tmSystem.wSecond = tmFields.nSecond;
	tmSystem.wMilliseconds = tmFields.lNanosecond / 1000;

	SystemTimeToVariantTime( &tmSystem, &dRet );

	return dRet;
}

EMSTIME
CEMSADOHelper::GetEMSTime( const VARIANT cvValue )
{
	EMSTIME timeRet;
	timeRet.intTime = 0;

	SYSTEMTIME tmSystem;
	memset( &tmSystem, 0, sizeof(SYSTEMTIME) );
	VariantTimeToSystemTime( cvValue.date, &tmSystem );

	CEMSTime oTime( tmSystem.wYear, tmSystem.wMonth, tmSystem.wDay, tmSystem.wHour, 
				tmSystem.wMinute, tmSystem.wSecond, tmSystem.wMilliseconds * 1000 );

	timeRet = oTime;

	return timeRet;
}

AffectEnum				
CEMSADOHelper::GetADOAffectType( const EMSDBAFFECTS ceAffect )
{
	AffectEnum eRet = adAffectCurrent;

	switch( ceAffect )
	{
		case DBAFFECT_ALL:
			eRet = adAffectAll;
			break;
		case DBAFFECT_CURRENT:
			eRet = adAffectCurrent;
			break;
		case DBAFFECT_ALL_CHAPTERS:
			eRet = adAffectAllChapters;
			break;
		case DBAFFECT_GROUP:
			eRet = adAffectGroup;
			break;
		default:
			eRet = adAffectCurrent;

	}

	return eRet;
}

void 
CEMSADOHelper::_LoadAdoToEmsFldTypeTable()
{
	if( m_mapAdoToEmsFldType.empty() )
	{
		long l = 0;

		while( -1 != l )
		{
			if( 0 != s_caFldTypeConversions[l].eAdoType )
			{
				m_mapAdoToEmsFldType.insert( std::pair<DataTypeEnum,EMSDBFLDTYPE>( s_caFldTypeConversions[l].eAdoType,
																					s_caFldTypeConversions[l].eEmsType ) );

				l++;
			}
			else
			{
				l = -1;
			}
		}
	}
}

void 
CEMSADOHelper::_LoadEmsToAdoFldTypeTable()
{
	if( m_mapEmsToAdoFldType.empty() )
	{
		long l = 0;

		while( -1 != l )
		{
			if( 0 != s_caFldTypeConversions[l].eAdoType )
			{
				m_mapEmsToAdoFldType.insert( std::pair<EMSDBFLDTYPE,DataTypeEnum>( s_caFldTypeConversions[l].eEmsType,
																					s_caFldTypeConversions[l].eAdoType ) );

				l++;
			}
			else
			{
				l = -1;
			}
		}
	}
}

void 
CEMSADOHelper::_LoadEMSDataSizes()
{
	if( m_mapEmsDataSizes.empty() )
	{
		long l = 0;

		while( -1 != l )
		{
			if( 0 != s_caFldSizes[l].eDataType )
			{
				m_mapEmsDataSizes.insert( std::pair<EMSDBFLDTYPE,long>( s_caFldSizes[l].eDataType,
																		s_caFldSizes[l].lBytes ) );

				l++;
			}
			else
			{
				l = -1;
			}
		}
	}
}

void 
CEMSADOHelper::_LoadAdoToEmsObjectStateTable()
{
	if( m_mapAdoToEmsObjState.empty() )
	{
		long l = 0;

		while( -1 != l )
		{
			if( -1 != s_caObjStateConversions[l].eAdoState )
			{
				m_mapAdoToEmsObjState.insert( std::pair<ObjectStateEnum,EMSDBOBJECTSTATE>( s_caObjStateConversions[l].eAdoState,
																					s_caObjStateConversions[l].eEmsState ) );

				l++;
			}
			else
			{
				l = -1;
			}
		}
	}
}