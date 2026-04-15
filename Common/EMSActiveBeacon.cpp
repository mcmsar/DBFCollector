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

#include "emsactivebeacon.h"
#include "emsexcpt.h"
#include "ABLMsgs.h"
#include "emsclock.h"
#include "emsencod.h"
#include "convutility.h"
#include "CBeaconMessage.h"
#include <EMSStandardDeviation.h>
#include "EMSBEACON.h"
#include "CBcnMsgDecode.h"
#include "emscoord.h"


const std::string  CEMSActiveBeacon::ms_szTimeFormat = "%d/%d/%d %d:%d:%d.%d";

const int c_iDefaultMaxSubstituteFSErrors = 6;
const int c_iDefaultMaxSubstitutePDF1Errors = 4;
const int c_iDefaultMaxSubstitutePDF2Errors = 4;
const int c_iInvalidMsgFieldsErrors = -1;

const double c_dMaxBurstPeriod = 25.0;

CEMSActiveBeacon::CEMSActiveBeacon() :  CApiObjBase( TEXT("CEMSActiveBeacon") ),
										m_i64BeaconId(0),
										m_ulHistoryID(0),
										m_ulLastSatID(0),
										m_ulLastLutID(0),
										m_ulLastPassID(0),
										m_ulBurstsCount(0),
										m_ulMsgCount(0),
										m_bListIsDirty(true),
										m_bNewBurstIn(true),
										m_bLoggingEnabled(false),
										m_bForceUpdate(false),
										m_bIgnoreConfRules(false),
										m_dRadius(0.0),
										m_dFloatRate(0.0),
										m_dOrbDetError(0.0),
										m_dSDEL(1.0),
										m_dLastFrequency(0.0),
										m_dLastPower(0.0),
										m_dVLAT(0.0),
										m_dVLONG(0.0),
										m_dCLALO(0.0),
										m_dFreqBiasError(0.0),
										m_dFreq(0.0),
										m_dAgeOutPeriod(0.0),
										m_dMsgMaxInterval(0.0),
										m_dMinTimeBtwnBursts(0.0),
										m_dMaxTimeStdDev(0.0),
										m_dMaxFreqStdDev(0.0),
										m_dMaxHDOP(0.0),
										m_dLcnProximityThreshold(0.0),
										m_dMaxSubsPeriod(0.0),
										m_iMaxSubstituteFSErrors(c_iDefaultMaxSubstituteFSErrors),
										m_iMaxSubstitutePDF1Errors(c_iDefaultMaxSubstitutePDF1Errors),
										m_iMaxSubstitutePDF2Errors(c_iDefaultMaxSubstitutePDF2Errors),
										m_iMinTotalSatsNum(0),
										m_iMinGEOSatsNum(0),
										m_iMinLEOSatsNum(0),
										m_iMinMEOSatsNum(0),
										m_iMostRecentMsgFSErrors(c_iInvalidMsgFieldsErrors),
										m_iMostRecentMsgPDF1Errors(c_iInvalidMsgFieldsErrors),
										m_iMostRecentMsgPDF2Errors(c_iInvalidMsgFieldsErrors),
										m_iMostRecentMsgNum(c_iInvalidMsgFieldsErrors),
										m_wType(0),
										m_wWaveFormID(0),
										m_bIsRefBcn(false),
										m_bCheckBcnCorrection(false)
{
	memset( &m_ABLData, 0, sizeof( EMSABLData ) );
	memset( &m_tmLastTCA, 0, sizeof( EMSTIME ) );
	memset( &m_timeLastData, 0, sizeof(EMSTIME) );
	memset( &m_timeFirstData, 0, sizeof(EMSTIME) );
	memset( &m_timeLastOutput, 0, sizeof(EMSTIME) );
	memset( m_acMostRecentBcnMsg, 0, sizeof( m_acMostRecentBcnMsg ) );
	memset( &m_tmMostRecentMsg, 0, sizeof( EMSTIME ) );
	memset( &m_RefBcnData, 0, sizeof( EMSREFBEACONDATAEX ) );
}

CEMSActiveBeacon::CEMSActiveBeacon( const INT64 ci64beacon) : CApiObjBase( TEXT("CEMSActiveBeacon") ),
															  m_i64BeaconId(ci64beacon),
															  m_ulHistoryID(0),
															  m_ulLastSatID(0),
															  m_ulLastLutID(0),
															  m_ulLastPassID(0),
															  m_ulBurstsCount(0),
															  m_ulMsgCount(0),
															  m_bListIsDirty(true),
															  m_bNewBurstIn(true),
															  m_bLoggingEnabled(false),
															  m_bForceUpdate(false),
															  m_bIgnoreConfRules(false),
															  m_dRadius(0.0),
															  m_dFloatRate(0.0),
															  m_dOrbDetError(0.0),
															  m_dSDEL(1.0),
															  m_dLastFrequency(0.0),
															  m_dLastPower(0.0),
															  m_dVLAT(0.0),
															  m_dVLONG(0.0),
															  m_dCLALO(0.0),
															  m_dFreqBiasError(0.0),
															  m_dFreq(0.0),
															  m_dAgeOutPeriod(0.0),
															  m_dMsgMaxInterval(0.0),
															  m_dMaxSubsPeriod(0.0),
															  m_dMinTimeBtwnBursts(0.0),
    														  m_dMaxTimeStdDev(0.0),
															  m_dMaxFreqStdDev(0.0),
															  m_dMaxHDOP(0.0),
															  m_dLcnProximityThreshold(0.0),
															  m_iMaxSubstituteFSErrors(c_iDefaultMaxSubstituteFSErrors),
															  m_iMaxSubstitutePDF1Errors(c_iDefaultMaxSubstitutePDF1Errors),
															  m_iMaxSubstitutePDF2Errors(c_iDefaultMaxSubstitutePDF2Errors),
															  m_iMinTotalSatsNum(0),
															  m_iMinGEOSatsNum(0),
															  m_iMinLEOSatsNum(0),
															  m_iMinMEOSatsNum(0),
															  m_iMostRecentMsgFSErrors(c_iInvalidMsgFieldsErrors),
															  m_iMostRecentMsgPDF1Errors(c_iInvalidMsgFieldsErrors),
															  m_iMostRecentMsgPDF2Errors(c_iInvalidMsgFieldsErrors),
															  m_iMostRecentMsgNum(c_iInvalidMsgFieldsErrors),
															  m_wType(0),
															  m_wWaveFormID(0),
															  m_bIsRefBcn(false),
															  m_bCheckBcnCorrection(false)
{
	memset( &m_ABLData, 0, sizeof( EMSABLData ) );
	memset( &m_tmLastTCA, 0, sizeof( EMSTIME ) );
	memset( &m_timeLastData, 0, sizeof(EMSTIME) );
	memset( &m_timeFirstData, 0, sizeof(EMSTIME) );
	memset( &m_timeLastOutput, 0, sizeof(EMSTIME) );
	m_ABLData.Id.i64BeaconID = ci64beacon;
	memset( m_acMostRecentBcnMsg, 0, sizeof( m_acMostRecentBcnMsg ) );
	memset( &m_tmMostRecentMsg, 0, sizeof( EMSTIME ) );
	memset( &m_RefBcnData, 0, sizeof( EMSREFBEACONDATAEX ) );
	_CheckRefBcnInfo();
}

CEMSActiveBeacon::~CEMSActiveBeacon()
{
	m_csvFAllInputLocations.Close();
	m_csvFInputLocations.Close();
	m_csvFBestCluster.Close();
	m_csvFOutputLocation.Close();
	m_csvFOutputSummary.Close();
	m_csvFExcludedLocations.Close();
}

void
CEMSActiveBeacon::Init( const char* cszWorkingDir )
{
	try
	{
		ms_mtxRawObjecsts.Enter();
		
		m_bListIsDirty = true;
		m_bNewBurstIn = true;
			
		m_lstRawLocations.Clear();

		memset( &m_timeLastData, 0, sizeof(EMSTIME) );
		memset( &m_timeFirstData, 0, sizeof(EMSTIME) );
		memset( &m_timeLastOutput, 0, sizeof(EMSTIME) );

		if( cszWorkingDir && ( 0 < strlen( cszWorkingDir ) ) ) 
		{
			m_szABLDir = cszWorkingDir;
		}

		_SetUpLogFiles();

		ms_mtxRawObjecsts.Leave();
	}
	catch( ... )
	{
		ms_mtxRawObjecsts.Leave();
	}
}

void
CEMSActiveBeacon::_CheckRefBcnInfo()
{
	EMS_RESULT hr = EMS_OK;
	IEMSRefBeaconInfo* lpRefBeaconObj = NULL;
	// Get accesss to reference beacon information.
	hr = CoCreateInstance(CLSID_EMSRefBeaconInfo, 0, CLSCTX_ALL, 
						IID_IEMSRefBeaconInfo, (LPVOID*)&lpRefBeaconObj);

	if( EMS_OK == hr )
	{
		ULONG ulCount = 0;

		hr = lpRefBeaconObj->GetCount(&ulCount);

		if((hr == EMS_OK) && ulCount)
		{
			EMSREFBEACONDATAEX* lpRefBeaconData= new EMSREFBEACONDATAEX[ulCount];

			if(lpRefBeaconData)
			{
				memset(lpRefBeaconData, 0, sizeof(EMSREFBEACONDATAEX)*ulCount);

				for ( int i = 0; (i < (int)ulCount) && (hr == EMS_OK); i++ )
				{
					hr = lpRefBeaconObj->GetIndexedData(i, &lpRefBeaconData[i].i64BeaconID, 
														 &lpRefBeaconData[i].data );
					if ( hr == EMS_OK && (lpRefBeaconData[i].i64BeaconID == m_ABLData.Id.i64BeaconID) )
					{
						m_bIsRefBcn = true;
						memcpy( &m_RefBcnData, &lpRefBeaconData[i], sizeof( EMSREFBEACONDATAEX ) );
						break;
					}
				}
				delete []lpRefBeaconData;
				lpRefBeaconData = NULL;
			}
		}
	}

	if( lpRefBeaconObj )
	{
		lpRefBeaconObj->Release();
		lpRefBeaconObj = NULL;
	}
}

CEMSABLRawObject*
CEMSActiveBeacon::FreeRawObj( ULONG ulMinLocatePerABL )
{
	CEMSABLRawObject* pRawObject = NULL;
	CEMSABLRawObject* pOldestObject = NULL;
	
	try
	{
		ms_mtxRawObjecsts.Enter();
		
		if( m_lstRawLocations.Count() > ulMinLocatePerABL )
		{
			m_lstRawLocations.MoveFirst();
			while( pRawObject = m_lstRawLocations.GetNext() )
			{
				if( !pOldestObject )
				{
					pOldestObject = pRawObject;
				}
				else if( pRawObject->IsOlderThan( *pOldestObject ) )
				{
					pOldestObject->Release();
					pOldestObject = NULL;
					pOldestObject = pRawObject;
				}
				else
				{
					pRawObject->Release();
					pRawObject = NULL;
				}
			}
			
			if( pOldestObject )
			{
				m_lstRawLocations.MoveFirst();
				while( pRawObject = m_lstRawLocations.GetNext() )
				{
					if( pRawObject == pOldestObject )
					{
						m_lstRawLocations.RemoveCurrent();
						pRawObject->Release();
						pRawObject = NULL;
						break;
					}
					else
					{
						pRawObject->Release();
						pRawObject = NULL;
					}
				}
			}
		}

		ms_mtxRawObjecsts.Leave();
	}
	catch( ... )
	{
		ms_mtxRawObjecsts.Leave();

		if( pRawObject )
		{
			pRawObject->Release();
			pRawObject = NULL;
		}

		if( pOldestObject )
		{
			pOldestObject->Release();
			pOldestObject = NULL;
		}
	}

	if( pOldestObject && m_bLoggingEnabled )
	{
		std::string szCsvStr;
		pOldestObject->ToCSVString( szCsvStr );
		m_csvFExcludedLocations.WriteText( szCsvStr.c_str() );
	}

	return pOldestObject;
}

bool
CEMSActiveBeacon::IsAged()
{
	bool bRet = false;

	if( 0 != m_timeLastData.intTime )
	{
		CEMSTime timeCheck;

		timeCheck.SetTime( m_timeLastData );

		if( timeCheck.MinutesDifferent( CEMSSystemClock::GetTime() ) > m_dAgeOutPeriod )
		{
			bRet = true;
		}
	}

	return bRet;
}

EMS_RESULT
CEMSActiveBeacon::GetBeaconLocation( EMSLOCATE& emsLocate )
{
	EMS_RESULT hr = EMS_OK;

	if( _HasUpdate() )
	{
		hr = _GetBeaconSummary( m_ABLData );
		_GetLocationDataFromSumary( emsLocate );
		m_timeLastOutput = CEMSSystemClock::GetTime();
	}
	else
	{
		hr = EMS_ABL_NO_LOCATION_UPDATE;
	}

	return hr;
}

