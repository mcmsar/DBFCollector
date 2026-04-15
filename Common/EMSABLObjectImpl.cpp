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


#include "EMSABLObjectImpl.h"
#include "emsexcpt.h"
#include "ABLMsgs.h"
#include "configurationaccessor.h"
#include "convutility.h"



const std::string   CEMSABLObjectImpl::ms_szInputLocationsFileName = "InputLocations.csv";
const std::string   CEMSABLObjectImpl::ms_szOutputLocationsFileName = "OutputLocations.csv";
const std::string   CEMSABLObjectImpl::ms_szOutputSummariesFileName = "OutputSummaries.csv";

const wchar_t* CEMSABLObjectImpl::ms_cwszWorkingDir = L"WorkingDir";
const wchar_t* CEMSABLObjectImpl::ms_cwszAcceptCBC = L"AcceptCBC";
const wchar_t* CEMSABLObjectImpl::ms_cwszLoggingEnabled = L"LoggingEnabled";


CEMSABLObjectImpl::CEMSABLObjectImpl(): CApiObjBase("CEMSABLObjectImpl"), 
                                        m_bLoggingEnabled(false),
										m_bAcceptCBC(false)
{
}

CEMSABLObjectImpl::~CEMSABLObjectImpl()
{
}

EMS_RESULT 
CEMSABLObjectImpl::Init( const wchar_t* cwszXMLString )
{
	EMS_RESULT hr = m_oABLProperties.InitXml( cwszXMLString );

	if( cwszXMLString && ( 0 < wcslen( cwszXMLString ) ) )
	{
		CEMSConfigurationAccessor oConfig;

		oConfig.SetSource( cwszXMLString );
		m_szABLDir = CEMSConversionUtil::ConvertToString( oConfig.GetElementValue( CEMSABLObjectImpl::ms_cwszWorkingDir ).c_str() );
		m_bLoggingEnabled = oConfig.GetElementValueBoolean( CEMSABLObjectImpl::ms_cwszLoggingEnabled );
		m_bAcceptCBC = oConfig.GetElementValueBoolean( CEMSABLObjectImpl::ms_cwszAcceptCBC );
	}

	if( SUCCEEDED( hr ) )
	{
		hr = Reset();
	}

	return hr;
}


EMS_RESULT 
CEMSABLObjectImpl::Init( const EMSABLProperties& cemsABLProps )
{
	EMS_RESULT hr = EMS_OK;

	m_oABLProperties.SetProperties( cemsABLProps );

	Reset();

	return hr;
}

CEMSABLRawObject*
CEMSABLObjectImpl::_GetNextEmptyRawObj()
{
	CEMSABLRawObject* pRet = NULL;
	CEMSActiveBeacon* pABObject = NULL;
	bool bEmptyRawLcns = true;
	
	try
	{
		ms_mtxEmptyRawLocations.Enter();

		if( m_lstEmptyRawLocations.Count() > 0 )
		{
			bEmptyRawLcns = false;
			m_lstEmptyRawLocations.MoveFirst();
			pRet = m_lstEmptyRawLocations.GetNext();
			m_lstEmptyRawLocations.RemoveCurrent();
			_AddRawObjToInUseList( pRet );
		}
		else
		{
			ms_mtxActiveBeacons.Enter();
			m_mapActiveBeacons.MoveFirst();
			while( pABObject = m_mapActiveBeacons.GetNext() )
			{
				pRet = pABObject->FreeRawObj( m_oABLProperties.GetMinLocatesPerAB() );
				pABObject->Release();
				pABObject = NULL;
				
				if( pRet )
				{
					break;
				}
			}

			// at this point if pRet is a valid object it must've been "InUse" 
			// and so no need to call _AddRawObjToInUseList( pRet );
			ms_mtxActiveBeacons.Leave();
		}
		
		ms_mtxEmptyRawLocations.Leave();
	}
	catch( ... )
	{
		ms_mtxEmptyRawLocations.Leave();
		
		if( bEmptyRawLcns )
		{
			ms_mtxActiveBeacons.Leave();
		}
		
		if( pRet )
		{
			pRet->Release();
			pRet = NULL;
		}

		if( pABObject )
		{
			pABObject->Release();
			pABObject = NULL;
		}
		throw;
	}

	return pRet;
}

void
CEMSABLObjectImpl::_SetRawObjInUse( CEMSABLRawObject* pRawObj )
{
	if( pRawObj )
	{
		_RemoveRawObjFromEmpty( pRawObj );
		_AddRawObjToInUseList( pRawObj );
	}
}

