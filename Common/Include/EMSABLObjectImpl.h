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


#ifndef __EMS_ABL_OBJECT_IMPL_H__
#define __EMS_ABL_OBJECT_IMPL_H__

#pragma warning(disable : 4786)

#include "aobjbase.h"
#include "ABLObject.h"
#include "emsablproperties.h"
#include "emsactivebeacon.h"
#include "PointerMap.h"

//! @class CEMSABLObjectImpl
//! Implementation of Active Beacon List Object. This class provides all operations
//! involved in building a list of active beacons based on certain configurations.
class CEMSABLObjectImpl : public CApiObjBase
{
public:
	CEMSABLObjectImpl();
	virtual ~CEMSABLObjectImpl();

	EMS_RESULT Init( const EMSABLProperties& cObjProperties );

	EMS_RESULT Init( const wchar_t* cwszXMLString );

	EMS_RESULT GetABLProperties( EMSABLProperties* pObjProperties );

	EMS_RESULT GetLuts( const ULONG culCount,
		                ULONG* pulActualSize, 
					    ULONG* aLutProperties );
						

	EMS_RESULT GetSats( const ULONG  culCount,
				        ULONG*  pulActualSize,
						ULONG* aSatProperties );

	EMS_RESULT GetBeacons( const ULONG  culCount,
		                   ULONG* pulActualSize,
						   INT64* aBeaconProperties );

	EMS_RESULT GetLocationTypes( const ULONG  culCount,
							     ULONG* pulActualSize,
					             EMSLOCATETYPE* aLocationProperties );

	EMS_RESULT GetCountryCodes( const ULONG  culCount,
							    ULONG* pulActualSize,
					            int* aCCProperies );

	EMS_RESULT GetProtocolTypes( const ULONG  culCount,
							     ULONG* pulActualSize,
					             int* aProtocolProperies );

	// To add data to the ABL object.
	EMS_RESULT PutData( const ULONG culNumOfRecords, 
	                    EMSLOCATE* caLocate );

    // Get ABL count
	EMS_RESULT GetBeaconCount( ULONG* pulCount );

    // Get ABL IDs
	EMS_RESULT GetBeaconIDs( const ULONG culCount, 
						     ULONG* pulActualSize,
						     INT64* aBeaconIDs );

    // Get ABL data records
	EMS_RESULT GetBeaconLocationsEx( const ULONG culCount,
								     ULONG *pulActualSize,
								     EMSABLData* aABLData );

    // Get ABL data records in location record format
	EMS_RESULT GetBeaconLocations( const ULONG culCount,
								   ULONG *pulActualSize,
								   EMSLOCATE* aLocations );

    // Get an active beacon data
	EMS_RESULT GetBeaconLocationEx( const INT64 ci64BeaconID, 
	                                EMSABLData* pABLData );

    // Get an active beacon data in location record format
	EMS_RESULT GetBeaconLocation( const INT64 ci64BeaconID, 
	                              EMSLOCATE* pLocation );

    // Get an active beacon data and array of raw data records
	EMS_RESULT GetBeaconDataEx( const INT64 ci64BeaconID, 
	                            EMSABLData* pABLData,
						        ULONG* pulCount, 
								EMSABLRawData* aLocations );

    // Get an active beacon data and array of raw data records in locate record format
	EMS_RESULT GetBeaconData( const INT64 ci64BeaconID,
	                          EMSLOCATE* ABLData,
							  ULONG* pulCount,
							  EMSLOCATE* aLocations );

    // Get raw + FLAG location records
	EMS_RESULT GetABLRawDataEx( const INT64 ci64BeaconID,
		                        ULONG culCount,
								ULONG* pulActualSize,
								EMSABLRawData* aRawLocations );

	// Get raw location records
	EMS_RESULT GetABLRawData( const INT64 ci64BeaconID,
		                      ULONG culCount,
							  ULONG* pulActualSize,
							  EMSLOCATE* aLocations );

	// Reset everything to initial state (keeps the config props)
	EMS_RESULT Reset();

	//Serialize - Deserialize 
	EMS_RESULT Serialize( IEMSSeqStream* pIEMSStream );

	EMS_RESULT Deserialize( IEMSSeqStream* pIEMSStream );
	
	ULONG GetID(){ return m_oABLProperties.GetABLID();}

protected:
	CEMSABLRawObject* _GetNextEmptyRawObj();

	void _SetRawObjInUse( CEMSABLRawObject* pRawObj );
	void _SetRawObjAsEmpty( CEMSABLRawObject* pRawObj );

	void _AddRawObjToInUseList( CEMSABLRawObject* pRawObj );
	void _AddRawObjToEmptyList( CEMSABLRawObject* pRawObj );

	void _RemoveRawObjFromInUse( CEMSABLRawObject* pRawObj );
	void _RemoveRawObjFromEmpty( CEMSABLRawObject* pRawObj );

	EMS_RESULT _PutRawObj( CEMSABLRawObject* pRawObj );

	ULONG _GetABCount();

	void _ClearAgedOutBcns();

	void _SetRawObjectsAsEmpty( CEMSPointerList<CEMSABLRawObject>& rlstRawObjs );

	bool _NoEmptyRawObject();

private:

	bool   m_bLoggingEnabled;
	bool   m_bAcceptCBC;
	CEMSABLProperties m_oABLProperties;
	std::string       m_szABLDir;
	
	CEMSPointerMap<INT64, CEMSActiveBeacon> m_mapActiveBeacons;

	CEMSPointerList<CEMSABLRawObject>  m_lstEmptyRawLocations;
	CEMSPointerList<CEMSABLRawObject>  m_lstInUseRawLocations;

	CEMSCriticalSection    ms_mtxActiveBeacons;
	CEMSCriticalSection    ms_mtxEmptyRawLocations;
	CEMSCriticalSection    ms_mtxInUseRawLocations;

	CEMSTextFile     m_csvFInputLocations;
	CEMSTextFile     m_csvFOutputLocations;
	CEMSTextFile     m_csvFOutputSummary;

	static const std::string   ms_szInputLocationsFileName;
	static const std::string   ms_szOutputLocationsFileName;
	static const std::string   ms_szOutputSummariesFileName;

	static const wchar_t* ms_cwszWorkingDir;
	static const wchar_t* ms_cwszAcceptCBC;
	static const wchar_t* ms_cwszLoggingEnabled;
};

#endif 