void
CEMSActiveBeacon::_GetLocationDataFromSumary( EMSLOCATE& emsLocate )
{
    emsLocate.wType = m_ABLData.Id.wType;

	memcpy( emsLocate.cSatIDs, m_ABLData.Id.acSatIDs, sizeof( emsLocate.cSatIDs ) );
	memcpy( emsLocate.cLutIDs, m_ABLData.Id.acLutIDs, sizeof( emsLocate.cLutIDs ) );
	emsLocate.ulSatPassID = m_ulLastPassID;
	emsLocate.i64BeaconID = m_ABLData.Id.i64BeaconID;

//...........emswllocate
    emsLocate.wlsSolution.location.degLatitude = m_ABLData.Locate.dLatitude;
    emsLocate.wlsSolution.location.degLongitude = m_ABLData.Locate.dLongitude;
    emsLocate.wlsSolution.location.fAltitude = m_ABLData.Locate.dAltitude;

    emsLocate.wlsSolution.dFrequency = (m_dFreq > 0.0) ? m_dFreq : m_ABLData.Beacon.dFrequency_Ave; 
    emsLocate.wlsSolution.fFreqDrift = m_ABLData.Locate.dHDOP;
    emsLocate.wlsSolution.wNumMsgs = m_ABLData.Detect.wNumMsgs;
    emsLocate.wlsSolution.wNumMsgsUsed = m_ABLData.Detect.wNumFOAMsgsUsed;
    emsLocate.wlsSolution.wNumBurstsUsed = m_ABLData.Detect.wNumBursts;
//    emsLocate.wlsSolution.wNumIterations = m_ABLData.Detect.;  //find this
    emsLocate.wlsSolution.fRadiusErrEllipse = m_ABLData.Locate.dRadiusErrEllipse;
    emsLocate.wlsSolution.fFreqBiasError = m_dFreqBiasError;
    emsLocate.wlsSolution.fMajorError = m_ABLData.Locate.dMajorError;
    emsLocate.wlsSolution.fMinorError = m_ABLData.Locate.dMinorError;
    emsLocate.wlsSolution.fHeading = m_ABLData.Locate.dHeading;
    emsLocate.wlsSolution.fRMS = m_ABLData.Locate.dFOANoise;
	emsLocate.wlsSolution.fTrend = m_ABLData.Locate.dTOANoise;
//	memset( emsLocate.wlsSolution.fCoVarianceMatrix, 0, sizeof( emsLocate.wlsSolution.fCoVarianceMatrix ) );  //find this

	emsLocate.wlsSolution.fCoVarianceMatrix[0] = m_ABLData.Beacon.dCNR_Ave;
	emsLocate.wlsSolution.fCoVarianceMatrix[1] = m_ABLData.Beacon.dCNR_Sigma;
	emsLocate.wlsSolution.fCoVarianceMatrix[2] = m_ABLData.Beacon.dFrequency_Ave;
	emsLocate.wlsSolution.fCoVarianceMatrix[3] = m_ABLData.Beacon.dFrequency_Sigma;
	emsLocate.wlsSolution.fCoVarianceMatrix[4] = m_ABLData.Beacon.dRepetitionRate_Ave;
	emsLocate.wlsSolution.fCoVarianceMatrix[5] = m_ABLData.Beacon.dRepetitionRate_Sigma;
	emsLocate.wlsSolution.fCoVarianceMatrix[6] = m_ABLData.Beacon.dRepetitionRate_Ave;
	emsLocate.wlsSolution.fCoVarianceMatrix[7] = m_ABLData.Beacon.dRepetitionRate_Sigma;
	emsLocate.wlsSolution.fCoVarianceMatrix[8] = m_ABLData.Id.wWaveFormID;

    emsLocate.timeTCA = m_tmLastTCA.intTime ? m_tmLastTCA: m_ABLData.Detect.timeDataEnd;
//    emsLocate.fCrossTrackAngle = 0;  //find this
//    emsLocate.wWindowFactor = 0;  //find this
	emsLocate.fConfidence = m_ABLData.Locate.dComputedQualityFactor;
    emsLocate.fProbability = m_ABLData.Locate.dProbability;
    emsLocate.fPower = (float)m_ABLData.Beacon.dCNR_Ave;
    emsLocate.timeFirstData = m_ABLData.Detect.timeDataStart;  //find this
    emsLocate.timeLastData = m_ABLData.Detect.timeDataEnd;  //find this

    memcpy( emsLocate.info.rec406.cBeaconMsg, m_ABLData.Id.acBeaconMsg, sizeof( emsLocate.info.rec406.cBeaconMsg ) );
    emsLocate.info.rec406.wBitErrorFrameSync = m_ABLData.Id.wBitErrorFS;
    emsLocate.info.rec406.wBitErrorField1 = m_ABLData.Id.wBitErrorField1;
    emsLocate.info.rec406.wBitErrorField2 = m_ABLData.Id.wBitErrorField2;
}

bool
CEMSActiveBeacon::_HasBcnMsgEncodedLcn( const BYTE cMsg[] )
{
	bool bHasEncodedLocation = false;
	double dLat, dLong;

	CBeaconMessage	oNewMsg( cMsg );
	CBcnMsgDecode	oDecode;
	oDecode.DecodeEx( oNewMsg );
	oDecode.GetEncodedLocation( bHasEncodedLocation, dLat, dLong );

	return bHasEncodedLocation;
}

bool 
CEMSActiveBeacon::_CheckBcnCorrection( const BYTE* acBcnMsg, int iSize )
{
	bool bCheckCorrection = false;

	if( EMSBEACONMSGLEN == iSize )
	{
		BYTE abCorrected[EMSBEACONMSGLEN];
		CBeaconMsg oBcnMsg( acBcnMsg );

		memset( abCorrected, 0, EMSBEACONMSGLEN );
		oBcnMsg.Get( abCorrected );

		if( memcmp( acBcnMsg, abCorrected, EMSBEACONMSGLEN ) )
		{
			bCheckCorrection = true;
		}
	}
	else
	{
		bCheckCorrection = true;
	}
	return bCheckCorrection;
}


//bool
//CEMSActiveBeacon::_UpdateBcnMsgData( CEMSABLRawObject* pRawLcn )
//{
//	bool bMsgChanged = false;
//	
//	if( pRawLcn )
//	{
//		if( (0 == m_tmMostRecentMsg.intTime) || (c_iInvalidMsgFieldsErrors == m_iMostRecentMsgFSErrors) )
//		{
//			// first message to get in.
//			BYTE abBcnMsg[EMSBEACONMSGLEN];
//			pRawLcn->GetBeaconMsg( abBcnMsg, sizeof(abBcnMsg) );
//
//			bMsgChanged = true;
//			m_bCheckBcnCorrection = _CheckBcnCorrection( abBcnMsg, EMSBEACONMSGLEN );
//		}
//		else
//		{
//			// compare
//			BYTE abBcnMsg[EMSBEACONMSGLEN];
//			pRawLcn->GetBeaconMsg( abBcnMsg, sizeof(abBcnMsg) );
//
//			m_bCheckBcnCorrection = _CheckBcnCorrection( abBcnMsg, EMSBEACONMSGLEN );
//
//			if( memcmp( abBcnMsg, m_acMostRecentBcnMsg, sizeof(m_acMostRecentBcnMsg) ) )
//			{
//				// they are different
//				CBeaconMsg oBcnMsg( abBcnMsg );
///*				int iFSErrors = oBcnMsg.CheckFSError();
//				int iPDF1Errors = oBcnMsg.getPDF1BitErrors();
//				int iPDF2Errors = oBcnMsg.getPDF2BitErrors();
//*/
//				int iFSErrors = pRawLcn->GetBitErrorFS();
//				int iPDF1Errors = pRawLcn->GetBitErrorF1();
//				int iPDF2Errors = pRawLcn->GetBitErrorF2();
//
//				bool bCheckNext = true;
//				bool bNewerMsg = true;
//				bool bNewMsgEncodedLcn = _HasBcnMsgEncodedLcn( abBcnMsg );
//				bool bCurrentMsgEncodedLcn = _HasBcnMsgEncodedLcn( m_acMostRecentBcnMsg );
//
//				
//				if( m_tmMostRecentMsg.intTime > pRawLcn->GetTimeLastData().intTime )
//				{
//					bNewerMsg = false;
//				}
//				else if( (m_tmMostRecentMsg.intTime == pRawLcn->GetTimeLastData().intTime) &&
//					     (m_iMostRecentMsgNum > pRawLcn->GetNumMsgs()) )
//				{
//					bNewerMsg = false;
//				}
//
//				if( (iFSErrors <= m_iMaxSubstituteFSErrors) && 
//					(m_iMostRecentMsgFSErrors > m_iMaxSubstituteFSErrors) )
//				{
//					bCheckNext = false;
//					bMsgChanged = true;
//				}
//				else if( (iFSErrors > m_iMaxSubstituteFSErrors) && 
//					(m_iMostRecentMsgFSErrors <= m_iMaxSubstituteFSErrors) )
//				{
//					bCheckNext = false;
//					bMsgChanged = false;
//				}
//				// else --> both are valid or both are invalid continue to test.
//
//				if( bCheckNext )
//				{
//					if( (iPDF1Errors <= m_iMaxSubstitutePDF1Errors) && 
//						(m_iMostRecentMsgPDF1Errors > m_iMaxSubstitutePDF1Errors) )
//					{
//						bCheckNext = false;
//						bMsgChanged = true;
//					}
//					else if( (iPDF1Errors > m_iMaxSubstitutePDF1Errors) && 
//						(m_iMostRecentMsgPDF1Errors <= m_iMaxSubstitutePDF1Errors) )
//					{
//						bCheckNext = false;
//						bMsgChanged = false;
//					}
//					// else --> both are valid or both are invalid continue to test.
//				}
//
//				if( bCheckNext )
//				{
//					if( (iPDF2Errors <= m_iMaxSubstitutePDF2Errors) && 
//						(m_iMostRecentMsgPDF2Errors > m_iMaxSubstitutePDF2Errors) )
//					{
//						bCheckNext = false;
//						bMsgChanged = true;
//					}
//					else if( (iPDF2Errors > m_iMaxSubstitutePDF2Errors) && 
//						(m_iMostRecentMsgPDF2Errors <= m_iMaxSubstitutePDF2Errors) )
//					{
//						bCheckNext = false;
//						bMsgChanged = false;
//					}
//					// else --> both are valid or both are invalid continue to test.
//				}
//
//				if( bCheckNext )
//				{
//					// both are either valid or invalid, check which one is newer
//					if( bNewerMsg )
//					{
//						bMsgChanged = true;
//					}
//					bCheckNext = false; // no more checking.
//				}
//
//				if( bMsgChanged )
//				{
//					// last thing to check, keep last valid encoded location beacon.
//					if( (iPDF1Errors <= m_iMaxSubstitutePDF1Errors) && 
//						(m_iMostRecentMsgPDF1Errors <= m_iMaxSubstitutePDF1Errors) )
//					{
//						// both are valid check the encoded lcn.
//						if( !bNewMsgEncodedLcn && bCurrentMsgEncodedLcn )
//						{
//							bMsgChanged = false;
//						}
//					}
//				}
//			}
//		}
//
//		if( bMsgChanged )
//		{
//			pRawLcn->GetBeaconMsg( m_acMostRecentBcnMsg, sizeof(m_acMostRecentBcnMsg) );
//
//			m_iMostRecentMsgFSErrors = pRawLcn->GetBitErrorFS();
//			m_iMostRecentMsgPDF1Errors = pRawLcn->GetBitErrorF1();
//			m_iMostRecentMsgPDF2Errors = pRawLcn->GetBitErrorF2();
//			m_iMostRecentMsgNum = pRawLcn->GetNumMsgs();
//		}
//	}
//	
//	if( m_tmMostRecentMsg.intTime < pRawLcn->GetTimeLastData().intTime )
//	{
//		m_tmMostRecentMsg = pRawLcn->GetTimeLastData();
//	}
//
//	return bMsgChanged;
//}


bool
CEMSActiveBeacon::_UpdateBcnMsgData( CEMSABLRawObject* pRawLcn )
{
	bool bMsgChanged = false;
	
	if( pRawLcn )
	{
		bMsgChanged = true;
		if( bMsgChanged )
		{
			pRawLcn->GetBeaconMsg( m_acMostRecentBcnMsg, sizeof(m_acMostRecentBcnMsg) );

			m_iMostRecentMsgFSErrors = pRawLcn->GetBitErrorFS();
			m_iMostRecentMsgPDF1Errors = pRawLcn->GetBitErrorF1();
			m_iMostRecentMsgPDF2Errors = pRawLcn->GetBitErrorF2();
			m_iMostRecentMsgNum = pRawLcn->GetNumMsgs();
		}
	
		if( m_tmMostRecentMsg.intTime < pRawLcn->GetTimeLastData().intTime )
		{
			m_tmMostRecentMsg = pRawLcn->GetTimeLastData();
		}
	}

	return bMsgChanged;
}

bool
CEMSActiveBeacon::_ValidateLocationData( CEMSABLRawObject* pRawLcn )
{
	bool bValid = false;
	
	if( pRawLcn )
	{
		if( !pRawLcn->IsDetectOnly() )
		{
			bValid = true;
			//if( (m_dMaxHDOP > 0.0) && (fabs(pRawLcn->GetHDOP()) > m_dMaxHDOP) )
			//{
			//	bValid = false;
			//}
			//else if( (m_dMaxTimeStdDev > 0.0) && (fabs(pRawLcn->GetTOANoise()) > m_dMaxTimeStdDev) )
			//{
			//	bValid = false;
			//}
			//else if( (m_dMaxFreqStdDev > 0.0) && (fabs(pRawLcn->GetFOANoise()) > m_dMaxFreqStdDev) )
			//{
			//	bValid = false;
			//}
			//else
			//{
			//	bValid = _ValidateLocnSatellites( pRawLcn );
			//}
		}
	}
	
	return bValid;
}