void
CEMSABLObjectImpl::_SetRawObjAsEmpty( CEMSABLRawObject* pRawObj )
{
	if( pRawObj )
	{
		_RemoveRawObjFromInUse( pRawObj );
		_AddRawObjToEmptyList( pRawObj );
	}
}

void
CEMSABLObjectImpl::_AddRawObjToInUseList( CEMSABLRawObject* pRawObj )
{
	if( pRawObj )
	{
		try
		{
			ms_mtxInUseRawLocations.Enter();

			m_lstInUseRawLocations.Add( pRawObj );

			ms_mtxInUseRawLocations.Leave();
		}
		catch( ... )
		{
			ms_mtxInUseRawLocations.Leave();
			throw;
		}
	}
}

void
CEMSABLObjectImpl::_AddRawObjToEmptyList( CEMSABLRawObject* pRawObj )
{
	if( pRawObj )
	{
		pRawObj->Reset();
		try
		{
			ms_mtxEmptyRawLocations.Enter();

			m_lstEmptyRawLocations.Add( pRawObj );

			ms_mtxEmptyRawLocations.Leave();
		}
		catch( ... )
		{
			ms_mtxEmptyRawLocations.Leave();
			throw;
		}
	}
}

void
CEMSABLObjectImpl::_RemoveRawObjFromInUse( CEMSABLRawObject* pRawObj )
{
	if( pRawObj )
	{
		CEMSABLRawObject* pRawLcnObj = NULL;
		try
		{
			ms_mtxInUseRawLocations.Enter();

			m_lstInUseRawLocations.MoveFirst();

			while( pRawLcnObj = m_lstInUseRawLocations.GetNext() )
			{
				if( pRawObj == pRawLcnObj )
				{
					m_lstInUseRawLocations.RemoveCurrent();
					pRawLcnObj->Release();
					pRawLcnObj = NULL;
					break;
				}
				else
				{
					pRawLcnObj->Release();
					pRawLcnObj = NULL;
				}
			}

			ms_mtxInUseRawLocations.Leave();
		}
		catch( ... )
		{
			ms_mtxInUseRawLocations.Leave();
			
			if( pRawLcnObj )
			{
				pRawLcnObj->Release();
				pRawLcnObj = NULL;
			}

			throw;
		}
	}
}


void
CEMSABLObjectImpl::_RemoveRawObjFromEmpty( CEMSABLRawObject* pRawObj )
{
	if( pRawObj )
	{
		CEMSABLRawObject* pRawLcnObj = NULL;
		try
		{
			ms_mtxEmptyRawLocations.Enter();

			m_lstEmptyRawLocations.MoveFirst();

			while( pRawLcnObj = m_lstEmptyRawLocations.GetNext() )
			{
				if( pRawObj == pRawLcnObj )
				{
					m_lstEmptyRawLocations.RemoveCurrent();
					pRawLcnObj->Release();
					pRawLcnObj = NULL;
					break;
				}
				else
				{
					pRawLcnObj->Release();
					pRawLcnObj = NULL;
				}
			}

			ms_mtxEmptyRawLocations.Leave();
		}
		catch( ... )
		{
			ms_mtxEmptyRawLocations.Leave();
			
			if( pRawLcnObj )
			{
				pRawLcnObj->Release();
				pRawLcnObj = NULL;
			}

			throw;
		}
	}
}


