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

#ifndef __ACTIVE_BEACON_H__
#define __ACTIVE_BEACON_H__

#pragma warning(disable : 4786)

#include "ablobject.h"
#include "logclient.h"
#include "AOBJBASE.H"
#include <locate.h>
#include "emserror.h"
#include "EMSABLRawObject.h"
#include "pointerlist.h"
#include "EMSTextFile.h"
#include "EMSBEACN.h"

//! @class CActiveBeacon
//! This class represents active beacon data records
//! of the ABL Core Module

class CEMSActiveBeacon :	public CApiObjBase  
{			
	public:
		CEMSActiveBeacon();
		CEMSActiveBeacon( const INT64 ci64beacon );
		~CEMSActiveBeacon();

		void Init( const char* cszWorkingDir );
		CEMSABLRawObject* FreeRawObj( ULONG ulMinLocatePerABL );

		void  GetAgedOutRawObjects( CEMSPointerList<CEMSABLRawObject>&  lstRawLocations );
		void  FreePurgedRawObjects( CEMSPointerList<CEMSABLRawObject>&  lstRawLocations );
		void  FreeAllRawObjects( CEMSPointerList<CEMSABLRawObject>&  lstRawLocations );

		INT64 GetBeaconID(){ return m_i64BeaconId;}

		EMS_RESULT GetBeaconSummary( EMSABLData& ablData );
		EMS_RESULT GetBeaconLocation( EMSLOCATE& emsLocate );

		void  SetBeaconID( const INT64 ci64BcnID ){ m_i64BeaconId = ci64BcnID;}

		EMS_RESULT PutRawLocationObject( CEMSABLRawObject* pRawObj );

		EMS_RESULT GetBeaconDataEx( EMSABLData* pABLData,
									ULONG* pulCount,
									EMSABLRawData* aLocations );

		EMS_RESULT GetBeaconData( EMSLOCATE* pSummary,
								  ULONG* pulCount,
								  EMSLOCATE* aLocations );

		void SetRadius( double dRadius ){ m_dRadius = dRadius;}
		void SetFloatRate( double dFloatRate ){ m_dFloatRate = dFloatRate;}
		void SetOrbDetErr( double dOrbDetError ){ m_dOrbDetError = dOrbDetError;}
		void SetSDEL( double dSDEL ){ m_dSDEL = dSDEL;}
		
		void SetAgeOutPeriod( double dAgeOutPeriod ){ m_dAgeOutPeriod = dAgeOutPeriod;}

		void SetForceUpdate( bool bForceUpdate ){ m_bForceUpdate = bForceUpdate; }
		void SetIgnoreConfRules( bool bIgnoreConfRules ){ m_bIgnoreConfRules = bIgnoreConfRules; }
		void SetMsgMaxInterval( double dMinutes ){ m_dMsgMaxInterval = dMinutes;}
		void SetSubstituteTimeWindow( double dMinutes ){ m_dMaxSubsPeriod = dMinutes;}
		void SetMaxSubstituteFSErrors( int iMaxErrors ){ m_iMaxSubstituteFSErrors = iMaxErrors;}
		void SetMaxSubstitutePDF1Errors( int iMaxErrors ){ m_iMaxSubstitutePDF1Errors = iMaxErrors;}
		void SetMaxSubstitutePDF2Errors( int iMaxErrors ){ m_iMaxSubstitutePDF2Errors = iMaxErrors;}
		void SetMinTotalSatsNum( int iMinTotalSatsNum ){ m_iMinTotalSatsNum = iMinTotalSatsNum;}
		void SetMinGEOSatsNum( int iMinGEOSatsNum ){ m_iMinGEOSatsNum = iMinGEOSatsNum;}
		void SetMinLEOSatsNum( int iMinLEOSatsNum ){ m_iMinLEOSatsNum = iMinLEOSatsNum;}
		void SetMinMEOSatsNum( int iMinMEOSatsNum ){ m_iMinMEOSatsNum = iMinMEOSatsNum;}
		void SetMinTimeBtwnBursts( double dMinutes ){ m_dMinTimeBtwnBursts = dMinutes;}
		void SetMaxTimeStdDev( double dMaxTimeStdDev ){ m_dMaxTimeStdDev = dMaxTimeStdDev;}
		void SetMaxFreqStdDev( double dMaxFreqStdDev ){ m_dMaxFreqStdDev = dMaxFreqStdDev;}
		void SetMaxHDOP( double dMaxHDOP ){ m_dMaxHDOP = dMaxHDOP;}
		void SetLcnProximityThreshold( double dLcnProximityThreshold ){ m_dLcnProximityThreshold = dLcnProximityThreshold;}

		void EnableLogging( bool bEnable = true ){ m_bLoggingEnabled = bEnable;}

		bool IsAged();

		static void GetCSVString( EMSABLData* pABLData, std::string& szCSVStr );
		static void GetABLSmryCSVHeaderString( std::string& szCSVHeader );

	protected:
		CEMSABLRawObject* _FindCentralLocation( CEMSPointerList<CEMSABLRawObject>&  lstRawLocations );
		void _FindBestCluster( CEMSPointerList<CEMSABLRawObject>&  lstRawLocations );
		
		void _SortCluster( CEMSPointerList<CEMSABLRawObject>&  lstRawLocations );
		void _RemoveDuplicates( CEMSPointerList<CEMSABLRawObject>&  lstRawLocations, CEMSABLRawObject* pCentralObject );