bool
CEMSActiveBeacon::_ValidateLocnSatellites( CEMSABLRawObject* pRawLcn )
{
	bool bValid = false;
	
	if( pRawLcn )
	{
		if( !pRawLcn->IsDetectOnly() )
		{
			int iMeoSats = _GetMEOSatsCount();
			int iLeoSats = _GetLEOSatsCount();
			int iGeoSats = _GetGEOSatsCount();

			if( iMeoSats < m_iMinMEOSatsNum )
			{
				bValid = false;
			}
			else if( iLeoSats < m_iMinLEOSatsNum )
			{
				bValid = false;
			}
			else if( iGeoSats < m_iMinGEOSatsNum )
			{
				bValid = false;
			}
			else if( (iMeoSats + iLeoSats + iGeoSats) < m_iMinTotalSatsNum )
			{
				bValid = false;
			}
			else
			{
				bValid = true;
			}
		}
	}

	return bValid;
}


bool
CEMSActiveBeacon::_UpdateInputLcnData( CEMSABLRawObject* pRawLcn )
{
	bool bRet = true; // for now always true until we figure out more details.
	// TO DO
	return bRet;
}

EMS_RESULT 
CEMSActiveBeacon::PutRawLocationObject( CEMSABLRawObject* pRawObj )
{
	EMS_RESULT hr = EMS_OK;
	
	if( pRawObj )
	{
		try
		{
			ms_mtxRawObjecsts.Enter();

			m_ulMsgCount++;

			m_wType = pRawObj->GetLocationType();

			pRawObj->SetProbability( 0.5 );

			m_wWaveFormID = pRawObj->GetWaveFormID();

			bool bValidLcn = _ValidateLocationData( pRawObj );
			bool bMsgNewMsg = _UpdateBcnMsgData( pRawObj );
			pRawObj->GetSATIDs( m_lstSATids );
			pRawObj->GetLUTIDs( m_lstLUTids );

			if( bValidLcn )
			{
				_UpdateInputLcnData( pRawObj );
				m_lstRawLocations.Add( pRawObj );
				m_bListIsDirty = true;
			}
			else
			{
				// we will use it to update the message only then purge it.
				m_dLastFrequency = pRawObj->GetFrequency();
				m_dLastPower = pRawObj->GetCNR();
				m_lstPurgedRawLocations.Add( pRawObj );
			}
			
			if( m_dMsgMaxInterval > 0.0 )
			{
				CEMSTime timeCheck;

				timeCheck.SetTime( m_timeLastOutput );

				if( timeCheck.MinutesDifferent( CEMSSystemClock::GetTime() ) > m_dMsgMaxInterval )
				{
					if( m_timeLastData.intTime < pRawObj->GetTimeLastData().intTime )
					{
						m_bNewBurstIn = true;
					}
					//m_ulBurstsCount++;
				}
				else if( bMsgNewMsg )
				{
					m_bNewBurstIn = true;
					//m_ulBurstsCount++;
				}
			}
			else
			{
				m_bNewBurstIn = true;
				//m_ulBurstsCount++;
			}
			
			m_ulLastSatID = pRawObj->GetFirstSATID();
			m_ulLastLutID = pRawObj->GetFirstLUTID();
			m_ulLastPassID = pRawObj->GetPassID();

			// update the bursts count
			{
				CEMSTime timeCheck;

				timeCheck.SetTime( m_timeLastData );

				if( timeCheck.SecondsDifferent( pRawObj->GetTimeLastData() ) > c_dMaxBurstPeriod )
				{
					m_ulBurstsCount++;
				}
			}
			
			if( m_timeLastData.intTime < pRawObj->GetTimeLastData().intTime )
			{
				m_timeLastData = pRawObj->GetTimeLastData();
			}
			if( (m_timeFirstData.intTime == 0) || 
				(m_timeFirstData.intTime > pRawObj->GetTimeFirstData().intTime) )
			{
				m_timeFirstData = pRawObj->GetTimeFirstData();
			}

			if( m_bLoggingEnabled )
			{
				std::string szCsvStr;
				pRawObj->ToCSVString( szCsvStr );
				m_csvFAllInputLocations.WriteText( szCsvStr.c_str() );
			}

			ms_mtxRawObjecsts.Leave();
		}
		catch( ... )
		{
			ms_mtxRawObjecsts.Leave();
			throw;
		}
	}

	return hr;
}

void 
CEMSActiveBeacon::_ResetSummaryProcessing()
{
	memset( &m_ABLData, 0, sizeof(EMSABLData) );
	memset( &m_tmLastTCA, 0, sizeof(m_tmLastTCA) );
	m_dVLAT = 0.0;
	m_dVLONG = 0.0;
	m_dCLALO = 0.0;
}

bool
CEMSActiveBeacon::_HasUpdate( )
{
	bool bOutput = false;

	if( m_bNewBurstIn )
	{
		bOutput = true;
	}
	else if( m_bForceUpdate )
	{
/*		// Ticket# 37050, do not send an update if no more incoming bursts.
		// check the last time outputed...
		CEMSTime timeCheck;

		timeCheck.SetTime( m_timeLastOutput );

		if( timeCheck.MinutesDifferent( CEMSSystemClock::GetTime() ) >  )
		{
			bOutput = true;
		}*/
	}

	if( !bOutput && m_bListIsDirty )
	{
		// check the last time outputed...
		CEMSTime timeCheck;

		timeCheck.SetTime( m_timeLastOutput );

		if( timeCheck.MinutesDifferent( CEMSSystemClock::GetTime() ) > m_dMsgMaxInterval )
		{
			bOutput = true;
		}
	}

	return bOutput;
}



EMS_RESULT
CEMSActiveBeacon::GetBeaconSummary( EMSABLData& ablData )
{
	EMS_RESULT hr = EMS_OK;

	if( _HasUpdate() )
	{
		hr = _GetBeaconSummary( ablData );
		m_timeLastOutput = CEMSSystemClock::GetTime();
	}
	else
	{
		hr = EMS_ABL_NO_LOCATION_UPDATE;
	}

	return hr;
}


EMS_RESULT
CEMSActiveBeacon::_GetBeaconSummary( EMSABLData& ablData )
{
	EMS_RESULT hr = EMS_OK;
	CEMSABLRawObject* pCentralLocationObj = NULL;

	try
	{
		ms_mtxRawObjecsts.Enter();

		if( m_bListIsDirty || m_bNewBurstIn )
		{
			CEMSPointerList<CEMSABLRawObject> lstBestCluster = m_lstRawLocations;

			_ResetSummaryProcessing();
			
			_LogCSVLcns( m_lstRawLocations, &m_csvFInputLocations );

//			_FindBestCluster( lstBestCluster );

			if( 0 < lstBestCluster.Count() )
			{
				pCentralLocationObj = _FindCentralLocation( lstBestCluster );
				
				if( pCentralLocationObj )
				{
					pCentralLocationObj->AddRef();

					 if( m_bLoggingEnabled )
					 {
						 std::string    szCSVStr;
						 pCentralLocationObj->ToCSVString( szCSVStr );
						 m_csvFOutputLocation.WriteText( szCSVStr.c_str() );
					 }
				}

				//_SortCluster( lstBestCluster );

				//_RemoveDuplicates( lstBestCluster, pCentralLocationObj );

				_LogCSVLcns( lstBestCluster, &m_csvFBestCluster );

				_ApplyKalmanFilter( lstBestCluster );

				_UpdateMergeLocateInfo( lstBestCluster, pCentralLocationObj );
			}

			_UpdateMergeID( lstBestCluster );

			_UpdateMergeDetectInfo( lstBestCluster );

			_UpdateMergeBeaconInfo( lstBestCluster );

			if( EMSLOCTYPE_406_SARR_DETECT == m_ABLData.Id.wType )
			{
				m_ABLData.Id.wType = EMSLOCTYPE_GEO_SARR_UNCONFIRMED;
			}

			// Mark it as generated by the ABL.
			m_ABLData.Id.wType |= EMSLOCTYPE_ABGEN;

			_UpdateWaveFormID();

			_UpdateQualityFactors();

			if( m_bLoggingEnabled )
			{
				EMSLOCATE    emsLocate;
				std::string  szCSVStr;

				memset( &emsLocate, 0, sizeof( EMSLOCATE ) );
				_GetLocationDataFromSumary( emsLocate );

				CEMSABLRawObject::GetCSVString( &emsLocate, szCSVStr );
				m_csvFOutputLocation.WriteText( szCSVStr.c_str() );

				CEMSActiveBeacon::GetCSVString( &m_ABLData, szCSVStr );
				m_csvFOutputSummary.WriteText( szCSVStr.c_str() );
			}

			m_bListIsDirty = false;
			m_bNewBurstIn = false;

			if( pCentralLocationObj )
			{
				pCentralLocationObj->Release();
				pCentralLocationObj = NULL;
			}
			
			_SetUpLogFiles();
		}

		memcpy( &ablData, &m_ABLData, sizeof(EMSABLData) );

		ms_mtxRawObjecsts.Leave();
	}
	catch( ... )
	{
		ms_mtxRawObjecsts.Leave();
		if( pCentralLocationObj )
		{
			pCentralLocationObj->Release();
			pCentralLocationObj = NULL;
		}

		throw;
	}

	return hr;
}

void 
CEMSActiveBeacon::_ApplyKalmanFilter( CEMSPointerList<CEMSABLRawObject>&  lstRawLocations )
{
	if( 0 < lstRawLocations.Count() )
	{
		CEMSABLRawObject* pRawObj = NULL;
		try
		{
			lstRawLocations.MoveFirst();
			pRawObj = lstRawLocations.GetNext();
			if( pRawObj )
			{
				pRawObj->CalculateLatLongDeltaSigma( m_dOrbDetError, m_dSDEL );

				m_tmLastTCA = pRawObj->GetTCA();
				m_dVLAT = pRawObj->GetVLat();
				m_dVLONG = pRawObj->GetVLong();
				m_dCLALO = pRawObj->GetCLALO();
				m_dFreqBiasError = pRawObj->GetFreqBiasError();
				m_dFreq = pRawObj->GetFrequency();

				EMSLOCATION emsLocn = pRawObj->GetLocation();
				m_ABLData.Locate.dLatitude = emsLocn.degLatitude;
				m_ABLData.Locate.dLongitude = emsLocn.degLongitude;
				m_ABLData.Locate.dAltitude = emsLocn.fAltitude;
				_CalculateMajorMinorHeadingErrors();

				pRawObj->Release();
				pRawObj = NULL;

				while( pRawObj = lstRawLocations.GetNext() )
				{
					_ApplyKalmanFilter( pRawObj );
					pRawObj->Release();
					pRawObj = NULL;
				}
			}
		}
		catch( ... )
		{
			if( pRawObj )
			{
				pRawObj->Release();
				pRawObj = NULL;
			}
			throw;
		}
	}
}