EMS_RESULT
CEMSABLObjectImpl::GetABLProperties( EMSABLProperties* pObjProperties )
{
	EMS_RESULT hr = EMS_OK;

	if( pObjProperties )
	{
		m_oABLProperties.GetProperties( *pObjProperties );
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}

ULONG
CEMSABLObjectImpl::_GetABCount()
{
	ULONG ulCount = 0;
	
	try
	{
		ms_mtxActiveBeacons.Enter();
		ulCount = m_mapActiveBeacons.Count();
		ms_mtxActiveBeacons.Leave();
	}
	catch( ... )
	{
		ms_mtxActiveBeacons.Leave();
		throw;
	}

	return ulCount;
}

EMS_RESULT
CEMSABLObjectImpl::GetLuts( const ULONG culCount,
						    ULONG* pulActualSize,
							ULONG* aLutProperties )
{
	EMS_RESULT hr = EMS_OK;

	if( pulActualSize )
	{
		CEMSABLRawObject* pRawObj = NULL;
		try
		{
			std::list<ULONG> lstLutIds;
			ms_mtxInUseRawLocations.Enter();

			m_lstInUseRawLocations.MoveFirst();
			while( pRawObj = m_lstInUseRawLocations.GetNext() )
			{
				lstLutIds.push_back( pRawObj->GetLUTID() );
				pRawObj->Release();
				pRawObj = NULL;
			}

			lstLutIds.sort();
			lstLutIds.unique ();

			*pulActualSize = lstLutIds.size();
			if( *pulActualSize <= culCount )
			{
				std::list<ULONG>::iterator Iter = lstLutIds.begin();
				for( ULONG i = 0; Iter != lstLutIds.end(); i++, Iter++ )
				{
					aLutProperties[i] = *Iter;
				}
			}
			else
			{
				hr = EMS_ABL_MEM_OVERFLOW;
			}

			ms_mtxInUseRawLocations.Leave();
		}
		catch( ... )
		{
			ms_mtxInUseRawLocations.Leave();
			if( pRawObj )
			{
				pRawObj->Release();
				pRawObj = NULL;
			}
			throw;
		}
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}

						
EMS_RESULT
CEMSABLObjectImpl::GetSats( const ULONG  culCount,
						    ULONG*  pulActualSize,
							ULONG* aSatProperties )
{
	EMS_RESULT hr = EMS_OK;

	if( pulActualSize )
	{
		CEMSABLRawObject* pRawObj = NULL;
		try
		{
			std::list<ULONG> lstSATIds;
			ms_mtxInUseRawLocations.Enter();

			m_lstInUseRawLocations.MoveFirst();
			while( pRawObj = m_lstInUseRawLocations.GetNext() )
			{
				pRawObj->GetSATIDs( lstSATIds );

				pRawObj->Release();
				pRawObj = NULL;
			}

			*pulActualSize = lstSATIds.size();
			if( *pulActualSize <= culCount )
			{
				std::list<ULONG>::iterator Iter = lstSATIds.begin();
				for( ULONG i = 0; Iter != lstSATIds.end(); i++, Iter++ )
				{
					aSatProperties[i] = *Iter;
				}
			}
			else
			{
				hr = EMS_ABL_MEM_OVERFLOW;
			}

			ms_mtxInUseRawLocations.Leave();
		}
		catch( ... )
		{
			ms_mtxInUseRawLocations.Leave();
			if( pRawObj )
			{
				pRawObj->Release();
				pRawObj = NULL;
			}
			throw;
		}
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}



EMS_RESULT
CEMSABLObjectImpl::GetBeacons( const ULONG  culCount,
		                       ULONG* pulActualSize,
							   INT64* aBeaconProperties )
{
	EMS_RESULT hr = EMS_OK;

	hr = GetBeaconIDs( culCount, pulActualSize, aBeaconProperties );

	return hr;
}


EMS_RESULT
CEMSABLObjectImpl::GetLocationTypes( const ULONG  culCount,
									 ULONG* pulActualSize,
									 EMSLOCATETYPE* aLocationProperties )
{
	EMS_RESULT hr = EMS_OK;

	if( pulActualSize )
	{
		CEMSABLRawObject* pRawObj = NULL;
		try
		{
			std::list<WORD> lstLcnsTypes;
			ms_mtxInUseRawLocations.Enter();

			m_lstInUseRawLocations.MoveFirst();
			while( pRawObj = m_lstInUseRawLocations.GetNext() )
			{
				lstLcnsTypes.push_back( pRawObj->GetLocationType() );
				pRawObj->Release();
				pRawObj = NULL;
			}

			lstLcnsTypes.sort();
			lstLcnsTypes.unique();

			*pulActualSize = lstLcnsTypes.size();
			if( *pulActualSize <= culCount )
			{
				std::list<WORD>::iterator Iter = lstLcnsTypes.begin();
				for( ULONG i = 0; Iter != lstLcnsTypes.end(); i++, Iter++ )
				{
					aLocationProperties[i] = (EMSLOCATETYPE)*Iter;
				}
			}
			else
			{
				hr = EMS_ABL_MEM_OVERFLOW;
			}

			ms_mtxInUseRawLocations.Leave();
		}
		catch( ... )
		{
			ms_mtxInUseRawLocations.Leave();
			if( pRawObj )
			{
				pRawObj->Release();
				pRawObj = NULL;
			}
			throw;
		}
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}
	
	return hr;
}


EMS_RESULT 
CEMSABLObjectImpl::GetCountryCodes( const ULONG  culCount,
								    ULONG* pulActualSize,
									int* aCCProperies )
{
	EMS_RESULT hr = EMS_OK;

	if( pulActualSize )
	{
		CEMSABLRawObject* pRawObj = NULL;
		try
		{
			ULONG ulCntryCode = 0;
			std::list<ULONG> lstCntryCodes;
			ms_mtxInUseRawLocations.Enter();

			m_lstInUseRawLocations.MoveFirst();
			while( pRawObj = m_lstInUseRawLocations.GetNext() )
			{
				ulCntryCode = pRawObj->GetCountryCode();
				if( ulCntryCode )
				{
					lstCntryCodes.push_back( ulCntryCode );
				}
				pRawObj->Release();
				pRawObj = NULL;
			}

			lstCntryCodes.sort(); //TBV
			lstCntryCodes.unique();

			*pulActualSize = lstCntryCodes.size();
			if( *pulActualSize <= culCount )
			{
				std::list<ULONG>::iterator Iter = lstCntryCodes.begin();
				for( ULONG i = 0; Iter != lstCntryCodes.end(); i++, Iter++ )
				{
					aCCProperies[i] = *Iter;
				}
			}
			else
			{
				hr = EMS_ABL_MEM_OVERFLOW;
			}

			ms_mtxInUseRawLocations.Leave();
		}
		catch( ... )
		{
			ms_mtxInUseRawLocations.Leave();
			if( pRawObj )
			{
				pRawObj->Release();
				pRawObj = NULL;
			}
			throw;
		}
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}
	
	return hr;
}

EMS_RESULT 
CEMSABLObjectImpl::GetProtocolTypes( const ULONG  culCount,
									 ULONG* pulActualSize,
									 int* aProtocolProperies )
{
	EMS_RESULT hr = EMS_NOT_IMPLEMENTED;

	return hr;
}

EMS_RESULT 
CEMSABLObjectImpl::PutData( const ULONG culNumOfRecords,
						    EMSLOCATE* caLocate )
{
	EMS_RESULT hr = EMS_OK;

	for( ULONG i = 0; i < culNumOfRecords; i++ )
	{
		if( m_bAcceptCBC || ( (caLocate[i].wType & EMSLOCTYPE_CBC) != EMSLOCTYPE_CBC ) )
		{
			if( m_oABLProperties.IsMatchingProperties( &(caLocate[i]) ) )
			{
				bool bNoMoreFreeObjs = _NoEmptyRawObject();
				CEMSABLRawObject* pRawObj = _GetNextEmptyRawObj();
				if( pRawObj )
				{
					pRawObj->SetRawData( caLocate[i] );
					hr = _PutRawObj( pRawObj );
					if( FAILED(hr) )
					{
						THROW_RUNTIME_EXCEPTION(hr);
					}
					else if( bNoMoreFreeObjs )
					{
						hr = EMS_ABL_MAX_CAP;
					}
				}
				else
				{
					THROW_RUNTIME_EXCEPTION(EMS_ABL_MEM_OVERFLOW);
				}
			}
		}
	}

	return hr;
}

EMS_RESULT
CEMSABLObjectImpl::_PutRawObj( CEMSABLRawObject* pRawObj )
{
	EMS_RESULT hr = EMS_OK;
	if( pRawObj )
	{
		CEMSActiveBeacon* pActiveBcn = NULL;
		try
		{
			INT64 i64BcnID = pRawObj->GetBeaconID();
			ms_mtxActiveBeacons.Enter();

			pActiveBcn = m_mapActiveBeacons.Get( i64BcnID );

			if( pActiveBcn )
			{
				BYTE cBeaconMsg[ 18 ];
				EMSABLData ablData;
				memset( &ablData, 0, sizeof(EMSABLData) );
				pActiveBcn->GetBeaconSummary( ablData );
				pRawObj->GetBeaconMsg(cBeaconMsg, 18);

				if( ablData.Id.acBeaconMsg[2] != cBeaconMsg[2] )
				{
					m_mapActiveBeacons.Remove( i64BcnID );
					pActiveBcn->Release();
					pActiveBcn = NULL;
				}
			}

			if( !pActiveBcn )
			{
				// then it couldn't be found in the list.. create new one.
				pActiveBcn = new CEMSActiveBeacon( pRawObj->GetBeaconID() );
				if( !pActiveBcn )
				{
					THROW_NOMEMORY_EXCEPTION();
				}

				pActiveBcn->SetForceUpdate( (TRUE == m_oABLProperties.GetForceUpdate()) );
				pActiveBcn->SetIgnoreConfRules( (TRUE == m_oABLProperties.GetIgnoreConfRules()) );
				pActiveBcn->SetSubstituteTimeWindow( m_oABLProperties.GetSubstituteTimeWindow() );
				pActiveBcn->SetMsgMaxInterval( m_oABLProperties.GetMsgMaxInterval() );
				pActiveBcn->SetMinTimeBtwnBursts( m_oABLProperties.GetMinTimeBtwnBursts() );
				pActiveBcn->SetMaxSubstituteFSErrors( m_oABLProperties.GetMaxSubstituteFSErrors() );
				pActiveBcn->SetMaxSubstitutePDF1Errors( m_oABLProperties.GetMaxSubstitutePDF1Errors() );
				pActiveBcn->SetMaxSubstitutePDF2Errors( m_oABLProperties.GetMaxSubstitutePDF2Errors() );
				pActiveBcn->SetMinTotalSatsNum( m_oABLProperties.GetMinTotalSatsNum() );
				pActiveBcn->SetMinGEOSatsNum( m_oABLProperties.GetMinGEOSatsNum() );
				pActiveBcn->SetMinLEOSatsNum( m_oABLProperties.GetMinLEOSatsNum() );
				pActiveBcn->SetMinMEOSatsNum( m_oABLProperties.GetMinMEOSatsNum() );
				pActiveBcn->SetAgeOutPeriod( m_oABLProperties.GetABAgeout() );
				pActiveBcn->EnableLogging( m_bLoggingEnabled );
				pActiveBcn->SetRadius( m_oABLProperties.GetRadius() );
				pActiveBcn->SetFloatRate( m_oABLProperties.GetFloatRate() );
				pActiveBcn->SetMaxTimeStdDev( m_oABLProperties.GetMaxTimeStdDev() );
				pActiveBcn->SetMaxFreqStdDev( m_oABLProperties.GetMaxFreqStdDev() );
				pActiveBcn->SetMaxHDOP( m_oABLProperties.GetMaxHDOP() );
				pActiveBcn->SetLcnProximityThreshold( m_oABLProperties.GetLcnProximityThreshold() );
				pActiveBcn->Init( m_szABLDir.c_str() );

				m_mapActiveBeacons.Add( i64BcnID, pActiveBcn );
			}

			// by now there has to be a valid pActiveBcn...
			hr = pActiveBcn->PutRawLocationObject( pRawObj );

			{
				CEMSPointerList<CEMSABLRawObject>  lstRawLocations;
				pActiveBcn->GetAgedOutRawObjects( lstRawLocations );
				pActiveBcn->FreePurgedRawObjects( lstRawLocations );
				_SetRawObjectsAsEmpty( lstRawLocations );
			}

			pActiveBcn->Release();
			pActiveBcn = NULL;

			ms_mtxActiveBeacons.Leave();
		}
		catch( ... )
		{
			ms_mtxActiveBeacons.Leave();
			if( pActiveBcn )
			{
				pActiveBcn->Release();
				pActiveBcn = NULL;
			}
			throw;
		}

		if( m_bLoggingEnabled )
		{
			std::string szCSVStr;
			pRawObj->ToCSVString( szCSVStr );
			m_csvFInputLocations.WriteText( szCSVStr.c_str() );
		}
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}
	return hr;
}


EMS_RESULT 
CEMSABLObjectImpl::GetBeaconCount( ULONG* pulCount )
{
	EMS_RESULT hr = EMS_OK;

	if( pulCount )
	{
		*pulCount = _GetABCount();
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}


EMS_RESULT 
CEMSABLObjectImpl::GetBeaconIDs( const ULONG culCount,
								 ULONG* pulActualSize,
								 INT64* aBeaconIDs )
{
	EMS_RESULT hr = EMS_OK;

	if( pulActualSize && aBeaconIDs )
	{
		CEMSActiveBeacon* pABObject = NULL;
		try
		{
			ms_mtxActiveBeacons.Enter();

			ULONG i = 0;
			*pulActualSize = m_mapActiveBeacons.Count();
			if( *pulActualSize <= culCount )
			{
				m_mapActiveBeacons.MoveFirst();
				while( pABObject = m_mapActiveBeacons.GetNext() )
				{
					aBeaconIDs[i++] = pABObject->GetBeaconID();
					pABObject->Release();
					pABObject = NULL;
				}
			}
			else
			{
				hr = EMS_ABL_MEM_OVERFLOW;
			}
			ms_mtxActiveBeacons.Leave();
		}
		catch( ... )
		{
			ms_mtxActiveBeacons.Leave();
			if( pABObject )
			{
				pABObject->Release();
				pABObject = NULL;
			}
			throw;
		}
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}

void
CEMSABLObjectImpl::_ClearAgedOutBcns()
{
	CEMSActiveBeacon* pABObject = NULL;
	try
	{
		ms_mtxActiveBeacons.Enter();

		m_mapActiveBeacons.MoveFirst();
		while( pABObject = m_mapActiveBeacons.GetNext() )
		{
			if( pABObject->IsAged() )
			{
				CEMSPointerList<CEMSABLRawObject>  lstRawLocations;
				pABObject->FreeAllRawObjects( lstRawLocations );
				_SetRawObjectsAsEmpty( lstRawLocations );
				m_mapActiveBeacons.RemoveCurrent();
			}
			pABObject->Release();
			pABObject = NULL;
		}

		ms_mtxActiveBeacons.Leave();
	}
	catch( ... )
	{
		ms_mtxActiveBeacons.Leave();
		if( pABObject )
		{
			pABObject->Release();
			pABObject = NULL;
		}
		throw;
	}
}

void 
CEMSABLObjectImpl::_SetRawObjectsAsEmpty( CEMSPointerList<CEMSABLRawObject>& rlstRawObjs )
{
	CEMSABLRawObject* pRawObj = NULL;

	try
	{
		if( rlstRawObjs.Count() )
		{
			rlstRawObjs.MoveFirst();

			while( pRawObj = rlstRawObjs.GetNext() )
			{
				_SetRawObjAsEmpty( pRawObj );
				pRawObj->Release();
				pRawObj = NULL;
			}

			rlstRawObjs.Clear();
		}
	}
	catch( ... )
	{
		if( pRawObj )
		{
			pRawObj->Release();
			pRawObj = NULL;
		}
	}
}


EMS_RESULT 
CEMSABLObjectImpl::GetBeaconLocationsEx( const ULONG culCount,
										 ULONG *pulActualSize,
										 EMSABLData* aABLData )
{
	EMS_RESULT hr = EMS_OK;

	_ClearAgedOutBcns();

	if( pulActualSize && aABLData )
	{
		CEMSActiveBeacon* pABObject = NULL;
		try
		{
			ms_mtxActiveBeacons.Enter();

			ULONG i = 0;
			*pulActualSize = m_mapActiveBeacons.Count();
			if( *pulActualSize <= culCount )
			{
				m_mapActiveBeacons.MoveFirst();
				while( pABObject = m_mapActiveBeacons.GetNext() )
				{
					hr = pABObject->GetBeaconSummary( aABLData[i] );
					if( EMS_OK == hr )
					{
						++i;
					}

					pABObject->Release();
					pABObject = NULL;
				}

				*pulActualSize = i;
				if( EMS_ABL_NO_LOCATION_UPDATE == hr )
				{
					// it is not a failure, the last ABObject has no updates does not have an update.
					hr = EMS_OK;
				}

				if( m_bLoggingEnabled )
				{
					std::string szCSVStr;
					for( i = 0; i < *pulActualSize; i++ )
					{
						
						CEMSActiveBeacon::GetCSVString( &(aABLData[i]), szCSVStr );
						m_csvFOutputSummary.WriteText( szCSVStr.c_str() );
					}
				}
			}
			else
			{
				hr = EMS_ABL_MEM_OVERFLOW;
			}
			ms_mtxActiveBeacons.Leave();
		}
		catch( ... )
		{
			ms_mtxActiveBeacons.Leave();
			if( pABObject )
			{
				pABObject->Release();
				pABObject = NULL;
			}
			throw;
		}
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}


EMS_RESULT 
CEMSABLObjectImpl::GetBeaconLocations( const ULONG culCount,
									   ULONG *pulActualSize,
									   EMSLOCATE* aLocations )
{
	EMS_RESULT hr = EMS_OK;

	_ClearAgedOutBcns();

	if( pulActualSize && aLocations )
	{
		CEMSActiveBeacon* pABObject = NULL;
		try
		{
			ms_mtxActiveBeacons.Enter();

			ULONG i = 0;
			*pulActualSize = m_mapActiveBeacons.Count();
			if( *pulActualSize <= culCount )
			{
				m_mapActiveBeacons.MoveFirst();
				while( pABObject = m_mapActiveBeacons.GetNext() )
				{
					hr = pABObject->GetBeaconLocation( aLocations[i] );
					
					if( EMS_OK == hr )
					{
						++i;
					}
					
					pABObject->Release();
					pABObject = NULL;
				}

				*pulActualSize = i;
				if( EMS_ABL_NO_LOCATION_UPDATE == hr )
				{
					// it is not a failure, the last ABObject has no updates does not have an update.
					hr = EMS_OK;
				}

				if( m_bLoggingEnabled )
				{
					std::string szCSVStr;
					for( i = 0; i < *pulActualSize; i++ )
					{
						
						CEMSABLRawObject::GetCSVString( &(aLocations[i]), szCSVStr );
						m_csvFOutputLocations.WriteText( szCSVStr.c_str() );
					}
				}
			}
			else
			{
				hr = EMS_ABL_MEM_OVERFLOW;
			}
			ms_mtxActiveBeacons.Leave();
		}
		catch( ... )
		{
			ms_mtxActiveBeacons.Leave();
			if( pABObject )
			{
				pABObject->Release();
				pABObject = NULL;
			}
			throw;
		}
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}


EMS_RESULT 
CEMSABLObjectImpl::GetBeaconLocationEx( const INT64 ci64BeaconID,
									    EMSABLData* pABLData )
{
	EMS_RESULT hr = EMS_OK;

	if( pABLData )
	{
		CEMSActiveBeacon* pABObject = NULL;
		try
		{
			ms_mtxActiveBeacons.Enter();

			pABObject = m_mapActiveBeacons.Get( (INT64)ci64BeaconID );
			if( pABObject )
			{
				hr = pABObject->GetBeaconSummary( *pABLData );
				pABObject->Release();
				pABObject = NULL;
			}
			else
			{
				// no output the beacon is aged out
				hr = EMS_ABL_NO_LOCATION_UPDATE;
			}

			ms_mtxActiveBeacons.Leave();
		}
		catch( ... )
		{
			ms_mtxActiveBeacons.Leave();
			if( pABObject )
			{
				pABObject->Release();
				pABObject = NULL;
			}
			throw;
		}
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}


EMS_RESULT 
CEMSABLObjectImpl::GetBeaconLocation( const INT64 ci64BeaconID,
									  EMSLOCATE* pLocation )
{
	EMS_RESULT hr = EMS_OK;

	if( pLocation )
	{
		CEMSActiveBeacon* pABObject = NULL;
		try
		{
			ms_mtxActiveBeacons.Enter();

			pABObject = m_mapActiveBeacons.Get( (INT64)ci64BeaconID );
			if( pABObject )
			{
				hr = pABObject->GetBeaconLocation( *pLocation );
				pABObject->Release();
				pABObject = NULL;
			}
			else
			{
				// no output the beacon is aged out
				hr = EMS_ABL_NO_LOCATION_UPDATE;
			}

			ms_mtxActiveBeacons.Leave();
		}
		catch( ... )
		{
			ms_mtxActiveBeacons.Leave();
			if( pABObject )
			{
				pABObject->Release();
				pABObject = NULL;
			}
			throw;
		}
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}


EMS_RESULT 
CEMSABLObjectImpl::GetBeaconDataEx( const INT64 ci64BeaconID,
								    EMSABLData* pABLData,
									ULONG* pulCount,
									EMSABLRawData* aLocations )
{
	EMS_RESULT hr = EMS_OK;

	if( pABLData && pulCount && aLocations )
	{
		CEMSActiveBeacon* pABObject = NULL;
		try
		{
			ms_mtxActiveBeacons.Enter();

			ULONG i = 0;

			m_mapActiveBeacons.MoveFirst();
			while( pABObject = m_mapActiveBeacons.GetNext() )
			{
				if( pABObject->GetBeaconID() == ci64BeaconID )
				{
					hr = pABObject->GetBeaconDataEx( pABLData, pulCount, aLocations );
					pABObject->Release();
					pABObject = NULL;
					break;
				}
				else
				{
					pABObject->Release();
					pABObject = NULL;
				}
			}

			ms_mtxActiveBeacons.Leave();
		}
		catch( ... )
		{
			ms_mtxActiveBeacons.Leave();
			if( pABObject )
			{
				pABObject->Release();
				pABObject = NULL;
			}
			throw;
		}
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}


EMS_RESULT 
CEMSABLObjectImpl::GetBeaconData( const INT64 ci64BeaconID,
								  EMSLOCATE* pLocate,
								  ULONG* pulCount,
								  EMSLOCATE* aLocations )
{
	EMS_RESULT hr = EMS_OK;

	if( pLocate && pulCount && aLocations )
	{
		CEMSActiveBeacon* pABObject = NULL;
		try
		{
			ms_mtxActiveBeacons.Enter();

			ULONG i = 0;

			m_mapActiveBeacons.MoveFirst();
			while( pABObject = m_mapActiveBeacons.GetNext() )
			{
				if( pABObject->GetBeaconID() == ci64BeaconID )
				{
					hr = pABObject->GetBeaconData( pLocate, pulCount, aLocations );
					pABObject->Release();
					pABObject = NULL;
					break;
				}
				else
				{
					pABObject->Release();
					pABObject = NULL;
				}
			}

			ms_mtxActiveBeacons.Leave();
		}
		catch( ... )
		{
			ms_mtxActiveBeacons.Leave();
			if( pABObject )
			{
				pABObject->Release();
				pABObject = NULL;
			}
			throw;
		}
	}
	else
	{
		hr = EMS_BAD_PARAM;
	}

	return hr;
}


EMS_RESULT 
CEMSABLObjectImpl::GetABLRawDataEx( const INT64 ci64BeaconID,
								    ULONG culCount,
									ULONG* pulActualSize,
									EMSABLRawData* aRawLocations )
{
	EMS_RESULT hr = EMS_NOT_IMPLEMENTED;

	return hr;
}


EMS_RESULT 
CEMSABLObjectImpl::GetABLRawData( const INT64 ci64BeaconID,
								  ULONG culCount,
								  ULONG* pulActualSize,
								  EMSLOCATE* aLocations )
{
	EMS_RESULT hr = EMS_NOT_IMPLEMENTED;

	return hr;
}


EMS_RESULT 
CEMSABLObjectImpl::Reset()
{
	EMS_RESULT hr = EMS_OK;

	CEMSABLRawObject* pRawLocationObj = NULL;

	try
	{
		ms_mtxActiveBeacons.Enter();
		m_mapActiveBeacons.Clear();
		ms_mtxActiveBeacons.Leave();

		ms_mtxInUseRawLocations.Enter();
		m_lstInUseRawLocations.Clear();
		ms_mtxInUseRawLocations.Leave();

		ms_mtxEmptyRawLocations.Enter();
		m_lstEmptyRawLocations.Clear();
		
		for( ULONG i = 0; i < m_oABLProperties.GetMaxCapacity(); i++ )
		{
			pRawLocationObj = new CEMSABLRawObject();
			if( !pRawLocationObj )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			m_lstEmptyRawLocations.Add( pRawLocationObj );
			pRawLocationObj->Release();
			pRawLocationObj = NULL;
		}

		if( m_bLoggingEnabled && !m_szABLDir.empty() )
		{
			if ( !CreateDirectory( m_szABLDir.c_str(), 0 ) )
			{
				//error.
			}

			if( L'\\' != m_szABLDir[m_szABLDir.length() - 1] )
			{
				m_szABLDir += L'\\';
			}
			m_szABLDir += CEMSConversionUtil::ConvertToStringA( GetID() );
			m_szABLDir += L'\\';

			if ( !CreateDirectory( m_szABLDir.c_str(), 0 ) )
			{
				//error.
			}
			
			std::string szFileName;
			std::string szCSVStr;
			CEMSABLRawObject::GetLocateCSVHeaderString( szCSVStr );

			szFileName = m_szABLDir;
			szFileName += ms_szInputLocationsFileName;
			m_csvFInputLocations.OpenTextFile( szFileName.c_str(), "w" );
			m_csvFInputLocations.WriteText( szCSVStr.c_str() );

			szFileName = m_szABLDir;
			szFileName += ms_szOutputLocationsFileName;
			m_csvFOutputLocations.OpenTextFile( szFileName.c_str(), "w" );
			m_csvFOutputLocations.WriteText( szCSVStr.c_str() );

			szFileName = m_szABLDir;
			szFileName += ms_szOutputSummariesFileName;
			CEMSActiveBeacon::GetABLSmryCSVHeaderString( szCSVStr );
			m_csvFOutputSummary.OpenTextFile( szFileName.c_str(), "w" );
			m_csvFOutputSummary.WriteText( szCSVStr.c_str() );
		}

		ms_mtxEmptyRawLocations.Leave();
	}
	catch( ... )
	{
		ms_mtxActiveBeacons.Leave();
		ms_mtxEmptyRawLocations.Leave();
		ms_mtxInUseRawLocations.Leave();
		if( pRawLocationObj )
		{
			pRawLocationObj->Release();
			pRawLocationObj = NULL;
		}

		throw;
	}
	
	return hr;
}

bool
CEMSABLObjectImpl::_NoEmptyRawObject()
{
	bool bRet = false;
	try
	{
		ms_mtxEmptyRawLocations.Enter();
		if( 0 == m_lstEmptyRawLocations.Count() )
		{
			bRet = true;
		}
		ms_mtxEmptyRawLocations.Leave();
	}
	catch( ... )
	{
		ms_mtxEmptyRawLocations.Leave();
		throw;
	}
	return bRet;
}


EMS_RESULT 
CEMSABLObjectImpl::Serialize( IEMSSeqStream* pIEMSStream )
{
	EMS_RESULT hr = EMS_NOT_IMPLEMENTED;

	return hr;
}


EMS_RESULT 
CEMSABLObjectImpl::Deserialize( IEMSSeqStream* pIEMSStream )
{
	EMS_RESULT hr = EMS_NOT_IMPLEMENTED;

	return hr;
}