		void _ApplyKalmanFilter( CEMSABLRawObject* pABLRawObj );
		void _ApplyKalmanFilter( CEMSPointerList<CEMSABLRawObject>&  lstRawLocations );
		void _UpdateMergeID(  CEMSPointerList<CEMSABLRawObject>&  lstRawLocations );
		void _UpdateMergeLocateInfo(  CEMSPointerList<CEMSABLRawObject>&  lstRawLocations, CEMSABLRawObject* pCentralObject );
		void _UpdateMergeDetectInfo(  CEMSPointerList<CEMSABLRawObject>&  lstRawLocations );
		void _UpdateMergeBeaconInfo(  CEMSPointerList<CEMSABLRawObject>&  lstRawLocations );

		bool _UpdateBcnMsgData( CEMSABLRawObject* pRawLcn );
		bool _UpdateInputLcnData( CEMSABLRawObject* pRawLcn );
		bool _ValidateLocationData( CEMSABLRawObject* pRawLcn );
		bool _ValidateLocnSatellites( CEMSABLRawObject* pRawLcn );

		void _CalculateMajorMinorHeadingErrors();
		void _ResetSummaryProcessing();

		void _GetLocationDataFromSumary( EMSLOCATE& emsLocate );

		void _SetUpLogFiles();

		bool _HasUpdate();

		bool _HasBcnMsgEncodedLcn( const BYTE cMsg[] );

		EMS_RESULT _GetBeaconSummary( EMSABLData& ablData );

		void _LogCSVLcns( CEMSPointerList<CEMSABLRawObject>&  lstRawLocations, CEMSTextFile* pCSVFile );

		void _CheckRefBcnInfo();

		void _UpdateQualityFactors();
		void _UpdateMQF();
		void _UpdateLQF();

		int _GetMEOSatsCount();
		int _GetLEOSatsCount();
		int _GetGEOSatsCount();

		void _UpdateWaveFormID();

		bool _CheckBcnCorrection( const BYTE* acBcnMsg, int iSize );

	private:
		INT64            m_i64BeaconId;
		ULONG            m_ulHistoryID;
		ULONG            m_ulLastSatID;
		ULONG            m_ulLastLutID;
		ULONG            m_ulLastPassID;
		ULONG            m_ulBurstsCount;
		ULONG			 m_ulMsgCount;
		bool             m_bListIsDirty;
		bool             m_bNewBurstIn;
		bool             m_bLoggingEnabled;
		bool             m_bForceUpdate;
		bool             m_bIgnoreConfRules;
		double           m_dRadius;
		double           m_dFloatRate;
		double           m_dOrbDetError;
		double           m_dSDEL;
		double           m_dLastFrequency;
		double           m_dLastPower;
		EMSABLData  	 m_ABLData;

		EMSTIME          m_tmLastTCA;
		EMSTIME          m_timeLastData;
		EMSTIME          m_timeFirstData;
		EMSTIME          m_timeLastOutput;
		double			 m_dVLAT;
		double			 m_dVLONG;
		double			 m_dCLALO;
		double           m_dFreqBiasError;
		double           m_dFreq;

		double           m_dAgeOutPeriod; // in minutes.
		double           m_dMsgMaxInterval; // in minutes.
		double           m_dMaxSubsPeriod; // in minutes
		double           m_dMinTimeBtwnBursts; // in seconds
		double           m_dMaxTimeStdDev;
		double           m_dMaxFreqStdDev;
		double           m_dMaxHDOP;
		double           m_dLcnProximityThreshold;

		int              m_iMaxSubstituteFSErrors;
		int              m_iMaxSubstitutePDF1Errors;
		int              m_iMaxSubstitutePDF2Errors;
		int              m_iMinTotalSatsNum;
		int              m_iMinGEOSatsNum;
		int              m_iMinLEOSatsNum;
		int              m_iMinMEOSatsNum;

		CEMSTextFile     m_csvFAllInputLocations;
		CEMSTextFile     m_csvFInputLocations;
		CEMSTextFile     m_csvFBestCluster;
		CEMSTextFile     m_csvFOutputLocation;
		CEMSTextFile     m_csvFOutputSummary;
		CEMSTextFile     m_csvFExcludedLocations;

		std::string      m_szAllRawLcnsFileName;
		std::string      m_szCurrentRawLcnsFileName;
		std::string      m_szRawBestClusterFileName;
		std::string      m_szLocationFileName;
		std::string      m_szSummaryFileName;
		std::string      m_szExcludedLcnsFileName;
		std::string      m_szABLDir;

		BYTE             m_acMostRecentBcnMsg[EMSBEACONMSGLEN];
		EMSTIME          m_tmMostRecentMsg;
		int              m_iMostRecentMsgFSErrors;
		int              m_iMostRecentMsgPDF1Errors;
		int              m_iMostRecentMsgPDF2Errors;
		int              m_iMostRecentMsgNum;
		WORD             m_wType;
		WORD             m_wWaveFormID;

		bool                m_bIsRefBcn;
		bool                m_bCheckBcnCorrection;
		EMSREFBEACONDATAEX  m_RefBcnData;

		CEMSPointerList<CEMSABLRawObject>  m_lstRawLocations;
		CEMSPointerList<CEMSABLRawObject>  m_lstPurgedRawLocations;
		CEMSCriticalSection    ms_mtxRawObjecsts;

		std::list<ULONG> m_lstSATids;
		std::list<ULONG> m_lstLUTids;

		static const std::string   ms_szTimeFormat; 
};

#endif