void 
CEMSActiveBeacon::_ApplyKalmanFilter( CEMSABLRawObject* pABLRawObj )
{
	if( pABLRawObj )
	{
		EMSLOCATION newLocn = pABLRawObj->GetLocation();

		pABLRawObj->CalculateLatLongDeltaSigma( m_dOrbDetError, m_dSDEL );

		double dSVLAT = 0.001;
		double dSVLNG = 0.001;
		double dSCORR = m_dCLALO;

		double dMVLAT = 0.001;
		double dMVLNG = 0.001;
		double dMCORR = pABLRawObj->GetCLALO();

		if( m_dVLAT > 0.001 )
		{
			dSVLAT = m_dVLAT;
		}

		if( m_dVLONG > 0.001 )
		{
			dSVLNG = m_dVLONG;
		}

		if( pABLRawObj->GetVLat() > 0.001 )
		{
			dMVLAT = pABLRawObj->GetVLat();
		}

		if( pABLRawObj->GetVLong() > 0.001 )
		{
			dMVLNG = pABLRawObj->GetVLong();
		}

		INT64 DT = m_tmLastTCA.intTime - pABLRawObj->GetTCA().intTime;

		//convert DT to hours
		double DThrs = (double) DT * 1.0e-9 /3600.0; 
		double dSig = ( m_dFloatRate * DThrs ) * ( m_dFloatRate * DT );

		dSig = 0.0; // Beacon does not move very far in 20 minutes

		if( DT > 0.0 )
		{
			dMVLAT = sqrt( (double) ( (dMVLAT*dMVLAT) + dSig ) );
			dMVLNG = sqrt( (double) ( (dMVLNG*dMVLNG) + dSig ) );
		}
		else
		{
			dSVLAT = sqrt( (double) ( (dSVLAT*dSVLAT) + dSig ) );
			dSVLNG = sqrt( (double) ( (dSVLNG*dSVLNG) + dSig ) );
		}

		// Set up the covariance matrices, E and W, for the matching and input lat/long solutions (respectively).

		double dE11 = dMVLAT * dMVLAT;
		double dE22 = dMVLNG * dMVLNG;
		double dE12 = dMCORR * dMVLAT * dMVLNG;
		double dE21 = dE12;

		double dW11 = dSVLAT * dSVLAT;
		double dW22 = dSVLNG * dSVLNG;
		double dW12 = dSCORR * dSVLAT * dSVLNG;
		double dW21 = dW12;

		// Calculate, Q = Inv [W + E]
		double DETWE = (dW11 + dE11 ) * (dW22 + dE22) - (dW12 + dE12) * (dW21 + dE21);

		double dQ11 = 0.0;
		double dQ22 = 0.0;
		double dQ12 = 0.0;
		double dQ21 = 0.0;

		if( DETWE != 0.0 )
		{
			dQ11 = (dW22 + dE22)/DETWE;
			dQ22 = (dW11 + dE11)/DETWE;
			dQ12 = -(dW12 + dE12)/DETWE;
			dQ21 = dQ12;
		}

		// Calculate the Kalman gain matrix, K = [E] * [Q]
		double dK11 = (dE11 * dQ11) + (dE12 * dQ21);
		double dK12 = (dE11 * dQ12) + (dE12 * dQ22);
		double dK21 = (dE21 * dQ11) + (dE22 * dQ21);
		double dK22 = (dE21 * dQ12) + (dE22 * dQ22);

		// Calculate the Lat/Long, x = x + [K] * [XN - X]
		double dDIS1 = m_ABLData.Locate.dLatitude - newLocn.degLatitude;
		double dDIS2 = m_ABLData.Locate.dLongitude - newLocn.degLongitude;
		
		if(dDIS2 > 180.0)
		{
			 dDIS2 -= 360.0;
		}
		else if( dDIS2 < -180.0)
		{
			dDIS2 += 360.0;
		}

		newLocn.degLatitude = newLocn.degLatitude + (dDIS1 * dK11) + (dDIS2 * dK12);
		newLocn.degLongitude = newLocn.degLongitude + (dDIS1 * dK21) + (dDIS2 * dK22);

		//Update the lat/long covariance matrix, W = [I - K] . [E]

		dW11 = ( (1.0 - dK11) * dE11 ) - (dK12 * dE21);
		dW12 = ( (1.0 - dK11) * dE12 ) - (dK12 * dE22);
		dW21 = ( (1.0 - dK22) * dE21 ) - (dK21 * dE11);
		dW22 = ( (1.0 - dK22) * dE22 ) - (dK21 * dE12);

		// W should be symmetric but just in case
		dW12 = (dW12 + dW21 ) / 2.0;

		// Calculate the variances of the lat/long and their normalized
		// covariance. 

		double dABSw11 = dW11;
		if( dABSw11 < 0.0 )
		{
			dABSw11 *= -1.0;
		}

		double dABSw22 = dW22;
		if( dABSw22 < 0.0 )
		{
			dABSw22 *= -1.0;
		}

		dMVLAT = sqrt( dABSw11 );
		dMVLNG = sqrt( dABSw22 );

		if( (dMVLAT == 0.0) && (dMVLNG == 0.0) )
		{
			dMCORR = 0.0;
		}
		else
		{
			if( (dMVLAT == 0.0) || (dMVLNG == 0.0) )
			{
				double dABSw12 = dW12;
				if( dABSw12 < 0.0 )
				{
					dABSw12 *= -1;
				}

				dMCORR = (0.9 * dW12) / dABSw12;
			}
			else
			{
				dMCORR = dW12 / dMVLAT / dMVLNG;
			}
		}

		// Calculate Frequency Bias Estimate and Set up covariance [E], [W]  --> We disabled Freq calculations

//		dE11 = pABLRawObj->GetFreqBiasError() * pABLRawObj->GetFreqBiasError();

//		dW11 = m_dFreqBiasError * m_dFreqBiasError;

		// Compute Kalman gain, K = [E] / [E+W]
//		double dTMP1 = dE11 + dW11;
		
/*		if( dTMP1 == 0.0 )
		{
			dQ11 = 0.0;
		}
		else
		{
			dQ11 = 1.0 / (dE11 + dW11);
		}

*/
//		dK11 = dE11 * dQ11;

		// Update frequency bias, X = X + [K] . [XN - X] 
		// and its covariance,   W = [I - K] . [E]

//		dW11 = (1.0 - dK11) * dE11;
//		m_dFreq = pABLRawObj->GetFrequency() + dK11 * ( m_dFreq - pABLRawObj->GetFrequency() );
		
//		double dSqrtABSW11 = dW11;
//		if( dSqrtABSW11 < 0.0 )
//		{
//			dSqrtABSW11 *= -1.0;
//		}

//		dSqrtABSW11 = sqrt( dSqrtABSW11 );

//		dSqrtABSW11 = 1.0;
//		if( dSqrtABSW11 > 1.0 )
//		{
//			m_dFreqBiasError = dSqrtABSW11;
//		}

		// Store new SDs and CORR
		m_dVLAT = dMVLAT;
		if( dMVLAT < 0.001 )
		{
			dMVLAT = 0.001;
		}

		m_dVLONG = dMVLNG;
		if( m_dVLONG < 0.001 )
		{
			m_dVLONG = 0.001;
		}

		double dABSmcorr = dMCORR;
		if( dABSmcorr < 0.0 )
		{
			dABSmcorr *= -1;
		}

		double dMinCorr = 1.0;
		if( dABSmcorr < dMinCorr )
		{
			dMinCorr = dABSmcorr;
		}

		if( dABSmcorr != 0 )
		{
			m_dCLALO = dMinCorr * ( 1.0 * dMCORR / dABSmcorr );
		}
		else
		{
			m_dCLALO = dMinCorr * 1.0;
		}

		// Check latitude -90..90 and longitude -180..180
		if( newLocn.degLatitude > 90.0 )
		{
			newLocn.degLatitude -=  2*(newLocn.degLatitude - 90);
			newLocn.degLongitude += 180;
		}
		if( newLocn.degLatitude < -90.0 )
		{
			newLocn.degLatitude -=  2*(newLocn.degLatitude + 90);
			newLocn.degLongitude += 180;
		}
		if( newLocn.degLongitude > 180.0 )
		{
			newLocn.degLongitude -= 360;
		}
		if( newLocn.degLongitude < -180.0 )
		{
			newLocn.degLongitude += 360;
		}

		//if( (newLocn.degLatitude > 90.0) || (newLocn.degLatitude < -90.0) )
		//{
		//	newLocn.degLatitude = (-1 * newLocn.degLatitude) + ( 2 * fmod(newLocn.degLatitude, 90.0) );
		//}

		//if( (newLocn.degLongitude > 180.0) || (newLocn.degLongitude < -180.0) )
		//{
		//	newLocn.degLongitude = (-1 * newLocn.degLongitude) + ( 2 * fmod(newLocn.degLongitude, 180.0) );
		//}

		m_ABLData.Locate.dLatitude = newLocn.degLatitude;
		m_ABLData.Locate.dLongitude = newLocn.degLongitude;
		m_ABLData.Locate.dAltitude = newLocn.fAltitude;
		_CalculateMajorMinorHeadingErrors();
	}
}

void
CEMSActiveBeacon::_CalculateMajorMinorHeadingErrors()
{
	if( 0.0 ==  m_dSDEL )
	{
		m_dSDEL = 1.0;
	}
	// Calculate the standard deviations and normalized covariance 
	// for EAST and NORTH at the ELT lat / long.
	double dVE = c_dEarthKmRadius * COSD(m_ABLData.Locate.dLatitude) * (c_dPI * m_dVLONG / 180.0);
	double dVN = c_dEarthKmRadius * (c_dPI * m_dVLAT / 180.0);
	double dCEN = m_dCLALO;

    double dVE2 = dVE * dVE;
	double dVN2 = dVN * dVN;

	double dVE_VN_CEN = dVE * dVN * dCEN;
 
	// Calculate the heading of the error ellipse and its major and 
	// minor axes.
	if( (dVE_VN_CEN != 0.0) || (dVN2 != dVE2) )
	{
		m_ABLData.Locate.dHeading = 0.5 * ATAN2D( (2.0 * dVE_VN_CEN), (dVN2 - dVE2) ) ;
	}
	else
	{
		m_ABLData.Locate.dHeading = 0.0;
	}

	double dSH = SIND( m_ABLData.Locate.dHeading );
	double dCH = COSD( m_ABLData.Locate.dHeading );

	double dABSValue = (dVN * dCH) * (dVN * dCH) + (dVE * dSH) * (dVE * dSH) + (2.0 * dVE_VN_CEN * dSH* dCH);
	if( dABSValue < 0.0 )
	{
		dABSValue *= -1.0;
	}

	m_ABLData.Locate.dMajorError = sqrt( dABSValue ) * m_dSDEL; //Error ellipes scale factor

	dABSValue = (dVE * dCH) * (dVE * dCH) + (dVN * dSH) * (dVN * dSH) - (2.0 * dVE_VN_CEN * dSH * dCH);
	if( dABSValue < 0.0 )
	{
		dABSValue *= -1.0;
	}

	m_ABLData.Locate.dMinorError = sqrt( dABSValue ) * m_dSDEL; //Error ellipes scale factor

	m_ABLData.Locate.dMajorError = sqrt( (m_ABLData.Locate.dMajorError * m_ABLData.Locate.dMajorError) + (m_dOrbDetError * m_dOrbDetError) );
	m_ABLData.Locate.dMinorError = sqrt( (m_ABLData.Locate.dMinorError * m_ABLData.Locate.dMinorError) + (m_dOrbDetError * m_dOrbDetError) );

	if( m_ABLData.Locate.dMajorError < m_ABLData.Locate.dMinorError )
	{
		double dTemp = m_ABLData.Locate.dMinorError;
		m_ABLData.Locate.dMinorError = m_ABLData.Locate.dMajorError;
		m_ABLData.Locate.dMajorError = dTemp;

		m_ABLData.Locate.dHeading += 90.0;
	}
    
	if( m_ABLData.Locate.dHeading < 0.0 )
	{
		m_ABLData.Locate.dHeading += 180.0;
	}
}


void 
CEMSActiveBeacon::_LogCSVLcns( CEMSPointerList<CEMSABLRawObject>&  lstRawLocations, CEMSTextFile* pCSVFile )
{
	if( pCSVFile && (0 < lstRawLocations.Count()) )
	{
		CEMSABLRawObject* pRawObj = NULL;
		try
		{
			std::string szCSVStr;
			lstRawLocations.MoveFirst();
			while( pRawObj = lstRawLocations.GetNext() )
			{
				pRawObj->ToCSVString( szCSVStr );
				pCSVFile->WriteText( szCSVStr.c_str() );

				pRawObj->Release();
				pRawObj = NULL;
			}
		}
		catch( ... )
		{
			if( pRawObj )
			{
				pRawObj->Release();
				pRawObj = NULL;
			}
			throw;
		}
	}
}


void 
CEMSActiveBeacon::_UpdateMergeID(  CEMSPointerList<CEMSABLRawObject>&  lstRawLocations  )
{
	// haven't been populated yet
	int iLeastBcnMsgErrors = -1;
	std::list<ULONG>::iterator iterSatIds;
	std::list<ULONG>::iterator iterLutIds;

	m_ABLData.Id.timestamp = CEMSSystemClock::GetTime();

	// to make sure the last satID is the first in the list (SIT Msg issue).
	if( m_ulLastSatID )
	{
		m_lstSATids.remove( m_ulLastSatID );
		m_lstSATids.push_front( m_ulLastSatID );
	}

	// to make sure the last LutID is the first in the list (SIT Msg issue).
	if( m_ulLastLutID )
	{
		m_lstLUTids.remove( m_ulLastLutID );
		m_lstLUTids.push_front( m_ulLastLutID );
	}

	CEMSEncodedSatID::Reset( (EMSENCODEDSATID*)&m_ABLData.Id.acSatIDs );
	for( iterSatIds = m_lstSATids.begin(); iterSatIds != m_lstSATids.end(); iterSatIds++ )
	{
		CEMSEncodedSatID::Set( (EMSENCODEDSATID*)&m_ABLData.Id.acSatIDs, *iterSatIds );
	}

	for( iterLutIds = m_lstLUTids.begin(); iterLutIds != m_lstLUTids.end(); iterLutIds++ )
	{
		CEMSEncodedLutID::Set( (EMSENCODEDLUTID*)&m_ABLData.Id.acLutIDs, *iterLutIds );
	}

	CBeaconMsg oSumBcnMsg( m_acMostRecentBcnMsg );
//	memcpy( m_ABLData.Id.acBeaconMsg, m_acMostRecentBcnMsg, sizeof( m_ABLData.Id.acBeaconMsg ) );
	oSumBcnMsg.Get( m_ABLData.Id.acBeaconMsg );
	m_ABLData.Id.wBitErrorFS = m_iMostRecentMsgFSErrors;
	m_ABLData.Id.wBitErrorField1 = m_iMostRecentMsgPDF1Errors;
	m_ABLData.Id.wBitErrorField2 = m_iMostRecentMsgPDF2Errors;

	CBeaconMsg oBcnMsg( m_acMostRecentBcnMsg );
	m_ABLData.Id.i64BeaconID = (INT64)oBcnMsg.getBeaconID();
	m_ABLData.Id.wCountryCode = oBcnMsg.getCountryCode();
	m_ABLData.Id.wProtocolFlag = oBcnMsg.getProtocolFlag();
	m_ABLData.Id.wProtocolCode = oBcnMsg.getProtocolCode();

	{
		bool bHasEncodedLocation = false;
		CBeaconMessage	oNewMsg( m_acMostRecentBcnMsg );
		CBcnMsgDecode	oDecode;
		oDecode.DecodeEx( oNewMsg );
		oDecode.GetEncodedLocation( bHasEncodedLocation, m_ABLData.Locate.dEncodedLat, m_ABLData.Locate.dEncodedLong );

		if( bHasEncodedLocation )
		{
			m_ABLData.Id.dwEMSFlags |= EMS_ABL_ENCODED_LOCN_BCN;

			if( !m_bIsRefBcn )
			{
				CEMSCoordSystem oCoordSys;

				EMSLOCATION lcnCompt, lcnRef;
				memset( &lcnCompt, 0, sizeof( EMSLOCATION ) );
				memset( &lcnRef, 0, sizeof( EMSLOCATION ) );

				lcnCompt.degLatitude = m_ABLData.Locate.dLatitude;
				lcnCompt.degLongitude = m_ABLData.Locate.dLongitude;
				lcnCompt.fAltitude = (float)m_ABLData.Locate.dAltitude;

				lcnRef.degLatitude = m_ABLData.Locate.dEncodedLat;
				lcnRef.degLongitude = m_ABLData.Locate.dEncodedLong;
				lcnRef.fAltitude = 0.0;
				
				if( lcnCompt.degLatitude != 0.0 || lcnCompt.degLongitude != 0.0  )
				{
					// if it is computed
					m_ABLData.Locate.dLocationError = oCoordSys.DistanceApart( lcnCompt, lcnRef );
				}
				else
				{
					m_ABLData.Locate.dLocationError = 0.0;
				}
			}
		}
		else
		{
			m_ABLData.Locate.dEncodedLat = 0.0;
			m_ABLData.Locate.dEncodedLong = 0.0;
		}
	}
	
	// location error calculation
	if( m_bIsRefBcn && 
		( (0.0 != m_ABLData.Locate.dLatitude) || (0.0 != m_ABLData.Locate.dLongitude) ) )
	{
		CEMSCoordSystem oCoordSys;

		EMSLOCATION lcnCompt, lcnRef;
		memset( &lcnCompt, 0, sizeof( EMSLOCATION ) );
		memset( &lcnRef, 0, sizeof( EMSLOCATION ) );

		lcnCompt.degLatitude = m_ABLData.Locate.dLatitude;
		lcnCompt.degLongitude = m_ABLData.Locate.dLongitude;
		lcnCompt.fAltitude = (float)m_ABLData.Locate.dAltitude;

		lcnRef.degLatitude = m_RefBcnData.data.dLatitude;
		lcnRef.degLongitude = m_RefBcnData.data.dLongitude;
		lcnRef.fAltitude = m_RefBcnData.data.dAltitude;
		
		m_ABLData.Locate.dLocationError = oCoordSys.DistanceApart( lcnCompt, lcnRef );
		m_ABLData.Id.dwEMSFlags |= EMS_ABL_REFERENCE_BCN;
	}

	if( m_bCheckBcnCorrection )
	{
		m_ABLData.Id.dwEMSFlags |= EMS_ABL_CHECK_BCN_MSG;
	}
	else
	{
		m_ABLData.Id.dwEMSFlags &= ~EMS_ABL_CHECK_BCN_MSG;
	}
}

void 
CEMSActiveBeacon::_UpdateMergeLocateInfo(  CEMSPointerList<CEMSABLRawObject>&  lstRawLocations,
										   CEMSABLRawObject*                    pCentralObject  )
{
	CEMSABLRawObject* pRawObj = NULL;
	try
	{
		m_ABLData.Locate.dRadiusErrEllipse = sqrt( m_ABLData.Locate.dMajorError*m_ABLData.Locate.dMajorError
		                                          + m_ABLData.Locate.dMinorError*m_ABLData.Locate.dMinorError);

		if( pCentralObject )
		{
			m_ABLData.Locate.dTOANoise = pCentralObject->GetTOANoise();
			m_ABLData.Locate.dFOANoise = pCentralObject->GetFOANoise();
		}

		double dProb = 0.0;
		lstRawLocations.MoveFirst();
		pRawObj = lstRawLocations.GetNext();
		if( pRawObj )
		{
			dProb = (1 - pRawObj->GetProbability());
			pRawObj->Release();
			pRawObj = NULL;
		}

		while( pRawObj = lstRawLocations.GetNext() )
		{
			dProb *= (1 - pRawObj->GetProbability());
			pRawObj->Release();
			pRawObj = NULL;
		}

		m_ABLData.Locate.dProbability = 1 - dProb;
	}
	catch( ... )
	{
		if( pRawObj )
		{
			pRawObj->Release();
			pRawObj = NULL;
		}
		throw;
	}
}

void 
CEMSActiveBeacon::_UpdateMergeDetectInfo(  CEMSPointerList<CEMSABLRawObject>&  lstRawLocations  )
{
	CEMSABLRawObject* pRawObj = NULL;
	m_ABLData.Detect.timeDataStart = m_timeFirstData;
	m_ABLData.Detect.timeDataEnd = m_timeLastData;

	if( 0 == m_ABLData.Detect.wNumBursts )
	{
		m_ABLData.Detect.wNumBursts = m_ulBurstsCount;
	}
	
	if( 0 == m_ABLData.Detect.wNumMsgs )
	{
		m_ABLData.Detect.wNumMsgs = m_ulMsgCount;
	}

	if( lstRawLocations.Count() > 0 )
	{
		try
		{
			m_ABLData.Detect.timeDataStart.intTime = 0L;

			lstRawLocations.MoveFirst();
			while( pRawObj = lstRawLocations.GetNext() )
			{
				if( (m_ABLData.Detect.timeDataStart.intTime == 0) || (m_ABLData.Detect.timeDataStart.intTime > pRawObj->GetTimeFirstData().intTime) )
					m_ABLData.Detect.timeDataStart = pRawObj->GetTimeFirstData();
				
				pRawObj->Release();
				pRawObj = NULL;
			}
		}
		catch( ... )
		{
			if( pRawObj )
			{
				pRawObj->Release();
				pRawObj = NULL;
			}
			throw;
		}
	}
}

void 
CEMSActiveBeacon::_UpdateMergeBeaconInfo(  CEMSPointerList<CEMSABLRawObject>&  lstRawLocations  )
{
	CEMSABLRawObject* pRawObj = NULL;
	CEMSABLRawObject* pBestRawObj = NULL;

	ULONG ulNumOfLcns = m_lstRawLocations.Count();

	if( 0 == ulNumOfLcns )
	{
		m_ABLData.Id.wType = m_wType;
		m_ABLData.Id.wType &= 0xF7FF;
		m_ABLData.Beacon.dFrequency_Ave = m_dLastFrequency;
		m_ABLData.Beacon.dCNR_Ave = m_dLastPower;
		m_ABLData.Detect.wNumMsgs = m_ulMsgCount;
		m_ABLData.Detect.wNumBursts = m_ulBurstsCount;
		m_ABLData.Detect.wNumFOAMsgsUsed = 1;
		return;
	}

	try
	{
		CEMSPointerList<CEMSABLRawObject> lstRawLcns;
		if( lstRawLocations.Count() > 0 )
		{
			lstRawLcns = lstRawLocations;
		}
		else
		{
			lstRawLcns = m_lstRawLocations;
		}

		double dVal = 0.0;
		CEMSStandardDeviation<double> stDevCNR, stDevFreq, stDevBitRate, stDevRepRate;
		int iMaxMsgNum = -1;
		int iNumFOAMsg = -1;
		int iNumTOAMsg = -1;
		int iNumBurst = -1;
		lstRawLcns.MoveFirst();
		while( pRawObj = lstRawLcns.GetNext() )
		{
			//m_ABLData.Id.wType = pRawObj->GetLocationType();
			dVal = pRawObj->GetCNR();

			if( dVal > 0.0 )
				stDevCNR.AddReading( dVal );

			dVal = pRawObj->GetFrequency();
			if( dVal > 0.0 )
				stDevFreq.AddReading( dVal  );
			
			dVal = pRawObj->GetBitRate();
			if( dVal > 0.0 )
				stDevBitRate.AddReading( dVal );
			
			dVal = pRawObj->GetRepetitionRate();
			if( dVal > 0.0 )
				stDevRepRate.AddReading( dVal );

			if( !pBestRawObj )
			{
				pBestRawObj = pRawObj;
				pBestRawObj->AddRef();
				iMaxMsgNum = pBestRawObj->GetNumMsgs();
				iNumFOAMsg = pBestRawObj->GetNumFOAMsgUsed();
				iNumTOAMsg = pBestRawObj->GetNumTOAMsgUsed();
				iNumBurst = pBestRawObj->GetNumBurstsUsed();
			}
			else
			{
				bool bSwap = false;
				if( pRawObj->GetNumMsgs() > pBestRawObj->GetNumMsgs() )
				{
					//swap them
					bSwap = true;
				}
				else if( pRawObj->GetNumMsgs() == pBestRawObj->GetNumMsgs() )
				{
					if( pBestRawObj->GetTimeLastData().intTime <= pRawObj->GetTimeLastData().intTime )
					{
						bSwap = true;
					}
				}

				if( bSwap )
				{
					if( pRawObj->GetCNR_Ave() > 0.0 )
					{
						pBestRawObj->Release();
						pBestRawObj = NULL;
						pBestRawObj = pRawObj;
						pBestRawObj->AddRef();
					}

					iMaxMsgNum = pRawObj->GetNumMsgs();
					iNumFOAMsg = pRawObj->GetNumFOAMsgUsed();
					iNumTOAMsg = pRawObj->GetNumTOAMsgUsed();
					iNumBurst = pRawObj->GetNumBurstsUsed();
				}
			}

			pRawObj->Release();
			pRawObj = NULL;
		}

		m_ABLData.Id.wType = m_wType;
		m_ABLData.Id.wType &= 0xF7FF;

		if( m_ulBurstsCount < iNumBurst )
		{
			m_ulBurstsCount = iNumBurst;
		}
		
		if( m_ulMsgCount < iMaxMsgNum )
		{
			m_ulMsgCount = iMaxMsgNum;
		}

		m_ABLData.Detect.wNumMsgs = m_ulMsgCount;
		m_ABLData.Detect.wNumFOAMsgsUsed = iNumFOAMsg;
		m_ABLData.Detect.wNumTOAMsgsUsed = iNumTOAMsg;
		m_ABLData.Detect.wNumBursts = m_ulBurstsCount;

		if( pBestRawObj &&  (pBestRawObj->GetCNR_Ave() > 0.0) )
		{
			m_ABLData.Beacon.dCNR_Ave = pBestRawObj->GetCNR_Ave();
			m_ABLData.Beacon.dCNR_Sigma = pBestRawObj->GetCNR_Sigma();

			m_ABLData.Beacon.dFrequency_Ave = pBestRawObj->GetFrequency();
			m_ABLData.Beacon.dFrequency_Sigma = pBestRawObj->GetFrequency_Sigma();

			m_ABLData.Beacon.dBitRate_Ave = pBestRawObj->GetBitRate_Ave();
			m_ABLData.Beacon.dBitRate_Sigma = pBestRawObj->GetBitRate_Sigma();

			m_ABLData.Beacon.dRepetitionRate_Ave = pBestRawObj->GetRepetitionRate_Ave();
			m_ABLData.Beacon.dRepetitionRate_Sigma = pBestRawObj->GetRepetitionRate_Sigma();

			m_ABLData.Locate.dHDOP = pBestRawObj->GetHDOP();

			m_ABLData.Locate.dTOANoise = pBestRawObj->GetTOANoise();
			m_ABLData.Locate.dFOANoise = pBestRawObj->GetFOANoise();

//			m_ABLData.Id.wType = pBestRawObj->GetLocationType();
			m_ABLData.Id.wType = m_wType;
			m_ABLData.Id.wType &= 0xF7FF;

			pBestRawObj->Release();
			pBestRawObj = NULL;
		}
		else
		{
			m_ABLData.Beacon.dCNR_Ave = stDevCNR.GetMean();
			m_ABLData.Beacon.dCNR_Sigma = stDevCNR.GetStD();

			m_ABLData.Beacon.dFrequency_Ave = stDevFreq.GetMean();
			m_ABLData.Beacon.dFrequency_Sigma = stDevFreq.GetStD();

			m_ABLData.Beacon.dBitRate_Ave = stDevBitRate.GetMean();
			m_ABLData.Beacon.dBitRate_Sigma = stDevBitRate.GetStD();

			m_ABLData.Beacon.dRepetitionRate_Ave = stDevRepRate.GetMean();
			m_ABLData.Beacon.dRepetitionRate_Sigma = stDevRepRate.GetStD();
		}
	}
	catch( ... )
	{
		if( pRawObj )
		{
			pRawObj->Release();
			pRawObj = NULL;
		}
		if( pBestRawObj )
		{
			pBestRawObj->Release();
			pBestRawObj = NULL;
		}
		throw;
	}
}

void
CEMSActiveBeacon::_UpdateWaveFormID()
{
	m_ABLData.Id.wWaveFormID = m_wWaveFormID;
	
/*	if( 0 != m_ABLData.Id.wWaveFormID )
	{
		if( 1 == m_ABLData.Id.wWaveFormID )
		{
			m_ABLData.Id.wWaveFormID = -1;
		}
		else
		{
			m_ABLData.Id.wWaveFormID--;
		}
	}*/
}

void
CEMSActiveBeacon::_UpdateQualityFactors()
{
	_UpdateMQF();
	_UpdateLQF();
}


void
CEMSActiveBeacon::_UpdateMQF()
{
	m_ABLData.Locate.dEncodedQualityFactor = 0.0;

	if( (m_iMostRecentMsgFSErrors >= 0) &&
		(m_iMostRecentMsgPDF1Errors > 3) &&
		(m_ulBurstsCount == 1) )
	{
		// a) Frame synch errors >= 0
		// b) PDF1 errors > 3
		// c) Number of bursts = 1
		m_ABLData.Locate.dEncodedQualityFactor = 0.0;
	}

	if( (m_iMostRecentMsgFSErrors >= 0) &&
		(m_iMostRecentMsgPDF1Errors > 3) &&
		( (m_ulBurstsCount > 1) || (m_lstSATids.size() > 1) ) )
	{
		// a) Frame synch errors >= 0
		// b) PDF1 errors > 3
		// c) Number of bursts > 1 or Number of Satellites > 1
		m_ABLData.Locate.dEncodedQualityFactor = 1.0;
	}

	if( (m_iMostRecentMsgFSErrors >= 0) &&
		(m_iMostRecentMsgPDF1Errors <= 3) &&
		(m_ulBurstsCount == 1) )
	{
		// a) Frame synch errors >= 0
		// b) PDF1 errors <= 3
		// c) Number of bursts = 1
		m_ABLData.Locate.dEncodedQualityFactor = 2.0;
	}

	if( (m_iMostRecentMsgFSErrors == 0) &&
		(m_iMostRecentMsgPDF1Errors <= 3) &&
		(m_iMostRecentMsgPDF2Errors < 2) &&
		(m_ulBurstsCount >= 1) )
	{
		// a) Frame synch errors = 0
		// b) PDF1 errors <= 3
		// c) PDF2 errors < 2
		// d) Number of bursts = 1
		m_ABLData.Locate.dEncodedQualityFactor = 3.0;
	}

	if( (m_iMostRecentMsgFSErrors == 0) &&
		(m_iMostRecentMsgPDF1Errors <= 3) &&
		(m_iMostRecentMsgPDF2Errors < 2) &&
		(m_ulBurstsCount > 1) && 
		(m_lstSATids.size() > 1) )
	{
		// a) Frame synch errors = 0
		// b) PDF1 errors <= 3
		// c) PDF2 errors < 2
		// d) Number of bursts > 1 and Number of Satellites > 1
		m_ABLData.Locate.dEncodedQualityFactor = 4.0;
	}

	if( (m_iMostRecentMsgFSErrors == 0) &&
		(m_iMostRecentMsgPDF1Errors == 0) &&
		(m_iMostRecentMsgPDF2Errors == 0) &&
		(m_ulBurstsCount > 1) && 
		(m_lstSATids.size() > 1) )
	{
		// a)	Frame synch errors = 0
		// b)	PDF1 errors = 0
		// c)	PDF2 errors = 0
		// d)	Number of bursts > 1 and Number of Satellites > 1
		m_ABLData.Locate.dEncodedQualityFactor = 5.0;
	}

}

void
CEMSActiveBeacon::_UpdateLQF()
{
	int iSatCount = _GetMEOSatsCount() + _GetLEOSatsCount() + _GetGEOSatsCount();

	switch( iSatCount )
	{
	case 0:
	case 1: 
	case 2:
		{
			m_ABLData.Locate.dComputedQualityFactor = 0.0;
		}
		break;
	case 3:
		{
			if( (m_ABLData.Locate.dRadiusErrEllipse < 20.00) &&
				(m_ABLData.Locate.dRadiusErrEllipse > 0.00) )
			{
				m_ABLData.Locate.dComputedQualityFactor = 2.0;
			}
			else
				m_ABLData.Locate.dComputedQualityFactor = 1.0;
		}
		break;
	case 4:
		{
			m_ABLData.Locate.dComputedQualityFactor = 3.0;
		}
		break;
	case 5:
		{
			m_ABLData.Locate.dComputedQualityFactor = 4.0;
		}
		break;
	default:
		{
			m_ABLData.Locate.dComputedQualityFactor = 5.0;
		}
		break;
	}
}

//void
//CEMSActiveBeacon::_UpdateLQF()
//{
//	m_ABLData.Locate.dComputedQualityFactor = 0.0;
//
//	if( (m_ABLData.Locate.dRadiusErrEllipse > 100.00) ||
//		(m_ABLData.Locate.dTOANoise > 1.0) ||
//		(m_ABLData.Locate.dFOANoise > 5.0) || 
//		((m_ABLData.Id.wType & EMSLOCTYPE_DETECT_ONLY) && 
//		 !(m_ABLData.Id.dwEMSFlags & EMS_ABL_ENCODED_LOCN_BCN) ) )
//	{
//		// a)Error Ellipse Radius> 100 km or
//		// b)TOA noise > 1 second or 
//		// c)FOA noise > 5 Hz or
//		// d)Detect only message (no encoded location) 
//		m_ABLData.Locate.dComputedQualityFactor = 0.0;
//		return;
//	}
//
//	if( (m_ABLData.Id.wType & EMSLOCTYPE_DETECT_ONLY) &&
//		(m_ABLData.Locate.dEncodedQualityFactor > 2.0 ) &&
//		(m_ABLData.Id.dwEMSFlags & EMS_ABL_ENCODED_LOCN_BCN) )
//	{
//		// a) Encoded location only (MQF>2)
//		m_ABLData.Locate.dComputedQualityFactor = 1.0;
//		return;
//	}
//
//	// by now it is a 1.0.
//	m_ABLData.Locate.dComputedQualityFactor = 1.0;
//	if( !(m_ABLData.Id.wType & EMSLOCTYPE_DETECT_ONLY) &&
//		(m_ABLData.Locate.dRadiusErrEllipse > 0.00) && (m_ABLData.Locate.dRadiusErrEllipse <= 100.00) && 
//		(m_ABLData.Locate.dFOANoise < 2.0) )
//	{
//		// a) Error Ellipse Radius >10 and
//		// b) FOA noise < 2 Hz
//		m_ABLData.Locate.dComputedQualityFactor = 2.0;
//	}
//
//	if( (m_ABLData.Locate.dRadiusErrEllipse < 10.00) &&
//		(m_ABLData.Locate.dRadiusErrEllipse > 0.00) &&
//		( (_GetMEOSatsCount() + _GetLEOSatsCount()) > 2) )
//	{
//		// a) Number of MEO (and/or LEO) satellites > 2 and
//		// b) Error Ellipse Radius <10
//		m_ABLData.Locate.dComputedQualityFactor = 3.0;
//	}
//
//	if( (m_ABLData.Id.dwEMSFlags & EMS_ABL_ENCODED_LOCN_BCN) && 
//		( (m_ABLData.Locate.dLatitude != 0.0) || (m_ABLData.Locate.dLongitude != 0.0) ) )
//	{
//		// a) Encoded Location  < 100 km from Computed Location
//
//		CEMSCoordSystem oCoordSys;
//
//		EMSLOCATION lcnCompt, lcnRef;
//		memset( &lcnCompt, 0, sizeof( EMSLOCATION ) );
//		memset( &lcnRef, 0, sizeof( EMSLOCATION ) );
//
//		lcnCompt.degLatitude = m_ABLData.Locate.dLatitude;
//		lcnCompt.degLongitude = m_ABLData.Locate.dLongitude;
//		lcnCompt.fAltitude = (float)m_ABLData.Locate.dAltitude;
//
//		lcnRef.degLatitude = m_ABLData.Locate.dEncodedLat;
//		lcnRef.degLongitude = m_ABLData.Locate.dEncodedLong;
//		lcnRef.fAltitude = 0.0;
//				
//		if( 100.0 > oCoordSys.DistanceApart( lcnCompt, lcnRef ) )
//		{
//			m_ABLData.Locate.dComputedQualityFactor = 4.0;
//		}
//	}
//
//	if( (m_ABLData.Locate.dLocationError > 0.00) &&
//		(m_ABLData.Locate.dLocationError < 5.00) )
//	{
//		// a)	Location Error < 5 km
//		m_ABLData.Locate.dComputedQualityFactor = 5.0;
//	}
//}

int
CEMSActiveBeacon::_GetMEOSatsCount()
{
	int iRet = 0;
	std::list<ULONG>::iterator iterSatIds;

	for( iterSatIds = m_lstSATids.begin(); iterSatIds != m_lstSATids.end(); iterSatIds++ )
	{
		if( 300 <= *iterSatIds )
		{
			iRet++;
		}
	}

	return iRet;
}

int
CEMSActiveBeacon::_GetLEOSatsCount()
{
	int iRet = 0;
	std::list<ULONG>::iterator iterSatIds;

	for( iterSatIds = m_lstSATids.begin(); iterSatIds != m_lstSATids.end(); iterSatIds++ )
	{
		if( 200 > *iterSatIds )
		{
			iRet++;
		}
	}

	return iRet;
}

int
CEMSActiveBeacon::_GetGEOSatsCount()
{
	int iRet = 0;
	std::list<ULONG>::iterator iterSatIds;

	for( iterSatIds = m_lstSATids.begin(); iterSatIds != m_lstSATids.end(); iterSatIds++ )
	{
		if( (200 <= *iterSatIds) && (300 > *iterSatIds) )
		{
			iRet++;
		}
	}
	return iRet;
}

void
CEMSActiveBeacon::GetAgedOutRawObjects( CEMSPointerList<CEMSABLRawObject>&  lstRawLocations )
{
	CEMSABLRawObject* pRawObject = NULL;
	
	try
	{
		bool bCalculateFirstTime = false;
		ms_mtxRawObjecsts.Enter();
		
		if( m_lstRawLocations.Count() > 0 )
		{
			m_lstRawLocations.MoveFirst();
			while( pRawObject = m_lstRawLocations.GetNext() )
			{
				if( pRawObject->IsAged( m_timeLastData, m_dAgeOutPeriod ) )
				{
					lstRawLocations.Add( pRawObject );
					m_lstRawLocations.RemoveCurrent();
					bCalculateFirstTime = true;
				}

				pRawObject->Release();
				pRawObject = NULL;
			}
		}

		if( bCalculateFirstTime )
		{
			m_timeFirstData.intTime = 0L;
			if( m_lstRawLocations.Count() > 0 )
			{
				m_timeFirstData = m_timeLastData;
			}
			else
			{
				m_lstRawLocations.MoveFirst();
				while( pRawObject = m_lstRawLocations.GetNext() )
				{
					if( (m_timeFirstData.intTime == 0) || 
						(m_timeFirstData.intTime > pRawObject->GetTimeFirstData().intTime) )
					{
						m_timeFirstData = pRawObject->GetTimeFirstData();
					}
					pRawObject->Release();
					pRawObject = NULL;
				}
			}
		}

		ms_mtxRawObjecsts.Leave();
	}
	catch( ... )
	{
		ms_mtxRawObjecsts.Leave();

		if( pRawObject )
		{
			pRawObject->Release();
			pRawObject = NULL;
		}
	}
}

void
CEMSActiveBeacon::FreePurgedRawObjects( CEMSPointerList<CEMSABLRawObject>&  lstRawLocations )
{
	CEMSABLRawObject* pRawObject = NULL;
	
	try
	{
		ms_mtxRawObjecsts.Enter();
		
		if( m_lstPurgedRawLocations.Count() > 0 )
		{
			m_lstPurgedRawLocations.MoveFirst();
			while( pRawObject = m_lstPurgedRawLocations.GetNext() )
			{
				lstRawLocations.Add( pRawObject );

				pRawObject->Release();
				pRawObject = NULL;
			}

			m_lstPurgedRawLocations.Clear();
		}

		ms_mtxRawObjecsts.Leave();
	}
	catch( ... )
	{
		ms_mtxRawObjecsts.Leave();

		if( pRawObject )
		{
			pRawObject->Release();
			pRawObject = NULL;
		}
	}
}

void
CEMSActiveBeacon::FreeAllRawObjects( CEMSPointerList<CEMSABLRawObject>&  lstRawLocations )
{
	CEMSABLRawObject* pRawObject = NULL;
	
	try
	{
		ms_mtxRawObjecsts.Enter();
		
		if( m_lstRawLocations.Count() > 0 )
		{
			m_lstRawLocations.MoveFirst();
			while( pRawObject = m_lstRawLocations.GetNext() )
			{
				lstRawLocations.Add( pRawObject );

				pRawObject->Release();
				pRawObject = NULL;
			}

			m_lstRawLocations.Clear();
		}

		ms_mtxRawObjecsts.Leave();

		FreePurgedRawObjects( lstRawLocations );
	}
	catch( ... )
	{
		ms_mtxRawObjecsts.Leave();

		if( pRawObject )
		{
			pRawObject->Release();
			pRawObject = NULL;
		}
	}
}



void 
CEMSActiveBeacon::_RemoveDuplicates( CEMSPointerList<CEMSABLRawObject>&  lstRawLocations, CEMSABLRawObject* pCentralObject )
{
	CEMSABLRawObject* pRawObject = NULL;
	CEMSABLRawObject* pRawObject1 = NULL;
	CEMSABLRawObject* pOldestObject = NULL;
	
	if( pCentralObject && (lstRawLocations.Count() > 1) )
	{
		try
		{
			CEMSPointerList<CEMSABLRawObject> lstRawObjsA, lstRawObjsB;
			CEMSPointerList<CEMSABLRawObject> lstRawObjs = lstRawLocations;
			lstRawLocations.Clear();

			lstRawObjs.MoveFirst();
			while( pRawObject = lstRawObjs.GetNext() )
			{
				if( pRawObject->IsSideA() )
				{
					lstRawObjsA.Add( pRawObject );
				}
				else
				{
					lstRawObjsB.Add( pRawObject );
				}

				lstRawObjs.RemoveCurrent();
				pRawObject->Release();
				pRawObject = NULL;
			}

			if( 0 == lstRawObjsB.Count() )
			{
				lstRawLocations = lstRawObjsA;
			}
			else if( 0 == lstRawObjsA.Count() )
			{
				lstRawLocations = lstRawObjsB;
			}
			else
			{
				lstRawObjsA.MoveFirst();
				while( pRawObject = lstRawObjsA.GetNext() )
				{
					if( pCentralObject == pRawObject )
					{
						lstRawLocations.Add( pRawObject );
						lstRawObjsA.RemoveCurrent();
					}
					else
					{
						bool bHasPeer = false;
						lstRawObjsB.MoveFirst();
						while( pRawObject1 = lstRawObjsB.GetNext() )
						{
							if( pRawObject->IsPeer( *pRawObject1 ) )
							{
								if( pRawObject1 == pCentralObject )
								{
									lstRawLocations.Add( pRawObject1 );
								}
								else
								{
									double dDist = pRawObject->GetDistanceApart( *pCentralObject );
									double dDist1 = pRawObject1->GetDistanceApart( *pCentralObject );

									if( pRawObject->GetDistanceApart( *pCentralObject ) <= pRawObject1->GetDistanceApart( *pCentralObject ) )
									{
										lstRawLocations.Add( pRawObject );
									}
									else
									{
										lstRawLocations.Add( pRawObject1 );
									}
								}

								lstRawObjsA.RemoveCurrent();
								lstRawObjsB.RemoveCurrent();
								bHasPeer = true;
							}
							pRawObject1->Release();
							pRawObject1 = NULL;
						}
						if( !bHasPeer )
						{
							lstRawLocations.Add( pRawObject );
							lstRawObjsA.RemoveCurrent();
						}
					}
					pRawObject->Release();
					pRawObject = NULL;
				}
			}
		}
		catch( ... )
		{
			if( pRawObject )
			{
				pRawObject->Release();
				pRawObject = NULL;
			}

			if( pRawObject1 )
			{
				pRawObject1->Release();
				pRawObject1 = NULL;
			}

			if( pOldestObject )
			{
				pOldestObject->Release();
				pOldestObject = NULL;
			}
			throw;
		}
	}
}

void
CEMSActiveBeacon::_SortCluster( CEMSPointerList<CEMSABLRawObject>&  lstRawLocations  )
{
	CEMSABLRawObject* pRawObject = NULL;
	CEMSABLRawObject* pOldestObject = NULL;
	
	try
	{
		CEMSPointerList<CEMSABLRawObject> lstRawObjs = lstRawLocations;
		lstRawLocations.Clear();

		while( 0 < lstRawObjs.Count() )
		{
			lstRawObjs.MoveFirst();
			while( pRawObject = lstRawObjs.GetNext() )
			{
				if( !pOldestObject )
				{
					pOldestObject = pRawObject;
				}
				else if( pRawObject->IsOlderThan( *pOldestObject ) )
				{
					pOldestObject->Release();
					pOldestObject = NULL;
					pOldestObject = pRawObject;
				}
				else
				{
					pRawObject->Release();
					pRawObject = NULL;
				}
			}

			if( pOldestObject )
			{
				lstRawLocations.Add( pOldestObject );

				lstRawObjs.MoveFirst();
				while( pRawObject = lstRawObjs.GetNext() )
				{
					if( pRawObject == pOldestObject )
					{
						lstRawObjs.RemoveCurrent();
						pRawObject->Release();
						pRawObject = NULL;
						break;
					}
					else
					{
						pRawObject->Release();
						pRawObject = NULL;
					}
				}

				pOldestObject->Release();
				pOldestObject = NULL;
			}
		}
	}
	catch( ... )
	{
		if( pRawObject )
		{
			pRawObject->Release();
			pRawObject = NULL;
		}

		if( pOldestObject )
		{
			pOldestObject->Release();
			pOldestObject = NULL;
		}
		throw;
	}
}

CEMSABLRawObject*
CEMSActiveBeacon::_FindCentralLocation( CEMSPointerList<CEMSABLRawObject>&  lstRawLocations )
{
	CEMSABLRawObject*  pRawObj = NULL;
	CEMSABLRawObject*  pRet = NULL;
	CEMSABLRawObject** apRawlocations = NULL;
	
	ULONG ulArrSize = 0;

	try
	{
		ULONG ulIndex = 0;
		ulArrSize = lstRawLocations.Count();
				
		if( 0 < ulArrSize )
		{
			double dClosestDistance = -1.0;
			ULONG  ulMaxCount = 0;

			apRawlocations = (CEMSABLRawObject**)malloc( sizeof( CEMSABLRawObject* ) * ulArrSize );
			if( NULL == apRawlocations )
			{
				THROW_NOMEMORY_EXCEPTION();
			}

			lstRawLocations.MoveFirst();
			while( pRawObj = lstRawLocations.GetNext() )
			{
				apRawlocations[ulIndex++] = pRawObj;
			}

			for( ULONG i = 0; i < ulArrSize; i++ )
			{
				double dSumDistance = 0.0;

				for( ULONG j = 0; j < ulArrSize; j++ )
				{
					if( j != i )
					{
						double dDist = apRawlocations[i]->GetDistanceApart( *(apRawlocations[j]) );
						dSumDistance += dDist;
					}
				}

				dSumDistance /= ( (double)(ulArrSize - 1) );

				if( (0.0 > dClosestDistance) || (dClosestDistance > dSumDistance) )
				{
					dClosestDistance = dSumDistance;
					
					if( pRet )
					{
						pRet->Release();
						pRet = NULL;
					}

					pRet = apRawlocations[i];
					pRet->AddRef();
				}
			}

			for( ulIndex = 0; ulIndex < ulArrSize; ulIndex++ )
			{
				apRawlocations[ulIndex]->Release();
				apRawlocations[ulIndex] = NULL;
			}
			free( apRawlocations );
			apRawlocations = NULL;
		}
	}
	catch( ... )
	{
		if( apRawlocations )
		{
			for( ULONG ulIndex = 0; ulIndex < ulArrSize; ulIndex++ )
			{
				apRawlocations[ulIndex]->Release();
				apRawlocations[ulIndex] = NULL;
			}
			free( *apRawlocations );
			apRawlocations = NULL;
		}

		if( pRawObj )
		{
			pRawObj->Release();
			pRawObj = NULL;
		}

		if( pRet )
		{
			pRet->Release();
			pRet = NULL;
		}

		throw;
	}
	return pRet;
}

void 
CEMSActiveBeacon::_FindBestCluster( CEMSPointerList<CEMSABLRawObject>&  lstRawLocations )
{
	CEMSABLRawObject*  pCentreRawObj = NULL;
	CEMSABLRawObject*  pRawObj = NULL;
	CEMSABLRawObject*  pRawObj1 = NULL;
	CEMSABLRawObject*  pRawObj2 = NULL;
	ULONG ulArrSize = 0;
	bool  bCheckDist = true;
	try
	{
		ULONG ulIndex = 0;
		ulArrSize = m_lstRawLocations.Count();
		
		if( 2 == ulArrSize ) // most likely Side A and B
		{
			m_lstRawLocations.MoveFirst();

			pRawObj1 = m_lstRawLocations.GetNext();
			
			if( pRawObj1 )
			{
				pRawObj2 = m_lstRawLocations.GetNext();
				if( pRawObj2 )
				{
					bCheckDist = false;
					if( ( pRawObj1->IsSideA() && !pRawObj2->IsSideA() ) ||
						( !pRawObj1->IsSideA() && pRawObj2->IsSideA() ) )
					{
						if( pRawObj1->IsSideA() )
						{
							lstRawLocations.Add( pRawObj1 );
						}
						else
						{
							lstRawLocations.Add( pRawObj2 );
						}
					}
					else
					{
						if( pRawObj1->IsDetectOnly() && pRawObj2->IsDetectOnly() )
						{
							// do nothing 
						}
						else
						{
							if( pRawObj1->IsDetectOnly() )
							{
								lstRawLocations.Add( pRawObj2 );
							}
							else if( pRawObj2->IsDetectOnly() )
							{
								lstRawLocations.Add( pRawObj1 );
							}
							else if( pRawObj1->IsOlderThan( *pRawObj2 ) )
							{
								lstRawLocations.Add( pRawObj2 );
							}
							else
							{
								lstRawLocations.Add( pRawObj2 );
							}
						}
					}
					pRawObj2->Release();
					pRawObj2 = NULL;
				}
				pRawObj1->Release();
				pRawObj1 = NULL;
			}
		}
		
		if( (0 < ulArrSize) && bCheckDist )
		{
			pCentreRawObj = _FindCentralLocation( m_lstRawLocations );

			if( pCentreRawObj )
			{
				m_lstRawLocations.MoveFirst();

				while( pRawObj = m_lstRawLocations.GetNext() )
				{
					double dDist = pRawObj->GetDistanceApart( *pCentreRawObj );
					if( dDist <= m_dRadius )
					{
						lstRawLocations.Add( pRawObj );
					}
					pRawObj->Release();
					pRawObj = NULL;
				}

				pCentreRawObj->Release();
				pCentreRawObj = NULL;
			}
		}
	}
	catch( ... )
	{
		if( pRawObj )
		{
			pRawObj->Release();
			pRawObj = NULL;
		}

		if( pRawObj1 )
		{
			pRawObj1->Release();
			pRawObj1 = NULL;
		}

		if( pRawObj2 )
		{
			pRawObj2->Release();
			pRawObj2 = NULL;
		}

		throw;
	}
}

EMS_RESULT 
CEMSActiveBeacon::GetBeaconDataEx( EMSABLData* pABLData,
				 				   ULONG* pulCount,
								   EMSABLRawData* aLocations )
{
	EMS_RESULT hr = EMS_OK;

	if( pABLData && pulCount )
	{
		CEMSABLRawObject* pRawObj = NULL;
		try
		{
			ms_mtxRawObjecsts.Enter();
			
			if( *pulCount >= m_lstRawLocations.Count() )
			{
				memcpy( pABLData, &m_ABLData, sizeof( EMSABLData ) );
				*pulCount = m_lstRawLocations.Count();
				ULONG ulIndex = 0;

				m_lstRawLocations.MoveFirst();
				while( pRawObj = m_lstRawLocations.GetNext() )
				{
					pRawObj->GetRawData( aLocations[ulIndex++] );
					pRawObj->Release();
					pRawObj = NULL;
				}
			}
			else
			{
				hr = EMS_ABL_MEM_OVERFLOW;
			}

			ms_mtxRawObjecsts.Leave();
		}
		catch( ... )
		{
			ms_mtxRawObjecsts.Leave();
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
CEMSActiveBeacon::GetBeaconData( EMSLOCATE* pABLData,
								 ULONG* pulCount,
								 EMSLOCATE* aLocations )
{
	EMS_RESULT hr = EMS_OK;

	if( pABLData && pulCount )
	{
		CEMSABLRawObject* pRawObj = NULL;
		try
		{
			ms_mtxRawObjecsts.Enter();
			
			if( *pulCount >= m_lstRawLocations.Count() )
			{
				memcpy( pABLData, &m_ABLData, sizeof( EMSABLData ) );
				*pulCount = m_lstRawLocations.Count();
				ULONG ulIndex = 0;

				m_lstRawLocations.MoveFirst();
				while( pRawObj = m_lstRawLocations.GetNext() )
				{
					pRawObj->GetLocateData( aLocations[ulIndex++] );
					pRawObj->Release();
					pRawObj = NULL;
				}
			}
			else
			{
				hr = EMS_ABL_MEM_OVERFLOW;
			}

			ms_mtxRawObjecsts.Leave();
		}
		catch( ... )
		{
			ms_mtxRawObjecsts.Leave();
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
CEMSActiveBeacon::GetCSVString( EMSABLData* pABLData, std::string& szCSVStr )
{
	szCSVStr = "";

	// this method needs to be redesigned and tested.
	
	if( pABLData )
	{
		char szLine[256];
		CEMSTime emsTime( pABLData->Id.timestamp );
		EMSTIMEFIELDS timeF;

		emsTime.GetTime( &timeF );
		memset( szLine, 0, sizeof(szLine) );
		sprintf( szLine, ms_szTimeFormat.c_str(), timeF.nYear, timeF.nMonth, timeF.nDay, timeF.nHour, timeF.nMinute, timeF.nSecond, timeF.lNanosecond);
		szCSVStr += szLine;
		szCSVStr += ',';

		szCSVStr += CBeaconMessage::ConvertToHexString( pABLData->Id.i64BeaconID );
//		szCSVStr += CEMSConversionUtil::ConvertToStringA( pABLData->Id.i64BeaconID );
		szCSVStr += ',';

		memset( szLine, 0, sizeof(szLine) );
		CBeaconMessage msg( pABLData->Id.acBeaconMsg );
		msg.GetHexString( (char*)szLine );

		for( int i = 0; i < 36; i++ )
		{
			szLine[i] = toupper( szLine[i] );
			if( szLine[i] ==  ' ' )
			{
				szLine[i] = '0';
			}
		}
		szCSVStr += szLine;
		szCSVStr += ',';
		
		szCSVStr += CEMSConversionUtil::ConvertToStringA( (unsigned long)pABLData->Id.wBitErrorFS );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( (unsigned long)pABLData->Id.wBitErrorField1 );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( (unsigned long)pABLData->Id.wBitErrorField2 );
		szCSVStr += ',';
		memset( szLine, 0, sizeof(szLine) );
		sprintf( szLine, "%X", (unsigned long)pABLData->Id.wType );
		szCSVStr += szLine;
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( (unsigned long)pABLData->Id.dwEMSFlags );
		szCSVStr += ',';


/*		for( i = 0; i < MAX_ABL_SATS; i++ )
		{
			if( pABLData->Id.aulSatIDs[i] > 0 )
			{
				szCSVStr += CEMSConversionUtil::ConvertToStringA( pABLData->Id.aulSatIDs[i] );
				szCSVStr += ' ';
			}
		}

		szCSVStr += ',';

		for( i = 0; i < MAX_ABL_LUTS; i++ )
		{
			if( pABLData->Id.aulLutIDs[i] > 0 )
			{
				szCSVStr += CEMSConversionUtil::ConvertToStringA( pABLData->Id.aulLutIDs[i] );
				szCSVStr += ' ';
			}
		}

*/		szCSVStr += ',';

//		emsTime.SetTime( pABLData->Locate.timestamp );
//		emsTime.GetTime( &timeF );
//		memset( szLine, 0, sizeof(szLine) );
//		sprintf( szLine, ms_szTimeFormat.c_str(), timeF.nYear, timeF.nMonth, timeF.nDay, timeF.nHour, timeF.nMinute, timeF.nSecond, timeF.lNanosecond);
//		szCSVStr += szLine;
//		szCSVStr += ',';

		szCSVStr += CEMSConversionUtil::ConvertToStringA( pABLData->Locate.dLatitude );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( pABLData->Locate.dLongitude );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( pABLData->Locate.dAltitude );
		szCSVStr += ',';

//		szCSVStr += CEMSConversionUtil::ConvertToStringA( pABLData->Locate.dConfidence );
//		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( pABLData->Locate.dProbability );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( pABLData->Locate.dMajorError );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( pABLData->Locate.dMinorError );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( pABLData->Locate.dHeading );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( pABLData->Locate.dRadiusErrEllipse );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( pABLData->Locate.dTOANoise );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( pABLData->Locate.dFOANoise );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( pABLData->Locate.dLocationError );
		szCSVStr += ',';

		//pABLData->Detect.
		szCSVStr += CEMSConversionUtil::ConvertToStringA( (unsigned long)pABLData->Detect.wNumMsgs );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( (unsigned long)pABLData->Detect.wNumMsgs );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( (unsigned long)pABLData->Detect.wNumBursts );
		szCSVStr += ',';
//		szCSVStr += CEMSConversionUtil::ConvertToStringA( (unsigned long)pABLData->Detect.wNumMissedBursts );
//		szCSVStr += ',';

		emsTime.SetTime( pABLData->Detect.timeDataStart );
		emsTime.GetTime( &timeF );
		memset( szLine, 0, sizeof(szLine) );
		sprintf( szLine, ms_szTimeFormat.c_str(), timeF.nYear, timeF.nMonth, timeF.nDay, timeF.nHour, timeF.nMinute, timeF.nSecond, timeF.lNanosecond);
		szCSVStr += szLine;
		szCSVStr += ',';

		emsTime.SetTime( pABLData->Detect.timeDataEnd );
		emsTime.GetTime( &timeF );
		memset( szLine, 0, sizeof(szLine) );
		sprintf( szLine, ms_szTimeFormat.c_str(), timeF.nYear, timeF.nMonth, timeF.nDay, timeF.nHour, timeF.nMinute, timeF.nSecond, timeF.lNanosecond);
		szCSVStr += szLine;
		szCSVStr += ',';

//		emsTime.SetTime( pABLData->Detect.timeNextLEOVisible );
//		emsTime.GetTime( &timeF );
//		memset( szLine, 0, sizeof(szLine) );
//		sprintf( szLine, ms_szTimeFormat.c_str(), timeF.nYear, timeF.nMonth, timeF.nDay, timeF.nHour, timeF.nMinute, timeF.nSecond, timeF.lNanosecond);
//		szCSVStr += szLine;
//		szCSVStr += ',';

//		szCSVStr += CEMSConversionUtil::ConvertToStringA( pABLData->Detect.ulNextLEOLUTID );
//		szCSVStr += ',';
//		szCSVStr += CEMSConversionUtil::ConvertToStringA( pABLData->Detect.ulNextLEOSatID );
//		szCSVStr += ',';
//		szCSVStr += CEMSConversionUtil::ConvertToStringA( pABLData->Detect.ulNextLEOPassID );
//		szCSVStr += ',';
    
/* 		{
			ULONG* aulSatId = NULL;
			ULONG ulTemp = 0;
			int iSize = sizeof( pABLData->Detect.acMissedSatIDs );

			aulSatId = new ULONG[iSize];
			if( aulSatId )
			{
				try
				{
					CEMSEncodedSatID::Expand( &pABLData->Detect.acMissedSatIDs, aulSatId, iSize, &ulTemp );
					for( int i = 0; i < ulTemp; i++ )
					{
						if( aulSatId[i] > 0 )
						{
							szCSVStr += CEMSConversionUtil::ConvertToStringA( aulSatId[i] );
							szCSVStr += ' ';
						}
					}

					szCSVStr += ',';

					delete []aulSatId;
					aulSatId = NULL;
				}
				catch( ... )
				{
					if( aulSatId )
					{
						delete []aulSatId;
						aulSatId = NULL;
					}
					throw;
				}
			}
			else
			{
				THROW_NOMEMORY_EXCEPTION();
			}
		}
*/
		szCSVStr += CEMSConversionUtil::ConvertToStringA( pABLData->Beacon.dCNR_Ave );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( pABLData->Beacon.dCNR_Sigma );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( pABLData->Beacon.dFrequency_Ave );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( pABLData->Beacon.dFrequency_Sigma );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( pABLData->Beacon.dBitRate_Ave );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( pABLData->Beacon.dBitRate_Sigma );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( pABLData->Beacon.dRepetitionRate_Ave );
		szCSVStr += ',';
		szCSVStr += CEMSConversionUtil::ConvertToStringA( pABLData->Beacon.dRepetitionRate_Sigma );
		
		szCSVStr += '\n';
	}
}

void 
CEMSActiveBeacon::GetABLSmryCSVHeaderString( std::string& szCSVHeader )
{
	szCSVHeader = "timestamp";
	szCSVHeader += ',';
	szCSVHeader += "i64BeaconID";
	szCSVHeader += ',';
	szCSVHeader += "acBeaconMsg[ 18 ]";
	szCSVHeader += ',';
	szCSVHeader += "wBitErrorFS";
	szCSVHeader += ',';
	szCSVHeader += "wBitErrorField1";
	szCSVHeader += ',';
	szCSVHeader += "wBitErrorField2";
	szCSVHeader += ',';
	szCSVHeader += "wType";
	szCSVHeader += ',';
	szCSVHeader += "dwStatus";
	szCSVHeader += ',';
	szCSVHeader += "acSatIDs[ 16 ]";
	szCSVHeader += ',';
	szCSVHeader += "acLutIDs[ 16 ]";
	szCSVHeader += ',';
	szCSVHeader += "acSARIDs[ 128 ]";
	szCSVHeader += ',';

	szCSVHeader += "timestamp";
	szCSVHeader += ',';
	szCSVHeader += "dLatitude";
	szCSVHeader += ',';
	szCSVHeader += "dLongitude";
	szCSVHeader += ',';
	szCSVHeader += "dAltitude";
	szCSVHeader += ',';
	szCSVHeader += "dConfidence";
	szCSVHeader += ',';
	szCSVHeader += "dProbability";
	szCSVHeader += ',';
	szCSVHeader += "dMajorError";
	szCSVHeader += ',';
	szCSVHeader += "dMinorError";
	szCSVHeader += ',';
	szCSVHeader += "dHeading";
	szCSVHeader += ',';
	szCSVHeader += "dRadiusErrEllipse";
	szCSVHeader += ',';
	szCSVHeader += "dTOANoise";
	szCSVHeader += ',';
	szCSVHeader += "dFOANoise";
	szCSVHeader += ',';
	szCSVHeader += "dLocationError";
	szCSVHeader += ',';

	szCSVHeader += "wNumMsgs";
	szCSVHeader += ',';
	szCSVHeader += "wNumMsgs";
	szCSVHeader += ',';
	szCSVHeader += "wNumBursts";
	szCSVHeader += ',';
//	szCSVHeader += "wNumMissedBursts";
//	szCSVHeader += ',';
	szCSVHeader += "timeDataStart";
	szCSVHeader += ',';
	szCSVHeader += "timeDataEnd";
	szCSVHeader += ',';
	szCSVHeader += "timeNextLEOVisible";
	szCSVHeader += ',';
	szCSVHeader += "ulNextLEOLUTID";
	szCSVHeader += ',';
	szCSVHeader += "ulNextLEOSatID";
	szCSVHeader += ',';
	szCSVHeader += "ulNextLEOPassID";
	szCSVHeader += ',';
	szCSVHeader += "acMissedSatIDs[ 128 ]";
	szCSVHeader += ',';

	szCSVHeader += "dCNR_Ave";
	szCSVHeader += ',';
	szCSVHeader += "dCNR_Sigma";
	szCSVHeader += ',';
	szCSVHeader += "dFrequency_Ave";
	szCSVHeader += ',';
	szCSVHeader += "dFrequency_Sigma";
	szCSVHeader += ',';
	szCSVHeader += "dBitRate_Ave";
	szCSVHeader += ',';
	szCSVHeader += "dBitRate_Sigma";
	szCSVHeader += ',';
	szCSVHeader += "dRepetitionRate_Ave";
	szCSVHeader += ',';
	szCSVHeader += "dRepetitionRate_Sigma";
	
	szCSVHeader += '\n';
}

void
CEMSActiveBeacon::_SetUpLogFiles() // TBV the implementation of this is still initial.
{
	if( m_bLoggingEnabled )
	{
		//	Tickets 25170: Zero can actually be a valid identifier!
		//if( 0 != m_i64BeaconId )
		{
			std::string szCSVHeaderLine;
			m_szAllRawLcnsFileName = m_szABLDir;
			m_szAllRawLcnsFileName += "AB_";
			m_szAllRawLcnsFileName += CBeaconMessage::ConvertToHexString( m_i64BeaconId );
	//		m_szAllRawLcnsFileName += CEMSConversionUtil::ConvertToStringA( m_i64BeaconId );

			if( 0 == m_ulHistoryID )
			{
				if ( !CreateDirectory( m_szABLDir.c_str(), 0 ) )
				{
					//error.
					int x = 1;
				}

				if ( !CreateDirectory( m_szAllRawLcnsFileName.c_str(), 0 ) )
				{
					//error.
					int x = 1;
					DWORD dw = GetLastError();
					if( 183 != dw )
					{
						x = 2;
					}
				}
			}

			m_szAllRawLcnsFileName += "\\";

			m_szAllRawLcnsFileName += CEMSConversionUtil::ConvertToStringA( ++m_ulHistoryID );

			m_szAllRawLcnsFileName += "";

			if ( !CreateDirectory( m_szAllRawLcnsFileName.c_str(), 0 ) )
			{
				//error.
			}

			m_szAllRawLcnsFileName += "\\";

			m_szCurrentRawLcnsFileName = m_szAllRawLcnsFileName;
			m_szRawBestClusterFileName = m_szAllRawLcnsFileName;
			m_szLocationFileName = m_szAllRawLcnsFileName;
			m_szSummaryFileName = m_szAllRawLcnsFileName;
			m_szExcludedLcnsFileName = m_szAllRawLcnsFileName;

			CEMSABLRawObject::GetLocateCSVHeaderString( szCSVHeaderLine );

			m_szAllRawLcnsFileName += "All_Input_Locations.csv";
			m_csvFAllInputLocations.OpenTextFile( m_szAllRawLcnsFileName.c_str(), "w" );
			m_csvFAllInputLocations.WriteText( szCSVHeaderLine.c_str() );

			m_szCurrentRawLcnsFileName += "Current_Raw_Locations.csv";
			m_csvFInputLocations.OpenTextFile( m_szCurrentRawLcnsFileName.c_str(), "w" );
			m_csvFInputLocations.WriteText( szCSVHeaderLine.c_str() );

			m_szRawBestClusterFileName += "Best_Cluster.csv";
			m_csvFBestCluster.OpenTextFile( m_szRawBestClusterFileName.c_str(), "w" );
			m_csvFBestCluster.WriteText( szCSVHeaderLine.c_str() );
			
			m_szLocationFileName += "Location_Data.csv";
			m_csvFOutputLocation.OpenTextFile( m_szLocationFileName.c_str(), "w" );
			m_csvFOutputLocation.WriteText( szCSVHeaderLine.c_str() );
			
			m_szExcludedLcnsFileName += "Excluded_Data.csv";
			m_csvFExcludedLocations.OpenTextFile( m_szExcludedLcnsFileName.c_str(), "w" );
			m_csvFExcludedLocations.WriteText( szCSVHeaderLine.c_str() );

			m_szSummaryFileName += "Summary_Data.csv";
			m_csvFOutputSummary.OpenTextFile( m_szSummaryFileName.c_str(), "w" );

			CEMSActiveBeacon::GetABLSmryCSVHeaderString( szCSVHeaderLine );
			m_csvFOutputSummary.WriteText( szCSVHeaderLine.c_str() );
		}
		//	Ticket 25170: Zero can actually be a valid identifier!
/*		else
		{
			int x = 5;
		}
*/
	}
}
